
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
 * hw( turn, (rcc,(pa0,port)), on );	   // Clock the GPIO port of pin PA0
 * @endcode
 */

/*  Port name of a pin
 */
//#define hw__io1a_port(o,d)		HW_A0 d

#define hw__io1a_port			, _hw_io1a_port

//#define _hw_io1a_port(o,p,bn,bp)	_io1a,o,(p,bn,bp),port, HW_XO(p)
#define _hw_io1a_port(o,p,...)		_io1a,o,(p,__VA_ARGS__),port, HW_XO(p)


/**
 * @page stm32_io1a
 *
 * `HW_ADDRESS()` returns an address for an I/O definition.
 *
 *  The address is computed as:
 *  address_of_port + (number_of_bits-1)*16 + position_of_lsb.
 *
 *  Ports are maped 0x0400 bytes away in memory.
 *
 * @code
 * #if HW_ADDRESS(LED) == HW_ADDRESS(pa9)
 * // LED is connected on pa9, or LED and pa9 do not exist.
 * #else
 * // LED is not connected on pa9, or pa9 or LED does not exist.
 * #endif
 * @endcode
 */
#define HW_ADDRESS__io1a		, _hw_adio1a

#define _hw_adio1a(o,p,bn,bp,...)	_hw_adio1a01(hw_##p,bn,bp)
#define _hw_adio1a01(...)		_hw_adio1a02(__VA_ARGS__)
#define _hw_adio1a02(c,a,bn,bp)		(a+(bn-1)*16+bp)


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
 * #if (HW_ADDRESS(pa3) != -1) && (HW_BITS(pa3) != 1)
 * #  error HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_BITS__io1a			, _hw_btio1a
#define _hw_btio1a(o, cn,bn,bp,...)	bn


/**
 * @page stm32_io1a
 *
 * `HW_POSITION()` returns the position of the least significant bit:
 * @code
 * #if (HW_ADDRESS(pa3) != -1) && (HW_POSITION(pa3) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_POSITION__io1a		, _hw_pnio1a
#define _hw_pnio1a(o, cn,bn,bp,...)	bp
