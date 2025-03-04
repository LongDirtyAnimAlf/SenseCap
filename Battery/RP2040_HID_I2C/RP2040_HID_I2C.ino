#define USE_LCD

#include <PacketSerial.h>
#include <Arduino.h>

#ifndef STANDALONE
#include "Adafruit_TinyUSB.h"
#endif

#include "shared.h"
#include "comms.h"
#include "storage.h"

#define BUZZER_PIN 19  //Buzzer GPIO
#define PACKET_UART_RXD 16
#define PACKET_UART_TXD 17

TBatteryBoard BatteryBoards[DAUGHTERBOARDCOUNT] = {0};

bool SlavesReady = false;

char resetReasonText[][24] = { "Unknown", "Power On / Brownout", "Run pin", "Software", "Watchdog Timer", "Debug reset" };

COBSPacketSerial myPacketSerial;
//PacketSerial_<COBS, 0, 1024> myPacketSerial;

#ifndef STANDALONE
// USB HID object
Adafruit_USBD_HID usb_hid;

// Must be a global variable !!!
char mySerial[30];
char myFirmware[30];
#endif

void playTone(int tone, int duration)
{
    #if defined(__SAMD51__)
    for (long i = 0; i < duration * 1000L; i += tone * 2)
    {
        digitalWrite(BUZZER_PIN, HIGH);
        delayMicroseconds(tone);
        digitalWrite(BUZZER_PIN, LOW);
        delayMicroseconds(tone);
    }
    #endif
}

void EngageSlaves(void)
{
  // Engage the slaves !!
  SlavesReady = true;
  digitalWrite(PIN_WIRE_BATT_SDA, LOW);  
  digitalWrite(PIN_WIRE_BATT_SCL, LOW);    
  pinMode(PIN_WIRE_BATT_SDA, OUTPUT);
  pinMode(PIN_WIRE_BATT_SCL, OUTPUT);
  delayMicroseconds(5000U);
  pinMode(PIN_WIRE_BATT_SDA, INPUT_PULLUP);
  pinMode(PIN_WIRE_BATT_SCL, INPUT_PULLUP);
  delayMicroseconds(1000U);
}

void InitWire(void)
{
  #ifdef DEBUG
  Serial.println("InitWire");
  #endif  

  #ifdef STANDALONE
  if (!SlavesReady) EngageSlaves();
  #endif

  pinMode(PIN_WIRE_BATT_SDA, INPUT_PULLUP);
  pinMode(PIN_WIRE_BATT_SCL, INPUT_PULLUP);

  WireBattery.setSDA(PIN_WIRE_BATT_SDA);
  WireBattery.setSCL(PIN_WIRE_BATT_SCL);
  WireBattery.setTimeout(50U, /*reset=*/false);     // sets the maximum number of milliseconds to wait and try to reset but in case of timeout !!
  WireBattery.clearTimeoutFlag();            
  WireBattery.setClock(100000UL);
  
  gpio_set_input_hysteresis_enabled(PIN_WIRE_BATT_SDA,true);
  gpio_set_slew_rate(PIN_WIRE_BATT_SDA,GPIO_SLEW_RATE_SLOW);
  gpio_set_drive_strength(PIN_WIRE_BATT_SDA,GPIO_DRIVE_STRENGTH_12MA);
  
  gpio_set_input_hysteresis_enabled(PIN_WIRE_BATT_SCL,true);
  gpio_set_slew_rate(PIN_WIRE_BATT_SCL,GPIO_SLEW_RATE_SLOW);
  gpio_set_drive_strength(PIN_WIRE_BATT_SCL,GPIO_DRIVE_STRENGTH_12MA);
}

bool IsCharging(TStageMode Status)
{
  return ( (Status==smCharge) || (Status==smVoltage) || (Status==smPulse) );
}
bool IsDisCharging(TStageMode Status)
{
  return ( (Status==smCurrent) || (Status==smPower) || (Status==smResistor) );
}

void sensor_power_on(void) {
  pinMode(18, OUTPUT);
  digitalWrite(18, HIGH);
}

void sensor_power_off(void) {
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
}

void beep_off(void) {
  digitalWrite(19, LOW);
}

void beep_on(void) {
  analogWrite(BUZZER_PIN, 127);
  delay(50);
  analogWrite(BUZZER_PIN, 0);
}

