
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
 * @par Serial adapter wiring
 *
 *     BOARD -> RXD : RXD <- Serial Adapter
 *                  : TXD
 *              RST : DTR
 *              GND : GND
 *              VCC : VCC
 *
 * @par USBASP wiring
 *
 *      USBASP -> 1  MOSI  11  <- BOARD
 *                2  VCC   VCC
 *                4  GND   GND
 *                5  RST   RST
 *                7  SCK   13
 *                9  MISO  12
 *
 * @par  arduino_pro_mini.h
 * @include arduino_pro_mini.h
 * <br>
 */

/*  These are mostly the values as the board is shipped, except the bootsection
 *  size which is 1024 with Diabolo instead of 2048 with the Arduino bootloader.
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

/*  Settings for the Diabolo bootloader
 *    BPS and RESET_SIGNAL are only used by `make` to provide
 *    settings to the Diabolo application on the host.
 */
#define DIABOLO_PIN_RX                  hw_pin_rxd
#define DIABOLO_PIN_TX                  hw_pin_rxd
#define DIABOLO_BPS                     230400
#define DIABOLO_RESET_SIGNAL            DTR

/*  Board pins
 */
#define ARDUINO

#define PIN_LED                         hw_pin_pb5

/*  Include HWA definitions
 */
#include <hwa/atmega328p_au.h>
