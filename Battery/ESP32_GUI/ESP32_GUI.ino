/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html
 Install: lvgl*/

// This define is sometimes missing when using old ESP32-IDF version
//#define ESP_INTR_CPU_AFFINITY_AUTO 0

#include <Arduino.h>
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <PacketSerial.h>
#include <Ticker.h>
#include "Indicator_Extender.h"
#include "Indicator_SWSPI.h"
#include "ui.h"
#include "touch.h"
#include "shared.h"

#define HOR_RES 480
#define VER_RES 480

#define PACKET_UART_RXD 20
#define PACKET_UART_TXD 19

#define BUTTON_PIN 38

#define GFX_DEV_DEVICE ESP32_S3_RGB
#define RGB_PANEL
#define GFX_BL 45
Arduino_DataBus *bus = new Indicator_SWSPI(
    GFX_NOT_DEFINED /* DC */, EXPANDER_IO_LCD_CS /* CS */,
    SPI_SCLK /* SCK */, SPI_MOSI /* MOSI */, GFX_NOT_DEFINED /* MISO */);

Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    18 /* DE */, 17 /* VSYNC */, 16 /* HSYNC */, 21 /* PCLK */,
    4 /* R0 */, 3 /* R1 */, 2 /* R2 */, 1 /* R3 */, 0 /* R4 */,
    10 /* G0 */, 9 /* G1 */, 8 /* G2 */, 7 /* G3 */, 6 /* G4 */, 5 /* G5 */,
    15 /* B0 */, 14 /* B1 */, 13 /* B2 */, 12 /* B3 */, 11 /* B4 */,
    1 /* hsync_polarity */, 10 /* hsync_front_porch */, 8 /* hsync_pulse_width */, 50 /* hsync_back_porch */,
    1 /* vsync_polarity */, 10 /* vsync_front_porch */, 8 /* vsync_pulse_width */, 20 /* vsync_back_porch */);
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    HOR_RES /* width */, VER_RES /* height */, rgbpanel, 0 /* rotation */, false /* auto_flush */,
    bus, GFX_NOT_DEFINED /* RST */, st7701_indicator_init_operations, sizeof(st7701_indicator_init_operations));

TBatterySetting Batteries[DAUGHTERBOARDCOUNT]; // Battery data settings and results

volatile byte ActiveBatteryIndex = 0;

#ifdef STANDALONE
Ticker flipper;
volatile bool GetBatteryData = false;
volatile byte SendCommand[COMMAND_SIZE] = {0};
unsigned long ticksstore[DAUGHTERBOARDCOUNT] = {0};
#endif

COBSPacketSerial myPacketSerial;
//PacketSerial_<COBS, 0, 1024> myPacketSerial;

void onPacketReceived(const uint8_t* buffer, size_t size);

