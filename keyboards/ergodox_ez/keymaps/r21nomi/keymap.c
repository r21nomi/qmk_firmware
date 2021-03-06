#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NAV 2  // navigation keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

/**
 * Keycodes Overview
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * Build command
 * $ make ergodox_ez:r21nomi
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  cut |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Caps   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |Enter/L2|
 * |--------+------+------+------+------+------| copy |           | past |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1| Ctrl |   '  |  alt |  Cmd |                                       |  Cmd |  alt |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Esc  | LGui |       |   ←  |   →  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Home |       |   ↑  |      |      |
 *                                 |Del/L1| Space|------|       |------| Space| Backs|
 *                                 |      |      | undo |       |   ↓  |      |ace/L1|
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_TAB,         KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   LGUI(KC_X),
        KC_CAPSLOCK,    KC_A,    KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   LGUI(KC_C),
        LT(SYMB,KC_GRV),KC_LCTL, KC_QUOT,KC_LALT,KC_LGUI,
                                                            KC_ESC, KC_LGUI,
                                                                    KC_HOME,
                                          LT(SYMB, KC_DEL), KC_SPC, LGUI(KC_Z),
        // right hand
             KC_RGHT,     KC_6, KC_7,   KC_8,   KC_9,   KC_0,    KC_MINS,
             TG(SYMB),    KC_Y, KC_U,   KC_I,   KC_O,   KC_P,    KC_BSLS,
                          KC_H, KC_J,   KC_K,   KC_L,   KC_SCLN, LT(NAV,KC_ENT),
             LGUI(KC_V),  KC_N, KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_RSFT,
                                KC_RGUI,KC_RALT,KC_LBRC,KC_RBRC, KC_FN1,
             KC_LEFT, KC_RGHT,
             KC_UP,
             KC_DOWN, KC_SPC, LT(SYMB, KC_BSPC)
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |    '    |   !  |   @  |   {  |   }  |   |  |      |           |      |      |   7  |   8  |   9  |   +  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    &    |   #  |   $  |   (  |   )  |   `  |------|           |------|      |   4  |   5  |   6  |   -  |   =    |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   0  |   1  |   2  |   3  |   *  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |   0  |    . |      |   /  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |Bright|      |       |      |Hue-  |Backsp|
 *                                 |  Del |ness+ |------|       |------|      |ace   |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_QUOT,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_AMPR,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
          EPRM,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       RGB_MOD,KC_TRNS,
                                               KC_TRNS,
                               KC_DEL, RGB_VAI,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7, KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_TRNS, KC_7,  KC_8,    KC_9,    KC_PLUS, KC_F12,
                KC_TRNS, KC_4,  KC_5,    KC_6,    KC_MINS, KC_EQL,
       KC_TRNS, KC_0,    KC_1,  KC_2,    KC_3,    KC_ASTR, KC_TRNS,
                         KC_0,  KC_DOT,  KC_TRNS, KC_SLSH, KC_TRNS,
       RGB_TOG, RGB_SLD,
       KC_TRNS,
       KC_TRNS, RGB_HUD, KC_BSPC
),
/* Keymap 2: Navigation Layer
 *
 * ,----------------------------------------------------.           ,--------------------------------------------------.
 * | RESET|      |        | PgUp |        |      |      |           |      |      |      |      |      |      |        |
 * |------+------+--------+------+--------+-------------|           |------+------+------+------+------+------+--------|
 * |      |      |Prev tab|   ↑  |Next tab|      |      |           |      |      |      | MsUp |      |      |        |
 * |------+------+--------+------+--------+------|      |           |      |------+------+------+------+------+--------|
 * |      | |<-  |    ←   |   ↓  |   →    |  ->| |------|           |------|      |MsLeft|MsDown|MsRght|      |  Play  |
 * |------+------+--------+------+--------+------|      |           |      |------+------+------+------+------+--------|
 * |      |      |        |PgDown|        |      |      |           |      |      |      | Prev | Next |      |        |
 * `------+------+--------+------+--------+-------------'           `-------------+------+------+------+------+--------'
 *   |    |      |        |      |      |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Lclk |      |------|       |------|      | Rclk |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// NAVIGATION
[NAV] = LAYOUT_ergodox(
       RESET,   KC_TRNS,    KC_TRNS,             KC_PGUP, KC_TRNS,             KC_TRNS,    KC_TRNS,
       KC_TRNS, KC_TRNS,    LGUI(LSFT(KC_LCBR)), KC_UP,   LGUI(LSFT(KC_RCBR)), KC_TRNS,    KC_TRNS,
       KC_TRNS, RCTL(KC_A), KC_LEFT,             KC_DOWN, KC_RIGHT,            RCTL(KC_E),
       KC_TRNS, KC_TRNS,    KC_TRNS,             KC_PGDN, KC_TRNS,             KC_TRNS,    KC_TRNS,
       KC_TRNS, KC_TRNS,    KC_TRNS,             KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_BTN1, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_BTN2
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};
