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

#include <libopencm3/cm3/common.h>
#include <libopencm3/stm32/memorymap.h>
#include <stdint.h>

#ifndef DSI_H_
#define DSI_H_

/** @defgroup dsi_registers DSI Registers
 * @ingroup dsi_defines
 * @brief DSI Host Control Registers
@{*/

/* --- DSI Host --- */
/* DSI_VR:      DSI Host version */
#define DSI_VR       (MMIO32(DSI_BASE + 0x0000))
/* DSI_CR:      DSI Host control */
#define DSI_CR       (MMIO32(DSI_BASE + 0x0004))
/* DSI_CCR:     DSI Host clock control */
#define DSI_CCR      (MMIO32(DSI_BASE + 0x0008))
/* DSI_LVCIDR:  DSI Host LTDC VCID */
#define DSI_LVCIDR   (MMIO32(DSI_BASE + 0x000C))
/* DSI_LCOLCR:  DSI Host LTDC color coding */
#define DSI_LCOLCR   (MMIO32(DSI_BASE + 0x0010))
/* DSI_LPCR:    DSI Host LTDC polarity configuration */
#define DSI_LPCR     (MMIO32(DSI_BASE + 0x0014))
/* DSI_LPMCR:   DSI Host low-power mode configuration */
#define DSI_LPMCR    (MMIO32(DSI_BASE + 0x0018))
/* DSI_PCR:     DSI Host protocol configuration */
#define DSI_PCR      (MMIO32(DSI_BASE + 0x002C))
/* DSI_GVCIDR:  DSI Host generic VCID */
#define DSI_GVCIDR   (MMIO32(DSI_BASE + 0x0030))
/* DSI_MCR:     DSI Host mode configuration */
#define DSI_MCR      (MMIO32(DSI_BASE + 0x0034))
/* DSI_VMCR:    DSI Host video mode configuration */
#define DSI_VMCR     (MMIO32(DSI_BASE + 0x0038))
/* DSI_VPCR:    DSI Host video packet configuration */
#define DSI_VPCR     (MMIO32(DSI_BASE + 0x003C))
/* DSI_VCCR:    DSI Host video chunks configuration */
#define DSI_VCCR     (MMIO32(DSI_BASE + 0x0040))
/* DSI_VNPCR:   DSI Host video null packet configuration */
#define DSI_VNPCR    (MMIO32(DSI_BASE + 0x0044))
/* DSI_VHSACR:  DSI Host video HSA configuration */
#define DSI_VHSACR   (MMIO32(DSI_BASE + 0x0048))
/* DSI_VHBPCR:  DSI Host video HBP configuration */
#define DSI_VHBPCR   (MMIO32(DSI_BASE + 0x004C))
/* DSI_VLCR:    DSI Host video line configuration */
#define DSI_VLCR     (MMIO32(DSI_BASE + 0x0050))
/* DSI_VVSACR:  DSI Host video VSA configuration */
#define DSI_VVSACR   (MMIO32(DSI_BASE + 0x0054))
/* DSI_VVBPCR:  DSI Host video VBP configuration */
#define DSI_VVBPCR   (MMIO32(DSI_BASE + 0x0058))
/* DSI_VVFPCR:  DSI Host video VFP configuration */
#define DSI_VVFPCR   (MMIO32(DSI_BASE + 0x005C))
/* DSI_VVACR:   DSI Host video VA configuration */
#define DSI_VVACR    (MMIO32(DSI_BASE + 0x0060))
/* DSI_LCCR:    DSI Host LTDC command configuration */
#define DSI_LCCR     (MMIO32(DSI_BASE + 0x0064))
/* DSI_CMCR:    DSI Host command mode configuration */
#define DSI_CMCR     (MMIO32(DSI_BASE + 0x0068))
/* DSI_GHCR:    DSI Host generic header configuration */
#define DSI_GHCR     (MMIO32(DSI_BASE + 0x006C))
/* DSI_GPDR:    DSI Host generic payload data */
#define DSI_GPDR     (MMIO32(DSI_BASE + 0x0070))
/* DSI_GPSR:    DSI Host generic packet status */
#define DSI_GPSR     (MMIO32(DSI_BASE + 0x0074))
/* DSI_TCCR0:   DSI Host timeout counter configuration 0 */
#define DSI_TCCR0    (MMIO32(DSI_BASE + 0x0078))
/* DSI_TCCR1:   DSI Host timeout counter configuration 1 */
#define DSI_TCCR1    (MMIO32(DSI_BASE + 0x007C))
/* DSI_TCCR2:   DSI Host timeout counter configuration 2 */
#define DSI_TCCR2    (MMIO32(DSI_BASE + 0x0080))
/* DSI_TCCR3:   DSI Host timeout counter configuration 3 */
#define DSI_TCCR3    (MMIO32(DSI_BASE + 0x0084))
/* DSI_TCCR4:   DSI Host timeout counter configuration 4 */
#define DSI_TCCR4    (MMIO32(DSI_BASE + 0x0088))
/* DSI_TCCR5:   DSI Host timeout counter configuration 5 */
#define DSI_TCCR5    (MMIO32(DSI_BASE + 0x008C))
/* DSI_CLCR:    DSI Host clock lane configuration */
#define DSI_CLCR     (MMIO32(DSI_BASE + 0x0094))
/* DSI_CLTCR:   DSI Host clock lane timer configuration */
#define DSI_CLTCR    (MMIO32(DSI_BASE + 0x0098))
/* DSI_DLTCR:   DSI Host data lane timer configuration */
#define DSI_DLTCR    (MMIO32(DSI_BASE + 0x009C))
/* DSI_PCTLR:   DSI Host PHY control */
#define DSI_PCTLR    (MMIO32(DSI_BASE + 0x00A0))
/* DSI_PCONFR:  DSI Host PHY configuration */
#define DSI_PCONFR   (MMIO32(DSI_BASE + 0x00A4))
/* DSI_PUCR:    DSI Host PHY ULPS control */
#define DSI_PUCR     (MMIO32(DSI_BASE + 0x00A8))
/* DSI_PTTCR:   DSI Host PHY TX triggers configuration */
#define DSI_PTTCR    (MMIO32(DSI_BASE + 0x00AC))
/* DSI_PSR:     DSI Host PHY status */
#define DSI_PSR      (MMIO32(DSI_BASE + 0x00B0))
/* DSI_ISR0:    DSI Host interrupt and status 0 */
#define DSI_ISR0     (MMIO32(DSI_BASE + 0x00BC))
/* DSI_ISR1:    DSI Host interrupt and status 1 */
#define DSI_ISR1     (MMIO32(DSI_BASE + 0x00C0))
/* DSI_IER0:    DSI Host interrupt enable 0 */
#define DSI_IER0     (MMIO32(DSI_BASE + 0x00C4))
/* DSI_IER1:    DSI Host interrupt enable 1 */
#define DSI_IER1     (MMIO32(DSI_BASE + 0x00C8))
/* DSI_FIR0:    DSI Host force interrupt 0 */
#define DSI_FIR0     (MMIO32(DSI_BASE + 0x00D8))
/* DSI_FIR1:    DSI Host force interrupt 1 */
#define DSI_FIR1     (MMIO32(DSI_BASE + 0x00DC))
/* DSI_VSCR:    DSI Host video shadow control */
#define DSI_VSCR     (MMIO32(DSI_BASE + 0x0100))
/* DSI_LCVCIDR: DSI Host LTDC current VCID */
#define DSI_LCVCIDR  (MMIO32(DSI_BASE + 0x010C))
/* DSI_LCCCR:   DSI Host LTDC current color coding */
#define DSI_LCCCR    (MMIO32(DSI_BASE + 0x0110))
/* DSI_LPMCCR:  DSI Host low-power mode current configuration */
#define DSI_LPMCCR   (MMIO32(DSI_BASE + 0x0118))
/* DSI_VMCCR:   DSI Host video mode current configuration */
#define DSI_VMCCR    (MMIO32(DSI_BASE + 0x0138))
/* DSI_VPCCR:   DSI Host video packet current configuration */
#define DSI_VPCCR    (MMIO32(DSI_BASE + 0x013C))
/* DSI_VCCCR:   DSI Host video chunks current configuration */
#define DSI_VCCCR    (MMIO32(DSI_BASE + 0x0140))
/* DSI_VNPCCR:  DSI Host video null packet current configuration */
#define DSI_VNPCCR   (MMIO32(DSI_BASE + 0x0144))
/* DSI_VHSACCR: DSI Host video HSA current configuration */
#define DSI_VHSACCR  (MMIO32(DSI_BASE + 0x0148))
/* DSI_VHBPCCR: DSI Host video HBP current configuration */
#define DSI_VHBPCCR  (MMIO32(DSI_BASE + 0x014C))
/* DSI_VLCCR:   DSI Host video line current configuration */
#define DSI_VLCCR    (MMIO32(DSI_BASE + 0x0150))
/* DSI_VVSACCR: DSI Host video VSA current configuration */
#define DSI_VVSACCR  (MMIO32(DSI_BASE + 0x0154))
/* DSI_VVBPCCR: DSI Host video VBP current configuration */
#define DSI_VVBPCCR  (MMIO32(DSI_BASE + 0x0158))
/* DSI_VVFPCCR: DSI Host video VFP current configuration */
#define DSI_VVFPCCR  (MMIO32(DSI_BASE + 0x015C))
/* DSI_VVACCR:  DSI Host video VA current configuration */
#define DSI_VVACCR   (MMIO32(DSI_BASE + 0x0160))


/* --- DSI Wrapper --- */
/* DSI_WCFGR:   DSI wrapper configuration */
#define DSI_WCFGR    (MMIO32(DSI_BASE + 0x0400))
/* DSI_WCR:     DSI wrapper control */
#define DSI_WCR      (MMIO32(DSI_BASE + 0x0404))
/* DSI_WIER:    DSI wrapper interrupt enable */
#define DSI_WIER     (MMIO32(DSI_BASE + 0x0408))
/* DSI_WISR:    DSI wrapper interrupt and status */
#define DSI_WISR     (MMIO32(DSI_BASE + 0x040C))
/* DSI_WIFCR:   DSI wrapper interrupt flag clear */
#define DSI_WIFCR    (MMIO32(DSI_BASE + 0x0410))
/* DSI_WPCR0:   DSI wrapper PHY configuration 0 */
#define DSI_WPCR0    (MMIO32(DSI_BASE + 0x0418))
/* DSI_WPCR1:   DSI wrapper PHY configuration 1 */
#define DSI_WPCR1    (MMIO32(DSI_BASE + 0x041C))
/* DSI_WPCR2:   DSI wrapper PHY configuration 2 */
#define DSI_WPCR2    (MMIO32(DSI_BASE + 0x0420))
/* DSI_WPCR3:   DSI wrapper PHY configuration 3 */
#define DSI_WPCR3    (MMIO32(DSI_BASE + 0x0424))
/* DSI_WPCR4:   DSI wrapper PHY configuration 4 */
#define DSI_WPCR4    (MMIO32(DSI_BASE + 0x0428))
/* DSI_WRPCR:   DSI wrapper regulator and PLL control */
#define DSI_WRPCR    (MMIO32(DSI_BASE + 0x0430))

/*@}*/




/**
 * DSI Host
 */


/** @defgroup dsi_vr_values DSI_VR values
 * @ingroup dsihost_registers
 * @brief  DSI Host version
@{*/
/* VERSION[31:0] (825438250), Version of the DSI Host */
#define DSI_VR_VERSION_MASK            0xFFFFFFFF
#define DSI_VR_VERSION_SHIFT           0
/*@}*/

/** @defgroup dsi_cr_values DSI_CR values
 * @ingroup dsihost_registers
 * @brief  DSI Host control
@{*/
typedef enum {
	/* Reserved[31:1] (0) */
	/* EN[0] (0), Enable */
	DSI_CR_EN                        = 1<<0
} dsi_cr_flags_t;
#define DSI_CR_FLAGS_MASK              0x00000001
/*@}*/

/** @defgroup dsi_ccr_values DSI_CCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host clock control
@{*/
/* Reserved[31:16] (0) */
/* TOCKDIV[15:8] (0), Timeout clock division */
#define DSI_CCR_TOCKDIV_MASK           0x000000FF
#define DSI_CCR_TOCKDIV_SHIFT          8
/* TXECKDIV[7:0] (0), TX escape clock division */
#define DSI_CCR_TXECKDIV_MASK          0x000000FF
#define DSI_CCR_TXECKDIV_SHIFT         0
/*@}*/

/** @defgroup dsi_lvcidr_values DSI_LVCIDR values
 * @ingroup dsihost_registers
 * @brief  DSI Host LTDC VCID
@{*/
/* Reserved[31:2] (0) */
/* VCID[1:0] (0), Virtual channel ID */
#define DSI_LVCIDR_VCID_MASK           0x00000003
#define DSI_LVCIDR_VCID_SHIFT          0
/*@}*/

/** @defgroup dsi_lcolcr_values DSI_LCOLCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host LTDC color coding
@{*/
typedef enum {
	/* Reserved[31:9] (0) */
	/* LPE[8] (0), Loosely packet enable */
	DSI_LCOLCR_LPE                   = 1<<8
	/* Reserved[7:4] (0) */
	/* COLC[3:0] (0), Color coding */
} dsi_lcolcr_flags_t;
#define DSI_LCOLCR_FLAGS_MASK          0x00000100
#define DSI_LCOLCR_COLC_MASK           0x0000000F
#define DSI_LCOLCR_COLC_SHIFT          0
/*@}*/

/** @defgroup dsi_lpcr_values DSI_LPCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host LTDC polarity configuration
@{*/
typedef enum {
	/* Reserved[31:3] (0) */
	/* HSP[2] (0), HSYNC polarity */
	DSI_LPCR_HSP                     = 1<<2,
	/* VSP[1] (0), VSYNC polarity */
	DSI_LPCR_VSP                     = 1<<1,
	/* DEP[0] (0), Data enable polarity */
	DSI_LPCR_DEP                     = 1<<0
} dsi_lpcr_flags_t;
#define DSI_LPCR_FLAGS_MASK            0x00000007
/*@}*/

