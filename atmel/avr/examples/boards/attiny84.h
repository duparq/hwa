
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

/**
 * @page atmelavr_boards
 *
 * @section boards_attiny84 Attiny84
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
 *                           Vcc o   U   o Gnd
 *                XTAL1 CLKI PB0 o       o PA0 ADC0 AREF
 *                     XTAL2 PB1 o       o PA1 ADC1 AIN0
 *                     RESET PB3 o       o PA2 ADC2 AIN1
 *           INT0 OC0A CKOUT PB2 o       o PA3 ADC3 T0
 *             ICP OC0B ADC7 PA7 o       o PA4 ADC4 USCK SCL T1
 *     OC1A SDA MOSI DI ADC6 PA6 o       o PA5 ADC5 DO MISO OC1B
 *
 *
 * @par Serial adapter wiring
 *
 *     TINY84 ->  2 : RXD <- Serial Adapter
 *                  : TXD
 *                4 : DTR
 *               14 : GND
 *                1 : VCC
 *
 * @par USBASP wiring
 *
 *      USBASP -> 1  MOSI  7  <- TINY84
 *                2  VCC   1
 *                4  GND   14
 *                5  RST   4
 *                7  SCK   9
 *                9  MISO  8
 *
 * @par attiny84.h
 * @include boards/attiny84.h
 * <br>
 */

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

/*  Settings for the Diabolo bootloader
 *    BPS and RESET_SIGNAL are only used by `make` to provide
 *    settings to the Diabolo application on the host.
 */
#define DIABOLO_PIN_RX			hw_pin_2
#define DIABOLO_PIN_TX			hw_pin_2
#define DIABOLO_BPS			115200
#define DIABOLO_RESET_SIGNAL		DTR
#define DIABOLO_SYNC			10+1

/*  The pin at which the LED is connected. The target device name indicates its
 *  package, then pin numbers can be used as well as pin names.
 */
#define PIN_LED				hw_pin_7	// OC1A
//#define PIN_LED			  hw_pin_5	// OC0A

/*  Analog input pin
 */
#define PIN_ANALOG_INPUT		hw_pin_13	// ADC0

/*  Pins for hw_swuart1
 */
#define PIN_TX2				hw_pin_8
#define PIN_RX2				hw_pin_9

/*  Include HWA definitions
 */
#include <hwa/attiny84a_pu.h>
