#include "scan_keyboard.h"
#include "cjson/cJSON.h"
#include "keyboard_key_code_data.inc"

static scan_keyboard_t s_scan_keyboard;

#define SCAN_KEYBOARD_IS_LEFT(x)  ((x) < 4)

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

  return &s_scan_keyboard;
}

void scan_keyboard_destroy(const scan_keyboard_t* scan_keyboard) {

}

#define UPDATE_SCAN_KEYBOARB_KEY(key, px, py, down, is_special_key)                                                     \
  if (scan_keyboard->info->##key##_x == (px) && scan_keyboard->info->##key##_y == (py)) {                               \
    scan_keyboard->is_##key = down;                                                                                     \
    *is_special_key = TRUE;                                                                                             \
    return;                                                                                                             \
  }                                                                                                                     \

#define UPDATE_SCAN_KEYBOARB_LOCK_KEY(key, px, py, down)                                                                \
  if (scan_keyboard->info->##key##_x == (px) && scan_keyboard->info->##key##_y == (py)) {                               \
    if (scan_keyboard->is_##key && !down) {                                                                             \
      scan_keyboard->is_##key = FALSE;                                                                                  \
    } else if (!scan_keyboard->is_##key && down) {                                                                      \
      scan_keyboard->is_##key = TRUE;                                                                                   \
    }                                                                                                                   \
    return;                                                                                                             \
  }                                                                                                                     \

static void scan_keyboard_update_key_status(scan_keyboard_t* scan_keyboard, uint8_t x, uint8_t y, uint8_t down, c_bool_t* is_special_key) {
  *is_special_key = FALSE;
  UPDATE_SCAN_KEYBOARB_KEY(fn, x, y, down, is_special_key);

  UPDATE_SCAN_KEYBOARB_KEY(left_gui, x, y, down, is_special_key);
  UPDATE_SCAN_KEYBOARB_KEY(right_gui, x, y, down, is_special_key);

  UPDATE_SCAN_KEYBOARB_KEY(left_gui, x, y, down, is_special_key);
  UPDATE_SCAN_KEYBOARB_KEY(right_gui, x, y, down, is_special_key);

  UPDATE_SCAN_KEYBOARB_KEY(left_ctrl, x, y, down, is_special_key);
  UPDATE_SCAN_KEYBOARB_KEY(right_ctrl, x, y, down, is_special_key);

  UPDATE_SCAN_KEYBOARB_KEY(left_shift, x, y, down, is_special_key);
  UPDATE_SCAN_KEYBOARB_KEY(right_shift, x, y, down, is_special_key);

  UPDATE_SCAN_KEYBOARB_LOCK_KEY(caps_lock, x, y, down);
  UPDATE_SCAN_KEYBOARB_LOCK_KEY(number_lock, x, y, down);
}

static c_bool_t scan_keyboard_is_number_key(scan_keyboard_t* scan_keyboard, uint8_t x, uint8_t y) {
  if (scan_keyboard->info->number_lock_x != 0 && scan_keyboard->info->number_lock_y != 0) {
    if (scan_keyboard->info->number_lock_x <= x || scan_keyboard->info->number_lock_y <= y) {
      return TRUE;
    }
  }
  return FALSE;
}

static uint32_t scan_keyboard_add_key_by_list(usb_hid_key_code_t key_code, scan_keyboard_key_map_type_t* key_list, uint32_t key_list_size, uint32_t t_key_list_size) {
  if (key_list_size > t_key_list_size) {
    key_list[t_key_list_size++] = key_code;
  }
  return t_key_list_size;
}

