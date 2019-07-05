
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*  These macros expand the `object argument`.
 *  See HW_X() below.
 */


/*
 * @brief Returns the standard definition of o: c,o,(...)
 * Insert the name of the object, o, into the definition.
 * Return ,o,"error message" if o is not an object.
 */
#define HW_XO(o)			_HW_XO01(o,hw_##o)
#define _HW_XO01(...)			_HW_XO02(__VA_ARGS__)
#define _HW_XO02(o,...)			HW_Y0(_HW_XO02_,hw_class_##__VA_ARGS__)(o,__VA_ARGS__)
#define _HW_XO02_0(o,...)		HW_Y0(_HW_XO020,o)(o)
#define _HW_XO0200(o)			,o,HW_EM_O(o)
#define _HW_XO0201(o)			,o,HW_EM_OM(o)
#define _HW_XO02_1(o,c,...)		c,o,(__VA_ARGS__) // brackets


/*
 * @brief Returns the standardized definition of the relative r of object o: `o,c,(...)`
 *  
 *  Returns the standardized definition of o if r is void.
 *  Returns ,o,"error message" if the relative can not be found.
 *
 *  The relative r of o is searched in this order:
 *   * hw_o_r
 *   * _hw_rel_c_r(o,d)
 *   * hw_reg_o_r
 *   * hw_reg_c_r
 */
#define HW_OR(o,r)			HW_Y0(_HW_OR00_,r)(o,r)
#define _HW_OR00_1(o,...)		HW_XO(o)
#define _HW_OR00_0(o,r)			_HW_OR01(o,r,hw_##o##_##r)
#define _HW_OR01(...)			_HW_OR02(__VA_ARGS__)
#define _HW_OR02(o,r,...)		HW_Y0(_HW_OR02_,hw_class_##__VA_ARGS__)(o,r,__VA_ARGS__)
#define _HW_OR02_1(o,r,c,...)		c,o,(__VA_ARGS__)
#define _HW_OR02_0(o,r,x)		_HW_OR03(o,r,HW_XO(x))
#define _HW_OR03(...)			_HW_OR04(__VA_ARGS__)
#define _HW_OR04(o,r,c,...)		HW_Y0(_HW_OR04_,c)(o,r,c,__VA_ARGS__)
#define _HW_OR04_0(o,r,...)		__VA_ARGS__

//  Search _hw_rel_c_r(o,d)
#define _HW_OR04_1(o,r,...)		_HW_OR11(HW_XO(o),r)
#define _HW_OR11(...)			_HW_OR12(__VA_ARGS__)
#define _HW_OR12(c,...)			HW_Y0(_HW_OR12_,c)(c,__VA_ARGS__)
#define _HW_OR12_1(...)			__VA_ARGS__ // Error
#define _HW_OR12_0(c,o,d,r)		_HW_OR13(c,o,d,r,_hw_rel_##c##_##r(o,d))
#define _HW_OR13(...)			_HW_OR14(__VA_ARGS__)
#define _HW_OR14(c,o,d,r,x)		_HW_OR15(HW_XO(x),c,o,d,r,x)
#define _HW_OR15(...)			_HW_OR16(__VA_ARGS__)
#define _HW_OR16(c,...)			HW_Y0(_HW_OR16_,c)(c,__VA_ARGS__)
#define _HW_OR16_0(c,o,d,...)		c,o,d

//  Search hw_reg_o_r
#define _HW_OR16_1(_c,_o,_d,c,o,d,r,x)	_HW_OR21(c,o,d,r,hw_reg_##o##_##r)
#define _HW_OR21(...)			_HW_OR22(__VA_ARGS__)
#define _HW_OR22(c,o,d,r,...)		HW_Y0(_HW_OR22_,hw_class_##__VA_ARGS__)(c,o,d,r,__VA_ARGS__)
#define _HW_OR22_1(...)			_HW_OR40(__VA_ARGS__)

//  Search hw_reg_c_r
#define _HW_OR22_0(c,o,d,r,...)		_HW_OR31(c,o,d,r,hw_reg_##c##_##r)
#define _HW_OR31(...)			_HW_OR32(__VA_ARGS__)
#define _HW_OR32(c,o,d,r,...)		HW_Y0(_HW_OR32_,hw_class_##__VA_ARGS__)(c,o,d,r,__VA_ARGS__)
#define _HW_OR32_1(...)			_HW_OR40(__VA_ARGS__)
/* #define _HW_OR32_0(c,o,d,r,x)		,o,HW_EM_OO(o,r) */

