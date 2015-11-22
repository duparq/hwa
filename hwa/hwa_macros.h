
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
 *  or class name.
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


#define _hw_is_hw_error_hw_error	, 1, /* one more comma to remove '; StaticAssert(...)' */


#if defined __ASSEMBLER__
/*
 *  Assembler .error directive can not appear in operand position.
 *  So, emit a hw_error(...) that will be catched by the building process.
 */
#  define HW_ERR(msg)		hw_error(__FILE__,__LINE__,"HWA: " msg)
#  define HW_ERRFN(...)		.error __VA_ARGS__

#else

/**
 * @ingroup public_gen_macros
 * @brief Emit an error at preprocessing stage
 * @hideinitializer
 */
/*  avr-gcc ignores the GCC error pragma
 */
#  define HW_ERR(msg)		hw_error++; _Static_assert(0, "HWA: " msg);

/*  Avoid the emitting of an additionnal warning when HW_ERR is emittied.
 */
extern char hw_error ;

/**
 * @ingroup public_gen_macros
 * @brief Emit an error at preprocessing stage (when not inside a function)
 *
 * Encapsulate the error into a fake function.
 *
 * @hideinitializer
 */
#define HW_ERROR(...)		_HW_ERROR_2(__COUNTER__, __VA_ARGS__)
#define _HW_ERROR_2(...)	_HW_ERROR_3(__VA_ARGS__)
#define _HW_ERROR_3(n,...)	void hw_err_##n() { _Static_assert(0, "HWA: " #__VA_ARGS__) ; }

#endif


/*  Propagate error or continue: expand to x if x is an error,
 *  otherwise expand to y.
 */
#define HW_PE(...)		_HW_PE_2(__VA_ARGS__)
#define _HW_PE_2(x, y)		HW_G2(_HW_PE,HW_IS(hw_error,x))(x, y)
#define _HW_PE_0(x, y)		y
#define _HW_PE_1(x, y)		x


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
#define _HW_MTHD1(f,o,...)	_HW_MTHD2(f,o,_##o,__VA_ARGS__)
#define _HW_MTHD2(...)		_HW_MTHD3(__VA_ARGS__)

/*  Is there a method f for object o of class c?
 */
#define _HW_MTHD3(f,o,c,...)	HW_G2(_HW_MTHD4, HW_IS(,_hw_mthd_##f##_##c))(f,o,c,__VA_ARGS__)
#define _HW_MTHD4_1(f,o,c,...)	HW_A1(_hw_mthd_##f##_##c)(o,__VA_ARGS__)

/* No method f for object o of class c. Is o an object?
 */
#define _HW_MTHD4_0(f,o,c,...)	HW_G2(_HW_MTHD5, HW_IS(,_hw_class_##c))(f,o,c,__VA_ARGS__)
#define _HW_MTHD5_1(f,o,c,...)	HW_ERR("object `"#o"` of class `"#c"` has no method `"#f"`.")

/* o is not an object. Is it a class name?
 */
#define _HW_MTHD5_0(f,o,...)	HW_G2(_HW_MTHD6,HW_IS(,_hw_class_##o))(f,o,__VA_ARGS__)

/* Is there a method f for class c?
 */
#define _HW_MTHD6_1(f,o,oo,...)	HW_G2(_HW_MTHD8, HW_IS(,_hw_mthd_##f##_##o))(f,o,__VA_ARGS__)
#define _HW_MTHD8_0(f,c,...)	HW_ERR("class `"#c"` has no method `"#f"`.")
#define _HW_MTHD8_1(f,c,...)	HW_A1(_hw_mthd_##f##_##c)(__VA_ARGS__)

/* o is not an object and not a class name. Propagate or trigger an error.
 */
#define _HW_MTHD6_0(f,o,...)	HW_PE(o, HW_ERR("`"#o"` is not a HWA object."))


/**
 */
#define _HW_MTHD(...)		__HW_MTHD1(__VA_ARGS__)
#define __HW_MTHD1(f,o,...)	__HW_MTHD2(f,o,_##o,__VA_ARGS__)
#define __HW_MTHD2(...)		__HW_MTHD3(__VA_ARGS__)
#define __HW_MTHD3(f,o,c,...)	HW_A1(_hw_mthd_##f##_##c)(o,__VA_ARGS__)



