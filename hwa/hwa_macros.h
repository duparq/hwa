
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief General purpose macro definitions usable in C or assembler source code.
 *
 *  Upper case definitions process arbitrary lists of arguments.
 *
 *  Lower case definitions deal with lists of arguments starting with an object
 *  name or an object definition starting with a class name.
 */


/**
 * @ingroup public_ins
 * @brief Trigger an error at preprocessing stage
 * @hideinitializer
 *
 *  Error handling is based on the C99 _Pragma operator. It produces a
 *  preprocessing error as soon as the _Pragma(...) sentence is produced, be it
 *  inside or outside of a C function definition, or in an assembler
 *  source. _Pragma(...) can not be processed by macros as the sentence is
 *  removed from the preprocessor output and replaced by a void token.
 *
 *  The error message 's' must be a single argument, i.e. it must not contain
 *  commas.
 */
#define HW_E(s)			_HW_E2(GCC error HW_QUOTE(HWA: s.))
#define _HW_E2(s)		_HW_E3(s)
#if !defined HW_XE
#  define _HW_E3(s)		_Pragma(#s)
#else
#  define _HW_E3(s)		_xPragma(#s)
#endif

#define HW_E_O(x)		HW_E(`x` is not an object)
#define HW_E_P(x)		HW_E(`x` is not a pin)
#define HW_E_OM()		HW_E(missing object name)
#define HW_E_T(x)		HW_E(unrecognized token `x`)
#define HW_E_V()		HW_E(missing value)
#define HW_E_G(x)		HW_E(garbage parameters starting with `x`)
#define HW_E_K(k,x)		HW_E(expected `k` instead of `x`)

#define HW_E_OCM(o,c,m)		HW_E(object `o` of class `c` has no method named `m`)
#define HW_E_CM(c,m)		HW_E(class `c` has no method `m`)
#define HW_E_ST(x)		HW_E(`x` is not `on | off`)
#define HW_E_VL(v,l)		HW_E(`v` is not `l`)
#define HW_E_AVM(a)		HW_E(missing value for `a`)
#define HW_E_AVL(a,v,l)		HW_E(`a` can be `l` but not `v`)
#define HW_E_OAVL(a,v,l)	HW_E(optionnal parameter `a` can be `l` but not `v`)
#define HW_E_OKVL(k,v,l)	HW_E(value `v` for optionnal parameter `k` is not l)
#define HW_E_OO(o,x)		HW_E(object `o` has no relative named `x`)
#define HW_E_IOFN(o,a,v,l)	HW_E(`o`: `a` can be `l` but not `v`)
#define HW_E_IMP(f)		HW_E(`f`: not implemented for this target)

#define HW_ERROR		HW_E


/**
 * @ingroup private_mac
 * @brief Element a0 of the list a0,...
 * @hideinitializer
 */
#define HW_A0(...)		_HW_A0_2(__VA_ARGS__,)
#define _HW_A0_2(a0,...)	a0


/**
 * @ingroup private_mac
 * @brief Element a1 of the list a0,a1,...
 * @hideinitializer
 */
#define HW_A1(...)		_HW_A1_2(__VA_ARGS__,,)
#define _HW_A1_2(a0,a1,...)	a1


/**
 * @ingroup private_mac
 * @brief Element a2 of the list a0,a1,a2,...
 * @hideinitializer
 */
#define HW_A2(...)		_HW_A2_2(__VA_ARGS__,,,)
#define _HW_A2_2(a0,a1,a2,...)	a2


/**
 * @ingroup private_mac
 * @brief Element a2 of the list a0,a1,a2,...
 * @hideinitializer
 */
#define HW_TL(...)		_HW_TL2(__VA_ARGS__)
#define _HW_TL2(a0,...)		__VA_ARGS__


/**
 * @ingroup private_mac
 * @brief Glue the first two elements of the list with a '_' between them.
 * @hideinitializer
 */
#define HW_G2(...)		_HW_G2_(__VA_ARGS__,,)
#define _HW_G2_(a,b,...)	a##_##b


/**
 * @ingroup private_mac
 * @brief Glue the first three elements of the list with a '_' between them.
 * @hideinitializer
 */
#define HW_G3(...)		_HW_G3_(__VA_ARGS__,,,)
#define _HW_G3_(a,b,c,...)	a##_##b##_##c


/**
 * @ingroup private_mac
 * @brief Expands to 1 if the first two elements of the list are defined equal, 0 otherwise.
 *
 * For that to work, `HW_IS()` must be used as `HW_IS(x,y)` and there must be a
 * definition of `_hw_is_x_y` that expands as '`, 1`'
 *
 * @hideinitializer
 */
#define HW_IS(...)		_HW_IS_2(__VA_ARGS__,,)
#define _HW_IS_2(x,y,...)	HW_A1(_hw_is_##x##_##y,0)

