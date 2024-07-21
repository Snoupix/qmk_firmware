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

#include "action_layer.h"
#include "keyboard.h"
#include "keycodes.h"
#include "keymap_french.h"
#include "quantum.h"
#include "transactions.h"
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
#define _GR LSFT_T(KC_GRV)
#define _LP LALT_T(KC_LPRN)
#define _RP LGUI_T(KC_RPRN)

// Special tap dance
#define _AND TD(TD_AND)
#define _OR TD(TD_OR)
#define _EXC TD(TD_EXC)

#define _LEFT TD(TD_MINUS)
#define _DOWN TD(TD_4)
#define _UP TD(TD_5)
#define _RIGHT TD(TD_6)

#define _A TD(TD_A)
#define _Z TD(TD_Z)
#define _R TD(TD_R)
#define _C TD(TD_C)

#define _CAPS TD(TD_CAPS)
#define _ESC TD(TD_ESC)
#define _LYR TD(TD_LYR)

typedef struct Globals {
    bool is_oled_on;
    bool is_alt_tab_active;
    bool is_esc_caps_swapped;
    uint16_t alt_tab_timer;
} globals_t;

static globals_t globals = {
    .is_oled_on = true,
    .is_alt_tab_active = false,
    .is_esc_caps_swapped = false,
    .alt_tab_timer = 0,
};

uint32_t last_activity = 0;

enum layers {
    _DEFAULT,
    _NUMS,
    _SYMBOLS,
    _EXTRA,
    _GAMING,
    _GAMING2,
    // _RTS,
};

enum tap_dance {
    TD_AND,
    TD_OR,
    TD_EXC,

    TD_MINUS,
    TD_4,
    TD_5,
    TD_6,

    TD_A,
    TD_Z,
    TD_R,
    TD_Q,
    TD_C,

    TD_ESC,
    TD_CAPS,
    TD_LYR,
};

enum custom_keycodes {
    TOG_OLED = SAFE_RANGE,
};

void q_key_fn(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
    case 1: // One shot press
        if (globals.is_alt_tab_active) {
            globals.alt_tab_timer = timer_read();
        }

        tap_code16(globals.is_alt_tab_active ? KC_TAB : KC_Q);
        break;
    case 2: // Double tap dance triggered
        if (globals.is_alt_tab_active) {
            unregister_code(KC_LALT);
            globals.is_alt_tab_active = false;
            return;
        }

        register_code(KC_LALT);
        globals.is_alt_tab_active = true;
        globals.alt_tab_timer = timer_read();
        break;
    }
}

void a_key_fn(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
    case 1:
        switch (get_highest_layer(layer_state)) {
            case _DEFAULT:
                tap_code16(KC_A);
                break;
            case _GAMING:
                tap_code16(KC_Q);
                break;
        }
        break;
    case 2:
        tap_code16(FR_AGRV);
        break;
    }
}

void z_key_fn(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
    case 3: // Need to zz in nvim so fuck that
        tap_code16(FR_EURO);
        break;
    default:
        for (uint8_t i = 0; i < state->count; i += 1) {
            tap_code16(KC_Z);
        }
        break;
    }
}

void c_key_fn(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
    case 1:
        tap_code16(KC_C);
        break;
    case 2:
        tap_code16(FR_CCED);
        break;
    }
}

// Changed it from e to r because a lot of words needs a double e and that was annoying
void r_key_fn(tap_dance_state_t *state, void *user_data) {
    /* if (!globals.is_q_held) {
        for (uint8_t i = 0; i < state->count; i += 1) {
            tap_code16(KC_E);
        }
        return;
    }

    switch (state->count) {
    case 1:
        tap_code16(FR_EACU);
        break;
    case 2:
        tap_code16(FR_EGRV);
        break;
    case 3:
        tap_code16(FR_CIRC);
        break;
    } */
    switch (state->count) {
    case 1:
        tap_code16(KC_R);
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

void esc_key_fn(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
    case 1:
        tap_code16(globals.is_esc_caps_swapped ? KC_CAPS : KC_ESC);
        break;
    case 4: // Since it's meant to be used on kb changes, not often
        globals.is_esc_caps_swapped = !globals.is_esc_caps_swapped;
        break;
    }
}

void caps_key_fn(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
    case 1:
        tap_code16(globals.is_esc_caps_swapped ? KC_ESC : KC_CAPS);
        break;
    case 2:
    case 3:
        break;
    default:
        globals.is_esc_caps_swapped = !globals.is_esc_caps_swapped;
        break;
    }
}

