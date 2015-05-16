
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** @file
 *  @brief General purpose macro definitions usable in C or assembler source code.
 *
 *  Upper case definitions process arbitrary lists of arguments.
 *
 *  Lower case definitions deal with lists of arguments starting with an object
 *  or class name.
 */

#define hw_state_on			, 1
#define hw_state_off			, 0
#define hw_state_yes			, 1
#define hw_state_no			, 0
#define hw_state_enabled		, 1
#define hw_state_disabled		, 0

/*  HWA classes
 */
#define _hw_class__crg
#define _hw_class__cb1
#define _hw_class__cb2
#define _hw_class__irq
#define _hw_class__m1
#define _hw_class__m1x
#define _hw_class__m2

#define _hw_is_hw_error_hw_error	, 1, /* one more comma to remove '; StaticAssert(...)' */


#if defined __ASSEMBLER__
/* #  define HW_ERR(msg)		0 ; .fail "HWA: " msg */
/* hw_error = 0 */
#  define HW_ERR(msg)		hw_error ; .fail "HWA: " msg
#  define HW_ERRFN(...)		.fail __VA_ARGS__
#else
/*
 *  avr-gcc ignores the GCC error pragma
 */
extern char hw_error ;
#  define HW_ERR(msg)		hw_error ; _Static_assert(0, "HWA: " msg)

/*	Encapsulate the result of HW_ERR inside a fake function numberred
 */
#define HW_ERRFN(...)		_HW_ERRFN_2(__COUNTER__, __VA_ARGS__)
#define _HW_ERRFN_2(...)		_HW_ERRFN_3(__VA_ARGS__)
#define _HW_ERRFN_3(n,...)	void hw_err##n() { uint8_t x = __VA_ARGS__ ; } void hw_err##n##_()

#endif


/*  Propagate error or continue: expand to x if x is an error,
 *  otherwise expand to y.
 */
#define HW_PE(...)		_HW_PE_2(__VA_ARGS__)
#define _HW_PE_2(x, y)		HW_G2(_HW_PE,HW_IS(hw_error,x))(x, y)
#define _HW_PE_0(x, y)		y
#define _HW_PE_1(x, y)		x


/*  If x is an error, expand it. Otherwize expand 
 *  otherwise expand to y.
 */
/* #define HW_PEOC(...)		_HW_PEOC_2(__VA_ARGS__) */
/* #define _HW_PEOC_2(x,...)	HW_G2(_HW_PEOC,HW_IS(hw_error,x))(x,__VA_ARGS__) */
/* #define _HW_PEOC_1(x,...)	x */
/* #define _HW_PEOC_0(x,...)	x,__VA_ARGS__ */


/** \brief	Element a0 of the list a0,...
 *  @hideinitializer
 */
#define HW_A0(...)		_HW_A0_2(__VA_ARGS__,)
#define _HW_A0_2(a0,...)	a0


/** \brief	Element a1 of the list a0,a1,...
 *  @hideinitializer
 */
#define HW_A1(...)		_HW_A1_2(__VA_ARGS__,,)
#define _HW_A1_2(a0,a1,...)	a1


/** \brief	Element a2 of the list a0,a1,a2,...
 *  @hideinitializer
 */
#define HW_A2(...)		_HW_A2_2(__VA_ARGS__,,,)
#define _HW_A2_2(a0,a1,a2,...)	a2

/* #define HW_A3(...)		_HW_A3_2(__VA_ARGS__,,,,) */
/* #define _HW_A3_2(a0,a1,a2,a3,...)	a3 */


/** \brief	Glue the first two arguments
 *  @hideinitializer
 */
#define HW_G2(...)		_HW_G2_(__VA_ARGS__,,)
#define _HW_G2_(a,b,...)	a##_##b


/** \brief	Glue the first three arguments
 *  @hideinitializer
 */
#define HW_G3(...)		_HW_G3_(__VA_ARGS__,,,)
#define _HW_G3_(a,b,c,...)	a##_##b##_##c


/*	1 if the 2nd argument of _hw_is_x_y is 1, 0 if not
 */
