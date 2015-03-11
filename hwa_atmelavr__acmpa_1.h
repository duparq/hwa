
/*	Atmel AVR 8-bit analog comparator model 'a'
 *
 *	Used in:	ATtinyX4 acmp0
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Class & methods
 */
#define hw_class__acmpa
#define _hw_pop__acmpa(p,i,a,...)	__VA_ARGS__


#define hw__acmpa_acd			_cb1, csr, 1, 7
#define hw__acmpa_acbg			_cb1, csr, 1, 6
#define hw__acmpa_aco			_cb1, csr, 1, 5
#define hw__acmpa_aci			_cb1, csr, 1, 4
#define hw__acmpa_acie			_cb1, csr, 1, 3
#define hw__acmpa_acic			_cb1, csr, 1, 2
#define hw__acmpa_acis			_cb1, csr, 2, 0


#if !defined __ASSEMBLER__

typedef struct { hwa_r8_t csr ; } hwa_acmpa_t ;

#endif
