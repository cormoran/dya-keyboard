# dya

![dya](https://i.imgur.com/dpQ2xiX.jpeg)

_Dya is 60% split keyboard with trackball, US/JIS layout support_

- Keyboard Maintainer: [cormoran](https://github.com/cormoran)
- Hardware Supported: RP2040-zero (QMK), XIAO nRF52840 plus (ZMK)
- Hardware Availability: https://cormoran707.booth.pm/items/6705756

Make example for this keyboard (after setting up your build environment):

    make dya:default

Flashing example for this keyboard:

    make dyad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
- **Physical reset button**: Button on RP2040-zero, XIAO nRF52840 plus
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
