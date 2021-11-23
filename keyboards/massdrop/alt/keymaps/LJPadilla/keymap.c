#include QMK_KEYBOARD_H

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    MD_BOOT,               //Restart into bootloader after hold timeout
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
            KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
            KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_AMPR, \
            TG(2),      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_CIRC, \
            KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_ASTR, \
            KC_LCTL,    KC_LALT, KC_LGUI,                   KC_SPC,                          TG(1),  KC_RALT,              KC_LEFT, KC_DOWN, KC_RGHT \
            ),
    [1] = LAYOUT_65_ansi_blocker(
            KC_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
            _______, _______, _______,                            KC_SPC,                             _______, _______, _______, _______, _______ \
            ),
    [2] = LAYOUT_65_ansi_blocker(
            KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  MD_BOOT, RGB_TOG,\
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PERC, \
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_EXLM, \
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_CAPS,          KC_PGUP, KC_AT, \
            _______, _______, _______,                 KC_MPLY,                                       _______, _______, KC_HOME, KC_PGDN, KC_END \
            ),
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {  
                    case LED_FLAG_ALL: {
                                           rgb_matrix_set_flags(LED_FLAG_NONE);
                                           rgb_matrix_disable_noeeprom();
                                       }
                                       break;
                    default: {
                                 rgb_matrix_set_flags(LED_FLAG_ALL);
                                 rgb_matrix_enable_noeeprom();
                             }
                             break;
                }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

layer_state_t layer_state_set_user(layer_state_t state){
    rgb_matrix_set_color_all(0,0,0);
    uint8_t layer = get_highest_layer(state);
    switch(layer){
        case 0:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_sunset);
            break;
        case 1:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_sunset_gaming);
            break;
        case 2:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_sunset_function);
            break; 
    }
    return state;
}
