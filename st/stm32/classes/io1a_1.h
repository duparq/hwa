
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
 * `_io1a` objects are groups of one or more consecutive pins inside the same
 * GPIO port.
 */
#define hw_class__io1a


/**
 * @page stm32_io1a
 *
 * The relative `port` names the GPIO port the I/O pertains to:
 *
 * @code
 * hw( turn, (rcc,(pa0,port)), on );       // Clock the GPIO port of pin PA0
 * @endcode
 */
/* #define __io1a				, _HW_REL_io1a */
/* #define _HW_REL_io1a(o,x,...)		HW_Y(_HW_REL_io1a_,_hw_is_port_##x)(o,x,__VA_ARGS__) */
/* #define _HW_REL_io1a_1(o,x,i,p,...)	p */
/* #define _HW_REL_io1a_0(o,x,...)		HW_E_OO(o,x) */

/*  Port name of a pin
 */
#define _hw_rel__io1a_port(o,d)		HW_A1 d


/**
 * @page stm32_io1a
 * `HW_IDX()` returns a computed ID of an I/O definition.
 * @code
 * #if HW_IDX(LED) == HW_IDX(pa9)
 * // LED is connected on pa9, or LED and pa9 do not exist.
 * #else
 * // LED is not connected on pa9, or pa9 or LED does not exist.
 * #endif
 * @endcode
 */
#define HW_IDX__io1a			, _hw_idxio1a00
#define _hw_idxio1a00(o,i,p,bn,bp,...)	_hw_idxio1a01(hw_##p,bn,bp)
#define _hw_idxio1a01(...)		_hw_idxio1a02(__VA_ARGS__)
#define _hw_idxio1a02(c,i,a,bn,bp)	(a+bn*16+bp)


/**
 * @page stm32_io1a
 * `HW_PIN()` returns the canonical name (GPIO) of an I/O definition:
 * @code
 * hw( write, HW_PIN(1), 0 );
 * @endcode
 */


/**
 * @page stm32_io1a
 *
 * `HW_BITS()` returns the number of bits of an I/O definition:
 * @code
 * #if HW_ID(pa3) && (HW_BITS(pa3) != 1)
 * #  error HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_BITS__io1a			, _hw_btio1a
#define _hw_btio1a(o,i, cn,bn,bp,...)	bn


/**
 * @page stm32_io1a
 *
 * `HW_POSITION()` returns the position of the least significant bit:
 * @code
 * #if HW_ID(pa3) && (HW_POSITION(pa3) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_POSITION__io1a		, _hw_pnio1a
#define _hw_pnio1a(o,i, cn,bn,bp,...)	bp
