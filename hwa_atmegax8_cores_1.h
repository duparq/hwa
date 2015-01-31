
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
 *				 cb1, cr, bn, bp
 */
#define hw_core_osccal		crg, 8, 0x66, 0xFF, 0x00
#define hw_core_prr		crg, 8, 0x64, 0xEF, 0x00
#define  hw_core_prtwi		 cb1, prr, 1, 7
#define  hw_core_prtim2		 cb1, prr, 1, 6
#define  hw_core_prtim0		 cb1, prr, 1, 5
#define  hw_core_prtim1		 cb1, prr, 1, 3
#define  hw_core_prspi		 cb1, prr, 1, 2
#define  hw_core_prusart	 cb1, prr, 1, 1
#define  hw_core_pradc		 cb1, prr, 1, 0
#define hw_core_sreg		crg, 8, 0x5F, 0xFF, 0x00
#define hw_core_sph		crg, 8, 0x5E, 0x03, 0x00
#define hw_core_spl		crg, 8, 0x5D, 0xFF, 0x00
#define hw_core_mcucr		crg, 8, 0x55, 0x73, 0x00
#define  hw_core_bods		 cb1, mcucr, 1, 6
#define  hw_core_bodse		 cb1, mcucr, 1, 5
#define  hw_core_pud		 cb1, mcucr, 1, 4
#define  hw_core_ivsel		 cb1, mcucr, 1, 1
#define  hw_core_ivce		 cb1, mcucr, 1, 0
#define hw_core_mcusr		crg, 8, 0x54, 0x0F, 0x00
#define  hw_core_wdrf		 cb1, mcusr, 1, 3
#define  hw_core_borf		 cb1, mcusr, 1, 2
#define  hw_core_extrf		 cb1, mcusr, 1, 1
#define  hw_core_porf		 cb1, mcusr, 1, 0
#define  hw_core_allrf		 cb1, mcusr, 4, 0	/* convenient */
#define hw_core_smcr		crg, 8, 0x53, 0x0F, 0x00
#define  hw_core_sm		 cb1, smcr, 3, 1
#define  hw_core_se		 cb1, smcr, 1, 0
#define hw_core_gpior2		crg, 8, 0x4B, 0xFF, 0x00
#define hw_core_gpior1		crg, 8, 0x4A, 0xFF, 0x00
#define hw_core_gpior0		crg, 8, 0x3E, 0xFF, 0x00
#define hw_core_eimsk		crg, 8, 0x3D, 0x03, 0x00
#define  hw_core_int1		 cb1, eimsk, 1, 1
#define  hw_core_int0		 cb1, eimsk, 1, 0
#define hw_core_eifr		crg, 8, 0x3C, 0x03, 0x03
#define  hw_core_intf1		 cb1, eifr, 1, 1
#define  hw_core_intf0		 cb1, eifr, 1, 0


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t osccal ;
  hwa_r8_t prr ;
  hwa_r8_t mcucr ;
  hwa_r8_t mcusr ;
  hwa_r8_t smcr ;
  hwa_r8_t gpior2 ;
  hwa_r8_t gpior1 ;
  hwa_r8_t gpior0 ;
  hwa_r8_t eimsk ;
  hwa_r8_t eifr ;
} hwa_core_t ;

#define HWA_DCL_CORES		hwa_core_t core0

#endif /* !defined __ASSEMBLER__ */
