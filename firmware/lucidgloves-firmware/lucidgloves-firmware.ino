/*
 * LucidGloves Firmware Version 2
 * Author: Lucas_VRTech - LucidVR
 * lucidvrtech.com
 */
//This is the configuration file, main structure in _main.ino
//CONFIGURATION SETTINGS:
#define COMMUNICATION COMM_WIFISERIAL //Which communication protocol to use

#define LOOP_TIME 50 //How much time between data sends (ms), set to 0 for a good time :)
#define CALIBRATION_LOOPS -1//How many loops should be calibrated. Set to -1 to always be calibrated.

#define COMM_SERIAL 0   //serial over USB
  #define SERIAL_BAUD_RATE 115200
  
#define COMM_BTSERIAL 1 //serial over Bluetooth (Work in progress)
  #define BTSERIAL_DEVICE_NAME "lucidgloves-right"

#define COMM_WIFISERIAL 2
  #define WIFISERIAL_SSID "FRITZ!Box 7362 SL"
  #define WIFISERIAL_PASSWORD "86619567583490915352"
  #define WIFISERIAL_SERVER "192.168.0.48"
  #define WIFISERIAL_SERVER_PORT 9002

//ANALOG INPUT CONFIG
#define ANALOG_MAX 4095   //Set to 1023 on Arduino, 4095 on ESP32. Make sure is the same as driver setting.
#define FLIP_POTS  true  //Flip values from potentiometers (for fingers!) if they are backwards

//Gesture enables, make false to use button override
#define TRIGGER_GESTURE true
#define GRAB_GESTURE    true
#define PINCH_GESTURE   true

//joystick configuration
#define JOYSTICK_BLANK false //make true if not using the joystick
#define JOY_FLIP_X false
#define JOY_FLIP_Y false
#define JOYSTICK_DEADZONE 10 //deadzone in the joystick to prevent drift (in percent)

#define NO_THUMB false //If for some reason you don't want to track the thumb

#define USING_CALIB_PIN false //When PIN_CALIB is shorted (or it's button pushed) it will reset calibration if this is on.

//PINS CONFIGURATION 
#if defined(__AVR__)
  //(This configuration is for Arduino Nano so make sure to change if you're on another board)
  #define PIN_PINKY     A0
  #define PIN_RING      A1
  #define PIN_MIDDLE    A2
  #define PIN_INDEX     A3
  #define PIN_THUMB     A4
  #define PIN_JOY_X     A6
  #define PIN_JOY_Y     A7
  #define PIN_JOY_BTN   7 
  #define PIN_A_BTN     8 
  #define PIN_B_BTN     9
  #define PIN_TRIG_BTN  10 //unused if gesture set
  #define PIN_GRAB_BTN  11 //unused if gesture set
  #define PIN_PNCH_BTN  12 //unused if gesture set
  #define PIN_CALIB     13 //button for recalibration
  #define DEBUG_LED     LED_BUILTIN
#elif defined(ESP32)
  //(This configuration is for ESP32 DOIT V1 so make sure to change if you're on another board)
  #define PIN_PINKY     25
  #define PIN_RING      33
  #define PIN_MIDDLE    32
  #define PIN_INDEX     35
  #define PIN_THUMB     34
  #define PIN_JOY_X     26
  #define PIN_JOY_Y     27
  #define PIN_JOY_BTN   26
  #define PIN_A_BTN     27 
  #define PIN_B_BTN     14
  #define PIN_TRIG_BTN  12 //unused if gesture set
  #define PIN_GRAB_BTN  13 //unused if gesture set
  #define PIN_PNCH_BTN  23 //unused if gesture set
  #define PIN_CALIB     12 //button for recalibration
  #define DEBUG_LED 2
#endif
