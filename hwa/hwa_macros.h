
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief General purpose macro definitions usable in C or assembler source code.
 */

/**
 * @ingroup hwa_dev
 * @brief Element a0 of the list a0,...
 * @hideinitializer
 *
 * -
 */
#define HW_A0(...)			_HW_A0_2(__VA_ARGS__,)
#define _HW_A0_2(a0,...)		a0

#define HW_A0_A1(...)			_HW_A0_A1_2(__VA_ARGS__,,)
#define _HW_A0_A1_2(a0,a1,...)		a0,a1

#define HW_T4(...)			_HW_T4(__VA_ARGS__,,,,)
#define _HW_T4(a0,a1,a2,a3,...)		__VA_ARGS__


/**
 * @ingroup hwa_dev
 * @brief Element a1 of the list a0,a1,...
 * @hideinitializer
 *
 * -
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
 * @ingroup hwa_dev
 * @brief  Reduce the definition of the object in first position to one single
 *  element in parentheses: '(c,o,d)'
 * @hideinitializer
 *
 * -
 */
#define HW_AD(x,...)			_HW_B(_HW_AD1,_hw_par x)(x,__VA_ARGS__)
#define _HW_AD11(x,...)			(HW_D3(HW_X x)),__VA_ARGS__
#define _HW_AD10(x,...)			_HW_B(_HW_AD2,hw_class_##x)(x,__VA_ARGS__)
#define _HW_AD21(c,o,d,...)		(c,o,d),__VA_ARGS__
#define _HW_AD20(x,...)			(HW_D3(HW_X(x))),__VA_ARGS__


/**
 * @ingroup hwa_dev
 * @brief Replace the definition of an object by its name in the beginning of a list.
 * @hideinitializer
 *
 *    This is used by functions that accept HWA-built objects as arguments, such
 *    as HW_SWTWIMASTER. The functions get the definition instead of the object
 *    name.
 */
#define HW_ANAME(x,...)			_HW_B(_HW_ANAME1_,_hw_par x)(x,__VA_ARGS__)
#define _HW_ANAME1_1(...)		HW_E(HW_EM_TBI)
#define _HW_ANAME1_0(x,...)		_HW_B(_HW_ANAME2_,hw_class_##x)(x,__VA_ARGS__)
#define _HW_ANAME2_1(c,o,d,...)		o,__VA_ARGS__
#define _HW_ANAME2_0(...)		__VA_ARGS__


/**
 * @ingroup hwa_dev
 * @brief  Branch depending on a void element.
 * @hideinitializer
 *
 * HW_B(f,c) expands to:
 *  * f##1 if c is void
 *  * f##0 otherwise
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
 * @ingroup hwa_dev
 * @brief  Branch depending on a void element.
 * @hideinitializer
 *
 * _HW_B(f,x,...) expands to:
 *  * f1 if x is void
 *  * f0 otherwise
 * Unlike HW_B, this version does not handle parentheses.
 */
#define _HW_B(...)			_HW_B20(__VA_ARGS__,,)


/**
 * @ingroup hwa_dev
 * @brief  Branch depending on the expansion of a definition.
 * @hideinitializer
 *
 * HW_BED(f,x,...) expands to:
 *  * f1(...,{definition of x}) if x expands to the definition of an object
 *  * f0(...,x) otherwise
 */
#define HW_BED(f,x,...)		_HW_BED1((f,__VA_ARGS__),x,) ,x)//PUSH
#define _HW_BED1(a,x,...)	_HW_BED2(a,hw_class_##x)
#define _HW_BED2(...)		_HW_BED3(__VA_ARGS__,)
#define _HW_BED3(a,x,...)	_HW_BED4(a,_hw_is__##x,0,)
#define _HW_BED4(...)		_HW_BED5(__VA_ARGS__)
#define _HW_BED5(a,x,r,...)	_HW_BED6(r, HW_RP a)
#define _HW_BED6(...)		_HW_BED7(__VA_ARGS__)
#define _HW_BED7(x,f,...)	f##x(__VA_ARGS__ //POP


/**
 * @ingroup hwa_dev
 * @brief  Branch depending on an expansion starting with void
 * @hideinitializer
 *
 * HW_BEZ(f,x,...) expands to:
 *  * f1(...,{expansion of x}) if x expands to ' , ...'
 *  * f0(...,x) otherwise
 */
