#include "gtest/gtest.h"
#include "keyboard/scan_keyboard.h"
#include "keyboard_key_code_data.inc"

#if defined(WIN32)
#include <Windows.h>
#define sleep_ms(ms) Sleep(ms)
#else defined(__unix)
#include <unistd.h>
#include <sys/time.h>
#define sleep_ms() usleep(ms)
#endif

uint8_t key_map[SCAN_KEYBOARD_LAYOUT_MAX_NUMBER][SCAN_KEYBOARD_LINE_MAX_SIZE][SCAN_KEYBOARD_LINE_KEY_MAX_SIZE];

static c_bool_t dummy_keyboard_get_scan_keys(uint32_t number_line, uint8_t* key_list, uint32_t* key_list_size) {
  *key_list_size = min(*key_list_size, SCAN_KEYBOARD_LINE_KEY_MAX_SIZE);
  memcpy(key_list, key_map[0][number_line], *key_list_size);
  return TRUE;
}

TEST(scan_keyboard, create) {
#define CHECK_SPECIAL_KEY_POINT(scan_keyboard_manager, name, x, y) {                \
  ASSERT_EQ(scan_keyboard_manager->info->##name##_x, x);                            \
  ASSERT_EQ(scan_keyboard_manager->info->##name##_y, y);                            \
}

	scan_keyboard_t* scan_keyboard_manager = scan_keyboard_create((scan_keyboard_info_t*)g_scan_keyboard_info_data, dummy_keyboard_get_scan_keys);
  ASSERT_EQ(scan_keyboard_manager != NULL, true);

  CHECK_SPECIAL_KEY_POINT(scan_keyboard_manager, left_shift, 0, 4);
  CHECK_SPECIAL_KEY_POINT(scan_keyboard_manager, right_shift, 11, 4);

  CHECK_SPECIAL_KEY_POINT(scan_keyboard_manager, left_alt, 2, 5);
  CHECK_SPECIAL_KEY_POINT(scan_keyboard_manager, right_alt, 4, 5);

  CHECK_SPECIAL_KEY_POINT(scan_keyboard_manager, left_gui, 1, 5);
  // CHECK_SPECIAL_KEY_POINT(scan_keyboard_manager, right_gui, 5, 5);
  CHECK_SPECIAL_KEY_POINT(scan_keyboard_manager, fn, 5, 5);

  CHECK_SPECIAL_KEY_POINT(scan_keyboard_manager, left_ctrl, 0, 5);
  CHECK_SPECIAL_KEY_POINT(scan_keyboard_manager, right_ctrl, 7, 5);

  for (uint32_t i = 0; i < SCAN_KEYBOARD_LINE_MAX_SIZE; i++) {
    for (uint32_t j = 0; j < SCAN_KEYBOARD_LINE_KEY_MAX_SIZE; j++) {
      uint8_t keyboard[8] = {0};
      memset(key_map, 0x0, sizeof(key_map));
      key_map[0][i][j] = TRUE;
      scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
      if (scan_keyboard_manager->is_left_ctrl) {
        ASSERT_EQ(scan_keyboard_manager->info->key_map[0][i][j], USB_HID_KEY_CODE_LCTRL);
        scan_keyboard_manager->is_left_ctrl = FALSE;
      } else if (scan_keyboard_manager->is_left_shift) {
        ASSERT_EQ(scan_keyboard_manager->info->key_map[0][i][j], USB_HID_KEY_CODE_LSHIFT);
        scan_keyboard_manager->is_left_shift = FALSE;
      } else if (scan_keyboard_manager->is_left_alt) {
        ASSERT_EQ(scan_keyboard_manager->info->key_map[0][i][j], USB_HID_KEY_CODE_LALT);
        scan_keyboard_manager->is_left_alt = FALSE;
      } else if (scan_keyboard_manager->is_left_gui) {
        ASSERT_EQ(scan_keyboard_manager->info->key_map[0][i][j], USB_HID_KEY_CODE_LGUI);
        scan_keyboard_manager->is_left_gui = FALSE;
      } else if (scan_keyboard_manager->is_right_ctrl) {
        ASSERT_EQ(scan_keyboard_manager->info->key_map[0][i][j], USB_HID_KEY_CODE_RCTRL);
        scan_keyboard_manager->is_right_ctrl = FALSE;
      } else if (scan_keyboard_manager->is_right_shift) {
        ASSERT_EQ(scan_keyboard_manager->info->key_map[0][i][j], USB_HID_KEY_CODE_RSHIFT);
        scan_keyboard_manager->is_right_shift = FALSE;
      } else if (scan_keyboard_manager->is_right_alt) {
        ASSERT_EQ(scan_keyboard_manager->info->key_map[0][i][j], USB_HID_KEY_CODE_RALT);
        scan_keyboard_manager->is_right_alt = FALSE;
      } else if (scan_keyboard_manager->is_right_gui) {
        ASSERT_EQ(scan_keyboard_manager->info->key_map[0][i][j], USB_HID_KEY_CODE_RGUI);
        scan_keyboard_manager->is_right_gui = FALSE;
      } else if (scan_keyboard_manager->is_fn) {
        ASSERT_EQ(scan_keyboard_manager->info->key_map[0][i][j], USB_HID_KEY_CODE_FN);
        scan_keyboard_manager->is_fn = FALSE;
      } else {
        ASSERT_EQ(scan_keyboard_manager->info->key_map[0][i][j], keyboard[2]);
      }
    }
  }
  
  scan_keyboard_destroy(scan_keyboard_manager);
}


TEST(scan_keyboard, special_key) {
	scan_keyboard_t* scan_keyboard_manager = scan_keyboard_create((scan_keyboard_info_t*)g_scan_keyboard_info_data, dummy_keyboard_get_scan_keys);
  ASSERT_EQ(scan_keyboard_manager != NULL, true);

  uint8_t keyboard[8] = {0};

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  
  ASSERT_EQ(scan_keyboard_manager->is_left_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_gui == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_right_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_shift == FALSE, true);

  for (uint32_t i = 0; i < ARRAY_SIZE(keyboard); i++) {
    ASSERT_EQ(keyboard[i], 0x0);
  }

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  key_map[0][5][5] = TRUE;

  key_map[0][4][0] = TRUE;
  key_map[0][4][11] = TRUE;
  key_map[0][5][0] = TRUE;
  key_map[0][5][1] = TRUE;
  key_map[0][5][2] = TRUE;
  key_map[0][5][4] = TRUE;
  key_map[0][5][7] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(scan_keyboard_manager->is_fn == TRUE, true);

  ASSERT_EQ(scan_keyboard_manager->is_left_alt == TRUE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_ctrl == TRUE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_gui == TRUE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_shift == TRUE, true);

  ASSERT_EQ(scan_keyboard_manager->is_right_alt == TRUE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_ctrl == TRUE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_shift == TRUE, true);

  ASSERT_EQ(keyboard[0], 0x7F);
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], 0x0);
  ASSERT_EQ(keyboard[3], 0x0);
  ASSERT_EQ(keyboard[4], 0x0);
  ASSERT_EQ(keyboard[5], 0x0);
  ASSERT_EQ(keyboard[6], 0x0);
  ASSERT_EQ(keyboard[7], 0x0);

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  
  ASSERT_EQ(scan_keyboard_manager->is_left_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_shift == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_right_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_shift == FALSE, true);

  for (uint32_t i = 0; i < ARRAY_SIZE(keyboard); i++) {
    ASSERT_EQ(keyboard[i], 0x0);
  }

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  key_map[0][4][0] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(scan_keyboard_manager->is_fn == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_left_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_shift == TRUE, true);

  ASSERT_EQ(scan_keyboard_manager->is_right_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_shift == FALSE, true);

  ASSERT_EQ(keyboard[0], (1 << 1));
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], 0x0);
  ASSERT_EQ(keyboard[3], 0x0);
  ASSERT_EQ(keyboard[4], 0x0);
  ASSERT_EQ(keyboard[5], 0x0);
  ASSERT_EQ(keyboard[6], 0x0);
  ASSERT_EQ(keyboard[7], 0x0);

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);

  key_map[0][4][11] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(scan_keyboard_manager->is_fn == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_left_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_shift == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_right_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_shift == TRUE, true);

  ASSERT_EQ(keyboard[0], (1 << 5));
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], 0x0);
  ASSERT_EQ(keyboard[3], 0x0);
  ASSERT_EQ(keyboard[4], 0x0);
  ASSERT_EQ(keyboard[5], 0x0);
  ASSERT_EQ(keyboard[6], 0x0);
  ASSERT_EQ(keyboard[7], 0x0);

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  
  key_map[0][5][0] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(scan_keyboard_manager->is_fn == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_left_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_ctrl == TRUE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_shift == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_right_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_shift == FALSE, true);

  ASSERT_EQ(keyboard[0], (1 << 0));
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], 0x0);
  ASSERT_EQ(keyboard[3], 0x0);
  ASSERT_EQ(keyboard[4], 0x0);
  ASSERT_EQ(keyboard[5], 0x0);
  ASSERT_EQ(keyboard[6], 0x0);
  ASSERT_EQ(keyboard[7], 0x0);

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);

  key_map[0][5][1] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(scan_keyboard_manager->is_fn == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_left_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_gui == TRUE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_shift == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_right_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_shift == FALSE, true);

  ASSERT_EQ(keyboard[0], (1 << 3));
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], 0x0);
  ASSERT_EQ(keyboard[3], 0x0);
  ASSERT_EQ(keyboard[4], 0x0);
  ASSERT_EQ(keyboard[5], 0x0);
  ASSERT_EQ(keyboard[6], 0x0);
  ASSERT_EQ(keyboard[7], 0x0);

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  
  key_map[0][5][2] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(scan_keyboard_manager->is_fn == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_left_alt == TRUE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_shift == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_right_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_shift == FALSE, true);

  ASSERT_EQ(keyboard[0], (1 << 2));
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], 0x0);
  ASSERT_EQ(keyboard[3], 0x0);
  ASSERT_EQ(keyboard[4], 0x0);
  ASSERT_EQ(keyboard[5], 0x0);
  ASSERT_EQ(keyboard[6], 0x0);
  ASSERT_EQ(keyboard[7], 0x0);

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  
  key_map[0][5][4] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(scan_keyboard_manager->is_fn == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_left_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_shift == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_right_alt == TRUE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_shift == FALSE, true);

  ASSERT_EQ(keyboard[0], (1 << 6));
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], 0x0);
  ASSERT_EQ(keyboard[3], 0x0);
  ASSERT_EQ(keyboard[4], 0x0);
  ASSERT_EQ(keyboard[5], 0x0);
  ASSERT_EQ(keyboard[6], 0x0);
  ASSERT_EQ(keyboard[7], 0x0);

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  
  key_map[0][5][5] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(scan_keyboard_manager->is_fn == TRUE, true);

  ASSERT_EQ(scan_keyboard_manager->is_left_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_shift == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_right_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_shift == FALSE, true);

  ASSERT_EQ(keyboard[0], 0x0);
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], 0x0);
  ASSERT_EQ(keyboard[3], 0x0);
  ASSERT_EQ(keyboard[4], 0x0);
  ASSERT_EQ(keyboard[5], 0x0);
  ASSERT_EQ(keyboard[6], 0x0);
  ASSERT_EQ(keyboard[7], 0x0);

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  
  key_map[0][5][7] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(scan_keyboard_manager->is_fn == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_left_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_ctrl == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_shift == FALSE, true);

  ASSERT_EQ(scan_keyboard_manager->is_right_alt == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_ctrl == TRUE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_gui == FALSE, true);
  ASSERT_EQ(scan_keyboard_manager->is_right_shift == FALSE, true);

  ASSERT_EQ(keyboard[0], (1 << 4));
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], 0x0);
  ASSERT_EQ(keyboard[3], 0x0);
  ASSERT_EQ(keyboard[4], 0x0);
  ASSERT_EQ(keyboard[5], 0x0);
  ASSERT_EQ(keyboard[6], 0x0);
  ASSERT_EQ(keyboard[7], 0x0);

  scan_keyboard_destroy(scan_keyboard_manager);
}

