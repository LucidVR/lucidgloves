char* encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch){
  static char stringToPrint[75];
  
  sprintf(stringToPrint, "%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d\n", 
  flexion[4], flexion[3], flexion[2], flexion[1], flexion[0],
  joyX, joyY, joyClick,
  triggerButton, aButton, bButton, grab, pinch
  );
  return stringToPrint;
}
