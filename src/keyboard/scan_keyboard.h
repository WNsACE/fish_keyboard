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

typedef void (*keyboard_switch_scan_line_t)(uint32_t number_line);
typedef void (*keyboard_get_line_keys_t)(uint32_t* key_list, uint32_t* key_list_size);

typedef struct _scan_keyboard_line_info_t {
  uint32_t key_map_start;
  uint32_t key_length;
} scan_keyboard_line_info_t;


typedef struct _scan_keyboard_info_t {
  uint32_t line_size;
  uint32_t line_key_size;

  uint32_t key_map[SCAN_KEYBOARD_LAYOUT_MAX_NUMBER][SCAN_KEYBOARD_LINE_MAX_SIZE][SCAN_KEYBOARD_LINE_KEY_MAX_SIZE];
} scan_keyboard_info_t;

typedef struct _scan_keyboard_t {
  scan_keyboard_info_t info;

  keyboard_get_line_keys_t get_line_keys;
  keyboard_switch_scan_line_t switch_scan_line;
} scan_keyboard_t;

scan_keyboard_info_t* scan_keyboard_info_init(scan_keyboard_info_t* scan_keyboard_info, const char* str_keyboard_layout);

void scan_keyboard_set_function(scan_keyboard_t* scan_keyboard, keyboard_switch_scan_line_t switch_scan_line, keyboard_get_line_keys_t get_line_keys);

void scan_keyboard_deinit(void);

void scan_keyboard_get_scan_key_list(const scan_keyboard_t* scan_keyboard, uint32_t* key_list, uint32_t* key_list_size);

END_C_DECLS

#endif
