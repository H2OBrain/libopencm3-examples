/*
 * tft_impl.h
 *
 *  Created on: 21 Apr 2019
 *      Author: h2obrain
 */

#ifndef DRIVERS_TFT_IMPL_H_
#define DRIVERS_TFT_IMPL_H_

#include <libopencm3/stm32/gpio.h>
#include "../clock.h"

#define DISPLAY_32F769IDISCOVERY_CLOCKS \
	RCC_GPIOJ, \
	RCC_LTDC, RCC_DMA2D, RCC_DSI

#define DISPLAY_32F769IDISCOVERY_PINS \
	/* DSI_RESET */ \
	{ GPIOJ,\
		GPIO15, \
		GPIO_MODE_OUTPUT , GPIO_PUPD_NONE, \
		.out_mode={ GPIO_OTYPE_OD, GPIO_OSPEED_100MHZ  }, \
		.af_mode= { 0 }}, \
	/* DSIHOST_TE (Tearing signal line) */ \
	{ GPIOJ,\
		GPIO2, \
		GPIO_MODE_AF     , GPIO_PUPD_NONE, \
		.out_mode={ GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ  }, \
		.af_mode= { GPIO_AF12 }} \

#define TFT_NOT_RESET_PIN GPIOJ,GPIO15
static inline void tft_reset(void) {
	gpio_clear(TFT_NOT_RESET_PIN);
	msleep(20);
	gpio_set(TFT_NOT_RESET_PIN);
	msleep(10);
}

typedef enum {
	DSI_MODE_VIDEO_SYNC_PULSES,
	DSI_MODE_VIDEO_SYNC_EVENTS,
	DSI_MODE_VIDEO_BURST,

	DSI_MODE_VIDEO_PATTERN_BER,
	DSI_MODE_VIDEO_PATTERN_COLOR_BARS_HORIZONTAL,
	DSI_MODE_VIDEO_PATTERN_COLOR_BARS_VERTICAL,

	DSI_MODE_ADAPTED_COMMAND_MODE,
} display_dsi_mode_t;
typedef enum {
	DISPLAY_COLOR_CODING_ARGB8888 = 0,
	DISPLAY_COLOR_CODING_RGB888   = 1,
	DISPLAY_COLOR_CODING_RGB565   = 2
} display_color_coding_t;
typedef enum {
	DISPLAY_ORIENTATION_PORTRAIT,
	DISPLAY_ORIENTATION_LANDSCAPE
} display_orientation_t;
/* compatible with ltdc */
typedef enum {
	DISPLAY_LAYER_1 = 1,
	DISPLAY_LAYER_2 = 2
} display_layer_t;

void display_init(
		display_dsi_mode_t mode,
		display_color_coding_t color_coding,
		display_orientation_t orientation,
		uint8_t layer1_frame_buffer[],
		uint8_t layer2_frame_buffer[]
	);
display_dsi_mode_t display_get_dsi_mode(void);

bool display_ready(void);
void display_update(void);

bool display_ltdc_config_ready(void);
void display_ltdc_config_begin(void);
void display_ltdc_config_end(void);
void display_ltdc_config_layer(
		display_layer_t layer,
		bool enable
	);
void display_ltdc_config_windowing_xywh(
		display_layer_t layer,
		uint16_t x,     uint16_t y,
		uint16_t width, uint16_t height
	);

#endif /* DRIVERS_TFT_IMPL_H_ */
