#ifndef LV_SCREEN2_H
#define LV_SCREEN2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>

extern lv_obj_t * screen2;

void Screen2Create(lv_event_cb_t event_cb_more);
void Screen2AddData(unsigned long T, unsigned long  H);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_SCREEN2_H*/