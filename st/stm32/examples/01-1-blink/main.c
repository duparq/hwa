
/*  This file is part of the HWA project.
 *  Copyright (c) 2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * @par Blink a LED using a software loop
 *
 * This program enables the LED port, configures the LED pin as a digital
 * output, then in an infinite loop it toggles the LED state and waits for half
 * the period to be elapsed.
 *
 * `make run` to try the program. The LED should blink.
 *
 * Symbols:
 *
 * * `BOARD_H` is the name of the target board definition file. It can be
 *   specified at compile time via the command line. If not, the Makefile will
 *   set it to a default value. For example, `make BOARD=mini-stm32-v3.0` will
 *   lead to `BOARD_H` defined as `<boards/mini-stm32-v3.0.h>`. See @ref
 *   stm32_boards for the list of board definition files provided.
 *
 * * `PIN_LED1` is the name of the I/O pin at which a LED1 is connected. It is
 *   defined in the target board header file.
 *
 * * `PERIOD` is the blinking period.
 *
 * * `HW_DEVICE_HSIHZ` is the CPU frequency.
 *
 * @par main.c
 */
#include BOARD_H

#define PERIOD		0.5


int main ( )
{
  hw( power, (LED,port), on );

  hw( configure, LED,
      mode,	 digital_output,
      frequency, lowest );

  for(;;) {
    hw( toggle, LED );
    hw_waste_cycles( PERIOD/2 * HW_DEVICE_HSIHZ );
  }
}
