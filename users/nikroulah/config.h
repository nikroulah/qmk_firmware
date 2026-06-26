// nikroulah custom Miryoku config.
//
// This userspace reuses the pristine miryoku engine in
// users/manna-harbour_miryoku/ (referenced via ../). Everything custom to my
// setup lives here -- the miryoku userspace is left exactly as on its remote.
//
// What used to live in users/manna-harbour_miryoku/custom_config.h now lives
// here, plus the board-conditional layer selection and our custom layer-
// alternative macros. The pristine engine config (TAPPING_TERM, mouse/auto-
// shift defaults, thumb-combo config) is pulled in at the end.

#pragma once

// Clipboard keys (U_CPY/U_CUT/U_PST/U_UND/U_RDO) become Cmd+C/X/V/Z/Shift-Cmd-Z.
#define MIRYOKU_CLIPBOARD_MAC

// Caps Word: pressing BOTH home-row Shift mod-taps (A + ') together turns it on,
// so all-caps words don't require holding Shift. (There is also a CW_TOGG key on
// the BUTTON layer's V/M keys.) Auto-turns-off at the next word break.
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Mouse keys: constant-speed mode with momentary acceleration. No acceleration
// ramp -- the cursor/scroll move at a fixed default speed; holding the MOUSE
// layer's ACL0/ACL1/ACL2 keys momentarily selects slow / medium / fast (this
// makes the engine config.h MOUSEKEY_DELAY/INTERVAL/MAX_SPEED/TIME_TO_MAX inert).
// Tune the offsets (px per step) and intervals (ms between steps) below.
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL
// cursor
#define MK_C_OFFSET_UNMOD   25   // default speed
#define MK_C_INTERVAL_UNMOD 100
#define MK_C_OFFSET_0       4    // ACL0 = precision
#define MK_C_INTERVAL_0     50
#define MK_C_OFFSET_1       50   // ACL1 = slow
#define MK_C_INTERVAL_1     100
#define MK_C_OFFSET_2       50   // ACL2 = fast
#define MK_C_INTERVAL_2     50
// scroll wheel (offset stays 1 = whole scroll clicks; speed set by interval)
#define MK_W_OFFSET_UNMOD   1    // default scroll
#define MK_W_INTERVAL_UNMOD 100
#define MK_W_OFFSET_0       1    // ACL0 = slow scroll
#define MK_W_INTERVAL_0     125
#define MK_W_OFFSET_1       1   // ACL1 = medium scroll
#define MK_W_INTERVAL_1     75
#define MK_W_OFFSET_2       1    // ACL2 = fast scroll
#define MK_W_INTERVAL_2     50

// Map every layer slot to the layout for the board being built. Both layouts
// are defined in miryoku_nikroulah_alternatives.h (included below). The
// skeletyl (split_3x5_3) is the default; the sweep (split_3x5_2) is a separate,
// simpler layout selected by keyboard. Neither board uses the EXTRA/TAP slots
// anymore (num/sym are on Q/W letter-holds), so both point at a blank layer.
#define MIRYOKU_LAYER_EXTRA  MIRYOKU_ALTERNATIVES_NIKROULAH_BLANK
#define MIRYOKU_LAYER_TAP    MIRYOKU_ALTERNATIVES_NIKROULAH_BLANK
#if defined(KEYBOARD_ferris_sweep)
  #define MIRYOKU_LAYER_BASE   MIRYOKU_ALTERNATIVES_BASE_SWEEP
  #define MIRYOKU_LAYER_BUTTON MIRYOKU_ALTERNATIVES_BUTTON_NIKROULAH
  #define MIRYOKU_LAYER_NAV    MIRYOKU_ALTERNATIVES_NAV_SWEEP
  #define MIRYOKU_LAYER_MOUSE  MIRYOKU_ALTERNATIVES_MOUSE_SWEEP
  #define MIRYOKU_LAYER_MEDIA  MIRYOKU_ALTERNATIVES_MEDIA_SWEEP
  #define MIRYOKU_LAYER_NUM    MIRYOKU_ALTERNATIVES_NUM_SWEEP
  #define MIRYOKU_LAYER_SYM    MIRYOKU_ALTERNATIVES_SYM_SWEEP
  #define MIRYOKU_LAYER_FUN    MIRYOKU_ALTERNATIVES_FUN_SWEEP
#else
  #define MIRYOKU_LAYER_BASE   MIRYOKU_ALTERNATIVES_BASE_NIKROULAH
  #define MIRYOKU_LAYER_BUTTON MIRYOKU_ALTERNATIVES_BUTTON_NIKROULAH
  #define MIRYOKU_LAYER_NAV    MIRYOKU_ALTERNATIVES_NAV_NIKROULAH
  #define MIRYOKU_LAYER_MOUSE  MIRYOKU_ALTERNATIVES_MOUSE_NIKROULAH
  #define MIRYOKU_LAYER_MEDIA  MIRYOKU_ALTERNATIVES_MEDIA_NIKROULAH
  #define MIRYOKU_LAYER_NUM    MIRYOKU_ALTERNATIVES_NUM_NIKROULAH
  #define MIRYOKU_LAYER_SYM    MIRYOKU_ALTERNATIVES_SYM_NIKROULAH
  #define MIRYOKU_LAYER_FUN    MIRYOKU_ALTERNATIVES_FUN_NIKROULAH
#endif

// Our custom layer-alternative macros (the MIRYOKU_LAYER_* above reference
// these). Must be visible before the babel layer-selection runs.
#include "miryoku_nikroulah_alternatives.h"

// Pull in the pristine miryoku engine config last (TAPPING_TERM, mouse/auto-
// shift defaults, thumb-combo config). Its `#include "custom_config.h"`
// resolves to the engine's own (empty) hook -- our customizations are above.
#include "../manna-harbour_miryoku/config.h"
