
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 * 
 * @par A simple interface between UART and TWI
 * 
 * ~/dev/carspy/old/damnon/old/0.6.1/firmware/twm.c
 *
 * @par main.c
 **/

#include BOARD_H

#define UART	hw_uart0
#define TWI	hw_twi0


int
main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the software UART
   */
  /* hwa_config( UART, */
  /* 	      bps,  115200 ); */

  /*  Configure the TWI
   */
  hwa_config( TWI,
	      sclhz,         100000,
	      slave_address, 0x40
	      );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  hw_command( TWI, start, irq );
  hw_command( TWI, slaw, 19, irq );
  hw_command( TWI, write, 20, irq );
  hw_command( TWI, stop, irq );

  if ( hw_stat(TWI) == HW_TWI_START )
    *(volatile uint8_t*)0 = 1;
  else
    *(volatile uint8_t*)0 = 0;

  /*  Process commands from host
   */
  for(;;) {

    /*	Prompt
     */
    /* hw_write( UART, '$' ); */

    /*	The host sends commands starting with '=' and followed by:
     *	  * the number of bytes to send to SPI slave (1 byte)
     *	  * the number of bytes to read (1 byte)
     *	  * the bytes to send
     */
    /* hw_read( UART ); */
  }
}
