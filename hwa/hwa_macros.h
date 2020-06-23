
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief General purpose macro definitions usable in C or assembler source code.
 */


/**
 * @ingroup dev
 * @brief Element a0 of the list a0,...
 * @hideinitializer
 */
#define HW_A0(...)			_HW_A0_2(__VA_ARGS__,)
#define _HW_A0_2(a0,...)		a0

#define HW_A0_A1(...)			_HW_A0_A1_2(__VA_ARGS__,,)
#define _HW_A0_A1_2(a0,a1,...)		a0,a1

#define HW_T4(...)			_HW_T4(__VA_ARGS__,,,,)
#define _HW_T4(a0,a1,a2,a3,...)		__VA_ARGS__


/**
 * @ingroup dev
 * @brief Element a1 of the list a0,a1,...
 * @hideinitializer
 */
#define HW_A1(...)			_HW_A1_2(__VA_ARGS__,,)
#define _HW_A1_2(a0,a1,...)		a1

#define HW_A2(...)			_HW_A2_2(__VA_ARGS__,,,)
#define _HW_A2_2(a0,a1,a2,...)		a2

#define HW_A3(...)			_HW_A3_2(__VA_ARGS__,,,,)
#define _HW_A3_2(a0,a1,a2,a3,...)	a3

#define HW_A4(...)			HW_A0(HW_T4(__VA_ARGS__))
#define HW_A5(...)			HW_A1(HW_T4(__VA_ARGS__))
#define HW_A6(...)			HW_A2(HW_T4(__VA_ARGS__))
#define HW_A7(...)			HW_A3(HW_T4(__VA_ARGS__))

#define HW_A8(...)			HW_A0(HW_T4(HW_T4(__VA_ARGS__)))
#define HW_A9(...)			HW_A1(HW_T4(HW_T4(__VA_ARGS__)))
#define HW_A10(...)			HW_A2(HW_T4(HW_T4(__VA_ARGS__)))
#define HW_A11(...)			HW_A3(HW_T4(HW_T4(__VA_ARGS__)))


/**
 * @ingroup dev
 * @brief Replace the definition of an object by its name in the beginning of a list.
 *
 *    This is used by functions that accept HWA-built objects as arguments, such
 *    as HW_SWTWIMASTER. The functions get the definition instead of the object
 *    name.
 *
 * @hideinitializer
 */
#define HW_ANAME(x,...)			_HW_B(_HW_ANAME1_,_hw_par x)(x,__VA_ARGS__)
#define _HW_ANAME1_1(...)		HW_E(HW_EM_TBI)
#define _HW_ANAME1_0(x,...)		_HW_B(_HW_ANAME2_,hw_class_##x)(x,__VA_ARGS__)
#define _HW_ANAME2_1(c,o,d,...)		o,__VA_ARGS__
#define _HW_ANAME2_0(...)		__VA_ARGS__


/**
 * @ingroup dev
 * @brief  Put parentheses around arguments of a definition from 3rd position on.
 * @hideinitializer
 */
#define HW_D3(...)			_HW_D3(__VA_ARGS__)
#define _HW_D3(c,o,...)			c,o,(__VA_ARGS__)


/**
 * @ingroup dev
 * @brief  Reduce the definition of the object in first position to one single
 *  element in parentheses: '(c,o,d)'
 * @hideinitializer
 */
#define HW_AD(x,...)			_HW_B(_HW_AD1,_hw_par x)(x,__VA_ARGS__)
#define _HW_AD11(x,...)			(HW_D3(HW_X x)),__VA_ARGS__
#define _HW_AD10(x,...)			_HW_B(_HW_AD2,hw_class_##x)(x,__VA_ARGS__)
#define _HW_AD21(c,o,d,...)		(c,o,d),__VA_ARGS__
#define _HW_AD20(x,...)			(HW_D3(HW_X(x))),__VA_ARGS__


/**
 * @ingroup dev
 * @brief `HW_ADDRESS(object)` returns the address of the @ref using_objects "object".
 * @hideinitializer
 */
#define HW_ADDRESS(...)			HW_F( HW_ADDRESS, __VA_ARGS__ )
#define HW_ADDRESS_E(...)		-1	// Error


/*  Address correction
 *    C and assembly addresses are offset by 0x20 bytes with avr-gcc (or avrlibc?)
 */
