
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
 * @defgroup public_gen_instructions_atmelavr Instructions for Atmel AVR devices that are not related to a speficic object
 *
 * These instructions lead to a modification of the hardware configuration that
 * is not related to a specific object.
 */

#if defined DOXYGEN
/**
 * @ingroup public_gen_macros
 * @brief The name of the device as used by the compiler
 */
#  define HW_DEVICE
/**
 * @ingroup public_gen_macros
 * @brief Defined if the packaging of the device is device_package
 */
#  define HW_DEVICE_PACKAGE_device_package
#endif

/**
 * @ingroup public_gen_macros_atmelavr
 * @brief Defined for all Atmel AVR devices
 */
#define HW_DEVICE_ATMELAVR

/**
 * @ingroup public_gen_macros_atmelavr
 * @brief Defined as `atmel` for all Atmel devices
 */
#define HW_DEVICE_VENDOR	atmel

/**
 * @ingroup public_gen_macros_atmelavr
 * @brief Defined as `avr` for all Atmel AVR devices
 */
#define HW_DEVICE_ARCH		avr

/**
 * @ingroup public_gen_macros_atmelavr
 * @brief Expands to the CPU clock frequency (cpu cycles per second).
 */
#if defined DOXYGEN
#  define hw_syshz
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
#  define _HW_ISR_(vector, ...)			__vector_##vector
#endif
