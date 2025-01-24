#include <lvgl.h>

void BaseScreenSetup(lv_obj_t * basescreen, lv_event_cb_t event_cb_more)
{
  lv_obj_t * nav = lv_obj_create(basescreen);
  lv_obj_set_style_pad_top(nav, 6, LV_PART_MAIN);
  lv_obj_set_style_pad_bottom(nav, 6, LV_PART_MAIN);
  lv_obj_set_style_pad_left(nav, 2, LV_PART_MAIN);
  lv_obj_set_style_pad_right(nav, 2, LV_PART_MAIN);
  lv_obj_set_size(nav, lv_pct(100), LV_SIZE_CONTENT);
  lv_obj_align(nav, LV_ALIGN_BOTTOM_MID, 0, 0);

  lv_obj_t * obj = NULL;

  obj = lv_btn_create(nav);
  lv_obj_align(obj, LV_ALIGN_RIGHT_MID, 0, 0);
  lv_obj_set_size(obj, lv_pct(25), LV_SIZE_CONTENT);
  lv_obj_add_event_cb(obj, event_cb_more, LV_EVENT_CLICKED, (void *)0);
  lv_obj_set_style_bg_color(obj,lv_palette_darken(LV_PALETTE_INDIGO,4), LV_PART_MAIN);      

  obj = lv_label_create(obj);
  lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(obj, "Back");

  obj = lv_btn_create(nav);
  lv_obj_align(obj, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_set_size(obj, lv_pct(25), LV_SIZE_CONTENT);
  lv_obj_add_event_cb(obj, event_cb_more, LV_EVENT_CLICKED, (void *)1);      
  lv_obj_set_style_bg_color(obj,lv_palette_darken(LV_PALETTE_INDIGO,4), LV_PART_MAIN);      

  obj = lv_label_create(obj);
  lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(obj, "More");

  lv_obj_t * basescreeninfo = lv_label_create(nav);
  lv_obj_align(basescreeninfo, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_font(basescreeninfo, &lv_font_montserrat_32, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_label_set_text(basescreeninfo, "INFO");

  lv_obj_update_layout(nav);
  int nav_height = lv_obj_get_height(nav);

  lv_obj_t * cont = lv_obj_create(basescreen);
  lv_obj_remove_style_all(cont);
  lv_obj_set_size(cont, lv_pct(100), lv_pct(100));
  lv_obj_align(cont, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_set_style_margin_bottom(cont, nav_height, LV_PART_MAIN);

  lv_obj_move_to_index(cont, 0);
  lv_obj_move_to_index(basescreeninfo, 1);
}

lv_obj_t * GetContentObject(lv_obj_t * scr)
{
  return lv_obj_get_child(scr, 0);
}

lv_obj_t * GetInfoObject(lv_obj_t * scr)
{
  return lv_obj_get_child(scr, 1);
}
