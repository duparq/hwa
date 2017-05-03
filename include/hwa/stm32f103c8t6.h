
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief stm32f103c8t6 header file
 */

/**
 * @page stm32f103c8t6 STM32F103C8T6
 * @section stm32f103c8t6_symbols Defined symbols
 *
 * Symbol		       | Value
 * :---------------------------|:------------
 * `HW_DEVICE_STM32F103C8T6`   |Void.
 * `HW_DEVICE_STM32F103x8`     |Void.
 * `HW_DEVICE_PACKAGE_LQFP48`  |Void.
 * `HW_DEVICE_FLASH_SIZE`      |64*1024
 * `HW_DEVICE_RAM_SIZE`	       |20*1024
 *
 * See also:
 * * @ref stm32f103
 */

#define HW_DEVICE			stm32f103c8t6
#define HW_DEVICE_STM32F103C8T6
#define HW_DEVICE_STM32F103x8
#define HW_DEVICE_PACKAGE_LQFP48
#define HW_DEVICE_FLASH_SIZE		64*1024
#define HW_DEVICE_RAM_SIZE		20*1024

#include "../../st/stm32/devices/stm32f103.h"
