
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *  Blink a LED using a counter overflow flag
 */

/*  Target
 */
#include BOARD_H


/*  The counter
 */
#define COUNTER                 hw_counter0
#define CLKDIV                  64
#define COUNTMODE               loop_up
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

  /*  Configure the counter to overflow every 0.001 s.
   *  The compare unit `output0` (OCxA) is used to store the top value.
   *  Unless otherwise stated, the overflow will occur at top in `loop_up`
   *  counting mode, at bottom in `loop_updown` counting mode.
   */
  hwa_config( COUNTER,
              clock,     prescaler_output(CLKDIV),
              countmode, COUNTMODE,
              bottom,    0,
              top,       compare0,
              );
  if ( hw_streq(HW_QUOTE(COUNTMODE),"loop_updown") )
    hwa_write( hw_rel(COUNTER, compare0), 0.5 + 0.001 * hw_syshz / CLKDIV / 2 );
  else
    hwa_write( hw_rel(COUNTER, compare0), 0.5 + 0.001 * hw_syshz / CLKDIV );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  static uint8_t n ;
  for(;;) {
    if ( hw_stat_irqf( COUNTER, overflow ) ) {
      hw_clear_irqf( COUNTER, overflow );
      n++ ;
      if ( n >= (uint8_t)(PERIOD / 2.0 / 0.001) ) {
        n = 0 ;
        hw_toggle( PIN_LED );
      }
    }
  }
}
