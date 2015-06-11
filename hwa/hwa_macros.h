
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

#define _hw_state_on			, 1
#define _hw_state_off			, 0
#define _hw_state_yes			, 1
#define _hw_state_no			, 0
#define _hw_state_enabled		, 1
#define _hw_state_disabled		, 0

/*  HWA classes
 */
#define _hw_class__r8
#define _hw_class__r16
#define _hw_class__cb1
#define _hw_class__cb2
#define _hw_class__irq
#define _hw_class__m1
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


/*  Emit an error (when not inside a function)
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
 *  If a class c of an object o has a method f, _hw_mthd_f_c is defined as `, fm`
 *  where fm is the definition of f. fm is called with the definition of o after
 *  having replaced the class name of o with o's name.
 *
 *  If HW_A0(_hw_mthd_f_c) is not ``, there is no method f for class c. Then try
 *  to determine the reason:
 *
 *    * o is not a HWA object
 *    * c has no method f
 *    * o is already an error
 *
 *  Note: an extra void argument must be added for single argument instructions
 *  in order to avoid a warning at compilation. FIXME: could it be done here?
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
 * @brief Specialize instruction `f` for class `c`: _HW_SPEC(f,t,...) -> f_c(...)
 *
 *  Arguments must start with a class name that is to be appended to the
 *  function name.
 */
#define _HW_SPEC(...)		_HW_SPEC_2(__VA_ARGS__)
#define _HW_SPEC_2(f,c,...)	f##_##c(__VA_ARGS__)


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
 * @brief `result` if the next element is void, an error otherwise.
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
#define hw_hasbits__r8
#define hw_hasbits__r16
#define hw_hasbits__cb1
#define hw_hasbits__cb2
//#define hw_hasbits__ext
#define hw_hasbits__ob1
#define hw_hasbits__ob2
#define hw_hasbits__xob1


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
 *  `_m1, o,a, r,rc,ra,rwm,rfm, bn,bp`
 *
 *  `_m2, o,a, r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,
 *             r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2`
 */
/*  FIXME: fails without HW_ERR if p is a _pin1:
 *  	_hw_reg_3(_pin1,hw_pin_pa6,307, hw_porta, 1, 6,port)
 *  -> Should hw_reg() be a method?
 */
#define hw_reg(o,r)			HW_GNRC(_hw_reg_3,o,r)
#define _hw_reg_2(...)			_hw_reg_3(__VA_ARGS__)
#define _hw_reg_3(c,o,i,a,r)		_hw_reg_4(_hw_##c##_##r,o,c,a,r)
#define _hw_reg_4(...)			_hw_reg_5(__VA_ARGS__)
#define _hw_reg_5(t,...)		HW_G2(_hw_reg, HW_IS(,hw_hasbits_##t))(t,__VA_ARGS__)
#define _hw_reg_1(t,...)		_hw_x_##t(__VA_ARGS__)
#define _hw_reg_0(t,o,c,a,r)		_hw_reg_6(_##o##_##r,o,c,a,r)
#define _hw_reg_6(...)			_hw_reg_7(__VA_ARGS__)
#define _hw_reg_7(t,...)		HW_G2(_hw_reg_7, HW_IS(,hw_hasbits_##t))(t,__VA_ARGS__)
#define _hw_reg_7_1(t,...)		_hw_x_##t(__VA_ARGS__)
#define x_hw_reg_7_0(t,o,c,a,r)		HW_PE(o, HW_ERR("`"#o"` has no attribute `"#r"`."))


/**
 * @brief Memory definition of a register (internal use, no error checking)
 */
#define _hw_reg(o,r)			_hw__reg_2(o,_##o,r)
#define _hw__reg_2(...)			_hw__reg_3(__VA_ARGS__)
#define _hw__reg_3(o,c,i,a,r)		_hw__reg_4(_hw_##c##_##r,o,c,a,r)
#define _hw__reg_4(...)			_hw__reg_5(__VA_ARGS__)
#define _hw__reg_5(t,...)		HW_G2(_hw__reg, HW_IS(,hw_hasbits_##t))(t,__VA_ARGS__)
#define _hw__reg_1(t,...)		_hw_x_##t(__VA_ARGS__)
#define _hw__reg_0(t,o,c,a,r)		_hw__reg_6(_##o##_##r,o,c,a,r)
#define _hw__reg_6(...)			_hw__reg_1(__VA_ARGS__)


/**
 * @brief Memory definition of register `m` of an object of class `c` pointed by
 * p.
 *
 * @hideinitializer
 */
