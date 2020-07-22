
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
 * @defgroup stm32_board_bluepill Board from www.vcc-gnd.com aka "Blue pill"
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
 * @image html bluepill-pinout.gif
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


/**
 * @name Pin definitions
 * @{
 *
 *  The pin the LED is connected to. The target device name indicates its
 *  package, then pin numbers can be used as well as pin names.
 */
#define LED				(portc, 13)	///< X
#define LED1				(portc, 13)	///< X

/** @} */
/** @} */
/** @} */


/*  Include HWA definitions
 */
#include <hwa/stm32f103c8t6.h>
