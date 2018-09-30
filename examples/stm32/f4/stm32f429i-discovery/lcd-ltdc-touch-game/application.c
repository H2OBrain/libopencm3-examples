/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2016 Oliver Meier <h2obrain@gmail.com>
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
#include "sdram.h"
#include "lcd_ili9341.h"

#include "touchscreen_controller_stmpe811.h"
#include "fonts/Tamsyn5x9r_9.h"
#include "fonts/Tamsyn5x9b_9.h"
#include "vector_gfx/vector_gfx.h"


/* snake definitions */
typedef enum {
	RIGHT,UP,LEFT,DOWN
} direction_t;
typedef enum {
	LOST,
	STARTED
} state_t;
typedef struct {
	bool placed;
	point2d_t pos;
} snake_food_t;
typedef struct {
	/* play-field */
	int16_t off_x,off_y,fw,fh;
	/* snake */
	uint64_t last_time;
	float size, length, max_length, speed;
	point2d_t *history, *hcurr, *hfirst, *hend;
	direction_t dir;
	state_t state;
	snake_food_t food;
} snake_state_t;

snake_state_t snake;

static inline void snake_history_reset(void);
static void snake_turn(direction_t dir);


// simple static extension functions
static inline void enable_interrupts(void) {
	__enable_irq();
}
static inline void disable_interrupts(void) {
	__disable_irq();
}

static inline bool is_interrupt(void) {
    return (SCB->ICSR & SCB_ICSR_VECTACTIVE) != 0 ;
}

/**
 * Interrupts
 */

/* Display SPI interrupt */
void spi5_isr()
{
	if (ILI9341_SPI_IS_SELECTED()) {
		ili9341_spi5_isr();
	} else {
		spi_disable_tx_buffer_empty_interrupt(SPI5);
		(void)SPI_DR(SPI5);
	}
}

/* Touchscreen interrupt */
void
exti15_10_isr() {
	exti_reset_request(EXTI15);
	stmpe811_handle_interrupt();
}

/* Blue button interrupt */
void
exti0_isr()
{
	exti_reset_request(EXTI0);
//	new_demo_mode = (new_demo_mode+1) % (DEMO_MODE_BALLS+1);
	snake_history_reset();
	snake.state = STARTED;
}


/**
 * update touchscreen infos
 */
stmpe811_touch_t touch_data;
stmpe811_drag_data_t drag_data;
point2d_t touch_point;
point2d_t drag_distance;

