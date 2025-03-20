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
    // [0] = LAYOUT_jis(
    //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX                           XXXXXXX,                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //                                                           XXXXXXX,      XXXXXXX
    // ),
    [_DEFAULT] = LAYOUT_jis(
        JP_ZKHK, JP_1,    JP_2,    JP_3,    JP_4,    JP_5,    JP_6,         JP_6,    JP_7,    JP_8,    JP_9,    JP_0,    JP_MINS, JP_CIRC, JP_YEN, KC_BSPC,
        KC_TAB,     JP_Q,    JP_W,    JP_E,    JP_R,    JP_T,    JP_Y,          JP_Y,    JP_U,    JP_I,    JP_O,    JP_P,    JP_AT, JP_LBRC,
        KC_LCTL,       JP_A,    JP_S,    JP_D,    JP_F,    JP_G,                    JP_H,    JP_J,    JP_K,    JP_L,    JP_SCLN, JP_COLN, JP_RBRC,  KC_ENT,
        KC_LSFT,          JP_Z,    JP_X,    JP_C,    JP_V,    JP_B,            JP_B,    JP_N,    JP_M,    JP_COMM, JP_DOT,  JP_SLSH, JP_BSLS, KC_UP,   LT(_CONFIG, KC_ESC),
        JP_EISU, KC_LGUI, KC_LALT,       JP_MHEN,  KC_SPC,                           KC_SPC,                                KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT,
                                                                 JP_MHEN,       JP_HENK
    ),
    [_MOUSE] = LAYOUT_jis(
        _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, MS_BTN3, _______, _______, _______, _______,
        _______,       _______, _______, _______, _______, _______,            OSL(_SCROLL), MS_BTN1, MS_BTN2, MO(_MOUSE), MO(_SCROLL), _______, _______, _______,
        _______,          _______, _______, _______, _______, _______,         _______, MS_BTN4, MS_BTN5, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,       _______, _______,                          _______,                                _______, _______, _______, _______,
                                                          MO(_SCROLL),      _______
    ),
    [_SCROLL] = LAYOUT_jis(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,                           XXXXXXX,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                              XXXXXXX,      XXXXXXX
    ),
    [_CONFIG] = LAYOUT_jis(
        QK_BOOT, UG_TOGG, UG_VALU, UG_VALD, UG_HUEU, UG_HUED, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
        QK_RBT,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_RBT,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                XXXXXXX,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
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
