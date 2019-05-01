/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2019 Oliver Meier <h2obrain@gmail.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include <libopencmsis/core_cm3.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include "support/system.h"
#include "clock.h"
#include "sdram.h"
#include "drivers/display.h"

/**
 * Debugging
 */
void panic_mode(panic_mode_data_t *data) {
	print_panic_mode_data(data);
	while (1);
}

/**
 * Setup functions
 */
#define LED_LD1 GPIOJ,GPIO13
#define LED_LD2 GPIOJ,GPIO5
#define LED_LD3 GPIOA,GPIO12
#define BUTTON_BLUE GPIOA,GPIO0
#define BUTTON_BLUE_PRESSED() gpio_get(BUTTON_BLUE)
static void pin_setup(void) {
	/* pin-clocks */
	board_setup_clocks((uint32_t[]){
		RCC_GPIOA,
		RCC_GPIOJ,
		SDRAM_32F769IDISCOVERY_CLOCKS,
		DISPLAY_32F769IDISCOVERY_CLOCKS,
		0
	});
	/* pins */
	board_setup_pins((pin_setup_t[]) {
		/* outputs (LEDs 1-3) */
		{ GPIOJ,
			GPIO5  | GPIO13,
			GPIO_MODE_OUTPUT , GPIO_PUPD_NONE   ,
			.out_mode={ GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ  }, .af_mode ={0}},
		{ GPIOA,
			GPIO12,
			GPIO_MODE_OUTPUT , GPIO_PUPD_NONE   ,
			.out_mode={ GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ  }, .af_mode ={0}},
		/* inputs (blue button) */
		{ GPIOA,
			GPIO0,
			GPIO_MODE_INPUT  , GPIO_PUPD_NONE   ,
			.out_mode={0}, .af_mode ={0}},
		/* sdram */
		SDRAM_32F769IDISCOVERY_PINS,
		/* tft */
		DISPLAY_32F769IDISCOVERY_PINS,
		{0}
	});

	/* setup blue/user button */
	exti_select_source(EXTI0, GPIOA);
	exti_set_trigger(EXTI0, EXTI_TRIGGER_BOTH);
	exti_enable_request(EXTI0);
	nvic_enable_irq(NVIC_EXTI0_IRQ);
}

/**
 * Function definitions
 */
static void update_led_counter(void);

/**
 * Interrupts
 */

/* Blue button interrupt (EXTI makes not too much sense here :)) */
static bool blue_button_state_changed = false;
void
exti0_isr()
{
	exti_reset_request(EXTI0);
	blue_button_state_changed = true;
	update_led_counter();
}

/**
 * Functions
 */
void update_led_counter() {
	/* little grey code blinker */
	static const uint32_t  gcl[] = {0,1,3,2,6,7,5,4};
	static const uint32_t *gc    = gcl;
	static const uint32_t *gcle  = gcl+sizeof(gcl)/sizeof(gcl[0])-1;
	if (blue_button_state_changed) {
		blue_button_state_changed = false;
		gc = gcl;
	}
	if (BUTTON_BLUE_PRESSED()) {
		gpio_set(LED_LD1);
		gpio_set(LED_LD2);
		gpio_set(LED_LD3);
	} else {
		if (*gc&0b001) gpio_set(LED_LD1);
		else           gpio_clear(LED_LD1);
		if (*gc&0b010) gpio_set(LED_LD2);
		else           gpio_clear(LED_LD2);
		if (*gc&0b100) gpio_set(LED_LD3);
		else           gpio_clear(LED_LD3);
		if (gc==gcle) gc = gcl;
		else          gc++;
	}
}

#include <stdlib.h>
//#include "drivers/dsi_helper_functions.h"
//void *align_pointer(uint32_t alignment, void *pointer);
//void *align_pointer(uint32_t alignment, void *pointer) {
//	return (void *)align_up_to(alignment, (uint32_t)pointer);
//}
#define SDRAM_SIZE  (0x1000000U/4) // only the first bank accessible?

