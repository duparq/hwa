
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * TCS3200 color detector
 *
 * The microcontroller outputs a color number in binary form on 4 LED connected
 * to PIN_OUTS according to what it's has been taught previously.
 *
 * It can also communicate with the host through two host applications:
 *
 * `./tcs3200.py` to:
 *     - show status of device (threshold and regions)
 *
 *     - show real-time sampling and store samples into a file
 *
 *     - define a region in the device
 *
 *     - set the value of the maximum period (minimum light level) on the
 *	 clear channel that enables sampling (0..65535)
 *
 * `./display.py` to display (3D) the samples contained
 *		  in the provided files
 *
 * The same counter as the software uart swuart0 is used to compute the period
 * of the TCS3200 output signal.
 *
 * With S0=0 and S1=1, output frequency of the TCS is below 12 kHz, so
 * period is over 83 µs. With HW_SYSHZ=8 MHz, this gives periods >660
 * counter units. As the counter has 16 bits, the lowest period it can
 * measure is about 122 Hz. Experience shows that it is enough.
 *
 * @par boards/attiny84-tcs3200.h
 * @include boards/attiny84-tcs3200.h
 *
 * @par config.h
 * @include config.h
 */

#include "config.h"

#if ! defined BOARD_TCS3200
#  error Incompatible board
#endif


/*  Maximum period (minimum light level) required
 */
uint16_t		tclear_max ;


/*  A region is a structure that describes a 3D sphere in the RGB space
 *  and the result to produce when a RGB point is inside the sphere
 */
typedef struct {
  uint8_t	radius ;
  uint8_t	red, green, blue ;
  uint8_t	result ;  
} region_t ;


/*  Data stored in EEPROM
 */
static region_t HW_MEM_EEPROM	ee_regions[16] ;
static uint16_t HW_MEM_EEPROM	ee_tclear_max ;


/*  Measure the output signal period of the sensor on channel S3,S2 in HW_SYSHZ
 *  clock units. As we use period ratios, clock frequency has no incidence on
 *  the final results.
 */
static uint16_t measure ( uint8_t s3, uint8_t s2 )
{
  uint16_t t ;

  /*  Select the channel
   */
  hw( write, PIN_TCS3200_S3, s3!=0 );
  hw( write, PIN_TCS3200_S2, s2!=0 );

  /*	The datasheet says: ``The output-scaling counter registers are cleared
   *	upon the next pulse of the principal frequency after any transition of
   *	the S0, S1, S2, S3, and OE lines. The output goes high upon the next
   *	subsequent pulse of the principal frequency, beginning a new valid
   *	period.``
   *
   *	This is not what I've seen: the rising edge does not follow the change
   *	in S2/S3 immediately. This is not really a problem, just a little more
   *	time consuming.
   */

  /*  Prepare to capture the date of the next rising edge
   */
  hw( configure, CAPTURE, edge, rising );
  hw( clear, HW_IRQFLAG(CAPTURE) );

  /*  Use the compare unit to detect a too long elapsed time for rising edge to
   *  occur
   */
  hw( write, COMPARE, hw(read, COUNTER) );
  hw( clear, HW_IRQFLAG(COMPARE) );

  for (;;) {
    /*
     *	Rising edge occured: continue below
     */
    if ( hw( read, HW_IRQFLAG(CAPTURE) ) ) {
      t = hw( read, CAPTURE ) ;
      break ;
    }
    /*
     *	Compare-match occured: signal period is too long
     */
    if ( hw( read, HW_IRQFLAG(COMPARE) ) )
      return 0xFFFF ;
  }

  /*  Now wait for the falling edge
   */
  hw( configure, CAPTURE, edge, falling );
  hw( clear, HW_IRQFLAG(CAPTURE) );

  hw( write, COMPARE, t );
  hw( clear, HW_IRQFLAG(COMPARE) );

  for (;;) {
    if ( hw( read, HW_IRQFLAG(CAPTURE) ) )
      /*
       *  Return the half-period
       */
      return hw( read, CAPTURE ) - t ;
    if ( hw( read, HW_IRQFLAG(COMPARE) ) )
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
  hwa_begin_from_reset();

  hwa( configure, UART );

  /*  Capture used to compute the TCS output period
   */
  hwa( configure, CAPTURE,
       input,	  pin_icp,
       edge,	  rising );

  hwa( configure, PIN_TCS3200_S2, mode, digital_output );
  hwa( write, PIN_TCS3200_S2, 0 );

  hwa( configure, PIN_TCS3200_S3, mode, digital_output );
  hwa( write, PIN_TCS3200_S3, 0 );

  hwa( configure, PIN_OUTS, mode, digital_output );
  hwa( write, PIN_OUTS, 0 );

  hwa_commit();

  hw_enable_interrupts();

  /*  tclear_max is stored in EEPROM
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
    tclear = measure( 0,1 );	/* S3S2 = 01: Clear */
    tred   = measure( 0,0 );	/*	  00: Red   */
    tgreen = measure( 1,1 );	/*	  11: Green */
    tblue  = measure( 1,0 );	/*	  10: Blue  */

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
	hw( write, PIN_OUTS, r.result & 0x0F );
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
	    tx2h(r.result);
	    hw( write,UART, '\n');
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
	region.result = HH2i( &cmdbuf[10] );

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
