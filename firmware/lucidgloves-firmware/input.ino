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

int* getFingerPositions(bool calibrating, bool reset){
  int rawFingers[5] = {NO_THUMB?0:analogRead(PIN_THUMB), analogRead(PIN_INDEX), analogRead(PIN_MIDDLE), analogRead(PIN_RING), analogRead(PIN_PINKY)};
  static int calibrated[5] = {511,511,511,511,511};

  for (int i = 0; i <5; i++) {
    #if FLIP_POTS
      rawFingers[i] = ANALOG_MAX - rawFingers[i];
    #endif

    #if ENABLE_MEDIAN_FILTER
      rmSamples[i].add(rawFingers[i]);
      rawFingers[i] = rmSamples[i].getMedian();
    #endif

    // Reset max and mins as needed.
    if (reset) calibration[i].reset();

    // Put this value into the calibrator.
    if (calibrating) {
      #if !CLAMP_FLEXION
        calibration[i].update(rawFingers[i]);
      #else
        calibration[i].update(constrain(rawFingers[i], CLAMP_MIN, CLAMP_MAX));
      #endif
    }

    calibrated[i] = calibration[i].calibrate(rawFingers[i], 0, ANALOG_MAX);
  }
  return calibrated;
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
