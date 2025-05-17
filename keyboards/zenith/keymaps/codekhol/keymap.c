#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  KC_BSPC,
        KC_LOPT, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, MO(1),   KC_UP,
        KC_LCTL, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_DOWN,
        KC_LCMD, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LEFT, KC_RGHT,
        KC_SPC
    ),

    [1] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(0),   KC_PGUP,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END,
        _______
    )
};

static bool lbrc_held = false;
static bool rbrc_held = false;
static uint16_t lbrc_code = KC_NO;
static uint16_t rbrc_code = KC_NO;
static uint8_t last_shift_state = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LBRC:
            if (record->event.pressed) {
                lbrc_held = true;

                uint8_t mods = get_mods();
                if (mods & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    lbrc_code = KC_RBRC;  // ]
                    register_code(lbrc_code);
                    set_mods(mods);
                } else {
                    lbrc_code = KC_LBRC;  // [
                    register_code(lbrc_code);
                }
            } else {
                lbrc_held = false;
                unregister_code(lbrc_code);
                lbrc_code = KC_NO;
            }
            return false;

        case KC_RBRC:
            if (record->event.pressed) {
                rbrc_held = true;

                if (get_mods() & MOD_MASK_SHIFT) {
                    rbrc_code = S(KC_RBRC);  // }
                } else {
                    rbrc_code = S(KC_LBRC);  // {
                }

                register_code16(rbrc_code);
            } else {
                rbrc_held = false;
                unregister_code16(rbrc_code);
                rbrc_code = KC_NO;
            }
            return false;
        
        case FN_KEY:
            fn_pressed = record->event.pressed;
            break;
    
        case OPT_KEY:
            opt_pressed = record->event.pressed;
            break;
    }

    return true;
}

void matrix_scan_user(void) {
    uint8_t shift_state = get_mods() & MOD_MASK_SHIFT;

    if (shift_state != last_shift_state) {
        last_shift_state = shift_state;

        if (lbrc_held) {
            unregister_code(lbrc_code);

            uint8_t mods = get_mods();
            del_mods(MOD_MASK_SHIFT);

            lbrc_code = shift_state ? KC_RBRC : KC_LBRC;
            register_code(lbrc_code);

            set_mods(mods);
        }

        if (rbrc_held) {
            unregister_code16(rbrc_code);

            rbrc_code = shift_state ? S(KC_RBRC) : S(KC_LBRC);
            register_code16(rbrc_code);
        }
    }
}
