
/*  This file is part of the HWA project.
 *  Copyright (c) 2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 * 
 * This example has been inspired by 'ATtiny85 Graphics Display' by David
 * Johnson-Davies http://www.technoblogy.com/show?WNM
 *
 * This is a very simplified oscilloscope. One counter is used as timer to
 * trigger ADC conversions at regular intervals.
 *
 * It can use various kinds of SSD1306-driven OLED displays through software or
 * hardware SPI interface, or I²C interface (TWI).
 *
 * @par main.c
 **/

#include BOARD_H

#define DPY_DX			64		// Display columns (64 / 128)
#define DPY_DY			48		// Display lines (48 / 64)

#if defined HW_DEVICE_ATTINYX5
#  define DPY_SPI
#  define DPY_D0_CLK		HW_PIN(5)
#  define DPY_D1_MOSI		HW_PIN(6)
#  define DPY_CS		HW_PIN(2)
#  define DPY_DC		HW_PIN(7)
#  define AIN			HW_PIN(3)
#endif

#if defined HW_DEVICE_ATTINYX4
#  define DPY_SPI
#  define DPY_D0_CLK		HW_PIN(12)
#  define DPY_D1_MOSI		HW_PIN(11)
#  define DPY_CS		HW_PIN(10)
#  define DPY_DC		HW_PIN(9)
#  define DPY_RST		HW_PIN(8)
#  define LED			HW_PIN(7)
#  define AIN			HW_PIN(13)
#endif

#if defined NANODCCDUINO
#  define AIN			PIN_ANALOG_INPUT
/*  The display is connected to the TWI of the device
 */
/* #  define DPY_I2C */
/* #  define DPY_SLA		0x78>>1		// Slave address */
/* #  define LED			PIN_LED */

/*  The display is connected to the hardware SPI of a Nanodccduino
 */
#  define DPY_SPI
#  define DPY_D0_CLK		PIN_D13		// SPI_CLK
#  define DPY_D1_MOSI		PIN_D11		// SPI_MOSI
#  define DPY_CS		PIN_D10		// SPI_SS
#  define DPY_DC		PIN_D9		//
#  define DPY_RST		PIN_D8		//
#  define LED			PIN_D7
#endif


#if !defined DPY_I2C && !defined DPY_SPI
#  error error in configuration of the display
#endif

/*  Detect if the display is connected to a hardware SPI
 */
#if defined DPY_SPI &&				\
  HW_ID(DPY_D0_CLK) == HW_ID(HW_PIN(sck)) &&	\
  HW_ID(DPY_D1_MOSI) == HW_ID(HW_PIN(mosi)) &&	\
  HW_ID(DPY_CS) == HW_ID(HW_PIN(ss))
#  define DPY_HWSPI
#endif


/*  Avoid conflict between LED and SPI CLK
 */
#if defined DPY_HWSPI && HW_ID(LED) == HW_ID(HW_PIN(sck))
#  error LED is connected to SCK
#endif


/*  The linker scripts of avr-gcc/avr-libc put the .progmem section right after
 *  the .vectors section.
 *
 *  The Diabolo bootloader starts the application by jumping to the end of the
 *  .vectors section.
 *
 *  So, we ask GCC to put ROM data in a .flashdata section and use our own
 *  linker script that puts that section after all other sections in .text.
 *
 *  See Makefiles.
 */
#define ROM		__attribute__((section(".flashdata")))
#define TOROM(s)	(__extension__({static const char _s[] ROM = s; _s;}))


/*  Useful macros
 */
#define abs(x)		(x)>0 ? (x) : (-(x))
#define SIZE(x)		sizeof(x)/sizeof(*x)


/*  Sample number
 */
static volatile uint8_t	nsamples = 0 ;


/*  Display buffer
 */
uint8_t			dpybuffer[DPY_DX*DPY_DY/8] ;
uint8_t			dpybuffer_x ;
uint8_t			dpybuffer_y ;


/*  Display text font (stored in program memory)
 */