static
void
update_touchscreen_data(void)
{
	touch_data    = (stmpe811_touch_t){0};
	drag_data     = (stmpe811_drag_data_t){0};
	touch_point   = (point2d_t) {-1, -1};
	drag_distance = (point2d_t) { 0,  0};

	touch_data = stmpe811_get_touch_data();
	if (touch_data.touched == 1) {
		switch (gfx_get_rotation()) {
			case GFX_ROTATION_0_DEGREES :
			case GFX_ROTATION_180_DEGREES :
				break;
			case GFX_ROTATION_90_DEGREES :
			case GFX_ROTATION_270_DEGREES :
				swap_i16(touch_data.x,touch_data.y);
				break;
		}
		switch (gfx_get_rotation()) {
			case GFX_ROTATION_0_DEGREES :
				touch_data.x = STMPE811_X_MAX - touch_data.x;
				break;
			case GFX_ROTATION_90_DEGREES :
				touch_data.x = STMPE811_X_MAX - touch_data.x;
				touch_data.y = STMPE811_Y_MAX - touch_data.y;
				break;
			case GFX_ROTATION_180_DEGREES :
				touch_data.y = STMPE811_Y_MAX - touch_data.y;
				break;
			case GFX_ROTATION_270_DEGREES :
				break;
		}
		touch_point = (point2d_t) {
				(vector_flt_t)gfx_width()
				* (touch_data.x - STMPE811_Y_MIN)
				/ (STMPE811_Y_MAX - STMPE811_Y_MIN),
				(vector_flt_t)gfx_height()
				* (touch_data.y-STMPE811_X_MIN)
				/ (STMPE811_X_MAX-STMPE811_X_MIN)
		};
		if (touch_point.x < gfx_width()/2) {
		//if (point2d_compare((point2d_t){            25,gfx_height()-25},touch_point, 50)) {
			disable_interrupts();
			snake_turn(LEFT);
			enable_interrupts();
		} else
		if (touch_point.x > gfx_width()/2) {
		//if (point2d_compare((point2d_t){gfx_width()-25,gfx_height()-25},touch_point, 50)) {
			disable_interrupts();
			snake_turn(RIGHT);
			enable_interrupts();
		}
	} else {
		drag_data = stmpe811_get_drag_data();
		if (drag_data.data_is_valid) {
			drag_distance = (point2d_t) {
					(vector_flt_t)gfx_width()
					* drag_data.dy
					/ (STMPE811_Y_MAX-STMPE811_Y_MIN),
					(vector_flt_t)gfx_height()
					* drag_data.dx
					/ (STMPE811_X_MAX-STMPE811_X_MIN)
			};
		} else {
			/* stop drag*/
		}
	}
}
//static
//void
//print_touchscreen_data(int16_t x, int16_t y)
//{
//	char conv_buf[1024];
//
//	const char *state;
//	/*switch (stmpe811.sample_read_state) {*/
//	switch (stmpe811.current_touch_state) {
//	case STMPE811_TOUCH_STATE__UNTOUCHED:
//		state = "untouched";
//		break;
//	case STMPE811_TOUCH_STATE__TOUCHED:
//		state = "touched";
//		break;
//	case STMPE811_TOUCH_STATE__TOUCHED_WAITING_FOR_TIMEOUT:
//		state = "touched waiting";
//		break;
//	default:
//		state = "invalid";
//		break;
//	}
//
//	sprintf(conv_buf,
//			"touch % 8.1f%8.1f\n"
//			"drag  % 8.1f%8.1f\n"
//			"touch interrupts: %lu\n"
//			"state : %s\n"
//			"values count : %lu",
//			touch_point.x, touch_point.y,
//			drag_distance.x, drag_distance.y,
//			stmpe811.touch_interrupts,
//			state,
//			stmpe811.last_values_count
//		);
//
//	gfx_puts2(x, y, conv_buf, &font_Tamsyn5x9r_9, GFX_COLOR_WHITE);
//}


/**
 * Re-/draw background
 */
static void draw_background()
{
	ili9341_set_layer1();

	gfx_fill_screen(GFX_COLOR_BLACK);

	gfx_draw_rect(0, 0, gfx_width()  , 40  , GFX_COLOR_DARKGREY);
	gfx_fill_rect(1, 1, gfx_width()-2, 40-2, GFX_COLOR_BLUE2);
//						ltdc_get_rgb565_from_rgb888(0x111111));
//						((0x11 << 11) | (0x11 << 5) | 0x11));

	gfx_set_font_scale(3);
	gfx_puts2(10, 10, "Snake", &font_Tamsyn5x9b_9 , GFX_COLOR_WHITE);
	gfx_set_font_scale(1);
	gfx_set_font(&font_Tamsyn5x9r_9);
	gfx_set_text_color(GFX_COLOR_BLUE2);
	gfx_puts3(
			gfx_width()-10, 14,
			"Press the blue button to\nchange something",
			GFX_ALIGNMENT_RIGHT
		);

//	draw_antialised_line((segment2d_t){20,20,200,200},GFX_COLOR_GREEN2);

	/* flip background buffer */
	ili9341_flip_layer1_buffer();
}

