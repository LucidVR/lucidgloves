#pragma once
#include "../Util/DataStructs.h"




// Interface for encoding
class IEncoding {
public:
    virtual char* encode(OutboundData data) = 0;

    virtual DecodedData decodeData(char* stringToDecode) = 0;
};
