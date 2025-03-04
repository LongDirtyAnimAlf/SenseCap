#include <lvgl.h>
#include "shared.h"
#include "sevensegment.h"

lv_obj_t * screen1;

static lv_obj_t * Screen1Display[MAXDAUGHTERBOARDCOUNT] = {NULL};
static lv_obj_t * Screen1Led[MAXDAUGHTERBOARDCOUNT] = {NULL};
static lv_obj_t *unit_label[MAXDAUGHTERBOARDCOUNT] = {NULL};

static word VoltagemV[MAXDAUGHTERBOARDCOUNT] = {0};
static word CurrentmA[MAXDAUGHTERBOARDCOUNT] = {0};

static bool VI = true;

extern const lv_font_t lv_font_montserrat_32;

static void display_event_handler(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * btn = lv_event_get_current_target_obj(e);

  if (btn != NULL)
  {
    if(code == LV_EVENT_CLICKED)
    {
      int * btn_no = (int*)lv_event_get_user_data(e);

      if (btn_no==0) VI = true;
      if (btn_no==1) VI = false;

      int i = 0;
      word data;  

      for(i = 0; i < MAXDAUGHTERBOARDCOUNT; i++)
      {

        if (i < DAUGHTERBOARDCOUNT)
        {
          if (VI) data = VoltagemV[i]; else data = CurrentmA[i];
          SetDisplaymV(Screen1Display[i], data);
        }

        if (VI)
        {
          lv_label_set_text(unit_label[i], "V");
          lv_obj_set_style_translate_y(unit_label[i], -6, LV_PART_MAIN| LV_STATE_DEFAULT);
        }
        else
        {
          lv_label_set_text(unit_label[i], "A");
          lv_obj_set_style_translate_y(unit_label[i], 6, LV_PART_MAIN| LV_STATE_DEFAULT);
        }
      }
    }
  }
}

