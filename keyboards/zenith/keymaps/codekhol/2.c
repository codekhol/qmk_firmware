
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool lbrc_held = false;
    static bool rbrc_held = false;
    static uint16_t lbrc_code = KC_NO;
    static uint16_t rbrc_code = KC_NO;

    if (keycode == KC_LBRC) {
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
    }

    if (keycode == KC_RBRC) {
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
    }

    // --- Shift pressed or released while bracket key is held ---
    if (keycode == KC_LSFT || keycode == KC_RSFT) {
        if (record->event.pressed) {
            // Shift pressed
            if (lbrc_held) {
                unregister_code(lbrc_code);
                uint8_t mods = get_mods();
                del_mods(MOD_MASK_SHIFT);
                lbrc_code = KC_RBRC;  // ]
                register_code(lbrc_code);
                set_mods(mods);
            }
            if (rbrc_held) {
                unregister_code16(rbrc_code);
                rbrc_code = S(KC_RBRC);  // }
                register_code16(rbrc_code);
            }
        } else {
            // Shift released
            if (lbrc_held) {
                unregister_code(lbrc_code);
                uint8_t mods = get_mods();
                del_mods(MOD_MASK_SHIFT);
                lbrc_code = KC_LBRC;  // [
                register_code(lbrc_code);
                set_mods(mods);
            }
            if (rbrc_held) {
                unregister_code16(rbrc_code);
                rbrc_code = S(KC_LBRC);  // {
                register_code16(rbrc_code);
            }
        }
        return true;
    }

    return true;
}