#define _hw_reg_p(p,c,m)		_hw_reg_p_4(_hw_##c##_##m,p,c,m)
#define _hw_reg_p_4(...)		_hw_reg_p_5(__VA_ARGS__)
#define _hw_reg_p_5(t,...)		_hw_xp_##t(__VA_ARGS__)


/*  Memory definition of a hardware register
 *	-> _m1, p,a, r,rc,ra,rwm,rfm, bn,bp
 */
#define _hw_x__r8(ra,rwm,rfm, o,c,a,r)	_m1, o,a, r, _r8, ra,rwm,rfm,  8,0
#define _hw_x__r16(ra,rwm,rfm, o,c,a,r)	_m1, o,a, r,_r16, ra,rwm,rfm, 16,0


/*  Memory definition of a group of consecutive bits in one class register
 *	-> _m1, p,a, r,rc,ra,rwm,rfm, bn,bp
 */
#define _hw_x__cb1(r,bn,bp, o,c,a,m)		_HW_SPEC(_hw_xcb1, _hw_##c##_##r,bn,bp,o,r)
#define _hw_xcb1__r8(ra,rwm,rfm,bn,bp,o,r) 	_m1, o,0, r,_r8,ra,rwm,rfm, bn,bp
#define _hw_xcb1__r16(ra,rwm,rfm,bn,bp,o,r) 	_m1, o,0, r,_r16,ra,rwm,rfm, bn,bp


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
 *	-> _m1, p,a, r,rc,ra,rwm,rfm, bn,bp
 */
#define _hw_x__ob1(r,bn,bp, o,c,a,m)		_HW_SPEC(_hw_xob1, _##o##_##r,bn,bp,o,r)
#define _hw_xob1__r8(ra,rwm,rfm,bn,bp,o,r) 	_m1, o,0, r,_r8,ra,rwm,rfm, bn,bp


/**
 * @brief Expand the memory definition of one group of consecutive bits to be
 * found in a another object `to` hardware register `tr`.
 */
/*  NOTE: we do not get the address of `to` and consider it is 0.
 */
#define _hw_x__xob1(to,tr,bn,bp, o,c,a,m)	_HW_SPEC(_hw_xxob1, _##to##_##tr,bn,bp,to,tr)
#define _hw_xxob1__r8(ra,rwm,rfm, bn,bp,o,r) 	_m1, o,0, r,_r8,ra,rwm,rfm, bn,bp


/**
 * @brief Expand the memory definition of one hardware register of another
 * object
 */
#define _hw_xp__r8(ra,rwm,rfm, p,c,r)		_m1_p, &p->r,_r8,rwm,rfm,8,0
#define _hw_xp__r16(ra,rwm,rfm, p,c,r)		_m1_p, &p->r,_r16,rwm,rfm,16,0


/**
 * @brief Expand the memory definition of one group of consecutive bits to be
 * found in a another object `o` hardware register `r` pointed by `p`
 */
#define _hw_xp__xob1(o,r,bn,bp, p,c,m)		_HW_SPEC(_hw_xpob1, _##o##_##r,bn,bp,&hwa->o.r)
#define _hw_xpob1__r8(ra,rwm,rfm, bn,bp,p)	_m1_p, p,_r8,rwm,rfm,bn,bp

/**
 * @brief Expand the memory definition of one group of consecutive bits in the
 * object pointed by `p`
 */
#define _hw_xp__cb1(r,bn,bp, p,c,m)		_HW_SPEC(_hw_xpcb1, _hw_##c##_##r,bn,bp,&p->r)
#define _hw_xpcb1__r8(ra,rwm,rfm, bn,bp,p)	_m1_p, p,_r8,rwm,rfm,bn,bp


/**
 * @brief Expand the memory definition of two groups of consecutive bits in the
 * object pointed by `p`
 */
#define _hw_xp__cb2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, p,c,m)		\
  _hw_xpcb2_2( &p->r1,_hw_##c##_##r1,rbn1,rbp1,vbp1,			\
		&p->r2,_hw_##c##_##r2,rbn2,rbp2,vbp2 )
#define _hw_xpcb2_2(...)			_hw_xpcb2_3(__VA_ARGS__)
#define _hw_xpcb2_3( p1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
		     p2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2 )		\
  _m2_p, p1,rc1,rwm1,rfm1,rbn1,rbp1,vbp1, p2,rc2,rwm2,rfm2,rbn2,rbp2,vbp2


/*  Memory definition of two groups of consecutive bits in one object register
 *	-> _m2, p,a, r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,
 *	             r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2
 */
