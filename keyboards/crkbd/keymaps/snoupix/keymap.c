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

#include "keycodes.h"
#include "keymap_french.h"
#include "quantum.h"
#include QMK_KEYBOARD_H

// Home row mods start
#define SUPER KC_LEFT_GUI
#define _Q TD(TD_Q)
#define _S LCTL_T(KC_S)
#define _D LSFT_T(KC_D)
#define _F LALT_T(KC_F)
#define _G LGUI_T(KC_G)

#define _H RGUI_T(KC_H)
#define _J RALT_T(KC_J)
#define _K RSFT_T(KC_K)
#define _L RCTL_T(KC_L)
// Home row mods end

// Home row mods layer 2 left side
#define _GT LCTL_T(KC_GT)
#define _LP LSFT_T(KC_LPRN)
#define _RP LALT_T(KC_RPRN)
#define _GR LGUI_T(KC_GRV)

// Special tap dance
#define _AND TD(TD_AND)
#define _OR TD(TD_OR)
#define _EXC TD(TD_EXC)

#define _LEFT TD(TD_MINUS)
#define _DOWN TD(TD_4)
#define _UP TD(TD_5)
#define _RIGHT TD(TD_6)

#define _CAPS KC_ESC
#define _ESC KC_CAPS
#define _A TD(TD_A)
#define _Z TD(TD_Z)
#define _E TD(TD_E)
#define _C TD(TD_C)

enum layers {
    _DEFAULT,
    _NUMS,
    _SYMBOLS,
    _EXTRA,
};

enum tap_dance {
    /*
    TD_S,
    TD_D,
    TD_F,
    TD_G,

    TD_H,
    TD_J,
    TD_K,
    TD_L,
    */

    TD_AND,
    TD_OR,
    TD_EXC,

    TD_MINUS,
    TD_4,
    TD_5,
    TD_6,

    TD_A,
    TD_Z,
    TD_E,
    TD_Q,
    TD_C,
};

bool is_ctrl_gui_active = false;
uint16_t ctrl_gui_timer = 0;

void q_key_fn(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1: // One shot press
            tap_code(KC_Q);
            break;
        case 2: // Double tap dance triggered
            if (is_ctrl_gui_active) {
                unregister_code(SUPER);
                unregister_code(KC_LCTL);
                is_ctrl_gui_active = false;
                return;
            }

            register_code(SUPER);
            register_code(KC_LCTL);
            is_ctrl_gui_active = true;
            ctrl_gui_timer = timer_read();
            break;
    }
}

void a_key_fn(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code(KC_A);
            break;
        case 2:
            tap_code16(FR_AGRV);
            break;
    }
}

void z_key_fn(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code(KC_Z);
            break;
        case 2:
            tap_code16(FR_EURO);
            break;
    }
}

void c_key_fn(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code(KC_C);
            break;
        case 2:
            tap_code16(FR_CCED);
            break;
    }
}

void e_key_fn(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(KC_E);
            break;
        case 2:
            tap_code16(FR_EACU);
            break;
        case 3:
            tap_code16(FR_EGRV);
            break;
        case 4:
            tap_code16(FR_CIRC);
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    /*
    [TD_S] = ACTION_TAP_DANCE_DOUBLE(KC_S, KC_LCTL),
    [TD_D] = ACTION_TAP_DANCE_DOUBLE(KC_D, KC_LSFT),
    [TD_F] = ACTION_TAP_DANCE_DOUBLE(KC_F, KC_LALT),
    [TD_G] = ACTION_TAP_DANCE_DOUBLE(KC_G, SUPER,

    [TD_H] = ACTION_TAP_DANCE_DOUBLE(KC_H, SUPER),
    [TD_J] = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_RALT),
    [TD_K] = ACTION_TAP_DANCE_DOUBLE(KC_K, KC_RSFT),
    [TD_L] = ACTION_TAP_DANCE_DOUBLE(KC_L, KC_RCTL),
    */

    [TD_AND] = ACTION_TAP_DANCE_DOUBLE(KC_UNDS, KC_PIPE),
    [TD_OR] = ACTION_TAP_DANCE_DOUBLE(KC_TILD, KC_AMPR),
    [TD_EXC] = ACTION_TAP_DANCE_DOUBLE(KC_EXLM, KC_QUES),

    [TD_MINUS] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_LEFT),
    [TD_4] = ACTION_TAP_DANCE_DOUBLE(KC_4, KC_DOWN),
    [TD_5] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_UP),
    [TD_6] = ACTION_TAP_DANCE_DOUBLE(KC_6, KC_RIGHT),

    [TD_A] = ACTION_TAP_DANCE_FN(a_key_fn),
    [TD_Z] = ACTION_TAP_DANCE_FN(z_key_fn),
    [TD_E] = ACTION_TAP_DANCE_FN(e_key_fn),
    [TD_Q] = ACTION_TAP_DANCE_FN(q_key_fn),
    [TD_C] = ACTION_TAP_DANCE_FN(c_key_fn),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,      _A,      _Z,      _E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   _CAPS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         _ESC,      _Q,      _S,      _D,      _F,      _G,                           _H,      _J,      _K,      _L,    KC_M,    _AND,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         _EXC,    KC_W,    KC_X,      _C,    KC_V,    KC_B,                         KC_N, KC_SCLN, KC_COMM,  KC_DOT, KC_SLSH,     _OR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             _ESC, KC_LSFT,  KC_SPC,    KC_BSPC,  KC_ENT,   TO(1)
                                      //`--------------------------'  `--------------------------'
  ),

    [_NUMS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_PEQL,    KC_7,    KC_8,    KC_9, KC_PSLS,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,   KC_LT,     _GT,     _LP,     _RP,     _GR,                        _LEFT,   _DOWN,     _UP,  _RIGHT, KC_PPLS, KC_PAST,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_QUOT,                         KC_0,    KC_1,    KC_2,    KC_3, KC_PDOT, KC_PENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            TO(0), KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS,   TO(2)
                                      //`--------------------------'  `--------------------------'
  ),

    [_SYMBOLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,   KC_NO, KC_MFFD, KC_MNXT, KC_VOLU, KC_MPLY,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_SLEP, KC_MRWD, KC_MPRV, KC_VOLD, KC_MSTP,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            TO(0), KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS,   TO(3)
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
                                            TO(0), KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS,   KC_NO
                                      //`--------------------------'  `--------------------------'
  ),
};

/*
void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_matrix=false;
    debug_keyboard=false;
}
*/

void matrix_scan_user(void) {
    if (is_ctrl_gui_active && timer_elapsed(ctrl_gui_timer) > 1000) {
        unregister_code(SUPER);
        unregister_code(KC_LCTL);
        is_ctrl_gui_active = false;
    }
}

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_A:
        if (record->event.pressed) {
            oled_status = true;
        } else {
            oled_status = false;
        }
        break;
    }
    return true;
}
*/

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