#define HW_IS(...)		_HW_IS_2(__VA_ARGS__,,)
#define _HW_IS_2(x,y,...)	HW_A1(_hw_is_##x##_##y,0)
//#define _hw_is_0_0			, 1,	/* one more comma to remove '; StaticAssert(...)' */
#define _hw_is_0_0			, 1
#define _hw_is__			, 1
#define _hw_is_enabled_enabled		, 1
#define _hw_is_disabled_disabled	, 1
#define _hw_is_yes_yes			, 1
#define _hw_is_no_no			, 1
#define _hw_is_off_off			, 1


/*
 * @brief `HW_MTHD(f,p,...)` applies member instruction `f` to object `p`
 * @hideinitializer
 *
 *  Arguments must start with the name of an object, or the the name of a class
 *  starting the definition of an object (as returned by instructions such as
 *  `hw_sup(...)`.
 *
 *  If `p` is an object of class `c` that has a method `f`,
 *  `_hw_mthd_##f##_##c` is defined as '`, fi`' where `fi` is the implementation of
 *  `f` for class `c`. Then, `HW_MTHD(f,p,...)` expands to `fi( p, i, a, ...)`.
 *
 *  If `HW_A0(_hw_mthd_##f##_##c)` is not ``, there is no method f for class c. Then try
 *  to determine the reason:
 *
 *    * p is not a HWA object
 *    * c has no method f
 *    * p is an error
 *
 *  Note: an extra void argument must be added for single argument instructions
 *  in order to avoid a compiler warning.
 */

/*  HW_MTHD(f, ...)	Apply method f to arguments
 *
 *  Arguments must start with the name of an object, or the definition of an
 *  object starting with its class (as returned by instructions such as
 *  hw_sup(...).
 *
 *  If a class c of an object p has a method f, _hw_mthd_f_c is defined as `, fm`
 *  where fm is the definition of f. fm is called with the definition of p after
 *  having replaced the p's class name with the p's name.
 *
 *  If HW_A0(_hw_mthd_f_c) is not ``, there is no method f for class c. Then try
 *  to determine the reason:
 *
 *    * p is not a HWA object
 *    * c has no method f
 *    * p is an error
 *
 *  Note: an extra void argument must be added for single argument instructions
 *  in order to avoid a warning at compilation.
 */
#if 1

/* Assume the argument is the name of an object, expand its definition to get its class */
#define HW_MTHD(...)		_HW_MTHD1(__VA_ARGS__)
#define _HW_MTHD1(f,p,...)	_HW_MTHD2(f,p,_##p,__VA_ARGS__) /* FIXME: this can append a void argument to the list. May be it should be appended above so that there is always this last void argument? */
//#define _HW_MTHD1(f,...)	_HW_MTHD2(f,HW_A0(__VA_ARGS),_##__VA_ARGS__,__VA_ARGS__)
#define _HW_MTHD2(...)		_HW_MTHD3(__VA_ARGS__)

/* Is there a method f for assumed object p of class c? */
// MCUSR = x_HW_MTHD4_0(_hw_addr,_m1,_hw__m1,core0,0, mcusr,8,0x54,0x0F,0x00, 8,0)
#define _HW_MTHD3(f,p,c,...)	HW_G2(_HW_MTHD4, HW_IS(,_hw_mthd_##f##_##c))(f,p,c,__VA_ARGS__)
#define _HW_MTHD4_1(f,p,c,...)	HW_A1(_hw_mthd_##f##_##c)(p,__VA_ARGS__)

/* No method f for assumed object p of class c. Is p an object? */
//  BP_EXTRF = x_HW_MTHD5_0(hw_bp,_m1,_hw__m1,core0,0, mcusr,8,0x54,0x0F,0x00, 1,1)
#define _HW_MTHD4_0(f,p,c,...)	HW_G2(_HW_MTHD5, HW_IS(,_hw_class_##c))(f,p,c,__VA_ARGS__)
#define _HW_MTHD5_1(f,p,c,...)	HW_ERR("object `"#p"` of class `"#c"` has no method `"#f"`.")

