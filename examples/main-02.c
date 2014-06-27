
/*	Blink a LED at 5 Hz using 
 */

#include <hwa.h>

#define	LED		hw_pin_7
#define COUNTER		hw_counter0
//#define MATCH_A		hw_cmou0a


#if 0
//HW_ISR(COUNTER, match_a /* , interruptible */)
HW_ISR(COUNTER, match_a)
{
  //  hw_write( LED, 0 );
  hw_toggle( LED );
}


//HW_ISR(COUNTER, overflow /* , naked, interruptible */)
HW_ISR(COUNTER, overflow)
{
  //  static _Bool		updown ;
  static uint8_t	phase ;

  uint8_t n = hw_read( COUNTER, match_a );
  //  if ( updown == 0 )
  if ( (phase & 1) == 0 ) {
    n++ ;
    if ( n==255 )
      phase++ ;
  }
  else {
    n-- ;
    if ( n==1 ) {
      phase++ ;
      if ( phase==2 ) {
	hw_turn_irq( COUNTER, match_a, off );
	hw_write( LED, 0 );
      }
      else if (phase == 4)
	phase = 0;
    }
  }

  hw_write( COUNTER, match_a, n );
  if ( phase<2 && n>1 ) {
    hw_turn_irq( COUNTER, match_a, on );
    hw_write( LED, 1 );
  }
}
#endif


HW_ISR(COUNTER, overflow)
{
  static uint8_t	duty ;
  static uint8_t	phase ;

  if ( duty==0 )
    phase = (phase + 1) & 3 ;

  if ( phase == 0 )
    //    hw_write( COUNTER, match_a, duty );
    hw_write( hw_oc0a, duty );
  else if ( phase == 1 )
    //    hw_write( COUNTER, match_a, ~duty );
    hw_write( hw_oc0a, ~duty );
  duty++ ;
}


int main ( )
{
  hwa_begin_from_reset();
  hwa_config( LED, output );
  //  hwa_config( COUNTER,
  hwa_config( hw_counter(hw_oc0a),
	      countmode,	loop_updown_pwm,
	      /* bottom,		0, */
	      /* top,		topreg, */
	      top,		255,
	      clk,		syshz_div_64 );

  //	     top,	hw_max(COUNTER),

  //  hwa_write( COUNTER, topreg, 127 );

  //  hwa_write( hw_oc0a, 64 );
  //  hwa_write( COUNTER, match_a, 64 );

  //  hwa_turn_irq( COUNTER, match_a, on );
  hwa_turn_irq( COUNTER, overflow, on );

  //  hwa_config( hw_pin_5, output );
  hwa_config( hw_oc0a, cleared_on_match_up_set_on_match_down );
  //  hwa_config( hw_oc0a, set_at_bottom_cleared_on_match );
  //  hwa_config( hw_oc0a, disconnected );

  hwa_commit();

  hw_enable_irqs();

  for(;;)
    hw_sleep_until_irq();

  return 0 ;
}