/** @defgroup dsi_lpmcr_values DSI_LPMCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host low-power mode configuration
@{*/
/* Reserved[31:24] (0) */
/* LPSIZE[23:16] (0), Largest packet size */
#define DSI_LPMCR_LPSIZE_MASK          0x000000FF
#define DSI_LPMCR_LPSIZE_SHIFT         16
/* Reserved[15:8] (0) */
/* VLPSIZE[7:0] (0), VACT largest packet size */
#define DSI_LPMCR_VLPSIZE_MASK         0x000000FF
#define DSI_LPMCR_VLPSIZE_SHIFT        0
/*@}*/

/** @defgroup dsi_pcr_values DSI_PCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host protocol configuration
@{*/
typedef enum {
	/* Reserved[31:5] (0) */
	/* CRCRXE[4] (0), CRC reception enable */
	DSI_PCR_CRCRXE                   = 1<<4,
	/* ECCRXE[3] (0), ECC reception enable */
	DSI_PCR_ECCRXE                   = 1<<3,
	/* BTAE[2] (0), Bus-turn-around enable */
	DSI_PCR_BTAE                     = 1<<2,
	/* ETRXE[1] (0), EoTp reception enable */
	DSI_PCR_ETRXE                    = 1<<1,
	/* ETTXE[0] (0), EoTp transmission enable */
	DSI_PCR_ETTXE                    = 1<<0
} dsi_pcr_flags_t;
#define DSI_PCR_FLAGS_MASK             0x0000001F
/*@}*/

/** @defgroup dsi_gvcidr_values DSI_GVCIDR values
 * @ingroup dsihost_registers
 * @brief  DSI Host generic VCID
@{*/
/* Reserved[31:2] (0) */
/* VCID[1:0] (0), Virtual channel ID */
#define DSI_GVCIDR_VCID_MASK           0x00000003
#define DSI_GVCIDR_VCID_SHIFT          0
/*@}*/

/** @defgroup dsi_mcr_values DSI_MCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host mode configuration
@{*/
typedef enum {
	/* Reserved[31:1] (0) */
	/* CMDM[0] (1), Command mode */
	DSI_MCR_CMDM                     = 1<<0
} dsi_mcr_flags_t;
#define DSI_MCR_FLAGS_MASK             0x00000001
/*@}*/

/** @defgroup dsi_vmcr_values DSI_VMCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video mode configuration
@{*/
typedef enum {
	/* Reserved[31:25] (0) */
	/* PGO[24] (0), Pattern generator orientation */
	DSI_VMCR_PGO                     = 1<<24,
	/* Reserved[23:21] (0) */
	/* PGM[20] (0), Pattern generator mode */
	DSI_VMCR_PGM                     = 1<<20,
	/* Reserved[19:17] (0) */
	/* PGE[16] (0), Pattern generator enable */
	DSI_VMCR_PGE                     = 1<<16,
	/* LPCE[15] (0), Low-power command enable */
	DSI_VMCR_LPCE                    = 1<<15,
	/* FBTAAE[14] (0), Frame bus-turn-around acknowledge enable */
	DSI_VMCR_FBTAAE                  = 1<<14,
	/* LPHFPE[13] (0), Low-power horizontal front-porch enable */
	DSI_VMCR_LPHFPE                  = 1<<13,
	/* LPHBPE[12] (0), Low-power horizontal back-porch enable */
	DSI_VMCR_LPHBPE                  = 1<<12,
	/* LPVAE[11] (0), Low-power vertical active enable */
	DSI_VMCR_LPVAE                   = 1<<11,
	/* LPVFPE[10] (0), Low-power vertical front-porch enable */
	DSI_VMCR_LPVFPE                  = 1<<10,
	/* LPVBPE[9] (0), Low-power vertical back-porch enable */
	DSI_VMCR_LPVBPE                  = 1<<9,
	/* LPVSAE[8] (0), Low-power vertical sync active enable */
	DSI_VMCR_LPVSAE                  = 1<<8
	/* Reserved[7:2] (0) */
	/* VMT[1:0] (0), Video mode type */
} dsi_vmcr_flags_t;
#define DSI_VMCR_FLAGS_MASK            0x0111FF00
#define DSI_VMCR_VMT_MASK              0x00000003
#define DSI_VMCR_VMT_SHIFT             0
/*@}*/

/** @defgroup dsi_vpcr_values DSI_VPCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video packet configuration
@{*/
/* Reserved[31:14] (0) */
/* VPSIZE[13:0] (0), Video packet size */
#define DSI_VPCR_VPSIZE_MASK           0x00003FFF
#define DSI_VPCR_VPSIZE_SHIFT          0
/*@}*/

/** @defgroup dsi_vccr_values DSI_VCCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video chunks configuration
@{*/
/* Reserved[31:13] (0) */
/* NUMC[12:0] (0), Number of chunks */
#define DSI_VCCR_NUMC_MASK             0x00001FFF
#define DSI_VCCR_NUMC_SHIFT            0
/*@}*/

/** @defgroup dsi_vnpcr_values DSI_VNPCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video null packet configuration
@{*/
/* Reserved[31:13] (0) */
/* NPSIZE[12:0] (0), Null packet size */
#define DSI_VNPCR_NPSIZE_MASK          0x00001FFF
#define DSI_VNPCR_NPSIZE_SHIFT         0
/*@}*/

/** @defgroup dsi_vhsacr_values DSI_VHSACR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video HSA configuration
@{*/
/* Reserved[31:12] (0) */
/* HSA[11:0] (0), Horizontal synchronism active duration */
#define DSI_VHSACR_HSA_MASK            0x00000FFF
#define DSI_VHSACR_HSA_SHIFT           0
/*@}*/

/** @defgroup dsi_vhbpcr_values DSI_VHBPCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video HBP configuration
@{*/
/* Reserved[31:12] (0) */
/* HBP[11:0] (0), Horizontal back-porch duration */
#define DSI_VHBPCR_HBP_MASK            0x00000FFF
#define DSI_VHBPCR_HBP_SHIFT           0
/*@}*/

/** @defgroup dsi_vlcr_values DSI_VLCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video line configuration
@{*/
/* Reserved[31:15] (0) */
/* HLINE[14:0] (0), Horizontal line duration */
#define DSI_VLCR_HLINE_MASK            0x00007FFF
#define DSI_VLCR_HLINE_SHIFT           0
/*@}*/

/** @defgroup dsi_vvsacr_values DSI_VVSACR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video VSA configuration
@{*/
/* Reserved[31:10] (0) */
/* VSA[9:0] (0), Vertical synchronism active duration */
#define DSI_VVSACR_VSA_MASK            0x000003FF
#define DSI_VVSACR_VSA_SHIFT           0
/*@}*/

/** @defgroup dsi_vvbpcr_values DSI_VVBPCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video VBP configuration
@{*/
/* Reserved[31:10] (0) */
/* VBP[9:0] (0), Vertical back-porch duration */
#define DSI_VVBPCR_VBP_MASK            0x000003FF
#define DSI_VVBPCR_VBP_SHIFT           0
/*@}*/

/** @defgroup dsi_vvfpcr_values DSI_VVFPCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video VFP configuration
@{*/
/* Reserved[31:10] (0) */
/* VFP[9:0] (0), Vertical front-porch duration */
#define DSI_VVFPCR_VFP_MASK            0x000003FF
#define DSI_VVFPCR_VFP_SHIFT           0
/*@}*/

/** @defgroup dsi_vvacr_values DSI_VVACR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video VA configuration
@{*/
/* Reserved[31:14] (0) */
/* VA[13:0] (0), Vertical active duration */
#define DSI_VVACR_VA_MASK              0x00003FFF
#define DSI_VVACR_VA_SHIFT             0
/*@}*/

/** @defgroup dsi_lccr_values DSI_LCCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host LTDC command configuration
@{*/
/* Reserved[31:16] (0) */
/* CMDSIZE[15:0] (0), Command size */
#define DSI_LCCR_CMDSIZE_MASK          0x0000FFFF
#define DSI_LCCR_CMDSIZE_SHIFT         0
/*@}*/

/** @defgroup dsi_cmcr_values DSI_CMCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host command mode configuration
@{*/
typedef enum {
	/* Reserved[31:25] (0) */
	/* MRDPS[24] (0), Maximum read packet size */
	DSI_CMCR_MRDPS                   = 1<<24,
	/* Reserved[23:20] (0) */
	/* DLWTX[19] (0), DCS long write transmission */
	DSI_CMCR_DLWTX                   = 1<<19,
	/* DSR0TX[18] (0), DCS short read zero parameter transmission */
	DSI_CMCR_DSR0TX                  = 1<<18,
	/* DSW1TX[17] (0), DCS short read one parameter transmission */
	DSI_CMCR_DSW1TX                  = 1<<17,
	/* DSW0TX[16] (0), DCS short write zero parameter transmission */
	DSI_CMCR_DSW0TX                  = 1<<16,
	/* Reserved[15] (0) */
	/* GLWTX[14] (0), Generic long write transmission */
	DSI_CMCR_GLWTX                   = 1<<14,
	/* GSR2TX[13] (0), Generic short read two parameters transmission */
	DSI_CMCR_GSR2TX                  = 1<<13,
	/* GSR1TX[12] (0), Generic short read one parameters transmission */
	DSI_CMCR_GSR1TX                  = 1<<12,
	/* GSR0TX[11] (0), Generic short read zero parameters transmission */
	DSI_CMCR_GSR0TX                  = 1<<11,
	/* GSW2TX[10] (0), Generic short write two parameters transmission */
	DSI_CMCR_GSW2TX                  = 1<<10,
	/* GSW1TX[9] (0), Generic short write one parameters transmission */
	DSI_CMCR_GSW1TX                  = 1<<9,
	/* GSW0TX[8] (0), Generic short write zero parameters transmission */
	DSI_CMCR_GSW0TX                  = 1<<8,
	/* Reserved[7:2] (0) */
	/* ARE[1] (0), Acknowledge request enable */
	DSI_CMCR_ARE                     = 1<<1,
	/* TEARE[0] (0), Tearing effect acknowledge request enable */
	DSI_CMCR_TEARE                   = 1<<0
} dsi_cmcr_flags_t;
#define DSI_CMCR_FLAGS_MASK            0x010F7F03
/*@}*/

/** @defgroup dsi_ghcr_values DSI_GHCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host generic header configuration
@{*/
/* Reserved[31:24] (0) */
/* WCMSB[23:16] (0), WordCount MSB */
#define DSI_GHCR_WCMSB_MASK            0x000000FF
#define DSI_GHCR_WCMSB_SHIFT           16
/* WCLSB[15:8] (0), WordCount LSB */
#define DSI_GHCR_WCLSB_MASK            0x000000FF
#define DSI_GHCR_WCLSB_SHIFT           8
/* VCID[7:6] (0), Channel */
#define DSI_GHCR_VCID_MASK             0x00000003
#define DSI_GHCR_VCID_SHIFT            6
/* DT[5:0] (0), Type */
#define DSI_GHCR_DT_MASK               0x0000003F
#define DSI_GHCR_DT_SHIFT              0
/*@}*/

/** @defgroup dsi_gpdr_values DSI_GPDR values
 * @ingroup dsihost_registers
 * @brief  DSI Host generic payload data
@{*/
/* DATA4[31:24] (0), Payload byte 4 */
#define DSI_GPDR_DATA4_MASK            0x000000FF
#define DSI_GPDR_DATA4_SHIFT           24
/* DATA3[23:16] (0), Payload byte 3 */
#define DSI_GPDR_DATA3_MASK            0x000000FF
#define DSI_GPDR_DATA3_SHIFT           16
/* DATA2[15:8] (0), Payload byte 2 */
#define DSI_GPDR_DATA2_MASK            0x000000FF
#define DSI_GPDR_DATA2_SHIFT           8
/* DATA1[7:0] (0), Payload byte 1 */
#define DSI_GPDR_DATA1_MASK            0x000000FF
#define DSI_GPDR_DATA1_SHIFT           0
/*@}*/

/** @defgroup dsi_gpsr_values DSI_GPSR values
 * @ingroup dsihost_registers
 * @brief  DSI Host generic packet status
@{*/
typedef enum {
	/* Reserved[31:7] (0) */
	/* RCB[6] (0), Read command busy */
	DSI_GPSR_RCB                     = 1<<6,
	/* PRDFF[5] (0), Payload read FIFO full */
	DSI_GPSR_PRDFF                   = 1<<5,
	/* PRDFE[4] (1), Payload read FIFO empty */
	DSI_GPSR_PRDFE                   = 1<<4,
	/* PWRFF[3] (0), Payload write FIFO full */
	DSI_GPSR_PWRFF                   = 1<<3,
	/* PWRFE[2] (1), Payload write FIFO empty */
	DSI_GPSR_PWRFE                   = 1<<2,
	/* CMDFF[1] (0), Command FIFO full */
	DSI_GPSR_CMDFF                   = 1<<1,
	/* CMDFE[0] (1), Command FIFO empty */
	DSI_GPSR_CMDFE                   = 1<<0
} dsi_gpsr_flags_t;
#define DSI_GPSR_FLAGS_MASK            0x0000007F
/*@}*/

/** @defgroup dsi_tccr0_values DSI_TCCR0 values
 * @ingroup dsihost_registers
 * @brief  DSI Host timeout counter configuration 0
@{*/
/* HSTX_TOCNT[31:16] (0), High-speed transmission timeout counter */
#define DSI_TCCR0_HSTX_TOCNT_MASK      0x0000FFFF
#define DSI_TCCR0_HSTX_TOCNT_SHIFT     16
/* LPRX_TOCNT[15:0] (0), Low-power reception timeout counter */
#define DSI_TCCR0_LPRX_TOCNT_MASK      0x0000FFFF
#define DSI_TCCR0_LPRX_TOCNT_SHIFT     0
/*@}*/

/** @defgroup dsi_tccr1_values DSI_TCCR1 values
 * @ingroup dsihost_registers
 * @brief  DSI Host timeout counter configuration 1
@{*/
/* Reserved[31:16] (0) */
/* HSRD_TOCNT[15:0] (0), High-speed read timeout counter */
#define DSI_TCCR1_HSRD_TOCNT_MASK      0x0000FFFF
#define DSI_TCCR1_HSRD_TOCNT_SHIFT     0
/*@}*/

