#include "Screenbase.h"

static byte Screen4SelectedIndex = 255; // valid numbers from 0 to 15 = daughterboardcount

#define SCREENINDEX 4

static lv_obj_t * ta = NULL;

#define CHARGECOLOR LV_PALETTE_GREEN

#define DISCHARGECOLOR LV_PALETTE_RED

lv_obj_t * CreateCell(lv_obj_t * parent, lv_palette_t p, lv_obj_t * kb, char* labelname, char* unitname, bool check);

static void btn_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * btn = lv_event_get_current_target_obj(e);

  // Transport the event itself to the main application !!
  //lv_event_cb_t event_cb = GetEvent();
  //event_cb(e);
}

void Setup_Screen4(byte index)
{
  lv_obj_t * obj = NULL;
  lv_obj_t * label = NULL;
  //lv_obj_t * ta = NULL;
  lv_obj_t * cell = NULL;
  lv_obj_t * chk = NULL;
  lv_obj_t * grid = NULL;
  lv_obj_t * cont = NULL;
  lv_obj_t * preset_list = NULL; 

  if (index<DAUGHTERBOARDCOUNT)
  {
    Screen4SelectedIndex = index;
    obj = GetInfoObject();
    if (obj != NULL) lv_label_set_text_fmt(obj,"Battery #%d",Screen4SelectedIndex+1);
  }

  obj = GetButtonLabelObject();
  if (obj != NULL) lv_label_set_text(obj,"Additional");

  cont = GetContentObject(3U);

  if (lv_obj_get_child_count(cont) == 0)
  {

  // Get the keyboard
  lv_obj_t * kb = GetKeyboard(); 
  // Set keyboard to used this cell to show itself
  //lv_obj_set_parent(kb,cont);

  static lv_style_t style_list_items;
  lv_style_init(&style_list_items);
  lv_style_set_bg_color(&style_list_items, lv_palette_main(LV_PALETTE_LIGHT_BLUE));
  lv_style_set_shadow_width(&style_list_items, 5);
  lv_style_set_shadow_ofs_y(&style_list_items, 5);
  lv_style_set_shadow_opa(&style_list_items, LV_OPA_50);
  lv_style_set_text_color(&style_list_items, lv_color_white());
  lv_style_set_width(&style_list_items, lv_pct(100));
  lv_style_set_height(&style_list_items, LV_SIZE_CONTENT);
  lv_style_set_text_font(&style_list_items, &lv_font_montserrat_14);  /*Set a larger font*/ 
  //lv_style_set_text_align(&style_list_items, LV_TEXT_ALIGN_CENTER);  
  //lv_style_set_align(&style_list_items, LV_ALIGN_CENTER);  

  static lv_style_t style_list_items_extra;
  lv_style_init(&style_list_items_extra);
  lv_style_set_bg_color(&style_list_items_extra, lv_palette_main(LV_PALETTE_YELLOW));

  static lv_style_t style_list_header;
  lv_style_init(&style_list_header);
  lv_style_set_text_font(&style_list_header, &lv_font_montserrat_18);  /*Set a larger font*/ 
  lv_style_set_text_align(&style_list_header, LV_TEXT_ALIGN_CENTER);  
  lv_style_set_border_width(&style_list_header, 4);
  lv_style_set_margin_top(&style_list_header, 4);
  lv_style_set_margin_left(&style_list_header, 4);
  lv_style_set_margin_right(&style_list_header, 4);  
  
  preset_list = lv_list_create(cont);
  lv_obj_set_size(preset_list, lv_pct(40), lv_pct(100));
  lv_obj_set_style_pad_row(preset_list, 10, 0);
  lv_obj_align(preset_list, LV_ALIGN_TOP_RIGHT, 0, 0);

  lv_obj_remove_style(preset_list, 0, LV_PART_SCROLLBAR);
  lv_obj_set_scrollbar_mode(preset_list, LV_SCROLLBAR_MODE_OFF);
  
  obj = lv_list_add_text(preset_list, "AA\ndisposable");
  obj = lv_list_add_button(preset_list, LV_SYMBOL_BATTERY_2, "ICRT Light");
  obj = lv_list_add_button(preset_list, LV_SYMBOL_BATTERY_2, "ICRT Medium");
  obj = lv_list_add_button(preset_list, LV_SYMBOL_BATTERY_2, "ICRT Heavy");
  obj = lv_list_add_text(preset_list, "AA\nrechargeable");
  obj = lv_list_add_button(preset_list, LV_SYMBOL_CHARGE, "ICRT standard");
  obj = lv_list_add_button(preset_list, LV_SYMBOL_CHARGE, "IEC standard");
  obj = lv_list_add_button(preset_list, LV_SYMBOL_CHARGE, "IEC fast");
  obj = lv_list_add_text(preset_list, "AAA\ndisposable");
  obj = lv_list_add_button(preset_list, LV_SYMBOL_BATTERY_2, "ICRT Light");
  obj = lv_list_add_button(preset_list, LV_SYMBOL_BATTERY_2, "ICRT Medium");
  obj = lv_list_add_button(preset_list, LV_SYMBOL_BATTERY_2, "ICRT Heavy");
  obj = lv_list_add_text(preset_list, "AAA\nrechargeable");
  obj = lv_list_add_button(preset_list, LV_SYMBOL_CHARGE, "ICRT standard");
  obj = lv_list_add_button(preset_list, LV_SYMBOL_CHARGE, "IEC standard");
  obj = lv_list_add_button(preset_list, LV_SYMBOL_CHARGE, "IEC fast");

  uint32_t i;

  for (i = 0; i < lv_obj_get_child_count(preset_list); i++)
  {
    obj = lv_obj_get_child(preset_list, i);

    if (lv_obj_check_type(obj, &lv_list_button_class))
    {
      lv_obj_add_style(obj, &style_list_items, 0);
      lv_obj_add_style(obj, &style_list_items_extra, LV_PART_MAIN | LV_STATE_PRESSED);
      lv_obj_add_event_cb(obj, btn_event_cb, LV_EVENT_ALL, NULL);      
    }
    else
    //if (lv_obj_check_type(obj, &lv_list_text_class))
    {
      lv_obj_add_style(obj, &style_list_header, 0);
      lv_obj_set_style_translate_y(obj, 4, LV_PART_MAIN| LV_STATE_DEFAULT);          
    }
  }

  static lv_style_t ta_style;
  lv_style_init(&ta_style);
  lv_style_set_text_font(&ta_style, &lv_font_montserrat_14);  /*Set a larger font*/ 
  //lv_style_set_text_align(&ta_style, LV_TEXT_ALIGN_CENTER);  
  //lv_style_set_border_width(&ta_style, 2);
  lv_style_set_pad_all(&ta_style, 4);  
  lv_style_set_radius(&ta_style, 0);    


  static lv_style_t label_style;
  lv_style_init(&label_style);
  lv_style_set_width(&label_style, LV_PCT(100));
  lv_style_set_height(&label_style, LV_SIZE_CONTENT);
  lv_style_set_border_width(&label_style, 1);
  lv_style_set_border_side(&label_style, LV_BORDER_SIDE_BOTTOM);
  lv_style_set_border_color(&label_style, lv_palette_main(LV_PALETTE_LIGHT_BLUE));
  //lv_style_set_text_color(&label_style, lv_palette_main(LV_PALETTE_DEEP_ORANGE));
  lv_style_set_text_font(&label_style, &lv_font_montserrat_24);
  lv_style_set_text_align(&label_style, LV_TEXT_ALIGN_CENTER);    

  // Discharge settings

  lv_obj_t * discharge_cont = lv_obj_create(cont);
  lv_obj_set_size(discharge_cont, lv_pct(58), lv_pct(48));
  lv_obj_align(discharge_cont, LV_ALIGN_TOP_LEFT, 0, 0);    
  lv_obj_set_style_pad_left(discharge_cont, 2, LV_PART_MAIN);  
  lv_obj_set_scrollbar_mode(discharge_cont, LV_SCROLLBAR_MODE_ON);  

  label = lv_label_create(discharge_cont);
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
  lv_label_set_text(label, "Discharge settings");
  lv_obj_add_style(label , &label_style, 0);
  lv_obj_set_style_text_color(label,lv_palette_main(DISCHARGECOLOR), 0);

  obj = label;
  cell =  CreateCell(discharge_cont, DISCHARGECOLOR, kb, "Current", "[mA]", false);
  lv_obj_align_to(cell,obj,LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);  

  obj = cell;
  cell =  CreateCell(discharge_cont, DISCHARGECOLOR, kb, "Time", "[sec]", true);  
  lv_obj_align_to(cell,obj,LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);  

  obj = cell;
  cell =  CreateCell(discharge_cont, DISCHARGECOLOR, kb, "End", "[mV]", true);  
  lv_obj_align_to(cell,obj,LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);  


  // Charge settings

  lv_obj_t * charge_cont = lv_obj_create(cont);
  lv_obj_set_size(charge_cont, lv_pct(58), lv_pct(48));
  lv_obj_align(charge_cont, LV_ALIGN_BOTTOM_LEFT, 0, 0);    
  lv_obj_set_style_pad_left(charge_cont, 2, LV_PART_MAIN);
  lv_obj_set_scrollbar_mode(charge_cont, LV_SCROLLBAR_MODE_ON);

  label = lv_label_create(charge_cont);
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
  lv_label_set_text(label, "Charge settings");
  lv_obj_add_style(label , &label_style, 0);
  lv_obj_set_style_text_color(label,lv_palette_main(CHARGECOLOR), 0);      

  obj = label;
  cell =  CreateCell(charge_cont, CHARGECOLOR, kb, "Current", "[mA]", false);
  lv_obj_align_to(cell,obj,LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);  

  obj = cell;
  cell =  CreateCell(charge_cont, CHARGECOLOR, kb, "Time", "[sec]", true);  
  lv_obj_align_to(cell,obj,LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);  

  obj = cell;
  cell =  CreateCell(charge_cont, CHARGECOLOR, kb, "-dV", "[mV]", true);  
  lv_obj_align_to(cell,obj,LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);  

  obj = cell;
  cell =  CreateCell(charge_cont, CHARGECOLOR, kb, "dT", "[°C]", true);  
  lv_obj_align_to(cell,obj,LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);  

  obj = cell;
  cell =  CreateCell(charge_cont, CHARGECOLOR, kb, "T", "[°C]", true);  
  lv_obj_align_to(cell,obj,LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);  

  }
}

