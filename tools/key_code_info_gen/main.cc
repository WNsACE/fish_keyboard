#include <stdio.h>
#include <stdarg.h>
#include "cjson/cJSON.h"
#include "keyboard/scan_keyboard.h"
#include "keyboard/usb_hid_key_code.h"

static void write_line(FILE *file, const char *str) {
  fwrite(str, sizeof(char), strlen(str), file);
}

static void write_printf_line(FILE *file, const char* const format_str, ...) {
  va_list v_l;
  va_start(v_l, format_str);
  vfprintf(file, format_str, v_l);
  va_end(v_l);
}

int main(int argc, char *argv[]) {
  FILE *file = NULL;
  const char *file_path = NULL;
  const char *inc_file_path = "./src/keyboard/keyboard_key_code_data.inc";
  if (argc > 1) {
    file_path = argv[1];
  }
  if (argc > 2) {
    inc_file_path = argv[2];
  }
  if (file_path != NULL) {
    file = fopen(file_path, "r");

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
        scan_keyboard_info_t scan_keyboard_info;
        scan_keyboard_info_t* p_scan_keyboard_info = scan_keyboard_info_init(&scan_keyboard_info, str_keyboard_layout);
        if (p_scan_keyboard_info != NULL) {
          FILE *inc_file = NULL;
          inc_file = fopen(inc_file_path, "w+");
          if (inc_file != NULL) {
            uint32_t i = 0;
            uint32_t size = sizeof(scan_keyboard_info_t);
            uint8_t* buff = (uint8_t*)p_scan_keyboard_info;
            write_printf_line(inc_file, "C_CONST_DATA_ALIGN(const unsigned char %s[]) = {", "g_scan_keyboard_info_data");
            for (i = 0; i < size; i++) {
              if ((i % 16) == 0) {
                write_line(inc_file, "\n");
              }
              write_printf_line(inc_file, "0x%02x,", (int)(buff[i]));
            }
            write_printf_line(inc_file, "};/*%u*/\n", size);
            fclose(inc_file);
          } else {
            printf(" create file : %s fail \r\n", inc_file_path);
          }
        }
      }
      delete[] str_keyboard_layout;
    }

    fclose(file);
  }

  return 0;
}
