#pragma once

#include "IEncoding.h"
#include "Config.h"

class LegacyEncoding : public IEncoding {
public:
    char* encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib, bool menu) override;
    DecodedData decodeData(char* stringToDecode) override;
};
