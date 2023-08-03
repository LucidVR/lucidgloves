#include "LegacyEncoding.h"
#include <Arduino.h>
char* LegacyEncoding::encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib, bool menu){
  static char stringToEncode[75];
  
  sprintf(stringToEncode, "%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d\n", 
  flexion[0], flexion[1], flexion[2], flexion[3], flexion[4],
  joyX, joyY, joyClick,
  triggerButton, aButton, bButton, grab, pinch
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
