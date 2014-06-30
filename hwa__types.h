
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/** \brief	1 if the object has a known type, 0 otherwise
 */
//#define HW_CT(...)		HW_IS(ok, HW_A1(hw_type_ ## __VA_ARGS__))


/** \brief	Type of the first argument. That is:
 *		\li '0' if error
 *		\li 'ctr', 'io', 'reg' ...
 *
 *	The macro checks that the given name has a declaration whose name
 *	(probably the same as the given name) leads to a declared type.
 */
#define hw_type(...)		_hw_type_2(__VA_ARGS__,)
#define _hw_type_2(t,...)	HW_G2(_hw_type_3,HW_A1(hw_type_##t))(t,__VA_ARGS__)
#define _hw_type_3_(...)	0	/* t is not a declared type */
#define _hw_type_3_ok(t,...)	t


/*	Types
 *
 *	Do not use the 1st argument of the expansion. Use the 2nd so that it is
 *	'ok' or void only whether the type is declared or not.
 */
#define hw_type_ctr		, ok, ctr
#define hw_type_mem		, ok, mem
#define hw_type_irq		, ok, irq
