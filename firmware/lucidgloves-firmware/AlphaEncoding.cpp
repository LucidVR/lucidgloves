#include "AlphaEncoding.h"

char* AlphaEncoding::encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib, bool menu){
  static char stringToEncode[75];
  int trigger = (flexion[1] > ANALOG_MAX/2) ? (flexion[1] - ANALOG_MAX/2) * 2:0;
  #if USING_SPLAY
  sprintf(stringToEncode, "A%dB%dC%dD%dE%dF%dG%dP%d%s%s%s%s%s%s%s%s(AB)%d(BB)%d(CB)%d(DB)%d(EB)%d\n", 
  flexion[0], flexion[1], flexion[2], flexion[3], flexion[4],
  joyX, joyY, trigger, joyClick?"H":"",
  triggerButton?"I":"", aButton?"J":"", bButton?"K":"", grab?"L":"", pinch?"M":"", menu?"N":"", calib?"O":"",
  flexion[5], flexion[6], flexion[7], flexion[8], flexion[9]
  );
  #else
  sprintf(stringToEncode, "A%dB%dC%dD%dE%dF%dG%dP%d%s%s%s%s%s%s%s%s\n", 
  flexion[0], flexion[1], flexion[2], flexion[3], flexion[4],
  joyX, joyY, trigger, joyClick?"H":"",
  triggerButton?"I":"", aButton?"J":"", bButton?"K":"", grab?"L":"", pinch?"M":"", menu?"N":"", calib?"O":""
  );
  #endif
  return stringToEncode;
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
