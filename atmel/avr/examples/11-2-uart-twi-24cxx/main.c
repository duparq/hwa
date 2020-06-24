
/*  This file is part of the HWA project.
 *  Copyright (c) 2019 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 * 
 * This is a variation of 11-1-uart-twi-eeprom that uses the HW_24CXX() object.
 *
 * @par main.c
 **/

#include <stdio.h>
#include <stdlib.h>

#include BOARD_H

#include <hwa/ext/24cxx.h>

#define TWI			twi0

#define DEBUG 1

#define EEPROM			HW_24CXX ( interface,   TWI,	\
					   address,     0x50,	\
					   addresssize, 2,	\
					   pagesize,    8 )

HW_DECLARE(EEPROM);
HW_IMPLEMENT(EEPROM);


/*
 * Note [6]
 * Send character c down the UART Tx, wait until tx holding register
 * is empty.
 */
int
uart_putchar(char c, FILE *unused __attribute__((unused)) )
{
  if (c == '\n')
    uart_putchar('\r',0);

  while ( !hw(stat,uart0).txqnf ) {}
  hw( write, uart0, c );
  
  return 0;
}


FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

const char msg[] = "The quick brown fox jumps over the lazy dog." ;

int
main(void)
{
  uint16_t a;
  uint8_t rv;
  uint8_t b[16];
  uint8_t x;

  hwa( begin, reset );
  hwa( configure,   uart0,
       bps,	    9600,
       receiver,    disabled,
       transmitter, enabled  );
  hwa( configure, TWI, bps, 100000 );
  hwa( commit );

  stdout = &mystdout;

  for (a = 0; a < 256;) {
    printf("%#04x: ", a);
    rv = hw( read,    EEPROM,
	     address, a,
	     size,    16,
	     buffer,  b);
    if (rv < 16)
      printf("warning: short read %d\n", rv);
    a += rv;
    for (x = 0; x < rv; x++)
      printf("%02x ", b[x]);
    putchar('\n');
  }

  rv = hw( write,   EEPROM,
	   address, 55,
	   size,    sizeof(msg)/sizeof(*msg)-1,
	   buffer,  msg );
  if (rv < sizeof(msg)/sizeof(*msg)-1)
    printf("warning: short write %d\n", rv);

  printf("Wrote %d bytes.\n", rv);

  for (a = 0; a < 256;) {
    printf("%#04x: ", a);
    rv = hw( read,    EEPROM,
	     address, a,
	     size,    16,
	     buffer,  b );
    if (rv < 16)
      printf("warning: short read %d\n", rv);
    a += rv;
    for (x = 0; x < rv; x++)
      printf("%02x ", b[x]);
    putchar('\n');
  }

  printf("done.\n");
  return 0;
}
