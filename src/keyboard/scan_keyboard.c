#include "cjson/cJSON.h"
#include "scan_keyboard.h"
#include "keyboard_key_code_data.inc"

static scan_keyboard_t s_scan_keyboard;

#define SCAN_KEYBOARD_IS_LEFT(x)  ((x) < 4)

static int scan_keyboard_fixed_list_on_compare(void* a, void* b) {
  scan_keyboard_send_key_type_t* key_a = (scan_keyboard_send_key_type_t*)a;
  scan_keyboard_send_key_type_t* key_b = (scan_keyboard_send_key_type_t*)b;
  if (key_a->y != key_b->y) {
    return key_a->y - key_b->y;
  }
  return key_a->x - key_a->x;
}

static void scan_keyboard_set_layer_info(scan_keyboard_info_t* scan_keyboard_info, uint8_t x, uint8_t y, usb_hid_key_code_t scan_key_code) {
  switch (scan_key_code) {
  case USB_HID_KEY_CODE_LSHIFT:
      scan_keyboard_info->left_shift_x = x;
      scan_keyboard_info->left_shift_y = y;
  case USB_HID_KEY_CODE_RSHIFT:
      scan_keyboard_info->right_shift_x = x;
      scan_keyboard_info->right_shift_y = y;
    break;
  case USB_HID_KEY_CODE_LALT:
      scan_keyboard_info->left_alt_x = x;
      scan_keyboard_info->left_alt_y = y;
  case USB_HID_KEY_CODE_RALT:
      scan_keyboard_info->right_alt_x = x;
      scan_keyboard_info->right_alt_y = y;
    break;
  case USB_HID_KEY_CODE_LCTRL:
      scan_keyboard_info->left_ctrl_x = x;
      scan_keyboard_info->left_ctrl_y = y;
  case USB_HID_KEY_CODE_RCTRL:
      scan_keyboard_info->right_ctrl_x = x;
      scan_keyboard_info->right_ctrl_y = y;
    break;
  case USB_HID_KEY_CODE_LGUI:
      scan_keyboard_info->left_gui_x = x;
      scan_keyboard_info->left_gui_y = y;
  case USB_HID_KEY_CODE_RGUI:
      scan_keyboard_info->right_gui_x = x;
      scan_keyboard_info->right_gui_y = y;
    break;
  case USB_HID_KEY_CODE_CAPSLOCK:
    scan_keyboard_info->caps_lock_x = x;
    scan_keyboard_info->caps_lock_y = y;
    break;
  case USB_HID_KEY_CODE_NUMLOCKCLEAR:
    scan_keyboard_info->number_lock_x = x;
    scan_keyboard_info->number_lock_y = y;
    break;
  case USB_HID_KEY_CODE_SCROLLLOCK:
    scan_keyboard_info->scroll_lock_x = x;
    scan_keyboard_info->scroll_lock_y = y;
    break;
  case USB_HID_KEY_CODE_FN:
    scan_keyboard_info->fn_x = x;
    scan_keyboard_info->fn_y = y;
    break; 
  default:
    break;
  }
}

