
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/** \brief	Target device is an Atmel AVR.
 */
#define HW_DEVICE_ATMELAVR
#define HW_DEVICE_VENDOR		atmel
#define HW_DEVICE_ARCH			avr


/*  Keywords
 */
#define _hw_is_bottom_bottom		, 1
#define _hw_is_clock_clock		, 1
#define _hw_is_countmode_countmode	, 1
#define _hw_is_edge_edge			, 1
#define _hw_is_filter_filter		, 1
#define _hw_is_input_input		, 1
#define _hw_is_ocu_ocu			, 1
#define _hw_is_overflow_overflow		, 1
#define _hw_is_top_top			, 1
#define _hw_is_update_update		, 1


/*  hw_addr(...) : address of a memory definition
 *
 *	C and assembler address differ!
 */
#if defined __ASSEMBLER__
#  define _hw_addr__m1(p,a, r,rw,ra,...)	(a+ra-0x20)
#else
#  define _hw_addr__m1(p,a, r,rw,ra,...)	(a+ra)
#endif

/*  _hw_isr_(...): address (vector) of ISR
 *
 *	FIXME: should name it _vector(...)
 */
#if defined __ASSEMBLER__
#  define _hw_isr_(vector, ...)			__vector_##vector
#endif
