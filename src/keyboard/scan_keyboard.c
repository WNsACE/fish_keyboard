#include "scan_keyboard.h"
#include "cjson/cJSON.h"
#include "keyboard_key_code_data.inc"

static scan_keyboard_t s_scan_keyboard;

static void scan_keyboard_set_layer_info(scan_keyboard_info_t* scan_keyboard_info, uint8_t x, uint8_t y, scan_key_code_t scan_key_code) {
  switch (scan_key_code)
  {
  case SCAN_KEY_SHIFT:
    if (scan_keyboard_info->shift_left_y == 0) {
      scan_keyboard_info->shift_left_x = x;
      scan_keyboard_info->shift_left_y = y;
    } else {
      if (scan_keyboard_info->shift_left_x >= x) {
        scan_keyboard_info->shift_right_x = scan_keyboard_info->shift_left_x;
        scan_keyboard_info->shift_right_y = scan_keyboard_info->shift_left_y;

        scan_keyboard_info->shift_left_x = x;
        scan_keyboard_info->shift_left_y = y;
      } else {
        scan_keyboard_info->shift_right_x = x;
        scan_keyboard_info->shift_right_y = y;
      }
    }
    break;
  case SCAN_KEY_CAPES_LOCK:
    scan_keyboard_info->caps_lock_x = x;
    scan_keyboard_info->caps_lock_y = y;
    break;
  case SCAN_KEY_NUM_LOCK:
    scan_keyboard_info->number_lock_x = x;
    scan_keyboard_info->number_lock_y = y;
    break;
  case SCAN_KEY_FN:
    scan_keyboard_info->fn_x = x;
    scan_keyboard_info->fn_y = y;
    break; 
  default:
    break;
  }
}

scan_keyboard_info_t* scan_keyboard_info_init(scan_keyboard_info_t* scan_keyboard_info, const char* str_keyboard_layout) {
  uint32_t i = 0, j = 0;
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
        const scan_key_code_info_t* info = NULL;
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
            if (strcmp(key, info->scan_key) == 0) {
              scan_keyboard_info->key_map[z++][i][line_key_size] = info->scan_key_code;
              scan_keyboard_set_layer_info(scan_keyboard_info, (uint8_t)line_key_size, (uint8_t)i, info->scan_key_code);
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

const scan_keyboard_t* scan_keyboard_create(scan_keyboard_info_t* scan_keyboard_info, keyboard_get_scan_keys_t get_line_keys) {
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

#define UPDATE_SCAN_KEYBOARB_KEY(key, px, py) if (scan_keyboard->info->##key##_x == (px) && scan_keyboard->info->##key##_y == (py)) scan_keyboard->is_##key = down;
#define UPDATE_SCAN_KEYBOARB_LOCK_KEY(key, px, py) \
  if (scan_keyboard->info->##key##_x == (px) && scan_keyboard->info->##key##_y == (py)) {                               \
    if (scan_keyboard->is_##key && !down) {                                                                             \
      scan_keyboard->is_##key = FALSE;                                                                                  \
    } else if (!scan_keyboard->is_##key && down) {                                                                      \
      scan_keyboard->is_##key = TRUE;                                                                                   \
    }                                                                                                                   \
  }                                                                                                                     \


static void scan_keyboard_update_key_status(scan_keyboard_t* scan_keyboard, uint8_t x, uint8_t y, uint8_t down) {

  UPDATE_SCAN_KEYBOARB_KEY(fn, x, y);
  UPDATE_SCAN_KEYBOARB_LOCK_KEY(caps_lock, x, y);
  UPDATE_SCAN_KEYBOARB_LOCK_KEY(number_lock, x, y);

  if ((scan_keyboard->info->shift_left_x == x && scan_keyboard->info->shift_left_y == y) || 
      (scan_keyboard->info->shift_right_x == x && scan_keyboard->info->shift_right_y == y)) {
    scan_keyboard->is_shift = down;
  }
}

static c_bool_t scan_keyboard_is_number_key(scan_keyboard_t* scan_keyboard, uint8_t x, uint8_t y) {
  if (scan_keyboard->info->number_lock_x != 0 && scan_keyboard->info->number_lock_y != 0) {
    if (scan_keyboard->info->number_lock_x <= x || scan_keyboard->info->number_lock_y <= y) {
      return TRUE;
    }
  }
  return FALSE;
}

static uint32_t scan_keyboard_add_key_by_list(scan_key_code_t key_code, uint32_t* key_list, uint32_t key_list_size, uint32_t t_key_list_size) {
  if (key_list_size > t_key_list_size) {
    key_list[t_key_list_size++] = key_code;
  }
  return t_key_list_size;
}

uint32_t scan_keyboard_get_scan_key_list(scan_keyboard_t* scan_keyboard, uint32_t* key_list, uint32_t key_list_size) {
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
        scan_key_code_t key_code = SCAN_KEY_NONE;

        scan_keyboard_update_key_status(scan_keyboard, x, y, line_key_list[x]);

        if (scan_keyboard_is_number_key(scan_keyboard, x, y)) {
          if (scan_keyboard->is_shift || scan_keyboard->is_number_lock) {
            key_code = scan_keyboard->info->key_map[1][y][x];
          } else {
            key_code = scan_keyboard->info->key_map[0][y][x];
          }
          t_key_list_size = scan_keyboard_add_key_by_list(key_code, key_list, key_list_size, t_key_list_size);
        } else {
          if (scan_keyboard->is_shift || scan_keyboard->is_caps_lock) {
            key_code = scan_keyboard->info->key_map[1][y][x];
          } else if (scan_keyboard->is_fn) {
            for (uint32_t i = SCAN_KEYBOARD_LAYOUT_MAX_NUMBER; i >= 0; i--) {
              scan_key_code_t code = scan_keyboard->info->key_map[i][y][x];
              if (code != SCAN_KEY_NONE && 
                  !(SCAN_KEY_0 <= code && code <= SCAN_KEY_9) &&
                  !(SCAN_KEY_A <= code && code <= SCAN_KEY_Z)) {
                key_code = code;
                break;
              }
            }
          } else {
            key_code = scan_keyboard->info->key_map[0][y][x];
          }
          t_key_list_size = scan_keyboard_add_key_by_list(key_code, key_list, key_list_size, t_key_list_size);
        }
      }
    }
  }
  
  return t_key_list_size;
}

