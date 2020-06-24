
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATmega328 / ATmega328P
 *
 *  Differences between P/non P versions:
 *    brown-out detector can be disabled by software in P versions
 */

/**
 * @ingroup atmegax8
 * @defgroup atmega328x ATmega328(P)
 * @{
 */

/**
 * @name Target device description
 *
 * These definitions are computed by HWA from the target device name.
 *
 * @{
 */

/**
 *  Flash size in bytes
 */
#define HW_DEVICE_FLASH_SIZE				32768

/**
 *  Flash page size in bytes
 */
#define HW_DEVICE_FLASH_PAGE_SIZE			128

/**
 *  EEPROM size in bytes
 */
#define HW_DEVICE_EEPROM_SIZE				1024

/**
 *  EEPROM page size in bytes
 */
#define HW_DEVICE_EEPROM_PAGE_SIZE			4

/**
 *  RAM size in bytes
 */
#define HW_DEVICE_RAM_SIZE				2048

/**
 *  Address of first application byte (after IRQ vector table)
 */
#define HW_DEVICE_APP_START				0x0068

/** @} */
/** @} */

#include "../../atmel/avr/devices/atmegax8.h"