#define _hw_is_0_0			, 1
#define _hw_is_				, 1
#define _hw_is__			, 1
#define _hw_is_enabled_enabled		, 1
#define _hw_is_disabled_disabled	, 1
#define _hw_is_yes_yes			, 1
#define _hw_is_no_no			, 1
#define _hw_is_off_off			, 1


/**
 * @ingroup private_mac
 * @brief Expands to 1 if the first element of the list is void, 0 otherwise.
 *
 * This is a more elaborate verification than `HW_IS(,x)` since it also accepts
 * x to begin with a left bracket.
 *
 * @hideinitializer
 */
#define HW_IS_VOID(...)		HW_X(_HW_IS_VOID_BKT,_hw_is__bkt __VA_ARGS__)(__VA_ARGS__)

#define _HW_IS_VOID_BKT_1(...)	0
#define _HW_IS_VOID_BKT_0(...)	HW_IS(,__VA_ARGS__)

#define _hw_is__bkt(...)


/**
 * @ingroup private_mac
 * @brief Concatenates '_1' or '_0' to the first argument according to the second.
 * @hideinitializer
 *
 * `HW_X(f,c)` expands to:
 *  * `f_1` if `c` is "",
 *  * `f_0` if `c` is not "".
 */
#define HW_X(...)			_HW_X2(__VA_ARGS__,,)
#define _HW_X2(f,x,...)			_HW_X3(f,_hw_is_##x,0,)
#define _HW_X3(...)			_HW_X4(__VA_ARGS__)
#define _HW_X4(f,x,y,...)		f##_##y


/**
 * @ingroup private_mac
 * @brief Connects a generic instruction to a method.
 * @hideinitializer
 *
 * @code
 * #define hw_myfunc(...)			HW_MTD(hw_myfunc, __VA_ARGS__,)
 * #define _hw_mtd_hw_myfunc__aclass(...)	, _hw_myfunc_aclass
 * @endcode
 *
 * makes the instruction `hw_myfunc()` accept an object of class `_aclass` as
 * first argument and expand as `_hw_myfunc_aclass(o,i,a,...)`.
 *
 * `HW_MTD()` verifies the existence of the object and its class method. An
 * explicit error message is produced if the object does not exist or if the
 * method is not supported by its class.
 *
 * __Note__ For instructions that accept a variable-length list of arguments,
 * it is advised to add a void argument to the list and check it after parsing
 * with `HW_TX()` or `HW_EOL()`.
 */

/* Note: an extra void argument must be added for single argument instructions
 * in order to avoid a compiler warning.
 */

#define HW_MTD(...)		_HW_MTD1(__VA_ARGS__)

/*  Get the definition of the object o. This will return the class in first
 *  position or void if an error occured.
 */
#define _HW_MTD1(f,o,...)	_HW_MTD2(f,HW_O(o),__VA_ARGS__)
#define _HW_MTD2(...)		_HW_MTD3(__VA_ARGS__)
#define _HW_MTD3(f,c,...)	HW_X(_HW_MTD3,c)(f,c,__VA_ARGS__)
#define _HW_MTD3_1(...)		//HW_E_OM() /* An error has been emitted by HW_O */

/*  Is there a method f for object o of class c?
 */
#define _HW_MTD3_0(f,c,...)	HW_X(_HW_MTD4,_hw_mtd_##f##_##c)(f,c,__VA_ARGS__)

#define _HW_MTD4_1(f,c,...)	HW_A1(_hw_mtd_##f##_##c)(__VA_ARGS__)

/*  Is there a method f for object o?
 */
#define _HW_MTD4_0(f,c,o,...)	HW_X(_HW_MTD5,_hw_mtd_##f##_##o)(f,c,o,__VA_ARGS__)
#define _HW_MTD5_1(f,c,o,...)	HW_E_OCM(o,c,f)


/**
 * @ingroup private_mac
 * @brief Connect a generic instruction to a method.
 * @hideinitializer
 *
 * This is used for internal instructions.
 */
#define _HW_MTD(...)		__HW_MTD1(__VA_ARGS__)
#define __HW_MTD1(f,o,...)	__HW_MTD2(f,o,_hw_def_##o,__VA_ARGS__)
#define __HW_MTD2(...)		__HW_MTD3(__VA_ARGS__)
#define __HW_MTD3(f,o,c,...)	HW_A1(_hw_mtd_##f##_##c)(o,__VA_ARGS__)



/**
 * @ingroup private_mac
 * @brief Specialize instruction `f` for class `c`: _HW_SPEC(f,c,...) -> f_c(...)
 * @hideinitializer
 *
 *  Arguments must start with a class name that is to be appended to the
 *  function name.
 */
#define _HW_SPEC(...)		__HW_SPEC_2(__VA_ARGS__)
#define __HW_SPEC_2(f,c,...)	f##_##c(__VA_ARGS__)