scan_keyboard_info_t* scan_keyboard_info_init(scan_keyboard_info_t* scan_keyboard_info, const char* str_keyboard_layout) {
  uint32_t i = 0;
  cJSON* json = cJSON_Parse(str_keyboard_layout);

  memset(scan_keyboard_info, 0x0, sizeof(scan_keyboard_info_t));

  scan_keyboard_info->line_size = cJSON_GetArraySize(json);

  assert(scan_keyboard_info->line_size <= SCAN_KEYBOARD_LINE_MAX_SIZE);
  
  for (i = 0; i < scan_keyboard_info->line_size; i++) {
    uint32_t j = 0, line_key_size = 0;
    cJSON* line_json = cJSON_GetArrayItem(json, i);
    uint32_t line_size = cJSON_GetArraySize(line_json);
    for (j = 0; j < line_size; j++) {
      cJSON* key = cJSON_GetArrayItem(line_json, j);
      if (cJSON_IsString(key)) {
        int z = 0;
        const char* end = NULL;
        const usb_hid_key_code_info_t* info = NULL;
        char* str_key = cJSON_GetStringValue(key);
        const char* start = str_key;
        do {
          char key[128] = {0}; 
          uint32_t jmp_number = g_keyboard_key_code_jmp_table[(uint32_t)key[0]];
          end = strchr(start, '\n');
          if (end != NULL) {
            memcpy(key, start, end - start);
            start = end + 1;
          } else {
            memcpy(key, start, strlen(start));
          }
          do {
            info = &(g_keyboard_key_code_map[jmp_number++]);
            if (strcmp(key, info->usb_hid_key) == 0) {
              if (USB_HID_KEY_CODE_IS_SCANCODE(info->usb_hid_key_code)) {
                usb_hid_key_code_t usb_hid_key_code = USB_HID_KEY_CODE_UNKNOWN;
                if (SCAN_KEYBOARD_IS_LEFT(line_key_size)) {
                  usb_hid_key_code = USB_HID_KEY_CODE_SCANCODE_GET_LEFT_KEY_CODE(info->usb_hid_key_code);
                } else {
                  usb_hid_key_code = USB_HID_KEY_CODE_SCANCODE_GET_RIGHT_KEY_CODE(info->usb_hid_key_code);
                }
                scan_keyboard_info->key_map[z++][i][line_key_size] = usb_hid_key_code;
                scan_keyboard_set_layer_info(scan_keyboard_info, (uint8_t)line_key_size, (uint8_t)i, usb_hid_key_code);
              } else {
                scan_keyboard_info->key_map[z++][i][line_key_size] = (usb_hid_key_code_t)info->usb_hid_key_code;
                scan_keyboard_set_layer_info(scan_keyboard_info, (uint8_t)line_key_size, (uint8_t)i, (usb_hid_key_code_t)info->usb_hid_key_code);
              }
              break;
            }
          } while(info != NULL);
        } while (end != NULL);
        line_key_size++;
      }
    }
    if (line_key_size > scan_keyboard_info->line_key_size) {
      scan_keyboard_info->line_key_size = line_key_size;
    }
  }
  cJSON_Delete(json);
  c_fixed_list_init((c_fixed_list_t*)&s_scan_keyboard.last_send_key_list, C_FIXED_LIST_GET_TYPE_SIZE(scan_keyboard_send_key_type_t), FISH_KEYBOARD_SEND_KEY_MAX_NUMBER, sizeof(scan_keyboard_send_key_type_t), scan_keyboard_fixed_list_on_compare);
  return scan_keyboard_info;
}

scan_keyboard_t* scan_keyboard_create(scan_keyboard_info_t* scan_keyboard_info, keyboard_get_scan_keys_t get_line_keys) {
  if (get_line_keys == NULL) {
    return NULL;
  }

  if (scan_keyboard_info != NULL) {
    s_scan_keyboard.info = scan_keyboard_info;
  } else {
    s_scan_keyboard.info = (scan_keyboard_info_t*)g_scan_keyboard_info_data;
  }

  s_scan_keyboard.get_line_keys = get_line_keys;

  s_scan_keyboard.p_last_send_key_list = (c_fixed_list_t*)&s_scan_keyboard.last_send_key_list;
  c_fixed_list_init((c_fixed_list_t*)&s_scan_keyboard.last_send_key_list, C_FIXED_LIST_GET_TYPE_SIZE(scan_keyboard_send_key_type_t), FISH_KEYBOARD_SEND_KEY_MAX_NUMBER, sizeof(scan_keyboard_send_key_type_t), scan_keyboard_fixed_list_on_compare);

  return &s_scan_keyboard;
}

