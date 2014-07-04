
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*
 *	Pin-change interrupt controllers (pcic) & pins (pcint)
 */


/*	pcic classes & methods
 */
#define hw_class_pcic0
#define hw_fn_hw_bits_pcic0		, _hw_bits

#define hw_class_pcic1
#define hw_fn_hw_bits_pcic1		, _hw_bits


/*	pcic instances		class, name, id, address
 */
#define hw_pcic0		pcic0, pcic0, 300, 0x32
#define hw_pcic1		pcic1, pcic1, 400, 0x40


/*	pcic class regs		reg, rw, ra, riv, rvm, rwm
 */
#define hw_pcic0_msk		reg, 8, 0x32-0x32, 0x00, 0xFF

#define hw_pcic0_irqe		xreg, hw_core0, pcie0
#define hw_pcic0_irqf		xreg, hw_core0, pcif0

#define hw_pcic0_pcint7		rb1, msk, 1, 7
#define hw_pcic0_pcint6		rb1, msk, 1, 6
#define hw_pcic0_pcint5		rb1, msk, 1, 5
#define hw_pcic0_pcint4		rb1, msk, 1, 4
#define hw_pcic0_pcint3		rb1, msk, 1, 3
#define hw_pcic0_pcint2		rb1, msk, 1, 2
#define hw_pcic0_pcint1		rb1, msk, 1, 1
#define hw_pcic0_pcint0		rb1, msk, 1, 0

#define hw_pcic1_msk		reg, 8, 0x40-0x40, 0x00, 0x0F

#define hw_pcic1_irqe		xreg, hw_core0, pcie1
#define hw_pcic1_irqf		xreg, hw_core0, pcif1

#define hw_pcic1_pcint11	rb1, msk, 1, 3
#define hw_pcic1_pcint10	rb1, msk, 1, 2
#define hw_pcic1_pcint9		rb1, msk, 1, 1
#define hw_pcic1_pcint8		rb1, msk, 1, 0


/*	pci io class & methods
 */
#define hw_class_pcint



#define hw_fn_hw_ctr_pcint		, _hw_ctr_pcint

#define _hw_ctr_pcint(t,n,...)		_hw_ctr_pcint_2(hw_##n##_##ext)
#define _hw_ctr_pcint_2(...)		_hw_ctr_pcint_3(__VA_ARGS__)
#define _hw_ctr_pcint_3(t,n,i,a, ion)	t,n,i,a


/*	io definition
 */
#define hw_fn_hw_io_pcint		, _hw_io_pcint

#define _hw_io_pcint(t,n,...)		_hw_io_pcint_2(hw_##n##_##ext)
#define _hw_io_pcint_2(...)		_hw_io_pcint_3(__VA_ARGS__)
#define _hw_io_pcint_3(t,n,i,a, ion)	hw_##ion


/*	pci io instances	class, name, id, (address)
 */
#define hw_pin_pcint0		pcint, pin_pcint0,  301,
#define hw_pin_pcint1		pcint, pin_pcint1,  302,
#define hw_pin_pcint2		pcint, pin_pcint2,  303,
#define hw_pin_pcint3		pcint, pin_pcint3,  304,
#define hw_pin_pcint4		pcint, pin_pcint4,  305,
#define hw_pin_pcint5		pcint, pin_pcint5,  306,
#define hw_pin_pcint6		pcint, pin_pcint6,  307,
#define hw_pin_pcint7		pcint, pin_pcint7,  308,
						             	 
#define hw_pin_pcint8		pcint, pin_pcint8,  401,
#define hw_pin_pcint9		pcint, pin_pcint9,  402,
#define hw_pin_pcint10		pcint, pin_pcint10, 403,
#define hw_pin_pcint11		pcint, pin_pcint11, 404,


/*	pci io instances extensions
 */
#define hw_pin_pcint0_ext	hw_pcic0, pin_13
#define hw_pin_pcint1_ext	hw_pcic0, pin_12
#define hw_pin_pcint2_ext	hw_pcic0, pin_11
#define hw_pin_pcint3_ext	hw_pcic0, pin_10
#define hw_pin_pcint4_ext	hw_pcic0, pin_9
#define hw_pin_pcint5_ext	hw_pcic0, pin_8
#define hw_pin_pcint6_ext	hw_pcic0, pin_7
#define hw_pin_pcint7_ext	hw_pcic0, pin_6
#define hw_pin_pcint8_ext	hw_pcic1, pin_2
#define hw_pin_pcint9_ext	hw_pcic1, pin_3
#define hw_pin_pcint10_ext	hw_pcic1, pin_5
#define hw_pin_pcint11_ext	hw_pcic1, pin_4

							  
#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t msk ;
} hwa_pcic_t ;

#define HWA_DCL_PCINTS				\
  hwa_pcic_t pcic0 ;				\
  hwa_pcic_t pcic1 ;

#endif
