/*
 * dma2d_helper_functions.c
 *
 *  Created on: 19 May 2019
 *      Author: h2obrain
 */


/*
 * dma2d_helper.h
 *
 *  Created on: 1 May 2019
 *      Author: h2obrain
 */

#include <assert.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/ltdc.h>
#include "dma2d_helper_functions.h"
#include "../clock.h"

void dma2d_init() {
	rcc_periph_reset_pulse(RST_DMA2D);
	nvic_disable_irq(NVIC_DMA2D_IRQ);
//	nvic_set_priority(NVIC_DMA2D_IRQ,10);
	DMA2D_CR &= ~(DMA2D_CR_CEIE | DMA2D_CR_CTCIE | DMA2D_CR_CAEIE
			    | DMA2D_CR_TWIE | DMA2D_CR_TCIE | DMA2D_CR_TEIE);
	DMA2D_CR |= DMA2D_CR_CEIE | DMA2D_CR_CAEIE | DMA2D_CR_TEIE;
	nvic_enable_irq(NVIC_DMA2D_IRQ);


	// wait 20 cycles between ahb accesses
	DMA2D_AMTCR |= ~(DMA2D_AMTCR_DT_MASK << DMA2D_AMTCR_DT_SHIFT);
	DMA2D_AMTCR |= 100 << DMA2D_AMTCR_DT_SHIFT;
	DMA2D_AMTCR |= DMA2D_AMTCR_EN;
}
void dma2d_isr(void) {
//	uint32_t isr = DMA2D_ISR;
//	DMA2D_IFCR = isr;
	wait_cycles(3); // wait a bit for the isr to be cleared
	while (1);
}


/* ltdc interoperability */
void dma2d_setup_ltdc_pixel_buffer(display_layer_t layer, dma2d_pixel_buffer_t *pxbuf) {
	pxbuf->buffer = (void *)ltdc_get_fbuffer_address(layer);

	uint32_t window_x0,window_x1;
	uint32_t window_y0,window_y1;
	window_x1 = ((LTDC_LxWHPCR(layer) >> LTDC_LxWHPCR_WHSPPOS_SHIFT) & LTDC_LxWHPCR_WHSPPOS_MASK);
	window_y1 = ((LTDC_LxWVPCR(layer) >> LTDC_LxWVPCR_WVSPPOS_SHIFT) & LTDC_LxWVPCR_WVSPPOS_MASK);

	window_x0 = ((LTDC_LxWHPCR(layer) >> LTDC_LxWHPCR_WHSTPOS_SHIFT) & LTDC_LxWHPCR_WHSTPOS_MASK);
	window_y0 = ((LTDC_LxWVPCR(layer) >> LTDC_LxWVPCR_WVSTPOS_SHIFT) & LTDC_LxWVPCR_WVSTPOS_MASK);

	pxbuf->width  = window_x1-window_x0 + 1;
	pxbuf->height = window_y1-window_y0 + 1;

	/* TODO maybe remove the next two switches? */

	/* input color */
	pxbuf->in.alpha_mod.mode  = 0;
	pxbuf->in.alpha_mod.alpha = 0xff;
	switch (LTDC_LxPFCR(layer)) {
		case LTDC_LxPFCR_ARGB8888 :
			pxbuf->in.pixel.format = DMA2D_xPFCCR_CM_ARGB8888;
			pxbuf->in.pixel.size = 4;
			break;
		case LTDC_LxPFCR_RGB888 :
			pxbuf->in.pixel.format = DMA2D_xPFCCR_CM_RGB888;
			pxbuf->in.pixel.size = 3;
			break;
		case LTDC_LxPFCR_RGB565 :
			pxbuf->in.pixel.format = DMA2D_xPFCCR_CM_RGB565;
			pxbuf->in.pixel.size = 2;
			break;
		case LTDC_LxPFCR_ARGB1555 :
			pxbuf->in.pixel.format = DMA2D_xPFCCR_CM_ARGB1555;
			pxbuf->in.pixel.size = 2;
			break;
		case LTDC_LxPFCR_ARGB4444 :
			pxbuf->in.pixel.format = DMA2D_xPFCCR_CM_ARGB4444;
			pxbuf->in.pixel.size = 2;
			break;
		case LTDC_LxPFCR_L8 :
			pxbuf->in.pixel.format = DMA2D_xPFCCR_CM_L8;
			pxbuf->in.pixel.size = 1;
			/* TODO bitch about color */
			//pxbuf->in.alpha_mode.color = ???;
			break;
		case LTDC_LxPFCR_AL44 :
			pxbuf->in.pixel.format = DMA2D_xPFCCR_CM_AL44;
			pxbuf->in.pixel.size = 1;
			/* TODO bitch about clut (cannot be retrieved from ltdc) */
			//pxbuf->in.clut_mode.clut = ???;
			//pxbuf->in.clut_mode.clut_size = ???;
			//pxbuf->in.clut_mode.clut_is_24bit = ???;
			break;
		case LTDC_LxPFCR_AL88 :
			pxbuf->in.pixel.format = DMA2D_xPFCCR_CM_AL88;
			pxbuf->in.pixel.size = 1;
			break;
		default:
			assert("Unsupported destination color format");
			break;
	}
	/* output color */
	switch (LTDC_LxPFCR(layer)) {
		case LTDC_LxPFCR_ARGB8888 :
			pxbuf->out.pixel.format = DMA2D_OPFCCR_CM_ARGB8888;
			pxbuf->out.pixel.size = 4;
			break;
		case LTDC_LxPFCR_RGB888 :
			pxbuf->out.pixel.format = DMA2D_OPFCCR_CM_RGB888;
			pxbuf->out.pixel.size = 3;
			break;
		case LTDC_LxPFCR_RGB565 :
			pxbuf->out.pixel.format = DMA2D_OPFCCR_CM_RGB565;
			pxbuf->out.pixel.size = 2;
			break;
		case LTDC_LxPFCR_ARGB1555 :
			pxbuf->out.pixel.format = DMA2D_OPFCCR_CM_ARGB1555;
			pxbuf->out.pixel.size = 2;
			break;
		case LTDC_LxPFCR_ARGB4444 :
			pxbuf->out.pixel.format = DMA2D_OPFCCR_CM_ARGB4444;
			pxbuf->out.pixel.size = 2;
			break;
		case LTDC_LxPFCR_L8 :
		case LTDC_LxPFCR_AL44 :
		case LTDC_LxPFCR_AL88 :
		default:
			assert("Unsupported destination color format");
			break;
	}
}

