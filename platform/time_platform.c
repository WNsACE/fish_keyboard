#include "stm32f1xx_hal.h"
#include "../base/c_types_def.h"

uint64_t time_platform_now_ms(void) {
  return HAL_GetTick();
}

