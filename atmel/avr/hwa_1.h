
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions common to all Atmel AVR devices that do not produce C code
 */

/**
 * @addtogroup atmelavr
 * @{
 *
 * @name Target device description
 *
 * These definitions are computed by HWA from the target device name and the
 * definitions provided by the user.
 *
 * @{
 */

/**
 * Device vendor
 */
#define HW_DEVICE_VENDOR		atmel

/**
 * Device vendor
 */
#define HW_DEVICE_VENDOR_ATMEL

/**
 * Device architecture
 */
#define HW_DEVICE_ARCH			avr

/**
 * Device architecture
 */
#define HW_DEVICE_ARCH_AVR


/**
 * Address correction for memory definitions (C and assembler address differ!)
 */
#if defined __ASSEMBLER__ || DOXYGEN
#  define HW_AC				-0x20
#else
typedef signed int			int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int			uint8_t __attribute__((__mode__(__QI__)));
typedef signed int			int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int			uint16_t __attribute__ ((__mode__ (__HI__)));
typedef signed int			int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int			uint32_t __attribute__ ((__mode__ (__SI__)));

typedef int16_t				intptr_t;
typedef uint16_t			uintptr_t;
#endif

/** @} */
/** @} */


#include "hwa_errors.h"
#include "../../hwa/hwa_1.h"
