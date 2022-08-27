#ifndef __USB_HID_KEY_CODE_H__
#define __USB_HID_KEY_CODE_H__

#include "../base/c_types_def.h"

/* 这个枚举的代码是从 SDL 的 SDL_scancode.h 文件中扣出来的 */

typedef enum _usb_hid_key_code_t {
  USB_HID_KEY_CODE_UNKNOWN = 0,

  /**
   *  \name Usage page 0x07
   *
   *  These values are from usage page 0x07 (USB keyboard page).
   */
  /* @{ */

  USB_HID_KEY_CODE_A = 4,                                                                                                             //大写字母A
  USB_HID_KEY_CODE_B = 5,                                                                                                             //大写字母B
  USB_HID_KEY_CODE_C = 6,                                                                                                             //大写字母C
  USB_HID_KEY_CODE_D = 7,                                                                                                             //大写字母D
  USB_HID_KEY_CODE_E = 8,                                                                                                             //大写字母E
  USB_HID_KEY_CODE_F = 9,                                                                                                             //大写字母F
  USB_HID_KEY_CODE_G = 10,                                                                                                            //大写字母G
  USB_HID_KEY_CODE_H = 11,                                                                                                            //大写字母H
  USB_HID_KEY_CODE_I = 12,                                                                                                            //大写字母I
  USB_HID_KEY_CODE_J = 13,                                                                                                            //大写字母J
  USB_HID_KEY_CODE_K = 14,                                                                                                            //大写字母K
  USB_HID_KEY_CODE_L = 15,                                                                                                            //大写字母L
  USB_HID_KEY_CODE_M = 16,                                                                                                            //大写字母M
  USB_HID_KEY_CODE_N = 17,                                                                                                            //大写字母N
  USB_HID_KEY_CODE_O = 18,                                                                                                            //大写字母O
  USB_HID_KEY_CODE_P = 19,                                                                                                            //大写字母P
  USB_HID_KEY_CODE_Q = 20,                                                                                                            //大写字母Q
  USB_HID_KEY_CODE_R = 21,                                                                                                            //大写字母R
  USB_HID_KEY_CODE_S = 22,                                                                                                            //大写字母S
  USB_HID_KEY_CODE_T = 23,                                                                                                            //大写字母T
  USB_HID_KEY_CODE_U = 24,                                                                                                            //大写字母U
  USB_HID_KEY_CODE_V = 25,                                                                                                            //大写字母V
  USB_HID_KEY_CODE_W = 26,                                                                                                            //大写字母W
  USB_HID_KEY_CODE_X = 27,                                                                                                            //大写字母X
  USB_HID_KEY_CODE_Y = 28,                                                                                                            //大写字母Y
  USB_HID_KEY_CODE_Z = 29,                                                                                                            //大写字母Z

  USB_HID_KEY_CODE_a = USB_HID_KEY_CODE_A,                                                                                            //小写字母a
  USB_HID_KEY_CODE_b = USB_HID_KEY_CODE_B,                                                                                            //小写字母b
  USB_HID_KEY_CODE_c = USB_HID_KEY_CODE_C,                                                                                            //小写字母c
  USB_HID_KEY_CODE_d = USB_HID_KEY_CODE_D,                                                                                            //小写字母d
  USB_HID_KEY_CODE_e = USB_HID_KEY_CODE_E,                                                                                            //小写字母e
  USB_HID_KEY_CODE_f = USB_HID_KEY_CODE_F,                                                                                            //小写字母f
  USB_HID_KEY_CODE_g = USB_HID_KEY_CODE_G,                                                                                            //小写字母g
  USB_HID_KEY_CODE_h = USB_HID_KEY_CODE_H,                                                                                            //小写字母h
  USB_HID_KEY_CODE_i = USB_HID_KEY_CODE_I,                                                                                            //小写字母i
  USB_HID_KEY_CODE_j = USB_HID_KEY_CODE_J,                                                                                            //小写字母j
  USB_HID_KEY_CODE_k = USB_HID_KEY_CODE_K,                                                                                            //小写字母k
  USB_HID_KEY_CODE_l = USB_HID_KEY_CODE_L,                                                                                            //小写字母l
  USB_HID_KEY_CODE_m = USB_HID_KEY_CODE_M,                                                                                            //小写字母m
  USB_HID_KEY_CODE_n = USB_HID_KEY_CODE_N,                                                                                            //小写字母n
  USB_HID_KEY_CODE_o = USB_HID_KEY_CODE_O,                                                                                            //小写字母o
  USB_HID_KEY_CODE_p = USB_HID_KEY_CODE_P,                                                                                            //小写字母p
  USB_HID_KEY_CODE_q = USB_HID_KEY_CODE_Q,                                                                                            //小写字母q
  USB_HID_KEY_CODE_r = USB_HID_KEY_CODE_R,                                                                                            //小写字母r
  USB_HID_KEY_CODE_s = USB_HID_KEY_CODE_S,                                                                                            //小写字母s
  USB_HID_KEY_CODE_t = USB_HID_KEY_CODE_T,                                                                                            //小写字母t
  USB_HID_KEY_CODE_u = USB_HID_KEY_CODE_U,                                                                                            //小写字母u
  USB_HID_KEY_CODE_v = USB_HID_KEY_CODE_V,                                                                                            //小写字母v
  USB_HID_KEY_CODE_w = USB_HID_KEY_CODE_W,                                                                                            //小写字母w
  USB_HID_KEY_CODE_x = USB_HID_KEY_CODE_X,                                                                                            //小写字母x
  USB_HID_KEY_CODE_y = USB_HID_KEY_CODE_Y,                                                                                            //小写字母y
  USB_HID_KEY_CODE_z = USB_HID_KEY_CODE_Z,                                                                                            //小写字母z

  USB_HID_KEY_CODE_1 = 30,                                                                                                            //数字0
  USB_HID_KEY_CODE_2 = 31,                                                                                                            //数字1
  USB_HID_KEY_CODE_3 = 32,                                                                                                            //数字2
  USB_HID_KEY_CODE_4 = 33,                                                                                                            //数字3
  USB_HID_KEY_CODE_5 = 34,                                                                                                            //数字4
  USB_HID_KEY_CODE_6 = 35,                                                                                                            //数字5
  USB_HID_KEY_CODE_7 = 36,                                                                                                            //数字6
  USB_HID_KEY_CODE_8 = 37,                                                                                                            //数字7
  USB_HID_KEY_CODE_9 = 38,                                                                                                            //数字8
  USB_HID_KEY_CODE_0 = 39,                                                                                                            //数字9

  USB_HID_KEY_CODE_EXCLAIM = USB_HID_KEY_CODE_1,                                                                                      // !
  USB_HID_KEY_CODE_AT = USB_HID_KEY_CODE_2,                                                                                           // @
  USB_HID_KEY_CODE_HASH = USB_HID_KEY_CODE_3,                                                                                         // #
  USB_HID_KEY_CODE_DOLLAR = USB_HID_KEY_CODE_4,                                                                                       // $
  USB_HID_KEY_CODE_PERCENT = USB_HID_KEY_CODE_5,                                                                                      // %
  USB_HID_KEY_CODE_CARET = USB_HID_KEY_CODE_6,                                                                                        // ^
  USB_HID_KEY_CODE_AMPERSAND = USB_HID_KEY_CODE_7,                                                                                    // &
  USB_HID_KEY_CODE_ASTERISK = USB_HID_KEY_CODE_8,                                                                                     // *
  USB_HID_KEY_CODE_LEFTPAREN = USB_HID_KEY_CODE_9,                                                                                    //开括号 (
  USB_HID_KEY_CODE_RIGHTPAREN = USB_HID_KEY_CODE_0,                                                                                   //闭括号 )

  USB_HID_KEY_CODE_RETURN = 40,                                                                                                       //回车键
  USB_HID_KEY_CODE_ESCAPE = 41,                                                                                                       //ESC 键
  USB_HID_KEY_CODE_BACKSPACE = 42,                                                                                                    //退格键
  USB_HID_KEY_CODE_TAB = 43,                                                                                                          //标签符
  USB_HID_KEY_CODE_SPACE = 44,                                                                                                        //空格键

  USB_HID_KEY_CODE_MINUS = 45,                                                                                                        // -
  USB_HID_KEY_CODE_UNDERSCORE = USB_HID_KEY_CODE_MINUS,                                                                               // _ = Shift + -

  USB_HID_KEY_CODE_EQUALS = 46,                                                                                                       // =
  USB_HID_KEY_CODE_PLUS = USB_HID_KEY_CODE_EQUALS,                                                                                    // + = Shift + =

  USB_HID_KEY_CODE_LEFTBRACKET = 47,                                                                                                  // [{
  USB_HID_KEY_CODE_RIGHTBRACKET = 48,                                                                                                 // ]}
  USB_HID_KEY_CODE_BACKSLASH = 49, /**< Located at the lower left of the return                                                       // \|
                                    *   key on ISO keyboards and at the right end
                                    *   of the QWERTY row on ANSI keyboards.
                                    *   Produces REVERSE SOLIDUS (backslash) and
                                    *   VERTICAL LINE in a US layout, REVERSE
                                    *   SOLIDUS and VERTICAL LINE in a UK Mac
                                    *   layout, NUMBER SIGN and TILDE in a UK
                                    *   Windows layout, DOLLAR SIGN and POUND SIGN
                                    *   in a Swiss German layout, NUMBER SIGN and
                                    *   APOSTROPHE in a German layout, GRAVE
                                    *   ACCENT and POUND SIGN in a French Mac
                                    *   layout, and ASTERISK and MICRO SIGN in a
                                    *   French Windows layout.
                                    */
  USB_HID_KEY_CODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code                                                      // `~
                                    *   instead of 49 for the same key, but all
                                    *   OSes I've seen treat the two codes
                                    *   identically. So, as an implementor, unless
                                    *   your keyboard generates both of those
                                    *   codes and your OS treats them differently,
                                    *   you should generate USB_HID_KEY_CODE_BACKSLASH
                                    *   instead of this code. As a user, you
                                    *   should not rely on this code because SDL
                                    *   will never generate it with most (all?)
                                    *   keyboards.
                                    */
  USB_HID_KEY_CODE_SEMICOLON = 51,                                                                                                    // ;
  USB_HID_KEY_CODE_COLON = USB_HID_KEY_CODE_SEMICOLON,                                                                                // : = Shift + ;

  USB_HID_KEY_CODE_APOSTROPHE = 52,                                                                                                   // '
  USB_HID_KEY_CODE_APOSTROPHES = USB_HID_KEY_CODE_APOSTROPHE,                                                                         // "
  USB_HID_KEY_CODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                                *   and ISO keyboards). Produces GRAVE ACCENT and
                                *   TILDE in a US Windows layout and in US and UK
                                *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                                *   and NOT SIGN in a UK Windows layout, SECTION
                                *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                                *   layouts on ISO keyboards, SECTION SIGN and
                                *   DEGREE SIGN in a Swiss German layout (Mac:
                                *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                                *   DEGREE SIGN in a German layout (Mac: only on
                                *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                                *   French Windows layout, COMMERCIAL AT and
                                *   NUMBER SIGN in a French Mac layout on ISO
                                *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                                *   SIGN in a Swiss German, German, or French Mac
                                *   layout on ANSI keyboards.
                                */
  USB_HID_KEY_CODE_COMMA = 54,                                                                                                        // ,
  USB_HID_KEY_CODE_LESS = USB_HID_KEY_CODE_COMMA,                                                                                     // < = Shift + ,

  USB_HID_KEY_CODE_PERIOD = 55,                                                                                                       // .
  USB_HID_KEY_CODE_GREATER = USB_HID_KEY_CODE_PERIOD,                                                                                 // > = Shift + .

  USB_HID_KEY_CODE_SLASH = 56,                                                                                                        // /
  USB_HID_KEY_CODE_QUESTION = USB_HID_KEY_CODE_SLASH,                                                                                 // ? = Shift + /

  USB_HID_KEY_CODE_CAPSLOCK = 57,                                                                                                     // 大小写锁定键

  USB_HID_KEY_CODE_F1 = 58,
  USB_HID_KEY_CODE_F2 = 59,
  USB_HID_KEY_CODE_F3 = 60,
  USB_HID_KEY_CODE_F4 = 61,
  USB_HID_KEY_CODE_F5 = 62,
  USB_HID_KEY_CODE_F6 = 63,
  USB_HID_KEY_CODE_F7 = 64,
  USB_HID_KEY_CODE_F8 = 65,
  USB_HID_KEY_CODE_F9 = 66,
  USB_HID_KEY_CODE_F10 = 67,
  USB_HID_KEY_CODE_F11 = 68,
  USB_HID_KEY_CODE_F12 = 69,

  USB_HID_KEY_CODE_PRINTSCREEN = 70,                                                                                                  // 截屏按键
  USB_HID_KEY_CODE_SCROLLLOCK = 71,                                                                                                   // 滚动锁
  USB_HID_KEY_CODE_PAUSE = 72,                                                                                                        // 中断暂停键
  USB_HID_KEY_CODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but                                                    // 插入按键
                                  does send code 73, not 117) */
  USB_HID_KEY_CODE_HOME = 74,                                                                                                         // Home 按键
  USB_HID_KEY_CODE_PAGEUP = 75,                                                                                                       // 上翻页
  USB_HID_KEY_CODE_DELETE = 76,                                                                                                       // 删除按键
  USB_HID_KEY_CODE_END = 77,                                                                                                          // End 按键
  USB_HID_KEY_CODE_PAGEDOWN = 78,                                                                                                     // 下翻页
  USB_HID_KEY_CODE_RIGHT = 79,                                                                                                        // 右箭头按键
  USB_HID_KEY_CODE_LEFT = 80,                                                                                                         // 左箭头按键
  USB_HID_KEY_CODE_DOWN = 81,                                                                                                         // 下箭头按键
  USB_HID_KEY_CODE_UP = 82,                                                                                                           // 上箭头按键

  USB_HID_KEY_CODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards                                                     //数字键盘锁
                                       */
  USB_HID_KEY_CODE_KP_DIVIDE = 84,                                                                                                    //数字键盘—— /
  USB_HID_KEY_CODE_KP_MULTIPLY = 85,                                                                                                  //数字键盘—— *
  USB_HID_KEY_CODE_KP_MINUS = 86,                                                                                                     //数字键盘—— -
  USB_HID_KEY_CODE_KP_PLUS = 87,                                                                                                      //数字键盘—— +
  USB_HID_KEY_CODE_KP_ENTER = 88,                                                                                                     //数字键盘——回车
  USB_HID_KEY_CODE_KP_1 = 89,                                                                                                         //数字键盘——数字0
  USB_HID_KEY_CODE_KP_2 = 90,                                                                                                         //数字键盘——数字1
  USB_HID_KEY_CODE_KP_3 = 91,                                                                                                         //数字键盘——数字2
  USB_HID_KEY_CODE_KP_4 = 92,                                                                                                         //数字键盘——数字3
  USB_HID_KEY_CODE_KP_5 = 93,                                                                                                         //数字键盘——数字4
  USB_HID_KEY_CODE_KP_6 = 94,                                                                                                         //数字键盘——数字5
  USB_HID_KEY_CODE_KP_7 = 95,                                                                                                         //数字键盘——数字6
  USB_HID_KEY_CODE_KP_8 = 96,                                                                                                         //数字键盘——数字7
  USB_HID_KEY_CODE_KP_9 = 97,                                                                                                         //数字键盘——数字8
  USB_HID_KEY_CODE_KP_0 = 98,                                                                                                         //数字键盘——数字9
  USB_HID_KEY_CODE_KP_PERIOD = 99,                                                                                                    //数字键盘—— .

  USB_HID_KEY_CODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO                                                     // (\)
                                          *   keyboards have over ANSI ones,
                                          *   located between left shift and Y.
                                          *   Produces GRAVE ACCENT and TILDE in a
                                          *   US or UK Mac layout, REVERSE SOLIDUS
                                          *   (backslash) and VERTICAL LINE in a
                                          *   US or UK Windows layout, and
                                          *   LESS-THAN SIGN and GREATER-THAN SIGN
                                          *   in a Swiss German, German, or French
                                          *   layout. */
  USB_HID_KEY_CODE_SPLIT = USB_HID_KEY_CODE_NONUSBACKSLASH,                                                                           // (|)


  USB_HID_KEY_CODE_APPLICATION = 101,    /**< windows contextual menu, compose */                                                     // window=meun
  USB_HID_KEY_CODE_POWER = 102,          /**< The USB document says this is a status flag,                                            // mac=power
                                          *   not a physical key - but some Mac keyboards
                                          *   do have a power key. */


  USB_HID_KEY_CODE_KP_EQUALS = 103,                                                                                                   //数字键盘—— = (mac)
  
  USB_HID_KEY_CODE_F13 = 104,
  USB_HID_KEY_CODE_F14 = 105,
  USB_HID_KEY_CODE_F15 = 106,
  USB_HID_KEY_CODE_F16 = 107,
  USB_HID_KEY_CODE_F17 = 108,
  USB_HID_KEY_CODE_F18 = 109,
  USB_HID_KEY_CODE_F19 = 110,
  USB_HID_KEY_CODE_F20 = 111,
  USB_HID_KEY_CODE_F21 = 112,
  USB_HID_KEY_CODE_F22 = 113,
  USB_HID_KEY_CODE_F23 = 114,
  USB_HID_KEY_CODE_F24 = 115,

  USB_HID_KEY_CODE_EXECUTE = 116,
  USB_HID_KEY_CODE_HELP = 117,
  USB_HID_KEY_CODE_MENU = 118,
  USB_HID_KEY_CODE_SELECT = 119,
  USB_HID_KEY_CODE_STOP = 120,
  USB_HID_KEY_CODE_AGAIN = 121, /**< redo */
  USB_HID_KEY_CODE_UNDO = 122,
  USB_HID_KEY_CODE_CUT = 123,
  USB_HID_KEY_CODE_COPY = 124,
  USB_HID_KEY_CODE_PASTE = 125,
  USB_HID_KEY_CODE_FIND = 126,
  USB_HID_KEY_CODE_MUTE = 127,
  USB_HID_KEY_CODE_VOLUMEUP = 128,
  USB_HID_KEY_CODE_VOLUMEDOWN = 129,
  /* not sure whether there's a reason to enable these */
  /*     USB_HID_KEY_CODE_LOCKINGCAPSLOCK = 130,  */
  /*     USB_HID_KEY_CODE_LOCKINGNUMLOCK = 131, */
  /*     USB_HID_KEY_CODE_LOCKINGSCROLLLOCK = 132, */
  USB_HID_KEY_CODE_KP_COMMA = 133,
  USB_HID_KEY_CODE_KP_EQUALSAS400 = 134,

  USB_HID_KEY_CODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                          footnotes in USB doc */
  USB_HID_KEY_CODE_INTERNATIONAL2 = 136,
  USB_HID_KEY_CODE_INTERNATIONAL3 = 137, /**< Yen */
  USB_HID_KEY_CODE_INTERNATIONAL4 = 138,
  USB_HID_KEY_CODE_INTERNATIONAL5 = 139,
  USB_HID_KEY_CODE_INTERNATIONAL6 = 140,
  USB_HID_KEY_CODE_INTERNATIONAL7 = 141,
  USB_HID_KEY_CODE_INTERNATIONAL8 = 142,
  USB_HID_KEY_CODE_INTERNATIONAL9 = 143,
  USB_HID_KEY_CODE_LANG1 = 144, /**< Hangul/English toggle */
  USB_HID_KEY_CODE_LANG2 = 145, /**< Hanja conversion */
  USB_HID_KEY_CODE_LANG3 = 146, /**< Katakana */
  USB_HID_KEY_CODE_LANG4 = 147, /**< Hiragana */
  USB_HID_KEY_CODE_LANG5 = 148, /**< Zenkaku/Hankaku */
  USB_HID_KEY_CODE_LANG6 = 149, /**< reserved */
  USB_HID_KEY_CODE_LANG7 = 150, /**< reserved */
  USB_HID_KEY_CODE_LANG8 = 151, /**< reserved */
  USB_HID_KEY_CODE_LANG9 = 152, /**< reserved */

  USB_HID_KEY_CODE_ALTERASE = 153, /**< Erase-Eaze */
  USB_HID_KEY_CODE_SYSREQ = 154,
  USB_HID_KEY_CODE_CANCEL = 155,
  USB_HID_KEY_CODE_CLEAR = 156,
  USB_HID_KEY_CODE_PRIOR = 157,
  USB_HID_KEY_CODE_RETURN2 = 158,
  USB_HID_KEY_CODE_SEPARATOR = 159,
  USB_HID_KEY_CODE_OUT = 160,
  USB_HID_KEY_CODE_OPER = 161,
  USB_HID_KEY_CODE_CLEARAGAIN = 162,
  USB_HID_KEY_CODE_CRSEL = 163,
  USB_HID_KEY_CODE_EXSEL = 164,

  USB_HID_KEY_CODE_KP_00 = 176,
  USB_HID_KEY_CODE_KP_000 = 177,
  USB_HID_KEY_CODE_THOUSANDSSEPARATOR = 178,
  USB_HID_KEY_CODE_DECIMALSEPARATOR = 179,
  USB_HID_KEY_CODE_CURRENCYUNIT = 180,
  USB_HID_KEY_CODE_CURRENCYSUBUNIT = 181,
  USB_HID_KEY_CODE_KP_LEFTPAREN = 182,
  USB_HID_KEY_CODE_KP_RIGHTPAREN = 183,
  USB_HID_KEY_CODE_KP_LEFTBRACE = 184,
  USB_HID_KEY_CODE_KP_RIGHTBRACE = 185,
  USB_HID_KEY_CODE_KP_TAB = 186,
  USB_HID_KEY_CODE_KP_BACKSPACE = 187,
  USB_HID_KEY_CODE_KP_A = 188,
  USB_HID_KEY_CODE_KP_B = 189,
  USB_HID_KEY_CODE_KP_C = 190,
  USB_HID_KEY_CODE_KP_D = 191,
  USB_HID_KEY_CODE_KP_E = 192,
  USB_HID_KEY_CODE_KP_F = 193,
  USB_HID_KEY_CODE_KP_XOR = 194,
  USB_HID_KEY_CODE_KP_POWER = 195,
  USB_HID_KEY_CODE_KP_PERCENT = 196,
  USB_HID_KEY_CODE_KP_LESS = 197,
  USB_HID_KEY_CODE_KP_GREATER = 198,
  USB_HID_KEY_CODE_KP_AMPERSAND = 199,
  USB_HID_KEY_CODE_KP_DBLAMPERSAND = 200,
  USB_HID_KEY_CODE_KP_VERTICALBAR = 201,
  USB_HID_KEY_CODE_KP_DBLVERTICALBAR = 202,
  USB_HID_KEY_CODE_KP_COLON = 203,
  USB_HID_KEY_CODE_KP_HASH = 204,
  USB_HID_KEY_CODE_KP_SPACE = 205,
  USB_HID_KEY_CODE_KP_AT = 206,
  USB_HID_KEY_CODE_KP_EXCLAM = 207,
  USB_HID_KEY_CODE_KP_MEMSTORE = 208,
  USB_HID_KEY_CODE_KP_MEMRECALL = 209,
  USB_HID_KEY_CODE_KP_MEMCLEAR = 210,
  USB_HID_KEY_CODE_KP_MEMADD = 211,
  USB_HID_KEY_CODE_KP_MEMSUBTRACT = 212,
  USB_HID_KEY_CODE_KP_MEMMULTIPLY = 213,
  USB_HID_KEY_CODE_KP_MEMDIVIDE = 214,
  USB_HID_KEY_CODE_KP_PLUSMINUS = 215,
  USB_HID_KEY_CODE_KP_CLEAR = 216,
  USB_HID_KEY_CODE_KP_CLEARENTRY = 217,
  USB_HID_KEY_CODE_KP_BINARY = 218,
  USB_HID_KEY_CODE_KP_OCTAL = 219,
  USB_HID_KEY_CODE_KP_DECIMAL = 220,
  USB_HID_KEY_CODE_KP_HEXADECIMAL = 221,

  USB_HID_KEY_CODE_LCTRL = 224,                                                                                                       // 左边的 ctrl 按键
  USB_HID_KEY_CODE_LSHIFT = 225,                                                                                                      // 左边的 shift 按键
  USB_HID_KEY_CODE_LALT = 226, /**< alt, option */                                                                                    // 左边的 ALT 按键
  USB_HID_KEY_CODE_LGUI = 227, /**< windows, command (apple), meta */                                                                 // 左边的 Win 按键或者 command 按键
  USB_HID_KEY_CODE_RCTRL = 228,                                                                                                       // 右边的 ctrl 按键
  USB_HID_KEY_CODE_RSHIFT = 229,                                                                                                      // 右边的 shift 按键
  USB_HID_KEY_CODE_RALT = 230, /**< alt gr, option */                                                                                 // 右边的 ALT 按键
  USB_HID_KEY_CODE_RGUI = 231, /**< windows, command (apple), meta */                                                                 // 右边的 Win 按键或者 command 按键

  USB_HID_KEY_CODE_MODE = 257, /**< I'm not sure if this is really not covered
                                *   by any of the above, but since there's a
                                *   special KMOD_MODE for it I'm adding it here
                                */

  /* @} */ /* Usage page 0x07 */

  /**
   *  \name Usage page 0x0C
   *
   *  These values are mapped from usage page 0x0C (USB consumer page).
   */
  /* @{ */

  USB_HID_KEY_CODE_AUDIONEXT = 258,                                                                                                   // 下一首
  USB_HID_KEY_CODE_AUDIOPREV = 259,                                                                                                   // 上一首
  USB_HID_KEY_CODE_AUDIOSTOP = 260,                                                                                                   // 停止
  USB_HID_KEY_CODE_AUDIOPLAY = 261,                                                                                                   // 播放
  USB_HID_KEY_CODE_AUDIOMUTE = 262,                                                                                                   // 暂停
  USB_HID_KEY_CODE_MEDIASELECT = 263,                                                                                                 // 媒体选择
  USB_HID_KEY_CODE_WWW = 264,                                                                                                         // 打开浏览器
  USB_HID_KEY_CODE_MAIL = 265,                                                                                                        // 打开邮件
  USB_HID_KEY_CODE_CALCULATOR = 266,                                                                                                  // 计算器
  USB_HID_KEY_CODE_COMPUTER = 267,                                                                                                    // 我的电脑
  USB_HID_KEY_CODE_AC_SEARCH = 268,                                                                                                   // 搜索
  USB_HID_KEY_CODE_AC_HOME = 269,                                                                                                     // 主页
  USB_HID_KEY_CODE_AC_BACK = 270,                                                                                                     // 后退
  USB_HID_KEY_CODE_AC_FORWARD = 271,                                                                                                  // 前进
  USB_HID_KEY_CODE_AC_STOP = 272,                                                                                                     // 停止行动
  USB_HID_KEY_CODE_AC_REFRESH = 273,                                                                                                  // 刷新界面
  USB_HID_KEY_CODE_AC_BOOKMARKS = 274,                                                                                                // 书签

  /* @} */ /* Usage page 0x0C */

  /**
   *  \name Walther keys
   *
   *  These are values that Christian Walther added (for mac keyboard?).
   */
  /* @{ */

  USB_HID_KEY_CODE_BRIGHTNESSDOWN = 275,                                                                                              // 降低屏幕亮度
  USB_HID_KEY_CODE_BRIGHTNESSUP = 276,                                                                                                // 提高屏幕亮度
  USB_HID_KEY_CODE_DISPLAYSWITCH = 277, /**< display mirroring/dual display                                                           // 切换屏幕方式
                                          switch, video mode switch */
  USB_HID_KEY_CODE_KBDILLUMTOGGLE = 278,
  USB_HID_KEY_CODE_KBDILLUMDOWN = 279,
  USB_HID_KEY_CODE_KBDILLUMUP = 280,
  USB_HID_KEY_CODE_EJECT = 281,
  USB_HID_KEY_CODE_SLEEP = 282,

  USB_HID_KEY_CODE_APP1 = 283,
  USB_HID_KEY_CODE_APP2 = 284,

  /* @} */ /* Walther keys */

  /**
   *  \name Usage page 0x0C (additional media keys)
   *
   *  These values are mapped from usage page 0x0C (USB consumer page).
   */
  /* @{ */

  USB_HID_KEY_CODE_AUDIOREWIND = 285,
  USB_HID_KEY_CODE_AUDIOFASTFORWARD = 286,

  /* @} */ /* Usage page 0x0C (additional media keys) */

  /* Add any other keys here. */

  USB_HID_KEY_CODE_FN = 1 << 9,                                                                                                       // Fn

  USB_HID_KEY_CODE_COUNT,
} usb_hid_key_code_t;

