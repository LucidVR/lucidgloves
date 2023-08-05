//only compiles if needed
#if USING_FORCE_FEEDBACK && SERVO_INTERFACE == SERVO_PCA9685
#include "I2C.h"

class PCA9685ServoConnection : public IServo 
{
  private:
    bool m_isReady;
        
  public:
    PCA9685ServoConnection() {
      m_isReady = false;
    }

    bool isReady(){
      return m_isReady;
    }

    void InitServoInterface(){
      Setup_I2C();
      Initialize_PCA9685_Board();
      m_isReady = true;
    }
};
#endif
