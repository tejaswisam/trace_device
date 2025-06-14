// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.1
// LVGL version: 9.1.0
// Project name: CMD_ESP_UI

#include "ui.h"

void ui_MeasureScreen_screen_init(void)
{
    ui_MeasureScreen = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_MeasureScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_MeasureScreen, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MeasureScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MeasureScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image10 = lv_image_create(ui_MeasureScreen);
    lv_image_set_src(ui_Image10, &ui_img_arrow_back_png);
    lv_obj_set_width(ui_Image10, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image10, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image10, 28);
    lv_obj_set_y(ui_Image10, 12);
    lv_obj_add_flag(ui_Image10, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_remove_flag(ui_Image10, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Image10, 12, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui_Image10, lv_color_hex(0x706767), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_Image10, 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_Label5 = lv_label_create(ui_MeasureScreen);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label5, 4);
    lv_obj_set_y(ui_Label5, -116);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "Measure");
    lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label5, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel1 = lv_obj_create(ui_MeasureScreen);
    lv_obj_set_width(ui_Panel1, 216);
    lv_obj_set_height(ui_Panel1, 67);
    lv_obj_set_x(ui_Panel1, 1);
    lv_obj_set_y(ui_Panel1, -54);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel1, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x222020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_Panel1, 14, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x4A4A4A), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_color(ui_Panel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_Image11 = lv_image_create(ui_Panel1);
    lv_image_set_src(ui_Image11, &ui_img_group_21_png);
    lv_obj_set_width(ui_Image11, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image11, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image11, -5);
    lv_obj_set_y(ui_Image11, 0);
    lv_obj_set_align(ui_Image11, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_Image11, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_remove_flag(ui_Image11, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label6 = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label6, 26);
    lv_obj_set_y(ui_Label6, 0);
    lv_obj_set_align(ui_Label6, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label6, "Laser Ranging");
    lv_obj_set_style_text_color(ui_Label6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label6, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label7 = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label7, 21);
    lv_obj_set_y(ui_Label7, 2);
    lv_obj_set_align(ui_Label7, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label7, "for longer distances");
    lv_obj_set_style_text_color(ui_Label7, lv_color_hex(0x867B7B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label7, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel2 = lv_obj_create(ui_MeasureScreen);
    lv_obj_set_width(ui_Panel2, 216);
    lv_obj_set_height(ui_Panel2, 67);
    lv_obj_set_x(ui_Panel2, 0);
    lv_obj_set_y(ui_Panel2, 28);
    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel2, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x222020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_Panel2, 14, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x4A4A4A), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_Image12 = lv_image_create(ui_Panel2);
    lv_image_set_src(ui_Image12, &ui_img_group_22_png);
    lv_obj_set_width(ui_Image12, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image12, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image12, -4);
    lv_obj_set_y(ui_Image12, 0);
    lv_obj_set_align(ui_Image12, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_Image12, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_remove_flag(ui_Image12, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label8 = lv_label_create(ui_Panel2);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label8, 14);
    lv_obj_set_y(ui_Label8, 0);
    lv_obj_set_align(ui_Label8, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label8, "Roll Sensor");
    lv_obj_set_style_text_color(ui_Label8, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label8, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label9 = lv_label_create(ui_Panel2);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label9, 27);
    lv_obj_set_y(ui_Label9, 0);
    lv_obj_set_align(ui_Label9, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label9, "for shorter distances");
    lv_obj_set_style_text_color(ui_Label9, lv_color_hex(0x867B7B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label9, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image14 = lv_image_create(ui_MeasureScreen);
    lv_image_set_src(ui_Image14, &ui_img_265046220);
    lv_obj_set_width(ui_Image14, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image14, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image14, 0);
    lv_obj_set_y(ui_Image14, -24);
    lv_obj_set_align(ui_Image14, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_Image14, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_remove_flag(ui_Image14, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_Image10, ui_event_Image10, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Panel1, ui_event_Panel1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Panel2, ui_event_Panel2, LV_EVENT_ALL, NULL);

}