void scan_keyboard_destroy(scan_keyboard_t* scan_keyboard) {
  c_fixed_list_deinit(scan_keyboard->p_last_send_key_list);
}

#define UPDATE_SCAN_KEYBOARB_KEY(key, px, py, down, is_special_key)                                                     \
  if (scan_keyboard->info->##key##_x == (px) && scan_keyboard->info->##key##_y == (py)) {                               \
    scan_keyboard->is_##key = down;                                                                                     \
    *is_special_key = TRUE;                                                                                             \
    return;                                                                                                             \
  }                                                                                                                     \

#define UPDATE_SCAN_KEYBOARB_LOCK_KEY(key, px, py, down)                                                                \
  if (scan_keyboard->info->##key##_x == (px) && scan_keyboard->info->##key##_y == (py)) {                               \
    if (scan_keyboard->is_##key##.down && !down) {                                                                      \
      scan_keyboard->is_##key##.restate = FALSE;                                                                        \
    }                                                                                                                   \
    if (!scan_keyboard->is_##key##.restate && down) {                                                                   \
      scan_keyboard->is_##key##.lock = !scan_keyboard->is_##key##.lock;                                                 \
      scan_keyboard->is_##key##.restate = TRUE;                                                                         \
    }                                                                                                                   \
    scan_keyboard->is_##key##.down = down;                                                                              \
    return;                                                                                                             \
  }                                                                                                                     \

static void scan_keyboard_update_key_status(scan_keyboard_t* scan_keyboard, uint8_t x, uint8_t y, uint8_t down, c_bool_t* is_special_key) {
  *is_special_key = FALSE;
  UPDATE_SCAN_KEYBOARB_KEY(fn, x, y, down, is_special_key);

  UPDATE_SCAN_KEYBOARB_KEY(left_gui, x, y, down, is_special_key);
  UPDATE_SCAN_KEYBOARB_KEY(right_gui, x, y, down, is_special_key);

  UPDATE_SCAN_KEYBOARB_KEY(left_alt, x, y, down, is_special_key);
  UPDATE_SCAN_KEYBOARB_KEY(right_alt, x, y, down, is_special_key);

  UPDATE_SCAN_KEYBOARB_KEY(left_ctrl, x, y, down, is_special_key);
  UPDATE_SCAN_KEYBOARB_KEY(right_ctrl, x, y, down, is_special_key);

  UPDATE_SCAN_KEYBOARB_KEY(left_shift, x, y, down, is_special_key);
  UPDATE_SCAN_KEYBOARB_KEY(right_shift, x, y, down, is_special_key);

  UPDATE_SCAN_KEYBOARB_LOCK_KEY(caps_lock, x, y, down);
  UPDATE_SCAN_KEYBOARB_LOCK_KEY(number_lock, x, y, down);
  UPDATE_SCAN_KEYBOARB_LOCK_KEY(scroll_lock, x, y, down);
}

static c_bool_t scan_keyboard_is_FX_key_by_usb(scan_keyboard_key_map_type_t key) {
  return USB_HID_KEY_CODE_F1 <= key && key <= USB_HID_KEY_CODE_F12;
}

static c_bool_t scan_keyboard_is_special_control_key_by_usb(scan_keyboard_key_map_type_t key) {
  return (USB_HID_KEY_CODE_INSERT <= key && key <= USB_HID_KEY_CODE_UP) || ( USB_HID_KEY_CODE_RETURN <= key && key <= USB_HID_KEY_CODE_SPACE);
}

static uint32_t scan_keyboard_add_key_by_list(usb_hid_key_code_t key, uint32_t x, uint32_t y, scan_keyboard_send_key_type_t* key_list, uint32_t key_list_size, uint32_t t_key_list_size) {
  if (key_list_size > t_key_list_size) {
    key_list[t_key_list_size].key = key;
    key_list[t_key_list_size].x = (uint16_t)x;
    key_list[t_key_list_size].y = (uint16_t)y;
    t_key_list_size++;
  }
  return t_key_list_size;
}