/* p is not an object. Is it a class name? */
//  BP_EXTRF = x_HW_MTHD6_1(hw_bp,_m1,_hw__m1,core0,0, mcusr,8,0x54,0x0F,0x00, 1,1)
#define _HW_MTHD5_0(f,p,...)	HW_G2(_HW_MTHD6,HW_IS(,_hw_class_##p))(f,p,__VA_ARGS__)
//#define _HW_MTHD6_1(f,p,pp,...)	f##_##p(__VA_ARGS__)
/* Is there a method f for class c? */
#define _HW_MTHD6_1(f,p,pp,...)	HW_G2(_HW_MTHD8, HW_IS(,_hw_mthd_##f##_##p))(f,p,__VA_ARGS__)
//  BP_EXTRF = _HW_MTHD8_0(hw_bp,_m1,core0,0, mcusr,8,0x54,0x0F,0x00, 1,1)
#define _HW_MTHD8_0(f,c,...)	HW_ERR("class `"#c"` has no method `"#f"`.")
#define _HW_MTHD8_1(f,c,...)	HW_A1(_hw_mthd_##f##_##c)(__VA_ARGS__)

/* p is not an object and not a class name. Is it an error? */
/* #define _HW_MTHD6_0(f,p,...)	HW_G2(_HW_MTHD7,HW_IS(hw_error,p))(f,p,__VA_ARGS__) */
/* #define _HW_MTHD7_1(f,p,...)	p */
/* #define _HW_MTHD7_0(f,p,...)	HW_ERR("`"#p"` is not a HWA object.") */
#define _HW_MTHD6_0(f,p,...)	HW_PE(p, HW_ERR("`"#p"` is not a HWA object."))

#else
/*
 *  This version first assumes that the arguments start with a definition (class
 *  name first)
 */
/* Is the argument a definition starting with a class name? */
#define HW_MTHD(f,...)		HW_G2(_HW_MTHD2,HW_IS(,_hw_class_##__VA_ARGS__))(f,__VA_ARGS__)

/* Is f a method of the class? */
#define _HW_MTHD2_1(f,c,...)	HW_G2(_HW_MTHD3, HW_IS(,_hw_mthd_##f##_##c))(f,c,__VA_ARGS__)
#define _HW_MTHD3_0(f,c,p,...)	HW_ERR("object `"#p"` of class `"#c"` has no method `"#f"`.")
#define _HW_MTHD3_1(f,c,...)	HW_A1(_hw_mthd_##f##_##c)(__VA_ARGS__)

/* Assume the argument is the name of an object, expand its definition to get its class */
#define _HW_MTHD2_0(f,p,...)	_HW_MTHD4(f,p,_##p,__VA_ARGS__)
#define _HW_MTHD4(...)		_HW_MTHD5(__VA_ARGS__)

/* Is there a method f for assumed object p of class c? */
#define _HW_MTHD5(f,p,c,...)	HW_G2(_HW_MTHD5,HW_IS(,_hw_mthd_##f##_##c))(f,p,c,__VA_ARGS__)
#define _HW_MTHD5_1(f,p,c,...)	HW_A1(_hw_mthd_##f##_##c)(c,p,__VA_ARGS__)

/* No method f for assumed object p of class c. Is p an object? */
#define _HW_MTHD5_0(f,p,c,...)	HW_G2(_HW_MTHD6, HW_IS(,_hw_class_##c))(f,p,c,__VA_ARGS__)
#define _HW_MTHD6_1(f,p,c,...)	HW_ERR("object `"#p"` of class `"#c"` has no method `"#f"`.")

/* p is not an object. Is it an error? */
#define _HW_MTHD6_0(f,p,pp,...)	HW_G2(_HW_MTHD7,HW_IS(hw_error,p))(f,p,STOP,__VA_ARGS__)
#define _HW_MTHD7_1(f,x,...)	x
#define _HW_MTHD7_0(f,p,...)	HW_ERR("`"#p"` is not a HWA object.")

#endif


/*
 *  The same for internal use: no checkings
 */
//#define _HW_MTHD(f,...)		HW_A1(HW_G3(__hw_mthd,f,__VA_ARGS__))(__VA_ARGS__)


/*  Specialize instruction f for type t: _HW_SPEC(f,t,...) -> f_t(...)
 *
 *	Arguments must start with a class name that is to be appenned to the
 *	function name.
 */