#if LV_USE_LOG != 0
void my_print(lv_log_level_t level, const char *buf)
{
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
#endif

uint32_t millis_cb(void)
{
  return millis();
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PRESSED;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_RELEASED;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

static void navbutton_event_handler(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * btn = lv_event_get_current_target_obj(e);

  static byte screenindex = 0;

  if (btn != NULL)
  {
    lv_obj_t * screen = lv_obj_get_screen(btn);
    uintptr_t btn_no = (uintptr_t)lv_event_get_user_data(e);

    if (screen == screen1) ActiveBatteryIndex = (btn_no-1);
    
    PBatterySetting SET = &Batteries[ActiveBatteryIndex];
    PRunDatas RDS = &SET->TestData.RunDatas;

    if(code == LV_EVENT_CLICKED)
    {
      if (screen != NULL)
      {
        //memLog();

        if (screen == screen1)
        {
          lv_screen_load(screenbase);          
          Setup_Screen2(ActiveBatteryIndex);
          Screen2SetData(RDS);
          screenindex = 1U;
        }
        else
        if (screen == screenbase)
        {
          if ((btn_no == btn_back) || (btn_no == btn_next)) // screen navigation
          {
            if ( (btn_no == btn_back) && (screenindex>0) ) screenindex--; // back button
            if ( (btn_no == btn_next) && (screenindex<3) ) screenindex++; // forwards button
            switch(screenindex)
            {
              case 0: {lv_screen_load(screen1);break;}
              case 1: {Setup_Screen2(ActiveBatteryIndex);Screen2SetData(RDS);break;}
              case 2: {Setup_Screen3(ActiveBatteryIndex);Screen3SetData(SET);break;}
              case 3: {Setup_Screen4(ActiveBatteryIndex);Screen4SetData(SET);break;}
            }
          }
        }
      }
    }
    else
    if (code == LV_EVENT_VALUE_CHANGED)
    {
      #ifdef STANDALONE
      dword temp;

      //bool checked = (lv_obj_get_state(btn, LV_BTN_PART_MAIN) & LV_STATE_CHECKED);
      bool checked = (lv_obj_get_state(btn) & LV_STATE_CHECKED);

      if ( (btn_no == btn_test_discharge) || (btn_no == btn_start_discharge) || (btn_no == btn_test_charge) || (btn_no == btn_start_charge) )
      {
        SendCommand[0] = CMD_set_value;
        SendCommand[1] = ActiveBatteryIndex;
        SendCommand[2] = 5U; // length
        if (!checked)
        {
          SET->TestData.SetStageMode = smOff;
          SET->TestData.SetStageValue = 0;
          SET->TestData.Active = bmIdle;
        }
        else
        {
          if ((btn_no == btn_test_discharge) || (btn_no == btn_start_discharge))
          {
            SET->TestData.SetStageMode = smCurrent;
            SET->TestData.SetStageValue = SET->Stages[FIXEDDISCHARGESTAGENUMBER].SetValue;
          }
          if ((btn_no == btn_test_charge) || (btn_no == btn_start_charge))
          {
            SET->TestData.SetStageMode = smCharge;
            SET->TestData.SetStageValue = SET->Stages[FIXEDCHARGESTAGENUMBER].SetValue;
          }
          if ((btn_no == btn_start_discharge) || (btn_no == btn_start_charge))          
          {
            SET->TestData.Active = bmActive;
          }
        }

        SendCommand[3] = (byte)SET->TestData.SetStageMode;
        temp = SET->TestData.SetStageValue;

        SendCommand[4] = (temp % 256);
        temp /= 256;
        SendCommand[5] = (temp % 256);
        temp /= 256;
        SendCommand[6] = (temp % 256);
        temp /= 256;
        SendCommand[7] = (temp % 256);
      }
      #endif
    }
  }
}

void AddMeasurementData(byte index, word V, word I, dword E, word T)
{
  static bool GoAround[DAUGHTERBOARDCOUNT] = {false};

  if (index<DAUGHTERBOARDCOUNT)
  {
    PRunDatas RDS  = &Batteries[index].TestData.RunDatas;

    // Reset GoAround in needed
    if ((RDS->Head == -1) && (RDS->Tail == -1)) GoAround[index] = false;

    if (GoAround[index])
    {
      RDS->Tail++;
      if (RDS->Tail >= DATASIZE) RDS->Tail = 0;
    }

    RDS->Head++;
    if (RDS->Head >= DATASIZE)
    {
      RDS->Head = 0;
      if (!GoAround[index]) RDS->Tail = 1; // Preset tail to last added value
      GoAround[index] = true;
    }

    //RDS->Energy += E;
    RDS->Temperature = T;    

    PMeasurementData MD = &RDS->BatteryDatas[RDS->Head];

    MD->V = V;
    MD->I = I;
  }
}

void ClearRunDatas(void)
{
  PRunDatas RDS;  
  for(byte index = 0; index < DAUGHTERBOARDCOUNT; index++)
  {
    RDS = &Batteries[index].TestData.RunDatas;

    memset(RDS->BatteryDatas, 0, DATASIZE * sizeof(TMeasurementData));
    RDS->CurrentStageNumber = 0;
    RDS->Capacity = 0;
    RDS->Energy = 0;
    RDS->Temperature = 0;
    RDS->Head = -1;
    RDS->Tail = -1;  

    for(byte i=tmNONE; i<tmLast; i++)
    {
      RDS->ThresholdResult[i].Enabled = false;
      RDS->ThresholdResult[i].Triggered = false;      
      RDS->ThresholdResult[i].Mode = tmNONE;
      RDS->ThresholdResult[i].SetValue = 0;
      RDS->ThresholdResult[i].GetValue = 0;      
    }
  }
}

#ifdef STANDALONE
void flip()
{
  GetBatteryData = true;
}
#endif

void setup()
{
  byte index;

  // Get memory for datastore
  PRunDatas RDS;  
  for(index = 0; index < DAUGHTERBOARDCOUNT; index++)
  {
    RDS = &Batteries[index].TestData.RunDatas;
    RDS->BatteryDatas = (TMeasurementData*)malloc(DATASIZE * sizeof(TMeasurementData));
  }
  // Initialize datastore  
  ClearRunDatas();

  // Set defaults;
  for(index = 0; index < DAUGHTERBOARDCOUNT; index++)
  {
    // Default iddle
    Batteries[index].Stages[IDDLESTAGENUMBER].Status = smOff;
    Batteries[index].Stages[IDDLESTAGENUMBER].SetValue = 0;

    // Default discharge
    Batteries[index].Stages[FIXEDDISCHARGESTAGENUMBER].Status = smCurrent; // a CC discharge
    Batteries[index].Stages[FIXEDDISCHARGESTAGENUMBER].SetValue = 500; // 500mA    
    //Batteries[index].Stages[FIXEDDISCHARGESTAGENUMBER].ThresholdSettings[tmMINV].Mode = tmMINV; //trivial: not needed
    Batteries[index].Stages[FIXEDDISCHARGESTAGENUMBER].ThresholdSettings[tmMINV].SetValue = 900; //900mV end value
    Batteries[index].Stages[FIXEDDISCHARGESTAGENUMBER].ThresholdSettings[tmMINV].Enabled = true;

    // Default charge
    Batteries[index].Stages[FIXEDCHARGESTAGENUMBER].Status = smCharge; // always a CC charge
    Batteries[index].Stages[FIXEDCHARGESTAGENUMBER].SetValue = 250; // 250mA charge current
    //Batteries[index].Stages[FIXEDCHARGESTAGENUMBER].ThresholdSettings[tmTIME].Mode = tmTIME; //trivial: not needed
    Batteries[index].Stages[FIXEDCHARGESTAGENUMBER].ThresholdSettings[tmTIME].SetValue = 57600; //16h
    Batteries[index].Stages[FIXEDCHARGESTAGENUMBER].ThresholdSettings[tmTIME].Enabled = true;
  }

  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  // while(!Serial);
  Serial.println("SenseCap Indicator startup");
  String LVGL_Arduino = String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.println(LVGL_Arduino);

  pinMode(BUTTON_PIN, INPUT);

  // Init Indicator hardware
  extender_init();

  myPacketSerial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, PACKET_UART_RXD, PACKET_UART_TXD);
  myPacketSerial.setStream(&Serial1);
  myPacketSerial.setPacketHandler(&onPacketReceived);

  // Init Display
  if (!gfx->begin(12000000L))
  {
    Serial.println("gfx->begin() failed!");
    Serial.println("Expect sever errors !!!");    
  }
  gfx->fillScreen(RGB565_BLACK);

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif
  lv_init();

  /*Set a tick source so that LVGL will know how much time elapsed. */
  lv_tick_set_cb(millis_cb);

  /* register print function for debugging */
#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print);
#endif

  lv_screen_init(gfx, HOR_RES, VER_RES);
  //lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_0);
  //lv_display_set_antialiasing(disp,false);

  // Init touch device
  touch_init(HOR_RES, VER_RES, 0); // rotation will be handled by lvgl
  /*Initialize the input device driver*/
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
  lv_indev_set_read_cb(indev, my_touchpad_read);

  CreateBaseScreen(navbutton_event_handler);
  Create_Screen1(navbutton_event_handler);
  lv_screen_load(screen1);

  Serial.println("Setup done");

  #ifdef STANDALONE
  flipper.attach_ms(250, flip);
  for(index = 0; index < DAUGHTERBOARDCOUNT; index++)
  {
    ticksstore[index] = millis();
  }
  #endif
}

void loop()
{
  static TickType_t xLastWakeTime = xTaskGetTickCount();
  
  /*
  unsigned long startTime = millis();
  while (digitalRead(BUTTON_PIN) == LOW)
  {
    if (millis() - startTime >= 10000)
    {
      ESP.restart();
      //esp_restart();
    }
  }
  */

  lv_task_handler(); /* let the GUI do its work */

  #ifdef STANDALONE

  byte i,j;
  uint8_t data_buf[32];

  // Do we have a valid command ?
  if ( (SendCommand[0] != 0U) && (SendCommand[0] != 255U) )
  {
    // Fill the data
    for (i=0; i<(SendCommand[2]+3); i++) data_buf[i] = SendCommand[i];
    // Reset command
    SendCommand[0] = 0U; 
    // Send the data request
    myPacketSerial.send(data_buf, i);
  }

  if (GetBatteryData)
  {
    GetBatteryData = false;
    
    for (i=0; i<DAUGHTERBOARDCOUNT; i++ )
    {
      j = 0;
      data_buf[j++] = CMD_get_data;
      data_buf[j++] = i;
      // Send the data request
      myPacketSerial.send(data_buf, j);
    }
  }
  #endif

  myPacketSerial.update();
  // Check for a receive buffer overflow (optional).
  if (myPacketSerial.overflow())
  {
    // Send an alert via a pin (e.g. make an overflow LED) or return a
    // user-defined packet to the sender.
  }

  // Simple delay always 5ms
  //delay(5);

  // This delay will adapt to the time consumed in the above tasks
  // If these tasks consume time, it will delay shorter
  vTaskDelayUntil( &xLastWakeTime, ( 5 / portTICK_PERIOD_MS ) );
}

unsigned long MillisBetween(unsigned long InitTicks, unsigned long EndTicks)
{
  unsigned long Result;
  Result = (EndTicks - InitTicks);
  if ((long)(~Result) < Result) Result = (long)(~Result);
  return (Result);
}

void onPacketReceived(const uint8_t* buffer, size_t size)
{
#ifdef YOLO
  Serial.printf("<--- recv len:%d, data: ", size);
  for (int i = 0; i < size; i++) {
    Serial.printf("0x%x ", buffer[i]);
  }
  Serial.println("");
#endif


  if (size < 1) {
    return;
  }

  byte counter = 0;

  //static word TestVolt[4] = {0};

  TCommands Command = (TCommands)buffer[counter++];

  if ( (Command == CMD_get_data) || (Command == CMD_set_value) )
  {
    byte BatteryIndex = buffer[counter++];

    if (Command == CMD_get_data)
    {
      dword dcalc;
      qword qcalc;
      word Volt = 0;
      word Amps = 0; 
      dword Energy = 0; 
      dword Capacity = 0; 
      word Temperature = 0; 
      unsigned long DT;

      PRunDatas RDS = NULL;

      memcpy(&Volt, &buffer[counter], 2);
      counter += 2;
      memcpy(&Amps, &buffer[counter], 2);
      counter += 2;
      memcpy(&Energy, &buffer[counter], 4);
      counter += 4;
      memcpy(&Temperature, &buffer[counter], 2);
      counter += 2;

      AddMeasurementData(BatteryIndex, Volt, Amps, Energy, Temperature);
      RDS = &Batteries[BatteryIndex].TestData.RunDatas;      

      // Put data on screen 1
      dcalc = Volt * 3300u;
      dcalc /= (dword)((1u << BITS)-1u);
      SetVoltageScreen1mV(BatteryIndex,(word)dcalc);

      qcalc = dcalc;

      dcalc = Amps * 6000u;
      dcalc /= (dword)((1u << BITS)-1u);
      SetCurrentScreen1mA(BatteryIndex,(word)dcalc);

      // Energy calculations
      qcalc *= dcalc; // this is now mV * mA = uW

      DT = MillisBetween(ticksstore[BatteryIndex],millis());
      ticksstore[BatteryIndex] = millis();

      qcalc *= DT; // this is now uW * ms = uWms
      qcalc /= (3600ULL*1000ULL); // this is uWh !!      
      
      RDS->Energy += qcalc;

      // Capacity calculations
      qcalc = dcalc; // this is now mA
      qcalc *= DT; // this is now mA * ms = mAms
      qcalc /= (3600ULL); // this is uAh !!      

      RDS->Capacity += qcalc;

      if (ActiveBatteryIndex==BatteryIndex)
      {
        Screen2AddData(Volt,Amps);
        Screen3AddData(Volt,Amps,RDS->Energy,RDS->Capacity);        
        //Screen3AddData(123,1234,1234*1000,12345*1000);        
        //Screen4AddData(Volt,Amps);
      }
    }

    if (Command == CMD_set_value)
    {
      lv_color_t c = LV_COLOR_MAKE(0,0,0);  
      TStageMode Status = (TStageMode)buffer[counter++];
      switch (Status)
      {
        case smCurrent:
        case smPower:
        case smResistor:
        {
          c = lv_palette_main(LV_PALETTE_DEEP_ORANGE);
          break;
        }
        case smCharge:
        case smVoltage:
        case smPulse:
        {
          c = lv_palette_main(LV_PALETTE_LIGHT_GREEN);
          break;
        }  
        case smOff:
        case smZero:
        case smDisabled:
        {
          c = LV_COLOR_MAKE(0X00,0xFF,0xFF);
          break;
        }
        default:
        {
          c = lv_palette_main(LV_PALETTE_YELLOW);
        }
      }
      SetLedScreen1(BatteryIndex,c);
    }
  }
}

void memLog()
{
  Serial.printf("Free heap: %d\n", esp_get_free_heap_size());
  Serial.printf("Largest block: %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
  Serial.printf(
  "  MALLOC_CAP_8BIT      %7zu bytes\n"
  "  MALLOC_CAP_DMA       %7zu bytes\n"
  "  MALLOC_CAP_SPIRAM    %7zu bytes\n"
  "  MALLOC_CAP_INTERNAL  %7zu bytes\n"
  "  MALLOC_CAP_DEFAULT   %7zu bytes\n"
  "  MALLOC_CAP_IRAM_8BIT %7zu bytes\n"
  "  MALLOC_CAP_RETENTION %7zu bytes\n",
  heap_caps_get_free_size(MALLOC_CAP_8BIT),
  heap_caps_get_free_size(MALLOC_CAP_DMA),
  heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
  heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
  heap_caps_get_free_size(MALLOC_CAP_DEFAULT),
  heap_caps_get_free_size(MALLOC_CAP_IRAM_8BIT),
  heap_caps_get_free_size(MALLOC_CAP_RETENTION));
}