uint32_t scan_keyboard_get_scan_key_list(scan_keyboard_t* scan_keyboard, scan_keyboard_send_key_type_t* key_list, uint32_t key_list_size) {
  uint32_t x = 0, y = 0;
  uint32_t t_key_list_size = 0;
  c_fixed_list_node_t* key_node = NULL;
  c_fixed_list_t* p_last_send_key_list = NULL;
  scan_keyboard_send_key_type_t tmp_key = {0};
  if (scan_keyboard == NULL || scan_keyboard->get_line_keys == NULL || key_list == NULL) {
    return t_key_list_size;
  }
  p_last_send_key_list = scan_keyboard->p_last_send_key_list;
  key_node = c_fixed_list_get_first_node(p_last_send_key_list);
  for (y = 0; y < scan_keyboard->info->line_size; y++) {
    uint8_t line_key_list[SCAN_KEYBOARD_LINE_KEY_MAX_SIZE] = {0};
    uint32_t line_key_list_size = ARRAY_SIZE(line_key_list);
    if (scan_keyboard->get_line_keys(y, line_key_list, &line_key_list_size)) {
      for (x = 0; x < SCAN_KEYBOARD_LINE_KEY_MAX_SIZE; x++) {
        c_bool_t cache = FALSE;
        c_bool_t is_special_key = FALSE;
        c_bool_t is_down = line_key_list[x] == TRUE;
        scan_keyboard_update_key_status(scan_keyboard, x, y, is_down, &is_special_key);

        if (c_fixed_list_get_node_data(p_last_send_key_list, key_node, &tmp_key)) {
          if (tmp_key.x == x && tmp_key.y == y) {
            if (!is_down) {
              scan_keyboard_send_key_type_t tmp_key1 = {0};
              c_fixed_list_pop(p_last_send_key_list, &tmp_key1);
              key_node = c_fixed_list_get_first_node(p_last_send_key_list);
            } else {
              cache = TRUE;
              key_node = c_fixed_list_get_next_node(p_last_send_key_list, key_node);
            }
          }
        }

        if (is_down && !is_special_key && !cache) {
          usb_hid_key_code_t key_code = (usb_hid_key_code_t)scan_keyboard->info->key_map[0][y][x];
          t_key_list_size = scan_keyboard_add_key_by_list(key_code, x, y, key_list, key_list_size, t_key_list_size);
        }
      }
    }
  }
  
  return t_key_list_size;
}

static uint32_t scan_keyboard_get_send_usb_keyboard_code(scan_keyboard_t* scan_keyboard, scan_keyboard_send_key_type_t* key_list, uint32_t key_list_size) {
  uint32_t i = 0, size = 0, capacity = 0;
  c_fixed_list_t* p_last_send_key_list = scan_keyboard->p_last_send_key_list;
  
  capacity = c_fixed_list_get_capacity(p_last_send_key_list);
  size = capacity - c_fixed_list_get_count(p_last_send_key_list);

  for (i = 0; i < size && i < key_list_size; i++) {
    c_fixed_list_sorted_insert(p_last_send_key_list, &key_list[i]);
  }
  
  return c_fixed_list_get_count(p_last_send_key_list);
}