#define _HW_SPEC(...)		_HW_SPEC_2(__VA_ARGS__)
#define _HW_SPEC_2(f,t,...)	f##_##t(__VA_ARGS__)


/**
 * @brief Applies generic instruction `f` to object `p` (applies to all HWA
 * objects).
 * @hideinitializer
 *
 * Expands to `f(class, p, id, address, ...)` if `p` is the name of a HWA object.
 * <ul><li>`f`: the instruction
 * <li>`p`: the name of the object
 * <li>`class`: the class of `p`
 * <li>`id`: the ID of `p`
 * <li>`address`: the address of `p`
 * </ul>
 */
#define HW_GNRC(f,p,...)	_HW_GNRC_2(f,p,_##p,__VA_ARGS__)
#define _HW_GNRC_2(...)		_HW_GNRC_3(__VA_ARGS__)
#define _HW_GNRC_3(f,p,c,...)	HW_G2(_HW_GNRC,HW_IS(,_hw_class_##c))(f,p,c,__VA_ARGS__)
#define _HW_GNRC_1(f,p,c,...)	f(c,p,__VA_ARGS__)
#define _HW_GNRC_0(f,p,...)	HW_PE(p, HW_ERR("`"#p"` is not a HWA object."))


/**
 * @brief `1` if the first element is the name of a HWA object, `0` if not.
 * @hideinitializer
 */
#define HW_ISOBJ(...)		_HW_ISOBJ_2(__VA_ARGS__)
#define _HW_ISOBJ_2(...)	HW_IS(,HW_G2(_hw_class,_##__VA_ARGS__))


/**
 * @brief `result` if the next element is void, the remaining elements
 *  otherwise.
 * @hideinitializer
 *
 * This is used to help detecting and propagating errors, or ensuring that
 * there is no remaining elements in a list at the end of its parsing.
 */
#define HW_TX(result, ...)	HW_G2(_HW_TX,HW_IS(,__VA_ARGS__))((result),__VA_ARGS__)
#define _HW_TX_0(result, ...)	HW_ERR("garbage found: `" HW_QUOTE(__VA_ARGS__) "`.")
#define _HW_TX_1(result, ...)	_HW_TX_2 result
#define _HW_TX_2(...)		__VA_ARGS__


/**
 * @brief C string from the first element in the list
 * @hideinitializer
 */
#define HW_QUOTE(...)		_HW_QUOTE_2(__VA_ARGS__,)
#define _HW_QUOTE_2(x,...)	#x


/*  Define wich classes are hardware bits
 */
#define hw_hasbits__crg
#define hw_hasbits__cb1
#define hw_hasbits__cb2
#define hw_hasbits__ext
#define hw_hasbits__ob1


/**
 * @brief Memory definition of register `m` of object `p`.
 * @hideinitializer
 *
 *  The word 'register' here stands for 'set of bits' (may be sprayed over 2
 *  hardware registers).
 *
 *  This is a generic instruction that can be applied to every declared instance
 *  whatever its class. `HW_GNRC` expands the definition of object `p` or
 *  produces an error.
 *
 *  Errors are processed at last.
 *
 *  Successful results can be:
 *
 *  `_m1, p,a, r,rw,ra,rwm,rfm, bn,bp`
 *
 *  `_m1x, p,a, r,rw,ra,rwm,rfm, bn,bp`  // same as _m1, resulting from the
 *                                       // expansion of a register of another instance
 *
 *  `_m2, p,a, r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,
 *             r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2`
 */
/*  FIXME: fails without HW_ERR if p is a _pin1:
 *  	_hw_reg_3(_pin1,hw_pin_pa6,307, hw_porta, 1, 6,port)
 *  -> Should hw_reg() be a method?
 */
