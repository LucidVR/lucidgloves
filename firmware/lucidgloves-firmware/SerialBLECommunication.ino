//only compiles if BLE is set because it won't compile for a non-compatible board
#if COMMUNICATION == COMM_BLE
#include "ArduinoBLE.h"
class BLECommunication : public ICommunication {
  private:
    bool m_isOpen;
    BLECharacteristic m_tx;
    BLECharacteristic m_rx;
    BLEService m_serial;
    
  public:
    BLECommunication() :
      m_isOpen(false),
      m_tx(BLE_TX_UUID, BLERead | BLENotify, 75),
      m_rx(BLE_RX_UUID, BLEWrite | BLEWriteWithoutResponse, 75),
      m_serial(BLE_SERVICE_UUID) {}

    bool isOpen(){
      return m_isOpen;
    }

    void start(){
      Serial.begin(115200);
  
      BLE.begin();

      BLE.setLocalName(BLE_DEVICE_NAME);
      BLE.setAdvertisedService(m_serial);
      m_serial.addCharacteristic(m_tx);
      m_serial.addCharacteristic(m_rx);
      BLE.addService(m_serial);

      int initialFlexion[10] = { 0 };
      char* encoded = encode(initialFlexion, 0, 0, false, false, false, false, false, false, false, false);
      m_tx.writeValue(encoded, strlen(encoded));

      BLE.advertise();

      Serial.println("The device started, now you can pair it with bluetooth!");
      m_isOpen = true;
    }

    void output(char* data){
      m_tx.writeValue(data);
    }

    bool readData(char* input){
      if (input == NULL) {
        return false;
      }
      strcpy(input, reinterpret_cast<const char*>(m_rx.value()));
      return strlen(input) > 0;
    }
};
#endif