/** @defgroup dsi_tccr2_values DSI_TCCR2 values
 * @ingroup dsihost_registers
 * @brief  DSI Host timeout counter configuration 2
@{*/
/* Reserved[31:16] (0) */
/* LPRD_TOCNT[15:0] (0), Low-power read timeout counter */
#define DSI_TCCR2_LPRD_TOCNT_MASK      0x0000FFFF
#define DSI_TCCR2_LPRD_TOCNT_SHIFT     0
/*@}*/

/** @defgroup dsi_tccr3_values DSI_TCCR3 values
 * @ingroup dsihost_registers
 * @brief  DSI Host timeout counter configuration 3
@{*/
typedef enum {
	/* Reserved[31:25] (0) */
	/* PM[24] (0), Presp mode */
	DSI_TCCR3_PM                     = 1<<24
	/* Reserved[23:16] (0) */
	/* HSWR_TOCNT[15:0] (0), High-speed write timeout counter */
} dsi_tccr3_flags_t;
#define DSI_TCCR3_FLAGS_MASK           0x01000000
#define DSI_TCCR3_HSWR_TOCNT_MASK      0x0000FFFF
#define DSI_TCCR3_HSWR_TOCNT_SHIFT     0
/*@}*/

/** @defgroup dsi_tccr4_values DSI_TCCR4 values
 * @ingroup dsihost_registers
 * @brief  DSI Host timeout counter configuration 4
@{*/
/* Reserved[31:16] (0) */
/* LPWR_TOCNT[15:0] (0), Low-power write timeout counter */
#define DSI_TCCR4_LPWR_TOCNT_MASK      0x0000FFFF
#define DSI_TCCR4_LPWR_TOCNT_SHIFT     0
/*@}*/

/** @defgroup dsi_tccr5_values DSI_TCCR5 values
 * @ingroup dsihost_registers
 * @brief  DSI Host timeout counter configuration 5
@{*/
/* Reserved[31:16] (0) */
/* BTA_TOCNT[15:0] (0), Bus-turn-around timeout counter */
#define DSI_TCCR5_BTA_TOCNT_MASK       0x0000FFFF
#define DSI_TCCR5_BTA_TOCNT_SHIFT      0
/*@}*/

/** @defgroup dsi_clcr_values DSI_CLCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host clock lane configuration
@{*/
typedef enum {
	/* Reserved[31:2] (0) */
	/* ACR[1] (0), Automatic clock lane control */
	DSI_CLCR_ACR                     = 1<<1,
	/* DPCC[0] (0), D-PHY clock control */
	DSI_CLCR_DPCC                    = 1<<0
} dsi_clcr_flags_t;
#define DSI_CLCR_FLAGS_MASK            0x00000003
/*@}*/

/** @defgroup dsi_cltcr_values DSI_CLTCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host clock lane timer configuration
@{*/
/* Reserved[31:26] (0) */
/* HS2LP_TIME[25:16] (0), High-speed to low-power time */
#define DSI_CLTCR_HS2LP_TIME_MASK      0x000003FF
#define DSI_CLTCR_HS2LP_TIME_SHIFT     16
/* Reserved[15:10] (0) */
/* LP2HS_TIME[9:0] (0), Low-power to high-speed time */
#define DSI_CLTCR_LP2HS_TIME_MASK      0x000003FF
#define DSI_CLTCR_LP2HS_TIME_SHIFT     0
/*@}*/

/** @defgroup dsi_dltcr_values DSI_DLTCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host data lane timer configuration
@{*/
/* HS2LP_TIME[31:24] (0), High-speed To low-power time */
#define DSI_DLTCR_HS2LP_TIME_MASK      0x000000FF
#define DSI_DLTCR_HS2LP_TIME_SHIFT     24
/* LP2HS_TIME[23:16] (0), Low-power to high-speed time */
#define DSI_DLTCR_LP2HS_TIME_MASK      0x000000FF
#define DSI_DLTCR_LP2HS_TIME_SHIFT     16
/* Reserved[15] (0) */
/* MRD_TIME[14:0] (0), Maximum read time */
#define DSI_DLTCR_MRD_TIME_MASK        0x00007FFF
#define DSI_DLTCR_MRD_TIME_SHIFT       0
/*@}*/

/** @defgroup dsi_pctlr_values DSI_PCTLR values
 * @ingroup dsihost_registers
 * @brief  DSI Host PHY control
@{*/
typedef enum {
	/* Reserved[31:3] (0) */
	/* CKE[2] (0), Clock enable */
	DSI_PCTLR_CKE                    = 1<<2,
	/* DEN[1] (0), Digital enable */
	DSI_PCTLR_DEN                    = 1<<1
	/* Reserved[0] (0) */
} dsi_pctlr_flags_t;
#define DSI_PCTLR_FLAGS_MASK           0x00000006
/*@}*/

/** @defgroup dsi_pconfr_values DSI_PCONFR values
 * @ingroup dsihost_registers
 * @brief  DSI Host PHY configuration
@{*/
/* Reserved[31:16] (0) */
/* SW_TIME[15:8] (0), Stop wait time */
#define DSI_PCONFR_SW_TIME_MASK        0x000000FF
#define DSI_PCONFR_SW_TIME_SHIFT       8
/* Reserved[7:2] (0) */
/* NL[1:0] (1), Number of lanes */
#define DSI_PCONFR_NL_MASK             0x00000003
#define DSI_PCONFR_NL_SHIFT            0
/*@}*/

/** @defgroup dsi_pucr_values DSI_PUCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host PHY ULPS control
@{*/
typedef enum {
	/* Reserved[31:4] (0) */
	/* UEDL[3] (0), ULPS exit on data lane */
	DSI_PUCR_UEDL                    = 1<<3,
	/* URDL[2] (0), ULPS request on data lane */
	DSI_PUCR_URDL                    = 1<<2,
	/* UECL[1] (0), ULPS exit on clock lane */
	DSI_PUCR_UECL                    = 1<<1,
	/* URCL[0] (0), ULPS request on clock lane */
	DSI_PUCR_URCL                    = 1<<0
} dsi_pucr_flags_t;
#define DSI_PUCR_FLAGS_MASK            0x0000000F
/*@}*/

/** @defgroup dsi_pttcr_values DSI_PTTCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host PHY TX triggers configuration
@{*/
/* Reserved[31:4] (0) */
/* TX_TRIG[3:0] (0), Transmission trigger */
#define DSI_PTTCR_TX_TRIG_MASK         0x0000000F
#define DSI_PTTCR_TX_TRIG_SHIFT        0
/*@}*/

/** @defgroup dsi_psr_values DSI_PSR values
 * @ingroup dsihost_registers
 * @brief  DSI Host PHY status
@{*/
typedef enum {
	/* Reserved[31:9] (10) */
	/* UAN1[8] (1), ULPS active not lane 1 */
	DSI_PSR_UAN1                     = 1<<8,
	/* PSS1[7] (0), PHY stop state lane 1 */
	DSI_PSR_PSS1                     = 1<<7,
	/* RUE0[6] (0), RX ULPS escape lane 0 */
	DSI_PSR_RUE0                     = 1<<6,
	/* UAN0[5] (1), ULPS active not lane 1 */
	DSI_PSR_UAN0                     = 1<<5,
	/* PSS0[4] (0), PHY stop state lane 0 */
	DSI_PSR_PSS0                     = 1<<4,
	/* UANC[3] (1), ULPS active not clock lane */
	DSI_PSR_UANC                     = 1<<3,
	/* PSSC[2] (0), PHY stop state clock lane */
	DSI_PSR_PSSC                     = 1<<2,
	/* PD[1] (0), PHY direction */
	DSI_PSR_PD                       = 1<<1
	/* Reserved[0] (0) */
} dsi_psr_flags_t;
#define DSI_PSR_FLAGS_MASK             0x000001FE
/*@}*/

/** @defgroup dsi_isr0_values DSI_ISR0 values
 * @ingroup dsihost_registers
 * @brief  DSI Host interrupt and status 0
@{*/
typedef enum {
	/* Reserved[31:21] (0) */
	/* PE4[20] (0), PHY error 4 */
	DSI_ISR0_PE4                     = 1<<20,
	/* PE3[19] (0), PHY error 3 */
	DSI_ISR0_PE3                     = 1<<19,
	/* PE2[18] (0), PHY error 2 */
	DSI_ISR0_PE2                     = 1<<18,
	/* PE1[17] (0), PHY error 1 */
	DSI_ISR0_PE1                     = 1<<17,
	/* PE0[16] (0), PHY error 0 */
	DSI_ISR0_PE0                     = 1<<16,
	/* AE15[15] (0), Acknowledge error 15 */
	DSI_ISR0_AE15                    = 1<<15,
	/* AE14[14] (0), Acknowledge error 14 */
	DSI_ISR0_AE14                    = 1<<14,
	/* AE13[13] (0), Acknowledge error 13 */
	DSI_ISR0_AE13                    = 1<<13,
	/* AE12[12] (0), Acknowledge error 12 */
	DSI_ISR0_AE12                    = 1<<12,
	/* AE11[11] (0), Acknowledge error 11 */
	DSI_ISR0_AE11                    = 1<<11,
	/* AE10[10] (0), Acknowledge error 10 */
	DSI_ISR0_AE10                    = 1<<10,
	/* AE9[9] (0), Acknowledge error 9 */
	DSI_ISR0_AE9                     = 1<<9,
	/* AE8[8] (0), Acknowledge error 8 */
	DSI_ISR0_AE8                     = 1<<8,
	/* AE7[7] (0), Acknowledge error 7 */
	DSI_ISR0_AE7                     = 1<<7,
	/* AE6[6] (0), Acknowledge error 6 */
	DSI_ISR0_AE6                     = 1<<6,
	/* AE5[5] (0), Acknowledge error 5 */
	DSI_ISR0_AE5                     = 1<<5,
	/* AE4[4] (0), Acknowledge error 4 */
	DSI_ISR0_AE4                     = 1<<4,
	/* AE3[3] (0), Acknowledge error 3 */
	DSI_ISR0_AE3                     = 1<<3,
	/* AE2[2] (0), Acknowledge error 2 */
	DSI_ISR0_AE2                     = 1<<2,
	/* AE1[1] (0), Acknowledge error 1 */
	DSI_ISR0_AE1                     = 1<<1,
	/* AE0[0] (0), Acknowledge error 0 */
	DSI_ISR0_AE0                     = 1<<0
} dsi_isr0_flags_t;
#define DSI_ISR0_FLAGS_MASK            0x001FFFFF
/*@}*/

/** @defgroup dsi_isr1_values DSI_ISR1 values
 * @ingroup dsihost_registers
 * @brief  DSI Host interrupt and status 1
@{*/
typedef enum {
	/* Reserved[31:13] (0) */
	/* GPRXE[12] (0), Generic payload receive error */
	DSI_ISR1_GPRXE                   = 1<<12,
	/* GPRDE[11] (0), Generic payload read error */
	DSI_ISR1_GPRDE                   = 1<<11,
	/* GPTXE[10] (0), Generic payload transmit error */
	DSI_ISR1_GPTXE                   = 1<<10,
	/* GPWRE[9] (0), Generic payload write error */
	DSI_ISR1_GPWRE                   = 1<<9,
	/* GCWRE[8] (0), Generic command write error */
	DSI_ISR1_GCWRE                   = 1<<8,
	/* LPWRE[7] (0), LTDC payload write error */
	DSI_ISR1_LPWRE                   = 1<<7,
	/* EOTPE[6] (0), EoTp error */
	DSI_ISR1_EOTPE                   = 1<<6,
	/* PSE[5] (0), Packet size error */
	DSI_ISR1_PSE                     = 1<<5,
	/* CRCE[4] (0), CRC error */
	DSI_ISR1_CRCE                    = 1<<4,
	/* ECCME[3] (0), ECC multi-bit error */
	DSI_ISR1_ECCME                   = 1<<3,
	/* ECCSE[2] (0), ECC single-bit error */
	DSI_ISR1_ECCSE                   = 1<<2,
	/* TOLPRX[1] (0), Timeout low-power reception */
	DSI_ISR1_TOLPRX                  = 1<<1,
	/* TOHSTX[0] (0), Timeout high-speed transmission */
	DSI_ISR1_TOHSTX                  = 1<<0
} dsi_isr1_flags_t;
#define DSI_ISR1_FLAGS_MASK            0x00001FFF
/*@}*/

