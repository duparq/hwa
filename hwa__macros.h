
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** @file
 *
 *  @brief	General purpose macro definitions usable in C or assembler source code.
 *
 *	Upper case definitions process arbitrary lists of arguments.
 *
 *	Lower case definitions deal with lists of arguments starting with a
 *	class name.
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
#define _hw_class__m2

#define _hw_is_hw_error_hw_error		, 1, /* one more comma to remove '; StaticAssert(...)' */


#if defined __ASSEMBLER__
#  define HW_ERR(msg)		0 ; .fail "HWA: " msg
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
#define _HW_ERRFN_3(n,...)	void hw_err##n { uint8_t x = __VA_ARGS__ } void hw_err##n##_

#endif


/*  Produce an error message: expand to x if it is already is an error,
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
#define _hw_is_0_0		, 1,	/* one more comma to remove '; StaticAssert(...)' */
#define _hw_is__			, 1
#define _hw_is_enabled_enabled	, 1
#define _hw_is_disabled_disabled	, 1
#define _hw_is_yes_yes		, 1
#define _hw_is_no_no		, 1
#define _hw_is_off_off		, 1


/*  HW_MTHD(f, ...)	Apply method f to arguments
 *
 *  Arguments must start with the name of an object, or the definition of an
 *  object starting with its class (as returned by instructions such as
 *  hw_sup(...).
 *
 *  If a class c of an object p has a method f, hw_mthd_f_c is defined as `, fm`
 *  where fm is the definition of f. fm is called with the definition of p after
 *  having replaced the p's class name with the p's name.
 *
 *  If HW_A0(hw_mthd_f_c) is not ``, there is no method f for class c. Then try
 *  to determine the reason:
 *
 *    * p is not a HWA object
 *    * c has no method f
 *    * p is an error
 *
 *  TODO: HW_MTHD could append the last void argument used for garbage checking.
 */
#if 1

/* Assume the argument is the name of an object, expand its definition to get its class */
#define HW_MTHD(...)		_HW_MTHD1(__VA_ARGS__)
#define _HW_MTHD1(f,p,...)	_HW_MTHD2(f,p,_##p,__VA_ARGS__)
#define _HW_MTHD2(...)		_HW_MTHD3(__VA_ARGS__)

/* Is there a method f for assumed object p of class c? */
// MCUSR = x_HW_MTHD4_0(_hw_addr,_m1,_hw__m1,core0,0, mcusr,8,0x54,0x0F,0x00, 8,0)
#define _HW_MTHD3(f,p,c,...)	HW_G2(_HW_MTHD4, HW_IS(,hw_mthd_##f##_##c))(f,p,c,__VA_ARGS__)
#define _HW_MTHD4_1(f,p,c,...)	HW_A1(hw_mthd_##f##_##c)(p,__VA_ARGS__)

/* No method f for assumed object p of class c. Is p an object? */
//  BP_EXTRF = x_HW_MTHD5_0(hw_bp,_m1,_hw__m1,core0,0, mcusr,8,0x54,0x0F,0x00, 1,1)
#define _HW_MTHD4_0(f,p,c,...)	HW_G2(_HW_MTHD5, HW_IS(,_hw_class_##c))(f,p,c,__VA_ARGS__)
#define _HW_MTHD5_1(f,p,c,...)	HW_ERR("object `"#p"` of class `"#c"` has no method `"#f"`.")

/* p is not an object. Is it a class name? */
//  BP_EXTRF = x_HW_MTHD6_1(hw_bp,_m1,_hw__m1,core0,0, mcusr,8,0x54,0x0F,0x00, 1,1)
#define _HW_MTHD5_0(f,p,...)	HW_G2(_HW_MTHD6,HW_IS(,_hw_class_##p))(f,p,__VA_ARGS__)
//#define _HW_MTHD6_1(f,p,pp,...)	f##_##p(__VA_ARGS__)
/* Is there a method f for class c? */
#define _HW_MTHD6_1(f,p,pp,...)	HW_G2(_HW_MTHD8, HW_IS(,hw_mthd_##f##_##p))(f,p,__VA_ARGS__)
//  BP_EXTRF = _HW_MTHD8_0(hw_bp,_m1,core0,0, mcusr,8,0x54,0x0F,0x00, 1,1)
#define _HW_MTHD8_0(f,c,...)	HW_ERR("class `"#c"` has no method `"#f"`.")
#define _HW_MTHD8_1(f,c,...)	HW_A1(hw_mthd_##f##_##c)(__VA_ARGS__)

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
#define _HW_MTHD2_1(f,c,...)	HW_G2(_HW_MTHD3, HW_IS(,hw_mthd_##f##_##c))(f,c,__VA_ARGS__)
#define _HW_MTHD3_0(f,c,p,...)	HW_ERR("object `"#p"` of class `"#c"` has no method `"#f"`.")
#define _HW_MTHD3_1(f,c,...)	HW_A1(hw_mthd_##f##_##c)(__VA_ARGS__)

