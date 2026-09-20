// nikroulah custom Miryoku layer alternatives.
//
// Moved out of the pristine users/manna-harbour_miryoku/miryoku_babel/
// miryoku_layer_alternatives.h so that the miryoku userspace matches its
// remote exactly. Included from users/nikroulah/config.h (before the babel
// layer-selection runs), so the MIRYOKU_LAYER_* overrides there resolve to
// these MIRYOKU_ALTERNATIVES_*_{NIKROULAH,SWEEP} / _BLANK macros.

#pragma once

// ============================================================================
// nikroulah custom layout
// Source: keyboards/bastardkb/skeletyl/keymaps/nikroulah/keymap.json
// - Home-row mods in SCAG order (Shift on the pinkies, Gui on the index),
//   right hand uses RGUI/RALT/RCTL/RSFT.
// - Outer-pinky bottom-row keys are LT(U_BUTTON, ...).
// - Clipboard keys use the U_CPY/U_CUT/U_PST/U_UND macros, so they follow
//   MIRYOKU_CLIPBOARD_MAC (Cmd+C/X/V/Z) from manna-harbour_miryoku.h.
// Miryoku layer-slot assignments (set in custom_config.h):
//   BASE   base alphas
//   NAV    arrows + clipboard      (opened by the Spc thumb)
//   NUM    numbers (left hand)     (opened by the Bspc thumb)
//   MOUSE  mouse                   (opened by the Tab thumb)
//   SYM    symbols (left hand)     (opened by the Ent thumb)
//   MEDIA  media transport         (opened by the Del thumb)
//   EXTRA  numbers (right hand) + gateway, opened by the Esc thumb; its two
//          MO() keys open the TAP (symbols) and FUN (function) layers. Must be
//          a lower layer number than TAP/FUN or it would shadow them.
//   TAP    symbols (right hand)    (opened with MO from the EXTRA layer)
//   FUN    function keys (right hand) + screenshots (opened with MO from EXTRA)
//   BUTTON modifiers + clipboard   (opened by the outer-pinky LT keys)
// ============================================================================

#define MIRYOKU_ALTERNATIVES_BASE_NIKROULAH \
LT(U_SYM,KC_Q),    KC_W,              KC_E,              KC_R,              LT(U_NUM,KC_T),    KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              \
LSFT_T(KC_A),      LCTL_T(KC_S),      LALT_T(KC_D),      LGUI_T(KC_F),      KC_G,              KC_H,              RGUI_T(KC_J),      RALT_T(KC_K),      RCTL_T(KC_L),      RSFT_T(KC_QUOT),   \
LT(U_BUTTON,KC_Z), KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,            LT(U_BUTTON,KC_SLSH),\
U_NP,              U_NP,              LT(U_NUM,KC_ESC),  LT(U_NAV,KC_SPC),  LT(U_MOUSE,KC_TAB),LT(U_FUN,KC_ENT),  LT(U_MEDIA,KC_SPC),KC_BSPC,           U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_NAV_NIKROULAH \
TD(U_TD_BOOT),     U_NA,              U_NA,              U_NA,              U_NA,              U_CUT,             U_CPY,             KC_UP,             U_RDO,             U_UND,             \
KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           KC_TAB,            U_PST,             KC_LEFT,           KC_DOWN,           KC_RGHT,           U_NA,              \
U_NA,              U_NA,              LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),      U_NA,              U_NA,              KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            \
U_NP,              U_NP,              U_NA,              KC_TRNS,           U_NA,              KC_ENT,            KC_SPC,            KC_BSPC,           U_NP,              U_NP

// Right-hand numbers, opened by the W letter-hold (LT(U_NUM,KC_W) on base).
#define MIRYOKU_ALTERNATIVES_NUM_NIKROULAH \
U_NA,              U_NA,              U_NA,              U_NA,              KC_TRNS,           KC_LBRC,           KC_7,              KC_8,              KC_9,              KC_RBRC,           \
KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           U_NA,              KC_MINS,           KC_4,              KC_5,              KC_6,              KC_GRV,            \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              KC_EQL,            KC_1,              KC_2,              KC_3,              KC_SCLN,           \
U_NP,              U_NP,              KC_TRNS,           U_NA,              U_NA,              KC_BSLS,           KC_0,              KC_DOT,            U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_MOUSE_NIKROULAH \
TD(U_TD_BOOT),     MS_ACL0,           MS_ACL1,           MS_ACL2,           U_NA,              U_CUT,             U_CPY,             MS_UP,           U_RDO,             U_UND,             \
KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           KC_TAB,            U_PST,             MS_LEFT,           MS_DOWN,           MS_RGHT,           LCTL(KC_RGHT),     \
TD(U_TD_U_BASE),   U_NA,              LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),      U_NA,              LCTL(KC_LEFT),     MS_WHLL,           MS_WHLD,           MS_WHLU,           MS_WHLR,           \
U_NP,              U_NP,              U_NA,              U_NA,              KC_TRNS,           MS_BTN2,           MS_BTN1,           MS_BTN3,           U_NP,              U_NP

