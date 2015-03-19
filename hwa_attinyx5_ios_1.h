
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*
 *	IO: General-Purpose Inputs & Outputs
 */

#include "hwa_atmelavr__io_1.h"

#define HWA_DCL_IOS			hwa_io6a_t portb


/*	Instances			class, name, id, address
 */
#define hw_portb			_io6a, portb, 300, 0x36

/*	Pins				class, name, id, controller, bn, bp
 */
#define hw_port_b			_io, port_b,  309, hw_portb, 6, 0
#define hw_pin_pb0			_io, pin_pb0, 301, hw_portb, 1, 0
#define hw_pin_pb1			_io, pin_pb1, 302, hw_portb, 1, 1
#define hw_pin_pb2			_io, pin_pb2, 303, hw_portb, 1, 2
#if !HW_IS(external,HW_DEVICE_CLK_SRC)		\
  && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define hw_pin_pb3			_io, pin_pb3, 304, hw_portb, 1, 3
#endif
#if !HW_IS(enabled,HW_DEVICE_CLOCK_OUTPUT)	\
  && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define hw_pin_pb4			_io, pin_pb4, 305, hw_portb, 1, 4
#endif
#if !HW_IS(enabled,HW_DEVICE_EXTERNAL_RESET)	\
  && !HW_IS(enabled,HW_DEVICE_DEBUG_WIRE)
#  define hw_pin_pb5			_io, pin_pb5, 306, hw_portb, 1, 5
#endif

/*	Pins by numbers
 */
#define _hw_is_8pdip_8pdip		, 1
#define _hw_is_8soic_8soic		, 1
#define _hw_is_8tssop_8tssop		, 1
#define _hw_is_20qfn_20qfn		, 1
#define _hw_is_20mlf_20mlf		, 1


#if HW_IS(8pdip,HW_DEVICE_PACKAGE)		\
  || HW_IS(8soic,HW_DEVICE_PACKAGE)		\
  || HW_IS(8tssop,HW_DEVICE_PACKAGE)
#
#  define hw_pin_1			hw_pin_pb5
#  define hw_pin_2			hw_pin_pb3
#  define hw_pin_3			hw_pin_pb4
#  define hw_pin_5			hw_pin_pb0
#  define hw_pin_6			hw_pin_pb1
#  define hw_pin_7			hw_pin_pb2
#
#elif HW_IS(20qfn,HW_DEVICE_PACKAGE)		\
  || HW_IS(20mlf,HW_DEVICE_PACKAGE)
#
#  define hw_pin_1			hw_pin_pb5
#  define hw_pin_2			hw_pin_pb3
#  define hw_pin_5			hw_pin_pb4
#  define hw_pin_11			hw_pin_pb0
#  define hw_pin_12			hw_pin_pb1
#  define hw_pin_14			hw_pin_pb2
#
#elif !HW_IS(,HW_DEVICE_PACKAGE)
#  error Package type not recognized
#endif
