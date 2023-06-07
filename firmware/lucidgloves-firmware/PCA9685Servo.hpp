#pragma once
#include <Adafruit_PWMServoDriver.h>
#include "AdvancedConfig.h"

#define MIN_PULSE_WIDTH ServoMin_uS   //Sets the MIN_PULSE_WIDTH setting used by smooth stepping to your configured ServoMin (Default in esp32servo is 500)
#define MAX_PULSE_WIDTH ServoMax_uS   //Sets the Max_PULSE_WIDTH setting used by smooth stepping to your configured ServoMax (Default in esp32servo is 2500)

class Servo
{
public:
  Servo();
  int attach(int pin);            // input to match servo.h & esp32servo.h format
  void write(int value);          // Write as an angle (converted into microsecond pulse below)
  void writeMicroseconds(int value);  // Write to servo directly as an "X" microsecond pulse

private:
  int minMicroSeconds = ServoMin_uS;                  // microsecond value to move servo to 0* or fully retracted position  
  int maxMicroSeconds = ServoMax_uS;                  // microsecond value to move servo to 180* or whatever it's max rotation position is  
  int driverChannel = 0;                          // driverboard channel connected to the servo
  Adafruit_PWMServoDriver pwm_board_0;
};
