![LucidGloves](https://cdn.discordapp.com/attachments/785135646082990120/873666310855360582/LucidGlovesBlackwbkgnd.png)

# lucidgloves- Firmware and 3D Print Files
This repo contains the arduino firmware as well as the STL files for Prototypes 3 through 4 of the LucidVR glove. This is a finger tracking glove that allows you to use your hands in VR. Follow along with Lucas_VRTech's developments on his Tiktok page:
https://www.tiktok.com/@lucas_vrtech

# Support
Join the LucidVR discord server for assistance:
https://discord.gg/lucidvr


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
*Prototype 4 models are currently experimental*

The assembly **for each hand** is as follows:

For Prototypes 3 and 3.1 - 
* Spool (5x)
* Tensioner (5x)
* Cover (5x)
* Holder (5x)
* GuideRing(Will need to be resized) OR GuideNode(3.1) (2+ per finger, 1+ for thumb)
* EndCap (1x per finger, will need to be resized to fit) 

For Prototype 4 - 
* HapticSpool (5x)
* Tensioner_GreenPot (5x) OR Tensioner_WLPot (5x)
* SpoolCover (5x)
* RigidMount (2x) (One for each hand, make sure to flip for other hand)
* WLPotSlideHolder OR WLPotElasticHolder OR GreenPotSlideHolder (5x)
* Quest2_MountSlider OR Vive3.0_MountSlider (2x)
* GuideRing (Proto 3) (Will need to be resized) OR GuideNode (Proto 3.1) (2+ per finger, 1+ for thumb)
* EndCap (Proto 3) (1x per finger, will need to be resized to fit)


Guide for printing parts: [Printing guide](https://github.com/LucidVR/lucidgloves-hardware/wiki/Parts-Printing-Guide)

**Required parts for each hand: [Parts Lists](https://github.com/LucidVR/lucidgloves/wiki/Parts-Lists)**  
Optional:  
* Joysticks for locomotion 
  - will be making a DIY treadmill eventually as well for those who would prefer that  
* Buttons (Most can be replaced with gestures) (One is required for autocalibration)

More information will be available on the [LucidVR site](http://lucidvrtech.com/) very soon.  
*  [Prototype 3/3.1 Building Tutorial](https://youtu.be/Qj4hqRKiy8g)
*  Prototype 4 Tutorial to come out in the future

# Driver
This project uses the open source OpenVR driver created by LucidVR and Danwillm:
https://github.com/LucidVR/lucidgloves-openvr
