#include <Arduino.h>
#include <lvgl.h>

extern const lv_font_t lv_font_dseg7_64;
extern const lv_font_t lv_font_dseg7_32;

lv_obj_t * create_display(lv_obj_t * parent, lv_color_t c, bool size)
{

  lv_font_t * digitfont;

  lv_obj_t *digits = lv_obj_create(parent);

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
  lv_label_set_text(digits_back, "8.888");

  lv_obj_t *digits_front = lv_label_create(digits);
  lv_obj_remove_style_all(digits_front);
  lv_obj_align(digits_front, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_set_style_text_color(digits_front, c, LV_PART_MAIN | LV_STATE_DEFAULT );
  lv_obj_set_style_text_font(digits_front, digitfont, LV_PART_MAIN| LV_STATE_DEFAULT);
  lv_label_set_text(digits_front, "0.000");

  return digits;
}

byte WordToTxtThousands(unsigned long value, byte displaysize, char* destination)
{
  byte dot = 1;
  unsigned long tmp = value;
  byte runner;

  while (tmp >= 10u)
  {
    if (tmp>=10000u) dot++; else break;
    tmp /= 10u;
  }

  tmp = value;
  if (dot>1)
  {
    runner = (dot-1);
    while (runner-- > 0) tmp /= 10u;
  }

  destination += (displaysize);
  *destination-- = 0;
  runner = (displaysize-1);
  if (runner < (dot+1)) *destination-- = 0;
  while (runner)
  {
    runner--;
    *destination-- = (tmp  % 10u) + '0';    
    if (dot == runner)
    {
      *destination-- = '.';
    }
    tmp /= 10u;
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
      char tmpArray[12] = "0000000000";
      byte dp = WordToTxtThousands(value,5,tmpArray);

      char ascArray[6] = "88888";
      if (dp<4) ascArray[dp] = '.'; else ascArray[4] = '\0';

      lv_label_set_text(digits_back, ascArray);          
      lv_label_set_text(digits_front, tmpArray); 

    }
  }
}
