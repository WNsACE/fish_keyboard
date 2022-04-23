#include "scan_keyboard.h"
#include "../3rd/cjson/cJSON.h"

static scan_keyboard_t scan_keyboard;

const scan_keyboard_info_t* scan_keyboard_info_init(scan_keyboard_info_t* scan_keyboard_info,const char* str_keyboard_layout) {
  uint32_t i = 0, j = 0;
  cJSON* json = cJSON_Parse(str_keyboard_layout);

  scan_keyboard_info->line_size = cJSON_GetArraySize(json);

  assert(scan_keyboard_info->line_size <= SCAN_KEYBOARD_LINE_MAX_SIZE);
  
  for (i = 0; i < scan_keyboard_info->line_size; i++) {
    uint32_t j = 0, line_key_size = 0;
    cJSON* line_json = cJSON_GetArrayItem(json, i);
    uint32_t line_size = cJSON_GetArraySize(line_json);
    for (j = 0; j < line_key_size; j++) {
      cJSON* key = cJSON_GetArrayItem(line_json, j);
      if (cJSON_IsString(key)) {
        int z = 0;
        const char* end = NULL;
        scan_key_code_info_t* info = NULL;
        char* str_key = cJSON_GetStringValue(key);
        const char* start = str_key;
        do {
          char* key = start;
          uint32_t jmp_number = g_keyboard_key_code_jmp_table[(uint32_t)key[0]];
          end = strchr(key, '\n');
          do {
            info = &(g_keyboard_key_code_map[jmp_number]);
            if (strcmp(info->scan_key, key) == 0) {
              scan_keyboard_info->key_map[z++][i][j] = info->scan_key_code;
              break;;
            }
          } while(info != NULL);
        } while (end != NULL);
      }
    }
    if (line_key_size > scan_keyboard_info->line_key_size) {
      scan_keyboard_info->line_key_size = line_key_size;
    }
  }
}

void scan_keyboard_set_function(scan_keyboard_t* scan_keyboard, keyboard_switch_scan_line_t switch_scan_line, keyboard_get_line_keys_t get_line_keys) {

}

void scan_keyboard_deinit(void) {
  cJSON_Delete((cJSON*)scan_keyboard.keyboard_layout_data);
}

void scan_keyboard_get_scan_key_list(const scan_keyboard_t* scan_keyboard, uint32_t* key_list, uint32_t* key_list_size) {

}