/** @defgroup dsi_ier0_values DSI_IER0 values
 * @ingroup dsihost_registers
 * @brief  DSI Host interrupt enable 0
@{*/
typedef enum {
	/* Reserved[31:21] (0) */
	/* PE4IE[20] (0), PHY error 4 interrupt enable */
	DSI_IER0_PE4IE                   = 1<<20,
	/* PE3IE[19] (0), PHY error 3 interrupt enable */
	DSI_IER0_PE3IE                   = 1<<19,
	/* PE2IE[18] (0), PHY error 2 interrupt enable */
	DSI_IER0_PE2IE                   = 1<<18,
	/* PE1IE[17] (0), PHY error 1 interrupt enable */
	DSI_IER0_PE1IE                   = 1<<17,
	/* PE0IE[16] (0), PHY error 0 interrupt enable */
	DSI_IER0_PE0IE                   = 1<<16,
	/* AE15IE[15] (0), Acknowledge error 15 interrupt enable */
	DSI_IER0_AE15IE                  = 1<<15,
	/* AE14IE[14] (0), Acknowledge error 14 interrupt enable */
	DSI_IER0_AE14IE                  = 1<<14,
	/* AE13IE[13] (0), Acknowledge error 13 interrupt enable */
	DSI_IER0_AE13IE                  = 1<<13,
	/* AE12IE[12] (0), Acknowledge error 12 interrupt enable */
	DSI_IER0_AE12IE                  = 1<<12,
	/* AE11IE[11] (0), Acknowledge error 11 interrupt enable */
	DSI_IER0_AE11IE                  = 1<<11,
	/* AE10IE[10] (0), Acknowledge error 10 interrupt enable */
	DSI_IER0_AE10IE                  = 1<<10,
	/* AE9IE[9] (0), Acknowledge error 9 interrupt enable */
	DSI_IER0_AE9IE                   = 1<<9,
	/* AE8IE[8] (0), Acknowledge error 8 interrupt enable */
	DSI_IER0_AE8IE                   = 1<<8,
	/* AE7IE[7] (0), Acknowledge error 7 interrupt enable */
	DSI_IER0_AE7IE                   = 1<<7,
	/* AE6IE[6] (0), Acknowledge error 6 interrupt enable */
	DSI_IER0_AE6IE                   = 1<<6,
	/* AE5IE[5] (0), Acknowledge error 5 interrupt enable */
	DSI_IER0_AE5IE                   = 1<<5,
	/* AE4IE[4] (0), Acknowledge error 4 interrupt enable */
	DSI_IER0_AE4IE                   = 1<<4,
	/* AE3IE[3] (0), Acknowledge error 3 interrupt enable */
	DSI_IER0_AE3IE                   = 1<<3,
	/* AE2IE[2] (0), Acknowledge error 2 interrupt enable */
	DSI_IER0_AE2IE                   = 1<<2,
	/* AE1IE[1] (0), Acknowledge error 1 interrupt enable */
	DSI_IER0_AE1IE                   = 1<<1,
	/* AE0IE[0] (0), Acknowledge error 0 interrupt enable */
	DSI_IER0_AE0IE                   = 1<<0
} dsi_ier0_flags_t;
#define DSI_IER0_FLAGS_MASK            0x001FFFFF
/*@}*/

/** @defgroup dsi_ier1_values DSI_IER1 values
 * @ingroup dsihost_registers
 * @brief  DSI Host interrupt enable 1
@{*/
typedef enum {
	/* Reserved[31:13] (0) */
	/* GPRXEIE[12] (0), Generic payload receive error interrupt enable */
	DSI_IER1_GPRXEIE                 = 1<<12,
	/* GPRDEIE[11] (0), Generic payload read error interrupt enable */
	DSI_IER1_GPRDEIE                 = 1<<11,
	/* GPTXEIE[10] (0), Generic payload transmit error interrupt enable */
	DSI_IER1_GPTXEIE                 = 1<<10,
	/* GPWREIE[9] (0), Generic payload write error interrupt enable */
	DSI_IER1_GPWREIE                 = 1<<9,
	/* GCWREIE[8] (0), Generic command write error interrupt enable */
	DSI_IER1_GCWREIE                 = 1<<8,
	/* LPWREIE[7] (0), LTDC payload write error interrupt enable */
	DSI_IER1_LPWREIE                 = 1<<7,
	/* EOTPEIE[6] (0), EoTp error interrupt enable */
	DSI_IER1_EOTPEIE                 = 1<<6,
	/* PSEIE[5] (0), Packet size error interrupt enable */
	DSI_IER1_PSEIE                   = 1<<5,
	/* CRCEIE[4] (0), CRC error interrupt enable */
	DSI_IER1_CRCEIE                  = 1<<4,
	/* ECCMEIE[3] (0), ECC multi-bit error interrupt enable */
	DSI_IER1_ECCMEIE                 = 1<<3,
	/* ECCSEIE[2] (0), ECC single-bit error interrupt enable */
	DSI_IER1_ECCSEIE                 = 1<<2,
	/* TOLPRXIE[1] (0), Timeout low-power reception interrupt enable */
	DSI_IER1_TOLPRXIE                = 1<<1,
	/* TOHSTXIE[0] (0), Timeout high-speed transmission interrupt enable */
	DSI_IER1_TOHSTXIE                = 1<<0
} dsi_ier1_flags_t;
#define DSI_IER1_FLAGS_MASK            0x00001FFF
/*@}*/

/** @defgroup dsi_fir0_values DSI_FIR0 values
 * @ingroup dsihost_registers
 * @brief  DSI Host force interrupt 0
@{*/
typedef enum {
	/* Reserved[31:21] (0) */
	/* FPE4[20] (0), Force PHY error 4 */
	DSI_FIR0_FPE4                    = 1<<20,
	/* FPE3[19] (0), Force PHY error 3 */
	DSI_FIR0_FPE3                    = 1<<19,
	/* FPE2[18] (0), Force PHY error 2 */
	DSI_FIR0_FPE2                    = 1<<18,
	/* FPE1[17] (0), Force PHY error 1 */
	DSI_FIR0_FPE1                    = 1<<17,
	/* FPE0[16] (0), Force PHY error 0 */
	DSI_FIR0_FPE0                    = 1<<16,
	/* FAE15[15] (0), Force acknowledge error 15 */
	DSI_FIR0_FAE15                   = 1<<15,
	/* FAE14[14] (0), Force acknowledge error 14 */
	DSI_FIR0_FAE14                   = 1<<14,
	/* FAE13[13] (0), Force acknowledge error 13 */
	DSI_FIR0_FAE13                   = 1<<13,
	/* FAE12[12] (0), Force acknowledge error 12 */
	DSI_FIR0_FAE12                   = 1<<12,
	/* FAE11[11] (0), Force acknowledge error 11 */
	DSI_FIR0_FAE11                   = 1<<11,
	/* FAE10[10] (0), Force acknowledge error 10 */
	DSI_FIR0_FAE10                   = 1<<10,
	/* FAE9[9] (0), Force acknowledge error 9 */
	DSI_FIR0_FAE9                    = 1<<9,
	/* FAE8[8] (0), Force acknowledge error 8 */
	DSI_FIR0_FAE8                    = 1<<8,
	/* FAE7[7] (0), Force acknowledge error 7 */
	DSI_FIR0_FAE7                    = 1<<7,
	/* FAE6[6] (0), Force acknowledge error 6 */
	DSI_FIR0_FAE6                    = 1<<6,
	/* FAE5[5] (0), Force acknowledge error 5 */
	DSI_FIR0_FAE5                    = 1<<5,
	/* FAE4[4] (0), Force acknowledge error 4 */
	DSI_FIR0_FAE4                    = 1<<4,
	/* FAE3[3] (0), Force acknowledge error 3 */
	DSI_FIR0_FAE3                    = 1<<3,
	/* FAE2[2] (0), Force acknowledge error 2 */
	DSI_FIR0_FAE2                    = 1<<2,
	/* FAE1[1] (0), Force acknowledge error 1 */
	DSI_FIR0_FAE1                    = 1<<1,
	/* FAE0[0] (0), Force acknowledge error 0 */
	DSI_FIR0_FAE0                    = 1<<0
} dsi_fir0_flags_t;
#define DSI_FIR0_FLAGS_MASK            0x001FFFFF
/*@}*/

/** @defgroup dsi_fir1_values DSI_FIR1 values
 * @ingroup dsihost_registers
 * @brief  DSI Host force interrupt 1
@{*/
typedef enum {
	/* Reserved[31:13] (0) */
	/* FGPRXE[12] (0), Force generic payload receive error */
	DSI_FIR1_FGPRXE                  = 1<<12,
	/* FGPRDE[11] (0), Force generic payload read error */
	DSI_FIR1_FGPRDE                  = 1<<11,
	/* FGPTXE[10] (0), Force generic payload transmit error */
	DSI_FIR1_FGPTXE                  = 1<<10,
	/* FGPWRE[9] (0), Force generic payload write error */
	DSI_FIR1_FGPWRE                  = 1<<9,
	/* FGCWRE[8] (0), Force generic command write error */
	DSI_FIR1_FGCWRE                  = 1<<8,
	/* FLPWRE[7] (0), Force LTDC payload write error */
	DSI_FIR1_FLPWRE                  = 1<<7,
	/* FEOTPE[6] (0), Force EoTp error */
	DSI_FIR1_FEOTPE                  = 1<<6,
	/* FPSE[5] (0), Force packet size error */
	DSI_FIR1_FPSE                    = 1<<5,
	/* FCRCE[4] (0), Force CRC error */
	DSI_FIR1_FCRCE                   = 1<<4,
	/* FECCME[3] (0), Force ECC multi-bit error */
	DSI_FIR1_FECCME                  = 1<<3,
	/* FECCSE[2] (0), Force ECC single-bit error */
	DSI_FIR1_FECCSE                  = 1<<2,
	/* FTOLPRX[1] (0), Force timeout low-power reception */
	DSI_FIR1_FTOLPRX                 = 1<<1,
	/* FTOHSTX[0] (0), Force timeout high-speed transmission */
	DSI_FIR1_FTOHSTX                 = 1<<0
} dsi_fir1_flags_t;
#define DSI_FIR1_FLAGS_MASK            0x00001FFF
/*@}*/

/** @defgroup dsi_vscr_values DSI_VSCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video shadow control
@{*/
typedef enum {
	/* Reserved[31:9] (0) */
	/* UR[8] (0), Update register */
	DSI_VSCR_UR                      = 1<<8,
	/* Reserved[7:1] (0) */
	/* EN[0] (0), Enable */
	DSI_VSCR_EN                      = 1<<0
} dsi_vscr_flags_t;
#define DSI_VSCR_FLAGS_MASK            0x00000101
/*@}*/

/** @defgroup dsi_lcvcidr_values DSI_LCVCIDR values
 * @ingroup dsihost_registers
 * @brief  DSI Host LTDC current VCID
@{*/
/* Reserved[31:2] (0) */
/* VCID[1:0] (0), Virtual channel ID */
#define DSI_LCVCIDR_VCID_MASK          0x00000003
#define DSI_LCVCIDR_VCID_SHIFT         0
/*@}*/

/** @defgroup dsi_lcccr_values DSI_LCCCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host LTDC current color coding
@{*/
typedef enum {
	/* Reserved[31:9] (0) */
	/* LPE[8] (0), Loosely packed enable */
	DSI_LCCCR_LPE                    = 1<<8
	/* Reserved[7:4] (0) */
	/* COLC[3:0] (0), Color coding */
} dsi_lcccr_flags_t;
#define DSI_LCCCR_FLAGS_MASK           0x00000100
#define DSI_LCCCR_COLC_MASK            0x0000000F
#define DSI_LCCCR_COLC_SHIFT           0
/*@}*/

/** @defgroup dsi_lpmccr_values DSI_LPMCCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host low-power mode current configuration
@{*/
/* Reserved[31:24] (0) */
/* LPSIZE[23:16] (0), Largest packet size */
#define DSI_LPMCCR_LPSIZE_MASK         0x000000FF
#define DSI_LPMCCR_LPSIZE_SHIFT        16
/* Reserved[15:8] (0) */
/* VLPSIZE[7:0] (0), VACT largest packet size */
#define DSI_LPMCCR_VLPSIZE_MASK        0x000000FF
#define DSI_LPMCCR_VLPSIZE_SHIFT       0
/*@}*/

/** @defgroup dsi_vmccr_values DSI_VMCCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video mode current configuration
@{*/
typedef enum {
	/* Reserved[31:10] (0) */
	/* LPCE[9] (0), Low-power command enable */
	DSI_VMCCR_LPCE                   = 1<<9,
	/* FBTAAE[8] (0), Frame BTA acknowledge enable */
	DSI_VMCCR_FBTAAE                 = 1<<8,
	/* LPHFE[7] (0), Low-power horizontal front-porch enable */
	DSI_VMCCR_LPHFE                  = 1<<7,
	/* LPHBPE[6] (0), Low-power horizontal back-porch enable */
	DSI_VMCCR_LPHBPE                 = 1<<6,
	/* LPVAE[5] (0), Low-power vertical active enable */
	DSI_VMCCR_LPVAE                  = 1<<5,
	/* LPVFPE[4] (0), Low-power vertical front-porch enable */
	DSI_VMCCR_LPVFPE                 = 1<<4,
	/* LPVBPE[3] (0), Low-power vertical back-porch enable */
	DSI_VMCCR_LPVBPE                 = 1<<3,
	/* LPVSAE[2] (0), Low-power vertical sync time enable */
	DSI_VMCCR_LPVSAE                 = 1<<2
	/* VMT[1:0] (0), Video mode type */
} dsi_vmccr_flags_t;
#define DSI_VMCCR_FLAGS_MASK           0x000003FC
#define DSI_VMCCR_VMT_MASK             0x00000003
#define DSI_VMCCR_VMT_SHIFT            0
/*@}*/

/** @defgroup dsi_vpccr_values DSI_VPCCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video packet current configuration
@{*/
/* Reserved[31:14] (0) */
/* VPSIZE[13:0] (0), Video packet size */
#define DSI_VPCCR_VPSIZE_MASK          0x00003FFF
#define DSI_VPCCR_VPSIZE_SHIFT         0
/*@}*/

/** @defgroup dsi_vcccr_values DSI_VCCCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video chunks current configuration
@{*/
/* Reserved[31:13] (0) */
/* NUMC[12:0] (0), Number of chunks */
#define DSI_VCCCR_NUMC_MASK            0x00001FFF
#define DSI_VCCCR_NUMC_SHIFT           0
/*@}*/

/** @defgroup dsi_vnpccr_values DSI_VNPCCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video null packet current configuration
@{*/
/* Reserved[31:13] (0) */
/* NPSIZE[12:0] (0), Null packet size */
#define DSI_VNPCCR_NPSIZE_MASK         0x00001FFF
#define DSI_VNPCCR_NPSIZE_SHIFT        0
/*@}*/

/** @defgroup dsi_vhsaccr_values DSI_VHSACCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video HSA current configuration
@{*/
/* Reserved[31:12] (0) */
/* HSA[11:0] (0), Horizontal synchronism active duration */
#define DSI_VHSACCR_HSA_MASK           0x00000FFF
#define DSI_VHSACCR_HSA_SHIFT          0
/*@}*/

/** @defgroup dsi_vhbpccr_values DSI_VHBPCCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video HBP current configuration
@{*/
/* Reserved[31:12] (0) */
/* HBP[11:0] (0), Horizontal back-porch duration */
#define DSI_VHBPCCR_HBP_MASK           0x00000FFF
#define DSI_VHBPCCR_HBP_SHIFT          0
/*@}*/

