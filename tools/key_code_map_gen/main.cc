#include <map>
#include <list>
#include <string>
#include <stdio.h>
#include <algorithm>
#include "cjson/cJSON.h"
#include "keyboard/scan_key_code.h"

using namespace std;

class keyboard_info_t {
  public:
  char *keyboard_key_name;
  uint32_t len;

  bool operator>(keyboard_info_t info) {
    return strcmp(keyboard_key_name, info.keyboard_key_name) > 0;
  }

  bool operator<(keyboard_info_t info) {
    return strcmp(keyboard_key_name, info.keyboard_key_name) < 0;
  }

  bool operator==(keyboard_info_t info) {
    return strcmp(keyboard_key_name, info.keyboard_key_name) == 0;
  }
};

static int32_t num_lock_x = -1;
static int32_t num_lock_y = -1;
static const char *g_str_num_lock = "Num Lock";
static map<string, const char *> g_keyboard_key_code_relation_table = {
    {"", "SCAN_KEY_SPACEBAR"},
    {"!", "SCAN_KEY_EXCLAIM"},
    {"\"", "SCAN_KEY_QUOTEDBL"},
    {"#", "SCAN_KEY_HASH"},
    {"$", "SCAN_KEY_DOLLAR"},
    {"%", "SCAN_KEY_PERCENT"},
    {"&", "SCAN_KEY_AMPERSAND"},
    {"'", "SCAN_KEY_BACK_QUOTE"},
    {"(", "SCAN_KEY_LEFTPAREN"},
    {")", "SCAN_KEY_RIGHTPAREN"},
    {"*", "SCAN_KEY_ASTERISK"},
    {"+", "SCAN_KEY_PLUS"},
    {",", "SCAN_KEY_COMMA"},
    {"-", "SCAN_KEY_MINUS"},
    {".", "SCAN_KEY_PERIOD"},
    {"/", "SCAN_KEY_SLASH"},
    {"0", "SCAN_KEY_0"},
    {"0_Num", "SCAN_KEY_NUM_0"},
    {"1", "SCAN_KEY_1"},
    {"1_Num", "SCAN_KEY_NUM_1"},
    {"2", "SCAN_KEY_2"},
    {"2_Num", "SCAN_KEY_NUM_2"},
    {"3", "SCAN_KEY_3"},
    {"3_Num", "SCAN_KEY_NUM_3"},
    {"4", "SCAN_KEY_4"},
    {"4_Num", "SCAN_KEY_NUM_4"},
    {"5", "SCAN_KEY_5"},
    {"5_Num", "SCAN_KEY_NUM_5"},
    {"6", "SCAN_KEY_6"},
    {"6_Num", "SCAN_KEY_NUM_6"},
    {"7", "SCAN_KEY_7"},
    {"7_Num", "SCAN_KEY_NUM_7"},
    {"8", "SCAN_KEY_8"},
    {"8_Num", "SCAN_KEY_NUM_8"},
    {"9", "SCAN_KEY_9"},
    {"9_Num", "SCAN_KEY_NUM_9"},
    {":", "SCAN_KEY_COLON"},
    {";", "SCAN_KEY_SEMICOLON"},
    {"<", "SCAN_KEY_LESS"},
    {"=", "SCAN_KEY_EQUAL"},
    {">", "SCAN_KEY_GREATER"},
    {"?", "SCAN_KEY_QUESTION"},
    {"@", "SCAN_KEY_AT"},
    {"A", "SCAN_KEY_A"},
    {"Alt", "SCAN_KEY_ALT"},
    {"B", "SCAN_KEY_B"},
    {"Backspace", "SCAN_KEY_BACK_SPACE"},
    {"Break", "SCAN_KEY_PAUSE_BREAK"},
    {"C", "SCAN_KEY_C"},
    {"Caps Lock", "SCAN_KEY_CAPE_LOCK"},
    {"Ctrl", "SCAN_KEY_CTRL"},
    {"D", "SCAN_KEY_D"},
    {"Del", "SCAN_KEY_DELETE"},
    {"Delete", "SCAN_KEY_DELETE"},
    {"E", "SCAN_KEY_E"},
    {"End", "SCAN_KEY_END"},
    {"Enter", "SCAN_KEY_ENTER"},
    {"Esc", "SCAN_KEY_ESC"},
    {"F", "SCAN_KEY_F"},
    {"F1", "SCAN_KEY_F1"},
    {"F10", "SCAN_KEY_F10"},
    {"F11", "SCAN_KEY_F11"},
    {"F12", "SCAN_KEY_F12"},
    {"F2", "SCAN_KEY_F2"},
    {"F3", "SCAN_KEY_F3"},
    {"F4", "SCAN_KEY_F4"},
    {"F5", "SCAN_KEY_F5"},
    {"F6", "SCAN_KEY_F6"},
    {"F7", "SCAN_KEY_F7"},
    {"F8", "SCAN_KEY_F8"},
    {"F9", "SCAN_KEY_F9"},
    {"FN", "SCAN_KEY_FN"},
    {"G", "SCAN_KEY_G"},
    {"H", "SCAN_KEY_H"},
    {"Home", "SCAN_KEY_HOME"},
    {"I", "SCAN_KEY_I"},
    {"Ins", "SCAN_KEY_INSERT"},
    {"Insert", "SCAN_KEY_INSERT"},
    {"J", "SCAN_KEY_J"},
    {"K", "SCAN_KEY_K"},
    {"L", "SCAN_KEY_L"},
    {"M", "SCAN_KEY_M"},
    {"Menu", "SCAN_KEY_MENU"},
    {"N", "SCAN_KEY_N"},
    {"Num Lock", "SCAN_KEY_NUM_LOCK"},
    {"O", "SCAN_KEY_O"},
    {"P", "SCAN_KEY_P"},
    {"Pause", "SCAN_KEY_PAUSE_BREAK"},
    {"PgDn", "SCAN_KEY_PAGE_DOWM"},
    {"PgUp", "SCAN_KEY_PAGE_UP"},
    {"PrtSc", "SCAN_KEY_PRINT_SCREEN"},
    {"Q", "SCAN_KEY_Q"},
    {"R", "SCAN_KEY_R"},
    {"S", "SCAN_KEY_S"},
    {"Scroll Lock", "SCAN_KEY_SCROLL_LOCK"},
    {"Shift", "SCAN_KEY_SHIFT"},
    {"T", "SCAN_KEY_T"},
    {"Tab", "SCAN_KEY_TAB"},
    {"U", "SCAN_KEY_U"},
    {"V", "SCAN_KEY_V"},
    {"W", "SCAN_KEY_W"},
    {"Win", "SCAN_KEY_WIN"},
    {"X", "SCAN_KEY_X"},
    {"Y", "SCAN_KEY_Y"},
    {"Z", "SCAN_KEY_Z"},
    {"[", "SCAN_KEY_RIGHT_BRACKET"},
    {"\\", "SCAN_KEY_A_SLASH"},
    {"]", "SCAN_KEY_RIGHT_BRACKET"},
    {"^", "SCAN_KEY_CARET"},
    {"_", "SCAN_KEY_UNDER_SCORE"},
    {"`", "SCAN_KEY_BACK_QUOTE"},
    {"a", "SCAN_KEY_a"},
    {"b", "SCAN_KEY_b"},
    {"c", "SCAN_KEY_c"},
    {"d", "SCAN_KEY_d"},
    {"e", "SCAN_KEY_e"},
    {"f", "SCAN_KEY_f"},
    {"g", "SCAN_KEY_g"},
    {"h", "SCAN_KEY_h"},
    {"i", "SCAN_KEY_i"},
    {"j", "SCAN_KEY_j"},
    {"k", "SCAN_KEY_k"},
    {"l", "SCAN_KEY_l"},
    {"m", "SCAN_KEY_m"},
    {"n", "SCAN_KEY_n"},
    {"o", "SCAN_KEY_o"},
    {"p", "SCAN_KEY_p"},
    {"q", "SCAN_KEY_q"},
    {"r", "SCAN_KEY_r"},
    {"s", "SCAN_KEY_s"},
    {"t", "SCAN_KEY_t"},
    {"u", "SCAN_KEY_u"},
    {"v", "SCAN_KEY_v"},
    {"w", "SCAN_KEY_w"},
    {"x", "SCAN_KEY_x"},
    {"y", "SCAN_KEY_y"},
    {"z", "SCAN_KEY_z"},
    {"{", "SCAN_KEY_LEFT_BRACKET"},
    {"|", "SCAN_KEY_SPLIT"},
    {"}", "SCAN_KEY_RIGHT_BRACKET"},
    {"~", "SCAN_KEY_TILDE"},
    {"←", "SCAN_KEY_LEFT_ARROW"},
    {"↑", "SCAN_KEY_UP_ARROW"},
    {"→", "SCAN_KEY_RIGHT_ARROW"},
    {"↓", "SCAN_KEY_DOWN_ARROW"},
};

