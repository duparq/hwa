
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *  Blink a LED using a counter overflow flag
 */

/*  Target
 */
#include BOARD_H


/*  The counter
 */
#define COUNTER			counter0
#define CLKDIV			64
#define COUNTMODE		up_loop
#define PERIOD			0.5

/*  Compare strings
 */
#define STRCMP(s1,s2)		__builtin_strcmp(s1,s2)


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa( configure, PIN_LED, direction, output );

  /*  Configure the counter to overflow every 0.001 s.
   *  The compare unit `output0` (OCxA) is used to store the top value.
   *  Unless otherwise stated, the overflow will occur at top in `up_loop`
   *  counting mode, at bottom in `updown_loop` counting mode.
   */
  hwa( configure, COUNTER,
       clock,	  ioclk / CLKDIV,
       countmode, COUNTMODE,
       bottom,	  0,
       top,	  compare0 );
  
  if ( !STRCMP(HW_QUOTE(COUNTMODE),"updown_loop") )
    hwa( write, HW_RELATIVE(COUNTER, compare0), 0.5 + 0.001 * HW_SYSHZ / CLKDIV / 2 );
  else
    hwa( write, HW_RELATIVE(COUNTER, compare0), 0.5 + 0.001 * HW_SYSHZ / CLKDIV );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  static uint8_t n ;
  for(;;) {
    if ( hw( read, HW_IRQFLAG(COUNTER, overflow) ) ) {
      hw( clear, HW_IRQFLAG(COUNTER, overflow) );
      n++ ;
      if ( n >= (uint8_t)(PERIOD / 2.0 / 0.001) ) {
	n = 0 ;
	hw( toggle, PIN_LED );
      }
    }
  }
}