/** @defgroup dsi_vlccr_values DSI_VLCCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video line current configuration
@{*/
/* Reserved[31:15] (0) */
/* HLINE[14:0] (0), Horizontal line duration */
#define DSI_VLCCR_HLINE_MASK           0x00007FFF
#define DSI_VLCCR_HLINE_SHIFT          0
/*@}*/

/** @defgroup dsi_vvsaccr_values DSI_VVSACCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video VSA current configuration
@{*/
/* Reserved[31:10] (0) */
/* VSA[9:0] (0), Vertical synchronism active duration */
#define DSI_VVSACCR_VSA_MASK           0x000003FF
#define DSI_VVSACCR_VSA_SHIFT          0
/*@}*/

/** @defgroup dsi_vvbpccr_values DSI_VVBPCCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video VBP current configuration
@{*/
/* Reserved[31:10] (0) */
/* VBP[9:0] (0), Vertical back-porch duration */
#define DSI_VVBPCCR_VBP_MASK           0x000003FF
#define DSI_VVBPCCR_VBP_SHIFT          0
/*@}*/

/** @defgroup dsi_vvfpccr_values DSI_VVFPCCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video VFP current configuration
@{*/
/* Reserved[31:10] (0) */
/* VFP[9:0] (0), Vertical front-porch duration */
#define DSI_VVFPCCR_VFP_MASK           0x000003FF
#define DSI_VVFPCCR_VFP_SHIFT          0
/*@}*/

/** @defgroup dsi_vvaccr_values DSI_VVACCR values
 * @ingroup dsihost_registers
 * @brief  DSI Host video VA current configuration
@{*/
/* Reserved[31:14] (0) */
/* VA[13:0] (0), Vertical active duration */
#define DSI_VVACCR_VA_MASK             0x00003FFF
#define DSI_VVACCR_VA_SHIFT            0
/*@}*/


/**
 * DSI Wrapper
 */


/** @defgroup dsi_wcfgr_values DSI_WCFGR values
 * @ingroup dsihost_registers
 * @brief  DSI wrapper configuration
@{*/
typedef enum {
	/* Reserved[31:8] (0) */
	/* VSPOL[7] (0), VSync polarity */
	DSI_WCFGR_VSPOL                  = 1<<7,
	/* AR[6] (0), Automatic refresh */
	DSI_WCFGR_AR                     = 1<<6,
	/* TEPOL[5] (0), TE polarity */
	DSI_WCFGR_TEPOL                  = 1<<5,
	/* TESRC[4] (0), TE source */
	DSI_WCFGR_TESRC                  = 1<<4,
	/* COLMUX[3:1] (0), Color multiplexing */
	/* DSIM[0] (0), DSI mode */
	DSI_WCFGR_DSIM                   = 1<<0
} dsi_wcfgr_flags_t;
#define DSI_WCFGR_FLAGS_MASK           0x000000F1
#define DSI_WCFGR_COLMUX_MASK          0x00000007
#define DSI_WCFGR_COLMUX_SHIFT         1
/*@}*/

/** @defgroup dsi_wcr_values DSI_WCR values
 * @ingroup dsihost_registers
 * @brief  DSI wrapper control
@{*/
typedef enum {
	/* Reserved[31:4] (0) */
	/* DSIEN[3] (0), DSI enable */
	DSI_WCR_DSIEN                    = 1<<3,
	/* LTDCEN[2] (0), LTDC enable */
	DSI_WCR_LTDCEN                   = 1<<2,
	/* SHTDN[1] (0), Shutdown */
	DSI_WCR_SHTDN                    = 1<<1,
	/* COLM[0] (0), Color mode */
	DSI_WCR_COLM                     = 1<<0
} dsi_wcr_flags_t;
#define DSI_WCR_FLAGS_MASK             0x0000000F
/*@}*/

/** @defgroup dsi_wier_values DSI_WIER values
 * @ingroup dsihost_registers
 * @brief  DSI wrapper interrupt enable
@{*/
typedef enum {
	/* Reserved[31:14] (0) */
	/* RRIE[13] (0), Regulator ready interrupt enable */
	DSI_WIER_RRIE                    = 1<<13,
	/* Reserved[12:11] (0) */
	/* PLLUIE[10] (0), PLL unlock interrupt enable */
	DSI_WIER_PLLUIE                  = 1<<10,
	/* PLLLIE[9] (0), PLL lock interrupt enable */
	DSI_WIER_PLLLIE                  = 1<<9,
	/* Reserved[8:2] (0) */
	/* ERIE[1] (0), End of refresh interrupt enable */
	DSI_WIER_ERIE                    = 1<<1,
	/* TEIE[0] (0), Tearing effect interrupt enable */
	DSI_WIER_TEIE                    = 1<<0
} dsi_wier_flags_t;
#define DSI_WIER_FLAGS_MASK            0x00002603
/*@}*/

/** @defgroup dsi_wisr_values DSI_WISR values
 * @ingroup dsihost_registers
 * @brief  DSI wrapper interrupt and status
@{*/
typedef enum {
	/* Reserved[31:14] (0) */
	/* RRIF[13] (0), Regulator ready interrupt flag */
	DSI_WISR_RRIF                    = 1<<13,
	/* RRS[12] (0), Regulator ready status */
	DSI_WISR_RRS                     = 1<<12,
	/* Reserved[11] (0) */
	/* PLLUIF[10] (0), PLL unlock interrupt flag */
	DSI_WISR_PLLUIF                  = 1<<10,
	/* PLLLIF[9] (0), PLL lock interrupt flag */
	DSI_WISR_PLLLIF                  = 1<<9,
	/* PLLLS[8] (0), PLL lock status */
	DSI_WISR_PLLLS                   = 1<<8,
	/* Reserved[7:3] (0) */
	/* BUSY[2] (0), Busy flag */
	DSI_WISR_BUSY                    = 1<<2,
	/* ERIF[1] (0), End of refresh interrupt flag */
	DSI_WISR_ERIF                    = 1<<1,
	/* TEIF[0] (0), Tearing effect interrupt flag */
	DSI_WISR_TEIF                    = 1<<0
} dsi_wisr_flags_t;
#define DSI_WISR_FLAGS_MASK            0x00003707
/*@}*/

/** @defgroup dsi_wifcr_values DSI_WIFCR values
 * @ingroup dsihost_registers
 * @brief  DSI wrapper interrupt flag clear
@{*/
typedef enum {
	/* Reserved[31:14] (0) */
	/* CRRIF[13] (0), Clear regulator ready interrupt flag */
	DSI_WIFCR_CRRIF                  = 1<<13,
	/* Reserved[12:11] (0) */
	/* CPLLUIF[10] (0), Clear PLL unlock interrupt flag */
	DSI_WIFCR_CPLLUIF                = 1<<10,
	/* CPLLLIF[9] (0), Clear PLL lock interrupt flag */
	DSI_WIFCR_CPLLLIF                = 1<<9,
	/* Reserved[8:2] (0) */
	/* CERIF[1] (0), Clear end of refresh interrupt flag */
	DSI_WIFCR_CERIF                  = 1<<1,
	/* CTEIF[0] (0), Clear tearing effect interrupt flag */
	DSI_WIFCR_CTEIF                  = 1<<0
} dsi_wifcr_flags_t;
#define DSI_WIFCR_FLAGS_MASK           0x00002603
/*@}*/

/** @defgroup dsi_wpcr0_values DSI_WPCR0 values
 * @ingroup dsihost_registers
 * @brief  DSI wrapper PHY configuration 0
@{*/
typedef enum {
	/* Reserved[31:28] (0) */
	/* TCLKPOSTEN[27] (0), Custom time for tCLK-POST enable */
	DSI_WPCR0_TCLKPOSTEN             = 1<<27,
	/* TLPXCEN[26] (0), Custom time for tLPX for clock lane enable */
	DSI_WPCR0_TLPXCEN                = 1<<26,
	/* THSEXITEN[25] (0), Custom time for tHS-EXIT enable */
	DSI_WPCR0_THSEXITEN              = 1<<25,
	/* TLPXDEN[24] (0), Custom time for tLPX for data lanes enable */
	DSI_WPCR0_TLPXDEN                = 1<<24,
	/* THSZEROEN[23] (0), Custom time for tHS-ZERO enable */
	DSI_WPCR0_THSZEROEN              = 1<<23,
	/* THSTRAILEN[22] (0), Custom time for tHS-TRAIL enable */
	DSI_WPCR0_THSTRAILEN             = 1<<22,
	/* THSPREPEN[21] (0), Custom time for tHS-PREPARE enable */
	DSI_WPCR0_THSPREPEN              = 1<<21,
	/* TCLKZEROEN[20] (0), Custom time for tCLK-ZERO enable */
	DSI_WPCR0_TCLKZEROEN             = 1<<20,
	/* TCLKPREPEN[19] (0), Custom time for tCLK-PREPARE enable */
	DSI_WPCR0_TCLKPREPEN             = 1<<19,
	/* PDEN[18] (0), Pull-down enable */
	DSI_WPCR0_PDEN                   = 1<<18,
	/* Reserved[17] (0) */
	/* TDDL[16] (0), Turn disable data lanes */
	DSI_WPCR0_TDDL                   = 1<<16,
	/* Reserved[15] (0) */
	/* CDOFFDL[14] (0), Contention detection OFF on data lanes */
	DSI_WPCR0_CDOFFDL                = 1<<14,
	/* FTXSMDL[13] (0), Force in TX Stop mode the data lanes */
	DSI_WPCR0_FTXSMDL                = 1<<13,
	/* FTXSMCL[12] (0), Force in TX Stop mode the clock lane */
	DSI_WPCR0_FTXSMCL                = 1<<12,
	/* HSIDL1[11] (0), Invert the high-speed data signal on data lane 1 */
	DSI_WPCR0_HSIDL1                 = 1<<11,
	/* HSIDL0[10] (0), Invert the high-speed data signal on data lane 0 */
	DSI_WPCR0_HSIDL0                 = 1<<10,
	/* HSICL[9] (0), Invert high-speed data signal on clock lane */
	DSI_WPCR0_HSICL                  = 1<<9,
	/* SWDL1[8] (0), Swap data lane 1 pins */
	DSI_WPCR0_SWDL1                  = 1<<8,
	/* SWDL0[7] (0), Swap data lane 0 pins */
	DSI_WPCR0_SWDL0                  = 1<<7,
	/* SWCL[6] (0), Swap clock lane pins */
	DSI_WPCR0_SWCL                   = 1<<6
	/* UIX4[5:0] (0), Unit interval multiplied by 4 */
} dsi_wpcr0_flags_t;
#define DSI_WPCR0_FLAGS_MASK           0x0FFD7FC0
#define DSI_WPCR0_UIX4_MASK            0x0000003F
#define DSI_WPCR0_UIX4_SHIFT           0
/*@}*/

/** @defgroup dsi_wpcr1_values DSI_WPCR1 values
 * @ingroup dsihost_registers
 * @brief  DSI wrapper PHY configuration 1
@{*/
typedef enum {
	/* Reserved[31:27] (0) */
	/* LPRXFT[26:25] (0), Low-power RX low-pass filtering tuning */
	/* Reserved[24:23] (0) */
	/* FLPRXLPM[22] (0), Forces LP receiver in low-power mode */
	DSI_WPCR1_FLPRXLPM               = 1<<22,
	/* Reserved[21:20] (0) */
	/* HSTXSRCDL[19:18] (0), High-speed transmission slew-rate control on data lanes */
	/* HSTXSRCCL[17:16] (0), High-speed transmission slew-rate control on clock lane */
	/* Reserved[15:13] (0) */
	/* SDDC[12] (0), SDD control */
	DSI_WPCR1_SDDC                   = 1<<12
	/* Reserved[11:10] (0) */
	/* LPSRCDL[9:8] (0), Low-power transmission slew-rate compensation on data lanes */
	/* LPSRCCL[7:6] (0), Low-power transmission slew-rate compensation on clock lane */
	/* Reserved[5:4] (0) */
	/* HSTXDDL[3:2] (0), High-speed transmission delay on data lanes */
	/* HSTXDCL[1:0] (0), High-speed transmission delay on clock lane */
} dsi_wpcr1_flags_t;
#define DSI_WPCR1_FLAGS_MASK           0x00401000
#define DSI_WPCR1_LPRXFT_MASK          0x00000003
#define DSI_WPCR1_LPRXFT_SHIFT         25
#define DSI_WPCR1_HSTXSRCDL_MASK       0x00000003
#define DSI_WPCR1_HSTXSRCDL_SHIFT      18
#define DSI_WPCR1_HSTXSRCCL_MASK       0x00000003
#define DSI_WPCR1_HSTXSRCCL_SHIFT      16
#define DSI_WPCR1_LPSRCDL_MASK         0x00000003
#define DSI_WPCR1_LPSRCDL_SHIFT        8
#define DSI_WPCR1_LPSRCCL_MASK         0x00000003
#define DSI_WPCR1_LPSRCCL_SHIFT        6
#define DSI_WPCR1_HSTXDDL_MASK         0x00000003
#define DSI_WPCR1_HSTXDDL_SHIFT        2
#define DSI_WPCR1_HSTXDCL_MASK         0x00000003
#define DSI_WPCR1_HSTXDCL_SHIFT        0
/*@}*/

/** @defgroup dsi_wpcr2_values DSI_WPCR2 values
 * @ingroup dsihost_registers
 * @brief  DSI wrapper PHY configuration 2
@{*/
/* THSTRAIL[31:24] (0), tHSTRAIL */
#define DSI_WPCR2_THSTRAIL_MASK        0x000000FF
#define DSI_WPCR2_THSTRAIL_SHIFT       24
/* THSPREP[23:16] (0), tHS-PREPARE */
#define DSI_WPCR2_THSPREP_MASK         0x000000FF
#define DSI_WPCR2_THSPREP_SHIFT        16
/* TCLKZERO[15:8] (0), tCLK-ZERO */
#define DSI_WPCR2_TCLKZERO_MASK        0x000000FF
#define DSI_WPCR2_TCLKZERO_SHIFT       8
/* TCLKPREP[7:0] (0), tCLK-PREPARE */
#define DSI_WPCR2_TCLKPREP_MASK        0x000000FF
#define DSI_WPCR2_TCLKPREP_SHIFT       0
/*@}*/

