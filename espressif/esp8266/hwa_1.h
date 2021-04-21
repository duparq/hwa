
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions common to all Espressif devices that do not produce C code
 */

/**
 * @addtogroup esp8266
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
 *  Device family
 */
#define HW_DEVICE_FAMILY		esp8266

/**
 *  Device family
 */
#define HW_DEVICE_FAMILY_ESP8266

/**
 * Device vendor
 */
#define HW_DEVICE_VENDOR		espressif

/**
 * Device vendor
 */
#define HW_DEVICE_VENDOR_ESPRESSIF

/**
 * Device architecture
 */
#define HW_DEVICE_ARCH			xtensa

/**
 * Device architecture
 */
#define HW_DEVICE_ARCH_XTENSA

/** @} */
/** @} */


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

#include "hwa_errors.h"		/* Family specific error messages */

#include "../hwa/hwa_1.h"
