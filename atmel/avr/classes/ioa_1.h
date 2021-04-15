
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_ioa Class _ioa: General Purpose Input/Output
 *
 * This class implements a group of consecutive I/O pins inside the same @ref
 * atmelavr_gpa "_gpa" GPIO port. It handles not-connected pins and triggers an
 * error if such a pin is addressed (but no error is triggered if you access
 * the registers directly).
 *
 * It supports HW_ADDRESS(), HW_BITS(), and HW_POSITION().
 */
#define hw_class__ioa

#define _hw_is__ioa__ioa		, 1

#define HW_ADDRESS__ioa			, _hw_adioa

#define _hw_adioa(o,p,bn,bp,...)	_hw_adioa01(hw_##p,bn,bp)
#define _hw_adioa01(...)		_hw_adioa02(__VA_ARGS__)
#define _hw_adioa02(c,a,bn,bp)		(((bn-1)*16+bp)*0x10000 + a)

#define HW_BITS__ioa			, _hw_bits_ioa
#define _hw_bits_ioa(o,p,bn,bp,...)	bn

#define HW_POSITION__ioa		, _hw_position_ioa
#define _hw_position_ioa(o,p,bn,bp,...)	bp


/**
 * @addtogroup atmelavr_ioa
 * @section atmelavr_ioarel Relatives
 *
 * IOs are relatives of their port:
 *
 *  * `(porta,1)`: pin PA1
 *  * `(portb,4,2)`: pins PB5 PB4 PB3 PB2
 *
 * and have their port as relative:
 *
 *  * `((portb,1),port)`: portb
 *
 * Single IO pins can be designated as relatives of the virtual `pin` object:
 *
 *  * `(pin,int0)`: pin named int0
 *  * `(pin,1)`: pin number 1 (depends on the package of the device)
 *
 * Analog input pins have a `did` register that disables the digital input stage:
 *
 *  * `(portb,1,0,did)`: DID logical register for PB0
 */
#define hw__ioa_			, _hw_ioa_
#define _hw_ioa_(o,r,p,bn,bp)		_HW_B(_hw_ioa_,_hw_is_1_##bn)(o,r,p,bn,bp)
#define _hw_ioa_0(o,r,...)		,(o,r),HW_EM_OO(o,r)
#define _hw_ioa_1(o,r,p,bn,bp)		_HW_B(_hw_ioa1_,_hw_isa_3bn_##r)(o,r,p,bn,bp)
#define _hw_ioa1_1(o,r,p,bn,bp)		_ioa,p##_##bp##_##r,(p,bp,r)
#define _hw_ioa1_0(o,r,p,bn,bp)		_hw_ioa10(o,r,p,bn,bp,hw_##p##_##bn##_##bp##_##r)
#define _hw_ioa10(...)			_hw_ioa11(__VA_ARGS__)
#define _hw_ioa11(o,r,p,bn,bp,...)	_HW_B(_hw_ioa2,_hw_isa_reg_##__VA_ARGS__)(o,r,p,bn,bp,__VA_ARGS__)
#define _hw_ioa21(o,r,p,bn,bp,cr,...)	HW_OXR(cr,r,__VA_ARGS__,_ioa,o,__VA_ARGS__)

#define _hw_ioa20(o,r,p,bn,bp,...)	_hw_ioa22(o,r,p,bn,bp,HW_XO(__VA_ARGS__))
#define _hw_ioa22(...)			_hw_ioa23(__VA_ARGS__)
#define _hw_ioa23(o,r,p,bn,bp,x,...)	_HW_B(_hw_ioa23,x)(o,r,p,bn,bp,x,__VA_ARGS__)
#define _hw_ioa231(o,r,p,bn,bp,...)	,(o),HW_EM_OO(o,r)
#define _hw_ioa230(o,r,p,bn,bp,...)	__VA_ARGS__

#define hw__ioa_port			, _hw_ioa_port
#define _hw_ioa_port(o,p,...)		_hw_ioa_port1(p,hw_##p)
#define _hw_ioa_port1(...)		_hw_ioa_port2(__VA_ARGS__)
#define _hw_ioa_port2(p,c,...)		c,p,(__VA_ARGS__)