/** @defgroup dsi_wpcr3_values DSI_WPCR3 values
 * @ingroup dsihost_registers
 * @brief  DSI wrapper PHY configuration 3
@{*/
/* TLPXC[31:24] (0), tLPXC for clock lane */
#define DSI_WPCR3_TLPXC_MASK           0x000000FF
#define DSI_WPCR3_TLPXC_SHIFT          24
/* THSEXIT[23:16] (0), tHSEXIT */
#define DSI_WPCR3_THSEXIT_MASK         0x000000FF
#define DSI_WPCR3_THSEXIT_SHIFT        16
/* TLPXD[15:8] (0), tLPX for data lanes */
#define DSI_WPCR3_TLPXD_MASK           0x000000FF
#define DSI_WPCR3_TLPXD_SHIFT          8
/* THSZERO[7:0] (0), tHS-ZERO */
#define DSI_WPCR3_THSZERO_MASK         0x000000FF
#define DSI_WPCR3_THSZERO_SHIFT        0
/*@}*/

/** @defgroup dsi_wpcr4_values DSI_WPCR4 values
 * @ingroup dsihost_registers
 * @brief  DSI wrapper PHY configuration 4
@{*/
/* Reserved[31:8] (0) */
/* TCLKPOST[7:0] (0), tCLK-POST */
#define DSI_WPCR4_TCLKPOST_MASK        0x000000FF
#define DSI_WPCR4_TCLKPOST_SHIFT       0
/*@}*/

/** @defgroup dsi_wrpcr_values DSI_WRPCR values
 * @ingroup dsihost_registers
 * @brief  DSI wrapper regulator and PLL control
@{*/
typedef enum {
	/* Reserved[31:25] (0) */
	/* REGEN[24] (0), Regulator enable */
	DSI_WRPCR_REGEN                  = 1<<24,
	/* Reserved[23:18] (0) */
	/* ODF[17:16] (0), PLL output division factor */
	/* Reserved[15] (0) */
	/* IDF[14:11] (0), PLL input division factor */
	/* Reserved[10:9] (0) */
	/* NDIV[8:2] (0), PLL loop division factor */
	/* Reserved[1] (0) */
	/* PLLEN[0] (0), PLL enable */
	DSI_WRPCR_PLLEN                  = 1<<0
} dsi_wrpcr_flags_t;
#define DSI_WRPCR_FLAGS_MASK           0x01000001
#define DSI_WRPCR_ODF_MASK             0x00000003
#define DSI_WRPCR_ODF_SHIFT            16
#define DSI_WRPCR_IDF_MASK             0x0000000F
#define DSI_WRPCR_IDF_SHIFT            11
#define DSI_WRPCR_NDIV_MASK            0x0000007F
#define DSI_WRPCR_NDIV_SHIFT           2
/*@}*/





/** @defgroup dsi_functions DSI Functions
 * @ingroup dsi_registers
 * @brief DSI Host Dummi access functions
@{*/


/**
 * DSI Host setter function templates
 */

/* DSI_VR:  DSI Host version */
static inline void dsi_vr_set(uint32_t version)
{
	DSI_VR &= ~((DSI_VR_VERSION_MASK << DSI_VR_VERSION_SHIFT));
	DSI_VR |= ((version & DSI_VR_VERSION_MASK) << DSI_VR_VERSION_SHIFT);
}

/* DSI_CR:  DSI Host control */
static inline void dsi_cr_set(dsi_cr_flags_t flags)
{
	DSI_CR &= ~(DSI_CR_FLAGS_MASK);
	DSI_CR |= (flags & DSI_CR_FLAGS_MASK);
}

/* DSI_CCR:  DSI Host clock control */
static inline void dsi_ccr_set(uint32_t tockdiv, uint32_t txeckdiv)
{
	DSI_CCR &= ~(
		(DSI_CCR_TOCKDIV_MASK << DSI_CCR_TOCKDIV_SHIFT)
	  | (DSI_CCR_TXECKDIV_MASK << DSI_CCR_TXECKDIV_SHIFT));
	DSI_CCR |=
		((tockdiv & DSI_CCR_TOCKDIV_MASK) << DSI_CCR_TOCKDIV_SHIFT)
	  | ((txeckdiv & DSI_CCR_TXECKDIV_MASK) << DSI_CCR_TXECKDIV_SHIFT);
}

/* DSI_LVCIDR:  DSI Host LTDC VCID */
static inline void dsi_lvcidr_set(uint32_t vcid)
{
	DSI_LVCIDR &= ~((DSI_LVCIDR_VCID_MASK << DSI_LVCIDR_VCID_SHIFT));
	DSI_LVCIDR |= ((vcid & DSI_LVCIDR_VCID_MASK) << DSI_LVCIDR_VCID_SHIFT);
}

/* DSI_LCOLCR:  DSI Host LTDC color coding */
static inline void dsi_lcolcr_set(uint32_t colc, dsi_lcolcr_flags_t flags)
{
	DSI_LCOLCR &= ~(
		(DSI_LCOLCR_COLC_MASK << DSI_LCOLCR_COLC_SHIFT)
	  | DSI_LCOLCR_FLAGS_MASK);
	DSI_LCOLCR |=
		((colc & DSI_LCOLCR_COLC_MASK) << DSI_LCOLCR_COLC_SHIFT)
	  | (flags & DSI_LCOLCR_FLAGS_MASK);
}

/* DSI_LPCR:  DSI Host LTDC polarity configuration */
static inline void dsi_lpcr_set(dsi_lpcr_flags_t flags)
{
	DSI_LPCR &= ~(DSI_LPCR_FLAGS_MASK);
	DSI_LPCR |= (flags & DSI_LPCR_FLAGS_MASK);
}

/* DSI_LPMCR:  DSI Host low-power mode configuration */
static inline void dsi_lpmcr_set(uint32_t lpsize, uint32_t vlpsize)
{
	DSI_LPMCR &= ~(
		(DSI_LPMCR_LPSIZE_MASK << DSI_LPMCR_LPSIZE_SHIFT)
	  | (DSI_LPMCR_VLPSIZE_MASK << DSI_LPMCR_VLPSIZE_SHIFT));
	DSI_LPMCR |=
		((lpsize & DSI_LPMCR_LPSIZE_MASK) << DSI_LPMCR_LPSIZE_SHIFT)
	  | ((vlpsize & DSI_LPMCR_VLPSIZE_MASK) << DSI_LPMCR_VLPSIZE_SHIFT);
}

/* DSI_PCR:  DSI Host protocol configuration */
static inline void dsi_pcr_set(dsi_pcr_flags_t flags)
{
	DSI_PCR &= ~(DSI_PCR_FLAGS_MASK);
	DSI_PCR |= (flags & DSI_PCR_FLAGS_MASK);
}

/* DSI_GVCIDR:  DSI Host generic VCID */
static inline void dsi_gvcidr_set(uint32_t vcid)
{
	DSI_GVCIDR &= ~((DSI_GVCIDR_VCID_MASK << DSI_GVCIDR_VCID_SHIFT));
	DSI_GVCIDR |= ((vcid & DSI_GVCIDR_VCID_MASK) << DSI_GVCIDR_VCID_SHIFT);
}

/* DSI_MCR:  DSI Host mode configuration */
static inline void dsi_mcr_set(dsi_mcr_flags_t flags)
{
	DSI_MCR &= ~(DSI_MCR_FLAGS_MASK);
	DSI_MCR |= (flags & DSI_MCR_FLAGS_MASK);
}

/* DSI_VMCR:  DSI Host video mode configuration */
static inline void dsi_vmcr_set(uint32_t vmt, dsi_vmcr_flags_t flags)
{
	DSI_VMCR &= ~(
		(DSI_VMCR_VMT_MASK << DSI_VMCR_VMT_SHIFT)
	  | DSI_VMCR_FLAGS_MASK);
	DSI_VMCR |=
		((vmt & DSI_VMCR_VMT_MASK) << DSI_VMCR_VMT_SHIFT)
	  | (flags & DSI_VMCR_FLAGS_MASK);
}

/* DSI_VPCR:  DSI Host video packet configuration */
static inline void dsi_vpcr_set(uint32_t vpsize)
{
	DSI_VPCR &= ~((DSI_VPCR_VPSIZE_MASK << DSI_VPCR_VPSIZE_SHIFT));
	DSI_VPCR |= ((vpsize & DSI_VPCR_VPSIZE_MASK) << DSI_VPCR_VPSIZE_SHIFT);
}

/* DSI_VCCR:  DSI Host video chunks configuration */
static inline void dsi_vccr_set(uint32_t numc)
{
	DSI_VCCR &= ~((DSI_VCCR_NUMC_MASK << DSI_VCCR_NUMC_SHIFT));
	DSI_VCCR |= ((numc & DSI_VCCR_NUMC_MASK) << DSI_VCCR_NUMC_SHIFT);
}

/* DSI_VNPCR:  DSI Host video null packet configuration */
static inline void dsi_vnpcr_set(uint32_t npsize)
{
	DSI_VNPCR &= ~((DSI_VNPCR_NPSIZE_MASK << DSI_VNPCR_NPSIZE_SHIFT));
	DSI_VNPCR |= ((npsize & DSI_VNPCR_NPSIZE_MASK) << DSI_VNPCR_NPSIZE_SHIFT);
}

/* DSI_VHSACR:  DSI Host video HSA configuration */
static inline void dsi_vhsacr_set(uint32_t hsa)
{
	DSI_VHSACR &= ~((DSI_VHSACR_HSA_MASK << DSI_VHSACR_HSA_SHIFT));
	DSI_VHSACR |= ((hsa & DSI_VHSACR_HSA_MASK) << DSI_VHSACR_HSA_SHIFT);
}

/* DSI_VHBPCR:  DSI Host video HBP configuration */
static inline void dsi_vhbpcr_set(uint32_t hbp)
{
	DSI_VHBPCR &= ~((DSI_VHBPCR_HBP_MASK << DSI_VHBPCR_HBP_SHIFT));
	DSI_VHBPCR |= ((hbp & DSI_VHBPCR_HBP_MASK) << DSI_VHBPCR_HBP_SHIFT);
}

/* DSI_VLCR:  DSI Host video line configuration */
static inline void dsi_vlcr_set(uint32_t hline)
{
	DSI_VLCR &= ~((DSI_VLCR_HLINE_MASK << DSI_VLCR_HLINE_SHIFT));
	DSI_VLCR |= ((hline & DSI_VLCR_HLINE_MASK) << DSI_VLCR_HLINE_SHIFT);
}

/* DSI_VVSACR:  DSI Host video VSA configuration */
static inline void dsi_vvsacr_set(uint32_t vsa)
{
	DSI_VVSACR &= ~((DSI_VVSACR_VSA_MASK << DSI_VVSACR_VSA_SHIFT));
	DSI_VVSACR |= ((vsa & DSI_VVSACR_VSA_MASK) << DSI_VVSACR_VSA_SHIFT);
}

/* DSI_VVBPCR:  DSI Host video VBP configuration */
static inline void dsi_vvbpcr_set(uint32_t vbp)
{
	DSI_VVBPCR &= ~((DSI_VVBPCR_VBP_MASK << DSI_VVBPCR_VBP_SHIFT));
	DSI_VVBPCR |= ((vbp & DSI_VVBPCR_VBP_MASK) << DSI_VVBPCR_VBP_SHIFT);
}

/* DSI_VVFPCR:  DSI Host video VFP configuration */
static inline void dsi_vvfpcr_set(uint32_t vfp)
{
	DSI_VVFPCR &= ~((DSI_VVFPCR_VFP_MASK << DSI_VVFPCR_VFP_SHIFT));
	DSI_VVFPCR |= ((vfp & DSI_VVFPCR_VFP_MASK) << DSI_VVFPCR_VFP_SHIFT);
}

/* DSI_VVACR:  DSI Host video VA configuration */
static inline void dsi_vvacr_set(uint32_t va)
{
	DSI_VVACR &= ~((DSI_VVACR_VA_MASK << DSI_VVACR_VA_SHIFT));
	DSI_VVACR |= ((va & DSI_VVACR_VA_MASK) << DSI_VVACR_VA_SHIFT);
}

/* DSI_LCCR:  DSI Host LTDC command configuration */
static inline void dsi_lccr_set(uint32_t cmdsize)
{
	DSI_LCCR &= ~((DSI_LCCR_CMDSIZE_MASK << DSI_LCCR_CMDSIZE_SHIFT));
	DSI_LCCR |= ((cmdsize & DSI_LCCR_CMDSIZE_MASK) << DSI_LCCR_CMDSIZE_SHIFT);
}

/* DSI_CMCR:  DSI Host command mode configuration */
static inline void dsi_cmcr_set(dsi_cmcr_flags_t flags)
{
	DSI_CMCR &= ~(DSI_CMCR_FLAGS_MASK);
	DSI_CMCR |= (flags & DSI_CMCR_FLAGS_MASK);
}

/* DSI_GHCR:  DSI Host generic header configuration */
static inline void dsi_ghcr_set(
	uint32_t wcmsb,
	uint32_t wclsb,
	uint32_t vcid,
	uint32_t dt)
{
	DSI_GHCR &= ~(
		(DSI_GHCR_WCMSB_MASK << DSI_GHCR_WCMSB_SHIFT)
	  | (DSI_GHCR_WCLSB_MASK << DSI_GHCR_WCLSB_SHIFT)
	  | (DSI_GHCR_VCID_MASK << DSI_GHCR_VCID_SHIFT)
	  | (DSI_GHCR_DT_MASK << DSI_GHCR_DT_SHIFT));
	DSI_GHCR |=
		((wcmsb & DSI_GHCR_WCMSB_MASK) << DSI_GHCR_WCMSB_SHIFT)
	  | ((wclsb & DSI_GHCR_WCLSB_MASK) << DSI_GHCR_WCLSB_SHIFT)
	  | ((vcid & DSI_GHCR_VCID_MASK) << DSI_GHCR_VCID_SHIFT)
	  | ((dt & DSI_GHCR_DT_MASK) << DSI_GHCR_DT_SHIFT);
}

