
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
 * @defgroup board_pro_mini Board pro-mini
 * @{
 *
 * @image html pro-mini.jpeg
 *
 * This is an Arduino clone board with a MEGA328P-AU microcontroller and a 16
 * MHz crystal.
 *
 * The serial communication uses 1 wire for RX/TX. The board RX pin is connected
 * to the RXD pin of the serial adapter and a 1k resistor is connected between
 * the RXD and TXD pins. Alternately, RX can be tied to VCC through a 1k
 * resistor and a Schottky diode connected between TXD (anode) and RXD
 * (cathode).
 *
 * @par Serial adapter wiring
 *
 *     BOARD -> RXD : RXD <- Serial Adapter
 *		    : TXD
 *		RST : DTR
 *		GND : GND
 *		VCC : VCC
 *
 * @par USBASP wiring
 *
 *	USBASP -> 1  MOSI  11  <- BOARD
 *		  2  VCC   VCC
 *		  4  GND   GND
 *		  5  RST   RST
 *		  7  SCK   13
 *		  9  MISO  12
 *
 * @par pro_mini.h
 * @include boards/pro-mini.h
 * <br>
 */

/*  These are mostly the values as the board is shipped, except the bootsection
 *  size which is 1024 with Diabolo instead of 2048 with the Arduino bootloader.
 */
#define HW_DEVICE_BOOT			bootloader
#define HW_DEVICE_BOOTSECTION_SIZE	1024

#define HW_DEVICE_CLK_SRC		low_power_xosc
#define HW_DEVICE_CLK_SRC_HZ		16000000
#define HW_DEVICE_CLK_PSC		1
#define HW_DEVICE_STARTUP_DELAYS	16KCK_14CK_64ms
#define HW_DEVICE_BROWNOUT_DETECTION	4100_4500mV
#define HW_DEVICE_SELF_PROGRAMMING	enabled

#define HW_DEVICE_EXTERNAL_RESET	enabled
#define HW_DEVICE_DEBUG_WIRE		disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON	no
#define HW_DEVICE_CLOCK_OUTPUT		disabled

/*  Settings for building the Diabolo bootloader
 *  Settings for the Diabolo application are in the board's Makefile
 */
#define DIABOLO_PIN_RX			pin_rxd
#define DIABOLO_PIN_TX			pin_rxd
#define DIABOLO_SYNC			51

/*  Board pins
 */
#define ARDUINO

#define PIN_D2				(portd,2)	// INT0
#define PIN_D3				(portd,3)	// OC2B INT1
#define PIN_D4				(portd,4)	//	T0
#define PIN_D5				(portd,5)	// OC0B T1
#define PIN_D6				(portd,6)	// OC0A AIN0
#define PIN_D7				(portd,7)	//	AIN1
#define PIN_D8				(portb,0)	// ICP1
#define PIN_D9				(portb,1)	// OC1A
#define PIN_D10				(portb,2)	// OC1B SS
#define PIN_D11				(portb,3)	// OC2A MOSI
#define PIN_D12				(portb,4)	//	MISO
#define PIN_D13				(portb,5)	//	SCK

#define PIN_ANALOG_INPUT		(pin,adc0)

#define PIN_LED				(portb,5)

/** @} */

/*  Include HWA definitions
 */
#include <hwa/atmega328p_au.h>
