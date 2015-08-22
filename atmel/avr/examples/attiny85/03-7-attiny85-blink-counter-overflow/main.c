
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * This example is meant to validate the porting of HWA to the Atmel AVR ATtinyX5.
 *
 * Generate a complementary PWM signal with dead time using hw_counter1.
 */

//#include <boards/attiny85.h>
#include BOARD_H
#if !defined HW_DEVICE_ATTINYX5
#  error This example does work only with ATtinyX5s
#endif

#define COUNTER			hw_counter1	// hw_counter1
#define CLOCK_SRC		system		// system | pll_32MHz | pll_64MHz
#define CLOCK_PSC		16		// power of 2 in the range 1..16384
#define PWM_HZ			20000		// frequency of generated signals
#define OUTPUT			compare0	// compare unit


#define COUNT			HW_G2(HZ,CLOCK_SRC)/CLOCK_PSC/PWM_HZ
#define HZ_system		hw_syshz
#define HZ_pll_32MHz		32000000
#define HZ_pll_64MHz		64000000


#if ( COUNT*PWM_HZ*CLOCK_PSC != HW_G2(HZ,CLOCK_SRC) )
#  error "PWM_HZ can not be achived with these settings"
#endif


int main ( )
{

  hwa_begin_from_reset();

  hwa_config( hw_rel(COUNTER, prescaler0),
  	      clock,     CLOCK_SRC
  	      );

  hwa_config( COUNTER,
              clock,     HW_G2(prescaler_output,CLOCK_PSC),
  	      countmode, loop_up,
  	      bottom,    0,
	      top,	 compare2,
  	      overflow,  at_bottom
  	      );

  hwa_write( hw_rel(COUNTER, compare2), COUNT-1 );

  hwa_config( hw_rel(COUNTER, OUTPUT),
  	      output_h,	set_at_bottom_clear_on_match,
	      output_l,	clear_at_bottom_set_on_match,
  	      );
  
  hwa_write( hw_rel(COUNTER, OUTPUT), 0.5 * COUNT );

  hwa_config( hw_rel(COUNTER, dtg0),
  	      clock_div,  4,		// 1 | 2 | 4 | 8
  	      HW_G2(OUTPUT,h), 3,	// 0..15
  	      HW_G2(OUTPUT,l), 9	// 0..15
  	      );

  //  hwa_write( COUNTER, 42 );
    //    hwa_commit();

  hwa_commit();

  for(;;) {
    /* hw_read( COUNTER ); */
    /* hw_write( COUNTER, 42 ); */
    /* hwa_write( COUNTER, hw_read(COUNTER)+1 ); */
    /* hwa_commit(); */
  }
}
