![LucidGloves](https://cdn.discordapp.com/attachments/785135646082990120/873666310855360582/LucidGlovesBlackwbkgnd.png)

# LucidGloves - Firmware and 3D Printer Files
This repo contains the arduino firmware as well as the STL files for Prototypes 3 through 4 of the LucidVR glove. This is a finger tracking glove that allows you to use your hands in VR. Follow along with Lucas_VRTech's developments on his Tiktok page:
https://www.tiktok.com/@lucas_vrtech

# Building your own gloves
**Start here at the wiki! https://github.com/LucidVR/lucidgloves/wiki**

# Support
Join the LucidVR discord server for assistance:
https://discord.gg/lucidvr


# Firmware
Open the firmware files located in the firmware/lucidgloves-firmware folder.
By default the firmware is configured for an arduino nano using serial.
To configure the firmware, change the defines in the lucidgloves-firmware.ino file.

**Configuration instructions are here: [Configuration Instructions](https://github.com/LucidVR/lucidgloves/wiki/Firmware-Setup-and-Customization-Tutorial).**\
**Firmware Troubleshooting Guide is here: [Firmware Troubleshooting Guide](https://github.com/LucidVR/lucidgloves/wiki/Firmware-Troubleshooting-Guide).** 

## Tested boards:
* Arduino Nano
* ESP-WROOM-32

## Supported Communication Methods:
* USB Serial
* Bluetooth Serial (On ESP32 boards)
* BLE (Soon, not up yet)

# Hardware
STL files for 3D printing are located in the hardware folder. 
*Prototype 4 models are currently experimental.*

The assembly **for each hand** is as follows:

For Prototypes 3 and 3.1 - 
* Spool (5x)
* Tensioner (5x)
* Cover (5x)
* Holder (5x)
* GuideRing(Will need to be resized) OR GuideNode(3.1) (2+ per finger, 1+ for thumb)
* EndCap (1x per finger, will need to be resized to fit) 

For Prototypes 4 and 4.1 - 
* HapticSpool (5x)
* Tensioner_GreenPot (5x) OR Tensioner_WLPot (5x)
* SpoolCover (5x)
* RigidMount (1x) (Left or right hand)
* WLPotSlideHolder OR WLPotElasticHolder OR GreenPotSlideHolder (5x)
* Quest2_MountSlider OR Vive3.0_MountSlider (1x)
* GuideRing (Proto 3) (Will need to be resized) OR GuideNode (Proto 3.1) (2+ per finger, 1+ for thumb)
* EndCap (Proto 3) (1x per finger, will need to be resized to fit)



Guide for printing parts: [Printing guide](https://github.com/LucidVR/lucidgloves/wiki/Parts-Printing-Guides)


**Required parts for each hand: [Parts Lists](https://github.com/LucidVR/lucidgloves/wiki/Parts-Lists)**  
Optional:  
* Joysticks for locomotion 
  - Will be making a DIY treadmill eventually as well for those who would prefer that  
* Buttons (Most can be replaced with gestures) (One is required for autocalibration)

More information will be available on the [LucidVR site](http://lucidvrtech.com/) very soon.  
*  [Prototype 3/3.1 Building Tutorial](https://youtu.be/Qj4hqRKiy8g)
*  [Prototype 4/4.1 Building Tutorial](https://youtu.be/2yF-SJcg3zQ)

# SteamVR Compatibility (OpenGloves)
This project uses the OpenGloves OpenVR driver for compatibility with SteamVR, which is downloadable on Steam:  
https://store.steampowered.com/app/1574050/OpenGloves/

Source code available on GitHub:  
https://github.com/LucidVR/opengloves-driver

# Other Languages
**[English](https://github.com/LucidVR/lucidgloves/blob/main/README.md) | [简体中文](https://github.com/LucidVR/lucidgloves/blob/main/Readme_Languages/README_CN.md)**
