#if USING_FORCE_FEEDBACK

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

void setupServoHaptics(){
  pinkyServo.attach(PIN_PINKY_MOTOR);
  ringServo.attach(PIN_RING_MOTOR);
  middleServo.attach(PIN_MIDDLE_MOTOR);
  indexServo.attach(PIN_INDEX_MOTOR);
  thumbServo.attach(PIN_THUMB_MOTOR);
}

static int scale(int limit) {
  return 180.f - limit / 1000.f * 180.f;
}

//dynamic scaling, maps to the limits calibrated from your finger
void dynScaleLimits(int* hapticLimits, float* scaledLimits){
  //will be refactored to take min and max as an argument

  /* this implementation of dynamic scaling relies on the assumption 
   * that the servo reaches 2/3 of the potentiometer's range, 
   * and that 0 degrees is geared to the start of the potentiometer.
   * Different hardware types may need to handle dynamic scaling differently.
   */
  for (int i = 0; i < sizeof(hapticLimits); i++){
    scaledLimits[i] = hapticLimits[i] / 1000.0f * 180.0f;
  }
}

void writeServoHaptics(int* hapticLimits){
  if(hapticLimits[4] >= 0) pinkyServo.write(scale(hapticLimits[4]));
  if(hapticLimits[3] >= 0) ringServo.write(scale(hapticLimits[3]));
  if(hapticLimits[2] >= 0) middleServo.write(scale(hapticLimits[2]));
  if(hapticLimits[1] >= 0) indexServo.write(scale(hapticLimits[1]));
  if(hapticLimits[0] >= 0) thumbServo.write(scale(hapticLimits[0]));
}

#endif