static void write_line(FILE *file, const char *str) {
  fwrite(str, sizeof(char), strlen(str), file);
  fwrite("\n", sizeof(char), 1, file);
}

static void write_bom_head_info(FILE *file) {
  char buffer[] = {(char)0xEF, (char)0xBB, (char)0xBF};
  fwrite(buffer, sizeof(char), sizeof(buffer), file);
}

static bool sort_keyboard_key_name(keyboard_info_t &a, keyboard_info_t &b) {
  if (a.len == 1 || b.len == 1) {
    return *(a.keyboard_key_name) == *(b.keyboard_key_name);
  } else {
    return strcmp(a.keyboard_key_name, b.keyboard_key_name) == 0;
  }
}

int main() {
  FILE *file = NULL;
  FILE *inc_file = NULL;
  list<keyboard_info_t> keyboard_info_list;
  const char *file_path = "../res/keyboard-layout.json";
  const char *inc_file_path = "../src/keyboard/keyboard_key_code_map.inc";

  fopen_s(&file, file_path, "r");
  if (file == NULL) {
    file_path = "./res/keyboard-layout.json";
    inc_file_path = "./src/keyboard/keyboard_key_code_map.inc";
    fopen_s(&file, file_path, "r");
  }

  if (file != NULL) {
    uint32_t len = 0;
    uint32_t read_data_size = 0;
    char *str_keyboard_layout = NULL;

    fseek(file, 0, SEEK_END);
    len = ftell(file);
    fseek(file, 0, SEEK_SET);

    str_keyboard_layout = new char[len];
    read_data_size = fread_s(str_keyboard_layout, len, 1, len, file);
    if (read_data_size == len) {
      uint32_t i = 0, j = 0, max_line_key_size = 0;
      cJSON *json = cJSON_Parse(str_keyboard_layout);
      uint32_t t_line_size = cJSON_GetArraySize(json);

      for (i = 0; i < t_line_size; i++) {
        uint32_t j = 0, line_key_size = 0;
        cJSON *line_json = cJSON_GetArrayItem(json, i);
        uint32_t line_size = cJSON_GetArraySize(line_json);
        for (j = 0; j < line_size; j++) {
          cJSON *key = cJSON_GetArrayItem(line_json, j);
          if (cJSON_IsString(key)) {
            keyboard_info_t info;
            const char *str = cJSON_GetStringValue(key);
            const char *start = str;
            const char *end = NULL;
            if (*str == *g_str_num_lock && strcmp(g_str_num_lock, str) == 0) {
              num_lock_x = j;
              num_lock_y = i;
            }
            do {
              uint32_t l = 0;
              bool is_num = false;
              end = strchr(start, '\n');
              if (end != NULL) {
                l = (uint32_t)(end - start) + 1;
              } else {
                l = (uint32_t)strlen(start) + 1;
              }
              info.len = l - 1;
              if (num_lock_x >= 0 && num_lock_y >= 0 && info.len == 1 && 48 <= *start && *start <= 57) {
                is_num = true;
                l += 4;
                info.len += 4;
                info.keyboard_key_name = new char[l];
                info.keyboard_key_name[l - 1] = 0;
                memcpy(info.keyboard_key_name, start, 1);
                memcpy(info.keyboard_key_name + 1, "_Num", 4);
              } else {
                info.keyboard_key_name = new char[l];
                info.keyboard_key_name[l - 1] = 0;
                memcpy(info.keyboard_key_name, start, l - 1);
              }
              keyboard_info_list.push_back(move(info));
              start = end + 1;
            } while (end != NULL);
          }
        }
      }

      keyboard_info_list.sort();
      keyboard_info_list.erase(unique(keyboard_info_list.begin(), keyboard_info_list.end()), keyboard_info_list.end());

      fopen_s(&inc_file, inc_file_path, "w+");
      if (inc_file != NULL) {
        write_bom_head_info(inc_file);
        write_line(inc_file, "static const scan_key_code_info_t g_keyboard_key_code_map[] = {");
        for (list<keyboard_info_t>::iterator begin = keyboard_info_list.begin(); begin != keyboard_info_list.end(); begin++) {
          char str_info[256] = {0};
          if (*begin->keyboard_key_name == '\"' || *begin->keyboard_key_name == '\\') {
            sprintf_s(str_info, sizeof(str_info), "  {\"\\%s\", },", begin->keyboard_key_name);
          } else {
            uint8_t c = (uint8_t)(*begin->keyboard_key_name);
            const char *str_code = g_keyboard_key_code_relation_table[begin->keyboard_key_name];
            sprintf_s(str_info, sizeof(str_info), "  {\"%s\", %s},", begin->keyboard_key_name, str_code);
          }
          write_line(inc_file, str_info);
        }
        write_line(inc_file, "};");

        uint8_t last_char = 0xFF;
        uint8_t next_char = 0xFF;
        uint32_t jmp_table_id = 0;
        uint32_t jmp_table_size = 0;
        if (SCAN_KEY_CODE_COUNT < (1 << 7)) {
          write_line(inc_file, "static const int8_t g_keyboard_key_code_jmp_table[] = {");
        } else if (SCAN_KEY_CODE_COUNT < (1 << 15)) {
          write_line(inc_file, "static const int16_t g_keyboard_key_code_jmp_table[] = {");
        } else {
          write_line(inc_file, "static const int32_t g_keyboard_key_code_jmp_table[] = {");
        }
        for (list<keyboard_info_t>::iterator iter = keyboard_info_list.begin(); iter != keyboard_info_list.end(); iter++, jmp_table_id++) {
          uint8_t c = *(iter->keyboard_key_name);
          char str_info[32] = {0};
          if (last_char != c) {
            if (c > next_char) {
              for (size_t i = next_char; i < c; i++) {
                sprintf_s(str_info, sizeof(str_info), "  -1,");
                write_line(inc_file, str_info);
              }
            }
            sprintf_s(str_info, sizeof(str_info), "  %d,", jmp_table_id);
            write_line(inc_file, str_info);
            last_char = c;
            next_char = c + 1;
          }
        }
        write_line(inc_file, "};");

        fclose(inc_file);
      }
    }

    for (list<keyboard_info_t>::iterator iter = keyboard_info_list.begin(); iter != keyboard_info_list.end(); iter++) {
      delete[] iter->keyboard_key_name;
    }
    fclose(file);
  }

  return 0;
}
