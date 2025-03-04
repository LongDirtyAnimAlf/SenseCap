#ifndef LV_SCREEN1_H
#define LV_SCREEN1_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>

extern lv_obj_t * screen1;

void Create_Screen1(lv_event_cb_t event_cb_more);
void SetVoltageScreen1mV(uint8_t Index, word data);
void SetCurrentScreen1mA(uint8_t Index, word data);
void SetLedScreen1(uint8_t Index, lv_color_t c);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_SCREEN1_H*/