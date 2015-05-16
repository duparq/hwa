
/*	Drive a TCS3200 color detector
 *
 *	The timer used by the SWUART is also used to compute the frequency of
 *	the output signal of the TCS3200.
 *
 *	With S0= and S1= , frequency is in the range f0..12 kHz, so period is in
 *	the range 83..t0 µs.
 *
 *	With hw_syshz = 8 MHz, this gives periods >512 counter units so we can
 *	drop last 8 bits of counting.
 *
 *	"The output-scaling counter registers are cleared upon the next pulse of
 *	the principal frequency after any transition of the S0, S1, S2, S3, and
 *	OE lines.The output goes high upon the next subsequent pulse of the
 *	principal frequency, beginning a new valid period."
 *
 *	Test: ./main.py
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */

#include "config.h"
#include <hwa.h>

#if !defined PIN_LED
#define PIN_LED		hw_pin_7
#endif

#define UART		hw_swuart0
#define TIME_COUNTER	HW_SWUART0_COUNTER
#define CAPTURE		HW_G2(TIME_COUNTER,capture0)

#define PIN_S2		hw_pin_8
#define PIN_S3		hw_pin_9


typedef union
{
  uint16_t	t ;
  struct {
    uint8_t	l ;
    uint8_t	h ;
  };
} t16_t ;


typedef union {
  uint32_t	t ;
  struct {
    t16_t	l ;
    t16_t	h ;
  };
} t32_t ;


volatile t16_t		timex ;
volatile uint32_t	values[4];
volatile uint8_t	dirties[4];


/*  Process counter overflow for time calculation
 *    Do it with asm to keep execution time as short as possible
 */
HW_ISR( TIME_COUNTER, overflow, isr_naked )
{
  hw_asm("    push	r24				\n"
	 "    push	r25				\n"
	 "    in	r25, __SREG__			\n"
	 "    push	r25				\n"
	 "    lds	r24, timex+0			\n"
	 "    sei					\n"
	 "    lds	r25, timex+1			\n"
	 "    adiw	r24, 1				\n"
	 "    sts	timex+1, r25			\n"
	 "    sts	timex+0, r24			\n"
	 "    pop	r25				\n"
	 "    out	__SREG__, r25			\n"
	 "    pop	r25				\n"
	 "    pop	r24				\n"
	 "    reti					\n"
	 );
}


/*  Capture event
 *
 *  TCS3200 outputs a square wave whose frequency is related to the intensity of
 *  light received on the selected channel.
 *
 *  Make this ISR interruptible so that software UART is not perturbated too
 *  much.
 */
HW_ISR( TIME_COUNTER, capture0, isr_interruptible )
{
  static uint8_t	channel ;
  static uint8_t	phase ;
  static uint32_t	t0 ;

  /* hw_config( CAPTURE, */
  /* 	      edge,    rising ); */

  /*  Get current time
   *
   *    Since this ISR is interruptible, we need to make sure that the time is
   *    not modified while we are reading it. A change in timex indicates that
   *    it was.
   */
  t32_t t ;
  do {
    t.l.t = hw_read_reg( TIME_COUNTER, count );
    t.h.t = timex.t ;
  }while( t.h.l != timex.l ); /* Testing low byte is enough. */

  /*  Phase 0: the first edge is discarded since it could be a glitch due to
   *           channel switching
   *  Phase 1: record date of the edge (beginning of a period)
   *  Phase 2: discard, wait one more period
   *  Phase 3: compute period duration, select next channel, reset phase
   */
  if ( phase == 1 ) {
    t0 = t.t ;
  }
  else if ( phase == 3 ) {
    /*
     *  Compute the average period for current channel
     *  Low-pass filtering does not seem to be very usefull.
     */
    //    uint32_t *v = (uint32_t*)&values[channel];	/* values are not volatile here */
    //    *v = *v - *v/4 + (t.t-t0)/2 ;		/* small low-pass filtering */
    //    values[channel] = *v ;
    values[channel] = (t.t-t0)/2 ;
    dirties[channel] = 1 ;			/* set modification flag */
    /*
     *  Select next TCS3200 channel
     */
    channel = (channel+1) & 0x03 ;
    hw_write( PIN_S2, (channel & 0x01)!=0 );
    hw_write( PIN_S3, (channel & 0x02)!=0 );
  }

  phase = (phase+1) & 0x03 ;
}


int
main ( )
{
  hwa_begin_from_reset();

  /*  Configure the software UART
   */
  hwa_config( UART );

  hwa_config( PIN_LED, direction, output );
  hwa_write( PIN_LED, 1 );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa_config( hw_core0,
  	      sleep,      enabled,
  	      sleep_mode, idle );

  /*  Counter overflow is required to compute system time
   */
  hwa_turn_irq( TIME_COUNTER, overflow, on );

  /*  Capture is used to compute TCS output period
   *  Output goes high after changing the channel, indicating a nec
   */
  hwa_config( CAPTURE,
	      input,   pin_icp,
	      edge,    rising );
  hwa_turn_irq( CAPTURE, on );

  hwa_config( PIN_S2, direction, output );
  hwa_config( PIN_S3, direction, output );
  hwa_write( PIN_S2, 0 );
  hwa_write( PIN_S3, 0 );

  /*  Write all this into hardware
   */
  hwa_commit();

  /*  Interrupt requests must be serviced for all this to work!
   */
  hw_enable_interrupts();

  /*  Wait for the UART to be synchronized
   */
  while ( !hw_stat( UART ).synced )
    hw_sleep();

  /*  Send the '$' prompt
   */
  hw_write( UART,'$');

  for(;;) {
    /*
     *  Main loop:
     *    put the MCU into sleep mode, any interrupt will wake it up
     *    process host commands
     */
    hw_sleep();
    if ( hw_stat( UART ).rxc ) {
      uint8_t byte = hw_read(UART);

      if ( byte == 't' ) {
	/*
	 *  Reply with measured periods for the 4 channels
	 */
	for ( uint8_t i=0 ; i<4 ; i++ ) {
	  uint32_t value ;
	  do {
	    dirties[i] = 0 ;			/* clear modification flag */
	    value = values[i] ;
	  } while( dirties[i] );		/* re-read if modified */

	  hw_write( UART, (value>> 0) & 0xFF );
	  hw_write( UART, (value>> 8) & 0xFF );
	  hw_write( UART, (value>>16) & 0xFF );
	  hw_write( UART, (value>>24) & 0xFF );
	}

	hw_write( UART,'$');
      }
      else
	hw_write( UART,'?');
    }
  }
}
