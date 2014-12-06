
/*	Tower Pro SG90 servomotor connected to output-compare pin
 *
 *	min: 500 us
 *	max: 2400 us
 */

#include <hwa.h>


#define	SERVO_COUNTER	hw_counter1
#define	SERVO		hw_counter1_compare_a		/* compare unit output OC1A */
/* #define DUTY_MIN	260 */
/* #define DUTY_MAX	1200 */
#define DUTY_MIN	270
#define DUTY_MAX	1300
#define DUTY_PERIOD	5000*2
#define DUTY_STEP	10


HW_ISR( hw_irq(SERVO_COUNTER, overflow) )
{
  static uint16_t	duty = DUTY_MAX ;
  static uint8_t	phase ;

#if 0
  if ( phase < 2 )
    hw_write( SERVO, duty );

  if ( (phase & 1) == 0 )
    duty += DUTY_STEP ;
  else
    duty -= DUTY_STEP ;

  if ( duty > DUTY_MAX || duty < DUTY_MIN )
    phase = (phase + 1) & 3 ;
#endif

  if ( (phase & 1) == 0 )
    hw_write( SERVO, duty );

  if ( phase < 2 )
    duty += DUTY_STEP ;
  else
    duty -= DUTY_STEP ;

  if ( duty < DUTY_MAX && duty > DUTY_MIN )
    return ;

  phase = (phase + 1) & 3 ;

  if ( phase < 2 )
    duty = DUTY_MIN ;
  else
    duty = DUTY_MAX ;
}


/*	Configure the counter to have a 1 us clock.
 */
HW_INLINE void config_counter( hwa_t *hwa )
{
  hwa_config( SERVO_COUNTER,
	      clock,		syshz_div_8,
	      countmode,	loop_updown,
	      bottom,		0,
	      top,		register_capture,
	      update,		at_bottom,
	      overflow,		at_bottom,
	      );

  hwa_write( hw_bits(SERVO_COUNTER, capture), DUTY_PERIOD );
  //  hwa_write( hw_reg(SERVO_COUNTER, capture), DUTY_PERIOD );
  hwa_turn( hw_irq(SERVO_COUNTER, overflow), on );
}


HW_INLINE void config_servo( hwa_t *hwa )
{
  hwa_config( SERVO, clear_on_match_up_set_on_match_down );
  //  hwa_write( SERVO, DUTY_MIN );
}


int main ( )
{
  hwa_begin_from_reset();
  //  hwa_config(hw_pin_8, output);
  config_servo(hwa);
  config_counter(hwa);
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep_until_irq();

  return 0 ;
}
