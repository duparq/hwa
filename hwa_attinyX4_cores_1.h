
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*
 *	ATtinyX4 core & int0
 */


/*	Class & methods
 */
#define hw_class_core
#define HW_POP_core(c,n,i,a,...)	__VA_ARGS__

#define hw_def_hw_reg_core		, _hw_reg


/*	Instance	        class, name, id, address
 */
#define hw_core0		core, core0, 101, 0x00


/*	Class regs		class, rw, ra, riv, rwm, rfm
 */
#define hw_core_sreg		crg, 8, 0x5F, 0x00, 0xFF, 0x00
#define hw_core_gimsk		crg, 8, 0x5B, 0x00, 0xFF, 0x00
#define hw_core_gifr		crg, 8, 0x5A, 0x00, 0x70, 0x00
#define hw_core_mcucr		crg, 8, 0x55, 0x00, 0xFF, 0x00
#define hw_core_mcusr		crg, 8, 0x54, 0x00, 0x0F, 0x00 /* problem with watchdog */
#define hw_core_osccal		crg, 8, 0x51, 0x00, 0xFF, 0x00
#define hw_core_gpior2		crg, 8, 0x35, 0x00, 0xFF, 0x00
#define hw_core_gpior1		crg, 8, 0x33, 0x00, 0xFF, 0x00
#define hw_core_gpior0		crg, 8, 0x33, 0x00, 0xFF, 0x00
#define hw_core_prr		crg, 8, 0x20, 0x00, 0xFF, 0x00

#define hw_core_bods		cb1, mcucr, 1, 7
#define hw_core_pud		cb1, mcucr, 1, 6
#define hw_core_se		cb1, mcucr, 1, 5
#define hw_core_sm		cb1, mcucr, 2, 3
#define hw_core_bodse		cb1, mcucr, 1, 2
#define hw_core_isc0		cb1, mcucr, 2, 0

#define hw_core_int0		cb1, gimsk, 1, 6
#define hw_core_pcie1		cb1, gimsk, 1, 5
#define hw_core_pcie0		cb1, gimsk, 1, 4

#define hw_core_intf0		cb1, gifr, 1, 6
#define hw_core_pcif1		cb1, gifr, 1, 5
#define hw_core_pcif0		cb1, gifr, 1, 4

#define hw_core_prtim1		cb1, prr, 1, 3
#define hw_core_prtim0		cb1, prr, 1, 2
#define hw_core_prusi		cb1, prr, 1, 1
#define hw_core_pradc		cb1, prr, 1, 0


/*	INT0 class
 */
#define hw_class_int0

/*	INT0 instance	        class, name, id, address
 */
#define hw_pin_int0		int0, pin_int0, 102, core0, pin_pb2


/*	Power management
 */
#define hw_def_hwa_turn_c8a	, _hwa_turn_power
#define hw_def_hwa_turn_c16a	, _hwa_turn_power
#define hw_def_hwa_turn_usia	, _hwa_turn_power
#define hw_def_hwa_turn_ad10a	, _hwa_turn_power

#define hw_power_counter1	prtim1
#define hw_power_counter0	prtim0
#define hw_power_usi0		prusi
#define hw_power_adc0		pradc

#define _hwa_turn_power(c,n,i,a,vstate)\
  HW_G2(_hwa_turn_power, HW_IS(,hw_state_##vstate))(c,n,i,a,vstate)
#define _hwa_turn_power_0(c,n,i,a, vstate)			\
  HW_ERR("expected `on` or `off`, got `" #vstate "` instead.")
#define _hwa_turn_power_1(c,n,i,a, vstate)	\
  _hwa_write_reg(hw_core0, hw_power_##n, (HW_A1(hw_state_##vstate)==0))


#if !defined __ASSEMBLER__

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
