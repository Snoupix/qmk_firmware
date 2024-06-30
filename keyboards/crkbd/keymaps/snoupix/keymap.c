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

#include QMK_KEYBOARD_H

/* #define A_Q MT(MOD_LGUI, KC_A) */
/* #define _S MT(MOD_LALT, KC_S) */
/* #define D MT(MOD_LSFT, KC_D) */
/* #define F MT(MOD_LCTL, KC_F) */
#define A_Q KC_A
#define _S KC_S
#define D KC_D
#define F KC_F

/* #define J MT(MOD_RCTL, KC_J) */
/* #define K MT(MOD_RSFT, KC_K) */
/* #define L MT(MOD_RALT, KC_L) */
/* #define M_Q MT(MOD_RGUI, KC_M) */
/* #define M_A MT(MOD_RGUI, KC_SCLN) */
#define J KC_J
#define K KC_K
#define L KC_L
#define M_Q KC_M
#define M_A KC_SCLN

enum layers {
    _DEFAULT,
    _NUMS,
    _SYMBOLS,
    _EXTRA,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  QK_GESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_PIPE,     A_Q,      _S,       D,       F,    KC_G,                         KC_H,       J,       K,       L,    M_A,  KC_CAPS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MINS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,    KC_2,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_RALT, KC_LSFT,  KC_SPC,     KC_ENT, KC_BSPC,   TO(1)
                                      //`--------------------------'  `--------------------------'
  ),

    [_NUMS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_PEQL,   KC_P7,   KC_P8,   KC_P9, KC_PSLS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_RALT,   KC_LT,   KC_GT, KC_LPRN, KC_RPRN,  KC_GRV,                      KC_PMNS,   KC_P4,   KC_P5,   KC_P6, KC_PPLS, KC_PAST,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,   KC_NO,                        KC_P0,   KC_P1,   KC_P2,   KC_P3, KC_PDOT, KC_PENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            TO(0), KC_LSFT,  KC_SPC,     KC_ENT, KC_BSPC,   TO(2)
                                      //`--------------------------'  `--------------------------'
  ),

    [_SYMBOLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_RALT,   KC_NO, KC_MFFD, KC_MNXT, KC_VOLU, KC_MPLY,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_SLEP, KC_MRWD, KC_MPRV, KC_VOLD, KC_MSTP,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            TO(0), KC_LSFT,  KC_SPC,     KC_ENT, KC_BSPC,   TO(3)
                                      //`--------------------------'  `--------------------------'
  ),

    [_EXTRA] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      RGB_TOG,   KC_NO,   KC_NO,   KC_NO,   KC_NO, BL_TOGG,                      BL_STEP,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,   BL_UP,   BL_ON,                      BL_BRTG, RGB_M_B, RGB_M_K, RGB_M_P, RGB_M_X,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, BL_DOWN,  BL_OFF,                      RGB_M_R,RGB_M_SW, RGB_M_G,RGB_M_SN, RGB_M_T,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            TO(0), KC_LSFT,  KC_SPC,     KC_ENT, KC_BSPC,   KC_NO
                                      //`--------------------------'  `--------------------------'
  ),
};

#ifdef OLED_ENABLE

#include "oled_luna.c"
#include "oled_bongocat.c"

oled_rotation_t oled_init_user(oled_rotation_t const rotation) {
    if (is_keyboard_master()) {
        return is_keyboard_left() ? rotation : OLED_ROTATION_180;
    } else {
        return OLED_ROTATION_270;
    }
}


bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_bongocat();
    } else {
        render_luna_status();
    }
    return false;
}

#endif
