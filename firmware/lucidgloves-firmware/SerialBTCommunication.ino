//only compiles if BTSerial is set because it won't compile for a non-compatible board
#if COMMUNICATION == COMM_BTSERIAL
#include "BluetoothSerial.h"
class BTSerialCommunication : public ICommunication {
  private:
    bool m_isOpen;
    BluetoothSerial m_SerialBT;
    
  public:
    BTSerialCommunication() {
      m_isOpen = false;
    }

    bool isOpen(){
      return m_isOpen;
    }

    void start(){
      Serial.begin(115200);
      m_SerialBT.begin(BTSERIAL_DEVICE_NAME);
      Serial.println("The device started, now you can pair it with bluetooth!");
      m_isOpen = true;
    }

    void output(char* data){
      m_SerialBT.print(data);
    }

    bool readData(char* input){
      /*byte size = m_SerialBT.readBytesUntil('\n', input, 100);
      input[size] = NULL;*/
      String message = m_SerialBT.readStringUntil('\n');
      strcpy(input, message.c_str());
      return input != NULL && strlen(input) > 0;
    }
};
#endif
