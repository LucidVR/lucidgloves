#pragma once
#include "ICommunication.h"
#include "config.h"
#include <Arduino.h>

class SerialCommunication : public ICommunication {
private:
    bool m_isOpen;

public:
    SerialCommunication();

    bool isOpen() override;

    void start() override;

    void output(char* data) override;

    bool readData(char* input) override;
};
