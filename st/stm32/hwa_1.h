
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions common to all STM32 devices that do not produce C code
 */
#if !defined DOXYGEN
#  define HW_DEVICE_VENDOR_ST
#  define HW_DEVICE_ARCH_STM32
#  define HW_DEVICE_VENDOR		st
#  define HW_DEVICE_ARCH		stm32
#endif


/*  Keywords for stm32
 */
#define _hw_is_compare_flag_compare_flag	, 1


#if !defined __ASSEMBLER__
typedef signed int int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
typedef signed int int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));
typedef int32_t intptr_t;
typedef uint32_t uintptr_t;
#endif

#include "../../hwa/hwa_1.h"
