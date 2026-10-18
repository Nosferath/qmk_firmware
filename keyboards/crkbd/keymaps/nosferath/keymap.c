/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#if __has_include("secrets.h")
#    include "secrets.h"
#else
#    define EMAILS "you@example.com\0"
#endif

/*
 * Two typing setups, chosen with the LAYOUT key on the adjust layer:
 *   - QWERTY layer: the computer is set to Colemak (home machines).
 *   - COLEMAK layer: the computer is set to plain US (any other machine).
 * Anything the firmware types itself (accents, ∴, emails) is translated
 * for the computer's layout based on which of the two is active.
 */
enum layers { _QWERTY, _COLEMAK, _NUM, _SYM, _ADJ };

enum custom_keycodes {
    LAYOUT_TG = SAFE_RANGE, // switch between QWERTY and Colemak setups
    EMAIL,                  // type an email address; press again for the next one
    THEREF,                 // type ∴
    COMPOSE,                // Linux Compose key (sent as Caps Lock)
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO(_NUM),  KC_SPC,     KC_ENT, MO(_SYM), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO(_NUM),  KC_SPC,     KC_ENT, MO(_SYM), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, COMPOSE,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, MO(_ADJ), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_MUTE, KC_VOLD, KC_VOLU,   EMAIL,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT,  THEREF,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO(_ADJ),  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJ] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,LAYOUT_TG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,  KC_INS, KC_HOME, KC_PGUP, KC_PSCR, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU,                      XXXXXXX,  KC_DEL,  KC_END, KC_PGDN, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, RM_NEXT, RM_HUED, RM_SATD, RM_VALD, RM_SPDD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};
// clang-format on

/* ---------- Host setup ---------- */

static bool host_is_mac(void) {
    os_variant_t os = detected_host_os();
    return os == OS_MACOS || os == OS_IOS;
}

// The computer runs Colemak when the keyboard itself is in QWERTY mode.
static bool host_is_colemak(void) {
    return get_highest_layer(default_layer_state) == _QWERTY;
}

// What a Colemak computer types for each QWERTY key A..Z ('o' is on KC_SCLN).
static const char colemak_chars[] PROGMEM = "abcsftdhuneimky;qprglvwxjz";

// Keycode to send so the computer types `ch` (a lowercase letter or ';').
static uint8_t host_keycode(char ch) {
    if (!host_is_colemak()) return ch == ';' ? KC_SCLN : KC_A + (ch - 'a');
    if (ch == 'o') return KC_SCLN;
    for (uint8_t i = 0; i < 26; i++) {
        if (pgm_read_byte(&colemak_chars[i]) == ch) return KC_A + i;
    }
    return KC_NO;
}

// Letter the computer types for a key on the active base layer, or 0.
static char typed_letter(uint16_t keycode) {
    if (keycode == KC_SCLN) return host_is_colemak() ? 'o' : 0;
    if (keycode < KC_A || keycode > KC_Z) return 0;
    return host_is_colemak() ? pgm_read_byte(&colemak_chars[keycode - KC_A]) : 'a' + (keycode - KC_A);
}

static void tap_shifted(uint8_t keycode, bool shift) {
    tap_code16(shift ? LSFT(keycode) : keycode);
}

#define LUT_BIT(table, pos) ((pgm_read_byte(&(table)[(pos) / 8]) >> ((pos) % 8)) & 1)

// Like SEND_STRING, but translated for a Colemak computer when needed.
static void send_text_P(const char *str) {
    char c;
    while ((c = pgm_read_byte(str++))) {
        uint8_t keycode = pgm_read_byte(&ascii_to_keycode_lut[(uint8_t)c]);
        bool    shift   = LUT_BIT(ascii_to_shift_lut, (uint8_t)c);
        if (keycode == KC_SCLN) {
            keycode = host_keycode(';');
        } else if (keycode >= KC_A && keycode <= KC_Z) {
            keycode = host_keycode('a' + (keycode - KC_A));
        }
        tap_shifted(keycode, shift);
    }
}

// Linux Unicode entry (Ctrl+Shift+U, hex, space), for computers set to plain US.
static void send_unicode_hex(uint16_t codepoint) {
    tap_code16(LCTL(LSFT(KC_U)));
    for (int8_t shift = 12; shift >= 0; shift -= 4) {
        uint8_t digit = (codepoint >> shift) & 0xF;
        tap_code(digit == 0 ? KC_0 : digit < 10 ? KC_1 + digit - 1 : KC_A + digit - 10);
    }
    tap_code(KC_SPC);
}

/* ---------- Accents: hold Right Alt and tap a letter, tap again to cycle ---------- */

