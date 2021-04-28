
/*  This file is part of the HWA project.
 *  Copyright (c) 2021 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_iob Class _iob: General Purpose Input/Output
 *
 * `_iob` objects are groups of one or more consecutive pins inside the same
 * @ref stm32_gpb "port".
 */
#define hw_class__iob


/**
 * @addtogroup stm32_iob
 *
 * @section stm32_iobrel Relatives
 *
 *  * `port`: the GPIO port the I/O pertains to.
 *
 */
#define hw__iob_port			, _hw_iob_port
#define _hw_iob_port(o,p,...)		_hw_iob_port1(p,hw_##p)
#define _hw_iob_port1(...)		_hw_iob_port2(__VA_ARGS__)
#define _hw_iob_port2(p,c,...)		c,p,(__VA_ARGS__)


/**
 * @addtogroup stm32_iob
 *
 * @section stm32_iobif Interface
 *
 * `HW_ADDRESS()` returns an address for an I/O definition, computed as:
 *
 *      address_of_port + (number_of_bits-1)*16 + position_of_lsb
 *
 * Ports are mapped every 0x0400 bytes in memory.
 *
 * @code
 * #if HW_ADDRESS(LED) == HW_ADDRESS((porta,9))
 * // LED is connected on pa9, or LED and pa9 do not exist.
 * #else
 * // LED is not connected on pa9, or pa9 or LED does not exist.
 * #endif
 * @endcode
 */
#define HW_ADDRESS__iob			, _hw_adiob
#define _hw_adiob(o,p,bn,bp,...)	_hw_adiob01(hw_##p,bn,bp)
#define _hw_adiob01(...)		_hw_adiob02(__VA_ARGS__)
#define _hw_adiob02(c,a,bn,bp)		(a+(bn-1)*16+bp)

/**
 * @addtogroup stm32_iob
 *
 * `HW_BITS()` returns the number of bits of an I/O definition:
 * @code
 * #if (HW_ADDRESS((porta,3)) != -1) && (HW_BITS((porta,3)) != 1)
 * #  error HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_BITS__iob			, _hw_btiob
#define _hw_btiob(o, cn,bn,bp,...)	bn


/**
 * @addtogroup stm32_iob
 *
 * `HW_POSITION()` returns the position of the least significant bit:
 * @code
 * #if (HW_ADDRESS((porta,3)) != -1) && (HW_POSITION((porta,3)) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_POSITION__iob		, _hw_pniob
#define _hw_pniob(o, cn,bn,bp,...)	bp


/*  Access 'mode' bits in crl/crh from a pin. [_HW_OX26]
 */
/* #define hw__iob_mode			, _hw_iob_mode */

/* #define _hw_iob_mode(...)		_hw_iob_mode10(__VA_ARGS__) */
/* #define _hw_iob_mode10(o,p,bn,bp)	HW_B(_hw_iob_mode10_,_hw_is_1_##bn)(o,p,bn,bp) */
/* #define _hw_iob_mode10_0(o,p,bn,bp)	,o,HW_EM(is not a single pin) */
/* #define _hw_iob_mode10_1(o,p,bn,bp)	_hw_iob_mode20(bp,hw__gpa_mode##bp,p,hw_##p) */
/* #define _hw_iob_mode20(...)		_hw_iob_mode21(__VA_ARGS__) */
/* #define _hw_iob_mode21(bp,rc,r,rbn,rbp,p,pc,pa)	HW_OXR(rc,,r,rbn,rbp,pc,p,pa) */


/*  Access 'cnf' bits in crl/crh from a pin. [_HW_OX26]
 */
/* #define hw__iob_cnf			, _hw_iob_cnf */

/* #define _hw_iob_cnf(...)		_hw_iob_cnf10(__VA_ARGS__) */
/* #define _hw_iob_cnf10(o,p,bn,bp)	HW_B(_hw_iob_cnf10_,_hw_is_1_##bn)(o,p,bn,bp) */
/* #define _hw_iob_cnf10_0(o,p,bn,bp)	,o,HW_EM("is not a single pin") */
/* #define _hw_iob_cnf10_1(o,p,bn,bp)	_hw_iob_cnf20(bp,hw__gpa_cnf##bp,p,hw_##p) */
/* #define _hw_iob_cnf20(...)		_hw_iob_cnf21(__VA_ARGS__) */
/* #define _hw_iob_cnf21(bp,rc,r,rbn,rbp,p,pc,pa)	HW_OXR(rc,,r,rbn,rbp,pc,p,pa) */


/*  Accept to append a number to a _iob definition so that:
 *   * (portx,n) becomes a single pin at position n of portx.
 *   * (portx,n,p) becomes a set of n consecutive pins at position p of portx.
 */
#define hw__iob_			, _hw_iob_
#define _hw_iob_(o,r,p,bn,bp)		_HW_B(_hw_iob_,_hw_is_1_##bn)(o,r,p,bn,bp)
#define _hw_iob_0(o,r,...)		,(o,r),HW_EM(o has no relative r)
#define _hw_iob_1(o,r,p,bn,bp)		_HW_B(_hw_iob1_,_hw_isa_4bn_##r)(o,r,p,bn,bp)
#define _hw_iob1_1(o,r,p,bn,bp)		_iob,p##_##bp##_##r,(p,bp,r)
#define _hw_iob1_0(o,r,p,bn,bp)		_hw_iob10(o,r,p,bn,bp,hw_##p##_##bn##_##bp##_##r)
#define _hw_iob10(...)			_hw_iob11(__VA_ARGS__)
#define _hw_iob11(o,r,p,bn,bp,...)	_HW_B(_hw_iob2,_hw_isa_reg_##__VA_ARGS__)(o,r,p,bn,bp,__VA_ARGS__)
#define _hw_iob21(o,r,p,bn,bp,cr,...)	HW_OXR(cr,r,__VA_ARGS__,_iob,o,__VA_ARGS__)
#define _hw_iob20(o,r,p,bn,bp,...)	_hw_iob22(o,r,p,bn,bp,HW_XO(__VA_ARGS__))
#define _hw_iob22(...)			_hw_iob23(__VA_ARGS__)
#define _hw_iob23(o,r,p,bn,bp,x,...)	_HW_B(_hw_iob23,x)(o,r,p,bn,bp,x,__VA_ARGS__)
#define _hw_iob231(o,r,p,bn,bp,...)	,(o),HW_EM(o has no relative r)
#define _hw_iob230(o,r,p,bn,bp,...)	__VA_ARGS__
