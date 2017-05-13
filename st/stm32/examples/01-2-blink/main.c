
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
 * To try the program, run `make openocd` in one terminal, and `make gdb` in
 * another one. In `gdb` type `reload` to load the program (it executes from
 * RAM) and `continue` to run it. The LED should blink.
 *
 * Symbols:
 *
 * * `BOARD_H` is the name of the target board definition file. It can be
 *   specified at compile time via the command line. If not, the Makefile will
 *   set it to a default value. For example, `make BOARD=mini-stm32-v3.0` will
 *   lead to `BOARD_H` defined as `<boards/mini-stm32-v3.0.h>`. See @ref
 *   stm32_boards for the list of board definition files provided.
 *
 * * `PIN_LED1` is the name of the I/O pin at which LED1 is connected. It is
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
  hwa_begin_from_reset();
  
  hwa( power, HW_RELATIVE(PIN_LED1,port), on );

  hwa( configure, PIN_LED1,
       mode,	  digital,
       direction, output,
       frequency, 50MHz );

  hwa_commit();

  for(;;) {
    hwa( write, PIN_LED1, 1 );
    hwa_commit();

    hw_waste_cycles( PERIOD/2 * HW_DEVICE_HSIHZ );

    hwa( write, PIN_LED1, 0 );
    hwa_commit();

    hw_waste_cycles( PERIOD/2 * HW_DEVICE_HSIHZ );
  }
}
