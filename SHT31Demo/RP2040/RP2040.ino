#include <PacketSerial.h>
#include <Arduino.h>
#include <Wire.h>
#include "SHT31.h"

#define BUZZER_PIN 19  //Buzzer GPIO
#define PACKET_UART_RXD 16
#define PACKET_UART_TXD 17

unsigned long previousMillis = 0;  // will store last time data was updated
const long interval = 1000;  // interval at which to send data (milliseconds)

//SHT35 sensor(PIN_WIRE0_SCL, 0x44);
SHT31 sensor = SHT31();

COBSPacketSerial myPacketSerial;
//PacketSerial_<COBS, 0, 1024> myPacketSerial;

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
  Serial1.setRX(PACKET_UART_TXD);
  Serial1.setTX(PACKET_UART_RXD);
  Serial1.begin(115200);
  myPacketSerial.setStream(&Serial1);
  myPacketSerial.setPacketHandler(&onPacketReceived);

  sensor_power_on();

  // If we have external sensors, init
  sensor.begin();  
  //sensor.reset();

  Serial.begin(115200);
  Serial.println("Datalogger ready for use !!");
}

void loop()
{

  uint8_t data_buf[32] = {0};
  uint8_t index;

  bool DataValid;
  float TF,HF;
  long T,H;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you send the data
    previousMillis = currentMillis;

    TF = sensor.getTemperature();
    HF = sensor.getHumidity();

    index = 0;

    data_buf[index++] = 0x55;

    T = long(trunc(TF * 1000));

    data_buf[index++] = T & 0xFF;
    data_buf[index++] = (T >> 8) & 0xFF;
    data_buf[index++] = (T >> 16) & 0xFF;
    data_buf[index++] = (T >> 24) & 0xFF;

    H = long(trunc(HF * 1000));

    data_buf[index++] = H & 0xFF;
    data_buf[index++] = (H >> 8) & 0xFF;
    data_buf[index++] = (H >> 16) & 0xFF;
    data_buf[index++] = (H >> 24) & 0xFF;

    // Send the data
    myPacketSerial.send(data_buf, index);
  }

  myPacketSerial.update();
  if (myPacketSerial.overflow())
  {
  }

  sleep_ms(10);
}
