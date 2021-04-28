
/*  This file is part of the HWA project.
 *  Copyright (c) 2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * This program blinks a LED after it has configured the system clock to use the
 * PLL driven by the HSE.
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

  /*  After RESET, the core is clocked at 8 MHz by the HSI RC oscillator.
   *
   *  * Start the high-speed external oscillator.
   *  * Configure the PLL source and multiplier (must be done before it is
   *    enabled).
   *  * Prepare the connection of the sysclk to the pll. The hardware waits for
   *    the clocks to be stable before switching.
   */
  hwa( power, hse, on );
  hwa( configure,  pll,
       input,      hse,
       multiplier, SYSHZ/HW_DEVICE_HSEHZ );
  hwa( connect, sysclk, pll );
  hwa( commit );

  /*  Now turn the PLL on and the hardware will use it as sysclk when the PLL is
   *  locked.
   */
  hwa( power, pll, on );
  hwa( commit );

  /*  Power the GPIO port
   */
  hwa( power, (LED1,port), on );

  /*  Configure the GPIO pin
   */
  hwa( configure, LED1,
       mode,      digital_output,
       frequency, lowest );

  hwa( commit );


  for(;;) {
    hw( toggle, LED1 );
    hw_waste_cycles( PERIOD/2 * SYSHZ );
  }
}
