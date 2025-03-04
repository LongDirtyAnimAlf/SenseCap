#include "Screenbase.h"

static byte Screen3SelectedIndex = 255; // valid numbers from 0 to 15 = daughterboardcount

#define SCREENINDEX 3

//PBatterySetting Settings = NULL;

static lv_obj_t * ta1 = NULL;
static lv_obj_t * ta2 = NULL;

static lv_obj_t * testdischargebutton = NULL;
static lv_obj_t * startdischargebutton = NULL;
static lv_obj_t * testchargebutton = NULL;
static lv_obj_t * startchargebutton = NULL;

static lv_obj_t * zerocapacitybutton = NULL;
static lv_obj_t * zeroenergybutton = NULL;

static lv_obj_t * Display[4] = {NULL};

static void btn_event_cb(lv_event_t * e)
{
  static bool checked = false;

  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * btn = lv_event_get_current_target_obj(e);
  if ( (btn != NULL) && (code == LV_EVENT_VALUE_CHANGED) )
  {
    byte i;
    lv_obj_t * btns[4] = {testdischargebutton,startdischargebutton,testchargebutton,startchargebutton};

    checked = (lv_obj_get_state(btn) & LV_STATE_CHECKED);

    for (i = 0; i < 4; i++)
    {
      if ( (btns[i] != NULL) && (btns[i] != btn) )
      {
        if (checked)  
        {
          lv_obj_add_state(btns[i],LV_STATE_DISABLED);
          lv_obj_add_state(zerocapacitybutton,LV_STATE_DISABLED);
          lv_obj_add_state(zeroenergybutton,LV_STATE_DISABLED);
          lv_obj_add_state(ta1,LV_STATE_DISABLED);
          lv_obj_add_state(ta2,LV_STATE_DISABLED);          
          lv_obj_clear_flag(ta1, LV_OBJ_FLAG_CLICK_FOCUSABLE);          
          lv_obj_clear_flag(ta2, LV_OBJ_FLAG_CLICK_FOCUSABLE);                    
        }
        else
        {
          lv_obj_remove_state(btns[i],LV_STATE_DISABLED);
          lv_obj_remove_state(zerocapacitybutton,LV_STATE_DISABLED);
          lv_obj_remove_state(zeroenergybutton,LV_STATE_DISABLED);
          lv_obj_remove_state(ta1,LV_STATE_DISABLED);
          lv_obj_remove_state(ta2,LV_STATE_DISABLED);          
          lv_obj_add_flag(ta1, LV_OBJ_FLAG_CLICK_FOCUSABLE);          
          lv_obj_add_flag(ta2, LV_OBJ_FLAG_CLICK_FOCUSABLE);                    
        }
      }
    }

    // Transport the event itself to the main application !!
    lv_event_cb_t event_cb = GetEvent();
    event_cb(e);
  }
}

