
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
@example

        A simple interface between software UART and USI configured as SPI
        master.

	Test application: `./main.py`

	The host displays the values of the registers of an nRF24L01+
	connected to USI. It should be 0x08 for the config register and
	0x3F for the EN_AA register.

@par nRF24L01+ module pinout:
@verbatim
	        Gnd  [1](2)  Vcc
	 Gnd <- CE   (3)(4)  CSN  -> 
	 SCL <- SCK  (5)(6)  MOSI -> MISO
	MOSI <- MISO (7)(8)  IRQ
@endverbatim

NOTE: pin MISO, output of the nRF, has to be connected to pin MOSI of the MCU
(considered as a slave regarding the pin names).

@par boards/attiny84.h
@include boards/attiny84.h

@par config.h
@include config.h

@par Main file
 */

/*  Include the configuration (includes hwa.h)
 */
#include "config.h"


#define USI             hw_usi0
#define NRF_CSN         hw_pin_6


/*  USI is configured as SPI master clocked by software.
 *  We then need to clock it ourselves!
 */
static void write_usi ( char c )
{
  hw_write( USI, c );
  hw_clear_irqf( USI, txc );
  do {
    hw_trigger( USI );
    // hw_delay_cycles( 50e-6 * hw_syshz );
  }
  while ( !hw_stat(USI).txc );
}


int
main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the software UART
   */
  hwa_config( UART );

  /*  Configure the USI as SPI master clocked by software
   */
  hwa_config( USI,
	      mode,  spi_master,
	      clock, software );

  /*  Configure nRF CSN pin
   */
  hwa_config( NRF_CSN, direction, output );
  hwa_write(  NRF_CSN, 1 );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  /*  Wait for UART synchronization
   */
  while ( !hw_stat(UART).synced ) {}

  /*  Process commands from host
   */
  for(;;) {

    /*  Prompt
     */
    hw_write( UART, '$' );

    /*	The host sends commands starting with '=' and followed by:
     *	  * the number of bytes to send to SPI slave (1 byte)
     *	  * the number of bytes to read (1 byte)
     *	  * the bytes to send
     */
    uint8_t c = hw_read( UART );
    if ( c == '=' ) {

      /*  Number of bytes to send to SPI slave
       */
      uint8_t ntx = hw_read( UART );
      if ( ntx < 1 || ntx > 33 )
	goto error ;

      /*  Number of bytes to send back to talker
       */
      uint8_t nrx = hw_read( UART );
      if ( nrx > 32 )
	goto error ;

      /*  Select SPI slave and send data
       */
      hw_write( NRF_CSN, 0 );
      while ( ntx-- ) {
	c = hw_read( UART );
	write_usi( c );
      }

      /*  Send reply to talker and deselect SPI slave
       */
      while ( nrx-- ) {
	write_usi( 0 );
	c = hw_read( USI );
	hw_write( UART, c );
      }
      hw_write( NRF_CSN, 1 );
    }
    else {
      /*
       *  First byte of command must be '='. Send '!' as error indicator and
       *  wait for '\n' as error aknowledgement.
       */
      do {
      error:
	hw_write( UART, '!' );
	c = hw_read( UART );
      } while ( c != '\n' ) ;
    }
  }
}
