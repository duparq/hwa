
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*  These macros expand the `object argument`.
 *  See HW_X() below.
 */


/*  Return the definition of o as a triplet: c,o,(d).
 *  or ,o,"error message" if o is not an object.
 */
#define HW_XO(o)			_HW_XO01(o,hw_##o)
#define _HW_XO01(...)			_HW_XO02(__VA_ARGS__)
#define _HW_XO02(o,...)			HW_Y0(_HW_XO02,hw_class_##__VA_ARGS__)(o,__VA_ARGS__)
#define _HW_XO021(o,c,...)		c,o,(__VA_ARGS__)
#define _HW_XO020(o,...)		HW_Y0(_HW_XO020,o)(o)
#define _HW_XO0200(o)			,o,HW_EM_O(o)
#define _HW_XO0201(o)			,o,HW_EM_OM(o)


/*  Return the definition of the relative x of object o as a triplet: `c,(o,x),(d)`
 *    Return `,o,error message` if the relative can not be found.
 *    Return `(),,` if the definition is a path to another object
 *    Convert register definitions to memory definitions (a register has no relatives).
 */
/*
 *  1. If x is void, return the definition of o.
 */
#define HW_OX(o,x)			HW_Y(_HW_OX0_,x)(o,x)
#define _HW_OX0_1(o,...)		HW_XO(o)
/*
 *  2. Object relative. Assume that o is an object name.
 */
#define _HW_OX0_0(o,x)			_HW_OX02(o,x,hw_##o##_##x)
#define _HW_OX02(...)			_HW_OX03(__VA_ARGS__)
/*
 *     If the expansion of hw_o_x starts with left bracket, return it as is (...),,
 */
#define _HW_OX03(o,x,...)		HW_Y0(_HW_OX1_,_hw_isa_leftbkt __VA_ARGS__)(o,x,__VA_ARGS__)
#define _HW_OX1_1(o,x,...)		__VA_ARGS__,,
/*
 *     If the expansion of hw_o_x starts with a class name, return the definition: c,(o,x),(...)
 */  
#define _HW_OX1_0(o,x,...)		HW_Y0(_HW_OX2_,hw_class_##__VA_ARGS__)(o,x,__VA_ARGS__)
/*
 *     hw_o_x starts with a class name.
 */
#define _HW_OX2_1(o,x,c,...)		HW_Y0(_HW_OX3_,_hw_isa_reg_##c)(o,x,c,__VA_ARGS__)
/*
 *     hw_o_x is a definition of an object.
 */
//#define _HW_OX3_0(o,x,c,...)		c,o,(__VA_ARGS__)
#define _HW_OX3_0(o,x,c,...)		c,o##_##x,(__VA_ARGS__)

/*
 *     hw_o_x is a register. We need the definition of its holder. Return the definition of the reg.
 */
#define _HW_OX3_1(o,...)		_HW_OX32((o,__VA_ARGS__),hw_##o)
#define _HW_OX32(...)			_HW_OX33(__VA_ARGS__)
#define _HW_OX33(va,c,...)		_HW_OX34(c,(__VA_ARGS__),HW_XB va)
#define _HW_OX34(...)			_HW_OX35(__VA_ARGS__)
#define _HW_OX35(c,d,o,x,xc,...)	_HW_OXR(xc,x,__VA_ARGS__,c,o,HW_XB d)
/*
 *  3. If the expansion of hw_o_x is the name of an object o2, return the definition: c2,o2,(...)
 */
#define _HW_OX2_0(o,x,o2)		_HW_OX22(o,x,HW_XO(o2))
#define _HW_OX22(...)			_HW_OX23(__VA_ARGS__)
#define _HW_OX23(o,x,c2,...)		HW_Y0(_HW_OX4_,c2)(o,x,c2,__VA_ARGS__)
#define _HW_OX4_0(o,x,...)		__VA_ARGS__ // The definition of o2
/*
 *  4. Look for a class relative.
 *     Get the class name from the definition of o: c,o,d
 */
#define _HW_OX4_1(o,x,...)		_HW_OX42(HW_XO(o),x)
#define _HW_OX42(...)			_HW_OX43(__VA_ARGS__)
#define _HW_OX43(c,...)			HW_Y0(_HW_OX5_,c)(c,__VA_ARGS__)
#define _HW_OX5_1(c,o,d,...)		,o,d //__VA_ARGS__ // Error: o is not an object
/*
 *  5. Expand hw_c_x
 */
#define _HW_OX5_0(c,o,d,x)		_HW_OX52(c,o,d,x,hw_##c##_##x)
#define _HW_OX52(...)			_HW_OX53(__VA_ARGS__)
/*
 *     If the expansion of hw_c_x starts with a void, return the expansion of a function
 */
