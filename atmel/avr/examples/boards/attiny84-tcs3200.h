
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
 * @section boards_tcs3200 Board attiny84-tcs3200
 *
 * This is a ATTINY84A-PU on a breadboard with a USB/Serial adapter, a
 * TCS3200 color detector and 3 LED. No crystal.
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
 * @par tcs3200.h
 * @include boards/attiny84-tcs3200.h
 * <br>
 */

#define BOARD_TCS3200

/*  Device configuration
 */
#define HW_DEVICE_CLK_SRC		rc_8MHz
#define HW_DEVICE_CLK_PSC		1
#define HW_DEVICE_EXTERNAL_RESET	enabled
#define HW_DEVICE_SELF_PROGRAMMING	enabled
#define HW_DEVICE_DEBUG_WIRE		disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON	no
#define HW_DEVICE_CLOCK_OUTPUT		disabled
#define HW_DEVICE_BROWNOUT_DETECTION	2500_2900mV

/*  Settings for building the Diabolo bootloader.
 *  (Settings for the host application are in the board's Makefile)
 */
#define DIABOLO_PIN_RX			HW_PIN(2)
#define DIABOLO_PIN_TX			HW_PIN(2)
#define DIABOLO_SYNC			10+1

/*  Channel selection pins
 */
#define PIN_TCS3200_S2			HW_PIN(5)
#define PIN_TCS3200_S3			HW_PIN(3)

/*  Create a `PIN_OUTS` object consisting of the 4 consecutive I/O pins
 *  PA5,PA4,PA3,PA2 (14pdip: 8..11)
 *
 *					class, id, parent, #of bits, position of lsb
 */
#define _hw_def_PIN_OUTS		_io1a, 1001, port0, 4, 2

/*  Include HWA definitions
 */
#include <hwa/attiny84a_pu.h>