#define HW_BEZ(f,x,...)		_HW_BEZ1((f,__VA_ARGS__),x,)	,x)//PUSH
#define _HW_BEZ1(a,x,...)	_HW_BEZ4(a,_hw_is__##x,0,)
#define _HW_BEZ4(...)		_HW_BEZ5(__VA_ARGS__)
#define _HW_BEZ5(a,x,r,...)	_HW_BEZ6(r, HW_RP a)
#define _HW_BEZ6(...)		_HW_BEZ7(__VA_ARGS__)
#define _HW_BEZ7(x,f,...)	f##x(__VA_ARGS__ //POP


/**
 * @ingroup hwa_dev
 * @brief  Branch depending on a parenthesis element.
 * @hideinitializer
 *
 * HW_BP(f,x) expands to:
 *  * f1 if x is '(...)'
 *  * f0 otherwise
 */
#define HW_BP(f,x)			_HW_BP0(f,_hw_par x,0)
#define _HW_BP0(...)			_HW_BP1(__VA_ARGS__)
#define _HW_BP1(f,x,r,...)		f##r


/**
 * @ingroup hwa_dev
 * @brief  Branch depending on a value.
 * @hideinitializer
 *
 * HW_BV(f,p,s,...) expands to:
 *  * `f_(s,...)` if `s` is '(...)'.
 *  * `f0(s,...)` if the expansion of `_hw_<p><s>` does not start with a void.
 *  * `f1(r,...)` where `r` is the 2nd and following elements of the expansion of `_hw_<p><s>`.
 *
 * Example:
 * @code
 * //  The following code provides the following expansions:
 * //
 * //      fun((foo),bar) -> fun_((foo),x) (bar)
 * //      fun(foo,bar) -> fun0(foo,x) (bar)
 * //      fun(yes,bar) -> fun1(yesval,x) (bar)
 * //
 * #define fun(v,...)			HW_BV(fun,funval_,v,x)(__VA_ARGS__)
 *
 * #define _hw_funval_yes		, yesval
 * @endcode
 */
#define HW_BV(f,p,s,...)		_HW_B(_HW_BV1,_hw_par s)(f,p,s,__VA_ARGS__)
#define _HW_BV11(f,p,s,...)		f##_
#define _HW_BV10(f,p,s,...)		_HW_BV12(f,p,s,_hw_##p##s,__VA_ARGS__)
#define _HW_BV12(...)			_HW_BV13(__VA_ARGS__)
#define _HW_BV13(f,p,s,...)		_HW_B(_HW_BV2,__VA_ARGS__)(f,s,__VA_ARGS__)
#define _HW_BV20(f,s,r,...)		f##0(s,__VA_ARGS__)
#define _HW_BV21(f,s,z,...)		f##1(__VA_ARGS__)

  
/**
 * @ingroup hwa_dev
 * @brief  Branch depending on a word
 * @hideinitializer
 *
 * HW_BW(f,k,w) expands to:
 *  * f0 if k is not w
 *  * f1 if k is w	(there must a: `#define` _hw_is_k_k , 1)
 *
 * @code
 * #define _hw_is_key_key	, 1
 *
 * HW_BW(func,key,word)  ->  func0
 * HW_BW(func,key,key)   ->  func1
 * @endcode
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
/*
 *  Avoid concatenation in case of math expression, e.g.:
 *    HW_BW(func,key,key/x) -> func1/x
 */
//#define _HW_BW07(f,k,w,z,x,...)		f##x
#define _HW_BW07(f,k,w,z,x,...)		_HW_BW08(f,_HW_BW_##x,)
#define _HW_BW08(...)			_HW_BW09(__VA_ARGS__)
#define _HW_BW09(f,v,...)		f##v

#define _HW_BW_0			0,
#define _HW_BW_1			1,


/**
 * @ingroup hwa_dev
 * @brief  Branch depending on a void result after appending p and x:
 * @hideinitializer
 *
 * HW_BX(f,p,x,...) expands to:
 *  * f1 if px is void
 *  * f0 otherwise
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
 * @ingroup hwa_dev
 * @brief  Branch depending on a void element. Does not handle parentheses.
 * @hideinitializer
 *
 * _HW_BZ(f,x,...) expands to:
 *  * f1 if x is void
 *  * f0 otherwise
 */
