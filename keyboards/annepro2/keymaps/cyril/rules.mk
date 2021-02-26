# Keys
TAP_DANCE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
MOUSEKEY_ENABLE = yes

# Get token from keychain
KC_TOKEN = $(shell security find-generic-password -a qmk -s pass -w)
CFLAGS += -DKC_TOKEN=\"$(KC_TOKEN)\"
