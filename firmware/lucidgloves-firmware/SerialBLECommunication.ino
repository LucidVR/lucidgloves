//only compiles if BLESerial is set because it won't compile for a non-compatible board
#if COMMUNICATION == COMM_BLESERIAL
#include <NimBLEDevice.h>
#define   CONFIG_BT_NIMBLE_PINNED_TO_CORE   1 //Pins NimBLE to core 1
static NimBLEServer* pServer;
class BLESerialCommunication : public ICommunication {
  private:
    bool m_isOpen;

  public:
    BLESerialCommunication() {
      m_isOpen = false;
    }

    bool isOpen(){
      return m_isOpen;
    }

    void start(){
      NimBLEDevice::init(BTSERIAL_DEVICE_NAME);

      pServer = NimBLEDevice::createServer();
      NimBLEService *pService = pServer->createService("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"); //Main service
      NimBLECharacteristic *rxCharacteristic = pService->createCharacteristic("6E400002-B5A3-F393-E0A9-E50E24DCCA9E",NIMBLE_PROPERTY::WRITE);
      NimBLECharacteristic *txCharacteristic = pService->createCharacteristic("6E400003-B5A3-F393-E0A9-E50E24DCCA9E",NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
      pService->start();

      NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising(); // create advertising instance
      pAdvertising->addServiceUUID(pService->getUUID()); // tell advertising the UUID of our service
      pAdvertising->start(); // start advertising
      
      #if BT_ECHO
      Serial.begin(SERIAL_BAUD_RATE);
      Serial.println("The device started, now you can pair it with bluetooth!");
      #endif
      m_isOpen = true;
    }

    void output(char* data){
      if(pServer->getConnectedCount()) {
        NimBLEService* pSvc = pServer->getServiceByUUID("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
        if(pSvc) {
            NimBLECharacteristic* qChr = pSvc->getCharacteristic("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");
            if(qChr) {
                qChr->setValue(String(data));
            }
        }
      }
      //else
      //vTaskDelay(1); //keep watchdog fed
      #if BT_ECHO
      Serial.print(data);
      Serial.flush();
      #endif
    }

    bool readData(char* input){
      /*byte size = m_SerialBT.readBytesUntil('\n', input, 100);
      input[size] = NULL;*/
      if(pServer->getConnectedCount()) {
        NimBLEService* pSvc = pServer->getServiceByUUID("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
        if(pSvc) {
          NimBLECharacteristic* qChr = pSvc->getCharacteristic("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
          if(qChr) {
            //String message = qChr->getValue();
            strcpy(input, qChr->getValue().c_str());
          }
        }
      }
      return input != NULL && strlen(input) > 0;
    }
};
#endif
