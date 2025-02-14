#ifndef IND_EXT_H
#define IND_EXT_H

#include <Arduino.h>
#include <Wire.h>
#include <PCA95x5.h>

#define SPI_MISO  47
#define SPI_MOSI  48
#define SPI_SCLK  41

#define EXTENDER_SCL 40
#define EXTENDER_SDA 39
#define EXTENDER_INT 45

//#define ESP32_EXPANDER_IO_INT   42
//#define ESP32_EXPANDER_IO_INT   45

#define EXTENDER_SPEED 400000 // = MAX_SPEED_FOR_LCD

#define EXPANDER_IO_RADIO_NSS        PCA95x5::Port::P00  // IO0_0
#define EXPANDER_IO_RADIO_RST        PCA95x5::Port::P01  // IO0_1
#define EXPANDER_IO_RADIO_BUSY       PCA95x5::Port::P02  // IO0_2
#define EXPANDER_IO_RADIO_DIO_1      PCA95x5::Port::P03  // IO0_3

#define EXPANDER_IO_LCD_CS          PCA95x5::Port::P04  // IO0_4
#define EXPANDER_IO_LCD_RESET       PCA95x5::Port::P05  // IO0_5
#define EXPANDER_IO_LCD_INT         PCA95x5::Port::P06  // IO0_6

#define EXPANDER_IO_TP_RESET        PCA95x5::Port::P07  // IO0_7

#define EXPANDER_IO_RP2040_RESET    PCA95x5::Port::P08  // IO1_0

#define EXPANDER_IO_BMP_PWR         PCA95x5::Port::P10  // IO1_2
#define SENSOR_BMP_ADDR             (0X77)

extern PCA9555 ioex;

#ifdef __cplusplus
extern "C" {
#endif

void extender_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*IND_EXT_H*/