#if USING_FORCE_FEEDBACK

#if defined(ESP32)
  #include "ESP32Servo.h"
#else
  #include "Servo.h"
#endif

#if SERVO_SCALING // NOTE: .ino files are loaded in alphabetical order
  #define POT_180 2500.0f // the value on a potentiometer (or other finger tracking device) when you rotate it by 180°
  #define SERVO_MARGIN_ERROR 0 // some leeway if the servos still restrict your movement after retracting (enable SCALE_ZERO to test)
  #define SCALE_ZERO false // true - full retraction is also scaled, servos move less; false - useful for initial testing so you don't end up with stuck servos unable to calibrate your fingers properly
  int maxFingersServo[5] = {0,0,0,0,0};
  int minFingersServo[5] = {ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX};
  int maxFingersAngle[5] = {180, 180, 180, 180, 180}; // max angle to which your fingers can rotate a potentiometer
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

//static scaling, maps to entire range of servo
void scaleLimits(int* hapticLimits, float* scaledLimits){
  for (int i = 0; i < 5; i++){
    scaledLimits[i] = 180.0f - hapticLimits[i] / 1000.0f * 180.0f;
  }
}

//dynamic scaling, maps to the limits calibrated from your fingers
void dynScaleLimits(int* hapticLimits, float* scaledLimits) {
  /* This implementation of dynamic scaling relies on the finger
   * calibration of the gloves and scales to each finger individually.
   * Fingers don't need to start at pot reading 0, what matters is the
   * difference between opened and closed hand. The bigger the difference,
   * in the readings, the more degree of freedom servos will allow.
   * Ideally, with SCALE_ZERO turned on, you should be able to fully
   * close your hand and the screws should barely touch servo horns.
   * Different hardware types may need to handle dynamic scaling differently.
   */
  for (int i = 0; i <= sizeof(hapticLimits); i++) {
    #if !SCALE_ZERO
      if (hapticLimits[i] == 0) {
        scaledLimits[i] = 180;
        continue;
      }
    #endif
    scaledLimits[i] = maxFingersAngle[i] - hapticLimits[i] / 1000.0f * maxFingersAngle[i] + SERVO_MARGIN_ERROR;
  }
}

void writeServoHaptics(int* hapticLimits){
  float scaledLimits[5];
  #if SERVO_SCALING
  dynScaleLimits(hapticLimits, scaledLimits);
  #else
  scaleLimits(hapticLimits, scaledLimits);
  #endif
  if(hapticLimits[0] >= 0) thumbServo.write(scaledLimits[0]);
  if(hapticLimits[1] >= 0) indexServo.write(scaledLimits[1]);
  if(hapticLimits[2] >= 0) middleServo.write(scaledLimits[2]);
  if(hapticLimits[3] >= 0) ringServo.write(scaledLimits[3]);
  if(hapticLimits[4] >= 0) pinkyServo.write(scaledLimits[4]);
}

#endif
