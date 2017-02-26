
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * @par Process read/write commands on the Flash memory.
 *
 * Algorithm:
 *
 *     Synchronize the software UART.
 *     Send the applicapion '$' prompt
 *     Infinite loop:
 *       Wait for: c + al + ah + n + '\n'
 *       IF c=='f' THEN read n bytes from Flash address al:ah
 *       IF c=='F' THEN write n at Flash address al:ah
 *
 * @par Test applicapion
 *
 *      ./main.py --help
 *      ./main.py read 0 1024
 *      ./main.py write 0x800 0x55 # BE CAREFULL OF NOT OVERWRITING THE APPLICATION OR THE BOOTLOADER!
 *  Note: if you have Diabolo installed, writing into the Flash memory below
 *  Diabolo will corrupt the applicapion CRC and Diabolo will not start the
 *  applicapion anymore after RESET. Oonly a few 0xFF bytes above Diabolo can be
 *  modified without changing the CRC. If the applicapion does not start, you
 *  can still dump the Flash content with:
 *
 *      diabolo.py --read-flash --hexdump
 *
 *  FIXME: the Diabolo host applicapion should help repairing the CRC.
 *
 * @par config.h
 * @include 08-1-swuart-flash-read-write/config.h
 * 
 * @par main.c
 */

#include "config.h"


/*  Process received bytes. Valid sequences are:
 *
 *  'f'+al+ah+n+'\n'    Read n bytes of Flash from address al:ah
 *  'F'+al+ah+v+'\n'    Write v in Flash at address al:ah
 */
static void process ( uint8_t byte )
{
  static uint8_t        bcount = 0 ;
  static union {
    uint8_t             buf[4] ;
    struct {
      uint8_t           cmd ;
      //      intptr_t          addr ;
      uint16_t          addr ;
      uint8_t           n ;
    } ;
  } buf ;

  /*  Buffer for one Flash page
   */
  static uint8_t        page[HW_DEVICE_FLASH_PAGE_SIZE] ;

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
        hw( read_bytes, flash0, page, zpage, sizeof(page) );
        page[ zbyte ] = buf.n ;

        /*  Process the reprogramming of the page. Some more checkings could be
         *  done in order to not erase or program blank pages.
         */
        hw( load_buffer, flash0, page );
        hw( erase_page,  flash0, zpage );
        hw( write_page,  flash0, zpage );

        hw( write, UART, '$');
        return ;
      }
      else if ( buf.cmd == 'f' ) {
        /*
         *  Read data
         */
        while ( buf.n-- ) {
          uint8_t byte = hw( read, flash0, buf.addr++ );
          hw( write, UART,  byte );
        }
        hw( write, UART, '$');
        return ;
      }
    }
    hw( write, UART, '!');
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
  hwa( configure, UART );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa( configure,  core0,
       sleep,      enabled,
       sleep_mode, idle );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  /*  Wait for UART synchronization, then send the prompt
   */
  while ( !hw( stat,UART).sync )
    hw_sleep();
  hw( write, UART, '$');

  for(;;) {
    /*
     *  Main loop:
     *    put the MCU into sleep mode, an interrupt will awake it
     */
    hw_sleep();
    if ( hw( stat,UART).rxc ) {
      /*
       *  MCU awakened by SWUART that has received a stop bit
       *  Get the received byte (clears rxc flag)
       */
      process( hw( read,UART) );
    }
  }
}
