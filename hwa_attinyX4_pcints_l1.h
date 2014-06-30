
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Pin-change interrupt controllers
 *
 *				'ctr', class, name, address
 */
#define hw_pcic0		ctr, pcic0, pcic0, 0x32
#define hw_pcic1		ctr, pcic1, pcic1, 0x40

/*	Registers		'reg', rw, ra, riv, rvm, rwm
 */
#define hw_pcic0_msk		mem, reg, 8, 0x32-0x32, 0x00, 0xFF

#define hw_pcic0_irqe		mem, xreg, hw_core0, pcie0
#define hw_pcic0_irqf		mem, xreg, hw_core0, pcif0

#define hw_pcic0_pcint7		mem, regb, msk, 1, 7
#define hw_pcic0_pcint6		mem, regb, msk, 1, 6
#define hw_pcic0_pcint5		mem, regb, msk, 1, 5
#define hw_pcic0_pcint4		mem, regb, msk, 1, 4
#define hw_pcic0_pcint3		mem, regb, msk, 1, 3
#define hw_pcic0_pcint2		mem, regb, msk, 1, 2
#define hw_pcic0_pcint1		mem, regb, msk, 1, 1
#define hw_pcic0_pcint0		mem, regb, msk, 1, 0

#define hw_pcic1_msk		mem, reg, 8, 0x40-0x40, 0x00, 0x0F

#define hw_pcic1_irqe		mem, xreg, hw_core0, pcie1
#define hw_pcic1_irqf		mem, xreg, hw_core0, pcif1

#define hw_pcic1_pcint11	mem, regb, msk, 1, 3
#define hw_pcic1_pcint10	mem, regb, msk, 1, 2
#define hw_pcic1_pcint9		mem, regb, msk, 1, 1
#define hw_pcic1_pcint8		mem, regb, msk, 1, 0


/*	Equality test
 */
#define hw_is_pcic0_pcic0	,1
#define _hw_eq_pcic0_isfn
#define _hw_eq_pcic0		_hw_eq_pcic
#define hw_is_pcic1_pcic1	,1
#define _hw_eq_pcic1_isfn
#define _hw_eq_pcic1		_hw_eq_pcic

#define _hw_eq_pcic(ctr,cc,cn,ca,...)	HW_IS(cc,hw_class(__VA_ARGS__))


/*	Pin-change interrupt controller pins
 *
 *	Each pin is an alternate io-pin of class 'aio' associated to an io-pin
 *	and a controller of class 'pcic'.
 *
 *				'aio', name, io-name, controller def
 */
#define hw_pin_pcint0		ctr, pcint, pin_pcint0,  pin_13, hw_pcic0
#define hw_pin_pcint1		ctr, pcint, pin_pcint1,  pin_12, hw_pcic0
#define hw_pin_pcint2		ctr, pcint, pin_pcint2,  pin_11, hw_pcic0
#define hw_pin_pcint3		ctr, pcint, pin_pcint3,  pin_10, hw_pcic0
#define hw_pin_pcint4		ctr, pcint, pin_pcint4,  pin_9,  hw_pcic0
#define hw_pin_pcint5		ctr, pcint, pin_pcint5,  pin_8,  hw_pcic0
#define hw_pin_pcint6		ctr, pcint, pin_pcint6,  pin_7,  hw_pcic0
#define hw_pin_pcint7		ctr, pcint, pin_pcint7,  pin_6,  hw_pcic0
						             	  
#define hw_pin_pcint8		ctr, pcint, pin_pcint8,  pin_2,  hw_pcic1
#define hw_pin_pcint9		ctr, pcint, pin_pcint9,  pin_3,  hw_pcic1
#define hw_pin_pcint10		ctr, pcint, pin_pcint10, pin_5,  hw_pcic1
#define hw_pin_pcint11		ctr, pcint, pin_pcint11, pin_4,  hw_pcic1

							  
/** \brief	Part of HWA struct for ios
 */
#if !defined __ASSEMBLER__
typedef struct {
  hwa_r8_t msk ;
} hwa_pcic_t ;
#endif


#define HWA_DCL_PCINTS				\
  hwa_pcic_t pcic0 ;				\
  hwa_pcic_t pcic1 ;


/*	Equality test
 */
#define hw_is_pcint_pcint	,1
#define _hw_eq_pcint_isfn
#define _hw_eq_pcint(ctr1,cc1,cn1,ion1, sctr1,scc1,scn1,sca1, ...) \
  HW_G2(_hw_eq_pcint,HW_IS(pcint,hw_class(__VA_ARGS__)))(ctr1,cc1,cn1,ion1, \
							 sctr1,scc1,scn1,sca1, __VA_ARGS__)
#define _hw_eq_pcint_0(...)	0
#define _hw_eq_pcint_1(ctr1,cc1,cn1,ion1, sctr1,scc1,scn1,sca1, \
		       ctr2,cc2,cn2,ion2, sctr2,scc2,scn2,sca2)\
  _hw_eq_pcint_2(hw_##ion1, hw_##ion2)
#define _hw_eq_pcint_2(...)	_hw_eq_io_1(__VA_ARGS__)


/*	Controller
 */
#define hw_ctr_pcint_isfn
#define hw_ctr_pcint(cn,ion, ...)	__VA_ARGS__


/*	io definition
 */
#define hw_io_pcint_isfn
#define hw_io_pcint(cn,ion, ...)	hw_##ion
