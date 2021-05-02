#include <Arduino.h>
#include "config.h"
#include "ICommunication.h"
#include "input.h"
#include "SerialCommunication.h"
#include "SerialBTCommunitaction.h"
#include "gesture.h"
#include "Encoding.h"

#define ALWAYS_CALIBRATING CALIBRATION_LOOPS == -1

ICommunication* comm;
int loops = 0;
void setup() {
  // we dont need to manually set ANALOG_MAX in config.h, we could just do it here...
  analogReadResolution(10); //1023
  #if COMMUNICATION == COMM_SERIAL
    comm = new SerialCommunication();
  #elif COMMUNICATION == COMM_BTSERIAL
    comm = new BTSerialCommunication();
  #endif  
  comm->start();

  setupInputs();
  
}

void loop() {
  if (comm->isOpen()){

    bool calibrate = false;
    if (loops < CALIBRATION_LOOPS || ALWAYS_CALIBRATING){
      calibrate = true;
      loops++;
    }
      
    
    int* fingerPos = getFingerPositions(calibrate);
    bool joyButton = getButton(PIN_JOY_BTN);

    #if TRIGGER_GESTURE
    bool triggerButton = triggerGesture(fingerPos);
    #else
    bool triggerButton = getButton(PIN_TRIG_BTN);
    #endif

    bool aButton = getButton(PIN_A_BTN);
    bool bButton = getButton(PIN_B_BTN);

    #if GRAB_GESTURE
    bool grabButton = grabGesture(fingerPos);
    #else
    bool grabButton = getButton(PIN_GRAB_BTN);
    #endif

    #if PINCH_GESTURE
    bool pinchButton = grabGesture(fingerPos);
    #else
    bool pinchButton = getButton(PIN_PNCH_BTN);
    #endif
    
    comm->output(encode(fingerPos, getJoyX(), getJoyY(), joyButton, triggerButton, aButton, bButton, grabButton, pinchButton));
    delay(LOOP_TIME);
  }
}