void Setup_Screen3(byte index)
{
  lv_obj_t * obj = NULL;
  lv_obj_t * label = NULL;
  lv_obj_t * cell = NULL;
  lv_obj_t * grid = NULL;
  lv_obj_t * cont = NULL;
  lv_obj_t * ta = NULL;  
  lv_obj_t * btn = NULL;    

  if (index<DAUGHTERBOARDCOUNT)
  {
    Screen3SelectedIndex = index;
    obj = GetInfoObject();
    if (obj != NULL) lv_label_set_text_fmt(obj,"Battery #%d",Screen3SelectedIndex+1);
  }

  obj = GetButtonLabelObject();
  if (obj != NULL) lv_label_set_text(obj,"Settings");

  cont = GetContentObject(2U);

  if (lv_obj_get_child_count(cont) == 0)
  {

  // Get the keyboard
  lv_obj_t * kb = GetKeyboard(); 

  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_text_font(&style, &lv_font_montserrat_24);  /*Set a larger font*/ 
  lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);  
  lv_style_set_border_width(&style, 4);
  lv_style_set_pad_all(&style, 4);  


  // Create container for top
  lv_obj_t * top_cont = lv_obj_create(cont);
  lv_obj_remove_style_all(top_cont);
  lv_obj_set_size(top_cont, lv_pct(100), lv_pct(20));
  lv_obj_align(top_cont, LV_ALIGN_TOP_MID, 0, 0);    
  
  // Create container for discharge setting and test  
  obj = lv_obj_create(top_cont);
  lv_obj_remove_style_all(obj);
  lv_obj_set_size(obj, lv_pct(50), lv_pct(100));
  lv_obj_align(obj, LV_ALIGN_TOP_LEFT, 0, 0);    

  //Create the label
  label = lv_label_create(obj);
  lv_obj_set_width(label, lv_pct(100));    
  lv_obj_set_style_text_font(label, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_label_set_text(label, "Discharge current [mA]");
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

  //Create the current setting text area
  ta = lv_textarea_create(obj);
  lv_obj_set_width(ta, lv_pct(40));
  lv_obj_add_style(ta, &style, 0);
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
  lv_textarea_set_accepted_chars(ta, "0123456789");
  //lv_textarea_set_max_length(ta1, 4);
  lv_textarea_set_one_line(ta, true);
  lv_textarea_set_text(ta, "0");
  lv_obj_set_user_data(ta,(void *)LV_ALIGN_CENTER);
  lv_obj_align_to(ta,label,LV_ALIGN_OUT_BOTTOM_LEFT, 20, 10);    

  ta1 = ta;

  //Create the test button
  btn = lv_button_create(obj);
  lv_obj_set_size(btn, lv_pct(40), LV_SIZE_CONTENT);
  lv_obj_align_to(btn,label,LV_ALIGN_OUT_BOTTOM_RIGHT, -20, 10);    

  //lv_obj_set_style_bg_color(btn,lv_palette_darken(LV_PALETTE_INDIGO,3), LV_PART_MAIN); 
  lv_obj_set_style_bg_color(btn, lv_palette_darken(LV_PALETTE_RED,3), LV_PART_MAIN | LV_STATE_CHECKED);       
  lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_VALUE_CHANGED, (void *)btn_test_discharge);      

  label = lv_label_create(btn);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(label, "TEST");

  testdischargebutton = btn;

  // Create container for charge setting and test  
  obj = lv_obj_create(top_cont);
  lv_obj_remove_style_all(obj);
  lv_obj_set_size(obj, lv_pct(50), lv_pct(100));
  lv_obj_align(obj, LV_ALIGN_TOP_RIGHT, 0, 0);    

  //Create the label
  label = lv_label_create(obj);
  lv_obj_set_width(label, lv_pct(100));    
  lv_obj_set_style_text_font(label, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_label_set_text(label, "Charge current [mA]");
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

  //Create the current setting text area
  ta = lv_textarea_create(obj);
  lv_obj_set_width(ta, lv_pct(40));
  lv_obj_add_style(ta, &style, 0);
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
  lv_textarea_set_accepted_chars(ta, "0123456789");
  //lv_textarea_set_max_length(ta1, 4);
  lv_textarea_set_one_line(ta, true);
  lv_textarea_set_text(ta, "0");
  lv_obj_set_user_data(ta,(void *)LV_ALIGN_CENTER);
  lv_obj_align_to(ta,label,LV_ALIGN_OUT_BOTTOM_LEFT, 20, 10);    

  ta2 = ta;

  //Create the test button
  btn = lv_button_create(obj);
  lv_obj_set_size(btn, lv_pct(40), LV_SIZE_CONTENT);
  lv_obj_align_to(btn,label,LV_ALIGN_OUT_BOTTOM_RIGHT, -20, 10);    

  //lv_obj_set_style_bg_color(btn,lv_palette_darken(LV_PALETTE_INDIGO,3), LV_PART_MAIN); 
  lv_obj_set_style_bg_color(btn, lv_palette_darken(LV_PALETTE_RED,3), LV_PART_MAIN | LV_STATE_CHECKED);       
  lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_VALUE_CHANGED, (void *)btn_test_charge);      

  label = lv_label_create(btn);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(label, "TEST");

  testchargebutton = btn;

  static lv_coord_t col_dsc2[] = { LV_GRID_FR(3), LV_GRID_FR(5), LV_GRID_FR(2), LV_GRID_TEMPLATE_LAST };
  static lv_coord_t row_dsc2[] = { LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };

  grid = lv_obj_create(cont);

  lv_obj_set_size(grid, 400, 50*4);
  //lv_obj_set_size(grid,LV_SIZE_CONTENT,LV_SIZE_CONTENT);
  //lv_obj_set_size(grid,lv_pct(80),lv_pct(100));
  //lv_obj_align(grid, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_align(grid, LV_ALIGN_CENTER, 0, 0);

  lv_obj_set_style_pad_top(grid, 4, LV_PART_MAIN);
  lv_obj_set_style_pad_bottom(grid, 4, LV_PART_MAIN);
  lv_obj_set_style_pad_left(grid, 4, LV_PART_MAIN);
  lv_obj_set_style_pad_right(grid, 4, LV_PART_MAIN);
  lv_obj_set_style_pad_row(grid, 4, 0);
  lv_obj_set_style_pad_column(grid, 4, 0);
  lv_obj_set_grid_dsc_array(grid, col_dsc2, row_dsc2);

  int i,row,col;

  for(i = 0; i < 4; i++)
  {

    cell = lv_obj_create(grid);

    if (cell != NULL)
    {
      row = i;
      col = 1;

      lv_obj_clear_flag(cell, LV_OBJ_FLAG_SCROLLABLE);

      lv_obj_set_style_bg_color(cell,lv_palette_darken(LV_PALETTE_BLUE_GREY,4), LV_PART_MAIN);

      lv_obj_set_style_pad_all(cell, 0, LV_PART_MAIN);
      lv_obj_set_style_pad_left(cell, 10, LV_PART_MAIN);

      lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_STRETCH, row, 1);

      lv_obj_set_flex_flow(cell, LV_FLEX_FLOW_ROW);          
      //lv_obj_set_flex_align(cell, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);          
      lv_obj_set_flex_align(cell, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);          
      lv_obj_set_style_pad_column(cell, 10, 0); //Space between widgets

      byte count = 5;
      if ((row==2) || (row==3)) count = 6;
      obj = create_display(cell, lv_palette_main(LV_PALETTE_RED), false, count);
      Display[i] = obj;

      obj = lv_label_create(cell);
      lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
      lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);
      lv_obj_set_style_text_color(obj, lv_palette_main(LV_PALETTE_YELLOW), LV_PART_MAIN | LV_STATE_DEFAULT );	
      switch (row)
      {
        case 0: {lv_label_set_text(obj, "Volt"); break;}
        case 1: {lv_label_set_text(obj, "Amps"); break;}        
        case 2: {lv_label_set_text(obj, "mAh"); break;}                
        case 3: {lv_label_set_text(obj, "mWh"); break;}                        
      }
      lv_obj_set_style_translate_x(obj, -8, LV_PART_MAIN| LV_STATE_DEFAULT);          
      lv_obj_set_style_translate_y(obj, -6, LV_PART_MAIN| LV_STATE_DEFAULT);
    }

    cell = lv_obj_create(grid);

    if (cell != NULL)
    {
      row = i;
      col = 0;

      lv_obj_clear_flag(cell, LV_OBJ_FLAG_SCROLLABLE);      

      lv_obj_set_style_bg_color(cell,lv_palette_darken(LV_PALETTE_BLUE_GREY,4), LV_PART_MAIN);

      lv_obj_set_style_pad_all(cell, 0, LV_PART_MAIN);
      lv_obj_set_style_pad_left(cell, 10, LV_PART_MAIN);

      lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_STRETCH, row, 1);

      lv_obj_set_flex_flow(cell, LV_FLEX_FLOW_ROW);          
      lv_obj_set_flex_align(cell, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);          
      lv_obj_set_style_pad_column(cell, 10, 0); //Space between widgets

      obj = lv_label_create(cell);
      lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
      lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);
      lv_obj_set_style_text_color(obj, lv_palette_main(LV_PALETTE_YELLOW), LV_PART_MAIN | LV_STATE_DEFAULT );	
      switch (row)
      {
        case 0: {lv_label_set_text(obj, "Voltage"); break;}
        case 1: {lv_label_set_text(obj, "Current"); break;}        
        case 2: {lv_label_set_text(obj, "Capacity"); break;}                
        case 3: {lv_label_set_text(obj, "Energy"); break;}                        
      }
    }

    cell = lv_obj_create(grid);

    if (cell != NULL)
    {
      row = i;
      col = 2;

      lv_obj_remove_style_all(cell);

      lv_obj_clear_flag(cell, LV_OBJ_FLAG_SCROLLABLE);      

      lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_STRETCH, row, 1);

      //lv_obj_set_style_bg_color(cell,lv_palette_darken(LV_PALETTE_BLUE_GREY,4), LV_PART_MAIN);

      lv_obj_set_style_pad_all(cell, 0, LV_PART_MAIN);
      //lv_obj_set_style_pad_left(cell, 10, LV_PART_MAIN);

      obj = lv_button_create(cell);
      lv_obj_set_size(obj, lv_pct(80), lv_pct(80));
      lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
      //lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);

      if ((row==2) || (row==3))
      {
        //lv_obj_add_event_cb(obj, event_cb, LV_EVENT_VALUE_CHANGED, (void *)btn_start_discharge);
        lv_obj_set_style_bg_color(obj,lv_palette_darken(LV_PALETTE_RED,4), LV_PART_MAIN);      

        label = lv_label_create(obj);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);  
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(label, "Zero");

        if (row==2) zerocapacitybutton = obj;
        if (row==3) zeroenergybutton = obj;
      }
      else
      {
        lv_obj_add_state(obj,LV_STATE_DISABLED);
      }
    }  
  }  

  lv_obj_t * bottom_cont = lv_obj_create(cont);
  lv_obj_remove_style_all(bottom_cont);
  lv_obj_clear_flag(bottom_cont, LV_OBJ_FLAG_SCROLLABLE);  
  lv_obj_set_size(bottom_cont, lv_pct(100), lv_pct(15));
  lv_obj_align(bottom_cont, LV_ALIGN_BOTTOM_MID, 0, 0);    
  //lv_obj_set_flex_align(bottom_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);          

  btn = lv_button_create(bottom_cont);
  lv_obj_set_size(btn, lv_pct(48), LV_SIZE_CONTENT);
  //lv_obj_set_size(btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);    
  lv_obj_align(btn, LV_ALIGN_LEFT_MID, 6, 0);
  lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_VALUE_CHANGED, (void *)btn_start_discharge);      
  lv_obj_set_style_bg_color(btn, lv_palette_darken(LV_PALETTE_RED,3), LV_PART_MAIN | LV_STATE_CHECKED);             

  label = lv_label_create(btn);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_24, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(label, "GO DISCHARGE");

  startdischargebutton = btn;


  btn = lv_button_create(bottom_cont);
  lv_obj_set_size(btn, lv_pct(48), LV_SIZE_CONTENT);
  //lv_obj_set_size(btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);    
  lv_obj_align(btn, LV_ALIGN_RIGHT_MID, -6, 0);
  lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_VALUE_CHANGED, (void *)btn_start_charge);      
  lv_obj_set_style_bg_color(btn, lv_palette_darken(LV_PALETTE_RED,3), LV_PART_MAIN | LV_STATE_CHECKED);             

  label = lv_label_create(btn);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_24, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(label, "GO CHARGE");

  startchargebutton = btn;
  }
}

