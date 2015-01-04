
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*
 *	ATtinyX4 flash memory
 */


/*	Class & methods
 */
#define hw_class_flash
#define _hw_pop_flash(c,n,i,a,...)	__VA_ARGS__


/*	Instance	        class, name, id, address
 */
#define hw_flash0		flash, flash0, 1100, 0


/*	Class regs		class, rw, ra, rwm, rfm
 */
#define hw_flash_csr		crg,  8, 0x57, 0x1F, 0x00

#define hw_flash_sigrd		cb1, csr, 1, 5
#define hw_flash_rsig		cb1, csr, 1, 5	/* old definition */
#define hw_flash_rwwsre		cb1, csr, 1, 4
#define hw_flash_ctpb		cb1, csr, 1, 4	/* old definition */
#define hw_flash_blbset		cb1, csr, 1, 3
#define hw_flash_rflb		cb1, csr, 1, 3	/* old definition */
#define hw_flash_pgwrt		cb1, csr, 1, 2
#define hw_flash_pgers		cb1, csr, 1, 1
#define hw_flash_spmen		cb1, csr, 1, 0

/*
 *	No HWA declaration.
 */
