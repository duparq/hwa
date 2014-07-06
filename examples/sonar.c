
/*	Trigger the sonar every 100 ms
 */

#include <hwa.h>

#define SONAR_COUNTER		hw_counter1
#define	SONAR_TRIG		hw_oc1b		/* output compare OC1B */
#define SONAR_TRIG_PERIOD	0.1		/* 100 ms */
#define SONAR_TRIG_LEN		0.000020	/* 20 µs */


/* HW_ISR( hw_irq(hw_ctr(SONAR), overflow) ) */
/* { */
/*   if ( (phase & 1) == 0 ) */
/*     hw_write( SONAR, duty ); */

/*   if ( phase < 2 ) */
/*     duty += DUTY_STEP ; */
/*   else */
/*     duty -= DUTY_STEP ; */

/*   if ( duty < DUTY_MAX && duty > DUTY_MIN ) */
/*     return ; */

/*   phase = (phase + 1) & 3 ; */

/*   if ( phase < 2 ) */
/*     duty = DUTY_MIN ; */
/*   else */
/*     duty = DUTY_MAX ; */
/* } */


int main ( )
{
  hwa_begin_from_reset();
  hwa_config( SONAR_COUNTER,			/* hw_ctr(SONAR_TRIG) */
	      clock,		syshz_div_64,
	      countmode,	loop_up,
	      bottom,		0,
	      top,		register_compare_a,
	      /* update,		at_top, */
	      /* overflow,		at_top, */
	      );

  hwa_write_bits( SONAR_COUNTER, compare_a, SONAR_TRIG_PERIOD * hw_syshz/64) ;
  hwa_config(SONAR_TRIG, set_at_bottom_clear_on_match );
  hwa_write(SONAR_TRIG, SONAR_TRIG_LEN * hw_syshz/64);
  //  hwa_turn( hw_irq(hw_ctr(SONAR), overflow), on );

  hwa_commit();

  hw_enable_irqs();

  for(;;)
    hw_sleep_until_irq();

  return 0 ;
}
