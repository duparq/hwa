
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *  Blink a LED using a counter overflow interrupt
 */

/*  Include the target board (and device) definitions
 */
#include BOARD_H


/*  The counter
 */
#define COUNTER                 hw_counter0
#define CLKDIV                  64
#define COUNTMODE               loop_up
#define PERIOD                  0.5


/*  Service the counter overflow IRQ
 */
HW_ISR( COUNTER, overflow )
{
  static uint8_t n ;
  n++ ;
  if ( n >= (uint8_t)(PERIOD / 2.0 / 0.001) ) {
    n = 0 ;
    hw( toggle, PIN_LED );
  }
}


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin
   */
  hwa( config, PIN_LED, direction, output );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa( config, hw_core0,
              sleep,      enabled,
              sleep_mode, idle );

  /*  Configure the counter to overflow every 0.001 s.
   *
   *  The compare unit `compare0` (OCRxA) is used to store the top value.
   *  Unless otherwise stated, the overflow will be automatically set to occur
   *  at top in `loop_up` counting mode, and at bottom in `loop_updown` counting
   *  mode.
   */
  hwa( config, COUNTER,
              clock,     prescaler_output(CLKDIV),
              countmode, COUNTMODE,
              bottom,    0,
              top,       compare0
              );
  if ( hw_streq(HW_QUOTE(COUNTMODE),"loop_updown") )
    hwa( write, hw_rel(COUNTER, compare0), 0.5 + 0.001 * hw_syshz / CLKDIV / 2 );
  else
    hwa( write, hw_rel(COUNTER, compare0), 0.5 + 0.001 * hw_syshz / CLKDIV );

  hwa( turn, HW_IRQ(COUNTER,overflow), on );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep();
}