/* DSI_GPDR:  DSI Host generic payload data */
static inline void dsi_gpdr_set(
	uint32_t data4,
	uint32_t data3,
	uint32_t data2,
	uint32_t data1)
{
	DSI_GPDR &= ~(
		(DSI_GPDR_DATA4_MASK << DSI_GPDR_DATA4_SHIFT)
	  | (DSI_GPDR_DATA3_MASK << DSI_GPDR_DATA3_SHIFT)
	  | (DSI_GPDR_DATA2_MASK << DSI_GPDR_DATA2_SHIFT)
	  | (DSI_GPDR_DATA1_MASK << DSI_GPDR_DATA1_SHIFT));
	DSI_GPDR |=
		((data4 & DSI_GPDR_DATA4_MASK) << DSI_GPDR_DATA4_SHIFT)
	  | ((data3 & DSI_GPDR_DATA3_MASK) << DSI_GPDR_DATA3_SHIFT)
	  | ((data2 & DSI_GPDR_DATA2_MASK) << DSI_GPDR_DATA2_SHIFT)
	  | ((data1 & DSI_GPDR_DATA1_MASK) << DSI_GPDR_DATA1_SHIFT);
}

/* DSI_GPSR:  DSI Host generic packet status */
static inline void dsi_gpsr_set(dsi_gpsr_flags_t flags)
{
	DSI_GPSR &= ~(DSI_GPSR_FLAGS_MASK);
	DSI_GPSR |= (flags & DSI_GPSR_FLAGS_MASK);
}

/* DSI_TCCR0:  DSI Host timeout counter configuration 0 */
static inline void dsi_tccr0_set(uint32_t hstx_tocnt, uint32_t lprx_tocnt)
{
	DSI_TCCR0 &= ~(
		(DSI_TCCR0_HSTX_TOCNT_MASK << DSI_TCCR0_HSTX_TOCNT_SHIFT)
	  | (DSI_TCCR0_LPRX_TOCNT_MASK << DSI_TCCR0_LPRX_TOCNT_SHIFT));
	DSI_TCCR0 |=
		((hstx_tocnt & DSI_TCCR0_HSTX_TOCNT_MASK) << DSI_TCCR0_HSTX_TOCNT_SHIFT)
	  | ((lprx_tocnt & DSI_TCCR0_LPRX_TOCNT_MASK) << DSI_TCCR0_LPRX_TOCNT_SHIFT);
}

/* DSI_TCCR1:  DSI Host timeout counter configuration 1 */
static inline void dsi_tccr1_set(uint32_t hsrd_tocnt)
{
	DSI_TCCR1 &= ~((DSI_TCCR1_HSRD_TOCNT_MASK << DSI_TCCR1_HSRD_TOCNT_SHIFT));
	DSI_TCCR1 |= ((hsrd_tocnt & DSI_TCCR1_HSRD_TOCNT_MASK) << DSI_TCCR1_HSRD_TOCNT_SHIFT);
}

/* DSI_TCCR2:  DSI Host timeout counter configuration 2 */
static inline void dsi_tccr2_set(uint32_t lprd_tocnt)
{
	DSI_TCCR2 &= ~((DSI_TCCR2_LPRD_TOCNT_MASK << DSI_TCCR2_LPRD_TOCNT_SHIFT));
	DSI_TCCR2 |= ((lprd_tocnt & DSI_TCCR2_LPRD_TOCNT_MASK) << DSI_TCCR2_LPRD_TOCNT_SHIFT);
}

/* DSI_TCCR3:  DSI Host timeout counter configuration 3 */
static inline void dsi_tccr3_set(uint32_t hswr_tocnt, dsi_tccr3_flags_t flags)
{
	DSI_TCCR3 &= ~(
		(DSI_TCCR3_HSWR_TOCNT_MASK << DSI_TCCR3_HSWR_TOCNT_SHIFT)
	  | DSI_TCCR3_FLAGS_MASK);
	DSI_TCCR3 |=
		((hswr_tocnt & DSI_TCCR3_HSWR_TOCNT_MASK) << DSI_TCCR3_HSWR_TOCNT_SHIFT)
	  | (flags & DSI_TCCR3_FLAGS_MASK);
}

/* DSI_TCCR4:  DSI Host timeout counter configuration 4 */
static inline void dsi_tccr4_set(uint32_t lpwr_tocnt)
{
	DSI_TCCR4 &= ~((DSI_TCCR4_LPWR_TOCNT_MASK << DSI_TCCR4_LPWR_TOCNT_SHIFT));
	DSI_TCCR4 |= ((lpwr_tocnt & DSI_TCCR4_LPWR_TOCNT_MASK) << DSI_TCCR4_LPWR_TOCNT_SHIFT);
}

/* DSI_TCCR5:  DSI Host timeout counter configuration 5 */
static inline void dsi_tccr5_set(uint32_t bta_tocnt)
{
	DSI_TCCR5 &= ~((DSI_TCCR5_BTA_TOCNT_MASK << DSI_TCCR5_BTA_TOCNT_SHIFT));
	DSI_TCCR5 |= ((bta_tocnt & DSI_TCCR5_BTA_TOCNT_MASK) << DSI_TCCR5_BTA_TOCNT_SHIFT);
}

/* DSI_CLCR:  DSI Host clock lane configuration */
static inline void dsi_clcr_set(dsi_clcr_flags_t flags)
{
	DSI_CLCR &= ~(DSI_CLCR_FLAGS_MASK);
	DSI_CLCR |= (flags & DSI_CLCR_FLAGS_MASK);
}

/* DSI_CLTCR:  DSI Host clock lane timer configuration */
static inline void dsi_cltcr_set(uint32_t hs2lp_time, uint32_t lp2hs_time)
{
	DSI_CLTCR &= ~(
		(DSI_CLTCR_HS2LP_TIME_MASK << DSI_CLTCR_HS2LP_TIME_SHIFT)
	  | (DSI_CLTCR_LP2HS_TIME_MASK << DSI_CLTCR_LP2HS_TIME_SHIFT));
	DSI_CLTCR |=
		((hs2lp_time & DSI_CLTCR_HS2LP_TIME_MASK) << DSI_CLTCR_HS2LP_TIME_SHIFT)
	  | ((lp2hs_time & DSI_CLTCR_LP2HS_TIME_MASK) << DSI_CLTCR_LP2HS_TIME_SHIFT);
}

/* DSI_DLTCR:  DSI Host data lane timer configuration */
static inline void dsi_dltcr_set(
	uint32_t hs2lp_time,
	uint32_t lp2hs_time,
	uint32_t mrd_time)
{
	DSI_DLTCR &= ~(
		(DSI_DLTCR_HS2LP_TIME_MASK << DSI_DLTCR_HS2LP_TIME_SHIFT)
	  | (DSI_DLTCR_LP2HS_TIME_MASK << DSI_DLTCR_LP2HS_TIME_SHIFT)
	  | (DSI_DLTCR_MRD_TIME_MASK << DSI_DLTCR_MRD_TIME_SHIFT));
	DSI_DLTCR |=
		((hs2lp_time & DSI_DLTCR_HS2LP_TIME_MASK) << DSI_DLTCR_HS2LP_TIME_SHIFT)
	  | ((lp2hs_time & DSI_DLTCR_LP2HS_TIME_MASK) << DSI_DLTCR_LP2HS_TIME_SHIFT)
	  | ((mrd_time & DSI_DLTCR_MRD_TIME_MASK) << DSI_DLTCR_MRD_TIME_SHIFT);
}

/* DSI_PCTLR:  DSI Host PHY control */
static inline void dsi_pctlr_set(dsi_pctlr_flags_t flags)
{
	DSI_PCTLR &= ~(DSI_PCTLR_FLAGS_MASK);
	DSI_PCTLR |= (flags & DSI_PCTLR_FLAGS_MASK);
}

/* DSI_PCONFR:  DSI Host PHY configuration */
static inline void dsi_pconfr_set(uint32_t sw_time, uint32_t nl)
{
	DSI_PCONFR &= ~(
		(DSI_PCONFR_SW_TIME_MASK << DSI_PCONFR_SW_TIME_SHIFT)
	  | (DSI_PCONFR_NL_MASK << DSI_PCONFR_NL_SHIFT));
	DSI_PCONFR |=
		((sw_time & DSI_PCONFR_SW_TIME_MASK) << DSI_PCONFR_SW_TIME_SHIFT)
	  | ((nl & DSI_PCONFR_NL_MASK) << DSI_PCONFR_NL_SHIFT);
}

/* DSI_PUCR:  DSI Host PHY ULPS control */
static inline void dsi_pucr_set(dsi_pucr_flags_t flags)
{
	DSI_PUCR &= ~(DSI_PUCR_FLAGS_MASK);
	DSI_PUCR |= (flags & DSI_PUCR_FLAGS_MASK);
}

/* DSI_PTTCR:  DSI Host PHY TX triggers configuration */
static inline void dsi_pttcr_set(uint32_t tx_trig)
{
	DSI_PTTCR &= ~((DSI_PTTCR_TX_TRIG_MASK << DSI_PTTCR_TX_TRIG_SHIFT));
	DSI_PTTCR |= ((tx_trig & DSI_PTTCR_TX_TRIG_MASK) << DSI_PTTCR_TX_TRIG_SHIFT);
}

/* DSI_PSR:  DSI Host PHY status */
static inline void dsi_psr_set(dsi_psr_flags_t flags)
{
	DSI_PSR &= ~(DSI_PSR_FLAGS_MASK);
	DSI_PSR |= (flags & DSI_PSR_FLAGS_MASK);
}

/* DSI_ISR0:  DSI Host interrupt and status 0 */
static inline void dsi_isr0_set(dsi_isr0_flags_t flags)
{
	DSI_ISR0 &= ~(DSI_ISR0_FLAGS_MASK);
	DSI_ISR0 |= (flags & DSI_ISR0_FLAGS_MASK);
}

/* DSI_ISR1:  DSI Host interrupt and status 1 */
static inline void dsi_isr1_set(dsi_isr1_flags_t flags)
{
	DSI_ISR1 &= ~(DSI_ISR1_FLAGS_MASK);
	DSI_ISR1 |= (flags & DSI_ISR1_FLAGS_MASK);
}

/* DSI_IER0:  DSI Host interrupt enable 0 */
static inline void dsi_ier0_set(dsi_ier0_flags_t flags)
{
	DSI_IER0 &= ~(DSI_IER0_FLAGS_MASK);
	DSI_IER0 |= (flags & DSI_IER0_FLAGS_MASK);
}

/* DSI_IER1:  DSI Host interrupt enable 1 */
static inline void dsi_ier1_set(dsi_ier1_flags_t flags)
{
	DSI_IER1 &= ~(DSI_IER1_FLAGS_MASK);
	DSI_IER1 |= (flags & DSI_IER1_FLAGS_MASK);
}

/* DSI_FIR0:  DSI Host force interrupt 0 */
static inline void dsi_fir0_set(dsi_fir0_flags_t flags)
{
	DSI_FIR0 &= ~(DSI_FIR0_FLAGS_MASK);
	DSI_FIR0 |= (flags & DSI_FIR0_FLAGS_MASK);
}

/* DSI_FIR1:  DSI Host force interrupt 1 */
static inline void dsi_fir1_set(dsi_fir1_flags_t flags)
{
	DSI_FIR1 &= ~(DSI_FIR1_FLAGS_MASK);
	DSI_FIR1 |= (flags & DSI_FIR1_FLAGS_MASK);
}

/* DSI_VSCR:  DSI Host video shadow control */
static inline void dsi_vscr_set(dsi_vscr_flags_t flags)
{
	DSI_VSCR &= ~(DSI_VSCR_FLAGS_MASK);
	DSI_VSCR |= (flags & DSI_VSCR_FLAGS_MASK);
}

/* DSI_LCVCIDR:  DSI Host LTDC current VCID */
static inline void dsi_lcvcidr_set(uint32_t vcid)
{
	DSI_LCVCIDR &= ~((DSI_LCVCIDR_VCID_MASK << DSI_LCVCIDR_VCID_SHIFT));
	DSI_LCVCIDR |= ((vcid & DSI_LCVCIDR_VCID_MASK) << DSI_LCVCIDR_VCID_SHIFT);
}

/* DSI_LCCCR:  DSI Host LTDC current color coding */
static inline void dsi_lcccr_set(uint32_t colc, dsi_lcccr_flags_t flags)
{
	DSI_LCCCR &= ~(
		(DSI_LCCCR_COLC_MASK << DSI_LCCCR_COLC_SHIFT)
	  | DSI_LCCCR_FLAGS_MASK);
	DSI_LCCCR |=
		((colc & DSI_LCCCR_COLC_MASK) << DSI_LCCCR_COLC_SHIFT)
	  | (flags & DSI_LCCCR_FLAGS_MASK);
}

/* DSI_LPMCCR:  DSI Host low-power mode current configuration */
static inline void dsi_lpmccr_set(uint32_t lpsize, uint32_t vlpsize)
{
	DSI_LPMCCR &= ~(
		(DSI_LPMCCR_LPSIZE_MASK << DSI_LPMCCR_LPSIZE_SHIFT)
	  | (DSI_LPMCCR_VLPSIZE_MASK << DSI_LPMCCR_VLPSIZE_SHIFT));
	DSI_LPMCCR |=
		((lpsize & DSI_LPMCCR_LPSIZE_MASK) << DSI_LPMCCR_LPSIZE_SHIFT)
	  | ((vlpsize & DSI_LPMCCR_VLPSIZE_MASK) << DSI_LPMCCR_VLPSIZE_SHIFT);
}