#define _HW_OX53(c,o,d,x,...)		HW_Y0(_HW_OX6_,__VA_ARGS__)(c,o,d,x,__VA_ARGS__)
#define _HW_OX6_1(c,o,d,x,z,f)		_HW_OX62(f,o,HW_XB d)
#define _HW_OX62(f,...)			_HW_OX63(f(__VA_ARGS__)) // Expand f( o, ...d... )
#define _HW_OX63(...)			_HW_OX6_0(__VA_ARGS__)
/*
 *     If the expansion of hw_c_x starts with a class name, return this.
 *       The expansion of hw_c_x can be a single name (check for a register first)
 */
#define _HW_OX6_0(c,o,d,x,...)		HW_Y0(_HW_OX7_,hw_class_##__VA_ARGS__)(c,o,d,x,__VA_ARGS__)
#define _HW_OX7_0(c,o,d,x,y)		_HW_OX72(c,o,d,x,y,hw_##c##_##y)
#define _HW_OX72(...)			_HW_OX73(__VA_ARGS__)
#define _HW_OX73(c,o,d,x,y,...)		HW_Y0(_HW_OX9_,_hw_isa_reg_##__VA_ARGS__)(c,o,d,x,y,__VA_ARGS__)
#define _HW_OX9_1(c,o,d,x,y,cx,...)	_HW_OXR(cx,y,__VA_ARGS__,c,o,HW_XB d)
#define _HW_OX9_0(c,o,d,x,y,...)	HW_Y0(_HW_OXA_,hw_class_##y)(c,o,d,x,y,__VA_ARGS__)
#define _HW_OXA_0(c,o,d,x,y,...)	,(o,x),o has no relative x
#define _HW_OXA_1(c,o,d,x,y,...)	y,(o,x),__VA_ARGS__
/*
 *       If it is a register, return its memory definition.
 */
#define _HW_OX7_1(c,o,d,x,cx,...)	HW_Y0(_HW_OX8_,_hw_isa_reg_##cx)(c,o,d,x,cx,__VA_ARGS__)
#define _HW_OX8_0(c,o,d,x,...)		__VA_ARGS__
#define _HW_OX8_1(c,o,d,x,cx,...)	_HW_OXR(cx,x,__VA_ARGS__,c,o,HW_XB d)

/*
 *  Convert a register definition to a memory definitions:
 *   * _m111,(o,r),(o,r,rc,a,wm,fm,bn,bp)
 *   * _m112,(o,r),(o,r,rc,a,wm,fm,bn1,bp1,vp1,bn2,bp2,vp2)
 *   * _m122,(o,r),(o,r1,rc1,a1,wm1,fm1,bn1,bp1,vp1,r2,rc2,a2,wm2,fm2,bn2,bp2,vp2)
 */
#define _HW_OXR(...)			_HW_OXR2(__VA_ARGS__)
#define _HW_OXR2(rc,...)		_HW_OXR##rc(__VA_ARGS__)

#define _HW_OXR_r8(r,ra,rwm,rfm,c,o,a)	_m111,(o,r),(o,r,_r8,a+ra,rwm,rfm,8,0)
#define _HW_OXR_r16(r,ra,rwm,rfm,c,o,a)	_m111,(o,r),(o,r,_r16,a+ra,rwm,rfm,16,0)
#define _HW_OXR_r32(r,ra,rwm,rfm,c,o,a)	_m111,(o,r),(o,r,_r32,a+ra,rwm,rfm,32,0)

#define _HW_OXR_ob1(s,r,bn,bp,c,o,a)	_HW_OXR_ob1_01(o,a,r,hw_##o##_##r,bn,bp)
#define _HW_OXR_ob1_01(...)		_HW_OXR_ob1_02(__VA_ARGS__)
#define _HW_OXR_ob1_02(o,a,r,rc,ra,...)	_m111,(o,r),(o,r,rc,a+ra,__VA_ARGS__)

#define _HW_OXR_cb1(s,r,bn,bp,c,o,a)	_HW_OXR_ob1_01(o,a,r,hw_##c##_##r,bn,bp)

#define _HW_OXR_xob1(s,xo,xr,bn,bp,...)			_HW_OXR_xob1_01(xo,hw_##xo,xr,bn,bp,hw_##xo##_##xr)
#define _HW_OXR_xob1_01(...)				_HW_OXR_xob1_02(__VA_ARGS__)
#define _HW_OXR_xob1_02(o,c,a,r,bn,bp,...)		HW_Y0(_HW_OXR_xob1_02_,_hw_isa_reg_##__VA_ARGS__)(o,c,a,r,bn,bp,__VA_ARGS__)
#define _HW_OXR_xob1_02_1(o,c,a,r,bn,bp,rc,ra,wm,fm)	_m111,(o,r),(o,r,rc,a+ra,wm,fm,bn,bp)
#define _HW_OXR_xob1_02_0(o,c,a,r,bn,bp,...)		_HW_OXR_xob1_03(o,a,r,bn,bp,hw_##c##_##r)
#define _HW_OXR_xob1_03(...)				_HW_OXR_xob1_04(__VA_ARGS__)
#define _HW_OXR_xob1_04(o,a,r,bn,bp,rc,ra,wm,fm)		_m111,(o,r),(o,r,rc,a+ra,wm,fm,bn,bp)

