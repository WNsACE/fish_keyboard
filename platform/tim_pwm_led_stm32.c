#include "tim_pwm_led_stm32.h"

#define LED_BUFFR_DMA_OFFSET    3

static uint32_t s_tim_channel;
static TIM_HandleTypeDef* s_tim_handle = NULL;


static tim_pwm_led_t s_tim_pwm_led_stm32;
static uint16_t s_led_buffer[TIM_PWM_LED_STM32_LED_NUMBER * 24 + LED_BUFFR_DMA_OFFSET * 2] = {0};


static void tim_pwm_led_stm32_DMA_send_data(const tim_pwm_led_t* tim_pwm_led) {
  (void)tim_pwm_led;
  HAL_TIM_PWM_Start_DMA(s_tim_handle, s_tim_channel, (uint32_t*)s_led_buffer, ARRAY_SIZE(s_led_buffer));
}

const tim_pwm_led_t* tim_pwm_led_stm32_init(tim_pwm_led_type_t led_type, TIM_HandleTypeDef* tim_handle, uint32_t tim_channel) {
  s_tim_handle = tim_handle;
  s_tim_channel = tim_channel;
  return tim_pwm_led_init(&s_tim_pwm_led_stm32, led_type, s_led_buffer, TIM_PWM_LED_STM32_LED_NUMBER, LED_BUFFR_DMA_OFFSET, tim_pwm_led_stm32_DMA_send_data);
}

