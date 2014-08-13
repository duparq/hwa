
/*	ADC
 */

#define HWA_DEVICE		attiny84
#define HWA_DEVICE_PACKAGE	dil

#define SG90_MIN		0.000270*2
#define SG90_MAX		0.001300*2
#define SG90_PERIOD		0.02

#define SERVO_PIN		hw_pin_5
#define SERVO_PERIOD		0.02
#define SERVO_COUNTER		hw_counter0
#define SERVO_COUNTER_PSC	1024

#define SERVO_MIN		(int)(SG90_MIN * hw_syshz/SERVO_COUNTER_PSC)
#define SERVO_MAX		(int)(SG90_MAX * hw_syshz/SERVO_COUNTER_PSC)
#define SERVO_STEP		1

#define PIN_DBG			hw_pin_3
#define PIN_ADO			hw_pin_7

#include <hwa.h>


/*	Raise pulse for servo
 */
HW_ISR( hw_irq(SERVO_COUNTER, compare_a) )
{
  static uint16_t	duty = SERVO_MAX ;
  static uint8_t	phase ;

  hw_toggle(PIN_DBG);

  if ( (phase & 1) == 0 ) {
    hw_write( SERVO_PIN, 1 );
    //    hw_write_reg( SERVO_COUNTER, compare_b, duty );
    hw_write( hw_reg(SERVO_COUNTER, compare_b), duty );
    hw_turn( hw_irq(SERVO_COUNTER, compare_b), on );
  //    hw_write( SERVO, duty );
  }

  if ( phase < 2 )
    duty += SERVO_STEP ;
  else
    duty -= SERVO_STEP ;

  if ( duty < SERVO_MAX && duty > SERVO_MIN )
    return ;

  phase = (phase + 1) & 3 ;

  if ( phase < 2 )
    duty = SERVO_MIN ;
  else
    duty = SERVO_MAX ;
}


/*	Lower pulse for servo
 */
HW_ISR( hw_irq(SERVO_COUNTER, compare_b) )
{
  hw_write( SERVO_PIN, 0 );
  hw_turn( hw_irq(SERVO_COUNTER, compare_b), off );
}


/*	AD conversion done
 */
HW_ISR( hw_adc0 )
{
  uint8_t adc = hw_read_reg( hw_adc0, adch );
  //  hw_write( PIN_ADO, adc >= 240 ) ;
  if ( adc >= 240 )
    hw_write( PIN_ADO, 1 ) ;
  else
    hw_write( PIN_ADO, 0 ) ;
}


int main ( )
{
  hwa_begin_from_reset();

  hwa_config( SERVO_COUNTER,
  	      clock,		HW_G2(syshz_div, SERVO_COUNTER_PSC),
  	      countmode,	loop_up,
  	      top,		register_compare_a
  	      );

  if ( SERVO_PERIOD * hw_syshz/SERVO_COUNTER_PSC > (1<<hw_bn(SERVO_COUNTER))-1 )
    HWA_ERR("SERVO_COUNTER can not afford SERVO_PERIOD." );

  hwa_write_reg( SERVO_COUNTER, compare_a, SERVO_PERIOD * hw_syshz/SERVO_COUNTER_PSC) ;
  hwa_turn( hw_irq(SERVO_COUNTER, compare_a), on );
  hwa_turn( hw_irq(SERVO_COUNTER, compare_b), on );

  hwa_config( PIN_DBG, output );
  hwa_config( SERVO_PIN, output );

  hwa_config( hw_adc0,
	      clock,		syshz_div_128,
	      trigger,		auto,
	      vref,		vcc,
	      align,		left,
	      input,		pin_adc0
	      );
  hwa_turn( hw_irq(hw_adc0), on );

  hwa_config( hw_pin_adc0, input );
  hwa_config( PIN_ADO, output );

  hwa_commit();

  hw_enable_interrupts();

  for(;;) {
    hw_sleep_until_irq();
  }

  return 0 ;
}
