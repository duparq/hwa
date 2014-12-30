
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*
 *	IO: General-Purpose Inputs & Outputs
 */

#include "hwa_atmelavr_ios_1.h"


/*	Class & method
 */
#define hw_class_portb
#define _hw_pop_portb(c,n,i,a,...)	__VA_ARGS__

/*	Instances			class, name, id, address
 */
#define hw_portb			portb, portb, 300, 0

/*	Class regs			class, rw, ra, rwm, rfm
 */
#define hw_portb_port			crg, 8, 0x25, 0xFF, 0x00
#define hw_portb_ddr			crg, 8, 0x24, 0xFF, 0x00
#define hw_portb_pin			crg, 8, 0x23, 0xFF, 0x00

/*	Pins				class, name, id, controller, bn, bp
 */
#define hw_port_b			io, port_b,  309, hw_portb, 8, 0
#define hw_pin_pb0			io, pin_pb0, 301, hw_portb, 1, 0
#define hw_pin_pb1			io, pin_pb1, 302, hw_portb, 1, 1
#define hw_pin_pb2			io, pin_pb2, 303, hw_portb, 1, 2
#define hw_pin_pb3			io, pin_pb3, 304, hw_portb, 1, 3
#define hw_pin_pb4			io, pin_pb4, 305, hw_portb, 1, 4
#define hw_pin_pb5			io, pin_pb5, 306, hw_portb, 1, 5
#define hw_pin_pb6			io, pin_pb6, 307, hw_portb, 1, 6
#define hw_pin_pb7			io, pin_pb7, 308, hw_portb, 1, 7


/*	Class & method
 */
#define hw_class_portc
#define _hw_pop_portc(c,n,i,a,...)	__VA_ARGS__

/*	Instances			class, name, id, address
 */
#define hw_portc			portc, portc, 310, 0

/*	Class regs			class, rw, ra, rwm, rfm
 */
#define hw_portc_port			crg, 8, 0x28, 0x7F, 0x00
#define hw_portc_ddr			crg, 8, 0x27, 0x7F, 0x00
#define hw_portc_pin			crg, 8, 0x26, 0x7F, 0x00

/*	Pins				class, name, id, controller, bn, bp
 */
#define hw_port_c			io, port_c,  319, hw_portc, 8, 0
#define hw_pin_pc0			io, pin_pc0, 311, hw_portc, 1, 0
#define hw_pin_pc1			io, pin_pc1, 312, hw_portc, 1, 1
#define hw_pin_pc2			io, pin_pc2, 313, hw_portc, 1, 2
#define hw_pin_pc3			io, pin_pc3, 314, hw_portc, 1, 3
#define hw_pin_pc4			io, pin_pc4, 315, hw_portc, 1, 4
#define hw_pin_pc5			io, pin_pc5, 316, hw_portc, 1, 5
#define hw_pin_pc6			io, pin_pc6, 317, hw_portc, 1, 6


/*	Class & method
 */
#define hw_class_portd
#define _hw_pop_portd(c,n,i,a,...)	__VA_ARGS__

/*	Instances			class, name, id, address
 */
#define hw_portd			portd, portd, 320, 0

/*	Class regs			class, rw, ra, rwm, rfm
 */
#define hw_portd_port			crg, 8, 0x2B, 0xFF, 0x00
#define hw_portd_ddr			crg, 8, 0x2A, 0xFF, 0x00
#define hw_portd_pin			crg, 8, 0x29, 0xFF, 0x00

/*	Pins				class, name, id, controller, bn, bp
 */
#define hw_port_d			io, port_d,  329, hw_portd, 8, 0
#define hw_pin_pd0			io, pin_pd0, 321, hw_portd, 1, 0
#define hw_pin_pd1			io, pin_pd1, 322, hw_portd, 1, 1
#define hw_pin_pd2			io, pin_pd2, 323, hw_portd, 1, 2
#define hw_pin_pd3			io, pin_pd3, 324, hw_portd, 1, 3
#define hw_pin_pd4			io, pin_pd4, 325, hw_portd, 1, 4
#define hw_pin_pd5			io, pin_pd5, 326, hw_portd, 1, 5
#define hw_pin_pd6			io, pin_pd6, 327, hw_portd, 1, 6
#define hw_pin_pd7			io, pin_pd7, 328, hw_portd, 1, 7


/*	Pins by numbers
 */
#define hw_is_dil_dil			, 1
#define hw_is_28PDIP_28PDIP		, 1
#define hw_is_28MLF_28MLF		, 1
#define hw_is_32MLF_32MLF		, 1


