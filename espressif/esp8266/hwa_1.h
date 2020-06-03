
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions common to all Espressif devices that do not produce C code
 */


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
#  define HW_SYSHZ
#endif

#if !defined __ASSEMBLER__
typedef signed int int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
typedef signed int int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));
typedef signed int int64_t __attribute__((__mode__(__DI__)));
typedef unsigned int uint64_t __attribute__((__mode__(__DI__)));
typedef int32_t intptr_t;
typedef uint32_t uintptr_t;
#endif

#include "../hwa/hwa_1.h"
