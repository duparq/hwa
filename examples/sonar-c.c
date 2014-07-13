
/*	Measure a distance with ultrasonic module and drive a servo accordingly
 *
 *	308 bytes of code
 */

#include <hwa.h>

#define	SONAR_TRIG		hw_oc1b		/* output compare OC1B */
#define SONAR_TRIG_PERIOD	0.1		/* 100 ms */
#define SONAR_TRIG_LEN		0.000020	/* 20 µs */
#define SONAR_CAPTURE		hw_ic1a		/* Echo delay: 58.824 µs / 1 cm */
#define SONAR_COUNTER		hw_counter1	/* = hw_ctr(SONAR_TRIG) */

#define SG90_MIN		0.000270*2
#define SG90_MAX		0.001300*2
#define SG90_PERIOD		0.02

#define PIN_SERVO		hw_pin_5
#define SERVO_PERIOD		0.02
#define SERVO_COUNTER		hw_counter0

#define SERVO_MIN		(int)(SG90_MIN * hw_syshz/1024)
#define SERVO_MAX		(int)(SG90_MAX * hw_syshz/1024)

#define PIN_DBG			hw_pin_3


uint16_t	delay ;


/*  Rising or falling edge on capture pin
 *	Compute delay
 */
HW_ISR( hw_irq(SONAR_CAPTURE) )
{
  static uint16_t	start ;

  uint16_t capture = hw_read(SONAR_CAPTURE) ;
  if ( hw_read(hw_io(SONAR_CAPTURE)) == 0 ) {
    hw_config( SONAR_CAPTURE, edge, rising );
    delay = capture - start ;
  }
  else {
    hw_config( SONAR_CAPTURE, edge, falling );
    start = capture ;
  }
}


/*  Compare A : raise pulse for servo and set date for lowering
 */
HW_ISR( hw_irq(SERVO_COUNTER, compare_a) )
{
  hw_toggle(PIN_DBG);
  hw_write( PIN_SERVO, 1 );
  uint16_t x = SERVO_MIN+delay/8 ;
  if ( x > SERVO_MAX )
    x = SERVO_MAX ;
  hw_write_bits( SERVO_COUNTER, compare_b, x );
}


/*  Compare B : lower pulse for servo
 */
HW_ISR( hw_irq(SERVO_COUNTER, compare_b) )
{
  hw_write( PIN_SERVO, 0 );
}


int main ( )
{
  hwa_begin_from_reset();
  hwa_config( SONAR_COUNTER,
	      clock,		syshz_div_64,	/* ~8 µs */
	      countmode,	loop_up,
	      bottom,		0,
	      top,		register_compare_a );
  hwa_write_bits( SONAR_COUNTER, compare_a, SONAR_TRIG_PERIOD * hw_syshz/64) ;

  hwa_config( SONAR_TRIG, set_at_bottom_clear_on_match );
  hwa_write( SONAR_TRIG, SONAR_TRIG_LEN * hw_syshz/64 );

  hwa_config( SONAR_CAPTURE,
  	      input,		pin_icp,
  	      edge,		rising
  	      );

  hwa_turn( hw_irq(SONAR_CAPTURE), on );

  hwa_config( SERVO_COUNTER,
  	      clock,		syshz_div_1024,
  	      countmode,	loop_up,
  	      top,		register_compare_a
  	      );

  /*	Check that the count register can support the period
   */
  if ( SERVO_PERIOD * hw_syshz/1024 > (1<<hw_bn(SERVO_COUNTER))-1 )
    HWA_ERR("SERVO_COUNTER can not hold SERVO_PERIOD." );

  hwa_write_bits( SERVO_COUNTER, compare_a, SERVO_PERIOD * hw_syshz/1024) ;
  hwa_turn( hw_irq(SERVO_COUNTER, compare_a), on );
  hwa_turn( hw_irq(SERVO_COUNTER, compare_b), on );

  hwa_config( PIN_DBG, output );
  hwa_config( PIN_SERVO, output );

  hwa_commit();

  hw_enable_irqs();

  for(;;) {
    hw_sleep_until_irq();
  }

  return 0 ;
}
