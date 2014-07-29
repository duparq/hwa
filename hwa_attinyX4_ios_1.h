
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
#define hw_class_porta
#define HW_POP_porta(c,n,i,a,...)	__VA_ARGS__

#define hw_def_hw_reg_porta		, _hw_reg

/*	Instances		class, name, id, address
 */
#define hw_porta		porta, porta, 300, 0x21

/*	Class regs		class, rw, ra, riv, rvm, rwm, rfm
 */
#define hw_porta_port		crg, 8, 0x3B-0x21, 0x00, 0xFF, 0x00
#define hw_porta_ddr		crg, 8, 0x3A-0x21, 0x00, 0xFF, 0x00
#define hw_porta_pin		crg, 8, 0x39-0x21, 0x00, 0xFF, 0x00

/*	Pins			class, name, id, controller, bn, bp
 */
#define hw_port_a		io, port_a,  309, hw_porta, 8, 0
#define hw_pin_pa0		io, pin_pa0, 301, hw_porta, 1, 0
#define hw_pin_pa1		io, pin_pa1, 302, hw_porta, 1, 1
#define hw_pin_pa2		io, pin_pa2, 303, hw_porta, 1, 2
#define hw_pin_pa3		io, pin_pa3, 304, hw_porta, 1, 3
#define hw_pin_pa4		io, pin_pa4, 305, hw_porta, 1, 4
#define hw_pin_pa5		io, pin_pa5, 306, hw_porta, 1, 5
#define hw_pin_pa6		io, pin_pa6, 307, hw_porta, 1, 6
#define hw_pin_pa7		io, pin_pa7, 308, hw_porta, 1, 7


/*	Class & methods
 */
#define hw_class_portb
#define HW_POP_portb(c,n,i,a,...)	__VA_ARGS__

#define hw_def_hw_reg_portb		, _hw_reg

/*	Instances		class, name, id, address
 */
#define hw_portb		portb, portb, 310, 0x36

/*	Class regs		class, rw, ra, riv, rvm, rwm, rfm
 */
#define hw_portb_port		crg, 8, 0x38-0x36, 0x00, 0x0F, 0x00
#define hw_portb_ddr		crg, 8, 0x37-0x36, 0x00, 0x0F, 0x00
#define hw_portb_pin		crg, 8, 0x36-0x36, 0x00, 0x0F, 0x00

/*	Pins			class, name, id, controller, bn, bp
 */
#define hw_port_b		io, port_b,  319, hw_portb, 8, 0
#define hw_pin_pb0		io, pin_pb0, 311, hw_portb, 1, 0
#define hw_pin_pb1		io, pin_pb1, 312, hw_portb, 1, 1
#define hw_pin_pb2		io, pin_pb2, 313, hw_portb, 1, 2
#define hw_pin_pb3		io, pin_pb3, 314, hw_portb, 1, 3


/*	Pins by numbers
 */
#define hw_is_dil_dil		, 1

#if HW_IS(dil,HWA_DEVICE_PACKAGE)
#
#  define hw_pin_2		hw_pin_pb0
#  define hw_pin_3		hw_pin_pb1
#  define hw_pin_4		hw_pin_pb3
#  define hw_pin_5		hw_pin_pb2
#  define hw_pin_6		hw_pin_pa7
#  define hw_pin_7		hw_pin_pa6
#  define hw_pin_8		hw_pin_pa5
#  define hw_pin_9		hw_pin_pa4
#  define hw_pin_10		hw_pin_pa3
#  define hw_pin_11		hw_pin_pa2
#  define hw_pin_12		hw_pin_pa1
#  define hw_pin_13		hw_pin_pa0
#
#endif


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t port ;
  hwa_r8_t ddr ;
} hwa_io_t ;

#define HWA_DCL_IOS		hwa_io_t porta, portb

#endif /* !defined __ASSEMBLER__ */
