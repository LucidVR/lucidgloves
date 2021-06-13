#define ALWAYS_CALIBRATING CALIBRATION_LOOPS == -1

ICommunication* comm;
int loops = 0;
void setup() {
  Serial.println("Starting!");
  #if COMMUNICATION == COMM_SERIAL
    comm = new SerialCommunication();
  #elif COMMUNICATION == COMM_BTSERIAL
    comm = new BTSerialCommunication();
  #elif COMMUNICATION == COMM_WIFISERIAL
    comm = new WifiSerialCommunication();
  #endif  
  comm->start();

  setupInputs();
}

void loop() {
  comm->loop();
  
  if (comm->isOpen()){
    #if USING_CALIB_PIN
    bool calibButton = getButton(PIN_CALIB);
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
    
    int* fingerPos = getFingerPositions(calibrate, calibButton);
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
