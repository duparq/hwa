
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Target board definition
 */

/**
 * @page atmelavr_boards
 *
 * @section boards_attiny45 Board attiny45
 *
 * This is just a ATTINY45-20PU on a breadboard with a USB/Serial adapter and a
 * LED connected at pin #5 (PB0/OC0A). No crystal.
 *
 * The serial communication uses 1 wire for RX/TX, AVR pin #2 connected to the
 * RXD pin of the serial adapter, and a 1k resistor is connected between the RXD
 * and TXD pins (it could be replaced by a diode, Schottky preferably).
 *
 *     TINY45 ->  2 : RXD <- Serial Adapter
 *		    : TXD
 *		  1 : DTR
 *		  4 : GND
 *		  8 : VCC
 *
 * To install Diabolo with avrdude/usbasp:
 *
 *	USBASP -> 1  MOSI  5 <- TINY45
 *		  2  VCC   8
 *		  4  GND   4
 *		  5  RST   1
 *		  7  SCK   7
 *		  9  MISO  6
 *
 * @par attiny45.h
 * @include boards/attiny45.h
 * <br>
 */

/*  Device configuration
 */
#define HW_DEVICE_CLK_SRC		rc_pll_16MHz
#define HW_DEVICE_CLK_PSC		1
#define HW_DEVICE_EXTERNAL_RESET	enabled
#define HW_DEVICE_SELF_PROGRAMMING	enabled
#define HW_DEVICE_DEBUG_WIRE		disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON	no
#define HW_DEVICE_CLOCK_OUTPUT		disabled
#define HW_DEVICE_BROWNOUT_DETECTION	4100_4500mV

/*  Settings for building the Diabolo bootloader
 *  Settings for the Diabolo application are in the board's Makefile
 */
#define DIABOLO_PIN_RX			HW_PIN(2)
#define DIABOLO_PIN_TX			HW_PIN(2)
#define DIABOLO_SYNC			5+1

/*  The pin at which the LED is connected. The target device name indicapes its
 *  package, then pin numbers can be used as well as pin names.
 */
#define PIN_LED				HW_PIN(5)	// OC0A

/*  Include HWA definitions
 */
#include <hwa/attiny45_20pu.h>
