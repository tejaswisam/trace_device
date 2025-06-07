#include "encoder.h"

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

void encoder_init() {
    pinMode(ROTARY_ENCODER_BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_BUTTON_PIN), rotary_onButtonClick, FALLING);
    rotaryEncoder.begin();
    rotaryEncoder.setup(readEncoderISR);
    rotaryEncoder.setBoundaries(0, 1000, false);
    rotaryEncoder.disableAcceleration();
}

void rotary_onButtonClick() {
    static unsigned long lastTimePressed = 0;
    if (millis() - lastTimePressed < 30) {
        return;
    }
    lastTimePressed = millis();
    Serial.print("button pressed ");
    Serial.print(millis());
    Serial.println(" milliseconds after restart");
}

void rotary_loop() {
    if (rotaryEncoder.encoderChanged()) {
        Serial.print("Value: ");
        Serial.println(rotaryEncoder.readEncoder());
    }
    if (rotaryEncoder.isEncoderButtonClicked()) {
        rotary_onButtonClick();
    }
}

void IRAM_ATTR readEncoderISR() {
    rotaryEncoder.readEncoder_ISR();
}

void my_encoder_read(lv_indev_t *indev, lv_indev_data_t *data) {
    static int32_t last_counter = 0;
    int32_t counter = rotaryEncoder.readEncoder();
    bool btn_state = rotaryEncoder.isEncoderButtonClicked();
    data->key = LV_KEY_ENTER;
    data->enc_diff = counter - last_counter;
    data->state = btn_state ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
    last_counter = counter;
}