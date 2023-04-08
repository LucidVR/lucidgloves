//Advanced settings, only for the pros XD

#define LOOP_TIME 4 //How much time between data sends (ms), set to 0 for a good time :)
#define CALIBRATION_LOOPS -1//How many loops should be calibrated. Set to -1 to always be calibrated.

//Comm defines, no touchy
#define COMM_SERIAL 0
#define COMM_BTSERIAL 1
#define COMM_BLE 2

#define BLE_SERVICE_UUID "090b69e6-d509-4c32-8b20-5f8b947b253a"
#define BLE_TX_UUID "0eac19b9-5441-40bc-afca-cffb4380714d"
#define BLE_RX_UUID "54cd1674-a8aa-4b15-ac74-361b0084877f"

//Encoding
#define ENCODING 1
#define ENCODE_LEGACY 0
#define ENCODE_ALPHA  1

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


//ANALOG_MAX OVERRIDE:
//uncomment and set as needed (only touch if you know what you are doing)
//#define ANALOG_MAX 4095 

#ifndef ANALOG_MAX
#error "This board doesn't have an auto ANALOG_MAX assignment, please set it manually by uncommenting ANALOG_MAX OVERRIDE!"
#endif

//Filtering and clamping analog inputs
#define CLAMP_ANALOG_MAP true //clamp the mapped analog values from 0 to ANALOG_MAX

// Enable and set min and max to match your sensor's expected raw value range
// This discards any spurious values outside of the useful range
#define CLAMP_FLEXION false  //clamp the raw flexion values
#define CLAMP_MIN 0  //the minimum value from the flexion sensors
#define CLAMP_MAX ANALOG_MAX  //the maximum value from the flexion sensors

// You must install RunningMedian library to use this feature
// https://www.arduino.cc/reference/en/libraries/runningmedian/
#define ENABLE_MEDIAN_FILTER false //use the median of the previous values, helps reduce noise
#define MEDIAN_SAMPLES 20
