
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
#define hw_core_sph		crg, 8, 0x5E, 0x03, 0x00
#define hw_core_spl		crg, 8, 0x5D, 0xFF, 0x00
#define hw_core_gimsk		crg, 8, 0x5B, 0x60, 0x00
#define  hw_core_int0		 cb1, gimsk, 1, 6
#define  hw_core_pcie		 cb1, gimsk, 1, 5
#define hw_core_gifr		crg, 8, 0x5A, 0x60, 0x60
#define  hw_core_intf0		 cb1, gifr, 1, 6
#define  hw_core_pcif		 cb1, gifr, 1, 5
#define hw_core_mcucr		crg, 8, 0x55, 0xFF, 0x00
#define  hw_core_bods		 cb1, mcucr, 1, 7
#define  hw_core_pud		 cb1, mcucr, 1, 6
#define  hw_core_se		 cb1, mcucr, 1, 5
#define  hw_core_sm		 cb1, mcucr, 2, 3
#define  hw_core_bodse		 cb1, mcucr, 1, 2
#define  hw_core_isc0		 cb1, mcucr, 2, 0
#define hw_core_mcusr		crg, 8, 0x54, 0x0F, 0x00
#define  hw_core_wdrf		 cb1, mcusr, 1, 3
#define  hw_core_borf		 cb1, mcusr, 1, 2
#define  hw_core_extrf		 cb1, mcusr, 1, 1
#define  hw_core_porf		 cb1, mcusr, 1, 0
#define  hw_core_allrf		 cb1, mcusr, 4, 0	/* convenient */
#define hw_core_osccal		crg, 8, 0x51, 0xFF, 0x00
#define hw_core_gpior2		crg, 8, 0x33, 0xFF, 0x00
#define hw_core_gpior1		crg, 8, 0x32, 0xFF, 0x00
#define hw_core_gpior0		crg, 8, 0x31, 0xFF, 0x00
#define hw_core_prr		crg, 8, 0x40, 0x0F, 0x00
#define  hw_core_prtim1		 cb1, prr, 1, 3
#define  hw_core_prtim0		 cb1, prr, 1, 2
#define  hw_core_prusi		 cb1, prr, 1, 1
#define  hw_core_pradc		 cb1, prr, 1, 0


/*	INT0 class
 */
#define hw_class_int0


/*	INT0 instance	        class, name, id, address
 */
#define hw_pin_int0		int0, pin_int0, 102, core0, pin_pb2


#if !defined __ASSEMBLER__

#if 0
#define hw_sleep()							\
  do {									\
      hw_write_reg( hw_core0, se, 1 );					\
      __asm__ __volatile__("  sleep		"	"\n\t" :::);	\
      hw_write_reg( hw_core0, se, 0 );					\
  } while(0)
#elif 0
#define hw_sleep()							\
  do {									\
    uint8_t reg ;							\
    __asm__ __volatile__("  in    %[r], %[mcucr]"	"\n\t"		\
			 "  ori   %[r], %[se]	"	"\n\t"		\
			 "  out   %[mcucr], %[r]"	"\n\t"		\
			 "  sleep		"	"\n\t"	\
			 "  andi  %[r], ~%[se]	"	"\n\t"		\
			 "  out   %[mcucr], %[r]"	"\n\t"		\
			 : [r] "=&d" (reg)				\
			 : [mcucr] "I" (hw_addr(hw_reg(hw_core0, mcucr))-0x20),	\
			   [se] "I" (1<<hw_bp(hw_reg(hw_core0, se))));	\
  } while(0)
#elif 0
#define hw_sleep()						\
  __asm__ __volatile__("    sleep          "	"\n\t" :::)
#endif


typedef struct {
  hwa_r8_t sreg ;
  hwa_r8_t gimsk ;
  hwa_r8_t gifr ;
  hwa_r8_t mcucr ;
  hwa_r8_t mcusr ;
  hwa_r8_t osccal ;
  hwa_r8_t gpior2 ;
  hwa_r8_t gpior1 ;
  hwa_r8_t gpior0 ;
  hwa_r8_t prr ;
} hwa_core_t ;

#define HWA_DCL_CORES		hwa_core_t core0

#endif /* !defined __ASSEMBLER__ */
