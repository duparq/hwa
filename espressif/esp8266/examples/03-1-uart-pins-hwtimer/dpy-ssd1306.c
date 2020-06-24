
/*  This file is part of the HWA project.
 *  Copyright (c) 2018 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

#include BOARD_H
#include "dpy.h"

#if !defined DPY_SWSPI && !defined DPY_HWSPI
#  define DPY_CS	fake
#endif

/*  Display buffer
 */
uint8_t			dpybuffer[DPY_DX*DPY_DY/8] ;
uint8_t			dpybuffer_x ;
uint8_t			dpybuffer_y ;


/*  Useful macros
 */
#define abs(x)		(x)>0 ? (x) : (-(x))
#define SIZE(x)		sizeof(x)/sizeof(*x)


/*  Display text font (stored in program memory)
 */
#define FONT_DX		5
#define FONT_DY		8

const uint8_t dpy_font[96][FONT_DX] /* ROM */ = {
  { 0x00, 0x00, 0x00, 0x00, 0x00 }, 
  { 0x00, 0x00, 0x5F, 0x00, 0x00 }, 
  { 0x00, 0x07, 0x00, 0x07, 0x00 }, 
  { 0x14, 0x7F, 0x14, 0x7F, 0x14 }, 
  { 0x24, 0x2A, 0x7F, 0x2A, 0x12 }, 
  { 0x23, 0x13, 0x08, 0x64, 0x62 }, 
  { 0x36, 0x49, 0x56, 0x20, 0x50 }, 
  { 0x00, 0x08, 0x07, 0x03, 0x00 }, 
  { 0x00, 0x1C, 0x22, 0x41, 0x00 }, 
  { 0x00, 0x41, 0x22, 0x1C, 0x00 }, 
  { 0x2A, 0x1C, 0x7F, 0x1C, 0x2A }, 
  { 0x08, 0x08, 0x3E, 0x08, 0x08 }, 
  { 0x00, 0x80, 0x70, 0x30, 0x00 }, 
  { 0x08, 0x08, 0x08, 0x08, 0x08 }, 
  { 0x00, 0x00, 0x60, 0x60, 0x00 }, 
  { 0x20, 0x10, 0x08, 0x04, 0x02 }, 
  { 0x3E, 0x51, 0x49, 0x45, 0x3E }, 
  { 0x00, 0x42, 0x7F, 0x40, 0x00 }, 
  { 0x72, 0x49, 0x49, 0x49, 0x46 }, 
  { 0x21, 0x41, 0x49, 0x4D, 0x33 }, 
  { 0x18, 0x14, 0x12, 0x7F, 0x10 }, 
  { 0x27, 0x45, 0x45, 0x45, 0x39 }, 
  { 0x3C, 0x4A, 0x49, 0x49, 0x31 }, 
  { 0x41, 0x21, 0x11, 0x09, 0x07 }, 
  { 0x36, 0x49, 0x49, 0x49, 0x36 }, 
  { 0x46, 0x49, 0x49, 0x29, 0x1E }, 
  { 0x00, 0x00, 0x14, 0x00, 0x00 }, 
  { 0x00, 0x40, 0x34, 0x00, 0x00 }, 
  { 0x00, 0x08, 0x14, 0x22, 0x41 }, 
  { 0x14, 0x14, 0x14, 0x14, 0x14 }, 
  { 0x00, 0x41, 0x22, 0x14, 0x08 }, 
  { 0x02, 0x01, 0x59, 0x09, 0x06 }, 
  { 0x3E, 0x41, 0x5D, 0x59, 0x4E }, 
  { 0x7C, 0x12, 0x11, 0x12, 0x7C }, 
  { 0x7F, 0x49, 0x49, 0x49, 0x36 }, 
  { 0x3E, 0x41, 0x41, 0x41, 0x22 }, 
  { 0x7F, 0x41, 0x41, 0x41, 0x3E }, 
  { 0x7F, 0x49, 0x49, 0x49, 0x41 }, 
  { 0x7F, 0x09, 0x09, 0x09, 0x01 }, 
  { 0x3E, 0x41, 0x41, 0x51, 0x73 }, 
  { 0x7F, 0x08, 0x08, 0x08, 0x7F }, 
  { 0x00, 0x41, 0x7F, 0x41, 0x00 }, 
  { 0x20, 0x40, 0x41, 0x3F, 0x01 }, 
  { 0x7F, 0x08, 0x14, 0x22, 0x41 }, 
  { 0x7F, 0x40, 0x40, 0x40, 0x40 }, 
  { 0x7F, 0x02, 0x1C, 0x02, 0x7F }, 
  { 0x7F, 0x04, 0x08, 0x10, 0x7F }, 
  { 0x3E, 0x41, 0x41, 0x41, 0x3E }, 
  { 0x7F, 0x09, 0x09, 0x09, 0x06 }, 
  { 0x3E, 0x41, 0x51, 0x21, 0x5E }, 
  { 0x7F, 0x09, 0x19, 0x29, 0x46 }, 
  { 0x26, 0x49, 0x49, 0x49, 0x32 }, 
  { 0x03, 0x01, 0x7F, 0x01, 0x03 }, 
  { 0x3F, 0x40, 0x40, 0x40, 0x3F }, 
  { 0x1F, 0x20, 0x40, 0x20, 0x1F }, 
  { 0x3F, 0x40, 0x38, 0x40, 0x3F }, 
  { 0x63, 0x14, 0x08, 0x14, 0x63 }, 
  { 0x03, 0x04, 0x78, 0x04, 0x03 }, 
  { 0x61, 0x59, 0x49, 0x4D, 0x43 }, 
  { 0x00, 0x7F, 0x41, 0x41, 0x41 }, 
  { 0x02, 0x04, 0x08, 0x10, 0x20 }, 
  { 0x00, 0x41, 0x41, 0x41, 0x7F }, 
  { 0x04, 0x02, 0x01, 0x02, 0x04 }, 
  { 0x40, 0x40, 0x40, 0x40, 0x40 }, 
  { 0x00, 0x03, 0x07, 0x08, 0x00 }, 
  { 0x20, 0x54, 0x54, 0x78, 0x40 }, 
  { 0x7F, 0x28, 0x44, 0x44, 0x38 }, 
  { 0x38, 0x44, 0x44, 0x44, 0x28 }, 
  { 0x38, 0x44, 0x44, 0x28, 0x7F }, 
  { 0x38, 0x54, 0x54, 0x54, 0x18 }, 
  { 0x00, 0x08, 0x7E, 0x09, 0x02 }, 
  { 0x18, 0xA4, 0xA4, 0x9C, 0x78 }, 
  { 0x7F, 0x08, 0x04, 0x04, 0x78 }, 
  { 0x00, 0x44, 0x7D, 0x40, 0x00 }, 
  { 0x20, 0x40, 0x40, 0x3D, 0x00 }, 
  { 0x7F, 0x10, 0x28, 0x44, 0x00 }, 
  { 0x00, 0x41, 0x7F, 0x40, 0x00 }, 
  { 0x7C, 0x04, 0x78, 0x04, 0x78 }, 
  { 0x7C, 0x08, 0x04, 0x04, 0x78 }, 
  { 0x38, 0x44, 0x44, 0x44, 0x38 }, 
  { 0xFC, 0x18, 0x24, 0x24, 0x18 }, 
  { 0x18, 0x24, 0x24, 0x18, 0xFC }, 
  { 0x7C, 0x08, 0x04, 0x04, 0x08 }, 
  { 0x48, 0x54, 0x54, 0x54, 0x24 }, 
  { 0x04, 0x04, 0x3F, 0x44, 0x24 }, 
  { 0x3C, 0x40, 0x40, 0x20, 0x7C }, 
  { 0x1C, 0x20, 0x40, 0x20, 0x1C }, 
  { 0x3C, 0x40, 0x30, 0x40, 0x3C }, 
  { 0x44, 0x28, 0x10, 0x28, 0x44 }, 
  { 0x4C, 0x90, 0x90, 0x90, 0x7C }, 
  { 0x44, 0x64, 0x54, 0x4C, 0x44 }, 
  { 0x00, 0x08, 0x36, 0x41, 0x00 }, 
  { 0x00, 0x00, 0x77, 0x00, 0x00 }, 
  { 0x00, 0x41, 0x36, 0x08, 0x00 }, 
  { 0x02, 0x01, 0x02, 0x04, 0x02 }, 
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
};