#define _HW_OXR_ob2(r,r1,bn1,bp1,vp1,r2,bn2,bp2,vp2,c,o,a)		\
  _HW_OXR_ob2_01(o,r,a,r1,hw_##o##_##r1,bn1,bp1,vp1,r2,hw_##o##_##r2,bn2,bp2,vp2)
#define _HW_OXR_ob2_01(...)				_HW_OXR_ob2_02(__VA_ARGS__)
#define _HW_OXR_ob2_02(o,r,a,r1,rc1,ra1,wm1,fm1,bn1,bp1,vp1,r2,rc2,ra2,wm2,fm2,bn2,bp2,vp2) \
  _m122,(o,r),(o,r1,rc1,a+ra1,wm1,fm1,bn1,bp1,vp1,r2,rc2,a+ra2,wm2,fm2,bn2,bp2,vp2)

#define _HW_OXR_cb2(r,r1,bn1,bp1,vp1,r2,bn2,bp2,vp2,c,o,a)	\
  _HW_OXR_ob2_01(o,r,a,r1,hw_##c##_##r1,bn1,bp1,vp1,r2,hw_##c##_##r2,bn2,bp2,vp2)

//  Assume r1 == r2
#define _HW_OXR_xob2(s,xo,r1,bn1,bp1,vp1,r2,bn2,bp2,vp2,c,o,a)		\
  _HW_OXR_xob2_01(o,a,r1,hw_##xo##_##r1,bn1,bp1,vp1,bn2,bp2,vp2)
#define _HW_OXR_xob2_01(...)					_HW_OXR_xob2_02(__VA_ARGS__)
#define _HW_OXR_xob2_02(o,a,r,rc,ra,wm,fm,bn1,bp1,vp1,bn2,bp2,vp2)	\
  _m112,(o,r),(o,r,rc,a+ra,wm,fm,bn1,bp1,vp1,bn2,bp2,vp2)


/*  Follow an object path.
 *    Return the definition of the target object as a triplet: c,o,d
 *
 *  1. If the path is in brackets, remove them.
 */
#define HW_XP(...)			HW_Y0(_HW_XP01_,_hw_isa_leftbkt __VA_ARGS__)(__VA_ARGS__)
#define _HW_XP01_0(...)			_HW_XP11(__VA_ARGS__,,)
#define _HW_XP01_1(...)			_HW_XP02( HW_XB __VA_ARGS__ )
#define _HW_XP02(...)			_HW_XP03( __VA_ARGS__)
/*
 *  2. If the first arg is in brackets, remove them.
 */
#define _HW_XP03(...)			HW_Y0(_HW_XP03_,_hw_isa_leftbkt __VA_ARGS__)(__VA_ARGS__)
#define _HW_XP03_0(...)			_HW_XP11(__VA_ARGS__,,)
#define _HW_XP03_1(...)			_HW_XP04( HW_XB __VA_ARGS__ )
#define _HW_XP04(...)			_HW_XP11( __VA_ARGS__,,)
/*
 *  3. If the second arg is a path (in brackets), expand it.
 */
#define _HW_XP11(o,x,...)		HW_Y0(_HW_XP11_,_hw_isa_leftbkt x)(o,x,__VA_ARGS__)
#define _HW_XP11_0(o,x,...)		_HW_XP22(HW_OX(o,x),__VA_ARGS__)
#define _HW_XP11_1(o,x,...)		_HW_XP12(o, HW_OX x, __VA_ARGS__)
#define _HW_XP12(...)			_HW_XP13(__VA_ARGS__)
#define _HW_XP13(o,c,...)		HW_Y0(_HW_XP19_,c)(o,c,__VA_ARGS__)
#define _HW_XP19_1(o,z,r,e,...)		,r,e // Error
/*
 *  2nd arg.
 */
#define _HW_XP19_0(o,c,x,d,...)		_HW_XP22(HW_OX(o,x),__VA_ARGS__)

#define _HW_XP22(...)			_HW_XP23(__VA_ARGS__)
#define _HW_XP23(c,...)			HW_Y0(_HW_XP23_,c)(c,__VA_ARGS__)
#define _HW_XP23_1(...)			__VA_ARGS__ // Error
#define _HW_XP23_0(c,o,d,...)		HW_Y0(_HW_XP29_,__VA_ARGS__)(c,o,d,__VA_ARGS__)
#define _HW_XP29_1(c,o,d,...)		c,o,d
/*
 *  3rd arg.
 */
#define _HW_XP29_0(c,o,d,x,...)		_HW_XP31(HW_OX(o,x),__VA_ARGS__)
#define _HW_XP31(...)			_HW_XP32(__VA_ARGS__)
/*
 *     If the result of the expansion is a path, expand it again.
 */
#define _HW_XP32(c,...)			HW_Y0(_HW_XP32_,_hw_isa_leftbkt c)(c,__VA_ARGS__)
#define _HW_XP32_1(c,...)		_HW_XP33(HW_OX c,__VA_ARGS__)
#define _HW_XP33(...)			_HW_XP32_0(__VA_ARGS__)
#define _HW_XP32_0(c,...)		HW_Y0(_HW_XP33_,c)(c,__VA_ARGS__)
#define _HW_XP33_1(...)			__VA_ARGS__ // Error
#define _HW_XP33_0(c,o,d,...)		HW_Y0(_HW_XP39_,__VA_ARGS__)(c,o,d,__VA_ARGS__)
#define _HW_XP39_1(c,o,d,...)		c,o,d
/*
 *  4th arg
 */
#define _HW_XP39_0(c,o,d,x,...)		_HW_XP41(HW_OX(o,x),__VA_ARGS__)
#define _HW_XP41(...)			_HW_XP42(__VA_ARGS__)
#define _HW_XP42(c,...)			HW_Y0(_HW_XP42_,c)(c,__VA_ARGS__)
#define _HW_XP42_1(...)			__VA_ARGS__ // Error
#define _HW_XP42_0(c,o,d,...)		HW_Y0(_HW_XP43_,__VA_ARGS__)(c,o,d,__VA_ARGS__)
#define _HW_XP43_1(c,o,d,...)		c,o,d
#define _HW_XP43_0(c,o,d,...)		,o,() HW_E(too many arguments)


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

/* Returns the definition of an object: `c,o,...`
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
/*  1. If the args start with a left bracket, expand the path. End.
 *  2. If the args start with with a class name, return them as is. End.
 *  3. If the args start with a keyword (reg, irq...), use the corresponding macro HW_X_... . End.
 *  4. Expand the path. End.
 */
#define HW_X(...)			HW_Y0(_HW_X00_,_hw_isa_leftbkt __VA_ARGS__)(__VA_ARGS__)
#define _HW_X00_1(...)			_HW_X09( HW_XP __VA_ARGS__ )
#define _HW_X00_0(...)			HW_Y0(_HW_X01_,hw_class_##__VA_ARGS__)(__VA_ARGS__)
#define _HW_X01_1(...)			__VA_ARGS__
#define _HW_X01_0(...)			_HW_X01((__VA_ARGS__),_HW_X_##__VA_ARGS__)
#define _HW_X01(...)			_HW_X02(__VA_ARGS__ )
#define _HW_X02(va,...)			HW_Y0(_HW_X02_,__VA_ARGS__)(va,__VA_ARGS__)
#define _HW_X02_1(va,z,...)		_HW_X09( __VA_ARGS__ )
#define _HW_X02_0(va,...)		_HW_X09( HW_XP va )
/*
 *  End of the expansion. 3 arguments: c, o, d.
 *  If brackets around the definition (d), remove them.
 */
#define _HW_X09(...)			_HW_X0A(__VA_ARGS__)
#define _HW_X0A(c,o,...)		HW_Y0(_HW_X09_,_hw_isa_leftbkt __VA_ARGS__)(c,o,__VA_ARGS__)
#define _HW_X09_1(c,o,...)		_HW_X09_0(c,o,HW_XB __VA_ARGS__)
#define _HW_X09_0(...)			__VA_ARGS__


#define _HW_X_irq			, HW_XIRQ
#define _HW_X_irqflag			, HW_XIRQFLAG
#define _HW_X_irqmask			, HW_XIRQMASK
#define _HW_X_xb			, HW_XB /* just remove brackets */

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
#define _HW_XIRQF02_0(c,o,n,v,m,f)	HW_OX(n,f)

/*  Expand the definition of an IRQ mask.
 */
#define HW_XIRQMASK(...)		_HW_XIRQM01( HW_XIRQ(__VA_ARGS__) )
#define _HW_XIRQM01(...)		_HW_XIRQM02(__VA_ARGS__)
#define _HW_XIRQM02(c,...)		HW_Y0(_HW_XIRQM02_,c)(c,__VA_ARGS__)
#define _HW_XIRQM02_1(c,o,...)		,irqmask(o),__VA_ARGS__	// Error
#define _HW_XIRQM02_0(c,o,n,v,m,f)	HW_OX(n,m)
