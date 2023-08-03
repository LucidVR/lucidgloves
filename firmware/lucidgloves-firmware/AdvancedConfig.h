#pragma once
#include "src/Util/ConfigUtils.h"
//THIS FILE HAS SOME EXTRA SETTINGS, MAIN SETTINGS ARE IN Config.h

#define LOOP_TIME 1 //How much time between data sends (ms), set to 0 for a good time :)
#define CALIBRATION_LOOPS -1//How many loops should be calibrated. Set to -1 to always be calibrated.

//Encoding
#define ENCODING ENCODE_ALPHA

#define NUM_FINGERS 5

//Bluetooth advaned settings
#define BT_ECHO false//Should the bluetooth data be echoed over serial for debugging

//ESP32 Specific Settings
#define ESP32_DUAL_CORE true //Should inputs be handled on a separate core for communication for more accurate rotation counting

//Finger indeces (not used for legacy)
#define PINKY_IND 4
#define RING_IND 3
#define MIDDLE_IND 2
#define INDEX_IND 1
#define THUMB_IND 0

//Automatically set ANALOG_MAX depending on the microcontroller
#if defined(__AVR__)
#define ANALOG_MAX 1023
#elif defined(ESP32)
#define ANALOG_MAX 4095 
#endif


#define MULTIPLEXER_DELAY   5 //How many microseconds should be delayed between multiplexer reads


//ANALOG_MAX OVERRIDE:
//#define ANALOG_MAX 4095 //uncomment and set as needed

#ifndef ANALOG_MAX
#error "This board doesn't have an auto ANALOG_MAX assignment, please set it manually by uncommenting the line below ANALOG_MAX OVERRIDE in AdvancedConfig.h"
#endif

//Filtering and clamping analog inputs
#define CLAMP_ANALOG_MAP true //clamp the mapped analog values from 0 to ANALOG_MAX

// Enable and set min and max to match your sensor's expected raw value range
// This discards any spurious values outside of the useful range
#define CLAMP_SENSORS false  //clamp the raw sensor values
#define CLAMP_MIN 0  //the minimum value from the flexion sensors
#define CLAMP_MAX ANALOG_MAX  //the maximum value from the flexion sensors

// You must install RunningMedian library to use this feature
// https://www.arduino.cc/reference/en/libraries/runningmedian/
#define ENABLE_MEDIAN_FILTER false //use the median of the previous values, helps reduce noise
#define MEDIAN_SAMPLES 10

//intermediate filtering. Options are INTERFILTER_NONE, INTERFILTER_LIMITS (filter is only used for limit calib), INTERFILTER_ALL (filter all the way)
#define INTERFILTER_MODE INTERFILTER_LIMITS
#define INTERFILTER_SAMPLES 10

//ESP dual core hardware check
#if defined(ESP32) && ESP32_DUAL_CORE
  #define ESP32_DUAL_CORE_SET true
#endif
