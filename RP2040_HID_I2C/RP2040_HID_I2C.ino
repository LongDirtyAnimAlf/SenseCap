#include <PacketSerial.h>
#include <Arduino.h>

#include "shared.h"

#define FW_MAJOR              56
#define FW_MINOR              12

#define WIRE_SPEED 100000UL

#ifdef ARDUINO_SEEED_INDICATOR_RP2040
#define USE_FLASH_STORE
#define BUZZER_PIN 19  //Buzzer GPIO
#define PACKET_UART_RXD 16
#define PACKET_UART_TXD 17
#endif

#ifdef USE_FLASH_STORE
#include <EEPROM.h>
int BoardInfoAddress = 0;
#endif

#define DAUGHTERBOARDCOUNT    16
#define BITS 16

const byte DefaultBoardSerial[12] = {0xFF,0x1F,0xFF,0x2F,0xFF,0x3F,0xFF,0x4F,0xFF,0x5F,0xFF,0x6F};

TBatteryBoard BatteryBoards[DAUGHTERBOARDCOUNT] = {0};

COBSPacketSerial myPacketSerial;
//PacketSerial_<COBS, 0, 1024> myPacketSerial;

TBoardInfo BoardInfo = 
{
  true, // DataInValid
  {0}, // Default BoardSerial
  0 // Default BoardNumber
};

unsigned long previousMillis = 0;  // will store last time fdata was updated
const long interval = 1000;  // interval at which to send sim-data (milliseconds)

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

bool IsCharging(TBatteryStatus Status)
{
  return ( (Status==BSCharge) || (Status==BSVoltage) || (Status==BSPulse) );
}
bool IsDisCharging(TBatteryStatus Status)
{
  return ( (Status==BSCurrent) || (Status==BSPower) || (Status==BSResistor) );
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

void onPacketReceived(const uint8_t *buffer, size_t size)
{
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

// the setup function runs once when you press reset or power the board
void setup()
{
  byte i;
  word y1,tempintcalc;
  char myHex[10] = "";

  Serial1.setRX(PACKET_UART_TXD);
  Serial1.setTX(PACKET_UART_RXD);
  Serial1.begin(115200);
  myPacketSerial.setStream(&Serial1);
  myPacketSerial.setPacketHandler(&onPacketReceived);
  sensor_power_on();

  for (i=0; i < DAUGHTERBOARDCOUNT;i++)
  {
    BatteryBoards[i].Data.V = 0;
    BatteryBoards[i].Data.I = 0;
    BatteryBoards[i].Data.E = 0;
    BatteryBoards[i].Data.T = 0;
    BatteryBoards[i].Data.Status = BSOff;
    BatteryBoards[i].Data.SetValue = 0;
  }

  Serial.begin(115200);
  Serial.println("Datalogger ready for use !!");
}

void loop() {
  PBatteryBoard LocalBatteryBoard;
  TBatteryBoard BatteryBoardCopy;
  PBatteryData LocalBatteryData;

  uint8_t data_buf[32];
  byte i,index;
  word WordValue;  

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you send the data
    previousMillis = currentMillis;

    for(i = 0; i < DAUGHTERBOARDCOUNT; i++)    
    {
      index = 0;

      data_buf[index++] = CMD_get_data;
      data_buf[index++] = i;

      WordValue = (20000 + random(2000) + (i*500)); // Voltage as 16 bit value with 3300mV reference
      memcpy(&data_buf[index], &WordValue, 2);
      index += 2;

      WordValue = (5000  + random(1000) - (i*200)); // Current as 16 bit value with 6000mA reference
      memcpy(&data_buf[index], &WordValue, 2);
      index += 2;

      myPacketSerial.send(data_buf, index);
    }
  }

  myPacketSerial.update();
  if (myPacketSerial.overflow())
  {
  }

}