/* color and blending stuff */
static inline
void dsi_dma2d_set_input_color_format(
		dma2d_pixel_buffer_t *pxbuf,
		volatile uint32_t *xpfccr,
		volatile uint32_t *xcmar,
		volatile uint32_t *xcolr
) {
	*xpfccr &= ~(
				(DMA2D_xPFCCR_CM_MASK << DMA2D_xPFCCR_CM_SHIFT)
			  | (DMA2D_xPFCCR_AM_MASK << DMA2D_xPFCCR_AM_SHIFT)
			  | (DMA2D_xPFCCR_ALPHA_MASK << DMA2D_xPFCCR_ALPHA_SHIFT)
			  | (DMA2D_xPFCCR_CS_MASK << DMA2D_xPFCCR_CS_SHIFT)
			);
	*xpfccr |= pxbuf->in.pixel.format << DMA2D_xPFCCR_CM_SHIFT;
	*xpfccr |= pxbuf->in.alpha_mod.mode << DMA2D_xPFCCR_AM_SHIFT;
	*xpfccr |= pxbuf->in.alpha_mod.alpha << DMA2D_xPFCCR_ALPHA_SHIFT;
	switch (pxbuf->in.pixel.format) {
		case DMA2D_xPFCCR_CM_ARGB8888 :
		case DMA2D_xPFCCR_CM_RGB888 :
		case DMA2D_xPFCCR_CM_RGB565 :
		case DMA2D_xPFCCR_CM_ARGB1555 :
		case DMA2D_xPFCCR_CM_ARGB4444 :
			break;
		case DMA2D_xPFCCR_CM_L4 :
		case DMA2D_xPFCCR_CM_L8 :
		case DMA2D_xPFCCR_CM_AL44 :
		case DMA2D_xPFCCR_CM_AL88 :
			/* Setup/load CLUT */
			if (*xcmar != (uint32_t)pxbuf->in.pixel.clut_mode.clut) { // this test is not 100% safe..
				*xcmar  = (uint32_t)pxbuf->in.pixel.clut_mode.clut;
				*xpfccr |= (uint32_t)pxbuf->in.pixel.clut_mode.clut_size << DMA2D_xPFCCR_CS_SHIFT;
				if (pxbuf->in.pixel.clut_mode.clut_is_24bit) {
					*xpfccr |= DMA2D_xPFCCR_CCM_RGB888;
				} else {
					*xpfccr &= ~DMA2D_xPFCCR_CCM_RGB888;
				}
				*xpfccr |= DMA2D_xPFCCR_START;
				//while (*xpfccr & DMA2D_xPFCCR_START); // done before start..
			}
			break;
		case DMA2D_xPFCCR_CM_A8 :
		case DMA2D_xPFCCR_CM_A4 :
			/* Set color */
			*xcolr = pxbuf->in.pixel.alpha_mode.color;
			break;
		default:
			assert("Unsupported destination color format");
			break;
	}
}
static inline
void dsi_dma2d_set_output_color_format(
		dma2d_pixel_buffer_t *pxbuf
) {
	DMA2D_OPFCCR &= ~(DMA2D_OPFCCR_CM_MASK << DMA2D_OPFCCR_CM_SHIFT);
	DMA2D_OPFCCR |= pxbuf->out.pixel.format << DMA2D_OPFCCR_CM_SHIFT;
}
/* positional stuff */
static inline
void dma2d_fix_pos(
		int16_t p, int16_t s,
		uint32_t *P, uint32_t *S
) {
	if (p<0) {
		s=(s+p);
		p=0;
	} else
	if (s<0) s=0;
	*P = (uint32_t)p;
	*S = (uint32_t)s;
//	assert(w);
}