#define hw_reg(o,m)			HW_GNRC(_hw_reg_3,o,m)
#define _hw_reg_2(...)			_hw_reg_3(__VA_ARGS__)
#define _hw_reg_3(c,o,i,a,m)		_hw_reg_4(_hw_##c##_##m,o,c,a,m)
#define _hw_reg_4(...)			_hw_reg_5(__VA_ARGS__)
#define _hw_reg_5(t,...)		HW_G2(_hw_reg, HW_IS(,hw_hasbits_##t))(t,__VA_ARGS__)
#define _hw_reg_1(t,...)		_hw_x##t(__VA_ARGS__)
//#define _hw_reg_0(t,p,c,a,m)		HW_PE(p, HW_ERR("`"#p"` has no attribute `"#m"`."))

/*  m is not a class member, is it an object member?
 */
#define _hw_reg_0(t,o,c,a,m)		_hw_reg_6(_##o##_##m,o,c,a,m)
#define _hw_reg_6(...)			_hw_reg_7(__VA_ARGS__)
#define _hw_reg_7(t,...)		HW_G2(_hw_reg_7, HW_IS(,hw_hasbits_##t))(t,__VA_ARGS__)
#define _hw_reg_7_1(t,...)		_hw_x##t(__VA_ARGS__)
#define _hw_reg_7_0(t,o,c,a,m)		HW_PE(o, HW_ERR("`"#o"` has no attribute `"#m"`."))


#define _hw_reg(p,m)			_hw__reg_2(p,_##p,m)
#define _hw__reg_2(...)			_hw__reg_3(__VA_ARGS__)
#define _hw__reg_3(p,c,i,a,m)		_hw__reg_4(_hw_##c##_##m,p,c,a,m)
#define _hw__reg_4(...)			_hw__reg_5(__VA_ARGS__)
#define _hw__reg_5(t,...)		_hw_x##t(__VA_ARGS__)


/**
 * @brief Memory definition of register `m` of object of class `c`.
 * @hideinitializer
 */
#define _hw_creg(c,m)			_hw__creg_4(_hw_##c##_##m,_,c,_,m)
#define _hw__creg_4(...)		_hw__creg_5(__VA_ARGS__)
#define _hw__creg_5(t,...)		_hw_x##t(__VA_ARGS__)


/*  Memory definition of a class register
 *	-> _m1, p,a, r,rw,ra,rwm,rfm, bn,bp
 */
#define _hw_x_crg(rw,ra,rwm,rfm, p,c,a,r)	\
  _m1, p,a, r,rw,ra,rwm,rfm, rw,0


/*  Memory definition of a group of consecutive bits in one class register
 *	-> _m1, p,a, r,rw,ra,rwm,rfm, bn,bp
 */
#define _hw_x_cb1(r,bn,bp, p,c,a,m)	_hw_xcb1_2(_hw_##c##_##r,bn,bp,p,c,a,r)
#define _hw_xcb1_2(...)			_hw_xcb1_3(__VA_ARGS__)
#define _hw_xcb1_3(t,...)		_hw_xcb1_##t(__VA_ARGS__)
#define _hw_xcb1__crg(rw,ra,rwm,rfm, bn,bp,p,c,a,r)	\
  _m1, p,a, r,rw,ra,rwm,rfm, bn,bp


//_hw_x_ob1(sr, 1, 0,hw_swuart1,_swuarta,0,synced);

/*  Memory definition of a group of consecutive bits in one object register
 *	-> _m1, p,a, r,rw,ra,rwm,rfm, bn,bp
 */
#define _hw_x_ob1(r,bn,bp, o,c,a,m)	_hw_xob1_2(_##o##_##r,bn,bp,o,c,a,r)
#define _hw_xob1_2(...)			_hw_xob1_3(__VA_ARGS__)
#define _hw_xob1_3(t,...)		_hw_xob1_##t(__VA_ARGS__)
#define _hw_xob1__crg(rw,ra,rwm,rfm, bn,bp,o,c,a,r)	\
  _m1, o,a, r,rw,ra,rwm,rfm, bn,bp



/*  Memory definition of two groups of consecutive bits in one or two class
 *  registers
 *	-> _m2, p,a, r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,
 *	             r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2
 */
