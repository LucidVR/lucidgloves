#if USING_FORCE_FEEDBACK
#include "MinMaxCalibration.h"

#if defined(ESP32)
  #include "ESP32Servo.h"
#else
  #include "Servo.h"
#endif

Servo pinkyServo;
Servo ringServo;
Servo middleServo;
Servo indexServo;
Servo thumbServo;

// Use a list for easier modification of all servos.
Servo* servos[5] = { &thumbServo, &indexServo, &middleServo, &ringServo, &pinkyServo };

void setupServoHaptics(){
  pinkyServo.attach(PIN_PINKY_MOTOR);
  ringServo.attach(PIN_RING_MOTOR);
  middleServo.attach(PIN_MIDDLE_MOTOR);
  indexServo.attach(PIN_INDEX_MOTOR);
  thumbServo.attach(PIN_THUMB_MOTOR);
}

void writeServoHaptics(const MinMaxCalibration<int>* calibrators, const int* hapticLimits) {
  // haptic limits are 0-1000, calibration outputs are 0-4096, servo inputs are 0-180

  for (size_t i = 0; i < 5; ++i) {
    int servo_output;
    #if !USING_FORCE_FEEDBACK_SCALING
      // haptic limits are 0-1000, need to map to servo output of 0-180
      servo_output = map(hapticLimits[i], 0, 1000, 0, 180);
    #else
      // First map 0-1000 to 0-4096 based on the calibrated range of the fingers.
      servo_output = calibrators[i].calibrate(hapticLimits[i], 0, 1000);

      // Second map from 0-4096 to the input of the servos.
      servo_output = map(hapticLimits[i], 0, ANALOG_MAX, 0, 180);
    #endif

    servos[i]->write(servo_output);
  }
}

#endif
