#include "tim_pwm_led.h"

#define BLEND_COLOR(a, c) (c) = (uint8_t)(((uint32_t)(a) * (uint32_t)(r)) >> 8)

extern const tim_pwm_led_vt_t* tim_pwm_led_ws2812_get_vt(void);

const static tim_pwm_led_get_vtabel g_led_get_vtable_list[TIM_PWM_LED_TYPE_COUNT] = {
  tim_pwm_led_ws2812_get_vt,
};

static const tim_pwm_led_vt_t* tim_pwm_led_get_vtable(tim_pwm_led_type_t led_type) {
  return g_led_get_vtable_list[(uint32_t)led_type - 1]();
}

tim_pwm_led_t* tim_pwm_led_init(tim_pwm_led_t* tim_pwm_led, tim_pwm_led_type_t led_type, float max_hsv_value, uint16_t* led_buffer, uint32_t led_number, uint32_t led_buffer_offset, tim_pwm_led_send_data_t send_data_cb) {
  assert(tim_pwm_led != NULL && led_buffer != NULL && led_number > 0 && send_data_cb != NULL);
  tim_pwm_led->led_type = led_type;
  tim_pwm_led->led_buffer = led_buffer;
  tim_pwm_led->led_number = led_number;
  tim_pwm_led->send_data_cb = send_data_cb;
  tim_pwm_led->max_hsv_value = max_hsv_value;
  tim_pwm_led->led_buffer_offset = led_buffer_offset;
  tim_pwm_led->vt = tim_pwm_led_get_vtable(led_type);
  tim_pwm_led->max_alpha = (uint8_t)(max_hsv_value * 256);

  tim_pwm_led->pixel_bit_size = tim_pwm_led->vt->get_pixel_bit_size();

  memset(led_buffer, 0x0, sizeof(uint16_t) * (led_number + led_buffer_offset));

  return tim_pwm_led;
}

void tim_pwm_led_deinit(tim_pwm_led_t* tim_pwm_led) {
  C_UNUSED(tim_pwm_led);
}

tim_pwm_led_pixel_t tim_pwm_led_pixel_init(const tim_pwm_led_t* tim_pwm_led, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  a = (tim_pwm_led->max_alpha * a) >> 8;
  if (a < 0xf8) {
    BLEND_COLOR(a, r);
    BLEND_COLOR(a, g);
    BLEND_COLOR(a, b);
  } else if (a < 0x08) {
    r = g = b = 0;
  }
  switch (tim_pwm_led->led_type) {
  case TIM_PWM_LED_TYPE_WS2812_GRB: {
    tim_pwm_led_pixel_grb_t pixel;
    pixel.color.r = r;
    pixel.color.g = g;
    pixel.color.b = b;
    return pixel.value;
  }
  default:
    break;
  }
  return 0;
}

tim_pwm_led_pixel_t tim_pwm_led_pixel_init_by_hsv(const tim_pwm_led_t* tim_pwm_led, float h, float s, float v) {
  uint8_t r, g, b;
  v = tim_pwm_led->max_hsv_value * v;
  convertHSVtoRGB(h, s, v, &r, &g, &b);
  switch (tim_pwm_led->led_type) {
  case TIM_PWM_LED_TYPE_WS2812_GRB: {
    tim_pwm_led_pixel_grb_t pixel;
    pixel.color.r = r;
    pixel.color.g = g;
    pixel.color.b = b;
    return pixel.value;
  }
  default:
    break;
  }
  return 0;
}

void tim_pwm_led_pixel_set_led_max_power(tim_pwm_led_t* tim_pwm_led, float led_max_power) {
  tim_pwm_led->max_hsv_value = c_min(led_max_power, TIM_PWM_LED_STM32_LED_MAX_POWER);
}

void tim_pwm_led_pixel_to_bytes(tim_pwm_led_t* tim_pwm_led, uint32_t index, tim_pwm_led_pixel_t pixel) {
  assert(tim_pwm_led != NULL && tim_pwm_led->led_number > index);
  tim_pwm_led->vt->pixel_to_bytes(pixel, tim_pwm_led->led_buffer + tim_pwm_led->led_buffer_offset + index * tim_pwm_led->pixel_bit_size);
}

void tim_pwm_led_pixel_to_bytes_by_data(tim_pwm_led_t* tim_pwm_led, uint32_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  assert(tim_pwm_led != NULL && tim_pwm_led->led_number > index);
  tim_pwm_led->vt->pixel_to_bytes_by_data(r, g, b, a, tim_pwm_led->led_buffer + tim_pwm_led->led_buffer_offset + index * tim_pwm_led->pixel_bit_size);
}

void tim_pwm_led_pixel_reset_data(tim_pwm_led_t* tim_pwm_led) {
  assert(tim_pwm_led != NULL);
  tim_pwm_led->vt->pixel_reset_data(tim_pwm_led->led_buffer, tim_pwm_led->led_number);
}

void tim_pwm_led_show(tim_pwm_led_t* tim_pwm_led) {
  assert(tim_pwm_led != NULL);
  tim_pwm_led->send_data_cb(tim_pwm_led);
}

void tim_pwm_led_pixel_set_all_color(tim_pwm_led_t* tim_pwm_led, tim_pwm_led_pixel_t pixel) {
  uint32_t i = 0;
  uint16_t* led_buffer = tim_pwm_led->led_buffer + tim_pwm_led->led_buffer_offset;
  for (i = 0; i < tim_pwm_led->led_number; i++) {
    tim_pwm_led->vt->pixel_to_bytes(pixel, led_buffer + i * tim_pwm_led->pixel_bit_size);
  }
}

void tim_pwm_led_pixel_set_all_black(tim_pwm_led_t* tim_pwm_led) {
  tim_pwm_led_pixel_t pixel = tim_pwm_led_pixel_init(tim_pwm_led, 0x0, 0x0, 0x0, 0xFF);
  tim_pwm_led_pixel_set_all_color(tim_pwm_led, pixel);
}
