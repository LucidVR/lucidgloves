//only compiles if needed
#if USING_FORCE_FEEDBACK && SERVO_INTERFACE == SERVO_DIRECT
  #pragma once
  #if defined(ESP32)
    #include <ESP32Servo.h>
  #else
    #include <Servo.h>
  #endif

class DirectServoConnection : public IServo {
  private:
    bool m_isReady;
        
  public:
    DirectServoConnection() {
      m_isReady = false;
    }

    bool isReady(){
      return m_isReady;
    }

    void InitServoInterface(){
      m_isReady = true;
    }
};
#endif
