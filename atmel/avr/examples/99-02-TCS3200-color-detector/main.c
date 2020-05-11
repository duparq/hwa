
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * TCS3200 color detector
 *
 * This is an alternate version of the 99-01-TCS3200-color-detector that uses
 * the class `_tcs3200` provided by HWA.
 *
 * @par boards/attiny84-tcs3200.h
 * @include boards/attiny84-tcs3200.h
 *
 * @par config.h
 * @include 99-02-TCS3200-color-detector/config.h
 *
 * @par main.c
 */

#include "config.h"

#if ! defined BOARD_TCS3200
#  error Incompatible board
#endif


/*  Load HWA declarations for the TCS3200
 */
#include <hwa/tcs3200.h>


/*  Create a 'sensor0' device of class _tcs3200a.
 */
#define hw_sensor0		_tcs3200, 0, 0
#define hw_sensor0_s2		PIN_TCS3200_S2
#define hw_sensor0_s3		PIN_TCS3200_S3


/*  Maximum period (minimum light level) required
 */
uint16_t		tclear_max ;


/*  A region is a structure that describes a 3D sphere in the RGB space.
 */
typedef struct {
  uint8_t	radius ;
  uint8_t	red, green, blue ;
  uint8_t	id ;
} region_t ;


/*  Data stored in EEPROM
 */
static region_t HW_MEM_EEPROM	ee_regions[16] ;
static uint16_t HW_MEM_EEPROM	ee_tclear_max ;


/*  Measure the output signal period of the sensor. As we use period ratios,
 *  clock frequency has no incidence on the final results.
 */
static uint16_t measure ( )
{
  uint16_t t ;

  /*	The datasheet says: ``The output-scaling counter registers are cleared
   *	upon the next pulse of the principal frequency after any transition of
   *	the S0, S1, S2, S3, and OE lines. The output goes high upon the next
   *	subsequent pulse of the principal frequency, beginning a new valid
   *	period.``
   */

  /*  Use the compare unit to detect a too long elapsed time for rising edge to
   *  occur
   */
  hw( write, COMPARE, hw(read, COUNTER) );
  hw( clear, (COMPARE,irq) );

  /*  Prepare to capture the date of the next rising edge
   */
  hw( configure, CAPTURE, edge, rising );
  hw( clear, (CAPTURE,irq) );

  for (;;) {
    /*
     *	Rising edge occured: continue below.
     */
    if ( hw( read, (CAPTURE,irq) ) )
      break ;

    /*
     *	Compare-match occured: signal period is too long, return.
     */
    if ( hw( read, (COMPARE,irq) ) )
      return 0xFFFF ;
  }

  t = hw( read, CAPTURE ) ;
  hw( write, COMPARE, t );
  hw( clear, (COMPARE,irq) );

  /*  Now wait for the falling edge
   */
  hw( configure, CAPTURE, edge, falling );
  hw( clear, (CAPTURE,irq) );

  for (;;) {
    if ( hw( read, (CAPTURE,irq) ) )
      /*
       *  Return the half-period
       */
      return hw( read, CAPTURE ) - t ;
    if ( hw( read, (COMPARE,irq) ) )
      /*
       *  Half-period is too long
       */
      return 0xFFFF ;
  }
}


/*  !0 if h is an hexa char '0'..'9','A'..'F'
 */
static uint8_t ishex ( uint8_t h )
{
  return (h>='0' && h<='9') || (h>='A' && h<='F') ;
}


/*  Send one hexa char on UART
 */
static void tx1h ( uint8_t n )
{
  if ( n < 10 )
    n = n + '0' ;
  else
    n = n - 10 + 'A' ;

  hw( write, UART, n );
}


/*  Send one hexa byte on UART
 */
static void tx2h ( uint8_t n )
{
  tx1h( (n>>4) & 0x0F );
  tx1h( (n>>0) & 0x0F );
}


/*  Send one hexa short on UART
 */
static void tx4h ( uint16_t n )
{
  tx2h( (n>>0) & 0xFF );
  tx2h( (n>>8) & 0xFF );
}


/*  Convert hexa char to uint8_t
 */
static uint8_t H2i ( uint8_t c )
{
  if ( c<='9' )
    return c-'0' ;
  return 10+c-'A' ;
}


/*  Convert hexa byte to uint8_t
 */
static uint8_t HH2i ( uint8_t s[] )
{
  return (H2i(s[0])<<4) + H2i(s[1]) ;
}


/*  Convert hexa short to uint16_t
 */
