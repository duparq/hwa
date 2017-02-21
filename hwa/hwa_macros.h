
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


/*	State definitions		, positive, negative
 */
#define _hw_state_on			, 1, 0
#define _hw_state_off			, 0, 1
#define _hw_state_yes			, 1, 0
#define _hw_state_no			, 0, 1
#define _hw_state_enabled		, 1, 0
#define _hw_state_disabled		, 0, 1

/**
 * @ingroup private_classes
 * @brief 8-bit hardware register class.
 */
#define _hw_class__r8


/**
 * @ingroup private_classes
 * @brief 16-bit hardware register class.
 */
#define _hw_class__r16


/**
 * @ingroup private_classes
 * @brief 32-bit hardware register class.
 */
#define _hw_class__r32


/**
 * @ingroup private_classes
 * @brief Class logical register made of one group of consecutive bits.
 */
#define _hw_class__cb1


/**
 * @ingroup private_classes
 * @brief Class logical register made of two groups of consecutive bits.
 */
#define _hw_class__cb2


/**
 * @ingroup private_classes
 * @brief Object logical register made of one group of consecutive bits.
 */
#define _hw_class__ob1


/**
 * @ingroup private_classes
 * @brief Object logical register made of two groups of consecutive bits.
 */
#define _hw_class__ob2


/**
 * @ingroup private_classes
 * @brief Interrupt object class.
 */
#define _hw_class__irq


/**
 * @ingroup private_classes
 * @brief Memory definition of one group of consecutive bits.
 */
#define _hw_class__m1


/**
 * @ingroup private_classes
 * @brief Memory definition of two groups of consecutive bits.
 */
#define _hw_class__m2


/**
 * @ingroup private_classes
 * @brief Object logical register made of one group of consecutive bits.
 */
#define _hw_class__xob1


/**
 * @ingroup public_gen_macros
 * @brief Emit an error at preprocessing stage
 * @hideinitializer
 */
/*  Error handling is based on the C99 _Pragma operator. It produces a
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
#define HW_E_OM()		HW_E(missing object name)
#define HW_E_T(x)		HW_E(unrecognized token `x`)

#define HW_E_OCM(o,c,m)		HW_E(object `o` of class `c` has no method named `m`)
#define HW_E_CM(c,m)		HW_E(class `c` has no method `m`)
#define HW_E_ST(x)		HW_E(`x` is not `on | off`)

#define HW_E_VL(v,l)		HW_E(`v` is not `l`)
#define HW_E_AVM(a)		HW_E(missing value for `a`)
#define HW_E_AVL(a,v,l)		HW_E(`a` can be `l` but not `v`)
#define HW_E_OAVL(a,v,l)	HW_E(optionnal parameter `a` can be `l` but not `v`)
#define HW_E_OO(o,x)		HW_E(object `o` has no relative named `x`)
#define HW_E_IOFN(o,a,v,l)	HW_E(`o`: `a` can be `l` but not `v`)

#define HW_ERROR		HW_E


/**
 * @ingroup public_gen_macros
 * @brief Element a0 of the list a0,...
 * @hideinitializer
 */
#define HW_A0(...)		_HW_A0_2(__VA_ARGS__,)
#define _HW_A0_2(a0,...)	a0


/**
 * @ingroup public_gen_macros
 * @brief Element a1 of the list a0,a1,...
 * @hideinitializer
 */
#define HW_A1(...)		_HW_A1_2(__VA_ARGS__,,)
#define _HW_A1_2(a0,a1,...)	a1


/**
 * @ingroup public_gen_macros
 * @brief Element a2 of the list a0,a1,a2,...
 * @hideinitializer
 */
#define HW_A2(...)		_HW_A2_2(__VA_ARGS__,,,)
#define _HW_A2_2(a0,a1,a2,...)	a2


/**
 * @ingroup public_gen_macros
 * @brief Glue the first two elements of the list with a '_' between them.
 * @hideinitializer
 */
#define HW_G2(...)		_HW_G2_(__VA_ARGS__,,)
#define _HW_G2_(a,b,...)	a##_##b


/**
 * @ingroup public_gen_macros
 * @brief Glue the first three elements of the list with a '_' between them.
 * @hideinitializer
 */
#define HW_G3(...)		_HW_G3_(__VA_ARGS__,,,)
#define _HW_G3_(a,b,c,...)	a##_##b##_##c