#define _hw_x_cb2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, p,c,a,m)	\
  _hw_xcb2_2( r1,_hw_##c##_##r1,rbn1,rbp1,vbp1,			\
	      r2,_hw_##c##_##r2,rbn2,rbp2,vbp2, p,c,a,m)
#define _hw_xcb2_2(...)		_hw_xcb2_3(__VA_ARGS__)
#define _hw_xcb2_3( r1,rc1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
		    r2,rc2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2, p,c,a,m ) \
  _m2, p,a,								\
    r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,				\
    r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2


/*  Memory definition of one instance register bits
 */
#define _hw_x_ext(p,r, p0,c0,a0,r0)	_hw_xext_2(_##p,p,r)
#define _hw_xext_2(...)			_hw_xext_3(__VA_ARGS__)
#define _hw_xext_3(c,i,a,p,r)		_hw_xext_4(_hw_##c##_##r,p,c,a,r)
#define _hw_xext_4(...)			_hw_xext_5(__VA_ARGS__)
#define _hw_xext_5(t,...)		_hw_xext_##t(__VA_ARGS__)

/*  Memory definition of a group of consecutive bits in one instance register
 *	-> _m1x, p,a, r,rw,ra,rwm,rfm, bn,bp
 */
#define _hw_xext__cb1(r,bn,bp, p,c,a,m)	_hw_xextcb1_2(_hw_##c##_##r,bn,bp,p,c,a,r)
#define _hw_xextcb1_2(...)		_hw_xextcb1_3(__VA_ARGS__)
#define _hw_xextcb1_3(rc,rw,ra,rwm,rfm, bn,bp,p,c,a,r)	\
  _m1x, p,a, r,rw,ra,rwm,rfm, bn,bp


/**
 * @brief  hw_addr(...): address of something (method)
 * @hideinitializer
 *
 * This is defined in the vendor-specific file since the adress can be different
 * between compiler and assembler.
 */
#define hw_addr(...)			HW_MTHD(hw_addr, __VA_ARGS__)

#define _hw_mthd_hw_addr__m1		, _hw_addr__m1
#define _hw_mthd_hw_addr__m1x		, _hw_addr__m1


/**
 * @brief  Address of an object's register (internal use)
 * @hideinitializer
*/
#define _hw_ra(p,m)			_hw__ra_2(p,_##p,m)
#define _hw__ra_2(...)			_hw__ra_3(__VA_ARGS__)
#define _hw__ra_3(p,c,i,a,m)		_hw__ra_4(_hw_##c##_##m,p,c,a,m)
#define _hw__ra_4(...)			_hw__ra_5(__VA_ARGS__)
#define _hw__ra_5(t,...)		_hw__ra_6(_hw_x##t(__VA_ARGS__))
#define _hw__ra_6(...)			_hw__ra_7(__VA_ARGS__)
#define _hw__ra_7(t,...)		_hw_addr_##t(__VA_ARGS__)


/**
 * @brief  Address of an object's register (internal use)
 * @hideinitializer
*/
#define _hw_rbp(p,m)			_hw__rbp_2(p,_##p,m)
#define _hw__rbp_2(...)			_hw__rbp_3(__VA_ARGS__)
#define _hw__rbp_3(p,c,i,a,m)		_hw__rbp_4(_hw_##c##_##m,p,c,a,m)
#define _hw__rbp_4(...)			_hw__rbp_5(__VA_ARGS__)
#define _hw__rbp_5(t,...)		_hw__rbp_6(_hw_x##t(__VA_ARGS__))
#define _hw__rbp_6(...)			_hw__rbp_7(__VA_ARGS__)
#define _hw__rbp_7(t,...)		_hw_bp_##t(__VA_ARGS__)


/*	hw_ap(...): address, position of least significant bit (method)
 */
#define hw_ap(...)		HW_MTHD(hw_ap, __VA_ARGS__)

#define _hw_mthd_hw_ap__m1	, _hw_ap__m1
#define _hw_ap__m1(...)		_hw_addr__m1(__VA_ARGS__), _hw_bp__m1(__VA_ARGS__)

//_m1x, hw_core0,0, gimsk,8,0x5B,0x70,0x00, 1,5
#define _hw_mthd_hw_ap__m1x	, _hw_ap__m1
//#define _hw_ap__m1x(...)	_hw_addr__m1(__VA_ARGS__), _hw_bp__m1(__VA_ARGS__)