/**
 * @brief Specialize instruction `f` for class `c`: _HW_SPEC(f,t,...) -> f_c(...)
 *
 *  Arguments must start with a class name that is to be appended to the
 *  function name.
 */
#define _HW_SPEC(...)		_HW_SPEC_2(__VA_ARGS__)
#define _HW_SPEC_2(f,c,...)	f##_##c(__VA_ARGS__)


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
#define HW_GNRC(f,o,...)	_HW_GNRC_2(f,o,_##o,__VA_ARGS__)
#define _HW_GNRC_2(...)		_HW_GNRC_3(__VA_ARGS__)
#define _HW_GNRC_3(f,o,c,...)	HW_G2(_HW_GNRC,HW_IS(,_hw_class_##c))(f,o,c,__VA_ARGS__)
#define _HW_GNRC_1(f,o,c,...)	f(c,o,__VA_ARGS__)
#define _HW_GNRC_0(f,o,...)	HW_PE(o, HW_ERR("`"#o"` is not a HWA object."))


/**
 * @ingroup public_gen_macros
 * @brief `1` if the first element is the name of a HWA object, `0` if not.
 * @hideinitializer
 */
#define HW_ISOBJ(...)		_HW_ISOBJ_2(__VA_ARGS__)
#define _HW_ISOBJ_2(...)	HW_IS(,HW_G2(_hw_class,_##__VA_ARGS__))


/**
 * @brief `result` if the next element is void, an error otherwise.
 * @hideinitializer
 *
 * This is used to help detecting and propagating errors, or ensuring that
 * there is no remaining elements in a list at the end of its parsing.
 */
#define HW_TX(result, ...)	HW_G2(_HW_TX,HW_IS(,__VA_ARGS__))((result),__VA_ARGS__)
#define _HW_TX_0(result, ...)	HW_ERR("garbage found: `" HW_QUOTE(__VA_ARGS__) "`.");
#define _HW_TX_1(result, ...)	_HW_TX_2 result
#define _HW_TX_2(...)		__VA_ARGS__


/**
 * @brief Trigger an error if the first argument is not void.
 * @hideinitializer
 *
 * This is used to ensure that there is no remaining elements in a list at the
 * end of its parsing.
 */
#define HW_EOL(...)		HW_G2(_HW_EOL,HW_IS(,__VA_ARGS__))(__VA_ARGS__)
#define _HW_EOL_0(...)		HW_ERR("garbage found: `" HW_QUOTE(__VA_ARGS__) "`.");
#define _HW_EOL_1(...)


/**
 * @ingroup public_gen_macros
 * @brief Build a C string from the first element in the list
 * @hideinitializer
 */
#define HW_QUOTE(...)		_HW_QUOTE_2(__VA_ARGS__,)
#define _HW_QUOTE_2(x,...)	#x


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
 * whatever its class. `HW_GNRC` expands the definition of object `o` or
 * produces an error.
 *
 * Errors are processed at last.
 */
/*  FIXME: fails without HW_ERR if p is a _pin1:
 *  	_hw_reg_3(_pin1,hw_pin_pa6,307, hw_porta, 1, 6,port)
 *  -> Should hw_reg() be a method?
 */
#define hw_reg(o,r)			HW_GNRC(_hw_reg_3,o,r)
//#define _hw_reg_2(...)			_hw_reg_3(__VA_ARGS__)
#define _hw_reg_3(c,o,i,a,r)		_hw_reg_4(_hw_##c##_##r,o,c,a,r)
#define _hw_reg_4(...)			_hw_reg_5(__VA_ARGS__)
#define _hw_reg_5(t,...)		HW_G2(_hw_reg, HW_IS(,_hw_hasbits_##t))(t,__VA_ARGS__)
#define _hw_reg_1(t,...)		_hw_x_##t(__VA_ARGS__)
#define _hw_reg_0(t,o,c,a,r)		_hw_reg_6(_##o##_##r,o,c,a,r)
#define _hw_reg_6(...)			_hw_reg_7(__VA_ARGS__)
#define _hw_reg_7(t,...)		HW_G2(_hw_reg_7, HW_IS(,_hw_hasbits_##t))(t,__VA_ARGS__)
#define _hw_reg_7_1(t,...)		_hw_x_##t(__VA_ARGS__)
#define _hw_reg_7_0(t,o,c,a,r)		HW_PE(o, HW_ERR("`"#o"` has no attribute `"#r"`."))