// Right-hand symbols, opened by the Q letter-hold (LT(U_SYM,KC_Q) on base).
#define MIRYOKU_ALTERNATIVES_SYM_NIKROULAH \
KC_TRNS,           U_NA,              U_NA,              U_NA,              U_NA,              KC_LCBR,           KC_AMPR,           KC_ASTR,           KC_LPRN,           KC_RCBR,           \
KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           U_NA,              KC_UNDS,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_TILD,           \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              KC_PLUS,           KC_EXLM,           KC_AT,             KC_HASH,           KC_COLN,           \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_PIPE,           KC_LPRN,           KC_RPRN,           U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_MEDIA_NIKROULAH \
U_NA,              KC_BRID,           KC_BRIU,           U_NA,              KC_EJCT,           U_NA,              U_NA,              U_GAME_SWITCH,     TD(U_TD_U_MOUSE),  TD(U_TD_BOOT),\
KC_MRWD,           KC_VOLD,           KC_VOLU,           KC_MFFD,           U_NA,              U_NA,              KC_RGUI,           KC_RALT,           KC_RCTL,           KC_RSFT,           \
KC_MPRV,           U_NA,              KC_MSTP,           KC_MNXT,           U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              \
U_NP,              U_NP,              U_NA,              KC_MPLY,           KC_MUTE,           U_NA,              KC_TRNS,           U_NA,              U_NP,              U_NP

// The EXTRA and TAP slots are unused now that num/sym moved to the Q/W
// letter-holds (no more gateway hack). Point both at this blank layer so they
// cost nothing and are never reachable.
#define MIRYOKU_ALTERNATIVES_NIKROULAH_BLANK \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NP,              U_NP

// F-keys on the LEFT hand (mods on the right), so it's comfortable held by the
// right-outer (Bspc) thumb. Mirrors the sweep's FUN.
#define MIRYOKU_ALTERNATIVES_FUN_NIKROULAH \
KC_F12,            KC_F7,             KC_F8,             KC_F9,             KC_PSCR,           U_NA,              U_NA,              U_GAME_SWITCH,     TD(U_TD_U_MOUSE),  TD(U_TD_BOOT),     \
KC_F11,            KC_F4,             KC_F5,             KC_F6,             LCTL(LSFT(LGUI(KC_4))),U_NA,          KC_RGUI,           KC_RALT,           KC_RCTL,           KC_RSFT,           \
KC_F10,            KC_F1,             KC_F2,             KC_F3,             LCTL(LSFT(LGUI(KC_3))),U_NA,          U_NA,              U_NA,              U_NA,              U_NA,              \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_TRNS,           U_NA,              U_NA,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_BUTTON_NIKROULAH \
U_UND,             U_RDO,             U_NA,              U_CPY,             U_CUT,             U_CUT,             U_CPY,             U_NA,              U_RDO,             U_UND,             \
KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           U_PST,             U_PST,             KC_RGUI,           KC_RALT,           KC_RCTL,           KC_RSFT,           \
U_NA,              TD(U_TD_BOOT),     U_NA,              CW_TOGG,           U_NA,              U_NA,              CW_TOGG,           U_NA,              TD(U_TD_BOOT),     U_NA,              \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NP,              U_NP


// ============================================================================
// nikroulah sweep layout (ferris/sweep, split_3x5_2 -- 2 thumbs per side)
// The split_3x5_2 mapping passes only the inner four thumbs (K33 K34 K35 K36)
// to the board; K32/K37 are dropped, so they are U_NP here. Layer access that
// the skeletyl puts on its extra thumbs is moved onto letter holds: Q->SYM,
// W->NUM, Z//->BUTTON. Thumbs: Esc->MOUSE, Tab->NAV, Spc->FUN, Bspc->MEDIA.
// num/sym match the skeletyl's fixed arrangement; reuses BUTTON_NIKROULAH.
// ============================================================================