TEST(scan_keyboard, full_6key) {
	scan_keyboard_t* scan_keyboard_manager = scan_keyboard_create((scan_keyboard_info_t*)g_scan_keyboard_info_data, dummy_keyboard_get_scan_keys);
  ASSERT_EQ(scan_keyboard_manager != NULL, true);

  uint8_t keyboard[8] = {0};
  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  for (uint32_t i = 0; i < ARRAY_SIZE(keyboard); i++) {
    ASSERT_EQ(keyboard[i], 0x0);
  }
  
  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  key_map[0][0][0] = TRUE;
  key_map[0][0][1] = TRUE;
  key_map[0][0][2] = TRUE;
  key_map[0][0][3] = TRUE;
  key_map[0][0][4] = TRUE;
  key_map[0][0][5] = TRUE;
  key_map[0][0][6] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(keyboard[0], 0x0);
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], USB_HID_KEY_CODE_ESCAPE);
  ASSERT_EQ(keyboard[3], USB_HID_KEY_CODE_F1);
  ASSERT_EQ(keyboard[4], USB_HID_KEY_CODE_F2);
  ASSERT_EQ(keyboard[5], USB_HID_KEY_CODE_F3);
  ASSERT_EQ(keyboard[6], USB_HID_KEY_CODE_F4);
  ASSERT_EQ(keyboard[7], USB_HID_KEY_CODE_F5);

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  for (uint32_t i = 0; i < ARRAY_SIZE(keyboard); i++) {
    ASSERT_EQ(keyboard[i], 0x0);
  }
  
  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  key_map[0][0][0] = TRUE;
  key_map[0][0][1] = TRUE;
  key_map[0][0][2] = TRUE;
  key_map[0][0][3] = TRUE;
  key_map[0][0][4] = TRUE;
  key_map[0][0][5] = TRUE;
  key_map[0][0][6] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(keyboard[0], 0x0);
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], USB_HID_KEY_CODE_ESCAPE);
  ASSERT_EQ(keyboard[3], USB_HID_KEY_CODE_F1);
  ASSERT_EQ(keyboard[4], USB_HID_KEY_CODE_F2);
  ASSERT_EQ(keyboard[5], USB_HID_KEY_CODE_F3);
  ASSERT_EQ(keyboard[6], USB_HID_KEY_CODE_F4);
  ASSERT_EQ(keyboard[7], USB_HID_KEY_CODE_F5);

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  key_map[0][0][1] = TRUE;
  key_map[0][0][2] = TRUE;
  key_map[0][0][3] = TRUE;
  key_map[0][0][4] = TRUE;
  key_map[0][0][5] = TRUE;
  key_map[0][0][6] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(keyboard[0], 0x0);
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], USB_HID_KEY_CODE_F1);
  ASSERT_EQ(keyboard[3], USB_HID_KEY_CODE_F2);
  ASSERT_EQ(keyboard[4], USB_HID_KEY_CODE_F3);
  ASSERT_EQ(keyboard[5], USB_HID_KEY_CODE_F4);
  ASSERT_EQ(keyboard[6], USB_HID_KEY_CODE_F5);
  ASSERT_EQ(keyboard[7], USB_HID_KEY_CODE_F6);

  memset(key_map, 0x0, sizeof(key_map));
  memset(keyboard, 0x0, sizeof(keyboard));
  key_map[0][0][1] = TRUE;
  key_map[0][0][2] = TRUE;
  key_map[0][0][3] = TRUE;
  key_map[0][0][4] = TRUE;
  key_map[0][0][5] = TRUE;
  key_map[0][0][6] = TRUE;

  key_map[0][4][0] = TRUE;
  key_map[0][5][0] = TRUE;
  scan_keyboard_get_usb_keyboard_code(scan_keyboard_manager, keyboard);
  ASSERT_EQ(scan_keyboard_manager->is_left_ctrl == TRUE, true);
  ASSERT_EQ(scan_keyboard_manager->is_left_shift == TRUE, true);
  ASSERT_EQ(keyboard[0], (1 << 0) | (1 << 1));
  ASSERT_EQ(keyboard[1], 0x0);
  ASSERT_EQ(keyboard[2], USB_HID_KEY_CODE_F1);
  ASSERT_EQ(keyboard[3], USB_HID_KEY_CODE_F2);
  ASSERT_EQ(keyboard[4], USB_HID_KEY_CODE_F3);
  ASSERT_EQ(keyboard[5], USB_HID_KEY_CODE_F4);
  ASSERT_EQ(keyboard[6], USB_HID_KEY_CODE_F5);
  ASSERT_EQ(keyboard[7], USB_HID_KEY_CODE_F6);

  scan_keyboard_destroy(scan_keyboard_manager);
}
