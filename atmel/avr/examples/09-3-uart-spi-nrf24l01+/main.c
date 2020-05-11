
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015,2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 * 
 * @par A simple interface between UART and SPI master connected to a nRF24L01
 * 
 * @par nRF24L01+ module wiring
 *
 *                   Gnd  [1](2)  Vcc
 *            Gnd <- CE   (3)(4)  CSN  -> SS
 *            SCL <- SCK  (5)(6)  MOSI -> MOSI
 *           MISO <- MISO (7)(8)  IRQ
 *
 * @par Test application
 *
 *     ./main.py
 * 
 * should display:
 *
 *     Register CONFIG    : 0x00 = 08
 *     Register EN_AA     : 0x01 = 3F
 *     Register EN_RX_ADDR: 0x02 = 03
 *     Register SETUP_AW  : 0x03 = 03
 *     Register SETUP_RETR: 0x04 = 03
 *     Register RF_CH     : 0x05 = 02
 *     Register RF_SETUP  : 0x06 = 0F
 *     Register STATUS    : 0x07 = 0E
 *     Register RX_ADDR_P0: 0x0A = E7 E7 E7 E7 E7
 *     Register RX_ADDR_P1: 0x0B = C2 C2 C2 C2 C2
 *     Register DYNPD     : 0x1C = 00
 *     Register FEATURE   : 0x1D = 00
 * 
 * * `BOARD_H` is the name of the target board header file. It can be defined at
 * compile time via the command line. For example, `make BOARD=nanodccduino`
 * will define `BOARD_H` as `<boards/nanodccduino.h>`. See @ref atmelavr_boards for the
 * board definitions provided with HWA.
 * 
 * @par main.c
 **/

#include BOARD_H

#if defined ARDUINO
/*
 *  If a pin other than PIN_SS is used, and PIN_SS is an input, it must be held
 *  high otherwise the SPI will be automatically turned into slave mode by
 *  hardware as soon as PIN_SS goes low.
 */
#  define NRF_CSN	PIN_SS
#else
#  error That should not happen
#endif

#define UART		uart0


/*  Transfer 1 byte on the SPI.
 *  This is used for reading as well as for writing.
 *  Return the received byte.
 */
uint8_t spi ( uint8_t v )
{
  hw( write, spi0, v );
  while( !hw( read, (spi0,irq) ) ) {}
  return hw( read, spi0 );
}


/*  Wait for one byte received on the UART and read it.
 */
uint8_t uart_rx()
{
  while ( !hw( read, (UART,irq,rxc) ) ) {}
  return hw( read, UART );
}


/*  Wait until the transmit buffer of the UART is not full, then write one byte
 *  into it.
 */
void uart_tx( uint8_t c )
{
  while ( !hw( read, (UART,irq,txqnf) ) ) {}
  hw( write, UART, c );
}


int
main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa( begin, reset );

  /*  Configure the software UART
   */
  hwa( configure, UART,
       bps,	  115200 );

  /*  Configure the SPI as master
   */
  hwa( configure,     spi0,
       function,      master,
       clock,	      ioclk / 128,
       /* mode,          0, */
       idle_state,    low,
       sampling_edge, rising,
       data_order,    msb_first );

  /*  Configure nRF CSN pin
   */
  hwa( configure, NRF_CSN, mode, digital_output );
  hwa( write, NRF_CSN, 1 );

  /*  Write this configuration into the hardware
   */
  hwa( commit );

  /*  Process commands from host
   */
  for(;;) {

    /*	Prompt
     */
    uart_tx( '$' );

    /*	The host sends commands starting with '=' and followed by:
     *	  * the number of bytes to send to SPI slave (1 byte)
     *	  * the number of bytes to read (1 byte)
     *	  * the bytes to send
     */
    uint8_t c = uart_rx();
    if ( c == '=' ) {

      /*  Number of bytes to send to SPI slave
       */
      uint8_t ntx = uart_rx();
      if ( ntx < 1 || ntx > 33 )
	goto error ;

      /*  Number of bytes to send back to talker
       */
      uint8_t nrx = uart_rx();
      if ( nrx > 32 )
	goto error ;

      /*  Select SPI slave and send data
       */
      hw( write, NRF_CSN, 0 );
      while ( ntx-- ) {
	c = uart_rx();
	spi( c );
      }

      /*  Send reply to host and deselect SPI slave
       */
      while ( nrx-- ) {
	c = spi(0);
	uart_tx(c);
      }
      hw( write, NRF_CSN, 1 );
    }
    else {
      /*
       *  First byte of command must be '='. Send '!' as error indicator and
       *  wait for '\n' as error acknowledgement.
       */
      do {
      error:
	uart_tx('!');
	c = uart_rx();
      } while ( c != '\n' ) ;
    }
  }
}
