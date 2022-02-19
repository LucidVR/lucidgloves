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
char* encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib, bool menu){
  static char stringToEncode[75];
  
  sprintf(stringToEncode, "%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d\n", 
  flexion[0], flexion[1], flexion[2], flexion[3], flexion[4],
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
char* encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib, bool menu){
  static char stringToEncode[75];
  sprintf(stringToEncode, "A%dB%dC%dD%dE%dF%dG%d%s%s%s%s%s%s%s%s\n",
  flexion[0], flexion[1], flexion[2], flexion[3], flexion[4],
  joyX, joyY, joyClick?"H":"",
  triggerButton?"I":"", aButton?"J":"", bButton?"K":"", grab?"L":"", pinch?"M":"", menu?"N":"", calib?"O":""
  );
  return stringToEncode;
}
#endif

#if ENCODING == ENCODE_ALPHA_FULL_JOINT
// Full Joint encoding
int encode(char* output, char** finger, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib, bool menu){
  return sprintf(output, "%s%s%s%s%sF%dG%d%s%s%s%s%s%s%s%s\n",
                 finger[0], finger[1], finger[2], finger[3], finger[4],
                 joyX, joyY,
                 joyClick?"H":"", triggerButton?"I":"", aButton?"J":"", bButton?"K":"", grab?"L":"", pinch?"M":"", menu?"N":"", calib?"O":"");
}

enum FingerPrefix : char {
  Thumb = 'A',
  Index = 'B',
  Middle = 'C',
  Ring = 'D',
  Pinky = 'E'
};

int encode_thumb(char* output, int* values) {
  // Values should be joints 0, 1, 2, Splay.
  return sprintf(output, "(AAA)%d(AAB)%d(AAC)%d(AB)%d", values[0], values[2], values[2], values[3]);
}

int encode_finger(int finger, char* output, int* values) {
  FingerPrefix f = (FingerPrefix)(FingerPrefix::Thumb + (char)finger);
  // Values should be joints 0, 1, 2, 3, Splay.
  return sprintf(output, "(%cAA)%d(%cAB)%d(%cAC)%d(%cB)%d", f, values[0], f, values[2], f, values[2], f, values[3], f, values[4]);
}

#endif


#if ENCODING == ENCODE_ALPHA || ENCODING == ENCODE_ALPHA_FULL_JOINT

//legacy decoding
void decodeData(char* stringToDecode, int* hapticLimits){
  hapticLimits[0] = getArgument(stringToDecode, 'A'); //thumb
  hapticLimits[1] = getArgument(stringToDecode, 'B'); //index
  hapticLimits[2] = getArgument(stringToDecode, 'C'); //middle
  hapticLimits[3] = getArgument(stringToDecode, 'D'); //ring
  hapticLimits[4] = getArgument(stringToDecode, 'E'); //pinky
  //Serial.println("Haptic: "+ (String)hapticLimits[0] + " " + (String)hapticLimits[1] + " " + (String)hapticLimits[2] + " " + (String)hapticLimits[3] + " " + (String)hapticLimits[4] + " ");
}

int getArgument(char* stringToDecode, char command){
  char* start = strchr(stringToDecode, command);
  if (start == NULL)
    return -1;
  else
    return atoi(start + 1);
}

#endif
