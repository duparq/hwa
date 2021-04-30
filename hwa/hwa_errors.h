
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Error management: macros and messages (in English)
 */

/**
 * @ingroup hwa_dev
 * @brief Trigger an error at preprocessing stage
 * @hideinitializer
 *
 * Error handling is based on the C99 _Pragma operator. It produces a
 * preprocessing error as soon as the _Pragma(...) sentence is emitted, be it
 * inside or outside of a C function definition, or in an assembler
 * source.
 *
 * @note The preprocessor expands _Pragma(...) as a void token.
 *
 * Error messages are produced by HW_EM() macros so that they can be localized
 * easily.
 */
#define HW_E(...)		_HW_E2(HWA: __VA_ARGS__.)
#define _HW_E2(...)		_HW_E3(GCC error #__VA_ARGS__)
#define _HW_E3(s)		_Pragma(#s)

#define HW_E_OCM(o,c,m)		HW_B(HW_E_OCM_,c)(o,c,m)
#define HW_E_OCM_0(o,c,m)	HW_E(HW_EM_OCM(o,c,m))
#define HW_E_OCM_1(...)

/*  Error messages
 */
#define HW_EM_AI(a)		invalid argument HW_Q(a)
#define HW_EM_AL(a,l)		argument HW_Q(a) is not in l
#define HW_EM_ACCESS		invalid access
#define HW_EM_ADOO(a,o1,o2)	value of parameter `a` mismatch beween `o1` and `o2`
#define HW_EM_AOCL(a,o,c,l)	action HW_Q(a) for object HW_Q(o) of class HW_Q(c) is not in l
#define HW_EM_AVL(a,l)		value of parameter `a` is not in l
#define HW_EM_AVOL(a,o,l)	value of parameter `a` for `o` is not in l
#define HW_EM_AVM(a,v)		value of parameter `a` must be `v`
#define HW_EM_AOVM(a,o,v)	value of parameter `a` for `o` must be `v`
#define HW_EM_AM(a)		missing argument HW_Q(a)
#define HW_EM_AML(l)		expected at least one argument of l
#define HW_EM_AN(a,n)		expected argument HW_Q(n) instead of HW_Q(a)
#define HW_EM_CAN(c,a,n)	constructor c expects an argument HW_Q(n) instead of HW_Q(a)
#define HW_EM_CANTREMAP		remapping is impossible
#define HW_EM_COR(o)		configuration of `o` is required
#define HW_EM_COMMITRQ		committing is required before setting a new value
#define HW_EM_CMOO(o1,o2)	configuration mismatch beween `o1` and `o2`
#define HW_EM_FO(f,o)		no function `f` for `o`
#define HW_EM_G(x)		garbage starting at HW_Q(x)
#define HW_EM_KX(k,x)		expected HW_Q(k) instead of HW_Q(x)
#define HW_EM_NKX(n,k,x)	expected HW_Q(k) instead of HW_Q(x) in HW_Q(n)
#define HW_EM_NOP		no operation
#define HW_EM_O(x)		HW_Q(x) is not an object
#define HW_EM_OAVI(o,a,v)	`o` does not support value `v` for `a`
#define HW_EM_OCM(o,c,m)	object HW_Q(o) of class HW_Q(c) has no method HW_Q(m)
#define HW_EM_OM()		missing object name
#define HW_EM_OMAP(o)		remapping error for `o`
#define HW_EM_MAP		signal is already mapped to another pin
#define HW_EM_IONC		IO contains disconnected pins
#define HW_EM_ISR(o)		no ISR known for `o`
#define HW_EM_ONC(o)		HW_Q(o) is not connected
#define HW_EM_OO(o,x)		HW_Q(o) has no relative HW_Q(x)
#define HW_EM_OPTIM		you may have forgotten to turn optimizations on
#define HW_EM_OT(o,t)		HW_Q(o) is not a t
#define HW_EM_OVL(v,l)		optionnal value HW_Q(v) is not in l
#define HW_EM_SD(s)		symbol #s not defined
#define HW_EM_SL(l)		suggest you try one of l
#define HW_EM_ST(x)		HW_Q(x) is not in (0,1,on,off,yes,no)
#define HW_EM_SY(s)		syntax is s
#define HW_EM_TBD(...)		to be done (this feature is not implemented yet) [__VA_ARGS__]
#define HW_EM_V			missing value
#define HW_EM_VAL(v,a,l)	value HW_Q(v) for argument HW_Q(a) is not in l
#define HW_EM_VAM(a)		missing value for argument HW_Q(a)
#define HW_EM_VL(v,l)		value HW_Q(v) is not in l
#define HW_EM_VOAL(v,a,l)	value HW_Q(v) for optionnal argument HW_Q(a) is not in l
#define HW_EM_VOAST(v,a)	value HW_Q(v) for optionnal argument HW_Q(a) is not in (0,1,on,off,yes,no)
#define HW_EM_VSL(s,l)		value `s` of symbol #s is not in l
#define HW_EM_XWW(x,w1,w2)	expected HW_Q(w2) instead of HW_Q(x) after HW_Q(w1)

#define HW_EM_XNIL(x,l)		HW_Q(x) is not in l
#define HW_EM_XSO(x,o)		can not solve value of `x` for `o`

#define HW_EM_X(x)		internal error x
