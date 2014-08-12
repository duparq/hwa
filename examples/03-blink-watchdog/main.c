
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
 *    initializations even though none is used.
 */
HW_ISR( hw_watchdog0, naked )
{
  __asm__ __volatile__("reti"	"\n\t" ::: );
}


int main ( )
{
  hwa_begin_from_reset();

  hwa_config( LED_PIN, output );
  hwa_write(  LED_PIN, 0 );

  /*	Have the CPU enter power_down mode when the 'sleep' instruction is
   *	executed.
   */
  hwa_config( hw_core0, sleep_mode, power_down );

  /*	Watchdog timeout and action. The IRQ is used to wake-up the CPU.
   */
  hwa_config( hw_watchdog0,
	      timeout,		64ms,
	      action,		irq );

  /*	Power-off unused peripherals.
   */
  hwa_turn( hw_counter0, off );
  hwa_turn( hw_counter1, off );
  hwa_turn( hw_usi0,     off );
  hwa_turn( hw_adc0,     off );

  hwa_commit();

  hw_enable_interrupts();

  /*	Toggle the LED each time the CPU will enter sleep mode. After the 20th
   *	time it awakes, disable the watchdog interrupt so that the CPU will
   *	never wake-up again.
   */
  for( uint8_t count = 0 ;; ) {
    hw_toggle( LED_PIN );
    hw_sleep_until_irq();
    count++ ;
    if ( count == 20 ) {
      hwa_config( hw_watchdog0, action,	none ); /* Reuse the HWA cache created above */
      hwa_commit();
      //      hw_config( hw_watchdog0, action,	none );
    }
  }

  return 0 ;
}
