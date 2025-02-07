#include <PacketSerial.h>
#include <Arduino.h>
#include <Wire.h>

#define BUZZER_PIN 19  //Buzzer GPIO
#define PACKET_UART_RXD 16
#define PACKET_UART_TXD 17

COBSPacketSerial myPacketSerial;
//PacketSerial_<COBS, 0, 1024> myPacketSerial;

void InitWire(void)
{
  // Setup hardware
  Wire.setSDA(PIN_WIRE0_SDA);
  Wire.setSCL(PIN_WIRE0_SCL);
  Wire.setClock(100000UL);
  Wire.setTimeout(25U, true);     // sets the maximum number of milliseconds to wait and try to reset but in case of timeout !!
 
   // Join i2c bus as master
  Wire.begin();
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
  Serial1.setRX(PACKET_UART_TXD);
  Serial1.setTX(PACKET_UART_RXD);
  Serial1.begin(115200);
  myPacketSerial.setStream(&Serial1);
  myPacketSerial.setPacketHandler(&onPacketReceived);

  sensor_power_on();

  // If we have external sensors, init the I2C master
  //InitWire();

  Serial.begin(115200);
  Serial.println("Datalogger ready for use !!");
}

void loop()
{

  uint8_t data_buf[32] = {0};
  uint8_t index = 0;

  data_buf[index++] = 0x55;

  long T = 20000UL + random(2000);
  data_buf[index++] = T & 0xFF;
  data_buf[index++] = (T >> 8) & 0xFF;
  data_buf[index++] = (T >> 16) & 0xFF;
  data_buf[index++] = (T >> 24) & 0xFF;

  long H = 60000UL + random(5000);
  data_buf[index++] = H & 0xFF;
  data_buf[index++] = (H >> 8) & 0xFF;
  data_buf[index++] = (H >> 16) & 0xFF;
  data_buf[index++] = (H >> 24) & 0xFF;

  // Send the data
  myPacketSerial.send(data_buf, index);

  myPacketSerial.update();
  if (myPacketSerial.overflow())
  {
  }

  sleep_ms(1000);
}
