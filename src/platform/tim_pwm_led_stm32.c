#include "tim_pwm_led_stm32.h"

#define LED_BUFFR_DMA_OFFSET    3

typedef enum _color_model_t {
  /* 静态颜色 */
  COLOR_MODEL_STATIC_COLOR = 0,
  /* 循环颜色 */
  COLOR_MODEL_ROUND_HSV_COLOR,
  /* 呼吸灯颜色 */
  COLOR_MODEL_BREATHING_COLOR,
} color_model_t;

struct _tim_pwm_led_stm32_t {
  tim_pwm_led_t base;

  uint32_t tim_channel;
  TIM_HandleTypeDef* tim_handle;

  uint32_t timer_id;

  c_bool_t is_stop_switch_color;
  c_bool_t is_reversed;

  float curr_hsv_hue;
  float curr_hsv_value;
  float curr_hsv_saturation;

  float color_interval;
  uint32_t color_duration;

  color_model_t color_model;
  tim_pwm_led_type_t led_type;
  uint16_t led_buffer[TIM_PWM_LED_STM32_LED_NUMBER * 24 + LED_BUFFR_DMA_OFFSET * 2];
};

static tim_pwm_led_stm32_t s_tim_pwm_led_stm32;

static c_ret_t tim_pwm_led_stm32_on_timer(c_timer_info_t* timer_info);

tim_pwm_led_stm32_t* tim_pwm_led_stm32(void) {
  return &s_tim_pwm_led_stm32;
}

static void tim_pwm_led_stm32_DMA_send_data(const tim_pwm_led_t* tim_pwm_led) {
  tim_pwm_led_stm32_t* tim_pwm_led_stm32 = (tim_pwm_led_stm32_t*)tim_pwm_led;
  HAL_TIM_PWM_Start_DMA(tim_pwm_led_stm32->tim_handle, tim_pwm_led_stm32->tim_channel, (uint32_t*)tim_pwm_led_stm32->led_buffer, ARRAY_SIZE(tim_pwm_led_stm32->led_buffer));
}

tim_pwm_led_stm32_t* tim_pwm_led_stm32_init(tim_pwm_led_type_t led_type, TIM_HandleTypeDef* tim_handle, uint32_t tim_channel) {
  memset(&s_tim_pwm_led_stm32, 0x0, sizeof(tim_pwm_led_stm32_t));
  s_tim_pwm_led_stm32.led_type = led_type;
  s_tim_pwm_led_stm32.tim_handle = tim_handle;
  s_tim_pwm_led_stm32.tim_channel = tim_channel;
  tim_pwm_led_init(&s_tim_pwm_led_stm32.base, led_type, TIM_PWM_LED_STM32_LED_MAX_POWER, s_tim_pwm_led_stm32.led_buffer, TIM_PWM_LED_STM32_LED_NUMBER, LED_BUFFR_DMA_OFFSET, tim_pwm_led_stm32_DMA_send_data);

  s_tim_pwm_led_stm32.timer_id = c_timer_manager_add(c_timer_manager(), 16, tim_pwm_led_stm32_on_timer, &s_tim_pwm_led_stm32);
  return (tim_pwm_led_stm32_t*)&s_tim_pwm_led_stm32;
}

void tim_pwm_led_stm32_deinit(tim_pwm_led_stm32_t* tim_pwm_led_stm32) {
  if (s_tim_pwm_led_stm32.timer_id != C_TIMER_MANAGER_INVALID_ID) {
    c_timer_manager_remove(c_timer_manager(), s_tim_pwm_led_stm32.timer_id);
  }
}

static void tim_pwm_led_stm32_on_timer_by_breathing_color(tim_pwm_led_stm32_t* tim_pwm_led_stm32, float interval, float* v, c_bool_t* is_reversed) {
  if (*is_reversed) {
    *v -= interval;
  } else {
    *v += interval;
  }   
  if (*v >= 1.0f) {
    *v = 1.0f;
    *is_reversed = TRUE;
  } else if (*v <= 0.0f) {
    *v = 0.0f;
    *is_reversed = FALSE;
  }
}

static void tim_pwm_led_stm32_on_timer_by_round_hsv_color(tim_pwm_led_stm32_t* tim_pwm_led_stm32, float interval, float* h, float* s, float* v) {
  *v = 1.0f;
  *s = 1.0f;
  *h += interval;
  if (*h >= 360.0f) {
    *h = 0.0f;
  }
}

