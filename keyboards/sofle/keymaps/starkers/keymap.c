// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    NORMAL,
    RAISED,
};

enum custom_keycodes {
    KC_PRVWD = QK_USER,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND
};

#define KC_QWERTY PDF(_QWERTY)
#define KC_COLEMAK PDF(_COLEMAK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * NORMAL
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |           Rotation |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|           AltShF2  |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |           AltShF3  |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |AltShF1|------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |  [   | /Space  /       \Enter \  |   ]  | RCTR | RAlt | RGUI |
 *            |      |      |      |HLD FN|/       /         \      \ |HLD L2|      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[NORMAL] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSLS,
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    A(S(KC_F1)),  KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
            KC_LGUI,KC_LALT,KC_LCTL, LT(RAISED,KC_LBRC),KC_SPC,   KC_ENT, LT(2,KC_RBRC), KC_RCTL, KC_RALT, KC_RGUI
),
/*
 * RAISED
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |         Rotation:  |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
 * |------+------+------+------+------+------|            AltShF5 |------+------+------+------+------+------|
 * | xxx  |  INS | HOME | PGUP |  xxx |  xxx |            AltShF6 |  xxx | xxx  |  xxx |  xxx |  xxx |  DEL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | xxx  |  DEL | END  | PGDN |  xxx |  xxx |-------.    ,-------| LEFT | DOWN |  UP  |RIGHT |   -  |  =   |
 * |------+------+------+------+------+------|  xxx  |    |AltShF4|------+------+------+------+------+------|
 * | xxx  |  xxx | xxx  | xxx  |  xxx |  xxx |-------|    |-------|  xxx |  xxx |  xxx | xxx  |  xxx |  xxx |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | xxx  | xxx  |  xxx |  xxx | /  xxx  /       \  xxx \  | xxx  |  xxx |  xxx |  xxx |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[RAISED] = LAYOUT(
  KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                       KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
  KC_NO, KC_INS, KC_HOME, KC_PGUP, KC_NO, KC_NO,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL,
  KC_NO, KC_DEL, KC_END, KC_PGDN, KC_NO, KC_NO,              KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_MINS, KC_EQL,
  KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, A(S(KC_F4)), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO,             KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS)

};

#if defined(ENCODER_MAP_ENABLE)
//F16 - F18 are used on NORMAL because they are supported on all OSs and are unlikely to clober anything.
//My thinking is that they should be software mapped, eg to next pane in tmux.conf.
//F13 - F15 are used in RAISED as they are slightly more likely to already be in use (though still unlikely)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [NORMAL] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(A(S(KC_F2)), A(S(KC_F3)))  },
    [RAISED] = { ENCODER_CCW_CW(KC_NO, KC_NO),  ENCODER_CCW_CW(A(S(KC_F5)), A(S(KC_F6)))  },
};
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
    }
    return true;
}
