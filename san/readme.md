# san

![san](https://i.imgur.com/eKg5Vrt.jpg)

3keys macro pad.

Keyboard Maintainer: [Takuya Urakawa (dm9records.com 5z6p.com)](https://github.com/hsgw)  
Hardware Supported: STM32F042K6  
Hardware Availability: https://github.com/hsgw/san

Make example for this keyboard (after setting up your build environment):

    make san:default

## Update firmware
### Enter bootloader
1. Push and hold reset button
2. Push boot button
3. Release reset button
4. Release boot button

### Burn with dfu-util

    make san:default:dfu-util


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
