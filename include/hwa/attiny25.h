#ifndef HWA_H
#define HWA_H

/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny25
 */

/**
 * @ingroup attinyx5
 * @defgroup attiny25 ATtiny25
 *
 * Header file:
 *
 * @code
 * #include <hwa/attiny25.h>
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
#define HW_DEVICE			attiny25

/**
 *  Device family
 */
#define HW_DEVICE_ATTINY25

/**
 *  Signature bytes
 */
#define HW_DEVICE_SIGNATURE		0x1E,0x91,0x08

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


#include "../../atmel/avr/devices/attinyx5.h"

#endif
