
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *	Synchronize the software UART
 *	Send the application '$' prompt
 *	Infinite loop:
 *	  Wait for: c + al + ah + n + '\n'
 *	  IF c=='f' THEN read n bytes from Flash address al:ah
 *        IF c=='F' THEN write n at Flash address al:ah
 *
 *	Test application: @code
 *	     ./main.py --help
 *	     ./main.py read 0 1024
 *	     ./main.py write 0x800 0x55 # BE CAREFULL OF NOT OVERWRITING THE APPLICATION OR THE BOOTLOADER! @endcode
 *
 *	Note: if you installed Diabolo, writing into the Flash memory below
 *	Diabolo will corrupt the application CRC and Diabolo will not start the
 *	application anymore after RESET (only a few 0xFF bytes above Diabolo can
 *	be modified without changing the CRC). If the application does not
 *	start, you can still dump the Flash content with:
 *
 *	@code
 *		diabolo.py --read-flash --hexdump
 *	@endcode
 */

/*  Include the configuration (includes hwa.h)
 */
#include "config.h"


/*  Process received bytes. Valid sequences are:
 *
 *  'f'+al+ah+n+'\n'	Read n bytes of eeprom from address al:ah
 *  'F'+al+ah+v+'\n'	Write v in eeprom at address al:ah
 */
static void process ( uint8_t byte )
{
  static uint8_t	bcount = 0 ;
  static union {
    uint8_t		buf[4] ;
    struct {
      uint8_t		cmd ;
      intptr_t		addr ;
      uint8_t		n ;
    } ;
  } buf ;

  /*  Buffer for one Flash page
   */
  static uint8_t	page[HW_DEVICE_FLASH_PAGE_SIZE] ;

  if ( bcount == 0 ) {
    buf.cmd = byte ;
    bcount++ ;
  } else if ( bcount < 4 )
    buf.buf[bcount++] = byte ;
  else {
    bcount = 0 ;
    if ( byte == '\n'
	 && buf.addr < HW_DEVICE_FLASH_SIZE ) {
      if ( buf.cmd == 'F' ) {
	/*
	 *  Write data
	 */
	uint8_t  zbyte = buf.addr & (HW_DEVICE_FLASH_PAGE_SIZE-1) ;
	intptr_t zpage = buf.addr & ~(HW_DEVICE_FLASH_PAGE_SIZE-1) ;

	/*  Get the content of the page to be modified and make the required
	 *  change
	 */
	hw_read_bytes( hw_flash0, page, zpage, sizeof(page) );
	page[ zbyte ] = buf.n ;

	/*  Process the reprogramming of the page. Some more checkings could be
	 *  done in order to not erase or program blank pages.
	 */
	hw_command( hw_flash0, load_page, page );
	hw_command( hw_flash0, erase_page, zpage );
	hw_command( hw_flash0, write_page, zpage );

	hw_write( UART, '$');
	return ;
      }
      else if ( buf.cmd == 'f' ) {
	/*
	 *  Read data
	 */
	while ( buf.n-- ) {
	  uint8_t byte = hw_read( hw_flash0, buf.addr++ );
	  hw_write( UART,  byte );
	}
	hw_write( UART, '$');
	return ;
      }
    }
    hw_write( UART, '!');
    return ;
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
     *    put the MCU into sleep mode, an interrupt we awake it
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
