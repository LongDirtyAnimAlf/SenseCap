#include "Screenbase.h"

#define CHARTSIZE 255

static byte SelectedIndex = 255; // valid numbers from 0 to 15 = daughterboardcount

#define SCREENINDEX 2

static lv_obj_t * Screen2VoltageDisplay = NULL;
static lv_obj_t * Screen2CurrentDisplay = NULL;
static lv_obj_t * chart = NULL;
static lv_chart_series_t * voltage_series = NULL;
static lv_chart_series_t * current_series = NULL;

void Setup_Screen2(byte index)
{
  lv_obj_t * obj = NULL;
  lv_obj_t * cont = NULL;

  if (index<DAUGHTERBOARDCOUNT)
  {
    SelectedIndex = index;
    obj = GetInfoObject();
    if (obj != NULL) lv_label_set_text_fmt(obj,"Battery #%d",SelectedIndex+1);
  }

  obj = GetButtonLabelObject();
  if (obj != NULL) lv_label_set_text(obj,"Control");

  cont = GetContentObject(1U);

  if (lv_obj_get_child_count(cont) == 0)
  {
  
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

  Screen2VoltageDisplay = create_display(cell, lv_palette_main(LV_PALETTE_RED), true, 5);
  //lv_obj_null_on_delete(&Screen2VoltageDisplay);
  lv_obj_add_style(Screen2VoltageDisplay, &style2, 0);  
  lv_obj_align(Screen2VoltageDisplay, LV_ALIGN_CENTER, 0, 0);

  cell = lv_obj_create(grid);
  lv_obj_remove_style_all(cell);
  lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

  Screen2CurrentDisplay = create_display(cell, lv_palette_main(LV_PALETTE_GREEN), true, 5);
  //lv_obj_null_on_delete(&Screen2CurrentDisplay);
  lv_obj_add_style(Screen2CurrentDisplay, &style2, 0);  
  lv_obj_align(Screen2CurrentDisplay, LV_ALIGN_CENTER, 0, 0);
 
  cell = lv_obj_create(grid);
  lv_obj_remove_style_all(cell);
  lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_STRETCH, 1, 1);

  lv_obj_t * scale_y = lv_scale_create(cell);
  lv_obj_set_size(scale_y, lv_pct(8), lv_pct(96));

  chart = lv_chart_create(cell);
  //lv_obj_null_on_delete(&chart);  
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
  //lv_obj_null_on_delete(&voltage_series);  
  current_series = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);  
  //lv_obj_null_on_delete(&current_series);    

  lv_obj_set_style_pad_ver(scale_y, lv_chart_get_first_point_center_offset(chart), 0);

  obj = lv_label_create(cell);
  lv_obj_align_to(obj, scale_y, LV_ALIGN_OUT_RIGHT_TOP, 5, 0);
  lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);  
  lv_label_set_text(obj, "Volt / Amps");
  }
}

void Screen2AddData(word V, word I)
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

byte Screen2GetActive(void)
{
  return SelectedIndex;
}

void Screen2SetData(PRunDatas MAD)
{
  if (Screen2VoltageDisplay != NULL) SetDisplaymV(Screen2VoltageDisplay, 0);          
  if (Screen2CurrentDisplay != NULL) SetDisplaymV(Screen2CurrentDisplay, 0);

  if (voltage_series != NULL) lv_chart_set_all_value(chart, voltage_series, LV_CHART_POINT_NONE);
  if (current_series != NULL) lv_chart_set_all_value(chart, current_series, LV_CHART_POINT_NONE);

  if (MAD->Head != -1)
  {
    word i,j;
    dword tempvcalc,tempicalc = 0;
    int start,stop,runner;
    PMeasurementData BD;
  
    stop = (MAD->Head + DATASIZE);
    if (MAD->Tail == -1) start = DATASIZE; start = (MAD->Tail + DATASIZE);

    if (start>stop) stop += DATASIZE;
    if ((stop-start)>=CHARTSIZE)  start = (stop - CHARTSIZE);

    for(runner = start; runner <= stop; runner++)
    {
      j = runner % DATASIZE;
      BD = &MAD->BatteryDatas[j];

      tempvcalc = BD->V * MAXVOLTAGE;
      tempvcalc /= (dword)((1u << BITS)-1u);
      if (voltage_series != NULL) lv_chart_set_next_value(chart, voltage_series, (word)tempvcalc);

      tempicalc = BD->I * MAXCURRENT;
      tempicalc /= (dword)((1u << BITS)-1u);
      if (current_series != NULL) lv_chart_set_next_value(chart, current_series, (word)tempicalc);
    }

    if (Screen2VoltageDisplay != NULL) SetDisplaymV(Screen2VoltageDisplay, (word)tempvcalc);
    if (Screen2CurrentDisplay != NULL) SetDisplaymV(Screen2CurrentDisplay, (word)tempicalc);

  }
}
