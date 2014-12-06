
/*
 *	Find limits of Tower Pro SG90 servomotor connected to output-compare pin
 */

#define HW_DEVICE		attiny84, dil

#define SERVO_PERIOD		0.02
#define SERVO_MIN		0.000300
#define SERVO_MAX		0.003000
#define SERVO_MID		0.001500

#define SERVO_COUNTER_OUTPUT	hw_counter1_output0	/* compare unit output OC1A, DIL#7 */
#define SERVO_COUNTER		hw_counter1
#define SERVO_COUNTER_PSC	8
#define SERVO_COUNTER_MIN	(uint16_t)(SERVO_MIN*hw_syshz/SERVO_COUNTER_PSC)
#define SERVO_COUNTER_MAX	(uint16_t)(SERVO_MAX*hw_syshz/SERVO_COUNTER_PSC)
#define SERVO_COUNTER_MID	(uint16_t)(SERVO_MID*hw_syshz/SERVO_COUNTER_PSC)

#define SERVO_COUNTER_STEP	((SERVO_COUNTER_MAX-SERVO_COUNTER_MIN)/180)

#define ADC_CLK_DIV		128
#define ADC_PERIOD		(13.0*ADC_CLK_DIV/hw_syshz)
#define ADC_INPUT		hw_pin_adc0

#define PIN_DBG			hw_pin_6

#include <hwa.h>


uint8_t				n_low_samples ;


/*	Interrupt: PWM output has just been cleared
 */
HW_ISR( SERVO_COUNTER_OUTPUT )
{
  static uint16_t	duty ;
  static uint8_t	phase ;
  static uint8_t	nloads ;

  if ( phase == 0 ) {
    /*
     *	Begin with middle-length pulse width
     */
    duty = SERVO_COUNTER_MID ;
    phase = 10 ;
  }
  else if ( phase == 10 ) {
    /*
     *	Wait for motion
     */
    if ( n_low_samples )
      phase = 2 ;
  }
  else if ( phase == 1 ) {
    /*
     *	Wait for end of motion
     */
    if ( n_low_samples < (uint8_t)(0.002 / ADC_PERIOD) ) {
      nloads = 0 ;
      phase = 2 ;
    }
  }
  else if ( phase == 2 ) {
    //    hw_toggle( PIN_DBG );
    /*
     *	Reduce pulse width until the servo draws current for more than 0.2 s
     */
    if ( n_low_samples < (uint8_t)(0.002 / ADC_PERIOD) ) {
      nloads = 0 ;
      duty -= SERVO_COUNTER_STEP ;
      if ( duty < SERVO_COUNTER_MIN )
	phase = 99 ;
    }
    else {
      nloads++ ;
      if ( nloads > (uint8_t)(0.3 / SERVO_PERIOD) )
	phase = 3 ;
    }
  }
  else if ( phase == 3 ) {
    /*
     *	Grow pulse width until the servo stops drawing current for more than 0.2 s
     */
    if ( n_low_samples > (uint8_t)(0.002 / ADC_PERIOD) ) {
      duty += SERVO_COUNTER_STEP ;
      if ( duty > SERVO_COUNTER_MAX )
	phase = 99 ;
    }
    else
      phase = 4 ;
  }
  else if ( phase == 4 ) {
    /*
     *	Grow pulse width until the servo draws current for more than 0.2 s
     */
    if ( n_low_samples < (uint8_t)(0.002 / ADC_PERIOD) ) {
      nloads = 0 ;
      duty += SERVO_COUNTER_STEP ;
      if ( duty > SERVO_COUNTER_MAX )
	phase = 99 ;
    }
    else {
      nloads++ ;
      if ( nloads > (uint8_t)(0.3 / SERVO_PERIOD) )
	phase = 99 ;
    }
  }
  else {
    /*
     *	Stop everything
     */
    hw_turn( hw_irq(SERVO_COUNTER_OUTPUT), off );
    hw_turn( hw_irq(hw_adc0), off );
    hw_config( SERVO_COUNTER_OUTPUT, disconnected );
    phase = 5 ;
  }

  hw_write( SERVO_COUNTER_OUTPUT, duty );
  n_low_samples = 0 ;
}


/*	AD conversion done
 */
HW_ISR( hw_adc0 )
{
  //  hw_toggle( PIN_DBG ) ;
  uint8_t adc = hw_read( hw_adc0, data_high_byte );

  if ( adc < (uint8_t)(256*0.98) ) {
    if ( n_low_samples < 0xFF ) {
      hw_disable_interrupts();
      n_low_samples++ ;
      hw_enable_interrupts();
    }
    hw_write( PIN_DBG, 0 ) ;
  }
  else
    hw_write( PIN_DBG, 1 ) ;
}


int main ( )
{
  hwa_begin_from_reset();

  hwa_config( PIN_DBG, output );

  if ( (uint32_t)(SERVO_PERIOD*hw_syshz/SERVO_COUNTER_PSC) > ((1UL<<hw_bn(SERVO_COUNTER))-1) )
    HWA_ERR("SERVO_COUNTER can not afford SERVO_PERIOD.") ;

  hwa_config( SERVO_COUNTER,
	      clock,		HW_G2(syshz_div, SERVO_COUNTER_PSC),
	      countmode,	loop_up,
	      bottom,		0,
	      top,		register_capture
	      );
  hwa_write( hw_reg(SERVO_COUNTER, capture), SERVO_PERIOD*hw_syshz/SERVO_COUNTER_PSC );
  hwa_config( SERVO_COUNTER_OUTPUT, set_at_bottom_clear_on_match );
  hwa_turn_irq( SERVO_COUNTER_OUTPUT, on );

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

  /*	No sleeping ?
   */
  for(;;) {
    //    hw_sleep_until_irq();
    /* hw_atomic_read( hw_adc0 ); */
    //    hw_read( hw_adc0 );
  }

  return 0 ;
}
