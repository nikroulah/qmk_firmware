// Copyright 2024 ZSA Technology Labs, Inc <@zsa>
// SPDX-License-Identifier: GPL-2.0-or-later
//
#pragma once
#include "quantum.h"
// List of ZSA specific keycodes, appended to the end of the keycode list.
//
// nikroulah forward-port: mainline QMK's keyboards/zsa/voyager/voyager.h already
// defines TOGGLE_LAYER_COLOR / LED_LEVEL at QK_KB (ZSA's own fork moved them out
// of the board and into this module, so their voyager.h omits them). Defining
// them here too collides. The board owns those two keycodes; keep only the
// safe-range marker (unused by the modules we load).
enum zsa_keycodes {
    ZSA_SAFE_RANGE = QK_KB
};
