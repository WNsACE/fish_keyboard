#include "c_easing_func.h"

typedef struct _c_easing_func_vt_t {
  c_easing_type_t easing_type;
  c_easing_func_t func;
} c_easing_func_vt_t;




static float c_easing_linear(float k) {
  return k;
}



static const c_easing_func_vt_t easing_func_vt_list[] = {
  {C_EASING_LINEAR, c_easing_linear},
};


c_easing_func_t c_easing_func_from_str(const char* str) {
  uint32_t i = 0;
  for (i = 0; i < C_EASING_TYPE_COUNT; i++) {
    if (*str == *g_easing_type_string_list[i] && strcmp(str, g_easing_type_string_list[i]) == 0) {
      return c_easing_func_from_type((c_easing_type_t)i);
    }
  }
  return NULL;
}

c_easing_func_t c_easing_func_from_type(c_easing_type_t easing_type) {
  uint32_t id = (uint32_t)easing_type;
  if (id < C_EASING_TYPE_COUNT) {
    if (easing_func_vt_list[id].easing_type == easing_type) {
      return easing_func_vt_list[id].func;
    }
  }
  return NULL;
}

