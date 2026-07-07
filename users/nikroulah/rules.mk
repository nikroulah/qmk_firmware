# nikroulah custom Miryoku userspace.
#
# Mirrors users/manna-harbour_miryoku/rules.mk (the miryoku feature set), but
# points introspection at our own nikroulah.c (a verbatim copy of the engine
# keymap C with our qmk_viewer additions). RAW_ENABLE (for the qmk_viewer
# indicator) is currently off. The miryoku post_rules.mk
# (MIRYOKU_* make-var -> -D handling) is reused from the pristine engine dir.

MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes

INTROSPECTION_KEYMAP_C = nikroulah.c # keymaps

# Raw HID for the qmk_viewer live layer/keypress indicator (see the
# matrix_scan_user / raw_hid_* handlers in nikroulah.c). Currently disabled;
# flip back to yes to re-enable the qmk_viewer indicator.
RAW_ENABLE = no

include users/manna-harbour_miryoku/post_rules.mk
