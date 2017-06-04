
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
 * @section boards_pro_mini Board pro-mini
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
#define DIABOLO_SYNC			5+1

/*  Board pins
 */
#define ARDUINO

#define PIN_D2				pin_pd2	// INT0
#define PIN_D3				pin_pd3	// OC2B INT1
#define PIN_D4				pin_pd4	//	T0
#define PIN_D5				pin_pd5	// OC0B T1
#define PIN_D6				pin_pd6	// OC0A AIN0
#define PIN_D7				pin_pd7	//	AIN1
#define PIN_D8				pin_pb0	// ICP1
#define PIN_D9				pin_pb1	// OC1A
#define PIN_D10				pin_pb2	// OC1B
#define PIN_D11				pin_pb3	// OC2A MOSI
#define PIN_D12				pin_pb4
#define PIN_D13				pin_pb5

#define PIN_ANALOG_INPUT		HW_PIN(adc0)

#define PIN_LED				pin_pb5

/*  Include HWA definitions
 */
#include <hwa/atmega328p_au.h>