static c_ret_t tim_pwm_led_stm32_on_timer(c_timer_info_t* timer_info) {
  uint32_t interval = timer_info->interval;
  tim_pwm_led_stm32_t* tim_pwm_led_stm32 = (tim_pwm_led_stm32_t*)(timer_info->ctx);
  if (!tim_pwm_led_stm32->is_stop_switch_color) {
    tim_pwm_led_pixel_t color = 0;
    tim_pwm_led_t* tim_pwm_led = TIM_PWM_LED(tim_pwm_led_stm32);
    switch (tim_pwm_led_stm32->color_model) {
    case COLOR_MODEL_ROUND_HSV_COLOR: {
      float new_interval = tim_pwm_led_stm32->color_interval * interval;
      tim_pwm_led_stm32_on_timer_by_round_hsv_color(tim_pwm_led_stm32, new_interval, &tim_pwm_led_stm32->curr_hsv_hue, &tim_pwm_led_stm32->curr_hsv_saturation, &tim_pwm_led_stm32->curr_hsv_value);
      break;
    }
    case COLOR_MODEL_BREATHING_COLOR : {
      float new_interval = tim_pwm_led_stm32->color_interval * interval;
      tim_pwm_led_stm32_on_timer_by_breathing_color(tim_pwm_led_stm32, new_interval, &tim_pwm_led_stm32->curr_hsv_value, &tim_pwm_led_stm32->is_reversed);
      break;
    }
    default:
      break;
    }
    
    color = tim_pwm_led_pixel_init_by_hsv(tim_pwm_led, tim_pwm_led_stm32->curr_hsv_hue, tim_pwm_led_stm32->curr_hsv_saturation, tim_pwm_led_stm32->curr_hsv_value);
    tim_pwm_led_pixel_set_all_color(tim_pwm_led, color);
    tim_pwm_led_show(tim_pwm_led);
  }
  return C_RET_REPEAT;
}

c_bool_t tim_pwm_led_stm32_set_round_hsv_color_model(tim_pwm_led_stm32_t* tim_pwm_led_stm32, uint32_t round_hsv_color_duration){
  if (tim_pwm_led_stm32 == NULL) return FALSE;
  tim_pwm_led_stm32->color_duration = round_hsv_color_duration;
  tim_pwm_led_stm32->color_interval = 360.f / round_hsv_color_duration;
  tim_pwm_led_stm32->color_model = round_hsv_color_duration > 0 ? COLOR_MODEL_ROUND_HSV_COLOR : COLOR_MODEL_STATIC_COLOR;
  return TRUE;
}

c_bool_t tim_pwm_led_stm32_set_breathing_color(tim_pwm_led_stm32_t* tim_pwm_led_stm32, uint32_t duration) {
  if (tim_pwm_led_stm32 == NULL) return FALSE;
  tim_pwm_led_stm32->color_duration = duration;
  tim_pwm_led_stm32->color_interval = 0.5f / duration;
  tim_pwm_led_stm32->color_model = duration > 0 ? COLOR_MODEL_BREATHING_COLOR : COLOR_MODEL_STATIC_COLOR;
  return TRUE;
}

c_bool_t tim_pwm_led_stm32_set_static_color(tim_pwm_led_stm32_t* tim_pwm_led_stm32, uint8_t r, uint8_t g, uint8_t b) {
  if (tim_pwm_led_stm32 == NULL) return FALSE;
  tim_pwm_led_stm32->color_duration = 1;
  tim_pwm_led_stm32->color_interval = 1.0f;
  tim_pwm_led_stm32->color_model = COLOR_MODEL_STATIC_COLOR;
  convertRGBtoHSV(r, g, b, &tim_pwm_led_stm32->curr_hsv_hue, &tim_pwm_led_stm32->curr_hsv_saturation, &tim_pwm_led_stm32->curr_hsv_value);
  return TRUE;
}

c_bool_t tim_pwm_led_stm32_set_curr_color(tim_pwm_led_stm32_t* tim_pwm_led_stm32, uint8_t r, uint8_t g, uint8_t b) {
  if (tim_pwm_led_stm32 == NULL) return FALSE;
  convertRGBtoHSV(r, g, b, &tim_pwm_led_stm32->curr_hsv_hue, &tim_pwm_led_stm32->curr_hsv_saturation, &tim_pwm_led_stm32->curr_hsv_value);
  return TRUE;
}

c_bool_t tim_pwm_led_stm32_set_curr_color_by_hsv(tim_pwm_led_stm32_t* tim_pwm_led_stm32, float h, float s, float v) {
  if (tim_pwm_led_stm32 == NULL) return FALSE;
  tim_pwm_led_stm32->curr_hsv_hue = h;
  tim_pwm_led_stm32->curr_hsv_value = v;
  tim_pwm_led_stm32->curr_hsv_saturation = s;
  return TRUE;
}