/**
 * @ingroup private_mac
 * @brief Returns `1` if the first element is the name of a HWA object, `0` if not.
 * @hideinitializer
 */
#define HW_ISON(o)		HW_IS(,HW_G2(_hw_class,HW_G2(_hw_def,o)))


/**
 * @ingroup private_mac
 * @brief Returns the first argument if the second is void, an error otherwise.
 * @hideinitializer
 *
 * This is used to help detecting and propagating errors, or ensuring that
 * there is no remaining elements in a list at the end of its parsing.
 */
#define HW_TX(result, ...)	HW_X(_HW_TX,__VA_ARGS__)((result),__VA_ARGS__,)
#define _HW_TX_0(result,x,...)	HW_E_T(x)
#define _HW_TX_1(result, ...)	_HW_TX_2 result
#define _HW_TX_2(...)		__VA_ARGS__


/**
 * @ingroup private_mac
 * @brief Trigger an error if the first argument is not void.
 * @hideinitializer
 *
 * This is used to ensure that there is no remaining elements in a list at the
 * end of its parsing.
 */
#define HW_EOL(...)		HW_X(_HW_EOL,__VA_ARGS__)(__VA_ARGS__,)
#define _HW_EOL_0(x,...)	HW_E_T(x)
#define _HW_EOL_1(...)


/**
 * @ingroup public_mac
 * @brief Build a C string from the first element in the list
 * @hideinitializer
 */
#define HW_QUOTE(...)		_HW_QUOTE_2(__VA_ARGS__,)
#define _HW_QUOTE_2(x,...)	#x



/**
 * @ingroup private_mac
 * @brief Returns the definition of the @ref using_objects "object".
 * @hideinitializer
 *
 * The argument can be an object name, an object definition starting with a
 * class name, or an error.
 *
 * If successful, returns the definition starting with a class name followed by the object
 * name: c,o,... Otherwise, triggers an error and returns a void token.
 */
#define HW_O(object)		_HW_O1(object)
#define _HW_O1(...)		HW_X(_HW_O2,_hw_class_##__VA_ARGS__)(__VA_ARGS__)
#define _HW_O2_1(...)		__VA_ARGS__		/*  Class name found, job's done. */
#define _HW_O2_0(o)		_HW_O3(o,_hw_def_##o)	/*  Is o an object's name? */
#define _HW_O3(...)		_HW_O4(__VA_ARGS__)
#define _HW_O4(o,...)		HW_X(_HW_O4,_hw_class_##__VA_ARGS__)(o,__VA_ARGS__)
#define _HW_O4_1(o,c,...)	c,o,__VA_ARGS__
#define _HW_O4_0(o,...)		HW_X(_HW_O5,o)(o)	/*  o is not an object, produce an error. */
#define _HW_O5_0(o)		HW_E_O(o)
#define _HW_O5_1(o)		HW_E_OM()


/**
 * @ingroup private_mac
 * @brief Returns the definition of the @ref using_objects "object".
 * @hideinitializer
 *
 * This is an equivalent for HW_O() but without error checking.
 */
#define _HW_O(o)		__HW_O1(o,_hw_def_##o)
#define __HW_O1(...)		__HW_O2(__VA_ARGS__)
#define __HW_O2(o,c,...)	c,o,__VA_ARGS__


/**
 * @ingroup public_ins_obj
 * @brief Executes an @ref using_actions "action" immediately on an @ref using_objects "object".
 * @hideinitializer
 *
 * Additional arguments may follow.
 *
 * An explicit error message is produced if the object does not exist or if it
 * does not support the action.
 *
 * @code
 * hw( configure, pin_pa0, direction, output );
 * hw( write, counter0, 0 );
 * @endcode
 */

/*  Make prefix 'hw_' or 'hwa_' an argument, have the arguments expanded, and
 *  add a void argument to signal the end of the list.
 */
#if defined DOXYGEN
#  define hw(action,object,...)
#else
#  define hw(...)		_hwx1(hw,__VA_ARGS__,,)
#endif


/**
 * @ingroup public_ins_obj
 * @brief Store @ref using_actions "action" on @ref using_objects "object" into the context.
 * @hideinitializer
 *
 * Additional arguments may follow.
 *
 * An explicit error message is produced if the object does not exist or if it
 * does not support the action.
 *
 * The context must have been created with the `hwa_begin()` or the
 * `hwa_begin_from_reset()` instruction.
 *
 * The `hw_commit()` instruction triggers the production of the machine code.
 *
 * The `hw_nocommit()` instruction does not produce code and is useful to put
 * the context in a known state.
 *
 * @code
 * hwa( configure, pin_pa0, direction, output );
 * hwa( write, counter0, 0 );
 * @endcode
 */
