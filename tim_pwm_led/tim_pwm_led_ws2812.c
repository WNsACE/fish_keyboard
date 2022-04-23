#include "tim_pwm_led_def.h"

/*硬件定时器 PWM 模拟 ws2812 时序（用 16 位数据模拟 ws2812 的一位数据）

WS2812 颜色为 GRB 24 位色。

WS2812 采用 PWM方式来编码，即每个PWM的周期固定为 1.25us（800k），占空比为 30% 时为 0 码，占空比为 60% 为 1 码。另外 WS2812 复位信号为一个 不低于 50us 的低电平

                WS2812芯片的通信时序。
+-------------+-------------------+----------+--------+ 
| T0H  |  o code high level  |  350ns  |  200~500ns   |
|-------------+---------+---------+----------+--------|
| T0L  |  o code low level   |  800ns  |  650~950ns   |
|-------------+---------+---------+----------+--------|
| T1H  |  1 code high level  |  700ns  |  550~850ns   |
|-------------+---------+---------+----------+--------|
| T1L  |  1 code low level   |  600ns  |  450~750ns   |
|-------------+---------+---------+----------+--------|
| RES  |    reset begin send data      |  > 50us      |
+------+---------------------+---------+--------------+

low level：0.3*1250 = 375ns   0.7*1250 = 875ns

high level：0.6*1250 = 750ns   0.4*1250 = 500ns

reset begin send data time : 80 * 1.25 = 100us

*/

#define TIM_PWM_LED_PERIOD                  90

#define TIM_PWM_LED_BIT_NUMBER              8 * 3

#define TIM_PWM_LED_RESET_BIT_NUMBER        80

#define TIM_PWM_LED_LOW_PERIOD              (uint16_t)(TIM_PWM_LED_PERIOD * 0.3)
#define TIM_PWM_LED_HIGH_PERIOD             (uint16_t)(TIM_PWM_LED_PERIOD * 0.6)


void tim_pwm_led_ws2812_pixel_to_bytes(tim_pwm_led_pixel_t pixel, uint16_t* bytes) {
  uint32_t i = 0;
  for (i = 0; i < TIM_PWM_LED_BIT_NUMBER; i++) {
    bytes[i] = ((pixel & (0x800000 >> i)) == 0) ? TIM_PWM_LED_LOW_PERIOD : TIM_PWM_LED_HIGH_PERIOD;
  }
}

void tim_pwm_led_ws2812_pixel_to_bytes_by_data(uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint16_t* bytes) {
  tim_pwm_led_pixel_grb_t pixel;
  pixel.color.r = r;
  pixel.color.g = g;
  pixel.color.b = b;
  (void)a;
  tim_pwm_led_ws2812_pixel_to_bytes(pixel.value, bytes);
}

void tim_pwm_led_ws2812_pixel_reset_data(uint16_t* bytes, uint32_t bytes_size) {
  uint32_t i = 0;
  uint32_t n = c_min(TIM_PWM_LED_RESET_BIT_NUMBER, bytes_size);
  for (i = 0; i < n; i++) {
    bytes[i] = TIM_PWM_LED_LOW_PERIOD;
  }
}

uint32_t tim_pwm_led_ws2812_get_pixel_bit_size(void) {
  return TIM_PWM_LED_BIT_NUMBER;
}

static tim_pwm_led_vt_t s_vt = {
  .pixel_to_bytes = tim_pwm_led_ws2812_pixel_to_bytes,
  .pixel_reset_data = tim_pwm_led_ws2812_pixel_reset_data,
  .get_pixel_bit_size = tim_pwm_led_ws2812_get_pixel_bit_size,
  .pixel_to_bytes_by_data = tim_pwm_led_ws2812_pixel_to_bytes_by_data,
};

const tim_pwm_led_vt_t* tim_pwm_led_ws2812_get_vt(void) {
  return &s_vt;
}
