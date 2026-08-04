// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// ZSA community modules (declared in this dir's keymap.json). The automouse
// module needs the target layer: our Miryoku MOUSE layer is enum slot 5 (order:
// 0 BASE, 1 EXTRA, 2 TAP, 3 BUTTON, 4 NAV, 5 MOUSE, ...). Moving the Navigator
// pointer momentarily activates MOUSE (which carries the mouse buttons).
#define AUTOMOUSE_LAYER 5

// nikroulah Miryoku mapping for the ZSA Voyager (52 keys: 6 cols x 4 rows +
// 2 thumbs per side). The Voyager has only 2 thumbs/side, so it reuses the
// SWEEP layout macros (selected in users/nikroulah/config.h by the
// KEYBOARD_zsa_voyager guard). This mapping ports Miryoku's 3x5 + 2 thumbs onto
// the Voyager physical LAYOUT:
//   - rows: Voyager rows 1-3 (QWERTY top / home / bottom); the top row 0 (the
//     number row) is unused.
//   - columns: the inner 5 finger columns each hand (x=1..5 left, x=10..14
//     right); the OUTER extra column each hand (x=0 / x=15, which the stock
//     Voyager keymap gives to Backspace/mods) is unused.
//   - thumbs: both thumbs per side. K33/K34 -> left outer/inner, K35/K36 ->
//     right inner/outer, matching the sweep's inner/outer thumb assignment.
// Every unused physical key is KC_NO. (One expected tradeoff of 5-on-6: the
// right pinky ' lands on the physical ; keycap; the printed ' cap is unused.)
// The usual 40 Miryoku args, plus 9 EXTRA slots (E0..E8) for the Voyager's
// otherwise-unused physical keys. Each layer supplies its own E0..E8 (see the
// *_VOYAGER macros in users/nikroulah/miryoku_nikroulah_alternatives.h), so the
// extra keys are addressable per layer -- inert on most layers, RGB on MEDIA.
//   E0..E5 -> right-hand top row, inner->outer
//   E6 / E7 / E8 -> right outer (6th) column on the three finger rows
// The left-hand top row and left outer column stay KC_NO (unmapped for now).
#define LAYOUT_miryoku( \
K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09, \
K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19, \
K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29, \
N30,   N31,   K32,   K33,   K34,          K35,   K36,   K37,   N38,   N39, \
E0,    E1,    E2,    E3,    E4,    E5,    E6,    E7,    E8 \
) \
LAYOUT( \
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       E0,    E1,    E2,    E3,    E4,    E5,   \
KC_NO, K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09,   E6,   \
KC_NO, K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19,   E7,   \
KC_NO, K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29,   E8,   \
                            K33,   K34,          K35,   K36 \
)
