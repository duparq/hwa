
/*  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *      Blink a LED using a counter compare-match flag
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


/*  The counter
 */
#define COUNTER                 hw_counter0
#define CLKDIV                  64
#define COMPARE                 compare0
#define PERIOD                  0.5


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Configure the counter to count from 0 to its max and loop
   */
  hwa_config( COUNTER,
              clock,     HW_G2(syshz_div, CLKDIV),
              countmode, loop_up,
              bottom,    0,
              top,       max,
              );

  /*  Configure the compare unit to match when 0.001 s has elapsed
   */
  hwa_write( hw_sub(COUNTER,COMPARE), 0.001 * hw_syshz / CLKDIV );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  static uint8_t n ;
  for(;;) {
    /*
     *  When a compare-match occurs, clear the counter, clear the flag and count
     *  the elapsed millisecond
     */
    if ( hw_stat(COUNTER).COMPARE ) {
      hw_clear( COUNTER );
      hw_clear_irqf( COUNTER, COMPARE );
      n++ ;
      if ( n >= (uint8_t)(PERIOD/0.001/2.0+0.5) ) {
        /*
         *  Toggle the LED when a half period has elapsed
         */
        n = 0 ;
        hw_toggle( PIN_LED );
      }
    }
  }
}
