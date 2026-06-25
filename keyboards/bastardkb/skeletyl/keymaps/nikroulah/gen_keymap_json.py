import json

# Each layer = 40 tokens (the 4x10 Miryoku macro grid) copied verbatim from the
# MIRYOKU_ALTERNATIVES_*_NIKROULAH macros in miryoku_layer_alternatives.h.
slots = {
"BASE": [
"KC_Q","KC_W","KC_E","KC_R","KC_T","KC_Y","KC_U","KC_I","KC_O","KC_P",
"LSFT_T(KC_A)","LCTL_T(KC_S)","LALT_T(KC_D)","LGUI_T(KC_F)","KC_G","KC_H","RGUI_T(KC_J)","RALT_T(KC_K)","RCTL_T(KC_L)","RSFT_T(KC_QUOT)",
"LT(U_BUTTON,KC_Z)","KC_X","KC_C","KC_V","KC_B","KC_N","KC_M","KC_COMM","KC_DOT","LT(U_BUTTON,KC_SLSH)",
"U_NP","U_NP","LT(U_EXTRA,KC_ESC)","LT(U_NAV,KC_SPC)","LT(U_MOUSE,KC_TAB)","LT(U_SYM,KC_ENT)","LT(U_NUM,KC_BSPC)","LT(U_MEDIA,KC_DEL)","U_NP","U_NP",
],
"TAP": [
"KC_TRNS","U_NA","U_NA","U_NA","U_NA","KC_LCBR","KC_AMPR","KC_ASTR","KC_LPRN","KC_RCBR",
"U_NA","U_NA","U_NA","U_NA","U_NA","KC_PLUS","KC_DLR","KC_PERC","KC_CIRC","KC_COLN",
"U_NA","U_NA","U_NA","U_NA","U_NA","KC_PIPE","KC_EXLM","KC_AT","KC_HASH","KC_TILD",
"U_NP","U_NP","KC_TRNS","U_NA","U_NA","KC_UNDS","KC_LPRN","KC_RPRN","U_NP","U_NP",
],
"EXTRA": [
"MO(U_TAP)","U_NA","U_NA","U_NA","U_NA","KC_LBRC","KC_7","KC_8","KC_9","KC_RBRC",
"KC_LSFT","KC_LCTL","KC_LALT","KC_LGUI","U_NA","KC_EQL","KC_4","KC_5","KC_6","KC_SCLN",
"MO(U_FUN)","U_NA","U_NA","U_NA","U_NA","KC_BSLS","KC_1","KC_2","KC_3","KC_GRV",
"U_NP","U_NP","KC_TRNS","U_NA","U_NA","KC_MINS","KC_DOT","KC_0","U_NP","U_NP",
],
"BUTTON": [
"U_UND","U_NA","U_NA","U_CPY","U_CUT","U_CUT","U_CPY","U_NA","U_NA","U_UND",
"KC_LSFT","KC_LCTL","KC_LALT","KC_LGUI","U_PST","U_PST","KC_RGUI","KC_RALT","KC_RCTL","KC_RSFT",
"U_NA","U_NA","U_NA","U_NA","U_NA","U_NA","U_NA","U_NA","U_NA","U_NA",
"U_NP","U_NP","U_NA","U_NA","U_NA","U_NA","U_NA","U_NA","U_NP","U_NP",
],
"NAV": [
"U_NA","U_NA","U_NA","U_NA","U_NA","U_CUT","U_CPY","KC_UP","U_NA","U_UND",
"KC_LSFT","KC_LCTL","KC_LALT","KC_LGUI","U_NA","U_PST","KC_LEFT","KC_DOWN","KC_RGHT","U_NA",
"U_NA","U_NA","U_NA","U_NA","U_NA","U_NA","KC_HOME","KC_PGDN","KC_PGUP","KC_END",
"U_NP","U_NP","U_NA","KC_TRNS","U_NA","KC_ENT","KC_BSPC","KC_DEL","U_NP","U_NP",
],
"MOUSE": [
"U_NA","U_NA","U_NA","U_NA","U_NA","U_CUT","U_CPY","KC_MS_U","U_NA","U_UND",
"KC_LSFT","KC_LCTL","KC_LALT","KC_LGUI","U_NA","U_PST","KC_MS_L","KC_MS_D","KC_MS_R","U_NA",
"U_NA","KC_ACL0","KC_ACL1","KC_ACL2","U_NA","U_NA","KC_WH_L","KC_WH_D","KC_WH_U","KC_WH_R",
"U_NP","U_NP","U_NA","U_NA","KC_TRNS","KC_BTN2","KC_BTN1","KC_BTN3","U_NP","U_NP",
],
"MEDIA": [
"U_NA","U_NA","U_NA","U_NA","U_NA","QK_BOOT","U_NA","U_NA","U_NA","U_NA",
"KC_MRWD","KC_VOLD","KC_VOLU","KC_MFFD","U_NA","U_NA","KC_RGUI","KC_RALT","KC_RCTL","KC_RSFT",
"U_NA","U_NA","U_NA","U_NA","U_NA","U_NA","U_NA","U_NA","U_NA","U_NA",
"U_NP","U_NP","KC_MSTP","KC_MPLY","KC_MUTE","U_NA","U_NA","KC_TRNS","U_NP","U_NP",
],
"NUM": [
"KC_LBRC","KC_7","KC_8","KC_9","KC_RBRC","U_NA","U_NA","U_NA","U_NA","U_NA",
"KC_SCLN","KC_4","KC_5","KC_6","KC_EQL","U_NA","KC_RGUI","KC_RALT","KC_RCTL","KC_RSFT",
"KC_GRV","KC_1","KC_2","KC_3","KC_BSLS","U_NA","U_NA","U_NA","U_NA","U_NA",
"U_NP","U_NP","KC_DOT","KC_0","KC_MINS","U_NA","KC_TRNS","U_NA","U_NP","U_NP",
],
"SYM": [
"KC_LCBR","KC_AMPR","KC_ASTR","KC_LPRN","KC_RCBR","U_NA","U_NA","U_NA","U_NA","U_NA",
"KC_COLN","KC_DLR","KC_PERC","KC_CIRC","KC_PLUS","U_NA","KC_RGUI","KC_RALT","KC_RCTL","KC_RSFT",
"KC_TILD","KC_EXLM","KC_AT","KC_HASH","KC_PIPE","U_NA","U_NA","U_NA","U_NA","U_NA",
"U_NP","U_NP","KC_LPRN","KC_RPRN","KC_UNDS","KC_TRNS","U_NA","U_NA","U_NP","U_NP",
],
"FUN": [
"U_NA","U_NA","U_NA","U_NA","U_NA","KC_PSCR","KC_F7","KC_F8","KC_F9","KC_F12",
"U_NA","U_NA","U_NA","U_NA","U_NA","LCTL(LSFT(LGUI(KC_4)))","KC_F4","KC_F5","KC_F6","KC_F11",
"KC_TRNS","U_NA","U_NA","U_NA","U_NA","LCTL(LSFT(LGUI(KC_3)))","KC_F1","KC_F2","KC_F3","KC_F10",
"U_NP","U_NP","KC_TRNS","U_NA","U_NA","U_NA","U_NA","U_NA","U_NP","U_NP",
],
}

