#ifndef __TIM_PWM_LED_H__
#define __TIM_PWM_LED_H__

#include "tim_pwm_led_def.h"

BEGIN_C_DECLS

tim_pwm_led_t* tim_pwm_led_init(tim_pwm_led_t* tim_pwm_led, tim_pwm_led_type_t led_type, uint16_t* led_buffer, uint32_t led_number, uint32_t led_buffer_offset, tim_pwm_led_send_data_t send_data_cb);

void tim_pwm_led_show(const tim_pwm_led_t* tim_pwm_led);
void tim_pwm_led_pixel_reset_data(const tim_pwm_led_t* tim_pwm_led);
void tim_pwm_led_pixel_to_bytes(const tim_pwm_led_t* tim_pwm_led, uint32_t index, tim_pwm_led_pixel_t pixel);
void tim_pwm_led_pixel_to_bytes_by_data(const tim_pwm_led_t* tim_pwm_led, uint32_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t a);


void tim_pwm_led_pixel_set_all_black(const tim_pwm_led_t* tim_pwm_led);


tim_pwm_led_t* tim_pwm_led_get(void);


END_C_DECLS

#endif
