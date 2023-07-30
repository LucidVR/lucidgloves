#pragma once
#include "AdvancedConfig.h"

struct ReceivedFields {
    bool servoValuesReceived[NUM_FINGERS];
    bool specialCommandReceived;
};

struct DecodedData {
    ReceivedFields fields;
    int servoValues[NUM_FINGERS];
    SpecialCommands command;
};

enum SpecialCommands : uint8_t {
    NO_COMMAND = 0,
    CLEAR_FLAGS,
    SAVE_INTERMEDIATE,
    SAVE_TRAVEL,
};
