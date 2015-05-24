
/*  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *      Blink a LED using the watchdog flag
 */

/*      Target
 */
#include <targets/attiny84.h>
#include <hwa.h>


/*  The pin at which the LED is connected (already done for Arduino
 *  targets). The target also defines the package of the device, then pin
 *  numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED               hw_pin_7
#endif


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
    if ( hw_read_irqf(hw_wdog0) ) {
      hw_clear_irqf( hw_wdog0 );
      hw_toggle( PIN_LED );
    }
  }
    
  return 0 ;
}
