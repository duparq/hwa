
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *      Blink a LED using the watchdog IRQ
 */

/*      Target
 */
#include <targets/attiny84.h>
#include <hwa.h>


/*  The pin at which the LED is connected (already done for Arduino
 *  targets). The target also defines the package of the device, then pin
 *  numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED               hw_pin_7
#endif


/*  Service watchdog IRQ
 */
HW_ISR( hw_wdog0 )
{
  /*  Blink the LED
   */
  hw_toggle( PIN_LED );
}


int main ( )
{
  /*  Create a HWA context preloaded with RESET values to
   *  collect the hardware configuration
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Configure the watchdog to trigger an IRQ every 125ms
   */
  hwa_config( hw_wdog0,
              timeout,          125ms,
              action,           irq
              );

  /*  Configure the core to enter idle mode when asked to sleep
   */
  hwa_config( hw_core0,
              sleep,      enabled,
              sleep_mode, idle
              );

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
