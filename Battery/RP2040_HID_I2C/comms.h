#ifndef _COMMS_H_
#define _COMMS_H_

#ifdef ARDUINO_WIO_TERMINAL
#define USE_LCD 
#define BUZZER_PIN WIO_BUZZER /* sig pin of the buzzer */
//#define PIN_WIRE_SERCOM SERCOM3
//#define PIN_WIRE_BATT_SDA  PIN_WIRE_SDA
//#define PIN_WIRE_BATT_SCL  PIN_WIRE_SCL
#define PIN_WIRE_SERCOM SERCOM4
#define PIN_WIRE_BATT_SDA  PIN_WIRE1_SDA
#define PIN_WIRE_BATT_SCL  PIN_WIRE1_SCL
#endif

#ifdef SEEED_XIAO_M0
#define PIN_WIRE_SERCOM SERCOM2
#define PIN_WIRE_BATT_SDA PIN_WIRE_SDA
#define PIN_WIRE_BATT_SCL PIN_WIRE_SCL
#endif

#ifdef ARDUINO_SEEED_INDICATOR_RP2040
#define PIN_WIRE_BATT_SDA  PIN_WIRE0_SDA
#define PIN_WIRE_BATT_SCL  PIN_WIRE0_SCL
#endif

#include <Arduino.h>
#include "Adafruit_TinyUSB.h"
#include "shared.h"
#include "storage.h"

#ifdef ARDUINO_SEEED_INDICATOR_RP2040
#include <Wire.h>
#endif

#if defined(ARDUINO_ARCH_SAMD)
#include "src/MYSERCOM.h"
#include "src/Wire.h"
#endif

/* USB HID report descriptor. */
uint8_t const desc_hid_report[] = 
{
  TUD_HID_REPORT_DESC_GENERIC_INOUT(HID_INT_OUT_EP_SIZE)
};

const byte DefaultBoardSerial[12] = {0xFF,0x1F,0xFF,0x2F,0xFF,0x3F,0xFF,0x4F,0xFF,0x5F,0xFF,0x6F};

#if defined(ARDUINO_ARCH_SAMD)
#define WireBattery MyWire
#endif

#ifdef ARDUINO_SEEED_INDICATOR_RP2040
#define WireBattery Wire
#endif

extern TwoWire WireBattery;

extern TBatteryBoard BatteryBoards[];//[DAUGHTERBOARDCOUNT];
extern TBoardInfo BoardInfo;
extern volatile THIDData HIDData[];//[DAUGHTERBOARDCOUNT];
extern Adafruit_USBD_HID usb_hid;

bool process_command(void const *data, void *result);
void set_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* hid_report_out, uint16_t bufsize);

#endif
