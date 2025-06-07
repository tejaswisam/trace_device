#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>
#include "lvgl.h"
#include "ui.h"

// Display Dimensions
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 280
#define SCREENBUFFER_SIZE_PIXELS (SCREEN_WIDTH * SCREEN_HEIGHT / 20)

extern TFT_eSPI tft;
extern lv_color_t buf[SCREENBUFFER_SIZE_PIXELS];
extern lv_indev_t *encoder_indev;

void display_init();
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap);
uint32_t my_tick_get_cb();

#endif