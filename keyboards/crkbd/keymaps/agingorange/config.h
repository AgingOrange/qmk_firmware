/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
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

#pragma once

#define MASTER_LEFT

#define NO_AUTO_SHIFT_ALPHA
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// #define QUICK_TAP_TERM 0
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define TAPPING_TERM_HOMEROW_MODS 200
#define PERMISSIVE_HOLD
// #define HOLD_ON_OTHER_KEY_PRESS

#define ONESHOT_TAP_TOGGLE 3
#define ONESHOT_TIMEOUT 2000

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    define HSV_GREEN_DIM 85, 255, 50
#    define HSV_RED_DIM 0, 255, 50
#    define HSV_YELLOW_DIM 40, 255, 50
#    define HSV_WHITE_DIM 0, 0, 50
#    define HSV_DEFAULT HSV_WHITE_DIM
#endif // defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)

#if defined(RGBLIGHT_ENABLE)
#    define RGBLIGHT_SLEEP
#endif // defined(RGBLIGHT_ENABLE)

#if defined(OLED_ENABLE)
#    define OLED_BRIGHTNESS 128
#endif // defined(OLED_ENABLE)