//  Search _hw_rel_c(o,d,r)
#define _HW_OR32_0(c,o,d,r,x)		_HW_OR43(c,o,d,r,_hw_rel_##c(o,d,r))
#define _HW_OR43(...)			_HW_OR44(__VA_ARGS__)
#define _HW_OR44(c,o,d,r,x)		_HW_OR45(HW_XO(x),c,o,d,r,x)
#define _HW_OR45(...)			_HW_OR46(__VA_ARGS__)
#define _HW_OR46(c,...)			HW_Y0(_HW_OR46_,c)(c,__VA_ARGS__)
#define _HW_OR46_0(c,o,d,...)		c,o,d
#define _HW_OR46_1(_c,_o,_d,c,o,d,r,x)	,o,HW_EM_OO(o,r)


/*  Registers are converted to standardized memory definitions:
 *   * _m111,reg(o,r),(o,r,rc,a,wm,fm,bn,bp)
 *   * _m112,reg(o,r),(o,r,rc,a,wm,fm,bn1,bp1,vp1,bn2,bp2,vp2)
 *   * _m122,reg(o,r),(o,r1,rc1,a1,wm1,fm1,bn1,bp1,vp1,r2,rc2,a2,wm2,fm2,bn2,bp2,vp2)
 */
#define _HW_OR40(c,o,d,r,rc,...)	_HW_OR41(rc,r,__VA_ARGS__,c,o,HW_XB d)
#define _HW_OR41(...)			_HW_OR42(__VA_ARGS__)
#define _HW_OR42(rc,...)		_HW_XR##rc(__VA_ARGS__)

#define _HW_XR_r8(r,ra,rwm,rfm,c,o,i,a)		_m111,reg(o,r),(o,r,_r8,a+ra,rwm,rfm,8,0)
#define _HW_XR_r16(r,ra,rwm,rfm,c,o,i,a)	_m111,reg(o,r),(o,r,_r16,a+ra,rwm,rfm,16,0)
#define _HW_XR_r32(r,ra,rwm,rfm,c,o,i,a)	_m111,reg(o,r),(o,r,_r32,a+ra,rwm,rfm,32,0)

#define _HW_XR_ob1(s,r,bn,bp,c,o,i,a)	_HW_XR_ob1_01(o,a,r,hw_reg_##o##_##r,bn,bp)
#define _HW_XR_ob1_01(...)		_HW_XR_ob1_02(__VA_ARGS__)
#define _HW_XR_ob1_02(o,a,r,rc,ra,...)	_m111,reg(o,r),(o,r,rc,a+ra,__VA_ARGS__)

#define _HW_XR_cb1(s,r,bn,bp,c,o,i,a)	_HW_XR_ob1_01(o,a,r,hw_reg_##c##_##r,bn,bp)

#define _HW_XR_xob1(s,xo,xr,bn,bp,...)	_HW_XOB101(xo,hw_##xo,xr,bn,bp,hw_reg_##xo##_##xr)
#define _HW_XOB101(...)			_HW_XOB102(__VA_ARGS__)
#define _HW_XOB102(o,c,i,a,r,bn,bp,...)	HW_Y0(_HW_XOB102_,_hw_isa_reg_##__VA_ARGS__)(o,c,a,r,bn,bp,__VA_ARGS__)
#define _HW_XOB102_1(o,c,a,r,bn,bp,rc,ra,wm,fm)	_m111,reg(o,r),(o,r,rc,a+ra,wm,fm,bn,bp)
#define _HW_XOB102_0(o,c,a,r,bn,bp,...)		_HW_XOB103(o,a,r,bn,bp,hw_reg_##c##_##r)
#define _HW_XOB103(...)				_HW_XOB104(__VA_ARGS__)
#define _HW_XOB104(o,a,r,bn,bp,rc,ra,wm,fm)	_m111,reg(o,r),(o,r,rc,a+ra,wm,fm,bn,bp)


#define _HW_XR_ob2	_HW_XR_or2b2

