/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2023 @AgingOrange

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

#include "caps_word.h"
#include "config.h"
#include "oled_driver.h"
#include "quantum.h"
#include "send_string_keycodes.h"
#include QMK_KEYBOARD_H
#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include "action_layer.h"
#include "rgblight.h"
#include "keycodes.h"
#include "process_combo.h"
#include "progmem.h"
#include "keycodes.h"
#include "process_tap_dance.h"
#include "quantum_keycodes.h"
#include "keycodes.h"

// Define custom keycodes and layers for readability
enum custom_layers {
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
};

enum custom_keycodes {
    // Key to change OS
    KC_OS = SAFE_RANGE,

    // OS independent keys to change workspace
    WS_1,
    WS_2,
    WS_3,
    WS_4,
    WS_5,
    WS_6,
    WS_7,
    WS_8,
    WS_9,
    WS_0,
    WS_NEXT,
    WS_PREV,

    // Macro keys
    M_PRJ,
    M_CFG,
};

// Define tapdances
enum {
    TD_WSPC,
    TD_LOUT,
};

void dance_layer_to_qwerty(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_move(_QWERTY);
    }
}

void dance_layer_to_colemak(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        layer_move(_COLEMAK);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_WSPC] = ACTION_TAP_DANCE_DOUBLE(G(KC_3), G(KC_2)),
    [TD_LOUT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_layer_to_qwerty, dance_layer_to_colemak)};

// Define RGB timeout
#if defined(RGBLIGHT_ENABLE)
uint32_t rgb_timer;
#    define RGB_TIMEOUT 5 * 60 * 1000
#endif // defined(RGBLIGHT_ENABLE)

// Global to hold OS, we only use macOS and Linux
bool is_macos = true;

// Process keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // We're not processing any key release
    if (!record->event.pressed) {
        return true; // Skip on key release
    }

#if defined(RGBLIGHT_ENABLE)
    // Start the timer and enable the RGB lights on every keypress
    rgb_timer = timer_read32();
    if (!rgblight_is_enabled()) {
        rgblight_enable_noeeprom();
    }
#endif // defined(RGBLIGHT_ENABLE)

    switch (keycode) {
        case KC_OS:
            is_macos = !is_macos; // Toggle the operating system
            return false;

        case WS_1:
            if (is_macos) {
                tap_code16(C(KC_1));
            } else {
                tap_code16(G(KC_1));
            }
            return false;

        case WS_2:
            if (is_macos) {
                tap_code16(C(KC_2));
            } else {
                tap_code16(G(KC_2));
            }
            return false;

        case WS_3:
            if (is_macos) {
                tap_code16(C(KC_3));
            } else {
                tap_code16(G(KC_3));
            }
            return false;

        case WS_4:
            if (is_macos) {
                tap_code16(C(KC_4));
            } else {
                tap_code16(G(KC_4));
            }
            return false;

        case WS_5:
            if (is_macos) {
                tap_code16(C(KC_5));
            } else {
                tap_code16(G(KC_5));
            }
            return false;

        case WS_6:
            if (is_macos) {
                tap_code16(C(KC_6));
            } else {
                tap_code16(G(KC_6));
            }
            return false;

        case WS_7:
            if (is_macos) {
                tap_code16(C(KC_7));
            } else {
                tap_code16(G(KC_7));
            }
            return false;

        case WS_8:
            if (is_macos) {
                tap_code16(C(KC_8));
            } else {
                tap_code16(G(KC_8));
            }
            return false;

        case WS_9:
            if (is_macos) {
                tap_code16(C(KC_9));
            } else {
                tap_code16(G(KC_9));
            }
            return false;

        case WS_0:
            if (is_macos) {
                tap_code16(C(KC_0));
            } else {
                tap_code16(G(KC_0));
            }
            return false;

        case WS_PREV:
            // if (is_macos) {
                tap_code16(C(KC_LEFT));
            // } else {
            //     tap_code16(C(G(KC_UP)));
            // }
            return false;

        case WS_NEXT:
            // if (is_macos) {
                tap_code16(C(KC_RGHT));
            // } else {
            //     tap_code16(C(G(KC_DOWN)));
            // }
            return false;

        case M_CFG:
            SEND_STRING("_cfg\n");
            return false;

        case M_PRJ:
            SEND_STRING("_prj\n");
            return false;
    }

    return true;
}

