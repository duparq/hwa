
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @page boards
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
 * @include attiny84.h
 * <br>
 */

/*  Device configuration
 */
#define HW_DEVICE_CLK_SRC               rc_8MHz
#define HW_DEVICE_CLK_PSC               1
#define HW_DEVICE_EXTERNAL_RESET        enabled
#define HW_DEVICE_SELF_PROGRAMMING      enabled
#define HW_DEVICE_DEBUG_WIRE            disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON    no
#define HW_DEVICE_CLOCK_OUTPUT          disabled
#define HW_DEVICE_BROWNOUT_DETECTION    2500_2900mV

/*  Settings for the Diabolo bootloader
 *    BPS and RESET_SIGNAL are only used by `make` to provide
 *    settings to the Diabolo application on the host.
 */
#define DIABOLO_PIN_RX                  hw_pin_2
#define DIABOLO_PIN_TX                  hw_pin_2
#define DIABOLO_BPS                     115200
#define DIABOLO_RESET_SIGNAL            DTR

/*  The pin at which the LED is connected. The target device name indicates its
 *  package, then pin numbers can be used as well as pin names.
 */
#define PIN_LED                         hw_pin_7

/*  Include HWA definitions
 */
#include <hwa/attiny84a_pu.h>
