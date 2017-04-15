
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny84
 */

/**
 * @page attiny84 ATtiny84
 * @section attiny84_symbols Defined symbols
 *
 * Symbol		       | Value
 * :---------------------------|:------------
 * `HW_DEVICE`                 |attiny84
 * `HW_DEVICE_ATTINY84`        |Void.
 * `HW_DEVICE_SIGNATURE`       |0x1E,0x93,0x0C
 * `HW_DEVICE_FLASH_SIZE`      |8192
 * `HW_DEVICE_FLASH_PAGE_SIZE` |64
 * `HW_DEVICE_EEPROM_SIZE`     |512
 * `HW_DEVICE_EEPROM_PAGE_SIZE`|4
 * `HW_DEVICE_RAM_SIZE`	       |512
 *
 * See also:
 * * @subpage attiny84a_pu
 * * @ref attinyx4
 */

#define HW_DEVICE			attiny84
#define HW_DEVICE_ATTINY84
#define HW_DEVICE_SIGNATURE		0x1E,0x93,0x0C
#define HW_DEVICE_FLASH_SIZE		8192
#define HW_DEVICE_FLASH_PAGE_SIZE	64
#define HW_DEVICE_EEPROM_SIZE		512
#define HW_DEVICE_EEPROM_PAGE_SIZE	4
#define HW_DEVICE_RAM_SIZE		512

#include "../../atmel/avr/devices/attinyx4.h"
