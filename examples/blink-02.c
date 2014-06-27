
/*	Blink a LED at ~15 Hz using timer overflow and compare-match interrupts
 */

#include <hwa.h>

#define	LED		hw_pin_7
#define COUNTER		hw_counter0


HW_ISR( COUNTER, match_a )
{
  hw_toggle( LED );
}


HW_ISR( COUNTER, overflow )
{
  hw_write( LED, 1 );
}


int main ( )
{
  hwa_begin_from_reset();
  hwa_config( LED, output );
  hwa_config( COUNTER,
	      countmode,	loop_updown_pwm,
	      bottom,		0,
	      top,		fixed_0xFF,
	      clock,		syshz_div_1024 );

  hwa_write( COUNTER, match_a, 16 );
  hwa_turn_irq( COUNTER, match_a, on );
  hwa_turn_irq( COUNTER, overflow, on );
  hwa_commit();

  hw_enable_irqs();

  for(;;)
    hw_sleep_until_irq();

  return 0 ;
}
