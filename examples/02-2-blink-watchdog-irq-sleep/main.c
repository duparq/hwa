
/*	Blink a LED 10 times using the watchdog IRQ
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */


/*	Target			Result (hw_pin_7, 250ms)
 *
 *	attiny84		134 bytes, CRC=0xFEF2
 *	attiny85		130 bytes, CRC=0x3858
 *	arduino_pro_mini/	
 *	  nanodccduino		232 bytes, CRC=0xC6AA
 */
#include "targets/attiny84.h"
//#include "targets/attiny85.h"
//#include "targets/nanodccduino.h"
#include <hwa.h>


/*  Define the pin at which the LED is connected (already done for Arduino
 *  targets). The target definitions also define the package of the device, then
 *  pin numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED		pin_7
#endif


/*  Watchdog timeout interrupt
 *
 *    The IRQ awakes the MCU but the ISR itself does nothing. Then we can spare
 *    a few bytes of program memory declaring the ISR 'naked' and inserting the
 *    'reti' instruction ourselves since otherwise avr-gcc does some register
 *    initializations even though none is used.
 */
HW_ISR( watchdog0, isr_naked )
{
  hw_asm("reti\n");
}


int main ( )
{
  /*  Load the HWA context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Have the CPU enter power_down mode when the 'sleep' instruction is
   *  executed and make it wake up as a watchdog interrupt occurs.
   */
  hwa_config( core0,
  	      sleep,      enabled,
  	      sleep_mode, power_down );

  /*  Go into sleep definitely if the watchdog triggered a reset.
   */
  if ( hw_stat( core0 ).reset_by_watchdog ) {
    hwa_clear( core0 );

    /*  When the device is reset by the watchdog, the watchdog remains enabled!
     */
    hwa_turn( watchdog0, off );
    hwa_commit();
    hw_sleep();
    for (;;)			/* This should */
      hw_toggle( PIN_LED );	/* not happen  */
  }

  /*  Configure the watchdog to time-out every 250 ms (this will wake the CPU
   *  up), first setting its flag, then resetting the device unless it has been
   *  reconfigured.
   */
  hwa_config( watchdog0,
  	      timeout,      250ms,
  	      action,       irq_or_reset );

  /*  Write all this into the hardware
   */
  hwa_commit();

  /*  MCU can't awake from sleep without interrupts!
   */
  hw_enable_interrupts();

  static uint8_t count ;

  for(;;) {
    hw_sleep();

    /*  When watchdog action is 'irq_or_reset', it is automatically reset by
     *	hardware to 'reset' after a time-out.
     */
    hwa_config( watchdog0,
		timeout,      250ms,
		action,       reset );
    hwa_nocommit();

    hw_toggle( PIN_LED );
    count++ ;
    if ( count < 19 ) {
      // hwa_clear_irq( hw_watchdog0 );

      /*  Set again watchdog action to 'irq_or_reset' so that the device is not
       *  reset when the next time-out occurs.
       */
      hwa_config( watchdog0,
      		  timeout,      250ms,
      		  action,       irq_or_reset );
      hwa_commit();
    }
  }
}