#if !defined HW_AC
#  define HW_AC
#endif

#define HW_ADDRESS__m111		, _hw_address_m111
#define _hw_address_m111(n,o,r,c,a,...)	(a HW_AC)

#define HW_ADDRESS__m1			, _hw_address_m1
#define _hw_address_m1(n,o,r,c,a,...)	(a HW_AC)

#define HW_ADDRESS_			, _hw_address_		// By default
#define _hw_address_(o,a,...)		a


/**
 * @ingroup dev
 * @brief `HW_AP(logical_register)` returns the pair address,position of a logical register.
 *
 * This is useful for assembly programming, for example with the SBI / CBI instructions.
 *
 * @hideinitializer
 */
#define HW_AP(...)			HW_F( HW_AP, __VA_ARGS__ )
#define HW_AP_E(...)			0 // An error occured

#define HW_AP__m111				, _hw_ap_m111
#define _hw_ap_m111(n,o,r,c,a,wm,fm,bn,bp,...)	(a HW_AC), bp


/**
 * @ingroup pub
 * @brief `HW_BITS(object)` returns the number of bits of the @ref using_objects "object".
 * @hideinitializer
 *
 * The object may be an I/O definition, a register, a counter...
 *
 * @code
 * #if HW_BITS(counter0) != 16
 * # error You must chose a 16-bit counter
 * #endif
 * @endcode
 */
#define HW_BITS(...)			HW_F( HW_BITS, __VA_ARGS__ )
#define HW_BITS_E(...)			0


/**
 * @ingroup dev
 * @brief Trigger an error at preprocessing stage
 * @hideinitializer
 *
 * Error handling is based on the C99 _Pragma operator. It produces a
 * preprocessing error as soon as the _Pragma(...) sentence is emitted, be it
 * inside or outside of a C function definition, or in an assembler
 * source.
 *
 * The error message 's' must be a single argument, i.e. it must not contain
 * commas.
 *
 * @note _Pragma(...) can not be processed by macros as the sentence is removed
 * from the preprocessor output and replaced by a void token.
 */
/* #define HW_E(s)			_HW_E2(GCC error HW_Q(HWA: s.)) */
#define HW_E(s)				_HW_E2(HWA: s.)
#define _HW_E2(...)			_HW_E3(GCC error #__VA_ARGS__)
#if !defined HW_XE
#  define _HW_E3(s)			_Pragma(#s)
#else
#  define _HW_E3(s)			_xPragma(#s)
#endif

#define HW_EM_C(c)		HW_Q(c) is not a class
#define HW_EM_CM(c,m)		class HW_Q(c) has no method HW_Q(m)
#define HW_EM_F(f)		`f`: unknown function
#define HW_EM_G(x)		garbage starting at HW_Q(x)
#define HW_EM_GA(x)		garbage after HW_Q(x)
#define HW_EM_IA(a)		HW_Q(a): invalid argument
#define HW_EM_IRQ(n)		HW_Q(n) is not an IRQ
#define HW_EM_KX(k,x)		expected HW_Q(k) instead of HW_Q(x)
#define HW_EM_XNIL(x,l)		HW_Q(x) is not in l
#define HW_EM_NKX(n,k,x)	expected HW_Q(k) instead of HW_Q(x) in HW_Q(n)
#define HW_EM_O(x)		HW_Q(x) is not an object
#define HW_EM_OM()		HW_Q(missing object name)
#define HW_EM_ONAP(x)		HW_Q(x) is not a pin name
#define HW_EM_OO(o,x)		HW_Q(o) has no relative named HW_Q(x)
#define HW_EM_S(s)		syntax is s
#define HW_EM_ST(x)		HW_Q(x) is not in (0,1,on,off,yes,no)
#define HW_EM_TL(l)		try one of l

