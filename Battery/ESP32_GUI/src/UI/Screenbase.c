#include "Screenbase.h"

lv_obj_t * screenbase = NULL;
lv_obj_t * keyboardbase = NULL;
lv_event_cb_t event;

PBatterySetting Settings = NULL;

void BaseScreenSetup(lv_obj_t * basescreen, lv_event_cb_t event_cb_more)
{
  if (basescreen == NULL) return;

  event = event_cb_more;

  lv_obj_t * nav = lv_obj_create(basescreen);
  //lv_obj_remove_style_all(nav);
  lv_obj_clear_flag(nav, LV_OBJ_FLAG_SCROLLABLE);    
  lv_obj_set_style_pad_top(nav, 6, LV_PART_MAIN);
  lv_obj_set_style_pad_bottom(nav, 6, LV_PART_MAIN);
  lv_obj_set_style_pad_left(nav, 2, LV_PART_MAIN);
  lv_obj_set_style_pad_right(nav, 2, LV_PART_MAIN);
  lv_obj_set_size(nav, lv_pct(100), lv_pct(10));
  lv_obj_align(nav, LV_ALIGN_BOTTOM_MID, 0, 0);

  lv_obj_t * obj = NULL;

  obj = lv_button_create(nav);
  lv_obj_align(obj, LV_ALIGN_RIGHT_MID, 0, 0);
  lv_obj_set_size(obj, lv_pct(25), LV_SIZE_CONTENT);
  lv_obj_add_event_cb(obj, event_cb_more, LV_EVENT_CLICKED, (void *)btn_back);
  lv_obj_set_style_bg_color(obj,lv_palette_darken(LV_PALETTE_INDIGO,4), LV_PART_MAIN);      

  obj = lv_label_create(obj);
  lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(obj, "Back");

  lv_obj_t * morebutton = lv_button_create(nav);
  lv_obj_align(morebutton, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_set_size(morebutton, lv_pct(25), LV_SIZE_CONTENT);
  lv_obj_add_event_cb(morebutton, event_cb_more, LV_EVENT_CLICKED, (void *)btn_next);      
  lv_obj_set_style_bg_color(morebutton,lv_palette_darken(LV_PALETTE_INDIGO,4), LV_PART_MAIN);      

  obj = lv_label_create(morebutton);
  lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(obj, "More");

  lv_obj_t * basescreeninfo = lv_label_create(nav);
  lv_obj_align(basescreeninfo, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_font(basescreeninfo, &lv_font_montserrat_32, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_label_set_text(basescreeninfo, "INFO");

  lv_obj_t * cont_screen2 = lv_obj_create(basescreen);
  obj = cont_screen2;
  lv_obj_remove_style_all(obj);
  lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, 0);  
  lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);    
  lv_obj_set_size(obj, lv_pct(100), lv_pct(90));
  lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);

  lv_obj_t * cont_screen3 = lv_obj_create(basescreen);
  obj = cont_screen3;
  lv_obj_remove_style_all(obj);
  lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, 0);  
  lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);    
  lv_obj_set_size(obj, lv_pct(100), lv_pct(90));
  lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);

  lv_obj_t * cont_screen4 = lv_obj_create(basescreen);
  obj = cont_screen4;
  lv_obj_remove_style_all(obj);
  lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, 0);  
  lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);    
  lv_obj_set_size(obj, lv_pct(100), lv_pct(90));
  lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
  

  lv_obj_move_to_index(nav, 0);
  lv_obj_move_to_index(cont_screen2, 1);
  lv_obj_move_to_index(cont_screen3, 2);
  lv_obj_move_to_index(cont_screen4, 3);    

  lv_obj_move_to_index(morebutton, 0);
  lv_obj_move_to_index(basescreeninfo, 1);
}

