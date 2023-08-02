#pragma once

#include <mutex>
#include "Gesture.h"
#include "Haptics.h"
#include "AlphaEncoding.h"
#include "LegacyEncoding.h"
#include "SerialCommunication.h"
#include "BTSerialCommunication.h"
#include "AdvancedConfig.h"
#include "ConfigUtils.h"
#include "InputManager.h"


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
  int* fingerPos = (int[]){0,0,0,0,0,0,0,0,0,0};
  int loops = 0;

  #if ESP32_DUAL_CORE_SET
  void getInputs();
  ordered_lock* fingerPosLock = new ordered_lock();
  TaskHandle_t Task1;
  int threadLoops = 1;
  #endif

};
