#include <PacketSerial.h>
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_TinyUSB.h"

#include "shared.h"

#define DEMO

#ifdef ARDUINO_WIO_TERMINAL
#define USE_FLASH_STORE
#define WIO_TERMINAL_USE_LCD
#define BUZZER_PIN WIO_BUZZER /* sig pin of the buzzer */
#define WireBattery Wire1
#define PIN_WIRE_BATT_SDA  PIN_WIRE1_SDA
#define PIN_WIRE_BATT_SCL  PIN_WIRE1_SCL
#endif

#ifdef SEEED_XIAO_M0
#define USE_FLASH_STORE
#define WireBattery Wire
#define PIN_WIRE_BATT_SDA PIN_WIRE_SDA
#define PIN_WIRE_BATT_SCL PIN_WIRE_SCL
#endif

#ifdef ARDUINO_SEEED_INDICATOR_RP2040
#define USE_FLASH_STORE
#define WireBattery Wire
//#define PIN_WIRE_BATT_SDA  20
//#define PIN_WIRE_BATT_SCL  21
#define PIN_WIRE_BATT_SDA  PIN_WIRE0_SDA
#define PIN_WIRE_BATT_SCL  PIN_WIRE0_SCL
#define RXD2 16
#define TXD2 17
#endif

#ifdef USE_FLASH_STORE
#ifdef ARDUINO_SEEED_INDICATOR_RP2040
#include <EEPROM.h>
int BoardInfoAddress = 0;
#else
#include "FlashStorage.h"
#endif
#endif

#ifdef WIO_TERMINAL_USE_LCD
#include "Free_Fonts.h" // Include the header file attached to this sketch
#include <TFT_eSPI.h> // Hardware-specific library
//#define CONSOLE_DEBUG
#endif

#define FW_MAJOR              56
#define FW_MINOR              8

#define DAUGHTERBOARDCOUNT    16
#define BITS 16

#ifdef CFG_TUD_ENDPOINT0_SIZE
#undef CFG_TUD_ENDPOINT0_SIZE
#endif

#ifndef CFG_TUD_ENDPOINT0_SIZE
#define CFG_TUD_ENDPOINT0_SIZE 16
#endif

#define    HID_INT_IN_EP_SIZE     CFG_TUD_ENDPOINT0_SIZE
#define    HID_INT_OUT_EP_SIZE    CFG_TUD_ENDPOINT0_SIZE

#ifdef WIO_TERMINAL_USE_LCD
#define  IDLECOLOR            TFT_CYAN
#define  CHARGECOLOR          TFT_MAGENTA
#define  DISCHARGECOLOR       TFT_RED
#define  READYCOLOR           TFT_BLUE

typedef enum _TChartType {
  ctDisplay,
  ctEnergy,
  ctCapacity,
  ctError,
  ctOff  
} TChartType;
#endif

#ifdef DEMO
unsigned long previousMillis = 0;  // will store last time fdata was updated
const long interval = 1000;  // interval at which to send sim-data (milliseconds)
#endif

void set_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* hid_report_out, uint16_t bufsize);

const byte DefaultBoardSerial[12] = {0xFF,0x1F,0xFF,0x2F,0xFF,0x3F,0xFF,0x4F,0xFF,0x5F,0xFF,0x6F};

struct
{
    char Serial[25];
    TBatteryData Data[DAUGHTERBOARDCOUNT] = {0};
    word Vmax[DAUGHTERBOARDCOUNT] = {0};
    word Imax[DAUGHTERBOARDCOUNT] = {0};
    word Firmware[DAUGHTERBOARDCOUNT] = {0};
} MyUSBDevice;

// HID report descriptor using TinyUSB's template
// Generic In Out with 64 bytes report (max)
uint8_t const desc_hid_report[] = {
    TUD_HID_REPORT_DESC_GENERIC_INOUT(HID_INT_OUT_EP_SIZE)
};

#ifdef WIO_TERMINAL_USE_LCD
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

 // Sprite objects
TFT_eSprite DataSprites[DAUGHTERBOARDCOUNT] = {
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft),
  TFT_eSprite(&tft)
  };

TChartType ChartType;
#endif

COBSPacketSerial myPacketSerial;

// USB HID object
Adafruit_USBD_HID usb_hid;

TBoardInfo BoardInfo = 
{
  true, // DataInValid
  {0}, // Default BoardSerial
  0 // Default BoardNumber
};

