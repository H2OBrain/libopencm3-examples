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
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <libopencmsis/core_cm3.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include "clock.h"
#include "board.h"
#include "sdram.h"

/***********************************************************************
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
		{0}
	});

	/* setup blue/user button */
	exti_select_source(EXTI0, GPIOA);
	exti_set_trigger(EXTI0, EXTI_TRIGGER_RISING);
	exti_enable_request(EXTI0);
	nvic_enable_irq(NVIC_EXTI0_IRQ);
}

/***********************************************************************
 * Function definitions
 */

static void ram_test(void);

/***********************************************************************
 * Interrupts
 */

/* Blue button interrupt */
void
exti0_isr()
{
	exti_reset_request(EXTI0);
	ram_test();
}

/***********************************************************************
 * Functions
 */

/**
 * Very simple ram checker
 */
void ram_test() {
	/* Set error and success */
	gpio_set(LED_LD1);
	gpio_set(LED_LD2);
	
	/* Iterate over the whole ram area */
	uint32_t error_count=0;
#define SDRAM_SIZE  1000000*4
	uint32_t *sdram;
	sdram = (uint32_t *)SDRAM1_BASE_ADDRESS;
	for (uint32_t i = 0; i<SDRAM_SIZE; i++) {
		*sdram++=i;
	}
	sdram = (uint32_t *)SDRAM1_BASE_ADDRESS;
	for (uint32_t i = 0; i<SDRAM_SIZE; i++) {
		if (*sdram++!=i) error_count++;
	}
	
	/* Clear error or success */
	if (error_count>0) {
		gpio_clear(LED_LD2);
	} else {
		gpio_clear(LED_LD1);
	}
}

/***********************************************************************
 * Main loop
 */
int main(void)
{
	/* init timers. */
	clock_setup();
	/* setup pins */
	pin_setup();
	/* setup sdram */
	sdram_init();
	/* run initial ram test */
	ram_test();
	while (1) {}
}


