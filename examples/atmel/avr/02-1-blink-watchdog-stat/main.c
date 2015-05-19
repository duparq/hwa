
/*	Blink a LED using the watchdog flag
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/*	Target
 */
#include "targets/attiny84.h"		// 78 bytes
//#include "targets/attiny85.h"		// 74 /8192 application bytes, CRC=0x244E
//#include "targets/nanodccduino.h"	// 168 /32768 application bytes, CRC=0x8FF8
#include <hwa.h>


/*  The pin at which the LED is connected (already done for Arduino
 *  targets). The target also defines the package of the device, then pin
 *  numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED		hw_pin_7
#endif


/*  Watchdog timeout
 */
#define TIMEOUT			250ms


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Configure the watchdog to trigger an IRQ periodically
   */
  hwa_config( hw_wdog0,
  	      timeout,		TIMEOUT,
  	      action,		irq );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  for(;;) {
    /*
     *  Check the status of the watchdog. As soon as the IRQ flag is set, clear
     *  it and toggle the LED.
     */
    hw_stat_t( hw_wdog0 ) stat ;
    stat = hw_stat( hw_wdog0 ) ;
    if ( stat.irq ) {
      hw_clear_irq( hw_wdog0 );
      hw_toggle( PIN_LED );
    }
  }
    
  return 0 ;
}
