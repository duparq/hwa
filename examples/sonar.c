
/*	Trigger the sonar every 100 ms
 */

#include <hwa.h>

#define SONAR_COUNTER		hw_counter1
#define	SONAR_TRIG		hw_oc1b		/* output compare OC1B */
#define SONAR_TRIG_PERIOD	0.1		/* 100 ms */
#define SONAR_TRIG_LEN		0.000020	/* 20 µs */
#define SONAR_CAPTURE		hw_ic1a

#define SG90_MIN		0.000270*2
#define SG90_MAX		0.001300*2
#define SG90_PERIOD		0.02

#define PIN_SERVO		hw_pin_5
#define SERVO_PERIOD		0.02
#define SERVO_COUNTER		hw_counter0
//#define SERVO_PULSAR		hw_oc0b

#define PIN_DBG			hw_pin_3


uint16_t	delay ;


HW_ISR( hw_irq(SONAR_CAPTURE) )
{
  static uint16_t	start ;

  /* hw_toggle(PIN_DBG); */

  //  hw_write_bits( SONAR_COUNTER, ices, !hw_read_bits( SONAR_COUNTER, ices) );
  //  hw_write_bits( SONAR_COUNTER, ices, hw_read_bits(SONAR_COUNTER, ices)==0 );

  /* hw_write_bits( SONAR_COUNTER, ices, 0 ); */
  /* hw_write_bits( SONAR_COUNTER, ices, 1 ); */

  /* if ( hw_read_bits( SONAR_COUNTER, ices) == 0 ) */
  /*   hw_write_bits( SONAR_COUNTER, ices, 1 ); */
  /* else */
  /*   hw_write_bits( SONAR_COUNTER, ices, 0 ); */

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

/*	Raise pulse for servo
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

HW_ISR( hw_irq(SERVO_COUNTER, compare_b) )
{
  hw_write( PIN_SERVO, 0 );
}


int main ( )
{
  /*	Echo delay: 58.824 µs / 1 cm
   */
  hwa_begin_from_reset();
  hwa_config( SONAR_COUNTER,			/* hw_ctr(SONAR_TRIG) */
	      clock,		syshz_div_64,	/* ~8 µs */
	      countmode,	loop_up,
	      bottom,		0,
	      top,		register_compare_a,
	      /* update,		at_top, */
	      /* overflow,		at_top, */
	      );
  hwa_write_bits( SONAR_COUNTER, compare_a, SONAR_TRIG_PERIOD * hw_syshz/64) ;

  hwa_config(SONAR_TRIG, set_at_bottom_clear_on_match );
  hwa_write(SONAR_TRIG, SONAR_TRIG_LEN * hw_syshz/64);

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

  if ( SERVO_PERIOD * hw_syshz/1024 > (1<<hw_bn(SERVO_COUNTER))-1 )
    HWA_ERR("SERVO_COUNTER can not afford SERVO_PERIOD." );

  hwa_write_bits( SERVO_COUNTER, compare_a, SERVO_PERIOD * hw_syshz/1024) ;
  //  hwa_turn( hw_irq(SERVO_COUNTER, overflow), on ); /* Overflow at MAX! */
  hwa_turn( hw_irq(SERVO_COUNTER, compare_a), on );
  hwa_turn( hw_irq(SERVO_COUNTER, compare_b), on );

  //  hwa_config( SERVO_PULSAR, set_at_bottom_clear_on_match );

  hwa_config( PIN_DBG, output );
  hwa_config( PIN_SERVO, output );

  hwa_commit();

  hw_enable_irqs();

  for(;;) {
    hw_sleep_until_irq();
  }

  return 0 ;
}
