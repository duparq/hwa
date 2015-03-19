
/*	Blink a LED using a counter overflow interrupt
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */


/*	Target				Results (pin_7, 64, loop_up, 0.5 s)
 *					   hw_counter0		hw_counter1
 *					   bytes:CRC		bytes:CRC
 */
#include "targets/attiny84.h"		// 146:0x8161		148:0x1D4A
//#include "targets/attiny85.h"		// 142:0x9B16		-
//#include "targets/nanodccduino.h"	// 222:0x1E8B		234:0x84B9
#include <hwa.h>


/*  Define the pin at which the LED is connected (already done for Arduino
 *  targets). The target definitions also define the package of the device, then
 *  pin numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED		hw_pin_7
#endif


/*  The counter
 */
#define COUNTER			hw_counter0
#define CLKDIV			64
#define COUNTMODE		loop_up
#define PERIOD			0.5


/*  Service the counter overflow IRQ
 */
HW_ISR( COUNTER, overflow )
{
  static uint8_t n ;
  n++ ;
  if ( n >= (uint8_t)(PERIOD / 2.0 / 0.001) ) {
    n = 0 ;
    hw_toggle( PIN_LED );
  }
}


int main ( )
{
  /*  Load the HWA context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa_config( hw_core0,
  	      sleep,      enabled,
  	      sleep_mode, idle );

  /*  Configure the counter to overflow every 0.001 s.
   *
   *  The compare unit `compare0` (OCRxA) is used to store the top value.
   *  Unless otherwise stated, the overflow will be automatically set to occur
   *  at top in `loop_up` counting mode, and at bottom in `loop_updown` counting
   *  mode.
   */
  hwa_config( COUNTER,
	      clock,     HW_G2(syshz_div, CLKDIV),
	      countmode, COUNTMODE,
	      bottom,    0,
	      top,       compare0
	      );
  if ( hw_streq(HW_QUOTE(COUNTMODE),"loop_updown") )
    hwa_write( hw_sub(COUNTER, compare0), 0.001 * hw_syshz / CLKDIV / 2 );
  else
    hwa_write( hw_sub(COUNTER, compare0), 0.001 * hw_syshz / CLKDIV );

  hwa_turn_irq( COUNTER, overflow, on );

  /*  Write all this into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep();
}