#define HW_E_AVL(a,v,l)		HW_E(HW_Q(a) can be HW_Q(l) but not HW_Q(v))
#define HW_E_AVM(a)		HW_E(missing value for HW_Q(a))
#define HW_E_CM(c,m)		HW_E(class HW_Q(c) has no method HW_Q(m))
#define HW_E_G(x)		HW_E(garbage starting at HW_Q(x))
#define HW_E_IMP(f)		HW_E(HW_Q(f): not implemented for this target)
#define HW_E_IOFN(o,a,v,l)	HW_E(HW_Q(o): HW_Q(a) can be HW_Q(l) but not HW_Q(v))
#define HW_E_IRQ(n)		HW_E(HW_Q(n) is not an IRQ)
#define HW_E_K(k,x)		HW_E(expected HW_Q(k) instead of HW_Q(x))
#define HW_E_KVNIY(k,v)		HW_E(HW_Q(k=v) is not implemented yet)
#define HW_E_KW(w)		HW_E(HW_Q(w) is not an argument name)
#define HW_E_KX(k,x)		HW_E(expected HW_Q(k) instead of HW_Q(x))
#define HW_E_M(m)		HW_E(unknown method HW_Q(m))
#define HW_E_MA(w)		HW_E(missing argument HW_Q(w))
#define HW_E_ML(l)		HW_E(expected one argument in HW_Q(l))
#define HW_E_NIL(v,l)		HW_E(HW_Q(v) is not in l)
#define HW_E_O(x)		HW_E(HW_Q(x) is not an object)
#define HW_E_OAVL(a,v,l)	HW_E(optionnal parameter HW_Q(a) can be HW_Q(l) but not HW_Q(v))
#define HW_E_OCM(o,c,m)		HW_B(_HW_EOCM_,c)(o,c,m)
#define HW_E_OKMV(k,v,l)	HW_E(value of optionnal parameter HW_Q(k) must be HW_Q(l) not HW_Q(v))
#define HW_E_OKVL(k,v,l)	HW_E(value HW_Q(v) for optionnal parameter HW_Q(k) is not in l)
#define HW_E_OM()		HW_E(missing object name)
#define HW_E_OO(o,x)		HW_E(object HW_Q(o) has no relative named HW_Q(x))
#define HW_E_P(x)		HW_E(HW_Q(x) is not a pin)
#define HW_E_ST(x)		HW_E(HW_EM_ST(x))
#define HW_E_T(x)		HW_E(unrecognized token HW_Q(x))
#define HW_E_TBI(...)		HW_E(instruction is not implemented yet)
#define HW_E_TBIKV(k,v)		HW_E(k HW_Q(v) is not implemented yet)
#define HW_E_V()		HW_E(missing value)
#define HW_E_VL(v,l)		HW_E(HW_Q(v) is not HW_Q(l))

#define _HW_EOCM_0(o,c,m)	HW_E(object HW_Q(o) of class HW_Q(c) has no method named HW_Q(m))
#define _HW_EOCM_1(...)


/**
 * @ingroup dev
 * @brief Trigger an error if the first argument is not void.
 * @hideinitializer
 *
 * This is used to ensure that there is no remaining elements in a list at the
 * end of its parsing.
 */
#define HW_EOL(...)			HW_B(_HW_EOL_,__VA_ARGS__)(__VA_ARGS__,)
#define _HW_EOL_0(g,...)		HW_E_G(g)
#define _HW_EOL_1(...)


/**
 * @ingroup dev
 * @brief Find a function f for object o and call it.
 * @hideinitializer
 *
 * Call f_E(e) with an error message if an error occurs. It's up to f_E to
 * produce an error (or not).
 *
 * The method is searched in this order:
 *  1. f_c
 *  2. f_o
 *  3. f
 *
 * The definition of the object is pushed away with the arguments of the method.
 */
#define HW_F(...)			_HW_F(__VA_ARGS__,)
#define _HW_F(f,x,...)			_HW_B(_HW_F_,_hw_par x)(f,x,__VA_ARGS__)
/*
 *  x is not (...)
 */
#define _HW_F_0(f,x,...)		_HW_B(_HW_F_0_,hw_class_##x)(f,x,__VA_ARGS__)
/*
 *  x is a class name
 */
#define _HW_F_0_1(f,x,o,d,...)		_HW_F01(f,x,o,HW_RP d,__VA_ARGS__)
/*
 *  x is not a class name
 */
#define _HW_F_0_0(f,x,...)		_HW_B(_HW_F00_,x)(f,x,__VA_ARGS__)
/*
 *  x is void (error message or void)
 */
#define _HW_F00_1(...)			_HW_F00_2(__VA_ARGS__,,,,)
#define _HW_F00_2(f,z,o,e,...)		_HW_B(_HW_F00_2,o)(f,z,o,e,__VA_ARGS__)
#define _HW_F00_21(f,z,o,e,...)		f##_E(HW_EM_OM())
#define _HW_F00_20(f,z,o,e,...)		f##_E(e)
/*
 *  x is not void
 */
