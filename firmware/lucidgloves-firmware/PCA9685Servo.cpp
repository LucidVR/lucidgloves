#pragma once
#include "PCA9685Servo.hpp"

Servo::Servo()
{
  pwm_board_0.begin();
  pwm_board_0.setOscillatorFrequency(25000000);
  pwm_board_0.setPWMFreq(PWM_Board_0_PWM_FREQUENCY);  // Analog servos usually run at ~50 Hz updates
  Serial.println("PCA9685 Board Initialized ");
}

int Servo::attach(int pin)
{
  this->driverChannel = pin;
}

void Servo::write(int value)
{
  {
  if (value < 0)
      value = 0;
  else if (value > 180)
      value = 180;

  value = map(value, 0, 180, this->minMicroSeconds, this->maxMicroSeconds);
  }
  this->writeMicroseconds(value);
}

void Servo::writeMicroseconds(int value){
    pwm_board_0.writeMicroseconds(this->driverChannel, value);
}