#define _hw_x_ob2(r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2, o,c,a,m)	\
  _hw_xcb2_2(r1,_##o##_##r1,rbn1,rbp1,vbp1,				\
	     r2,_##o##_##r2,rbn2,rbp2,vbp2, o,c,a,m)


/**
 * @brief  hw_addr(...): address of an object
 * @hideinitializer
 */
/* This is defined in the vendor-specific file since the address can be
 * different between C and assembler.
 */
#define hw_addr(...)			HW_MTHD(hw_addr, __VA_ARGS__)

#define _hw_mthd_hw_addr__m1		, _hw_addr__m1


/**
 * @brief  Address of an object's register (internal use)
 * @hideinitializer
*/
#define _hw_ra(o,r)			_HW_SPEC(_hw_ra, _hw_reg(o,r))


/*	hw_ap(...): address, position of least significant bit (method)
 */
#define hw_ap(...)			HW_MTHD(hw_ap, __VA_ARGS__)

#define _hw_mthd_hw_ap__m1		, _hw_ap__m1
#define _hw_ap__m1(...)			_hw_addr__m1(__VA_ARGS__), _hw_bp__m1(__VA_ARGS__)


/**
 * @brief  Number of bits of an object
 * @hideinitializer
 */
#define hw_bn(...)			HW_MTHD(hw_bn, __VA_ARGS__,)

#define _hw_mthd_hw_bn__m1		, _hw_bn__m1

#define _hw_bn__m1(o,a, r,rw,ra,rwm,rfm, bn,bp)	bn


/**
 * @brief  Number of bits of an object's register (internal use)
 * @hideinitializer
 */
#define _hw_rbn(o,r)					_HW_SPEC(_hw_rbn,_hw_reg(o,r))
#define _hw_rbn__m1(o,a, r,rc,ra,rwm,rfm, bn,bp)	bn


/*	hw_bp(...): position of least significant bit of something (method)
 */
#define hw_bp(...)					HW_MTHD(hw_bp, __VA_ARGS__)

#define _hw_mthd_hw_bp__m1				, _hw_bp__m1

#define _hw_bp__m1(o,a, r,rw,ra,rwm,rfm, bn,bp)		bp


/**
 * @brief  Position of the lsb of a register (internal use)
 * @hideinitializer
*/
#define _hw_rbp(o,r)					_HW_SPEC(_hw_rbp,_hw_reg(o,r))
#define _hw_rbp__m1(o,a, r,rc,ra,rwm,rfm, bn,bp)	bp


/**
 * @brief uint_t type type of an object's hardware register (method)
 * Expands to `uint8_t`, `uint16_t`...
 * @hideinitializer
 */
#define hw_uint_t(o,r)					_HW_SPEC(_hw_uintt,hw_reg(o,r))
#define _hw_uintt__m1(o,a,r,rc,ra,rwm,rfm,bn,bp)	uint##bn##_t


/**
 * @brief Class of an object's register (internal use)
 * @hideinitializer
 */
#define _hw_rc(o,r)					_HW_SPEC(_hw_rc,_hw_reg(o,r))
#define _hw_rc__m1(o,a,r,rc,ra,rwm,rfm,bn,bp)		rc


/**
 * @brief ID of an object. 0 if the object does not exist.
 * @hideinitializer
 */
#define hw_id(o)			HW_G2(_hw_id,HW_ISOBJ(o))(o)
#define _hw_id_1(o)			HW_A1(_##o)
#define _hw_id_0(o)			0


/**
 * @brief Definition of the i/o associated to an object, or the io itself
 * @hideinitializer
 */
#define hw_io(o)			HW_MTHD(hw_io, o,)


/**
 * @brief Name of an object of a peripheral
 * @hideinitializer
 */
#define hw_sub(o,x)			_hw_sub_2(o,x)
#define _hw_sub_2(o,x)			HW_G2(_hw_sub,HW_ISOBJ(o##_##x))(o,x)
#define _hw_sub_1(o,x)			o##_##x

#define _hw_sub_0(o,x)			HW_PE(o, HW_G2(_hw_sub0,HW_ISOBJ(o))(o,x))
#define _hw_sub0_0(o,x)			HW_ERR("`"#o"` is not a HWA object.")
#define _hw_sub0_1(o,x)			HW_ERR("`"#o"` has no object `"#x"`."))


/**
 * @brief  Definition of the peripheral associated to an object (method)
 * @hideinitializer
 */
#define hw_sup(o)			HW_MTHD(hw_sup, o,)