// Must be a global variable !!!
char mySerial[30];
char myFirmware[30];

// Reserve a portion of flash memory to store an "BoardInfo" variable
// and call it "my_flash_store".
#ifdef USE_FLASH_STORE
#ifndef ARDUINO_SEEED_INDICATOR_RP2040
FlashStorage(my_flash_store, TBoardInfo);
#endif
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

void InitWire(void)
{
  // Input on I2C pins to read values
  pinMode(PIN_WIRE_BATT_SDA, INPUT);
  pinMode(PIN_WIRE_BATT_SCL, INPUT);

  WireBattery.setSDA(PIN_WIRE_BATT_SDA);
  WireBattery.setSCL(PIN_WIRE_BATT_SCL);
 
   // Join i2c bus as master
  WireBattery.begin();
  //WireBattery.setClock(400000UL);
  // Set wire timeout to prevent stall on errors
  // This might call the wring timeout ... check !!!!!!!
  //PERIPH_WIRE1.setWireTimeout(100UL);
  //delay(1);

#ifdef ARDUINO_SEEED_INDICATOR_RP2040
  WireBattery.setTimeout(25, true);     // sets the maximum number of milliseconds to wait
#endif

  #ifdef SLOWI2CCLOCK
  #if defined(__SAMD51__)
  PERIPH_WIRE1.disableWIRE(); 
  int8_t idx = PERIPH_WIRE1.getSercomIndex();
  PERIPH_WIRE1.setClockSource(idx, SERCOM_CLOCK_SOURCE_12M, true);  // true  = core clock
  PERIPH_WIRE1.setClockSource(idx, SERCOM_CLOCK_SOURCE_32K, false); // false = slow clock
  PERIPH_WIRE1.enableWIRE();                             // Enable the I2C SERCOM 
  WireBattery.setClock(200000UL);
  #endif
  #endif
}

bool CheckWireStuck(void)
{
  bool Result = false;
  Result |= (digitalRead(PIN_WIRE_BATT_SDA) == LOW);  
  Result |= (digitalRead(PIN_WIRE_BATT_SCL) == LOW);
  return Result;    
}

void ResetWire(void)
{
  byte bits;

  // Disable Wire
  WireBattery.end();

  pinMode(PIN_WIRE_BATT_SDA, INPUT);
  while (digitalRead(PIN_WIRE_BATT_SDA) == 0)
  {

    // Send 9 clock pulses
    bits=0;
    digitalWrite(PIN_WIRE_BATT_SCL,LOW);
    for (uint8_t i=0;i<9;i++)
    {
      pinMode(PIN_WIRE_BATT_SCL, OUTPUT);
      delayMicroseconds(100);
      if (digitalRead(PIN_WIRE_BATT_SDA) == 0) bits += 1;
      pinMode(PIN_WIRE_BATT_SCL, INPUT);
      delayMicroseconds(100);
    }

    if (digitalRead(PIN_WIRE_BATT_SDA) == 1)
    {
      // Send stop
      pinMode(PIN_WIRE_BATT_SCL, OUTPUT);
      digitalWrite(PIN_WIRE_BATT_SDA,LOW);
      pinMode(PIN_WIRE_BATT_SDA, OUTPUT);
      delayMicroseconds(100);
      pinMode(PIN_WIRE_BATT_SCL, INPUT);
      delayMicroseconds(100);
      pinMode(PIN_WIRE_BATT_SDA, INPUT);
      delayMicroseconds(100);
      if (digitalRead(PIN_WIRE_BATT_SDA) == 1) break;
    }
    if (bits>=8) break;
  }

  // Re-enable wire
  InitWire();
}

uint16_t UpdateCrc(uint16_t crc, const uint8_t* data_p, uint8_t length)
{
  uint8_t x;

  while (length--){
      x = crc >> 8 ^ *data_p++;
      x ^= x>>4;
      crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x <<5)) ^ ((uint16_t)x);
  }
  return crc;
}

bool IsCharging(TBatteryStatus Status)
{
  return ( (Status==BSCharge) || (Status==BSVoltage) || (Status==BSPulse) );
}
bool IsDisCharging(TBatteryStatus Status)
{
  return ( (Status==BSCurrent) || (Status==BSPower) || (Status==BSResistor) );
}

