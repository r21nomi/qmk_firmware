#include "crkbd.h"
#include "bootloader.h"
#include "action_layer.h"
#include "action_util.h"
#include "eeconfig.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#include "LUFA/Drivers/Peripheral/TWI.h"
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#include "../lib/mode_icon_reader.c"
#include "../lib/layer_state_reader.c"
#include "../lib/host_led_state_reader.c"
#include "../lib/logo_reader.c"
#include "../lib/keylogger.c"
#include "../lib/timelogger.c"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 3
#define _NAV 4
#define _ADJUST 5

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSMOD RGB_SMOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

/**
 * Keycodes Overview
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * Build command
 * $ make crkbd:r21nomi
 *
 * Upload command
 * $ make crkbd:r21nomi:avrdude
 */

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
  [_QWERTY] = LAYOUT(
        LT(_ADJUST, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T,       KC_Y, KC_U, KC_I,    KC_O,   KC_P,    LT(_ADJUST, KC_BSLS),
        KC_LCTL,             KC_A, KC_S, KC_D, KC_F, KC_G,       KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, LT(_NAV, KC_ENT),
        KC_LSFT,             KC_Z, KC_X, KC_C, KC_V, KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        ALT_T(KC_MHEN), LT(_SYMB, KC_DEL), LGUI_T(KC_ESC),       LT(_NAV, KC_SPC), LT(_SYMB, KC_BSPC), KC_HENK
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
  [_SYMB] = LAYOUT(
        KC_QUOT, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,     KC_TRNS, KC_7, KC_8, KC_9, KC_PLUS, KC_TRNS,
        KC_AMPR, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,      KC_TRNS, KC_4, KC_5, KC_6, KC_MINS, KC_EQL,
        KC_LSFT, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,     KC_0,    KC_1, KC_2, KC_3, KC_ASTR, KC_RSFT,
                                KC_CAPSLOCK, KC_DEL, KC_ESC,      KC_SPC, KC_BSPC, KC_0
  ),

  /* NAVIGATION
     * ,---------------------------------------------.                ,------------------------------------------.
     * |      |      |Prev tab|   ↑  |Next tab|      |                |      |      | MsUp |      |      |       |
     * |------+------+--------+------+--------+------|                |------+------+------+------+------+-------|
     * |      | |<-  |   ←    |   ↓  |    →   |   -> |                |      |MsLeft|MsDown|MsRght|      |       |
     * |------+------+--------+------+--------+------|                |------+------+------+------+------+-------|
     * |      |      |        |PgDown|        |      |                |      |      |      |      |      |       |
     * `-----------------------------------------------------. ,-------------------------------------------------'
     *                               |        |      | Lclk  | | Rclk |      |      |
     *                               `-----------------------' `--------------------'
     */
  [_NAV] = LAYOUT(
        KC_TRNS, KC_TRNS,    LGUI(LSFT(KC_LCBR)), KC_UP,   LGUI(LSFT(KC_RCBR)), KC_TRNS,       KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RCTL(KC_A), KC_LEFT,             KC_DOWN, KC_RIGHT,            RCTL(KC_E),    KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,             KC_PGDN, KC_TRNS,             KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
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
  [_ADJUST] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                   RGB_VAD, RGB_SAD, RGB_HUD,       RGB_HUI, RGB_SAI, RGB_VAI
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
    set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_SYMB);
        update_tri_layer_RGB(_SYMB, _NAV, _ADJUST);
      } else {
        layer_off(_SYMB);
        update_tri_layer_RGB(_SYMB, _NAV, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_NAV);
        update_tri_layer_RGB(_SYMB, _NAV, _ADJUST);
      } else {
        layer_off(_NAV);
        update_tri_layer_RGB(_SYMB, _NAV, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

#endif
