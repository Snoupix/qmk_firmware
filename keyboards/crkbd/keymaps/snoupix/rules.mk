# https://github.com/qmk/qmk_firmware/blob/master/docs/config_options.md

# RGB stuff
# https://github.com/qmk/qmk_firmware/tree/master/keyboards/crkbd#rgb-matrix
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
# RGB_MATRIX_SPLIT_RIGHT=yes

# Extra features / APIs
VIA_ENABLE = no
TAP_DANCE_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
SEND_STRING_ENABLE = yes
UNICODE_COMMON = no
UNICODE_ENABLE = no
UNICODEMAP_ENABLE = no

# Oled screens
WPM_ENABLE = yes
OLED_ENABLE = yes
SRC += oled_icons.c

# Needed / Opti
LTO_ENABLE = yes
SPLIT_KEYBOARD = yes
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
AVR_USE_MINIMAL_PRINTF = yes
MUSIC_ENABLE = no
