
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATmega32U4
 */

#define HW_DEVICE					atmega32u4
#define HW_DEVICE_ATMEGA32U4
#define HW_DEVICE_SIGNATURE				0x1E,0x95,0x87

#define HW_DEVICE_FLASH_SIZE				32768
#define HW_DEVICE_FLASH_PAGE_SIZE			128	/* Error in the datasheet */
#define HW_DEVICE_EEPROM_SIZE				1024
#define HW_DEVICE_EEPROM_PAGE_SIZE			4	/* Error in the datasheet */

#define HW_DEVICE_RAM_SIZE				2560
#define HW_DEVICE_RAM_START				0x0100
#define HW_DEVICE_APP_START				0x00AC // 0x00C0 in Caterina ?


/*  Fuse bit whose configuration differs between ATmega16U4 and ATmega32U4
 */
#if !defined HW_DEVICE_PIN_HWB
#  define HW_DEVICE_PIN_HWB				enabled
#endif


#include "atmegaxu4.h"
