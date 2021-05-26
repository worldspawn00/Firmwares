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


enum custom_keycodes {
  BIN_0 = SAFE_RANGE,
  BIN_1,
  BIN_ENT,
  BIN_BS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(BIN_0,BIN_1,BIN_ENT,BIN_BS)
};

uint32_t code = 0;

void register_hex32(uint32_t hex) {
  bool onzerostart = true;
  for(int i = 7; i >= 0; i--) {
    if (i <= 3) {
      onzerostart = false;
    }
    uint8_t digit = ((hex >> (i*4)) & 0xF);
    if (digit == 0) {
      if (!onzerostart) {
        register_code(hex_to_keycode(digit));
        unregister_code(hex_to_keycode(digit));
      }
    } else {
      register_code(hex_to_keycode(digit));
      unregister_code(hex_to_keycode(digit));
      onzerostart = false;
    }
  }
}

bool send_unicode(uint32_t code) {
  uint8_t input_mode = get_unicode_input_mode();
  if (code > 0xFFFF && code <= 0x10ffff && input_mode == UC_OSX) {
    // Convert to UTF-16 surrogate pair
    code -= 0x10000;
    uint32_t lo = code & 0x3ff;
    uint32_t hi = (code & 0xffc00) >> 10;
    unicode_input_start();
    register_hex32(hi + 0xd800);
    register_hex32(lo + 0xdc00);
    unicode_input_finish();
  } else if ((code > 0x10ffff && input_mode == UC_OSX) || (code > 0xFFFFF && input_mode == UC_LNX)) {
    // when character is out of range supported by the OS
    return false;
  } else {
    unicode_input_start();
    register_hex32(code);
    unicode_input_finish();
  }
  return true;
}



void matrix_init_user(void) {
  set_unicode_input_mode(UC_LNX);
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
        send_unicode(code);
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
