
/*	Blink a LED using a counter compare-match flag
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */


/*	Target				Results (pin_7, 64, output0, 0.5 s)
 *					   hw_counter0		hw_counter1
 *					   bytes:CRC		bytes:CRC
 */
#include "targets/attiny84.h"		// 116:0x5653		118:0x2CBB
//#include "targets/attiny85.h"		// 112:0xE1C9
//#include "targets/nanodccduino.h"	// 188:0x929D		204:0x6670
#include <hwa.h>


/*  Define the pin at which the LED is connected (already done for Arduino
 *  targets). The the package of the device is defined in the target
 *  definitions, then pin numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED		hw_pin_7
#endif


/*  The counter
 */
#define COUNTER			hw_counter0
#define CLKDIV			64
#define COMPARE			compare0
#define PERIOD			0.5


int main ( )
{
  /*  Create a HWA context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Configure the counter to count from 0 to its max and loop
   */
  hwa_config( COUNTER,
	      clock,     HW_G2(syshz_div, CLKDIV),
	      countmode, loop_up,
	      bottom,    0,
	      top,       max,
	      );

  /* hwa_config( hw_sub(COUNTER,COMPARE), */
  /* 	      update,    at_bottom, */
  /* 	      output,    set_at_bottom_clear_on_match ); */

  /*  Configure the compare unit to match when 0.001 s has elapsed
   */
  hwa_write( hw_sub(COUNTER,COMPARE), 0.001 * hw_syshz / CLKDIV );

  /*  Write all this into the hardware
   */
  hwa_commit();

  static uint8_t n ;
  for(;;) {
    /*
     *  When a compare-match occurs, clear the counter, clear the flag and count
     *  the elapsed millisecond
     */
    if ( hw_stat(COUNTER).COMPARE ) {
      hw_clear( COUNTER );
      hw_clear_irq( COUNTER, COMPARE );
      n++ ;
      if ( n >= (uint8_t)(PERIOD/0.001/2.0+0.5) ) {
	/*
	 *  Toggle the LED when a half period has elapsed
	 */
	n = 0 ;
	hw_toggle( PIN_LED );
      }
    }
  }
}
