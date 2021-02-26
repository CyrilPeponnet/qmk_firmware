#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"
#include "config.h"

enum anne_pro_layers {
  _BASE_LAYER,
  _FN1_LAYER,
  _FN2_LAYER,
  _FN3_LAYER,
};

enum macros {
  SUSPEND = AP2_SAFE_RANGE,
  SSO,
};


typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

// Define a type for as many tap dance states as you need
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    TRIPLE_TAP,
    TRIPLE_HOLD
};


enum {
    TAP_DANCE,
};


// This is ROW*MATRIX_COLS + COL
#define CAPS_LOCATION (MATRIX_COLS * 2 + 0)

// Key symbols are based on QMK. Use them to remap your keyboard
/*
* Layer _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | Caps    |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
* |-----------------------------------------------------------------------------------------+
* | Ctrl  |  ALT   |  L1  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
* \-----------------------------------------------------------------------------------------/
* Layer TAP in _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
* |-----------------------------------------------------------------------------------------+
* |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
* |-----------------------------------------------------------------------------------------+
* |         |     |     |     |     |     |     |     |     |     |     |     |             |
* |-----------------------------------------------------------------------------------------+
* |            |     |     |     |     |     |     |     |     |     |     |       UP       |
* |-----------------------------------------------------------------------------------------+
* |       |       |       |                                 |       |  LEFT | DOWN  | RIGHT |
* \-----------------------------------------------------------------------------------------/
*/
 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_BASE_LAYER] = KEYMAP( /* Base */
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    TD(TAP_DANCE), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_UP),
    KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RALT, LT(_FN1_LAYER,KC_LEFT), LT(_FN2_LAYER,KC_DOWN), RCTL_T(KC_RGHT)
),
  /*
  * Layer _FN1_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | MUTE | VDOWN | VUP |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  LC  | UP  |  RC |  r  |  t  |  y  |  u  |  i  |  o  | PLAY | PREV | NEXT |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  GP->MEH(KC_G)  |  h  |  j  |  k  |  l  | PGUP|PGDN |    SSO    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |z |x|c |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    KC_MS_WH_DOWN       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  KC_MS_WH_UP  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN1_LAYER] = KEYMAP( /* Base */
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_MUTE, KC_VOLD, KC_VOLU, KC_DEL,
    KC_TRNS, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_MPRV, KC_MNXT, KC_TRNS,
    KC_TRNS, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRNS, MEH(KC_G), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, SSO,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_MS_WH_DOWN,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_WH_UP, KC_TRNS
),
  /*
  * Layer _FN2_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  ESC  | BT1 | BT2 | BT3 | BT4 |  F5 |  F6 |  F7 |LEDOF|LEDON| LED BRI | LED ANIM | F12 | SUSPEND |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               KC_MS_WH_UP             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN2_LAYER] = KEYMAP( /* Base */
    KC_ESC, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, KC_TRNS, KC_TRNS, KC_TRNS, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, KC_TRNS, SUSPEND,
    MO(_FN2_LAYER), KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_WH_UP, KC_TRNS, MO(_FN1_LAYER), MO(_FN2_LAYER), KC_TRNS
 ),
  /*
  * Layer _FN3_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | DYN_REC_START1 | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |V-UP |V-DWN|MUTE |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN3_LAYER] = KEYMAP( /* Base */
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_END, KC_TRNS,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_FN2_LAYER), KC_TRNS
),
};

const uint16_t keymaps_size = sizeof(keymaps);



// Function associated with all tap dances
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void layer_finished(qk_tap_dance_state_t *state, void *user_data);
void layer_reset(qk_tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with example tap dance key
static tap tap_state = {
  .is_press_action = true,
  .state = 0
};


// Determine the current tap dance state
uint8_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (!state->pressed) return DOUBLE_TAP;
    else return DOUBLE_HOLD;
  } else if (state->count == 3) {
    if (!state->pressed) return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }  else return 8;
}

// Functions that control what our tap dance key does
void layer_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);

  switch (tap_state.state) {
    case SINGLE_TAP:
      tap_code(KC_CAPSLOCK);
      break;
    case SINGLE_HOLD:
      layer_on(_FN1_LAYER);
      break;
    case DOUBLE_HOLD:
      layer_on(_FN2_LAYER);
      break;
    case TRIPLE_HOLD:
      layer_on(_FN3_LAYER);
      break;
  }
}

void layer_reset(qk_tap_dance_state_t *state, void *user_data) {
  // If the key was held down and now is released then switch off the layer
  if (tap_state.state == SINGLE_HOLD) {
    layer_off(_FN1_LAYER);
  }
  if (tap_state.state == DOUBLE_HOLD) {
    layer_off(_FN2_LAYER);
  }
  if (tap_state.state == TRIPLE_HOLD) {
    layer_off(_FN3_LAYER);
  }
  tap_state.state = 0;
}


// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
  [TAP_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, layer_finished, layer_reset, 250),
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

// Code to run after initializing the keyboard
void keyboard_post_init_user(void) {
    annepro2LedEnable();
    annepro2LedSetProfile(0);
}

// Change color layout depending on the layer
layer_state_t layer_state_set_user(layer_state_t layer) {
  switch(get_highest_layer(layer)) {
    case _FN1_LAYER:
      // Set the leds to green
      annepro2LedSetProfile(1);
      break;
    case _FN2_LAYER:
      // Set the leds to blue
      annepro2LedSetProfile(2);
      break;
    case _FN3_LAYER:
      // Set the leds to orange
      annepro2LedSetProfile(3);
      break;
    default:
      // Reset back to the current profile
      annepro2LedSetProfile(0);
      break;
  }
  return layer;
}

// The function to handle the caps lock logic
// We use a state to avoid clearing the background if capslock was not set
// somehow it leads to flickering with fn1 and fn1 in tap mode.
bool is_caps_on = false;
bool led_update_user(led_t leds) {
  if (leds.caps_lock) {
    // Set the leds to red
    is_caps_on = true;
    annepro2LedSetForegroundColor(0xFF, 0x00, 0x00);
  } else if (is_caps_on){
    // Reset back to the current profile if there is no layer active
    if(!layer_state_is(_FN1_LAYER) && !layer_state_is(_FN2_LAYER)) {
      annepro2LedResetForegroundColor();
      is_caps_on = false;
    }
  }
  return true;
}

// Track led status
bool is_led_on = true;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SSO:
      if (record->event.pressed) {
        SEND_STRING(KC_TOKEN);
      }
      return true;
    // Turn off the leds and send the sleep shortcut
    case SUSPEND:
      if (record->event.pressed) {
        if(is_led_on) {
          is_led_on = false;
          annepro2LedDisable();
          SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_ESC))));
        }
      }
      return true;
    default:
       if (record->event.pressed) {
         // If the leds where off then we turn them on
          if(!is_led_on) {
              is_led_on = true;
              annepro2LedEnable();
            }
          }
        return true;
    }
}
