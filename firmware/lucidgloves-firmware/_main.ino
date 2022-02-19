#define ALWAYS_CALIBRATING CALIBRATION_LOOPS == -1

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
    
    int* fingerPos = getFingerPositions(calibrate, calibButton);
    bool joyButton = getButton(PIN_JOY_BTN) != INVERT_JOY;

    #if TRIGGER_GESTURE
    bool triggerButton = triggerGesture(fingerPos);
    #else
    bool triggerButton = getButton(PIN_TRIG_BTN) != INVERT_TRIGGER;
    #endif

    bool aButton = getButton(PIN_A_BTN) != INVERT_A;
    bool bButton = getButton(PIN_B_BTN) != INVERT_B;

    #if GRAB_GESTURE
    bool grabButton = grabGesture(fingerPos);
    #else
    bool grabButton = getButton(PIN_GRAB_BTN) != INVERT_GRAB;
    #endif

    #if PINCH_GESTURE
    bool pinchButton = pinchGesture(fingerPos);
    #else
    bool pinchButton = getButton(PIN_PNCH_BTN) != INVERT_PINCH;
    #endif

    bool menuButton = getButton(PIN_MENU_BTN) != INVERT_MENU;
    #if ENCODING == ENCODE_ALPHA_FULL_JOINT
      // String length based on str_len((AAA)XXXX(AAB)XXXX(AAC)XXXX(AAD)XXXX(AB)XXXX) + '\0'
      // We first allocate a blob of memory, then we convert it to a list of pointers, by
      // indexing into it.
      char blob[5][44 + 1];
      char* encoded_fingers[5] = {blob[0], blob[1], blob[2], blob[3], blob[4]};

      // String length based Fingers + Joys (FXXXXGXXXXX) + Buttons + '\0'
      char comm_message[44*5 + 5*2 + 1*8 + 1];

      // Encode each finger. Since we only have one measurement per finger, set all joints
      // to the same, and set splay to the middle.
      int thumb_values[4] = { fingerPos[0], fingerPos[0], fingerPos[0], ANALOG_MAX/2 };
      encode_thumb(encoded_fingers[0], thumb_values);
      for (int i = 1; i < 5; i++) {
        // Joint 0 should be 0 for all fingers, we don't track that, the rest are the same
        // as the thumb.
        int finger_values[5] = { 0, fingerPos[i], fingerPos[i], fingerPos[i], ANALOG_MAX/2 };
        encode_finger(i, encoded_fingers[i], finger_values);
      }

      encode(comm_message, encoded_fingers, getJoyX(), getJoyY(), joyButton, triggerButton, aButton, bButton, grabButton, pinchButton, calibButton, menuButton);

      comm->output(comm_message);
    #else
      comm->output(encode(fingerPos, getJoyX(), getJoyY(), joyButton, triggerButton, aButton, bButton, grabButton, pinchButton, calibButton, menuButton));
    #endif

    #if USING_FORCE_FEEDBACK
      char received[100];
      if (comm->readData(received)){
        int hapticLimits[5];
        decodeData(received, hapticLimits);
        writeServoHaptics(hapticLimits);
      }
    #endif
    delay(LOOP_TIME);
  }
}
