#include "MinMaxCalibration.h"

#define ALWAYS_CALIBRATING CALIBRATION_LOOPS == -1

#define CALIBRATION_RANGE { 0, ANALOG_MAX, CLAMP_ANALOG_MAP }
MinMaxCalibration<int> calibrators[5] = {CALIBRATION_RANGE, CALIBRATION_RANGE, CALIBRATION_RANGE, CALIBRATION_RANGE, CALIBRATION_RANGE};
// Prevent Arduino IDE from being "helpful" and auto generating this prototype ABOVE the inludes.
void writeServoHaptics(const MinMaxCalibration<int>* calibrators, const int* hapticLimits);

ICommunication* comm;
int loops = 0;
void setup() {
  #if COMMUNICATION == COMM_SERIAL
    comm = new SerialCommunication();
  #elif COMMUNICATION == COMM_BTSERIAL
    comm = new BTSerialCommunication();
  #endif  
  comm->start();

  setupInputs();

  #if USING_FORCE_FEEDBACK
    setupServoHaptics();  
  #endif
  
}

void loop() {
  if (comm->isOpen()){
    #if USING_CALIB_PIN
    bool calibButton = getButton(PIN_CALIB) != INVERT_CALIB;
    if (calibButton)
      loops = 0;
    #else
    bool calibButton = false;
    #endif
    
    bool calibrate = false;
    if (loops < CALIBRATION_LOOPS || ALWAYS_CALIBRATING){
      calibrate = true;
      loops++;
    }
    
    int rawFingerPositions[5];
    int calibratedFingerPositions[5];
    getFingerPositions(rawFingerPositions);

    for (size_t i = 0; i < 5; ++i) {
      // Calibration button is set. Reset the the min/max values.
      if (calibButton) {
        calibrators[i].reset();
      }

      // Add the new value to the calibration set.
      if (calibrate) {
        calibrators[i].update(rawFingerPositions[i]);
      }

      // Adjust the raw data based on the calibrator.
      calibratedFingerPositions[i] = calibrators[i].calibrate(rawFingerPositions[i], 0, ANALOG_MAX);
    }

    bool joyButton = getButton(PIN_JOY_BTN) != INVERT_JOY;

    #if TRIGGER_GESTURE
    bool triggerButton = triggerGesture(calibratedFingerPositions);
    #else
    bool triggerButton = getButton(PIN_TRIG_BTN) != INVERT_TRIGGER;
    #endif

    bool aButton = getButton(PIN_A_BTN) != INVERT_A;
    bool bButton = getButton(PIN_B_BTN) != INVERT_B;

    #if GRAB_GESTURE
    bool grabButton = grabGesture(calibratedFingerPositions);
    #else
    bool grabButton = getButton(PIN_GRAB_BTN) != INVERT_GRAB;
    #endif

    #if PINCH_GESTURE
    bool pinchButton = pinchGesture(calibratedFingerPositions);
    #else
    bool pinchButton = getButton(PIN_PNCH_BTN) != INVERT_PINCH;
    #endif

    bool menuButton = getButton(PIN_MENU_BTN) != INVERT_MENU;
    
    comm->output(encode(calibratedFingerPositions, getJoyX(), getJoyY(), joyButton, triggerButton, aButton, bButton, grabButton, pinchButton, calibButton, menuButton));

    #if USING_FORCE_FEEDBACK
      char received[100];
      if (comm->readData(received)){
        int hapticLimits[5];
        decodeData(received, hapticLimits);
        writeServoHaptics(calibrators, hapticLimits);
      }
    #endif
    delay(LOOP_TIME);
  }
}
