
#ifndef HWA_H
#define HWA_H

/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny45
 */

/**
 * @page attiny45 ATtiny45
 * @section attiny45_symbols Defined symbols
 *
 * Symbol		       | Value
 * :---------------------------|:------------
 * `HW_DEVICE`                 |attiny45
 * `HW_DEVICE_ATTINY45`        |Void.
 * `HW_DEVICE_SIGNATURE`       |0x1E,0x92,0x06
 * `HW_DEVICE_FLASH_SIZE`      |4096
 * `HW_DEVICE_FLASH_PAGE_SIZE` |64
 * `HW_DEVICE_EEPROM_SIZE`     |256
 * `HW_DEVICE_EEPROM_PAGE_SIZE`|4
 * `HW_DEVICE_RAM_SIZE`	       |256
 *
 * See also:
 * * @ref attinyx5
 * * @subpage attiny45_20pu
 */

#define HW_DEVICE			attiny45
#define HW_DEVICE_ATTINY45
#define HW_DEVICE_SIGNATURE		0x1E,0x92,0x06
#define HW_DEVICE_FLASH_SIZE		4096
#define HW_DEVICE_FLASH_PAGE_SIZE	64
#define HW_DEVICE_EEPROM_SIZE		256
#define HW_DEVICE_EEPROM_PAGE_SIZE	4
#define HW_DEVICE_RAM_SIZE		256

#include "../../atmel/avr/devices/attinyx5.h"

#endif
