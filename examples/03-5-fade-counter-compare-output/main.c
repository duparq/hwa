
/*	Fade a LED connected to a counter compare output (method 1)
 *
 *	Note: see method 2 in the next example.
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */


/*	Target
 */
#include "targets/attiny84.h"	     // 192 bytes
//#include "targets/attiny85.h"	     // 188:0x8F4B	-	   	-	  
//#include "targets/nanodccduino.h"    // 268:0x2D65 (D6)	294:0xDF1A 	280:0xAC79 (D11)
#include <hwa.h>


/*  The counter
 */
#define COUNTER			hw_counter0
#define CLKDIV			64
#define COUNTMODE		loop_up
#define COMPARE			compare0


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
  static uint8_t	duty ;
  static uint8_t	phase ;

  if ( phase == 0 )
    hw_write( hw_sub(COUNTER,COMPARE), duty );
  else if ( phase == 1 )
    hw_write( hw_sub(COUNTER,COMPARE), ~duty );

  duty++ ;

  if ( duty==0 ) {
    phase = (phase + 1) & 3 ;

    /*  In 'loop_up' counting mode, we must disconnect/reconnect the output of
     *	the compare unit as it can not provide pulses of less than 1 cycle.
     *
     *  Note that the configuration of the counter is not known here, so there
     *  is only loose checking against the arguments provided and the generated
     *  code will probably have to read the hardware to retrieve unknown bit
     *  values.
     */
    if ( hw_streq(HW_QUOTE(COUNTMODE),"loop_up") ) {
      if ( phase == 2 )
	hw_config( hw_sub(COUNTER,COMPARE), output, disconnected );
      else if ( phase == 0 )
	hw_config( hw_sub(COUNTER,COMPARE), output, set_at_bottom_clear_on_match );
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
  hwa_config( hw_core0,
  	      sleep,      enabled,
  	      sleep_mode, idle );

  /*  Configure the counter to count between 0 and 0xFF
   */
  hwa_config( COUNTER,
	      clock,     HW_G2(syshz_div, CLKDIV),
	      countmode, COUNTMODE,
	      bottom,    0,
	      top,       fixed_0xFF
	      );
  if ( hw_streq(HW_QUOTE(COUNTMODE),"loop_updown") )
    hwa_config( hw_sub(COUNTER,COMPARE),
		output, clear_on_match_up_set_on_match_down );
  else /* loop_up */
    hwa_config( hw_sub(COUNTER,COMPARE),
		output, set_at_bottom_clear_on_match );

  /*  Enable overflow IRQ
   */
  hwa_turn_irq( COUNTER, overflow, on );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep();
}


/* _hw_x... -> faire retourner le nom du sous-registre
 */

//  hwa->hw_counter0->cs.r = (hwa_r8_t*)hwa->hw_counter0.

#define _hwa_begin_m8(on,m)		_hwa_begin_m8_2( _##on,on,m )
#define _hwa_begin_m8_2(...)		_hwa_begin_m8_3(__VA_ARGS__)
//_hwa_begin_m8_2( _c8a, 400, 0,hw_counter0,cs );
#define _hwa_begin_m8_3(c,i,a,on,m)	_hwa_begin_m8_4(m,_hw_##c##_##m,on,c,a)
#define _hwa_begin_m8_4(...)		_hwa_begin_m8_5(__VA_ARGS__)

#define _hwa_begin_m8_5(m,t,...)	HW_G2(_hwa_begin_m8,HW_IS(,hw_hasbits_##t))(m,t,__VA_ARGS__)

#define _hwa_begin_m8_1(m,t,...)	_HW_SPEC(_hwa_begin, _hw_x##t(__VA_ARGS__,m), m)

//_hwa_begin__m1(hw_counter0,0, ccrb,8,0x53,0xCF,0x00, 3,0);

//_hwa_begin__m1(hw_counter0,0, ccrb,8,0x53,0xCF,0x00, 3,0, cs);
#define _hwa_begin__m1(on,a, rn,rw,ra,rwm,rfm, bn, bp, m)	\
  hwa->on.m.r = (hwa_r8_t*)&hwa->on.rn



//_hwa_begin_m8( hw_counter0, cs );