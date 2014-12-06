
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/** \brief	Target device is an Atmel AVR.
 */
#define HW_DEVICE_ATMELAVR


/*	Keywords
 */
#define hw_is_bottom_bottom		, 1
#define hw_is_clock_clock		, 1
#define hw_is_countmode_countmode	, 1
#define hw_is_edge_edge			, 1
#define hw_is_filter_filter		, 1
#define hw_is_input_input		, 1
#define hw_is_ocu_ocu			, 1
#define hw_is_overflow_overflow		, 1
#define hw_is_top_top			, 1
#define hw_is_update_update		, 1


/*	Register address offset for C/assembler
 */
#ifndef __ASSEMBLER__
#  define HW_RA_OFFSET		0
#else
#  define HW_RA_OFFSET		-0x20
#endif


/*	hw_addr(...) : address of a memory definition (generic)
 */
#if defined __ASSEMBLER__
#  define _hw_addr_bits1(cc,cn,ca, rn,rw,ra,...)	(ca+ra-0x20)
#  define _hw_isr_(vector, ...)				__vector_##vector
#else
#  define _hw_addr_bits1(cc,cn,ca, rn,rw,ra,...)	(ca+ra)
#endif