c_bool_t scan_keyboard_get_usb_keyboard_code(scan_keyboard_t* scan_keyboard, uint8_t keyboard[8]) {
  uint32_t size = 0, send_key_size = 0;
  scan_keyboard_send_key_type_t common_key_list[FISH_KEYBOARD_SEND_KEY_MAX_NUMBER];
  memset(common_key_list, 0x0, sizeof(scan_keyboard_send_key_type_t) * FISH_KEYBOARD_SEND_KEY_MAX_NUMBER);

  if (scan_keyboard == NULL || scan_keyboard->get_line_keys == NULL || keyboard == NULL) {
    return FALSE;
  }

  size = scan_keyboard_get_scan_key_list(scan_keyboard, common_key_list, ARRAY_SIZE(common_key_list));

  send_key_size = scan_keyboard_get_send_usb_keyboard_code(scan_keyboard, common_key_list, size);
  if (send_key_size == 0 && 
      !scan_keyboard->is_left_ctrl && 
      !scan_keyboard->is_left_shift && 
      !scan_keyboard->is_left_alt && 
      !scan_keyboard->is_left_gui && 
      !scan_keyboard->is_right_ctrl && 
      !scan_keyboard->is_right_shift && 
      !scan_keyboard->is_right_alt && 
      !scan_keyboard->is_right_gui) {
    memset(keyboard, 0x0, 8 * sizeof(uint8_t));
  } else {
    uint32_t i = 0;
    uint8_t kb_id = 2;
    uint8_t kb_byte1 = 0;
    c_fixed_list_t* p_send_key_list = scan_keyboard->p_last_send_key_list;
    c_fixed_list_node_t* curr_node = c_fixed_list_get_first_node(p_send_key_list);
    for (i = 0; i < send_key_size; i++) {
      scan_keyboard_send_key_type_t tmp_key = {0};
      if (c_fixed_list_get_node_data(p_send_key_list, curr_node, &tmp_key)) {
        usb_hid_key_code_t usb_hid_key_code = (usb_hid_key_code_t)tmp_key.key;
        keyboard[kb_id++] = usb_hid_key_code;
      }
      curr_node = c_fixed_list_get_next_node(p_send_key_list, curr_node);
    }

    if (scan_keyboard->is_left_ctrl) {
      kb_byte1 |= (1 << 0);
    }
    if (scan_keyboard->is_left_shift) {
      kb_byte1 |= (1 << 1);
    }
    if (scan_keyboard->is_left_alt) {
      kb_byte1 |= (1 << 2);
    }
    if (scan_keyboard->is_left_gui) {
      kb_byte1 |= (1 << 3);
    }
    if (scan_keyboard->is_right_ctrl) {
      kb_byte1 |= (1 << 4);
    }
    if (scan_keyboard->is_right_shift) {
      kb_byte1 |= (1 << 5);
    }
    if (scan_keyboard->is_right_alt) {
      kb_byte1 |= (1 << 6);
    }
    if (scan_keyboard->is_right_gui) {
      kb_byte1 |= (1 << 7);
    }
    keyboard[0] = kb_byte1;
  }
  return TRUE;
}

c_bool_t scan_keyboard_get_num_lock_statue(scan_keyboard_t* scan_keyboard) {
  if (scan_keyboard != NULL) {
    return scan_keyboard->is_scroll_lock.lock;
  }
  return FALSE;
}

c_bool_t scan_keyboard_get_caps_lock_statue(scan_keyboard_t* scan_keyboard) {
  if (scan_keyboard != NULL) {
    return scan_keyboard->is_scroll_lock.lock;
  }
  return FALSE;
}

c_bool_t scan_keyboard_get_scroll_lock_statue(scan_keyboard_t* scan_keyboard) {
  if (scan_keyboard != NULL) {
    return scan_keyboard->is_scroll_lock.lock;
  }
  return FALSE;
}

void scan_keyboard_set_num_lock_statue(scan_keyboard_t* scan_keyboard, c_bool_t lock) {
  if (scan_keyboard != NULL) {
    scan_keyboard->is_scroll_lock.lock = lock;
  }
}

void scan_keyboard_set_caps_lock_statue(scan_keyboard_t* scan_keyboard, c_bool_t lock) {
  if (scan_keyboard != NULL) {
    scan_keyboard->is_scroll_lock.lock = lock;
  }
}

void scan_keyboard_set_scroll_lock_statue(scan_keyboard_t* scan_keyboard, c_bool_t lock) {
  if (scan_keyboard != NULL) {
    scan_keyboard->is_scroll_lock.lock = lock;
  }
}
