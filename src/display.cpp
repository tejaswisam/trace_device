#include "display.h"
#include "encoder.h"

TFT_eSPI tft = TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT);
lv_color_t buf[SCREENBUFFER_SIZE_PIXELS];
lv_indev_t *encoder_indev = NULL;

void display_init() {
    lv_init();
    tft.begin();
    tft.setRotation(0);

    static lv_disp_t *disp;
    disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_display_set_buffers(disp, buf, NULL, SCREENBUFFER_SIZE_PIXELS * sizeof(lv_color_t), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(disp, my_disp_flush);

    encoder_indev = lv_indev_create();
    lv_indev_set_type(encoder_indev, LV_INDEV_TYPE_ENCODER);
    lv_indev_set_read_cb(encoder_indev, my_encoder_read);

    lv_tick_set_cb(my_tick_get_cb);

    ui_init();
}

void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)pixelmap, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

uint32_t my_tick_get_cb() {
    return millis();
}