/*  Send one data byte to the display
 */
static IROM uint8_t dpy_data ( uint8_t data )
{
#if defined DPY_HWSPI

  /*  Hardware SPI interface
   */
  hw( write, spi0, data );
  while( !hw( read, HW_IRQFLAG(spi0) ) ) {}

#elif defined DPY_SWSPI

  /*  Software SPI interface
   */
  uint8_t changes = data ^ (data>>1);
  hw( write, DPY_D1_MOSI, 0);
  for (uint8_t bit = 0x80; bit; bit >>= 1) {
    hw( toggle, DPY_D0_CLK );			// CLK low
    if ( changes & bit )
      hw( toggle, DPY_D1_MOSI );		// data
    hw( toggle, DPY_D0_CLK );			// CLK high
  }

#elif defined DPY_TWI

  /*  TWI interface
   */
  hw( xfr_start, TWI );				// START
  while( !hw(read, HW_IRQFLAG(TWI)) ) {}	//   Wait for transmission

  hw( xfr_slaw, TWI, DPY_SLA );			// Send SLA+W
  while( !hw(read, HW_IRQFLAG(TWI)) ) {}	//   Wait for transmission

  if ( hw(stat,TWI) != HW_TWI_MT_SLA_ACK ) {	// Slave acknowledged?
    hw( xfr_stop, TWI );			//   STOP
    return 1 ;					//   Slave unreachable
  }

  hw( bus_data, TWI, 0x40 );			// Control byte (Co = 0, D/C = 1)
  while( !hw(read, HW_IRQFLAG(TWI)) ) {}	//   Wait for transmission

  hw( bus_data, TWI, data );			// Data byte
  while( !hw(read, HW_IRQFLAG(TWI)) ) {}	//   Wait for transmission

  hw( xfr_stop, TWI );				// STOP
#endif

  return 0 ;
}


