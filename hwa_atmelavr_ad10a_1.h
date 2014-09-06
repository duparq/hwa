
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*
 *	Atmel AVR 10-bit analog-digital converter model 'a'
 *
 *	Used in:	ATtinyX4
 */


/*	Class & methods
 */
#define hw_class_ad10a
#define _hw_pop_ad10a(c,n,i,a,...)	__VA_ARGS__

#define hw_def_hw_bn_ad10a		, _hw_bn_ad10a
#define _hw_bn_ad10a(c,n,i,a)		10


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t admux ;
  hwa_r8_t sra ;
  hwa_r8_t srb ;
  hwa_r8_t did ;
} hwa_ad10a_t ;

#endif
