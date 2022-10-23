#include <mutex>
#define ALWAYS_CALIBRATING CALIBRATION_LOOPS == -1

#define CALIB_OVERRIDE false
#if USING_CALIB_PIN && COMMUNICATION == COMM_SERIAL && PIN_CALIB == 0 && !CALIB_OVERRIDE
  #error "You can't set your calibration pin to 0 over usb. You can calibrate with the BOOT button when using bluetooth only. Set CalibOverride to true to override this."
#endif

bool calibrate = false;
bool calibButton = false;
int* fingerPos;
int sinScaledTest = 0;
int cosScaledTest = 0;
int sinCalibTest = 0;
int cosCalibTest = 0;
int totalAngleTest = 0;
int totalOffsetTest = 0;
int angleRawTest = 0;
int sinMinTest = 0;
int sinMaxTest = 0;
int cosMinTest = 0;
int cosMaxTest = 0;
int minFingersTest = 0;
int maxFingersTest = 0;
int sinTest = 0;
int cosTest = 0;

ICommunication* comm;

#if ESP32_DUAL_CORE_SET
//std::mutex fingerPosMutex;
ordered_lock* fingerPosLock = new ordered_lock();
TaskHandle_t Task1;
int threadLoops = 1;
int totalLocks = 0;
int lastMicros = 0;
int fullLoopTime = 0;
//int otherStuffLast = 0;
//int fingerPosTotal = 0;
//int otherStuffTotal = 0;
int fullLoopTotal = 0;
void getInputs(void* parameter){
    for(;;){
      fullLoopTime = micros() - lastMicros;
      fullLoopTotal += fullLoopTime;
      //int fingerPosTime;
      //int otherStuffTime;
      lastMicros = micros();
      {
        //otherStuffLast=micros();
        //std::lock_guard<std::mutex> lock(fingerPosMutex);
        fingerPosLock->lock();
        //otherStuffTime = micros() - otherStuffLast;
        //otherStuffTotal += otherStuffTime;
        //int fingerPosLast = micros();
        totalLocks++;
        getFingerPositions(calibrate, calibButton); //Save finger positions in thread

        fingerPosLock->unlock();
        //fingerPosTime = micros() - fingerPosLast;
        //fingerPosTotal += fingerPosTime;
      }
      threadLoops++;
      if (threadLoops%100 == 0){
        vTaskDelay(1); //keep watchdog fed
      }
      delayMicroseconds(1);
      /*Serial.println(//"Full loop: " + (String)fullLoopTime + 
                 //", Full Loop Avg: " + (String)(fullLoopTotal / threadLoops) +
                 ", Finger Pos: " + (String)fingerPosTime + 
                 ", Finger Pos Avg: " + (String)(fingerPosTotal / threadLoops) +
                 ", Mutex Stuff: " + (String)otherStuffTime + 
                 ", Mutex Stuff Avg: " + (String)(otherStuffTotal / threadLoops));*/
    }           
}
#endif

int loops = 0;
void setup() {
  fingerPos = new int[10];
  for (int i=0; i<10; i++){
    fingerPos[i] = 0;
  }
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
  
  #if ESP32_DUAL_CORE_SET
    xTaskCreatePinnedToCore(
      getInputs, /* Function to implement the task */
      "Get_Inputs", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      tskIDLE_PRIORITY,  /* Priority of the task */
      &Task1,  /* Task handle. */
      0); /* Core where the task should run */
  #endif
}

int lastMainMicros = micros();
int mainMicros = 0;
int mainMicrosTotal = 0;
int mainloops = 1;

int target = 0;

void loop() {
  mainloops++;
  mainMicros = micros() - lastMainMicros;
  mainMicrosTotal += mainMicros;
  lastMainMicros = micros();

  if (Serial.available() > 0){
    target = Serial.parseInt();
    Serial.println("Swtiching target to " + (String)target);
  }
  
  
  if (comm->isOpen()){
    #if USING_CALIB_PIN
    calibButton = getButton(PIN_CALIB) != INVERT_CALIB;
    //Serial.println(getButton(PIN_CALIB));
    if (calibButton)
      loops = 0;
    #else
    calibButton = false;
    #endif


    //bool calibrate = false;
    if (loops < CALIBRATION_LOOPS || ALWAYS_CALIBRATING){
      calibrate = true;
      loops++;
    }
    else{
      calibrate = false;
    }

    #if !ESP32_DUAL_CORE_SET
      getFingerPositions(calibrate, calibButton);
    #endif
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

    int fingerPosCopy[10];
    int mutexTimeDone;
    bool menuButton = getButton(PIN_MENU_BTN) != INVERT_MENU;
    //Serial.println("Outside lock: " + String(totalLocks));
    //totalLocks = 0;
    {
      #if ESP32_DUAL_CORE_SET
      int mutexTime = micros();
      //const std::lock_guard<std::mutex> lock(fingerPosMutex);
      fingerPosLock->lock();
      mutexTimeDone = micros()-mutexTime;
      #endif
      //memcpy(fingerPosCopy, fingerPos, sizeof(fingerPos));
      for (int i = 0; i < 10; i++){
        fingerPosCopy[i] = fingerPos[i];
      }
      #if ESP32_DUAL_CORE_SET
      fingerPosLock->unlock();
      #endif
      /*
      Serial.println((String)sinTest + " " + (String)cosTest + " " + 
      (String)sinMinTest + " " + (String)sinMaxTest + " " + 
      (String)cosMinTest + " " + (String)cosMaxTest + " " + (String)fingerPosCopy[target] + " " + 
      (String)minFingersTest + " " + (String)maxFingersTest + " " + (String)totalAngleTest + " " + 
      (String)totalOffsetTest + " " + (String)angleRawTest + " " + 
      (String)mainMicros + " " + (String)fullLoopTime
      );
      */
      //Serial.println((String)sinTest + ", " + (String)sinMinTest + ", " + (String)sinMaxTest + ", " + (String)sinCalibTest);
    }
    //Serial.println("TotalLocks: " + String(totalLocks));
   //totalLocks = 0;
    comm->output(encode(fingerPosCopy, getJoyX(), getJoyY(), joyButton, triggerButton, aButton, bButton, grabButton, pinchButton, calibButton, menuButton));
    #if USING_FORCE_FEEDBACK
      char received[100];
      if (comm->readData(received)){
        int hapticLimits[5];
        //This check is a temporary hack to fix an issue with haptics on v0.5 of the driver, will make it more snobby code later
        if(String(received).length() >= 10) {
           decodeData(received, hapticLimits);
           writeServoHaptics(hapticLimits); 
        }
      }
    #endif
    delay(LOOP_TIME);
    //Serial.println("Main: " + String(mainMicros) + " Main Avg: " + String(mainMicrosTotal/mainloops) + " Side: " + String(fullLoopTime) + " Side Avg: " + String(fullLoopTotal/threadLoops) + " Lock: " + String(lockTime) + " Lock avg: " + String(lockTimeTotal/lockLoops) );
  }
}
