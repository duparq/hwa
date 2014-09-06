
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*
 *	Atmel AVR 8-bit timer-counter model 'a'
 *
 *	Used in:	ATtinyX4 Timer 0
 *			ATtinyX5 Timer 0
 *			ATmegaX8 Timer 0
 */


/*	Generic functions
 */
#define hw_class_c8a
#define _hw_pop_c8a(c,n,i,a,...)		__VA_ARGS__

#define hw_def_hw_bn_c8a		, _hw_bn_c8a
#define _hw_bn_c8a(c,n,i,a)		8

/**
 * \todo
 */
#if !defined __ASSEMBLER__
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t 	ccra ;
  hwa_r8_t 	ccrb ;
  hwa_r8_t 	count ;
  union {
    hwa_r8_t	ocra ;
    hwa_r8_t	compare_a ;
  };
  union {
    hwa_r8_t	ocrb ;
    hwa_r8_t	compare_b ;
  };
  hwa_r8_t 	imsk ;
  hwa_r8_t 	ifr ;

  /*  HWA configuration
   */
  uint8_t	clock, countmode, top, update, overflow ;
  uint8_t	ocra_mode ;
  uint8_t	ocrb_mode ;

} hwa_c8a_t ;

#endif
