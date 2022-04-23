#ifndef __SCAN_KEY_CODE_H__
#define __SCAN_KEY_CODE_H__

#include "../base/c_types_def.h"

typedef enum _scan_key_code_t {
    SCAN_KEY_NONE = 0,

    /*      控制键   */
    SCAN_KEY_BACK_SPACE = 8,                                                                                            //退格键
    SCAN_KEY_TAB = 9,                                                                                                   //标签符
    SCAN_KEY_CLEAR = 12,                                                                                                //数字键盘上锁时数字 5 的键值
    SCAN_KEY_ENTER = 13,                                                                                                //回车键
    SCAN_KEY_SHIFT = 16,                                                                                                //Shift 键
    SCAN_KEY_CTRL = 17,                                                                                                 //Ctrl 键
    SCAN_KEY_ALT = 18,                                                                                                  //Alt 键
    SCAN_KEY_PAUSE_BREAK = 19,                                                                                          //中断暂停键
    SCAN_KEY_CAPE_LOCK = 20,                                                                                            //大小写锁定键

    SCAN_KEY_ESC = 27,                                                                                                  //Esc键

    SCAN_KEY_SPACEBAR = 32,                                                                                             //空格键
    SCAN_KEY_PAGE_UP = 33,                                                                                              //上翻页
    SCAN_KEY_PAGE_DOWM = 34,                                                                                            //下翻页
    SCAN_KEY_END = 35,                                                                                                  //End 键
    SCAN_KEY_HOME = 36,                                                                                                 //Home键
    SCAN_KEY_LEFT_ARROW = 37,                                                                                           //左箭头按键
    SCAN_KEY_UP_ARROW = 38,                                                                                             //上箭头按键
    SCAN_KEY_RIGHT_ARROW = 39,                                                                                          //右箭头按键
    SCAN_KEY_DOWN_ARROW = 40,                                                                                           //下箭头按键

    SCAN_KEY_PRINT_SCREEN = 44,                                                                                         //截屏按键
    SCAN_KEY_INSERT = 45,                                                                                               //插入按键
    SCAN_KEY_DELETE = 46,                                                                                               //删除按键

    /*      字母和数字键    */
    SCAN_KEY_0 = 48,                                                                                                    //数字0
    SCAN_KEY_1 = 49,                                                                                                    //数字1
    SCAN_KEY_2 = 50,                                                                                                    //数字2
    SCAN_KEY_3 = 51,                                                                                                    //数字3
    SCAN_KEY_4 = 52,                                                                                                    //数字4
    SCAN_KEY_5 = 53,                                                                                                    //数字5
    SCAN_KEY_6 = 54,                                                                                                    //数字6
    SCAN_KEY_7 = 55,                                                                                                    //数字7
    SCAN_KEY_8 = 56,                                                                                                    //数字8
    SCAN_KEY_9 = 57,                                                                                                    //数字9

    SCAN_KEY_EXCLAIM = SCAN_KEY_1,                                                                                      // !
    SCAN_KEY_AT = SCAN_KEY_2,                                                                                           // @
    SCAN_KEY_HASH = SCAN_KEY_3,                                                                                         // #
    SCAN_KEY_DOLLAR = SCAN_KEY_4,                                                                                       // $
    SCAN_KEY_PERCENT = SCAN_KEY_5,                                                                                      // %
    SCAN_KEY_CARET = SCAN_KEY_6,                                                                                        // ^
    SCAN_KEY_AMPERSAND = SCAN_KEY_7,                                                                                    // &
    SCAN_KEY_ASTERISK = SCAN_KEY_8,                                                                                     // *
    SCAN_KEY_LEFTPAREN = SCAN_KEY_9,                                                                                    //开括号 (
    SCAN_KEY_RIGHTPAREN = SCAN_KEY_0,                                                                                   //闭括号 )

    SCAN_KEY_A = 65,                                                                                                    //大写字母A
    SCAN_KEY_B = 66,                                                                                                    //大写字母B
    SCAN_KEY_C = 67,                                                                                                    //大写字母C
    SCAN_KEY_D = 68,                                                                                                    //大写字母D
    SCAN_KEY_E = 69,                                                                                                    //大写字母E
    SCAN_KEY_F = 70,                                                                                                    //大写字母F
    SCAN_KEY_G = 71,                                                                                                    //大写字母G
    SCAN_KEY_H = 72,                                                                                                    //大写字母H
    SCAN_KEY_I = 73,                                                                                                    //大写字母I
    SCAN_KEY_J = 74,                                                                                                    //大写字母J
    SCAN_KEY_K = 75,                                                                                                    //大写字母K
    SCAN_KEY_L = 76,                                                                                                    //大写字母L
    SCAN_KEY_M = 77,                                                                                                    //大写字母M
    SCAN_KEY_N = 78,                                                                                                    //大写字母N
    SCAN_KEY_O = 79,                                                                                                    //大写字母O
    SCAN_KEY_P = 80,                                                                                                    //大写字母P
    SCAN_KEY_Q = 81,                                                                                                    //大写字母Q
    SCAN_KEY_R = 82,                                                                                                    //大写字母R
    SCAN_KEY_S = 83,                                                                                                    //大写字母S
    SCAN_KEY_T = 84,                                                                                                    //大写字母T
    SCAN_KEY_U = 85,                                                                                                    //大写字母U
    SCAN_KEY_V = 86,                                                                                                    //大写字母V
    SCAN_KEY_W = 87,                                                                                                    //大写字母W
    SCAN_KEY_X = 88,                                                                                                    //大写字母X
    SCAN_KEY_Y = 89,                                                                                                    //大写字母Y
    SCAN_KEY_Z = 90,                                                                                                    //大写字母Z

    SCAN_KEY_a = SCAN_KEY_A,                                                                                            //小写字母a
    SCAN_KEY_b = SCAN_KEY_B,                                                                                            //小写字母b
    SCAN_KEY_c = SCAN_KEY_C,                                                                                            //小写字母c
    SCAN_KEY_d = SCAN_KEY_D,                                                                                            //小写字母d
    SCAN_KEY_e = SCAN_KEY_E,                                                                                            //小写字母e
    SCAN_KEY_f = SCAN_KEY_F,                                                                                            //小写字母f
    SCAN_KEY_g = SCAN_KEY_G,                                                                                            //小写字母g
    SCAN_KEY_h = SCAN_KEY_H,                                                                                            //小写字母h
    SCAN_KEY_i = SCAN_KEY_I,                                                                                            //小写字母i
    SCAN_KEY_j = SCAN_KEY_J,                                                                                            //小写字母j
    SCAN_KEY_k = SCAN_KEY_K,                                                                                            //小写字母k
    SCAN_KEY_l = SCAN_KEY_L,                                                                                            //小写字母l
    SCAN_KEY_m = SCAN_KEY_M,                                                                                            //小写字母m
    SCAN_KEY_n = SCAN_KEY_N,                                                                                            //小写字母n
    SCAN_KEY_o = SCAN_KEY_O,                                                                                            //小写字母o
    SCAN_KEY_p = SCAN_KEY_P,                                                                                            //小写字母p
    SCAN_KEY_q = SCAN_KEY_Q,                                                                                            //小写字母q
    SCAN_KEY_r = SCAN_KEY_R,                                                                                            //小写字母r
    SCAN_KEY_s = SCAN_KEY_S,                                                                                            //小写字母s
    SCAN_KEY_t = SCAN_KEY_T,                                                                                            //小写字母t
    SCAN_KEY_u = SCAN_KEY_U,                                                                                            //小写字母u
    SCAN_KEY_v = SCAN_KEY_V,                                                                                            //小写字母v
    SCAN_KEY_w = SCAN_KEY_W,                                                                                            //小写字母w
    SCAN_KEY_x = SCAN_KEY_X,                                                                                            //小写字母x
    SCAN_KEY_y = SCAN_KEY_Y,                                                                                            //小写字母y
    SCAN_KEY_z = SCAN_KEY_Z,                                                                                            //小写字母z

    SCAN_KEY_WIN = 91,                                                                                                  // win 键

    SCAN_KEY_MENU = 93,                                                                                                 // Menu 键

    /*      数字键盘     */
    SCAN_KEY_NUM_0 = 96,                                                                                                //数字键盘——数字0
    SCAN_KEY_NUM_1 = 97,                                                                                                //数字键盘——数字1
    SCAN_KEY_NUM_2 = 98,                                                                                                //数字键盘——数字2
    SCAN_KEY_NUM_3 = 99,                                                                                                //数字键盘——数字3
    SCAN_KEY_NUM_4 = 100,                                                                                               //数字键盘——数字4
    SCAN_KEY_NUM_5 = 101,                                                                                               //数字键盘——数字5
    SCAN_KEY_NUM_6 = 102,                                                                                               //数字键盘——数字6
    SCAN_KEY_NUM_7 = 103,                                                                                               //数字键盘——数字7
    SCAN_KEY_NUM_8 = 104,                                                                                               //数字键盘——数字8
    SCAN_KEY_NUM_9 = 105,                                                                                               //数字键盘——数字9

    /*      功能键      */
    SCAN_KEY_F1 = 112,
    SCAN_KEY_F2 = 113,
    SCAN_KEY_F3 = 114,
    SCAN_KEY_F4 = 115,
    SCAN_KEY_F5 = 116,
    SCAN_KEY_F6 = 117,
    SCAN_KEY_F7 = 118,
    SCAN_KEY_F8 = 119,
    SCAN_KEY_F9 = 120,
    SCAN_KEY_F10 = 121,
    SCAN_KEY_F11 = 122,
    SCAN_KEY_F12 = 123,
    SCAN_KEY_F13 = 124,
    SCAN_KEY_F14 = 125,
    SCAN_KEY_F15 = 126,
    SCAN_KEY_F16 = 127,
    SCAN_KEY_F17 = 128,
    SCAN_KEY_F18 = 129,
    SCAN_KEY_F19 = 130,
    SCAN_KEY_F20 = 131,
    SCAN_KEY_F21 = 132,
    SCAN_KEY_F22 = 133,
    SCAN_KEY_F23 = 134,
    SCAN_KEY_F24 = 135,
    SCAN_KEY_F25 = 136,
    SCAN_KEY_F26 = 137,
    SCAN_KEY_F27 = 138,
    SCAN_KEY_F28 = 139,
    SCAN_KEY_F29 = 140,
    SCAN_KEY_F30 = 141,
    SCAN_KEY_F41 = 142,
    SCAN_KEY_F42 = 143,

    SCAN_KEY_NUM_LOCK = 144,                                                                                             //数字键盘锁
    SCAN_KEY_SCROLL_LOCK = 145,                                                                                          //滚动锁

    SCAN_KEY_OPEN_BROWSER = 172,                                                                                         //浏览器
    SCAN_KEY_SWITCH_SOUND = 173,                                                                                         //静音/非静音
    SCAN_KEY_VOL_DOWN = 174,                                                                                             //音量减
    SCAN_KEY_VOL_UP = 175,                                                                                               //音量加
    SCAN_KEY_NEXT = 176,                                                                                                 //下一首
    SCAN_KEY_PREV = 177,                                                                                                 //上一首
    SCAN_KEY_STOP = 178,                                                                                                 //停止
    SCAN_KEY_PLAY_OR_PAUSE = 179,                                                                                        //播放/暂停
    SCAN_KEY_EMAIL = 180,                                                                                                //邮件
    SCAN_KEY_MUTE_FOR_FIREFOX = 181,                                                                                     //静音/非静音（Firefox）
    SCAN_KEY_VOL_DOWN_FOR_FIREFOX = 182,                                                                                 //音量减（Firefox）
    SCAN_KEY_VOL_UP_FOR_FIREFOX = 183,                                                                                   //音量加（Firefox）

    SCAN_KEY_SEMICOLON = 186,                                                                                            // ;
    SCAN_KEY_EQUAL = 187,                                                                                                // =
    SCAN_KEY_COMMA = 188,                                                                                                // ,
    SCAN_KEY_MINUS = 189,                                                                                                // -
    SCAN_KEY_PERIOD = 190,                                                                                               // .
    SCAN_KEY_SLASH = 191,                                                                                                // /
    SCAN_KEY_BACK_QUOTE = 192,                                                                                           // `

    SCAN_KEY_COLON = SCAN_KEY_SEMICOLON,                                                                                  // : = Shift + ;
    SCAN_KEY_PLUS = SCAN_KEY_EQUAL,                                                                                       // + = Shift + =
    SCAN_KEY_LESS = SCAN_KEY_COMMA,                                                                                       // < = Shift + ,
    SCAN_KEY_UNDER_SCORE = SCAN_KEY_MINUS,                                                                                // _ = Shift + -
    SCAN_KEY_GREATER = SCAN_KEY_PERIOD,                                                                                   // > = Shift + .
    SCAN_KEY_QUESTION = SCAN_KEY_SLASH,                                                                                   // ? = Shift + /
    SCAN_KEY_TILDE = SCAN_KEY_BACK_QUOTE,                                                                                 // ~ = Shift + `


    SCAN_KEY_LEFT_BRACKET = 219,                                                                                          // ([{)
    SCAN_KEY_A_SLASH = 220,                                                                                               // (\)
    SCAN_KEY_RIGHT_BRACKET = 221,                                                                                         // (]})

    SCAN_KEY_SPLIT = SCAN_KEY_A_SLASH,                                                                                    // (|)

    SCAN_KEY_QUOTE = 222,                                                                                                 // '
    SCAN_KEY_QUOTEDBL = SCAN_KEY_QUOTE,                                                                                   // " = Shift + '
    

    SCAN_KEY_FN = 1 << 8,                                                                                                 // Fn

    SCAN_KEY_CODE_COUNT,
} scan_key_code_t;

typedef struct _scan_key_code_info_t {
    const char* scan_key;
    scan_key_code_t scan_key_code;
} scan_key_code_info_t;

#include "./keyboard_key_code_map.inc"

#endif