#if defined DOXYGEN
#  define hwa(action,object,...)
#else
#  define hwa(...)		_hwx1(hwa,__VA_ARGS__,,)
#endif


#define _hwx1(h,f,o,...)	_hwx2(h,f,HW_O(o),__VA_ARGS__)
#define _hwx2(...)		_hwx3(__VA_ARGS__)

/*  Do not proceed further in case of error
 */
#define _hwx3(h,f,c,...)	HW_X(_hwx4,c)(h,f,c,__VA_ARGS__)
#define _hwx4_1(...)		// HW_E_OM() /* An error has already been emitted by HW_O */

/*  Look for a class method x_f for object o of class c.
 */
#define _hwx4_0(h,f,c,...)	HW_X(_hwx5,_hw_mtd_##h##_##f##_##c)(h,f,c,__VA_ARGS__)
#define _hwx5_1(h,f,c,...)	HW_A1(_hw_mtd_##h##_##f##_##c)(__VA_ARGS__)

/*  Look for a method x_f for object o.
 */
#define _hwx5_0(h,f,c,o,...)	HW_X(_hwx6,_hw_mtd_##h##_##f##_##o)(h,f,c,o,__VA_ARGS__)
#define _hwx6_1(h,f,c,o,...)	HW_A1(_hw_mtd_##h##_##f##_##o)(__VA_ARGS__)

/*  Look for a global method
 */
#define _hwx6_0(h,f,...)	HW_X(_hwx7,_hw_mtd_##h##_##f)(h,f,__VA_ARGS__)
#define _hwx7_1(h,f,...)	HW_A1(_hw_mtd_##h##_##f)(__VA_ARGS__)
#define _hwx7_0(h,f,c,o,...)	HW_E_OCM(o,c,h(f,...))


/*  Internal use only version
 */
#define _hw(...)		__hw1(__VA_ARGS__,)
#define __hw1(f,o,...)		__hw2(f,HW_O(o),__VA_ARGS__)
#define __hw2(...)		__hw3(__VA_ARGS__)
#define __hw3(f,c,...)		HW_X(__hw4,c)(f,c,__VA_ARGS__)
#define __hw4_1(...)		// An error has been emitted. Stop here.

/*  Look for a method x_f for object o of class c.
 */
#define __hw4_0(f,c,...)	HW_X(__hw41,_hw_mtd_hw_##f##_##c)(f,c,__VA_ARGS__)
#define __hw41_1(f,c,...)	HW_A1(_hw_mtd_hw_##f##_##c)(__VA_ARGS__)
#define __hw41_0(f,c,o,...)	HW_E_OCM(o,c,hw_##f)


/*  Internal use only version
 */
#define _hwa(...)		__hwa1(__VA_ARGS__,)
#define __hwa1(f,o,...)		__hwa2(f,HW_O(o),__VA_ARGS__)
#define __hwa2(...)		__hwa3(__VA_ARGS__)

/*  Do not proceed further in case of error
 */
#define __hwa3(f,c,...)		HW_X(__hwa4,c)(f,c,__VA_ARGS__)
#define __hwa4_1(...)		//HW_E(processing error: HW_QUOTE(__hwa4_0(f,c,__VA_ARGS__)))

/*  Look for a method x_f for object o of class c.
 */
#define __hwa4_0(f,c,...)	HW_X(__hwa41,_hw_mtd_hwa_##f##_##c)(f,c,__VA_ARGS__)
#define __hwa41_1(f,c,...)	HW_A1(_hw_mtd_hwa_##f##_##c)(__VA_ARGS__)
#define __hwa41_0(f,c,o,...)	HW_E_OCM(o,c,hwa_##f)

#if 0
/**
 * @ingroup public_ins_obj
 * @brief Implement methods of an object.
 * @hideinitializer
 *
 * The optionnal argument `static` can be specified to have the methods prefixed
 * with the `static` keyword.
 *
 * @code
 * HW_IMPLEMENT(sensor0);
 * @endcode
 * @code
 * HW_IMPLEMENT(sensor0,static);
 * @endcode
 */
/*    Do not use hw() to keep it enabled for expansion.
 */
#define HW_IMPLEMENT(...)	_HW_IMP1(__VA_ARGS__,,)
#define _HW_IMP1(o,...)		_HW_IMP2(HW_O(o),__VA_ARGS__)
#define _HW_IMP2(...)		_HW_IMP3(__VA_ARGS__)
#define _HW_IMP3(c,...)		HW_X(_HW_IMP4,c)(c,__VA_ARGS__)
#define _HW_IMP4_1(...)		// An error message has been emitted. Stop here.
#define _HW_IMP4_0(c,...)	HW_X(_HW_IMP5,_hw_implement_##c)(c,__VA_ARGS__)
#define _HW_IMP5_0(c,o,...)	HW_E_OCM(o,c,HW_IMPLEMENT)
#define _HW_IMP5_1(c,o,i,a,p,...)	HW_X(_HW_IMP6,_hw_implement_prefix_##p)(c,o,i,a,p)
#define _HW_IMP6_1(c,...)	HW_A1(_hw_implement_##c)(__VA_ARGS__)
#define _HW_IMP6_0(c,o,i,a,p)	HW_E_VL(p, static or "" )

