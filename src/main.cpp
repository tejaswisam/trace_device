#include <esp_wifi.h>
#include <esp_netif.h>
#include "config.h"
#include "display.h"
#include "sensors.h"
#include "encoder.h"
#include "navigation.h"

int current_screen = 0;
TaskHandle_t Task1;

void setup() {

    Serial.begin(115200);
    Wire.begin(I2C_SDA, I2C_SCL);

    // Initialize haptic pin as digital output
    pinMode(hapticPin, OUTPUT);
    digitalWrite(hapticPin, LOW); // Ensure haptic is off initially

    // Initialize buzzer pin
    pinMode(buzzerPin, OUTPUT);
    noTone(buzzerPin); // Ensure buzzer is off initially

    digitalWrite(hapticPin, HIGH);
    delay(200);
    digitalWrite(hapticPin, LOW);
    delay(300);
    digitalWrite(hapticPin, HIGH);
    delay(200);
    digitalWrite(hapticPin, LOW);
    Serial.println("Haptic feedback activated (two pulses)");

    tone(buzzerPin, 500, 100);
    delay(150); // Wait for tone (100ms) + 50ms pause
    tone(buzzerPin, 800, 100);
    delay(150); // Wait for tone + pause
    tone(buzzerPin, 1200, 200);
    delay(150); // Wait for tone to complete
    noTone(25); // Ensure buzzer is off
    Serial.println("Startup tone played");

    display_init();
    encoder_init();
    sensors_init();
    set_group();

    Serial.println("Setup done");

    lv_scr_load(ui_StartupScreen);

    if (ui_Bar2) {
        lv_bar_set_range(ui_Bar2, 0, 100);
        for (int value = 0; value <= 100; value++) {
            lv_bar_set_value(ui_Bar2, value, LV_ANIM_ON);
            lv_task_handler();
            delay(30);
        }
    } else {
        Serial.println("ERROR: ui_Bar2 is NULL!");
    }

    Serial.println("Switching to Home Screen...");
    lv_scr_load(ui_HomeScreen);
    // Increased stack size to 16384 to handle UI and sensor tasks
    xTaskCreatePinnedToCore(group_action, "GroupTask", 16384, NULL, 4, &Task1, 1);
}

void loop() {
    static unsigned long lastSensorRead = 0;
    const unsigned long sensorReadInterval = 100;

    rotary_loop();
    lv_timer_handler();

    if (millis() - lastSensorRead >= sensorReadInterval) {
        // Update ToF readings if active (handles live and average UI updates for INPUT_TOF)
        updateToFReading();

        // Handle Distance Screen (screen 5)
        if (current_screen == 5 && distanceInputSource == INPUT_ENCODER) {
            // Update encoder (AS5600) distance
            char buffer[16];
            float distance = getLinearDistanceFromAS5600();
            if (distance >= 0) {
                snprintf(buffer, sizeof(buffer), "%.1f", distance);
                _ui_label_set_property(ui_Label11, _UI_LABEL_PROPERTY_TEXT, buffer);
                float distance_inch = distance / 25.4;
                int feet = int(distance_inch) / 12;
                int inches = int(distance_inch) % 12;
                snprintf(buffer, sizeof(buffer), "%d ft %d in", feet, inches);
                _ui_label_set_property(ui_Label51, _UI_LABEL_PROPERTY_TEXT, buffer);
            } else {
                _ui_label_set_property(ui_Label11, _UI_LABEL_PROPERTY_TEXT, "Error");
                _ui_label_set_property(ui_Label51, _UI_LABEL_PROPERTY_TEXT, "Error");
            }
        }

        // Handle other screens
        if (current_screen != 5) {
            if (isBNO055Active) {
                updateCompass();
                sensors_event_t gravity;
                bno.getEvent(&gravity, Adafruit_BNO055::VECTOR_GRAVITY);
                float ax = gravity.acceleration.x;
                float ay = gravity.acceleration.y;
                float angle = atan2(ay, ax) * 180.0 / PI;
                if (angle < 0) angle += 360;
                lv_img_set_angle(ui_Image21, (int)(angle * 10));
                char buffer[16];
                snprintf(buffer, sizeof(buffer), "%d\u00B0", (int)angle);
                _ui_label_set_property(ui_Label22, _UI_LABEL_PROPERTY_TEXT, "Angle");
                _ui_label_set_property(ui_Label23, _UI_LABEL_PROPERTY_TEXT, buffer);
            }

            if (isAS5600Active) {
                Serial.print("AS5600 Angle: ");
                Serial.println(magen.rawAngle());
            }
        }

        lastSensorRead = millis();
    }

    delay(5);
}