/* Snake */
static inline
point2d_t *dec(point2d_t *p) {
	if (p==snake.history) p = snake.hend-1;
	else                  p--;
	return p;
}
static inline
point2d_t *inc(point2d_t *p) {
	if (p==snake.hend-1) p = snake.history;
	else                  p++;
	return p;
}
static inline
bool dec_and_test(point2d_t **p, point2d_t *test_p) {
	return test_p == (*p=dec(*p));
}
static inline
bool inc_and_test(point2d_t **p, point2d_t *test_p) {
	return test_p == (*p=inc(*p));
}
#define SNAKE_HISTORY_LENGTH 1000
static void init_snake(void) {
	point2d_t *history = malloc(sizeof(point2d_t)*SNAKE_HISTORY_LENGTH);
	snake = (snake_state_t) {
		.off_x=5,.off_y=45, .fw=gfx_width()-10, .fh=gfx_height()-50,
		.last_time=mtime(),
		.size=10,.length=0,.max_length=50,.speed=30,
		.history=history,.hcurr=history,.hfirst=history,.hend=history+SNAKE_HISTORY_LENGTH,
		.dir=RIGHT,
		.state=LOST,
		.food={0}
	};
	snake_history_reset();
	rand_r(666);
}
static inline void snake_history_reset(void) {
	snake.length = 0; snake.max_length = 50;
	snake.speed = 30;
	snake.dir    = RIGHT;
	snake.hfirst = snake.hcurr;
	point2d_t reset_point = (point2d_t){snake.off_x+snake.fw/2,snake.off_y+snake.fh/2};
	*snake.hcurr = reset_point;
	 snake.hcurr = inc(snake.hcurr);
	*snake.hcurr = reset_point;
}
static vector_flt_t var_thickness(vector_flt_t *arg, int16_t p, int16_t length) {
	(void)p;(void)length;
	return snake.size/4-1+snake.size/4*(((1+vector_flt_cos((*arg+p)/5))/2));
}
static void do_snake(void) {
	disable_interrupts();

	uint64_t t = mtime();
	float tdiff = (float)(t-snake.last_time) / 1000;

	point2d_t *p = snake.hcurr;
	bool lost;
	switch (snake.state) {
		case STARTED :
		{
			float dist = snake.speed * tdiff;
			switch (snake.dir) {
				case RIGHT :
					p->x += dist;
					break;
				case UP :
					p->y -= dist;
					break;
				case LEFT :
					p->x -= dist;
					break;
				case DOWN :
					p->y += dist;
					break;
			}

			snake.length += dist;
			if (snake.length > snake.max_length) snake.length = snake.max_length;

			lost = p->x < snake.off_x
				|| p->x > snake.off_x+snake.fw
				|| p->y < snake.off_y
				|| p->y > snake.off_y+snake.fh;

			if (!snake.food.placed) {
				snake.food.placed = true;
				snake.food.pos = (point2d_t){
					(vector_flt_t)rand()/RAND_MAX*snake.fw+snake.off_x,
					(vector_flt_t)rand()/RAND_MAX*snake.fh+snake.off_y
				};
			}
		} break;
		case LOST :
//		default :
			lost = true;
			break;
	}
	snake.last_time = t;

	/* drawing snake from front to back, while keeping track of the total length */
	bool done = false;
	float l = snake.length;
	float dl = 0;
	point2d_t *lp = p;
	while (true) {
		done = dec_and_test(&p, snake.hfirst);
		vector_flt_t dist = point2d_dist(*lp,*p);
		l -= dist;
		if (l<=0.0001f) { // <=0
			if (l<0) {
				point2d_t dir = point2d_normalize(point2d_sub_ts(*lp,*p));
				*p = point2d_add_ts(*p, point2d_mul_t(dir,-l));
			}
			done  = true;
		}

		draw_thick_line(
				lp->x,lp->y,p->x,p->y,
				snake.size,
				GFX_COLOR_GREEN2
			);
		draw_varthick_line(
				lp->x,lp->y,p->x,p->y,
				(drawing_varthick_fct_t)var_thickness, &dl,
				(drawing_varthick_fct_t)var_thickness, &dl,
				GFX_COLOR_RED
			);
//		draw_antialised_line((segment2d_t){*lp,*p},GFX_COLOR_WHITE);

		if (done) break;
		lp  = p;
		dl += dist;
	}
	gfx_fill_circle(
			(int16_t)snake.hcurr->x,(int16_t)snake.hcurr->y,
			(int16_t)vector_flt_round(snake.size/2),
			GFX_COLOR_GREEN2
		);

	snake.hfirst = p;
	if (!lost) {
		/* test for intersections in the current direction */
		/* TODO this is very inefficient.. */
		segment2d_t s1;
		p = snake.hcurr;
		s1.p1 = *p;
		if (snake.food.placed
		 && (point2d_dist(snake.food.pos,s1.p1) < snake.size)
		) {
			snake.food.placed = false;
			snake.max_length += 50;
			snake.speed += 5;
		}

		done = dec_and_test(&p, snake.hfirst);
		s1.p2 = *p;
		if (snake.food.placed
		 && (dist_point_to_segment(snake.food.pos,s1) < snake.size)
		) {
			snake.food.placed = false;
		}
		if (!done) {
			while (p != snake.hcurr) {
				/* TODO optimize.. */
				if (dec_and_test(&p, snake.hfirst)) break;
				segment2d_t s2;
				s2.p1 = *p;
				while (true) {
					bool last_p;
					last_p = dec_and_test(&p, snake.hfirst);
					s2.p2 = *p;
					if (dist_segment_to_segment(s1,s2).distance < snake.size) {
						lost = true;
						break;
					}
					if (snake.food.placed
					 && (dist_point_to_segment(snake.food.pos,s2) < snake.size)
					) {
						snake.food.placed = false;
					}
					if (last_p) break;
					s2.p1 = s2.p2;
				}
				break;
			}
		}
	}

	/* draw food */
	if (snake.food.placed) {
		gfx_fill_circle(
				(int16_t)snake.food.pos.x,(int16_t)snake.food.pos.y,
				(int16_t)vector_flt_round(snake.size/2),
				GFX_COLOR_RED
			);
	}

	/* check if lost */
	if (lost) { snake.state = LOST; }

	enable_interrupts();
}
static void snake_turn(direction_t dir) {
	/* snake */
	switch (snake.state) {
		case LOST :
			snake_history_reset();
			snake.state = STARTED;
			break;
		case STARTED :
		{
			point2d_t *third_last = snake.hcurr;
			if (!dec_and_test(&third_last, snake.hfirst)) {
				dec(third_last);
				switch (snake.dir) {
					case RIGHT :
					case LEFT :
						if (fabs(third_last->x-snake.hcurr->x) < snake.size) return;
						break;
					case UP :
					case DOWN :
						if (fabs(third_last->y-snake.hcurr->y) < snake.size) return;
						break;
				}
			}
			switch (dir) {
				case UP :
				case DOWN :
					assert(0);
					break;
				case LEFT :
					if (snake.dir==DOWN) snake.dir = RIGHT;
					else snake.dir++;
					break;
				case RIGHT :
					if (snake.dir==RIGHT) snake.dir = DOWN;
					else snake.dir--;
					break;
			}
			point2d_t p = *snake.hcurr;
			snake.hcurr++;
			if (snake.hcurr==snake.hend) {
				snake.hcurr = snake.history;
			}
			*snake.hcurr = p;
		}	break;
	}
}


