#if USING_FORCE_FEEDBACK

#if defined(ESP32)
  #include "ESP32Servo.h"
#else
  #include "Servo.h"
#endif

#if SERVO_SMOOTH_STEPPING
  #define SERVO_MIN MIN_PULSE_WIDTH
  #define SERVO_MAX MAX_PULSE_WIDTH
  #define WRITE_FUNCTION(x) writeMicroseconds(x)
#else
  #define SERVO_MIN 0
  #define SERVO_MAX 180
  #define WRITE_FUNCTION(x) write(x)
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

// Re-implimentation of map() using floats. If we need speed in the future swap to the integer
// based map() function and give up a bit of accuracy.
inline long scaleLimits(float x, float in_min, float in_max, float out_min, float out_max) {
  // Map one range to the other.
  x = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

  // Constrain x to the servo limits. We don't ever want to try to move to 200 degrees.
  return (long)constrain(x, out_min, out_max);
}

//dynamic scaling, maps to the limits calibrated from your finger
void dynScaleLimits(int* hapticLimits, float* scaledLimits) {
  //will be refactored to take min and max as an argument

  /* this implementation of dynamic scaling relies on the assumption 
   * that the servo reaches 2/3 of the potentiometer's range, 
   * and that 0 degrees is geared to the start of the potentiometer.
   * Different hardware types may need to handle dynamic scaling differently.
   */
  for (int i = 0; i < sizeof(hapticLimits); i++){
    scaledLimits[i] = hapticLimits[i] / FORCE_FEEDBACK_MAX * SERVO_MAX;
  }
}

void writeServoHaptics(int* hapticLimits) {
  for (int i = 0; i < sizeof(servos); ++i) {
    // Need to convert the input range sent over comm to the correct servo range.
    servos[i]->WRITE_FUNCTION(scaleLimits(hapticLimits[0], FORCE_FEEDBACK_MIN, FORCE_FEEDBACK_MAX, SERVO_MIN, SERVO_MAX));
  }
}

#endif
