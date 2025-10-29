#pragma once
#include "ICommunication.h"
#include "../../Config.h"

#if COMMUNICATION == COMM_WIFISERIAL
#include <WiFi.h>
#include <HTTPClient.h>

class WIFISerialCommunication : public ICommunication {
private:
    bool m_isOpen;
    WiFiClient client;

    void connect();

public:
    WIFISerialCommunication();

    bool isOpen() override;

    void start() override;

    void output(char *data) override;

    bool readData(char *input) override;
};
#endif