enum accent { ACUTE, TILDE, CIRCUMFLEX, GRAVE, DIAERESIS, CEDILLA };

typedef struct {
    char    key;       // letter pressed together with Right Alt
    char    base;      // letter that carries the accent
    uint8_t accent;    // enum accent
    uint8_t codepoint; // lowercase Latin-1 code point (uppercase is 0x20 less)
} accent_t;

// Entries with the same key form one cycle, in this order.
static const accent_t PROGMEM accents[] = {
    {'a', 'a', ACUTE, 0xE1}, {'a', 'a', TILDE, 0xE3}, {'a', 'a', CIRCUMFLEX, 0xE2}, {'a', 'a', GRAVE, 0xE0},
    {'e', 'e', ACUTE, 0xE9}, {'e', 'e', CIRCUMFLEX, 0xEA},
    {'i', 'i', ACUTE, 0xED},
    {'o', 'o', ACUTE, 0xF3}, {'o', 'o', TILDE, 0xF5}, {'o', 'o', CIRCUMFLEX, 0xF4},
    {'u', 'u', ACUTE, 0xFA}, {'u', 'u', DIAERESIS, 0xFC},
    {'y', 'u', DIAERESIS, 0xFC},
    {'n', 'n', TILDE, 0xF1},
    {'c', 'c', CEDILLA, 0xE7},
};

// Right Alt + key for each accent, by computer layout. Accents are dead keys
// (press, then the letter); the cedilla types ç directly.
static const uint8_t PROGMEM dead_keys_colemak[] = {
    [ACUTE] = KC_F, [TILDE] = KC_GRV, [CIRCUMFLEX] = KC_X, [GRAVE] = KC_S, [DIAERESIS] = KC_G, [CEDILLA] = KC_C,
};
static const uint8_t PROGMEM dead_keys_mac_us[] = {
    [ACUTE] = KC_E, [TILDE] = KC_N, [CIRCUMFLEX] = KC_I, [GRAVE] = KC_GRV, [DIAERESIS] = KC_U, [CEDILLA] = KC_C,
};

static void send_accented(const accent_t *entry, bool upper) {
    uint8_t accent = pgm_read_byte(&entry->accent);
    if (!host_is_colemak() && !host_is_mac()) {
        send_unicode_hex(pgm_read_byte(&entry->codepoint) - (upper ? 0x20 : 0));
        return;
    }
    uint8_t dead_key = pgm_read_byte(host_is_colemak() ? &dead_keys_colemak[accent] : &dead_keys_mac_us[accent]);
    if (accent == CEDILLA) {
        tap_code16(upper ? RALT(LSFT(dead_key)) : RALT(dead_key));
        return;
    }
    tap_code16(RALT(dead_key));
    tap_shifted(host_keycode(pgm_read_byte(&entry->base)), upper);
}

static char    cycle_key  = 0; // letter currently being cycled, 0 if none
static uint8_t cycle_step = 0;

// Returns true when the key press was turned into an accented letter.
static bool process_accent(uint16_t keycode, uint8_t mods) {
    char key = typed_letter(keycode);
    if (!key) return false;

    uint8_t first = 0xFF, count = 0;
    for (uint8_t i = 0; i < ARRAY_SIZE(accents); i++) {
        if (pgm_read_byte(&accents[i].key) == key) {
            if (first == 0xFF) first = i;
            count++;
        }
    }
    if (!count) return false;

    // Letters with a single option (ç, ñ, í...) just repeat instead of cycling.
    if (cycle_key == key && count > 1) {
        tap_code(KC_BSPC);
        cycle_step = (cycle_step + 1) % count;
    } else {
        cycle_key  = key;
        cycle_step = 0;
    }
    send_accented(&accents[first + cycle_step], mods & MOD_MASK_SHIFT);
    return true;
}

/* ---------- Emails: press again to replace with the next address ---------- */

static const char emails[] PROGMEM = EMAILS;
static int8_t     email_index = -1; // address last typed, -1 if the last key wasn't EMAIL

static const char *email_at(int8_t index) {
    const char *p = emails;
    while (index-- > 0) p += strlen_P(p) + 1;
    return p;
}

static void type_next_email(void) {
    if (email_index >= 0) {
        const char *previous = email_at(email_index);
        for (uint8_t n = strlen_P(previous); n > 0; n--) tap_code(KC_BSPC);
        email_index++;
        if (!pgm_read_byte(email_at(email_index))) email_index = 0; // wrap around
    } else {
        email_index = 0;
    }
    send_text_P(email_at(email_index));
}

