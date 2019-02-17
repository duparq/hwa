
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * Fade a LED connected to a counter compare output (method 1)
 *
 * __Note__ See method 2 in the next example.
 */


/*  Include the target board (and device) definitions
 */
#include BOARD_H


/*  The counter
 */
#define COUNTER			counter0
#define CLKDIV			64
#define COUNTMODE		up_loop
#define COMPARE			compare0
#define TOP			0xFF

/*  Compare strings
 */
#define STRCMP(s1,s2)		__builtin_strcmp(s1,s2)


/*  Service the counter overflow IRQ:
 *    compute the next value of the compare unit
 *
 *    Phase 0: increase duty cycle from 0 to 255
 *    Phase 1: decrease duty cycle from 255 to 0 (use ~duty)
 *    Phase 2: off
 *    Phase 3: off
 */
HW_ISR( COUNTER, overflow )
{
  static hw_uint_t(HW_BITS(COUNTER))	duty ;
  static uint8_t			phase ;

  if ( phase == 0 )
    hw( write, (COUNTER,COMPARE), duty );
  else if ( phase == 1 )
    hw( write, (COUNTER,COMPARE), ~duty );

  duty++ ;

  if ( (duty & TOP) == 0 ) {
    phase = (phase + 1) & 3 ;

    /*	In 'up_loop' counting mode, we must disconnect/reconnect the output of
     *	the compare unit as it can not provide pulses of less than 1 cycle.
     *
     *	Note that the configuration of the counter is not known here, so there
     *	is only loose checking against the arguments provided and the generated
     *	code will probably have to read the hardware to retrieve unknown bit
     *	values.
     */
    if ( !STRCMP(HW_QUOTE(COUNTMODE),"up_loop") ) {
      if ( phase == 2 )
	hw( configure, (COUNTER,COMPARE), output, disconnected );
      else if ( phase == 0 )
	hw( configure, (COUNTER,COMPARE), output, set_at_bottom_clear_after_match );
    }
  }
}


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa( begin_from_reset );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa( configure,  core0,
       sleep,	   enabled,
       sleep_mode, idle );

  /*  Configure the counter to count between 0 and TOP
   */
  hwa( configure, COUNTER,
       clock,	  ioclk / CLKDIV,
       direction, COUNTMODE,
       bottom,	  0,
       top,	  TOP );

  if ( !STRCMP(HW_QUOTE(COUNTMODE),"updown_loop") )
    hwa( configure, (COUNTER,COMPARE),
	 output, clear_after_match_up_set_after_match_down );
  else /* up_loop */
    hwa( configure, (COUNTER,COMPARE),
	 output, set_at_bottom_clear_after_match );

  /*  Enable overflow IRQ
   */
  hwa( turn, irq(COUNTER,overflow), on );

  /*  Write this configuration into the hardware
   */
  hwa( commit );

  hw( enable_interrupts );

  for(;;)
    hw( sleep_until_irq );
}
