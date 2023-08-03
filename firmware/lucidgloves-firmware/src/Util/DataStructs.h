#pragma once
#include "../../AdvancedConfig.h"

const char* const SPECIAL_COMMANDS[] = {
    "SaveInter",
    "SaveTravel",
    "ClearData"
    // Add more commands as needed
};

//NUM_SPECIAL_COMMANDS can be defined this way because all char* are pointers of the same size
const int NUM_SPECIAL_COMMANDS = sizeof(SPECIAL_COMMANDS) / sizeof(SPECIAL_COMMANDS[0]);

struct ReceivedFields {
    bool servoValuesReceived[NUM_FINGERS];
    bool specialCommandReceived;
};

struct DecodedData {
    ReceivedFields fields;
    int servoValues[NUM_FINGERS];
    const char* command;
};

struct OutboundData {
    int fingers[NUM_FINGERS];
    int joyX;
    int joyY;
    bool joyClick;
    bool triggerButton;
    bool aButton;
    bool bButton;
    bool grab;
    bool pinch;
    bool calib;
    bool menu;

    #if USING_SPLAY
    int splay[NUM_FINGERS];
    #endif
};