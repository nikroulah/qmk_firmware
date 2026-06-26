# CLAUDE.md — nikroulah's Miryoku layouts

This is a personal QMK fork (branch `miryoku`) whose purpose is the `nikroulah`
custom Miryoku keymaps for two boards: the **bastardkb skeletyl (v1/elitec)**
(`split_3x5_3`, 6 thumbs) and the **ferris/sweep** (`split_3x5_2`, 4 thumbs).
Both are Miryoku builds driven from the same shared files, selected per board.
This file documents that work so future sessions don't have to re-derive it.

**No PRs, ever.** This fork is personal and never upstreams — do not open pull
requests (to `upstream` qmk/qmk_firmware, the `nikroulah` fork's default branch,
or anywhere). Commit and push to `origin/miryoku` only when asked.

## Board facts

- **skeletyl**: `bastardkb/skeletyl/v1/elitec`, atmega32u4, bootloader
  `atmel-dfu`, split `MASTER_RIGHT` (no `EE_HANDS`/`SPLIT_HAND_PIN` → **same
  firmware flashed to both halves**), `LAYOUT_split_3x5_3` (36 keys).
- **sweep**: `ferris/sweep`, atmega32u4, split. `LAYOUT_split_3x5_2` (34 keys).
- Both declare the matching `community_layouts`, so the Miryoku keymap comes from
  `layouts/community/split_3x5_{3,2}/manna-harbour_miryoku/` — there is **no**
  `keymaps/manna-harbour_miryoku/` dir under either board.
- The `split_3x5_2` Miryoku mapping passes only the **inner four thumbs**
  (K33 K34 K35 K36) to the board; the outer two (K32/K37) are dropped. That's
  why the sweep moves some layer access onto letter holds (see layout below).

## Build & flash

```bash
# build (skeletyl)
qmk compile -kb bastardkb/skeletyl/v1/elitec -km manna-harbour_miryoku
# build (sweep)
qmk compile -kb ferris/sweep -km manna-harbour_miryoku
# flash: same -km, run once per half; reset each half when prompted
qmk flash -kb <board> -km manna-harbour_miryoku
```

- **Do not run `qmk flash` yourself.** Flashing is a physical operation (the user
  resets each half by hand) — only the user runs it. Claude builds with
  `qmk compile` and leaves flashing to the user.
- Use `qmk compile`, **not** bare `make` — the avr toolchain is only on PATH
  inside the qmk wrapper (bare make fails with `gccversion Error 127`).
- Firmware is near full: skeletyl ~**27.2 KB**, sweep ~**27.0 KB** (of 28.7 KB;
  ~1.4–1.7 KB free). Watch the size on any change. `CONSOLE_ENABLE` does **not**
  fit (~3.25 KB, overflows); `RAW_ENABLE` costs ~358 B and is already on.

## The files that matter (all edits live here)

| File | What we put there |
|---|---|
| `users/manna-harbour_miryoku/miryoku_babel/miryoku_layer_alternatives.h` | The `MIRYOKU_ALTERNATIVES_*_NIKROULAH` (skeletyl) and `*_SWEEP` layer macros, in commented blocks at the end. **Source of truth for both layouts.** |
| `users/manna-harbour_miryoku/custom_config.h` | `MIRYOKU_CLIPBOARD_MAC` + a `#if defined(KEYBOARD_ferris_sweep)` block selecting the `*_SWEEP` macros, `#else` the `*_NIKROULAH` macros. **This is how the two boards are differentiated.** |
| `users/manna-harbour_miryoku/custom_rules.mk` | `RAW_ENABLE = yes` (for the qmk_viewer indicator). |
| `users/manna-harbour_miryoku/manna-harbour_miryoku.c` | qmk_viewer raw-HID block at the end, guarded by `#if defined(RAW_ENABLE)`. |
| `keyboards/bastardkb/skeletyl/keymaps/nikroulah/keymap.json`, `keyboards/ferris/sweep/keymaps/nikroulah/keymap.json` | Render sources for qmk_viewer (see below). **Not daily-driver keymaps.** |
| `keyboards/bastardkb/skeletyl/keymaps/nikroulah/gen_keymap_json.py` | Generator for **both** render JSONs. **Parses the macros out of the `.h`** (no hardcoded copy → can't drift). |
| `nikroulah-sweep-configurator.json` (repo root) | The sweep's editable Configurator-format design doc (8 layers, the user's own numbering). Superseded by the Miryoku build for actual firmware; kept for re-import/iteration in config.qmk.fm. |

