
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *  Blink a LED with a software loop
 */

/*  Include the board definition (includes hwa.h)
 */
#include <boards/attiny84.h>


/*  The pin at which the LED is connected (already defined for Arduino
 *  boards). The target also defines the package of the device, then pin
 *  numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED               hw_pin_7
#endif


/*  The blinking period
 */
#define PERIOD                  0.5


int main ( )
{
  /*  Configure the LED pin
   */
  hw_config( PIN_LED, direction, output );

  for(;;) {
    hw_toggle( PIN_LED );
    hw_delay_cycles( PERIOD/2 * hw_syshz );  // `hw_syshz` is the CPU clock frequency
  }
}