/*  Send one command byte to the display.
 *
 *  There is only one master and one slave on the bus, so we do not handle
 *  arbitration and some other errors.
 */
static IROM uint8_t dpy_command ( uint8_t c )
{
#if defined DPY_SWSPI || defined DPY_HWSPI

  /*  SPI interface
   */
  hw( toggle, DPY_DC );				// DC low
  dpy_data(c);
  hw( toggle, DPY_DC );				// DC high

#elif defined DPY_TWI

  /*  TWI interface
   */
  hw( xfr_start, TWI );				// START
  while( !hw(read, HW_IRQFLAG(TWI)) ) {}	//   Wait for transmission

  hw( xfr_slaw, TWI, DPY_SLA );			// Send SLA+W
  while( !hw(read, HW_IRQFLAG(TWI)) ) {}	//   Wait for transmission

  if ( hw(stat,TWI) != HW_TWI_MT_SLA_ACK ) {	// Slave acknowledge?
    hw( xfr_stop, TWI );			//   STOP
    return 1 ;					//   Slave unreachable
  }

  hw( bus_data, TWI, 0 );			// Control byte (Co = 0, D/C = 0)
  while( !hw(read, HW_IRQFLAG(TWI)) ) {}	//   Wait for transmission

  hw( bus_data, TWI, c );			// Command byte
  while( !hw(read, HW_IRQFLAG(TWI)) ) {}	//   Wait for transmission

  hw( xfr_stop, TWI );				// STOP

#endif

  return 0 ;
}


/*  Initialize the display
 */
