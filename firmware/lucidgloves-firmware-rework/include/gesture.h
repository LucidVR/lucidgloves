#pragma once
#include "config.h"

bool grabGesture(int *flexion){
  return (flexion[0] + flexion[1] + flexion[2] + flexion[3]) / 4 <= ANALOG_MAX/2 ? 0:1;
}

bool pinchGesture(int *flexion){
  return (flexion[0] + flexion[1]) / 2 <= ANALOG_MAX/2 ? 0:1;
}

bool triggerGesture(int *flexion){
  return flexion[1]<=(ANALOG_MAX/2)?0:1;
}
