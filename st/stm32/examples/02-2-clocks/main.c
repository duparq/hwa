
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

  /*  After RESET, the core is clocked at 8 MHz by the HSI RC oscillator.
   *
   *  * Start the high-speed external oscillator.
   *  * Configure the PLL source and multiplier (must be done before it is
   *    enabled).
   *  * Prepare the connection of the sysclk to the pll. The hardware waits for
   *    the clocks to be stable before switching.
   *
   *  Alternately, we could check ourselves the clocks:
   *    while ( !hw(stat,hse).ready ) {} : waits for the HSE to be stable.
   *    while ( !hw(stat,pll).ready ) {} : waits for the PLL to be locked.
   */
  hwa( power, hse, on );

  hwa( connect, pll, hse/2 );

  hwa( write, pll, (SYSHZ / HW_DEVICE_HSEHZ) );
  hwa( connect, sysclk, pll );
  hwa_commit();

  /*  Now turn the PLL on and the hardware will use it as SYSCLK when the PLL is
   *  locked.
   */
  hwa( turn, pll, on );
  hwa_commit();

  /*  Power the GPIO port
   */
  hwa( power, HW_RELATIVE(PIN_LED1,port), on );

  /*  Configure the GPIO pin
   */
  hwa( configure, PIN_LED1,
       mode,      digital,
       direction, output,
       frequency, 50MHz );

  hwa( write, ahbprescaler, SYSHZ / COREHZ );

  hwa_commit();


  for(;;) {
    hw( toggle, PIN_LED1 );
    hw_waste_cycles( PERIOD/2 * COREHZ );
  }
}
