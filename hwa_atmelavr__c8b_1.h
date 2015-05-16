
/*	Atmel AVR 8-bit timer-counter model 'b'
 *
 *	This is almost the same as model 'a' but with different clocking
 *	possibilities.
 *
 *	Used in: ATmegaX8 hw_counter2
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


//#include "hwa_atmelavr__ocua_1.h"


/*  Class & methods
 */
#define _hw_class__c8b


/*  Methods that do not produce C code
 */
#define _hw_mthd_hw_bn__c8b		, _hw_bn_c8b
#define _hw_bn_c8b(p,i,a)		8


#if !defined __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t 	ccra ;
  hwa_r8_t 	ccrb ;
  hwa_r8_t 	count ;
  union {
    hwa_r8_t	ocra ;
    hwa_r8_t	compare0 ;
  };
  union {
    hwa_r8_t	ocrb ;
    hwa_r8_t	compare1 ;
  };
  hwa_r8_t 	imsk ;
  hwa_r8_t 	ifr ;
  hwa_r8_t 	assr ;

  /*  Registers for high-level configuration
   */
  uint8_t	clock, countmode, top, overflow ;
  uint8_t	compare0_update, compare0_output ;
  uint8_t	compare1_update, compare1_output ;
  /* hwa_ocua_t	compare0, compare1 ; */

  /*  Values to write into registers after solving
   */
  /* struct { */
  /*   uint8_t	cs, wgm, coma, comb ; */
  /* } solved ; */

} hwa_c8b_t ;

#endif
