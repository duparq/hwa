
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions common to all Atmel AVR devices that do not produce C code
 */

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


/*  Keywords for stm32
 */
#define _hw_is_compare_flag_compare_flag	, 1
#define _hw_is_loop_loop			, 1


#include "../../hwa/hwa_1.h"