const uint8_t dpy_font[96][5] ROM = {
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
static uint8_t dpy_data ( uint8_t data )
{
#if defined DPY_HWSPI

  /*  Hardware SPI interface
   */
  hw( write, spi0, data );
  while( !hw( read, HW_IRQFLAG(spi0) ) ) {}

#elif defined DPY_SPI

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

#elif defined DPY_I2C

  /*  TWI interface
   */
  hw( tx_start, twi0 );				// START
  while( !hw(read, HW_IRQFLAG(twi0)) ) {}	//   Wait for transmission

  hw( tx_slaw, twi0, DPY_SLA );			// Send SLA+W
  while( !hw(read, HW_IRQFLAG(twi0)) ) {}	//   Wait for transmission

  if ( hw(stat,twi0) != HW_TWI_MT_SLA_ACK ) {	// Slave acknowledged?
    hw( tx_stop, twi0 );			//   STOP
    return 1 ;					//   Slave unreachable
  }

  hw( tx_data, twi0, 0x40 );			// Control byte (Co = 0, D/C = 1)
  while( !hw(read, HW_IRQFLAG(twi0)) ) {}	//   Wait for transmission

  hw( tx_data, twi0, data );			// Data byte
  while( !hw(read, HW_IRQFLAG(twi0)) ) {}	//   Wait for transmission

  hw( tx_stop, twi0 );				// STOP

#endif

  return 0 ;
}


/*  Send one command byte to the display.
 *
 *  There is only one master and one slave on the bus, so we do not handle
 *  arbitration and some other errors.
 */
static uint8_t dpy_command ( uint8_t c )
{
#if defined DPY_SPI

  /*  SPI interface
   */
  hw( toggle, DPY_DC );				// DC low
  dpy_data(c);
  hw( toggle, DPY_DC );				// DC high

#elif defined DPY_I2C

  /*  TWI interface
   */
  hw( tx_start, twi0 );				// START
  while( !hw(read, HW_IRQFLAG(twi0)) ) {}	//   Wait for transmission

  hw( tx_slaw, twi0, DPY_SLA );			// Send SLA+W
  while( !hw(read, HW_IRQFLAG(twi0)) ) {}	//   Wait for transmission

  if ( hw(stat,twi0) != HW_TWI_MT_SLA_ACK ) {	// Slave acknowledge?
    hw( tx_stop, twi0 );			//   STOP
    return 1 ;					//   Slave unreachable
  }

  hw( tx_data, twi0, 0 );			// Control byte (Co = 0, D/C = 0)
  while( !hw(read, HW_IRQFLAG(twi0)) ) {}	//   Wait for transmission

  hw( tx_data, twi0, c );			// Command byte
  while( !hw(read, HW_IRQFLAG(twi0)) ) {}	//   Wait for transmission

  hw( tx_stop, twi0 );				// STOP

#endif

  return 0 ;
}


/*  Initialize the display
 */
static uint8_t dpy_init ( )
{
  static const unsigned char seq[] ROM = {
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

#if defined DPY_SPI
  hw( toggle, DPY_CS );				// CS low
#endif

  for ( unsigned int i=0 ; i<SIZE(seq) ; i++ )
    if ( dpy_command( hw(read,flash0,&seq[i]) ) )
      return 1 ;

#if defined DPY_SPI
  hw( toggle, DPY_CS );				// CS high
#endif

  return 0 ;
}


/*  Send the buffer to the display
 */
static void dpybuffer_show ( )
{
#if defined DPY_SPI
  hw( toggle, DPY_CS );				// CS low
#endif

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

#if defined DPY_SPI
  hw( toggle, DPY_CS );				// CS high
#endif
}


/*  Clear the display buffer
 */
static void dpybuffer_clear ( )
{
  for ( unsigned int i=0 ; i<SIZE(dpybuffer) ; i++ )
    dpybuffer[i] = 0;
}


/*  Plot point x,y into buffer
 */
static void dpybuffer_point ( int x, int y )
{
  int row = DPY_DY-1 - y ;
  int page = row / 8;
  int bit = row & 0x07;

  dpybuffer[ page*DPY_DX + x ] |= 1<<bit ;
}


/*  Move current plot position to x,y
 */
static void dpybuffer_moveto ( int x, int y )
{
  dpybuffer_x = x ;
  dpybuffer_y = y ;
}


/*  Draw a line to x,y
 */
static void dpybuffer_lineto ( int x, int y )
{
  int sx, sy, e2, err;
  int dx = abs(x - dpybuffer_x);
  int dy = abs(y - dpybuffer_y);
  if (dpybuffer_x < x) sx = 1; else sx = -1;
  if (dpybuffer_y < y) sy = 1; else sy = -1;
  err = dx - dy;
  for (;;) {
    dpybuffer_point(dpybuffer_x, dpybuffer_y);
    if (dpybuffer_x==x && dpybuffer_y==y) return;
    e2 = err<<1;
    if (e2 > -dy) {
      err = err - dy;
      dpybuffer_x += sx;
    }
    if (e2 < dx) {
      err = err + dx;
      dpybuffer_y += sy;
    }
  }
}


/*  Plot text from program memory into buffer at x,y
 */
static void dpybuffer_text ( int x, int y, const char *s )
{
  int p = (int)s;
  int page = (DPY_DY-y -1)/8;

  x += page*DPY_DX;
  for(;;) {
    char c = hw(read,flash0,p++);
    if (c == 0) return;
    for ( unsigned int col = 0 ; col<5 ; col++ )
      dpybuffer[x++] = hw( read, flash0, &dpy_font[c-32][col]) ;
    dpybuffer[x++] = 0 ;
  }
}


/*  ADC conversion completed
 */
HW_ISR( adc0 )
{
  uint8_t x = nsamples ;
  uint8_t y = hw( read, adc0, hi8 ) / 4 ;	// 0..63

  if ( x == 0 )
    dpybuffer_moveto(x, y);
  else
    dpybuffer_lineto(x, y);

  x++ ;

  /*  Stop the sampling when the last column of the display is reached.
   */
  if ( x < DPY_DX )
    /*
     *  We must clear this flag so that the next rising edge triggers the ADC
     *  again.
     */
    hw( clear, HW_IRQFLAG(counter0,compare0) );
  else
    x = 0xFF ;

  nsamples = x ;
}


int main ( )
{
  hwa_begin_from_reset();

#if defined LED
  hwa( configure, LED, direction, output );
#endif

#if defined DPY_HWSPI

  /*  Hardware SPI interface
   */
  hwa( configure, DPY_DC, direction, output );
  hwa( configure, DPY_CS, direction, output );
  hwa( write, DPY_DC, 1 );
  hwa( write, DPY_CS, 1 );

  hwa( configure,     spi0,
       function,      master,
       clock,         ioclk/4,
       idle_state,    high,
       sampling_edge, rising,
       data_order,    msb_first );

#elif defined DPY_SPI

  /*  Software SPI interface
   */
  hwa( configure, DPY_D0_CLK,  direction, output );
  hwa( configure, DPY_D1_MOSI, direction, output );
  hwa( configure, DPY_CS,   direction, output );
  hwa( configure, DPY_DC,   direction, output );
  hwa( write, DPY_DC,   1 );
  hwa( write, DPY_D0_CLK,  1 );
  hwa( write, DPY_CS,   1 );
  hwa( write, DPY_D1_MOSI, 0 );

#elif defined DPY_I2C

  /*  TWI interface (1 Mbps I²C)
   */
  hwa( configure, twi0, sclhz, 1000000 );
  hwa( configure, HW_PIN(sda),
       direction, input,
       pullup,    on );
  
#endif

#if defined DPY_RST
  hwa( configure, DPY_RST, direction, output );
  hwa( write, DPY_RST,  0 );
#endif


  /*  Generate 1 kHz compare events
   */
  hwa( configure, counter0,
       clock,     ioclk / 64,
       countmode, up_loop,
       top,       compare0 );

#if hw_syshz == 8000000
  hwa( write, counter0compare0, 125 );
#elif hw_syshz == 16000000
  hwa( write, counter0compare0, 250 );
#else
#  error could not generate 1 kHz compare events
#endif

  /*  Trigger ADC conversion on compare event.
   *  Align the result so that we can read it as a single byte (MSB).
   */
  hwa( configure, adc0,
       clock,     max,
       trigger,   counter0_compare0,
       vref,      vcc,
       align,     left,
       input,     AIN );

  hwa( turn, irq(adc0), on );

  /*  Configure the analog input
   */
  hwa( configure, AIN,
       mode,      analog,
       direction, input,
       pullup,    disabled );
  
  /*  Write configuration into hardware
   */
  hwa_commit();

#if defined DPY_RST
  /*
   *  Release the RESET pin of the display after 10 ms.
   */
  hw_waste_cycles( 0.01 * hw_syshz );
  hwa( write, DPY_RST, 1 );
  hwa_commit();
#endif

  /*  Blink LED forever if display does not initialize
   */
  if ( dpy_init() )
    for(;;){
#if defined LED
      hw( toggle, LED );
#endif
      hw_waste_cycles(0.5*hw_syshz);
    }

  dpybuffer_clear();
  hw_enable_interrupts();

  for(;;) {
    if ( nsamples == 0xFF ) {
      /*
       *  The buffer must be displayed.
       */
      nsamples = 0 ;
#if defined LED
      hw( toggle, LED );
#endif
      dpybuffer_text( 0, DPY_DY-8, TOROM("Input A0"));
      dpybuffer_show();
      dpybuffer_clear();

      /*  Clear this flag so that the next event will trigger the ADC.
       */
      hw( clear, HW_IRQFLAG(counter0,compare0) );
    }
  }
}