// the setup function runs once when you press reset or power the board
void setup()
{
  byte i;
  word y1,tempintcalc;
  char myHex[10] = "";

  // This will remove the unwanted default string descriptor
  // And kill the unwanted (unneeded) serial port.
  #ifndef DEBUG    
  Serial.end();
  #endif

  Serial1.setRX(PACKET_UART_TXD);
  Serial1.setTX(PACKET_UART_RXD);
  Serial1.begin(115200);
  myPacketSerial.setStream(&Serial1);
  #ifdef STANDALONE  
  myPacketSerial.setPacketHandler(&onPacketReceived);
  #endif
  sensor_power_on();
  
  for (i=0; i < DAUGHTERBOARDCOUNT;i++)
  {
    BatteryBoards[i].MD.V    = 0;
    BatteryBoards[i].MD.I    = 0;
    BatteryBoards[i].MD.E    = 0;
    BatteryBoards[i].MD.T    = 0;
    BatteryBoards[i].BM.Status = smOff;
    BatteryBoards[i].BM.SetValue = 0;
    BatteryBoards[i].I2CStatus.I2CAddress   = 0;
  }

  #ifndef STANDALONE

  // Manual begin() is required on core without built-in support e.g. mbed rp2040
  if (!TinyUSBDevice.isInitialized()) {
    TinyUSBDevice.begin(0);
  }

  //usb_hid.setStringDescriptor("HIDI2C BATT_CTRL");
  
  USBDevice.setID(0x04D8,0x003F);
  USBDevice.setVersion(0x0002);
  USBDevice.setDeviceVersion(0x0002);

  USBDevice.setManufacturerDescriptor("Consulab for pleasure");
  USBDevice.setProductDescriptor("USB controler with HID");

  storeInit();
  storeGetBoardInfo(&BoardInfo);

  if (BoardInfo.InValid)
  {
    for (i=0; i<12;i++)
    {
      BoardInfo.BoardSerial[i] = DefaultBoardSerial[i];
    }
  }

  i = 0;
  mySerial[0] = '\0';  
  while (i<12)
  {
    tempintcalc=(BoardInfo.BoardSerial[i]+(BoardInfo.BoardSerial[i+1]*256));
    sprintf(myHex, "%04X", tempintcalc);    
    strcat(mySerial,myHex);    
    i += 2;
    if (i<12) strcat(mySerial,"-");
  }
  mySerial[29] = '\0';  

  USBDevice.setSerialDescriptor(mySerial);  
  //USBDevice.addStringDescriptor(mySerial);

  /*Init USB Device*/
  //usb_hid.setReportCallback(get_report_callback, set_report_callback);
  usb_hid.setReportCallback(NULL, set_report_callback);

  usb_hid.enableOutEndpoint(true);
  usb_hid.setPollInterval(1);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));

  myFirmware[0] = '\0';  
  sprintf(myFirmware, "BATT-CAP-2025 V%02d-%02d", FW_MAJOR, FW_MINOR);
  myFirmware[16] = '\0';   
  //USBDevice.setSerialDescriptor(myFirmware);
  USBDevice.addStringDescriptor(myFirmware);  

  usb_hid.begin();

  #endif // STANDALONE

  // Enable serial (again) for programming and debugging
  #ifdef DEBUG  
  Serial.begin(115200);
  //while (!Serial) delay(10);
  #endif

  InitWire();

  // Get the reset reason
  RP2040::resetReason_t rr = rp2040.getResetReason(); 
  Serial.printf("RP2040 reset !!!!! Reset Reason %i: %s\r\n", rr, resetReasonText[rr]);

  // We might want to do someting with the WDT
  rp2040.wdt_begin(1000u);

  Serial.println("Datalogger ready for use !!");
}

