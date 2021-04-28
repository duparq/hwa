
/*  This file is part of the HWA project.
 *  Copyright (c) 2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Target board definition
 */

/**
 * @ingroup stm32_boards
 * @defgroup mini-stm32-v3-0 Board from www.PowerMCU.com
 *
 * There is a @ref stm32f103 "STM32F103RBT6" with:
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
 * @image html mini-stm32-v3.0.jpeg
 *
 * @{
 */

/**
 * @name Board description
 * @{
 */

/**
 * Frequency of the HSE oscillator crystal
 */
#define HW_DEVICE_HSEHZ			8e6

/**
 * Frequency of the LSE oscillator crystal
 */
#define HW_DEVICE_LSEHZ			32768

/** @} */


/**
 * @name Pin definitions
 * @{
 */
#define LED				(porta,2)	///< X
#define LED1				(porta,2)	///< X
#define LED2				(porta,3)	///< X

/** @} */
/** @} */


/*  Include HWA definitions
 */
#include <hwa/stm32f103rbt6.h>
