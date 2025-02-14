/*******************************************************************************
 * Size: 32 px
 * Bpp: 4
 * Opts: --bpp 4 --size 32 --no-compress --font DSEG7Classic-BoldItalic.ttf --symbols 0123456789+-.:;ABCDEF --format lvgl -o lv_font_dseg7_32.c
 ******************************************************************************/

#include <lvgl.h>

#ifndef LV_FONT_DSEG7_32
#define LV_FONT_DSEG7_32 1
#endif

#if LV_FONT_DSEG7_32

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+002D "-" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x20,
    0x1c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1,
    0x1d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd1,
    0x2, 0xef, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x10,

    /* U+002E "." */
    0x0, 0x0, 0x0, 0xaf, 0xb0, 0x4f, 0xff, 0x74,
    0xff, 0xf7, 0x9, 0xfb, 0x0,

    /* U+0030 "0" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x0,
    0x0, 0x0, 0x49, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf6, 0x60, 0x0, 0x8, 0xf6, 0xbf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6e, 0xf1,
    0x0, 0xb, 0xff, 0x5c, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe6, 0xef, 0xf0, 0x0, 0xd, 0xff, 0xf1,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xe0,
    0x0, 0xe, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1f, 0xff, 0xd0, 0x0, 0xf, 0xff, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xc0,
    0x0, 0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xa0, 0x0, 0x2f, 0xff, 0xc0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x5f, 0xff, 0x90,
    0x0, 0x4f, 0xff, 0xa0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7f, 0xff, 0x80, 0x0, 0x5f, 0xff, 0x90,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8f, 0xff, 0x60,
    0x0, 0x6f, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x9f, 0xff, 0x50, 0x0, 0x8f, 0xff, 0x60,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xff, 0x30,
    0x0, 0x9f, 0xff, 0x30, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xbf, 0xff, 0x20, 0x0, 0xbf, 0xf5, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1d, 0xff, 0x10,
    0x0, 0x8b, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x2, 0xaa, 0x0, 0x0, 0x9a, 0x30, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xa9, 0x0,
    0x0, 0xff, 0xe2, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4f, 0xfc, 0x0, 0x0, 0xff, 0xfc, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2, 0xff, 0xfb, 0x0,
    0x2, 0xff, 0xfd, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x5, 0xff, 0xfa, 0x0, 0x3, 0xff, 0xfb, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x6, 0xff, 0xf8, 0x0,
    0x4, 0xff, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xff, 0xf7, 0x0, 0x6, 0xff, 0xf8, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9, 0xff, 0xf5, 0x0,
    0x7, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xa, 0xff, 0xf4, 0x0, 0x9, 0xff, 0xf6, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xc, 0xff, 0xf3, 0x0,
    0xa, 0xff, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xd, 0xff, 0xf1, 0x0, 0xb, 0xff, 0xf3, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf0, 0x0,
    0xd, 0xff, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xe, 0xff, 0xf0, 0x0, 0xe, 0xff, 0x7e, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xd4, 0xff, 0xd0, 0x0,
    0xf, 0xf6, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xfc, 0x5f, 0xa0, 0x0, 0x5, 0x6f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xb4, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xa0, 0x0, 0x0,

    /* U+0031 "1" */
    0x0, 0x0, 0x4, 0x90, 0x0, 0x0, 0x5f, 0xf1,
    0x0, 0x6, 0xff, 0xf0, 0x0, 0xf, 0xff, 0xe0,
    0x0, 0x2f, 0xff, 0xd0, 0x0, 0x3f, 0xff, 0xb0,
    0x0, 0x4f, 0xff, 0xa0, 0x0, 0x6f, 0xff, 0x90,
    0x0, 0x7f, 0xff, 0x70, 0x0, 0x8f, 0xff, 0x60,
    0x0, 0xaf, 0xff, 0x50, 0x0, 0xbf, 0xff, 0x30,
    0x0, 0x9f, 0xff, 0x20, 0x0, 0xc, 0xff, 0x0,
    0x0, 0x1, 0x77, 0x0, 0x0, 0x7, 0xfd, 0x0,
    0x0, 0x8f, 0xfc, 0x0, 0x3, 0xff, 0xfb, 0x0,
    0x5, 0xff, 0xf9, 0x0, 0x6, 0xff, 0xf8, 0x0,
    0x8, 0xff, 0xf7, 0x0, 0x9, 0xff, 0xf5, 0x0,
    0xa, 0xff, 0xf4, 0x0, 0xc, 0xff, 0xf2, 0x0,
    0xd, 0xff, 0xf1, 0x0, 0xf, 0xff, 0xf0, 0x0,
    0xd, 0xff, 0xe0, 0x0, 0x2, 0xef, 0xd0, 0x0,
    0x0, 0x3f, 0x90, 0x0, 0x0, 0x2, 0x0, 0x0,

    /* U+0032 "2" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x0,
    0x0, 0x0, 0x9, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf7, 0x60, 0x0, 0x0, 0x0, 0xbf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7e, 0xf1,
    0x0, 0x0, 0x0, 0xc, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe7, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xe0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xc0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xa0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x5f, 0xff, 0x90,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7f, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8f, 0xff, 0x60,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x9f, 0xff, 0x50, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xff, 0x30,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xbf, 0xff, 0x20, 0x0, 0x0, 0x0, 0xbf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x4d, 0xff, 0x10,
    0x0, 0x0, 0x1c, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe4, 0xaa, 0x0, 0x0, 0x9a, 0x4d, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xd1, 0x0, 0x0,
    0x0, 0xff, 0xe4, 0xef, 0xff, 0xff, 0xff, 0xff,
    0xfc, 0x10, 0x0, 0x0, 0x0, 0xff, 0xfc, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x2, 0xff, 0xfd, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x3, 0xff, 0xfb, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x4, 0xff, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x6, 0xff, 0xf8, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9, 0xff, 0xf6, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xa, 0xff, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xb, 0xff, 0xf3, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xd, 0xff, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0x7e, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xd1, 0x0, 0x0, 0x0,
    0xf, 0xf7, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xfc, 0x0, 0x0, 0x0, 0x5, 0x7f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xb0, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xa0, 0x0, 0x0,

    /* U+0033 "3" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x8, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf5, 0x0, 0x0, 0x9,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7,
    0x60, 0x0, 0x0, 0xbf, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x7e, 0xf1, 0x0, 0x0, 0xc, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xf0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf,
    0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xc0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x4f, 0xff, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x5f, 0xff, 0x90, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xff,
    0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x8f, 0xff, 0x60, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9f, 0xff, 0x50, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xbf,
    0xff, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xbf, 0xff, 0x20, 0x0, 0x0, 0xbf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x4d, 0xff, 0x10,
    0x0, 0x1c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xe4, 0xaa, 0x0, 0x0, 0x1d, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xd5, 0xa9, 0x0, 0x0, 0x2,
    0xef, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x5f, 0xfc,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x2, 0xff, 0xfb, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x5, 0xff, 0xfa, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0xff,
    0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9, 0xff, 0xf5, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa,
    0xff, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xc, 0xff, 0xf3, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xd, 0xff, 0xf1,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xe, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xe, 0xff, 0xf0, 0x0, 0x0,
    0x2e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd4, 0xff,
    0xd0, 0x0, 0x3, 0xef, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfc, 0x5f, 0xa0, 0x0, 0x3f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xb4, 0x0, 0x0,
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xa0, 0x0, 0x0,

    /* U+0034 "4" */
    0x1, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x2, 0x60, 0xa, 0xf9, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x3e, 0xf1, 0xc, 0xff,
    0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0xff,
    0xf0, 0xd, 0xff, 0xf1, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xf, 0xff, 0xe0, 0xe, 0xff, 0xf0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x1f, 0xff, 0xd0, 0xf,
    0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f,
    0xff, 0xc0, 0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x4f, 0xff, 0xa0, 0x2f, 0xff, 0xc0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x5f, 0xff, 0x90,
    0x4f, 0xff, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7f, 0xff, 0x70, 0x5f, 0xff, 0x90, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x8f, 0xff, 0x60, 0x7f, 0xff,
    0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9f, 0xff,
    0x50, 0x8f, 0xff, 0x60, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xbf, 0xff, 0x30, 0x9f, 0xff, 0x30, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xbf, 0xff, 0x20, 0xbf,
    0xf5, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x4d,
    0xff, 0x10, 0x8a, 0x5c, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xe4, 0xaa, 0x0, 0x0, 0x1d, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xd5, 0xa9, 0x0,
    0x0, 0x2, 0xef, 0xff, 0xff, 0xff, 0xff, 0xfc,
    0x5f, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x2, 0xff, 0xfb, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x5, 0xff, 0xfa,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x6, 0xff, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x7, 0xff, 0xf7, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0xff,
    0xf6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xa, 0xff, 0xf4, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xb, 0xff, 0xf3, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xd,
    0xff, 0xf2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xe, 0xff, 0xf0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x5, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x7f, 0xc0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7,
    0x10, 0x0,

    /* U+0035 "5" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x8, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xf5, 0x0, 0x49, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf4, 0x8, 0xf6,
    0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x30,
    0xb, 0xff, 0x5c, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xe3, 0x0, 0xd, 0xff, 0xf1, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff,
    0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x2f, 0xff, 0xc0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x4f, 0xff, 0xa0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5f, 0xff,
    0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x6f, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x8f, 0xff, 0x60, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9f, 0xff, 0x30, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xf5,
    0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x20, 0x0,
    0x8a, 0x5c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xe1, 0x0, 0x0, 0x1d, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xd5, 0xa9, 0x0, 0x2, 0xef, 0xff,
    0xff, 0xff, 0xff, 0xfc, 0x5f, 0xfc, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0xff, 0xfb,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5,
    0xff, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x6, 0xff, 0xf8, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x7, 0xff, 0xf7, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0xff, 0xf5,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa,
    0xff, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xc, 0xff, 0xf3, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xd, 0xff, 0xf1, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe,
    0xff, 0xf0, 0x0, 0x2e, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xd4, 0xff, 0xd0, 0x3, 0xef, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfc, 0x5f, 0xa0, 0x3f, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb4, 0x0,
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xa0, 0x0,

    /* U+0036 "6" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x0, 0x0,
    0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf4, 0x0, 0x8, 0xf6, 0xbf, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x30, 0x0, 0xb, 0xff, 0x5c,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x0, 0x0,
    0xd, 0xff, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xe, 0xff, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff,
    0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2f, 0xff, 0xc0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4f,
    0xff, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x5f, 0xff, 0x90, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x6f, 0xff, 0x80,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x8f, 0xff, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x9f, 0xff, 0x30, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xf5,
    0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x20, 0x0,
    0x0, 0x8a, 0x5c, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe1, 0x0, 0x0, 0x9a, 0x4d, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xd5, 0xa9, 0x0, 0xff,
    0xe4, 0xef, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x6f,
    0xfc, 0x0, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x2, 0xff, 0xfb, 0x2, 0xff, 0xfd, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x5, 0xff, 0xfa, 0x3,
    0xff, 0xfb, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6,
    0xff, 0xf8, 0x4, 0xff, 0xfa, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x7, 0xff, 0xf7, 0x6, 0xff, 0xf8,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0xff, 0xf5,
    0x7, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xa, 0xff, 0xf4, 0x9, 0xff, 0xf6, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xc, 0xff, 0xf3, 0xa, 0xff,
    0xf4, 0x0, 0x0, 0x0, 0x0, 0x0, 0xd, 0xff,
    0xf1, 0xb, 0xff, 0xf3, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xe, 0xff, 0xf0, 0xd, 0xff, 0xf1, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf0, 0xe,
    0xff, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd4,
    0xff, 0xd0, 0xf, 0xf7, 0xef, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xfc, 0x5f, 0xa0, 0x5, 0x7f, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb4, 0x0,
    0x0, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xa0, 0x0,

    /* U+0037 "7" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x8, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf5, 0x0, 0x0, 0x49,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf6,
    0x40, 0x8, 0xf6, 0xbf, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x5d, 0xf1, 0xb, 0xff, 0x5c, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe5, 0xef, 0xf0, 0xd,
    0xff, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe,
    0xff, 0xf0, 0xe, 0xff, 0xf0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x1f, 0xff, 0xd0, 0xf, 0xff, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xff, 0xc0,
    0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x4f, 0xff, 0xa0, 0x2f, 0xff, 0xc0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x5f, 0xff, 0x90, 0x4f, 0xff,
    0xb0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xff,
    0x80, 0x5f, 0xff, 0x90, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x8f, 0xff, 0x60, 0x6f, 0xff, 0x80, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9f, 0xff, 0x50, 0x8f,
    0xff, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0xbf,
    0xff, 0x40, 0x9f, 0xff, 0x40, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xbf, 0xff, 0x20, 0xaf, 0xf7, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x2e, 0xff, 0x10,
    0xad, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x3, 0xdd, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1, 0x77, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2e, 0xfd,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1, 0xef, 0xfb, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x4, 0xff, 0xfa, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0xff,
    0xf9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x8, 0xff, 0xf6, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa,
    0xff, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xb, 0xff, 0xf3, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xd, 0xff, 0xf2,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xe, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xf, 0xff, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xff,
    0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x9f, 0xc0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0x30, 0x0,

    /* U+0038 "8" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x0,
    0x0, 0x0, 0x49, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf7, 0x60, 0x0, 0x8, 0xf6, 0xbf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7e, 0xf1,
    0x0, 0xb, 0xff, 0x5c, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe7, 0xff, 0xf0, 0x0, 0xd, 0xff, 0xf1,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xe0,
    0x0, 0xe, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1f, 0xff, 0xd0, 0x0, 0xf, 0xff, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xc0,
    0x0, 0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xa0, 0x0, 0x2f, 0xff, 0xc0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x5f, 0xff, 0x90,
    0x0, 0x4f, 0xff, 0xa0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7f, 0xff, 0x80, 0x0, 0x5f, 0xff, 0x90,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8f, 0xff, 0x60,
    0x0, 0x6f, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x9f, 0xff, 0x50, 0x0, 0x8f, 0xff, 0x60,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xff, 0x30,
    0x0, 0x9f, 0xff, 0x30, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xbf, 0xff, 0x20, 0x0, 0xbf, 0xf5, 0xbf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x4d, 0xff, 0x10,
    0x0, 0x8a, 0x5c, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe4, 0xaa, 0x0, 0x0, 0x9a, 0x4d, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xd5, 0xa9, 0x0,
    0x0, 0xff, 0xe4, 0xef, 0xff, 0xff, 0xff, 0xff,
    0xfc, 0x6f, 0xfc, 0x0, 0x0, 0xff, 0xfc, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2, 0xff, 0xfb, 0x0,
    0x2, 0xff, 0xfd, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x5, 0xff, 0xfa, 0x0, 0x3, 0xff, 0xfb, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x6, 0xff, 0xf8, 0x0,
    0x4, 0xff, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xff, 0xf7, 0x0, 0x6, 0xff, 0xf8, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9, 0xff, 0xf5, 0x0,
    0x7, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xa, 0xff, 0xf4, 0x0, 0x9, 0xff, 0xf6, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xc, 0xff, 0xf3, 0x0,
    0xa, 0xff, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xd, 0xff, 0xf1, 0x0, 0xb, 0xff, 0xf3, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf0, 0x0,
    0xd, 0xff, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xe, 0xff, 0xf0, 0x0, 0xe, 0xff, 0x7e, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xd4, 0xff, 0xd0, 0x0,
    0xf, 0xf7, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xfc, 0x5f, 0xa0, 0x0, 0x5, 0x7f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xb4, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xa0, 0x0, 0x0,

    /* U+0039 "9" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x8, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf5, 0x0, 0x0, 0x49,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7,
    0x60, 0x8, 0xf6, 0xbf, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x7e, 0xf1, 0xb, 0xff, 0x5c, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xf0, 0xd,
    0xff, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf,
    0xff, 0xe0, 0xe, 0xff, 0xf0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x1f, 0xff, 0xd0, 0xf, 0xff, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xc0,
    0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x4f, 0xff, 0xa0, 0x2f, 0xff, 0xc0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x5f, 0xff, 0x90, 0x4f, 0xff,
    0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xff,
    0x80, 0x5f, 0xff, 0x90, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x8f, 0xff, 0x60, 0x6f, 0xff, 0x80, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9f, 0xff, 0x50, 0x8f,
    0xff, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0xbf,
    0xff, 0x30, 0x9f, 0xff, 0x30, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xbf, 0xff, 0x20, 0xbf, 0xf5, 0xbf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x4d, 0xff, 0x10,
    0x8a, 0x5c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xe4, 0xaa, 0x0, 0x0, 0x1d, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xd5, 0xa9, 0x0, 0x0, 0x2,
    0xef, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x5f, 0xfc,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x2, 0xff, 0xfb, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x5, 0xff, 0xfa, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0xff,
    0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9, 0xff, 0xf5, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa,
    0xff, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xc, 0xff, 0xf3, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xd, 0xff, 0xf1,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xe, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xe, 0xff, 0xf0, 0x0, 0x0,
    0x2e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd4, 0xff,
    0xd0, 0x0, 0x3, 0xef, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfc, 0x5f, 0xa0, 0x0, 0x3f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xb4, 0x0, 0x0,
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xa0, 0x0, 0x0,

    /* U+003A ":" */
    0x0, 0x7f, 0xd2, 0x1, 0xff, 0xfa, 0x1, 0xff,
    0xfa, 0x0, 0x7e, 0xc2, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9,
    0xfb, 0x10, 0x4f, 0xff, 0x80, 0x3f, 0xff, 0x70,
    0x9, 0xfb, 0x10,

    /* U+0041 "A" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x0,
    0x0, 0x0, 0x49, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf7, 0x60, 0x0, 0x8, 0xf6, 0xbf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7e, 0xf1,
    0x0, 0xb, 0xff, 0x5c, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe7, 0xff, 0xf0, 0x0, 0xd, 0xff, 0xf1,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xe0,
    0x0, 0xe, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1f, 0xff, 0xd0, 0x0, 0xf, 0xff, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xc0,
    0x0, 0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xa0, 0x0, 0x2f, 0xff, 0xc0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x5f, 0xff, 0x90,
    0x0, 0x4f, 0xff, 0xa0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7f, 0xff, 0x80, 0x0, 0x5f, 0xff, 0x90,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8f, 0xff, 0x60,
    0x0, 0x6f, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x9f, 0xff, 0x50, 0x0, 0x8f, 0xff, 0x60,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xff, 0x30,
    0x0, 0x9f, 0xff, 0x30, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xbf, 0xff, 0x20, 0x0, 0xbf, 0xf5, 0xbf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x4d, 0xff, 0x10,
    0x0, 0x8a, 0x5c, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe4, 0xaa, 0x0, 0x0, 0x9a, 0x4d, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xd5, 0xa9, 0x0,
    0x0, 0xff, 0xe4, 0xef, 0xff, 0xff, 0xff, 0xff,
    0xfc, 0x5f, 0xfc, 0x0, 0x0, 0xff, 0xfc, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2, 0xff, 0xfb, 0x0,
    0x2, 0xff, 0xfd, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x5, 0xff, 0xfa, 0x0, 0x3, 0xff, 0xfb, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x6, 0xff, 0xf8, 0x0,
    0x4, 0xff, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xff, 0xf7, 0x0, 0x6, 0xff, 0xf8, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9, 0xff, 0xf6, 0x0,
    0x7, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xa, 0xff, 0xf4, 0x0, 0x9, 0xff, 0xf6, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xb, 0xff, 0xf3, 0x0,
    0xa, 0xff, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xd, 0xff, 0xf2, 0x0, 0xb, 0xff, 0xf3, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf0, 0x0,
    0xd, 0xff, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xf, 0xff, 0xf0, 0x0, 0xe, 0xff, 0x50, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x5, 0xff, 0xd0, 0x0,
    0xf, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7f, 0xc0, 0x0, 0x5, 0x30, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x10, 0x0,

    /* U+0042 "B" */
    0x0, 0x1, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xa, 0xf9, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc,
    0xff, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xd, 0xff, 0xf1, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xf, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1f, 0xff, 0xd0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xff,
    0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xa0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x5f, 0xff, 0x90, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f,
    0xff, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x8f, 0xff, 0x60, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x9f, 0xff, 0x30,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xbf, 0xf5, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x20, 0x0, 0x0, 0x8a, 0x5c, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xe1, 0x0, 0x0, 0x9a, 0x4d,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd5, 0xa9,
    0x0, 0xff, 0xe4, 0xef, 0xff, 0xff, 0xff, 0xff,
    0xfc, 0x6f, 0xfc, 0x0, 0xff, 0xfc, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x2, 0xff, 0xfb, 0x2, 0xff,
    0xfd, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5, 0xff,
    0xfa, 0x3, 0xff, 0xfb, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x6, 0xff, 0xf8, 0x4, 0xff, 0xfa, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x7, 0xff, 0xf7, 0x6,
    0xff, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9,
    0xff, 0xf5, 0x7, 0xff, 0xf7, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xa, 0xff, 0xf4, 0x9, 0xff, 0xf6,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0xff, 0xf3,
    0xa, 0xff, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xd, 0xff, 0xf1, 0xb, 0xff, 0xf3, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xe, 0xff, 0xf0, 0xd, 0xff,
    0xf1, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0xff,
    0xf0, 0xe, 0xff, 0x7e, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xd4, 0xff, 0xd0, 0xf, 0xf7, 0xef, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfc, 0x5f, 0xa0, 0x5,
    0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xb4, 0x0, 0x0, 0x4f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xa0, 0x0,

    /* U+0043 "C" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x20, 0x0, 0x0, 0x1c, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0x0, 0x9a,
    0x4d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd1,
    0x0, 0xff, 0xe4, 0xef, 0xff, 0xff, 0xff, 0xff,
    0xfc, 0x10, 0x0, 0xff, 0xfc, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2, 0xff, 0xfd, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xff,
    0xfb, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x4, 0xff, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x6, 0xff, 0xf8, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x7, 0xff, 0xf7, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0xff,
    0xf6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xa, 0xff, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xb, 0xff, 0xf3, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xd, 0xff, 0xf1, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0xff,
    0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd1, 0x0,
    0xf, 0xf7, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xfc, 0x0, 0x5, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xb0, 0x0, 0x4f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xa0,

    /* U+0044 "D" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x2, 0x60, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3e, 0xf1,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xe0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xc0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xa0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x5f, 0xff, 0x90,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7f, 0xff, 0x70, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8f, 0xff, 0x60,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x9f, 0xff, 0x50, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xff, 0x30,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xbf, 0xff, 0x20, 0x0, 0x0, 0x0, 0xbf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x4d, 0xff, 0x10,
    0x0, 0x0, 0x1c, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe4, 0xaa, 0x0, 0x0, 0x9a, 0x4d, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xd5, 0xa9, 0x0,
    0x0, 0xff, 0xe4, 0xef, 0xff, 0xff, 0xff, 0xff,
    0xfc, 0x6f, 0xfc, 0x0, 0x0, 0xff, 0xfc, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2, 0xff, 0xfb, 0x0,
    0x2, 0xff, 0xfd, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x5, 0xff, 0xfa, 0x0, 0x3, 0xff, 0xfb, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x6, 0xff, 0xf8, 0x0,
    0x4, 0xff, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xff, 0xf7, 0x0, 0x6, 0xff, 0xf8, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9, 0xff, 0xf5, 0x0,
    0x7, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xa, 0xff, 0xf4, 0x0, 0x9, 0xff, 0xf6, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xc, 0xff, 0xf3, 0x0,
    0xa, 0xff, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xd, 0xff, 0xf1, 0x0, 0xb, 0xff, 0xf3, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf0, 0x0,
    0xd, 0xff, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xe, 0xff, 0xf0, 0x0, 0xe, 0xff, 0x7e, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xd4, 0xff, 0xd0, 0x0,
    0xf, 0xf7, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xfc, 0x5f, 0xa0, 0x0, 0x5, 0x7f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xb4, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xa0, 0x0, 0x0,

    /* U+0045 "E" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x0, 0x0,
    0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf4, 0x0, 0x8, 0xf6, 0xbf, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x30, 0x0, 0xb, 0xff, 0x5c,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x0, 0x0,
    0xd, 0xff, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xe, 0xff, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff,
    0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2f, 0xff, 0xc0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4f,
    0xff, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x5f, 0xff, 0x90, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x6f, 0xff, 0x80,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x8f, 0xff, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x9f, 0xff, 0x30, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xf5,
    0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x20, 0x0,
    0x0, 0x8a, 0x5c, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe1, 0x0, 0x0, 0x9a, 0x4d, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xd1, 0x0, 0x0, 0xff,
    0xe4, 0xef, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x10,
    0x0, 0x0, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2, 0xff, 0xfd, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3,
    0xff, 0xfb, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x4, 0xff, 0xfa, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0xff, 0xf8,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x9, 0xff, 0xf6, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa, 0xff,
    0xf4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xb, 0xff, 0xf3, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xd, 0xff, 0xf1, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe,
    0xff, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd1,
    0x0, 0x0, 0xf, 0xf7, 0xef, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xfc, 0x0, 0x0, 0x5, 0x7f, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb0, 0x0,
    0x0, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xa0, 0x0,

    /* U+0046 "F" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x0, 0x0,
    0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf4, 0x0, 0x8, 0xf6, 0xbf, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x30, 0x0, 0xb, 0xff, 0x5c,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x0, 0x0,
    0xd, 0xff, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xe, 0xff, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff,
    0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1f, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2f, 0xff, 0xc0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4f,
    0xff, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x5f, 0xff, 0x90, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x6f, 0xff, 0x80,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x8f, 0xff, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x9f, 0xff, 0x30, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xf5,
    0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x20, 0x0,
    0x0, 0x8a, 0x5c, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe1, 0x0, 0x0, 0x9a, 0x4d, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xd1, 0x0, 0x0, 0xff,
    0xe4, 0xef, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x10,
    0x0, 0x0, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2, 0xff, 0xfd, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3,
    0xff, 0xfb, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x4, 0xff, 0xfa, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0xff, 0xf8,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x9, 0xff, 0xf6, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa, 0xff,
    0xf4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xb, 0xff, 0xf3, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xd, 0xff, 0xf1, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe,
    0xff, 0x50, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xf, 0xf4, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x5, 0x30, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 418, .box_w = 16, .box_h = 5, .ofs_x = 5, .ofs_y = 14},
    {.bitmap_index = 40, .adv_w = 0, .box_w = 5, .box_h = 5, .ofs_x = -4, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 418, .box_w = 24, .box_h = 33, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 418, .box_w = 8, .box_h = 30, .ofs_x = 17, .ofs_y = 1},
    {.bitmap_index = 569, .adv_w = 418, .box_w = 24, .box_h = 33, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 965, .adv_w = 418, .box_w = 22, .box_h = 33, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 1328, .adv_w = 418, .box_w = 22, .box_h = 30, .ofs_x = 3, .ofs_y = 1},
    {.bitmap_index = 1658, .adv_w = 418, .box_w = 20, .box_h = 33, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 1988, .adv_w = 418, .box_w = 22, .box_h = 33, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2351, .adv_w = 418, .box_w = 22, .box_h = 32, .ofs_x = 3, .ofs_y = 1},
    {.bitmap_index = 2703, .adv_w = 418, .box_w = 24, .box_h = 33, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3099, .adv_w = 418, .box_w = 22, .box_h = 33, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 3462, .adv_w = 102, .box_w = 6, .box_h = 17, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 3513, .adv_w = 418, .box_w = 24, .box_h = 32, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 3897, .adv_w = 418, .box_w = 22, .box_h = 31, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4238, .adv_w = 418, .box_w = 20, .box_h = 19, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4428, .adv_w = 418, .box_w = 24, .box_h = 31, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4800, .adv_w = 418, .box_w = 22, .box_h = 33, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 5163, .adv_w = 418, .box_w = 22, .box_h = 32, .ofs_x = 1, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_0[] = {
    0, 1, 0, 2, 3, 4, 5, 6,
    7, 8, 9, 10, 11, 12, 0, 0,
    0, 0, 0, 0, 13, 14, 15, 16,
    17, 18
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 45, .range_length = 26, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_0, .list_length = 26, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t lv_font_dseg7_32 = {
#else
lv_font_t lv_font_dseg7_32 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 33,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if LV_FONT_DSEG7_32*/

