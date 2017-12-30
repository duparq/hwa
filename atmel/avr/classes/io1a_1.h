
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
#define _hw_class__io1a


/**
 * @page atmelavr_io1a
 *
 * The `HW_BITS()` instruction returns the number of bits of an I/O definition:
 *
 * @code
 * #if HW_ID(pa3) && (HW_BITS(pa3) != 1)
 * #  error HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mtd_HW_BITS__io1a			, _HW_BITS__io1a

#define _HW_BITS__io1a(o,i, cn,bn,bp,...)	bn


/**
 * @page atmelavr_io1a
 *
 * For a group of consecutive pins, the `HW_POSITION()` instruction gives the position
 * of the least significant bit:
 *
 * @code
 * #if HW_ID(pa3) && (HW_POSITION(pa3) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mtd_HW_POSITION__io1a		, _HW_POSITION__io1a

#define _HW_POSITION__io1a(o,i, cn,bn,bp,...)	bp

/**
 * @page atmelavr_io1a
 * @section atmelavr_io1a_rel Relatives
 *
 * `_io1a` objects have the following relatives:
 *
 *  * `port`: the I/O port the object pertains to:
 *     @code
 *     HW_RELATIVE( pa0, port )
 *     @endcode
 *  * `pcic`: the pin-change interrupt controller:
 *     @code
 *     HW_RELATIVE( pa0, pcic )
 *     @endcode
 */
/*  Class-defined HW_RELATIVE()
 */
#define _hw_mtd_HW_RELATIVE__io1a	, _HW_REL_io1a

#define _HW_REL_io1a(o,x,...)		HW_Y(_HW_REL_io1a,_hw_is_port_##x)(o,x,__VA_ARGS__)
#define _HW_REL_io1a_1(o,x,i,p,...)	p
#define _HW_REL_io1a_0(o,x,...)		HW_E_OO(o,x)
