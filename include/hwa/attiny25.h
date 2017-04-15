
#ifndef HWA_H
#define HWA_A

/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny25
 */

/**
 * @page attiny25 ATtiny25
 * @section attiny25_symbols Defined symbols
 *
 * Symbol		       | Value
 * :---------------------------|:------------
 * `HW_DEVICE`                 |attiny25
 * `HW_DEVICE_ATTINY25`        |Void.
 * `HW_DEVICE_SIGNATURE`       |0x1E,0x91,0x08
 * `HW_DEVICE_FLASH_SIZE`      |2048
 * `HW_DEVICE_FLASH_PAGE_SIZE` |32
 * `HW_DEVICE_EEPROM_SIZE`     |128
 * `HW_DEVICE_EEPROM_PAGE_SIZE`|4
 * `HW_DEVICE_RAM_SIZE`	       |128
 *
 * See also:
 * * @ref attinyx5
 * * @subpage attiny25_20pu
 */

#define HW_DEVICE			attiny25
#define HW_DEVICE_ATTINY25
#define HW_DEVICE_SIGNATURE		0x1E,0x91,0x08
#define HW_DEVICE_FLASH_SIZE		2048
#define HW_DEVICE_FLASH_PAGE_SIZE	32
#define HW_DEVICE_EEPROM_SIZE		128
#define HW_DEVICE_EEPROM_PAGE_SIZE	4
#define HW_DEVICE_RAM_SIZE		128

#include "../../atmel/avr/devices/attinyx5.h"

#endif
