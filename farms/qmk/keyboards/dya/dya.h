// Copyright 2025 cormoran707
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef DYA_H
#define DYA_H

#ifndef DYA_SCROLL_CPI
#    define DYA_SCROLL_CPI 200
#endif

#ifndef DYA_POINTING_CPI
#    define DYA_POINTING_CPI 800
#endif

#ifndef DYA_SCROLL_DIVISOR
#    define DYA_SCROLL_DIVISOR 10
#endif

#ifndef DYA_LED_INDICATOR_ON_RGB
#    define DYA_LED_INDICATOR_ON_RGB 0, 0, 255
#endif

#ifndef DYA_LED_INDICATOR_OFF_RGB
#    define DYA_LED_INDICATOR_OFF_RGB 0, 0, 0
#endif
// To set under glow color to LED indicator, define DYA_LED_INDICATOR_OFF_UNDERGLOW
// #define DYA_LED_INDICATOR_OFF_UNDERGLOW

void dya_set_scroll_layer(uint8_t layer);
void dya_set_mouse_layer(uint8_t layer);
void dya_set_config_layer(uint8_t layer);
void dya_enable_layer_led(void);

#endif