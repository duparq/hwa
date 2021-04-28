
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief STM32F103C8T6
 */

/**
 * @ingroup stm32f103
 * @defgroup stm32f103c8t6 STM32F103C8T6
 *
 * Header file:
 *
 * @code
 * #include <hwa/stm32f103c8t6.h>
 * @endcode
 *
 * @{
 */

/**
 *  Device family
 */
#define HW_DEVICE_STM32F103C8T6

/**
 *  Device family
 */
#define HW_DEVICE_STM32F103x8

/**
 *  Device family
 */
#define HW_DEVICE_STM32F103Cx

/**
 *  Device family
 */
#define HW_DEVICE_DENSITY_MEDIUM

/**
 *  Device family
 */
#define HW_DEVICE_LINE_PERFORMANCE

/**
 *  Package of the device
 */
#define HW_DEVICE_PACKAGE_LQFP48

/**
 *  Flash size in bytes
 */
#define HW_DEVICE_FLASH_SIZE		(64*1024)

/**
 *  RAM size in bytes
 */
#define HW_DEVICE_RAM_SIZE		(20*1024)

/** @} */

/*	Peripheral counts
 */
/* #define HW_DEVICE_NGPTIM		3 */
/* #define HW_DEVICE_NACTIM		1 */
/* #define HW_DEVICE_NSPI			2 */
/* #define HW_DEVICE_NI2C			2 */
/* #define HW_DEVICE_NUSART		3 */
/* #define HW_DEVICE_NUSB			1 */
/* #define HW_DEVICE_NCAN			1 */
/* #define HW_DEVICE_NGPIO			37 */
/* #define HW_DEVICE_NADC12		2 */
/* #define HW_DEVICE_NADC12CH		10 */


#include "../../st/stm32/devices/stm32f103.h"
