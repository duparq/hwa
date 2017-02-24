
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
 * hardware registers at once with the most efficient code possible.
 */

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
  hwa( configure, PIN_LED, direction, output );

  /*  Configure the watchdog to trigger an IRQ periodically
   */
  hwa( configure, wdog0,
       timeout,   TIMEOUT,
       action,    irq       );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  for(;;) {
    /*
     *  As soon as the watchdog IRQ flag is set, clear
     *  it and toggle the LED.
     */
    if ( hw( read, HW_IRQF(wdog0) ) ) {
      hw( clear, HW_IRQF(wdog0) );
      hw( toggle, PIN_LED );
    }
  }
    
  return 0 ;
}
