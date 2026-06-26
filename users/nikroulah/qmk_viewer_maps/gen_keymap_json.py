#!/usr/bin/env python3
"""Generate qmk_viewer render-source keymap.json files for the nikroulah
Miryoku layouts, by PARSING the macros out of miryoku_nikroulah_alternatives.h
so the JSON can never drift from the firmware.

Emits, in Miryoku enum order (so qmk_viewer's layer number matches the
firmware's raw-HID indicator), into users/nikroulah/qmk_viewer_maps/<board>/:
  - skeletyl  (bastardkb/skeletyl/v1/elitec, split_3x5_3)  <- *_NIKROULAH macros
  - sweep     (ferris/sweep, split_3x5_2)                  <- *_SWEEP macros (+ reused BUTTON)

Run:  python3 users/nikroulah/qmk_viewer_maps/gen_keymap_json.py
"""
import json, os, re

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
ALT = os.path.join(REPO, "users/nikroulah/miryoku_nikroulah_alternatives.h")

ENUM = {"U_BASE":0,"U_EXTRA":1,"U_TAP":2,"U_BUTTON":3,"U_NAV":4,
        "U_MOUSE":5,"U_MEDIA":6,"U_NUM":7,"U_SYM":8,"U_FUN":9}
CLIP = {"U_UND":"LGUI(KC_Z)","U_CUT":"LGUI(KC_X)","U_CPY":"LGUI(KC_C)",
        "U_PST":"LGUI(KC_V)","U_RDO":"SGUI(KC_Z)"}
ENUM_ORDER = ["BASE","EXTRA","TAP","BUTTON","NAV","MOUSE","MEDIA","NUM","SYM","FUN"]


def split_tokens(s):
    toks, depth, cur = [], 0, ""
    for ch in s:
        if ch == "," and depth == 0:
            toks.append(cur.strip()); cur = ""
        else:
            if ch in "([": depth += 1
            elif ch in ")]": depth -= 1
            cur += ch
    if cur.strip():
        toks.append(cur.strip())
    return toks


def get_macro(text, name):
    """Return the 40 raw tokens of `#define <name> \\` ... or None if absent."""
    lines = text.splitlines()
    for idx, l in enumerate(lines):
        if l.strip().startswith("#define " + name + " "):
            body, j = [], idx + 1
            while True:
                body.append(lines[j])
                if not lines[j].rstrip().endswith("\\"):
                    break
                j += 1
            joined = " ".join(x.rstrip().rstrip("\\").strip() for x in body)
            toks = split_tokens(joined)
            assert len(toks) == 40, "%s: got %d tokens" % (name, len(toks))
            return toks
    return None


def xlate(t):
    if t in ("U_NP", "U_NA", "U_NU"):
        return "KC_NO"
    if t in CLIP:
        return CLIP[t]
    if t == "TD(U_TD_BOOT)":
        return "QK_BOOT"          # plain JSON can't express the tap dance
    for name, i in ENUM.items():
        t = t.replace(name, str(i))
    return t


def build(text, suffix, drop_keep, reuse_button=False):
    """suffix: 'NIKROULAH' or 'SWEEP'. drop_keep: indices to keep from the 40."""
    layers = []
    for slot in ENUM_ORDER:
        name = "MIRYOKU_ALTERNATIVES_%s_%s" % (slot, suffix)
        toks = get_macro(text, name)
        if toks is None and reuse_button and slot == "BUTTON":
            toks = get_macro(text, "MIRYOKU_ALTERNATIVES_BUTTON_NIKROULAH")
        if toks is None:
            toks = ["U_NP"] * 40          # slot unused on this board -> blank
        keys = [toks[i] for i in drop_keep]
        layers.append([xlate(t) for t in keys])
    return layers


def main():
    text = open(ALT).read()

    # split_3x5_3: keep K32..K37 (drop the 4 U_NP corners N30/N31/N38/N39)
    KEEP_3 = list(range(0, 30)) + [32, 33, 34, 35, 36, 37]
    # split_3x5_2: only the inner four thumbs K33..K36 reach the board
    KEEP_2 = list(range(0, 30)) + [33, 34, 35, 36]

    targets = [
        ("bastardkb/skeletyl/promicro", "LAYOUT_split_3x5_3", "NIKROULAH", KEEP_3,
         False, "users/nikroulah/qmk_viewer_maps/skeletyl/keymap.json"),
        ("ferris/sweep", "LAYOUT_split_3x5_2", "SWEEP", KEEP_2,
         True, "users/nikroulah/qmk_viewer_maps/sweep/keymap.json"),
    ]
    for kb, layout, suffix, keep, reuse_button, relpath in targets:
        out = {
            "version": 1,
            "notes": "Generated from miryoku_layer_alternatives.h (see gen_keymap_json.py). "
                     "Render source for qmk_viewer; layer order matches the Miryoku enum.",
            "documentation": "",
            "keyboard": kb,
            "keymap": "nikroulah",
            "layout": layout,
            "layers": build(text, suffix, keep, reuse_button),
            "author": "nikroulah",
        }
        path = os.path.join(REPO, relpath)
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "w") as f:
            json.dump(out, f, indent=2)
            f.write("\n")
        print("wrote", relpath)
        for i, name in enumerate(ENUM_ORDER):
            print("  %d %-6s %s ..." % (i, name, out["layers"][i][:5]))


if __name__ == "__main__":
    main()
