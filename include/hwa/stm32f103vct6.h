
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief stm32f103vct6 header file
 */

/**
 * @page stm32f103vct6 STM32F103VCT6
 * @section stm32f103vct6_sym Defined symbols
 *
 * Symbol		       | Value
 * :---------------------------|:------------
 * `HW_DEVICE_STM32F103VCT6`   |Void.
 * `HW_DEVICE_STM32F103xC`     |Void.
 * `HW_DEVICE_PACKAGE_LQFP100` |Void.
 * `HW_DEVICE_FLASH_SIZE`      |256*1024
 * `HW_DEVICE_RAM_SIZE`	       |48*1024
 *
 * See also:
 * * @ref stm32f103
 */

#define HW_DEVICE_STM32F103VCT6
#define HW_DEVICE_STM32F103xC
#define HW_DEVICE_PACKAGE_LQFP100
#define HW_DEVICE_FLASH_SIZE		256*1024
#define HW_DEVICE_RAM_SIZE		48*1024

#include "../../st/stm32/devices/stm32f103.h"
