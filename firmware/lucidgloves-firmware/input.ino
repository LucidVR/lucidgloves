#include "MinMaxCalibration.h"

// Requires RunningMedian library by Rob Tillaart
#if ENABLE_MEDIAN_FILTER
  #include <RunningMedian.h>
  RunningMedian rmSamples[5] = {
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES)
  };
#endif

#define CALIBRATION_RANGE { 0, ANALOG_MAX, CLAMP_ANALOG_MAP }
MinMaxCalibration<int> calibration[5] = {CALIBRATION_RANGE, CALIBRATION_RANGE, CALIBRATION_RANGE, CALIBRATION_RANGE, CALIBRATION_RANGE};

void setupInputs(){
  pinMode(PIN_JOY_BTN, INPUT_PULLUP);
  pinMode(PIN_A_BTN, INPUT_PULLUP);
  pinMode(PIN_B_BTN, INPUT_PULLUP);

  pinMode(PIN_MENU_BTN, INPUT_PULLUP);
  
  #if !TRIGGER_GESTURE
  pinMode(PIN_TRIG_BTN, INPUT_PULLUP);
  #endif

  #if !GRAB_GESTURE
  pinMode(PIN_GRAB_BTN, INPUT_PULLUP);
  #endif

  #if !PINCH_GESTURE
  pinMode(PIN_PNCH_BTN, INPUT_PULLUP);
  #endif

  #if USING_CALIB_PIN
  pinMode(PIN_CALIB, INPUT_PULLUP);
  #endif
}


void getFingerPositions(int* rawFingers){
  rawFingers[0] = NO_THUMB?0:analogRead(PIN_THUMB);
  rawFingers[1] = analogRead(PIN_INDEX);
  rawFingers[2] = analogRead(PIN_MIDDLE);
  rawFingers[3] = analogRead(PIN_RING);
  rawFingers[4] = analogRead(PIN_PINKY);

  for (int i = 0; i < 5; i++) {
    #if FLIP_POTS
      rawFingers[i] = ANALOG_MAX - rawFingers[i];
    #endif

    #if ENABLE_MEDIAN_FILTER
      rmSamples[i].add(rawFingers[i]);
      rawFingers[i] = rmSamples[i].getMedian();
    #endif

    #if CLAMP_FLEXION
      rawFingers[i] = constrain(rawFingers[i], CLAMP_MIN, CLAMP_MAX);
    #endif
  }
}

int analogReadDeadzone(byte pin){
  int raw = analogRead(pin);
  if (abs(ANALOG_MAX/2 - raw) < JOYSTICK_DEADZONE * ANALOG_MAX / 100)
    return ANALOG_MAX/2;
  else
    return raw;
}

int getJoyX(){
  #if JOYSTICK_BLANK
  return ANALOG_MAX/2;
  #elif JOY_FLIP_X
  return ANALOG_MAX - analogReadDeadzone(PIN_JOY_X);
  #else
  return analogReadDeadzone(PIN_JOY_X);
  #endif
}

int getJoyY(){
  #if JOYSTICK_BLANK
  return ANALOG_MAX/2;
  #elif JOY_FLIP_Y
  return ANALOG_MAX - analogReadDeadzone(PIN_JOY_Y);
  #else
  return analogReadDeadzone(PIN_JOY_Y);
  #endif
}

bool getButton(byte pin){
  return digitalRead(pin) != HIGH;
}