// Check RGB timeout
#if defined(RGBLIGHT_ENABLE)
void matrix_scan_user(void) {
    if (timer_elapsed32(rgb_timer) > RGB_TIMEOUT) {
        rgblight_disable_noeeprom();
    }
}
#endif // defined(RGBLIGHT_ENABLE)

// Define QWERTY home row mods
#define G_T_A GUI_T(KC_A)
#define A_T_S ALT_T(KC_S)
#define C_T_D CTL_T(KC_D)
#define S_T_F SFT_T(KC_F)
#define S_T_J RSFT_T(KC_J)
#define C_T_K CTL_T(KC_K)
#define A_T_L ALT_T(KC_L)
#define G_T_SC GUI_T(KC_SCLN)

// Define Colemak home row mods
// G_T_A is already defined
#define A_T_R ALT_T(KC_R)
#define C_T_S CTL_T(KC_S)
#define S_T_T SFT_T(KC_T)
#define S_T_N RSFT_T(KC_N)
#define C_T_E CTL_T(KC_E)
#define A_T_I ALT_T(KC_I)
#define G_T_O GUI_T(KC_O)

// Define thumb keys
#define LTL_AGR LT(_LOWER, KC_ALGR)
#define LTR_BSP LT(_RAISE, KC_BSPC)
#define S_T_GUI MT(MOD_LSFT, KC_LGUI)

// Define extra keys for sixth column, etc.
#define GO_QWER TO(_QWERTY)
#define WS_PREV LCTL(LGUI(KC_K))
#define WS_NEXT LCTL(LGUI(KC_J))
#define S_CAPS S(KC_CAPS)

// Define combos
enum combos {
    // QWERTY
    SD_GRV,
    DF_BSPC,
    SF_TAB,
    CV_MINS,
    KL_QUOT,
    KJ_ESC,
    JL_BSLS,
    MCOMM_EQL,
    // COLEMAK
    RS_GRV,
    ST_BSPC,
    RT_TAB,
    CD_MINS,
    EI_QUOT,
    NE_ESC,
    NI_BSLS,
    HCOMM_EQL,
};

// Define combo action keys
// QWERTY
const uint16_t PROGMEM sd_combo[]    = {A_T_S, C_T_D, COMBO_END};
const uint16_t PROGMEM df_combo[]    = {C_T_D, S_T_F, COMBO_END};
const uint16_t PROGMEM sf_combo[]    = {A_T_S, S_T_F, COMBO_END};
const uint16_t PROGMEM cv_combo[]    = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM kl_combo[]    = {C_T_K, A_T_L, COMBO_END};
const uint16_t PROGMEM kj_combo[]    = {C_T_K, S_T_J, COMBO_END};
const uint16_t PROGMEM jl_combo[]    = {S_T_J, A_T_L, COMBO_END};
const uint16_t PROGMEM mcomm_combo[] = {KC_M, KC_COMM, COMBO_END};
// Colemak
const uint16_t PROGMEM rs_combo[]    = {A_T_R, C_T_S, COMBO_END};
const uint16_t PROGMEM st_combo[]    = {C_T_S, S_T_T, COMBO_END};
const uint16_t PROGMEM rt_combo[]    = {A_T_R, S_T_T, COMBO_END};
const uint16_t PROGMEM cd_combo[]    = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM ei_combo[]    = {C_T_E, A_T_I, COMBO_END};
const uint16_t PROGMEM ne_combo[]    = {S_T_N, C_T_E, COMBO_END};
const uint16_t PROGMEM ni_combo[]    = {S_T_N, A_T_I, COMBO_END};
const uint16_t PROGMEM hcomm_combo[] = {KC_H, KC_COMM, COMBO_END};