#ifdef ARDUINO_SEEED_INDICATOR_RP2040

// sensor data send to  esp32
void sensor_data_send(uint8_t type, float data) {
  uint8_t data_buf[32] = { 0 };
  int index = 0;

  data_buf[0] = type;
  index++;

  memcpy(&data_buf[1], &data, sizeof(float));
  index += sizeof(float);

  myPacketSerial.send(data_buf, index);

#if DEBUG
  Serial.printf("---> send len:%d, data: ", index);
  for (int i = 0; i < index; i++) {
    Serial.printf("0x%x ", data_buf[i]);
  }
  Serial.println("");
#endif
}

void printUint16Hex(uint16_t value) {
  Serial.print(value < 4096 ? "0" : "");
  Serial.print(value < 256 ? "0" : "");
  Serial.print(value < 16 ? "0" : "");
  Serial.print(value, HEX);
}

void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2) {
  Serial.print("Serial: 0x");
  printUint16Hex(serial0);
  printUint16Hex(serial1);
  printUint16Hex(serial2);
  Serial.println();
}

void sensor_power_on(void) {
  pinMode(18, OUTPUT);
  digitalWrite(18, HIGH);
}

void sensor_power_off(void) {
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
}

/************************ beep ****************************/

#define Buzzer 19  //Buzzer GPIO

void beep_init(void) {
  pinMode(Buzzer, OUTPUT);
}
void beep_off(void) {
  digitalWrite(19, LOW);
}
void beep_on(void) {
  analogWrite(Buzzer, 127);
  delay(50);
  analogWrite(Buzzer, 0);
}

static bool shutdown_flag = false;

void onPacketReceived(const uint8_t *buffer, size_t size) {
#if DEBUG
  Serial.printf("<--- recv len:%d, data: ", size);
  for (int i = 0; i < size; i++) {
    Serial.printf("0x%x ", buffer[i]);
  }
  Serial.println("");
#endif
  if (size < 1) {
    return;
  }
}
#endif // ARDUINO_SEEED_INDICATOR_RP2040

// the setup function runs once when you press reset or power the board
void setup()
{
  byte i;
  word y1,tempintcalc;
  char myHex[10] = "";

  // This will remove the unwanted default string descriptor
  // And kill the unwanted (unneeded) serial port.
  Serial.end();

  #ifdef ARDUINO_SEEED_INDICATOR_RP2040
  Serial1.setRX(TXD2);
  Serial1.setTX(RXD2);
  Serial1.begin(115200);
  myPacketSerial.setStream(&Serial1);
  myPacketSerial.setPacketHandler(&onPacketReceived);
  sensor_power_on();
  #endif // ARDUINO_SEEED_INDICATOR_RP2040

  for (i=0; i < DAUGHTERBOARDCOUNT;i++)
  {
    MyUSBDevice.Data[i].V = 0;
    MyUSBDevice.Data[i].I = 0;
    MyUSBDevice.Data[i].E = 0;
    MyUSBDevice.Data[i].T = 0;
    MyUSBDevice.Data[i].Status = BSOff;
    MyUSBDevice.Data[i].StatusValue = 0;
  }

  // Manual begin() is required on core without built-in support e.g. mbed rp2040
  if (!TinyUSBDevice.isInitialized()) {
    TinyUSBDevice.begin(0);
  }

  usb_hid.setStringDescriptor("HIDI2C BATT_CTRL");
  
  USBDevice.setID(0x04D8,0x003F);
  USBDevice.setVersion(0x0002);
  USBDevice.setDeviceVersion(0x0002);

  USBDevice.setManufacturerDescriptor("Consulab for pleasure");
  USBDevice.setProductDescriptor("USB controler with HID");

  #ifdef USE_FLASH_STORE
  #ifdef ARDUINO_SEEED_INDICATOR_RP2040
  EEPROM.begin(512);
  EEPROM.get(BoardInfoAddress, BoardInfo);
  #else
  BoardInfo = my_flash_store.read();
  #endif
  #endif

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

  USBDevice.addStringDescriptor(mySerial);

  /*Init USB Device*/
  //usb_hid.setReportCallback(get_report_callback, set_report_callback);
  usb_hid.setReportCallback(NULL, set_report_callback);

  usb_hid.enableOutEndpoint(true);
  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));

  myFirmware[0] = '\0';  
  sprintf(myFirmware, "BATT-2025 V%02d-%02d", FW_MAJOR, FW_MINOR);
  myFirmware[16] = '\0';   
  USBDevice.setSerialDescriptor(myFirmware);

  usb_hid.begin();

  // If already enumerated, additional class driverr begin() e.g msc, hid, midi won't take effect until re-enumeration
  if (TinyUSBDevice.mounted()) {
    TinyUSBDevice.detach();
    delay(10);
    TinyUSBDevice.attach();
  }

  // For buzzer
  #if defined(ARDUINO_WIO_TERMINAL)
  pinMode(BUZZER_PIN, OUTPUT);
  #endif

  Serial.begin(115200);

  //while (!Serial)
  {

    ; // wait for serial port to connect. Needed for native USB port only

  }

  Serial.println("Datalogger ready for use !!");
  //Serial.print("EEPROM size:");  
  //Serial.println(EEPROM.length());

  InitWire();
}

