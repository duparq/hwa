
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *  @par Blink a LED using a software loop
 *
 *  This program configures the LED pin as a digital output, then in an infinite
 *  loop it toggles the LED state and waits for half the period to be elapsed.
 *
 *  Symbols:
 *
 *  * `BOARD_H` is the name of the target board header file. It can be defined
 *  at compile time via the command line. For example, `make BOARD=nanodccduino`
 *  will define `BOARD_H` as `<boards/nanodccduino.h>`. See @ref atmelavr_boards
 *  for the board definitions provided with HWA.
 *
 *  * `PIN_LED` is the definition of the pin at which a LED is connected. It is
 *  defined in the target board header file.
 *
 *  * `PERIOD` is the blinking period.
 *
 *  * `hw_syshz` is the CPU frequency computed by HWA from the device settings.
 *
 * @par main.c
 */


/*  Set a default target board
 */
#if !defined BOARD_H
#  define BOARD_H               <boards/attiny84.h>
#endif

#include BOARD_H


#define PERIOD                  0.5


int main ( )
{
  hw_config( PIN_LED, direction, output );

  for(;;) {
    hw_toggle( PIN_LED );
    hw_delay_cycles( PERIOD/2 * hw_syshz );
  }
}
