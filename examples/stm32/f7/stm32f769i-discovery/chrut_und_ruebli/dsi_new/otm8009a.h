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

/**
 * The definitions here are base on the otm8009a_v02 datasheet
 */

#ifndef DRIVERS_OTM8009A_H_
#define DRIVERS_OTM8009A_H_

/*
 * LPDT: Low power data transfer mode
 * HSDT: High speed data transfer mode
 * C: Command
 * R: Read
 * W: Write
 */

typedef enum {
/* System Commands */

	/* No Operation */
	OTM8009A_CMD_NOP          = 0x00, /* C   - LPDT/HSDT - 0 */
	/* Software reset */
	OTM8009A_CMD_SWRESET      = 0x01, /* C   - LPDT/HSDT - 0 */
	/* Read Number of the Errors on DSI */
	OTM8009A_CMD_RDNUMED      = 0x05, /* R   - LPDT/HSDT - 1 */
	/* Read Display Power Mode */
	OTM8009A_CMD_RDDPM        = 0x0A, /* R   - LPDT/HSDT - 1 */
	/* Read Display MADCTL */
	OTM8009A_CMD_RDDMADCTL    = 0x0B, /* R   - LPDT/HSDT - 1 */
	/* Read Display Pixel Format */
	OTM8009A_CMD_RDDCOLMOD    = 0x0C, /* R   - LPDT/HSDT - 1 */
	/* Read Display Image Mode */
	OTM8009A_CMD_RDDIM        = 0x0D, /* R   - LPDT/HSDT - 1 */
	/* Read Display Signal Mode */
	OTM8009A_CMD_RDDSM        = 0x0E, /* R   - LPDT/HSDT - 1 */
	/* Read Display Self Diagnostic Result */
	OTM8009A_CMD_RDDSDR       = 0x0F, /* R   - LPDT/HSDT - 1 */
	/* Sleep in */
	OTM8009A_CMD_SLPIN        = 0x10, /* C   - LPDT/HSDT - 0 */
	/* Sleep out */
	OTM8009A_CMD_SLPOUT       = 0x11, /* C   - LPDT/HSDT - 0 */
	/* Partial Mode On */
	OTM8009A_CMD_PTLON        = 0x12, /* C   - LPDT/HSDT - 0 */
	/* Normal Display Mode On */
	OTM8009A_CMD_NORON        = 0x13, /* C   - LPDT/HSDT - 0 */
	/* Display Inversion Off */
	OTM8009A_CMD_INVOFF       = 0x20, /* C   - LPDT/HSDT - 0 */
	/* Display Inversion On */
	OTM8009A_CMD_INVON        = 0x21, /* C   - LPDT/HSDT - 0 */
	/* All Pixels Off */
	OTM8009A_CMD_ALLPOFF      = 0x22, /* C   - LPDT/HSDT - 0 */
	/* All Pixels On */
	OTM8009A_CMD_ALLPON       = 0x23, /* C   - LPDT/HSDT - 0 */
	/* Gamma Set */
	OTM8009A_CMD_GAMSET       = 0x26, /* W   - LPDT/HSDT - 1 */
	/* Display off */
	OTM8009A_CMD_DISPOFF      = 0x28, /* C   - LPDT/HSDT - 0 */
	/* Display on */
	OTM8009A_CMD_DISPON       = 0x29, /* C   - LPDT/HSDT - 0 */
	/* Column Address Set */
	OTM8009A_CMD_CASET        = 0x2A, /* W   - LPDT/HSDT - 4 */
	/* Page Address Set */
	OTM8009A_CMD_PASET        = 0x2B, /* W   - LPDT/HSDT - 4 */
	/* Memory Write */
	OTM8009A_CMD_RAMWR        = 0x2C, /* W   - LPDT/HSDT - Any Length */
	/* Memory Read */
	OTM8009A_CMD_RAMRD        = 0x2E, /* R   - LPDT/HSDT - Any Length */
	/* Partial area */
	OTM8009A_CMD_PLTAR        = 0x30, /* W   - LPDT/HSDT - 4 */
	/* Tearing Effect Line Off */
	OTM8009A_CMD_TEOFF        = 0x34, /* C   - LPDT/HSDT - 0 */
	/* Tearing Effect Line On */
	OTM8009A_CMD_TEEON        = 0x35, /* W   - LPDT/HSDT - 1 */
	/* Memory Access Control */
	OTM8009A_CMD_MADCTL       = 0x36, /* W   - LPDT/HSDT - 1 */
	/* Idle Mode off */
	OTM8009A_CMD_IDMOFF       = 0x38, /* C   - LPDT/HSDT - 0 */
	/* Idle Mode on */
	OTM8009A_CMD_IDMON        = 0x39, /* C   - LPDT/HSDT - 0 */
	/* Interface Pixel Format */
	OTM8009A_CMD_COLMOD       = 0x3A, /* C   - LPDT/HSDT - 1 */
	/* Memory Write Continue */
	OTM8009A_CMD_RAMWRC       = 0x3C, /* W   - LPDT/HSDT - Any Length */
	/* Memory Read Continue */
	OTM8009A_CMD_RAMRDC       = 0x3E, /* R   - LPDT/HSDT - Any Length */
	/* Write TE Scan Line */
	OTM8009A_CMD_WRTESCN      = 0x44, /* W   - LPDT/HSDT - 2 */
	/* Read Scan Line */
	OTM8009A_CMD_RDSCNL       = 0x45, /* R   - LPDT/HSDT - 2 */
	/* Write Display Brightness */
	OTM8009A_CMD_WRDISBV      = 0x51, /* W   - LPDT/HSDT - 1 */
	/* Read Display Brightness Value */
	OTM8009A_CMD_RDDISBV      = 0x52, /* R   - LPDT/HSDT - 1 */
	/* Write CTRL Display */
	OTM8009A_CMD_WRCTRLD      = 0x53, /* W   - LPDT/HSDT - 1 */
	/* Read CTRL Display */
	OTM8009A_CMD_RDCTRLD      = 0x54, /* R   - LPDT/HSDT - 1 */
	/* Write Content Adaptive Brightness Control */
	OTM8009A_CMD_WRCABC       = 0x55, /* W   - LPDT/HSDT - 1 */
	/* Read Content Adaptive Brightness Control */
	OTM8009A_CMD_RDCABC       = 0x56, /* R   - LPDT/HSDT - 1 */
	/* Write CABC Minimum Brightness */
	OTM8009A_CMD_WRCABCMB     = 0x5E, /* W   - LPDT/HSDT - 1 */
	/* Read CABC Minimum Brightness */
	OTM8009A_CMD_RDCABCMB     = 0x5F, /* R   - LPDT/HSDT - 1 */
	/* Read Automatic Brightness Control Self-diagnostics Result */
	OTM8009A_CMD_RDABCSDR     = 0x68, /* R   - LPDT/HSDT - 1 */
	/* Read Black/White Low Bits */
	OTM8009A_CMD_RDBWLB       = 0x70, /* R   - LPDT/HSDT - 1 */
	/* Read Bkx */
	OTM8009A_CMD_RDBKx        = 0x71, /* R   - LPDT/HSDT - 1 */
	/* Read Bky */
	OTM8009A_CMD_RDBKy        = 0x72, /* R   - LPDT/HSDT - 1 */
	/* Read Wx */
	OTM8009A_CMD_RDWx         = 0x73, /* R   - LPDT/HSDT - 1 */
	/* Read Wy */
	OTM8009A_CMD_RDWy         = 0x74, /* R   - LPDT/HSDT - 1 */
	/* Read Red/Green Low Bits */
	OTM8009A_CMD_RDRGLB       = 0x75, /* R   - LPDT/HSDT - 1 */
	/* Read Rx */
	OTM8009A_CMD_RDRx         = 0x76, /* R   - LPDT/HSDT - 1 */
	/* Read Ry */
	OTM8009A_CMD_RDRy         = 0x77, /* R   - LPDT/HSDT - 1 */
	/* Read Gx */
	OTM8009A_CMD_RDGx         = 0x78, /* R   - LPDT/HSDT - 1 */
	/* Read Gy */
	OTM8009A_CMD_RDGy         = 0x79, /* R   - LPDT/HSDT - 1 */
	/* Read Blue/AColour Low Bits */
	OTM8009A_CMD_RDBALB       = 0x7A, /* R   - LPDT/HSDT - 1 */
	/* Read Bx */
	OTM8009A_CMD_RDBx         = 0x7B, /* R   - LPDT/HSDT - 1 */
	/* Read By */
	OTM8009A_CMD_RDBy         = 0x7C, /* R   - LPDT/HSDT - 1 */
	/* Read Ax */
	OTM8009A_CMD_RDAx         = 0x7D, /* R   - LPDT/HSDT - 1 */
	/* Read Ay */
	OTM8009A_CMD_RDAy         = 0x7E, /* R   - LPDT/HSDT - 1 */
	/* Read DDB Start */
	OTM8009A_CMD_RDDDBS       = 0xA1, /* R   - LPDT/HSDT - 5 */
	/* Read DDB Continue */
	OTM8009A_CMD_RDDDBC       = 0xA8, /* R   - LPDT/HSDT - Any Length */
	/* Read First Checksum */
	OTM8009A_CMD_RDFCS        = 0xAA, /* R   - LPDT/HSDT - 1 */
	/* Read Continue Checksum */
	OTM8009A_CMD_RDCCS        = 0xAF, /* R   - LPDT/HSDT - 1 */
	/* Read ID1 */
	OTM8009A_CMD_RDID1        = 0xDA, /* R   - LPDT/HSDT - 1 */
	/* Read ID2 */
	OTM8009A_CMD_RDID2        = 0xDB, /* R   - LPDT/HSDT - 1 */
	/* Read ID3 */
	OTM8009A_CMD_RDID3        = 0xDC, /* R   - LPDT/HSDT - 1 */

/* Manufacturer Commands */
	/* Address Shift Function */
	OTM8009A_CMD_ADRSFT       = 0x0000, /* W   - LPDT - 1 */
	/* Enable Access Command2 “CMD2” */
	OTM8009A_CMD_CMD2_ENA1    = 0xFF00, /* W   - LPDT - 3 */
	/* Enable Access Orise Command2 */
	OTM8009A_CMD_CMD2_ENA2    = 0xFF80, /* W   - LPDT - 2 */
	/* OTP Select Region */
	OTM8009A_CMD_OTPSEL       = 0xA000, /* W/R - LPDT - 1 */
	/* MIPI Setting1 */
	OTM8009A_CMD_MIPISET1     = 0xB080, /* W/R - LPDT - 4 */
	/* MIPI Setting2 */
	OTM8009A_CMD_MIPISET2     = 0xB0A1, /* W/R - LPDT - 5 */
	/* IF Parameter 1 */
	OTM8009A_CMD_IF_PARA1     = 0xB280, /* W/R - LPDT - 1 */
	/* IF Parameter 2 */
	OTM8009A_CMD_IF_PARA2     = 0xB282, /* W/R - LPDT - 1 */
	/* IOPAD Parameter 1 */
	OTM8009A_CMD_PAD_PARA1    = 0xB390, /* W/R - LPDT - 1 */
	/* IOPAD Parameter 2 */
	OTM8009A_CMD_PAD_PARA2    = 0xB391, /* W/R - LPDT - 1 */
	/* IOPAD Parameter 3 */
	OTM8009A_CMD_PAD_PARA3    = 0xB392, /* W/R - LPDT - 1 */
	/* SRAM Power Setting */
	OTM8009A_CMD_RAMPWRSET    = 0xB3C0, /* W/R - LPDT - 2 */
	/* TCON Setting Parameter1 */
	OTM8009A_CMD_TSP1         = 0xC080, /* W/R - LPDT - 9 */
	/* Panel Timing Setting Parameter1 */
	OTM8009A_CMD_PTSP1        = 0xC092, /* W/R - LPDT - 2 */
	/* Panel Timing Setting Parameter2 */
	OTM8009A_CMD_PTSP2        = 0xC094, /* W/R - LPDT - 1 */
	/* Panel Timing Setting Parameter3 */
	OTM8009A_CMD_PTSP3        = 0xC0A2, /* W/R - LPDT - 1 */
	/* Panel Timing Setting Parameter4 */
	OTM8009A_CMD_PTSP4        = 0xC0A3, /* W/R - LPDT - 1 */
	/* Interval Scan Frame Setting */
	OTM8009A_CMD_ISC          = 0xC0B3, /* W/R - LPDT - 1 */
	/* Panel Driving Mode */
	OTM8009A_CMD_P_DRV_M      = 0xC0B4, /* W/R - LPDT - 1 */
	/* Oscillator Adjustment for Idle/Normal Mode */
	OTM8009A_CMD_OSC_ADJ      = 0xC181, /* W/R - LPDT - 1 */
	/* Source Driver Precharge Control */
	OTM8009A_CMD_SD_PCH_CTRL  = 0xC480, /* W/R - LPDT - 9 */
	/* Power Control Setting 1 */
	OTM8009A_CMD_PWR_CTRL1    = 0xC580, /* W/R - LPDT - 4 */
	/* Power Control Setting 2 for Normal Mode */
	OTM8009A_CMD_PWR_CTRL2    = 0xC590, /* W/R - LPDT - 7 */
	/* Power Control Setting 3 for Idle Mode */
	OTM8009A_CMD_PWR_CTRL3    = 0xC5A0, /* W/R - LPDT - 7 */
	/* PowerControlSetting 4 for DC Voltage Settings */
	OTM8009A_CMD_PWR_CTRL4    = 0xC5B0, /* W/R - LPDT - 2 */
	/* PWM_PARA1 (C680H) PWM Parameter 1 */
	OTM8009A_CMD_PWM_PARA1    = 0xC680, /* W/R - LPDT - 1 */
	/* PWM_PARA2 (C6B0H) PWM Parameter 2 */
	OTM8009A_CMD_PWM_PARA2    = 0xC6B0, /* W/R - LPDT - 1 */
	/* PWM_PARA3 (C6B1H) PWM Parameter 3 */
	OTM8009A_CMD_PWM_PARA3    = 0xC6B1, /* W/R - LPDT - 1 */
	/* PWM_PARA4 (C6B3H) PWM Parameter 4 */
	OTM8009A_CMD_PWM_PARA4    = 0xC6B2, /* W/R - LPDT - 1 */
	/* PWM_PARA5 (C6B4H) PWM Parameter 5 */
	OTM8009A_CMD_PWM_PARA5    = 0xC6B3, /* W/R - LPDT - 1 */
	/* PWM_PARA6 (C6B5H) PWM Parameter 6 */
	OTM8009A_CMD_PWM_PARA6    = 0xC6B4, /* W/R - LPDT - 1 */
	/* CABC Setting */
	OTM8009A_CMD_CABCSET1     = 0xC700, /* W/R - LPDT - 1 */
	/* CABC Gamma Curve Setting */
	OTM8009A_CMD_CABCSET2     = 0xC800, /* W/R - LPDT - 18 */
	/* AIE Setting */
	OTM8009A_CMD_AIESET       = 0xC900, /* W/R - LPDT - 18 */
	/* GOA VST Setting */
	OTM8009A_CMD_OAVST        = 0xCE80, /* W/R - LPDT - 12 */
	/* GOA VEND Setting */
	OTM8009A_CMD_OAVEND       = 0xCE90, /* W/R - LPDT - 12 */
	/* GOA Group Setting */
	OTM8009A_CMD_OAGPSET      = 0xCE9C, /* W/R - LPDT - 2 */
	/* GOA CLKA1 Setting */
	OTM8009A_CMD_OACLKA1      = 0xCEA0, /* W/R - LPDT - 7 */
	/* GOA CLKA2 Setting */
	OTM8009A_CMD_OACLKA2      = 0xCEA7, /* W/R - LPDT - 7 */
	/* GOA CLKA3 Setting */
	OTM8009A_CMD_OACLKA3      = 0xCEB0, /* W/R - LPDT - 7 */
	/* GOA CLKA4 Setting */
	OTM8009A_CMD_OACLKA4      = 0xCEB7, /* W/R - LPDT - 7 */
	/* GOA CLKB1 Setting */
	OTM8009A_CMD_OACLKB1      = 0xCEC0, /* W/R - LPDT - 7 */
	/* GOA CLKB2 Setting */
	OTM8009A_CMD_OACLKB2      = 0xCEC7, /* W/R - LPDT - 7 */
	/* GOA CLKB3 Setting */
	OTM8009A_CMD_OACLKB3      = 0xCED0, /* W/R - LPDT - 7 */
	/* GOA CLKB4 Setting */
	OTM8009A_CMD_OACLKB4      = 0xCED7, /* W/R - LPDT - 7 */
	/* GOA CLKC1 Setting */
	OTM8009A_CMD_OACLKC1      = 0xCF80, /* W/R - LPDT - 7 */
	/* GOA CLKC2 Setting */
	OTM8009A_CMD_OACLKC2      = 0xCF87, /* W/R - LPDT - 7 */
	/* GOA CLKC3 Setting */
	OTM8009A_CMD_OACLKC3      = 0xCF90, /* W/R - LPDT - 7 */
	/* GOA CLKC4 Setting */
	OTM8009A_CMD_OACLKC4      = 0xCF97, /* W/R - LPDT - 7 */
	/* GOA CLKD1 Setting */
	OTM8009A_CMD_OACLKD1      = 0xCFA0, /* W/R - LPDT - 7 */
	/* GOA CLKD2 Setting */
	OTM8009A_CMD_OACLKD2      = 0xCFA7, /* W/R - LPDT - 7 */
	/* GOA CLKD3 Setting */
	OTM8009A_CMD_OACLKD3      = 0xCFB0, /* W/R - LPDT - 7 */
	/* GOA CLKD4 Setting */
	OTM8009A_CMD_OACLKD4      = 0xCFB7, /* W/R - LPDT - 7 */
	/* GOA ECLK Setting */
	OTM8009A_CMD_OAECLK       = 0xCFC0, /* W/R - LPDT - 6 */
	/* GOA Other Options 1 */
	OTM8009A_CMD_OAOPT1       = 0xCFC6, /* W/R - LPDT - 1 */
	/* GOA Signal Toggle Option Setting */
	OTM8009A_CMD_OATGOPT      = 0xCFC7, /* W/R - LPDT - 2 */
	/* ID1 Setting */
	OTM8009A_CMD_RID1         = 0xD000, /* W/R - LPDT - 1 */
	/* ID2/ID3 Setting */
	OTM8009A_CMD_RID2         = 0xD100, /* W/R - LPDT - 2 */
	/* DDB Setting */
	OTM8009A_CMD_RDDB         = 0xD200, /* W/R - LPDT - 4 */
	/* EXTC Check */
	OTM8009A_CMD_XTCCHK       = 0xD300, /* R   - LPDT - 1 */
	/* CE Correction Characteristics Setting1 */
	OTM8009A_CMD_ESET1        = 0xD400, /* W/R - LPDT - 360 */
	/* CE Correction Characteristics Setting2 */
	OTM8009A_CMD_ESET2        = 0xD500, /* W/R - LPDT - 360 */
	/* CE Enable */
	OTM8009A_CMD_EEN          = 0xD680, /* W/R - LPDT - 1 */
	/* AIE Enable */
	OTM8009A_CMD_IEEN         = 0xD700, /* W/R - LPDT - 1 */
	/* GVDD/NGVDD Setting */
	OTM8009A_CMD_VDDSET       = 0xD800, /* W/R - LPDT - 2 */
	/* VCOM Voltage Setting */
	OTM8009A_CMD_COMDC        = 0xD900, /* W/R - LPDT - 1 */
	/* Gamma Correction Characteristics Setting (2.2 + ) */
	OTM8009A_CMD_MCT22P       = 0xE100, /* W/R - LPDT - 16 */
	/* Gamma Correction Characteristics Setting (2.2 - ) */
	OTM8009A_CMD_MCT22N       = 0xE200, /* W/R - LPDT - 16 */
	/* Gamma Correction Characteristics Setting (1.8 + ) */
	OTM8009A_CMD_MCT18P       = 0xE300, /* W/R - LPDT - 16 */
	/* Gamma Correction Characteristics Setting (1.8 - ) */
	OTM8009A_CMD_MCT18N       = 0xE400, /* W/R - LPDT - 16 */
	/* Gamma Correction Characteristics Setting (2.5 + ) */
	OTM8009A_CMD_MCT25P       = 0xE500, /* W/R - LPDT - 16 */
	/* Gamma Correction Characteristics Setting (2.5 - ) */
	OTM8009A_CMD_MCT25N       = 0xE600, /* W/R - LPDT - 16 */
	/* Gamma Correction Characteristics Setting (1.0 + ) */
	OTM8009A_CMD_MCT10P       = 0xE700, /* W/R - LPDT - 16 */
	/* Gamma Correction Characteristics Setting (1.0 - ) */
	OTM8009A_CMD_MCT10N       = 0xE800, /* W/R - LPDT - 16 */
	/* NV Memory Write Mode */
	OTM8009A_CMD_VMIN         = 0xEB00, /* W   - LPDT - 1 */
	/* DigitalGammaCorrectionCharacteristics Setting (Red) */
	OTM8009A_CMD_GAMR         = 0xEC00, /* W/R - LPDT - 17 */
	/* DigitalGammaCorrectionCharacteristics Setting (Green) */
	OTM8009A_CMD_GAMG         = 0xED00, /* W/R - LPDT - 17 */
	/* DigitalGammaCorrectionCharacteristics Setting (Blue) */
	OTM8009A_CMD_GAMB         = 0xEE00, /* W/R - LPDT - 17 */
} otm8009a_command_t;


#endif /* DRIVERS_OTM8009A_H_ */
