#include "Main.h"
#include "Communication/SerialCommunication.h"
#include "Communication/BTSerialCommunication.h"
#include "Encoding/AlphaEncoding.h"
#include "Encoding/LegacyEncoding.h"
#include "Util/DataStructs.h"

#define ALWAYS_CALIBRATING CALIBRATION_LOOPS == -1
#define CALIB_OVERRIDE false
#if USING_CALIB_PIN && COMMUNICATION == COMM_SERIAL && PIN_CALIB == 0 && !CALIB_OVERRIDE
  #error "You can't set your calibration pin to 0 over usb. You can calibrate with the BOOT button when using bluetooth only. Set CalibOverride to true to override this."
#endif

Main::Main() {
  // Constructor code here
}

void Main::setup() {
  pinMode(32, INPUT_PULLUP);
  pinMode(DEBUG_LED, OUTPUT);
  digitalWrite(DEBUG_LED, HIGH); 

  #if COMMUNICATION == COMM_SERIAL
    comm = new SerialCommunication();
  #elif COMMUNICATION == COMM_BTSERIAL
    comm = new BTSerialCommunication();
  #else
    #error "Communication not set."
  #endif 

  #if ENCODING == ENCODE_ALPHA
    encoding = new AlphaEncoding();
  #elif ENCODING == ENCODE_LEGACY
    encoding = new LegacyEncoding();
  #else
    #error "Encoding not set."
  #endif

  
  comm->start();

  input.setupInputs();

  #if USING_FORCE_FEEDBACK
    haptics.setupServoHaptics();  
  #endif
  
  #if ESP32_DUAL_CORE_SET
    xTaskCreatePinnedToCore(
      Main::getInputsWrapper, /* Function to implement the task */
      "Get_Inputs", /* Name of the task */
      10000,  /* Stack size in words */
      this,  /* Task input parameter */
      tskIDLE_PRIORITY,  /* Priority of the task */
      &Task1,  /* Task handle. */
      0); /* Core where the task should run */
  #endif
}

void Main::loop() {
  
  if (comm->isOpen()){

    #if USING_CALIB_PIN
    data.calib = input.getButton(PIN_CALIB) != INVERT_CALIB;
    if (data.calib)
      loops = 0;
    #else
    data.calib = false;
    #endif
    if (loops < CALIBRATION_LOOPS || ALWAYS_CALIBRATING){
      calibrate = true;
      loops++;
    }
    else{
      calibrate = false;
    }

    #if !ESP32_DUAL_CORE_SET
      input.getFingerPositions(calibrate, data.calib, fingerPos);
    #endif
    data.joyClick = input.getButton(PIN_JOY_BTN) != INVERT_JOY;

    #if TRIGGER_GESTURE
    data.triggerButton = gesture.triggerGesture(fingerPos);
    #else
    data.triggerButton = input.getButton(PIN_TRIG_BTN) != INVERT_TRIGGER;
    #endif

    data.aButton = input.getButton(PIN_A_BTN) != INVERT_A;
    data.bButton = input.getButton(PIN_B_BTN) != INVERT_B;

    #if GRAB_GESTURE
    data.grab = gesture.grabGesture(fingerPos);
    #else
    data.grab = input.getButton(PIN_GRAB_BTN) != INVERT_GRAB;
    #endif

    #if PINCH_GESTURE
    data.pinch = gesture.pinchGesture(fingerPos);
    #else
    data.pinch = input.getButton(PIN_PNCH_BTN) != INVERT_PINCH;
    #endif

    int fingerPosCopy[10];
    int mutexTimeDone;
    data.menu = input.getButton(PIN_MENU_BTN) != INVERT_MENU;
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
      
    }

    memcpy(data.fingers, fingerPosCopy, 5 * sizeof(int));
    data.joyX = input.getJoyX();
    data.joyY = input.getJoyY();

    static char encodedString[100] = {0};
    encoding->encode(data, encodedString);
    comm->output(encodedString);
    #if USING_FORCE_FEEDBACK
      static char received[100];
      if (comm->readData(received)){
        int hapticLimits[5];
        //This check is a temporary hack to fix an issue with haptics on v0.5 of the driver, will make it more snobby code later
        if(String(received).length() >= 5) {
           DecodedData recievedData = encoding->decodeData(received);
           haptics.writeServoHaptics(recievedData.servoValues); 
           if (recievedData.fields.specialCommandReceived){
            Serial.println("Special command recieved!!!");
              if (recievedData.command == "ClearData")
                input.clearFlags();
              else if (recievedData.command == "SaveInter")
                input.saveIntermediate();
              else if (recievedData.command == "SaveTravel")
                input.saveTravel();
           }
        }
      }
    #endif
    #if defined(ESP32)
      vTaskDelay(LOOP_TIME);
    #else
      delay(LOOP_TIME);
    #endif
  }
}


#if ESP32_DUAL_CORE_SET
void Main::getInputs(){
    for(;;){
      {
        fingerPosLock->lock();
        input.getFingerPositions(calibrate, data.calib, fingerPos); //Save finger positions in thread

        fingerPosLock->unlock();
      }
      threadLoops++;
      if (threadLoops%100 == 0){
        vTaskDelay(1); //keep watchdog fed
      }
      delayMicroseconds(1);
    }           
}

void Main::getInputsWrapper(void* _this) {
  // Cast the void* parameter back to a Main* and call getInputs on it
  static_cast<Main*>(_this)->getInputs();
}

#endif
