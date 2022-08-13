#include <map>
#include <list>
#include <string>
#include <stdio.h>
#include <algorithm>
#include "cjson/cJSON.h"
#include "keyboard/usb_hid_key_code.h"

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
    {"", "USB_HID_KEY_CODE_SPACE"},
    {"!", "USB_HID_KEY_CODE_EXCLAIM"},
    {"\"", "USB_HID_KEY_CODE_APOSTROPHES"},
    {"#", "USB_HID_KEY_CODE_HASH"},
    {"$", "USB_HID_KEY_CODE_DOLLAR"},
    {"%", "USB_HID_KEY_CODE_PERCENT"},
    {"&", "USB_HID_KEY_CODE_AMPERSAND"},
    {"'", "USB_HID_KEY_CODE_APOSTROPHE"},
    {"(", "USB_HID_KEY_CODE_LEFTPAREN"},
    {")", "USB_HID_KEY_CODE_RIGHTPAREN"},
    {"*", "USB_HID_KEY_CODE_ASTERISK"},
    {"+", "USB_HID_KEY_CODE_PLUS"},
    {",", "USB_HID_KEY_CODE_COMMA"},
    {"-", "USB_HID_KEY_CODE_MINUS"},
    {".", "USB_HID_KEY_CODE_PERIOD"},
    {"/", "USB_HID_KEY_CODE_SLASH"},
    {"0", "USB_HID_KEY_CODE_0"},
    {"0_Num", "USB_HID_KEY_CODE_KP_0"},
    {"1", "USB_HID_KEY_CODE_1"},
    {"1_Num", "USB_HID_KEY_CODE_KP_1"},
    {"2", "USB_HID_KEY_CODE_2"},
    {"2_Num", "USB_HID_KEY_CODE_KP_2"},
    {"3", "USB_HID_KEY_CODE_3"},
    {"3_Num", "USB_HID_KEY_CODE_KP_3"},
    {"4", "USB_HID_KEY_CODE_4"},
    {"4_Num", "USB_HID_KEY_CODE_KP_4"},
    {"5", "USB_HID_KEY_CODE_5"},
    {"5_Num", "USB_HID_KEY_CODE_KP_5"},
    {"6", "USB_HID_KEY_CODE_6"},
    {"6_Num", "USB_HID_KEY_CODE_KP_6"},
    {"7", "USB_HID_KEY_CODE_7"},
    {"7_Num", "USB_HID_KEY_CODE_KP_7"},
    {"8", "USB_HID_KEY_CODE_8"},
    {"8_Num", "USB_HID_KEY_CODE_KP_8"},
    {"9", "USB_HID_KEY_CODE_9"},
    {"9_Num", "USB_HID_KEY_CODE_KP_9"},
    {":", "USB_HID_KEY_CODE_COLON"},
    {";", "USB_HID_KEY_CODE_SEMICOLON"},
    {"<", "USB_HID_KEY_CODE_LESS"},
    {"=", "USB_HID_KEY_CODE_EQUALS"},
    {">", "USB_HID_KEY_CODE_GREATER"},
    {"?", "USB_HID_KEY_CODE_QUESTION"},
    {"@", "USB_HID_KEY_CODE_AT"},
    {"A", "USB_HID_KEY_CODE_A"},
    {"Alt", "USB_HID_KEY_CODE_ALT"},
    {"B", "USB_HID_KEY_CODE_B"},
    {"Backspace", "USB_HID_KEY_CODE_BACKSPACE"},
    {"Break", "USB_HID_KEY_CODE_PAUSE"},
    {"C", "USB_HID_KEY_CODE_C"},
    {"Caps Lock", "USB_HID_KEY_CODE_CAPSLOCK"},
    {"Ctrl", "USB_HID_KEY_CODE_CTRL"},
    {"D", "USB_HID_KEY_CODE_D"},
    {"Del", "USB_HID_KEY_CODE_DELETE"},
    {"Delete", "USB_HID_KEY_CODE_DELETE"},
    {"E", "USB_HID_KEY_CODE_E"},
    {"End", "USB_HID_KEY_CODE_END"},
    {"Enter", "USB_HID_KEY_CODE_RETURN"},
    {"Esc", "USB_HID_KEY_CODE_ESCAPE"},
    {"F", "USB_HID_KEY_CODE_F"},
    {"F1", "USB_HID_KEY_CODE_F1"},
    {"F10", "USB_HID_KEY_CODE_F10"},
    {"F11", "USB_HID_KEY_CODE_F11"},
    {"F12", "USB_HID_KEY_CODE_F12"},
    {"F2", "USB_HID_KEY_CODE_F2"},
    {"F3", "USB_HID_KEY_CODE_F3"},
    {"F4", "USB_HID_KEY_CODE_F4"},
    {"F5", "USB_HID_KEY_CODE_F5"},
    {"F6", "USB_HID_KEY_CODE_F6"},
    {"F7", "USB_HID_KEY_CODE_F7"},
    {"F8", "USB_HID_KEY_CODE_F8"},
    {"F9", "USB_HID_KEY_CODE_F9"},
    {"FN", "USB_HID_KEY_CODE_FN"},
    {"G", "USB_HID_KEY_CODE_G"},
    {"H", "USB_HID_KEY_CODE_H"},
    {"Home", "USB_HID_KEY_CODE_HOME"},
    {"I", "USB_HID_KEY_CODE_I"},
    {"Ins", "USB_HID_KEY_CODE_INSERT"},
    {"Insert", "USB_HID_KEY_CODE_INSERT"},
    {"J", "USB_HID_KEY_CODE_J"},
    {"K", "USB_HID_KEY_CODE_K"},
    {"L", "USB_HID_KEY_CODE_L"},
    {"M", "USB_HID_KEY_CODE_M"},
    {"Menu", "USB_HID_KEY_CODE_APPLICATION"},//USB_HID_KEY_CODE_MENU
    {"N", "USB_HID_KEY_CODE_N"},
    {"Num Lock", "USB_HID_KEY_CODE_NUMLOCKCLEAR"},
    {"O", "USB_HID_KEY_CODE_O"},
    {"P", "USB_HID_KEY_CODE_P"},
    {"Pause", "USB_HID_KEY_CODE_PAUSE"},
    {"PgDn", "USB_HID_KEY_CODE_PAGEDOWN"},
    {"PgUp", "USB_HID_KEY_CODE_PAGEUP"},
    {"PrtSc", "USB_HID_KEY_CODE_PRINTSCREEN"},
    {"Q", "USB_HID_KEY_CODE_Q"},
    {"R", "USB_HID_KEY_CODE_R"},
    {"S", "USB_HID_KEY_CODE_S"},
    {"Scroll Lock", "USB_HID_KEY_CODE_SCROLLLOCK"},
    {"Shift", "USB_HID_KEY_CODE_SHIFT"},
    {"T", "USB_HID_KEY_CODE_T"},
    {"Tab", "USB_HID_KEY_CODE_TAB"},
    {"U", "USB_HID_KEY_CODE_U"},
    {"V", "USB_HID_KEY_CODE_V"},
    {"W", "USB_HID_KEY_CODE_W"},
    {"Win", "USB_HID_KEY_CODE_GUI"},
    {"X", "USB_HID_KEY_CODE_X"},
    {"Y", "USB_HID_KEY_CODE_Y"},
    {"Z", "USB_HID_KEY_CODE_Z"},
    {"[", "USB_HID_KEY_CODE_LEFTBRACKET"},
    {"\\", "USB_HID_KEY_CODE_BACKSLASH"},
    {"]", "USB_HID_KEY_CODE_RIGHTBRACKET"},
    {"^", "USB_HID_KEY_CODE_CARET"},
    {"_", "USB_HID_KEY_CODE_UNDERSCORE"},
    {"`", "USB_HID_KEY_CODE_NONUSHASH"},
    {"a", "USB_HID_KEY_CODE_a"},
    {"b", "USB_HID_KEY_CODE_b"},
    {"c", "USB_HID_KEY_CODE_c"},
    {"d", "USB_HID_KEY_CODE_d"},
    {"e", "USB_HID_KEY_CODE_e"},
    {"f", "USB_HID_KEY_CODE_f"},
    {"g", "USB_HID_KEY_CODE_g"},
    {"h", "USB_HID_KEY_CODE_h"},
    {"i", "USB_HID_KEY_CODE_i"},
    {"j", "USB_HID_KEY_CODE_j"},
    {"k", "USB_HID_KEY_CODE_k"},
    {"l", "USB_HID_KEY_CODE_l"},
    {"m", "USB_HID_KEY_CODE_m"},
    {"n", "USB_HID_KEY_CODE_n"},
    {"o", "USB_HID_KEY_CODE_o"},
    {"p", "USB_HID_KEY_CODE_p"},
    {"q", "USB_HID_KEY_CODE_q"},
    {"r", "USB_HID_KEY_CODE_r"},
    {"s", "USB_HID_KEY_CODE_s"},
    {"t", "USB_HID_KEY_CODE_t"},
    {"u", "USB_HID_KEY_CODE_u"},
    {"v", "USB_HID_KEY_CODE_v"},
    {"w", "USB_HID_KEY_CODE_w"},
    {"x", "USB_HID_KEY_CODE_x"},
    {"y", "USB_HID_KEY_CODE_y"},
    {"z", "USB_HID_KEY_CODE_z"},
    {"{", "USB_HID_KEY_CODE_LEFTBRACKET"},
    {"|", "USB_HID_KEY_CODE_BACKSLASH"},
    {"}", "USB_HID_KEY_CODE_RIGHTBRACKET"},
    {"~", "USB_HID_KEY_CODE_NONUSHASH"},
    {"←", "USB_HID_KEY_CODE_LEFT"},
    {"↑", "USB_HID_KEY_CODE_UP"},
    {"→", "USB_HID_KEY_CODE_RIGHT"},
    {"↓", "USB_HID_KEY_CODE_DOWN"},
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

  file = fopen(file_path, "r");
  if (file == NULL) {
    file_path = "./res/keyboard-layout.json";
    inc_file_path = "./src/keyboard/keyboard_key_code_map.inc";
    file = fopen(file_path, "r");
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
              if (find(keyboard_info_list.begin(), keyboard_info_list.end(), move(info)) != keyboard_info_list.end()) {
                delete[] info.keyboard_key_name;
              } else {
                keyboard_info_list.push_back(move(info));
              }
              start = end + 1;
            } while (end != NULL);
          }
        }
      }

      cJSON_Delete(json);
      keyboard_info_list.sort();

      inc_file = fopen(inc_file_path, "w+");
      if (inc_file != NULL) {
        write_bom_head_info(inc_file);
        write_line(inc_file, "#ifndef __KEYBOARD_KEY_CODE_MAP_INC__");
        write_line(inc_file, "#define __KEYBOARD_KEY_CODE_MAP_INC__\n");

        write_line(inc_file, "static const usb_hid_key_code_info_t g_keyboard_key_code_map[] = {");
        for (list<keyboard_info_t>::iterator begin = keyboard_info_list.begin(); begin != keyboard_info_list.end(); begin++) {
          char str_info[256] = {0};
          const char *str_code = g_keyboard_key_code_relation_table[begin->keyboard_key_name];
          if (*begin->keyboard_key_name == '\"' || *begin->keyboard_key_name == '\\') {
            sprintf_s(str_info, sizeof(str_info), "  {\"\\%s\", %s},", begin->keyboard_key_name, str_code);
          } else {
            sprintf_s(str_info, sizeof(str_info), "  {\"%s\", %s},", begin->keyboard_key_name, str_code);
          }
          write_line(inc_file, str_info);
        }
        write_line(inc_file, "};");

        uint8_t last_char = 0xFF;
        uint8_t next_char = 0xFF;
        uint32_t jmp_table_id = 0;
        uint32_t jmp_table_size = 0;
        if (USB_HID_KEY_CODE_COUNT < (1 << 7)) {
          write_line(inc_file, "static const int8_t g_keyboard_key_code_jmp_table[] = {");
        } else if (USB_HID_KEY_CODE_COUNT < (1 << 15)) {
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
        write_line(inc_file, "\n#endif");

        fclose(inc_file);
      }
    }

    for (list<keyboard_info_t>::iterator iter = keyboard_info_list.begin(); iter != keyboard_info_list.end(); iter++) {
      delete[] iter->keyboard_key_name;
    }
    fclose(file);

    delete[] str_keyboard_layout;
  }

  return 0;
}