#define MIRYOKU_ALTERNATIVES_BASE_SWEEP \
LT(U_SYM,KC_Q),    KC_W,              KC_E,              KC_R,              LT(U_NUM,KC_T),    KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              \
LSFT_T(KC_A),      LCTL_T(KC_S),      LALT_T(KC_D),      LGUI_T(KC_F),      KC_G,              KC_H,              RGUI_T(KC_J),      RALT_T(KC_K),      RCTL_T(KC_L),      RSFT_T(KC_QUOT),   \
LT(U_BUTTON,KC_Z), KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,            LT(U_BUTTON,KC_SLSH),\
U_NP,              U_NP,              U_NP,              LT(U_NAV,KC_ESC),  LT(U_MOUSE,KC_ENT),LT(U_FUN,KC_SPC),  LT(U_MEDIA,KC_BSPC),U_NP,             U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_NAV_SWEEP \
TD(U_TD_BOOT),     U_NA,              U_NA,              U_NA,              U_NA,              U_CUT,             U_CPY,             KC_UP,             U_RDO,             U_UND,             \
KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           KC_TAB,            U_PST,             KC_LEFT,           KC_DOWN,           KC_RGHT,           U_NA,              \
U_NA,              U_NA,              LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),      U_NA,              U_NA,              KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            \
U_NP,              U_NP,              U_NP,              KC_TRNS,           U_NA,              KC_ENT,            KC_BSPC,           U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_MOUSE_SWEEP \
TD(U_TD_BOOT),     MS_ACL0,           MS_ACL1,           MS_ACL2,           U_NA,              U_CUT,             U_CPY,             MS_UP,           U_RDO,             U_UND,             \
KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           KC_TAB,            U_PST,             MS_LEFT,           MS_DOWN,           MS_RGHT,           LCTL(KC_RGHT),     \
TD(U_TD_U_BASE),   U_NA,              LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),      U_NA,              LCTL(KC_LEFT),     MS_WHLL,           MS_WHLD,           MS_WHLU,           MS_WHLR,           \
U_NP,              U_NP,              U_NP,              U_NA,              KC_TRNS,           MS_BTN1,           MS_BTN2,           U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_MEDIA_SWEEP \
U_NA,              KC_BRID,           KC_BRIU,           U_NA,              KC_EJCT,           U_NA,              U_NA,              U_GAME_SWITCH,     TD(U_TD_U_MOUSE),  TD(U_TD_BOOT),\
KC_MRWD,           KC_VOLD,           KC_VOLU,           KC_MFFD,           U_NA,              U_NA,              KC_RGUI,           KC_RALT,           KC_RCTL,           KC_RSFT,           \
KC_MPRV,           U_NA,              KC_MSTP,           KC_MNXT,           U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              \
U_NP,              U_NP,              U_NP,              KC_MPLY,           KC_MUTE,           U_NA,              KC_TRNS,           U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_FUN_SWEEP \
KC_F12,            KC_F7,             KC_F8,             KC_F9,             KC_PSCR,           U_NA,              U_NA,              U_GAME_SWITCH,     TD(U_TD_U_MOUSE),  TD(U_TD_BOOT),     \
KC_F11,            KC_F4,             KC_F5,             KC_F6,             LCTL(LSFT(LGUI(KC_4))),U_NA,          KC_RGUI,           KC_RALT,           KC_RCTL,           KC_RSFT,           \
KC_F10,            KC_F1,             KC_F2,             KC_F3,             LCTL(LSFT(LGUI(KC_3))),U_NA,          U_NA,              U_NA,              U_NA,              U_NA,              \
U_NP,              U_NP,              U_NP,              U_NA,              U_NA,              KC_TRNS,           U_NA,              U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_NUM_SWEEP \
U_NA,              U_NA,              U_NA,              U_NA,              KC_TRNS,           KC_LBRC,           KC_7,              KC_8,              KC_9,              KC_RBRC,           \
KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           U_NA,              KC_MINS,           KC_4,              KC_5,              KC_6,              KC_GRV,            \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              KC_EQL,            KC_1,              KC_2,              KC_3,              KC_SCLN,           \
U_NP,              U_NP,              U_NP,              U_NA,              KC_BSLS,           KC_0,              KC_DOT,            U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_SYM_SWEEP \
KC_TRNS,           U_NA,              U_NA,              U_NA,              U_NA,              KC_LCBR,           KC_AMPR,           KC_ASTR,           KC_LPRN,           KC_RCBR,           \
KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           U_NA,              KC_UNDS,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_TILD,           \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              KC_PLUS,           KC_EXLM,           KC_AT,             KC_HASH,           KC_COLN,           \
U_NP,              U_NP,              U_NP,              U_NA,              KC_PIPE,           KC_LPRN,           KC_RPRN,           U_NP,              U_NP,              U_NP


