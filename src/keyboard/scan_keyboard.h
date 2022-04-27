#ifndef __SCAN_KEYBOARD_H__
#define __SCAN_KEYBOARD_H__

#include "../base/c_types_def.h"
#include "scan_key_code.h"

BEGIN_C_DECLS

#ifndef SCAN_KEYBOARD_LINE_MAX_SIZE
#define SCAN_KEYBOARD_LINE_MAX_SIZE 6
#endif

#ifndef SCAN_KEYBOARD_LINE_KEY_MAX_SIZE
#define SCAN_KEYBOARD_LINE_KEY_MAX_SIZE 30
#endif


#ifndef SCAN_KEYBOARD_LAYOUT_MAX_NUMBER
#define SCAN_KEYBOARD_LAYOUT_MAX_NUMBER 2
#endif

typedef c_bool_t (*keyboard_get_scan_keys_t)(uint32_t number_line, uint8_t* key_list, uint32_t* key_list_size);

typedef struct _scan_keyboard_info_t {
  uint8_t line_size;
  uint8_t line_key_size;

  uint8_t fn_x;
  uint8_t fn_y;

  uint8_t caps_lock_x;
  uint8_t caps_lock_y;

  uint8_t shift_left_x;
  uint8_t shift_left_y;

  uint8_t shift_right_x;
  uint8_t shift_right_y;

  uint8_t number_lock_x;
  uint8_t number_lock_y;

#if SCAN_KEY_CODE_COUNT < 65536
  uint16_t 
#else
  uint32_t
#endif
  key_map[SCAN_KEYBOARD_LAYOUT_MAX_NUMBER][SCAN_KEYBOARD_LINE_MAX_SIZE][SCAN_KEYBOARD_LINE_KEY_MAX_SIZE];
} scan_keyboard_info_t;

typedef struct _scan_keyboard_t {
  scan_keyboard_info_t* info;

  c_bool_t is_fn;
  c_bool_t is_shift;
  c_bool_t is_caps_lock;
  c_bool_t is_number_lock;

  keyboard_get_scan_keys_t get_line_keys;
} scan_keyboard_t;

scan_keyboard_info_t* scan_keyboard_info_init(scan_keyboard_info_t* scan_keyboard_info, const char* str_keyboard_layout);

const scan_keyboard_t* scan_keyboard_init(scan_keyboard_info_t* scan_keyboard_info, keyboard_get_scan_keys_t get_line_keys);

void scan_keyboard_destroy(const scan_keyboard_t* scan_keyboard);

uint32_t scan_keyboard_get_scan_key_list(scan_keyboard_t* scan_keyboard, uint32_t* key_list, uint32_t key_list_size);

END_C_DECLS

#endif