/* ---------- Key handling ---------- */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        if (keycode == KC_RALT) cycle_key = 0;
        return true;
    }

    uint8_t mods = get_mods();
    bool    handled = false;

    // Everything below types on its own, so held modifiers are lifted meanwhile.
    clear_mods();
    if ((mods & MOD_BIT(KC_RALT)) && process_accent(keycode, mods)) {
        handled = true;
    } else {
        cycle_key = 0;
        switch (keycode) {
            case LAYOUT_TG:
                set_single_persistent_default_layer(host_is_colemak() ? _COLEMAK : _QWERTY);
                handled = true;
                break;
            case EMAIL:
                type_next_email();
                handled = true;
                break;
            case THEREF:
                if (host_is_mac()) {
                    send_text_P(PSTR(";tf")); // Mac text replacement: ;tf -> ∴
                } else if (host_is_colemak()) {
                    tap_code(KC_CAPS); // Compose, then : .
                    send_text_P(PSTR(":."));
                } else {
                    send_unicode_hex(0x2234);
                }
                handled = true;
                break;
            case COMPOSE:
                // Linux reads Caps Lock as Compose; on a Mac it's a plain Caps Lock.
                tap_code(KC_CAPS);
                handled = true;
                break;
        }
    }
    // Layer and modifier keys don't interrupt email cycling.
    if (keycode != EMAIL && !IS_QK_MOMENTARY(keycode) && !IS_MODIFIER_KEYCODE(keycode)) email_index = -1;
    set_mods(mods);
    if (handled) send_keyboard_report();
    return !handled;
}

/* ---------- Screens (vertical: 5 characters x 16 lines) ---------- */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // Status screen upright (32x128); the cat screen keeps the keyboard's wide default.
    return is_keyboard_master() ? OLED_ROTATION_270 : rotation;
}

static void write_line(uint8_t row, const char *text_P, bool invert) {
    oled_set_cursor(0, row);
    oled_write_P(text_P, invert);
}

static void write_value(uint8_t row, char label, uint8_t value) {
    oled_set_cursor(0, row);
    oled_write_char(label, false);
    oled_write_char(' ', false);
    oled_write(get_u8_str(value, ' '), false);
}

static void render_status(void) {
    write_line(0, host_is_colemak() ? PSTR("QWRTY") : PSTR("CLMAK"), false);
    write_line(1, host_is_mac() ? PSTR(" MAC ") : PSTR("LINUX"), false);

    switch (get_highest_layer(layer_state)) {
        case _NUM: write_line(3, PSTR(" NUM "), true); break;
        case _SYM: write_line(3, PSTR(" SYM "), true); break;
        case _ADJ: write_line(3, PSTR(" ADJ "), true); break;
        default:   write_line(3, PSTR("     "), false); break;
    }

    uint8_t mods = get_mods() | get_oneshot_mods();
    write_line(5, PSTR("CTRL "), mods & MOD_MASK_CTRL);
    write_line(6, PSTR("SHIFT"), mods & MOD_MASK_SHIFT);
    write_line(7, PSTR("ALT  "), mods & MOD_BIT(KC_LALT));
    write_line(8, PSTR("ALTGR"), mods & MOD_BIT(KC_RALT));
    write_line(9, PSTR("GUI  "), mods & MOD_MASK_GUI);

    // Light settings while the adjust layer is held.
    if (get_highest_layer(layer_state) == _ADJ) {
        write_value(11, 'H', rgb_matrix_get_hue());
        write_value(12, 'S', rgb_matrix_get_sat());
        write_value(13, 'V', rgb_matrix_get_val());
        write_value(14, 'F', rgb_matrix_get_speed());
    } else {
        for (uint8_t row = 11; row <= 14; row++) write_line(row, PSTR("     "), false);
    }
}

/* Bongo cat for the other screen (wide, 128x32), reacting to typing on either
 * half (this board copies the full key state to both halves).
 * Art and drawing approach adapted from keyboards/custommk/evo70
 * (Copyright 2021 customMK, GPL-2.0-or-later): frames are built from shared
 * 6x8-pixel tiles, so all 8 frames take under 600 bytes. */
#    define BONGO_FRAME_MS 75       // idle animation speed
#    define BONGO_PREP_MS 750       // paws stay raised this long after typing
#    define BONGO_SLEEP_MS 15000    // stop the idle animation after this long

