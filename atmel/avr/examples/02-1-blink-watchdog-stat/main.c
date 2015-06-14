
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * @par Blink a LED using the watchdog flag
 *
 * This program configures the LED pin as a digital output and the watchdog to
 * trigger an IRQ periodically. Then, in an infinite loop, when the watchdog IRQ
 * flag is set, it clears it and toggles the LED state.
 *
 * A HWA context is used to gather the configuration and write it into the
 * hardware registers at once with the most efficient code.
 *
 * Symbols:
 *
 * * `BOARD_H` is the name of the target board header file. It can be defined at
 * compile time via the command line. For example, `make BOARD=nanodccduino`
 * will define `BOARD_H` as `<boards/nanodccduino.h>`. See @ref atmelavr_boards
 * for the board definitions provided with HWA.
 *
 * * `PIN_LED` is the definition of the pin at which a LED is connected. It is
 * defined in the target board header file.
 *
 * * `TIMEOUT` is the watchdog timeout period.
 */


/*  Set a default target board
 */
#if !defined BOARD_H
#  define BOARD_H               <boards/attiny84.h>
#endif

#include BOARD_H


/*  Watchdog timeout
 */
#define TIMEOUT                 250ms


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Configure the watchdog to trigger an IRQ periodically
   */
  hwa_config( hw_wdog0,
              timeout,          TIMEOUT,
              action,           irq );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  for(;;) {
    /*
     *  As soon as the watchdog IRQ flag is set, clear
     *  it and toggle the LED.
     */
    if ( hw_stat_irqf(hw_wdog0) ) {
      hw_clear_irqf( hw_wdog0 );
      hw_toggle( PIN_LED );
    }
  }
    
  return 0 ;
}
