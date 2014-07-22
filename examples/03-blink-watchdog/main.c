
/*	Blink a LED using the watchdog timeout interrupt. Demonstrate some power
 *	management too.
 */

#define HWA_DEVICE		attiny84
#define HWA_DEVICE_PACKAGE	dil

#define	LED_PIN			hw_pin_5

#include <hwa.h>


/*  Watchdog timeout interrupt
 *
 *    The IRQ awakes the MCU but the ISR itself does nothing. Then we can spare
 *    a few bytes of program memory declaring the ISR 'naked' and inserting the
 *    'reti' instruction ourselves since otherwise avr-gcc does some register
 *    initializations even if none is used.
 */
HW_ISR( hw_irq(hw_watchdog0), naked )
{
  __asm__ __volatile__("reti"	"\n\t" ::: );
}


int main ( )
{
  hwa_begin_from_reset();

  hwa_config( LED_PIN, output );
  hwa_write(  LED_PIN, 0 );

  hwa_config( hw_core0,
	      sleep_mode,	power_down );

  hwa_config( hw_watchdog0,
	      timeout,		64ms,
	      action,		irq );

  hwa_turn( hw_counter0,	off );
  hwa_turn( hw_counter1,	off );
  hwa_turn( hw_usi0,		off );
  hwa_turn( hw_adc0,		off );

  hwa_commit();

  hw_enable_interrupts();

  uint8_t count = 0 ;

  for(;;) {
    hw_toggle( LED_PIN );
    hw_sleep_until_irq();
    count++ ;
    if ( count == 20 ) {
      hwa_config( hw_watchdog0, action,	none );
      hwa_commit();
    }
  }

  return 0 ;
}
