#include QMK_KEYBOARD_H
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _NAV 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMB,
  NAV,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

/**
 * Keycodes Overview
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * Build and upload command
 * $ make fortitude60/rev1:r21nomi:avrdude
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------.                   ,---------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |    F5    |   F6   |                   |   F7   |  F8  |  F9  |  F10 |  F11 |   F12  |
 * |------+------+------+------+----------+--------|                   |--------+------+------+------+------+--------|
 * | Tab  |   Q  |   W  |   E  |     R    |    T   |                   |   Y    |   U  |   I  |   O  |   P  | KC_BSLS|
 * |------+------+------+------+----------+--------|                   |--------+------+------+------+------+--------|
 * | Caps |   A  |   S  |   D  |     F    |    G   |                   |   H    |   J  |   K  |   L  |   ;  |Enter/L2|
 * |------+------+------+------+----------+--------+-------------------+--------+------+------+------+------+--------|
 * |LShift|   Z  |   X  |   C  |     V    |    B   |    [    |    ]    |   N    |   M  |   ,  |   .  |   /  | RShift |
 * `-------------+------+------+----------+--------+---------+---------+--------+------+------+------+---------------'
 *               |  GUI | Ctrl | MHEN/alt | Del/L1 | Ecs/Cmd | spc/Cmd | Bsp/L1 | HENK |  Alt |  GUI |
 *               `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT(
  KC_F1,       KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                                    KC_F7, KC_F8, KC_F9,   KC_F10, KC_F11,  KC_F12,
  KC_TAB,      KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                                     KC_Y,  KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC,
  KC_CAPSLOCK, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                                     KC_H,  KC_J,  KC_K,    KC_L,   KC_SCLN, LT(_NAV, KC_ENT),
  KC_LSFT,     KC_Z,  KC_X,  KC_C,  KC_V,  KC_B, KC_LBRC,                   KC_RBRC, KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
  KC_LGUI, KC_LCTL, ALT_T(KC_MHEN), LT(_SYMB, KC_DEL), LGUI_T(KC_ESC),  RGUI_T(KC_SPC), LT(_SYMB, KC_BSPC), KC_HENK, KC_RALT, KC_RGUI
),

/* Symbol
 * ,-----------------------------------------.             ,-----------------------------------------.
 * |      |      |      |      |      |      |             |      |      |      |      |      |      |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |   '  |   !  |   @  |   {  |   }  |   |  |             |      |   7  |   8  |   9  |   +  |      |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |   &  |   #  |   $  |   (  |   )  |   `  |             |      |   4  |   5  |   6  |   -  |   =  |
 * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 * |LShift|   %  |   ^  |   [  |   ]  |   ~  |      |      |   0  |   1  |   2  |   3  |   *  |RShift|
 * `-------------+------+------+------+------+------+------+------+------+------+------+-------------'
 *               |      |      | Ctrl |  Del |  Ecs | spc  |  Bsp |  0   |      |      |
 *               `---------------------------------------------------------------------'
 */
[_SYMB] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  KC_QUOT, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                   _______, KC_7,    KC_8,    KC_9,    KC_PLUS, _______,
  KC_AMPR, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                    _______, KC_4,    KC_5,    KC_6,    KC_MINS, KC_EQL,
  KC_LSFT, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    KC_ASTR, KC_RSFT,
                    _______, _______, KC_LCTL, _______, KC_ESC,  KC_SPC,  _______, KC_0,    _______, _______
),

/* Navigation
 * ,---------------------------------------------.             ,-----------------------------------------.
 * |      |      |        | PgUp |        |      |             |      |      |      |      |      |      |
 * |------+------+--------+------+--------+------.             ,------+------+------+------+------+------|
 * |      |      |Prev tab|   ↑  |Next tab|      |             |      |      | MsUp |      |      |      |
 * |------+------+--------+------+--------+------.             ,------+------+------+------+------+------|
 * |      | |<-  |    ←   |   ↓  |    →   | ->|  |             |      |MsLeft|MsDown|MsRght|      |      |
 * |------+------+--------+------+--------+------+-------------+------+------+------+------+------+------|
 * |      |      |        |PgDown|        |      |      |      |      |      |      |      |      |      |
 * `-------------+--------+------+--------+------+------+------+------+------+------+------+-------------'
 *               |        |      |        |      | Lclk | Rclk |      |      |      |      |
 *               `-------------------------------------------------------------------------'
 */
[_NAV] = LAYOUT(
  _______, _______,    _______,             KC_PGUP, _______,             _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______,    LGUI(LSFT(KC_LCBR)), KC_UP,   LGUI(LSFT(KC_RCBR)), _______,                     _______, _______, KC_MS_U, _______, _______, _______,
  _______, RCTL(KC_A), KC_LEFT,             KC_DOWN, KC_RIGHT,            RCTL(KC_E),                  _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
  _______, _______,    _______,             KC_PGDN, _______,             _______,  _______, _______,  _______, _______, _______, _______, _______, _______,
                                                _______, _______, _______, _______, KC_BTN1, KC_BTN2,  _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------.             ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------.             ,------+------+------+------+------+------|
 * |      | Reset|RGB Tg|RGB Md|Hue Up|Hue Dn|             |Sat Up|Sat Dn|Val Up|Val Dn|      | Bksp |
 * |------+------+------+------+------+------.             ,------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|             |AGswap|      |BL TOG|BL STP|      |      |
 * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 * |Qwerty|Colemk|Dvorak|      |      |      |      |      |      |      |      |      |      |      |
 * `-------------+------+------+------+------+------+------+------+------+------+------+-------------'
 *               |      |      |      |      |      |      |      |      |      |      |
 *               `---------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,                   RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_BSPC,
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM,                   AG_SWAP, _______, BL_TOGG, BL_STEP, _______, _______,
  QWERTY,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______\
)

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _SYMB, _NAV, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
  }
  return true;
}