#define _HW_F00_0(f,x,...)		_HW_F00(f, HW_X(x),__VA_ARGS__)
/*
 *  x is (...)
 */
#define _HW_F_1(f,x,...)		_HW_F00(f, HW_X x,__VA_ARGS__)
#define _HW_F00(...)			_HW_F01(__VA_ARGS__)
/*
 *  Got object definition in c,o,...
 */
#define _HW_F01(f,c,o,...)		_HW_B(_HW_F01_,c)(f,c,o)(o,__VA_ARGS__) /* <- push */
#define _HW_F01_1(f,c,o)		f##_E(HW_EM_O(o)) HW_EAT /* <-- Arguments pushed */
/* Class method? */
#define _HW_F01_0(f,c,o)		_HW_F02(f,c,o,f##_##c,)
#define _HW_F02(...)			_HW_F03(__VA_ARGS__)
#define _HW_F03(f,c,o,x,...)		_HW_B(_HW_F03_,x)(f,c,o,x,__VA_ARGS__)
#define _HW_F03_1(f,c,o,z,y,...)	y /* <-- Arguments popped */
/* Object method? */
#define _HW_F03_0(f,c,o,...)		_HW_F04(f,c,o,f##_##o,)
#define _HW_F04(...)			_HW_F05(__VA_ARGS__)
#define _HW_F05(f,c,o,x,...)		_HW_B(_HW_F05_,x)(f,c,o,x,__VA_ARGS__)
#define _HW_F05_1(f,c,o,z,y,...)	y /* <-- Arguments popped */
/* Global method? */
#define _HW_F05_0(f,c,o,...)		_HW_F06(f,c,o,f##_,)
#define _HW_F06(...)			_HW_F07(__VA_ARGS__)
#define _HW_F07(f,c,o,x,...)		_HW_B(_HW_F07_,x)(f,c,o,x,__VA_ARGS__)
#define _HW_F07_1(f,c,o,z,y,...)	y /* <-- Arguments popped */
/* Fake object? */
#define _HW_F07_0(f,c,o,...)		_HW_B(_HW_F08_,_hw_is__fake_##c)(f,c,o)
#define _HW_F08_1(f,c,o)
#define _HW_F08_0(f,c,o)		f##_E(HW_EM(no function f for o)) HW_EAT  /* <-- Arguments pushed */


/**
 * @ingroup dev
 * @brief Glue the first two elements of the list with a '_' between them.
 * @hideinitializer
 */
#define HW_G2(...)			_HW_G2_(__VA_ARGS__,,)
#define _HW_G2_(a,b,...)		a##_##b


/**
 * @ingroup dev
 * @brief Glue the first three elements of the list with a '_' between them.
 * @hideinitializer
 */
#define HW_G3(...)			_HW_G3_(__VA_ARGS__,,,)
#define _HW_G3_(a,b,c,...)		a##_##b##_##c


/**
 * @ingroup pub
 * @brief `HW_IMPLEMENT(object)` defines the functions that implement an object.
 * @hideinitializer
 *
 * External objects usually rely on functions to implement their HWA
 * actions. These functions are declared by `HW_DECLARE()` and implemened by
 * `HW_IMPLEMENT()`.
 *
 * @code
 * #define PCF		HW_PCF8574( interface, twi0, address, 0x27 )
 *
 * HW_IMPLEMENT(PCF);
 * @endcode
 */
#define HW_IMPLEMENT(...)		HW_F(HW_IMPLEMENT,__VA_ARGS__)
#define HW_IMPLEMENT_E(e)		HW_E(e) HW_FOO() /* for semicolon */

/**
 * @ingroup pub
 * @brief `HW_IMPLEMENT_WEAK(object)` defines the functions that implement an object.
 * @hideinitializer
 *
 * Using HW_IMPLEMENT_WEAK() instead of HW_IMPLEMENT() allows multiple definitions of
 * the same functions without errors.
 *
 * @code
 * #define PCF		HW_PCF8574( interface, twi0, address, 0x27 )
 *
 * HW_IMPLEMENT_WEAK(PCF);
 * @endcode
 */