/*	hw_bn(...): number of bits of something (method)
 */
#define hw_bn(...)		HW_MTHD(hw_bn, __VA_ARGS__,)

//#define _hw_mthd_hw_bn__m1	, _hw_bn__m1

//#define _hw_bn__m1(t, n,c, rn,rw,ra,rwm,rfm, bn,bp)	bn


/*	hw_bp(...): position of least significant bit of something (method)
 */
#define hw_bp(...)		HW_MTHD(hw_bp, __VA_ARGS__)
//#define _hw_bp(...)		_HW_MTHD(_hw_bp, __VA_ARGS__)

#define _hw_mthd_hw_bp__m1	, _hw_bp__m1
#define _hw_mthd_hw_bp__m1x	, _hw_bp__m1

#define _hw_bp__m1(p,a, r,rw,ra,rwm,rfm, bn,bp)	bp


/**
 * @brief Register type of an object (method)
 * Expands to `uint8_t`, `uint16_t`...
 * @hideinitializer
 */
#define hw_rt(o,m)		HW_G2(_hw_rt,HW_ISOBJ(o))(o,m)
#define _hw_rt_0(o,m)		HW_ERR("`" #o "` is not a HWA object.")
#define _hw_rt_1(o,m)		_hw_rt_2(hw_reg(o,m))
#define _hw_rt_2(...)		_hw_rt_3(__VA_ARGS__,)
#define _hw_rt_3(x,...)		HW_PE(x,_hw_rt_##x(__VA_ARGS__))
#define _hw_rt__m1(o,a,rn,rw,...)	uint##rw##_t


/*	hw_id(...): id of an instance (generic)
 *
 *	Do not use HW_GNRC(), return 0 if instance does not exist
 */
/* #define hw_id(...)		_hw_id_2(__VA_ARGS__) */
/* #define _hw_id_2(...)		HW_G2(_hw_id, HW_IS(,_hw_class_##__VA_ARGS__))(__VA_ARGS__) */
/* #define _hw_id_0(...)		0	/\* instance does not exist *\/ */
/* #define _hw_id_1(n,c,i,...)	i */

#define hw_id(p)		HW_G2(_hw_id,HW_ISOBJ(p))(p)
#define _hw_id_1(p)		HW_A1(_##p)
#define _hw_id_0(p)		0


/*	hw_io(...): definition of the io associated to an instance, or the io itself (method)
 */
//#define hw_io(...)		HW_MTHD(hw_io, __VA_ARGS__)
#define hw_io(p)		HW_MTHD(hw_io, p,)

/*	hw_sub(...): name of the sub module of a controller
 */
/* #define hw_sub(p,x)		HW_GNRC(_hw_sub,p,x) */
/* #define _hw_sub(c,p,i,a, x)	HW_G2(_hw_sub,HW_ISOBJ(p##_##x))(p,x) */
/* #define _hw_sub_0(p,x)		HW_ERR("`"#p"` has no sub `"#x"`.") */
/* #define _hw_sub_1(p,x)		p##_##x */

/* #define hw_sub(...)		_hw_sub_2(__VA_ARGS__,,) */
/* #define _hw_sub_2(p,x,...)	HW_G2(_hw_sub,HW_ISOBJ(p##_##x))(p,x,__VA_ARGS__) */
/* #define _hw_sub_1(p,x,...)	HW_TX(p##_##x, __VA_ARGS__) */

#define hw_sub(p,x)		_hw_sub_2(p,x)
#define _hw_sub_2(p,x)		HW_G2(_hw_sub,HW_ISOBJ(p##_##x))(p,x)
#define _hw_sub_1(p,x)		p##_##x

#define _hw_sub_0(p,x)		HW_PE(p, HW_G2(_hw_sub0,HW_ISOBJ(p))(p,x))
#define _hw_sub0_0(p,x)		HW_ERR("`"#p"` is not a HWA object.")
#define _hw_sub0_1(p,x)		HW_ERR("`"#p"` has no sub `"#x"`."))


/*	hw_sup(...): definition of the controller associated to an instance (method)
 */
#define hw_sup(p)		HW_MTHD(hw_sup, p,)
