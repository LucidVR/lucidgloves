// Requires RunningMedian library by Rob Tillaart
#if ENABLE_MEDIAN_FILTER
  #include <RunningMedian.h>
  RunningMedian rmSamples[10] = {
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES),
      RunningMedian(MEDIAN_SAMPLES)
  };
#endif

int maxFingers[10] = {0,0,0,0,0,0,0,0,0,0};
int minFingers[10] = {ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX};

#if FLEXION_MIXING == MIXING_SINCOS
  int sinMin[5] = {ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX};
  int sinMax[5] = {0,0,0,0,0};

  int cosMin[5] = {ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX};
  int cosMax[5] = {0,0,0,0,0};

  bool cosPositive[5] = {true, true, true, true, true};
  double totalOffset[5] = {0,0,0,0,0};
#endif

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

  #if USING_MULTIPLEXER
  byte selectPins[] = {PINS_MUX_SELECT};
  for (int i = 0; i < sizeof(selectPins); i++){
    pinMode(selectPins[i], OUTPUT);
  }
  #endif
}

int analogPinRead(int pin){
  #if USING_MULTIPLEXER
  if (ISMUX(pin)){
    return readMux(UNMUX(pin));
  }
  else{
    return analogRead(pin);
  }
  #else
   return analogRead(UNMUX(pin));
  #endif
}

#if USING_MULTIPLEXER
int readMux(byte pin){
  byte selectPins[] = {PINS_MUX_SELECT}; //get the array of select pins for the mux

  for (int i = sizeof(selectPins - 1); i > -1; i--){
    digitalWrite(selectPins[i], ((int)pow(2,i) & (pin)) == 0 ? LOW:HIGH); //convert the pin number to binary, and set each digit to it's corresponsing select pin.
  }

  delayMicroseconds(MULTIPLEXER_DELAY);
  return analogRead(MUX_INPUT);
}
#endif

