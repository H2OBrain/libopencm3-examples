/*
 * gfx_monochrome.h
 *
 *  Created on: 6 Aug 2017
 *      Author: Oliver Meier
 */

#ifndef SRC_GFX_MONOCHROME_H_
#define SRC_GFX_MONOCHROME_H_

#define GFX_MONO_COLOR_ON (gfx_color_t){.mono=true}
#define GFX_MONO_COLOR_OFF (gfx_color_t){.mono=false}

#define GFX_COLOR_SIZE 1
#define GFXV gfx_mono_
#include "gfx_header.h"
#undef GFXV
#undef GFX_COLOR_SIZE


#endif /* SRC_GFX_MONOCHROME_H_ */
