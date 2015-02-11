
/*	Blink a LED at ~2 Hz for 10 times, using watchdog interrupts and sleep
 *	mode
 */

//#include "config.attiny84.h"
//#include "config.attiny85.h"
#include "config.nanodccduino.h"
#include <hwa.h>


/*  Watchdog timeout interrupt
 *
 *    The IRQ awakes the MCU but the ISR itself does nothing. Then we can spare
 *    a few bytes of program memory declaring the ISR 'naked' and inserting the
 *    'reti' instruction ourselves since otherwise avr-gcc does some register
 *    initializations even though none is used.
 */
HW_ISR( hw_watchdog0, isr_naked )
{
  hw_asm("reti\n");
}


int main ( )
{
  static uint8_t	count = 0 ;

  hwa_begin_from_reset();

  /*	Configure LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*	Have the CPU enter power_down mode when the 'sleep' instruction is
   *	executed and make it wake up as a watchdog interrupt occurs.
   */
  hwa_config( hw_core0,
  	      sleep,		enabled,
  	      sleep_mode,	power_down );

  /*	Stop the watchdog and enter sleep if the watchdog triggered a reset.
   *	Note: when the device is reset by the watchdog, the watchdog remains enabled!
   */
  if ( hw_stat( hw_core0 ).reset_by_watchdog ) {
    hwa_turn( hw_watchdog0, off );
    hwa_commit();
    hw_sleep();
    for (;;)			/* This should */
      hw_toggle( PIN_LED );	/* not happen  */
  }

  /*	Watchdog timeout and action. The IRQ is used to wake-up the CPU.
   */
  hwa_config( hw_watchdog0,
  	      timeout,      250ms,
  	      action,       irq_or_reset );

  hwa_commit();

  /*	MCU can't awake from sleep without interrupts.
   */
  hw_enable_interrupts();

  for(;;) {
    hw_sleep();
    hw_toggle( PIN_LED );
    count++ ;
    if ( count < 19 ) {
      /*
       *  WDIE is cleared by hardware after a time-out when watchdog action is
       *  set to 'irq_or_reset'. If WDIE is not set, the next time-out will
       *  trigger a reset.
       */
      /* hwa_begin(); */
      /* hwa_clear_irq( hw_watchdog0 ); */
      hwa_config( hw_watchdog0,
      		  timeout,      250ms,
      		  action,       irq_or_reset );
      hwa_commit();

      /* hwa_begin(); */
      /* hwa_write_reg( hw_watchdog0, wdie, 0 ); */
      /* hwa_nocommit(); */
      /* hwa_clear_irq( hw_watchdog0 ); */
      /* hwa_write_reg( hw_watchdog0, wdie, 1 ); */
      /* hwa_commit(); */
    }
  }

  return 0 ;
}