// ============================================================================
// nikroulah ZSA Voyager layout (zsa/voyager, LAYOUT -- 2 thumbs/side).
// The Voyager has 18 physical keys Miryoku doesn't use (the top number row + the
// outer pinky columns, both hands). Rather than fix a keycode onto them for every
// layer, we expose all 18 as EXTRA layer slots (E0..E17, appended past the normal
// thumb row) so they're addressable PER LAYER. The Voyager's LAYOUT_miryoku (in
// keyboards/zsa/voyager/keymaps/nikroulah/config.h) takes the usual 40 args plus
// these 18 and routes them to:
//   E0..E5   -> right-hand top row, inner->outer
//   E6/E7/E8 -> right outer (6th) column, the three finger rows
//   E9..E14  -> left-hand top row, outer(pinky)->inner
//   E15/E16/E17 -> left outer (6th) column, the three finger rows
// Each Voyager layer = the matching SWEEP layer + its 18 extras. Uses so far:
//   - MEDIA: RGB controls on the right-side extras (E0..E8); left extras inert.
//   - EXTRA (the "gaming" base layer): the top-row extras become a number row
//     (1..6 left, 7 8 9 0 - = right); pinky-column extras inert, like BASE. See
//     U_EXTRAS_GAME / GAME_VOYAGER below.
// Every other layer leaves the extras inert (U_NA).
// U_GAME_SWITCH is the tap-dance that makes the gaming layer the default base;
// it sits next to the MOUSE-layer switch on MEDIA/FUN. It resolves to U_NA on
// non-Voyager boards, so the shared MEDIA/FUN macros stay byte-identical there.
// TOGGLE_LAYER_COLOR / RM_* / the gaming keys are only expanded in the Voyager build.
// ============================================================================

// Enter-switch for the "gaming" layer (the EXTRA slot). Sits at MEDIA/FUN slot
// [7], next to the MOUSE-layer switch; double-tap makes the gaming layer the
// default base. Return to the normal BASE via TD(U_TD_U_BASE) on the MOUSE layer.
// U_NA on non-Voyager boards, so the shared MEDIA/FUN macros stay byte-identical
// there (the gaming layer only exists on the Voyager).
#if defined(KEYBOARD_zsa_voyager)
#    define U_GAME_SWITCH TD(U_TD_U_EXTRA)
#else
#    define U_GAME_SWITCH U_NA
#endif

#define U_EXTRAS_BLANK  U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA
#define U_EXTRAS_RGB    RM_VALD, RM_VALU, RM_HUED, RM_HUEU, RM_SATD, RM_SATU, RM_NEXT, TOGGLE_LAYER_COLOR, RM_TOGG,  U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA
// Gaming layer extras: a number row on the Voyager's spare top-row keys.
// E0..E5 = right-hand top row (inner->outer) = 7 8 9 0 - = ; E9..E14 = left-hand
// top row (outer->inner) = 1 2 3 4 5 6. The outer pinky columns (E6..E8, E15..E17)
// stay blank, matching the base layer.
#define U_EXTRAS_GAME   KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,  U_NA, U_NA, U_NA,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,  U_NA, U_NA, U_NA

#define MIRYOKU_ALTERNATIVES_BASE_VOYAGER    MIRYOKU_ALTERNATIVES_BASE_SWEEP,       U_EXTRAS_BLANK
#define MIRYOKU_ALTERNATIVES_NAV_VOYAGER     MIRYOKU_ALTERNATIVES_NAV_SWEEP,        U_EXTRAS_BLANK
#define MIRYOKU_ALTERNATIVES_MOUSE_VOYAGER   MIRYOKU_ALTERNATIVES_MOUSE_SWEEP,      U_EXTRAS_BLANK
#define MIRYOKU_ALTERNATIVES_MEDIA_VOYAGER   MIRYOKU_ALTERNATIVES_MEDIA_SWEEP,      U_EXTRAS_RGB
#define MIRYOKU_ALTERNATIVES_NUM_VOYAGER     MIRYOKU_ALTERNATIVES_NUM_SWEEP,        U_EXTRAS_BLANK
#define MIRYOKU_ALTERNATIVES_SYM_VOYAGER     MIRYOKU_ALTERNATIVES_SYM_SWEEP,        U_EXTRAS_BLANK
#define MIRYOKU_ALTERNATIVES_FUN_VOYAGER     MIRYOKU_ALTERNATIVES_FUN_SWEEP,        U_EXTRAS_BLANK
#define MIRYOKU_ALTERNATIVES_BUTTON_VOYAGER  MIRYOKU_ALTERNATIVES_BUTTON_NIKROULAH, U_EXTRAS_BLANK
#define MIRYOKU_ALTERNATIVES_VOYAGER_BLANK   MIRYOKU_ALTERNATIVES_NIKROULAH_BLANK,  U_EXTRAS_BLANK

// Gaming layer (Voyager EXTRA slot): identical to the BASE layer (home-row mods,
// letter-hold + thumb layer-taps, all of it) PLUS a number row on the Voyager's
// spare top-row keys (1..6 left hand, 7 8 9 0 - = right hand -- see U_EXTRAS_GAME).
// Enter via U_GAME_SWITCH on MEDIA/FUN [7]; exit via TD(U_TD_U_BASE) on MOUSE.
// Not yet flash-tested.
#define MIRYOKU_ALTERNATIVES_GAME_VOYAGER    MIRYOKU_ALTERNATIVES_BASE_SWEEP, U_EXTRAS_GAME