static uint16_t HHHH2i ( uint8_t s[] )
{
  uint16_t r = HH2i(&s[2]);
  r <<= 8 ;
  r |= HH2i(&s[0]) ;
  return r ;
}


int
main ( )
{
  hwa( begin, reset );

  hwa( configure, UART );

  /*  Capture used to compute the TCS output period
   */
  hwa( configure, CAPTURE, input, pin_icp );

  hwa( configure, PIN_TCS3200_S2, mode, digital_output );
  hwa( configure, PIN_TCS3200_S3, mode, digital_output );

  hwa( configure, PIN_OUTS, mode, digital_output );

  hwa( write, PIN_OUTS, 0 );

  hwa( commit );

  hw( enable, interrupts );

  /*  Read tclear_max from EEPROM
   */
  hw( read_bytes, eeprom0, &tclear_max, &ee_tclear_max, sizeof(tclear_max) );

  /*  Main loop
   */
  uint16_t tclear ;
  uint16_t tred	  ;
  uint16_t tgreen ;
  uint16_t tblue  ;
  uint32_t pred	  ;	// Proportion of red
  uint32_t pgreen ;	// Proportion of green
  uint32_t pblue  ;	// Proportion of blue

  for(;;) {
    uint8_t  rn ;	/* region # that owns the sample */

    /*	Sample all channels in turn
     */
    hw( configure, sensor0, filter, clear ); tclear = measure();
    hw( configure, sensor0, filter, red );   tred   = measure();
    hw( configure, sensor0, filter, green ); tgreen = measure();
    hw( configure, sensor0, filter, blue );  tblue  = measure();

    /*	A minimum light level is required to trigger region search
     */
    if ( tclear < tclear_max &&
	 tred	!= 0xFFFF &&
	 tgreen != 0xFFFF &&
	 tblue	!= 0xFFFF ) {
      /*
       *  Compute the contribution of each primary color
       *  in the range [0..255]
       */
      uint32_t tclear256 = 256 * (uint32_t)tclear ;
      pred   = (tclear256 + tred/2   ) / tred	;
      pgreen = (tclear256 + tgreen/2 ) / tgreen ;
      pblue  = (tclear256 + tblue/2  ) / tblue	;
      /*
       *  Find the region that owns the sample
       *    Compute the quadratic 3D distance
       */
      region_t r ;
      for ( rn=0 ; rn<sizeof(ee_regions)/sizeof(region_t) ; rn++ ) {
	hw( read_bytes, eeprom0, &r, &ee_regions[rn], sizeof(r) ) ;
	if ( r.radius < 0xFF ) {
	  uint16_t qp, qr, qg, qb ;
	  qp = r.radius ;
	  if (pred   > r.red)	qr=pred-r.red ;	    qr=r.red-pred ;
	  if (pgreen > r.green) qg=pgreen-r.green ; qg=r.green-pgreen ;
	  if (pblue  > r.blue)	qb=pblue-r.blue ;   qb=r.blue-pblue ;
	  qp = qp*qp ;
	  qr = qr*qr ;
	  qg = qg*qg ;
	  qb = qb*qb ;
	  if ( qr+qg+qb < qp )
	    break ;
	}
      }
      if ( rn < 16 ) {
	/*
	 *  Region found, produce the result
	 */
	hw( write, PIN_OUTS, r.id & 0x0F );
      }
      else {
	/*
	 *  No region found
	 */
	rn = 0xFF ;

	hw( write, PIN_OUTS, 0 );
      }
    }
    else {
      /*
       *  Minimum light level is not reached
       */
      rn = 0xFF ;

      pred   = 0 ;
      pgreen = 0 ;
      pblue  = 0 ;

      hw( write, PIN_OUTS, 0 );
    }

    if ( hw(stat,UART).rxc ) {
      /*
       *  Process received byte on UART
       */
      uint8_t cmd = hw( read,UART); 
      if ( cmd=='s' ) {
	/*
	 *  Return sampling data to host
	 */
	if ( tclear != 0xFFFF &&
	     tred   != 0xFFFF &&
	     tgreen != 0xFFFF &&
	     tblue  != 0xFFFF ) {
	  tx4h( tclear );
	  tx4h( tred   );
	  tx4h( tgreen );
	  tx4h( tblue  );

	  tx2h( pred   );
	  tx2h( pgreen );
	  tx2h( pblue  );

	  tx2h( rn  );
	}
	else
	  hw( write, UART, '.');
	hw( write, UART, '\n' );
      }
      else if ( cmd=='r' ) {
	/*
	 *  List regions stored in EEPROM
	 */
	for ( uint8_t i=0 ; i<sizeof(ee_regions)/sizeof(region_t) ; i++ ) {
	  region_t r ;
	  hw( read_bytes, eeprom0, &r, &ee_regions[i], sizeof(region_t) );
	  if ( r.radius != 0xFF ) {
	    tx2h(i);
	    tx2h(r.radius);
	    tx2h(r.red);
	    tx2h(r.green);
	    tx2h(r.blue);
	    tx2h(r.id);
	    hw( write, UART, '\n');
	  }
	}
      }
      else if ( cmd=='R' ) {
	/*
	 *  Store one region into EEPROM
	 */
	/*
	 *  Processing a sample can make the MCU busy for a long time compared
	 *  to communication data rate and characters may be missed if the host
	 *  sends several meanwhile. So, the host will have to wait a ' '
	 *  indicating that we're listening before it completes the command.
	 */
	hw( write,UART, ' ');
	/*
	 *  Receive the remaining of the command
	 *
	 *    0,1: region (0..15)
	 *    2,3: radius
	 *    4,5: red
	 *    6,7: green
	 *    8,9: blue
	 *    A,B: decision
	 *	   '\n'
	 */
	uint8_t cmdbuf[12] ;
	uint8_t i=0 ;
	for(;;) {
	  if ( hw(stat,UART).rxc ) {
	    uint8_t byte = hw( read,UART);
	    if (byte=='\n')
	      break ;
	    if ( !ishex(byte) )
	      i=0xFF ;
	    if ( i<sizeof(cmdbuf) )
	      cmdbuf[i++] = byte ;
	    else
	      i=0xFF ;
	  }
	}
	if ( i!=sizeof(cmdbuf) )
	  goto error ;

	/*  Command line seems valid, process it
	 */
	uint8_t rn = HH2i( &cmdbuf[0] );	// Region number
	if ( rn > 15 )
	  goto error ;

	region_t region ;
	region.radius = HH2i( &cmdbuf[2] );	// Region data
	region.red    = HH2i( &cmdbuf[4] );
	region.green  = HH2i( &cmdbuf[6] );
	region.blue   = HH2i( &cmdbuf[8] );
	region.id     = HH2i( &cmdbuf[10] );

	region_t region0 ;
	hw( read_bytes, eeprom0, &region0, &ee_regions[rn], sizeof(region) );

	/*  Update region if different
	 */
	if ( __builtin_memcmp(&region, &region0, sizeof(region_t)) )
	  hw( write_bytes, eeprom0, &ee_regions[rn], &region, sizeof(region) );

	hw( write, UART, '\n' );
      }
      else if ( cmd=='l' ) {
	/*
	 *  Return the threshold light level (maximum period on the clear
	 *  channel)
	 */
	tx4h(tclear_max);
	hw( write,UART, '\n');
      }
      else if ( cmd=='L' ) {
	/*
	 *  Store tclear_max in eeprom
	 */
	/*
	 *  Send a ' ' to indicate the host that we're now listening
	 */
	hw( write,UART, ' ');

	/*  Receive command line
	 */
	uint8_t cmdbuf[4] ;
	uint8_t i=0 ;
	for(;;) {
	  if ( hw(stat,UART).rxc ) {
	    uint8_t byte = hw( read,UART);
	    if (byte=='\n')
	      break ;
	    if ( !ishex(byte) )
	      i=0xFF ;
	    if ( i<sizeof(cmdbuf) )
	      cmdbuf[i++] = byte ;
	    else
	      i=0xFF ;
	  }
	}
	if ( i!=sizeof(cmdbuf) )
	  goto error ;

	/*  Command line seems valid, process it
	 */
	uint16_t max = HHHH2i( &cmdbuf[0] );
	if ( max != tclear_max ) {
	  tclear_max = max ;
	  hw( write_bytes, eeprom0, &ee_tclear_max, &tclear_max, sizeof(tclear_max) );
	  hw( write, UART, 'w' );
	}
	hw( write, UART, '\n' );
      }
      else if ( cmd=='\n' )
	hw( write, UART, '\n' );
      else {
      error:
	hw( write, UART, '!' );
      }
    }
  }
}

hw( configure, sensor0, filter, clear ); tclear = measure();

HW_SHOW( HW_X(sensor0) );

HW_SHOW( HW_X(sensor0,s0) );
