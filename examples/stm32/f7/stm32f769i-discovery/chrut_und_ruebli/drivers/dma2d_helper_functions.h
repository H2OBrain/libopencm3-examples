/*
 * dma2d_helper.h
 *
 *  Created on: 1 May 2019
 *      Author: h2obrain
 */

#ifndef DRIVERS_DMA2D_HELPER_H_
#define DRIVERS_DMA2D_HELPER_H_

#include <stdint.h>
#include <assert.h>
#include <libopencm3/stm32/dma2d.h>
#include <libopencm3/stm32/ltdc.h>
#include "display.h"


//static inline
//void dsi_dma2d_init(display_color_coding_t color_coding) {
//	uint32_t color;
//	switch (color_coding) {
//		case DSI_COLOR_CODING_RGB565   :
//		case DSI_COLOR_CODING_RGB565_  :
//		case DSI_COLOR_CODING_RGB565__ :
//			color = DMA2D_xPFCCR_CM_RGB565;
//			break;
//		case DSI_COLOR_CODING_RGB666   :
//		case DSI_COLOR_CODING_RGB666_  :
//			assert("Color mode is not supported!" && 0);
//			return;
//		case DSI_COLOR_CODING_RGB888   :
//			color = DMA2D_xPFCCR_CM_ARGB8888;
//			break;
//	}
//
//}

typedef enum {
	dasd
} dma2d_blending_mode_t;

static inline
uint32_t ltdc_dma2d_set_color_mode_from_layer(display_layer_t layer, volatile uint32_t *reg) {
	*reg &= ~(DMA2D_OPFCCR_CM_MASK << DMA2D_OPFCCR_CM_SHIFT);
	switch (LTDC_LxPFCR(layer)) {
		case LTDC_LxPFCR_ARGB8888 :
			*reg |= DMA2D_OPFCCR_CM_ARGB8888 << DMA2D_OPFCCR_CM_SHIFT;
			return 4;
		case LTDC_LxPFCR_RGB888 :
			*reg |= DMA2D_OPFCCR_CM_RGB888 << DMA2D_OPFCCR_CM_SHIFT;
			return 3;
		case LTDC_LxPFCR_RGB565 :
			*reg |= DMA2D_OPFCCR_CM_RGB565 << DMA2D_OPFCCR_CM_SHIFT;
			return 2;
		case LTDC_LxPFCR_ARGB1555 :
			*reg |= DMA2D_OPFCCR_CM_ARGB1555 << DMA2D_OPFCCR_CM_SHIFT;
			return 2;
		case LTDC_LxPFCR_ARGB4444 :
			*reg |= DMA2D_OPFCCR_CM_ARGB4444 << DMA2D_OPFCCR_CM_SHIFT;
			return 2;
		case LTDC_LxPFCR_L8 :
		case LTDC_LxPFCR_AL44 :
		case LTDC_LxPFCR_AL88 :
			assert("Unsupported (destination?) color format");
			return 0;
	}
	return 0;
}
static inline
void ltdc_dma2d_set_source_area(
		void    *source_buffer,
		uint16_t source_pitch,
		uint16_t sx, uint16_t sy, uint16_t w,
		uint32_t color_size
) {
	DMA2D_FGMAR = (uint32_t)source_buffer + (sx + sy * source_pitch) * color_size;
	DMA2D_FGOR  = source_pitch - w;
}
static inline
void ltdc_dma2d_set_destination_area(
		display_layer_t layer,
		uint16_t dx,uint16_t dy,uint16_t w,uint16_t h,
		uint32_t color_size
) {
	uint32_t window_x0,window_x1;
	uint32_t window_y0,window_y1;
	window_x1 = ((LTDC_LxWHPCR(layer) >> LTDC_LxWHPCR_WHSPPOS_SHIFT) & LTDC_LxWHPCR_WHSPPOS_MASK);
	window_y1 = ((LTDC_LxWVPCR(layer) >> LTDC_LxWVPCR_WVSPPOS_SHIFT) & LTDC_LxWVPCR_WVSPPOS_MASK);
	if ((dx>window_x1)||(dy>window_y1)) return;

	window_x0 = ((LTDC_LxWHPCR(layer) >> LTDC_LxWHPCR_WHSTPOS_SHIFT) & LTDC_LxWHPCR_WHSTPOS_MASK);
	window_y0 = ((LTDC_LxWVPCR(layer) >> LTDC_LxWVPCR_WVSTPOS_SHIFT) & LTDC_LxWVPCR_WVSTPOS_MASK);

	uint32_t window_width  = window_x1-window_x0 + 1;
	uint32_t window_height = window_y1-window_y0 + 1;
	if (w>window_width-dx)  w = window_width-dx;
	if (h>window_height-dy) h = window_height-dy;

	DMA2D_OMAR = ltdc_get_fbuffer_address(layer) + (dx + dy*window_width)*color_size;
	DMA2D_OOR  = window_width-w;
	DMA2D_NLR  = (w << DMA2D_NLR_PL_SHIFT) | (h << DMA2D_NLR_NL_SHIFT);
}

static inline
void ltdc_dma2d_fill_area(
		display_layer_t layer,
		uint32_t color,
		uint16_t dx,uint16_t dy,
		uint16_t w,uint16_t h
) {
	while (DMA2D_CR & DMA2D_CR_START);

	uint32_t color_size = ltdc_dma2d_set_color_mode_from_layer(layer, &DMA2D_OPFCCR);
	DMA2D_OCOLR = color;
	ltdc_dma2d_set_destination_area(layer, dx,dy,w,h, color_size);

	DMA2D_CR &= ~(DMA2D_CR_MODE_MASK << DMA2D_CR_MODE_SHIFT);
	DMA2D_CR |= DMA2D_CR_MODE_R2M << DMA2D_CR_MODE_SHIFT;
	DMA2D_CR |= DMA2D_CR_START;
}

static inline
void ltdc_dma2d_copy2d(
		uint32_t layer,
		void    *source_buffer, uint16_t source_pitch,
		uint16_t sx, uint16_t sy,
		uint16_t dx, uint16_t dy,
		uint16_t w, uint16_t h
) {
	while (DMA2D_CR & DMA2D_CR_START);

	uint32_t color_size = ltdc_dma2d_set_color_mode_from_layer(layer, &DMA2D_FGPFCCR);
	ltdc_dma2d_set_source_area(source_buffer, source_pitch, sx,sy,w, color_size);
	ltdc_dma2d_set_destination_area(layer, dx,dy,w,h, color_size);

	DMA2D_CR &= ~(DMA2D_CR_MODE_MASK << DMA2D_CR_MODE_SHIFT);
	DMA2D_CR |= DMA2D_CR_MODE_M2M << DMA2D_CR_MODE_SHIFT;
	DMA2D_CR |= DMA2D_CR_START;
}

//static inline
//void dsi_dma2d_copy2d_with_pixel_conversion(
//		uint32_t layer,
//		uint32_t src_color_coding,
//		sx,sy,dx,dy,w,h,
//		point_t dst,
//		dma2d_blending_mode_t blending
//) {
//}
//static inline
//void dsi_dma2d_copy2d_with_pixel_conversion_and_blending(
//		uint32_t layer,
//		uint32_t src_color_coding,
//		sx,sy,dx,dy,w,h,
//		point_t dst,
//		dma2d_blending_mode_t blending
//) {
//}


#endif /* DRIVERS_DMA2D_HELPER_H_ */
