#ifndef __TIM_PWM_LED_H__
#define __TIM_PWM_LED_H__

#include "tim_pwm_led_def.h"
#include "Simple-Color-Conversions/color.h"

BEGIN_C_DECLS

tim_pwm_led_t* tim_pwm_led_init(tim_pwm_led_t* tim_pwm_led, tim_pwm_led_type_t led_type, float max_hsv_value, uint16_t* led_buffer, uint32_t led_number, uint32_t led_buffer_offset, tim_pwm_led_send_data_t send_data_cb);

tim_pwm_led_pixel_t tim_pwm_led_pixel_init_by_hsv(const tim_pwm_led_t* tim_pwm_led, float h, float s, float v);
tim_pwm_led_pixel_t tim_pwm_led_pixel_init(const tim_pwm_led_t* tim_pwm_led, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

void tim_pwm_led_show(tim_pwm_led_t* tim_pwm_led);
void tim_pwm_led_pixel_reset_data(tim_pwm_led_t* tim_pwm_led);
void tim_pwm_led_pixel_to_bytes(tim_pwm_led_t* tim_pwm_led, uint32_t index, tim_pwm_led_pixel_t pixel);
void tim_pwm_led_pixel_to_bytes_by_data(tim_pwm_led_t* tim_pwm_led, uint32_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t a);


void tim_pwm_led_pixel_set_all_black(tim_pwm_led_t* tim_pwm_led);
void tim_pwm_led_pixel_set_all_color(tim_pwm_led_t* tim_pwm_led, tim_pwm_led_pixel_t pixel);

#define TIM_PWM_LED(p) ((tim_pwm_led_t*)(p))

END_C_DECLS

#endif
