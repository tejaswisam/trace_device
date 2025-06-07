#include "sensors.h"
#include <lvgl.h> // Added for lv_img_set_angle
#include "ui.h"   // Added for ui_Image26, ui_Label25, _ui_label_set_property
#include "config.h"

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
VL53L1X tof;
AS5600 magen;
bool isVL53L1XActive = false;
bool isBNO055Active = false;
bool isAS5600Active = false;
float headingOffset = 0;
DistanceInputSource distanceInputSource = INPUT_TOF; // Default to ToF

// Variables for non-blocking ToF reading
ToFReadingState tofReadingState = TOF_IDLE;
unsigned long tofStartTime = 0;
uint32_t tofDuration = 0;
float tofSum = 0.0;
int tofCount = 0;

// Variables for tracking AS5600 linear distance
static int16_t lastRawAngle = -1; // Store last raw angle, -1 indicates uninitialized
static float totalLinearDistance = 0.0; // Cumulative linear distance in mm

void sensors_init() {
    // Sensors are initialized on-demand by updateActiveSensors()
}

void startVL53L1X() {
    if (!isVL53L1XActive) {
        Serial.println("Starting VL53L1X...");
        if (!tof.init()) {
            Serial.println("Failed to initialize VL53L1X!");
            return;
        }
        tof.setTimeout(500);
        tof.setDistanceMode(VL53L1X::Long);
        tof.setMeasurementTimingBudget(50);
        tof.startContinuous(50);
        isVL53L1XActive = true;
        Serial.println("VL53L1X started");
    }
}
void stopVL53L1X() {
    if (isVL53L1XActive) {
        tof.stopContinuous();
        isVL53L1XActive = false;
        tofReadingState = TOF_IDLE;
        Serial.println("VL53L1X stopped");
    }
}

void startBNO055() {
    if (!isBNO055Active) {
        if (!bno.begin()) {
            Serial.println("Failed to initialize BNO055!");
            return;
        }
        bno.setExtCrystalUse(true);
        isBNO055Active = true;
        Serial.println("BNO055 started");
    }
}

void stopBNO055() {
    if (isBNO055Active) {
        isBNO055Active = false;
        Serial.println("BNO055 stopped");
    }
}

void startAS5600() {
    if (!isAS5600Active) {
        if (!magen.begin()) {
            Serial.println("Failed to initialize AS5600!");
            return;
        }
        magen.setDirection(AS5600_CLOCK_WISE);
        isAS5600Active = true;
        lastRawAngle = -1; // Reset angle tracking
        totalLinearDistance = 0.0; // Reset linear distance
        Serial.println("AS5600 started");
    }
}

void stopAS5600() {
    if (isAS5600Active) {
        isAS5600Active = false;
        lastRawAngle = -1; // Reset angle tracking
        totalLinearDistance = 0.0; // Reset linear distance
        Serial.println("AS5600 stopped");
    }
}

void updateActiveSensors() {
    stopVL53L1X();
    stopBNO055();
    stopAS5600();

    switch (current_screen) {
        case 0: // Home Screen
            break;
        case 1: // Measure Screen
            break;
        case 2: // Align Screen
            startBNO055();
            break;
        case 3: // Draft Screen
            startAS5600();
            break;
        case 4: // Settings Screen
            break;
        case 5: // Distance Screen
            if (distanceInputSource == INPUT_TOF) {
                startVL53L1X();
            } else if (distanceInputSource == INPUT_ENCODER) {
                startAS5600();
            }
            break;
        case 6: // Orientation Screen
            startBNO055();
            break;
        case 7: // Compass Screen
            startBNO055();
            break;
        case 8: // About Screen
            break;
        case 9: // Calibration Screen
            startBNO055();
            break;
        default:
            Serial.println("Unknown screen!");
            break;
    }
}

void setCurrentAsNorth() {
    sensors_event_t mag;
    bno.getEvent(&mag, Adafruit_BNO055::VECTOR_MAGNETOMETER);
    headingOffset = atan2(mag.magnetic.y, mag.magnetic.x) * 180 / PI;
    if (headingOffset < 0) headingOffset += 360;
}

float getAdjustedHeading() {
    sensors_event_t mag;
    bno.getEvent(&mag, Adafruit_BNO055::VECTOR_MAGNETOMETER);
    float rawHeading = atan2(mag.magnetic.y, mag.magnetic.x) * 180 / PI;
    if (rawHeading < 0) rawHeading += 360;
    float adjustedHeading = rawHeading - headingOffset;
    if (adjustedHeading < 0) adjustedHeading += 360;
    return adjustedHeading;
}

void updateCompass() {
    float heading = getAdjustedHeading();
    if (heading < 0) heading += 360;
    lv_img_set_angle(ui_Image26, (int)(heading * 10));
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%d \u00B0", (int)heading);
    _ui_label_set_property(ui_Label25, _UI_LABEL_PROPERTY_TEXT, buffer);
}

