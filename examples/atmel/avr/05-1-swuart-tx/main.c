
/*	Send a '.' on TXD every 0.1s.
 *
 *	Test: ./main.py -b <BAUDRATE>
 *
 *	This can fail if the system frequency is not known precisely enough.
 *
 *	Tested to work with:
 *	  ATtiny84 rc_8MHz, 115200 bps, hw_counter0 compare0 (296:509F)
 *	                    115200 bps, hw_counter1 compare0 (296:AE62)
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */


#include "config.h"
#include <hwa.h>


#define BAUDRATE	115200


int
main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the software UART
   */
  hwa_config( hw_swuart0, baudrate, BAUDRATE );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  for(;;) {

    /*  Wait for 0.1s
     */
    hw_delay_cycles( 0.1 * hw_syshz );

    /*  Send '.'
     */
    hw_write( hw_swuart0, '.');
  }
}
