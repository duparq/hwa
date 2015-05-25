
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *  Blink a LED 10 times using watchdog IRQ and reset
 */


/*  Include the board definition (includes hwa.h)
 */
#include <boards/attiny84.h>


/*  The pin at which the LED is connected (already defined for Arduino
 *  boards). The target also defines the package of the device, then pin
 *  numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED               hw_pin_7
#endif


/*  Watchdog timeout
 */
#define TIMEOUT                 250ms


/*  Watchdog timeout interrupt
 *
 *    The IRQ awakes the MCU but the ISR itself does nothing. We can spare a few
 *    bytes of program memory declaring the ISR 'naked' and inserting the 'reti'
 *    instruction ourselves (otherwise avr-gcc does some register
 *    initializations even though none is used).
 */
HW_ISR( hw_wdog0, isr_naked )
{
  hw_asm("reti");
}


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Have the CPU enter power_down mode when the 'sleep' instruction is
   *  executed and make it wake up as a watchdog interrupt occurs.
   */
  hwa_config( hw_core0,
              sleep,      enabled,
              sleep_mode, power_down );

  /*  Go into sleep definitely if the watchdog triggered a reset.
   */
  if ( hw_stat( hw_core0 ).reset_by_watchdog ) {
    hwa_clear( hw_core0 );

    /*  When the device is reset by the watchdog, the watchdog remains enabled!
     */
    hwa_turn( hw_wdog0, off );
    hwa_commit();
    hw_sleep();
    for (;;)                    /* This should */
      hw_toggle( PIN_LED );     /* not happen  */
  }

  /*  Configure the watchdog to time-out every TIMEOUT (this will wake the CPU
   *  up), first setting its flag, then resetting the device unless it has been
   *  reconfigured.
   */
  hwa_config( hw_wdog0,
              timeout,      TIMEOUT,
              action,       irq_or_reset );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  /*  MCU can't awake from sleep without interrupts!
   */
  hw_enable_interrupts();

  static uint8_t count ;

  for(;;) {
    hw_sleep();

    /*  When watchdog action is 'irq_or_reset', IRQ is automatically disabled by
     *  hardware after a timeout so that next timeout will reset the device.
     */
    hwa_turn_irq( hw_wdog0, off );
    hwa_nocommit();     /* do not write the context */

    hw_toggle( PIN_LED );
    count++ ;
    if ( count < 19 ) {
      /*
       *  Re-enable the watchdog IRQ.
       */
      hwa_turn_irq( hw_wdog0, on );
      hwa_commit();
    }
  }
}
