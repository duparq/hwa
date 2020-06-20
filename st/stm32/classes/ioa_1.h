
/*  This file is part of the HWA project.
 *  Copyright (c) 2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

/**
 * @page stm32_ioa Class _ioa: General Purpose Input/Output
 *
 * `_ioa` objects are groups of one or more consecutive pins inside the same
 * GPIO port.
 */
#define hw_class__ioa


/*  The virtual object 'pin' handles the '(pin,...)' notation.
 */
#define hw_class__pin

#define hw_pin				_pin, 0


/*
 * @page stm32_ioa
 *
 * `HW_IO(port,bn,bp)` creates an I/O object made of `bn` consecutive gpio pins
 * of port `port` starting at position `bp`.
 *
 * @code
 * hw( toggle, HW_IO(porta,2,2) );	// Toggle PA3,PA2 at once.
 * @endcode
 */
/* #define HW_IO__ioa				, _hw_io_ioa */
/* #define _hw_io_ioa(o,p,pbn,pbp,bn,bp,...)	_ioa,p##_##bn##_##bp,p,bn,bp HW_EOL(__VA_ARGS__) */

/* #define HW_IO__gpa				, _hw_io_gpa */
/* #define _hw_io_gpa(p,a,bn,bp,...)		_ioa,p##_##bn##_##bp,p,bn,bp HW_EOL(__VA_ARGS__) */


/**
 * @page stm32_ioa
 *
 * The relative `port` names the GPIO port the I/O pertains to:
 *
 * @code
 * hw( turn, (rcc,((porta,0),port)), on );	// Clock the GPIO port of pin PA0
 * @endcode
 *
 * @code
 * hw( power, ((porta,0),port), on );		// Clock the GPIO port of pin PA0
 * @endcode
 */

/*  Port name of a pin
 */
#define hw__ioa_port			, _hw_ioa_port
#define _hw_ioa_port(o,p,...)		_hw_ioa_port1(p,hw_##p)
#define _hw_ioa_port1(...)		_hw_ioa_port2(__VA_ARGS__)
#define _hw_ioa_port2(p,c,...)		c,p,(__VA_ARGS__)


/*  Access 'mode' bits in crl/crh from a pin. [_HW_OX26]
 */
#define hw__ioa_mode			, _hw_ioa_mode

#define _hw_ioa_mode(...)		_hw_ioa_mode10(__VA_ARGS__)
#define _hw_ioa_mode10(o,p,bn,bp)	HW_Y(_hw_ioa_mode10_,_hw_is_1_##bn)(o,p,bn,bp)
#define _hw_ioa_mode10_0(o,p,bn,bp)	,o,HW_EM(is not a single pin)
#define _hw_ioa_mode10_1(o,p,bn,bp)	_hw_ioa_mode20(bp,hw__gpa_mode##bp,p,hw_##p)
#define _hw_ioa_mode20(...)		_hw_ioa_mode21(__VA_ARGS__)
#define _hw_ioa_mode21(bp,rc,r,rbn,rbp,p,pc,pa)	HW_OXR(rc,,r,rbn,rbp,pc,p,pa)


/*  Access 'cnf' bits in crl/crh from a pin. [_HW_OX26]
 */
#define hw__ioa_cnf			, _hw_ioa_cnf

#define _hw_ioa_cnf(...)		_hw_ioa_cnf10(__VA_ARGS__)
#define _hw_ioa_cnf10(o,p,bn,bp)	HW_Y(_hw_ioa_cnf10_,_hw_is_1_##bn)(o,p,bn,bp)
#define _hw_ioa_cnf10_0(o,p,bn,bp)	,o,HW_EM("is not a single pin")
#define _hw_ioa_cnf10_1(o,p,bn,bp)	_hw_ioa_cnf20(bp,hw__gpa_cnf##bp,p,hw_##p)
#define _hw_ioa_cnf20(...)		_hw_ioa_cnf21(__VA_ARGS__)
#define _hw_ioa_cnf21(bp,rc,r,rbn,rbp,p,pc,pa)	HW_OXR(rc,,r,rbn,rbp,pc,p,pa)


