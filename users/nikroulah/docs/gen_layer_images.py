#!/usr/bin/env python3
"""Render per-layer SVGs for the nikroulah Miryoku layouts (for readme.md),
using keymap-drawer. Reads the qmk_viewer render JSONs (which are generated
from miryoku_nikroulah_alternatives.h, so these images can't drift from the
firmware), names the layers, prettifies the legends (Gui->cmd glyph, arrows,
layer holds -> layer names), drops the blank EXTRA/TAP slots, and draws each
remaining layer to docs/img/<board>/<layer>.svg with a clean split-ortho board.

Setup + run (keymap-drawer is not a repo dependency; install it ad hoc):

    python3 -m venv /tmp/kmd-venv
    /tmp/kmd-venv/bin/pip install keymap-drawer
    /tmp/kmd-venv/bin/python3 users/nikroulah/docs/gen_layer_images.py
"""
import json, os, subprocess, sys, tempfile
import yaml

HERE = os.path.dirname(os.path.abspath(__file__))
MAPS = os.path.join(HERE, "..", "qmk_viewer_maps")
KEYMAP = os.path.join(os.path.dirname(sys.executable), "keymap")

# Miryoku enum order -> display name. EXTRA/TAP are blank here and dropped.
NAMES = ["Base", "Extra", "Tap", "Button", "Nav", "Mouse", "Media", "Num", "Sym", "Fun"]
DRAW_LAYERS = ["Base", "Button", "Nav", "Mouse", "Media", "Num", "Sym", "Fun"]

# Exact-match legend prettifying (applied to tap and hold legends).
EXACT = {
    "LSFT": "⇧", "RSFT": "⇧", "LCTL": "⌃", "RCTL": "⌃",
    "LALT": "⌥", "RALT": "⌥", "LGUI": "⌘", "RGUI": "⌘", "ALGR": "⌥",
    "UP": "↑", "DOWN": "↓", "LEFT": "←", "RGHT": "→",
    "QK BOOT": "Boot", "CW TOGG": "Caps\nWord",
    "MS U": "🖱↑", "MS D": "🖱↓", "MS L": "🖱←", "MS R": "🖱→",
    "WH U": "≣↑", "WH D": "≣↓", "WH L": "≣←", "WH R": "≣→",
    "BTN1": "L-clk", "BTN2": "R-clk", "BTN3": "M-clk",
    "ACL0": "slow", "ACL1": "med", "ACL2": "fast",
    "VOLU": "Vol+", "VOLD": "Vol−", "MUTE": "Mute", "EJCT": "Eject",
    "MPLY": "▶", "MSTP": "■", "MPRV": "⏮", "MNXT": "⏭", "MRWD": "⏪", "MFFD": "⏩",
    "PSCR": "PrtSc", "TAB": "Tab", "ENT": "Enter", "SPC": "Space", "BSPC": "Bksp",
}
EXACT.update({"L%d" % i: NAMES[i] for i in range(10)})
# Substring (combo-modifier) prettifying, applied after exact misses.
SUBS = [("Gui+", "⌘"), ("Sft+", "⇧"), ("Alt+", "⌥"), ("Ctl+", "⌃")]


def pretty(s):
    if not isinstance(s, str):
        return s
    if s in EXACT:
        return EXACT[s]
    for a, b in SUBS:
        s = s.replace(a, b)
    return s


def fix_legend(item):
    if isinstance(item, str):
        return pretty(item)
    if isinstance(item, dict):
        for f in ("t", "h"):
            if f in item and isinstance(item[f], str):
                item[f] = pretty(item[f])
    return item


def board(json_path, out_dir, thumbs):
    with tempfile.NamedTemporaryFile("w", suffix=".yaml", delete=False) as tf:
        ytmp = tf.name
    subprocess.run([KEYMAP, "parse", "-q", json_path, "-o", ytmp], check=True)
    data = yaml.safe_load(open(ytmp))
    # clean split-ortho board geometry (like Miryoku's own reference images)
    data["layout"] = {"ortho_layout": {"split": True, "rows": 3, "columns": 5, "thumbs": thumbs}}
    layers = {}
    for i, name in enumerate(NAMES):
        keys = data["layers"]["L%d" % i]
        layers[name] = [fix_legend(k) for k in keys]
    data["layers"] = layers
    yaml.safe_dump(data, open(ytmp, "w"), allow_unicode=True, sort_keys=False, width=200)

    os.makedirs(out_dir, exist_ok=True)
    for name in DRAW_LAYERS:
        out = os.path.join(out_dir, name.lower() + ".svg")
        subprocess.run([KEYMAP, "draw", ytmp, "-s", name, "-o", out], check=True)
        print("wrote", os.path.relpath(out, os.path.join(HERE, "..", "..", "..")))
    os.unlink(ytmp)


def main():
    board(os.path.join(MAPS, "skeletyl", "keymap.json"),
          os.path.join(HERE, "img", "skeletyl"), thumbs=3)
    board(os.path.join(MAPS, "sweep", "keymap.json"),
          os.path.join(HERE, "img", "sweep"), thumbs=2)


if __name__ == "__main__":
    main()
