
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *  Blink a LED using the watchdog IRQ
 */

#include BOARD_H


/*  Watchdog timeout
 */
#define TIMEOUT			250ms


/*  Service watchdog IRQ
 */
HW_ISR( watchdog0 )
{
  /*  Blink the LED
   */
  hw( toggle, PIN_LED );
}


int main ( )
{
  /*  Create a HWA context preloaded with RESET values to
   *  collect the hardware configuration
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa( configure, PIN_LED, direction, output );

  /*  Configure the watchdog to trigger an IRQ every TIMEOUT
   */
  hwa( configure, watchdog0,
       timeout,   TIMEOUT,
       action,    irq );

  /*  Configure the core to enter idle mode when asked to sleep
   */
  hwa( configure,  core0,
       sleep,	   enabled,
       sleep_mode, idle );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  /*  Enable interrupts
   */
  hw_enable_interrupts();

  /*  Sleep between interrupts
   */
  for(;;)
    hw_sleep();
    
  return 0 ;
}
