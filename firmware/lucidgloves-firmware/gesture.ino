bool grabGesture(int *flexion, int *savedHapticLimits){
  #if FFB_SCALE_GRAB //if we're dynamically scaling for haptics
  int total = 0;
  for (int i = 0; i <5; i++){
    int xServo = savedHapticLimits[i] * 0.9; //10% wiggle room to prevent objects stuck in hand
    int xfscaled = flexion[i] * (1- xServo/ANALOG_MAX);
    total += xfscaled;
  }
  int avg = total/5;
  return avg <= ANALOG_MAX/2 ? 0:1;
  #else //classic grab gesture
  return (flexion[PINKY_IND] + flexion[RING_IND] + flexion[MIDDLE_IND] + flexion[INDEX_IND]) / 4 <= ANALOG_MAX/2 ? 0:1;
  #endif
}

bool pinchGesture(int *flexion){
  return (flexion[INDEX_IND] + flexion[THUMB_IND]) / 2 <= ANALOG_MAX/2 ? 0:1;
}

bool triggerGesture(int *flexion){
  return flexion[INDEX_IND]<=(ANALOG_MAX/2)?0:1;
}
