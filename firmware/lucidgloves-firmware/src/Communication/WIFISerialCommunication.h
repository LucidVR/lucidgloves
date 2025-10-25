#pragma once
#include "ICommunication.h"
#include "../../Config.h"

#if COMMUNICATION == COMM_WIFISERIAL
#include <WiFi.h>
#include <HTTPClient.h>

private:
    bool m_isOpen;
    WiFiClient client;

    void connect();

public:
    WIFISerialCommunication();

    bool isOpen();

    void start();

    void output(char *data);

    bool readData(char *input);
};
#endif