// Define combo actions
combo_t key_combos[] = {
    // QWERTY
    [SD_GRV]    = COMBO(sd_combo, KC_GRV),
    [DF_BSPC]   = COMBO(df_combo, KC_BSPC),
    [SF_TAB]    = COMBO(sf_combo, KC_TAB),
    [CV_MINS]   = COMBO(cv_combo, KC_MINS),
    [KL_QUOT]   = COMBO(kl_combo, KC_QUOT),
    [KJ_ESC]    = COMBO(kj_combo, KC_ESC),
    [JL_BSLS]   = COMBO(jl_combo, KC_BSLS),
    [MCOMM_EQL] = COMBO(mcomm_combo, KC_EQL),
    // Colemak
    [RS_GRV]    = COMBO(rs_combo, KC_GRV),
    [ST_BSPC]   = COMBO(st_combo, KC_BSPC),
    [RT_TAB]    = COMBO(rt_combo, KC_TAB),
    [CD_MINS]   = COMBO(cd_combo, KC_MINS),
    [EI_QUOT]   = COMBO(ei_combo, KC_QUOT),
    [NE_ESC]    = COMBO(ne_combo, KC_ESC),
    [NI_BSLS]   = COMBO(ni_combo, KC_BSLS),
    [HCOMM_EQL] = COMBO(hcomm_combo, KC_EQL),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (layer_state_is(_QWERTY)) {
        switch (combo_index) {
            case SD_GRV:
                if (pressed) {
                    tap_code16(KC_GRV);
                }
                break;
            case DF_BSPC:
                if (pressed) {
                    tap_code16(KC_BSPC);
                }
                break;
            case SF_TAB:
                if (pressed) {
                    tap_code16(KC_TAB);
                }
                break;
            case CV_MINS:
                if (pressed) {
                    tap_code16(KC_MINS);
                }
                break;
            case KL_QUOT:
                if (pressed) {
                    tap_code16(KC_QUOT);
                }
                break;
            case KJ_ESC:
                if (pressed) {
                    tap_code16(KC_ESC);
                }
                break;
            case JL_BSLS:
                if (pressed) {
                    tap_code16(KC_BSPC);
                }
                break;
            case MCOMM_EQL:
                if (pressed) {
                    tap_code16(KC_EQL);
                }
                break;
        }
    } else if (layer_state_is(_COLEMAK)) {
        switch (combo_index) {
            case RS_GRV:
                if (pressed) {
                    tap_code16(KC_GRV);
                }
                break;
            case ST_BSPC:
                if (pressed) {
                    tap_code16(KC_BSPC);
                }
                break;
            case RT_TAB:
                if (pressed) {
                    tap_code16(KC_TAB);
                }
                break;
            case CD_MINS:
                if (pressed) {
                    tap_code16(KC_MINS);
                }
                break;
            case EI_QUOT:
                if (pressed) {
                    tap_code16(KC_QUOT);
                }
                break;
            case NE_ESC:
                if (pressed) {
                    tap_code16(KC_ESC);
                }
                break;
            case NI_BSLS:
                if (pressed) {
                    tap_code16(KC_BSPC);
                }
                break;
            case HCOMM_EQL:
                if (pressed) {
                    tap_code16(KC_EQL);
                }
                break;
        }
    }
}

