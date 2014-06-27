
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

#include "hwa_atmelavr_ios_l1.h"


/*	Controllers		'ctr', name, class, address
 */
#define hw_porta		ctr, porta, io8, 0x21
#define hw_portb		ctr, portb, io4, 0x36


/*	Registers		'reg', rw, ra, riv, rvm, rwm
 */
#define hw_io8_port		reg, port, 8, 0x3B-0x21, 0x00, 0xFF
#define hw_io8_ddr		reg, ddr,  8, 0x3A-0x21, 0x00, 0xFF
#define hw_io8_pin		reg, pin,  8, 0x39-0x21, 0x00, 0xFF
#define hw_io8_didr		reg, didr, 8, 0x21-0x21, 0x00, 0xFF

#define hw_io4_port		reg, port, 8, 0x38-0x36, 0x00, 0x0F
#define hw_io4_ddr		reg, ddr,  8, 0x37-0x36, 0x00, 0x0F
#define hw_io4_pin		reg, pin,  8, 0x36-0x36, 0x00, 0x0F
#define hw_io4_didr		reg, didr, 8,   -1-0x36, 0x00, 0x0F /* Does not exist */


/*	Portable io names to be used with io functions
 *
 *				'io', name, controller, bn, bp
 */
#define hw_port_a		io, port_a, hw_porta, 8, 0
#define hw_pin_pa0		io, pin_pa0, hw_porta, 1, 0
#define hw_pin_pa1		io, pin_pa1, hw_porta, 1, 1
#define hw_pin_pa2		io, pin_pa2, hw_porta, 1, 2
#define hw_pin_pa3		io, pin_pa3, hw_porta, 1, 3
#define hw_pin_pa4		io, pin_pa4, hw_porta, 1, 4
#define hw_pin_pa5		io, pin_pa5, hw_porta, 1, 5
#define hw_pin_pa6		io, pin_pa6, hw_porta, 1, 6
#define hw_pin_pa7		io, pin_pa7, hw_porta, 1, 7

#define hw_port_b		io, port_b, hw_portb, 8, 0
#define hw_pin_pb0		io, pin_pb0, hw_portb, 1, 0
#define hw_pin_pb1		io, pin_pb1, hw_portb, 1, 1
#define hw_pin_pb2		io, pin_pb2, hw_portb, 1, 2
#define hw_pin_pb3		io, pin_pb3, hw_portb, 1, 3


/*	General-purpose ios by pin numbers
 */
#define hw_pin_2		io, pin_2,  hw_portb, 1, 0
#define hw_pin_3		io, pin_3,  hw_portb, 1, 1
#define hw_pin_4		io, pin_4,  hw_portb, 1, 3
#define hw_pin_5		io, pin_5,  hw_portb, 1, 2
#define hw_pin_6		io, pin_6,  hw_porta, 1, 7
#define hw_pin_7		io, pin_7,  hw_porta, 1, 6
#define hw_pin_8		io, pin_8,  hw_porta, 1, 5
#define hw_pin_9		io, pin_9,  hw_porta, 1, 4
#define hw_pin_10		io, pin_10, hw_porta, 1, 3
#define hw_pin_11		io, pin_11, hw_porta, 1, 2
#define hw_pin_12		io, pin_12, hw_porta, 1, 1
#define hw_pin_13		io, pin_13, hw_porta, 1, 0


/*	Analog comparator inputs
 */
/* #define hw_pin_ain0		aio, pin_ain0, pin_12, hw_acmp0 */
/* #define hw_pin_ain1		aio, pin_ain1, pin_11, hw_acmp0 */


/** \brief	Part of HWA struct for ios
 */
#if !defined __ASSEMBLER__
typedef struct {
  hwa_r8_t port ;
  hwa_r8_t ddr ;
  hwa_r8_t didr ;
} hwa_io_t ;
#endif


#define HWA_DCL_IOS				\
  hwa_io_t porta ;				\
  hwa_io_t portb ;
