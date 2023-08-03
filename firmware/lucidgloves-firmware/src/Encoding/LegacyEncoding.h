#pragma once

#include "IEncoding.h"
#include "Config.h"

class LegacyEncoding : public IEncoding {
public:
    char* encode(OutboundData data) override;
    DecodedData decodeData(char* stringToDecode) override;
};
