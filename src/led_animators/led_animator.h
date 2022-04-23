#ifndef __LED_ANIMATOR_H__
#define __LED_ANIMATOR_H__

#include "../base/c_types_def.h"
#include "../base/c_easing_func.h"
#include "../tim_pwm_led/tim_pwm_led.h"

BEGIN_C_DECLS

typedef struct _led_animator_t led_animator_t;

typedef c_ret_t (*led_animator_update_t)(led_animator_t* animator, float percent);
typedef c_ret_t (*led_animator_destroy_t)(led_animator_t* animator);


typedef struct _led_animator_t {

  uint32_t now;
  uint32_t delay;
  float time_scale;
  uint32_t duration;
  uint32_t yoyo_times;
  uint32_t start_time;
  uint32_t repeat_times;

  c_bool_t forever;
  c_bool_t reversed;
  c_bool_t destroy_when_done;

  c_easing_func_t easing;

  led_animator_update_t update;
  led_animator_destroy_t destroy;
} led_animator_t;



END_C_DECLS

#endif
