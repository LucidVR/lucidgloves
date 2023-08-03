#pragma once
#include "ICommunication.h"
#include "../../Config.h"

#if COMMUNICATION == COMM_BTSERIAL
#include "BluetoothSerial.h"

class BTSerialCommunication : public ICommunication {
private:
    bool m_isOpen;
    BluetoothSerial m_SerialBT;
    
public:
    BTSerialCommunication();

    bool isOpen() override;

    void start() override;

    void output(char* data) override;

    bool readData(char* input) override;
};
#endif
