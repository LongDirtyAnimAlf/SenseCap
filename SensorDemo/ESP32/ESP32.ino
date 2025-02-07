/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html
 Install: lvgl*/

// This define is sometimes missing when using old ESP32-IDF version
//#define ESP_INTR_CPU_AFFINITY_AUTO 0

#include <Arduino.h>
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <PacketSerial.h>
#include "Indicator_Extender.h"
#include "Indicator_SWSPI.h"
#include "ui.h"
#include "touch.h"

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


COBSPacketSerial myPacketSerial;

void onPacketReceived(const uint8_t* buffer, size_t size);

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

// Main buttons event handler
static void event_handler(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * btn = lv_event_get_current_target_obj(e);

  if (btn != NULL)
  {
    if(code == LV_EVENT_CLICKED)
    {
      void * btn_no_void = (void*)lv_event_get_user_data(e);
      byte btn_no = (byte)((uintptr_t)btn_no_void);
      lv_obj_t * screen = lv_obj_get_screen(btn);
      if (screen != NULL)
      {
        Serial.println("Screen assigned");
        if (screen == screen2)
        {
          Serial.println("Screen 2");
          if (btn_no != 0)
          {
            Create_Screen3(event_handler);
            lv_screen_load(screen3);
          }
        }
        if (screen == screen3)
        {
          Serial.println("Screen 3");
          if (btn_no == 0)
          {
            lv_screen_load(screen2);
            lv_obj_delete(screen3);
          }
        }
      }
    }
  }
}

void setup()
{
  Serial.begin(115200);
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

  Screen2Create(event_handler);

  lv_screen_load(screen2);

  Serial.println("Setup done");
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

  myPacketSerial.update();
  // Check for a receive buffer overflow (optional).
  if (myPacketSerial.overflow())
  {
    // Send an alert via a pin (e.g. make an overflow LED) or return a
    // user-defined packet to the sender.
  }

  lv_task_handler(); /* let the GUI do its work */

  // Simple delay always 5ms
  //delay(5);

  // This delay will adapt to the time consumed in the above tasks
  // If these tasks consume time, it will delay shorter
  vTaskDelayUntil( &xLastWakeTime, ( 5 / portTICK_PERIOD_MS ) );
}

void onPacketReceived(const uint8_t* buffer, size_t size)
{
  if (size < 1) {
    return;
  }

  byte index = 0;
  byte Command = buffer[index++];
  if (Command == 0x55)
  {
    long Temperature = 0;
    long Humidity = 0; 

    memcpy(&Temperature, &buffer[index], sizeof(Temperature));
    index += sizeof(Temperature);
    memcpy(&Humidity, &buffer[index], sizeof(Humidity));
    index += sizeof(Humidity);

    Screen2AddData(Temperature,Humidity);
  }
}
