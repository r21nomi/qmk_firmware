/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
* Keycodes Overview
* https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
*
* Compile command:
* $ qmk compile -kb crkbd -km r21nomi_mac
*
* Upload command:
* $ qmk flash -kb crkbd -km r21nomi_mac
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "keymap_japanese.h"

#define _QWERTY 0
#define _SYMB 1
#define _NAV 2
#define _ADJUST 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
     * ,-----------------------------------------.                ,-------------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                |   Y  |   U  |   I  |   O  |   P  |    \   |
     * |------+------+------+------+------+------|                |------+------+------+------+------+--------|
     * | Ctrl |   A  |   S  |   D  |   F  |   G  |                |   H  |   J  |   K  |   L  |   ;  |Enter/L2|
     * |------+------+------+------+------+------|                |------+------+------+------+------+--------|
     * |LShift|   Z  |   X  |   C  |   V  |   B  |                |   N  |   M  |   ,  |   .  |   /  | RShift |
     * `-------------------------------------------------. ,--------------------------------------------------'
     *                     | MHEN/alt | Del/L1 | Ecs/Cmd | | spc/L2 | Bsp/L1 | HENK |
     *                     `-----------------------------' `------------------------'
     */
  [_QWERTY] = LAYOUT_split_3x6_3(
        LT(_ADJUST, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T,       KC_Y, KC_U, KC_I,    KC_O,   KC_P,    LT(_ADJUST, KC_BSLS),
        KC_LCTL,             KC_A, KC_S, KC_D, KC_F, KC_G,       KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, LT(_NAV, KC_ENT),
        KC_LSFT,             KC_Z, KC_X, KC_C, KC_V, KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        ALT_T(JP_MHEN), LT(_SYMB, KC_DEL), LGUI_T(KC_ESC),       LT(_NAV, KC_SPC), LT(_SYMB, KC_BSPC), JP_HENK
  ),

  /* SYMBOLS
     * ,-----------------------------------------.                ,------------------------------------------.
     * |   '  |   !  |   @  |   {  |   }  |   |  |                |      |   7  |   8  |   9  |   +  |       |
     * |------+------+------+------+------+------|                |------+------+------+------+------+-------|
     * |   &  |   #  |   $  |   (  |   )  |   `  |                |      |   4  |   5  |   6  |   -  |   =   |
     * |------+------+------+------+------+------|                |------+------+------+------+------+-------|
     * |LShift|   %  |   ^  |   [  |   ]  |   ~  |                |   0  |   1  |   2  |   3  |   *  |RShift |
     * `-------------------------------------------------. ,-------------------------------------------------'
     *                                | Caps | Del | Ecs | | spc | Bsp | 0 |
     *                                `------------------' `---------------'
     */
  [_SYMB] = LAYOUT_split_3x6_3(
        KC_QUOT, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,     KC_TRNS, KC_7, KC_8, KC_9, KC_PLUS, KC_TRNS,
        KC_AMPR, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,      KC_TRNS, KC_4, KC_5, KC_6, KC_MINS, KC_EQL,
        KC_LSFT, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,     KC_0,    KC_1, KC_2, KC_3, KC_ASTR, KC_RSFT,
                                   JP_CAPS, KC_DEL,  KC_ESC,      KC_SPC, KC_BSPC, KC_0
  ),

  /* NAVIGATION
     * ,---------------------------------------------------.                ,------------------------------------------.
     * |      |      |  Prev tab |   ↑  | Next tab  |      |                |      |      | MsUp |      |      |       |
     * |------+------+-----------+------+-----------+------|                |------+------+------+------+------+-------|
     * |      | |<-  |     ←     |   ↓  |     →     |   -> |                |      |MsLeft|MsDown|MsRght|      |       |
     * |------+------+-----------+------+-----------+------|                |------+------+------+------+------+-------|
     * |      |      |Prev window|PgDown|Next window|      |                |      |      |      |      |      |       |
     * `-----------------------------------------------------------. ,-------------------------------------------------'
     *                                      |        |      | Lclk | | Rclk |      |      |
     *                                      `----------------------' `--------------------'
     */
  [_NAV] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS,    LGUI(LSFT(KC_LCBR)), KC_UP,   LGUI(LSFT(KC_RCBR)), KC_TRNS,       KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RCTL(KC_A), KC_LEFT,             KC_DOWN, KC_RIGHT,            RCTL(KC_E),    KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,    LCTL(KC_H),          KC_PGDN, LCTL(KC_L),          KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                              KC_TRNS, KC_TRNS, KC_BTN1,       KC_BTN2, KC_SPC, KC_TRNS
  ),

  /* ---
     * ,----------------------------------------------.                ,------------------------------------------.
     * |   F1  |  F2  |   F3   |  F4  |   F5   |  F6  |                |  F7  |  F8  |  F9  |  F10 |  F11 |  F12  |
     * |-------+------+--------+------+--------+------|                |------+------+------+------+------+-------|
     * |LED_TOG|      |        |      |        |      |                |      |      |      |      |      |LED_TOG|
     * |-------+------+--------+------+--------+------|                |------+------+------+------+------+-------|
     * |       |      |        |      |        |      |                |      |      |      |      |      |       |
     * `------------------------------------------------------. ,-------------------------------------------------'
     *                     | brightness- | saturation- | Hue- | | Hue+ | saturation+ | brightness+ |
     *                     `----------------------------------' `----------------------------------'
     */
  [_ADJUST] = LAYOUT_split_3x6_3(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                   RGB_VAD, RGB_SAD, RGB_HUD,       RGB_HUI, RGB_SAI, RGB_VAI
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_ENABLE