/**
 * @ingroup private
 * @brief Memory definition of a register (internal use, no error checking)
 * @hideinitializer
 */
#define _hw_reg(o,r)			_hw__reg_2(o,_##o,r)
#define _hw__reg_2(...)			_hw__reg_3(__VA_ARGS__)
#define _hw__reg_3(o,c,i,a,r)		_hw__reg_4(_hw_##c##_##r,o,c,a,r)
#define _hw__reg_4(...)			_hw__reg_5(__VA_ARGS__)
#define _hw__reg_5(t,...)		HW_G2(_hw__reg, HW_IS(,_hw_hasbits_##t))(t,__VA_ARGS__)
#define _hw__reg_1(t,...)		_hw_x_##t(__VA_ARGS__)
#define _hw__reg_0(t,o,c,a,r)		_hw__reg_6(_##o##_##r,o,c,a,r)
#define _hw__reg_6(...)			_hw__reg_1(__VA_ARGS__)


/* /\** */
/*  * @ingroup private */
/*  * @brief Memory definition of register `r` of the object of class `c` pointed by */
/*  * `p`. */
/*  * */
/*  * @hideinitializer */
/*  *\/ */
/* #define _hw_reg_p(o,c,r)		_hw_reg_p_4(_hw_##c##_##m,o,c,r) */
/* #define _hw_reg_p_4(...)		_hw_reg_p_5(__VA_ARGS__) */
/* #define _hw_reg_p_5(t,...)		_hw_xp_##t(__VA_ARGS__) */


/**
 * @ingroup private
 * @brief Definition of class or object `o` hardware register `r`
 * @hideinitializer
 */
#define _hw_hreg(o,r)			_hw__hreg_2(o,_##o,r)
#define _hw__hreg_2(...)		_hw__hreg_3(__VA_ARGS__)
#define _hw__hreg_3(o,c,i,a,r)		_hw__hreg_4(_hw_##c##_##r,o,c,a,r)
#define _hw__hreg_4(...)		_hw__hreg_5(__VA_ARGS__)
#define _hw__hreg_5(t,...)		HW_G2(_hw__hreg, HW_IS(,_hw_hasbits_##t))(t,__VA_ARGS__)
#define _hw__hreg_1(t,...)		t, __VA_ARGS__
#define _hw__hreg_0(t,o,c,a,r)		_hw__hreg_6(_##o##_##r,o,c,a,r)
#define _hw__hreg_6(...)		__VA_ARGS__


/*  Memory definition of a hardware register
 *	-> _m1, o,a, r,rc,ra,rwm,rfm, bn,bp
 */
#define _hw_x__r8(ra,rwm,rfm, o,c,a,r)	_m1, o,a, r, _r8, ra,rwm,rfm,  8,0
#define _hw_x__r16(ra,rwm,rfm, o,c,a,r)	_m1, o,a, r,_r16, ra,rwm,rfm, 16,0
#define _hw_x__r32(ra,rwm,rfm, o,c,a,r)	_m1, o,a, r,_r32, ra,rwm,rfm, 32,0


/*  Memory definition of one group of consecutive bits in one class or object
 *  hardware register
 *
 *	-> _m1, o,a, r,rc,ra,rwm,rfm, bn,bp
 */
//#define _hw_x__xb1(r,bn,bp, o,c,a,m)		_HW_SPEC(_hw_xxb1, _hw_##c##_##r,bn,bp,o,r)


/*  Memory definition of a group of consecutive bits in one class register
 *	-> _m1, o,a, r,rc,ra,rwm,rfm, bn,bp
 */
#define _hw_x__cb1(r,bn,bp, o,c,a,m)		_HW_SPEC(_hw_xcb1, _hw_##c##_##r,bn,bp,o,r)
#define _hw_xcb1__r8(ra,rwm,rfm,bn,bp,o,r) 	_m1, o,0, r,_r8,ra,rwm,rfm, bn,bp
#define _hw_xcb1__r16(ra,rwm,rfm,bn,bp,o,r) 	_m1, o,0, r,_r16,ra,rwm,rfm, bn,bp
#define _hw_xcb1__r32(ra,rwm,rfm,bn,bp,o,r) 	_m1, o,0, r,_r32,ra,rwm,rfm, bn,bp