#define _hw_implement_prefix_		, 1
#define _hw_implement_prefix_static	, 1


/**
 * @ingroup public_ins_obj
 * @brief Check the definition of an external object.
 * @hideinitializer
 *
 * @code
 * HW_CHECK(sensor0);
 * @endcode
 */
#define HW_CHECK(o)		_HW_CHK2(HW_O(o))
#define _HW_CHK2(...)		_HW_CHK3(__VA_ARGS__)
#define _HW_CHK3(c,...)		HW_X(_HW_CHK4,c)(c,__VA_ARGS__)
#define _HW_CHK4_1(...)		// An error message has been emitted.
#define _HW_CHK4_0(c,...)	HW_X(_HW_CHK5,_hw_check_##c)(c,__VA_ARGS__)
#define _HW_CHK5_0(c,o,...)	HW_E_OCM(o,c,HW_CHECK)
#define _HW_CHK5_1(c,...)	HW_A1(_hw_check_##c)(__VA_ARGS__)
#endif


/*  Define wich classes are hardware bits
 */
#define _hw_isa_reg__r8			, 1
#define _hw_isa_reg__r16		, 1
#define _hw_isa_reg__r32		, 1
#define _hw_isa_reg__cb1		, 1
#define _hw_isa_reg__cb2		, 1
#define _hw_isa_reg__ob1		, 1
#define _hw_isa_reg__ob2		, 1
#define _hw_isa_reg__xob1		, 1
#define _hw_isa_reg__xob2		, 1


/**
 * @ingroup public_ins_obj
 * @brief Returns the memory definition for register `reg` of @ref using_objects "object".
 * @hideinitializer
 *
 * The word _register_ here stands for "set of bits" that may be sprayed over 2
 * hardware registers. It can be a hardware register as well as a logical
 * register.
 *
 * Successful results can be:
 *
 *  * `_m1, o,a, r,rc,ra,rwm,rfm, rbn,rbp`
 *
 *  * `_m2, o,a, r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,
 *		 r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2`
 *
 * with:
 *
 *  * '`_m1`': class of one group of consecutive bits in one hardware register
 *
 *  * '`_m2`': class of a set of bits made of two groups of consecutive bits in
 *	     one or two hardware registers
 *
 *  * `o`: the object name
 *
 *  * `a`: the base address of the object
 *
 *  * `r`: the name of the hardware register
 *
 *  * `rc`: the class of the hardware register
 *
 *  * `ra`: the address of the hardware register relative to the address of the object
 *
 *  * `rwm`: the mask of bits that are writeable
 *
 *  * `rfm`: the mask of flag bits (bits that are reset by writing 1 in them)
 *
 *  * `rbn`: the number of consecutive bits concerned
 *
 *  * `rbp`: the position of the least significant bit of the group in the hardware register
 *
 *  * `vbp`: the position of the least significant bit of the group in the value
 *
 */
#if defined DOXYGEN
#  define HW_REGISTER(object, reg)
#else
#  define HW_REGISTER(o,x)		_HW_M1(HW_O(o),x)
#endif
#define _HW_M1(...)			_HW_M2(__VA_ARGS__)
#define _HW_M2(c,...)			HW_X(_HW_M2,c)(c,__VA_ARGS__)
#define _HW_M2_1(...)			// Error: return void 
#define _HW_M2_0(c,o,i,a,r)		_HW_M4(_hw_reg_##c##_##r,o,c,a,r)
#define _HW_M4(...)			_HW_M5(__VA_ARGS__)
#define _HW_M5(t,...)			HW_X(_HW_M5,_hw_isa_reg_##t)(t,__VA_ARGS__)
#define _HW_M5_1(t,...)			_hw_r2m_##t(__VA_ARGS__)
#define _HW_M5_0(t,o,c,a,r)		_HW_M6(_hw_reg_##o##_##r,o,c,a,r)
#define _HW_M6(...)			_HW_M7(__VA_ARGS__)
#define _HW_M7(t,...)			HW_X(_HW_M7,_hw_isa_reg_##t)(t,__VA_ARGS__)
#define _HW_M7_1(t,...)			_hw_r2m_##t(__VA_ARGS__)
#define _HW_M7_0(t,o,c,a,r)		HW_E(`o` has no register `r`)


/**
 * @ingroup private_ins
 * @brief Memory definition of a register (internal use, no error checking)
 * @hideinitializer
 */
