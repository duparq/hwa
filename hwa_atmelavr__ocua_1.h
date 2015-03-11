
/*	Atmel AVR 8-bit timer-counter compare unit version 'a'
 *
 *	Used in: ATtinyX4 OC0A	hw_counter0_compare0
 *		 	  OC0B	hw_counter0_compare1
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


#define hw_class__ocua
#define _hw_pop__ocua(p,i,cn,chn,ion,...)	__VA_ARGS__


#if !defined __ASSEMBLER__

typedef struct {
  uint8_t	update, output ;
} hwa_ocua_t ;

#endif
