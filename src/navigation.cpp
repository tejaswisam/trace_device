#include "navigation.h"
#include "sensors.h"
#include "display.h" // Added to access encoder_indev
#include "encoder.h" // Added to access rotaryEncoder

lv_group_t *groups[10];

void set_group() {
    for (int i = 0; i < 10; i++) {
        groups[i] = lv_group_create();
    }

    // Home Screen
    lv_group_add_obj(groups[0], ui_Image6); // Measure
    lv_group_add_obj(groups[0], ui_Image7); // Align
    lv_group_add_obj(groups[0], ui_Image8); // Draft
    lv_group_add_obj(groups[0], ui_Image9); // Settings

    // Measure Screen
    lv_group_add_obj(groups[1], ui_Image10); // Back
    lv_group_add_obj(groups[1], ui_Panel1); // Laser Ranging
    lv_group_add_obj(groups[1], ui_Panel2); // Roll Sensor

    // Align Screen
    lv_group_add_obj(groups[2], ui_Image15);
    lv_group_add_obj(groups[2], ui_Panel5); // Orientation
    lv_group_add_obj(groups[2], ui_Panel6); // Compass

    // Draft Screen
    lv_group_add_obj(groups[3], ui_Image2);
    lv_group_add_obj(groups[3], ui_Panel11);

    // Settings Screen
    lv_group_add_obj(groups[4], ui_Image27);
    lv_group_add_obj(groups[4], ui_Panel7);
    lv_group_add_obj(groups[4], ui_Switch1);
    lv_group_add_obj(groups[4], ui_Panel8);
    lv_group_add_obj(groups[4], ui_Panel23);

    // Distance Screen
    lv_group_add_obj(groups[5], ui_Image1);
    lv_group_add_obj(groups[5], ui_Image20);

    // Orientation Screen
    lv_group_add_obj(groups[6], ui_Image19);

    // Compass Screen
    lv_group_add_obj(groups[7], ui_Image23);

    // About Screen
    lv_group_add_obj(groups[8], ui_Image31);

    // Calibration Screen
    lv_group_add_obj(groups[9], ui_CalBack);

    lv_group_set_default(groups[0]);
    lv_indev_set_group(encoder_indev, groups[0]);
}

void button_state(lv_obj_t *button, bool pressed) {
    if (pressed) {
        lv_obj_send_event(button, LV_EVENT_PRESSED, NULL);
        lv_obj_clear_state(button, LV_STATE_PRESSED);
        lv_obj_add_state(button, LV_STATE_DEFAULT);
    }
}

void group_action(void *pvParameters) {
    while (1) {
        lv_obj_t *focused_obj = lv_group_get_focused(groups[current_screen]);
        lv_indev_set_group(encoder_indev, groups[current_screen]);

        if (rotaryEncoder.isEncoderButtonClicked()) {
            button_state(focused_obj, true);
            int prev_screen = current_screen;

            if (current_screen == 0) {
                if (focused_obj == ui_Image6) current_screen = 1;
                else if (focused_obj == ui_Image7) current_screen = 2;
                else if (focused_obj == ui_Image8) current_screen = 3;
                else if (focused_obj == ui_Image9) current_screen = 4;
            } else if (current_screen == 1) {
                if (focused_obj == ui_Image10) current_screen = 0;
                else if (focused_obj == ui_Panel1) {
                    current_screen = 5;
                    distanceInputSource = INPUT_TOF;
                    // startToFReading(2000); // Start non-blocking ToF reading for 3 seconds
                    lv_dropdown_set_options(ui_Dropdown1,"m");
                    Serial.println("Laser Ranging pressed, ToF reading started");
                } else if (focused_obj == ui_Panel2) {
                    stopVL53L1X();
                    current_screen = 5;
                    distanceInputSource = INPUT_ENCODER;
                    lv_dropdown_set_options(ui_Dropdown1,"mm");
                    Serial.println("Roll Sensor pressed, switching to encoder");
                }
            } else if (current_screen == 2) {
                if (focused_obj == ui_Image15) current_screen = 0;
                else if (focused_obj == ui_Panel5) current_screen = 6;
                else if (focused_obj == ui_Panel6) current_screen = 7;
            } else if (current_screen == 3) {
                if (focused_obj == ui_Image2) current_screen = 0;
            } else if (current_screen == 4) {
                if (focused_obj == ui_Image27) current_screen = 0;
                else if (focused_obj == ui_Panel8) current_screen = 9;
                else if (focused_obj == ui_Panel23) current_screen = 8;
            } else if (current_screen == 5) {
                if (focused_obj == ui_Image1){
                    current_screen = 1;
                    updateActiveSensors();
                }
                else if (focused_obj == ui_Image20) {
                    if (distanceInputSource == INPUT_TOF) {
                        startToFReading(2000); // Restart 3-second ToF reading
                        lv_dropdown_set_options(ui_Dropdown1,"m");
                        Serial.println("Reset button pressed, restarting ToF reading");
                    } else if (distanceInputSource == INPUT_ENCODER) {
                        resetAS5600LinearDistance(); // Reset AS5600 linear distance
                        lv_dropdown_set_options(ui_Dropdown1,"mm");
                        Serial.println("Reset button pressed, AS5600 distance reset");
                    }
                }
            } else if (current_screen == 6) {
                if (focused_obj == ui_Image19) current_screen = 2;
            } else if (current_screen == 7) {
                if (focused_obj == ui_Image23) current_screen = 2;
            } else if (current_screen == 8) {
                if (focused_obj == ui_Image31) current_screen = 4;
            } else if (current_screen == 9) {
                if (focused_obj == ui_CalBack) current_screen = 4;
            }

            if (prev_screen != current_screen) {
                updateActiveSensors();
                Serial.print("Switched to screen: ");
                Serial.println(current_screen);
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}