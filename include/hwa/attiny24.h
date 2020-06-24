
#ifndef HWA_H
#define HWA_H

/* This file is part of the HWA project.
 * Copyright (c) 2012,2015,2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny24
 */

/**
 * @ingroup attinyx4
 * @defgroup attiny24 ATtiny24
 *
 * Header file:
 *
 * @code
 * #include <hwa/attiny24.h>
 * @endcode
 *
 * @{
 *
 * @name Target device description
 *
 * These definitions are computed by HWA from the target device name.
 *
 * @{
 */

/**
 *  Name of the device (for the compiler/programmer)
 */
#define HW_DEVICE			attiny24

/**
 *  Device family
 */
#define HW_DEVICE_ATTINY24

/**
 *  Signature bytes
 */
#define HW_DEVICE_SIGNATURE		0x1E,0x91,0x0B

/**
 *  Flash size in bytes
 */
#define HW_DEVICE_FLASH_SIZE		2048

/**
 *  Flash page size in bytes
 */
#define HW_DEVICE_FLASH_PAGE_SIZE	32

/**
 *  EEPROM size in bytes
 */
#define HW_DEVICE_EEPROM_SIZE		128

/**
 *  EEPROM page size in bytes
 */
#define HW_DEVICE_EEPROM_PAGE_SIZE	4

/**
 *  RAM size in bytes
 */
#define HW_DEVICE_RAM_SIZE		128

/** @} */
/** @} */


#include "../../atmel/avr/devices/attinyx4.h"

#endif
