/*
 * gfx.h
 *
 *  Created on: 6 Aug 2017
 *      Author: Oliver Meier
 */

#include "gfx_config.h"
#include "fonts/fonts.h"

#ifdef GFX_WITH_DMA2D_FONTS
#define font_Tamsyn10x20r_20   font_Tamsyn10x20r_20_a4
#define font_Tamsyn10x20b_20   font_Tamsyn10x20b_20_a4
#define font_DejaVuSansMono_36 font_DejaVuSansMono_36_a4
#include "fonts/Tamsyn10x20r_20_a4.h"
#include "fonts/Tamsyn10x20b_20_a4.h"
#include "fonts/DejaVuSansMono_36_a4.h"
#else
#define font_Tamsyn10x20r_20 font_Tamsyn10x20r_20_mono
#define font_Tamsyn10x20b_20 font_Tamsyn10x20b_20_mono
#define font_DejaVuSansMono_36 font_DejaVuSansMono_36_mono
#include "fonts/Tamsyn10x20r_20_mono.h"
#include "fonts/Tamsyn10x20b_20_mono.h"
#include "fonts/DejaVuSansMono_36_mono.h"
#endif

#include "gfx/gfx_argb8888.h"
