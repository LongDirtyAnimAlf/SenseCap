#include <Arduino.h>
#include <lvgl.h>
#include "shared.h"

extern const lv_font_t lv_font_dseg7_64;
extern const lv_font_t lv_font_dseg7_32;

const char ZEROS[]    = "000000000000";
const char ALL[]      = "888888888888";
const char INVALID[]  = "------------";

char tmpArray[12] = "";

lv_obj_t * create_display(lv_obj_t * parent, lv_color_t c, bool size, byte count)
{
  byte i;

  lv_font_t * digitfont;

  lv_obj_t *digits = lv_obj_create(parent);
  lv_obj_set_user_data(digits,(void *)count);  

  if (size)
  {
    lv_obj_set_style_pad_top(digits, 18, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(digits, 18, LV_PART_MAIN);
    lv_obj_set_style_pad_left(digits, 4, LV_PART_MAIN);
    lv_obj_set_style_pad_right(digits, 4, LV_PART_MAIN);
    lv_obj_set_style_radius(digits, 10, LV_PART_MAIN);
    digitfont = &lv_font_dseg7_64;
  }
  else
  {
    lv_obj_remove_style_all(digits);
    digitfont = &lv_font_dseg7_32;
  }

  //lv_obj_add_flag(digits, LV_OBJ_FLAG_USER_1 );

  lv_obj_align(digits, LV_ALIGN_CENTER, 0, 0);
  lv_obj_center(digits);

  lv_obj_set_height(digits, LV_SIZE_CONTENT);
  if (size)
  {
    lv_obj_set_width(digits, 220);
  }
  else
  {
    lv_obj_set_width(digits, LV_SIZE_CONTENT);
  }
  lv_obj_set_style_bg_color(digits, lv_color_black(), LV_PART_MAIN| LV_STATE_DEFAULT);

  lv_obj_t *digits_back = lv_label_create(digits);
  lv_obj_remove_style_all(digits_back);
  lv_obj_align(digits_back, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_set_style_text_color(digits_back, c, LV_PART_MAIN | LV_STATE_DEFAULT );
  lv_obj_set_style_text_font(digits_back, digitfont, LV_PART_MAIN| LV_STATE_DEFAULT);
  lv_obj_set_style_opa(digits_back, LV_OPA_20, 0);

  strncpy(tmpArray,ALL,count);
  tmpArray[1] = '.';
  tmpArray[count] = 0;

  lv_label_set_text(digits_back, tmpArray);
  //lv_label_set_text(digits_back, "8.888");

  lv_obj_t *digits_front = lv_label_create(digits);
  lv_obj_remove_style_all(digits_front);
  lv_obj_align(digits_front, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_set_style_text_color(digits_front, c, LV_PART_MAIN | LV_STATE_DEFAULT );
  lv_obj_set_style_text_font(digits_front, digitfont, LV_PART_MAIN| LV_STATE_DEFAULT);

  strncpy(tmpArray,INVALID,count);
  tmpArray[1] = '.';
  tmpArray[count] = 0;

  lv_label_set_text(digits_front, tmpArray);
  //lv_label_set_text(digits_front, "-.---");

  return digits;
}

byte WordToTxtThousands(uint32_t value, byte displaysize, char* destination)
{
  int8_t dot;
  uint32_t tmp;
  int8_t runner;
  char * buffer;
  uint8_t v;

  tmp = value;
  dot = 1;

  buffer = destination;

  buffer[displaysize] = 0;

  // Fill buffer with zero
  uint8_t ndx = displaysize;
  while (ndx)
  {
    ndx--;
    buffer[ndx]  = '0';
    if (tmp>9999U) dot++;
    tmp /= 10; 
  }

  runner = dot + 3; // we process data in mV, mA, mW or mAh .. so 10-3

  tmp = value;
  while (true) 
  {
    if (runner == dot)
    {
      if (runner < (displaysize-1)) buffer[runner]  = '.';
      if (runner == (displaysize-1)) buffer[runner]  = 0;
    }
    else
    {
      v = tmp % 10;
      tmp /= 10; 
      if (runner < displaysize) buffer[runner]  = v + '0';
    }
    if (runner==0) break;
    runner--;
  }

  return dot;
}

void SetDisplaymV(lv_obj_t * target, unsigned long value)
{
  if (target != NULL)
  {
    lv_obj_t * digits_back = lv_obj_get_child(target, 0);
    lv_obj_t * digits_front = lv_obj_get_child(target, 1);

    if ((digits_back != NULL) && (digits_front != NULL))  
    {
      byte digitcount = (byte)(uintptr_t)lv_obj_get_user_data(target);    

      //char tmpArray[12] = "0000000000";
      strncpy(tmpArray,ZEROS,(digitcount));
      tmpArray[digitcount] = 0;

      byte dp = WordToTxtThousands(value,digitcount,tmpArray);
      lv_label_set_text(digits_front, tmpArray); 

      //char ascArray[6] = "88888";
      strncpy(tmpArray,ALL,(digitcount));
      tmpArray[digitcount] = 0;      

      if (dp<(digitcount-1)) tmpArray[dp] = '.'; else tmpArray[(digitcount-1)] = '\0';

      //lv_label_set_text(digits_back, ascArray);          
      lv_label_set_text(digits_back, tmpArray); 

    }
  }
}