void Create_Screen1(lv_event_cb_t event_cb_more)
{
  lv_obj_t * obj = NULL;

  screen1 = lv_obj_create(NULL);

  lv_obj_t * nav = lv_obj_create(screen1);
  lv_obj_set_style_pad_top(nav, 6, LV_PART_MAIN);
  lv_obj_set_style_pad_bottom(nav, 6, LV_PART_MAIN);
  lv_obj_set_style_pad_left(nav, 2, LV_PART_MAIN);
  lv_obj_set_style_pad_right(nav, 2, LV_PART_MAIN);

  lv_obj_set_size(nav, lv_pct(100), LV_SIZE_CONTENT);
  lv_obj_align(nav, LV_ALIGN_TOP_MID, 0, 0);

  obj = lv_btn_create(nav);
  lv_obj_align(obj, LV_ALIGN_RIGHT_MID, 0, 0);
  lv_obj_set_size(obj, lv_pct(25), LV_SIZE_CONTENT);
  lv_obj_add_event_cb(obj, display_event_handler, LV_EVENT_CLICKED, (void *)0);
  lv_obj_set_style_bg_color(obj,lv_palette_darken(LV_PALETTE_GREEN,4), LV_PART_MAIN);      

  obj = lv_label_create(obj);
  lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(obj, "Voltage");

  obj = lv_btn_create(nav);
  lv_obj_align(obj, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_set_size(obj, lv_pct(25), LV_SIZE_CONTENT);
  lv_obj_add_event_cb(obj, display_event_handler, LV_EVENT_CLICKED, (void *)1);      
  lv_obj_set_style_bg_color(obj,lv_palette_darken(LV_PALETTE_GREEN,4), LV_PART_MAIN);      

  obj = lv_label_create(obj);
  lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(obj, "Current");

  obj = lv_label_create(nav);
  lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(obj, "CONSULAB");
  lv_obj_set_style_bg_color(obj,lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN); 
  lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN| LV_STATE_DEFAULT);

  lv_obj_update_layout(nav);
  int nav_height = lv_obj_get_height(nav);

  static lv_coord_t col_dsc[] = { LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };
  static lv_coord_t row_dsc[] = { LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };

  lv_obj_t* grid = lv_obj_create(screen1);

  lv_obj_set_size(grid, lv_pct(100), lv_pct(100));
  lv_obj_align(grid, LV_ALIGN_BOTTOM_MID, 0, 0);

  lv_obj_set_style_margin_top(grid, nav_height, LV_PART_MAIN);	

  lv_obj_set_style_pad_top(grid, 4, LV_PART_MAIN);
  lv_obj_set_style_pad_bottom(grid, 4, LV_PART_MAIN);
  lv_obj_set_style_pad_left(grid, 4, LV_PART_MAIN);
  lv_obj_set_style_pad_right(grid, 4, LV_PART_MAIN);
  lv_obj_set_style_pad_row(grid, 4, 0);
  lv_obj_set_style_pad_column(grid, 4, 0);
  lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);

  int i = 0;
  for(i = 0; i < MAXDAUGHTERBOARDCOUNT; i++)
  {
    int row = i % (MAXDAUGHTERBOARDCOUNT / 2);
    int col = i / (MAXDAUGHTERBOARDCOUNT / 2);

    lv_obj_t * cell = lv_obj_create(grid);

    if (cell != NULL)
    {
      uint32_t idx = lv_obj_get_index(cell);

      lv_obj_set_style_bg_color(cell,lv_palette_darken(LV_PALETTE_BLUE_GREY,4), LV_PART_MAIN);


      lv_obj_set_style_pad_all(cell, 0, LV_PART_MAIN);
      lv_obj_set_style_pad_left(cell, 10, LV_PART_MAIN);

      lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_STRETCH, row, 1);

      lv_obj_set_flex_flow(cell, LV_FLEX_FLOW_ROW);          
      //lv_obj_set_flex_align(cell, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);          
      lv_obj_set_flex_align(cell, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);          
      lv_obj_set_style_pad_column(cell, 10, 0); //Space between widgets

      Screen1Led[i]  = lv_led_create(cell);
      lv_led_set_brightness(Screen1Led[i], 255);
      lv_led_set_color(Screen1Led[i], lv_palette_main(LV_PALETTE_BLUE));
      //lv_led_set_color(Screen1Led[i], LV_COLOR_MAKE(0,0xFF,0xFF));

      obj = lv_label_create(Screen1Led[i]);
      lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
      lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
      lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);
      lv_obj_set_style_text_color(obj, lv_color_black(), LV_PART_MAIN | LV_STATE_DEFAULT );	
      if (i<DAUGHTERBOARDCOUNT)
      {
        lv_label_set_text_fmt(obj, "%d", (i+1));
      }
      else
      {
        lv_label_set_text(obj, "-");
      }

      Screen1Display[i] = create_display(cell, lv_palette_main(LV_PALETTE_RED), false, 5);

      unit_label[i] = lv_label_create(cell);
      lv_obj_set_style_text_opa(unit_label[i], 255, LV_PART_MAIN| LV_STATE_DEFAULT);
      lv_obj_set_style_text_font(unit_label[i], &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);
      lv_obj_set_style_text_color(unit_label[i], lv_palette_main(LV_PALETTE_YELLOW), LV_PART_MAIN | LV_STATE_DEFAULT );	
      lv_label_set_text(unit_label[i], "V");
      lv_obj_set_style_translate_x(unit_label[i], -8, LV_PART_MAIN| LV_STATE_DEFAULT);          
      lv_obj_set_style_translate_y(unit_label[i], -6, LV_PART_MAIN| LV_STATE_DEFAULT);

      lv_obj_t *cell_button = lv_btn_create(cell);
      lv_obj_set_size(cell_button, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
      lv_obj_set_style_translate_x(cell_button, -4, LV_PART_MAIN| LV_STATE_DEFAULT);          
      lv_obj_set_style_pad_top(cell_button, 8, LV_PART_MAIN);
      lv_obj_set_style_pad_bottom(cell_button, 8, LV_PART_MAIN);
      lv_obj_set_style_pad_left(cell_button, 6, LV_PART_MAIN);
      lv_obj_set_style_pad_right(cell_button, 6, LV_PART_MAIN);
      lv_obj_set_style_bg_color(cell_button,lv_palette_darken(LV_PALETTE_INDIGO,4), LV_PART_MAIN);
      if (i<DAUGHTERBOARDCOUNT)
      {
        // Add event with userdata to indicate which battery button was used
        lv_obj_add_event_cb(cell_button, event_cb_more, LV_EVENT_CLICKED, (void *)(i+1));   
      }
      else
      {
        lv_obj_add_state(cell_button,LV_STATE_DISABLED);
      }

      lv_obj_t * label = lv_label_create(cell_button);
      if (i<DAUGHTERBOARDCOUNT)
      {
        lv_label_set_text(label, "More");
      }
      else
      {
        lv_label_set_text(label, "------");
      }
      lv_obj_center(label);
    }
  }  
}

void SetVoltageScreen1mV(uint8_t Index, word data)
{
  if (screen1 == NULL) return;

  if (Index<DAUGHTERBOARDCOUNT)
  {
    VoltagemV[Index] = data;
    if (Screen1Display[Index] != NULL)
    {
      if (VI) SetDisplaymV(Screen1Display[Index], data);
    }
  }
}
void SetCurrentScreen1mA(uint8_t Index, word data)
{
  if (screen1 == NULL) return;

  if (Index<DAUGHTERBOARDCOUNT)
  {
    CurrentmA[Index] = data;
    if (Screen1Display[Index] != NULL)
    {
      if (!VI) SetDisplaymV(Screen1Display[Index], data);
    }
  }
}

