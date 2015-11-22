
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions common to all Espressif devices that do not produce C code
 */

#include "../../hwa/hwa_1.h"


/**
 * @ingroup espressif_public_gen_macros
 * @brief Defined for all Atmel AVR devices
 */
#define HW_DEVICE_ESPRESSIF

/**
 * @ingroup espressif_public_gen_macros
 * @brief Defined as `atmel` for all Atmel devices
 */
#define HW_DEVICE_VENDOR	espressif

/**
 * @ingroup espressif_public_gen_macros
 * @brief Defined as `avr` for all Atmel AVR devices
 */
#define HW_DEVICE_ARCH		xtensa

/**
 * @ingroup espressif_public_gen_macros
 * @brief Expands to the CPU clock frequency (cpu cycles per second).
 */
#if defined DOXYGEN
#  define hw_syshz
#endif


/*  Keywords
 */
/* #define _hw_is_bottom_bottom		, 1 */
/* #define _hw_is_clock_clock		, 1 */
/* #define _hw_is_countmode_countmode	, 1 */
/* #define _hw_is_edge_edge		, 1 */
/* #define _hw_is_filter_filter		, 1 */
/* #define _hw_is_input_input		, 1 */
/* #define _hw_is_ocu_ocu			, 1 */
/* #define _hw_is_overflow_overflow	, 1 */
/* #define _hw_is_top_top			, 1 */
/* #define _hw_is_update_update		, 1 */


/**
 * @ingroup espressif_public_gen_macros
 * @brief Address of a register of an object
 */
#define _hw__ra__m1(o,oa, r,rc,ra,...)	(oa+ra)

