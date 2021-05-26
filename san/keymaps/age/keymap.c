/*
Copyright 2019 Takuya Urakawa (dm9records.com 5z6p.com)
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
#include <stdlib.h>

enum custom_keycodes {
    AGE_0 = SAFE_RANGE,
    AGE_1,
    AGE_2
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{{AGE_0, AGE_1, AGE_2}}};

const char age[24][64] = {
    "              XXXX  XXXXXX  XXXX                    \n",
    "            XX    XX      XX    XX                  \n",
    "            XX                  XX                  \n",
    "              XXXXXXXXXXXXXXXXXX                    \n",
    "          XXXX                  XXXX                \n",
    "        XX                          XX              \n",
    "      XX                              XX            \n",
    "    XX        XXXXXX      XXXXXX        XX          \n",
    "    XX      XX      XX  XX      XX      XX          \n",
    "  XX      XX    XX    XX    XX    XX      XXXXXXXX  \n",
    "  XX      XX  XX  XX  XX  XX  XX  XX      XX      XX\n",
    "  XX      XX          XX          XX      XX      XX\n",
    "  XX      XX          XX          XX      XX  XXXX  \n",
    "  XX        XX      XX  XX      XX        XX      XX\n",
    "  XX          XXXXXX      XXXXXX          XX      XX\n",
    "  XX                                      XXXXXXXX  \n",
    "    XX                                  XX          \n",
    "      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX            \n",
    "            XXXXXX          XXXXXX                  \n",
    "          XX  XX              XX  XX    XX          \n",
    "        XX  XX                  XX  XXXX  XX        \n",
    "          XX  XX                  XX      XX        \n",
    "        XX      XX                  XX  XX          \n",
    "        XXXXXXXXXX                    XX            \n"
};

void matrix_init_user(void) { srand(255); }

void send_katakana(const char* str) {
    SEND_STRING(str);
    wait_ms(10);
    SEND_STRING(SS_TAP(X_SPACE));
    wait_ms(20);
    SEND_STRING(SS_TAP(X_ENTER));
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case AGE_0:
            if (record->event.pressed) {
                send_katakana("age");
                return false;
            }
            break;
        case AGE_1:
            if (record->event.pressed) {
                send_katakana("juwa");
                return false;
            }
            break;
        case AGE_2:
            if (record->event.pressed) {
                for(uint8_t i=0; i<24; i++) {
                    send_string(age[i]);
                }
                return false;
            }
            break;
        default:
            break;
    }
    return true;
}

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   return true;
// }
