
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @page boards
 *
 * @section boards_arduino_pro_mini Arduino Pro Mini
 *
 * This is an Arduino clone board with a MEGA328P-AU microcontroller and a 16
 * MHz crystal.
 *
 * The serial communication uses 1 wire for RX/TX. The board RX pin is connected
 * to the RXD pin of the serial adapter and a 1k resistor is connected between
 * the RXD and TXD pins (it could be replaced by a diode, Schottky preferably).
 *
 *     BOARD -> RXD : RXD <- Serial Adapter
 *                  : TXD
 *              RST : DTR
 *              GND : GND
 *              VCC : VCC
 *
 * To install Diabolo with avrdude/usbasp:
 *
 *      USBASP -> 1  MOSI  11  <- BOARD
 *                2  VCC   VCC
 *                4  GND   GND
 *                5  RST   RST
 *                7  SCK   13
 *                9  MISO  12
 *
 * @include arduino_pro_mini.h
 */

/*  These are mostly the values as the board is shipped, except
 *  the bootsection size which is 1024 instead of 2048.
 */
#define HW_DEVICE_BOOT                  bootloader
#define HW_DEVICE_BOOTSECTION_SIZE      1024

#define HW_DEVICE_CLK_SRC               low_power_xosc
#define HW_DEVICE_CLK_SRC_HZ            16000000
#define HW_DEVICE_CLK_PSC               1
#define HW_DEVICE_STARTUP_DELAYS        16KCK_14CK_64ms
#define HW_DEVICE_BROWNOUT_DETECTION    4100_4500mV
#define HW_DEVICE_SELF_PROGRAMMING      enabled

#define HW_DEVICE_EXTERNAL_RESET        enabled
#define HW_DEVICE_DEBUG_WIRE            disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON    no
#define HW_DEVICE_CLOCK_OUTPUT          disabled

/*  Settings for Diabolo
 */
#define DIABOLO_PIN_RX                  hw_pin_rxd
#define DIABOLO_PIN_TX                  hw_pin_rxd
#define DIABOLO_BPS                     115200
#define DIABOLO_RESET_SIGNAL            DTR

#define PIN_LED                         hw_pin_pb5

/*  Include HWA header
 */
#include <hwa/atmega328p_au.h>
