
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*
 *	Analog comparator
 */


/*	Class & methods
 */
#define hw_class_acmp
#define _hw_pop_acmp(c,n,i,a,...)	__VA_ARGS__

/*	Instance			class, name, id, address
 */				        
#define hw_acmp0			acmp, acmp0, 700, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */				        
#define hw_acmp_csr			crg, 8, 0x28, 0xDF, 0x10

#define hw_acmp_acd			cb1, csr, 1, 7
#define hw_acmp_acbg			cb1, csr, 1, 6
#define hw_acmp_aco			cb1, csr, 1, 5
#define hw_acmp_aci			cb1, csr, 1, 4
#define hw_acmp_acie			cb1, csr, 1, 3
#define hw_acmp_acic			cb1, csr, 1, 2
#define hw_acmp_acis			cb1, csr, 2, 0

#if !defined __ASSEMBLER__

typedef struct { hwa_r8_t csr ; } hwa_acmp_t ;

#define HWA_DCL_ACMPS		hwa_acmp_t acmp0

#endif /* !defined __ASSEMBLER__ */
