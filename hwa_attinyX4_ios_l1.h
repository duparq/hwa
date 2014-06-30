
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


/*	Controllers		'ctr', class, name, address
 */
#define hw_porta		ctr, io8, porta, 0x21
#define hw_portb		ctr, io4, portb, 0x36


/*	Registers		'reg', rw, ra, riv, rvm, rwm
 */
#define hw_io8_port		mem, reg, 8, 0x3B-0x21, 0x00, 0xFF
#define hw_io8_ddr		mem, reg, 8, 0x3A-0x21, 0x00, 0xFF
#define hw_io8_pin		mem, reg, 8, 0x39-0x21, 0x00, 0xFF
#define hw_io8_didr		mem, reg, 8, 0x21-0x21, 0x00, 0xFF

#define hw_io4_port		mem, reg, 8, 0x38-0x36, 0x00, 0x0F
#define hw_io4_ddr		mem, reg, 8, 0x37-0x36, 0x00, 0x0F
#define hw_io4_pin		mem, reg, 8, 0x36-0x36, 0x00, 0x0F
#define hw_io4_didr		mem, reg, 8,   -1-0x36, 0x00, 0x0F /* Does not exist */


/*	Portable io names to be used with io functions
 *
 *				'io', name, controller, bn, bp
 */
#define hw_port_a		ctr, io, port_a, hw_porta, 8, 0
#define hw_pin_pa0		ctr, io, pin_pa0, hw_porta, 1, 0
#define hw_pin_pa1		ctr, io, pin_pa1, hw_porta, 1, 1
#define hw_pin_pa2		ctr, io, pin_pa2, hw_porta, 1, 2
#define hw_pin_pa3		ctr, io, pin_pa3, hw_porta, 1, 3
#define hw_pin_pa4		ctr, io, pin_pa4, hw_porta, 1, 4
#define hw_pin_pa5		ctr, io, pin_pa5, hw_porta, 1, 5
#define hw_pin_pa6		ctr, io, pin_pa6, hw_porta, 1, 6
#define hw_pin_pa7		ctr, io, pin_pa7, hw_porta, 1, 7

#define hw_port_b		ctr, io, port_b, hw_portb, 8, 0
#define hw_pin_pb0		ctr, io, pin_pb0, hw_portb, 1, 0
#define hw_pin_pb1		ctr, io, pin_pb1, hw_portb, 1, 1
#define hw_pin_pb2		ctr, io, pin_pb2, hw_portb, 1, 2
#define hw_pin_pb3		ctr, io, pin_pb3, hw_portb, 1, 3


/*	General-purpose ios by pin numbers
 */
#define hw_pin_2		ctr, io, pin_2,  hw_portb, 1, 0
#define hw_pin_3		ctr, io, pin_3,  hw_portb, 1, 1
#define hw_pin_4		ctr, io, pin_4,  hw_portb, 1, 3
#define hw_pin_5		ctr, io, pin_5,  hw_portb, 1, 2
#define hw_pin_6		ctr, io, pin_6,  hw_porta, 1, 7
#define hw_pin_7		ctr, io, pin_7,  hw_porta, 1, 6
#define hw_pin_8		ctr, io, pin_8,  hw_porta, 1, 5
#define hw_pin_9		ctr, io, pin_9,  hw_porta, 1, 4
#define hw_pin_10		ctr, io, pin_10, hw_porta, 1, 3
#define hw_pin_11		ctr, io, pin_11, hw_porta, 1, 2
#define hw_pin_12		ctr, io, pin_12, hw_porta, 1, 1
#define hw_pin_13		ctr, io, pin_13, hw_porta, 1, 0


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


/*	Equality test
 */
#define hw_is_io_io	,1
#define _hw_eq_io(ctr1,cc1,ion1, sctr1,scc1,scn1,sca1,sbn1,sbp1, ...)	\
  HW_G2(_hw_eq_io,HW_IS(io,hw_class(__VA_ARGS__)))			\
  (ctr1,cc1,ion1, sctr1,scc1,scn1,sca1,sbn1,sbp1, __VA_ARGS__)
#define _hw_eq_io_0(...)	0
#define _hw_eq_io_1(ctr1,cc1,ion1, sctr1,scc1,scn1,sca1,sbn1,sbp1,	\
		    ctr2,cc2,ion2, sctr2,scc2,scn2,sca2,sbn2,sbp2)	\
  (sca1==sca2 && sbn1==sbn2 && sbp1==sbp2)


/* #define hw_ra_io4_isfn */
/* #define hw_ra_io8_isfn */
/* #define hw_ra_io4		hw_ra_io8 */
/* #define hw_ra_io8(cn,...)	HW_A0(__VA_ARGS__) */
