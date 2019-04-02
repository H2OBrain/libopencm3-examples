/*
 * board.h
 *
 *  Created on: 31 Mar 2019
 *      Author: h2obrain
 */

#ifndef BOARD_H_
#define BOARD_H_
#include <stdint.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>


/**
 * Simplifying functions
 */

typedef struct {
	uint32_t GPIO;      // base address
	uint32_t GPIO_PINS; // flags
	// config
	uint8_t mode;
	uint8_t pullup_type;
	/*  */
	struct {       // if mode = af or output (i don't think af is needed here, but it's used in many samples, so i leave it..
		uint8_t otype;
		uint8_t ospeed;
	} out_mode;
	struct {        // if mode = af
		uint8_t gpioaf;
	} af_mode;
} pin_setup_t;

/* zero terminated list of pin-configs */
static inline void board_setup_clocks(uint32_t* clocks) {
	while (*clocks) {
		rcc_periph_clock_enable(*clocks);
		clocks++;
	}
	/* some clocks need some time before we can write to the registers
	 * (see errata sheet (it's only 1-2 cpu cycles..)
	 */
	__asm__ volatile ("dsb");
}

/* zero terminated list of pin-configs */
static inline void board_setup_pins(pin_setup_t *pin_configs) {
	while (pin_configs->GPIO) {
		/* mask out pins which are configured later in the array */
		pin_setup_t *pin_configs_following = pin_configs+1;
		while (pin_configs_following->GPIO) {
			if (pin_configs->GPIO == pin_configs_following->GPIO) {
				pin_configs->GPIO_PINS &= ~(pin_configs->GPIO_PINS & pin_configs_following->GPIO_PINS);
			}
			pin_configs_following++;
		}

		/* setup the pin(s) */
		if (pin_configs->GPIO_PINS) {
			gpio_mode_setup(pin_configs->GPIO, pin_configs->mode, pin_configs->pullup_type, pin_configs->GPIO_PINS);
			if ((pin_configs->mode == GPIO_MODE_OUTPUT) || (pin_configs->mode == GPIO_MODE_AF))
				gpio_set_output_options(pin_configs->GPIO, pin_configs->out_mode.otype, pin_configs->out_mode.ospeed, pin_configs->GPIO_PINS);
			if  (pin_configs->mode == GPIO_MODE_AF)
				gpio_set_af(pin_configs->GPIO, pin_configs->af_mode.gpioaf, pin_configs->GPIO_PINS);
		}

		pin_configs++;
	}
}

#endif /* BOARD_H_ */