#define HW_IMPLEMENT_WEAK(...)		HW_F(HW_IMPLEMENT_WEAK,__VA_ARGS__)
#define HW_IMPLEMENT_WEAK_E(e)		HW_E(e) HW_FOO() /* for semicolon */


/**
 * @ingroup pub
 * @brief `HW_DECLARE(object)` declares the functions that implement an object.
 * @hideinitializer
 *
 * External objects usually rely on functions to implement their HWA
 * actions. These functions are declared by `HW_DECLARE()` and implemened by
 * `HW_IMPLEMENT()`.
 *
 * @code
 * #define PCF		HW_PCF8574( interface, twi0, address, 0x27 )
 *
 * HW_DECLARE(PCF);
 * @endcode
 */
#define HW_DECLARE(...)			HW_F(HW_DECLARE,__VA_ARGS__)
#define HW_DECLARE_E(e)			HW_E(e) HW_FOO() /* for semicolon */


/**
 * @ingroup dev
 * @brief Eliminates arguments.
 * @hideinitializer
 *
 * Used when a parsing fails and remaining arguments have been pushed.
 */
#define HW_EAT(...)


/**
 * @ingroup dev
 * @brief Expands to 1 if the first two elements of the list are defined equal, 0 otherwise.
 * @hideinitializer
 *
 * For that to work, `HW_IS()` must be used as `HW_IS(x,y)` and there must be a
 * definition of `_hw_is_x_y` that expands as '`, 1`'
 *
 * FIXME: should probably remove this and use branches instead.
 */
#define HW_IS(...)			_HW_IS_2(__VA_ARGS__,,)
#define _HW_IS_2(x,y,...)		HW_A1(_hw_is_##x##_##y,0)


/**
 * @ingroup pub
 * @brief Returns the position of the least significant bit of an object.
 * @hideinitializer
 */
#define HW_POSITION(...)		HW_F( HW_POSITION, __VA_ARGS__ )
#define HW_POSITION_E(...)		0 // An error occured

#define HW_POSITION__m111				, _hw_position_m111
#define _hw_position_m111(n,o,r,c,a,wm,fm,bn,bp,...)	bp


/**
 * @ingroup dev
 * @brief Build a C string from a list of elements
 * @hideinitializer
 */
#define HW_Q(...)			_HW_Q_2(__VA_ARGS__)
#define _HW_Q_2(...)			#__VA_ARGS__


/**
 * @ingroup dev
 * @brief Elements a1,... of the list a0,a1,...
 * @hideinitializer
 */
#define HW_TL(...)			_HW_TL2(__VA_ARGS__,)
#define _HW_TL2(a0,...)			__VA_ARGS__


/**
 * @ingroup dev
 * @brief Expand the argument to a function call
 * @hideinitializer
 *
 * The first argument is ignored, the second is the name of the function, the
 * third is the argument of the function.
 */
#define HW_VF(...)			_HW_VF2(__VA_ARGS__)
#define _HW_VF2(x,f,a)			f(a)


/**
 * @ingroup dev
 * @brief Remove parentheses
 * @hideinitializer
 */
#define HW_RP(...)			__VA_ARGS__


/**
 * @ingroup dev
 * @brief  Branch depending on a void element.
 * @hideinitializer
 *
 *    HW_B(f,c) expands to:
 *	f##1 if c is "",
 *	f##0 if c is not "".
 */
#define HW_B(...)			_HW_B0(__VA_ARGS__,,)
#define _HW_B0(f,x,...)			_HW_B1(f,_hw_par x,0,x)
#define _HW_B1(...)			_HW_B2(__VA_ARGS__)
#define _HW_B2(f,x,y,...)		_HW_B2##y(f,__VA_ARGS__,)
#define _HW_B21(f,...)			f##0
#define _HW_B20(f,x,...)		_HW_B3(f,_hw_is__##x,0,)
#define _HW_B3(...)			_HW_B4(__VA_ARGS__)
#define _HW_B4(f,x,y,...)		f##y


/**
 * @ingroup dev
 * @brief  Branch depending on a void element.
 * @hideinitializer
 *
 *    _HW_B(f,x,...) expands to:
 *	f1 if x is void
 *	f0 otherwise
 *    Unlike HW_B, this version does not handle parentheses.
 */
