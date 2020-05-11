
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *  Blink a LED 10 times using the watchdog "IRQ or reset" mode.
 *
 *  FIXME: once the device goes into sleeping mode with , hardware reset does not
 *  awake it. Only a power-off/power-on cycle does wake it up.
 */


/*  Set a default target board
 */
#include BOARD_H


/*  Watchdog timeout
 */
#define TIMEOUT			250ms


/*  Watchdog timeout interrupt
 *
 *    The IRQ awakes the MCU but the ISR itself does nothing. We can spare a few
 *    bytes of program memory declaring the ISR 'naked' and inserting the 'reti'
 *    instruction ourselves (otherwise avr-gcc does some register
 *    initializations even though none is used).
 */
HW_ISR( (watchdog0,irq), naked )
{
  hw_asm("reti");
}


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa( begin, reset );

  /*  Configure the LED pin
   */
  hwa( configure, PIN_LED, mode, digital_output );

  /*  Have the CPU enter power_down mode when the 'sleep' instruction is
   *  executed and make it wake up as a watchdog interrupt occurs.
   */
  hwa( configure, core0,
       sleep,	  enabled,
       sleep_mode, power_down );

  /*  Go into sleep definitely if the watchdog triggered a reset.
   */
  if ( hw(stat,core0).reset_by_watchdog ) {
    hwa( clear, core0 );

    /*	When the device is reset by the watchdog, the watchdog remains enabled
     *	so we must stop it.
     */
    hwa( turn, watchdog0, off );
    hwa( commit );
    hw( wait, irq );
    for (;;)			/* This should */
      hw( toggle, PIN_LED );	/* not happen  */
  }

  /*  Configure the watchdog to time-out every TIMEOUT (this will wake the CPU
   *  up), setting its flag the first time, resetting the device the second time
   *  if it has been reconfigured.
   */
  hwa( configure, watchdog0,
       timeout,	  TIMEOUT,
       action,	  irq_or_reset );

  /*  Write this configuration into the hardware
   */
  hwa( commit );

  /*  MCU can't awake from sleep without interrupts!
   */
  hw( enable, interrupts );

  static uint8_t count ;

  for(;;) {
    hw( wait, irq );

    /*	When watchdog action is 'irq_or_reset', a timeout automatically disables
     *	the IRQ so that next timeout will reset the device. Load the context
     *	with this information, but do not write it into hardware.
     */
    hwa( disable, (watchdog0,irq) );
    hwa( nocommit );

    hw( toggle, PIN_LED );
    count++ ;
    if ( count < 19 ) {
      /*
       *  Re-enable the watchdog IRQ.
       */
      hwa( enable, (watchdog0,irq) );
      hwa( commit );
    }
  }
}
