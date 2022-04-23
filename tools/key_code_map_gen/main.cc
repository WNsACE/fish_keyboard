#include <stdio.h>
#include <list>
#include <algorithm>
#include "cjson/cJSON.h"
#include "keyboard/scan_key_code.h"

using namespace std;

class keyboard_info_t
{
public:
	char* keyboard_key_name;
	uint32_t len;

	bool operator > (keyboard_info_t info) {
		return strcmp(keyboard_key_name, info.keyboard_key_name) > 0;
	}

	bool operator < (keyboard_info_t info) {
		return strcmp(keyboard_key_name, info.keyboard_key_name) < 0;
	}

	bool operator == (keyboard_info_t info) {
		return strcmp(keyboard_key_name, info.keyboard_key_name) == 0;
	}

};


static int32_t num_lock_x = -1;
static int32_t num_lock_y = -1;
static const char* g_str_num_lock = "Num Lock";

static void write_line(FILE* file, const char* str) {
	fwrite(str, 1, strlen(str), file);
	fwrite("\n", 1, 1, file);
}

static bool sort_keyboard_key_name(keyboard_info_t& a, keyboard_info_t& b) {
	if (a.len == 1 || b.len == 1) {
		return *(a.keyboard_key_name) == *(b.keyboard_key_name);
	}
	else {
		return strcmp(a.keyboard_key_name, b.keyboard_key_name) == 0;
	}
}

int main() {
	FILE* file = NULL;
	FILE* inc_file = NULL;
	list<keyboard_info_t> keyboard_info_list;
	const char* file_path = R"(C:\Users\ACE\Downloads\keyboard-layout.json)";
	const char* inc_file_path = "./keyboard_key_code_map.inc";

	fopen_s(&file, file_path, "r");

	if (file != NULL) {
		uint32_t len = 0;
		uint32_t read_data_size = 0;
		char* str_keyboard_layout = NULL;

		fseek(file, 0, SEEK_END);
		len = ftell(file);
		fseek(file, 0, SEEK_SET);

		str_keyboard_layout = new char[len];
		read_data_size = fread_s(str_keyboard_layout, len, 1, len, file);
		if (read_data_size == len) {
			uint32_t i = 0, j = 0, max_line_key_size = 0;
			cJSON* json = cJSON_Parse(str_keyboard_layout);
			uint32_t t_line_size = cJSON_GetArraySize(json);

			for (i = 0; i < t_line_size; i++) {
				uint32_t j = 0, line_key_size = 0;
				cJSON* line_json = cJSON_GetArrayItem(json, i);
				uint32_t line_size = cJSON_GetArraySize(line_json);
				for (j = 0; j < line_size; j++) {
					cJSON* key = cJSON_GetArrayItem(line_json, j);
					if (cJSON_IsString(key)) {
						keyboard_info_t info;
						const char* str = cJSON_GetStringValue(key);
						const char* start = str;
						const char* end = NULL;
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
							}
							else {
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
							}
							else {
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
				write_line(inc_file, "static const scan_key_code_info_t g_keyboard_key_code_map[] = {");
				for (list<keyboard_info_t>::iterator begin = keyboard_info_list.begin(); begin != keyboard_info_list.end(); begin++) {
					char str_info[256] = { 0 };
					if (*begin->keyboard_key_name == '\"' || *begin->keyboard_key_name == '\\') {
						sprintf_s(str_info, sizeof(str_info), "  {\"\\%s\", },", begin->keyboard_key_name);
					}
					else {
						uint8_t c = (uint8_t)(*begin->keyboard_key_name);
						if (c > 127) {
							char char_info[256] = { 0 };
							for (size_t i = 0; i < begin->len; i++) {
								char tmp_char[10] = { 0 };
								sprintf_s(tmp_char, sizeof(tmp_char), "0x%02x", (uint8_t)(begin->keyboard_key_name[i]));
								if (i == 0) {
									sprintf_s(char_info, sizeof(char_info), " %s", tmp_char);
								} else {
									sprintf_s(char_info, sizeof(char_info), " %s, %s", char_info, tmp_char);
								}
							}
							sprintf_s(str_info, sizeof(str_info), "  { {%s}, },", char_info);
						}
						else {
							sprintf_s(str_info, sizeof(str_info), "  {\"%s\", },", begin->keyboard_key_name);
						}
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
					char str_info[32] = { 0 };
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

