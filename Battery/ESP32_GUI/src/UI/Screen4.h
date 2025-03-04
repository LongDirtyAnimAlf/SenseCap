#ifndef LV_SCREEN4_H
#define LV_SCREEN4_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>

void Setup_Screen4(byte index);
void Screen4SetData(PBatterySetting SET);
void Screen4AddData(word V, word I);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_SCREEN4_H*/