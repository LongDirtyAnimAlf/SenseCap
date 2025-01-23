#ifndef LV_SEVENSEGMENT_H
#define LV_SEVENSEGMENT_H

#include <Arduino.h>
#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

lv_obj_t * create_display(lv_obj_t * parent, lv_color_t c, bool size);
void SetDisplaymV(lv_obj_t * target, word value);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_SEVENSEGMENT_H*/