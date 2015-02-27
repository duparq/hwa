
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*
 *	IO: General-Purpose Inputs & Outputs
 */

#include "hwa_atmelavr__io_1.h"

#define HWA_DCL_IOS			hwa_io8a_t portb, portc, portd


/*	Instances			class, name, id, address
 */
#define hw_portb			_io8a, portb, 300, 0x23
#define hw_portc			_io8a, portc, 310, 0x26
#define hw_portd			_io8a, portd, 320, 0x29


/*	Pins				class, name, id, controller, bn, bp
 *
 *	FIXME: remove definition of pins used for alternate functions (XTAL, etc.)
 */
#define hw_port_b			_io, port_b,  309, hw_portb, 8, 0
#define hw_pin_pb0			_io, pin_pb0, 301, hw_portb, 1, 0
#define hw_pin_pb1			_io, pin_pb1, 302, hw_portb, 1, 1
#define hw_pin_pb2			_io, pin_pb2, 303, hw_portb, 1, 2
#define hw_pin_pb3			_io, pin_pb3, 304, hw_portb, 1, 3
#define hw_pin_pb4			_io, pin_pb4, 305, hw_portb, 1, 4
#define hw_pin_pb5			_io, pin_pb5, 306, hw_portb, 1, 5
#define hw_pin_pb6			_io, pin_pb6, 307, hw_portb, 1, 6
#define hw_pin_pb7			_io, pin_pb7, 308, hw_portb, 1, 7

#define hw_port_c			_io, port_c,  319, hw_portc, 8, 0
#define hw_pin_pc0			_io, pin_pc0, 311, hw_portc, 1, 0
#define hw_pin_pc1			_io, pin_pc1, 312, hw_portc, 1, 1
#define hw_pin_pc2			_io, pin_pc2, 313, hw_portc, 1, 2
#define hw_pin_pc3			_io, pin_pc3, 314, hw_portc, 1, 3
#define hw_pin_pc4			_io, pin_pc4, 315, hw_portc, 1, 4
#define hw_pin_pc5			_io, pin_pc5, 316, hw_portc, 1, 5
#define hw_pin_pc6			_io, pin_pc6, 317, hw_portc, 1, 6

#define hw_port_d			_io, port_d,  329, hw_portd, 8, 0
#define hw_pin_pd0			_io, pin_pd0, 321, hw_portd, 1, 0
#define hw_pin_pd1			_io, pin_pd1, 322, hw_portd, 1, 1
#define hw_pin_pd2			_io, pin_pd2, 323, hw_portd, 1, 2
#define hw_pin_pd3			_io, pin_pd3, 324, hw_portd, 1, 3
#define hw_pin_pd4			_io, pin_pd4, 325, hw_portd, 1, 4
#define hw_pin_pd5			_io, pin_pd5, 326, hw_portd, 1, 5
#define hw_pin_pd6			_io, pin_pd6, 327, hw_portd, 1, 6
#define hw_pin_pd7			_io, pin_pd7, 328, hw_portd, 1, 7

#define hw_pin_rxd			hw_pin_pd0
#define hw_pin_txd			hw_pin_pd1

/*	Pins by numbers
 */
#define hw_is_dil_dil			, 1
#define hw_is_28pdip_28pdip		, 1
#define hw_is_28mlf_28mlf		, 1
#define hw_is_32mlf_32mlf		, 1


#if HW_IS(dil,HW_DEVICE_PACKAGE) || HW_IS(28pdip,HW_DEVICE_PACKAGE)
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
#elif HW_IS(28mlf,HW_DEVICE_PACKAGE)
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
#elif HW_IS(32mlf,HW_DEVICE_PACKAGE)
#
#  define hw_pin_1			hw_pin_pd3
#  define hw_pin_2			hw_pin_pd4
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
#  define hw_pin_19			hw_pin_adc6
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
#elif !HW_IS(,HW_DEVICE_PACKAGE)
#  error Package type must be one of `dil`, `28pdip`, `28mlf`, or `32mlf`
#endif