/**
 * @ingroup public_gen_macros
 * @brief Expands to 1 is the first two elements of the list are defined equal, 0 otherwise.
 *
 * For that to work, `HW_IS()` must be used as `HW_IS(x,y)` and there must be a
 * definition of `_hw_is_x_y` that expands as '`, 1`'
 *
 * @hideinitializer
 */
#define HW_IS(...)		_HW_IS_2(__VA_ARGS__,,)
#define _HW_IS_2(x,y,...)	HW_A1(_hw_is_##x##_##y,0)
#define _hw_is_0_0			, 1
#define _hw_is__			, 1
#define _hw_is_enabled_enabled		, 1
#define _hw_is_disabled_disabled	, 1
#define _hw_is_yes_yes			, 1
#define _hw_is_no_no			, 1
#define _hw_is_off_off			, 1


/**
 * @ingroup public_gen_macros
 * @brief Expands to 1 is the first element of the list is void, 0 otherwise.
 *
 * This is a more elaborate verification than `HW_IS(,x)` since it also accepts
 * x to begin with a left bracket.
 *
 * @hideinitializer
 */
#define HW_IS_VOID(...)		HW_G2(_HW_IS_VOID_BKT,HW_IS(,_hw_is__bkt __VA_ARGS__))(__VA_ARGS__)

#define _HW_IS_VOID_BKT_1(...)	0
#define _HW_IS_VOID_BKT_0(...)	HW_IS(,__VA_ARGS__)

#define _hw_is__bkt(...)


/**
 * @brief Connect a generic instruction to an object's class method.
 * @hideinitializer
 *
 * @code
 * #define hw_myfunc(...)			HW_MTHD(_hw_myfunc, __VA_ARGS__,)
 * @endcode
 *
 * makes the instruction `hw_myfunc()` accept an object name as first argument
 * and expand as the method `_hw_myfunc` of the object's class.
 *
 * @code
 * #define _hw_mthd__hw_myfunc__myclass(...)	, _hw_myfunc_myclass
 * @endcode
 *
 * declares the method `_hw_myfunc()` for the class `_myclass`.
 *
 * If the object `hw_myobject` pertains to the class `_myclass`, the instruction
 * `hw_myfunc( hw_myboject, a0, a1 )` is expanded as: `_hw_myfunc_myclass(
 * hw_myobject,i,a, a0, a1, )` where `i` is the ID of `hw_myobject` and `a` its
 * the base address, followed by the arguments passed to the instruction.
 *
 * `HW_MTHD()` verifies the existence of the object and its class method. An
 * explicit error message is produced if the object does not exist or if the
 * method is not supported by its class.
 *
 * __Note__: for instructions that accept a variable-length list of arguments,
 * it is advised to add a void argument to the list and check it after parsing
 * with `HW_TX()` or `HW_EOL()`.
 */

/* If `HW_A0(_hw_mthd_##f##_##c)` is not ``, then there is no method f for class
 * c. Then try to determine the reason:
 *
 *   * p is not a HWA object
 *   * c has no method f
 *   * p is an error
 *
 * Note: an extra void argument must be added for single argument instructions
 * in order to avoid a compiler warning.
 */

#define HW_MTHD(...)		_HW_MTHD1(__VA_ARGS__)

/*  Get the definition of the object o (assuming the object exists)
 */
#define _HW_MTHD1(f,o,...)	_HW_MTHD2(f,o,_hw_obj_##o,__VA_ARGS__)
#define _HW_MTHD2(...)		_HW_MTHD3(__VA_ARGS__)

/*  Is there a method f for object o of class c?
 */
#define _HW_MTHD3(f,o,c,...)	HW_G2(_HW_MTHD4, HW_IS(,_hw_mthd_##f##_##c))(f,o,c,__VA_ARGS__)
#define _HW_MTHD4_1(f,o,c,...)	HW_A1(_hw_mthd_##f##_##c)(o,__VA_ARGS__)

/* No method f for object o of class c. Is o an object?
 */
#define _HW_MTHD4_0(f,o,c,...)	HW_G2(_HW_MTHD5, HW_IS(,_hw_class_##c))(f,o,c,__VA_ARGS__)
#define _HW_MTHD5_1(f,o,c,...)	HW_E_OCM(o,c,f)

/* o is not an object. Is it a class name?
 */
#define _HW_MTHD5_0(f,o,...)	HW_G2(_HW_MTHD6,HW_IS(,_hw_class_##o))(f,o,__VA_ARGS__)

/* Is there a method f for class c?
 */
