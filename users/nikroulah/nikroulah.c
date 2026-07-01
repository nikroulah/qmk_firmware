// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "../manna-harbour_miryoku/manna-harbour_miryoku.h"


// Additional Features double tap guard

enum {
    U_TD_BOOT,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
}

#define MIRYOKU_X(LAYER, STRING) \
void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) { \
    default_layer_set((layer_state_t)1 << U_##LAYER); \
  } \
}
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
#define MIRYOKU_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define MIRYOKU_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(MIRYOKU_LAYERMAPPING_##LAYER, MIRYOKU_LAYER_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// Chordal Hold + per-key tapping term for the home-row Shift mod-taps (A and ').
// 350ms term: a same-hand key within that window rolls as a tap (no accidental
// capital), while holding A/' alone past 350ms still settles as Shift.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LSFT_T(KC_A):
    case RSFT_T(KC_QUOT):
      return 350;
    default:
      return TAPPING_TERM;
  }
}

// Apply the Chordal Hold opposite-hands rule to ALL home-row mod-taps (both
// hands). Returning the default (true iff opposite hands) makes same-hand chords
// settle as taps. Only A/' get the longer 350ms term above; the other mods use
// the normal 200ms TAPPING_TERM. Layer-taps (thumbs, Q/T/Z letter holds) return
// true => unaffected, normal tap/hold.
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record,
                      uint16_t other_keycode, keyrecord_t *other_record) {
  switch (tap_hold_keycode) {
    case LSFT_T(KC_A):
    case LCTL_T(KC_S):
    case LALT_T(KC_D):
    case LGUI_T(KC_F):
    case RGUI_T(KC_J):
    case RALT_T(KC_K):
    case RCTL_T(KC_L):
    case RSFT_T(KC_QUOT):
      return get_chordal_hold_default(tap_hold_record, other_record);
    default:
      return true;
  }
}


// shift functions

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

// QMK >=0.22 collects key overrides by introspection via ARRAY_SIZE(), which
// needs a real array (not the old NULL-terminated `const key_override_t **`).
const key_override_t *key_overrides[] = {
    &capsword_key_override,
};


// thumb combos

#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(U_SYM, KC_ENT), LT(U_NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(U_NAV, KC_SPC), LT(U_MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN2, KC_BTN1, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_0, KC_MINS, COMBO_END};
  #if defined (MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_UNDS, KC_LPRN, COMBO_END};
  #else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
  #endif
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  COMBO(thumbcombos_base_right, LT(U_FUN, KC_DEL)),
  COMBO(thumbcombos_base_left, LT(U_MEDIA, KC_ESC)),
  COMBO(thumbcombos_nav, KC_DEL),
  COMBO(thumbcombos_mouse, KC_BTN3),
  COMBO(thumbcombos_media, KC_MUTE),
  COMBO(thumbcombos_num, KC_DOT),
  #if defined (MIRYOKU_LAYERS_FLIP)
  COMBO(thumbcombos_sym, KC_RPRN),
  #else
  COMBO(thumbcombos_sym, KC_LPRN),
  #endif
  COMBO(thumbcombos_fun, KC_APP)
};
#endif


// qmk_viewer live indicator (https://github.com/thooams/qmk_viewer)
// Sends a 32-byte raw HID report at most every 50ms (byte 0 = active layer,
// remaining bytes = a bitmap of pressed matrix keys) from matrix_scan_user.
// Polling here -- rather than sending from process_record_user on every key --
// keeps raw_hid_send (which blocks until the host drains the endpoint) off the
// keystroke path and caps it to ~20 sends/sec, so typing stays responsive
// regardless of speed. The viewer updates at ~20fps, which is plenty. Only
// built when RAW_ENABLE is set (see custom_rules.mk); other builds unaffected.
#if defined (RAW_ENABLE)
#include "raw_hid.h"

#define U_QMK_VIEWER_REPORT_SIZE 32

void raw_hid_receive(uint8_t *data, uint8_t length) {
  // qmk_viewer only reads keyboard state; nothing to handle on receive.
}

void matrix_scan_user(void) {
  static uint16_t last_sent = 0;
  if (timer_elapsed(last_sent) < 50) {
    return;
  }
  last_sent = timer_read();

  uint8_t report[U_QMK_VIEWER_REPORT_SIZE] = {0};
  // Include default_layer_state so a base-layer switch (e.g. TD(U_TD_U_MOUSE)
  // makes MOUSE the default) is reported: layer_state alone stays empty when no
  // momentary layer is active, so the viewer would otherwise render BASE while
  // the board is locked on the new base layer.
  report[0] = get_highest_layer(layer_state | default_layer_state);
  for (uint8_t i = 0; i < MATRIX_ROWS * MATRIX_COLS && i < (U_QMK_VIEWER_REPORT_SIZE - 1) * 8; i++) {
    if (matrix_is_on(i / MATRIX_COLS, i % MATRIX_COLS)) {
      report[1 + (i / 8)] |= 1 << (i % 8);
    }
  }
  raw_hid_send(report, U_QMK_VIEWER_REPORT_SIZE);
}
#endif
