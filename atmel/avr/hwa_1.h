
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions common to all Atmel AVR devices that do not produce C code
 */

#include "../../hwa/hwa_1.h"

/**
 * @ingroup public_atmelavr_def
 * @brief Defined for all Atmel AVR devices
 * @hideinitializer
 */
#define HW_DEVICE_ATMELAVR

#if !defined DOXYGEN
#  define HW_DEVICE_VENDOR	atmel
#  define HW_DEVICE_ARCH	avr
#endif


/*  Keywords
 */
#define _hw_is_bottom_bottom		, 1
#define _hw_is_clock_clock		, 1
#define _hw_is_countmode_countmode	, 1
#define _hw_is_edge_edge		, 1
#define _hw_is_filter_filter		, 1
#define _hw_is_input_input		, 1
#define _hw_is_ocu_ocu			, 1
#define _hw_is_overflow_overflow	, 1
#define _hw_is_top_top			, 1
#define _hw_is_update_update		, 1


/*  Address of a memory definition
 *
 *	C and assembler address differ!
 */
#if defined __ASSEMBLER__
#  define _hw__a__m1(o,a,r,rc,ra,...)		(a+ra-0x20)
#else
#  define _hw__a__m1(o,a,r,rc,ra,...)		(a+ra)
#endif


/*  _hw_isr_(...): address (vector) of ISR
 *
 *	FIXME: should name it _vector(...)
 */
#if defined __ASSEMBLER__
#  define _HW_ISR_(vector, ...)			__vector_##vector
#endif
