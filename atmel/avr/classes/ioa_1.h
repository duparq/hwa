
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

/**
 * @page atmelavr_ioa Class _ioa: General Purpose Input/Output
 *
 * A class `_ioa` object is a single or a group of consecutive pins inside the
 * same I/O port.
 *
 * The instruction `HW_PIN()` can be used to get the canonical name of an I/O
 * definition:
 * @code
 * hw( read, HW_PIN(int0) );
 * hw( write, HW_PIN(1), 0 );
 * @endcode
 */
#define hw_class__ioa

#define _hw_is__ioa__ioa		, 1

/**
 * @page atmelavr_ioa
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
#define HW_ADDRESS__ioa		, _hw_adioa

#define _hw_adioa(o,p,bn,bp,...)	_hw_adioa01(hw_##p,bn,bp)
#define _hw_adioa01(...)		_hw_adioa02(__VA_ARGS__)
#define _hw_adioa02(c,a,bn,bp)		(((bn-1)*16+bp)*0x10000 + a)


/**
 * @page atmelavr_ioa
 *
 * The `HW_BITS()` instruction returns the number of bits of an I/O definition:
 *
 * @code
 * #if (HW_ADDRESS(pa3) != -1) && (HW_BITS(pa3) != 1)
 * #  error HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_BITS__ioa			, _hw_bits_ioa
#define _hw_bits_ioa(o,p,bn,bp,...)	bn


/*
 * @page atmelavr_ioa
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
#define HW_POSITION__ioa			, _hw_position_ioa
#define _hw_position_ioa(o,p,bn,bp,...)	bp


/*  Port name of a pin
 */
//#define hw__ioa_port(o,d)			HW_A1 d
#define hw__ioa_port(o,d)			HW_A0 d


/*  Handle definitions such as HW_IO(pb1)
 */
#define hw_class__ioa_io

#define HW_IO__ioa				, _hw_io_ioa
#define _hw_io_ioa(o,p,bn,bp,...)		xb(_ioa,p##_##bn##_##bp,-1,p,bn,bp)
