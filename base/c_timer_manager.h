﻿#ifndef __C_TIMER_MANAGER_H__
#define __C_TIMER_MANAGER_H__

#include "c_types_def.h"
#include "c_list.h"

BEGIN_C_DECLS

#ifndef C_TIMER_MANAGER_MAX_SIZE
#define C_TIMER_MANAGER_MAX_SIZE  128
#endif

struct _c_timer_info_t;

typedef c_ret_t(*c_timer_cb_t)(struct _c_timer_info_t* timer_info);

typedef struct _c_timer_info_t {
  uint32_t id;
  uint32_t now;
  uint32_t start;
  uint32_t duration;

  void* ctx;
  c_timer_cb_t cb;
} c_timer_info_t;


typedef struct _c_timer_manager_t {
  uint32_t size;
  uint32_t timer_info_point;
  c_timer_info_t timer_infos[C_TIMER_MANAGER_MAX_SIZE];
} c_timer_manager_t;


c_timer_manager_t* c_timer_manager_init(c_timer_manager_t* timer_manager);

uint32_t c_timer_manager_add(c_timer_manager_t* timer_manager, uint32_t duration, c_timer_cb_t cb, void* ctx);

c_ret_t c_timer_manager_remove(c_timer_manager_t* timer_manager, uint32_t id);

c_ret_t c_timer_manager_dispatch_one(c_timer_manager_t* timer_manager);

END_C_DECLS

#endif