#define _HW_MTHD6_1(f,o,oo,...)	HW_G2(_HW_MTHD8, HW_IS(,_hw_mthd_##f##_##o))(f,o,__VA_ARGS__)
#define _HW_MTHD8_0(f,c,...)	HW_E_CM(c,f)
#define _HW_MTHD8_1(f,c,...)	HW_A1(_hw_mthd_##f##_##c)(__VA_ARGS__)

/* o is not an object and not a class name. Propagate or trigger an error.
 */
#define _HW_MTHD6_0(...)	HW_E(processing error)

/**
 */
#define _HW_MTHD(...)		__HW_MTHD1(__VA_ARGS__)
#define __HW_MTHD1(f,o,...)	__HW_MTHD2(f,o,_hw_obj_##o,__VA_ARGS__)
#define __HW_MTHD2(...)		__HW_MTHD3(__VA_ARGS__)
#define __HW_MTHD3(f,o,c,...)	HW_A1(_hw_mthd_##f##_##c)(o,__VA_ARGS__)



/**
 * @brief Specialize instruction `f` for class `c`: _HW_SPEC(f,t,...) -> f_c(...)
 *
 *  Arguments must start with a class name that is to be appended to the
 *  function name.
 */
#define _HW_SPEC(...)		__HW_SPEC_2(__VA_ARGS__)
#define __HW_SPEC_2(f,c,...)	f##_##c(__VA_ARGS__)


/**
 * @brief Apply generic instruction `f` to object `o` (applies to all HWA
 * objects).
 * @hideinitializer
 *
 * Expands to `f(class, o, id, address, ...)` if `o` is the name of a HWA object.
 * <ul><li>`f`: the instruction
 * <li>`o`: the name of the object
 * <li>`class`: the class of `o`
 * <li>`id`: the ID of `o`
 * <li>`address`: the address of `o`
 * </ul>
 */
#define _HW_GEN(f,o,...)	_HW_GEN2(f,HW_OD(o),__VA_ARGS__)
#define _HW_GEN2(...)		_HW_GEN3(__VA_ARGS__)
#define _HW_GEN3(f,c,...)	HW_G2(_HW_GEN,HW_IS(,c))(f,c,__VA_ARGS__)
#define _HW_GEN_0(f,...)	f(__VA_ARGS__)
#define _HW_GEN_1(f,o,...)	HW_E_MO()

/**
 * @ingroup public_gen_macros
 * @brief `1` if the first element is the name of a HWA object, `0` if not.
 * @hideinitializer
 */
#define HW_ISON(...)		HW_IS(,HW_G2(_hw_class,HW_G2(_hw_obj,__VA_ARGS__)))


/**
 * @brief `result` if the next element is void, an error otherwise.
 * @hideinitializer
 *
 * This is used to help detecting and propagating errors, or ensuring that
 * there is no remaining elements in a list at the end of its parsing.
 */
#define HW_TX(result, ...)	HW_G2(_HW_TX,HW_IS(,__VA_ARGS__))((result),__VA_ARGS__,)
#define _HW_TX_0(result,x,...)	HW_E_T(x)
#define _HW_TX_1(result, ...)	_HW_TX_2 result
#define _HW_TX_2(...)		__VA_ARGS__


/**
 * @brief Trigger an error if the first argument is not void.
 * @hideinitializer
 *
 * This is used to ensure that there is no remaining elements in a list at the
 * end of its parsing.
 */
#define HW_EOL(...)		HW_G2(_HW_EOL,HW_IS(,__VA_ARGS__))(__VA_ARGS__,)
#define _HW_EOL_0(x,...)	HW_E_T(x)
#define _HW_EOL_1(...)


/**
 * @ingroup public_gen_macros
 * @brief Build a C string from the first element in the list
 * @hideinitializer
 */
#define HW_QUOTE(...)		_HW_QUOTE_2(__VA_ARGS__,)
#define _HW_QUOTE_2(x,...)	#x



/**
 * @brief Expand the definition of an object.
 * @hideinitializer
 *
 * @code
 * HW_OD(o)
 * @endcode
 *
 * o can can be an object name, a class name starting an object definition, or
 * an error.
 *
 * Returns the definition starting with a class name followed by the object
 * name: c,o,... or a void token and emit an error.
 */

/*  If o is a class name, job's done
 */
#define HW_OD(o)		_HW_OD1(o)
#define _HW_OD1(...)		HW_G2(_HW_OD2,HW_IS(,_hw_class_##__VA_ARGS__))(__VA_ARGS__)
#define _HW_OD2_1(...)		__VA_ARGS__