#define _HW_BZ(...)			_HW_BZ1(__VA_ARGS__,,)
#define _HW_BZ1(f,x,...)		_HW_BZ2(f,x,0,)
#define _HW_BZ2(f,x,r,...)		f##r


/**
 * @ingroup hwa_dev
 * @brief Get the definition of object `o` as c,o,(d). No error checking.
 * @hideinitializer
 *
 * See HW_XO() for error checking.
 */
#define _HW_COD(o)			_HW_COD0(o)
#define _HW_COD0(o)			_HW_COD1(o,hw_##o)
#define _HW_COD1(...)			_HW_COD2(__VA_ARGS__)
#define _HW_COD2(o,c,...)		c,o,(__VA_ARGS__)


/**
 * @ingroup hwa_dev
 * @brief Get the memory definition of register `r` of object `o`.
 * @hideinitializer
 *
 * FIXME: to be continued.
 *
 */
#define HW_CODG(...)			_HW_CODG(__VA_ARGS__)
#define _HW_CODG(c,o,d,r)		HW_BED(_HW_CODG,hw_##o##_##r,) (c,o,d,r)//PUSH
#define _HW_CODG0(...)			_HW_CODG01 //POP
#define _HW_CODG01(c,o,d,r)		HW_BED(_HW_CODG1,hw_##c##_##r,) c,o,d,r)//PUSH
#define _HW_CODG11(z,...)		_HW_CODG2(__VA_ARGS__, //POP
#define _HW_CODG2(c,...)		_HW_CODG##c(__VA_ARGS__)
#define _HW_CODG_cb1(r,bn,bp,c,o,d,r0)	_HW_OXR_ob1_01(o,HW_RP d,r,hw_##c##_##r,bn,bp)


/**
 * @ingroup hwa_dev
 * @brief  Put parentheses around arguments of a definition from 3rd position on.
 * @hideinitializer
 *
 * -
 */
#define HW_D3(...)			_HW_D3(__VA_ARGS__)
#define _HW_D3(c,o,...)			c,o,(__VA_ARGS__)


/**
 * @ingroup hwa_dev
 * @brief Eliminates arguments.
 * @hideinitializer
 *
 * Used when a parsing fails and remaining arguments have been pushed.
 */
#define HW_EAT(...)


/**
 * @ingroup hwa_dev
 * @brief Trigger an error if the first argument is not void.
 * @hideinitializer
 *
 * This is used to ensure that there is no remaining elements in a list at the
 * end of its parsing.
 */
#define HW_EOL(...)			HW_B(_HW_EOL_,__VA_ARGS__)(__VA_ARGS__,)
#define _HW_EOL_0(g,...)		HW_E(HW_EM_G(g))
#define _HW_EOL_1(...)


/**
 * @ingroup hwa_dev
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
#define _HW_F(f,x,...)			_HW_B(_HW_F,_hw_par x)(f,x,__VA_ARGS__)
/*
 *  x is not (...)
 */
#define _HW_F0(f,x,...)			_HW_B(_HW_F0,hw_class_##x)(f,x,__VA_ARGS__)
/*
 *  x is a class name
 */
#define _HW_F01(f,x,o,d,...)		_HW_F3(f,x,o,HW_RP d,__VA_ARGS__)
/*
 *  x is not a class name
 */
#define _HW_F00(f,x,...)		_HW_B(_HW_F00,x)(f,x,__VA_ARGS__)
/*
 *  x is void (error message or void)
 */
#define _HW_F001(...)			_HW_F02(__VA_ARGS__,,,,)
#define _HW_F02(f,z,o,e,...)		_HW_B(_HW_F02,o)(f,z,o,e,__VA_ARGS__)
#define _HW_F021(f,z,o,e,...)		f##_E(HW_EM_OM())
#define _HW_F020(f,z,o,e,...)		f##_E(e)
/*
 *  x is not void
 */
#define _HW_F000(f,x,...)		_HW_F2(f, HW_X(x),__VA_ARGS__)
/*
 *  x is (...)
 */
#define _HW_F1(f,x,...)			_HW_F2(f, HW_X x,__VA_ARGS__)
#define _HW_F2(...)			_HW_F3(__VA_ARGS__)
/*
 *  Got object definition in c,o,...
 */
