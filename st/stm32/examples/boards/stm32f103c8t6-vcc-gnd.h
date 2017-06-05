
/*  This file is part of the HWA project.
 *  Copyright (c) 2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Target board definition
 */

/**
 * @page stm32_boards
 *
 * @section stm32_board_vcc_gnd Board from www.vcc-gnd.com
 *
 * There is a STM32F103C8T6 with:
 *  * one 8 MHz crystal
 *  * one 32768 Hz crystal
 *  * one reset button
 *  * one power LED
 *  * one I/O LED
 *  * two jumpers for BOOT0 and BOOT1
 *  * one USB connector
 *
 * @par stm32f103c8t6-vcc-gnd.h
 * @include boards/stm32f103c8t6-vcc-gnd.h
 * <br>
 */

/*  Device configuration
 */
#define HW_DEVICE_HSEHZ			8e6
#define HW_DEVICE_LSEHZ			32768

/*  The pin at which the LED is connected. The target device name indicapes its
 *  package, then pin numbers can be used as well as pin names.
 */
#define PIN_LED				pin_pc13
#define PIN_LED1			pin_pc13


/*  Include HWA definitions
 */
#include <hwa/stm32f103c8t6.h>
