
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_usia_1.h"

/*
 *	Universal Serial Interface
 */


/*	Class registers		'reg', rw, ra, riv, rwm
 */
#define hw_usia_br		reg, 8, 0x30 -0x2D, 0x00, 0x00
#define hw_usia_dr		reg, 8, 0x2F -0x2D, 0x00, 0xFF
#define hw_usia_sr		reg, 8, 0x2E -0x2D, 0x00, 0xEF
#define hw_usia_cr		reg, 8, 0x2D -0x2D, 0x00, 0xFF

/*	Class bits
 */
#define hw_usia_sie		rb1, cr, 1, 7
#define hw_usia_oie		rb1, cr, 1, 6
#define hw_usia_wm		rb1, cr, 2, 4
#define hw_usia_cs		rb1, cr, 2, 2
#define hw_usia_clk		rb1, cr, 1, 1
#define hw_usia_tc		rb1, cr, 1, 0

#define hw_usia_sif		rb1, sr, 1, 7
#define hw_usia_oif		rb1, sr, 1, 6
#define hw_usia_pf		rb1, sr, 1, 5
#define hw_usia_dc		rb1, sr, 1, 4
#define hw_usia_cnt		rb1, sr, 4, 0

/*	Instance	        class, name, id, address
 */
#define hw_usi0			usia, usi0, 601, 0x002D

/*	Instance of USI used as SPI master with software clock
 */
#define hw_usi0_spimaster_swclk		usia_spimaster_swclk, usi0_spimaster_swclk, 602, usi0

/*	Instance of USI used as SPI master with counter0 overflow clock
 */
#define hw_usi0_spimaster_c0clk		usia_spimaster_c0clk, usi0_spimaster_c0clk, 603, usi0


/*	HWA structure
 */
#define HWA_DCL_USIS		hwa_usia_t usi0
