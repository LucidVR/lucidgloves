#include "AlphaEncoding.h"
#include <Arduino.h>
void AlphaEncoding::encode(OutboundData data, char* stringToEncode){
  int trigger = (data.fingers[1] > ANALOG_MAX/2) ? (data.fingers[1] - ANALOG_MAX/2) * 2:0;
  char splayString[30] = "";
  #if USING_SPLAY
  sprintf(splayString, "(AB)%d(BB)%d(CB)%d(DB)%d(EB)%d", 
  data.splay[0], data.splay[1], data.splay[2], data.splay[3], data.splay[4]
  );
  #endif
  snprintf(stringToEncode, 100, "A%dB%dC%dD%dE%dF%dG%dP%d%s%s%s%s%s%s%s%s%s\n", 
  data.fingers[0], data.fingers[1], data.fingers[2], data.fingers[3], data.fingers[4],
  data.joyX, data.joyY, trigger, data.joyClick?"H":"",
  data.triggerButton?"I":"", data.aButton?"J":"", data.bButton?"K":"", data.grab?"L":"", data.pinch?"M":"", data.menu?"N":"", data.calib?"O":"",
  splayString);
}
DecodedData AlphaEncoding::decodeData(char* stringToDecode) {
  DecodedData decodedData = {};

  if (strchr(stringToDecode, 'Z') != NULL) {
    for (int i = 0; i < NUM_SPECIAL_COMMANDS; i++) {
      if (strstr(stringToDecode, SPECIAL_COMMANDS[i]) != NULL) {
        decodedData.command = SPECIAL_COMMANDS[i];
        decodedData.fields.specialCommandReceived = true;
        return decodedData;
      }
    }
  }

  for (int i = 0; i < NUM_FINGERS; i++) {
    int value = getArgument(stringToDecode, 'A' + i);
    if (value != -1) {
      decodedData.servoValues[i] = value;
      decodedData.fields.servoValuesReceived[i] = true;
    }
  }

  return decodedData;
}


int AlphaEncoding::getArgument(char* stringToDecode, char command){
  char* start = strchr(stringToDecode, command);
  if (start == NULL)
    return -1;
  else
    return atoi(start + 1);
}