/* Assume the argument is the name of an object, expand its definition to get its class */
#define _HW_MTHD2_0(f,p,...)	_HW_MTHD4(f,p,_##p,__VA_ARGS__)
#define _HW_MTHD4(...)		_HW_MTHD5(__VA_ARGS__)

/* Is there a method f for assumed object p of class c? */
#define _HW_MTHD5(f,p,c,...)	HW_G2(_HW_MTHD5,HW_IS(,hw_mthd_##f##_##c))(f,p,c,__VA_ARGS__)
#define _HW_MTHD5_1(f,p,c,...)	HW_A1(hw_mthd_##f##_##c)(c,p,__VA_ARGS__)

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
//#define _HW_MTHD(f,...)		HW_A1(HW_G3(_hw_mthd,f,__VA_ARGS__))(__VA_ARGS__)


/*  Specialize instruction f for type t: f(t,...) -> f_t(...)
 *
 *	Arguments must start with a class name that is to be appenned to the
 *	function name.
 */
#define _HW_SPEC(...)		_HW_SPEC_2(__VA_ARGS__)
#define _HW_SPEC_2(f,t,...)	f##_##t(__VA_ARGS__)


/*	Generic instruction (applies to all HWA objects).
 *
 * 	Check that p is the name of a HWA object (has a declared class). Then,
 * 	expand to:
 *
 *		f(class, p, id, address, ...).
 */
#define HW_GNRC(f,p,...)	_HW_GNRC_2(f,p,_##p,__VA_ARGS__)
#define _HW_GNRC_2(...)		_HW_GNRC_3(__VA_ARGS__)
#define _HW_GNRC_3(f,p,c,...)	HW_G2(_HW_GNRC,HW_IS(,_hw_class_##c))(f,p,c,__VA_ARGS__)
#define _HW_GNRC_1(f,p,c,...)	f(c,p,__VA_ARGS__)
#define _HW_GNRC_0(f,p,...)	HW_PE(p, HW_ERR("`"#p"` is not a HWA object."))


/*  1 if argument is the name of a HWA object, 0 if not
 */
#define HW_ISOBJ(...)		HW_IS(,HW_G2(_hw_class,_##__VA_ARGS__))


/*  Expand to `result` if the next argument is '', an error otherwise
 */
#define HW_TX(result, ...)	HW_G2(_HW_TX,HW_IS(,__VA_ARGS__))((result),__VA_ARGS__)
#define _HW_TX_0(result, ...)	HW_ERR("garbage found: `" HW_QUOTE(__VA_ARGS__) "`.")
#define _HW_TX_1(result, ...)	_HW_TX_2 result
#define _HW_TX_2(...)		__VA_ARGS__


/** \brief	Quote the first element in the list
 */
#define HW_QUOTE(...)		_HW_QUOTE_2(__VA_ARGS__,)
#define _HW_QUOTE_2(x,...)	#x


/*	hw_reg(...): get the memory definition of an instance's register. The
 *	word 'register' here stands for 'set of bits' that can be sprayed over 2
 *	MCU registers.
 *
 *	This is a generic instruction that can be applied to every declared
 *	instance whatever its class.
 *
 *	Results can be:
 *
 *	_m1, p,a, r,rw,ra,rwm,rfm, bn,bp
 *
 *	_m1x, p,a, r,rw,ra,rwm,rfm, bn,bp  // same as _m1, resulting from the
 *					   // expansion of an instance register
 *
 *	_m2, p,a, r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,
 *                r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2
 */
#define hw_hasbits__crg
#define hw_hasbits__cb1
#define hw_hasbits__cb2
#define hw_hasbits__irg


/*	hw_reg(p,m): memory definition of register bits 'm' of object 'p'
 *
 *	HW_GNRC expands the definition of the object p or produces an error.
 *	First, assume there is no error and try to get the definition of the
 *	register, handle errors at last.
 */
#define hw_reg(...)			HW_GNRC(_hw_reg_3,__VA_ARGS__)
#define _hw_reg_2(...)			_hw_reg_3(__VA_ARGS__)
#define _hw_reg_3(c,p,i,a,...)		_hw_reg_4(HW_G3(_hw,c,__VA_ARGS__),p,c,a,__VA_ARGS__)
#define _hw_reg_4(...)			_hw_reg_5(__VA_ARGS__)
#define _hw_reg_5(t,...)		HW_G2(_hw_reg, HW_IS(,hw_hasbits_##t))(t,__VA_ARGS__)
#define _hw_reg_1(t,...)		_hw_x##t(__VA_ARGS__)
#define _hw_reg_0(t,p,c,a,r)		HW_PE(p, HW_ERR("`"#p"` has no register named `"#r"`."))

