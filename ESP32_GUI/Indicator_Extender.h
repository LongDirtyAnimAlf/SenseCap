#ifndef IND_EXT_H
#define IND_EXT_H

#include <Arduino.h>
#include <Wire.h>
#include <PCA95x5.h>

#define LCD_SCL 40
#define LCD_SDA 39
#define EXTENDER_INT 45
#define LCD_SPEED 400000 // = MAX_SPEED

extern PCA9555 ioex;

#ifdef __cplusplus
extern "C" {
#endif

void extender_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*IND_EXT_H*/