void BaseKeyboardSetup(lv_obj_t * kb)
{
  if (kb == NULL) return;

  static const char * kb_map[] = {"1", "2", "3", "\n", "4", "5", "6", "\n", "7", "8", "9", "\n", LV_SYMBOL_BACKSPACE, "0", LV_SYMBOL_OK, NULL };
  static const lv_btnmatrix_ctrl_t kb_ctrl[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

  lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_USER_1, kb_map, kb_ctrl);
  lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_USER_1);  
  lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
  //lv_obj_set_size(kb, LV_PCT(100), LV_PCT(100));
  lv_obj_set_size(kb, 250, 250);
  lv_obj_align(kb, LV_ALIGN_CENTER, 0, 0);  
  lv_obj_set_style_bg_color(kb, lv_palette_darken(LV_PALETTE_INDIGO,4), LV_PART_MAIN);
  lv_obj_set_style_border_color(kb, lv_palette_darken(LV_PALETTE_BLUE_GREY,4), LV_PART_MAIN);
  lv_keyboard_set_textarea(kb, NULL);

  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_text_font(&style, &lv_font_montserrat_24);  /*Set a larger font*/ 
  lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);  
  lv_style_set_border_width(&style, 4);
  lv_style_set_pad_all(&style, 4);  
  lv_style_set_radius(&style, 4);  
  //lv_style_set_margin_top(&style, 20);
  //lv_style_set_margin_bottom(&style, 20);
  //lv_style_set_margin_left(&style, 20);
  //lv_style_set_margin_right(&style, 20);
    
  static lv_style_t style_btn;
  lv_style_init(&style_btn);
  lv_style_set_border_width(&style_btn, 4);
  lv_style_set_border_opa(&style_btn, LV_OPA_50);
  lv_style_set_border_color(&style_btn, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_border_side(&style_btn, LV_BORDER_SIDE_INTERNAL);
  lv_style_set_radius(&style_btn, 10);  
  lv_style_set_text_font(&style_btn, &lv_font_montserrat_24);  /*Set a larger font*/ 
  lv_style_set_text_align(&style_btn, LV_TEXT_ALIGN_CENTER);  
  //lv_style_set_pad_all(&style_btn, 10);
  //lv_style_set_pad_gap(&style_btn, 5);

  lv_obj_add_style(kb, &style, LV_PART_MAIN );
  lv_obj_add_style(kb, &style_btn, LV_PART_ITEMS);  

  lv_obj_set_style_margin_top(kb, 20, LV_PART_MAIN);
  lv_obj_set_style_margin_bottom(kb, 20, LV_PART_MAIN);
  lv_obj_set_style_margin_left(kb, 20, LV_PART_MAIN);
  lv_obj_set_style_margin_right(kb, 20, LV_PART_MAIN);
}

void CreateBaseScreen(lv_event_cb_t event_cb_more)
{
  screenbase = lv_obj_create(NULL);
  keyboardbase = lv_keyboard_create(screenbase); 
  BaseScreenSetup(screenbase, event_cb_more);
  BaseKeyboardSetup(keyboardbase);
}

void recursive_hide(lv_obj_t *parent, bool hide)
{
    uint32_t child_count = lv_obj_get_child_count(parent);
    lv_obj_t *child;

    for(uint32_t i=0;i<child_count;i++)
    {
      child = lv_obj_get_child(parent, i);
      if (hide)
      {
        if (!lv_obj_has_flag(child, LV_OBJ_FLAG_HIDDEN)) lv_obj_add_flag(child, LV_OBJ_FLAG_HIDDEN);
      }
      else
      {
        if (lv_obj_has_flag(child, LV_OBJ_FLAG_HIDDEN)) lv_obj_remove_flag(child, LV_OBJ_FLAG_HIDDEN);    
      }
      recursive_hide(child,hide);
    }
}

