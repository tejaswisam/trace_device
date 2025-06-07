#ifndef ENCODER_H
#define ENCODER_H

#include <AiEsp32RotaryEncoder.h>
#include <lvgl.h> // Added for lv_indev_t and lv_indev_data_t

// Rotary Encoder Pins
#define ROTARY_ENCODER_A_PIN 19
#define ROTARY_ENCODER_B_PIN 22
#define ROTARY_ENCODER_BUTTON_PIN 21
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4

extern AiEsp32RotaryEncoder rotaryEncoder;

void encoder_init();
void rotary_onButtonClick();
void rotary_loop();
void readEncoderISR();
void my_encoder_read(lv_indev_t *indev, lv_indev_data_t *data);

#endif