
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * Fade a LED connected to a counter compare output (method 1)
 *
 * @note See method 2 in the next example.
 */


/*  Include the target board (and device) definitions
 */
#include BOARD_H


/*  The counter
 */
#define COUNTER			hw_counter0
#define CLKDIV			64
#define COUNTMODE		loop_up
#define COMPARE			compare0
#define TOP			0xFF


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
  static hw_uint_t(hw_bn(COUNTER))	duty ;
  static uint8_t			phase ;

  if ( phase == 0 )
    hw( write, HW_REL(COUNTER,COMPARE), duty );
  else if ( phase == 1 )
    hw( write, HW_REL(COUNTER,COMPARE), ~duty );

  duty++ ;

  if ( (duty & TOP) == 0 ) {
    phase = (phase + 1) & 3 ;

    /*	In 'loop_up' counting mode, we must disconnect/reconnect the output of
     *	the compare unit as it can not provide pulses of less than 1 cycle.
     *
     *	Note that the configuration of the counter is not known here, so there
     *	is only loose checking against the arguments provided and the generated
     *	code will probably have to read the hardware to retrieve unknown bit
     *	values.
     */
    if ( hw_streq(HW_QUOTE(COUNTMODE),"loop_up") ) {
      if ( phase == 2 )
	hw( config, HW_REL(COUNTER,COMPARE), output, disconnected );
      else if ( phase == 0 )
	hw( config, HW_REL(COUNTER,COMPARE), output, set_at_bottom_clear_on_match );
    }
  }
}


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa( config, hw_core0,
	      sleep,	  enabled,
	      sleep_mode, idle );

  /*  Configure the counter to count between 0 and TOP
   */
  hwa( config, COUNTER,
	      clock,	 prescaler_output(CLKDIV),
	      countmode, COUNTMODE,
	      bottom,	 0,
	      top,	 TOP
	      );
  if ( hw_streq(HW_QUOTE(COUNTMODE),"loop_updown") )
    hwa( config, HW_REL(COUNTER,COMPARE),
		output, clear_on_match_up_set_on_match_down );
  else /* loop_up */
    hwa( config, HW_REL(COUNTER,COMPARE),
		output, set_at_bottom_clear_on_match );

  /*  Enable overflow IRQ
   */
  hwa( turn, HW_IRQ(COUNTER,overflow), on );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep();
}
