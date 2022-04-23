#ifndef __TIM_PWM_LED_DEF_H__
#define __TIM_PWM_LED_DEF_H__

#include "../base/c_types_def.h"

BEGIN_C_DECLS

typedef union _tim_pwm_led_pixel_abgr_t {
  struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
  } color;
  uint8_t data[4];
  uint32_t value;
} tim_pwm_led_pixel_abgr_t;

typedef union _tim_pwm_led_pixel_grb_t {
  struct {
    uint8_t b;
    uint8_t r;
    uint8_t g;
  } color;
  uint32_t value;
} tim_pwm_led_pixel_grb_t;

typedef enum _tim_pwm_led_type_t {
  TIM_PWM_LED_TYPE_NONE = 0,
  TIM_PWM_LED_TYPE_WS2812_GRB,

  TIM_PWM_LED_TYPE__COUNT,
} tim_pwm_led_type_t;

#define TIM_PWM_LED_TYPE_COUNT (TIM_PWM_LED_TYPE__COUNT - 1)

typedef uint32_t tim_pwm_led_pixel_t;
typedef struct _tim_pwm_led_t tim_pwm_led_t;
typedef struct _tim_pwm_led_vt_t tim_pwm_led_vt_t;

typedef const tim_pwm_led_vt_t* (*tim_pwm_led_get_vtabel)(void);
typedef uint32_t (*tim_pwm_led_get_pixel_bit_size_t)(void);
typedef void (*tim_pwm_led_pixel_reset_data_t)(uint16_t* bytes, uint32_t bytes_size);
typedef void (*tim_pwm_led_pixel_to_bytes_t)(tim_pwm_led_pixel_t pixel, uint16_t* bytes);
typedef void (*tim_pwm_led_pixel_to_bytes_by_data_t)(uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint16_t* bytes);

typedef void (*tim_pwm_led_send_data_t)(const tim_pwm_led_t* tim_pwm_led);

struct _tim_pwm_led_vt_t {
  tim_pwm_led_pixel_to_bytes_t pixel_to_bytes;
  tim_pwm_led_pixel_reset_data_t pixel_reset_data;
  tim_pwm_led_get_pixel_bit_size_t get_pixel_bit_size;
  tim_pwm_led_pixel_to_bytes_by_data_t pixel_to_bytes_by_data;
};

struct _tim_pwm_led_t {
  uint16_t* led_buffer;
  uint32_t led_number;
  uint32_t pixel_bit_size;
  uint32_t led_buffer_offset;
  tim_pwm_led_type_t led_type;

  tim_pwm_led_send_data_t send_data_cb;
  const tim_pwm_led_vt_t* vt;
};

tim_pwm_led_pixel_t tim_pwm_led_pixel_init(const tim_pwm_led_t* tim_pwm_led, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

END_C_DECLS

#endif
