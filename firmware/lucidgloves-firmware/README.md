# lucidgloves-firmware

## Adding Required ESP-32 Libraries
Using ESP-32 Dev Boards, which is required if you want to use Bluetooth Serial to connect your gloves wirelessly, requires you to install additional packages to your arduino IDE. Below is a procedure for doing so.

1. Go to File > Prefrences in your Arduino IDE
2. In the "Additional Board Manager URLs" field, enter this link: https://dl.espressif.com/dl/package_esp32_index.json and click the OK button
3. Go to Tools > Board > Boards Manager
4. Search "esp32" and install the "ESP32 by Espressif Systems" package.
5. Select your ESP32 board from Tools > Board
6. Download the ESP32 Arduino Servo Library from this link: https://github.com/RoboticsBrno/ESP32-Arduino-Servo-Library/archive/master.zip
7. Unzip the downloaded folder
8. Rename the folder from ESP32-Arduino-Servo-Library-Master to ESP32_Arduino_Servo_Library
9. Move the ESP32_Arduino_Servo_Library folder to your Arduino IDE installation libraries folder
10. Restart your IDE

All of your packages should be installed and ready to go.
