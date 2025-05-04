static bool lbrc_held = false;
static uint16_t lbrc_code = KC_NO;
static bool last_shift_state = false;

static bool rbrc_held = false;
static uint16_t rbrc_code = KC_NO;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

    return true;
}

void matrix_scan_user(void) {
    static uint16_t last_scan = 0;
    if (timer_elapsed(last_scan) < 10) return;
    last_scan = timer_read();

    bool shift_now = get_mods() & MOD_MASK_SHIFT;

    if (lbrc_held && shift_now != last_shift_state) {
        // Shift state changed while LBRC held – re-register
        unregister_code(lbrc_code);
        uint8_t mods = get_mods();
        del_mods(MOD_MASK_SHIFT);
        lbrc_code = shift_now ? KC_RBRC : KC_LBRC;
        register_code(lbrc_code);
        set_mods(mods);
    }

    last_shift_state = shift_now;
}
