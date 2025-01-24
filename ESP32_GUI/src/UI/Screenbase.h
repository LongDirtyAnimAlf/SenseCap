#ifndef LV_BASESCREEN_H
#define LV_BASESCREEN_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

void BaseScreenSetup(lv_obj_t * basescreen, lv_event_cb_t event_cb_more);
lv_obj_t * GetContentObject(lv_obj_t * scr);
lv_obj_t * GetInfoObject(lv_obj_t * scr);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_BASESCREEN_H*/