lv_obj_t * GetContentObject(byte contentindexnumber)
{
  lv_obj_t * obj = NULL;

  if (screenbase == NULL) return (NULL);

  for(byte i = 1; i < 4; i++)  
  {
    obj = lv_obj_get_child(screenbase, i);
    if ((obj != NULL) && (contentindexnumber != i))
    //if (obj != NULL)
    {
      //recursive_hide(obj,true);
      if (!lv_obj_has_flag(obj, LV_OBJ_FLAG_HIDDEN))
      {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        //lv_obj_set_local_style_prop(obj, LV_STYLE_OPA, 0, 0);   
        //lv_obj_invalidate(screenbase);      
      }
    }
  }

  obj = lv_obj_get_child(screenbase, contentindexnumber);

  if (obj != NULL)
  {
    //recursive_hide(obj,false);
    if (lv_obj_has_flag(obj, LV_OBJ_FLAG_HIDDEN)) lv_obj_remove_flag(obj, LV_OBJ_FLAG_HIDDEN);        
    //lv_obj_remove_local_style_prop(obj, LV_STYLE_OPA, 0);    
    //lv_obj_move_foreground(obj);
    //lv_obj_invalidate(screenbase);
    //lv_refr_now(NULL);
 
  }

  return (obj);
}

lv_obj_t * GetInfoObject(void)
{
  if (screenbase == NULL) return (NULL);
  lv_obj_t * nav = lv_obj_get_child(screenbase, 0);
  lv_obj_t * obj = lv_obj_get_child(nav, 1);
  if (!lv_obj_check_type(obj, &lv_label_class)) return (NULL);
  return obj;    
}

lv_obj_t * GetButtonLabelObject(void)
{
  if (screenbase == NULL) return (NULL);
  lv_obj_t * nav = lv_obj_get_child(screenbase, 0);
  lv_obj_t * btn = lv_obj_get_child(nav, 0);
  if (!lv_obj_check_type(btn, &lv_button_class)) return (NULL);
  lv_obj_t * obj = lv_obj_get_child(btn, 0);  
  if (!lv_obj_check_type(obj, &lv_label_class)) return (NULL);
  return obj;    
}

lv_event_cb_t GetEvent(void)
{
  return (event);
}

lv_obj_t * GetKeyboard(void)
{
  return (keyboardbase);
}

void ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    /*The original target of the event. Can be the buttons or the container*/
    lv_obj_t * ta = (lv_obj_t *)lv_event_get_target(e);
    /*The current target is always the container as the event is added to it*/
    lv_obj_t * cont = (lv_obj_t *)lv_event_get_current_target(e);

    /*If container was clicked do nothing*/
    //if(ta == cont) return;

    lv_obj_t * kb = (lv_obj_t *)lv_event_get_user_data(e);

    if(code == LV_EVENT_FOCUSED) {
        if(lv_indev_get_type(lv_indev_active()) != LV_INDEV_TYPE_KEYPAD)
        {
            lv_align_t alignment = (lv_align_t)(uintptr_t)lv_obj_get_user_data(ta);
            lv_obj_align(kb, alignment, 0, 0);      
            lv_keyboard_set_textarea(kb, ta);
            lv_obj_remove_flag(kb, LV_OBJ_FLAG_HIDDEN);
            lv_obj_move_foreground(kb);
            //lv_obj_scroll_to_view_recursive(ta, LV_ANIM_OFF);
            lv_indev_wait_release((lv_indev_t *)lv_event_get_param(e));
        }
    }
    else if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_align(kb, LV_ALIGN_DEFAULT, 0, 0);
        lv_indev_reset(NULL, ta);

    }
    else if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
      lv_keyboard_set_textarea(kb, NULL);
      lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
      lv_obj_align(kb, LV_ALIGN_DEFAULT, 0, 0);
      lv_obj_clear_state(ta, LV_STATE_FOCUSED);
      lv_indev_reset(NULL, ta);
    }
}

void ObjectDeleteAndNull(lv_obj_t ** target)
{
  if (*target != NULL)
  {
    lv_lock();
    lv_obj_delete(*target);
    *target = NULL;
    lv_unlock();
  }
}
