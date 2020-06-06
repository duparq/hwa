
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
#define HW_ADDRESS__ioa			, _hw_adioa

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
#define HW_POSITION__ioa		, _hw_position_ioa
#define _hw_position_ioa(o,p,bn,bp,...)	bp


/*  Name of the io port of a pin
 *    Could use HW_XO but we know that the port exists, so let's expand its definition here.
 */
#define hw__ioa_port			, _hw_ioa_port
#define _hw_ioa_port(o,p,...)		_hw_ioa_port1(p,hw_##p)
#define _hw_ioa_port1(...)		_hw_ioa_port2(__VA_ARGS__)
#define _hw_ioa_port2(p,c,...)		c,p,(__VA_ARGS__)


/*  Accept to append a number to a _ioa definition so that:
 *   * (portx,n) becomes a single pin at position n of portx.
 *   * (portx,n,p) becomes a set of n consecutive pins at position p of portx.
 */
#define hw__ioa_			, _hw_ioa_
#define _hw_ioa_(o,r,p,bn,bp)		HW_Y0(_hw_ioa_,_hw_is_1_##bn)(o,r,p,bn,bp)
#define _hw_ioa_0(o,r,...)		,(o,r),HW_EM(o has no relative r)
#define _hw_ioa_1(o,r,p,bn,bp)		HW_Y0(_hw_ioa1_,_hw_isa_4bn_##r)(o,r,p,bn,bp)
#define _hw_ioa1_1(o,r,p,bn,bp)		_ioa,p##_##bp##_##r,(p,bp,r)
#define _hw_ioa1_0(o,r,p,bn,bp)		,(o),HW_EM(o has no relative r)


/*  Process HW_IO()
 *   * HW_IO(pin,...)
 */
#define hw_class__ioa_io

#define HW_IO__ioa			, _hw_io_ioa
//#define _hw_io_ioa(o,p,bn,bp,...)	_ioa,p##_##bn##_##bp,(p,bn,bp)
/* #define _hw_io_ioa(o,p,bn,bp,...)	HW_Y(_hw_io_ioa,__VA_ARGS__)(o,p,bn,bp,__VA_ARGS__) */
/* #define _hw_io_ioa1(o,p,bn,bp,...)	_ioa,p##_##bn##_##bp,(p,bn,bp) */
  //_hw_io_ioa0((port1,4,2),port1,4,2,(port1,2,6),);
/* #define _hw_io_ioa0(o1,p1,bn1,bp1,...)	_ioa,p##_##bn##_##bp,(p,bn,bp) */
#define _hw_io_ioa(o,p,bn,bp,...)	_iox,HW_IO,(p,bn,bp),__VA_ARGS__
