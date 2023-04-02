#ifndef __C_TYPES_DEF_H__
#define __C_TYPES_DEF_H__

#include <stdint.h>
#include <assert.h>
#include <string.h>

#ifdef FISH_KEYBOARD_CONFIG_H
#include "fish_keyboard_config.h"
#else
#include "../fish_keyboard_config_sample.h"
#endif

#ifndef c_bool_t
#define c_bool_t uint8_t
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#endif /*ARRAY_SIZE*/

#define c_min(a, b) ((a) < (b) ? (a) : (b))
#define c_abs(a) ((a) < (0) ? (-(a)) : (a))
#define c_max(a, b) ((a) > (b) ? (a) : (b))
#define c_roundi(a) (int32_t)(((a) >= 0) ? ((a) + 0.5f) : ((a)-0.5f))
#define c_clamp(a, mn, mx) ((a) < (mn) ? (mn) : ((a) > (mx) ? (mx) : (a)))
#define c_clampi(a, mn, mx) (int32_t)((a) < (mn) ? (mn) : ((a) > (mx) ? (mx) : (a)))

#define C_UNUSED(X) (void)X                             /* To avoid gcc/g++ warnings */

#ifdef __cplusplus
#ifndef BEGIN_C_DECLS
#define BEGIN_C_DECLS extern "C" {
#endif
#ifndef END_C_DECLS
#define END_C_DECLS }
#endif
#else
#ifndef BEGIN_C_DECLS
#define BEGIN_C_DECLS
#endif
#ifndef END_C_DECLS
#define END_C_DECLS
#endif
#endif

#ifdef WITH_STD

#ifndef C_MALLOC
#define C_MALLOC malloc
#endif

#ifndef C_CALLOC
#define C_CALLOC calloc
#endif

#ifndef C_REALLOC
#define C_REALLOC realloc
#endif

#ifndef C_FREE
#define C_FREE free
#endif

#else 

#ifndef C_MALLOC
#define C_MALLOC
#endif

#ifndef C_CALLOC
#define C_CALLOC
#endif

#ifndef C_REALLOC
#define C_REALLOC
#endif

#ifndef C_FREE
#define C_FREE
#endif

#endif

#ifdef _MSC_VER
#define C_CONST_DATA_ALIGN(v) __declspec(align(8)) v
#else
#define C_CONST_DATA_ALIGN(v) v __attribute__((aligned(8)))
#endif /*_MSC_VER*/

typedef enum _c_ret_t {
  C_RET_OK = 0,
  C_RET_FAIL,
  C_RET_OOM,
  C_RET_BAD_PARAMS,
  C_RET_REMOVE,
  C_RET_REPEAT,
} c_ret_t;


typedef void(*c_foreach_cb_t)(void* data, void* ctx);


uint64_t time_platform_now_ms(void);

#endif
