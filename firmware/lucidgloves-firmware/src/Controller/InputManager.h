#pragma once

#include <EEPROM.h>
#include "../../Config.h"
#include "../../AdvancedConfig.h"


#if (ENABLE_MEDIAN_FILTER || ((INTERFILTER_MODE != INTERFILTER_NONE) && (FLEXION_MIXING != MIXING_NONE)))
  #include <RunningMedian.h>
#endif

class InputManager
{
public:
    InputManager();
    void setupInputs();
    int analogPinRead(int pin);
    #if USING_MULTIPLEXER
    int readMux(byte pin);
    #endif
    void getFingerPositions(bool calibrating, bool reset, int* fingerPos);
    int analogReadDeadzone(int pin);
    int getJoyX();
    int getJoyY();
    bool getButton(byte pin);
    #if FLEXION_MIXING == MIXING_SINCOS
    int sinCosMix(int sinPin, int cosPin, int i);
    #endif
    void saveTravel();
    void saveIntermediate();
    void clearFlags();
    bool isSavedLimits();
    bool isSavedIntermediate();
    void loadTravel();
    void loadIntermediate();
private:
    // Add your private variables here
    bool savedInter = false;
    bool savedTravel = false;

    int maxFingers[2* NUM_FINGERS] = {0,0,0,0,0,0,0,0,0,0};
    int minFingers[2* NUM_FINGERS] = {ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX};
    int maxTravel[2*NUM_FINGERS] = {ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX};
    
    #if FLEXION_MIXING == MIXING_SINCOS
    int sinMin[NUM_FINGERS] = {ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX};
    int sinMax[NUM_FINGERS] = {0,0,0,0,0};

    int cosMin[NUM_FINGERS] = {ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX};
    int cosMax[NUM_FINGERS] = {0,0,0,0,0};

    bool atanPositive[NUM_FINGERS] = {true, true, true, true, true};


    int totalOffset1[NUM_FINGERS] = {0,0,0,0,0};
    #endif

    #if ENABLE_MEDIAN_FILTER
  RunningMedian rmSamples[2* NUM_FINGERS] = {
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

  #if ((INTERFILTER_MODE != INTERFILTER_NONE) && (FLEXION_MIXING == MIXING_SINCOS))
  RunningMedian sinSamples[NUM_FINGERS] = {
      RunningMedian(INTERFILTER_SAMPLES),
      RunningMedian(INTERFILTER_SAMPLES),
      RunningMedian(INTERFILTER_SAMPLES),
      RunningMedian(INTERFILTER_SAMPLES),
      RunningMedian(INTERFILTER_SAMPLES)
  };

    RunningMedian cosSamples[NUM_FINGERS] = {
      RunningMedian(INTERFILTER_SAMPLES),
      RunningMedian(INTERFILTER_SAMPLES),
      RunningMedian(INTERFILTER_SAMPLES),
      RunningMedian(INTERFILTER_SAMPLES),
      RunningMedian(INTERFILTER_SAMPLES)
  };
  #endif



};
