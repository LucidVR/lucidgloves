#pragma once

#include "IEncoding.h"
#include "Config.h"

class AlphaEncoding : public IEncoding {
public:
    char* encode(OutboundData data) override;
    DecodedData decodeData(char* stringToDecode) override;
private:
    int getArgument(char* stringToDecode, char command);
};
