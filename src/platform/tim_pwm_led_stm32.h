#ifndef __TIM_PWM_LED_STM32_H__
#define __TIM_PWM_LED_STM32_H__

#include "tim.h"
#include "../tim_pwm_led/tim_pwm_led.h"

#ifndef TIM_PWM_LED_STM32_LED_NUMBER
#define TIM_PWM_LED_STM32_LED_NUMBER    8
#endif


const tim_pwm_led_t* tim_pwm_led_stm32_init(tim_pwm_led_type_t led_type, TIM_HandleTypeDef* tim_handle, uint32_t tim_channel);

#endif
