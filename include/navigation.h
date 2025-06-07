#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <lvgl.h>
#include "ui.h"
#include "config.h"

extern lv_group_t *groups[10];

void set_group();
void button_state(lv_obj_t *button, bool pressed);
void group_action(void *pvParameters);

#endif