void layer_key_fn(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
    case 2:
        layer_move(_GAMING);
        break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_AND] = ACTION_TAP_DANCE_DOUBLE(KC_UNDS, KC_PIPE),
    [TD_OR] = ACTION_TAP_DANCE_DOUBLE(KC_TILD, KC_AMPR),
    [TD_EXC] = ACTION_TAP_DANCE_DOUBLE(KC_EXLM, KC_QUES),

    [TD_MINUS] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_LEFT),
    [TD_4] = ACTION_TAP_DANCE_DOUBLE(KC_4, KC_DOWN),
    [TD_5] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_UP),
    [TD_6] = ACTION_TAP_DANCE_DOUBLE(KC_6, KC_RIGHT),

    [TD_A] = ACTION_TAP_DANCE_FN(a_key_fn),
    [TD_Z] = ACTION_TAP_DANCE_FN(z_key_fn),
    [TD_R] = ACTION_TAP_DANCE_FN(r_key_fn),
    [TD_Q] = ACTION_TAP_DANCE_FN(q_key_fn),
    [TD_C] = ACTION_TAP_DANCE_FN(c_key_fn),

    [TD_ESC] = ACTION_TAP_DANCE_FN(esc_key_fn),
    [TD_CAPS] = ACTION_TAP_DANCE_FN(caps_key_fn),

    [TD_LYR] = ACTION_TAP_DANCE_FN(layer_key_fn),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,      _A,      _Z,    KC_E,      _R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   _CAPS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         _ESC,      _Q,      _S,      _D,      _F,      _G,                           _H,      _J,      _K,      _L,    KC_M,    _AND,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         _EXC,    KC_W,    KC_X,      _C,    KC_V,    KC_B,                         KC_N, KC_SCLN, KC_COMM,  KC_DOT, KC_SLSH,     _OR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             _ESC,    _LYR,  KC_SPC,    KC_BSPC,  KC_ENT,   MO(1)
                                      //`--------------------------'  `--------------------------'
  ),

    [_NUMS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_EQL,    KC_7,    KC_8,    KC_9, KC_PSLS, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,   KC_LT,     _GT,     _GR,     _LP,     _RP,                        _LEFT,   _DOWN,     _UP,  _RIGHT, KC_PPLS, KC_PAST,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_QUOT,                         KC_0,    KC_1,    KC_2,    KC_3, KC_PDOT, KC_PENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            TO(2), KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS,   KC_NO
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
      RGB_TOG,TOG_OLED,   KC_NO,   KC_NO,   KC_NO, BL_TOGG,                      BL_STEP,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,   BL_ON,                      BL_BRTG, RGB_M_B, RGB_M_K, RGB_M_P, RGB_M_X,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,  BL_OFF,                      RGB_M_R,RGB_M_SW, RGB_M_G,RGB_M_SN, RGB_M_T,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            TO(0), KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS,   KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

    [_GAMING] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   _CAPS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                           _H,      _J,      _K,      _L, KC_SCLN,    _AND,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,     _OR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             _ESC, KC_LALT,  KC_SPC,    KC_BSPC,  KC_ENT,   MO(5)
                                      //`--------------------------'  `--------------------------'
  ),

    [_GAMING2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   _CAPS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,                       KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            TO(0), KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS,   KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

    // TODO
    /* [_RTS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   _CAPS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                           _H,      _J,      _K,      _L, KC_SCLN,    _AND,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,     _OR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             _ESC, KC_LALT,  KC_SPC,    KC_BSPC,  KC_ENT,   MO(5)
                                      //`--------------------------'  `--------------------------'
  ), */
};

void master_to_slave_sync(uint8_t in_buflen, const void* in_data, uint8_t _out_buflen, void* _out_data) {
    const globals_t *m_data = (const globals_t*)in_data;

    globals.is_oled_on = m_data->is_oled_on;
    globals.alt_tab_timer = m_data->alt_tab_timer;
    globals.is_alt_tab_active = m_data->is_alt_tab_active;
    globals.is_esc_caps_swapped = m_data->is_esc_caps_swapped;
}

void keyboard_post_init_user(void) {
    /* debug_enable=true;
    debug_matrix=false;
    debug_keyboard=false; */
    transaction_register_rpc(M2S_SYNC, master_to_slave_sync);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        static uint32_t last_sync = 0;

        if (timer_elapsed32(last_sync) > M2S_SYNC_RATE_MS) {
            // this returns bool of success; currently making it retry faster on fail
            if (!transaction_rpc_send(M2S_SYNC, sizeof(globals), &globals)) {
                return;
            }
            last_sync = timer_read32();
        }
    }
}

void matrix_scan_user(void) {
    if (globals.is_alt_tab_active && timer_elapsed(globals.alt_tab_timer) > 750) {
        unregister_code(KC_LALT);
        globals.is_alt_tab_active = false;
    }
}

#ifdef OLED_ENABLE

#include "oled_left.c" // Bongocat
#include "oled_right.c" // Luna & layer display

oled_rotation_t oled_init_user(oled_rotation_t const rotation) {
    if (is_keyboard_master()) {
        return is_keyboard_left() ? rotation : OLED_ROTATION_180;
    } else {
        return OLED_ROTATION_270;
    }
}

bool oled_task_user(void) {
    current_wpm = get_current_wpm();
    led_usb_state = host_keyboard_led_state();
    last_activity = last_matrix_activity_time();

    if (is_keyboard_master()) {
        render_bongocat();
    } else {
        #ifdef OLD_LUNA
        render_luna_status();
        #else
        print_status_narrow();
        #endif
    }
    return false;
}

void process_record_user_oled(uint16_t *keycode, keyrecord_t *record) {
    switch (*keycode) {
    case TOG_OLED:
        if (record->event.pressed) {
            globals.is_oled_on = !globals.is_oled_on;
        }
        break;
    case KC_LCTL:
    case KC_RCTL:
        is_sneaking = record->event.pressed;
        break;
    /* case KC_SPC:
        is_jumping = record->event.pressed;
        if (is_jumping) {
            showed_jump = false;
        }
        break; */
    case KC_CAPS:
        is_barking = record->event.pressed;
        break;
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    default:
        #ifdef OLED_ENABLE
        process_record_user_oled(&keycode, record);
        #endif
        break;
    }

    return true;
}
