
/*	Blink a LED using a counter compare interrupt
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */


/*	Target				Results (pin_7, 64, loop_up, compare0, 0.5 s)
 *					   hw_counter0		hw_counter1
 *					   bytes:CRC		bytes:CRC
 */
#include "targets/attiny84.h"		// 144:0x4D5C		148:0x3B2D
//#include "targets/attiny85.h"		// 140:0x2963		-
//#include "targets/nanodccduino.h"	// 222:0x8316		238:0xF8A3
#include <hwa.h>


/*  Define the pin at which the LED is connected (already done for Arduino
 *  targets). The target definitions also define the package of the device, then
 *  pin numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED		pin_7
#endif


/*  The counter
 */
#define COUNTER			counter0
#define CLKDIV			64
#define COUNTMODE		loop_up
#define COMPARE			compare0
#define PERIOD			0.5


/*  Service the compare-match IRQ
 */
HW_ISR( COUNTER, COMPARE )
{
  hw_clear( COUNTER );

  static uint8_t n ;
  n++ ;
  if ( n >= (uint8_t)(PERIOD / 2.0 / 0.001) ) {
    n = 0 ;
    hw_toggle( PIN_LED );
  }
}


int main ( )
{
  /*  Load the HWA context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa_config( core0,
  	      sleep,      enabled,
  	      sleep_mode, idle );

  /*  Configure the compare unit to match every 0.001 s.
   */
  hwa_config( COUNTER,
	      clock,     HW_G2(syshz_div, CLKDIV),
	      countmode, COUNTMODE,
	      bottom,    0,
	      top,       max
	      );
  if ( hw_streq(HW_QUOTE(COUNTMODE),"loop_updown") )
    hwa_write( hw_sub(COUNTER, COMPARE), 0.001 * hw_syshz / CLKDIV / 2 );
  else /* loop_up */
    hwa_write( hw_sub(COUNTER, COMPARE), 0.001 * hw_syshz / CLKDIV );

  /*  Enable compare IRQ
   */
  hwa_turn_irq( COUNTER, COMPARE, on );

  /*  Write all this into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep();
}