void SendBatteryData(byte index)
{
  byte j,k;
  PBatteryBoard LocalBatteryBoard;
  PMeasurementData LocalBatteryData;

  uint8_t data_buf[32];
  WORD_VAL data;
  
  LocalBatteryBoard= &BatteryBoards[index];

  if ((LocalBatteryBoard->NeedsGUIUpdate) || (LocalBatteryBoard->NeedsDataUpdate))
  {
    if (LocalBatteryBoard->NeedsGUIUpdate)
    {
      LocalBatteryBoard->NeedsGUIUpdate = false;

      LocalBatteryData = &LocalBatteryBoard->MD;

      j = 0;

      data_buf[j++] = CMD_get_data;
      data_buf[j++] = index;

      // Voltage
      data.Val = LocalBatteryData->V;
      data_buf[j++] = data.bytes.LB;
      data_buf[j++] = data.bytes.HB;

      // Current            
      data.Val = LocalBatteryData->I;
      data_buf[j++] = data.bytes.LB;
      data_buf[j++] = data.bytes.HB;

      // Energy            
      data.Val = (word)(LocalBatteryData->E % 0x10000UL);
      data_buf[j++] = data.bytes.LB;
      data_buf[j++] = data.bytes.HB;

      data.Val = (word)(LocalBatteryData->E >> 16);
      data_buf[j++] = data.bytes.LB;
      data_buf[j++] = data.bytes.HB;

      // Temperature
      data.Val = LocalBatteryData->T;
      data_buf[j++] = data.bytes.LB;
      data_buf[j++] = data.bytes.HB;

      // Send the data
      myPacketSerial.send(data_buf, j);

      //Status
      j = 0;

      data_buf[j++] = CMD_set_value;
      data_buf[j++] = index;
      data_buf[j++] = (byte)LocalBatteryBoard->BM.Status;

      // Send the data
      myPacketSerial.send(data_buf, j);
    }

    if (LocalBatteryBoard->NeedsDataUpdate)
    {
      LocalBatteryBoard->NeedsDataUpdate = false;

      j = 0;

      data_buf[j++] = CMD_get_firmware;
      data_buf[j++] = index;

      // Vmax
      data.Val = LocalBatteryBoard->Vmax;
      data_buf[j++] = data.bytes.LB;
      data_buf[j++] = data.bytes.HB;

      // Imax
      data.Val = LocalBatteryBoard->Imax;
      data_buf[j++] = data.bytes.LB;
      data_buf[j++] = data.bytes.HB;

      // Firmware version
      data_buf[j++] = LocalBatteryBoard->Firmware;

      // Serial of daughterboard
      for (byte k=0; k<8; k++ )
      {
        data_buf[j++] = LocalBatteryBoard->Serial[k];
      }

      // Send the data
      myPacketSerial.send(data_buf, j);
    }
  }
}

void loop()
{
  rp2040.wdt_reset();

  #ifndef STANDALONE
  #ifdef TINYUSB_NEED_POLLING_TASK
  // Manual call tud_task since it isn't called by Core's background
  TinyUSBDevice.task();
  #endif
  #endif

  byte i,j;
  THIDData* PLocalHD;
  THIDData LocalHDCopy;

  #ifndef STANDALONE
  for (i=0; i<DAUGHTERBOARDCOUNT; i++ )
  {
    if (HIDData[i].DataReceived)
    {
      #ifndef TINYUSB_NEED_POLLING_TASK
      // Make a local copy of the data 
      // This is needed due to the fact that the USB HID interrupt may update the data when in this loop 
      noInterrupts();
      for ( j=0; j<HID_INT_OUT_EP_SIZE; j++ ) LocalHDCopy.HIDEPOUTData[j] = HIDData[i].HIDEPOUTData[j];
      LocalHDCopy.DataReceived = HIDData[i].DataReceived;
      HIDData[i].DataReceived = false;
      interrupts();
      PLocalHD = &LocalHDCopy; 
      #else
      PLocalHD = (THIDData*)&HIDData[i];
      PLocalHD->DataReceived = false;
      #endif

      // Rough I2C traffic indicator
      #ifndef ARDUINO_SEEED_INDICATOR_RP2040
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      #endif

      if (!SlavesReady) EngageSlaves();

      //Now perform the Data update     
      if (process_command(&PLocalHD->HIDEPOUTData,&PLocalHD->HIDEPINData))
      {
        // Send report back to host
        usb_hid.sendReport(0, &PLocalHD->HIDEPINData, HID_INT_IN_EP_SIZE);
        #ifdef USE_LCD
        SendBatteryData(i);        
        #endif
      }
    }
  }
  #endif // !STANDALONE

  myPacketSerial.update();
  if (myPacketSerial.overflow())
  {
  }

}

#ifdef STANDALONE
void onPacketReceived(const uint8_t *buffer, size_t size)
{
  byte OUTData[HID_INT_OUT_EP_SIZE] = {0};
  byte INData[HID_INT_IN_EP_SIZE] = {0};

  if (size < 1) {
    return;
  }

  if (size <= HID_INT_OUT_EP_SIZE)
  {
    for (byte i=0; i<size; i++ ) OUTData[i]=buffer[i];
    if (process_command(&OUTData,&INData))
    {
      #ifdef USE_LCD
      SendBatteryData(buffer[1]);        
      #endif
    }
    delayMicroseconds(1000U);
  }
}
#endif
