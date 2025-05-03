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

// v1
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LBRC:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    // Temporarily disable Shift to send unshifted ']'
                    uint8_t saved_mods = get_mods();
                    del_mods(MOD_MASK_SHIFT);
                    tap_code(KC_RBRC);  // sends ]
                    set_mods(saved_mods);
                } else {
                    tap_code(KC_LBRC);  // sends [
                }
            }
            return false;

        case KC_RBRC:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(S(KC_RBRC));  // sends }
                } else {
                    tap_code16(S(KC_LBRC));  // sends {
                }
            }
            return false;
    }

    return true;
}

// v2
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     static bool shift_down = false;

//     // Track the Shift key state manually
//     if (keycode == KC_LSFT) {
//         shift_down = record->event.pressed;
//         return true;
//     }

//     switch (keycode) {
//         case KC_LBRC:
//             if (record->event.pressed) {
//                 uint8_t mods = get_mods();
//                 if (shift_down) {
//                     del_mods(MOD_MASK_SHIFT);
//                     register_code(KC_RBRC);  // ]
//                     set_mods(mods);
//                 } else {
//                     register_code(KC_LBRC);  // [
//                 }
//             } else {
//                 unregister_code(KC_LBRC);
//                 unregister_code(KC_RBRC);
//             }
//             return false;

//         case KC_RBRC:
//             if (record->event.pressed) {
//                 if (shift_down) {
//                     register_code16(S(KC_RBRC));  // }
//                 } else {
//                     register_code16(S(KC_LBRC));  // {
//                 }
//             } else {
//                 unregister_code16(S(KC_RBRC));
//                 unregister_code16(S(KC_LBRC));
//             }
//             return false;
//     }

//     return true;
// }
