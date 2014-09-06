
/*	A simple interface between software UART and USI as SPI master.
 *
 *	The talker displays the values of the registers of an nRF24L01+
 *	connected to USI.
 *
 *	Try it: ./talker.py
 *
 *	The talker sends commands starting with '=' and followed by:
 *	  * the number of bytes to send to SPI slave (1 byte)
 *	  * the number of bytes to read (1 byte)
 *	  * the bytes to send
 */

#include "config.h"
#include <hwa.h>
#include <swuart-src.h>


int
main ( )
{
  /*  Configure the hardware
   */
  hwa_begin_from_reset();

  swuart_configure(hwa);

  hwa_config( SPI );

  hwa_config( NRF_CE,  output );
  hwa_write(  NRF_CE,  0 );
  hwa_config( NRF_CSN, output );
  hwa_write(  NRF_CSN, 1 );

  hwa_commit();

  /*  Synchronize SWUART
   */
  swuart_set_dt( swuart_sync_10_1() );
  swuart_wait_rxidle(20);

  /*  Enable SWUART reception
   */
  hw_enable_interrupts();
  swuart_enable_rx();

  /*  Process commands from talker
   */
  for(;;) {

    /*  Prompt
     */
    swuart_putbyte('#');

    /*  Get command
     */
    uint8_t c = swuart_getbyte();
    if ( c == '=' ) {

      /*  Number of bytes to send to SPI slave
       */
      uint8_t ntx = swuart_getbyte();
      if ( ntx < 1 || ntx > 33 )
	goto error ;

      /*  Number of bytes to send back to talker
       */
      uint8_t nrx = swuart_getbyte();
      if ( nrx > 32 )
	goto error ;

      /*  Select SPI slave and send data
       */
      hw_write( NRF_CSN, 0 );
      while ( ntx-- ) {
	c = swuart_getbyte();
	hw_write( SPI, c );
      }

      /*  Send reply to talker and deselect SPI slave
       */
      while ( nrx-- ) {
	hw_write( SPI, 0 );
	c = hw_read( SPI );
	swuart_putbyte( c );
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
	swuart_putbyte( '!' );
	c = swuart_getbyte();
      } while ( c != '\n' ) ;
    }
  }
}
