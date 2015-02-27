
/*	Blink a LED using a counter overflow flag
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */


/*	Target				Results (pin_7, 64, loop_up, 0.5 s)
 *					   hw_counter0		hw_counter1
 *					   bytes:CRC		bytes:CRC
 */
#include "targets/attiny84.h"		// 118:0xA0E2		118:0xA058
//#include "targets/attiny85.h"		// 114:0xD1D4		-
//#include "targets/nanodccduino.h"	// 190:0xB4CB		
#include <hwa.h>


/*  Define the pin at which the LED is connected (already done for Arduino
 *  targets). The target definitions also define the package of the device, then
 *  pin numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED		hw_pin_7
#endif


/*  The counter
 */
#define COUNTER			hw_counter1
#define CLKDIV			64
#define COUNTMODE		loop_updown
#define PERIOD			0.5


int main ( )
{
  /*  Load the HWA context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Configure the counter to overflow every 0.001 s.
   *  The compare unit `output0` (OCxA) is used to store the top value.
   *  Unless otherwise stated, the overflow will occur at top in `loop_up`
   *  counting mode, at bottom in `loop_updown` counting mode.
   */
  hwa_config( COUNTER,
	      clock,     HW_G2(syshz_div, CLKDIV),
	      countmode, COUNTMODE,
	      bottom,    0,
	      top,       output0
	      );
  if ( hw_streq(HW_QUOTE(COUNTMODE),"loop_updown") )
    hwa_write( hw_sub(COUNTER, output0), 0.001 * hw_syshz / CLKDIV / 2 );
  else
    hwa_write( hw_sub(COUNTER, output0), 0.001 * hw_syshz / CLKDIV );

  /*  Write all this into the hardware
   */
  hwa_commit();

  static uint8_t n ;
  for(;;) {
    if ( hw_stat(COUNTER).overflow ) {
      hw_clear_irq( COUNTER, overflow );
      n++ ;
      if ( n >= (uint8_t)(PERIOD / 2.0 / 0.001) ) {
	n = 0 ;
	hw_toggle( PIN_LED );
      }
    }
  }
}
