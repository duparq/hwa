
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
 * The `HW_BITS()` instruction returns the number of bits of an I/O definition:
 *
 * @code
 * #if HW_ID(pa3) && (HW_BITS(pa3) != 1)
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
 * #if HW_ID(pa3) && (HW_POSITION(pa3) != 3)
 * #  HWA is damaged!
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

#define HW_IO__io1a			, _hw_io_io1a
#define _hw_io_io1a(o,i,p,bn,bp,...)	io(HW_A0(hw_##p),p##_##bn##_##bp,-1,p,bn,bp)
