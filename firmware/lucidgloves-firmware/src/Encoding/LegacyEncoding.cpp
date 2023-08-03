#include "LegacyEncoding.h"
#include <Arduino.h>
char* LegacyEncoding::encode(OutboundData data){
  static char stringToEncode[75];
  
  sprintf(stringToEncode, "%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d\n", 
  data.fingers[0], data.fingers[1], data.fingers[2], data.fingers[3], data.fingers[4],
  data.joyX, data.joyY, data.joyClick,
  data.triggerButton, data.aButton, data.bButton, data.grab, data.pinch
  );
  return stringToEncode;
}

DecodedData LegacyEncoding::decodeData(char* stringToDecode) {
    DecodedData decodedData = {};

    byte index = 0;
    char* ptr = strtok(stringToDecode, "&");
    while(ptr != NULL && index < NUM_FINGERS)
    {
        decodedData.servoValues[index] = atoi(ptr);
        decodedData.fields.servoValuesReceived[index] = true;
        index++;
        ptr = strtok(NULL, "&");
    }

    return decodedData;
}