int* getFingerPositions(bool calibrating, bool reset){
  #if FLEXION_MIXING == MIXING_NONE //no mixing, just linear
  int rawFingersFlexion[5] = {NO_THUMB?0:analogPinRead(PIN_THUMB), analogPinRead(PIN_INDEX), analogPinRead(PIN_MIDDLE), analogPinRead(PIN_RING), analogPinRead(PIN_PINKY)};
  
  #elif FLEXION_MIXING == MIXING_SINCOS
  int rawFingersFlexion[5] = {NO_THUMB?0:sinCosMix(PIN_THUMB, PIN_THUMB_SECOND, 0 ), 
                                  sinCosMix(PIN_INDEX, PIN_INDEX_SECOND, 1 ), 
                                  sinCosMix(PIN_MIDDLE,PIN_MIDDLE_SECOND,2 ), 
                                  sinCosMix(PIN_RING,  PIN_RING_SECOND,  3 ), 
                                  sinCosMix(PIN_PINKY, PIN_PINKY_SECOND, 4 )};

  #endif

  int rawFingers[10];

  #if USING_SPLAY
    int rawFingersSplay[5] = {NO_THUMB?0:analogPinRead(PIN_THUMB_SPLAY), 
                              analogPinRead(PIN_INDEX_SPLAY), 
                              analogPinRead(PIN_MIDDLE_SPLAY), 
                              analogPinRead(PIN_RING_SPLAY), 
                              analogPinRead(PIN_PINKY_SPLAY)};
  #else
    int rawFingersSplay[5] = {0,0,0,0,0};
  #endif
  
    //memcpy(rawFingers, rawFingersFlexion, 5); //memcpy doesn't seem to work here
    //memcpy(&rawFingers[5], rawFingersSplay, 5); 

  for (int i = 0; i < 5; i++){
    rawFingers[i] = rawFingersFlexion[i];
    rawFingers[i+5] = rawFingersSplay[i];
  }
  
  
  //flip pot values if needed
  #if FLIP_FLEXION
  for (int i = 0; i < 5; i++){
    rawFingers[i] = ANALOG_MAX - rawFingers[i];
  }
  #endif
  
  #if FLIP_SPLAY
  for (int i = 5; i < 10; i++){
    rawFingers[i] = ANALOG_MAX - rawFingers[i];
  }
  #endif

  #if ENABLE_MEDIAN_FILTER
  for (int i = 0; i < 10; i++){
    rmSamples[i].add( rawFingers[i] );
    rawFingers[i] = rmSamples[i].getMedian();
  }
  #endif

  //reset max and mins as needed
  if (reset){
    for (int i = 0; i <10; i++){
      if (i < 5)
        totalOffset[i] = 0;
      maxFingers[i] = 0;
      minFingers[i] = ANALOG_MAX;
    }
  }
  
  //if during the calibration sequence, make sure to update max and mins
  if (calibrating){
    for (int i = 0; i <10; i++){
      if (rawFingers[i] > maxFingers[i])
        #if CLAMP_SENSORS
          maxFingers[i] = ( rawFingers[i] <= CLAMP_MAX )? rawFingers[i] : CLAMP_MAX;
        #else
          maxFingers[i] = rawFingers[i];
        #endif
      if (rawFingers[i] < minFingers[i])
        #if CLAMP_SENSORS
          minFingers[i] = ( rawFingers[i] >= CLAMP_MIN )? rawFingers[i] : CLAMP_MIN;
        #else
          minFingers[i] = rawFingers[i];
        #endif
    }
  }

  static int calibrated[10] = {ANALOG_MAX / 2, ANALOG_MAX / 2, ANALOG_MAX / 2, ANALOG_MAX / 2, ANALOG_MAX / 2, ANALOG_MAX / 2, ANALOG_MAX / 2, ANALOG_MAX / 2, ANALOG_MAX / 2, ANALOG_MAX / 2};
  
  for (int i = 0; i<10; i++){
    if (minFingers[i] != maxFingers[i]){
      calibrated[i] = map( rawFingers[i], minFingers[i], maxFingers[i], 0, ANALOG_MAX );
      #if CLAMP_ANALOG_MAP
        if (calibrated[i] < 0)
          calibrated[i] = 0;
        if (calibrated[i] > ANALOG_MAX)
          calibrated[i] = ANALOG_MAX;
      #endif
    }
    else {
      calibrated[i] = ANALOG_MAX / 2;
    }
  }
  return calibrated;
  
}

int analogReadDeadzone(int pin){
  int raw = analogPinRead(pin);
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

#if FLEXION_MIXING == MIXING_SINCOS
//mixing
int sinCosMix(int sinPin, int cosPin, int i){

  int sinRaw = analogPinRead(sinPin);
  int cosRaw = analogPinRead(cosPin);

  
  //scaling
  sinMin[i] = min(sinRaw, sinMin[i]);
  sinMax[i] = max(sinRaw, sinMax[i]);

  cosMin[i] = min(cosRaw, cosMin[i]);
  cosMax[i] = max(cosRaw, cosMax[i]);

  int sinScaled = map(sinRaw, sinMin[i], sinMax[i], -ANALOG_MAX, ANALOG_MAX);
  int cosScaled = map(cosRaw, cosMin[i], cosMax[i], -ANALOG_MAX, ANALOG_MAX);

  //trigonometry stuffs
  double tanRaw = ((double)sinScaled)/((double)cosScaled);
  double angleRaw = atan(tanRaw);

  //counting rotations
  if ((cosScaled > 0) != cosPositive[i]){
    totalOffset[i] += PI * (cosPositive[i]?-1:1) * (cosScaled>sinScaled?1:-1);
  }
  cosPositive[i] = cosScaled > 0;
  double totalAngle = angleRaw + totalOffset[i];

  return (int)(totalAngle * ANALOG_MAX);
  
}
#endif
