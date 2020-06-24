
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * @par Blink a LED using a software loop
 *
 * This program configures the LED pin as a digital output, then in an infinite
 * loop it toggles the LED state and waits for half the period to be elapsed.
 *
 * Symbols:
 *
 * * `BOARD_H` is the name of the target board definition file. It can be
 *   specified at compile time via the command line. If not, the Makefile will
 *   set it to `attiny84` by default. For example, `make BOARD=nanodccduino`
 *   will lead to `BOARD_H` defined as `<boards/nanodccduino.h>`. See @ref
 *   atmelavr_boards for the list of board definition files provided.
 *
 * * `PIN_LED` is the name of the I/O pin at which a LED is connected. It
 *   is defined in the target board header file.
 *
 * * `PERIOD` is the blinking period.
 *
 * * `HW_SYSHZ` is the CPU frequency, computed by HWA from the device
 *    configuration fuses.
 *
 * @par main.c
 */

#include BOARD_H

#define PERIOD			0.5


int main ( )
{
  hw( configure, PIN_LED, mode, digital_output );
  
  for(;;) {
    hw( toggle, PIN_LED );
    hw_waste_cycles( PERIOD/2 * HW_SYSHZ );
  }
}