uint32_t scan_keyboard_get_scan_key_list(scan_keyboard_t* scan_keyboard, scan_keyboard_key_map_type_t* key_list, uint32_t key_list_size) {
  uint32_t x = 0, y = 0;
  uint32_t t_key_list_size = 0;
  if (scan_keyboard == NULL || scan_keyboard->get_line_keys == NULL || key_list == NULL) {
    return t_key_list_size;
  }
  for (y = 0; y < scan_keyboard->info->line_size; y++) {
    uint32_t line_key_list_size = 0;
    uint8_t line_key_list[SCAN_KEYBOARD_LINE_KEY_MAX_SIZE] = {0};
    if (scan_keyboard->get_line_keys(y, line_key_list, &line_key_list_size)) {
      for (x = 0; x < SCAN_KEYBOARD_LINE_KEY_MAX_SIZE; x++) {
        c_bool_t is_special_key = FALSE;
        c_bool_t is_down = line_key_list[x] == TRUE;
        usb_hid_key_code_t key_code = USB_HID_KEY_CODE_UNKNOWN;

        scan_keyboard_update_key_status(scan_keyboard, x, y, is_down, &is_special_key);
        if (is_special_key && is_down) {
          key_code = (usb_hid_key_code_t)scan_keyboard->info->key_map[0][y][x];
          if (key_code != USB_HID_KEY_CODE_FN) {
            t_key_list_size = scan_keyboard_add_key_by_list(key_code, key_list, key_list_size, t_key_list_size);
          }
          continue;
        }

        if (!is_down) {
          continue;
        }

        if (scan_keyboard_is_number_key(scan_keyboard, x, y)) {
          if (scan_keyboard->is_left_shift || scan_keyboard->is_right_shift || scan_keyboard->is_number_lock) {
            key_code = (usb_hid_key_code_t)scan_keyboard->info->key_map[1][y][x];
          } else {
            key_code = (usb_hid_key_code_t)scan_keyboard->info->key_map[0][y][x];
          }
          t_key_list_size = scan_keyboard_add_key_by_list(key_code, key_list, key_list_size, t_key_list_size);
        } else {
          if (scan_keyboard->is_left_shift || scan_keyboard->is_right_shift || scan_keyboard->is_caps_lock) {
            key_code = (usb_hid_key_code_t)scan_keyboard->info->key_map[1][y][x];
          } else if (scan_keyboard->is_fn) {
            for (int32_t i = SCAN_KEYBOARD_LAYOUT_MAX_NUMBER; i >= 0; i--) {
              usb_hid_key_code_t code = (usb_hid_key_code_t)scan_keyboard->info->key_map[i][y][x];
              if (code != USB_HID_KEY_CODE_UNKNOWN && 
                  !(USB_HID_KEY_CODE_0 <= code && code <= USB_HID_KEY_CODE_9) &&
                  !(USB_HID_KEY_CODE_A <= code && code <= USB_HID_KEY_CODE_Z)) {
                key_code = code;
                break;
              }
            }
          } else {
            key_code = (usb_hid_key_code_t)scan_keyboard->info->key_map[0][y][x];
          }
          t_key_list_size = scan_keyboard_add_key_by_list(key_code, key_list, key_list_size, t_key_list_size);
        }
      }
    }
  }
  
  return t_key_list_size;
}

static uint32_t scan_keyboard_get_send_usb_keyboard_code(scan_keyboard_key_map_type_t* key_list, uint32_t key_list_size, scan_keyboard_key_map_type_t* last_key_list, uint32_t last_key_list_size, scan_keyboard_key_map_type_t* send_key_list) {
  memcpy(send_key_list, key_list, key_list_size * sizeof(scan_keyboard_key_map_type_t));
  return key_list_size;
}

c_bool_t scan_keyboard_get_usb_keyboard_code(scan_keyboard_t* scan_keyboard, uint8_t keyboard[8]) {
#define USB_HID_KEYBOARD_KEY_MAX_NUMBER       6
#define USB_HID_KEYBOARD_KEY_ALL_NUMBER       USB_HID_KEYBOARD_KEY_MAX_NUMBER + 8

  uint32_t size = 0, send_key_size = 0;
  scan_keyboard_key_map_type_t key_list[FISH_KEYBOARD_KEY_MAX_NUMBER];
  scan_keyboard_key_map_type_t send_key_list[USB_HID_KEYBOARD_KEY_ALL_NUMBER];
  memset(key_list, 0x0, sizeof(key_list));
  memset(send_key_list, 0x0, sizeof(send_key_list));

  size = scan_keyboard_get_scan_key_list(scan_keyboard, key_list, FISH_KEYBOARD_KEY_MAX_NUMBER);

  if (scan_keyboard == NULL || scan_keyboard->get_line_keys == NULL || keyboard == NULL) {
    return FALSE;
  }

  send_key_size = scan_keyboard_get_send_usb_keyboard_code(key_list, size, scan_keyboard->last_send_key_list, scan_keyboard->last_send_key_list_size, send_key_list);

  if (send_key_size == 0) {
    memset(keyboard, 0x0, 8 * sizeof(uint8_t));
  } else {
    uint32_t i = 0;
    uint8_t kb_id = 2;
    uint8_t kb_byte1 = 0;
    for (i = 0; i < send_key_size; i++) {
      usb_hid_key_code_t usb_hid_key_code = (usb_hid_key_code_t)key_list[i];
      switch (usb_hid_key_code) {
      case USB_HID_KEY_CODE_LCTRL:
        kb_byte1 |= (1 << 0);
        break;
      case USB_HID_KEY_CODE_LSHIFT:
        kb_byte1 |= (1 << 1);
        break;
      case USB_HID_KEY_CODE_LALT:
        kb_byte1 |= (1 << 2);
        break;
      case USB_HID_KEY_CODE_LGUI:
        kb_byte1 |= (1 << 3);
        break;
      case USB_HID_KEY_CODE_RCTRL:
        kb_byte1 |= (1 << 4);
        break;
      case USB_HID_KEY_CODE_RSHIFT:
        kb_byte1 |= (1 << 5);
        break;
      case USB_HID_KEY_CODE_RALT:
        kb_byte1 |= (1 << 6);
        break;
      case USB_HID_KEY_CODE_RGUI:
        kb_byte1 |= (1 << 7);
        break;
      default:
        if (kb_id < USB_HID_KEYBOARD_KEY_MAX_NUMBER + kb_id) {
          keyboard[kb_id++] = usb_hid_key_code;
        }
        break;
      }
    }
    keyboard[0] = kb_byte1;
  }
  scan_keyboard->last_send_key_list_size = send_key_size;
  memcpy(scan_keyboard->last_send_key_list, send_key_list, send_key_size * sizeof(scan_keyboard_key_map_type_t));
  return TRUE;
}