#define _HW_M(o,r)			__HW_M2(o,_hw_def_##o,r)
#define __HW_M2(...)			__HW_M3(__VA_ARGS__)
#define __HW_M3(o,c,i,a,r)		__HW_M4(_hw_reg_##c##_##r,o,c,a,r)
#define __HW_M4(...)			__HW_M5(__VA_ARGS__)
#define __HW_M5(t,...)			HW_X(__HW_M5,_hw_isa_reg_##t)(t,__VA_ARGS__)
#define __HW_M5_1(t,...)		_hw_r2m_##t(__VA_ARGS__)
#define __HW_M5_0(t,o,c,a,r)		__HW_M6(_hw_reg_##o##_##r,o,c,a,r)
#define __HW_M6(...)			__HW_M5_1(__VA_ARGS__)

/* #define __HW_M5_0(t,o,c,a,r)		__HW_M7(_hw_reg_##o##_##r,o,c,a,r) */
/* #define __HW_M7(...)			__HW_M8(__VA_ARGS__) */
/* #define __HW_M8(t,...)			HW_X(__HW_M9,_hw_isa_reg_##t)(t,__VA_ARGS__) */
/* #define __HW_M9_1( */


/**
 * @ingroup private_ins
 * @brief Definition of class or object `o` hardware register `r`
 * @hideinitializer
 */
/*  We know that 'o' is defined but we do not know if 'r' is a class register or
 *  an object register.
 */
#define _HW_R(o,r)			__HW_R2(o,_hw_def_##o,r)
#define __HW_R2(...)			__HW_R3(__VA_ARGS__)
#define __HW_R3(o,c,i,a,r)		__HW_R4(_hw_reg_##c##_##r,o,c,a,r)
#define __HW_R4(...)			__HW_R5(__VA_ARGS__)
#define __HW_R5(t,...)			HW_X(__HW_R5,_hw_isa_reg_##t)(t,__VA_ARGS__)
#define __HW_R5_1(...)			__VA_ARGS__
#define __HW_R5_0(z,o,c,a,r)		_hw_reg_##o##_##r,o,c,a,r


/*  Convert a register definition to a memory definition of class _m1 or _m2
 *	-> _m1, o,a, r,rc,ra,rwm,rfm, bn,bp
 *	-> _m2, o,a, r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,
 *		     r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2
 */
/*
 *  Le nom du registre originel pourrait être conservé pour les messages
 *  d'erreur.
 */
#define _hw_r2m__r8(ra,rwm,rfm, o,c,a,r)	_m1,o,a,r, _r8,ra,rwm,rfm, 8,0
#define _hw_r2m__r16(ra,rwm,rfm, o,c,a,r)	_m1,o,a,r,_r16,ra,rwm,rfm,16,0
#define _hw_r2m__r32(ra,rwm,rfm, o,c,a,r)	_m1,o,a,r,_r32,ra,rwm,rfm,32,0
#define _hw_r2m__ob1(r,bn,bp, o,c,a,m)		_m1,o,0,r,_hw_reg_##o##_##r,bn,bp

/*  External object register can be a register of the target object's class
 */
#define _hw_r2m__xob1(to,tr,bn,bp,o,c,a,r)		_hw_r2m__xob12(_hw_reg_##to##_##tr,_hw_def_##to,to,tr,bn,bp)
#define _hw_r2m__xob12(...)				_hw_r2m__xob13(__VA_ARGS__)
#define _hw_r2m__xob13(t,...)				HW_X(_hw_r2m__xob13,_hw_isa_reg_##t)(t,__VA_ARGS__)
#define _hw_r2m__xob13_1(rc,ra,rwm,rfm,c,i,a,o,r,bn,bp)	_m1,o,a,r,rc,ra,rwm,rfm,bn,bp
#define _hw_r2m__xob13_0(x,c,i,a,o,r,bn,bp)		_hw_r2m__xob16(_hw_reg_##c##_##r,c,i,a,o,r,bn,bp)
#define _hw_r2m__xob16(...)				_hw_r2m__xob17(__VA_ARGS__)
#define _hw_r2m__xob17(rc,ra,rwm,rfm,c,i,a,o,r,bn,bp)	_m1,o,a,r,rc,ra,rwm,rfm,bn,bp

#define _hw_r2m__cb1(r,bn,bp, o,c,a,m)		_m1,o,a,r,_hw_reg_##c##_##r,bn,bp
#define _hw_r2m__cb2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, o,c,a,r)	\
  _m2,o,a, r1,_hw_reg_##c##_##r1,rbn1,rbp1,vbp1, r2,_hw_reg_##c##_##r2,rbn2,rbp2,vbp2
#define _hw_r2m__ob2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, o,c,a,r)	\
  _m2,o,a, r1,_hw_reg_##o##_##r1,rbn1,rbp1,vbp1, r2,_hw_reg_##o##_##r2,rbn2,rbp2,vbp2