/*  Is o an object's name?
 */
#define _HW_OD2_0(o)		_HW_OD3(o,_hw_obj_##o)
#define _HW_OD3(...)		_HW_OD4(__VA_ARGS__)
#define _HW_OD4(o,...)		HW_G2(_HW_OD4,HW_IS(,_hw_class_##__VA_ARGS__))(o,__VA_ARGS__)
#define _HW_OD4_1(o,c,...)	c,o,__VA_ARGS__

/*  o is not an object, produce an error
 */
#define _HW_OD4_0(o,...)	HW_G2(_HW_OD5, HW_IS(,o))(o)
#define _HW_OD5_0(o)		HW_E_O(o)
#define _HW_OD5_1(o)		HW_E_OM()


/**
 * @brief Generic instruction that applies an action to an object.
 * @hideinitializer
 *
 * @code
 * //  Apply action to object immediately.
 * //
 * hw( <action>, <object> [, <argument>]* );
 * @endcode
 *
 * @code
 * //  Store the action in the HWA context. The action will be performed
 * //  when the context is commited.
 * //
 * hwa( <action>, <object> [, <argument>]* );
 * @endcode
 *
 * <object> can be the name of an object or the result of a statement, e.g.:
 * `HW_REG(<object>,<register>)`, `HW_REL(<object>.<object>)` ...  Inside `hw()`
 * and `hwa()`, `hw_` prefixes can be omitted for the statements:
 * `reg(<object>,<register>)`, `rel(<object>.<object>)` ...
 *
 * Both `hw()` and `hwa()` verify that the object exists and that it supports
 * the action. An explicit error message is produced if the object does not
 * exist or if it does not support the action.
 */

/*  Make prefix 'hw_' or 'hwa_' an argument, have the arguments expanded, and
 *  add a void argument to signal the end of the list.
 */
#define hw(...)			_hwx0(hw_,__VA_ARGS__)
#define hwa(...)		_hwx0(hwa_,__VA_ARGS__)
#define _hwx0(...)		_hwx1(__VA_ARGS__,)
#define _hwx1(x,f,o,...)	_hwx2(x,f,HW_OD(o),__VA_ARGS__)
#define _hwx2(...)		_hwx3(__VA_ARGS__)

/*  Do not proceed further in case of error
 */
#define _hwx3(x,f,c,...)	HW_G2(_hwx4, HW_IS(,_hw_class_##c))(x,f,c,__VA_ARGS__)
#define _hwx4_0(x,f,c,...)	HW_G2(_hwx40, HW_IS(,c))(c)
#define _hwx40_1(...)		HW_E_OM()
#define _hwx40_0(c)		HW_E_O(c)

/*  Look for a method x_f for object o of class c.
 */
#define _hwx4_1(x,f,c,...)	HW_G2(_hwx5, HW_IS(,_hw_mthd_##x##f##_##c))(x,f,c,__VA_ARGS__)
#define _hwx5_1(x,f,c,...)	HW_A1(_hw_mthd_##x##f##_##c)(__VA_ARGS__)

/*  Look for a global method
 */
#define _hwx5_0(x,f,...)	HW_G2(_hwx6, HW_IS(,_hw_mthd_##x##f))(x,f,__VA_ARGS__)
#define _hwx6_1(x,f,...)	HW_A1(_hw_mthd_##x##f)(__VA_ARGS__)
#define _hwx6_0(x,f,c,o,...)	HW_E_OCM(o,c,f)



/*  Internal use only version
 */
#define _hwa(...)		__hwa1(__VA_ARGS__,)
#define __hwa1(f,o,...)		__hwa2(f,HW_OD(o),__VA_ARGS__)
#define __hwa2(...)		__hwa3(__VA_ARGS__)

/*  Do not proceed further in case of error
 */
#define __hwa3(f,c,...)		HW_G2(__hwa4, HW_IS(,_hw_class_##c))(f,c,__VA_ARGS__)
#define __hwa4_0(f,c,...)	HW_E(processing error: HW_QUOTE(__hwa4_0(f,c,__VA_ARGS__)))

/*  Look for a method x_f for object o of class c.
 */