void loop() {
  #ifdef TINYUSB_NEED_POLLING_TASK
  // Manual call tud_task since it isn't called by Core's background
  TinyUSBDevice.task();
  #endif

  #ifdef ARDUINO_SEEED_INDICATOR_RP2040
  //myPacketSerial.update();
  //if (myPacketSerial.overflow()) {
  //}
  #endif

  #ifdef DEMO
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you send the data
    previousMillis = currentMillis;

    #ifdef ARDUINO_SEEED_INDICATOR_RP2040
    uint8_t data_buf[32] = { 0 };
    word WordValue;
    for(byte i = 0; i < DAUGHTERBOARDCOUNT; i++)    
    {
      data_buf[0] = i;
      WordValue = (20000 + random(2000) + (i*500)); // Voltage as 16 bit value with 3300mV reference
      memcpy(&data_buf[1], &WordValue, 2);
      WordValue = (5000  + random(1000) - (i*200)); // Current as 16 bit value with 6000mA reference
      memcpy(&data_buf[3], &WordValue, 2);
      data_buf[5] = (uint8_t)BSCurrent;
      myPacketSerial.send(data_buf, 7);
      myPacketSerial.update();
    }

    #endif

  }
  #endif

}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void set_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* hid_report_out, uint16_t bufsize)
{
  (void) report_id;
  (void) report_type;

  byte hid_report_in[HID_INT_IN_EP_SIZE] = {0};
  byte I2CRXBUFFER[HID_INT_OUT_EP_SIZE] = {0};

	byte i,j;
  byte received,error = 0;
  byte cCmd,cBat,cLength,databyte = 0;
  byte slave_address = 0;
  
  WORD_VAL cRxCrc;
  WORD_VAL NewCRC;

  qword Ecalc;

  bool DataToSend = false;
  bool UpdateNeeded = false;

  #ifdef CONSOLE_DEBUG
  bool DEBUGONSCREEN = false;
  #endif

  PBatteryData LocalBatteryData;

	cCmd=hid_report_out[0];
	hid_report_in[0]=cCmd;
		
	switch (cCmd)
  {
	  case USB_CMD_get_serial:
		{
      for ( j=0; j<12; j++ )
      {
        hid_report_in[j+1] = BoardInfo.BoardSerial[j];
      }

      delay(1);
      DataToSend=true;
      break;
    }

		case USB_CMD_set_serial:
		{
      for ( j=0; j<12; j++ )
      {
        BoardInfo.BoardSerial[j] = hid_report_out[j+1];
        hid_report_in[j+1] = BoardInfo.BoardSerial[j];
      }
      BoardInfo.InValid = false;
      #ifdef USE_FLASH_STORE
      #ifdef ARDUINO_SEEED_INDICATOR_RP2040
      EEPROM.put(BoardInfoAddress, BoardInfo);
      EEPROM.commit();
      #else
      my_flash_store.write(BoardInfo);
      #endif
      #endif
      delay(1);
			DataToSend=true;
			break;
		}

		case USB_CMD_get_firmware:
		{
			hid_report_in[1]=FW_MAJOR;
			hid_report_in[2]=FW_MINOR;
      delay(1);
			DataToSend=true;
			break;
		}

    case USB_CMD_get_board_number:
    {
      hid_report_in[1] = BoardInfo.BoardNumber;
      delay(1);
			DataToSend=true;
      break;
    }

    case USB_CMD_set_board_number:
    {
      BoardInfo.BoardNumber = hid_report_out[1];
      BoardInfo.InValid = false;
      #ifdef USE_FLASH_STORE
      #ifdef ARDUINO_SEEED_INDICATOR_RP2040
      EEPROM.put(BoardInfoAddress, BoardInfo);
      EEPROM.commit();      
      #else
      my_flash_store.write(BoardInfo);
      #endif
      #endif
      delay(1);
			DataToSend=true;
      break;
    }

		default:
		{
			DataToSend=true;

      cBat=hid_report_out[1];

      LocalBatteryData = &MyUSBDevice.Data[cBat];

      LocalBatteryData->DatSendError = 0;
      LocalBatteryData->BytesReceived = 0;
      LocalBatteryData->CRCError = false;
      LocalBatteryData->Blocked = false;

      #if defined(ARDUINO_WIO_TERMINAL)
      UpdateNeeded = (ChartType == ctError);
      #else
      UpdateNeeded = false;
      #endif

      #ifdef CONSOLE_DEBUG
      DEBUGONSCREEN = (cBat==0);
      #endif

      if (cBat>=DAUGHTERBOARDCOUNT)
      {
	      hid_report_in[0]=CMD_error;
			  DataToSend=true;
			  break;
      }

      #ifndef COIN
      slave_address=((cBat)<<1U)+0x20U;
      #else
      slave_address=(cBat)/4;
      slave_address<<=1;
      slave_address+=0x20;
      #endif

      cLength=hid_report_out[2];

      #ifndef COIN
      if (cLength>13)
      #else
      if (cLength>12)
      #endif
      {
        cCmd=0;
        cLength=0;
      }

      if (cCmd == CMD_set_value)
      {
        if ((cLength == 5) || (cLength == 7))
        {
          LocalBatteryData->Status=TBatteryStatus(hid_report_out[3]);
          LocalBatteryData->StatusValue=hid_report_out[4]+256*hid_report_out[5]+256*256*hid_report_out[6]+256*256*256*hid_report_out[7];
          if (LocalBatteryData->StatusValue==0)
          {
            //LocalBatteryData->Status=BSOff;
          }
          UpdateNeeded = true;
        }
      }

      if (cCmd == CMD_set_energy)
      {
        if (cLength == 4)
        {
          Ecalc=(qword(hid_report_out[3])+qword(hid_report_out[4])*256+qword(hid_report_out[5])*256*256+qword(hid_report_out[6])*256*256*256);
          Ecalc *= 65536;
          Ecalc /= (8*32*3600/**1000*/);
          LocalBatteryData->E = dword(Ecalc);
          UpdateNeeded = true;
        }
      }

      WireBattery.flush();

      if (CheckWireStuck())
      {
        delay(1);
        if (CheckWireStuck())
        {
          // We have a severe bus-error !!!!!
          ResetWire();          
          LocalBatteryData->Blocked = CheckWireStuck();
        }
      }

      // Are we good to go ?
      if (!LocalBatteryData->Blocked)
      {
        // Prepare data towards device through I2C

        NewCRC.Val = 0xFFFFU;

        //WireBattery.flush();
        WireBattery.beginTransmission((slave_address)); 
        NewCRC.Val = UpdateCrc(NewCRC.Val, &slave_address, 1);

        databyte = cCmd; 
        WireBattery.write(databyte);
        NewCRC.Val = UpdateCrc(NewCRC.Val, &databyte, 1);

        #ifndef COIN
        databyte = cLength; 
        WireBattery.write(databyte);
        NewCRC.Val = UpdateCrc(NewCRC.Val, &databyte, 1);
        #else
        databyte = cLength+1; 
        WireBattery.write(databyte);
        NewCRC.Val = UpdateCrc(NewCRC.Val, &databyte, 1);
        databyte = cBat % 4; 
        WireBattery.write(databyte);
        NewCRC.Val = UpdateCrc(NewCRC.Val, &databyte, 1);
        #endif

        if (cLength>0)
        {
          for ( i=0; i < cLength;i++ )
          {
            databyte = hid_report_out[i+3];
            WireBattery.write(databyte);
          }
          NewCRC.Val = UpdateCrc(NewCRC.Val,(byte*)&hid_report_out[3],cLength);
        }

        WireBattery.write(NewCRC.bytes.HB);
        WireBattery.write(NewCRC.bytes.LB);

        // now, send all data !!
        error = WireBattery.endTransmission(false /* false will send a restart */);
  
        if (error)
        {
          LocalBatteryData->DatSendError = error;

          #ifdef CONSOLE_DEBUG
          #ifdef WIO_TERMINAL_USE_LCD          
          tft.print("Batt #");              
          tft.print(cBat);              
          tft.print(". ");              
          switch (error)
          {
            case 1:  {tft.println("Data too long error."); break;}
            case 2:  {tft.println("NACK on address."); break;}
            case 3:  {tft.println("NACK on Data->"); break;}
            case 5:  {tft.println("Timeout->"); break;}
            default: {tft.println("Other error."); break;}
          } 
          #endif
          #endif

          if (error=2)
          {
            // We have a severe bus-error !!!!!
            ResetWire();          
            //LocalBatteryData->Blocked = CheckWireStuck();
            LocalBatteryData->Blocked = true;
          }
        }

        NewCRC.Val = 0xFFFFU;
        cRxCrc.Val = 0U;
        cLength = 0;
        cCmd = USB_CMD_error;

        if (!error)
        {
          // Receive slave-address and 16 databytes

          #ifdef ARDUINO_SEEED_INDICATOR_RP2040
          WireBattery.clearTimeoutFlag();            
          #endif

          received = WireBattery.requestFrom(slave_address, 17, true);    // request max 17 bytes from slave device #2

          LocalBatteryData->BytesReceived = received;

          #ifdef CONSOLE_DEBUG
          if (DEBUGONSCREEN)
          {
              //tft.print(received);              
              //tft.println(" bytes data received");    
          }
          #endif

          if (received==0)
          {
            #ifdef ARDUINO_SEEED_INDICATOR_RP2040
            if (WireBattery.getTimeoutFlag())
            {

            }
            #endif
            //playTone(2000,100);          
            #ifdef CONSOLE_DEBUG
            #ifdef WIO_TERMINAL_USE_LCD            
            tft.print("Batt #");              
            tft.print(cBat);              
            tft.print(". ");              
            tft.println("No data received.");    
            #endif
            #endif
          }
          else
          {
            LocalBatteryData->BytesReceived = 0;
            if (WireBattery.available())
            {
              slave_address = WireBattery.read();
              LocalBatteryData->BytesReceived++;
            }

            NewCRC.Val = UpdateCrc(NewCRC.Val, &slave_address, 1);

            LocalBatteryData->Address = slave_address;

            j = 0;
            while ( WireBattery.available() && (j<HID_INT_OUT_EP_SIZE) )
            {
              I2CRXBUFFER[j++] = WireBattery.read();
            }
            LocalBatteryData->BytesReceived += j;
            
            j = 0;
            cCmd = I2CRXBUFFER[j++];
            NewCRC.Val = UpdateCrc(NewCRC.Val, &cCmd, 1);
            #ifdef CONSOLE_DEBUG
            #ifdef WIO_TERMINAL_USE_LCD            
            if (DEBUGONSCREEN)
            {
              //tft.print("Command: ");              
              //tft.print(cCmd,10);              
              //tft.println(" received");    
            }
            #endif
            #endif

            cLength = I2CRXBUFFER[j++];
            NewCRC.Val = UpdateCrc(NewCRC.Val, &cLength, 1);
            if (cLength>12) cLength=12;

            if (cLength>0)
            {
              NewCRC.Val = UpdateCrc(NewCRC.Val,(byte*)&I2CRXBUFFER[j],cLength);            
            }   

            j += cLength;

            cRxCrc.bytes.HB = I2CRXBUFFER[j++];
            cRxCrc.bytes.LB = I2CRXBUFFER[j++];

          }

          #ifdef CONSOLE_DEBUG
          if (DEBUGONSCREEN)
          {
              //tft.println("I2C ready");    
          }
          #endif
        }

        if (cRxCrc.Val != NewCRC.Val)
        {
          LocalBatteryData->CRCError = true;

          if (CheckWireStuck())
          {
            delay(1);
            if (CheckWireStuck())
            {
              // We have a severe bus-error !!!!!
              ResetWire();
              LocalBatteryData->Blocked = CheckWireStuck();
            }
          }
        }
        else
        {

          #ifdef CONSOLE_DEBUG
          #ifdef WIO_TERMINAL_USE_LCD          
          if (DEBUGONSCREEN)
          {
            tft.print("Command: ");              
            tft.print(cCmd,10);              
            tft.println(". CRC ok.");
          }
          #endif
          #endif

          if (cCmd == CMD_get_data)
          {
            LocalBatteryData->V = (I2CRXBUFFER[0 + 2] + I2CRXBUFFER[1 + 2]*256);
            LocalBatteryData->I = (I2CRXBUFFER[2 + 2] + I2CRXBUFFER[3 + 2]*256);
            LocalBatteryData->E = (I2CRXBUFFER[4 + 2] + I2CRXBUFFER[5 + 2]*256 + I2CRXBUFFER[6 + 2]*256*256 + I2CRXBUFFER[7 + 2]*256*256*256);
            Ecalc=(qword(I2CRXBUFFER[4 + 2])+qword(I2CRXBUFFER[5 + 2])*256+qword(I2CRXBUFFER[6 + 2])*256*256+qword(I2CRXBUFFER[7 + 2])*256*256*256);
            Ecalc *= 65536;
            Ecalc /= (8*32*3600/**1000*/);
            LocalBatteryData->E = dword(Ecalc);
            //MyUSBDevice.Data[cBat].C = MyUSBDevice.Data[cBat].E / (MyUSBDevice.Vmax[cBat]*MyUSBDevice.Data[cBat].V / ((1 << BITS)-1));
            LocalBatteryData->T = (I2CRXBUFFER[8 + 2] + I2CRXBUFFER[9 + 2]*256);
            UpdateNeeded = true;
          }

          if (cCmd == CMD_set_value)
          {
            if (cLength > 4)
            {
              LocalBatteryData->Status=TBatteryStatus(I2CRXBUFFER[4 + 2]);
              LocalBatteryData->StatusValue=I2CRXBUFFER[5 + 2]+256*I2CRXBUFFER[6 + 2]+256*256*I2CRXBUFFER[7 + 2]+256*256*256*I2CRXBUFFER[8 + 2];
              if (LocalBatteryData->StatusValue==0)
              {
                //LocalBatteryData->Status=BSOff;
              }
              UpdateNeeded = true;
            }
          }

          if (cCmd == CMD_get_firmware)
          {
            MyUSBDevice.Firmware[cBat] = (I2CRXBUFFER[0 + 2]);
            MyUSBDevice.Imax[cBat] = (I2CRXBUFFER[2 + 2] + I2CRXBUFFER[3 + 2]*256);
            MyUSBDevice.Vmax[cBat] = (I2CRXBUFFER[4 + 2] + I2CRXBUFFER[5 + 2]*256);
            //UpdateNeeded = true;
          }
        }

        hid_report_in[0]=cCmd;
        hid_report_in[1]=cBat;
        hid_report_in[2]=cLength;

        for ( i=0; i < 13 ;i++ )
        {
          hid_report_in[i + 3]= I2CRXBUFFER[i + 2];
        }
    
        if (cRxCrc.Val != NewCRC.Val) 
        {
          hid_report_in[15]=slave_address;
          #ifdef CONSOLE_DEBUGGG
          #ifdef WIO_TERMINAL_USE_LCD          
          if (DEBUGONSCREEN)
          {
            for ( j=0; j<16; j++ )
            {
              tft.print(hid_report_out[j]);
              tft.print(":");
            }
            tft.println(" in.");
          }
          #endif
          #endif
        }
      }

      #ifdef WIO_TERMINAL_USE_LCD
      #ifndef CONSOLE_DEBUG
      LocalBatteryData->NeedsGUIUpdate = UpdateNeeded;
      #endif
      #endif

      #ifdef ARDUINO_SEEED_INDICATOR_RP2040
      if (UpdateNeeded)
      {
        uint8_t data_buf[32] = { 0 };
        word WordValue;
        data_buf[0] = cBat;
        WordValue = LocalBatteryData->V;
        memcpy(&data_buf[1], &WordValue, 2);
        WordValue = LocalBatteryData->I;
        memcpy(&data_buf[3], &WordValue, 2);
        data_buf[5] = (uint8_t)LocalBatteryData->Status;
        myPacketSerial.send(data_buf, 7);
        myPacketSerial.update();
      }
      #endif


		}
    break;
  }


	if (DataToSend)
  {
    usb_hid.sendReport(0, hid_report_in, sizeof(hid_report_in));
  }
}