uint8_t IROM dpy_init ( )
{
  static const unsigned char seq[] /* ROM */ = {
    0xAE,	// Display off
    0xD5, 0x80,	// Set display clock: recommended value
    0xA8, 0x3F,	// Set multiplex
    0xD3, 0x00,	// Set display offset
    0x40,	// Zero start line
    0x8D, 0x14,	// Charge pump
    0x20, 0x00,	// Memory mode: horizontal addressing
    0xA1,	// 0xA0/0xA1 flip horizontally
    0xC8,	// 0xC0/0xC8 flip vertically
    0xDA, 0x12,	// Set comp ins
    0x81, 0x7F,	// Set contrast (0x00 to 0xFF)
    0xD9, 0xF1,	// Set pre charge  
    0xDB, 0x40,	// Set vcom detect
    0xA6,	// Normal (0xA7=Inverse)
    0xAF	// Display on
  };

  hw( toggle, DPY_CS );				// CS low

  for ( unsigned int i=0 ; i<SIZE(seq) ; i++ )
    /* if ( dpy_command( hw(read,flash0,&seq[i]) ) ) */
    if ( dpy_command(seq[i]) )
      return 1 ;

  hw( toggle, DPY_CS );				// CS high

  return 0 ;
}


/*  Send the buffer to the display
 */
void IROM dpybuffer_show ( )
{
  hw( toggle, DPY_CS );				// CS low

  /*  Set column address range
   */
  dpy_command( 0x21 );
  dpy_command( (128-DPY_DX)/2 );
  dpy_command( 63+DPY_DX/2 );

  /*  Set page address range
   */
  dpy_command( 0x22 );
  dpy_command( 8-DPY_DY/8 );
  dpy_command( 7 );

  /*  Transfer data
   */
  for ( unsigned int i=0 ; i<SIZE(dpybuffer) ; i++ )
    dpy_data( dpybuffer[i] );

  hw( toggle, DPY_CS );				// CS high
}


/*  Clear the display buffer
 */
void IROM dpybuffer_clear ( )
{
  for ( unsigned int i=0 ; i<SIZE(dpybuffer) ; i++ )
    dpybuffer[i] = 0;
}


/*  Plot point x,y into buffer
 */
void IROM dpybuffer_point ( )
{
  int page = dpybuffer_y / 8;
  int bit = dpybuffer_y & 0x07;

  dpybuffer[page*FONT_DY+dpybuffer_x] |= 1<<bit ;
}


/*  Move current plot position to x,y
 */
void IROM dpybuffer_moveto ( int x, int y )
{
  dpybuffer_x = x ;
  dpybuffer_y = y ;
}


/*  Draw a line to x,y
 */
void IROM dpybuffer_lineto ( int x, int y )
{
  int sx, sy, e2, err ;
  int dx = abs(x - dpybuffer_x);
  int dy = abs(y - dpybuffer_y);
  if ( dpybuffer_x < x ) sx = 1 ; else sx = -1 ;
  if ( dpybuffer_y < y ) sy = 1 ; else sy = -1 ;
  err = dx - dy;
  for (;;) {
    dpybuffer_point();
    if ( dpybuffer_x==x && dpybuffer_y==y ) return ;
    e2 = err<<1 ;
    if ( e2 > -dy ) {
      err = err - dy ;
      dpybuffer_x += sx ;
    }
    if ( e2 < dx ) {
      err = err + dx ;
      dpybuffer_y += sy ;
    }
  }
}


/*  Plot text char into buffer
 */
void IROM dpybuffer_putchar ( unsigned char c )
{
  c -= 32 ;
  dpybuffer_y /= FONT_DY ;
  for ( uint16_t col = 0 ; col < FONT_DX ; col++ ) {
    /* dpybuffer[dpybuffer_y*DPY_DX+dpybuffer_x++] = hw( read, flash0, &dpy_font[c][col]) ; */
    dpybuffer[dpybuffer_y*DPY_DX+dpybuffer_x++] = dpy_font[c][col] ;
    if ( dpybuffer_x >= DPY_DX ) {
      dpybuffer_x = 0 ;
      dpybuffer_y++ ;
    }
  }
  dpybuffer[dpybuffer_y*DPY_DX+dpybuffer_x++] = 0 ;
  dpybuffer_y *= FONT_DY ;
}
