#include "gtest/gtest.h"
#include "base/c_timer_manager.h"
#include <stdio.h>
#include <time.h>

typedef struct _c_info_t {
  uint64_t begin;
  uint64_t end;
  uint32_t duration;
  uint32_t number;
  uint32_t interval;
} c_info_t;

#if defined(WIN32)
#include <Windows.h>
#define sleep_ms(ms) Sleep(ms)
#else defined(__unix)
#include <unistd.h>
#include <sys/time.h>
#define sleep_ms() usleep(ms)
#endif

TEST(c_timer_manager, init) {
  c_timer_manager_t* timer_manager = c_timer_manager_init();
  ASSERT_EQ(timer_manager != NULL, true);
  c_timer_manager_deinit(timer_manager);
}

static c_ret_t timer_manager_test_cb0(struct _c_timer_info_t* timer_info) {
  c_info_t* info = (c_info_t*)(timer_info->ctx);
  info->end = time_platform_now_ms();
  info->interval = timer_info->interval;
  info->number++;
  return C_RET_OK;
}

TEST(c_timer_manager, add) {
#define SLEEP_INTERVAL_TIME         10

  c_info_t info;
  c_timer_manager_t* timer_manager = c_timer_manager_init();
  ASSERT_EQ(timer_manager != NULL, true);

#if defined(WIN32)
  timeBeginPeriod(1);
#endif
  memset(&info, 0x0, sizeof(c_info_t));
  info.duration = 40;
  info.begin = time_platform_now_ms();
  uint32_t id = c_timer_manager_add(timer_manager, info.duration, timer_manager_test_cb0, &info);
  ASSERT_NE(id, C_TIMER_MANAGER_INVALID_ID);
  
  for (uint32_t i = 0; i < 100; i++) {
    c_timer_manager_dispatch_one(timer_manager);
    Sleep(SLEEP_INTERVAL_TIME);
  }
  
  ASSERT_EQ(info.number, 1);
  ASSERT_LE(info.interval, SLEEP_INTERVAL_TIME * 2);
  ASSERT_LE((uint32_t)(info.end - info.begin) - info.duration, 10);

  c_timer_manager_deinit(timer_manager);

#if defined(WIN32)
  timeEndPeriod(1);
#endif
}

TEST(c_timer_manager, remove) {
  c_info_t info1;
  c_info_t info2;
  c_timer_manager_t* timer_manager = c_timer_manager_init();
  ASSERT_EQ(timer_manager != NULL, true);

#if defined(WIN32)
  timeBeginPeriod(1);
#endif

  memset(&info1, 0x0, sizeof(c_info_t));
  memset(&info2, 0x0, sizeof(c_info_t));

  info1.duration = 40;
  info1.begin = time_platform_now_ms();

  uint32_t id1 = c_timer_manager_add(timer_manager, info1.duration, timer_manager_test_cb0, &info1);
  ASSERT_NE(id1, C_TIMER_MANAGER_INVALID_ID);

  info2.duration = 40;
  info2.begin = time_platform_now_ms();

  uint32_t id2 = c_timer_manager_add(timer_manager, info2.duration, timer_manager_test_cb0, &info2);
  ASSERT_NE(id1, C_TIMER_MANAGER_INVALID_ID);

  uint32_t id3 = c_timer_manager_add(timer_manager, info1.duration, timer_manager_test_cb0, &info1);
  ASSERT_NE(id1, C_TIMER_MANAGER_INVALID_ID);
  
  ASSERT_EQ(c_timer_manager_remove(timer_manager, id1) == C_RET_OK, true);

  for (uint32_t i = 0; i < 100; i++) {
    c_timer_manager_dispatch_one(timer_manager);
    Sleep(10);
  }
  
  ASSERT_EQ(info1.number, 1);
  ASSERT_EQ(info2.number, 1);
  ASSERT_LE((uint32_t)(info1.end - info1.begin) - info1.duration, 10);
  ASSERT_LE((uint32_t)(info2.end - info1.begin) - info2.duration, 10);

  c_timer_manager_deinit(timer_manager);

#if defined(WIN32)
  timeEndPeriod(1);
#endif
}

static c_ret_t timer_manager_test_cb1(struct _c_timer_info_t* timer_info) {
  c_info_t* info = (c_info_t*)(timer_info->ctx);
  info->end = time_platform_now_ms();
  info->number++;
  return C_RET_REPEAT;
}

TEST(c_timer_manager, repeat) {
  c_info_t info;
  c_timer_manager_t* timer_manager = c_timer_manager_init();
  ASSERT_EQ(timer_manager != NULL, true);

#if defined(WIN32)
  timeBeginPeriod(1);
#endif
  memset(&info, 0x0, sizeof(c_info_t));

  info.duration = 20;
  info.begin = time_platform_now_ms();
  uint32_t id = c_timer_manager_add(timer_manager, info.duration, timer_manager_test_cb1, &info);
  ASSERT_NE(id, C_TIMER_MANAGER_INVALID_ID);
  
  for (uint32_t i = 0; i < 100; i++) {
    c_timer_manager_dispatch_one(timer_manager);
    Sleep(10);
  }

  ASSERT_GE(info.number, 45);
  ASSERT_LE(info.number, 50);

  c_timer_manager_deinit(timer_manager);

#if defined(WIN32)
  timeEndPeriod(1);
#endif
}

