
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

/*  Address correction of a memory definition (C and assembler address differ!)
 */
#if defined __ASSEMBLER__
#  define HW_AC					-0x20
#else
typedef signed int int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
typedef signed int int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));
typedef int16_t intptr_t;
typedef uint16_t uintptr_t;
#endif

#include "../../hwa/hwa_1.h"
