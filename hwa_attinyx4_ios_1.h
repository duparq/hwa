
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr__io_1.h"
//#include "hwa_atmelavr__io8a_1.h"

#define HWA_DCL_IOS			hwa_io8a_t porta, portb


/*	Instances			class, name, id, address
 */
#define hw_porta			_io8a, porta, 300, 0x39
#define hw_portb			_io8a, portb, 310, 0x36


/*  Pins				class, name, id, controller, bn, bp
 */
#define hw_pin_pa0			_io, pin_pa0, 301, hw_porta, 1, 0
#define hw_pin_pa1			_io, pin_pa1, 302, hw_porta, 1, 1
#define hw_pin_pa2			_io, pin_pa2, 303, hw_porta, 1, 2
#define hw_pin_pa3			_io, pin_pa3, 304, hw_porta, 1, 3
#define hw_pin_pa4			_io, pin_pa4, 305, hw_porta, 1, 4
#define hw_pin_pa5			_io, pin_pa5, 306, hw_porta, 1, 5
#define hw_pin_pa6			_io, pin_pa6, 307, hw_porta, 1, 6
#define hw_pin_pa7			_io, pin_pa7, 308, hw_porta, 1, 7
#define hw_port_a			_io, port_a,  309, hw_porta, 8, 0

#if !HW_IS(external,HW_DEVICE_CLK_SRC)		\
  && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define hw_pin_pb0			_io, pin_pb0, 311, hw_portb, 1, 0
#endif
#define hw_pin_pb1			_io, pin_pb1, 312, hw_portb, 1, 1
#if !HW_IS(enabled,HW_DEVICE_CLOCK_OUTPUT)	\
  && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define hw_pin_pb2			_io, pin_pb2, 313, hw_portb, 1, 2
#endif
#if !HW_IS(enabled,HW_DEVICE_EXTERNAL_RESET)	\
  && !HW_IS(enabled,HW_DEVICE_DEBUG_WIRE)
#  define hw_pin_pb3			_io, pin_pb3, 314, hw_portb, 1, 3
#endif
#define hw_port_b			_io, port_b,  319, hw_portb, 4, 0


/*	Pins by numbers
 */
#define hw_is_14pdip_14pdip		, 1

#if HW_IS(14pdip,HW_DEVICE_PACKAGE)
#
#  define hw_pin_2			hw_pin_pb0
#  define hw_pin_3			hw_pin_pb1
#  define hw_pin_4			hw_pin_pb3
#  define hw_pin_5			hw_pin_pb2
#  define hw_pin_6			hw_pin_pa7
#  define hw_pin_7			hw_pin_pa6
#  define hw_pin_8			hw_pin_pa5
#  define hw_pin_9			hw_pin_pa4
#  define hw_pin_10			hw_pin_pa3
#  define hw_pin_11			hw_pin_pa2
#  define hw_pin_12			hw_pin_pa1
#  define hw_pin_13			hw_pin_pa0
#
#elif !HW_IS(,HW_DEVICE_PACKAGE)
#  error Package type not recognized
#endif
