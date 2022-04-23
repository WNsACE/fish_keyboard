#ifndef __C_EASING_FUNC_H__
#define __C_EASING_FUNC_H__

#include "c_types_def.h"


BEGIN_C_DECLS

typedef float (*c_easing_func_t)(float k);

typedef enum _c_easing_type_t {
  C_EASING_LINEAR = 0,

  C_EASING_TYPE_COUNT
} c_easing_type_t;

static const char* g_easing_type_string_list[C_EASING_TYPE_COUNT] = { "linear" };


c_easing_func_t c_easing_func_from_str(const char* str);
c_easing_func_t c_easing_func_from_type(c_easing_type_t easing_type);

END_C_DECLS

#endif
