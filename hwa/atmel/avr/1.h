
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions common to all Atmel AVR devices that do not produce C code
 */

/**
 * @page atmelavr Atmel AVR common definitions
 */

/**
 * @page atmelavr
 * @section atmelavr_hw_device HW_DEVICE_ common definitions
 *
 * The following symbols are defined for all the Atmel AVR devices:
 * * @ref HW_DEVICE
 * * @ref HW_DEVICE_PACKAGE
 * * @ref HW_DEVICE_ATMELAVR
 * * @ref HW_DEVICE_VENDOR
 * * @ref HW_DEVICE_ARCH
 * * @ref hw_syshz
 */
#if defined DOXYGEN
/**
 * @brief The name of the device
 */
#  define HW_DEVICE	<device_name>
/**
 * @brief The packaging of the device
 */
#  define HW_DEVICE_PACKAGE	<device_package>
#endif

/**
 * @brief Defined for all Atmel AVR devices
 */
#define HW_DEVICE_ATMELAVR

/**
 * @brief Name of the vendor
 */
#define HW_DEVICE_VENDOR		atmel

/**
 * @brief Architecture name
 */
#define HW_DEVICE_ARCH			avr

/**
 * @brief The CPU clock frequency.
 */
#if defined DOXYGEN
#  define hw_syshz	<cpu cycles per second>
#endif


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
#  define _hw_addr__m1(o,a,r,rc,ra,...)		(a+ra-0x20)
#  define _hw_ra__m1(o,a,r,rc,ra,...)		(a+ra-0x20)
#else
#  define _hw_addr__m1(o,a,r,rc,ra,...)		(a+ra)
#  define _hw_ra__m1(o,a,r,rc,ra,...)		(a+ra)
#endif


/*  _hw_isr_(...): address (vector) of ISR
 *
 *	FIXME: should name it _vector(...)
 */
#if defined __ASSEMBLER__
#  define _hw_isr_(vector, ...)			__vector_##vector
#endif