#define _hw_r2m__xob2(to, r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, o,c,a,m) \
  _m2,o,a, r1,_hw_reg_##to##_##r1,rbn1,rbp1,vbp1, r2,_hw_reg_##to##_##r2,rbn2,rbp2,vbp2


/**
 * @ingroup public_ins_obj
 * @brief Returns the address of the @ref using_objects "object".
 * @hideinitializer
 *
 * The object should be a peripheral controller or a register.
 */
/*  The argument can be an object definition
 */
#if defined DOXYGEN
#  define HW_ADDRESS(object)
#else
#  define HW_ADDRESS(...)		HW_MTD(HW_ADDRESS, __VA_ARGS__,)
#endif


/* This is defined in the vendor-specific file since the address can be
 * different between C and assembler.
 */
#define _hw_mtd_HW_ADDRESS__m1		, _HW_ADDRESS__m1
#define _hw_mtd_HW_ADDRESS__r32		, _HW_ADDRESS__r32


/**
 * @ingroup private_ins
 * @brief  Address of an object's register (internal use)
 * @hideinitializer
 */
#define _HW_A(...)			_HW_SPEC(_HW_ADDRESS, __VA_ARGS__)


/**
 * @ingroup public_ins_obj
 * @brief Returns the number of bits of the @ref using_objects "object".
 * @hideinitializer
 */
/*  The argument can be an object definition
 */
#if defined DOXYGEN
#  define HW_BITS(object)
#else
#  define HW_BITS(...)			HW_MTD(HW_BITS, __VA_ARGS__,)
#endif

#define _hw_mtd_HW_BITS__m1		, _HW_BITS__m1

#define _HW_BITS__m1(o,a, r,rw,ra,rwm,rfm, bn,bp)	bn


/**
 * @ingroup public_ins_obj
 * @brief Returns the position of the least significant bit of the @ref using_objects "object".
 * @hideinitializer
 */
/*  The argument can be an object definition
 */
#if defined DOXYGEN
#  define HW_POSITION(object)
#else
#  define HW_POSITION(...)				HW_MTD(HW_POSITION, __VA_ARGS__,)
#endif

#define _hw_mtd_HW_POSITION__m1	, _HW_POSITION__m1

#define _HW_POSITION__m1(o,a, r,rw,ra,rwm,rfm, bn,bp,...)	bp


/**
 * @ingroup private_mac
 * @brief Number of bits of the register `r` of @ref using_objects "object" `o`.
 * @hideinitializer
 */
#define _HW_MBN(o,r)					_HW_SPEC(_HW_MBN,_HW_M(o,r))
#define _HW_MBN__m1(o,a, r,rc,ra,rwm,rfm, bn,bp)	bn


/**
 * @ingroup private_mac
 * @brief Position of the least significant bit of the register `r` of @ref using_objects "object" `o`.
 * @hideinitializer
 */
#define _HW_MBP(o,r)					_HW_SPEC(_HW_MBP,_HW_M(o,r))
#define _HW_MBP__m1(o,a, r,rc,ra,rwm,rfm, bn,bp)	bp


/**
 * @ingroup public_ins
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
#define _hw_uintt0(n)			HW_G2(_hw_uintt1,HW_IS(8,n##_))(n)
#define _hw_uintt1_1(n)			uint8_t
#define _hw_uintt1_0(n)			HW_G2(_hw_uintt2,HW_IS(16,n##_))(n)
#define _hw_uintt2_1(n)			uint16_t
#define _hw_uintt2_0(n)			HW_E_VL(n,8|16) uint8_t

#define _hw_is_8_8_			, 1
#define _hw_is_16_16_			, 1

/**
 * @ingroup private_ins
 * @brief Class of the register `r` of object `o`.
 * @hideinitializer
 */
#define _HW_RC(o,r)			HW_A0(_HW_R(o,r))


/**
 * @ingroup public_ins_obj
 * @brief Returns the ID of the @ref using_objects "object" or 0 if the object does not exist.
 * @hideinitializer
 */
/*  We do not use HW_O() because HW_ID() should not trigger an error if 'object'
 *  is not an object.
 */
#define HW_ID(object)			HW_G2(_HW_ID,HW_ISON(object))(object)
#define _HW_ID_1(o)			HW_A1(_hw_def_##o)
#define _HW_ID_0(o)			0


