char* encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch){
  static char stringToPrint[75];
  
  sprintf(stringToPrint, "%s&%s&%s&%s&%s&%d&%d&%d&%d&%d&%d&%d&%d\n", 
  debugi(flexion[4]), debugi(flexion[3]), debugi(flexion[2]), debugi(flexion[1]), debugi(flexion[0]),
  joyX, joyY, joyClick,
  triggerButton, aButton, bButton, grab, pinch
  );
  return stringToPrint;
}

String debugi(int thumb) {
  String s = String(thumb);
  while(s.length() < 4) {
    s = "0" + s;
  }
  return s;
}