#define _HW_XR_or2b2(r,r1,bn1,bp1,vp1,r2,bn2,bp2,vp2,c,o,i,a)		\
  _HW_XR_or2b2_01(o,r,a,r1,hw_reg_##o##_##r1,bn1,bp1,vp1,r2,hw_reg_##o##_##r2,bn2,bp2,vp2)
#define _HW_XR_or2b2_01(...)				_HW_XR_or2b2_02(__VA_ARGS__)
#define _HW_XR_or2b2_02(o,r,a,r1,rc1,ra1,wm1,fm1,bn1,bp1,vp1,r2,rc2,ra2,wm2,fm2,bn2,bp2,vp2) \
  _m122,reg(o,r),(o,r1,rc1,a+ra1,wm1,fm1,bn1,bp1,vp1,r2,rc2,a+ra2,wm2,fm2,bn2,bp2,vp2)

#define _HW_XR_or1b2(s,r,bn1,bp1,vp1,bn2,bp2,vp2,c,o,i,a)	_HW_XR_or1b2_01(o,a,r,hw_reg_##o##_##r,bn1,bp1,vp1,bn2,bp2,vp2)
#define _HW_XR_or1b2_01(...)					_HW_XR_or1b2_02(__VA_ARGS__)
#define _HW_XR_or1b2_02(o,a,r,rc,ra,wm,fm,bn1,bp1,vp1,bn2,bp2,vp2)	\
  _m112,reg(o,r),(o,r,rc,a+ra,wm,fm,bn1,bp1,vp1,bn2,bp2,vp2)

#define _HW_XR_cb2(r,r1,bn1,bp1,vp1,r2,bn2,bp2,vp2,c,o,i,a)	\
  _HW_XR_or2b2_01(o,r,a,r1,hw_reg_##c##_##r1,bn1,bp1,vp1,r2,hw_reg_##c##_##r2,bn2,bp2,vp2)

//  Assume r1 == r2
#define _HW_XR_xob2(s,xo,r1,bn1,bp1,vp1,r2,bn2,bp2,vp2,c,o,i,a)		\
  _HW_XR_or1b2_01(o,a,r1,hw_reg_##xo##_##r1,bn1,bp1,vp1,bn2,bp2,vp2)

#define _HW_XR_xb2(s,xo,r,bn1,bp1,vp1,bn2,bp2,vp2,c,o,i,a)		\
  _HW_XR_or1b2_01(o,a,r,hw_reg_##xo##_##r,bn1,bp1,vp1,bn2,bp2,vp2)


/*  Follow an object path.
 *    Returns the definition of the target object as: c,o,...
 */
#define HW_XP(...)			HW_Y0(_HW_XP10_,_hw_isa_leftbkt __VA_ARGS__)(__VA_ARGS__)
#define _HW_XP10_1(...)			_HW_XP10_2( HW_XB __VA_ARGS__ )
#define _HW_XP10_2(...)			_HW_XP110( __VA_ARGS__)
#define _HW_XP10_0(...)			_HW_XP11(__VA_ARGS__,,)
//  First couple
#define _HW_XP110(...)			HW_Y0(_HW_XP10,_hw_isa_leftbkt __VA_ARGS__)(__VA_ARGS__)
#define _HW_XP101(...)			_HW_XP102( HW_XB __VA_ARGS__ )
#define _HW_XP102(...)			_HW_XP10_0( __VA_ARGS__)
#define _HW_XP100(...)			_HW_XP11(__VA_ARGS__,,)

/* #define _HW_XP11(o,x,...)		_HW_XP12(HW_OR(o,x),__VA_ARGS__) */
#define _HW_XP11(o,x,...)		HW_Y0(_HW_XP11_,_hw_isa_leftbkt x)(o,x,__VA_ARGS__)
#define _HW_XP11_0(o,x,...)		_HW_XP12(HW_OR(o,x),__VA_ARGS__)
#define _HW_XP11_1(o,x,...)		_HW_XP112(o, HW_OR x, __VA_ARGS__)
#define _HW_XP112(...)			_HW_XP113(__VA_ARGS__)
#define _HW_XP113(o,x,...)		HW_Y0(_HW_XP113,x)(o,x,__VA_ARGS__)
#define _HW_XP1131(o,z,r,e,...)		,r,e //_fake,fake,() HW_E(e)
#define _HW_XP1130(o,c,r,d,...)		_HW_XP12(HW_OR(o,r),__VA_ARGS__)

#define _HW_XP12(...)			_HW_XP13(__VA_ARGS__)
#define _HW_XP13(c,...)			HW_Y0(_HW_XP13_,c)(c,__VA_ARGS__)
#define _HW_XP13_1(...)			__VA_ARGS__ // Error
#define _HW_XP13_0(c,o,d,...)		HW_Y0(_HW_XP14_,__VA_ARGS__)(c,o,d,__VA_ARGS__)
#define _HW_XP14_1(c,o,d,...)		c,o,d // _HW_XP99(c,o,d) // Done
//  3rd arg
#define _HW_XP14_0(c,o,d,x,...)		_HW_XP21(HW_OR(o,x),__VA_ARGS__)
#define _HW_XP21(...)			_HW_XP22(__VA_ARGS__)
#define _HW_XP22(c,...)			HW_Y0(_HW_XP22_,c)(c,__VA_ARGS__)
#define _HW_XP22_1(...)			__VA_ARGS__ // Error
#define _HW_XP22_0(c,o,d,...)		HW_Y0(_HW_XP23_,__VA_ARGS__)(c,o,d,__VA_ARGS__)
#define _HW_XP23_1(c,o,d,...)		c,o,d // _HW_XP99(c,o,d) // Done
//  4th arg
#define _HW_XP23_0(c,o,d,x,...)		_HW_XP31(HW_OR(o,x),__VA_ARGS__)
#define _HW_XP31(...)			_HW_XP32(__VA_ARGS__)
#define _HW_XP32(c,...)			HW_Y0(_HW_XP32_,c)(c,__VA_ARGS__)
#define _HW_XP32_1(...)			__VA_ARGS__ // Error
#define _HW_XP32_0(c,o,d,...)		HW_Y0(_HW_XP33_,__VA_ARGS__)(c,o,d,__VA_ARGS__)
#define _HW_XP33_1(c,o,d,...)		c,o,d //_HW_XP99(c,o,d) // Done

#define _HW_XP33_0(c,o,d,...)		,o,() HW_E(too many arguments)


/*
 * @ingroup public_mac
 * @brief Returns the definition of an object from its path.
 * @hideinitializer
 *
 * Parses the path and returns the definition of the target object if it exist
 * (its class has been declared), otherwise emits an error and returns the
 * definition of the fake object so that caller won't emit other errors.
 *
 * The definition of an object has the form `class, name, ...`
 *
 * @code
 * HW_X(counter0)
 * @endcode
 *
 * @code
 * HW_X((counter0,compare0))
 * @endcode
 *
 * @code
 * HW_X((counter0,compare0,output))
 * @endcode
 *
 * @code
 * HW_X(irq(counter0,compare0))
 * @endcode
 */
/**
 * @brief Returns the definition of an object: `c,o,...`
 *
 * The argument can be:
 *   * a single object name: `o`
 *   * an object definition starting with a class name
 *   * an object path: `(o,...)`
 *   * an IRQ: `irq(o [,r])`, `irq((o,...) [,r])`
 *   * an IRQ flag: `irqflag(o [,r])`, `irqflag((o,...) [,r])`
 *   * an IRQ mask: `irqmask(o [,r])`, `irqmask((o,...) [,r])`
 *
 * A list `c,o,...` is always returned with the class in first position followed
 * by the name of the object. If an error occurs, no error is triggered but the
 * class c is set void and the error message is stored in third position..
 */
#define HW_X(...)			HW_Y0(_HW_X00_,_hw_isa_leftbkt __VA_ARGS__)(__VA_ARGS__)
#define _HW_X00_1(...)			_HW_X90( HW_XP __VA_ARGS__ )
#define _HW_X00_0(...)			HW_Y0(_HW_X01_,hw_class_##__VA_ARGS__)(__VA_ARGS__)
#define _HW_X01_1(...)			__VA_ARGS__
#define _HW_X01_0(...)			_HW_X01((__VA_ARGS__),_HW_X_##__VA_ARGS__)

#define _HW_X01(...)			_HW_X02(__VA_ARGS__ )
#define _HW_X02(va,...)			HW_Y0(_HW_X02_,__VA_ARGS__)(va,__VA_ARGS__)
#define _HW_X02_1(va,z,...)		_HW_X90( __VA_ARGS__ )
#define _HW_X02_0(va,...)		_HW_X90( HW_XP va )

#define _HW_X90(...)			_HW_X91(__VA_ARGS__)
#define _HW_X91(c,o,...)		HW_Y0(_HW_X91_,_hw_isa_leftbkt __VA_ARGS__)(c,o,__VA_ARGS__)
#define _HW_X91_1(c,o,...)		_HW_X91_0(c,o,HW_XB __VA_ARGS__)
#define _HW_X91_0(...)			__VA_ARGS__

#define _HW_X_reg			, HW_XREG
#define _HW_X_irq			, HW_XIRQ
#define _HW_X_irqflag			, HW_XIRQFLAG
#define _HW_X_irqmask			, HW_XIRQMASK
#define _HW_X_xo			, HW_X_XO

/*  Expand the definition of a register.
 */
#define HW_XREG(...)			_HW_XREG01(__VA_ARGS__,)
#define _HW_XREG01(o,...)		_HW_XREG02(HW_XP(o),__VA_ARGS__)
#define _HW_XREG02(...)			_HW_XREG03(__VA_ARGS__)
#define _HW_XREG03(c,...)		HW_Y0(_HW_XREG03_,c)(c,__VA_ARGS__,)
#define _HW_XREG03_1(c,o,...)		,o,__VA_ARGS__	// Error: object not found
#define _HW_XREG03_0(c,o,d,r,...)	_HW_OR21(c,o,d,r,hw_reg_##o##_##r)

/* Expand the definition of an IRQ: _irq, irq(o,r), n, v, m, f
 *   The first arg must be an object name or an object path
 *   One optionnal interrupt name may follow
 */
#define HW_XIRQ(...)			_HW_XIRQ01(__VA_ARGS__,)
#define _HW_XIRQ01(o,...)		_HW_XIRQ02(HW_XP(o),__VA_ARGS__)
#define _HW_XIRQ02(...)			_HW_XIRQ03(__VA_ARGS__)
#define _HW_XIRQ03(c,...)		HW_Y0(_HW_XIRQ03_,c)(c,__VA_ARGS__,)
#define _HW_XIRQ03_1(c,o,...)		,irq(o),__VA_ARGS__	// Error: object not found
#define _HW_XIRQ03_0(c,o,d,r,...)	_HW_XIRQ04(o,r,hw_irq_##o##_##r,__VA_ARGS__)
#define _HW_XIRQ04(...)			_HW_XIRQ05(__VA_ARGS__)
#define _HW_XIRQ05(o,r,x,...)		HW_Y0(_HW_XIRQ05_,_hw_is_irq##x)(o,r,x,__VA_ARGS__)
#define _HW_XIRQ05_0(o,r,...)		,irq(o,r),HW_EM_IRQ((o,r))	// Error: no such IRQ
#define _HW_XIRQ05_1(o,r,c,n,v,m,f,...)	HW_Y0(_HW_XIRQ06_,__VA_ARGS__)(o,r,c,n,v,m,f,__VA_ARGS__)
#define _HW_XIRQ06_0(o,r,c,n,v,m,f,...)	,irq(o,r),HW_EM_G(HW_A0(__VA_ARGS__))	// Error: garbage
#define _HW_XIRQ06_1(o,r,c,n,v,m,f,...)	_irq,irq(o,r),n,v,m,f	// Success

/*  Expand the definition of an IRQ flag.
 */
#define HW_XIRQFLAG(...)		_HW_XIRQF01( HW_XIRQ(__VA_ARGS__) )
#define _HW_XIRQF01(...)		_HW_XIRQF02(__VA_ARGS__)
#define _HW_XIRQF02(c,...)		HW_Y0(_HW_XIRQF02_,c)(c,__VA_ARGS__)
#define _HW_XIRQF02_1(c,o,...)		,irqflag(o),__VA_ARGS__	// Error
#define _HW_XIRQF02_0(c,o,n,v,m,f)	_HW_X90( HW_XP(n,f) )

/*  Expand the definition of an IRQ mask.
 */
#define HW_XIRQMASK(...)		_HW_XIRQM01( HW_XIRQ(__VA_ARGS__) )
#define _HW_XIRQM01(...)		_HW_XIRQM02(__VA_ARGS__)
#define _HW_XIRQM02(c,...)		HW_Y0(_HW_XIRQM02_,c)(c,__VA_ARGS__)
#define _HW_XIRQM02_1(c,o,...)		,irqmask(o),__VA_ARGS__	// Error
#define _HW_XIRQM02_0(c,o,n,v,m,f)	_HW_X90( HW_XP(n,m) )

/*  Expand the definition of an external object
 */
#define HW_X_XO(...)			__VA_ARGS__
