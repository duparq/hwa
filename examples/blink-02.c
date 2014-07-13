
/*	Blink a LED at ~15 Hz using timer overflow and compare-match interrupts
 */

#include <hwa.h>

#define	LED		hw_pin_7
#define COUNTER		hw_counter0


HW_ISR( hw_irq(COUNTER, compare_a) )
{
  hw_toggle( LED );
}


HW_ISR( hw_irq(COUNTER, overflow) )
{
  hw_write( LED, 1 );
}


int main ( )
{
  hwa_begin_from_reset();
  hwa_config( LED, output );
  hwa_config( COUNTER,
	      clock,		syshz_div_1024,
	      countmode,	loop_updown,
	      bottom,		0,
	      top,		fixed_0xFF
	      );

  hwa_write_bits( COUNTER, compare_a, 16 );
  hwa_turn( hw_irq(COUNTER, compare_a), on );
  hwa_turn( hw_irq(COUNTER, overflow), on );
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep_until_irq();

  return 0 ;
}