#define _hw_reg(p,m)			_hw__reg_2(p,_##p,m)
#define _hw__reg_2(...)			_hw__reg_3(__VA_ARGS__)
#define _hw__reg_3(p,c,i,a,m)		_hw__reg_4(_hw_##c##_##m,p,c,a,m)
#define _hw__reg_4(...)			_hw__reg_5(__VA_ARGS__)
#define _hw__reg_5(t,...)		_hw_x##t(__VA_ARGS__)

/*	_hw_creg(c,m): memory definition of register bits 'm' of object of class
 *	'c'
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
#define _hw_xcb1_3(rc,rw,ra,rwm,rfm, bn,bp,p,c,a,r)	\
  _m1, p,a, r,rw,ra,rwm,rfm, bn,bp


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
#define _hw_x_irg(p,r, p0,c0,a0,r0)	_hw_xirg_2(_##p,p,r)
#define _hw_xirg_2(...)			_hw_xirg_3(__VA_ARGS__)
#define _hw_xirg_3(c,i,a,p,r)		_hw_xirg_4(_hw_##c##_##r,p,c,a,r)
#define _hw_xirg_4(...)			_hw_xirg_5(__VA_ARGS__)
#define _hw_xirg_5(t,...)		_hw_xirg_##t(__VA_ARGS__)

/*  Memory definition of a group of consecutive bits in one instance register
 *	-> _m1x, p,a, r,rw,ra,rwm,rfm, bn,bp
 */
#define _hw_xirg__cb1(r,bn,bp, p,c,a,m)	_hw_xirgcb1_2(_hw_##c##_##r,bn,bp,p,c,a,r)
#define _hw_xirgcb1_2(...)		_hw_xirgcb1_3(__VA_ARGS__)
#define _hw_xirgcb1_3(rc,rw,ra,rwm,rfm, bn,bp,p,c,a,r)	\
  _m1x, p,a, r,rw,ra,rwm,rfm, bn,bp


/*	hw_addr(...): address of something (method)
 */
#define hw_addr(...)		HW_MTHD(hw_addr, __VA_ARGS__)
#define _hw_addr(...)		_HW_MTHD(_hw_addr, __VA_ARGS__)

#define hw_mthd_hw_addr__m1	, _hw_addr__m1


/*	hw_ap(...): address, position of least significant bit (method)
 */
#define hw_ap(...)		HW_MTHD(hw_ap, __VA_ARGS__)

#define hw_mthd_hw_ap__m1	, _hw_ap__m1
#define _hw_ap__m1(...)		_hw_addr__m1(__VA_ARGS__), _hw_bp__m1(__VA_ARGS__)


/*	hw_bn(...): number of bits of something (method)
 */
#define hw_bn(...)		HW_MTHD(hw_bn, __VA_ARGS__)

//#define hw_mthd_hw_bn__m1	, _hw_bn__m1

//#define _hw_bn__m1(t, n,c, rn,rw,ra,rwm,rfm, bn,bp)	bn


/*	hw_bp(...): position of least significant bit of something (method)
 */
#define hw_bp(...)		HW_MTHD(hw_bp, __VA_ARGS__)
//#define _hw_bp(...)		_HW_MTHD(_hw_bp, __VA_ARGS__)

#define hw_mthd_hw_bp__m1	, _hw_bp__m1

#define _hw_bp__m1(p,a, r,rw,ra,rwm,rfm, bn,bp)	bp


/*	hw_id(...): id of an instance (generic)
 *
 *	Do not use HW_GNRC(), return 0 if instance does not exist
 */
#define hw_id(...)		_hw_id_2(__VA_ARGS__)
#define _hw_id_2(...)		HW_G2(_hw_id, HW_IS(,_hw_class_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_id_0(...)		0	/* instance does not exist */
#define _hw_id_1(n,c,i,...)	i


/*	hw_io(...): definition of the io associated to an instance, or the io itself (method)
 */
#define hw_io(...)		HW_MTHD(hw_io, __VA_ARGS__)


/*	hw_sub(...): name of the sub module of a controller
 */
#define hw_sub(p,x)		HW_GNRC(_hw_sub,p,x)
//#define _hw_sub(c,p,i,a, x)	p##_##x
#define _hw_sub(c,p,i,a, x)	HW_G2(_hw_sub,HW_ISOBJ(p##_##x))(p,x)
#define _hw_sub_0(p,x)		HW_ERR("`"#p"` has no sub `"#x"`.")
#define _hw_sub_1(p,x)		p##_##x
//#define _hw_sub_1(p,x)		hw_##p##_##x /* name missing */


/*	hw_sup(...): definition of the controller associated to an instance (method)
 */
#define hw_sup(...)		HW_MTHD(hw_sup, __VA_ARGS__,)
