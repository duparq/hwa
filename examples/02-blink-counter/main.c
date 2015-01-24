
/*	Blink a LED at ~15 Hz using timer overflow and compare-match interrupts
 */

#define HW_DEVICE		attiny84, 14pdip

#define	LED_PIN			hw_pin_7
//#define PERIOD			0.2
#define COUNTER			hw_counter0

#include <hwa.h>


//HW_ISR( hw_irq(COUNTER, compare_a), naked )
HW_ISR( COUNTER, compare_a, naked )
{
  hw_toggle( LED_PIN );
  hw_reti();
}


//HW_ISR( hw_irq(COUNTER, overflow) )
HW_ISR( COUNTER, overflow )
{
  hw_write( LED_PIN, 1 );
}


int main ( )
{
  hwa_begin_from_reset();
  hwa_config( LED_PIN, output );
  hwa_config( COUNTER,
	      clock,		syshz_div_1024,
	      countmode,	loop_updown,
	      bottom,		0,
	      top,		fixed_0xFF
	      );

  hwa_write_reg( COUNTER, compare_a, 16 );
  //  hwa_turn( hw_irq(COUNTER, compare_a), on );
  hwa_turn_irq( COUNTER, compare_a, on );

  //  hwa_turn_irq( COUNTER, compare_a, on );

  hwa_turn( hw_irq(COUNTER, overflow), on );
  //hwa_turn_irq( COUNTER, overflow, on );
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep_until_irq();

  return 0 ;
}


/* hw_irq( hw_counter0, overflow ); */

/* hw_irrq( hw_counter2, overflow ); */
/* hw_irrq( hw_counter0, xoverflow ); */
/* hw_irrq( hw_counter0, overflow ); */
/* hw_irrq( hw_counter0 ); */

/* hw_irrqe( hw_counter2, overflow ); */
/* hw_irrqe( hw_counter0, xoverflow ); */
/* hw_irrqe( hw_counter0, overflow ); */
/* hw_irrqe( hw_counter0 ); */

/* hw_reg( hw_counter0, ov ); */

/* hw_irrqf( hw_counter2, overflow ); */
/* hw_irrqf( hw_counter0, xoverflow ); */
/* hw_irrqf( hw_counter0, overflow ); */
/* hw_irrqf( hw_counter0 ); */

/* HW_ISSR( hw_counter2, overflow ); */
/* HW_ISSR( hw_counter0, xoverflow ); */
/* HW_ISSR( hw_counter0, overflow ); */
/* HW_ISSR( hw_counter0 ); */
/* HW_ISSR( hw_counter0, overflow, naked ); */
/* HW_ISSR( hw_counter0, naked ); */
/* HW_ISSR( hw_counter0, overflow, interruptible, naked ); */
/* HW_ISSR( hw_counter0, interruptible, naked ); */
/* HW_ISSR( hw_counter0, interruptible, naked, garb ); */

/* hwa_turn_irq( hw_pin_pcint0, on ); */
/* hwa_turn_irq( COUNTER, on ); */
/* hwa_turn_irq( COUNTER, overflow, on ); */


/* hw_irq(COUNTER, compare_a); */
/* hw_irq(COUNTER, compare_a), naked; */

/* 			  hw_irq(hw_irq(COUNTER, compare_a), naked); */

/* 			  HW_ISR2( hw_irq(COUNTER, compare_a), naked ); */
/*  			  HW_ISR2( COUNTER, compare_a, naked ); */
