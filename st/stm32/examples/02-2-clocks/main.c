
/*  This file is part of the HWA project.
 *  Copyright (c) 2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * This program:
 *  * Starts the high-speed external oscillator (HSE).
 *  * Configures the PLL source and multiplier.
 *  * Connects the SYSCLK to the PLL.
 *  * Configures the AHB prescaler.
 *  * Enables the LED port.
 *  * Configures the LED pin as a digital output.
 *  * Stops the high-speed internal oscillator (HSI).
 *  * Toggles the LED in an infinite loop.
 *
 * @par main.c
 */
#include BOARD_H

#define SYSHZ		(36*1000*1000)	// Desired frequency for the SYSCLK signal
#define AHBHZ		(9*1000*1000)	// Desired frequency for the core (and systick)

#define PERIOD		0.5		// Blinking period


int main ( )
{
  hwa( begin, reset );

  /*  Start the high-speed external oscillator.
   */
  hwa( power, hse, on );

  /* Configure the PLL source and multiplier (must be done before it is enabled).
   */
  hwa( configure,  pll,
       input,      hse/2,
       multiplier, SYSHZ/HW_DEVICE_HSEHZ );

  /* Prepare the connection of the sysclk to the pll. The hardware will wait for
   * the PLL to be locked before actually switching.
   */
  hwa( connect, sysclk, pll );
  hwa( commit );

  /*  Turn the PLL on.
   */
  hwa( power, pll, on );
  hwa( commit );

  /* Wait for the PLL to be locked.
   */
  while ( ! hw(stat,pll).ready ) {}

  /* Now that the SYSCLK is driven by the PLL, the HSI can be stopped.
   */
  hwa( power, hsi, off );

  /*  Configure the AHB
   */
  hwa( clock, ahb, sysclk / (SYSHZ/AHBHZ) );

  hwa( commit );

  /*  Configure the GPIO pin
   */
  hwa( power, (LED1,port), on );
  hwa( commit );

  hwa( configure, LED1,
       mode,      digital_output,
       frequency, lowest );
  hwa( commit );

  /*  Wait for the HSI to actually stop.
   */
  while ( hw(stat,hsi).ready ) {}

  for(;;) {
    hw( toggle, LED1 );
    hw_waste_cycles( PERIOD*AHBHZ/2 );
  }
}