/**
 * Main loop
 */

#define DISPLAY_TIMEOUT   33 /* ~30fps */
int main(void)
{
	/* init timers. */
	clock_setup();

	/* setup blue button */
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);
	exti_select_source(EXTI0, GPIOA);
	exti_set_trigger(EXTI0, EXTI_TRIGGER_RISING);
	exti_enable_request(EXTI0);
	nvic_enable_irq(NVIC_EXTI0_IRQ);

	/* set up SDRAM. */
	sdram_init();

	/* init LTDC (gfx
	 * cm3 and spi are also initialized by this function call) */
	ili9341_init(
		(uint16_t *[]){
			(uint16_t *)(
				SDRAM_BASE_ADDRESS + 0*ILI9341_SURFACE_SIZE
			),
			(uint16_t *)(
				SDRAM_BASE_ADDRESS + 1*ILI9341_SURFACE_SIZE
			)
		},
		(uint16_t *[]){
			(uint16_t *)(
				SDRAM_BASE_ADDRESS + 2*ILI9341_SURFACE_SIZE
			),
			(uint16_t *)(
				SDRAM_BASE_ADDRESS + 3*ILI9341_SURFACE_SIZE
			)
		}

	);


	/**
	 * setup stmpe811 touchscreen controller (via i2c)
	 */
	stmpe811_setup_hardware();
	stmpe811_setup();
	/* Temperature readings make no sense!
	stmpe811_start_temp_measurements();
	msleep(100);
	for (i=0; i<100000; i++) {
		uint16_t temp;
		msleep(11);
		temp = stmpe811_read_temp_sample();
		// do something with temp
	}
	stmpe811_stop_temp_measuements();
	*/
	stmpe811_start_tsc();
	stmpe811_enable_interrupts();


	/*
	 * Application start..
	 */

	/* rotate LCD */
	gfx_set_rotation(GFX_ROTATION_180_DEGREES);

	/* set background color */
	ltdc_set_background_color(0, 0, 0);

	/* clear unused layers */
	ili9341_set_layer1();
	gfx_fill_screen(GFX_COLOR_BLACK);
	ili9341_flip_layer1_buffer();

	ili9341_set_layer2();

	/* color key sets alpha to 0 (aka clear screen) */
	gfx_fill_screen(ILI9341_LAYER2_COLOR_KEY);
	ili9341_flip_layer2_buffer();
	gfx_fill_screen(ILI9341_LAYER2_COLOR_KEY);
	ili9341_flip_layer2_buffer();

	ltdc_reload(LTDC_SRCR_RELOAD_VBR);
	while (LTDC_SRCR_IS_RELOADING());

	/* draw background */
	draw_background();

	/* init snake */
	init_snake();