void startToFReading(uint32_t duration_ms) {
    // Force reset of ToF state to ensure fresh reading
    tofReadingState = TOF_IDLE;
    tofSum = 0.0;
    tofCount = 0;

    if (!isVL53L1XActive) {
        startVL53L1X();
        if (!isVL53L1XActive) {
            _ui_label_set_property(ui_Label11, _UI_LABEL_PROPERTY_TEXT, "Error");
            _ui_label_set_property(ui_Label51, _UI_LABEL_PROPERTY_TEXT, "Error");
            tofReadingState = TOF_COMPLETE;
            Serial.println("ToF reading failed: VL53L1X not active");
            return;
        }
    }

    tofReadingState = TOF_READING;
    tofStartTime = millis();
    tofDuration = duration_ms;
    Serial.println("Started ToF reading");
}

void updateToFReading() {
    if (tofReadingState != TOF_READING) {
        return;
    }

    if (millis() - tofStartTime >= tofDuration) {
        tofReadingState = TOF_COMPLETE;
        float average = getToFAverage();
        char buffer[16];
        if (average >= 0) {
            snprintf(buffer, sizeof(buffer), "%.2f", average/1000);
            _ui_label_set_property(ui_Label11, _UI_LABEL_PROPERTY_TEXT, buffer);
            float distance_inch = average / 25.4;
            int feet = int(distance_inch) / 12;
            int inches = int(distance_inch) % 12;
            snprintf(buffer, sizeof(buffer), "%d ft %d in", feet, inches);
            _ui_label_set_property(ui_Label51, _UI_LABEL_PROPERTY_TEXT, buffer);
            Serial.println("ToF reading complete, average displayed");
        } else {
            _ui_label_set_property(ui_Label11, _UI_LABEL_PROPERTY_TEXT, "Error");
            _ui_label_set_property(ui_Label51, _UI_LABEL_PROPERTY_TEXT, "Error");
            Serial.println("ToF reading failed");
        }
        digitalWrite(hapticPin, HIGH);
        delay(200);
        digitalWrite(hapticPin, LOW);
        tone(buzzerPin, 1200, 200);
        return;
    }

    // Read and update UI every 100ms to reduc
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate >= 100) {
        if (!tof.timeoutOccurred()) {
            float distance = tof.readRangeContinuousMillimeters();
            tofSum += distance;
            tofCount++;

            char buffer[16];
            snprintf(buffer, sizeof(buffer), "%.2f", distance/1000);
            _ui_label_set_property(ui_Label11, _UI_LABEL_PROPERTY_TEXT, buffer);
            float distance_inch = distance / 25.4;
            int feet = int(distance_inch) / 12;
            int inches = int(distance_inch) % 12;
            snprintf(buffer, sizeof(buffer), "%d ft %d in", feet, inches);
            _ui_label_set_property(ui_Label51, _UI_LABEL_PROPERTY_TEXT, buffer);

            Serial.print("Live ToF: ");
            Serial.println(distance);
        } else {
            Serial.println("VL53L1X timeout in update!");
            tofReadingState = TOF_COMPLETE;
            _ui_label_set_property(ui_Label11, _UI_LABEL_PROPERTY_TEXT, "Error");
            _ui_label_set_property(ui_Label51, _UI_LABEL_PROPERTY_TEXT, "Error");
        }
        lastUpdate = millis();
    }
}

float getToFAverage() {
    if (tofCount == 0) {
        return -1.0;
    }
    return tofSum / tofCount;
}


float getLinearDistanceFromAS5600() {
    if (!isAS5600Active) {
        startAS5600();
        if (!isAS5600Active) {
            return -1.0; // Sensor failed to start
        }
    }

    // Roller parameters
    const float rollerDiameter = 23.9; // mm
    const float circumference = PI * rollerDiameter; // mm per full rotation
    const float maxRawAngle = 4096.0; // AS5600 resolution (0-4095)

    // Read current raw angle
    uint16_t currentRawAngle = magen.rawAngle();

    // Initialize lastRawAngle on first reading
    if (lastRawAngle == -1) {
        lastRawAngle = currentRawAngle;
        return totalLinearDistance; // No change yet
    }

    // Calculate angle difference, handling wraparound
    int16_t angleDiff = currentRawAngle - lastRawAngle;
    if (angleDiff > maxRawAngle / 2) {
        angleDiff -= maxRawAngle; // Handle wraparound (counterclockwise)
    } else if (angleDiff < -maxRawAngle / 2) {
        angleDiff += maxRawAngle; // Handle wraparound (clockwise)
    }

    // Convert angle difference to linear distance
    float rotationFraction = angleDiff / maxRawAngle;
    float linearDistance = rotationFraction * circumference;
    totalLinearDistance += linearDistance;

    // Update last angle
    lastRawAngle = currentRawAngle;

    // Return cumulative distance
    return totalLinearDistance;
}

void resetAS5600LinearDistance() {
    totalLinearDistance = 0.0;
    lastRawAngle = magen.rawAngle(); // Update last angle to current to avoid jump
    Serial.println("AS5600 linear distance reset to 0");
    if (current_screen == 5 && distanceInputSource == INPUT_ENCODER) {
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%d", 0);
        _ui_label_set_property(ui_Label11, _UI_LABEL_PROPERTY_TEXT, buffer);
        snprintf(buffer, sizeof(buffer), "%d ft %d in", 0, 0);
        _ui_label_set_property(ui_Label51, _UI_LABEL_PROPERTY_TEXT, buffer);
    }
}