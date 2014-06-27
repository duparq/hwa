
/*	Fade a LED using an output-compare pin configured for PWM
 */

#include <hwa.h>

#define	LED		hw_oc0a


HW_ISR( hw_ctr(LED), overflow )
{
  static uint8_t	duty ;
  static uint8_t	phase ;

  if ( phase == 0 )
    hw_write( LED, duty );
  else if ( phase == 1 )
    hw_write( LED, ~duty );

  duty++ ;

  if ( duty==0 )
    phase = (phase + 1) & 3 ;
}


HW_INLINE void config_counter( hwa_t *hwa )
{
  hwa_config( hw_ctr(LED),
	      countmode,	loop_updown_pwm,
	      bottom,		0,
	      //	      top,		register_icr,
	      top,		fixed_0xFF,
	      clock,		syshz_div_64 );

  //  hwa_write( hw_ctr(LED), icr, 0xFF );

  hwa_turn_irq( hw_ctr(LED), overflow, on );
  //  hwa_turn_irq( hw_counter(LED), capture, on );
  //  hwa_turn_irq( hw_counter(LED), match_a, on );
}


HW_INLINE void config_led( hwa_t *hwa )
{
  hwa_config( LED, clearup_setdown );
}


int main ( )
{
  hwa_begin_from_reset();
  config_led(hwa);
  config_counter(hwa);
  hwa_commit();

  hw_enable_irqs();

  for(;;)
    hw_sleep_until_irq();

  return 0 ;
}
