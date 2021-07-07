/*struct inputData {
  int* flexion;
  int joyX;
  int joyY;
  bool joyClick;
  bool triggerButton;
  bool aButton;
  bool bButton;
  bool grab;
  bool pinch;
};

struct outputData{
  int* hapticLimits;
};
*/

#if ENCODING == ENCODING_LEGACY //will be moved to its own manager in Firmware v4
//legacy encoding
char* encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib){
  static char stringToEncode[75];
  
  sprintf(stringToEncode, "%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d\n", 
  flexion[4], flexion[3], flexion[2], flexion[1], flexion[0],
  joyX, joyY, joyClick,
  triggerButton, aButton, bButton, grab, pinch
  );
  return stringToEncode;
}
//legacy decoding
void decodeData(char* stringToDecode, int* hapticLimits){
    byte index = 0;
    char* ptr = strtok(stringToDecode, "&");  // takes a list of delimiters
    while(ptr != NULL)
    {
        hapticLimits[index] = atoi(ptr);
        index++;
        ptr = strtok(NULL, "&");  // takes a list of delimiters
    }
}
#endif

#if ENCODING == ENCODE_ALPHA
//alphabetic encoding
char* encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib){
  static char stringToEncode[75];
  
  flexion[4], flexion[3], flexion[2], flexion[1], flexion[0],
  joyX, joyY, joyClick?"H":"",
  triggerButton?"I":"", aButton?"J":"", bButton?"K":"", grab?"L":"", pinch?"M":"", calib?"O":""
  );
  return stringToEncode;
}

//alphabetic decoding
void decodeData(char* stringToDecode, int* hapticLimits){
  hapticLimits[0] = getArgument(stringToDecode, 'A'); //thumb
  hapticLimits[1] = getArgument(stringToDecode, 'B'); //index
  hapticLimits[2] = getArgument(stringToDecode, 'C'); //middle
  hapticLimits[3] = getArgument(stringToDecode, 'D'); //ring
  hapticLimits[4] = getArgument(stringToDecode, 'E'); //pinky
}

int getArgument(char* stringToDecode, char command){
  char* start = strchr(stringToDecode, command);
  if (start == NULL)
    return -1;
  else
    return atoi(start + 1);
}

#endif