# Miryoku enum order -> json layer index (so byte 0 from the firmware matches).
ENUM_ORDER = ["BASE","EXTRA","TAP","BUTTON","NAV","MOUSE","MEDIA","NUM","SYM","FUN"]

XLATE = {
"U_NP":"KC_NO","U_NA":"KC_NO","U_NU":"KC_NO",
"U_UND":"LGUI(KC_Z)","U_CUT":"LGUI(KC_X)","U_CPY":"LGUI(KC_C)","U_PST":"LGUI(KC_V)","U_RDO":"SGUI(KC_Z)",
"LT(U_EXTRA,KC_ESC)":"LT(1,KC_ESC)","LT(U_NAV,KC_SPC)":"LT(4,KC_SPC)","LT(U_MOUSE,KC_TAB)":"LT(5,KC_TAB)",
"LT(U_SYM,KC_ENT)":"LT(8,KC_ENT)","LT(U_NUM,KC_BSPC)":"LT(7,KC_BSPC)","LT(U_MEDIA,KC_DEL)":"LT(6,KC_DEL)",
"LT(U_BUTTON,KC_Z)":"LT(3,KC_Z)","LT(U_BUTTON,KC_SLSH)":"LT(3,KC_SLSH)",
"MO(U_TAP)":"MO(2)","MO(U_FUN)":"MO(9)",
}

def to_json_layer(tokens):
    assert len(tokens) == 40, len(tokens)
    keys36 = tokens[0:30] + tokens[32:38]   # drop the 4 U_NP corners, keep 6 thumbs
    return [XLATE.get(t, t) for t in keys36]

out = {
    "version": 1,
    "notes": "Generated from the MIRYOKU_ALTERNATIVES_*_NIKROULAH layers. Layer order matches the Miryoku layer enum so qmk_viewer's layer number lines up with the firmware's raw-HID indicator.",
    "documentation": "",
    "keyboard": "bastardkb/skeletyl/v1/elitec",
    "keymap": "nikroulah",
    "layout": "LAYOUT_split_3x5_3",
    "layers": [to_json_layer(slots[name]) for name in ENUM_ORDER],
    "author": "nikroulah",
}

path = "/Users/jwang/qmk_firmware/keyboards/bastardkb/skeletyl/keymaps/nikroulah/keymap.json"
with open(path, "w") as f:
    json.dump(out, f, indent=2)
    f.write("\n")

print("wrote", path)
for i, name in enumerate(ENUM_ORDER):
    print(i, name, "->", out["layers"][i][:5], "...")