The Miryoku `custom_*` files are the intended user-customization hooks. Editing
the shared `miryoku_babel/*.h` / `manna-harbour_miryoku.c` is fine here because
this is a personal fork and the qmk_viewer code is `RAW_ENABLE`-guarded, so other
Miryoku builds are unaffected.

## The layout

A customized Miryoku QWERTY. Differences from stock Miryoku:

- **Home-row mods in SCAG order** (Shift on the pinkies, then Ctrl, Alt, Gui on
  the index). Right hand uses `RGUI/RALT/RCTL/RSFT`. (Stock Miryoku is GACS.)
- Outer-pinky bottom-row keys are `LT(U_BUTTON, …)`.
- Custom **BUTTON** layer: home-row mods + cut/copy/paste/undo mirrored on both
  hands, nothing on the thumbs.
- Clipboard keys use the Miryoku `U_CPY/U_CUT/U_PST/U_UND` macros, which under
  `MIRYOKU_CLIPBOARD_MAC` expand to `LGUI(KC_C/X/V/Z)` — i.e. **mac-only**
  (switch to `MIRYOKU_CLIPBOARD_WIN` for Linux/Windows).

### Layer-slot mapping (important, non-obvious)

The configurator design had 9 flat layers; they were remapped onto Miryoku's
fixed 10-slot enum. Enum order (= the layer number qmk_viewer shows):

```
0 BASE    base alphas
1 EXTRA   numbers (right hand) + gateway; opened by the Esc thumb; its two
          MO() keys open TAP and FUN
2 TAP     symbols (right hand)        — reached via MO from EXTRA
3 BUTTON  modifiers + clipboard       — opened by the outer-pinky LT keys
4 NAV     arrows + clipboard          — Spc thumb
5 MOUSE   mouse                       — Tab thumb
6 MEDIA   media transport + QK_BOOT   — Del thumb
7 NUM     numbers (left hand)         — Bspc thumb
8 SYM     symbols (left hand)         — Ent thumb
9 FUN     function keys + mac screenshots — reached via MO from EXTRA
```

Base thumb → layer (skeletyl): Esc→EXTRA, Spc→**Bspc**(NAV), Tab→MOUSE, Ent→SYM,
Bspc→**Spc**(NUM), Del→MEDIA. (Space and Backspace tap-keycodes are swapped so
Space is on the right thumb; the NAV/NUM *layers* stay on their original thumbs.)
Note the slot *names* EXTRA/TAP are just enum labels here; their contents are
numbers/symbols, not Miryoku's usual tap/extra alpha layers. **The gateway must
sit in the lower-numbered slot (EXTRA=1) and the layers it `MO`s to in higher
slots (TAP=2, FUN=9)** — QMK resolves from the highest active layer down, so a
higher gateway would shadow its own sub-layers (this was a real bug).

### Sweep layer structure (different from skeletyl)

The sweep has only 4 thumbs, so it drops the EXTRA/TAP number/symbol *gateway*
entirely and moves that access onto **letter holds**. There is no nested `MO`
gateway, so no shadowing concern. Slot usage (EXTRA/TAP are unused/blank):

- Thumbs (K33–K36): `Esc`→MOUSE, `Tab`→NAV, `Spc`→FUN, `Bspc`→MEDIA.
- Letter holds: `Q`→SYM, `W`→NUM, `Z`/`/`→BUTTON.
- FUN F-keys sit on the **left** hand (mods on right) since FUN is a right-thumb
  hold; the skeletyl's FUN is right-hand.

### num/sym arrangement (both boards, shared design)

