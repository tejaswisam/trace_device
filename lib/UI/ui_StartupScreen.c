// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.1
// LVGL version: 9.1.0
// Project name: CMD_ESP_UI

#include "ui.h"

void ui_StartupScreen_screen_init(void)
{
    ui_StartupScreen = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_StartupScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_StartupScreen, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_StartupScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StartupScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Bar2 = lv_bar_create(ui_StartupScreen);
    lv_bar_set_value(ui_Bar2, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_Bar2, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Bar2, 159);
    lv_obj_set_height(ui_Bar2, 6);
    lv_obj_set_x(ui_Bar2, 0);
    lv_obj_set_y(ui_Bar2, -87);
    lv_obj_set_align(ui_Bar2, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_bg_color(ui_Bar2, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Bar2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Bar2, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Bar2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    //Compensating for LVGL9.1 draw crash with bar/slider max value when top-padding is nonzero and right-padding is 0
    if(lv_obj_get_style_pad_top(ui_Bar2, LV_PART_MAIN) > 0) lv_obj_set_style_pad_right(ui_Bar2,
                                                                                           lv_obj_get_style_pad_right(ui_Bar2, LV_PART_MAIN) + 1, LV_PART_MAIN);
    ui_Image4 = lv_image_create(ui_StartupScreen);
    lv_image_set_src(ui_Image4, &ui_img_265045193);
    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);   /// 134
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);    /// 29
    lv_obj_set_x(ui_Image4, 0);
    lv_obj_set_y(ui_Image4, -10);
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

}
