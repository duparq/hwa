
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*
 *	Atmel AVR universal serial interface model 'a'
 *
 *	Used in:	ATtinyX4
 */


/*	Class
 */
#define hw_class_usia


/*	Methods
 */
#define HW_POP_usia(c,n,i,a,...)		__VA_ARGS__


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t cr ;
  hwa_r8_t sr ;
  hwa_r8_t dr ;
} hwa_usia_t ;

#endif
