
/*  This file is part of the HWA project.
 *  Copyright (c) 2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

/**
 * @page stm32_io1a Class _io1a: General Purpose Input/Output
 *
 * A class `_io1a` object is a group of consecutive pins inside the same GPIO
 * port. It can also be a single pin.
 *
 * `HW_PIN()` returns the canonical name of an I/O definition:
 * @code
 * hw( read, HW_PIN(int0) );
 * hw( write, HW_PIN(1), 0 );
 * @endcode
 */
#define _hw_class__io1a


/**
 * @page stm32_io1a
 *
 * `HW_BITS()` returns the number of bits of an I/O definition:
 * @code
 * #if HW_ID(pin_pa3) && (HW_BITS(pin_pa3) != 1)
 * #  error HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mtd_HW_BITS__io1a			, _HW_BITS__io1a

#define _HW_BITS__io1a(o,i, cn,bn,bp,...)	bn


/**
 * @page stm32_io1a
 *
 * `HW_POSITION()` returns the position of the least significant bit:
 * @code
 * #if HW_ID(pin_pa3) && (HW_POSITION(pin_pa3) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mtd_HW_POSITION__io1a		, _HW_POSITION__io1a

#define _HW_POSITION__io1a(o,i, cn,bn,bp,...)	bp

/**
 * @page stm32_io1a
 *
 * `_io1a` objects have a relative `port` that represent the GPIO port the I/O
 * definition pertains to.
 *
 * @code
 * hw( power, HW_RELATIVE(pin_pa0,port), on );	// Power the GPIO port of pin PA0 on
 * @endcode
 */
#define _hw_mtd_HW_RELATIVE__io1a	, _HW_REL_io1a

#define _hw_is_port_port

#define _HW_REL_io1a(o,x,...)		HW_X(_HW_REL_io1a,_hw_is_port_##x)(o,x,__VA_ARGS__)
#define _HW_REL_io1a_1(o,x,i,p,...)	p
#define _HW_REL_io1a_0(o,x,...)		HW_E_OO(o,x)
