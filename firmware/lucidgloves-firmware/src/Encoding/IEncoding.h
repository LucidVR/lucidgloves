#pragma once
#include "../Util/DataStructs.h"

// Interface for encoding
class IEncoding {
public:
    virtual char* encode(int* flexion, int joyX, int joyY, bool joyClick, 
                         bool triggerButton, bool aButton, bool bButton, 
                         bool grab, bool pinch, bool calib, bool menu) = 0;

    virtual DecodedData decodeData(char* stringToDecode) = 0;
};
