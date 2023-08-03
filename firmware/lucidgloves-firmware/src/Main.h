#pragma once

#include <mutex>
#include "Controller/Gesture.h"
#include "Controller/Haptics.h"
#include "Encoding/AlphaEncoding.h"
#include "Encoding/LegacyEncoding.h"
#include "Communication/SerialCommunication.h"
#include "Communication/BTSerialCommunication.h"
#include "../AdvancedConfig.h"
#include "Util/ConfigUtils.h"
#include "Controller/InputManager.h"


class Main {
public:
  Main();
  void setup();
  void loop();

  #if ESP32_DUAL_CORE_SET
  static void getInputsWrapper(void* _this);
  #endif

private:

  ICommunication* comm;
  IEncoding* encoding;
  Haptics haptics;
  Gesture gesture;
  InputManager input;

  bool calibrate = false;
  bool calibButton = false;
  int fingerPos[10] = {0,0,0,0,0,0,0,0,0,0};
  int loops = 0;

  #if ESP32_DUAL_CORE_SET
  void getInputs();
  ordered_lock* fingerPosLock = new ordered_lock();
  TaskHandle_t Task1;
  int threadLoops = 1;
  #endif

};