#define _HW_B(...)			_HW_B_1(__VA_ARGS__,,)
#define _HW_B_1(f,x,...)		_HW_B_2(f,_hw_is__##x,0,)
#define _HW_B_2(...)			_HW_B_3(__VA_ARGS__)
#define _HW_B_3(f,x,r,...)		f##r


/**
 * @ingroup dev
 * @brief  Branch depending on the value of a symbol.
 * @hideinitializer
 *
 *  HW_BV(f,p,s) expands as:
 *   * f##b    if s is '(...)'
 *   * f##0(s) if p##s is not defined, i.e. its expansion does not start with a void
 *   * f##1(r) where r is the 2nd element of expansion of p##x, i.e. the defined value
 */
#define HW_BV(f,p,s)			_HW_B(_HW_BV1,_hw_par s)(f,p,s)
#define _HW_BV11(f,p,s)			f##b
#define _HW_BV10(f,p,s)			_HW_BV12(f,p,s,p##s,)
#define _HW_BV12(...)			_HW_BV13(__VA_ARGS__)
#define _HW_BV13(f,p,s,...)		_HW_B(_HW_BV2,__VA_ARGS__)(f,p,s,__VA_ARGS__)
#define _HW_BV20(f,p,s,...)		f##0(s)
#define _HW_BV21(f,p,s,z,r,...)		f##1(r)

  
/**
 * @ingroup dev
 * @brief  Branch depending on a word
 * @hideinitializer
 *
 *    HW_BW(f,k,w) expands to:
 *	f0 if k is not w
 *	f1 if k is w	(there must a: #define _hw_is_k_k , 1)
 */
#define HW_BW(...)			_HW_BW01(__VA_ARGS__,,,)
#define _HW_BW01(f,k,w,...)		_HW_BW02(f,k,w,_hw_par w, 0,)
#define _HW_BW02(...)			_HW_BW03(__VA_ARGS__)
#define _HW_BW03(f,k,w,z,x,...)		_HW_BW03##x(f,k,w)
#define _HW_BW031(f,k,w)		f##0
#define _HW_BW030(f,k,w)		_HW_BW04(f,k,w,_hw_is__##w, 0,)
#define _HW_BW04(...)			_HW_BW05(__VA_ARGS__)
#define _HW_BW05(f,k,w,z,x,...)		_HW_BW05##x(f,k,w)
#define _HW_BW051(f,k,w)		f##0
#define _HW_BW050(f,k,w)		_HW_BW06(f,k,w,_hw_is_##k##_##w, 0,)
#define _HW_BW06(...)			_HW_BW07(__VA_ARGS__)
#define _HW_BW07(f,k,w,z,x,...)		f##x


/**
 * @ingroup dev
 * @brief  Branch depending on a void result after appending p and x:
 * @hideinitializer
 *
 *    HW_BX(f,p,x,...) expands to:
 *	f1 if p##x is void
 *	f0 otherwise
 */
#define HW_BX(...)			_HW_BX01(__VA_ARGS__,,,)
#define _HW_BX01(f,p,x,...)		_HW_BX02(f,p,x,_hw_par x, 0,)
#define _HW_BX02(...)			_HW_BX03(__VA_ARGS__)
#define _HW_BX03(f,p,x,z,r,...)		_HW_BX03##r(f,p,x)
#define _HW_BX031(f,p,x)		f##0
#define _HW_BX030(f,p,x)		_HW_BX04(f,p,x,p##x, 0,)
#define _HW_BX04(...)			_HW_BX05(__VA_ARGS__)
#define _HW_BX05(f,p,x,z,r,...)		f##r


/**
 * @ingroup pub
 * @brief `hw( action, object [,...] )` executes an @ref using_actions "action" immediately on an @ref using_objects "object".
 * @hideinitializer
 *
 * * An explicit error message is produced if the object does not exist or if it
 *   does not support the action.
 * * Additional arguments may follow the name of the object.
 *
 * @code
 * hw( configure, (porta,0), direction, output );
 * hw( write, counter0, 0 );
 * @endcode
 */
#define hw(...)				hwx(hw_,__VA_ARGS__,,)


