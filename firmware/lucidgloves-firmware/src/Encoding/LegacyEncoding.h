#pragma once

#include "IEncoding.h"
#include "Config.h"

class LegacyEncoding : public IEncoding {
public:
    void encode(OutboundData data, char* stringToEncode) override;
    DecodedData decodeData(char* stringToDecode) override;
};
