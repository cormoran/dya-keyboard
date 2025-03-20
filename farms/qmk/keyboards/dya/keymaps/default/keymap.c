// Copyright 2025 cormoran707
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgblight.h"
#include "keymap_japanese.h"
#include "dya.h"

enum layer_names { _DEFAULT, _MOUSE, _SCROLL, _CONFIG };
#define GUI_EN MT(MOD_LGUI, KC_LNG2)
#define GUI_JP MT(MOD_RGUI, KC_LNG1)
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // [0] = LAYOUT(
    //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
    //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
    //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                         XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //                                                  XXXXXXX,              XXXXXXX
    // ),
    [_DEFAULT] = LAYOUT(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BACKSLASH,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                       KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   LT(_CONFIG, KC_GRV),
        KC_CAPS, KC_LALT, MT(MOD_LGUI, KC_LNG2),     KC_SPC,                              KC_SPC,                             KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT,
                                                     MT(MOD_LGUI, KC_LNG2),      MT(MOD_RGUI, KC_LNG1)
    ),
    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,     _______,      _______,     _______, _______,     _______,     _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______,                   _______,     _______, MS_BTN3,     _______,     _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                       OSL(_SCROLL),     MS_BTN1, MS_BTN2,  MO(_MOUSE), MO(_SCROLL), _______,          _______,
        _______, _______, _______, _______, _______, _______,              _______,      MS_BTN4,     MS_BTN5, _______,     _______,     _______, _______, _______, _______,
        _______, _______, _______,          _______,                                     _______,                                        _______, _______, _______, _______,
                                                          MO(_SCROLL),     _______
    ),
    [_SCROLL] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                         XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                     XXXXXXX,              XXXXXXX
    ),
    [_CONFIG] = LAYOUT(
        QK_BOOTLOADER, UG_TOGG, UG_VALU, UG_VALD, UG_HUEU, UG_HUED, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          QK_BOOTLOADER,
        QK_REBOOT,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_REBOOT,
        XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX,                                         XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                           XXXXXXX,              XXXXXXX
    )
};

// clang-format on

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
    set_auto_mouse_enable(true);
    dya_set_mouse_layer(_MOUSE);
    dya_set_scroll_layer(_SCROLL);
    dya_set_config_layer(_CONFIG);
    dya_enable_layer_led();
}
