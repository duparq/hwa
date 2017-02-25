
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny45
 */

#define HW_DEVICE_ATTINY45
#define HW_DEVICE_SIGNATURE		0x1E,0x92,0x06
#define HW_DEVICE_FLASH_SIZE		4096
#define HW_DEVICE_FLASH_PAGE_SIZE	64
#define HW_DEVICE_EEPROM_SIZE		256
#define HW_DEVICE_EEPROM_PAGE_SIZE	4
#define HW_DEVICE_RAM_SIZE		256

#include "attinyx5.h"
