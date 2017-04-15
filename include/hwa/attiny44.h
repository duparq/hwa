
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny44
 */

/**
 * @page attiny44 ATtiny44
 * @section attiny44_symbols Defined symbols
 *
 * Symbol		       | Value
 * :---------------------------|:------------
 * `HW_DEVICE_ATTINY44`        |Void.
 * `HW_DEVICE_SIGNATURE`       |0x1E,0x92,0x07
 * `HW_DEVICE_FLASH_SIZE`      |4096
 * `HW_DEVICE_FLASH_PAGE_SIZE` |64
 * `HW_DEVICE_EEPROM_SIZE`     |256
 * `HW_DEVICE_EEPROM_PAGE_SIZE`|4
 * `HW_DEVICE_RAM_SIZE`	       |256
 *
 * See also:
 * * @subpage attiny44a_pu
 * * @ref attinyx4
 */

#define HW_DEVICE_ATTINY44
#define HW_DEVICE_SIGNATURE		0x1E,0x92,0x07
#define HW_DEVICE_FLASH_SIZE		4096
#define HW_DEVICE_FLASH_PAGE_SIZE	64
#define HW_DEVICE_EEPROM_SIZE		256
#define HW_DEVICE_EEPROM_PAGE_SIZE	4
#define HW_DEVICE_RAM_SIZE		256

#include "../../atmel/avr/devices/attinyx4.h"
