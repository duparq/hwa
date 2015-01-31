
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
#define hw_portb_port			crg, 8, 0x38, 0x3F, 0x00
#define hw_portb_ddr			crg, 8, 0x37, 0x3F, 0x00
#define hw_portb_pin			crg, 8, 0x36, 0x3F, 0x00

/*	Pins				class, name, id, controller, bn, bp
 */
#define hw_port_b			io, port_b,  309, hw_portb, 6, 0
#define hw_pin_pb0			io, pin_pb0, 301, hw_portb, 1, 0
#define hw_pin_pb1			io, pin_pb1, 302, hw_portb, 1, 1
#define hw_pin_pb2			io, pin_pb2, 303, hw_portb, 1, 2
#if !HW_IS(external,HW_DEVICE_CLK_SRC)		\
  && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#define hw_pin_pb3			io, pin_pb3, 304, hw_portb, 1, 3
#endif
#if !HW_IS(enabled,HW_DEVICE_CLOCK_OUTPUT)	\
  && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#define hw_pin_pb4			io, pin_pb4, 305, hw_portb, 1, 4
#endif
#if !HW_IS(enabled,HW_DEVICE_EXTERNAL_RESET)	\
  && !HW_IS(enabled,HW_DEVICE_DEBUG_WIRE)
#  define hw_pin_pb5			io, pin_pb5, 306, hw_portb, 1, 5
#endif

/*	Pins by numbers
 */
#define hw_is_8pdip_8pdip		, 1
#define hw_is_8soic_8soic		, 1
#define hw_is_8tssop_8tssop		, 1
#define hw_is_20qfn_20qfn		, 1
#define hw_is_20mlf_20mlf		, 1


#if HW_IS(8pdip,HW_A1(HW_DEVICE))		\
  || HW_IS(8soic,HW_A1(HW_DEVICE))		\
  || HW_IS(8tssop,HW_A1(HW_DEVICE))
#
#  define hw_pin_1			hw_pin_pb5
#  define hw_pin_2			hw_pin_pb3
#  define hw_pin_3			hw_pin_pb4
#  define hw_pin_5			hw_pin_pb0
#  define hw_pin_6			hw_pin_pb1
#  define hw_pin_7			hw_pin_pb2
#
#elif HW_IS(20qfn,HW_A1(HW_DEVICE))		\
  || HW_IS(20mlf,HW_A1(HW_DEVICE))
#
#  define hw_pin_1			hw_pin_pb5
#  define hw_pin_2			hw_pin_pb3
#  define hw_pin_5			hw_pin_pb4
#  define hw_pin_11			hw_pin_pb0
#  define hw_pin_12			hw_pin_pb1
#  define hw_pin_14			hw_pin_pb2
#
#elif !HW_IS(,HW_A1(HW_DEVICE))
#  error Package type not recognized
#endif


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t port ;
  hwa_r8_t ddr ;
} hwa_io_t ;

#define HWA_DCL_IOS			hwa_io_t portb

#endif /* !defined __ASSEMBLER__ */
