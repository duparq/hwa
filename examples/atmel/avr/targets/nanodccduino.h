
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @page targets
 * @section targets_nanodccduino nanodccduino.h
 * This is an Arduino board
 *
 * These are mostly the values as the board was shipped, except the
 * bootsection size which is now 1024 for Diabolo instead of 2048.
 *
 *      USBASP -> 1  MOSI  D11 <- BOARD
 *                2  VCC   5V
 *                4  GND   GND
 *                5  RST   RST
 *                7  SCK   D13
 *                9  MISO  D12
 *
 * @include nanodccduino.h
 */
#define HW_DEVICE                       atmega328p
#define HW_DEVICE_PACKAGE               32mlf
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

/*      Settings for Diabolo
 */
#define DIABOLO_PIN_RX                  hw_pin_rxd
#define DIABOLO_PIN_TX                  hw_pin_txd
#define DIABOLO_BPS                     230400
#define DIABOLO_RESET_SIGNAL            DTR

#define PIN_LED                         hw_pin_pb5
