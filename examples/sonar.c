
/*	Trigger the sonar every 100 ms
 */

#include <hwa.h>

#define SONAR_COUNTER		hw_counter1
#define	SONAR_COMP		hw_counter1_compare_b
#define SONAR_CAPTURE		hw_counter1_capture
#define SONAR_TRIG_PERIOD	0.1		/* 100 ms */
#define SONAR_TRIG_LEN		0.000020	/* 20 µs */

#define SG90_MIN		0.000270*2
#define SG90_MAX		0.001300*2
#define SG90_PERIOD		0.02

#define PIN_SERVO		hw_pin_5
#define SERVO_PERIOD		0.02
#define SERVO_COUNTER		hw_counter0

#define PIN_DBG			hw_pin_3


uint16_t	delay ;


HW_ISR( hw_irq(SONAR_CAPTURE) )
{
  static uint16_t	start ;

  /* hw_toggle(PIN_DBG); */

#if 0
  /* hwa_begin(); */
  /* if ( hw_read(hw_io(SONAR_CAPTURE)) == 0 ) { */
  /*   hwa_config( SONAR_CAPTURE, */
  /* 		input,		pin_icp, */
  /* 		edge,		falling */
  /* 		); */
  /*   hwa_nocommit(); */
  /*   hwa_config( SONAR_CAPTURE, */
  /* 		input,		pin_icp, */
  /* 		edge,		rising */
  /* 		); */
  /*   hwa_commit(); */
  /*   delay = hw_read(SONAR_CAPTURE) - start ; */
  /* } */
  /* else { */
  /*   hwa_config( SONAR_CAPTURE, */
  /* 		input,		pin_icp, */
  /* 		edge,		rising */
  /* 		); */
  /*   hwa_nocommit(); */
  /*   hwa_config( SONAR_CAPTURE, */
  /* 		input,		pin_icp, */
  /* 		edge,		falling */
  /* 		); */
  /*   hwa_commit(); */
  /*   start = hw_read(SONAR_CAPTURE); */
  /* } */
#else
  uint16_t capture = hw_read(SONAR_CAPTURE) ;
  if ( hw_read(hw_io(SONAR_CAPTURE)) == 0 ) {
    hw_config( SONAR_CAPTURE, edge, rising );
    delay = capture - start ;
  }
  else {
    hw_config( SONAR_CAPTURE, edge, falling );
    start = capture ;
  }
#endif
}


#if 0
#if hw_addr(hw_bits(hw_ctr(PIN_DBG), pin)) < 0x40
HW_ISR( hw_irq(SERVO_COUNTER, compare_a), naked )
{
  hw_toggle(PIN_DBG);
  __asm__ __volatile__("    reti \n\t":::);
}
#else
HW_ISR( hw_irq(SERVO_COUNTER, compare_a) )
{
  hw_toggle(PIN_DBG);
}
#endif
#endif

#define SERVO_MIN	(int)(SG90_MIN * hw_syshz/1024)
#define SERVO_MAX	(int)(SG90_MAX * hw_syshz/1024)

/*	Servo counter reaches TOP: raise pulse for servo
 */
HW_ISR( hw_irq(SERVO_COUNTER, compare_a) )
{
  hw_toggle(PIN_DBG);
  /* uint16_t d = delay/4 ; */
  /* if ( d > 255 ) */
  /*   hw_write(SERVO_PULSAR, 255); */
  /* else */
  /*   hw_write(SERVO_PULSAR, d & 0xFF ); */
  hw_write( PIN_SERVO, 1 );
  //  hw_write_bits( SERVO_COUNTER, compare_b, delay );
  uint16_t x = SERVO_MIN+delay/8 ;
  if ( x > SERVO_MAX )
    x = SERVO_MAX ;
  hw_write_bits( SERVO_COUNTER, compare_b, x );
}

/*	Servo counter compare match: lower pulse for servo
 */
HW_ISR( hw_irq(SERVO_COUNTER, compare_b) )
{
  hw_write( PIN_SERVO, 0 );
}


int main ( )
{
  /*	Echo delay: 58.824 µs / 1 cm
   */
  hwa_begin_from_reset();
  hwa_config( SONAR_COUNTER,
	      clock,		syshz_div_64,	/* ~8 µs */
	      countmode,	loop_up,
	      bottom,		0,
	      top,		register_compare_a
	      );
  hwa_write_bits( SONAR_COUNTER, compare_a, SONAR_TRIG_PERIOD * hw_syshz/64) ;

  hwa_config( SONAR_COMP, set_at_bottom_clear_on_match );
  hwa_write( SONAR_COMP, SONAR_TRIG_LEN * hw_syshz/64);

  hwa_config( SONAR_CAPTURE,
  	      input,		pin_icp,
  	      edge,		rising
  	      );
  hwa_turn( hw_irq(SONAR_CAPTURE), on );

  if ( SERVO_PERIOD * hw_syshz/1024 > (1UL<<hw_bn(SERVO_COUNTER))-1 )
    HWA_ERR("SERVO_COUNTER can not afford SERVO_PERIOD." );

  hwa_config( SERVO_COUNTER,
  	      clock,		syshz_div_1024,
  	      countmode,	loop_up,
  	      top,		register_compare_a
  	      );
  hwa_turn( hw_irq(SERVO_COUNTER, compare_a), on );
  hwa_turn( hw_irq(SERVO_COUNTER, compare_b), on );
  hwa_write_bits( SERVO_COUNTER, compare_a, SERVO_PERIOD * hw_syshz/1024) ;

  //  hwa_config( SERVO_PULSAR, set_at_bottom_clear_on_match );

  hwa_config( PIN_DBG, output );
  hwa_config( PIN_SERVO, output );

  hwa_config( hw_core0, sleep_mode, idle );

  hwa_commit();

  hw_enable_interrupts();

  for(;;) {
    hw_sleep_until_irq();
  }

  return 0 ;
}
