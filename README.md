![LucidGloves](https://cdn.discordapp.com/attachments/785135646082990120/873660967521775736/LucidGlovesBlackwstroke.png)

# lucidgloves- Firmware and 3D Print Files
This repo contains the arduino firmware as well as the STL files for Prototype 3 of the LucidVR glove prototype. This is a finger tracking glove that allows you to use your hands in VR. Follow along with Lucas_VRTech's developments on his Tiktok page:
https://www.tiktok.com/@lucas_vrtech

# Support
Join the LucidVR discord server for assistance:
https://discord.gg/RjV9T8jN2G


# Firmware
Open the firmware files located in the firmware/lucidgloves-firmware folder.
By default the firmware is configured for an arduino nano using serial.
To configure the firmware, change the defines in the lucidgloves-firmware.ino file.

**Configuration instructions are here: [Configuration Instructions](https://github.com/LucidVR/lucidgloves-hardware/wiki/Firmware-V2-Customization).** 

## Tested boards:
	* Arduino Nano
	* ESP-WROOM-32

## Supported Communication Methods:
	* USB Serial
	* Bluetooth Serial (On ESP32 boards)
	* BLE (Soon, not up yet)

# Hardware
STL files for 3D printing are located in the hardware folder. 
*Prototype 3.1 models are currently experimental*

The assembly **for each hand** is as follows:
* Spool (5x)
* Tensioner (5x)
* Cover (5x)
* Holder (5x)
* GuideRing(Will need to be resized) OR GuideNode(3.1) (2+ per finger, 1+ for thumb)

* EndCap (1x per finger, will need to be resized to fit) 

Guide for printing parts: [Printing guide](https://github.com/LucidVR/lucidgloves-hardware/wiki/Parts-Printing-Guide)

**Required parts for each hand: [Parts Lists](https://github.com/LucidVR/lucidgloves/wiki/Parts-Lists)**  
Optional:  
* Joysticks for locomotion 
  - will be making a DIY treadmill eventually as well for those who would prefer that  
* Buttons (Most can be replaced with gestures)

More information will be available on the [LucidVR site](http://lucidvrtech.com/) very soon.  
Will be releasing video tutorials on how to assemble and setup the gloves.

# Driver
This project uses the open source OpenVR driver created by LucidVR and Danwillm:
https://github.com/LucidVR/lucidgloves-openvr
