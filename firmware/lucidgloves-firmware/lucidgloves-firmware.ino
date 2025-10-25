/*
 * LucidGloves Firmware Version 4
 * Author: Lucas_VRTech - LucidVR
 * lucidvrtech.com
 */


#include "src/Main.h"

/*
 * 
 *  THE CONFIG SETTINGS ARE NO LONGER STORED HERE. THEY HAVE BEEN MOVED TO Config.h
 *  
 *  You can now change the settings over at config.h before uploading to your gloves.
 * 
 */


Main mainClass;

void setup(){
  mainClass.setup();
}

void loop(){
  mainClass.loop();
}