typedef struct _usb_hid_key_code_info_t {
  const char* usb_hid_key;
  uint64_t usb_hid_key_code;
} usb_hid_key_code_info_t;

#define USB_HID_KEY_CODE_IS_SCANCODE(code)  (((code) >> 32) != 0)
#define USB_HID_KEY_CODE_TO_SCANCODE(x, y)  (uint64_t)(((uint64_t)(x) << 32) | (uint64_t)(y))
#define USB_HID_KEY_CODE_SCANCODE_GET_LEFT_KEY_CODE(x)  (usb_hid_key_code_t)((x) >> 32)
#define USB_HID_KEY_CODE_SCANCODE_GET_RIGHT_KEY_CODE(x)  (usb_hid_key_code_t)((x) & 0xFFFFFFFF)

#define USB_HID_KEY_CODE_GUI  USB_HID_KEY_CODE_TO_SCANCODE(USB_HID_KEY_CODE_LGUI, USB_HID_KEY_CODE_RGUI)
#define USB_HID_KEY_CODE_ALT  USB_HID_KEY_CODE_TO_SCANCODE(USB_HID_KEY_CODE_LALT, USB_HID_KEY_CODE_RALT)
#define USB_HID_KEY_CODE_CTRL  USB_HID_KEY_CODE_TO_SCANCODE(USB_HID_KEY_CODE_LCTRL, USB_HID_KEY_CODE_RCTRL)
#define USB_HID_KEY_CODE_SHIFT  USB_HID_KEY_CODE_TO_SCANCODE(USB_HID_KEY_CODE_LSHIFT, USB_HID_KEY_CODE_RSHIFT)

#define USB_HID_NUM_LOCK_STATE_UP      1 << 0
#define USB_HID_CAPS_LOCK_STATE_UP      1 << 1
#define USB_HID_SCROLL_LOCK_STATE_UP      1 << 2

#include "./keyboard_key_code_map.inc"

#endif
