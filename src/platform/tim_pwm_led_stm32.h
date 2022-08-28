#ifndef __TIM_PWM_LED_STM32_H__
#define __TIM_PWM_LED_STM32_H__

#include "stm32f1xx_hal.h"
#include "../base/c_timer_manager.h"
#include "../tim_pwm_led/tim_pwm_led.h"

#ifndef TIM_PWM_LED_STM32_LED_NUMBER
#define TIM_PWM_LED_STM32_LED_NUMBER    8
#endif

/* 灯的最大亮度（0-1.0） */
#ifndef TIM_PWM_LED_STM32_LED_MAX_POWER
#define TIM_PWM_LED_STM32_LED_MAX_POWER    1.0f
#endif

typedef struct _tim_pwm_led_stm32_t tim_pwm_led_stm32_t;

tim_pwm_led_stm32_t* tim_pwm_led_stm32(void);
void tim_pwm_led_stm32_deinit(tim_pwm_led_stm32_t* tim_pwm_led_stm32);
tim_pwm_led_stm32_t* tim_pwm_led_stm32_init(tim_pwm_led_type_t led_type, TIM_HandleTypeDef* tim_handle, uint32_t tim_channel);


c_bool_t tim_pwm_led_stm32_set_breathing_color(tim_pwm_led_stm32_t* tim_pwm_led_stm32, uint32_t duration);
c_bool_t tim_pwm_led_stm32_set_curr_color(tim_pwm_led_stm32_t* tim_pwm_led_stm32, uint8_t r, uint8_t g, uint8_t b);
c_bool_t tim_pwm_led_stm32_set_curr_color_by_hsv(tim_pwm_led_stm32_t* tim_pwm_led_stm32, float h, float s, float v);
c_bool_t tim_pwm_led_stm32_set_static_color(tim_pwm_led_stm32_t* tim_pwm_led_stm32, uint8_t r, uint8_t g, uint8_t b);
c_bool_t tim_pwm_led_stm32_set_round_hsv_color_model(tim_pwm_led_stm32_t* tim_pwm_led_stm32, uint32_t round_hsv_color_duration);

#endif
