
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Atmel AVR core model 'a'
 *
 *	Used in: ATtinyX4
 *		 ATtinyX5
 */


/*	Class & methods
 */
#define hw_class__coreb
#define _hw_pop__coreb(c,n,i,a,...)	__VA_ARGS__

#if !defined __ASSEMBLER__

typedef struct {
  /* hwa_r8_t sreg ; */
  hwa_r8_t eimsk ;
  hwa_r8_t eifr ;
  hwa_r8_t mcucr ;
  hwa_r8_t mcusr ;
  hwa_r8_t smcr ;
  hwa_r8_t osccal ;
  hwa_r8_t gpior2 ;
  hwa_r8_t gpior1 ;
  hwa_r8_t gpior0 ;
  hwa_r8_t prr ;
} hwa_coreb_t ;

#endif
