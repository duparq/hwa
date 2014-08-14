
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*
 *	Pin-change interrupt controllers (pcic) & pins (pcint)
 */


/*	Class & methods
 */
#define hw_class_pcic0
#define HW_POP_pcic0(c,n,i,a,...)	__VA_ARGS__

#define hw_class_pcic1
#define HW_POP_pcic1(c,n,i,a,...)	__VA_ARGS__

/*	Instances			class, name, id, address
 */
#define hw_pcic0			pcic0, pcic0, 200, 0
#define hw_pcic1			pcic1, pcic1, 210, 0

/*	Interrupts			class, vector, controller, enable, flag
 */
#define hw_irq_pcic0			irq, 2, core0, pcie0, pcif0
#define hw_irq_pcic1			irq, 3, core0, pcie1, pcif1

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw_pcic0_msk			crg, 8, 0x32, 0xFF, 0x00

#define hw_pcic0_irqe			irg, hw_core0, pcie0
#define hw_pcic0_irqf			irg, hw_core0, pcif0

#define hw_pcic0_pcint7			cb1, msk, 1, 7
#define hw_pcic0_pcint6			cb1, msk, 1, 6
#define hw_pcic0_pcint5			cb1, msk, 1, 5
#define hw_pcic0_pcint4			cb1, msk, 1, 4
#define hw_pcic0_pcint3			cb1, msk, 1, 3
#define hw_pcic0_pcint2			cb1, msk, 1, 2
#define hw_pcic0_pcint1			cb1, msk, 1, 1
#define hw_pcic0_pcint0			cb1, msk, 1, 0

#define hw_pcic1_msk			crg, 8, 0x40, 0x0F, 0x00

#define hw_pcic1_irqe			irg, hw_core0, pcie1
#define hw_pcic1_irqf			irg, hw_core0, pcif1

#define hw_pcic1_pcint11		cb1, msk, 1, 3
#define hw_pcic1_pcint10		cb1, msk, 1, 2
#define hw_pcic1_pcint9			cb1, msk, 1, 1
#define hw_pcic1_pcint8			cb1, msk, 1, 0


/*	Classes & methods: pin-change interrupt pins
 */
#define hw_class_pcint
#define HW_POP_pcint(c,n,i,cn,ion,...)	__VA_ARGS__

#define hw_def_hw_ctr_pcint		, _hw_ctr_pcint
#define _hw_ctr_pcint(c,n,i,cn,...)	hw_##cn

#define hw_def_hw_io_pcint		, _hw_io_pcint
#define _hw_io_pcint(c,n,i,cn,ion)	hw_##ion

/*	Instances			class, name, id, controller, io
 */
#define hw_pin_pcint0			pcint, pin_pcint0,  201, pcic0, pin_pa0
#define hw_pin_pcint1			pcint, pin_pcint1,  202, pcic0, pin_pa1
#define hw_pin_pcint2			pcint, pin_pcint2,  203, pcic0, pin_pa2
#define hw_pin_pcint3			pcint, pin_pcint3,  204, pcic0, pin_pa3
#define hw_pin_pcint4			pcint, pin_pcint4,  205, pcic0, pin_pa4
#define hw_pin_pcint5			pcint, pin_pcint5,  206, pcic0, pin_pa5
#define hw_pin_pcint6			pcint, pin_pcint6,  207, pcic0, pin_pa6
#define hw_pin_pcint7			pcint, pin_pcint7,  208, pcic0, pin_pa7
						             	 
#define hw_pin_pcint8			pcint, pin_pcint8,  211, pcic1, pin_pb0
#define hw_pin_pcint9			pcint, pin_pcint9,  212, pcic1, pin_pb1
#define hw_pin_pcint10			pcint, pin_pcint10, 213, pcic1, pin_pb2
#define hw_pin_pcint11			pcint, pin_pcint11, 214, pcic1, pin_pb3

/*	Interrupts
 */
#define hw_irq_pin_pcint0 		irq, 2, pcic0, pcint0 , irqf
#define hw_irq_pin_pcint1 		irq, 2, pcic0, pcint1 , irqf
#define hw_irq_pin_pcint2 		irq, 2, pcic0, pcint2 , irqf
#define hw_irq_pin_pcint3 		irq, 2, pcic0, pcint3 , irqf
#define hw_irq_pin_pcint4 		irq, 2, pcic0, pcint4 , irqf
#define hw_irq_pin_pcint5 		irq, 2, pcic0, pcint5 , irqf
#define hw_irq_pin_pcint6 		irq, 2, pcic0, pcint6 , irqf
#define hw_irq_pin_pcint7 		irq, 2, pcic0, pcint7 , irqf
			   			       
#define hw_irq_pin_pcint8 		irq, 3, pcic1, pcint8, irqf
#define hw_irq_pin_pcint9 		irq, 3, pcic1, pcint9, irqf
#define hw_irq_pin_pcint10		irq, 3, pcic1, pcint10, irqf
#define hw_irq_pin_pcint11		irq, 3, pcic1, pcint11, irqf

							  
#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t msk ;
} hwa_pcic_t ;

#define HWA_DCL_PCINTS		hwa_pcic_t pcic0, pcic1

#endif