/* DSI_VMCCR:  DSI Host video mode current configuration */
static inline void dsi_vmccr_set(uint32_t vmt, dsi_vmccr_flags_t flags)
{
	DSI_VMCCR &= ~(
		(DSI_VMCCR_VMT_MASK << DSI_VMCCR_VMT_SHIFT)
	  | DSI_VMCCR_FLAGS_MASK);
	DSI_VMCCR |=
		((vmt & DSI_VMCCR_VMT_MASK) << DSI_VMCCR_VMT_SHIFT)
	  | (flags & DSI_VMCCR_FLAGS_MASK);
}

/* DSI_VPCCR:  DSI Host video packet current configuration */
static inline void dsi_vpccr_set(uint32_t vpsize)
{
	DSI_VPCCR &= ~((DSI_VPCCR_VPSIZE_MASK << DSI_VPCCR_VPSIZE_SHIFT));
	DSI_VPCCR |= ((vpsize & DSI_VPCCR_VPSIZE_MASK) << DSI_VPCCR_VPSIZE_SHIFT);
}

/* DSI_VCCCR:  DSI Host video chunks current configuration */
static inline void dsi_vcccr_set(uint32_t numc)
{
	DSI_VCCCR &= ~((DSI_VCCCR_NUMC_MASK << DSI_VCCCR_NUMC_SHIFT));
	DSI_VCCCR |= ((numc & DSI_VCCCR_NUMC_MASK) << DSI_VCCCR_NUMC_SHIFT);
}

/* DSI_VNPCCR:  DSI Host video null packet current configuration */
static inline void dsi_vnpccr_set(uint32_t npsize)
{
	DSI_VNPCCR &= ~((DSI_VNPCCR_NPSIZE_MASK << DSI_VNPCCR_NPSIZE_SHIFT));
	DSI_VNPCCR |= ((npsize & DSI_VNPCCR_NPSIZE_MASK) << DSI_VNPCCR_NPSIZE_SHIFT);
}

/* DSI_VHSACCR:  DSI Host video HSA current configuration */
static inline void dsi_vhsaccr_set(uint32_t hsa)
{
	DSI_VHSACCR &= ~((DSI_VHSACCR_HSA_MASK << DSI_VHSACCR_HSA_SHIFT));
	DSI_VHSACCR |= ((hsa & DSI_VHSACCR_HSA_MASK) << DSI_VHSACCR_HSA_SHIFT);
}

/* DSI_VHBPCCR:  DSI Host video HBP current configuration */
static inline void dsi_vhbpccr_set(uint32_t hbp)
{
	DSI_VHBPCCR &= ~((DSI_VHBPCCR_HBP_MASK << DSI_VHBPCCR_HBP_SHIFT));
	DSI_VHBPCCR |= ((hbp & DSI_VHBPCCR_HBP_MASK) << DSI_VHBPCCR_HBP_SHIFT);
}

/* DSI_VLCCR:  DSI Host video line current configuration */
static inline void dsi_vlccr_set(uint32_t hline)
{
	DSI_VLCCR &= ~((DSI_VLCCR_HLINE_MASK << DSI_VLCCR_HLINE_SHIFT));
	DSI_VLCCR |= ((hline & DSI_VLCCR_HLINE_MASK) << DSI_VLCCR_HLINE_SHIFT);
}

/* DSI_VVSACCR:  DSI Host video VSA current configuration */
static inline void dsi_vvsaccr_set(uint32_t vsa)
{
	DSI_VVSACCR &= ~((DSI_VVSACCR_VSA_MASK << DSI_VVSACCR_VSA_SHIFT));
	DSI_VVSACCR |= ((vsa & DSI_VVSACCR_VSA_MASK) << DSI_VVSACCR_VSA_SHIFT);
}

/* DSI_VVBPCCR:  DSI Host video VBP current configuration */
static inline void dsi_vvbpccr_set(uint32_t vbp)
{
	DSI_VVBPCCR &= ~((DSI_VVBPCCR_VBP_MASK << DSI_VVBPCCR_VBP_SHIFT));
	DSI_VVBPCCR |= ((vbp & DSI_VVBPCCR_VBP_MASK) << DSI_VVBPCCR_VBP_SHIFT);
}

/* DSI_VVFPCCR:  DSI Host video VFP current configuration */
static inline void dsi_vvfpccr_set(uint32_t vfp)
{
	DSI_VVFPCCR &= ~((DSI_VVFPCCR_VFP_MASK << DSI_VVFPCCR_VFP_SHIFT));
	DSI_VVFPCCR |= ((vfp & DSI_VVFPCCR_VFP_MASK) << DSI_VVFPCCR_VFP_SHIFT);
}

/* DSI_VVACCR:  DSI Host video VA current configuration */
static inline void dsi_vvaccr_set(uint32_t va)
{
	DSI_VVACCR &= ~((DSI_VVACCR_VA_MASK << DSI_VVACCR_VA_SHIFT));
	DSI_VVACCR |= ((va & DSI_VVACCR_VA_MASK) << DSI_VVACCR_VA_SHIFT);
}



/**
 * DSI Wrapper setter function templates
 */

/* DSI_WCFGR:  DSI wrapper configuration */
static inline void dsi_wcfgr_set(uint32_t colmux, dsi_wcfgr_flags_t flags)
{
	DSI_WCFGR &= ~(
		(DSI_WCFGR_COLMUX_MASK << DSI_WCFGR_COLMUX_SHIFT)
	  | DSI_WCFGR_FLAGS_MASK);
	DSI_WCFGR |=
		((colmux & DSI_WCFGR_COLMUX_MASK) << DSI_WCFGR_COLMUX_SHIFT)
	  | (flags & DSI_WCFGR_FLAGS_MASK);
}

/* DSI_WCR:  DSI wrapper control */
static inline void dsi_wcr_set(dsi_wcr_flags_t flags)
{
	DSI_WCR &= ~(DSI_WCR_FLAGS_MASK);
	DSI_WCR |= (flags & DSI_WCR_FLAGS_MASK);
}

/* DSI_WIER:  DSI wrapper interrupt enable */
static inline void dsi_wier_set(dsi_wier_flags_t flags)
{
	DSI_WIER &= ~(DSI_WIER_FLAGS_MASK);
	DSI_WIER |= (flags & DSI_WIER_FLAGS_MASK);
}

/* DSI_WISR:  DSI wrapper interrupt and status */
static inline void dsi_wisr_set(dsi_wisr_flags_t flags)
{
	DSI_WISR &= ~(DSI_WISR_FLAGS_MASK);
	DSI_WISR |= (flags & DSI_WISR_FLAGS_MASK);
}

/* DSI_WIFCR:  DSI wrapper interrupt flag clear */
static inline void dsi_wifcr_set(dsi_wifcr_flags_t flags)
{
	DSI_WIFCR &= ~(DSI_WIFCR_FLAGS_MASK);
	DSI_WIFCR |= (flags & DSI_WIFCR_FLAGS_MASK);
}

/* DSI_WPCR0:  DSI wrapper PHY configuration 0 */
static inline void dsi_wpcr0_set(uint32_t uix4, dsi_wpcr0_flags_t flags)
{
	DSI_WPCR0 &= ~(
		(DSI_WPCR0_UIX4_MASK << DSI_WPCR0_UIX4_SHIFT)
	  | DSI_WPCR0_FLAGS_MASK);
	DSI_WPCR0 |=
		((uix4 & DSI_WPCR0_UIX4_MASK) << DSI_WPCR0_UIX4_SHIFT)
	  | (flags & DSI_WPCR0_FLAGS_MASK);
}

/* DSI_WPCR1:  DSI wrapper PHY configuration 1 */
static inline void dsi_wpcr1_set(
	uint32_t lprxft,
	uint32_t hstxsrcdl,
	uint32_t hstxsrccl,
	uint32_t lpsrcdl,
	uint32_t lpsrccl,
	uint32_t hstxddl,
	uint32_t hstxdcl,
	dsi_wpcr1_flags_t flags)
{
	DSI_WPCR1 &= ~(
		(DSI_WPCR1_LPRXFT_MASK << DSI_WPCR1_LPRXFT_SHIFT)
	  | (DSI_WPCR1_HSTXSRCDL_MASK << DSI_WPCR1_HSTXSRCDL_SHIFT)
	  | (DSI_WPCR1_HSTXSRCCL_MASK << DSI_WPCR1_HSTXSRCCL_SHIFT)
	  | (DSI_WPCR1_LPSRCDL_MASK << DSI_WPCR1_LPSRCDL_SHIFT)
	  | (DSI_WPCR1_LPSRCCL_MASK << DSI_WPCR1_LPSRCCL_SHIFT)
	  | (DSI_WPCR1_HSTXDDL_MASK << DSI_WPCR1_HSTXDDL_SHIFT)
	  | (DSI_WPCR1_HSTXDCL_MASK << DSI_WPCR1_HSTXDCL_SHIFT)
	  | DSI_WPCR1_FLAGS_MASK);
	DSI_WPCR1 |=
		((lprxft & DSI_WPCR1_LPRXFT_MASK) << DSI_WPCR1_LPRXFT_SHIFT)
	  | ((hstxsrcdl & DSI_WPCR1_HSTXSRCDL_MASK) << DSI_WPCR1_HSTXSRCDL_SHIFT)
	  | ((hstxsrccl & DSI_WPCR1_HSTXSRCCL_MASK) << DSI_WPCR1_HSTXSRCCL_SHIFT)
	  | ((lpsrcdl & DSI_WPCR1_LPSRCDL_MASK) << DSI_WPCR1_LPSRCDL_SHIFT)
	  | ((lpsrccl & DSI_WPCR1_LPSRCCL_MASK) << DSI_WPCR1_LPSRCCL_SHIFT)
	  | ((hstxddl & DSI_WPCR1_HSTXDDL_MASK) << DSI_WPCR1_HSTXDDL_SHIFT)
	  | ((hstxdcl & DSI_WPCR1_HSTXDCL_MASK) << DSI_WPCR1_HSTXDCL_SHIFT)
	  | (flags & DSI_WPCR1_FLAGS_MASK);
}

/* DSI_WPCR2:  DSI wrapper PHY configuration 2 */
static inline void dsi_wpcr2_set(
	uint32_t thstrail,
	uint32_t thsprep,
	uint32_t tclkzero,
	uint32_t tclkprep)
{
	DSI_WPCR2 &= ~(
		(DSI_WPCR2_THSTRAIL_MASK << DSI_WPCR2_THSTRAIL_SHIFT)
	  | (DSI_WPCR2_THSPREP_MASK << DSI_WPCR2_THSPREP_SHIFT)
	  | (DSI_WPCR2_TCLKZERO_MASK << DSI_WPCR2_TCLKZERO_SHIFT)
	  | (DSI_WPCR2_TCLKPREP_MASK << DSI_WPCR2_TCLKPREP_SHIFT));
	DSI_WPCR2 |=
		((thstrail & DSI_WPCR2_THSTRAIL_MASK) << DSI_WPCR2_THSTRAIL_SHIFT)
	  | ((thsprep & DSI_WPCR2_THSPREP_MASK) << DSI_WPCR2_THSPREP_SHIFT)
	  | ((tclkzero & DSI_WPCR2_TCLKZERO_MASK) << DSI_WPCR2_TCLKZERO_SHIFT)
	  | ((tclkprep & DSI_WPCR2_TCLKPREP_MASK) << DSI_WPCR2_TCLKPREP_SHIFT);
}

/* DSI_WPCR3:  DSI wrapper PHY configuration 3 */
static inline void dsi_wpcr3_set(
	uint32_t tlpxc,
	uint32_t thsexit,
	uint32_t tlpxd,
	uint32_t thszero)
{
	DSI_WPCR3 &= ~(
		(DSI_WPCR3_TLPXC_MASK << DSI_WPCR3_TLPXC_SHIFT)
	  | (DSI_WPCR3_THSEXIT_MASK << DSI_WPCR3_THSEXIT_SHIFT)
	  | (DSI_WPCR3_TLPXD_MASK << DSI_WPCR3_TLPXD_SHIFT)
	  | (DSI_WPCR3_THSZERO_MASK << DSI_WPCR3_THSZERO_SHIFT));
	DSI_WPCR3 |=
		((tlpxc & DSI_WPCR3_TLPXC_MASK) << DSI_WPCR3_TLPXC_SHIFT)
	  | ((thsexit & DSI_WPCR3_THSEXIT_MASK) << DSI_WPCR3_THSEXIT_SHIFT)
	  | ((tlpxd & DSI_WPCR3_TLPXD_MASK) << DSI_WPCR3_TLPXD_SHIFT)
	  | ((thszero & DSI_WPCR3_THSZERO_MASK) << DSI_WPCR3_THSZERO_SHIFT);
}

/* DSI_WPCR4:  DSI wrapper PHY configuration 4 */
static inline void dsi_wpcr4_set(uint32_t tclkpost)
{
	DSI_WPCR4 &= ~((DSI_WPCR4_TCLKPOST_MASK << DSI_WPCR4_TCLKPOST_SHIFT));
	DSI_WPCR4 |= ((tclkpost & DSI_WPCR4_TCLKPOST_MASK) << DSI_WPCR4_TCLKPOST_SHIFT);
}

/* DSI_WRPCR:  DSI wrapper regulator and PLL control */
static inline void dsi_wrpcr_set(
	uint32_t odf,
	uint32_t idf,
	uint32_t ndiv,
	dsi_wrpcr_flags_t flags)
{
	DSI_WRPCR &= ~(
		(DSI_WRPCR_ODF_MASK << DSI_WRPCR_ODF_SHIFT)
	  | (DSI_WRPCR_IDF_MASK << DSI_WRPCR_IDF_SHIFT)
	  | (DSI_WRPCR_NDIV_MASK << DSI_WRPCR_NDIV_SHIFT)
	  | DSI_WRPCR_FLAGS_MASK);
	DSI_WRPCR |=
		((odf & DSI_WRPCR_ODF_MASK) << DSI_WRPCR_ODF_SHIFT)
	  | ((idf & DSI_WRPCR_IDF_MASK) << DSI_WRPCR_IDF_SHIFT)
	  | ((ndiv & DSI_WRPCR_NDIV_MASK) << DSI_WRPCR_NDIV_SHIFT)
	  | (flags & DSI_WRPCR_FLAGS_MASK);
}


/*@}*/

#endif /* DSI_H_ */
