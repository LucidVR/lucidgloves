#pragma once
#include "../../Config.h"

#if defined(ESP32)
  #include "ESP32Servo.h"
#else
  #include "Servo.h"
#endif

class Haptics {
private:
    Servo pinkyServo;
    Servo ringServo;
    Servo middleServo;
    Servo indexServo;
    Servo thumbServo;

public:
    void setupServoHaptics();
    void scaleLimits(int* hapticLimits, float* scaledLimits);
    void dynScaleLimits(int* hapticLimits, float* scaledLimits);
    void writeServoHaptics(int* hapticLimits);
};
