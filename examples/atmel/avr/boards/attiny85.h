
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @page boards
 *
 * @section boards_attiny85 Attiny85
 *
 * A ATTINY85-20PU on a breadboard with a USB/Serial adapter. No crystal.
 *
 * The serial communication uses 1 wire for RX/TX. The AVR communication
 * pin is connected to the RXD pin of the serial adapter and a 1k resistor
 * is connected between the RXD and TXD pins (it could be replaced by a
 * diode, Schottky preferably).
 *
 *     TINY85 ->  2 : RXD <- Serial Adapter
 *                  : TXD
 *                1 : DTR
 *                4 : GND
 *                8 : VCC
 *
 * To install Diabolo with avrdude/usbasp:
 *
 *      USBASP -> 1  MOSI  5 <- DEVICE
 *                2  VCC   8
 *                4  GND   4
 *                5  RST   1
 *                7  SCK   7
 *                9  MISO  6
 *
 * @include attiny85.h
 */

/*      Device configuration
 */
#define HW_DEVICE                       attiny85_20pu
//#define HW_DEVICE_PACKAGE               8pdip
#define HW_DEVICE_CLK_SRC               rc_8MHz
#define HW_DEVICE_CLK_PSC               1
#define HW_DEVICE_EXTERNAL_RESET        enabled
#define HW_DEVICE_SELF_PROGRAMMING      enabled
#define HW_DEVICE_DEBUG_WIRE            disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON    no
#define HW_DEVICE_CLOCK_OUTPUT          disabled
#define HW_DEVICE_BROWNOUT_DETECTION    2500_2900mV

/*      Settings for Diabolo
 */
#define DIABOLO_PIN_RX                  hw_pin_2
#define DIABOLO_PIN_TX                  hw_pin_2
#define DIABOLO_BPS                     115200
#define DIABOLO_RESET_SIGNAL            DTR
