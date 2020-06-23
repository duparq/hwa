
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * Fade a LED connected to a counter compare output (method 2).
 *
 * Changes versus method 1:
 *
 *   * define PWM as `hw_ocXY` and use `(PWM,counter)` to retrieve the name of
 *     the counter;
 *
 *   * use a HWA context in the ISR and the couple `hwa_nocommit()` /
 *     `hwa_commit()` to write the changes to the hardware;
 *
 *   * use a seperate function to store the hardware configuration
 *     into a HWA context.
 */

#include BOARD_H


/*  The counter
 */
#define PWM			(counter0,compare0)
#define CLKDIV			64
#define COUNTMODE		up_loop
#define TOP			0xFF

/*  Compare strings
 */
#define STRCMP(s1,s2)		__builtin_strcmp(s1,s2)


/*  Store the hardware configuration into a HWA context
 */
HW_INLINE void setup_hwa_context ( hwa_t *hwa )
{
  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa( configure,  core0,
       sleep,	   enabled,
       sleep_mode, idle );

  /*  Configure the counter to count between 0 and 0xFF
   */
  hwa( configure, (PWM,counter),
       clock,	  ioclk / CLKDIV,
       direction, COUNTMODE,
       bottom,	  0,
       top,	  TOP );

  if ( !STRCMP(HW_Q(COUNTMODE),"updown_loop") )
    hwa( configure, PWM, output, clear_after_match_up_set_after_match_down );
  else /* up_loop */
    hwa( configure, PWM, output, set_at_bottom_clear_after_match );

  /*  Enable overflow IRQ
   */
  hwa( enable, (PWM,counter,irq,overflow) );
}


/*  Service the counter overflow IRQ: compute the next value of the compare unit
 *
 *    Phase 0: increase duty cycle from 0 to 255
 *    Phase 1: decrease duty cycle from 255 to 0 (use ~duty)
 *    Phase 2: off
 *    Phase 3: off
 */
HW_ISR( (PWM,counter,irq,overflow) )
{
  static uint8_t	duty ;
  static uint8_t	phase ;

  if ( phase == 0 )
    hw( write, PWM, duty );
  else if ( phase == 1 )
    hw( write, PWM, ~duty );

  duty++ ;

  if ( duty==0 ) {
    phase = (phase + 1) & 3 ;

    /*	In 'up_loop' counting mode, we must disconnect/reconnect the output of
     *	the compare unit as it can not provide pulses of less than 1 cycle.
     */
    if ( !STRCMP(HW_Q(COUNTMODE),"up_loop") ) {

      /*  Start from the hardawre configuration used at initialization
       */
      hwa( begin, reset );
      setup_hwa_context( hwa );

      if ( phase == 2 ) {
	/*
	 *  Change the compare output config from 'set_at_bottom_clear_after_match'
	 *  to 'disconnected'
	 */
	hwa( configure, PWM, output, set_at_bottom_clear_after_match );
	hwa( nocommit );
	hwa( configure, PWM, output, disconnected );
	hwa( commit );
      }
      else if ( phase == 0 ) {
	/*
	 *  Change the compare output config from 'disconnected' to
	 *  'set_at_bottom_clear_after_match'
	 */
	hwa( configure, PWM, output, disconnected );
	hwa( nocommit );
	hwa( configure, PWM, output, set_at_bottom_clear_after_match );
	hwa( commit );
      }
    }
  }
}


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa( begin, reset );

  /*  Store the hardware configuration into the HWA context
   */
  setup_hwa_context( hwa );

  /*  Write this configuration into the hardware
   */
  hwa( commit );

  hw( enable, interrupts );

  for(;;)
    hw( wait, irq );
}
