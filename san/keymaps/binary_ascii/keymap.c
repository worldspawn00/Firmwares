/* Copyright 2019 Takuya Urakawa (dm9records.com 5z6p.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// If use jis keyboard mode
#include <sendstring_jis.h>


enum custom_keycodes {
  BIN_0 = SAFE_RANGE,
  BIN_1,
  BIN_ENT,
  BIN_BS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(BIN_0,BIN_1,BIN_ENT,BIN_BS)
};

uint8_t code = 0;

void matrix_init_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BIN_0:
      if(record->event.pressed) {
        code = (code << 1) + 0;
      }
      break;
    case BIN_1:
      if(record->event.pressed) {
        code = (code << 1) + 1;
      }
      break;
    case BIN_ENT:
      if(record->event.pressed) {
        send_char(code);
        code = 0;
      }
     break;
    case BIN_BS:
      if(record->event.pressed) {
        if(code != 0) {
          code = 0;
        } else {
          register_code(KC_BSPC);
        }
      } else {
        unregister_code(KC_BSPC);
      }
      break;
    default:
      break;
  }
  return true;
}