#if HW_IS(dil,HW_A1(HW_DEVICE)) || HW_IS(28PDIP,HW_A1(HW_DEVICE))
#
#  define hw_pin_1			hw_pin_pc6
#  define hw_pin_2			hw_pin_pd0
#  define hw_pin_3			hw_pin_pd1
#  define hw_pin_4			hw_pin_pd2
#  define hw_pin_5			hw_pin_pd3
#  define hw_pin_6			hw_pin_pd4
#  define hw_pin_9			hw_pin_pb6
#  define hw_pin_10			hw_pin_pb7
#  define hw_pin_11			hw_pin_pd5
#  define hw_pin_12			hw_pin_pd6
#  define hw_pin_13			hw_pin_pd7
#  define hw_pin_14			hw_pin_pb0
#  define hw_pin_15			hw_pin_pb1
#  define hw_pin_16			hw_pin_pb2
#  define hw_pin_17			hw_pin_pb3
#  define hw_pin_18			hw_pin_pb4
#  define hw_pin_19			hw_pin_pb5
#  define hw_pin_23			hw_pin_pc0
#  define hw_pin_24			hw_pin_pc1
#  define hw_pin_25			hw_pin_pc2
#  define hw_pin_26			hw_pin_pc3
#  define hw_pin_27			hw_pin_pc4
#  define hw_pin_28			hw_pin_pc5
#
#elif HW_IS(28MLF,HW_A1(HW_DEVICE))
#
#  define hw_pin_1			hw_pin_pd3
#  define hw_pin_2			hw_pin_pd4
#  define hw_pin_3			hw_pin_
#  define hw_pin_4			hw_pin_
#  define hw_pin_5			hw_pin_pb6
#  define hw_pin_6			hw_pin_pb7
#  define hw_pin_7			hw_pin_pd5
#  define hw_pin_8			hw_pin_pd6
#  define hw_pin_9			hw_pin_pd7
#  define hw_pin_10			hw_pin_pb0
#  define hw_pin_11			hw_pin_pb1
#  define hw_pin_12			hw_pin_pb2
#  define hw_pin_13			hw_pin_pb3
#  define hw_pin_14			hw_pin_pb4
#  define hw_pin_15			hw_pin_pb5
#  define hw_pin_16			hw_pin_
#  define hw_pin_17			hw_pin_
#  define hw_pin_18			hw_pin_
#  define hw_pin_19			hw_pin_pc0
#  define hw_pin_20			hw_pin_pc1
#  define hw_pin_21			hw_pin_pc2
#  define hw_pin_22			hw_pin_pc3
#  define hw_pin_23			hw_pin_pc4
#  define hw_pin_24			hw_pin_pc5
#  define hw_pin_25			hw_pin_pc6
#  define hw_pin_26			hw_pin_pd0
#  define hw_pin_27			hw_pin_pd1
#  define hw_pin_28			hw_pin_pd2
#
#elif HW_IS(32MLF,HW_A1(HW_DEVICE))
#
#  define hw_pin_1			hw_pin_pd3
#  define hw_pin_2			hw_pin_pd4
#  define hw_pin_3			hw_pin_
#  define hw_pin_4			hw_pin_
#  define hw_pin_5			hw_pin_
#  define hw_pin_6			hw_pin_
#  define hw_pin_7			hw_pin_pb6
#  define hw_pin_8			hw_pin_pb7
#  define hw_pin_9			hw_pin_pd5
#  define hw_pin_10			hw_pin_pd6
#  define hw_pin_11			hw_pin_pd7
#  define hw_pin_12			hw_pin_pb0
#  define hw_pin_13			hw_pin_pb1
#  define hw_pin_14			hw_pin_pb2
#  define hw_pin_15			hw_pin_pb3
#  define hw_pin_16			hw_pin_pb4
#  define hw_pin_17			hw_pin_pb5
#  define hw_pin_18			hw_pin_
#  define hw_pin_19			hw_pin_adc6
#  define hw_pin_20			hw_pin_
#  define hw_pin_21			hw_pin_
#  define hw_pin_22			hw_pin_adc7
#  define hw_pin_23			hw_pin_pc0
#  define hw_pin_24			hw_pin_pc1
#  define hw_pin_25			hw_pin_pc2
#  define hw_pin_26			hw_pin_pc3
#  define hw_pin_27			hw_pin_pc4
#  define hw_pin_28			hw_pin_pc5
#  define hw_pin_29			hw_pin_pc6
#  define hw_pin_30			hw_pin_pd0
#  define hw_pin_31			hw_pin_pd1
#  define hw_pin_32			hw_pin_pd2
#
#endif


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t port ;
  hwa_r8_t ddr ;
} hwa_io_t ;

#define HWA_DCL_IOS			hwa_io_t portb, portc, portd

#endif /* !defined __ASSEMBLER__ */
