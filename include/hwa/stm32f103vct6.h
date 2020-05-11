
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief stm32f103vct6 Header file
 */

/**
 * @page stm32f103vct6 STM32F103VCT6
 * @section stm32f103vct6_inc Header file
 * @code
 * #include <hwa/stm32f103vct6.h>
 * @endcode
 */

/**
 * @page stm32f103vct6
 * @section stm32f103vct6_sym Defined symbols
 *
 * Symbol		       | Value
 * :---------------------------|:------------
 * `HW_DEVICE_STM32F103VCT6`   |Void.
 * `HW_DEVICE_STM32F103xC`     |Void.
 * `HW_DEVICE_STM32F103Vx`     |Void.
 * `HW_DEVICE_DENSITY_HIGH  `  |Void.
 * `HW_DEVICE_LINE_PERFORMANCE`|Void.
 * `HW_DEVICE_PACKAGE_LQFP100` |Void.
 * `HW_DEVICE_FLASH_SIZE`      |256*1024
 * `HW_DEVICE_RAM_SIZE`        |48*1024
 *
 */

#define HW_DEVICE_STM32F103VCT6
#define HW_DEVICE_STM32F103xC
#define HW_DEVICE_STM32F103Vx
#define HW_DEVICE_DENSITY_HIGH
#define HW_DEVICE_LINE_PERFORMANCE
#define HW_DEVICE_PACKAGE_LQFP100
#define HW_DEVICE_FLASH_SIZE		256*1024
#define HW_DEVICE_RAM_SIZE		48*1024

/*	Peripheral counts
 */
#define HW_DEVICE_NFSMC			1
#define HW_DEVICE_NGPTIM		4
#define HW_DEVICE_NACTIM		2
#define HW_DEVICE_NSPI			3
#define HW_DEVICE_NI2S			2
#define HW_DEVICE_NI2C			2
#define HW_DEVICE_NUSART		5
#define HW_DEVICE_NUSB			1
#define HW_DEVICE_NCAN			1
#define HW_DEVICE_NSDIO			1
#define HW_DEVICE_NGPIO			80
#define HW_DEVICE_NADC12		3
#define HW_DEVICE_NADC12CH		16


#include "../../st/stm32/devices/stm32f103.h"
