# CLAUDE.md — nikroulah's Miryoku skeletyl

This is a personal QMK fork (branch `miryoku`) whose purpose is the `nikroulah`
custom Miryoku keymap for the **bastardkb skeletyl (v1/elitec)**. This file
documents that work so future sessions don't have to re-derive it.

## Board facts

- Keyboard target: `bastardkb/skeletyl/v1/elitec`
- MCU: atmega32u4, bootloader `atmel-dfu`
- Split: `MASTER_RIGHT`, **no** `EE_HANDS`/`SPLIT_HAND_PIN` → the **same firmware
  is flashed to both halves**; handedness is fixed in config.
- Physical layout: `LAYOUT_split_3x5_3` (36 keys). The keyboard declares
  `community_layouts: ["split_3x5_3"]`, so the Miryoku keymap is pulled from
  `layouts/community/split_3x5_3/manna-harbour_miryoku/` — there is **no**
  `keymaps/manna-harbour_miryoku/` dir under the skeletyl.

## Build & flash

```bash
# build
qmk compile -kb bastardkb/skeletyl/v1/elitec -km manna-harbour_miryoku
# build + flash (run once per half; reset each half when prompted)
qmk flash -kb bastardkb/skeletyl/v1/elitec -km manna-harbour_miryoku
```

- **Do not run `qmk flash` yourself.** Flashing is a physical operation (the user
  resets each half by hand) — only the user runs it. Claude builds with
  `qmk compile` and leaves flashing to the user.
- Use `qmk compile`, **not** bare `make` — the avr toolchain is only on PATH
  inside the qmk wrapper (bare make fails with `gccversion Error 127`).
- Firmware is near full: ~**27.2 KB / 28.7 KB** (~1.4 KB free). Watch the size on
  any change. `CONSOLE_ENABLE` does **not** fit (~3.25 KB, overflows);
  `RAW_ENABLE` costs ~358 B and is already on.

## The files that matter (all edits live here)

| File | What we put there |
|---|---|
| `users/manna-harbour_miryoku/miryoku_babel/miryoku_layer_alternatives.h` | The 10 `MIRYOKU_ALTERNATIVES_*_NIKROULAH` layer macros (the actual layout), in a commented block at the end of the file. **Source of truth for the layout.** |
| `users/manna-harbour_miryoku/custom_config.h` | `#define MIRYOKU_CLIPBOARD_MAC` + the ten `#define MIRYOKU_LAYER_* …_NIKROULAH` overrides that select those macros. |
| `users/manna-harbour_miryoku/custom_rules.mk` | `RAW_ENABLE = yes` (for the qmk_viewer indicator). |
| `users/manna-harbour_miryoku/manna-harbour_miryoku.c` | qmk_viewer raw-HID block at the end, guarded by `#if defined(RAW_ENABLE)`. |
| `keyboards/bastardkb/skeletyl/keymaps/nikroulah/keymap.json` | Regenerated render source for qmk_viewer (see below). **Not a daily-driver keymap.** |
| `keyboards/bastardkb/skeletyl/keymaps/nikroulah/gen_keymap_json.py` | Generator that produces the keymap.json from the layer macros. |

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

Base thumb → layer: Esc→EXTRA, Spc→NAV, Tab→MOUSE, Ent→SYM, Bspc→NUM, Del→MEDIA.
Note the slot *names* EXTRA/TAP are just enum labels here; their contents are
numbers/symbols, not Miryoku's usual tap/extra alpha layers. **The gateway must
sit in the lower-numbered slot (EXTRA=1) and the layers it `MO`s to in higher
slots (TAP=2, FUN=9)** — QMK resolves from the highest active layer down, so a
higher gateway would shadow its own sub-layers (this was a real bug).

## qmk_viewer live layer/keypress indicator

App: https://github.com/thooams/qmk_viewer (reads keyboard state over raw HID).

- Firmware side (in `manna-harbour_miryoku.c`, `#if defined(RAW_ENABLE)`):
  `raw_hid_receive` (no-op), `u_qmk_viewer_send(layer)` builds a **32-byte**
  report (`byte 0` = highest active layer, remaining bytes = pressed-key
  bitmap), called from `layer_state_set_user` + `default_layer_state_set_user`
  (layer indicator) and `process_record_user` (live keypress highlight).
  Event-driven, no idle polling.
- Host side: load `keymaps/nikroulah/keymap.json` into qmk_viewer as the render
  source. It's generated in **enum order**, so qmk_viewer's "layer N" matches the
  firmware's byte 0.

## Regenerating keymap.json

`keymap.json` is a *static snapshot* for qmk_viewer only — it omits Miryoku
behaviors (auto-shift, tap-dance, caps-word, key-overrides), so **do not flash
the `nikroulah` keymap as a daily driver**; flash `manna-harbour_miryoku`.

To regenerate after editing the layout:

```bash
python3 keyboards/bastardkb/skeletyl/keymaps/nikroulah/gen_keymap_json.py
```

The script holds verbatim copies of the `…_NIKROULAH` macros — **keep them in
sync** with `miryoku_layer_alternatives.h`. It translates `U_NP/U_NA`→`KC_NO`,
`U_CPY`→`LGUI(KC_C)` etc., `LT(U_*,…)`/`MO(U_*)`→numeric layer indices, and emits
layers in enum order. Validate with:

```bash
qmk compile -kb bastardkb/skeletyl/v1/elitec -km nikroulah   # proves keycodes parse
```

## Gotchas

- QMK Configurator emits `LCSG(kc)` for mac screenshots — **not a valid QMK
  macro**. Use `LCTL(LSFT(LGUI(kc)))` instead (this bit us once).
- Features compiled in (`rules.mk`) but **unreachable in this layout** because no
  trigger key is placed: **Tap Dance** (no `TD()` keys — boot uses plain
  `QK_BOOT` on MEDIA instead), **Caps Word** (no `CW_TOGG` key), and the
  **Caps-Word key-override** (inert without `CW_TOGG`). Active features:
  mod-taps/layer-taps (`TAPPING_TERM 200`, `IGNORE_MOD_TAP_INTERRUPT`,
  `QUICK_TAP_TERM 0`), Auto Shift on non-alphas, mouse keys, media keys.
