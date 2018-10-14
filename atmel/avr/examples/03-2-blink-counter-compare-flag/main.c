
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *  Blink a LED using a counter compare-match flag
 */


/*  Set a default target board
 */
#include BOARD_H


/*  The counter
 */
#define COUNTER			counter0
#define CLKDIV			64
#define COMPARE			compare0
#define PERIOD			0.5

#define IRQF			HW_IRQFLAG(COUNTER,COMPARE)	// IRQ flag


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa( configure, PIN_LED, mode, digital_output );

  /*  Configure the counter to count from 0 to its max and loop
   */
  hwa( configure, COUNTER,
       clock,	  ioclk / CLKDIV,
       countmode, up_loop,
       bottom,	  0,
       top,	  max );

  /*  Configure the compare unit to match when 0.001 s has elapsed
   */
  hwa( write, (COUNTER,COMPARE), 0.001 * HW_SYSHZ / CLKDIV );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  static uint8_t n ;
  for(;;) {
    /*
     *	When a compare-match occurs, clear the counter, clear the flag and count
     *	the elapsed millisecond
     */
    if ( hw( read, IRQF ) ) {
      hw( write, COUNTER, 0 );
      hw( clear, IRQF );
      n++ ;
      if ( n >= (uint8_t)(0.5 + 1.0*PERIOD/0.001/2.0+0.5) ) {
	/*
	 *  Toggle the LED when a half period has elapsed
	 */
	n = 0 ;
	hw( toggle, PIN_LED );
      }
    }
  }
}
