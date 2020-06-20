
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
 * @section mini-stm32-v3-0 Board from www.PowerMCU.com
 *
 * There is a STM32F103RBT6 with:
 *  * one 8 MHz crystal
 *  * one 32768 Hz crystal
 *  * one reset button
 *  * one BOOT0 button
 *  * two buttons: KEY1 + KEY2
 *  * one power LED3
 *  * one com LED4
 *  * two I/O LEDs: LED1 + LED2
 *  * two USB connectors
 *
 * @par 
 * @include boards/mini-stm32-v3.0.h
 * <br>
 */

/*  Device configuration
 */
#define HW_DEVICE_HSEHZ			8e6
#define HW_DEVICE_LSEHZ			32768

/*  The pin at which the LED is connected. The target device name indicates its
 *  package, then pin numbers can be used as well as pin names.
 */
#define LED				(porta,2)
#define LED1				(porta,2)
#define LED2				(porta,3)


/*  Include HWA definitions
 */
#include <hwa/stm32f103rbt6.h>
