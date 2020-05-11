
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief stm32f103rbt6 Header file
 */

/**
 * @page stm32f103rbt6 STM32F103RBT6
 * @section stm32f103rbt6_inc Header file
 * @code
 * #include <hwa/stm32f103rbt6.h>
 * @endcode
 */

/**
 * @page stm32f103rbt6
 * @section stm32f103rbt6_sym Defined symbols
 *
 * Symbol		       | Value
 * :---------------------------|:------------
 * `HW_DEVICE_STM32F103RBT6`   |Void.
 * `HW_DEVICE_STM32F103xB`     |Void.
 * `HW_DEVICE_STM32F103Rx`     |Void.
 * `HW_DEVICE_DENSITY_MEDIUM`  |Void.
 * `HW_DEVICE_LINE_PERFORMANCE`|Void.
 * `HW_DEVICE_PACKAGE_LQFP64`  |Void.
 * `HW_DEVICE_FLASH_SIZE`      |128*1024
 * `HW_DEVICE_RAM_SIZE`        |20*1024
 *
 */

#define HW_DEVICE_STM32F103RBT6
#define HW_DEVICE_STM32F103xB
#define HW_DEVICE_STM32F103Rx
#define HW_DEVICE_DENSITY_MEDIUM
#define HW_DEVICE_LINE_PERFORMANCE
#define HW_DEVICE_PACKAGE_LQFP64
#define HW_DEVICE_FLASH_SIZE		128*1024
#define HW_DEVICE_RAM_SIZE		20*1024

/*	Peripheral counts
 */
#define HW_DEVICE_NGPTIM		3
#define HW_DEVICE_NACTIM		1
#define HW_DEVICE_NSPI			2
#define HW_DEVICE_NI2C			2
#define HW_DEVICE_NUSART		3
#define HW_DEVICE_NUSB			1
#define HW_DEVICE_NCAN			1
#define HW_DEVICE_NGPIO			51
#define HW_DEVICE_NADC			2
#define HW_DEVICE_NADCCH		16


#include "../../st/stm32/devices/stm32f103.h"
