
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *      Send a '.' on TXD every 0.1s.
 *
 *      Test application: @code ./main.py -b <BAUDRATE> @endcode
 *
 *      Note: this can fail if the system frequency is not known precisely
 *      enough.
 */

#include "config.h"
#include <hwa.h>


#define BAUDRATE        115200


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
