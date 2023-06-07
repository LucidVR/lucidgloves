#pragma once
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm_board_0 = Adafruit_PWMServoDriver(PWM_Board_0_I2C_ADDRESS, Wire);


int Initialize_PCA9685_Board()
{
  pwm_board_0.begin();
  pwm_board_0.setOscillatorFrequency(25000000);
  pwm_board_0.setPWMFreq(PWM_Board_0_PWM_FREQUENCY);  // Analog servos usually run at ~50 Hz updates
  Serial.println("PCA9685 Board Initialized ");
}


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
};


Servo::Servo()  //things break if this is gone
{}

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
    //Serial.println("Servo called!");
}