static inline int16_t bounce_add(int16_t v,int16_t *d,int16_t w) {
	v += *d;
	if (*d>0) {
		if (v>w) {
			*d = -*d;
			v  = w*2-v;
		}
	} else {
		if (v<0) {
			*d = -*d;
			v  = -v;
		}
	}
	return v;
}

/**
 * Main loop
 */
#include "drivers/dma2d_helper_functions.h"
int main(void)
{
	/* init timers. */
	clock_setup();
	/* setup pins */
	pin_setup();
	/* low level setup */
	system_setup();
	/* setup sdram */
	sdram_init();
	uint64_t ram_clear_time = mtime();
	memset((void *)SDRAM1_BASE_ADDRESS, 0x00, SDRAM_SIZE);
	ram_clear_time = mtime() - ram_clear_time;
	/* setup tft */
//	uint8_t *video_data = malloc(2 * 800*480*4+1024);
//	uint32_t (*layers)[800][480] = align_pointer(1024, video_data);
	// the whole 1st rambank is reserved for video
	uint32_t (*layers)[480][800] = (void*)SDRAM1_BASE_ADDRESS;
	display_init(
			DSI_MODE_VIDEO_BURST,
//			DSI_MODE_VIDEO_SYNC_PULSES,
//			DSI_MODE_VIDEO_SYNC_EVENTS,
//			DSI_MODE_VIDEO_PATTERN_BER,
//			DSI_MODE_VIDEO_PATTERN_COLOR_BARS_HORIZONTAL,
//			DSI_MODE_VIDEO_PATTERN_COLOR_BARS_VERTICAL,
//			DSI_MODE_ADAPTED_COMMAND_MODE,

			DISPLAY_COLOR_CODING_ARGB8888,

			DISPLAY_ORIENTATION_LANDSCAPE,
//			TFT_ORIENTATION_PORTRAIT,

			(uint8_t*)layers[0],
			(uint8_t*)layers[1]
//			(uint8_t*)SDRAM1_BASE_ADDRESS,
//			(uint8_t*)SDRAM1_BASE_ADDRESS+0xC2000000U
		);

//	uint32_t error_count=0;
//	uint32_t *sdram;
//	sdram = (uint32_t *)SDRAM1_BASE_ADDRESS;
//	for (uint32_t i = 0; i<SDRAM_SIZE; i++) {
//		*sdram++=i;
//	}
//	sdram = (uint32_t *)SDRAM1_BASE_ADDRESS;
//	for (uint32_t i = 0; i<SDRAM_SIZE; i++) {
//		if (*sdram++!=i) error_count++;
//	}
//	assert(error_count==0);

//	for (uint32_t i=1; i<=255; i++) {
//		memset((void *)SDRAM1_BASE_ADDRESS, i, 2 * 800*480*4);
//	}

#define bla
#ifdef bla
	display_ltdc_config_begin();
	display_ltdc_config_layer(DISPLAY_LAYER_1, false);
	display_ltdc_config_windowing_xywh(DISPLAY_LAYER_2, 100,100,200,200);
	display_ltdc_config_end();
#else
	/* Ram is too slow for 2 layers in 60Hz video mode (see wait_cycles below) */
	if (display_get_dsi_mode()!=DSI_MODE_ADAPTED_COMMAND_MODE) {
		while (!display_ltdc_config_ready());
		display_ltdc_config_begin();
		display_ltdc_config_layer(DISPLAY_LAYER_1, false);
		display_ltdc_config_end();
	}
#endif

	/* very verbose pixel set */
	uint32_t alpha = 0xff000000;
	for (uint32_t l = 0; l<2; l++) {
//		for (uint32_t x=l*200; x<(l+1)*150; x++) {
//			for (uint32_t y=l*100; y<(l+1)*100; y++) {
		for (uint32_t x=0; x<800; x++) {
			for (uint32_t y=0; y<480; y++) {
				layers[l][y][x] = alpha | (0xff<<(l*8)); // ARGB
//				wait_cycles(10000); // give the ram some time to breath
//				wait_cycles(100000); // give the ram some time to breath
			}
		}
		alpha = (alpha / 2 + 1) & 0xff000000;
	}

#ifdef bla
#else
	/* play with windows */
	uint32_t c=300;
	int16_t w,h,x,y,xd,yd;
	w=120;
	h=120;
	x=y=0;
	xd=3;
	yd=5;
	uint32_t (*layer1_data)[w] = (void *)layers[0];
	uint32_t (*layer2_data)[w] = (void *)layers[1];
	display_ltdc_config_begin();
	display_ltdc_config_windowing_xywh(DISPLAY_LAYER_1, x,y, w,h);
	display_ltdc_config_windowing_xywh(DISPLAY_LAYER_2, 800-w-x,480-h-y, w,h);
	/* Ram is fast enough for two small windowed layers */
	display_ltdc_config_layer(DISPLAY_LAYER_1, true);
	display_ltdc_config_end();
	while (!display_ltdc_config_ready());
#endif

	display_update();

	srand(systick_get_value());

	for (uint32_t x=10; x<20; x++) {
		for (uint32_t y=10; y<20; y++) {
			layers[1][y][x] = 0xffffffff;
		}
	}
	while (!display_ready());
	display_ltdc_config_begin();
	ltdc_dma2d_fill_area(
			DISPLAY_LAYER_2,
			0xff000000|rand()/(RAND_MAX/0xffffff),
			50,50, 300,100
		);
	for (uint32_t i=0; i<10; i++) {
		ltdc_dma2d_copy2d(
				DISPLAY_LAYER_2,
				layers[1],200,
				5, 48,
				5+i*20,48+i*20, 90,90
			);
	}
	display_ltdc_config_end();
	while(1) {
		msleep(30);
		if (display_ready()) {
			display_update();
		}
	}

#define REFRESH_RATE 30
	uint64_t timeout = mtime();
	while (1) {
#ifdef bla
//		layers[1][rand()/(RAND_MAX/480)][rand()/(RAND_MAX/800)] = 0xff000000|rand()/(RAND_MAX/0xffffff);
//		msleep(1000);

//		// dma2d fill
//		ltdc_dma2d_fill_area(
//				DISPLAY_LAYER_2,
//				0xff000000|rand()/(RAND_MAX/0xffffff),
//				rand()/(RAND_MAX/800),
//				rand()/(RAND_MAX/480),
//				rand()/(RAND_MAX/99)+1,
//				rand()/(RAND_MAX/99)+1,
//				0
//			);

#else
//		layers[1][rand()/(RAND_MAX/480)][rand()/(RAND_MAX/800)] = 0xff000000|rand()/(RAND_MAX/0xffffff);
//		wait_cycles(100000); // give the ram some time to breath
		layer1_data[10+rand()/(RAND_MAX/(h-20))][10+rand()/(RAND_MAX/(w-20))] = 0xcf000000|rand()/(RAND_MAX/0xffffff);
		layer2_data[10+rand()/(RAND_MAX/(h-20))][10+rand()/(RAND_MAX/(w-20))] = 0xcf000000|rand()/(RAND_MAX/0xffffff);
//		wait_cycles(1000); // give the ram some time to breath
#endif

		if (display_ready()) {
			uint64_t time = mtime();
			if (timeout<=time) {
				timeout += 1000/REFRESH_RATE;
				if (timeout<=time) timeout = time + 1000/REFRESH_RATE;
				update_led_counter();

#ifndef bla
				if (c) {
					//c--;
//					x = 360;
//					y = 200;
					x = bounce_add(x,&xd,800-w);
					y = bounce_add(y,&yd,480-h);

					display_ltdc_config_begin();
					display_ltdc_config_windowing_xywh(DISPLAY_LAYER_1, x,y, w,h);
					display_ltdc_config_windowing_xywh(DISPLAY_LAYER_2, 800-w-x,480-h-y, w,h);
					display_ltdc_config_end();

					display_update();
				}
#else
				display_update();
#endif

			}
		}
	}
}


