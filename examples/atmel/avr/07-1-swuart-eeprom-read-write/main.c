
/*  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *	Read/write bytes of EEPROM memory
 *
 *	Test application:
 * @code
 *	./main.py --help
 *	./main.py read 0 512
 *	./main.py write 0x01F0 0x55
 * @endcode
 */

#include "config.h"
#include <hwa.h>


/*  Process received bytes. Valid sequences are:
 *
 *  'e'+al+ah+n+'\n'	Read n bytes from eeprom address al:ah
 *  'E'+al+ah+v+'\n'	Write v in eeprom at address al:ah
 */
static void process ( uint8_t byte )
{
  static uint8_t	bcount = 0 ;
  static union {
    uint8_t		buf[4] ;
    struct {
      uint8_t		cmd ;
      uint16_t		addr ;
      uint8_t		n ;
    } ;
  } buf ;

  if ( bcount == 0 ) {
    if ( byte == 'E' || byte == 'e' ) {
      buf.cmd = byte ;
      bcount++ ;
    }
  } else if ( bcount < 4 )
    buf.buf[bcount++] = byte ;
  else {
    bcount = 0 ;
    if ( byte == '\n'
	 && buf.addr < HW_DEVICE_EEPROM_SIZE ) {
      if ( buf.cmd == 'E' )
	hw_write( hw_eeprom0, buf.addr, buf.n );
      else {
	while ( buf.n-- ) {
	  uint8_t byte = hw_read( hw_eeprom0, buf.addr );
	  hw_write( UART, byte );
	  buf.addr++ ;
	}
      }
      hw_write( UART, '$' );
      return ;
    }
    hw_write( UART, '!' );
  }
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

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa_config( hw_core0,
  	      sleep,      enabled,
  	      sleep_mode, idle );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  /*  Wait for UART synchronization, then send the prompt
   */
  while ( !hw_stat(UART).synced )
    hw_sleep();
  hw_write( UART, '$');

  for(;;) {
    /*
     *  Main loop:
     *    put the MCU into sleep mode, an interrupt will awake it
     *    process incomming bytes
     */
    hw_sleep();
    if ( hw_stat(UART).rxc ) {
      /*
       *  MCU awakened by SWUART that has received a stop bit
       *  Get the received byte (clears rxc flag)
       */
      process( hw_read(UART) );
    }
  }
}
