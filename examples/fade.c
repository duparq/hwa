
/*	Fade a LED using an output-compare pin configured for PWM
 */

#include <hwa.h>

#define	LED_PIN			hw_counter0_compare_b
#define LED_COUNTER		hw_counter0
#define LED_COUNTER_PSC		64


HW_ISR( hw_irq(LED_COUNTER, overflow) )
{
  static uint8_t	duty ;
  static uint8_t	phase ;

  if ( phase == 0 )
    hw_write( LED_PIN, duty );
  else if ( phase == 1 )
    hw_write( LED_PIN, ~duty );

  duty++ ;

  if ( duty==0 )
    phase = (phase + 1) & 3 ;
}


HW_INLINE void config_led_counter( hwa_t *hwa )
{
  hwa_config( LED_COUNTER,
	      clock,		HW_G2(syshz_div, LED_COUNTER_PSC),
	      countmode,	loop_up,
	      bottom,		0,
	      top,		register_compare_a
	      );

  hwa_write_bits( LED_COUNTER, compare_a, 0xFF );
  //  hwa_write( hw_ctr(LED), icr, 0xFF );

  hwa_turn( hw_irq(LED_COUNTER, overflow), on );
  //  hwa_turn_irq( hw_counter(LED), capture, on );
  //  hwa_turn_irq( hw_counter(LED), match_a, on );
}


HW_INLINE void config_led_pin( hwa_t *hwa )
{
  //  hwa_config( LED, clear_on_match_up_set_on_match_down );
  hwa_config( LED_PIN, set_at_bottom_clear_on_match );
}


int main ( )
{
  hwa_begin_from_reset();
  config_led_pin(hwa);
  config_led_counter(hwa);
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep_until_irq();

  return 0 ;
}