static inline
void dma2d_set_source_area(
		dma2d_pixel_buffer_t *pxbuf,
		volatile uint32_t *xxmar, volatile uint32_t *xxor,
		int16_t sx, int16_t sy, int16_t w
) {
	uint32_t Sx,Sy, W;
	dma2d_fix_pos(sx,w,&Sx,&W);
	if (W>pxbuf->width) W = pxbuf->width;
	if (sy<0) sy=0;
	Sy = (uint32_t)sy;

	*xxmar = (uint32_t)pxbuf->buffer + (Sx + Sy * pxbuf->width) * pxbuf->in.pixel.size;
	*xxor  = pxbuf->width - W;
}
static inline
void dma2d_set_destination_area(
		dma2d_pixel_buffer_t *pxbuf,
		int16_t dx,int16_t dy,int16_t w,int16_t h
) {
	uint32_t Dx,Dy, W,H;
	dma2d_fix_pos(dx,w,&Dx,&W);
	dma2d_fix_pos(dy,h,&Dy,&H);

	if ((Dx>=pxbuf->width)||(Dy>=pxbuf->height)) return;

	if (W>pxbuf->width-Dx)  W = pxbuf->width-Dx;
	if (H>pxbuf->height-Dy) H = pxbuf->height-Dy;

	DMA2D_OMAR = (uint32_t)pxbuf->buffer + (Dx + Dy*pxbuf->width)*pxbuf->out.pixel.size;
	DMA2D_OOR  = pxbuf->width-W;
	DMA2D_NLR  = (W << DMA2D_NLR_PL_SHIFT) | (H << DMA2D_NLR_NL_SHIFT);
}

