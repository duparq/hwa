
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015,2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny84
 */

/**
 * @ingroup attinyx4
 * @defgroup attiny84 ATtiny84
 *
 * Header file:
 *
 * @code
 * #include <hwa/attiny84.h>
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
#define HW_DEVICE			attiny84

/**
 *  Device family
 */
#define HW_DEVICE_ATTINY84

/**
 *  Signature bytes
 */
#define HW_DEVICE_SIGNATURE		0x1E,0x93,0x0C

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


#include "../../atmel/avr/devices/attinyx4.h"
