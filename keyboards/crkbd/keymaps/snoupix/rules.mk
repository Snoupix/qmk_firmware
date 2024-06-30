# https://github.com/qmk/qmk_firmware/blob/master/docs/config_options.md

# RGB stuff
# https://github.com/qmk/qmk_firmware/tree/master/keyboards/crkbd#rgb-matrix
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
# RGB_MATRIX_SPLIT_RIGHT=yes

# Extra features
VIA_ENABLE = yes
TAP_DANCE_ENABLE = no
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = no

# Oled screens
WPM_ENABLE = yes
OLED_ENABLE = yes
SRC += oled_icons.c

# Needed
LTO_ENABLE = yes
SPLIT_KEYBOARD = yes