/* exported functions */
void dma2d_wait_complete() {
	while (DMA2D_CR & DMA2D_CR_START);
}
void dma2d_fill(
		dma2d_pixel_buffer_t *pxdst,
		uint32_t color,
		int16_t dx,int16_t dy,
		int16_t w,int16_t h
) {
	dma2d_wait_complete();

	dsi_dma2d_set_output_color_format(pxdst);

	DMA2D_OCOLR = color;

	dma2d_set_destination_area(pxdst, dx,dy,w,h);

	DMA2D_CR &= ~(DMA2D_CR_MODE_MASK << DMA2D_CR_MODE_SHIFT);
	DMA2D_CR |= DMA2D_CR_MODE_R2M << DMA2D_CR_MODE_SHIFT;

	DMA2D_CR |= DMA2D_CR_START;
}
void dma2d_copy(
		dma2d_pixel_buffer_t *pxsrc,
		dma2d_pixel_buffer_t *pxdst,
		int16_t sx, int16_t sy,
		int16_t dx, int16_t dy,
		int16_t w, int16_t h
) {
	dma2d_wait_complete();

	dsi_dma2d_set_output_color_format(pxdst);

	dma2d_set_source_area(pxsrc, &DMA2D_FGMAR,&DMA2D_FGOR, sx,sy,w);
	dma2d_set_destination_area(pxdst, dx,dy,w,h);

	DMA2D_CR &= ~(DMA2D_CR_MODE_MASK << DMA2D_CR_MODE_SHIFT);
	DMA2D_CR |= DMA2D_CR_MODE_M2M << DMA2D_CR_MODE_SHIFT;

	DMA2D_CR |= DMA2D_CR_START;
}
void dma2d_convert_copy(
		dma2d_pixel_buffer_t *pxsrc,
		dma2d_pixel_buffer_t *pxdst,
		int16_t sx, int16_t sy,
		int16_t dx, int16_t dy,
		int16_t w, int16_t h
) {
	dma2d_wait_complete();

	dsi_dma2d_set_input_color_format(pxsrc, &DMA2D_FGPFCCR,&DMA2D_FGCMAR,&DMA2D_FGCOLR);
	dsi_dma2d_set_output_color_format(pxdst);

	dma2d_set_source_area(pxsrc, &DMA2D_FGMAR,&DMA2D_FGOR, sx,sy,w);
	dma2d_set_destination_area(pxdst, dx,dy,w,h);

	DMA2D_CR &= ~(DMA2D_CR_MODE_MASK << DMA2D_CR_MODE_SHIFT);
	DMA2D_CR |= DMA2D_CR_MODE_M2MWPFC << DMA2D_CR_MODE_SHIFT;

	/* wait for CLUTs to be loaded */
	while (DMA2D_FGPFCCR & DMA2D_xPFCCR_START);

	DMA2D_CR |= DMA2D_CR_START;
}
void dma2d_convert_blenddst_copy(
		dma2d_pixel_buffer_t *pxsrc,
		dma2d_pixel_buffer_t *pxdst,
		int16_t sx, int16_t sy,
		int16_t dx, int16_t dy,
		int16_t w, int16_t h
) {
	dma2d_convert_blend_copy(pxsrc,pxdst,pxdst, sx,sy, dx,dy, dx,dy, w,h);
}
void dma2d_convert_blend_copy(
		dma2d_pixel_buffer_t *pxsrc_fg,
		dma2d_pixel_buffer_t *pxsrc_bg,
		dma2d_pixel_buffer_t *pxdst,
		int16_t sx_fg, int16_t sy_fg,
		int16_t sx_bg, int16_t sy_bg,
		int16_t dx, int16_t dy,
		int16_t w, int16_t h
) {
	dma2d_wait_complete();

	dsi_dma2d_set_input_color_format(pxsrc_fg, &DMA2D_FGPFCCR,&DMA2D_FGCMAR,&DMA2D_FGCOLR);
	dsi_dma2d_set_input_color_format(pxsrc_bg, &DMA2D_BGPFCCR,&DMA2D_BGCMAR,&DMA2D_BGCOLR);
	dsi_dma2d_set_output_color_format(pxdst);

	dma2d_set_source_area(pxsrc_fg, &DMA2D_FGMAR,&DMA2D_FGOR, sx_fg,sy_fg,w);
	dma2d_set_source_area(pxsrc_bg, &DMA2D_BGMAR,&DMA2D_BGOR, sx_bg,sy_bg,w);
	dma2d_set_destination_area(pxdst, dx,dy,w,h);

	DMA2D_CR &= ~(DMA2D_CR_MODE_MASK << DMA2D_CR_MODE_SHIFT);
	DMA2D_CR |= DMA2D_CR_MODE_M2MWB << DMA2D_CR_MODE_SHIFT;

	/* wait for CLUTs to be loaded */
	while (DMA2D_BGPFCCR & DMA2D_xPFCCR_START);
	while (DMA2D_FGPFCCR & DMA2D_xPFCCR_START);

	DMA2D_CR |= DMA2D_CR_START;
}
