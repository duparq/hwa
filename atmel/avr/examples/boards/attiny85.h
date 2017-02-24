
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
 * @section boards_attiny85 Board attiny85
 *
 * This is a single ATTINY85-20PU without crystal on a breadboard with a
 * USB/Serial adapter for 1-wire communication, a LED connected at pin #5
 * (PB0/OC0A), one analog input pin.
 *
 * @par Pin Configuration
 *
 *                RESET ADC0 PB5 o   U   o Vcc
 *     XTAL1 CLKI /OC1B ADC3 PB3 o       o PB2 SCK USCK SCL ADC1 T0 INT0
 *      XTAL2 CLKO OC1B ADC2 PB4 o       o PB1 MISO DO AIN1 OC0B OC1A
 *                           Gnd o       o PB0 MOSI DI SDA AIN0 OC0A /OC1A AREF
 *
 * @par Serial adapter wiring
 *
 * The serial communication uses 1 wire for RX/TX, AVR pin #2 connected to the
 * RXD pin of the serial adapter, and a 1k resistor is connected between the RXD
 * and TXD pins (it could be replaced by a diode, Schottky preferably).
 *
 *     TINY85 ->  2 : RXD <- Serial Adapter
 *                  : TXD
 *                1 : DTR
 *                4 : GND
 *                8 : VCC
 *
 * To install Diabolo with avrdude/usbasp:
 *
 *      USBASP -> 1  MOSI  5 <- TINY85
 *                2  VCC   8
 *                4  GND   4
 *                5  RST   1
 *                7  SCK   7
 *                9  MISO  6
 *
 * @par attiny85.h
 * @include boards/attiny85.h
 * <br>
 */

/*  Device configuration
 */
//#define HW_DEVICE_CLK_SRC               rc_pll_16MHz
#define HW_DEVICE_CLK_SRC               rc_8MHz
#define HW_DEVICE_CLK_PSC               1
#define HW_DEVICE_EXTERNAL_RESET        enabled
#define HW_DEVICE_SELF_PROGRAMMING      enabled
#define HW_DEVICE_DEBUG_WIRE            disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON    no
#define HW_DEVICE_CLOCK_OUTPUT          disabled
#define HW_DEVICE_BROWNOUT_DETECTION    4100_4500mV
#define HW_DEVICE_STARTUP_DELAYS	6CK_14CK_64ms

/*  Settings for building the Diabolo bootloader
 *  Settings for the Diabolo application are in the board's Makefile
 */
#define DIABOLO_PIN_RX                  HW_PIN(2)
#define DIABOLO_PIN_TX                  HW_PIN(2)
#define DIABOLO_SYNC                    5+1

/*  The pin at which the LED is connected. The target device name indicates its
 *  package, then pins named by their number can be used.
 */
#define PIN_LED                         HW_PIN(5)	// OC0A

/*  Analog input pin
 */
#define PIN_ANALOG_INPUT		HW_PIN(7)	// ADC1

/*  HWA
 */
#include <hwa/attiny85_20pu.h>
