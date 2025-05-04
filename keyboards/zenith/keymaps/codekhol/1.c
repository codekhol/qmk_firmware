bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool shifted = get_mods() & MOD_MASK_SHIFT;

    switch (keycode) {
        case KC_LBRC:  // Physical key labeled [ ]
            if (record->event.pressed) {
                if (shifted) {
                    // Temporarily disable Shift to send plain KC_RBRC (which is ])
                    uint8_t mods = get_mods();
                    del_mods(MOD_MASK_SHIFT);
                    tap_code(KC_RBRC);  // Sends ]
                    set_mods(mods);     // Restore original modifiers
                } else {
                    tap_code(KC_LBRC);  // [
                }
            }
            return false;

        case KC_RBRC:  // Physical key labeled { }
            if (record->event.pressed) {
                if (shifted) {
                    tap_code(KC_RBRC);  // }
                } else {
                    tap_code16(S(KC_LBRC));  // {
                }
            }
            return false;

        default:
            return true;
    }
}