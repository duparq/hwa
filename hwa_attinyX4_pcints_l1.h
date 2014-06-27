
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Pin-change interrupt controllers
 *
 *				'ctr', name, class, address
 */
#define hw_pcic0		ctr, pcic0, pcic0, 0x32
#define hw_pcic1		ctr, pcic1, pcic1, 0x40

/*	Registers		'reg', rw, ra, riv, rvm, rwm
 */
#define hw_pcic0_msk		reg, msk, 8, 0x32-0x32, 0x00, 0xFF

#define hw_pcic0_irqe		regb, hw_core0, pcie0
#define hw_pcic0_irqf		regb, hw_core0, pcif0

#define hw_pcic0_pcint7		regb, hw_pcic0_msk, 1, 7
#define hw_pcic0_pcint6		regb, hw_pcic0_msk, 1, 6
#define hw_pcic0_pcint5		regb, hw_pcic0_msk, 1, 5
#define hw_pcic0_pcint4		regb, hw_pcic0_msk, 1, 4
#define hw_pcic0_pcint3		regb, hw_pcic0_msk, 1, 3
#define hw_pcic0_pcint2		regb, hw_pcic0_msk, 1, 2
#define hw_pcic0_pcint1		regb, hw_pcic0_msk, 1, 1
#define hw_pcic0_pcint0		regb, hw_pcic0_msk, 1, 0

#define hw_pcic1_msk		reg, msk, 8, 0x40-0x40, 0x00, 0x0F

#define hw_pcic1_irqe		regb, hw_core0, pcie1
#define hw_pcic1_irqf		regb, hw_core0, pcif1

#define hw_pcic1_pcint11	regb, hw_pcic1_msk, 1, 3
#define hw_pcic1_pcint10	regb, hw_pcic1_msk, 1, 2
#define hw_pcic1_pcint9		regb, hw_pcic1_msk, 1, 1
#define hw_pcic1_pcint8		regb, hw_pcic1_msk, 1, 0


/*	Pin-change interrupt controller pins
 *
 *	Each pin is an alternate io-pin of class 'aio' associated to an io-pin
 *	and a controller of class 'pcic'.
 *
 *				'aio', name, io-name, controller def
 */
#define hw_pin_pcint0		aio, pin_pcint0,  pin_13, hw_pcic0
#define hw_pin_pcint1		aio, pin_pcint1,  pin_12, hw_pcic0
#define hw_pin_pcint2		aio, pin_pcint2,  pin_11, hw_pcic0
#define hw_pin_pcint3		aio, pin_pcint3,  pin_10, hw_pcic0
#define hw_pin_pcint4		aio, pin_pcint4,  pin_9,  hw_pcic0
#define hw_pin_pcint5		aio, pin_pcint5,  pin_8,  hw_pcic0
#define hw_pin_pcint6		aio, pin_pcint6,  pin_7,  hw_pcic0
#define hw_pin_pcint7		aio, pin_pcint7,  pin_6,  hw_pcic0
						             	  
#define hw_pin_pcint8		aio, pin_pcint8,  pin_2,  hw_pcic1
#define hw_pin_pcint9		aio, pin_pcint9,  pin_3,  hw_pcic1
#define hw_pin_pcint10		aio, pin_pcint10, pin_5,  hw_pcic1
#define hw_pin_pcint11		aio, pin_pcint11, pin_4,  hw_pcic1
							  
							  
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