/**
 * @ingroup pub
 * @brief `hwa( action, object [,...] )` stores an @ref using_actions "action" for the @ref using_objects "object" into a *HWA context*.
 * @hideinitializer
 *
 * * An explicit error message is produced if the object does not exist or if it
 *   does not support the action.
 * * Additional arguments may follow the name of the object.
 * * The context must have been created, only once in the same translation unit,
 *   with `hwa(begin)` or `hwa(begin, reset)`.
 * * `hwa(commit)` triggers the production of the machine code.
 * * `hwa(nocommit)` does not produce code but is useful to put the context in a
 *   known state.
 *
 * @code
 * //  Configure PA0, PA2, PA4, PA5, PA6, PA7 as outputs
 * //  accessing the DDRA register only once.
 * //
 * hwa( begin, reset );
 * hwa( configure, (porta,0), direction, output );
 * hwa( configure, ((porta,2)), direction, output );	// Dual parentheses is OK
 * hwa( configure, (port0,4,4), direction, output );
 * hwa( commit );
 * @endcode
 */
#define hwa(...)			hwx(hwa_,__VA_ARGS__,,)


/**
 * @ingroup dev
 * @brief Find a method for an object and call it
 * @hideinitializer
 *
 * The method is searched in this order:
 *  1. A class method, h_f_c
 *  2. A global method, h_f
 *  3. A class method h_f_ if 'o' is void (begin,commit...)
 *
 * FIXME: using the object name to distinguish a no-object call and an
 * error-object call. A class _err would be faster?
 */
#define hwx(h,f,x,...)			_HW_B(_hwx0_,_hw_par x)(h,f,x,__VA_ARGS__)
/*
 *  x is ()
 */
#define _hwx0_1(h,f,x,...)		_hwx_0(h,f,HW_X x,__VA_ARGS__)
/*
 *  x is not ()
 */
#define _hwx0_0(h,f,x,...)		_HW_B(_hwx1_,hw_class_##x)(h,f,x,__VA_ARGS__)
/*
 *  x is a class name, expand the definition.
 */
#define _hwx1_1(h,f,x,o,d,...)		_hwx_10(h,f,x,o,HW_RP d,__VA_ARGS__)
/*
 *  x is not a class name
 */
#define _hwx1_0(h,f,x,...)		_HW_B(_hwx10_,x)(h,f,x,__VA_ARGS__)
/*
 *  x is void
 */
#define _hwx10_1(h,f,z,...)		_HW_B(_hwx101_,__VA_ARGS__)(h,f,z,__VA_ARGS__)
#define _hwx101_0(h,f,z,o,e,...)	HW_E(e)
#define _hwx101_1(h,f,x,...)		_hwx_0(h,f,HW_X(x),__VA_ARGS__)
/*
 *  x is not void
 */
#define _hwx10_0(h,f,x,...)		_hwx_0(h,f,HW_X(x),__VA_ARGS__)
#define _hwx_0(...)			_hwx_1(__VA_ARGS__)
#define _hwx_1(h,f,c,...)		_HW_B(_hwx_1,c)(h,f,c,__VA_ARGS__)
/*
 *  o is not an object. Look for h_##f##_##o
 */
#define _hwx_11(h,f,c,o,e,...)		_hwx_12(h,e,f,h##f##_##o,o,__VA_ARGS__)
#define _hwx_12(...)			_hwx_13(__VA_ARGS__)
#define _hwx_13(h,e,f,x,...)		_HW_B(_hwx_13,x)(h,e,f,x,__VA_ARGS__)
#define _hwx_131(h,e,f,z,y,...)		y(__VA_ARGS__)
/*
 *			      Look for h_##f##_
 */
#define _hwx_130(h,e,f,m,...)		_hwx_14(h,e,f,h##f##_,__VA_ARGS__)
#define _hwx_14(...)			_hwx_15(__VA_ARGS__)
#define _hwx_15(h,e,f,x,...)		_HW_B(_hwx_15,x)(h,e,f,x,__VA_ARGS__)
#define _hwx_151(h,f,z,y,...)		y(__VA_ARGS__)
//#define _hwx_150(...)			HW_E(internal error [_hwx_150(__VA_ARGS__)] )
#define _hwx_150(h,e,...)		HW_E(e) hw_foo()
/*
 *  2nd arg is an object of class c
 */
