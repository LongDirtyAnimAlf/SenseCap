#ifndef LV_BASESCREEN_H
#define LV_BASESCREEN_H

#include <Arduino.h>
#include <lvgl.h>
#include "sevensegment.h"
#include "shared.h"

extern const lv_font_t lv_font_montserrat_12;
extern const lv_font_t lv_font_montserrat_14;
extern const lv_font_t lv_font_montserrat_18;
extern const lv_font_t lv_font_montserrat_22;
extern const lv_font_t lv_font_montserrat_24;
extern const lv_font_t lv_font_montserrat_32;

extern PBatterySetting Settings;

extern lv_obj_t * screenbase;

#ifdef __cplusplus
extern "C" {
#endif

void CreateBaseScreen(lv_event_cb_t event_cb_more);

lv_obj_t * GetContentObject(byte contentindexnumber);
lv_obj_t * GetInfoObject(void);
lv_obj_t * GetButtonLabelObject(void);
lv_event_cb_t GetEvent(void);
lv_obj_t * GetKeyboard(void);
void ta_event_cb(lv_event_t * e);

void ObjectDeleteAndNull(lv_obj_t ** target);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_BASESCREEN_H*/