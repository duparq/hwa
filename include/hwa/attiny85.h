
#ifndef HWA_H
#define HWA_H

/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny85
 */

/**
 * @ingroup attinyx5
 * @defgroup attiny85 ATtiny85
 *
 * Header file:
 *
 * @code
 * #include <hwa/attiny85.h>
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
#define HW_DEVICE			attiny85

/**
 *  Device family
 */
#define HW_DEVICE_ATTINY85

/**
 *  Signature bytes
 */
#define HW_DEVICE_SIGNATURE		0x1E,0x93,0x0B

/**
 *  Flash size in bytes
 */
#define HW_DEVICE_FLASH_SIZE		8192

/**
 *  Flash page size in bytes
 */
#define HW_DEVICE_FLASH_PAGE_SIZE	64

/**
 *  EEPROM size in bytes
 */
#define HW_DEVICE_EEPROM_SIZE		512

/**
 *  EEPROM page size in bytes
 */
#define HW_DEVICE_EEPROM_PAGE_SIZE	4

/**
 *  RAM size in bytes
 */
#define HW_DEVICE_RAM_SIZE		512

/** @} */
/** @} */


#include "../../atmel/avr/devices/attinyx5.h"

#endif
