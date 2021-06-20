//Interface for communication

class ICommunication {

  public:
    virtual bool isOpen() = 0;

    virtual void start() = 0;

    virtual void output(char* data) = 0;

    virtual bool readData(char* input) = 0;
};
