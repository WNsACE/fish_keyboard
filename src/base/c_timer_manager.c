#include "c_timer_manager.h"

c_timer_manager_t* c_timer_manager_init(c_timer_manager_t* timer_manager) {
  uint32_t i = 0;
  if (timer_manager != NULL) {
    memset(timer_manager, 0x0, sizeof(c_timer_manager_t));
  }
  return timer_manager;
}

uint32_t c_timer_manager_add(c_timer_manager_t* timer_manager, uint32_t duration, c_timer_cb_t cb, void* ctx) {
  uint32_t p = 0;
  if (timer_manager == NULL || cb == NULL) {
    return -1;
  }
  if (timer_manager->size < C_TIMER_MANAGER_MAX_SIZE) {
    do {
      p = timer_manager->timer_info_point++;
      if (timer_manager->timer_info_point == C_TIMER_MANAGER_MAX_SIZE) {
        p = 0;
        timer_manager->timer_info_point = 0;
      }
      if(timer_manager->timer_infos[p].cb == NULL) {
        timer_manager->timer_infos[p].cb = cb;
        timer_manager->timer_infos[p].ctx = ctx;
        timer_manager->timer_infos[p].duration = duration;
        timer_manager->timer_infos[p].start = time_platform_now_ms();
        return p;
      }
    } while (1);
  }
  return -1;
}

c_ret_t c_timer_manager_remove(c_timer_manager_t* timer_manager, uint32_t id) {
  if (timer_manager == NULL) {
    return C_RET_BAD_PARAMS;
  }
  if(timer_manager->timer_infos[id].cb != NULL) {
    memset(&timer_manager->timer_infos[id], 0x0, sizeof(c_timer_info_t));
  }
  return C_RET_OK;
}

c_ret_t c_timer_manager_dispatch_one(c_timer_manager_t* timer_manager) {
  uint32_t i = 0;
  if (timer_manager == NULL) {
    return C_RET_BAD_PARAMS;
  }

  for (i = 0; i < C_TIMER_MANAGER_MAX_SIZE; i++) {
    c_timer_info_t* time_info = timer_manager->timer_infos + i;
    if(time_info->cb != NULL) {
      uint32_t now = time_platform_now_ms();
      uint32_t duration = now - time_info->start;
      if (duration - time_info->duration > 0) {
        time_info->now = now;
        if (time_info->cb(time_info) == C_RET_REMOVE) {
          c_timer_manager_remove(timer_manager, i);
        }
      }
    }
  }

  return C_RET_OK;
}