/**
 * @ingroup public_ins_obj
 * @brief Returns the name of the relative object `x` of the @ref using_objects "object".
 *
 * Many peripheral controllers are implemented by a set of objects that have a
 * relationship. Typically, the Atmel AVR timer/counters are implemented through
 * one counting unit, optionnal compare units, and optionnal capture
 * units. Output pins of the compare units are relatives of the compare units.
 * 
 * For example, the Atmel AVR ATmega328P has a compare output pin named OC0A
 * that is the output of the compare unit A of the TIM0 timer/counter. With HWA,
 * TIM0 is called `counter0` and its first compare unit (A) is called
 * `counter0compare0`.
 * 
 *  * `HW_RELATIVE( counter0, compare0 )` returns `counter0compare0`.
 *  * `HW_RELATIVE( counter0compare0, counter )` returns `counter0`.
 *  * `HW_RELATIVE( counter0compare0, pin )` returns `pin_pd6`.
 * 
 * The `HW_RELATIVE()` instruction is useful to make the source code less
 * dependant of the choice of the peripherals. For example, you define the
 * symbol PWM to hold the name of the compare unit whose output pin will produce
 * a PWM signal. You can configure its related objects, namely the counting unit
 * and the ouput pin, this way:
 * 
 * @code
 * #define PWM	counter0compare0
 * ...
 * hwa( configure, PWM, set_at_bottom_clear_on_match );
 * hwa( configure, HW_RELATIVE(PWM,counter), countmode, up_loop );
 * hwa( write, PWM, (1U<<HW_BITS(PWM))/2 ); // 50% duty cycle
 * @endcode
 * 
 * If in the future you must use `counter2compare1` instead of
 * `counter0compare0`, you just need to change the definition of the PWM symbol
 * accordingly and the rest of the code will remain unchanged.
 *
 * @hideinitializer
 */
/*  Check the object name,
 *  look for an object relative,
 *  look for a class-defined HW_REL() method.
 */
#define HW_RELATIVE(object,x)		_HW_REL1(object,x)
#define HW_REL(o,x)			_HW_REL1(o,x)
#define _HW_REL1(...)			_HW_REL2(__VA_ARGS__)
#define _HW_REL2(o,x)			HW_X(_HW_REL2,o)(o,x)
#define _HW_REL2_1(o,x)			HW_E_OM()
#define _HW_REL2_0(o,x)			HW_G2(_HW_REL3,HW_ISON(o))(o,x)
#define _HW_REL3_0(o,x)			HW_E_O(o)
#define _HW_REL3_1(o,x)			HW_G2(_HW_REL4,HW_ISON(_hw_rel_##o##_##x))(o,x)
#define _HW_REL4_1(o,x)			_hw_rel_##o##_##x
#define _HW_REL4_0(o,x)			_HW_REL4(o,x,_hw_def_##o)
#define _HW_REL4(...)			_HW_REL5(__VA_ARGS__)
#define _HW_REL5(o,x,c,...)		HW_X(_HW_REL5,_hw_class_##c)(o,x,c,__VA_ARGS__)
#define _HW_REL5_0(o,x,...)		HW_E_OO(o,x)
#define _HW_REL5_1(o,x,c,...)		HW_X(_HW_REL6,_hw_mtd_HW_RELATIVE_##c)(o,x,c,__VA_ARGS__)
#define _HW_REL6_0(o,x,...)		HW_E_OO(o,x)
#define _HW_REL6_1(o,x,c,...)		HW_A1(_hw_mtd_HW_RELATIVE_##c)(o,x,__VA_ARGS__)

/**
 * @ingroup private_ins
 * @brief Returns the name of the relative `x` of object `o`.
 * @hideinitializer
 *
 * The public version of `HW_RELATIVE()` fails if one of the arguments is the
 * result of a `HW_RELATIVE()`. This private version should be used instead in
 * internal HWA code.
 */
#define _HW_REL(o,x)			__HW_REL2(o,x)
#define __HW_REL2(o,x)			_hw_rel_##o##_##x


/**
 * @ingroup private_ins
 * @brief Returns the name of the relative `x` of object `o`.
 * @hideinitializer
 *
 * An alternative to `_HW_REL()` used by class _swuarta.
 */
#define _HW_RV(o,x)			__HW_RV2(o,x)
#define __HW_RV2(o,x)			_hw_rel_##o##_##x


/**
 * @ingroup public_ins_obj
 * @brief Returns the canonical name of pin `p`.
 * @hideinitializer
 */
#define HW_PIN(p)		_HW_PIN1(p,_hw_pin_##p,)
#define _HW_PIN1(...)		_HW_PIN2(__VA_ARGS__)
#define _HW_PIN2(o,x,...)	HW_X(_HW_PIN,x)(o,__VA_ARGS__)
#define _HW_PIN_0(o,...)	HW_E_P(o)
#define _HW_PIN_1(o,p,...)	p


/**
 * @ingroup private_ins
 * @brief Returns the canonical name of pin `p` of object `o`.
 * @hideinitializer
 */
#define _HW_PIN(o,p)		HW_A1(_hw_pin_##o##_##p,)


/**
 * @ingroup public_ins_obj
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