#define __hwa4_1(f,c,...)	HW_G2(__hwa41, HW_IS(,_hw_mthd_hwa_##f##_##c))(f,c,__VA_ARGS__)
#define __hwa41_1(f,c,...)	HW_A1(_hw_mthd_hwa_##f##_##c)(__VA_ARGS__)
#define __hwa41_0(f,c,o,...)	HW_E_OCM(o,c,hwa_##f)

  

/*  Define wich classes are hardware bits
 */
#define _hw_hasbits__r8
#define _hw_hasbits__r16
#define _hw_hasbits__r32
#define _hw_hasbits__cb1
#define _hw_hasbits__cb2
#define _hw_hasbits__ob1
#define _hw_hasbits__ob2
#define _hw_hasbits__xob1
#define _hw_hasbits__xob2


/**
 * @ingroup public_obj_macros
 * @brief Definition of the register `r` of the object `o`
 * @hideinitializer
 *
 * The word _register_ here stands for "set of bits" that may be sprayed over 2
 * hardware registers.
 *
 * Successful results can be:
 *
 *  * `_m1, o,a, r,rc,ra,rwm,rfm, rbn,rbp`
 *
 *  * `_m2, o,a, r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,
 *               r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2`
 *
 * with:
 *
 *  * '`_m1`': class of one group of consecutive bits in one hardware register
 *
 *  * '`_m2`': class of a set of bits made of two groups of consecutive bits in
 *           one or two hardware registers
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
/* This is a generic instruction that can be applied to every declared instance
 * whatever its class. `HW_GEN` expands the definition of object `o` or
 * produces an error.
 *
 * Errors are processed at last.
 */
/*  FIXME: fails without HW_ERR if p is a _pin1:
 *  	_HW_REG_3(_pin1,hw_pin_pa6,307, hw_porta, 1, 6,port)
 *  -> Should HW_REG() be a method?
 */

#define HW_REGISTER(o,x)		_HW_REG2(o,x)
#define _HW_REG2(...)			_HW_GEN(_HW_REG3,__VA_ARGS__)
#define _HW_REG3(c,o,i,a,r)		_HW_REG4(_hw_##c##_##r,o,c,a,r)
#define _HW_REG4(...)			_HW_REG5(__VA_ARGS__)
#define _HW_REG5(t,...)			HW_G2(_HW_REG5, HW_IS(,_hw_hasbits_##t))(t,__VA_ARGS__)
#define _HW_REG5_1(t,...)		_hw_r2m_##t(__VA_ARGS__)
#define _HW_REG5_0(t,o,c,a,r)		_HW_REG6(_##o##_##r,o,c,a,r)
#define _HW_REG6(...)			_HW_REG7(__VA_ARGS__)
#define _HW_REG7(t,...)			HW_G2(_HW_REG7, HW_IS(,_hw_hasbits_##t))(t,__VA_ARGS__)
#define _HW_REG7_1(t,...)		_hw_r2m_##t(__VA_ARGS__)
#define _HW_REG7_0(t,o,c,a,r)		HW_E(`o` has no register `r`)


/**
 * @ingroup private
 * @brief Memory definition of a register (internal use, no error checking)
 * @hideinitializer
 */
#define _HW_REGISTER(o,r)		_hw__reg_2(o,_hw_obj_##o,r)
#define _HW_REG(o,r)			_hw__reg_2(o,_hw_obj_##o,r)
#define _hw__reg_2(...)			_hw__reg_3(__VA_ARGS__)
#define _hw__reg_3(o,c,i,a,r)		_hw__reg_4(_hw_##c##_##r,o,c,a,r)
#define _hw__reg_4(...)			_hw__reg_5(__VA_ARGS__)
#define _hw__reg_5(t,...)		HW_G2(_hw__reg, HW_IS(,_hw_hasbits_##t))(t,__VA_ARGS__)
#define _hw__reg_1(t,...)		_hw_r2m_##t(__VA_ARGS__)
#define _hw__reg_0(t,o,c,a,r)		_hw__reg_6(_##o##_##r,o,c,a,r)
#define _hw__reg_6(...)			_hw__reg_1(__VA_ARGS__)


/*  Convert a register definition to a memory definition of class _m1 or _m2
 *	-> _m1, o,a, r,rc,ra,rwm,rfm, bn,bp
 *	-> _m2, o,a, r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,
 *	             r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2
 */
#define _hw_r2m__r8(ra,rwm,rfm, o,c,a,r)		_m1, o,a, r, _r8, ra,rwm,rfm,  8,0
#define _hw_r2m__r16(ra,rwm,rfm, o,c,a,r)		_m1, o,a, r,_r16, ra,rwm,rfm, 16,0
#define _hw_r2m__r32(ra,rwm,rfm, o,c,a,r)		_m1, o,a, r,_r32, ra,rwm,rfm, 32,0

