#ifndef LV_SCREEN3_H
#define LV_SCREEN3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>

void Setup_Screen3(byte index);
void Screen3SetData(PBatterySetting SET);
void Screen3AddData(word V, word I, dword E, dword C);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_SCREEN3_H*/