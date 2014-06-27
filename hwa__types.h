
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/** \brief	1 if the object has a known type, 0 otherwise
 */
#define HW_CT(...)		HW_IS(ok, HW_A1(hw_type_ ## __VA_ARGS__))


/** \brief	Type of the first argument. That is:
 *		\li '0' if its type is not declared
 *		\li '1' if the type of the declared name is not declared
 *		\li 'ctr', 'io', 'reg' ...
 *
 *	The macro checks that the given name has a declaration whose name
 *	(probably the same as the given name) leads to a declared type.
 */
#define hw_type(...)		_hw_type_2(__VA_ARGS__,)
#define _hw_type_2(t,...)	HW_G2(_hw_type_3,HW_A1(hw_type_##t))(t,__VA_ARGS__)
#define _hw_type_3_(...)	0	/* t is not a declared type */
#define _hw_type_3_ok(...)	_hw_type_4(__VA_ARGS__)
#define _hw_type_4(t,n,...) 	_hw_type_5(hw_##n,)
#define _hw_type_5(...)		_hw_type_6(__VA_ARGS__)
#define _hw_type_6(t,...)	HW_G2(_hw_type_7,HW_A1(hw_type_##t))(t)
#define _hw_type_7_(...)	1	/* n has not a declared type */
#define _hw_type_7_ok(t)	t


/*	Types
 *
 *	Do not use the 1st argument of the expansion. Use the 2nd so that it is
 *	'ok' or void only whether the type is declared or not.
 */
#define hw_type_ctr		, ok, ctr
#define hw_type_aio		, ok, aio
#define hw_type_io		, ok, io
/* #define hw_type_irqe		, ok, irqe */
/* #define hw_type_irqf		, ok, irqf */
#define hw_type_reg		, ok, reg
#define hw_type_regb		, ok, reg
#define hw_type_regbb		, ok, reg
#define hw_type_isr		, ok, isr


/*	The type of the argument or 0.
 */
//#define hw_loosetype(...)	HW_A1(HW_G2(hw_loosetype, HW_A0(__VA_ARGS__)))
#define hw_loosetype(...)	_hw_loosetype_2(__VA_ARGS__,)
#define _hw_loosetype_2(x,...)	HW_A1(hw_loosetype_##x, 0)

#define hw_loosetype_ctr	type, ctr
#define hw_loosetype_aio	type, aio
#define hw_loosetype_io		type, io
/* #define hw_loosetype_irqe	type, irqe */
/* #define hw_loosetype_irqf	type, irqf */
#define hw_loosetype_reg	type, reg
#define hw_loosetype_regb	type, regb
#define hw_loosetype_regbb	type, regbb
#define hw_loosetype_isr	type, isr
#define hw_loosetype_irq_vef	type, irq_vef
