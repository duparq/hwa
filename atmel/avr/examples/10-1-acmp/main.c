
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * @par Turn a LED on for 1 ms each time the analog comparator output toggles.
 *
 * @par main.c
 */

#include BOARD_H


/*  The analog comparator positive input
 *    This can be `bandgap` or `hw_pin_ain0` (or synonym)
 */
#define REFERENCE		bandgap

/*  The analog comparator output edge that will trigger an IRQ
 *    This can be `falling`, `rising` or `both`
 */
#define EDGE			falling

/*  The counter used to produce the LED pulse
 */
#define COUNTER			counter0
#define COUNTER_CLK_DIV		64
#define COMPARE			compare0

/*  The time the LED is turned on in seconds
 */
#define ON_TIME			0.001

/*  The time the LED is turned on in counter units
 */
#define ON_TIME_COUNT		ON_TIME * hw_syshz / COUNTER_CLK_DIV


/*  Service counter-compare0 IRQ:
 *    disable this IRQ
 *    turn the LED off
 *    turn analog comparator IRQ on
 */
HW_ISR( COUNTER, COMPARE )
{
  hw( turn, HW_IRQ(COUNTER,COMPARE), off );
  hw( write, PIN_LED, 0 );
  hw( clear, HW_IRQF(acmp0) );
  hw( turn, HW_IRQ(acmp0), on );
}


/*  Service analog comparator interrupt:
 *    disable this IRQ off
 *    turn the LED on
 *    program a compare-match IRQ to occur in 1ms.
 *	(maybe reset the prescaler)
 */
HW_ISR( acmp0 )
{
  hw( turn, HW_IRQ(acmp0), off );
  hw( write, PIN_LED, 1 );

  if ( COUNTER_CLK_DIV > 1 )
    hw( turn, HW_RELATIVE(COUNTER,prescaler0), off );

  hw( write, COUNTER, 0 );

  if ( COUNTER_CLK_DIV > 1 )
    hw( turn,HW_RELATIVE(COUNTER,prescaler0), on);

  hw( clear, HW_IRQF(COUNTER,COMPARE) );
  hw( turn, HW_IRQ(COUNTER,COMPARE), on );
}


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa( configure,  core0,
       sleep,      enabled,
       sleep_mode, idle );

  /*  Configure LED pin
   */
  hwa( configure, PIN_LED, direction, output );

  /*  If REFERENCE is a pin, configure it in analog mode (disable its digital
   *  input buffer)
   */
#if HW_ID( REFERENCE )
  hwa( configure, REFERENCE,
       mode,      analog,
       direction, input );
#endif

  /*  Configure INPUT_NEG pin in analog mode (disable digital input buffer)
   */
  hwa( configure, PIN_ANALOG_INPUT,
       mode,      analog,
       direction, input );

  /*  Check that the counter can handle the ON_TIME value. This must be done
   *  here since the C preprocessor does not allow floats in expressions.
   */
  if ( ON_TIME_COUNT > ((1UL<<HW_BITS(COUNTER))-1) )
    HWA_ERR("COUNTER can not afford ON_TIME.") ;

  /*  Configure the counter to count from 0 to max
   */
  hwa( configure, COUNTER,
       clock,     prescaler_output(COUNTER_CLK_DIV),
       countmode, up_loop );

  /*  Prepare the compare value for the PIN_LED pulse
   */
  hwa( write, HW_RELATIVE(COUNTER,COMPARE), ON_TIME_COUNT );

  /*  Configure the analog comparator
   */
  hwa( configure,      acmp0,
       edge,	       EDGE,
       positive_input, REFERENCE,
       negative_input, PIN_ANALOG_INPUT );

  hwa( turn, HW_IRQ(acmp0), on );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep();

  return 0 ;
}
