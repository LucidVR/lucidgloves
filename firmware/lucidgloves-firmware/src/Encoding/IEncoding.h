#pragma once
#include "../Util/DataStructs.h"




// Interface for encoding
class IEncoding {
public:
    virtual void encode(OutboundData data, char* stringToEncode) = 0;

    virtual DecodedData decodeData(char* stringToDecode) = 0;
};
