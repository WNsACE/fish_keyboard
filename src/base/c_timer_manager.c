#include "c_timer_manager.h"

static c_timer_manager_t s_timer_manager;

c_timer_manager_t* c_timer_manager(void) {
  return &s_timer_manager;
}

c_timer_manager_t* c_timer_manager_init(void) {
  memset(&s_timer_manager, 0x0, sizeof(c_timer_manager_t));
  s_timer_manager.timer_info_point = C_TIMER_MANAGER_INVALID_ID;
  return &s_timer_manager;
}

void c_timer_manager_deinit(c_timer_manager_t* timer_manager) {
  memset(&timer_manager, 0x0, sizeof(c_timer_manager_t));
}

uint32_t c_timer_manager_add(c_timer_manager_t* timer_manager, uint32_t duration, c_timer_cb_t cb, void* ctx) {
  uint32_t p = 0, id = 0;
  if (timer_manager == NULL || cb == NULL) {
    return C_TIMER_MANAGER_INVALID_ID;
  }
  if (timer_manager->size < C_TIMER_MANAGER_MAX_SIZE) {
    do {
      p = ++timer_manager->timer_info_point;
      if (timer_manager->timer_info_point == C_TIMER_MANAGER_MAX_SIZE) {
        timer_manager->timer_info_point = p = C_TIMER_MANAGER_INVALID_ID + 1;
      }
      id = p - 1;
      if(timer_manager->timer_infos[id].cb == NULL) {
        timer_manager->timer_infos[id].cb = cb;
        timer_manager->timer_infos[id].ctx = ctx;
        timer_manager->timer_infos[id].duration = duration;
        timer_manager->timer_infos[id].add_time = time_platform_now_ms();
        timer_manager->timer_infos[id].now = timer_manager->timer_infos[id].add_time;
        return p;
      }
    } while (TRUE);
  }
  return C_TIMER_MANAGER_INVALID_ID;
}

c_ret_t c_timer_manager_modify(c_timer_manager_t* timer_manager, uint32_t id, uint32_t duration) {
  if (timer_manager == NULL || id == C_TIMER_MANAGER_INVALID_ID) {
    return C_RET_BAD_PARAMS;
  }
  id--;
  if(timer_manager->timer_infos[id].cb != NULL) {
    timer_manager->timer_infos[id].duration = duration;
  }
  return C_RET_OK;
}

c_ret_t c_timer_manager_remove(c_timer_manager_t* timer_manager, uint32_t id) {
  if (timer_manager == NULL || id == C_TIMER_MANAGER_INVALID_ID) {
    return C_RET_BAD_PARAMS;
  }
  id--;
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
      uint32_t duration = now - time_info->now;
      time_info->now = now;
      if (duration - time_info->duration > 0) {
        time_info->interval = duration;
        if (time_info->cb(time_info) == C_RET_REMOVE) {
          c_timer_manager_remove(timer_manager, i);
        }
      }
    }
  }

  return C_RET_OK;
}

