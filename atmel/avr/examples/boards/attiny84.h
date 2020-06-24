
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Target board definition
 */

/**
 * @ingroup atmelavr_boards
 * @defgroup board_attiny84 Board ATtiny84
 *
 * This is just a ATTINY84A-PU on a breadboard with a USB/Serial adapter and a
 * LED connected at pin #7 (PA6/OC1A). No crystal.
 *
 * The serial communication uses 1 wire for RX/TX. The AVR communication
 * pin is connected to the RXD pin of the serial adapter and a 1k resistor
 * is connected between the RXD and TXD pins (it could be replaced by a
 * diode, Schottky preferably).
 *
 * @par Pin Configuration
 *
 *			     Vcc o   U	 o Gnd
 *		  XTAL1 CLKI PB0 o	 o PA0 ADC0 AREF
 *		       XTAL2 PB1 o	 o PA1 ADC1 AIN0
 *		       RESET PB3 o	 o PA2 ADC2 AIN1
 *	     INT0 OC0A CKOUT PB2 o	 o PA3 ADC3 T0
 *	       ICP OC0B ADC7 PA7 o	 o PA4 ADC4 USCK SCL T1
 *     OC1A SDA MOSI DI ADC6 PA6 o	 o PA5 ADC5 DO MISO OC1B
 *
 *
 * @par Serial adapter wiring
 *
 *     TINY84 ->  2 : RXD <- Serial Adapter
 *		    : TXD
 *		  4 : DTR
 *		 14 : GND
 *		  1 : VCC
 *
 * @par USBASP wiring
 *
 *	USBASP -> 1  MOSI  7  <- TINY84
 *		  2  VCC   1
 *		  4  GND   14
 *		  5  RST   4
 *		  7  SCK   9
 *		  9  MISO  8
 *
 * @par attiny84.h
 * @include boards/attiny84.h
 */

/**
 * @addtogroup board_attiny84
 * @{
 * @name Device configuration
 * @{
 */

#define HW_DEVICE_CLK_SRC		rc_8MHz			/**<> */
#define HW_DEVICE_CLK_PSC		1			/**<> */
#define HW_DEVICE_EXTERNAL_RESET	enabled			/**<> */
#define HW_DEVICE_SELF_PROGRAMMING	enabled			/**<> */
#define HW_DEVICE_DEBUG_WIRE		disabled		/**<> */
#define HW_DEVICE_WATCHDOG_ALWAYS_ON	no			/**<> */
#define HW_DEVICE_CLOCK_OUTPUT		disabled		/**<> */
#define HW_DEVICE_BROWNOUT_DETECTION	2500_2900mV		/**<> */

/**
 * @}
 *
 * @name Settings for the Diabolo bootloader
 *
 *  Settings for the Diabolo application are in the board's Makefile
 *
 * @{
 */
#define DIABOLO_PIN_RX			(pin,2)			/**<> */
#define DIABOLO_PIN_TX			(pin,2)			/**<> */
#define DIABOLO_SYNC			51			/**<> */

/**
 * @}
 *
 * @name Board pins
 *
 * The pin at which the LED is connected. The target device name indicates its
 * package, then pin numbers can be used as well as pin names.
 *
 * @{
 */
#define PIN_LED				(pin,7)		/* OC1A */	/**<> */
//#define PIN_LED			  (pin,5)	/* OC0A */	/**<> */

#define PIN_ANALOG_INPUT		(pin,13)	/* ADC0 */	/**<> */

/*  Pins for hw_swuart1
 */
#define PIN_TX2				(pin,8)			/**<> */
#define PIN_RX2				(pin,9)			/**<> */

/** @} */
/** @} */

/*  Include HWA definitions
 */
#include <hwa/attiny84a_pu.h>
