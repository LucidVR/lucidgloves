//Advanced settings, only for the pros XD

#define LOOP_TIME 4 //How much time between data sends (ms), set to 0 for a good time :)
#define CALIBRATION_LOOPS -1//How many loops should be calibrated. Set to -1 to always be calibrated.

//Comm defines, no touchy
#define COMM_SERIAL 0   
#define COMM_BTSERIAL 1 

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