/*  Accept to append a number to a _ioa definition so that:
 *   * (portx,n) becomes a single pin at position n of portx.
 *   * (portx,n,p) becomes a set of n consecutive pins at position p of portx.
 */
#define hw__ioa_			, _hw_ioa_
#define _hw_ioa_(o,r,p,bn,bp)		HW_Y0(_hw_ioa_,_hw_is_1_##bn)(o,r,p,bn,bp)
#define _hw_ioa_0(o,r,...)		,(o,r),HW_EM(o has no relative r)
#define _hw_ioa_1(o,r,p,bn,bp)		HW_Y0(_hw_ioa1_,_hw_isa_4bn_##r)(o,r,p,bn,bp)
#define _hw_ioa1_1(o,r,p,bn,bp)		_ioa,p##_##bp##_##r,(p,bp,r)
#define _hw_ioa1_0(o,r,p,bn,bp)		_hw_ioa10(o,r,p,bn,bp,hw_##p##_##bn##_##bp##_##r)
#define _hw_ioa10(...)			_hw_ioa11(__VA_ARGS__)
#define _hw_ioa11(o,r,p,bn,bp,...)	HW_Y0(_hw_ioa2,_hw_isa_reg_##__VA_ARGS__)(o,r,p,bn,bp,__VA_ARGS__)
#define _hw_ioa21(o,r,p,bn,bp,cr,...)	HW_OXR(cr,r,__VA_ARGS__,_ioa,o,__VA_ARGS__)
#define _hw_ioa20(o,r,p,bn,bp,...)	_hw_ioa22(o,r,p,bn,bp,HW_XO(__VA_ARGS__))
#define _hw_ioa22(...)			_hw_ioa23(__VA_ARGS__)
#define _hw_ioa23(o,r,p,bn,bp,x,...)	HW_Y0(_hw_ioa23,x)(o,r,p,bn,bp,x,__VA_ARGS__)
#define _hw_ioa231(o,r,p,bn,bp,...)	,(o),HW_EM(o has no relative r)
#define _hw_ioa230(o,r,p,bn,bp,...)	__VA_ARGS__


/**
 * @page stm32_ioa
 *
 * `HW_ADDRESS()` returns an address for an I/O definition, computed as:
 *  address_of_port + (number_of_bits-1)*16 + position_of_lsb.
 *
 *  Ports are mapped 0x0400 bytes away in memory.
 *
 * @code
 * #if HW_ADDRESS(LED) == HW_ADDRESS((porta,9))
 * // LED is connected on pa9, or LED and pa9 do not exist.
 * #else
 * // LED is not connected on pa9, or pa9 or LED does not exist.
 * #endif
 * @endcode
 */
#define HW_ADDRESS__ioa		, _hw_adioa

#define _hw_adioa(o,p,bn,bp,...)	_hw_adioa01(hw_##p,bn,bp)
#define _hw_adioa01(...)		_hw_adioa02(__VA_ARGS__)
#define _hw_adioa02(c,a,bn,bp)		(a+(bn-1)*16+bp)


/**
 * @page stm32_ioa
 *
 * `HW_BITS()` returns the number of bits of an I/O definition:
 * @code
 * #if (HW_ADDRESS((porta,3)) != -1) && (HW_BITS((porta,3)) != 1)
 * #  error HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_BITS__ioa			, _hw_btioa
#define _hw_btioa(o, cn,bn,bp,...)	bn


/**
 * @page stm32_ioa
 *
 * `HW_POSITION()` returns the position of the least significant bit:
 * @code
 * #if (HW_ADDRESS((porta,3)) != -1) && (HW_POSITION((porta,3)) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_POSITION__ioa		, _hw_pnioa
#define _hw_pnioa(o, cn,bn,bp,...)	bp