//	/* init floodfill4 demo */
//	init_floodfill4();
//
//	/* init/draw bezier */
//	init_bezier();
//
//	/* init balls demo */
//	init_balls();


	ltdc_reload(LTDC_SRCR_RELOAD_VBR);

	while (1) {
		uint64_t ctime   = mtime();
		static uint64_t draw_timeout = 1;
		static char fps_s[7] = "   fps";

		if (!LTDC_SRCR_IS_RELOADING() && (draw_timeout <= ctime)) {
			/* calculate fps */
			uint32_t fps;
			fps = 1000 / (ctime-draw_timeout+DISPLAY_TIMEOUT);
			/* set next timeout */
			draw_timeout = ctime+DISPLAY_TIMEOUT;

			/* select layer to draw on */
			ili9341_set_layer2();
			/* clear the whole screen */
			gfx_fill_screen(ILI9341_LAYER2_COLOR_KEY);

			/**
			 * Get touch infos
			 */
			update_touchscreen_data();

			/**
			 * Snake
			 */
			do_snake();
			char snake_length_s[64];
			sprintf(snake_length_s, "snake length:% 6.1f", snake.length);
			gfx_puts3(gfx_width()-10,30,snake_length_s, GFX_ALIGNMENT_RIGHT);

//			/**
//			 * Flood fill test
//			 */
//			draw_floodfill4(demo_mode);
//
//			/**
//			 * Bezier test
//			 */
//			draw_bezier(demo_mode);
//
//			/**
//			 * Bezier interactive
//			 */
//			draw_bezier_interactive(demo_mode);
//
//			/**
//			 * Ball stuff
//			 */
//			draw_balls(demo_mode);


			/* draw fps */
			gfx_set_font_scale(1);
			sprintf(fps_s, "%lu fps", fps);
			gfx_puts2(
					200, 15,
					fps_s,
					&font_Tamsyn5x9b_9,
					GFX_COLOR_WHITE
				);

			/* swap the double buffer */
			ili9341_flip_layer2_buffer();

			/* update dislay */
			ltdc_reload(LTDC_SRCR_RELOAD_VBR);
		}
	}
}


