
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015,2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny45
 */

/**
 * @ingroup attinyx5
 * @defgroup attiny45 ATtiny45
 *
 * Header file:
 *
 * @code
 * #include <hwa/attiny45.h>
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
#define HW_DEVICE			attiny45

/**
 *  Device family
 */
#define HW_DEVICE_ATTINY45

/**
 *  Signature bytes
 */
#define HW_DEVICE_SIGNATURE		0x1E,0x92,0x06

/**
 *  Flash size in bytes
 */
#define HW_DEVICE_FLASH_SIZE		4096

/**
 *  Flash page size in bytes
 */
#define HW_DEVICE_FLASH_PAGE_SIZE	64

/**
 *  EEPROM size in bytes
 */
#define HW_DEVICE_EEPROM_SIZE		256

/**
 *  EEPROM page size in bytes
 */
#define HW_DEVICE_EEPROM_PAGE_SIZE	4

/**
 *  RAM size in bytes
 */
#define HW_DEVICE_RAM_SIZE		256

/** @} */
/** @} */


#include "../../atmel/avr/devices/attinyx5.h"
