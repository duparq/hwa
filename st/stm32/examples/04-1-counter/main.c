
/*  This file is part of the HWA project.
 *  Copyright (c) 2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * This program blinks a LED using a counter reload event.
 *
 * @par main.c
 */
#include BOARD_H

#define SYSHZ		(36*1000*1000)		// Desired frequency for the SYSCLK signal
#define AHBHZ		(9*1000*1000)		// Desired frequency for the core (and systick)

#define COUNTER		counter2
#define PERIOD		0.5			// Blinking period


/*  The IRQ is used only to wake the core up.
 */
HW_ISR( COUNTER )
{
  hw( write, (COUNTER,if), 0) ;
  hw( toggle, LED );
}


int main ( )
{
  hwa_begin_from_reset();

  /* Configure the PLL source and multiplier (must be done before it is enabled).
   * Prepare the connection of the sysclk to the pll. The hardware will wait for
   * the PLL to be locked before actually switching.
   */
  hwa( configure,  pll,
       source,     hsi/2,
       multiplier, SYSHZ/(HW_DEVICE_HSIHZ/2) );
  hwa( connect, sysclk, pll );
  hwa_commit();

  /*  Turn the PLL on.
   */
  hwa( turn, pll, on );
  hwa_commit();

  /* Wait for the PLL to be locked.
   */
  while ( ! hw(stat,pll).ready ) {}

  /*  Configure the AHB
   */
  hwa( configure, ahb,
       clock,     sysclk,
       prescaler, SYSHZ/AHBHZ );
  hwa_commit();

  /*  Power on the controllers we use
   */
  hwa( power, (LED1,port), on );
  hwa( power, COUNTER, on );
  hwa_commit();

  /*  Configure the GPIO pin
   */
  hwa( configure, LED1,
       mode,      digital_output,
       frequency, lowest );
  hwa_commit();

  /*  Configure the counter
   */
  /* hwa( configure, COUNTER, */
  /*      clock,     from_apb1, */
  /*      direction, up_loop, */
  /*      prescaler, (uint16_t)(0.001*AHBHZ)-1, */
  /*      reload,    (uint16_t)(PERIOD/2 / 0.001)-1 ); */

  hwa( write, (COUNTER,dir), 0 );
  hwa( write, (COUNTER,psc), (uint32_t)(0.001*AHBHZ)-1 );
  hwa( write, (COUNTER,arr), (uint32_t)(PERIOD/2 / 0.001)-1 );
  //  hwa( write, register(COUNTER,cen), 1 );
  hwa( turn, COUNTER, on );

  hwa( turn, irq(COUNTER), on );
  hwa( turn, nvic, irq(COUNTER), on );
  hwa_commit();

  /*  Toggle the LED between sleeps
   */
  uint8_t n=0;
  for(;;) {
    hw_sleep_until_irq();	// hw_sleep_until_event() is OK too.
    n++ ;
    if ( n>20 )
      //      hw( turn, nvic, irq(COUNTER), off );
      hw( power, COUNTER, off );
  }
}