#define _HW_F3(f,c,o,...)		_HW_B(_HW_F3,c)(f,c,o)(o,__VA_ARGS__) // PUSH
#define _HW_F31(f,c,o)			f##_E(HW_EM_O(o)) HW_EAT // POP
/* Class method? */
#define _HW_F30(f,c,o)			_HW_F32(f,c,o,f##_##c,)
#define _HW_F32(...)			_HW_F33(__VA_ARGS__)
#define _HW_F33(f,c,o,x,...)		_HW_B(_HW_F4,x)(f,c,o,x,__VA_ARGS__)
#define _HW_F41(f,c,o,z,y,...)		y // POP
/* Object method? */
#define _HW_F40(f,c,o,...)		_HW_F42(f,c,o,f##_##o,)
#define _HW_F42(...)			_HW_F43(__VA_ARGS__)
#define _HW_F43(f,c,o,x,...)		_HW_B(_HW_F5,x)(f,c,o,x,__VA_ARGS__)
#define _HW_F51(f,c,o,z,y,...)		y // POP
/* Global method? */
#define _HW_F50(f,c,o,...)		_HW_F52(f,c,o,f##_,)
#define _HW_F52(...)			_HW_F53(__VA_ARGS__)
#define _HW_F53(f,c,o,x,...)		_HW_B(_HW_F6,x)(f,c,o,x,__VA_ARGS__)
#define _HW_F61(f,c,o,z,y,...)		y // POP
/* Fake object? */
#define _HW_F60(f,c,o,...)		_HW_B(_HW_F7,_hw_is__fake_##c)(f,c,o)
#define _HW_F71(f,c,o)
#define _HW_F70(f,c,o)			f##_E(HW_EM_FO(f,o)) HW_EAT // POP


/**
 * @ingroup hwa_dev
 * @brief Glue the first two elements of the list with a '_' between them.
 * @hideinitializer
 */
#define HW_G2(...)			_HW_G2_(__VA_ARGS__,,)
#define _HW_G2_(a,b,...)		a##_##b


/**
 * @ingroup hwa_dev
 * @brief Glue the first three elements of the list with a '_' between them.
 * @hideinitializer
 */
#define HW_G3(...)			_HW_G3_(__VA_ARGS__,,,)
#define _HW_G3_(a,b,c,...)		a##_##b##_##c


/**
 * @ingroup hwa_dev
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
 * @ingroup hwa_dev
 * @brief Build a C string from a list of elements
 * @hideinitializer
 *
 * -
 */
#define HW_Q(...)			_HW_Q_2(__VA_ARGS__)
#define _HW_Q_2(...)			#__VA_ARGS__


/**
 * @ingroup hwa_dev
 * @brief Show how x expands
 * @hideinitializer
 */
#define HW_SHOW(x)			#x: x


#if 0	// HW_BD may be used instead
/**
 *  Test a definition:
 *    HW_TD(x)	expands to:
 *      1,<definition of x> if x is the definition of an object (has a class)
 *      0,x otherwise.
 */
#define HW_TD(...)		_HW_TD1(__VA_ARGS__,), __VA_ARGS__)
#define _HW_TD1(x,...)		_HW_TD2(hw_class_##x)
#define _HW_TD2(...)		_HW_TD3(__VA_ARGS__,)
#define _HW_TD3(x,...)		_HW_TD4(_hw_is__##x,0,)
#define _HW_TD4(...)		_HW_TD5(__VA_ARGS__)
#define _HW_TD5(x,r,...)	r
#endif


/**
 * @ingroup hwa_dev
 * @brief Elements a1,... of the list a0,a1,...
 * @hideinitializer
 *
 * -
 */
#define HW_TL(...)			_HW_TL2(__VA_ARGS__,)
#define _HW_TL2(a0,...)			__VA_ARGS__


/**
 * @ingroup hwa_dev
 * @brief Expand the argument to a function call
 * @hideinitializer
 *
 * The first argument is ignored, the second is the name of the function, the
 * third is the argument of the function.
 */
#define HW_VF(...)			_HW_VF2(__VA_ARGS__)
#define _HW_VF2(x,f,a)			f(a)


/**
 * @ingroup hwa_dev
 * @brief Remove parentheses
 * @hideinitializer
 *
 * -
 */
#define HW_RP(...)			__VA_ARGS__


