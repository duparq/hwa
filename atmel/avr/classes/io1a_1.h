
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

/**
 * @page atmelavr_io1a Class _io1a: General Purpose Input/Output
 *
 * A class `_io1a` object is a single or a group of consecutive pins inside the
 * same I/O port.
 *
 * The instruction `HW_PIN()` can be used to get the canonical name of an I/O
 * definition:
 * @code
 * hw( read, HW_PIN(int0) );
 * hw( write, HW_PIN(1), 0 );
 * @endcode
 */
#define hw_class__io1a


/**
 * @page atmelavr_io1a
 *
 * `HW_ADDRESS()` returns an address for an I/O definition.
 *
 *  The address is computed as:
 *  ((number_of_bits-1)*16+position_of_lsb)*0x10000 + address_of_port.
 *
 * @code
 * #if HW_ADDRESS(LED) == HW_ADDRESS(pa2)
 * // LED is connected on pa2, or LED and pa2 do not exist.
 * #else
 * // LED is not connected on pa2, or pa9 or LED does not exist.
 * #endif
 * @endcode
 */
#define HW_ADDRESS__io1a		, _hw_adio1a

#define _hw_adio1a(o,i,p,bn,bp,...)	_hw_adio1a01(hw_##p,bn,bp)
#define _hw_adio1a01(...)		_hw_adio1a02(__VA_ARGS__)
#define _hw_adio1a02(c,i,a,bn,bp)	(((bn-1)*16+bp)*0x10000 + a)


/**
 * @page atmelavr_io1a
 *
 * The `HW_BITS()` instruction returns the number of bits of an I/O definition:
 *
 * @code
 * #if (HW_ADDRESS(pa3) != -1) && (HW_BITS(pa3) != 1)
 * #  error HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_BITS__io1a				, _hw_bits_io1a
#define _hw_bits_io1a(o,i,p,bn,bp,...)		bn


/*
 * @page atmelavr_io1a
 *
 * For a group of consecutive pins, the `HW_POSITION()` instruction gives the position
 * of the least significant bit:
 *
 * @code
 * #if (HW_ADDRESS(pa3) != -1) && (HW_POSITION(pa3) != 3)
 * #  error HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_POSITION__io1a			, _hw_position_io1a
#define _hw_position_io1a(o,i,p,bn,bp,...)	bp


/*  Port name of a pin
 */
#define _hw_rel__io1a_port(o,d)			HW_A1 d


/*  Handle definitions such as HW_IO(pb1)
 */
#define hw_class__io1a_io

#define HW_IO__io1a				, _hw_io_io1a
#define _hw_io_io1a(o,i,p,bn,bp,...)		xb(_io1a,p##_##bn##_##bp,-1,p,bn,bp)
