#include <Arduino.h>
#include <lvgl.h>
#include "sevensegment.h"
#include "shared.h"

#define DATASIZE 2000
#define CHARTSIZE 255

extern const lv_font_t lv_font_montserrat_18;
extern const lv_font_t lv_font_montserrat_32;

typedef struct
{
  word V;
  word I;
} __attribute__ ((packed)) BatteryData;

typedef struct
{
  BatteryData *BatteryDatas;
  int16_t Tail;
  int16_t Head;
} BatteryAllData;

BatteryAllData Datas[DAUGHTERBOARDCOUNT];// = {0};
static byte SelectedBattery = 0; // valid numbers from 1 to 16

lv_obj_t * screen2 = NULL;
static lv_obj_t * Screen2VoltageDisplay = NULL;
static lv_obj_t * Screen2CurrentDisplay = NULL;
static lv_obj_t * Screen2Info = NULL;
static lv_obj_t * chart = NULL;
static lv_chart_series_t * voltage_series = NULL;
static lv_chart_series_t * current_series = NULL;

void Screen2Create(lv_event_cb_t event_cb_more)
{
  lv_obj_t * obj = NULL;

  screen2 = lv_obj_create(NULL);

  lv_obj_t * nav = lv_obj_create(screen2);
  lv_obj_set_style_pad_top(nav, 6, LV_PART_MAIN);
  lv_obj_set_style_pad_bottom(nav, 6, LV_PART_MAIN);
  lv_obj_set_style_pad_left(nav, 2, LV_PART_MAIN);
  lv_obj_set_style_pad_right(nav, 2, LV_PART_MAIN);

  lv_obj_set_size(nav, lv_pct(100), LV_SIZE_CONTENT);
  lv_obj_align(nav, LV_ALIGN_BOTTOM_MID, 0, 0);

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

  Screen2Info = lv_label_create(nav);
  lv_obj_align(Screen2Info, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_font(Screen2Info, &lv_font_montserrat_32, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_label_set_text(Screen2Info, "INFO");

  lv_obj_update_layout(nav);
  int nav_height = lv_obj_get_height(nav);

  lv_obj_t * cont = lv_obj_create(screen2);
  lv_obj_remove_style_all(cont);
  lv_obj_set_size(cont, lv_pct(100), lv_pct(100));
  lv_obj_align(cont, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_set_style_margin_bottom(cont, nav_height, LV_PART_MAIN);

  static int32_t col_dsc2[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  static int32_t row_dsc2[] = {LV_GRID_FR(2), LV_GRID_FR(6), LV_GRID_TEMPLATE_LAST};

  lv_obj_t * grid = lv_obj_create(cont);
  lv_obj_set_size(grid, lv_pct(100), lv_pct(100));
  lv_obj_set_style_pad_all(grid, 0, LV_PART_MAIN);

  lv_obj_set_style_pad_row(grid, 0, 0);
  lv_obj_set_style_pad_column(grid, 0, 0);
  lv_obj_set_grid_dsc_array(grid, col_dsc2, row_dsc2);
  lv_obj_center(grid);

  // Style for 7 segment panel
  static lv_style_t style2;
  lv_style_init(&style2);
  // Set a background color and a radius
  lv_style_set_bg_opa(&style2, LV_OPA_COVER);
  lv_style_set_bg_color(&style2, lv_palette_lighten(LV_PALETTE_GREY, 1));
  // Add a shadow
  lv_style_set_shadow_width(&style2, 30);
  lv_style_set_shadow_color(&style2, lv_palette_main(LV_PALETTE_BLUE));

  lv_obj_t * cell = NULL;

  cell = lv_obj_create(grid);
  lv_obj_remove_style_all(cell);
  lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

  Screen2VoltageDisplay = create_display(cell, lv_palette_main(LV_PALETTE_RED), true);
  lv_obj_add_style(Screen2VoltageDisplay, &style2, 0);  
  lv_obj_align(Screen2VoltageDisplay, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_flag(Screen2VoltageDisplay, LV_OBJ_FLAG_USER_1);

  cell = lv_obj_create(grid);
  lv_obj_remove_style_all(cell);
  lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

  Screen2CurrentDisplay = create_display(cell, lv_palette_main(LV_PALETTE_GREEN), true);
  lv_obj_add_style(Screen2CurrentDisplay, &style2, 0);  
  lv_obj_align(Screen2CurrentDisplay, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_flag(Screen2CurrentDisplay, LV_OBJ_FLAG_USER_2);
 
  cell = lv_obj_create(grid);
  lv_obj_remove_style_all(cell);
  lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_STRETCH, 1, 1);

  lv_obj_t * scale_y = lv_scale_create(cell);
  lv_obj_set_size(scale_y, lv_pct(8), lv_pct(96));

  chart = lv_chart_create(cell);
  lv_obj_set_size(chart, lv_pct(92), lv_pct(96));

  // Set scale
  lv_scale_set_mode(scale_y, LV_SCALE_MODE_VERTICAL_LEFT);
  lv_obj_align(scale_y, LV_ALIGN_LEFT_MID, 0, 0);    
  lv_scale_set_total_tick_count(scale_y, 21);
  lv_scale_set_major_tick_every(scale_y, 5);

  static const char * voltages[] = {"0.0", "0.5", "1.0", "1.5", "2.0", NULL};
  lv_scale_set_text_src(scale_y, voltages);

  // Set chart
  lv_obj_align(chart, LV_ALIGN_RIGHT_MID, 0, 0);
  lv_chart_set_type(chart, LV_CHART_TYPE_LINE);   //Show lines and points too

  lv_obj_set_style_pad_all(chart, 0, 0);
  lv_obj_set_style_radius(chart, 0, 0);
  lv_chart_set_div_line_count(chart, 5, 0);

  lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT);
  lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 2000);    
  lv_chart_set_point_count(chart, CHARTSIZE);  

  voltage_series = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
  current_series = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);  

  lv_obj_set_style_pad_ver(scale_y, lv_chart_get_first_point_center_offset(chart), 0);

  obj = lv_label_create(cell);
  lv_obj_align_to(obj, scale_y, LV_ALIGN_OUT_RIGHT_TOP, 5, 0);
  lv_obj_set_style_text_font(Screen2Info, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_label_set_text(obj, "Volt / Amps");
}

void Screen2InitData(void)
{
  for(byte i = 0; i < DAUGHTERBOARDCOUNT; i++)
  {
    Datas[i].BatteryDatas = (BatteryData*)malloc(DATASIZE * sizeof(BatteryData));
    memset(Datas[i].BatteryDatas, 0, DATASIZE * sizeof(BatteryData));
    Datas[i].Tail = -1;
    Datas[i].Head = -1;
  }
}

void Screen2EmptyData(void)
{
  for(byte i = 0; i < DAUGHTERBOARDCOUNT; i++)
  {
    memset(Datas[i].BatteryDatas, 0, DATASIZE * sizeof(BatteryData));
    Datas[i].Tail = -1;
    Datas[i].Head = -1;
  }
}

void Screen2AddData(byte BN, word V, word I)
{
  static bool GoAround[DAUGHTERBOARDCOUNT] = {false};

  if ((BN!=0) && (BN<=DAUGHTERBOARDCOUNT))
  {
    BatteryAllData * BAD  = &Datas[BN-1];

    // Reset GoAround in needed
    if ((BAD->Head == -1) && (BAD->Tail == -1)) GoAround[BN-1] = false;

    if (GoAround[BN-1])
    {
      BAD->Tail++;
      if (BAD->Tail >= DATASIZE) BAD->Tail = 0;
    }

    BAD->Head++;
    if (BAD->Head >= DATASIZE)
    {
      BAD->Head = 0;
      if (!GoAround[BN-1]) BAD->Tail = 1; // Preset tail to last added value
      GoAround[BN-1] = true;
    }

    BatteryData * BD = &BAD->BatteryDatas[BAD->Head];

    BD->V = V;
    BD->I = I;

    if ((BN) == SelectedBattery)
    {
      dword tempcalc;
      tempcalc = V * MAXVOLTAGE;
      tempcalc /= (dword)((1u << BITS)-1u);
      if (Screen2VoltageDisplay != NULL) SetDisplaymV(Screen2VoltageDisplay, (word)tempcalc);
      if (voltage_series != NULL) lv_chart_set_next_value(chart, voltage_series, (word)tempcalc);

      tempcalc = I * MAXCURRENT;
      tempcalc /= (dword)((1u << BITS)-1u);
      if (Screen2CurrentDisplay != NULL)  SetDisplaymV(Screen2CurrentDisplay, (word)tempcalc);
      if (current_series != NULL) lv_chart_set_next_value(chart, current_series, (word)tempcalc);
    }
  }
}

byte Screen2GetActive(void)
{
  return SelectedBattery;
}

void Screen2SetActive(byte BN)
{
  if ((BN!=0) && (BN<=DAUGHTERBOARDCOUNT))
  {
    if (SelectedBattery != BN)
    {
      SelectedBattery = BN;

      if (Screen2VoltageDisplay != NULL) SetDisplaymV(Screen2VoltageDisplay, 0);          
      if (Screen2CurrentDisplay != NULL) SetDisplaymV(Screen2CurrentDisplay, 0);

      lv_label_set_text_fmt(Screen2Info,"Battery #%d",SelectedBattery);

      if (voltage_series != NULL) lv_chart_set_all_value(chart, voltage_series, LV_CHART_POINT_NONE);
      if (current_series != NULL) lv_chart_set_all_value(chart, current_series, LV_CHART_POINT_NONE);

      BatteryAllData * BAD  = &Datas[BN-1];

      if (BAD->Head != -1)
      {
        word i,j;
        dword tempcalc;
        int start,stop,runner;
        BatteryData * BD;
  
        stop = (BAD->Head + DATASIZE);
        if (BAD->Tail == -1) start = DATASIZE; start = (BAD->Tail + DATASIZE);

        if (start>stop) stop += DATASIZE;
        if ((stop-start)>=CHARTSIZE)  start = (stop - CHARTSIZE);

        for(runner = start; runner <= stop; runner++)
        {
          j = runner % DATASIZE;
          BD = &BAD->BatteryDatas[j];

          tempcalc = BD->V * MAXVOLTAGE;
          tempcalc /= (dword)((1u << BITS)-1u);
          if (voltage_series != NULL) lv_chart_set_next_value(chart, voltage_series, (word)tempcalc);
          if ((Screen2VoltageDisplay != NULL) && (runner==stop)) SetDisplaymV(Screen2VoltageDisplay, (word)tempcalc);

          tempcalc = BD->I * MAXCURRENT;
          tempcalc /= (dword)((1u << BITS)-1u);
          if (current_series != NULL) lv_chart_set_next_value(chart, current_series, (word)tempcalc);
          if ((Screen2CurrentDisplay != NULL) && (runner==stop)) SetDisplaymV(Screen2CurrentDisplay, (word)tempcalc);
        }
      }
    }
  }
}
