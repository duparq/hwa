
/*	Blink a LED with a software loop
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */


/*	Target				Result (hw_pin_7, 0.5s)
 */
#include "targets/attiny84.h"		// 80:0xE80B
//#include "targets/attiny85.h"		// 76 /8192 application bytes, CRC=0x3950
//#include "targets/nanodccduino.h"	// 156 /32768 application bytes, CRC=0xE183
#include <hwa.h>


/*  Define the pin at which the LED is connected (already done for Arduino
 *  targets). The target definitions also define the package of the device, then
 *  pin numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED		hw_pin_7
#endif


/*  Define the blinking period
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


/* hwa_config( pin_pb2, direction, output ); */

/* hwa_write( foo, foo ); */

/* hwa_write( core0, foo ); */

/* _hwa_write_creg( p, _wdoga, wdrf, 0 ); */

/* _hw_creg(_wdoga, wdrf); */
