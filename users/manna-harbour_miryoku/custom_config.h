// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// nikroulah custom layout (from keyboards/bastardkb/skeletyl/keymaps/nikroulah).
// Clipboard keys (U_CPY/U_CUT/U_PST/U_UND/U_RDO) become Cmd+C/X/V/Z/Shift-Cmd-Z.
#define MIRYOKU_CLIPBOARD_MAC

// Map every layer slot to the nikroulah alternatives defined in
// miryoku_babel/miryoku_layer_alternatives.h. See the header comment there for
// what each slot holds and how it is reached.
#define MIRYOKU_LAYER_BASE   MIRYOKU_ALTERNATIVES_BASE_NIKROULAH
#define MIRYOKU_LAYER_EXTRA  MIRYOKU_ALTERNATIVES_EXTRA_NIKROULAH
#define MIRYOKU_LAYER_TAP    MIRYOKU_ALTERNATIVES_TAP_NIKROULAH
#define MIRYOKU_LAYER_BUTTON MIRYOKU_ALTERNATIVES_BUTTON_NIKROULAH
#define MIRYOKU_LAYER_NAV    MIRYOKU_ALTERNATIVES_NAV_NIKROULAH
#define MIRYOKU_LAYER_MOUSE  MIRYOKU_ALTERNATIVES_MOUSE_NIKROULAH
#define MIRYOKU_LAYER_MEDIA  MIRYOKU_ALTERNATIVES_MEDIA_NIKROULAH
#define MIRYOKU_LAYER_NUM    MIRYOKU_ALTERNATIVES_NUM_NIKROULAH
#define MIRYOKU_LAYER_SYM    MIRYOKU_ALTERNATIVES_SYM_NIKROULAH
#define MIRYOKU_LAYER_FUN    MIRYOKU_ALTERNATIVES_FUN_NIKROULAH

