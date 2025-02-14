#include <lvgl.h>
#include "Screenbase.h"

lv_obj_t * screen3 = NULL;

extern const lv_font_t lv_font_montserrat_18;
extern const lv_font_t lv_font_montserrat_22;
extern const lv_font_t lv_font_montserrat_24;
extern const lv_font_t lv_font_montserrat_32;

static void ta_event_cb(lv_event_t * e);
static void slider_event_cb(lv_event_t * e);

void Create_Screen3(lv_event_cb_t event_cb_more)
{
  lv_obj_t * obj = NULL;
  lv_obj_t * label = NULL;
  lv_obj_t * ta = NULL;

  screen3 = lv_obj_create(NULL);
  BaseScreenSetup(screen3, event_cb_more);

  lv_obj_t * cont = GetContentObject(screen3);

  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_text_font(&style, &lv_font_montserrat_24);  /*Set a larger font*/ 
  lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);  

  /*Create a keyboard*/
  lv_obj_t * kb = lv_keyboard_create(cont);
  lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_NUMBER);
  lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
  lv_btnmatrix_set_btn_ctrl(kb,12,LV_BTNMATRIX_CTRL_DISABLED);
  lv_btnmatrix_set_btn_ctrl(kb,14,LV_BTNMATRIX_CTRL_DISABLED);  
  lv_obj_add_style(kb, &style, 0);

  /*Create a label and position it above the text box*/
  label = lv_label_create(cont);
  lv_obj_set_width(label, lv_pct(50));    
  lv_obj_set_style_text_font(label, &lv_font_montserrat_22, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_label_set_text(label, "Discharge current\n[mA]");
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 10);  

  /*Create the text area*/
  ta = lv_textarea_create(cont);
  lv_obj_set_width(ta, lv_pct(30));
  lv_obj_add_style(ta, &style, 0);
  lv_obj_align_to(ta, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
  lv_textarea_set_accepted_chars(ta, "0123456789");
  //lv_textarea_set_max_length(ta, 4);
  lv_textarea_set_one_line(ta, true);
  lv_textarea_set_text(ta, "0");


  /*Create a label and position it above the text box*/
  label = lv_label_create(cont);
  lv_obj_set_width(label, lv_pct(50));  
  lv_obj_set_style_text_font(label, &lv_font_montserrat_22, LV_PART_MAIN| LV_STATE_DEFAULT);    
  lv_label_set_text(label, "End voltage\n[mV]");
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);  
  lv_obj_align(label, LV_ALIGN_TOP_RIGHT, 0, 10);  

  /*Create the text area*/
  ta = lv_textarea_create(cont);
  lv_obj_set_width(ta, lv_pct(30));  
  lv_obj_add_style(ta, &style, 0);  
  lv_obj_align_to(ta, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
  lv_textarea_set_accepted_chars(ta, "0123456789");
  //lv_textarea_set_max_length(ta, 5);
  lv_textarea_set_one_line(ta, true);
  lv_textarea_set_text(ta, "0");

  lv_obj_t * slider = lv_slider_create(cont);
  lv_obj_center(slider);
  lv_slider_set_range(slider,25,500);
  lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, ta);
  lv_obj_set_style_bg_color(slider, lv_palette_main(LV_PALETTE_RED),LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(slider, lv_palette_main(LV_PALETTE_RED), LV_PART_KNOB);

  obj = lv_btn_create(cont);
  lv_obj_set_size(obj, lv_pct(80), LV_SIZE_CONTENT);
  lv_obj_align_to(obj, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 50);

  label = lv_label_create(obj);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_32, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(label, "START DISCHARGE");

  label = lv_label_create(cont);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_32, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_label_set_text(label, "Under construction !!");
  lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -20);
}

static void ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    /*The original target of the event. Can be the buttons or the container*/
    lv_obj_t * ta = (lv_obj_t *)lv_event_get_target(e);
    /*The current target is always the container as the event is added to it*/
    lv_obj_t * cont = (lv_obj_t *)lv_event_get_current_target(e);

    /*If container was clicked do nothing*/
    //if(target == cont) return;

    lv_obj_t * kb = (lv_obj_t *)lv_event_get_user_data(e);

    if(code == LV_EVENT_FOCUSED) {
        if(lv_indev_get_type(lv_indev_active()) != LV_INDEV_TYPE_KEYPAD)
        {
            lv_keyboard_set_textarea(kb, ta);
            lv_obj_set_style_max_height(kb, LV_HOR_RES * 2 / 3, 0);
            lv_obj_remove_flag(kb, LV_OBJ_FLAG_HIDDEN);
            lv_obj_move_foreground(kb);
            lv_obj_scroll_to_view_recursive(ta, LV_ANIM_OFF);
            lv_obj_set_style_bg_color(ta, lv_palette_main(LV_PALETTE_RED), 0);            
            lv_indev_wait_release((lv_indev_t *)lv_event_get_param(e));
        }
    }
    else if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_indev_reset(NULL, ta);

    }
    else if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_indev_reset(NULL, ta);   /*To forget the last clicked object to make it focusable again*/
        //lv_slider_set_value(slider, 70, LV_ANIM_OFF);

    }
}

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = (lv_obj_t *)lv_event_get_target(e);
    lv_obj_t * ta = (lv_obj_t *)lv_event_get_user_data(e);

    lv_slider_set_value(slider, (lv_slider_get_value(slider) + 5), LV_ANIM_ON);

    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d", (int)lv_slider_get_value(slider));
    
    lv_textarea_set_text(ta,buf);

}
