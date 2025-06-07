#ifndef SENSORS_H
#define SENSORS_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <VL53L1X.h>
#include <AS5600.h>

// Enum to track input source for Distance Screen
enum DistanceInputSource {
    INPUT_TOF,
    INPUT_ENCODER
};
extern DistanceInputSource distanceInputSource;

// Enum to track selected distance unit
enum DistanceUnit {
    UNIT_MM,
    UNIT_CM,
    UNIT_M
};
extern DistanceUnit distanceUnit;
// I2C Pins
#define I2C_SDA 32
#define I2C_SCL 33

// BNO055 Sampling Delay
#define BNO055_SAMPLERATE_DELAY_MS 100

extern Adafruit_BNO055 bno;
extern VL53L1X tof;
extern AS5600 magen;
extern bool isVL53L1XActive;
extern bool isBNO055Active;
extern bool isAS5600Active;

// State for non-blocking ToF reading
enum ToFReadingState {
    TOF_IDLE,
    TOF_READING,
    TOF_COMPLETE
};
extern ToFReadingState tofReadingState;
extern unsigned long tofStartTime;
extern float tofSum;
extern int tofCount;

void sensors_init();
void startVL53L1X();
void stopVL53L1X();
void startBNO055();
void stopBNO055();
void startAS5600();
void stopAS5600();
void updateActiveSensors();
void setCurrentAsNorth();
float getAdjustedHeading();
void updateCompass();

// Functions for ToF reading
void startToFReading(uint32_t duration_ms);
void updateToFReading();
float getToFAverage();
// Function to convert AS5600 raw angle to linear distance
float getLinearDistanceFromAS5600();

// Function to reset AS5600 linear distance
void resetAS5600LinearDistance();

#endif