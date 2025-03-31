// Copyright 2025 cormoran707
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "rgb_matrix.h"
#include "dya.h"

const uint8_t led_indicator_start_index = 4;
const uint8_t num_led_indicators        = 4;

static uint8_t mouse_layer        = 0xFF;
static uint8_t scroll_layer       = 0xFF;
static uint8_t config_layer       = 0xFF;
static bool    layer_led_enabled  = false;
static bool    set_scrolling      = false;
static int16_t scroll_h_remaining = 0;
static int16_t scroll_v_remaining = 0;

// functions provided for user

void dya_set_scroll_layer(uint8_t layer) {
    scroll_layer = layer;
}

void dya_set_mouse_layer(uint8_t layer) {
    mouse_layer = layer;
}

void dya_set_config_layer(uint8_t layer) {
    config_layer = layer;
}

void dya_enable_layer_led() {
    layer_led_enabled = true;
}

// keyboard functions

void keyboard_pre_init_kb(void) {
    // Enable LED
    gpio_set_pin_output(GP26);
    gpio_write_pin(GP26, 0);

    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    housekeeping_task_user();
}

void suspend_power_down_kb(void) {
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    suspend_wakeup_init_user();
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (!layer_led_enabled) {
        return true;
    }
    uint8_t highest_layer = get_highest_layer(layer_state | default_layer_state);
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(led_indicator_start_index, DYA_LED_INDICATOR_ON_RGB);
    } else {
#ifndef DYA_LED_INDICATOR_OFF_UNDERGLOW
        rgb_matrix_set_color(led_indicator_start_index, DYA_LED_INDICATOR_OFF_RGB);
#endif
    }
    for (int i = 1; i < num_led_indicators; i++) {
        if (highest_layer == i) {
            rgb_matrix_set_color(i + led_indicator_start_index, DYA_LED_INDICATOR_ON_RGB);
        } else {
#ifndef DYA_LED_INDICATOR_OFF_UNDERGLOW
            rgb_matrix_set_color(i + led_indicator_start_index, DYA_LED_INDICATOR_OFF_RGB);
#endif
        }
    }
    return true;
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    if (set_scrolling) {
        set_scrolling = false;
        pointing_device_set_cpi(DYA_POINTING_CPI);
    }
    return default_layer_state_set_user(state);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    uint8_t highest_layer = get_highest_layer(state);
    if (highest_layer == scroll_layer) {
        set_scrolling = true;
        pointing_device_set_cpi(DYA_SCROLL_CPI);
    } else {
        if (set_scrolling) {
            set_scrolling = false;
            pointing_device_set_cpi(DYA_POINTING_CPI);
        }
    }
    return layer_state_set_user(state);
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (set_scrolling) {
        int16_t h          = (int16_t)(mouse_report.x) + scroll_h_remaining;
        int16_t v          = (int16_t)(mouse_report.y) + scroll_v_remaining;
        mouse_report.h     = h / DYA_SCROLL_DIVISOR;
        scroll_h_remaining = h % DYA_SCROLL_DIVISOR;
        mouse_report.v     = v / DYA_SCROLL_DIVISOR;
        scroll_v_remaining = v % DYA_SCROLL_DIVISOR;
        mouse_report.x     = 0;
        mouse_report.y     = 0;
    } else {
        scroll_h_remaining = 0;
        scroll_v_remaining = 0;
    }
    return pointing_device_task_user(mouse_report);
}