#define _hw_r2m__ob1(r,bn,bp, o,c,a,m)		_HW_SPEC(_hw_r2m_ob1, _##o##_##r,bn,bp,o,r)
#define _hw_r2m_ob1__r8(ra,rwm,rfm,bn,bp,o,r) 		_m1, o,0, r,_r8,ra,rwm,rfm, bn,bp

#define _hw_r2m__ob2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, o,c,a,m)	\
  _hw_r2m_cb2_2( r1,_##o##_##r1,rbn1,rbp1,vbp1,				\
		 r2,_##o##_##r2,rbn2,rbp2,vbp2, o,c,a,m)


#define _hw_r2m__xob1(to,tr,bn,bp, o,c,a,m)	_HW_SPEC(_hw_r2m_xob1, _##to##_##tr,bn,bp,to,tr)
#define _hw_r2m_xob1__r8(ra,rwm,rfm, bn,bp,o,r) 	_m1, o,0, r,_r8,ra,rwm,rfm, bn,bp
#define _hw_r2m_xob1__r32(ra,rwm,rfm, bn,bp,o,r) 	_m1, o,0, r,_r32,ra,rwm,rfm, bn,bp

#define _hw_r2m__xob2(xo, r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, o,c,a,m) \
  _hw_r2m_cb2_2( r1,_##xo##_##r1,rbn1,rbp1,vbp1,			\
		 r2,_##xo##_##r2,rbn2,rbp2,vbp2, xo,c,a,m )

#define _hw_r2m__cb1(r,bn,bp, o,c,a,m)		_HW_SPEC(_hw_r2m_cb1, _hw_##c##_##r,bn,bp,o,r,a)
#define _hw_r2m_cb1__r8(ra,rwm,rfm,bn,bp,o,r,a) 	_m1, o,a, r,_r8,ra,rwm,rfm, bn,bp
#define _hw_r2m_cb1__r16(ra,rwm,rfm,bn,bp,o,r,a) 	_m1, o,a, r,_r16,ra,rwm,rfm, bn,bp
#define _hw_r2m_cb1__r32(ra,rwm,rfm,bn,bp,o,r,a) 	_m1, o,a, r,_r32,ra,rwm,rfm, bn,bp

#define _hw_r2m__cb2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, o,c,a,m)	\
  _hw_r2m_cb2_2( r1,_hw_##c##_##r1,rbn1,rbp1,vbp1,			\
		 r2,_hw_##c##_##r2,rbn2,rbp2,vbp2, o,c,a,m)
#define _hw_r2m_cb2_2(...)		_hw_r2m_cb2_3(__VA_ARGS__)
#define _hw_r2m_cb2_3( r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
		       r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2, o,c,a,m )	\
  _m2, o,a,								\
    r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,				\
    r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2

/*  Remplacement pour _hw_r2m(...)
 *
 *  Le nom du registre tel que demandé apparaît en 2e position, utile pour les
 *  messages d'erreurs.
 *
 *    o,c  ->  c,o
 *    _m1,o,a,r  ->  _m1,r,o,a
 *    _m2,o,a    ->  _m2,r,o,a
 */
/* #define _hw_r3m__r8(ra,rwm,rfm, c,o,a,r)		_m1,r,o,a,r, _r8, ra,rwm,rfm,  8,0 */
/* #define _hw_r3m__r16(ra,rwm,rfm, c,o,a,r)		_m1,r,o,a,r,_r16, ra,rwm,rfm, 16,0 */
/* #define _hw_r3m__r32(ra,rwm,rfm, c,o,a,r)		_m1,r,o,a,r,_r32, ra,rwm,rfm, 32,0 */
/* #define _hw_r3m__ob1(tr,bn,bp, c,o,a,r)			_m1,r,o,0,tr,_##o##_##tr,bn,bp */
/* #define _hw_r3m__cb1(tr,bn,bp, c,o,a,r)			_m1,r,o,a,tr,_hw_##c##_##tr,bn,bp */
/* #define _hw_r3m__xob1(to,tr,bn,bp, c,o,a,r)		_m1,r,o,0,tr,_##to##_##tr,bn,bp */

/* #define _hw_r3m__ob2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, c,o,a,r)	\ */
/*   _m2,r,o,a, r1,_##o##_##r1,rbn1,rbp1,vbp1, r2,_##o##_##r2,rbn2,rbp2,vbp2 */

/* #define _hw_r3m__cb2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, c,o,a,r)	\ */
/*   _m2,r,o,a, r1,_hw_##c##_##r1,rbn1,rbp1,vbp1, r2,_hw_##c##_##r2,rbn2,rbp2,vbp2 */

/* #define _hw_r3m__xob2(to, r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, c,o,a,r) \ */
/*   _m2,r,xo,a, r1,_##to##_##r1,rbn1,rbp1,vbp1, r2,_##to##_##r2,rbn2,rbp2,vbp2 */


/**
 * @ingroup private
 * @brief Definition of class or object `o` hardware register `r`
 * @hideinitializer
 */
#define _hw_hreg(o,r)			__hw_hreg_2(o,_hw_obj_##o,r)
#define __hw_hreg_2(...)		__hw_hreg_3(__VA_ARGS__)
#define __hw_hreg_3(o,c,i,a,r)		__hw_hreg_4(_hw_##c##_##r,o,c,a,r)
#define __hw_hreg_4(...)		__hw_hreg_5(__VA_ARGS__)
#define __hw_hreg_5(t,...)		HW_G2(__hw_hreg, HW_IS(,_hw_hasbits_##t))(t,__VA_ARGS__)
#define __hw_hreg_1(t,...)		t, __VA_ARGS__
#define __hw_hreg_0(t,o,c,a,r)		__hw_hreg_6(_##o##_##r,o,c,a,r)
#define __hw_hreg_6(...)		__VA_ARGS__


/**
 * @ingroup public_obj_macros
 * @brief Address of object `o`.
 * @hideinitializer
 */
/*  The argument can be an object definition
 */
#define HW_ADDRESS(...)			HW_MTHD(HW_ADDRESS, __VA_ARGS__,)


/* This is defined in the vendor-specific file since the address can be
 * different between C and assembler.
 */
#define _hw_mthd_hw_addr__m1		, _hw_addr__m1
#define _hw_mthd_HW_ADDRESS__m1		, _hw_addr__m1


/**
 * @ingroup private
 * @brief  Address of an object's register (internal use)
 * @hideinitializer
 */
#define _hw_ra(o,r)			_HW_SPEC(_hw__ra, _HW_REG(o,r))


/**
 * @ingroup public_obj_macros
 * @brief Address and position of the least significant bit of the object `o`.
 * @hideinitializer
 *
 * This is most useful in assembler programming.
 */
#define hw_ap(o)			HW_MTHD(hw_ap, o,)

#define _hw_mthd_hw_ap__m1		, _hw_ap__m1
#define _hw_ap__m1(...)			_hw_addr__m1(__VA_ARGS__), _hw_bp__m1(__VA_ARGS__)


/**
 * @ingroup private
 * @brief Address and position of the least significant bit of the register `r` of object `o`.
 * @hideinitializer
 */
/* #define _hw_rap(o,r)			_HW_SPEC(_hw__rap, _HW_REG(o,r)) */

/* #define _hw_mthd_hw__rap__m1		, _hw__rap__m1 */
/* #define _hw__rap__m1(...)		_hw_addr__m1(__VA_ARGS__,), _hw_bp__m1(__VA_ARGS__,) */


/**
 * @ingroup public_obj_macros
 * @brief Number of bits of object `o`.
 * @hideinitializer
 */
/*  The argument can be an object definition
 */
#define HW_BITS(...)			HW_MTHD(hw_bn, __VA_ARGS__,)

#define _hw_mthd_hw_bn__m1		, _hw_bn__m1

#define _hw_bn__m1(o,a, r,rw,ra,rwm,rfm, bn,bp)	bn


//#define _HW_BITS(o)			_HW_MTHD(hw_bn, o,)


/**
 * @ingroup private
 * @brief Number of bits of the register `r` of object `o`.
 * @hideinitializer
 */
#define _hw_rbn(o,r)					_HW_SPEC(_hw_rbn,_HW_REG(o,r))
#define _hw_rbn__m1(o,a, r,rc,ra,rwm,rfm, bn,bp)	bn


/**
 * @ingroup public_obj_macros
 * @brief Position of least significant bit of object `o`.
 * @hideinitializer
 */
/*  The argument can be an object definition
 */
#define HW_POSITION(...)				HW_MTHD(hw_bp, __VA_ARGS__,)

#define _hw_mthd_hw_bp__m1				, _hw_bp__m1

#define _hw_bp__m1(o,a, r,rw,ra,rwm,rfm, bn,bp,...)	bp


/**
 * @ingroup private
 * @brief Position of the least significant bit of the register `r` of object `o`.
 * @hideinitializer
 */
#define _hw_rbp(o,r)					_HW_SPEC(_hw_rbp,_HW_REG(o,r))
#define _hw_rbp__m1(o,a, r,rc,ra,rwm,rfm, bn,bp)	bp


/**
 * @ingroup public_obj_macros
 * @brief Unsigned integer type of `bn` bits.
 * @hideinitializer
 *
 * `hw_uint_t(8)` expands to `uint8_t`, `hw_uint_t(16)` expands to `uint16_t`, etc.
 */
#define hw_uint_t(bn)					_hw_uintt0(bn)
#define _hw_uintt0(bn)					HW_G2(_hw_uintt1,HW_IS(8,bn##_))(bn)
#define _hw_uintt1_1(bn)				uint8_t
#define _hw_uintt1_0(bn)				HW_G2(_hw_uintt2,HW_IS(16,bn##_))(bn)
#define _hw_uintt2_1(bn)				uint16_t
#define _hw_uintt2_0(bn)				HW_E_VL(bn,8|16) uint8_t

#define _hw_is_8_8_			, 1
#define _hw_is_16_16_			, 1

/**
 * @ingroup private
 * @brief Class of the register `r` of object `o`.
 * @hideinitializer
 */
#define _hw_rc(o,r)					_HW_SPEC(_hw_rc,_HW_REG(o,r))
#define _hw_rc__m1(o,a,r,rc,ra,rwm,rfm,bn,bp)		rc


/**
 * @ingroup public_obj_macros
 * @brief ID of object `o`. 0 if the object does not exist.
 * @hideinitializer
 */
#define HW_ID(o)			HW_G2(_HW_ID,HW_ISON(o))(o)
#define _HW_ID_1(o)			HW_A1(_hw_obj_##o)
#define _HW_ID_0(o)			0


/**
 * @ingroup public_obj_macros
 * @brief Name of the relative object `x` of object `o`.
 * @hideinitializer
 *
 * This is used for example to get the prescaler name of a counter, the output
 * pin name of a compare unit, etc.
 */
#define HW_RELATIVE(o,x)		_HW_REL1(o,x)
#define HW_REL(o,x)			_HW_REL1(o,x)
#define _HW_REL1(...)			_HW_REL2(__VA_ARGS__)
#define _HW_REL2(o,x)			HW_G2(_HW_REL2,HW_IS(,o))(o,x)
#define _HW_REL2_1(o,x)			HW_E_OM()
#define _HW_REL2_0(o,x)			HW_G2(_HW_REL3,HW_ISON(o))(o,x)
#define _HW_REL3_0(o,x)			HW_E_O(o)
#define _HW_REL3_1(o,x)			HW_G2(_HW_REL4,HW_ISON(o##x))(o,x)
#define _HW_REL4_1(o,x)			o##x

/*  Look for a class-defined HW_REL() method
 */
#define _HW_REL4_0(o,x)			_HW_REL4(o,x,_hw_obj_##o)
#define _HW_REL4(...)			_HW_REL5(__VA_ARGS__)
#define _HW_REL5(o,x,c,...)		HW_G2(_HW_REL5,HW_IS(,_hw_class_##c))(o,x,c,__VA_ARGS__)
#define _HW_REL5_0(o,x,...)		HW_E_OO(o,x)
#define _HW_REL5_1(o,x,c,...)		HW_G2(_HW_REL6, HW_IS(,_hw_mthd_HW_REL_##c))(o,x,c,__VA_ARGS__)
#define _HW_REL6_0(o,x,...)		HW_E_OO(o,x)
#define _HW_REL6_1(o,x,c,...)		HW_A1(_hw_mthd_HW_REL_##c)(o,x,__VA_ARGS__)


/**
 * @ingroup private_obj_macros
 * @brief Name of the relative `x` of object `o`.
 * @hideinitializer
 *
 * The public version of `HW_REL()` fails if one of the arguments is the result
 * of a `HW_REL()`. This private version should be used instead in HWA code.
 */
#define _HW_RELATIVE(o,x)		__HW_REL2(o,x)
#define _HW_REL(o,x)			__HW_REL2(o,x)
#define __HW_REL2(o,x)			o##x