/**
 * @ingroup hwa_pub
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
 * @ingroup hwa_pub
 * @brief `hwa( action, object [,...] )` stores an @ref using_actions "action"
 *        for an @ref using_objects "object" into a *HWA context*.
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
 * @ingroup hwa_dev
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
/*  h: prefix used, "hw" or "hwa"
 *  f: 1st arg, function
 *  c: 2nd arg, class
 */
#define hwx(h,f,x,...)			_HW_B(_hwx0_,_hw_par x)(h,f,x,__VA_ARGS__)
/*
 *  x is ()
 */
#define _hwx0_1(h,f,x,...)		_hwx01(h,f,HW_X x,__VA_ARGS__)
#define _hwx01(h,f,x,...)		_HW_B(_hwx01,x)(h,f,x,__VA_ARGS__)
#define _hwx011(h,f,x,o,e,...)		HW_E(e) hw_foo()
#define _hwx010				_hwx_0

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
 *  o is not an object. Look for h_f_o
 */
#define _hwx_11(h,f,c,o,...)		_HW_B(_hwx_11,_hw_par o)(h,f,c,o,__VA_ARGS__)
#define _hwx_111(h,f,c,o,e,...)		_hwx_14(h,e,f,h##f##_,__VA_ARGS__)
#define _hwx_110(h,f,c,o,e,...)		_hwx_12(h,e,f,h##f##_##o,o,__VA_ARGS__)

#define _hwx_12(...)			_hwx_13(__VA_ARGS__)
#define _hwx_13(h,e,f,x,...)		_HW_B(_hwx_13,x)(h,e,f,x,__VA_ARGS__)
#define _hwx_131(h,e,f,z,y,...)		y(__VA_ARGS__)
/*
 *      Look for h_f_
 */
#define _hwx_130(h,e,f,m,...)		_hwx_14(h,e,f,h##f##_,__VA_ARGS__)
#define _hwx_14(...)			_hwx_15(__VA_ARGS__)
#define _hwx_15(h,e,f,x,...)		_HW_B(_hwx_15,x)(h,e,f,x,__VA_ARGS__)
#define _hwx_151(h,f,z,y,...)		y(__VA_ARGS__)
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
/*
 *  Error: list valid actions if known.
 */
#define _hwx_80(h,f,c,o)		HW_B(_hwx_80,_##h##actions_##c)(h,f,c,o)
#define _hwx_800(h,f,c,o)		HW_E(HW_EM_OCM(o,c,f)) hw_foo()
#define _hwx_801(h,f,c,o)		HW_E(HW_EM_AOCL(f,o,c,HW_A1(_##h##actions_##c))) hw_foo()


/**
 * @ingroup hwa_dev
 * @brief Private version of hw().
 * @hideinitializer
 *
 * -
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
 * @ingroup hwa_dev
 * @brief Private version of hwa().
 * @hideinitializer
 *
 * -
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
 * @ingroup hwa_dev
 * @brief Second version of _hwa().
 * @hideinitializer
 *
 * Useful for external objects (such as HW_SWUARTA) that configure themselves
 * their objects.
 */
#define _hw_a(...)			_hw_a1(__VA_ARGS__,)
#define _hw_a1(f,o,...)			_hw_a2(f,HW_X(o),__VA_ARGS__)
#define _hw_a2(...)			_hw_a3(__VA_ARGS__)
#define _hw_a3(f,c,...)			HW_B(_hw_a4,c)(f,c,__VA_ARGS__)
#define _hw_a41(c,o,e,...)		HW_E(e)	// Error, stop here.
#define _hw_a40(f,c,...)		HW_B(_hw_a5,hwa_##f##_##c)(f,c,__VA_ARGS__)
#define _hw_a51(f,c,...)		HW_A1(hwa_##f##_##c)(__VA_ARGS__)
#define _hw_a50(f,c,o,...)		HW_E_OCM(o,c,hwa_##f)


/**
 * @ingroup hwa_pub
 * @brief Declares the appropriate structure that holds the status
 *        of an @ref using_objects "object".
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
 * @ingroup hwa_pub
 * @brief Declares an unsigned integer.
 * @hideinitializer
 *
 * * `hw_uint_t(8)` expands to `uint8_t`;
 * * `hw_uint_t(16)` expands to `uint16_t`.
 *
 * This is useful when you need to store a value whose size depends on an
 * object:
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
#define _hw_uintt10(n)			HW_E(HW_EM_XNIL(n,(8,16))) uint8_t