// Define keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_QWERTY] = LAYOUT_split_3x6_3(
        TD(TD_LOUT),KC_Q,      KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_OS,
        KC_LCTL,    G_T_A,     A_T_S,      C_T_D,      S_T_F,      KC_G,       KC_H,       S_T_J,      C_T_K,      A_T_L,      G_T_SC,     WS_PREV,
        KC_LSFT,    KC_Z,      KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    WS_NEXT,
                                           KC_LALT,    KC_ENT,     LTL_AGR,    LTR_BSP,    KC_SPC,     S_T_GUI
    ),

    [_COLEMAK] = LAYOUT_split_3x6_3(
        _______,    KC_Q,      KC_W,       KC_F,       KC_P,       KC_B,       KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN,    _______,
        _______,    G_T_A,     A_T_R,      C_T_S,      S_T_T,      KC_G,       KC_M,       S_T_N,      C_T_E,      A_T_I,      G_T_O,      _______,
        _______,    KC_Z,      KC_X,       KC_C,       KC_D,       KC_V,       KC_K,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH,    _______,
                                           _______,    _______,    _______,    _______,    _______,    _______
    ),

    [_LOWER] = LAYOUT_split_3x6_3(
        _______,    WS_1  ,     WS_2  ,     WS_3  ,     WS_4  ,     WS_5  ,     WS_6  ,     WS_7  ,     WS_8  ,     WS_9  ,     WS_0  ,     _______,
        _______,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       _______,
        _______,    XXXXXXX,    KC_CUT,     KC_COPY,    KC_PSTE,    QK_REP,     KC_APP,     KC_LBRC,    KC_RBRC,    S(KC_9),    S(KC_0),    _______,
                                            _______,    _______,    _______,    _______,    _______,    _______
    ),

    [_RAISE] = LAYOUT_split_3x6_3(
        _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     _______,
        _______,    KC_F11,     KC_F12,     KC_BRIU,    KC_VOLU,    KC_PSCR,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    C(KC_HOME), _______,
        _______,    M_PRJ,      M_CFG,      KC_BRID,    KC_VOLD,    S_CAPS,     KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     C(KC_END),  _______,
                                            _______,    _______,    _______,    _______,    _______,    _______
    )
    // clang-format on
};

// Define tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case G_T_A:
        case A_T_S:
        case C_T_D:
        case S_T_F:
        case S_T_J:
        case C_T_K:
        case A_T_L:
        case G_T_SC:
            return TAPPING_TERM_HOMEROW_MODS;
        default:
            return TAPPING_TERM;
    }
}

// Set layer state
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        // case _QWERTY:
        case _COLEMAK:
            rgblight_sethsv(HSV_YELLOW_DIM);
            break;
        case _LOWER:
            rgblight_sethsv(HSV_GREEN_DIM);
            break;
        case _RAISE:
            rgblight_sethsv(HSV_RED_DIM);
            break;
        default:
            // For any other layers, or the default layer
            rgblight_sethsv(HSV_DEFAULT);
            break;
    }
    return state;
}

#ifdef OLED_ENABLE
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
        0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA,
        0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5,
        0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};

    oled_write_P(qmk_logo, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }

    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_ln_P(is_macos ? PSTR("macOS") : PSTR("Linux"), false);

        oled_write_ln_P("", false);

        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                oled_write_ln_P(PSTR("QWERT"), false);
                break;
            case _COLEMAK:
                oled_write_ln_P(PSTR("COLEM"), false);
                break;
            case _LOWER:
                oled_write_ln_P(PSTR("LOWER"), false);
                break;
            case _RAISE:
                oled_write_ln_P(PSTR("RAISE"), false);
                break;
            default:
                oled_write_ln_P(PSTR("?????"), false);
        }

        oled_write_ln_P("", false);

        // Assume either CapsLock or CapsWord is on, not both
        led_t led_state = host_keyboard_led_state();
        if (led_state.caps_lock) {
            oled_write_ln_P(PSTR("CapsL"), false);
        } else if (is_caps_word_on()) {
            oled_write_ln_P(PSTR("CapsW"), false);
        } else {
            oled_write_ln_P(PSTR("     "), false);
        }

    } else {
        render_logo();
    }

    return false;
}

#endif

// Initialize keyboard
void keyboard_post_init_user(void) {
    rgblight_sethsv(HSV_DEFAULT);
}