/* Class method? */
#define _hwx_10(h,f,c,o,...)		_hwx_2(h,f,c,o,h##f##_##c,__VA_ARGS__)
#define _hwx_2(...)			_hwx_3(__VA_ARGS__)
#define _hwx_3(h,f,c,o,x,...)		_HW_B(_hwx_3,x)(h,f,c,o,x,__VA_ARGS__)
#define _hwx_31(h,f,c,o,z,y,...)	y(o,__VA_ARGS__)
/* Global method? */
#define _hwx_30(h,f,c,o,x,...)		_hwx_6(h,f,c,o,h##f,__VA_ARGS__)
#define _hwx_6(...)			_hwx_7(__VA_ARGS__)
#define _hwx_7(h,f,c,o,x,...)		_HW_B(_hwx_7,x)(h,f,c,o,x,__VA_ARGS__)
#define _hwx_71(h,f,c,o,z,y,...)	y(c,o,__VA_ARGS__)
/* Fake object? */
#define _hwx_70(h,f,c,o,x,...)		_HW_B(_hwx_8,_hw_is__fake_##c)(h,f,c,o)
#define _hwx_81(...)			// Nothing to do, fake is always OK.
#define _hwx_80(h,f,c,o)		/* h##f##_ */ HW_E_OCM(o,c,f)


/**
 * @ingroup priv
 * @brief Private version of hw().
 * @hideinitializer
 */
#define _hw(...)			_hw_1(__VA_ARGS__,,)
#define _hw_1(f,o,...)			_hw_2(f,HW_X(o),__VA_ARGS__)
#define _hw_2(...)			_hw_3(__VA_ARGS__)
#define _hw_3(f,c,...)			HW_B(_hw_4,c)(f,c,__VA_ARGS__)
#define _hw_41(c,o,e,...)		HW_E(e)	// Error, stop here.
#define _hw_40(f,c,...)			HW_B(_hw_5,hw_##f##_##c)(f,c,__VA_ARGS__)
#define _hw_51(f,c,...)			HW_A1(hw_##f##_##c)(__VA_ARGS__)
#define _hw_50(f,c,o,...)		HW_E_OCM(o,c,hw_##f)


/**
 * @ingroup priv
 * @brief Private version of hwa().
 * @hideinitializer
 */
#define _hwa(...)			_hwa_1(__VA_ARGS__,)
#define _hwa_1(f,o,...)			_hwa_2(f,HW_X(o),__VA_ARGS__)
#define _hwa_2(...)			_hwa_3(__VA_ARGS__)
#define _hwa_3(f,c,...)			HW_B(_hwa_4,c)(f,c,__VA_ARGS__)
#define _hwa_41(c,o,e,...)		HW_E(e)	// Error, stop here.
#define _hwa_40(f,c,...)		HW_B(_hwa_5,hwa_##f##_##c)(f,c,__VA_ARGS__)
#define _hwa_51(f,c,...)		HW_A1(hwa_##f##_##c)(__VA_ARGS__)
#define _hwa_50(f,c,o,...)		HW_E_OCM(o,c,hwa_##f)


/**
 * @ingroup pub
 * @brief Returns the structure of the status of the @ref using_objects "object".
 * @hideinitializer
 *
 * @code
 * hw_stat_t(spi0) st = hw(stat,spi0);
 * if ( st.collision )
 *   ++n_collisions;
 * @endcode
 */
#define hw_stat_t(object)		hw(stat_t,object)


/**
 * @ingroup pub
 * @brief Returns an unsigned integer type of `n` bits.
 * @hideinitializer
 *
 * * `hw_uint_t(8)` expands to `uint8_t`;
 * * `hw_uint_t(16)` expands to `uint16_t`.
 *
 * This is useful, for example,when you need to store a value whose size depends
 * on an object:
 *
 * @code
 * hw_uint_t(HW_BITS(counter0)) count = hw( read, counter0 );
 * @endcode
 */
#define hw_uint_t(n)			_hw_uintt0(n)
#define _hw_uintt0(n)			HW_BW(_hw_uintt0,8,n)(n)
#define _hw_uintt01(n)			uint8_t
#define _hw_uintt00(n)			HW_BW(_hw_uintt1,16,n)(n)
#define _hw_uintt11(n)			uint16_t
#define _hw_uintt10(n)			HW_E_VL(n,8|16) uint8_t


#if defined DOXYGEN
/**
 * @brief Remove Doxygen warnings "explicit link request to 'k' could not be resolved".
 * @hideinitializer
 */
#define k

/**
 * @brief Remove Doxygen warnings "explicit link request to 'v' could not be resolved".
 * @hideinitializer
 */
#define v

#endif
