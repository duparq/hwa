
/*	Fade a LED connected to a counter compare output (method 2)
 *
 *	Changes versus method 1:
 *
 *        * we define PWM as hw_counterX_compareY and use hw_sup(...) to
 *          retrieve the definition of the counter
 *
 *        * we use a HWA context in the ISR and the couple
 *          hwa_nocommit() / hwa_commit() to write the changes to the hardware
 *
 *        * we use a seperate function to store the hardware configuration
 *          into a HWA context
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */


/*	Target				Results (64, loop_up, compare0)
 *					   hw_counter0		hw_counter1
 *					   bytes:CRC		bytes:CRC
 */
//#include "targets/attiny84.h"		// 188:0x35C1		198:0xA553
//#include "targets/attiny85.h"		// 184:0xA55D		-
#include "targets/nanodccduino.h"	// 264:0x17F7		286:0x5C01
#include <hwa.h>


/*  The counter
 */
#define PWM			hw_counter0_compare0
#define CLKDIV			64
#define COUNTMODE		loop_up


/*  Load a HWA context with the hardware configuration
 */
HW_INLINE void setup_hardware ( hwa_t *hwa )
{
  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa_config( hw_core0,
  	      sleep,      enabled,
  	      sleep_mode, idle );

  /*  Configure the counter to count between 0 and 0xFF
   */
  hwa_config( hw_sup(PWM),
	      clock,     HW_G2(syshz_div, CLKDIV),
	      countmode, COUNTMODE,
	      bottom,    0,
	      top,       fixed_0xFF
	      );
  if ( hw_streq(HW_QUOTE(COUNTMODE),"loop_updown") )
    hwa_config( PWM, output, clear_on_match_up_set_on_match_down );
  else /* loop_up */
    hwa_config( PWM, output, set_at_bottom_clear_on_match );

  /*  Enable overflow IRQ
   */
  hwa_turn_irq( hw_sup(PWM), overflow, on );
}


/*  Service the counter overflow IRQ:
 *    compute the next value of the compare unit
 *
 *    Phase 0: increase duty cycle from 0 to 255
 *    Phase 1: decrease duty cycle from 255 to 0 (use ~duty)
 *    Phase 2: off
 *    Phase 3: off
 */
HW_ISR( hw_sup(PWM), overflow )
{
  static uint8_t	duty ;
  static uint8_t	phase ;

  if ( phase == 0 )
    hw_write( PWM, duty );
  else if ( phase == 1 )
    hw_write( PWM, ~duty );

  duty++ ;

  if ( duty==0 ) {
    phase = (phase + 1) & 3 ;

    /*  In 'loop_up' counting mode, we must disconnect/reconnect the output of
     *	the compare unit as it can not provide pulses of less than 1 cycle.
     */
    if ( hw_streq(HW_QUOTE(COUNTMODE),"loop_up") ) {
      hwa_begin_from_reset();
      setup_hardware( hwa );

      if ( phase == 2 ) {
	/*
	 *  Change the compare output config from 'set_at_bottom_clear_on_match'
	 *  to 'disconnected'
	 */
	hwa_config( PWM, output, set_at_bottom_clear_on_match );
	hwa_nocommit();
	hwa_config( PWM, output, disconnected );
	hwa_commit();
      }
      else if ( phase == 0 ) {
	/*
	 *  Change the compare output config from 'disconnected' to
	 *  'set_at_bottom_clear_on_match'
	 */
	hwa_config( PWM, output, disconnected );
	hwa_nocommit();
	hwa_config( PWM, output, set_at_bottom_clear_on_match );
	hwa_commit();
      }
    }
  }
}


int main ( )
{
  /*  Create a HWA context and load it with RESET values
   */
  hwa_begin_from_reset();

  /*  Load the HWA context with the hardware config
   */
  setup_hardware( hwa );

  /*  Write the configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep();
}
