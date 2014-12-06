
/*	Convert voltage to pulse width
 *
 *	Can be used to drive a servo (use a good power supply for the servo, USB
 *	RS232 modules do not provide enough current):
 *
 *		brown  -> ground
 *              red    -> +6 V
 *              yellow -> pwm
 */

#define HW_DEVICE		attiny84, dil

#define PWM_PERIOD		0.02		/* 50 Hz */
#define PWM_TON_MIN		0.000300	/*  300 µs min */
#define PWM_TON_MAX		0.003000	/* 3000 µs max */

#define PWM_COUNTER		hw_counter1
#define PWM_COUNTER_OUTPUT	hw_counter1_output0	/* compare unit output OC1A, DIL#7 */
#define PWM_COUNTER_CLK_DIV	8
#define PWM_COUNTER_MIN		(uint16_t)(PWM_TON_MIN*hw_syshz/PWM_COUNTER_CLK_DIV)
#define PWM_COUNTER_MAX		(uint16_t)(PWM_TON_MAX*hw_syshz/PWM_COUNTER_CLK_DIV)

#define ADC_CLK_DIV		128
#define ADC_INPUT		hw_pin_adc0

#define PIN_DBG			hw_pin_6

#include <hwa.h>


/*  AD conversion done
 *
 *  Convert voltage in [0..255] to duty cycle in [PWM_TON_MIN, PWM_TON_MAX] with
 *  low-pass filtering
 */
HW_ISR( hw_adc0 )
{
  static uint8_t		n ;
  static uint8_t		adc ;

  if ( n==0 ) {
    uint16_t tmp = adc ;
    tmp = (15*tmp + hw_read_reg( hw_adc0, data_high_byte ) + 8) / 16 ;
    adc = tmp ;

    uint32_t duty = adc ;
    duty = duty*(PWM_COUNTER_MAX-PWM_COUNTER_MIN)/255 + PWM_COUNTER_MIN ;
    hw_write( PWM_COUNTER_OUTPUT, duty );
    n=32 ;
  }
  else
    n-- ;
}


int main ( )
{
  hwa_begin_from_reset();

  hwa_config( PIN_DBG, output );

  if ( (uint32_t)(PWM_PERIOD*hw_syshz/PWM_COUNTER_CLK_DIV) > ((1UL<<hw_bn(PWM_COUNTER))-1) )
    HWA_ERR("PWM_COUNTER can not afford PWM_PERIOD.") ;

  hwa_config( PWM_COUNTER,
	      clock,		HW_G2(syshz_div, PWM_COUNTER_CLK_DIV),
	      countmode,	loop_up,
	      bottom,		0,
	      top,		register_capture
	      );
  hwa_write( hw_reg(PWM_COUNTER, capture), PWM_PERIOD*hw_syshz/PWM_COUNTER_CLK_DIV );
  hwa_config( PWM_COUNTER_OUTPUT, set_at_bottom_clear_on_match );

  hwa_config( hw_adc0,
	      clock,		HW_G2(syshz_div, ADC_CLK_DIV),
	      trigger,		auto,
	      vref,		vcc,
	      align,		left,
	      input,		hw_name(ADC_INPUT),
	      );
  hwa_turn( hw_irq(hw_adc0), on );
  hwa_trigger( hw_adc0 );
  hwa_config( hw_pin_adc0, input );

  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep_until_irq();

  return 0 ;
}
