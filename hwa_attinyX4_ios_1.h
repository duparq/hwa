
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*
 *	IO: General-Purpose Inputs & Outputs
 *
 *	  Note: all hw_io_ functions are declared in hwa_atmelavr_io_l1.h
 *
 *	  Note: porta & portb use both the same hwa_io_t struct but inexistant
 *	  portb.didr is not committed and not accessed by hw_io_config.
 */

#include "hwa_atmelavr_ios_1.h"


/*	Class & method
 */
#define hw_class_porta
#define hw_def_hw_bits_porta	, _hw_bits

/*	Instances		class, name, id, address
 */
#define hw_porta		porta, porta, 300, 0x21

/*	Class regs		'reg', rw, ra, riv, rvm, rwm
 */
#define hw_porta_port		reg, 8, 0x3B-0x21, 0x00, 0xFF
#define hw_porta_ddr		reg, 8, 0x3A-0x21, 0x00, 0xFF
#define hw_porta_pin		reg, 8, 0x39-0x21, 0x00, 0xFF
//#define hw_porta_didr		reg, 8, 0x21-0x21, 0x00, 0xFF

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
#define hw_def_hw_bits_portb	, _hw_bits

/*	Instances		class, name, id, address
 */
#define hw_portb		portb, portb, 310, 0x36

/*	Class regs		'reg', rw, ra, riv, rvm, rwm
 */
#define hw_portb_port		reg, 8, 0x38-0x36, 0x00, 0x0F
#define hw_portb_ddr		reg, 8, 0x37-0x36, 0x00, 0x0F
#define hw_portb_pin		reg, 8, 0x36-0x36, 0x00, 0x0F

/*	Pins			class, name, id, controller, bn, bp
 */
#define hw_port_b		io, port_b,  319, hw_portb, 8, 0
#define hw_pin_pb0		io, pin_pb0, 311, hw_portb, 1, 0
#define hw_pin_pb1		io, pin_pb1, 312, hw_portb, 1, 1
#define hw_pin_pb2		io, pin_pb2, 313, hw_portb, 1, 2
#define hw_pin_pb3		io, pin_pb3, 314, hw_portb, 1, 3


/*	Pins by numbers
 */
#if defined HW_PKG_DIL
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
  hwa_r8_t didr ;
} hwa_io_t ;

#define HWA_DCL_IOS				\
  hwa_io_t porta ;				\
  hwa_io_t portb ;

#endif /* !defined __ASSEMBLER__ */
