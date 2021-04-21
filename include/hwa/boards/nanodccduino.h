
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
 * @defgroup board_nanodccduino Board nanodccduino
 *
 * This is an Arduino clone board with a MEGA328P-AU microcontroller, a 16 MHz
 * crystal and a CH340 USB/Serial adapter.
 *
 * @note I've discovered that my Linux driver for CH340/CH341 is buggy and does
 * not send parity bytes. So, use the 51 synchronization sequence.
 *
 * @image html nanodccduino.png
 *
 * @par USBASP wiring
 *
 *	USBASP -> 1  MOSI  D11 <- BOARD
 *		  2  VCC   5V
 *		  4  GND   GND
 *		  5  RST   RST
 *		  7  SCK   D13
 *		  9  MISO  D12
 *
 * @par nanodccduino.h
 * @include nanodccduino.h
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
#define DIABOLO_PIN_RX			(pin,rxd)
#define DIABOLO_PIN_TX			(pin,txd)
#define DIABOLO_SYNC			51

/*  Board pins
 */
#define ARDUINO
#define NANODCCDUINO

#define PIN_RX0				(portd,0)
#define PIN_TX1				(portd,1)
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

#define PIN_A5				(portc,5)	// SCL
#define PIN_A4				(portc,4)	// SDA

#define PIN_SS				(portb,2)
#define PIN_MOSI			(portb,3)
#define PIN_MISO			(portb,4)
#define PIN_SCK				(portb,5)

#define PIN_ANALOG_INPUT		(pin,adc0)

#define PIN_LED				(portb,5)


/*  Pins for swuart1
 */
#define PIN_TX2				PIN_D8
#define PIN_RX2				PIN_D9

/*  Include HWA MCU definitions
 */
#include <hwa/atmega328p_au.h>
