#include "lvgldriver.h"

lv_display_t *disp = NULL;

Arduino_RGB_Display *gfxdisplay = NULL;

#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /*will be 2 for RGB565 */

#define LVGL_DRAW_BUF_LINES    50 // number of display lines in each draw buffer

#define DIRECT_MODE // Uncomment to enable full frame buffer

#ifdef DIRECT_MODE

//#define DIRECT_GFX

/* LVGL calls it when a rendered image needs to copied to the display*/
void my_disp_flush_direct(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
{

    #ifndef DIRECT_GFX
    int32_t disp_hres = lv_display_get_horizontal_resolution(disp);
    int32_t disp_vres = lv_display_get_vertical_resolution(disp);
    lv_color_format_t cf = lv_display_get_color_format(disp);
    uint32_t px_size = lv_color_format_get_size(cf);

    //Calculate the position of the rotated area
    lv_area_t rotated_area = *area;
    lv_display_rotate_area(disp, &rotated_area);

    //Calculate the source stride (bytes in a line) from the width of the area
    uint32_t src_stride = lv_draw_buf_width_to_stride(disp_hres, cf);

    //Calculate the stride of the destination (rotated) area too
    int32_t fb_stride = lv_draw_buf_width_to_stride(disp_hres, cf);

    uint8_t * fb_start = (uint8_t *)gfxdisplay->getFramebuffer();
    fb_start += rotated_area.y1 * fb_stride + rotated_area.x1 * px_size;

    px_map += area->y1 * src_stride + area->x1 * px_size;

    lv_display_rotation_t rotation = lv_display_get_rotation(disp);
    if(rotation == LV_DISPLAY_ROTATION_0) {
        // Direct copy !!
        int32_t y;
        for(y = area->y1; y <= area->y2; y++) {
            lv_memcpy(fb_start, px_map, src_stride);
            px_map += src_stride;
            fb_start += fb_stride;
        }
    }
    else
    {
      //Calculate the properties of the source buffer
      int32_t src_w = lv_area_get_width(area);
      int32_t src_h = lv_area_get_height(area);
      // Rotate
      lv_draw_sw_rotate(px_map, fb_start, src_w, src_h, src_stride, fb_stride, rotation, cf);
    }
    #endif
    if (lv_display_flush_is_last(disp))
    {
      gfxdisplay->flush();
    }
    lv_disp_flush_ready(disp);
}

void lv_screen_init(void * gfx, word W, word H)
{
  gfxdisplay = (Arduino_RGB_Display*) gfx;

  #ifdef DIRECT_GFX  
  static uint8_t * sbuf2_1 = (uint8_t *)gfxdisplay->getFramebuffer();
  static uint8_t * sbuf2_2 = NULL;
  #else
  static uint8_t * sbuf2_1 = (uint8_t *)heap_caps_aligned_alloc(4, W * H * BYTE_PER_PIXEL, MALLOC_CAP_SPIRAM);
  static uint8_t * sbuf2_2 = NULL;
  //sbuf2_2 = (uint8_t *)heap_caps_aligned_alloc(4, screenWidth * screenHeight * BYTE_PER_PIXEL, MALLOC_CAP_SPIRAM);
  #endif

  disp = lv_display_create(W, H);

  lv_display_set_flush_cb(disp, my_disp_flush_direct);
  lv_display_set_buffers(disp, sbuf2_1, sbuf2_2, W * H * BYTE_PER_PIXEL, LV_DISPLAY_RENDER_MODE_DIRECT);
  lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);
}

#else

/* LVGL calls it when a rendered image needs to copied to the display*/
void my_disp_flush_simple(lv_display_t *disp, const lv_area_t *area, uint8_t * px_map)
{
  uint32_t w = lv_area_get_width(area);
  uint32_t h = lv_area_get_height(area);

  uint16_t * buf16 = (uint16_t *)px_map; /* Let's say it's a 16 bit (RGB565) display */

  lv_display_rotation_t rotation = lv_display_get_rotation(disp);
  switch(rotation) {
      case LV_DISPLAY_ROTATION_0:
        gfxdisplay->setRotation(0);
        break;
      case LV_DISPLAY_ROTATION_90:
        gfxdisplay->setRotation(3);      
        break;
      case LV_DISPLAY_ROTATION_180:
        gfxdisplay->setRotation(2);      
        break;
      case LV_DISPLAY_ROTATION_270:
        gfxdisplay->setRotation(1);      
        break;
  }

#if (LV_COLOR_16_SWAP != 0)
  gfxdisplay->draw16bitBeRGBBitmap(area->x1, area->y1, buf16, w, h);
#else
  gfxdisplay->draw16bitRGBBitmap(area->x1, area->y1, buf16, w, h);
#endif

  if (lv_display_flush_is_last(disp))
  {
    gfxdisplay->flush();
  }

  /*Call it to tell LVGL you are ready*/
  lv_disp_flush_ready(disp);
}

void lv_screen_init(void * gfx, word W, word H)
{
  gfxdisplay = (Arduino_RGB_Display*) gfx;

  size_t draw_buffer_sz = (W * LVGL_DRAW_BUF_LINES * BYTE_PER_PIXEL);

  //static uint8_t * sbuf1_1 = (uint8_t *)heap_caps_aligned_alloc(4, draw_buffer_sz, MALLOC_CAP_8BIT | MALLOC_CAP_INTERNAL);
  static uint8_t * sbuf1_1 = (uint8_t *)heap_caps_malloc(draw_buffer_sz, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  static uint8_t * sbuf1_2 = NULL;

  disp = lv_display_create(W, H);
  lv_display_set_flush_cb(disp, my_disp_flush_simple);
  
  lv_display_set_buffers(disp, sbuf1_1, sbuf1_2, draw_buffer_sz, LV_DISP_RENDER_MODE_PARTIAL);
  lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);
}

#endif
