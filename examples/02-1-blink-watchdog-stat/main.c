
/*	Blink a LED using the watchdog flag
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */


/*	Target				Result (hw_pin_7, 250ms)
 */
#include "targets/attiny84.h"		// 78 bytes, CRC=0x0280
//#include "targets/attiny85.h"		// 74 /8192 application bytes, CRC=0x244E
//#include "targets/nanodccduino.h"	// 168 /32768 application bytes, CRC=0x8FF8
#include <hwa.h>


/*  Define the pin at which the LED is connected (already done for Arduino
 *  targets). The target definitions also define the package of the device, then
 *  pin numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED		pin_7
#endif


int main ( )
{
  /*  Load the HWA context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Configure the watchdog to trigger an IRQ periodically
   */
  hwa_config( watchdog0,
  	      timeout,		125ms,
  	      action,		irq );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  for(;;) {
    /*
     *  Check the status of the watchdog. As soon as the IRQ flag is set, clear
     *  it and toggle the LED.
     */
    hw_stat_t( watchdog0 ) stat ;
    stat = hw_stat( watchdog0 ) ;
    if ( stat.irq ) {
      hw_clear_irq( watchdog0 );
      hw_toggle( PIN_LED );
    }
  }
    
  return 0 ;
}
