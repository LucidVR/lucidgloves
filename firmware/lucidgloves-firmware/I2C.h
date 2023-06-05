 #pragma once
 #include "AdvancedConfig.h"
 #include <Wire.h>


void Setup_I2C() {
      Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
      Serial.println("I2C Initialized");
}
