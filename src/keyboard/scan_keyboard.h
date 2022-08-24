#ifndef __SCAN_KEYBOARD_H__
#define __SCAN_KEYBOARD_H__

#include "../fish_keyboard_config.h"
#include "../base/c_types_def.h"
#include "usb_hid_key_code.h"

BEGIN_C_DECLS

#ifndef SCAN_KEYBOARD_LINE_MAX_SIZE
#define SCAN_KEYBOARD_LINE_MAX_SIZE                               6
#endif

#ifndef SCAN_KEYBOARD_LINE_KEY_MAX_SIZE
#define SCAN_KEYBOARD_LINE_KEY_MAX_SIZE                           30
#endif


#ifndef SCAN_KEYBOARD_LAYOUT_MAX_NUMBER
#define SCAN_KEYBOARD_LAYOUT_MAX_NUMBER                           2
#endif

#ifndef FISH_KEYBOARD_KEY_MAX_NUMBER
#define FISH_KEYBOARD_KEY_MAX_NUMBER                              108
#endif

#ifndef FISH_KEYBOARD_SEND_KEY_MAX_NUMBER
#define FISH_KEYBOARD_SEND_KEY_MAX_NUMBER                         6
#endif

#if USB_HID_KEY_CODE_COUNT < (1 << 8)
#define scan_keyboard_key_map_type_t    uint16_t
#else
#define scan_keyboard_key_map_type_t    uint32_t
#endif

typedef struct _scan_keyboard_send_key_type_t {
  uint16_t x;
  uint16_t y;
  scan_keyboard_key_map_type_t key;
} scan_keyboard_send_key_type_t;

typedef c_bool_t (*keyboard_get_scan_keys_t)(uint32_t number_line, uint8_t* key_list, uint32_t* key_list_size);

typedef struct _scan_keyboard_info_t {
  uint8_t line_size;
  uint8_t line_key_size;

  uint8_t fn_x;
  uint8_t fn_y;

  uint8_t caps_lock_x;
  uint8_t caps_lock_y;

  uint8_t number_lock_x;
  uint8_t number_lock_y;

  uint8_t scroll_lock_x;
  uint8_t scroll_lock_y;

  uint8_t left_shift_x;
  uint8_t left_shift_y;

  uint8_t right_shift_x;
  uint8_t right_shift_y;

  uint8_t left_ctrl_x;
  uint8_t left_ctrl_y;

  uint8_t right_ctrl_x;
  uint8_t right_ctrl_y;

  uint8_t left_gui_x;
  uint8_t left_gui_y;

  uint8_t right_gui_x;
  uint8_t right_gui_y;

  uint8_t left_alt_x;
  uint8_t left_alt_y;

  uint8_t right_alt_x;
  uint8_t right_alt_y;

  scan_keyboard_key_map_type_t key_map[SCAN_KEYBOARD_LAYOUT_MAX_NUMBER][SCAN_KEYBOARD_LINE_MAX_SIZE][SCAN_KEYBOARD_LINE_KEY_MAX_SIZE];
} scan_keyboard_info_t;

typedef struct _scan_keyboard_lock_key_t {
  uint8_t down;
  uint8_t restate;
  uint8_t lock;
} scan_keyboard_lock_key_t;

typedef struct _scan_keyboard_t {
  scan_keyboard_info_t* info;

  c_bool_t is_left_shift;
  c_bool_t is_right_shift;

  c_bool_t is_left_ctrl;
  c_bool_t is_right_ctrl;

  c_bool_t is_left_gui;     // window = win按键，mac = commond 按键
  c_bool_t is_right_gui;    // window = win按键，mac = commond 按键

  c_bool_t is_left_alt;
  c_bool_t is_right_alt;

  c_bool_t is_fn;

  scan_keyboard_lock_key_t is_caps_lock;
  scan_keyboard_lock_key_t is_number_lock;
  scan_keyboard_lock_key_t is_scroll_lock;

  uint32_t last_send_key_list_size;
  scan_keyboard_send_key_type_t last_send_key_list[FISH_KEYBOARD_SEND_KEY_MAX_NUMBER];

  keyboard_get_scan_keys_t get_line_keys;
} scan_keyboard_t;

scan_keyboard_info_t* scan_keyboard_info_init(scan_keyboard_info_t* scan_keyboard_info, const char* str_keyboard_layout);

const scan_keyboard_t* scan_keyboard_init(scan_keyboard_info_t* scan_keyboard_info, keyboard_get_scan_keys_t get_line_keys);

scan_keyboard_t* scan_keyboard_create(scan_keyboard_info_t* scan_keyboard_info, keyboard_get_scan_keys_t get_line_keys);

void scan_keyboard_destroy(const scan_keyboard_t* scan_keyboard);

uint32_t scan_keyboard_get_scan_key_list(scan_keyboard_t* scan_keyboard, scan_keyboard_send_key_type_t* key_list, uint32_t key_list_size);

uint32_t scan_keyboard_get_usb_keyboard_code(scan_keyboard_t* scan_keyboard, uint8_t keyboard[8]);

c_bool_t scan_keyboard_get_num_lock_statue(scan_keyboard_t* scan_keyboard);

c_bool_t scan_keyboard_get_caps_lock_statue(scan_keyboard_t* scan_keyboard);

c_bool_t scan_keyboard_get_scroll_lock_statue(scan_keyboard_t* scan_keyboard);

END_C_DECLS

#endif
