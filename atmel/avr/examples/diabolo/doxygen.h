
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @addtogroup atmelavr_diabolo
 *
 * Diabolo is a bootloader developed using HWA for assembler programming for the
 * device side, and Python for the host application.
 * 
 *  * it is fast, as the host application uses a __cache mecanism__ to determine
 *    the pages that have to be programmed;
 * 
 *  * it is not too big: ~ __640 bytes__;
 * 
 *  * it is very convenient since it can use __any pin__ for __1 or 2-wire serial
 *    communication__ (__automatically detected__ by the host side application)
 *    with __automatic detection of baudrate__ so that no baudrate has to be
 *    hardcoded in the project and __no crystal__ is required on the target;
 * 
 *  * validity of application code and communication messages are checked with a
 *    __16-bit CRC__.
 * 
 * The source code of Diabolo is in the `atmel/avr/examples/diabolo/` directory.
 * 
 * 
 * Installing Diabolo on an AVR
 * ----------------------------
 * 
 * In order to install Diabolo on the microcontroller, you must edit the file
 * `device/diabolo.sx` to either include a preconfigured target definition or
 * define the following symbols:
 * 
 * @code
 * #define DIABOLO_PIN_RX                  (pin,2)
 * #define DIABOLO_PIN_TX                  (pin,2)
 * 
 * #define HW_DEVICE_SELF_PROGRAMMING      enabled
 * @endcode
 * 
 * Optionnally, you can also define additionnal fuses:
 * 
 * @code
 * #define HW_DEVICE_CLK_SRC               rc_8MHz
 * #define HW_DEVICE_CLK_PSC               1
 * #define HW_DEVICE_EXTERNAL_RESET        enabled
 * #define HW_DEVICE_DEBUG_WIRE            disabled
 * #define HW_DEVICE_WATCHDOG_ALWAYS_ON    no
 * #define HW_DEVICE_CLOCK_OUTPUT          disabled
 * #define HW_DEVICE_BROWNOUT_DETECTION    2500_2900mV
 * @endcode
 * 
 * Then, you must include the HWA header that suits your target:
 * 
 * @code
 * #include <hwa/atmega328p_au.h>
 * @endcode
 * 
 * 
 * If you have `avrdude` installed on your system and your ISP is `usbasp` you
 * just have to wire the target device to your programmer and that will program
 * the Flash memory and the fuse bytes:
 *
 *     make install
 * 
 * Otherwise, you'll have to edit the `device/Makefile` to suit your programming
 * tools.
 * 
 * 
 * Using the Diabolo host application
 * ----------------------------------
 * 
 * Once you have installed Diabolo on your microcontroller, you can check that
 * everything works with the `software/diabolo.py` application.
 * 
 * Assuming you have only one USB-Serial adapter, that should display the status of
 * your device:
 * 
 *     python diabolo.py
 * 
 * and that should dump the program memory entirely:
 * 
 *     python diabolo.py --read-flash --full --hexdump
 * 
 * Type `python diabolo.py --help` for a description of the command line arguments.
 * 
 * 
 * Known problems
 * --------------
 * 
 * Diabolo launches the application by jumping to the address the immediately
 * follows the interrupt vectors. That fails if the application uses PROGMEM data
 * and GCC stores it at that address.
 */
