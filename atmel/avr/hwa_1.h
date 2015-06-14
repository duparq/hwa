
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions common to all Atmel AVR devices that do not produce C code
 */

#include "../../../hwa/hwa_1.h"

/**
 * @defgroup public_gen_instructions_atmelavr Instructions related to hardware modification for Atmel AVR devices
 *
 * These instructions lead to a modification of the hardware configuration that
 * is not related to a specific object.
 */

#if defined DOXYGEN
/**
 * @ingroup public_gen_macros
 * @brief The name of the device
 */
#  define HW_DEVICE		<device_name>
/**
 * @ingroup public_gen_macros
 * @brief The packaging of the device
 */
#  define HW_DEVICE_PACKAGE	<device_package>
#endif

/**
 * @ingroup public_gen_macros_atmelavr
 * @brief This symbol is defined for all Atmel AVR devices
 */
#define HW_DEVICE_ATMELAVR

/**
 * @ingroup public_gen_macros_atmelavr
 * @brief Name of the vendor
 */
#define HW_DEVICE_VENDOR	atmel

/**
 * @ingroup public_gen_macros_atmelavr
 * @brief Architecture name
 */
#define HW_DEVICE_ARCH		avr

/**
 * @ingroup public_gen_macros_atmelavr
 * @brief The CPU clock frequency.
 */
#if defined DOXYGEN
#  define hw_syshz		<cpu cycles per second>
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


/*  hw_addr(...) : address of a memory definition
 *
 *	C and assembler address differ!
 */
#if defined __ASSEMBLER__
#  define _hw_addr__m1(o,a,r,rc,ra,...)		(a+ra-0x20)
#  define _hw__ra__m1(o,a,r,rc,ra,...)		(a+ra-0x20)
#  define _hw_ra__m1(o,a,r,rc,ra,...)		(a+ra-0x20)
#else
#  define _hw_addr__m1(o,a,r,rc,ra,...)		(a+ra)
#  define _hw__ra__m1(o,a,r,rc,ra,...)		(a+ra)
#  define _hw_ra__m1(o,a,r,rc,ra,...)		(a+ra)
#endif


/*  _hw_isr_(...): address (vector) of ISR
 *
 *	FIXME: should name it _vector(...)
 */
#if defined __ASSEMBLER__
#  define _hw_isr_(vector, ...)			__vector_##vector
#endif
