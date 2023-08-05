//Interface for Servo Connections

class IServo {

  public:
    virtual bool isReady() = 0;

    virtual void InitServoInterface() = 0;
};
