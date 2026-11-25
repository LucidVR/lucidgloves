# lucidgloves-firmware


Check the [Wiki](https://github.com/LucidVR/lucidgloves/wiki/Firmware-Setup-and-Customization-Tutorial/) for instructions on how to set it up.

## Optional library

Install **RunningMedian** by Rob Tillaart from the Arduino Library Manager if you enable either configuration below.

- `ENABLE_MEDIAN_FILTER` is `true` in [AdvancedConfig.h](AdvancedConfig.h).
- `FLEXION_MIXING` is `MIXING_SINCOS` in [Config.h](Config.h) and `INTERFILTER_MODE` is `INTERFILTER_LIMITS` or `INTERFILTER_ALL` in [AdvancedConfig.h](AdvancedConfig.h).

`INTERFILTER_LIMITS` is the default intermediate filter. To install the library with Arduino CLI, run `arduino-cli lib install RunningMedian`.
