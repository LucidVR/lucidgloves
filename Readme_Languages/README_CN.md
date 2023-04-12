![LucidGloves](https://cdn.discordapp.com/attachments/785135646082990120/873666310855360582/LucidGlovesBlackwbkgnd.png)

# lucid手套- 固件与3D打印文件
此Repo含有lucid手套的原型机V3到V4的arduino固件以及3D打印所需要的STL文件。LucidGloves是DIY触觉反馈手指追踪手套，如果配合LucidVR使用，可以在大部分支持Valve Index手柄支持的游戏。我们的宗旨是用最少的钱，得到最大的体验。原作者Lucas_VRTech会在他的抖音账号里更新此项目的最新进展, 请关注https://www.tiktok.com/@lucas_vrtech 。

# 支持此项目
欢迎计入LucidVR的discord服务器，更多详细问题以及内容可以在LucidVR的官方discord讨论:
https://discord.gg/lucidvr

# 固件
固件文件在firmware/lucidgloves-firmware文件夹.
此固件默认使用和配置arduino nano以及它的USB通讯端口。如果使用USB通讯端口，您需要使用相应的数据项与设备相连。
如果您想配置此固件，请在lucidgloves-firmware.ino文件做出相应的改变。

**详细的配置方法：请点击此处进入配置教程 -> [配置教程传送门](https://github.com/LucidVR/lucidgloves-hardware/wiki/Firmware-V2-Customization).**\
**固件问题的故障排除教程：-> [固件故障排除教程](https://github.com/LucidVR/lucidgloves/wiki/Firmware-Troubleshooting-Guide).** 

## 已测试过的主板:
	* Arduino Nano
	* ESP-WROOM-32

## 现已支持的通讯方法:
	* USB Serial
	* Bluetooth Serial (可以在 ESP32 boards实现，详情请看教程。)
	* BLE (敬请期待)

# 硬件
3D打印所需要的STL文件在hardware文件夹。
*关于原型机V4:目前还在测试阶段*

以下是针对**单个手套**需要打印以下材料：

原型机V3/V3.1：
* Spool (5x) | 卷轴
* Tensioner (5x) | 卷轴张紧器
* Cover (5x) | 卷轴保护外圈
* Holder (5x) | 卷轴固定器
* GuideRing(Will need to be resized) OR GuideNode(3.1) (2+ per finger, 1+ for thumb) | 导环
* EndCap (1x per finger, will need to be resized to fit)  | 手指套

原型机V4/V4.1：
* HapticSpool (5x) | 触觉反馈卷轴
* Tensioner_GreenPot (5x) OR Tensioner_WLPot (5x) | 触觉反馈卷轴张紧器，根据您的电位器型号选择
* SpoolCover (5x) | 卷轴保护外圈
* RigidMount (2x) (One for each hand, make sure to flip for other hand) | 固定装置
* WLPotSlideHolder OR WLPotElasticHolder OR GreenPotSlideHolder (5x) | 卷轴滑轨固定器
* Quest2_MountSlider OR Vive3.0_MountSlider (2x) | Quest2手柄固定器
* GuideRing (Proto 3) (Will need to be resized) OR GuideNode (Proto 3.1) (2+ per finger, 1+ for thumb) | 导环
* EndCap (Proto 3) (1x per finger, will need to be resized to fit) | 手指套


3D打印教程: [打印教程传送门](https://github.com/LucidVR/lucidgloves-hardware/wiki/Parts-Printing-Guides)

**需要购买的材料: [所需材料传送门](https://github.com/LucidVR/lucidgloves/wiki/Parts-Lists)**  
可选配置:  
* 遥感：可以控制人物在游戏里的运动
  - 此项目的最终计划是加入VR跑步机
* 按钮 (几乎所有按钮都可用手势替代) (至少需要一个来用作自动校准)

想要更多信息和情报？请关注[LucidVR官方网站](http://lucidvrtech.com/). 
*  [原型机V3/V3.1制作教程](https://youtu.be/Qj4hqRKiy8g)
*  原型机V4的教程会很快跟进的。

# SteamVR兼容性(OpenGloves)
此项会用到OpenVR驱动程序去兼容SteamVR, 您可以到Steam下载:  
https://store.steampowered.com/app/1574050/OpenGloves/

GitHub上已公布的源代码:  
https://github.com/LucidVR/opengloves-driver

# Other Languages
**[English](https://github.com/LucidVR/lucidgloves/blob/main/README.md) | [简体中文](https://github.com/LucidVR/lucidgloves/blob/main/Readme_Languages/README_CN.md)**