void Screen4SetData(PBatterySetting SET)
{
  Settings = SET;
}

void Screen4AddData(word V, word I)
{
}

lv_obj_t * CreateCell(lv_obj_t * parent, lv_palette_t p, lv_obj_t * kb, char* labelname, char* unitname, bool check)
{
  lv_obj_t * label;
  lv_obj_t * chk;  
  lv_obj_t * ta;
  lv_obj_t * cell;    

  static lv_style_t ta_style;
  lv_style_init(&ta_style);
  lv_style_set_text_font(&ta_style, &lv_font_montserrat_14);  /*Set a larger font*/ 
  lv_style_set_pad_all(&ta_style, 4);  
  lv_style_set_radius(&ta_style, 0);    

  cell = lv_obj_create(parent);
  lv_obj_remove_style_all(cell);  
  lv_obj_clear_flag(cell, LV_OBJ_FLAG_SCROLLABLE);  
  lv_obj_set_size(cell, lv_pct(100), LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(cell, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(cell, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);          
  lv_obj_set_style_pad_column(cell, 10, 0); //Space between widgets
  lv_obj_set_style_bg_color(cell, lv_palette_darken(LV_PALETTE_INDIGO,4), LV_PART_MAIN);
  lv_obj_set_style_border_color(cell, lv_palette_darken(LV_PALETTE_BLUE_GREY,4), LV_PART_MAIN);
  lv_obj_set_style_border_width(cell, 2, LV_PART_MAIN);  

  lv_obj_set_style_pad_top(cell, 2, LV_PART_MAIN);  
  lv_obj_set_style_pad_bottom(cell, 2, LV_PART_MAIN);    

  lv_obj_set_style_shadow_width(cell, 5, 0);
  //lv_obj_set_style_shadow_ofs_x(cell, 5, 0);
  lv_obj_set_style_shadow_ofs_y(cell, 5, 0);  
  lv_obj_set_style_shadow_opa(cell, LV_OPA_50, 0);


  if (check)
  {
    chk = lv_checkbox_create(cell);
    lv_obj_align_to(chk,label,LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
    lv_obj_set_width(chk, 70);
    lv_checkbox_set_text(chk, labelname);
    lv_obj_add_style(chk, &ta_style, 0);        
  }
  else
  {
    label = lv_label_create(cell);
    lv_obj_set_width(label, 70);
    lv_label_set_text(label, labelname);
    lv_obj_add_style(label, &ta_style, 0);      
  }

  ta = lv_textarea_create(cell);
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);    
  lv_textarea_set_one_line(ta, true);
  lv_obj_set_width(ta, 110);
  lv_textarea_set_text(ta, "123456");
  lv_textarea_set_accepted_chars(ta, "0123456789");  
  lv_obj_set_user_data(ta,(void *)LV_ALIGN_TOP_LEFT);
  lv_obj_add_style(ta, &ta_style, 0); 
  lv_obj_set_style_border_color(ta, lv_palette_main(p), LV_PART_MAIN);
  lv_obj_set_style_border_width(ta, 2, LV_PART_MAIN);  
  lv_obj_set_style_text_color(ta, lv_palette_darken(p,4), LV_PART_SELECTED); 
  lv_obj_set_style_bg_color(ta, lv_palette_lighten(p,4), LV_PART_MAIN);

  label = lv_label_create(cell);
  lv_obj_set_width(label, 60);  
  lv_label_set_text(label, unitname);
  lv_obj_add_style(label, &ta_style, 0);
  
  return (cell);
}