void Screen3SetData(PBatterySetting SET)
{
  bool StartDisabled;
  bool TestDisabled;

  Settings = SET;

  //char str[10] = "yolo";
  char str[10] = "";
  sprintf(str, "%d", Settings->Stages[FIXEDDISCHARGESTAGENUMBER].SetValue);
  lv_textarea_set_text(ta1, str);
  sprintf(str, "%d", Settings->Stages[FIXEDCHARGESTAGENUMBER].SetValue);
  lv_textarea_set_text(ta2, str);

  StartDisabled = false;
  TestDisabled = false;

  if (Settings->TestData.Active == bmActive)
  {
    TestDisabled = true;
    if (Settings->TestData.SetStageMode != smCurrent) StartDisabled = true;
    if (Settings->TestData.SetStageMode == smCurrent) lv_obj_add_state(startdischargebutton,LV_STATE_CHECKED);
  }
  else
  {
    // if not discharging or off, disable all
    if ( (Settings->TestData.SetStageMode != smCurrent) && (Settings->TestData.SetStageMode != smOff) )
    {
       StartDisabled = true;
       TestDisabled = true;       
    }
    // If test-discharging, disable start
    if (Settings->TestData.SetStageMode == smCurrent)
    {
      StartDisabled = true;
      lv_obj_add_state(testdischargebutton,LV_STATE_CHECKED);
    }  
  }

  if (StartDisabled) lv_obj_add_state(startdischargebutton,LV_STATE_DISABLED);
  if (TestDisabled) lv_obj_add_state(testdischargebutton,LV_STATE_DISABLED);  

  if ( (StartDisabled) || (TestDisabled) )
  {
    lv_obj_add_state(zerocapacitybutton,LV_STATE_DISABLED);
    lv_obj_add_state(zeroenergybutton,LV_STATE_DISABLED);
  }

  StartDisabled = false;
  TestDisabled = false;

  if (Settings->TestData.Active == bmActive)
  {
    TestDisabled = true;
    if (Settings->TestData.SetStageMode != smCharge) StartDisabled = true;
    if (Settings->TestData.SetStageMode == smCharge) lv_obj_add_state(startchargebutton,LV_STATE_CHECKED);
  }
  else
  {
    // if not charging or off, disable all
    if ( (Settings->TestData.SetStageMode != smCharge) && (Settings->TestData.SetStageMode != smOff) )
    {
       StartDisabled = true;
       TestDisabled = true;       
    }
    // If test-charging, disable start
    if (Settings->TestData.SetStageMode == smCharge)
    {
      StartDisabled = true;
      lv_obj_add_state(testchargebutton,LV_STATE_CHECKED);      
    }
  }

  if (StartDisabled) lv_obj_add_state(startchargebutton,LV_STATE_DISABLED);
  if (TestDisabled) lv_obj_add_state(testchargebutton,LV_STATE_DISABLED);  

  if ( (StartDisabled) || (TestDisabled) )
  {
    lv_obj_add_state(zerocapacitybutton,LV_STATE_DISABLED);
    lv_obj_add_state(zeroenergybutton,LV_STATE_DISABLED);
  }
}

void Screen3AddData(word V, word I, dword E, dword C)
{
  dword tempcalc;

  tempcalc = V * MAXVOLTAGE;
  tempcalc /= (dword)((1u << BITS)-1u);
  if (Display[0] != NULL) SetDisplaymV(Display[0], tempcalc);

  tempcalc = I * MAXCURRENT;
  tempcalc /= (dword)((1u << BITS)-1u);
  if (Display[1] != NULL) SetDisplaymV(Display[1], tempcalc);

  if (Display[2] != NULL) SetDisplaymV(Display[2], C);

  if (Display[3] != NULL) SetDisplaymV(Display[3], E);
}
