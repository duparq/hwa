
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * @par Read/write bytes of EEPROM memory
 *
 * @par Test application
 *
 *      ./main.py --help
 *      ./main.py read 0 512
 *      ./main.py write 0x01F0 0x55
 *
 * @par config.h
 * @include 07-1-swuart-eeprom-read-write/config.h
 * 
 * @par main.c
 */

#include "config.h"


/*  Process received bytes. Valid sequences are:
 *
 *  'e'+al+ah+n+'\n'    Read n bytes from eeprom address al:ah
 *  'E'+al+ah+v+'\n'    Write v in eeprom at address al:ah
 */
static void process ( uint8_t byte )
{
  static uint8_t        bcount = 0 ;
  static union {
    uint8_t             buf[4] ;
    struct {
      uint8_t           cmd ;
      uint16_t          addr ;
      uint8_t           n ;
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
        hw( write, hw_eeprom0, buf.addr, buf.n );
      else {
        while ( buf.n-- ) {
          uint8_t byte = hw( read, hw_eeprom0, buf.addr );
          hw( write, UART, byte );
          buf.addr++ ;
        }
      }
      hw( write, UART, '$' );
      return ;
    }
    hw( write, UART, '!' );
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
  hwa( configure,  hw_core0,
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
     *    process incomming bytes
     */
    hw_sleep();
    if ( hw( stat,UART).rxc ) {
      /*
       *  MCU awakened by SWUART that has received a stop bit
       *  Process the received byte (clears rxc flag)
       */
      process( hw( read,UART) );
    }
  }
}
