
/*	Blink a LED with a software loop
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */


/*	Target
 */
#include <targets/attiny84.h>		// 80 bytes
//#include "targets/attiny85.h"		// 76 /8192
//#include <targets/nanodccduino.h>	// 156
#include <hwa.h>


/*  The pin at which the LED is connected (already done for Arduino
 *  targets). The target also defines the package of the device, then pin
 *  numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED		hw_pin_7
#endif


/*  The blinking period
 */
#define PERIOD			0.5


int main ( )
{
  /*  Configure the LED pin
   */
  hw_config( PIN_LED, direction, output );

  for(;;) {
    hw_toggle( PIN_LED );
    hw_delay_cycles( PERIOD/2 * hw_syshz );
  }
}
