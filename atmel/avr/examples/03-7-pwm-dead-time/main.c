
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * This example is meant to validate the porting of HWA to the Atmel AVR ATtinyX5.
 *
 * Generate a complementary PWM signal with dead time using counter1.
 */

#include BOARD_H
#if !defined HW_DEVICE_ATTINYX5
#  error This example does work only with ATtinyX5s
#endif

#define COUNTER			counter1	// counter1
#define CLOCK_SRC		ioclk		// ioclk | pll_32MHz | pll_64MHz
#define CLOCK_PSC		16		// power of 2 in the range 1..16384
#define PWM_HZ			20000		// frequency of generated signals
#define OUTPUT			compare0	// compare unit

#define COUNT			HW_G2(HZ,CLOCK_SRC)/CLOCK_PSC/PWM_HZ
#define HZ_ioclk		HW_SYSHZ
#define HZ_pll_32MHz		32000000
#define HZ_pll_64MHz		64000000


#if COUNT*PWM_HZ*CLOCK_PSC != HW_G2(HZ,CLOCK_SRC)
#  error "PWM_HZ can not be achieved"
#endif


int main ( )
{
  hwa_begin_from_reset();

  hwa( configure, (COUNTER, prescaler0),
       clock,	  CLOCK_SRC );

  hwa( configure, COUNTER,
       clock,	  ioclk / CLOCK_PSC,
       countmode, up_loop,
       bottom,	  0,
       top,	  compare2,
       overflow,  at_bottom );

  hwa( write, (COUNTER, compare2), COUNT-1 );

  hwa( configure, (COUNTER, OUTPUT),
       output_h,  set_at_bottom_clear_on_match,
       output_l,  clear_at_bottom_set_on_match );
  
  hwa( write, (COUNTER, OUTPUT), 0.5 * COUNT );

  hwa( configure,	(COUNTER, dtg0),
       prescaler,	4,	// 1 | 2 | 4 | 8
       HW_G2(OUTPUT,h), 3,	// 0..15
       HW_G2(OUTPUT,l), 9 );	// 0..15

  hwa_commit();

  for(;;) {}
}
