/*
 * LucidGloves Firmware Version 2
 * Author: Lucas_VRTech - LucidVR
 * lucidvrtech.com
 */
//This is the configuration file, main structure in _main.ino
//CONFIGURATION SETTINGS:
#define DEBUG_LED LED_BUILTIN
#define COMMUNICATION COMM_SERIAL //Which communication protocol to use

#define LOOP_TIME 4 //How much time between data sends (ms), set to 0 for a good time :)
#define CALIBRATION_LOOPS 5000//How many loops should be calibrated. Set to -1 to always be calibrated.

#define COMM_SERIAL 0   //serial over USB
  #define SERIAL_BAUD_RATE 115200
  
#define COMM_BTSERIAL 1 //serial over Bluetooth (Work in progress)
  #define BTSERIAL_DEVICE_NAME "ESP32test"

//PINS CONFIGURATION 
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

//ANALOG INPUT CONFIG
#define ANALOG_MAX 1023   //Set to 1023 on Arduino, 4095 on ESP32
#define FLIP_POTS  false  //Flip values from potentiometers (for fingers!) if they are backwards

//Gesture enables, make false to use button override
#define TRIGGER_GESTURE true
#define GRAB_GESTURE    true
#define PINCH_GESTURE   true

//joystick configuration
#define JOYSTICK_BLANK true
#define JOY_FLIP_X false
#define JOY_FLIP_Y false

#define NO_THUMB false //If for some reason you don't want to track the thumb