/*  Memory definition of two groups of consecutive bits in one or two class
 *  registers
 *	-> _m2, o,a, r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,
 *	             r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2
 */
#define _hw_x__cb2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, o,c,a,m)	\
  _hw_xcb2_2( r1,_hw_##c##_##r1,rbn1,rbp1,vbp1,				\
	      r2,_hw_##c##_##r2,rbn2,rbp2,vbp2, o,c,a,m)
#define _hw_xcb2_2(...)		_hw_xcb2_3(__VA_ARGS__)
#define _hw_xcb2_3( r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
		    r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2, o,c,a,m )	\
  _m2, o,a,								\
    r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,				\
    r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2


/*  Memory definition of a group of consecutive bits in one object register
 *	-> _m1, o,a, r,rc,ra,rwm,rfm, bn,bp
 */
#define _hw_x__ob1(r,bn,bp, o,c,a,m)		_HW_SPEC(_hw_xob1, _##o##_##r,bn,bp,o,r)
/* #define _hw_x__ob1(r,bn,bp, o,c,a,m)		_hw_xob1_2(_##o##_##r,bn,bp,o,r) */
/* #define _hw_xob1_2(...)				_hw_xob1_3(__VA_ARGS__) */
/* #define _hw_xob1_3(t,...)			_hw_xob1_##t(__VA_ARGS__) */

#define _hw_xob1__r8(ra,rwm,rfm,bn,bp,o,r) 	_m1, o,0, r,_r8,ra,rwm,rfm, bn,bp

/*  Memory definition of two groups of consecutive bits in one or two object
 *  registers
 *	-> _m2, o,a, r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,
 *	             r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2
 */
