
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny85
 */

#define HW_DEVICE                       attiny85
#define HW_DEVICE_ATTINY85
#define HW_DEVICE_SIGNATURE             0x1E,0x93,0x0B
#define HW_DEVICE_FLASH_SIZE            8192
#define HW_DEVICE_FLASH_PAGE_SIZE       64
#define HW_DEVICE_EEPROM_SIZE           512
#define HW_DEVICE_EEPROM_PAGE_SIZE      4
#define HW_DEVICE_RAM_SIZE              512

#include "attinyx5.h"
