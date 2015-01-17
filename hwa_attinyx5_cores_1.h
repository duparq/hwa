
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	Class & methods
 */
#define hw_class_core
#define _hw_pop_core(c,n,i,a,...)	__VA_ARGS__


/*	Instance	        class, name, id, address
 */
#define hw_core0		core, core0, 101, 0


/*	Class regs		class, rw, ra, rwm, rfm
 */
#define hw_core_sreg		crg, 8, 0x5F, 0xFF, 0x00
#define hw_core_mcusr		crg, 8, 0x54, 0x0F, 0x00
#define hw_core_porf		cb1, mcusr, 1, 0