- NUM digits `7 8 9 / 4 5 6 / 1 2 3` on three rows, flanked by `[ ]`; `-` on the
  4/5/6 row, `=` on the 1/2/3 row, `` ` `` and `;` on the right ends; `.`, `\`, `0`
  on the free-hand thumb cluster (**`\` on the right thumb cluster**).
- SYM mirrors NUM; `|` sits where `\` is (right thumb cluster); `_` is on the
  bottom row; `(` `)` round out the thumbs. (A `LSA_T(KC_NO)` Shift+Alt hold used
  to live on a SYM/NUM left-hand key for em-dashes; removed — alt + a SYM key is
  already alt+shift+base, so it was redundant.)
- On the skeletyl, these arrangements appear on all four number/symbol layers
  (left-hand NUM/SYM and right-hand EXTRA/TAP), column-mirrored per hand. On the
  left-hand layers the aux keys (`\`/`|`) mirror to the **left** thumb cluster.

## qmk_viewer live layer/keypress indicator

App: https://github.com/thooams/qmk_viewer (reads keyboard state over raw HID).

- Firmware side (in `manna-harbour_miryoku.c`, `#if defined(RAW_ENABLE)`):
  `raw_hid_receive` (no-op), `u_qmk_viewer_send(layer)` builds a **32-byte**
  report (`byte 0` = highest active layer, remaining bytes = pressed-key
  bitmap), called from `layer_state_set_user` + `default_layer_state_set_user`
  (layer indicator) and `process_record_user` (live keypress highlight).
  Event-driven, no idle polling.
- Host side: load the board's `keymaps/nikroulah/keymap.json` into qmk_viewer as
  the render source. It's generated in **enum order**, so qmk_viewer's "layer N"
  matches the firmware's byte 0.

## Regenerating the render JSONs

They're *static snapshots* for qmk_viewer only — they omit Miryoku behaviors
(auto-shift, tap-dance, caps-word), so **do not flash the `nikroulah` keymaps as
daily drivers**; flash `manna-harbour_miryoku`.

After editing any layout macro, regenerate **both** boards' JSONs:

```bash
python3 keyboards/bastardkb/skeletyl/keymaps/nikroulah/gen_keymap_json.py
```

The generator **parses the `MIRYOKU_ALTERNATIVES_*` macros straight out of
`miryoku_layer_alternatives.h`** (no hardcoded copy, so it can't drift). It
translates `U_NP/U_NA`→`KC_NO`, `U_CPY`→`LGUI(KC_C)` etc., `LT(U_*,…)`/`MO(U_*)`
→numeric indices, `TD(U_TD_BOOT)`→`QK_BOOT` (plain JSON can't tap-dance), drops
the right thumbs per board, and emits layers in enum order. Validate:

```bash
qmk compile -kb bastardkb/skeletyl/v1/elitec -km nikroulah   # proves keycodes parse
qmk compile -kb ferris/sweep -km nikroulah
```

## Gotchas

- QMK Configurator emits `LCSG(kc)` for mac screenshots — **not a valid QMK
  macro**. The firmware macros use `LCTL(LSFT(LGUI(kc)))`; the root Configurator
  JSON keeps `LCSG` (round-trips in config.qmk.fm but won't compile as-is).
- Configurator JSON **can't express tap dances**. The bootloader key uses
  `TD(U_TD_BOOT)` (Miryoku's built-in double-tap-to-boot) in the firmware, but a
  plain `QK_BOOT` in the root Configurator JSON.
- Features compiled in (`rules.mk`): **Tap Dance** is used (the boot key).
  **Caps Word** is now reachable two ways: `BOTH_SHIFTS_TURNS_ON_CAPS_WORD`
  (press both home-row Shift mod-taps A+' together) and a `CW_TOGG` key on the
  BUTTON layer's V and M keys. Active: mod-taps/layer-taps (`TAPPING_TERM 200`,
  `IGNORE_MOD_TAP_INTERRUPT`, `QUICK_TAP_TERM 0`), Auto Shift on non-alphas,
  mouse keys, media keys.