void SetLedScreen1(uint8_t Index, lv_color_t c)
{
  if (screen1 == NULL) return;

  if (Index<DAUGHTERBOARDCOUNT)
  {
    if (Screen1Led[Index] != NULL)
    {
      lv_led_set_color(Screen1Led[Index], c);  
    }
  }
}


#ifdef YOLO

#define NUM_HIST_X_LABELS	25
#define NUM_HIST_Y_LABELS	13
#define MINUTES_IN_A_DAY	1440
#define CHART_HEIGHT	410
#define CHART_WIDTH		610

static char 				*history_x_buf[NUM_HIST_X_LABELS];
static char 				*history_y_buf[NUM_HIST_Y_LABELS];
static lv_obj_t				*chart_history;
static lv_chart_series_t	*series_history;
static lv_coord_t			history[MINUTES_IN_A_DAY];


static void hist_chart_event_cb(lv_event_t * e) {

	lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
	if(!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL)/* || (dsc->value > 4)*/) return;
	static int32_t idx = NUM_HIST_Y_LABELS-1;

	if(dsc->id == LV_CHART_AXIS_PRIMARY_Y && dsc->text) {
		lv_snprintf(dsc->text, dsc->text_length, "%s", history_y_buf[idx]);
		if( --idx == -1 ) idx = NUM_HIST_Y_LABELS-1;
	} else if(dsc->id == LV_CHART_AXIS_PRIMARY_X && dsc->text) {
		lv_snprintf(dsc->text, dsc->text_length, "%s", history_x_buf[dsc->value]);
	}
}

static double random_temperature( void ) {

	double range = -120;

	range *= ((double)rand()/(double)(RAND_MAX));
	range += 100; // generate random temperature between -20 and 100
	printf( "temperature:%f\n", range);
	fflush(stdout);
	return( range );
}

static void update_chart( lv_timer_t * timer ) {

	static uint16_t idx = 0;

	lv_coord_t chart_value = (lv_coord_t)((random_temperature()+20) * 10); // get a random temperature and scale it to our chart
	printf( "scaled for chart:%d\n", chart_value);
	fflush(stdout);

	lv_chart_set_value_by_id(chart_history, series_history, idx % MINUTES_IN_A_DAY , chart_value );
	idx++;
}

static void make_chart( void ) {

	double			ticks;
	int32_t			i_pnt;

	chart_history = lv_chart_create(lv_scr_act());
	lv_obj_set_style_text_font (chart_history, &lv_font_roboto_8, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_size(chart_history, CHART_WIDTH, CHART_HEIGHT);
	lv_obj_align(chart_history, LV_ALIGN_BOTTOM_MID, 28, -50);
	lv_chart_set_type(chart_history, LV_CHART_TYPE_LINE);
	lv_chart_set_range(chart_history, LV_CHART_AXIS_PRIMARY_Y, 0, 1200 );
	lv_chart_set_div_line_count(chart_history, 13, 25);
	lv_chart_set_update_mode(chart_history, LV_CHART_UPDATE_MODE_CIRCULAR);	//LV_CHART_UPDATE_MODE_SHIFT
	lv_chart_set_axis_tick(chart_history, LV_CHART_AXIS_PRIMARY_X, 10, 5, 25, 1, true, 50);
	lv_chart_set_axis_tick(chart_history, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 13, 5, true, 30);
	/*Add a data series*/
	series_history = lv_chart_add_series(chart_history, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
	lv_obj_set_style_line_width(chart_history, 1, LV_PART_INDICATOR);
	lv_obj_set_style_size(chart_history, 0, LV_PART_INDICATOR);
	lv_chart_set_ext_y_array(chart_history, series_history, history);
	lv_chart_set_point_count(chart_history, sizeof(history)/sizeof(history[0]));
	lv_obj_update_layout(chart_history);
	// These never change so just set them the first time...
	i_pnt = 0;
	int32_t i = NUM_HIST_Y_LABELS-1;
	char buf[40];
	for( ticks=100; ticks >= -30; ticks-= 10 ) {
		i_pnt = snprintf( buf, sizeof(buf), "%6.1f", ticks  );
		history_y_buf[i] = malloc(i_pnt);
		strcpy( history_y_buf[i--], buf );

	}
	for( int iticks = 0; iticks < NUM_HIST_X_LABELS; iticks++ ) {
			i_pnt = snprintf( buf, sizeof(buf), "%02d\n", iticks );
			history_x_buf[iticks] = malloc(i_pnt);
			if( iticks < 24 ) strcpy( history_x_buf[iticks], buf );
			else history_x_buf[iticks][0] = 0;// Set Null string for last tick
	}
    lv_obj_add_event_cb(chart_history, hist_chart_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
	lv_timer_create((void*)update_chart, 250, NULL );  // Update the chart periodically

}
#endif