static const uint8_t bongofont[] PROGMEM = {
    0xC1, 0xC1, 0xC2, 0x04, 0x08, 0x10,
    0xC0, 0x38, 0x04, 0x03, 0x00, 0x00,
    0xA0, 0x22, 0x24, 0x14, 0x12, 0x12,
    0xA0, 0x21, 0x22, 0x12, 0x11, 0x11,
    0x83, 0x7C, 0x41, 0x41, 0x40, 0x40,
    0x82, 0x82, 0x84, 0x08, 0x10, 0x20,
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x70, 0x19, 0x06, 0x00, 0x00,
    0x80, 0x70, 0x0C, 0x03, 0x00, 0x00,
    0x80, 0x00, 0x30, 0x30, 0x00, 0xC0,
    0x80, 0x00, 0x30, 0x30, 0x00, 0x00,
    0x49, 0x88, 0x08, 0x08, 0x08, 0x00,
    0x44, 0x84, 0x04, 0x04, 0x00, 0x00,
    0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x40, 0x20, 0x20, 0x20, 0x20,
    0x3C, 0xC2, 0x01, 0x01, 0x02, 0x02,
    0x35, 0x01, 0x8A, 0x7C, 0x00, 0x00,
    0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
    0x20, 0x21, 0x22, 0x12, 0x11, 0x11,
    0x20, 0x20, 0x10, 0x10, 0x10, 0x10,
    0x1E, 0xE1, 0x00, 0x00, 0x01, 0x01,
    0x1C, 0xE2, 0x01, 0x01, 0x02, 0x02,
    0x18, 0x64, 0x82, 0x02, 0x02, 0x02,
    0x18, 0x60, 0x80, 0x00, 0x00, 0x00,
    0x18, 0x18, 0x1B, 0x03, 0x00, 0x40,
    0x18, 0x06, 0x05, 0x98, 0x99, 0x84,
    0x12, 0x0B, 0x08, 0x08, 0x08, 0x08,
    0x11, 0x09, 0x08, 0x08, 0x08, 0x08,
    0x10, 0x10, 0xD0, 0x11, 0x0F, 0x21,
    0x10, 0x10, 0x10, 0x11, 0x0F, 0x01,
    0x10, 0x08, 0x08, 0x04, 0x04, 0x04,
    0x10, 0x08, 0x04, 0x02, 0x02, 0x04,
    0x0C, 0x30, 0x40, 0x80, 0x00, 0x00,
    0x0C, 0x0C, 0x0D, 0x01, 0x00, 0x40,
    0x08, 0xE8, 0x08, 0x07, 0x10, 0x24,
    0x08, 0x30, 0x40, 0x80, 0x00, 0x00,
    0x08, 0x08, 0x08, 0x07, 0x00, 0x00,
    0x08, 0x08, 0x04, 0x02, 0x02, 0x02,
    0x08, 0x04, 0x02, 0x01, 0x01, 0x02,
    0x05, 0x05, 0x09, 0x09, 0x10, 0x10,
    0x04, 0x38, 0x40, 0x80, 0x00, 0x00,
    0x04, 0x04, 0x08, 0x08, 0x10, 0x10,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x02, 0x01, 0x00, 0x00,
    0x02, 0x02, 0x81, 0x80, 0x80, 0x00,
    0x02, 0x02, 0x04, 0x04, 0x08, 0x08,
    0x02, 0x02, 0x02, 0x01, 0x01, 0x01,
    0x02, 0x02, 0x01, 0x00, 0x00, 0x00,
    0x01, 0xE1, 0x1A, 0x06, 0x09, 0x31,
    0x01, 0x01, 0x02, 0x04, 0x08, 0x10,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x40, 0x40, 0x20, 0x20,
    0x00, 0x00, 0x80, 0x80, 0x40, 0x40,
    0x00, 0x00, 0x60, 0x60, 0x00, 0x81,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x18,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t bongo_line_data[8][26] PROGMEM = {
    { //idle1
    60, 52, 19, 30, 35,
    22, 47, 51, 60, 9, 0, 17,
    1, 57, 33, 3, 27, 41, 29, 50,
    45, 36, 60, 60, 60, 60},
    { //idle2
    60, 52, 19, 30, 35,
    22, 47, 51, 60, 9, 0, 17,
    1, 57, 33, 3, 27, 41, 29, 50,
    45, 36, 60, 60, 60, 60},
    { //idle3
    60, 53, 14, 31, 23,
    15, 43, 60, 60, 54, 5, 13,
    7, 56, 24, 2, 26, 39, 29, 50,
    45, 36, 60, 60, 60, 60},
    { //idle4
    6, 52, 19, 38, 32,
    20, 47, 51, 60, 9, 0, 17,
    8, 57, 33, 3, 27, 41, 29, 50,
    45, 36, 60, 60, 60, 60},
    { //idle5
    60, 52, 19, 37, 40,
    21, 47, 51, 60, 9, 0, 17,
    8, 57, 33, 3, 27, 41, 29, 50,
    45, 36, 60, 60, 60, 60},
    { //prep
    6, 52, 19, 38, 32,
    20, 44, 51, 60, 10, 48, 16,
    8, 25, 4, 18, 27, 42, 46, 50,
    60, 60, 60, 60, 60, 60},
    { //tap1
    6, 52, 19, 38, 32,
    20, 44, 51, 60, 10, 49, 17,
    8, 25, 4, 18, 27, 41, 28, 11,
    60, 60, 60, 60, 58, 59},
    { //tap2
    6, 52, 19, 38, 32,
    20, 47, 51, 60, 10, 48, 16,
    8, 60, 55, 3, 27, 42, 46, 50,
    45, 34, 12, 60, 60, 60}
};

// Tiles per frame are laid out in 4 rows starting at these positions.
static const uint8_t bongo_row_x[]   = {51, 49, 48, 57};
static const uint8_t bongo_row_len[] = {5, 7, 8, 6};

enum bongo_frame { BONGO_IDLE_LAST = 4, BONGO_PREP = 5, BONGO_TAP1 = 6, BONGO_TAP2 = 7 };
enum bongo_state { BONGO_SLEEPING, BONGO_IDLE, BONGO_PREPPING, BONGO_TAPPING };

static void draw_bongo_tile(uint8_t x, uint8_t y, uint8_t tile) {
    for (uint8_t i = 0; i < 6; i++) {
        uint8_t column = pgm_read_byte(&bongofont[tile * 6 + i]);
        for (uint8_t j = 0; j < 8; j++) {
            oled_write_pixel(x + i, y + j, column & 1);
            column >>= 1;
        }
    }
}

static void draw_bongo_frame(uint8_t frame) {
    static uint8_t last_frame = 0xFF;
    if (frame == last_frame) return;
    last_frame = frame;
    uint8_t tile = 0;
    for (uint8_t row = 0; row < 4; row++) {
        for (uint8_t i = 0; i < bongo_row_len[row]; i++) {
            draw_bongo_tile(bongo_row_x[row] + i * 6, row * 8, pgm_read_byte(&bongo_line_data[frame][tile++]));
        }
    }
}

// The table edge doesn't change between frames: two diagonal lines.
static void draw_bongo_table(void) {
    for (uint8_t i = 17; i < 57; i++) oled_write_pixel(i, 31 - (i - 17) / 5, true);
    for (uint8_t i = 91; i < 128; i++) oled_write_pixel(i, 15 - (i - 91) / 4, true);
}

static void render_bongocat(void) {
    static bool         started    = false;
    static uint8_t      state      = BONGO_IDLE;
    static uint8_t      idle_frame = 0;
    static uint8_t      tap_frame  = BONGO_TAP1;
    static uint16_t     anim_timer = 0;
    static uint32_t     last_typed = 0;
    static matrix_row_t previous[MATRIX_ROWS];

    if (!started) {
        oled_clear();
        draw_bongo_table();
        started = true;
    }

    bool key_down = false, new_press = false;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t current = matrix_get_row(row);
        if (current) key_down = true;
        if (current & ~previous[row]) new_press = true;
        previous[row] = current;
    }

    if (key_down) {
        // Alternate paws on every new key press.
        if (new_press) tap_frame = (tap_frame == BONGO_TAP1) ? BONGO_TAP2 : BONGO_TAP1;
        state = BONGO_TAPPING;
    } else if (state == BONGO_TAPPING) {
        state      = BONGO_PREPPING;
        last_typed = timer_read32();
    } else if (state == BONGO_PREPPING && timer_elapsed32(last_typed) >= BONGO_PREP_MS) {
        state      = BONGO_IDLE;
        idle_frame = 0;
    } else if (state == BONGO_IDLE && timer_elapsed32(last_typed) >= BONGO_SLEEP_MS) {
        state = BONGO_SLEEPING;
    }

    switch (state) {
        case BONGO_TAPPING: draw_bongo_frame(tap_frame); break;
        case BONGO_PREPPING: draw_bongo_frame(BONGO_PREP); break;
        case BONGO_SLEEPING: draw_bongo_frame(BONGO_IDLE_LAST); break;
        default:
            draw_bongo_frame(BONGO_IDLE_LAST - idle_frame);
            if (timer_elapsed(anim_timer) > BONGO_FRAME_MS) {
                idle_frame = (idle_frame + 1) % 5;
                anim_timer = timer_read();
            }
            break;
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
        render_bongocat();
    }
    return false;
}
#endif // OLED_ENABLE
