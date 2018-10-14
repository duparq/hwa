
/*  This file is part of the HWA project.
 *  Copyright (c) 2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * This program:
 *  * Starts the high-speed external oscillator.
 *  * Configures the PLL source and multiplier.
 *  * Connects the SYSCLK to the PLL.
 *  * Enables the LED port.
 *  * Configures the LED pin as a digital output.
 *  * Toggles the LED in an infinite loop.
 *
 * @par main.c
 */
#include BOARD_H

#define SYSHZ		72e6	// Desired frequency for the SYSCLK signal
#define COREHZ		9e6	// Desired frequency for the core

#define PERIOD		0.5	// Blinking period


int main ( )
{
  hwa_begin_from_reset();

  /*  Start the high-speed external oscillator.
   */
  hwa( power, hse, on );

  /* Configure the PLL source and multiplier (must be done before it is enabled).
   */
  hwa( configure,  pll,
       source,     hse/2,
       multiplier, SYSHZ/HW_DEVICE_HSEHZ );

  /* Prepare the connection of the sysclk to the pll. The hardware will wait for
   * the PLL to be locked before actually switching.
   */
  hwa( connect, sysclk, pll );
  hwa_commit();

  /*  Turn the PLL on.
   */
  hwa( turn, pll, on );
  hwa_commit();

  /* Wait for the PLL to be locked.
   */
  while ( ! hw(stat,pll).ready ) {}

  /* Now that the SYSCLK is driven by the PLL, the HSI can be stopped.
   */
  hwa( power, hsi, off );

  /*  Configure the AHB
   */
  hwa( configure, ahb,
       clock,     sysclk,
       prescaler, SYSHZ/COREHZ );
  hwa_commit();

  /*  Configure the GPIO pin
   */
  hwa( power, (LED1,port), on );
  hwa_commit();

  hwa( configure, LED1,
       mode,      digital_output,
       frequency, lowest );
  hwa_commit();

  /*  Wait for the HSI to actually stop.
   */
  while ( hw(stat,hsi).ready ) {}

  for(;;) {
    hw( toggle, LED1 );
    hw_waste_cycles( PERIOD*COREHZ/2 );
  }
}
