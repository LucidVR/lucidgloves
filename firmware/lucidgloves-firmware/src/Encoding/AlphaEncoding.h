#pragma once

#include "IEncoding.h"
#include "Config.h"

class AlphaEncoding : public IEncoding {
public:
    void encode(OutboundData data, char* stringToEncode) override;
    DecodedData decodeData(char* stringToDecode) override;
private:
    int getArgument(char* stringToDecode, char command);
};