//_hw_x__ob2(ccra, 2, 0, 0, ccrb, 1, 3, 2,hw_counter0,_c8c,0,wgm);
#define _hw_x__ob2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, o,c,a,m)	\
  _hw_xcb2_2( r1,_##o##_##r1,rbn1,rbp1,vbp1,				\
	      r2,_##o##_##r2,rbn2,rbp2,vbp2, o,c,a,m)


/**
 * @brief Expand the memory definition of one group of consecutive bits to be
 * found in a another object `to` hardware register `tr`.
 */
/*  NOTE: we do not get the address of `to` and consider it is 0.
 */
#define _hw_x__xob1(to,tr,bn,bp, o,c,a,m)	_HW_SPEC(_hw_xxob1, _##to##_##tr,bn,bp,to,tr)
#define _hw_xxob1__r8(ra,rwm,rfm, bn,bp,o,r) 	_m1, o,0, r,_r8,ra,rwm,rfm, bn,bp


//_hw_x__xob2(hw_counter0, gtccr, 1, 7, 1, gtccr, 1, 7, 0,hw_psc0,_psca,0,tsmpsr)
#define _hw_x__xob2(xo, r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, o,c,a,m)	\
  _hw_xcb2_2( r1,_##xo##_##r1,rbn1,rbp1,vbp1,				\
	      r2,_##xo##_##r2,rbn2,rbp2,vbp2, xo,c,a,m )


/* /\** */
/*  * @brief Expand the memory definition of one hardware register of another */
/*  * object */
/*  *\/ */
/* #define _hw_xp__r8(ra,rwm,rfm, o,c,r)		_m1_p, &o->r,_r8,rwm,rfm,8,0 */
/* #define _hw_xp__r16(ra,rwm,rfm, o,c,r)		_m1_p, &o->r,_r16,rwm,rfm,16,0 */


/* /\** */
/*  * @brief Expand the memory definition of one group of consecutive bits to be */
/*  * found in a another object `o` hardware register `r` pointed by `p` */
/*  *\/ */
/* #define _hw_xp__xob1(o,r,bn,bp, p,c,m)		_HW_SPEC(_hw_xpob1, _##o##_##r,bn,bp,&hwa->o.r) */
/* #define _hw_xpob1__r8(ra,rwm,rfm, bn,bp,p)	_m1_p, o,_r8,rwm,rfm,bn,bp */

/* /\** */
/*  * @brief Expand the memory definition of one group of consecutive bits in the */
/*  * object pointed by `p` */
/*  *\/ */
/* #define _hw_xp__cb1(r,bn,bp, o,c,m)		_HW_SPEC(_hw_xpcb1, _hw_##c##_##r,bn,bp,&o->r) */
/* #define _hw_xpcb1__r8(ra,rwm,rfm, bn,bp,o)	_m1_p, o,_r8,rwm,rfm,bn,bp */


/* /\** */
/*  * @brief Expand the memory definition of two groups of consecutive bits in the */
/*  * object pointed by `p` */
/*  *\/ */
/* #define _hw_xp__cb2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, o,c,m)		\ */
/*   _hw_xpcb2_2( &o->r1,_hw_##c##_##r1,rbn1,rbp1,vbp1,			\ */
/* 		&o->r2,_hw_##c##_##r2,rbn2,rbp2,vbp2 ) */
/* #define _hw_xpcb2_2(...)			_hw_xpcb2_3(__VA_ARGS__) */
/* #define _hw_xpcb2_3( p1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\ */
/* 		     p2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2 )		\ */
/*   _m2_p, p1,rc1,rwm1,rfm1,rbn1,rbp1,vbp1, p2,rc2,rwm2,rfm2,rbn2,rbp2,vbp2 */


/*  Memory definition of two groups of consecutive bits in one object register
 *	-> _m2, o,a, r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,
 *	             r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2
 */
#define _hw_x_ob2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, o,c,a,m)	\
  _hw_xcb2_2(r1,_##o##_##r1,rbn1,rbp1,vbp1,				\
	     r2,_##o##_##r2,rbn2,rbp2,vbp2, o,c,a,m)


/**
 * @ingroup public_obj_macros
 * @brief Address of object `o`.
 * @hideinitializer
 */
#define hw_addr(o)			HW_MTHD(hw_addr, o,)

/* This is defined in the vendor-specific file since the address can be
 * different between C and assembler.
 */
#define _hw_mthd_hw_addr__m1		, _hw_addr__m1


/**
 * @ingroup public_obj_macros
 * @brief  Address of the register `r` of object `o`.
 * @hideinitializer
 */
/* This is defined in the vendor-specific file since the address can be
 * different between C and assembler.
 */
//#define hw_ra(o,r)			_HW_SPEC(_hw_ra, hw_reg(o,r))
#define hw_ra(o,r)			_hw_ra_2(hw_reg(o,r))
#define _hw_ra_2(...)			_hw_ra_3(__VA_ARGS__)
#define _hw_ra_3(x,...)			HW_PE(x, _HW_SPEC(_hw_ra, x, __VA_ARGS__))


/**
 * @ingroup private
 * @brief  Address of an object's register (internal use)
 * @hideinitializer
 */
#define _hw_ra(o,r)			_HW_SPEC(_hw__ra, _hw_reg(o,r))


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
#define _hw_rap(o,r)			_HW_SPEC(_hw__rap, _hw_reg(o,r))

#define _hw_mthd_hw__rap__m1		, _hw__rap__m1
#define _hw__rap__m1(...)		_hw_addr__m1(__VA_ARGS__,), _hw_bp__m1(__VA_ARGS__,)


/**
 * @ingroup public_obj_macros
 * @brief Number of bits of object `o`.
 * @hideinitializer
 */
#define hw_bn(o)			HW_MTHD(hw_bn, o,)

#define _hw_mthd_hw_bn__m1		, _hw_bn__m1

#define _hw_bn__m1(o,a, r,rw,ra,rwm,rfm, bn,bp)	bn


#define _hw_bn(o)			_HW_MTHD(hw_bn, o,)


/**
 * @ingroup private
 * @brief Number of bits of the register `r` of object `o`.
 * @hideinitializer
 */
#define _hw_rbn(o,r)					_HW_SPEC(_hw_rbn,_hw_reg(o,r))
#define _hw_rbn__m1(o,a, r,rc,ra,rwm,rfm, bn,bp)	bn


/**
 * @ingroup public_obj_macros
 * @brief Position of least significant bit of object `o`.
 * @hideinitializer
 */
#define hw_bp(o)					HW_MTHD(hw_bp, o,)

#define _hw_mthd_hw_bp__m1				, _hw_bp__m1

#define _hw_bp__m1(o,a, r,rw,ra,rwm,rfm, bn,bp,...)	bp


/**
 * @ingroup private
 * @brief Position of the least significant bit of the register `r` of object `o`.
 * @hideinitializer
 */
#define _hw_rbp(o,r)					_HW_SPEC(_hw_rbp,_hw_reg(o,r))
#define _hw_rbp__m1(o,a, r,rc,ra,rwm,rfm, bn,bp)	bp


/*
 * @ingroup public_obj_macros
 * @brief Integer type of an object's hardware register (`uint8_t`, `uint16_t`...)
 * @hideinitializer
 */
/* #define hw_uint_t(o,r)					_HW_SPEC(_hw_uintt,hw_reg(o,r)) */
/* #define _hw_uintt__m1(o,a,r,rc,ra,rwm,rfm,bn,bp)	uint##bn##_t */

/**
 * @ingroup public_obj_macros
 * @brief Unsigned integer type of `bn` bits.
 * @hideinitializer
 *
 * `hw_uint_t(8)` expands to `uint8_t`, `hw_uint_t(16)` expands to `uint16_t`, etc.
 */
#define hw_uint_t(bn)					HW_G2(_hw_uintt,HW_IS(hw_error,bn))(bn)
#define _hw_uintt_1(...)				__VA_ARGS__
#define _hw_uintt_0(bn)					uint##bn##_t

/**
 * @ingroup private
 * @brief Class of the register `r` of object `o`.
 * @hideinitializer
 */
#define _hw_rc(o,r)					_HW_SPEC(_hw_rc,_hw_reg(o,r))
#define _hw_rc__m1(o,a,r,rc,ra,rwm,rfm,bn,bp)		rc


/**
 * @ingroup public_obj_macros
 * @brief ID of object `o`. 0 if the object does not exist.
 * @hideinitializer
 */
#define hw_id(o)			HW_G2(_hw_id,HW_ISOBJ(o))(o)
#define _hw_id_1(o)			HW_A1(_##o)
#define _hw_id_0(o)			0


/**
 * @ingroup public_obj_macros
 * @brief Name of the relative object `x` of object `o`.
 * @hideinitializer
 *
 * This is used for example to get the prescaler name of a counter, the pin name
 * of a compare unit output, etc.
 */
#define hw_rel(o,x)			_hw_rel_2(o,x)
#define _hw_rel_2(o,x)			HW_G2(_hw_rel,HW_ISOBJ(o##x))(o,x)
#define _hw_rel_1(o,x)			o##x

#define _hw_rel_0(o,x)			HW_PE(o, HW_G2(_hw_rel0,HW_ISOBJ(o))(o,x))
#define _hw_rel0_0(o,x)			HW_ERR("`"#o"` is not a HWA object.")

//#define _hw_rel0_1(o,x)			HW_ERR("`"#o"` has no relative named `"#x"`."))

/*  Look for a class-defined hw_rel() method
 */
#define _hw_rel0_1(o,x)			_hw_rel2(o,x,_##o)
#define _hw_rel2(...)			_hw_rel3(__VA_ARGS__)
#define _hw_rel3(o,x,c,...)		HW_G2(_hw_rel3,HW_IS(,_hw_class_##c))(o,x,c,__VA_ARGS__)
#define _hw_rel3_0(o,x,...)		HW_ERR("`"#o"` has no relative named `"#x"`.")
#define _hw_rel3_1(o,x,c,...)		HW_G2(_hw_rel31, HW_IS(,_hw_mthd_hw_rel_##c))(o,x,c,__VA_ARGS__)
#define _hw_rel31_0(o,x,...)		HW_ERR("`"#o"` has no relative named `"#x"`.")
#define _hw_rel31_1(o,x,c,...)		HW_A1(_hw_mthd_hw_rel_##c)(o,x,__VA_ARGS__)


/**
 * @ingroup private_obj_macros
 * @brief Name of the relative `x` of object `o`.
 * @hideinitializer
 */
#define _hw_rel(o,x)			__hw_rel_2(o,x)
#define __hw_rel_2(o,x)			o##x
