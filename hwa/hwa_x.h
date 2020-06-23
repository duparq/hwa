

/*  Expand the definition of object register r of object o.
 *    No error checking. r must be a register of object o, not a class register.
 */
#define HW_XOR(o,r)			_HW_XOR1(r,hw_##o##_##r,o,hw_##o)
#define _HW_XOR1(...)			_HW_XOR2(__VA_ARGS__)
#define _HW_XOR2(r,rc,ra,rwm,rfm,o,c,a)	HW_OXR(rc,r,ra,rwm,rfm,c,o,a)


/*
 *  Convert a register definition to a memory definitions:
 *   * _m111,(o,r),(o,r,rc,a,wm,fm,bn,bp)
 *   * _m112,(o,r),(o,r,rc,a,wm,fm,bn1,bp1,vp1,bn2,bp2,vp2)
 *   * _m122,(o,r),(o,r1,rc1,a1,wm1,fm1,bn1,bp1,vp1,r2,rc2,a2,wm2,fm2,bn2,bp2,vp2)
 */
#define HW_OXR(...)			_HW_OXR2(__VA_ARGS__)
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
#define _HW_OXR_xob1_02(o,c,a,r,bn,bp,...)		_HW_B(_HW_OXR_xob1_02_,_hw_isa_reg_##__VA_ARGS__)(o,c,a,r,bn,bp,__VA_ARGS__)
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



/*  Get the definition of an object named 'o' as a triplet: c,o,(d).
 *  or ,o,"error message" if o is not an object.
 */
#define HW_XO(o)			_HW_XO01(o,hw_##o)
#define _HW_XO01(...)			_HW_XO02(__VA_ARGS__)
#define _HW_XO02(o,...)			_HW_B(_HW_XO02,hw_class_##__VA_ARGS__)(o,__VA_ARGS__)
#define _HW_XO021(o,c,...)		c,o,(__VA_ARGS__)
#define _HW_XO020(o,...)		_HW_B(_HW_XO020,o)(o)
#define _HW_XO0200(o)			,o,HW_EM_O(o)	/* o is not the name of an object */
#define _HW_XO0201(o)			,o,HW_EM_OM(o)	/* object name missing */


/*  Get the definition of the relative r of object o as a triplet: 'c,o_r,(d)' or 'c,(o,r),(d)'
 *    Return ',o,error message' if the relative can not be found.
 *    Register definitions are converted to memory definitions.
 */
#define HW_CODR(c,o,...)		_HW_B(_HW_CODR_,_hw_par o)(c,o,__VA_ARGS__)
#define _HW_CODR_1(c,o,d,r)		_HW_CODR2(c,o,d,r,hw_##c##_##r)	// Can not compute o_r since o is ()
#define _HW_CODR_0(c,o,d,r)		_HW_B(_HW_CODR0_,_hw_par r)(c,o,d,r)
#define _HW_CODR0_1(c,o,d,r)		_HW_CODR6(c,o,d,r,hw_##c##_)	// Can not compute o_r since r is ()
#define _HW_CODR0_0(c,o,d,r)		_HW_CODR0(c,o,d,r,hw_##o##_##r)
#define _HW_CODR0(...)			_HW_CODR1(__VA_ARGS__)
#define _HW_CODR1(c,o,d,r,...)		_HW_B(_HW_CODR1_,hw_class_##__VA_ARGS__)(c,o,d,r,__VA_ARGS__)
/*
 *  hw_o_r is a definition.
 */
#define _HW_CODR1_1(c,o,d,r,...)	_HW_B(_HW_CODR10_,_hw_isa_reg_##__VA_ARGS__)(c,o,d,r,__VA_ARGS__)
/*
 *  hw_o_r is not a register. Return the definition.
 */
#define _HW_CODR10_0(c,o,d,r,x,...)	x,o##_##r,(__VA_ARGS__)
/* #define _HW_CODR10_0(c,o,d,r,x,...)	x,(o,r),(__VA_ARGS__) */
/*
 *  hw_o_r is a register. Return the memory definition.
 */
#define _HW_CODR10_1(c,o,d,r,cr,...)	HW_OXR(cr,r,__VA_ARGS__,c,o,HW_RP d)
/*
 *  x is a not a class, is it the name of an object?
 */
#define _HW_CODR1_0(c,o,d,r,x)		_HW_CODR10(c,o,d,r,HW_XO(x),)
#define _HW_CODR10(...)			_HW_CODR11(__VA_ARGS__)
#define _HW_CODR11(c,o,d,r,x,...)	_HW_B(_HW_CODR11_,hw_class_##x)(c,o,d,r,x,__VA_ARGS__)
/*
 *  hw_o_r is the name of an object. Return its definition.
 */
#define _HW_CODR11_1(c,o,d,r,oc,oo,od,...)	oc,oo,od
/*
 *  hw_o_r is not the name of an object. Try hw_c_r.
 */
#define _HW_CODR11_0(c,o,d,r,...)	_HW_CODR2(c,o,d,r,hw_##c##_##r)
#define _HW_CODR2(...)			_HW_CODR3(__VA_ARGS__)
#define _HW_CODR3(c,o,d,r,...)		_HW_B(_HW_CODR3_,__VA_ARGS__)(c,o,d,r,__VA_ARGS__)
/*
 *  hw_c_r is void -> delegate to the provided function
 */
#define _HW_CODR3_1(c,o,d,r,z,f)	_HW_CODR4(f,o,HW_RP d)
#define _HW_CODR4(f,...)		_HW_CODR5(f(__VA_ARGS__))
#define _HW_CODR5(...)			__VA_ARGS__
/*
 *  hw_c_r is not void. FIXME: remove this when its known that it will never be used.
 */
#define _HW_CODR3_0(c,o,d,r,...)	_HW_B(_HW_CODR4_,_hw_par __VA_ARGS__)(c,o,d,r,__VA_ARGS__)
#define _HW_CODR4_1(c,o,d,r,...)	,(o,r),internal error: expanding () is not implemented [_HW_CODR4_1]
/*
 *  hw_c_r is a word.
 */
#define _HW_CODR4_0(c,o,d,r,...)	_HW_B(_HW_CODR5_,_hw_isa_reg_##__VA_ARGS__)(c,o,d,r,__VA_ARGS__)
/*
 *  hw_c_r is a register
 *    Convert the register definition to a memory definition.
 */
#define _HW_CODR5_1(c,o,d,r,cr,...)	HW_OXR(cr,r,__VA_ARGS__,c,o,HW_RP d)
/*
 *  hw_c_r is not a register, try a function hw_c_
 */
#define _HW_CODR5_0(c,o,d,r,...)	_HW_CODR6(c,o,d,r,hw_##c##_)
#define _HW_CODR6(...)			_HW_CODR7(__VA_ARGS__)
#define _HW_CODR7(c,o,d,r,...)		_HW_B(_HW_CODR7_,__VA_ARGS__)(c,o,d,r,__VA_ARGS__)
/*
 *  hw_c_ is a function that would provide class relatives
 */
#define _HW_CODR7_1(c,o,d,r,z,f)	_HW_CODR8(f,o,r,HW_RP d)
#define _HW_CODR8(f,...)		_HW_CODR9(f(__VA_ARGS__))
#define _HW_CODR9(...)			__VA_ARGS__

#define _HW_CODR7_0(c,o,d,r,...)	,o,o has no relative r


//HW_CODR(_oca,counter0_compare0,(counter0, 0),pin);
//HW_CODR(_swuarta,swuart_pb0pa1,((portb,0),(porta,1),(counter0,compare0),1),txd)
//HW_CODR(_swuarta,swuart_pb0pa1,((portb,0),(porta,1),(counter0,compare0),1),txd)


/*  Compute the beginning of a path: o
 */
#define HW_XS(x,...)			_HW_B(_HW_XS1_,_hw_par x)(x,__VA_ARGS__)
#define _HW_XS1_1(...)			_HW_XS1_2( HW_RP __VA_ARGS__ )		// Remove parentheses
#define _HW_XS1_2(...)			_HW_XS1_3(__VA_ARGS__ )
#define _HW_XS1_3(x,...)		_HW_B(_HW_XS2_,_hw_par x)(x,__VA_ARGS__)
#define _HW_XS2_1(x,...)		,o,two many parentheses in path before (__VA_ARGS__) [HW_XS2_1],__VA_ARGS__
#define _HW_XS2_0(x,...)		HW_B(_HW_XS3_,hw_class_##x)(x,__VA_ARGS__)

#define _HW_XS1_0(x,...)		HW_B(_HW_XS3_,hw_class_##x)(x,__VA_ARGS__)
#define _HW_XS3_0(x,...)		_HW_XS3_1( HW_XO(x), __VA_ARGS__ )	// Element 1 is a word, process it
#define _HW_XS3_1(...)			__VA_ARGS__


/*  Compute the concatenation of c,o,(d) with x.
 *  Put the resulting definition or ',o,error message' in c,o,(d).
 *  FIXME: is it useful to process parentheses around x?
 *  FIXME: is it useful to process concatenation of x being a c,o,(d)?
 */
/* #define HW_XC(c,o,d,x,...)		HW_B(_HW_XC_,_hw_par x)(c,o,d,x,__VA_ARGS__) */
/* #define _HW_XC_1(c,o,d,x,...)		_HW_XC2(c,o,d,HW_XS x,__VA_ARGS__ ) */
/* #define _HW_XC2(...)			_HW_XC3_0(__VA_ARGS__) */
/* #define _HW_XC_0(c,o,d,x,...)		HW_B(_HW_XC3_,x)(c,o,d,x,__VA_ARGS__) */
/* #define _HW_XC3_1(c,o,d,z,o2,e,...)	,o2,e */
/* #define _HW_XC3_0(c,o,d,x,...)		HW_B(_HW_XC4_,hw_class_##x)(c,o,d,x,__VA_ARGS__) */
/* #define _HW_XC4_0(c,o,d,r,...)		_HW_XC5( HW_CODR(c,o,d,r), __VA_ARGS__ ) */
/* #define _HW_XC4_1(c,o,d,c2,r,d2,...)	_HW_XC5( HW_CODR(c,o,d,r), __VA_ARGS__ ) */
/* #define _HW_XC5(...)			__VA_ARGS__ */


/*  Parse an object path to return the definition with the format: c,o,...
 *  Up to 5 elements can be put in the path.
 *
 *  First element can be:
 *    * a single word: `o`
 *    * a definition: c,o,(d)
 *    * a path: (...)
 *  following elements must be object names.
 *
 *  If an error occurs, ',o,error message' is returned.
 */
#define HW_X(...)			_HW_X0(__VA_ARGS__,,,,)			// Ensure at least 5 arguments

#define _HW_X0(x,...)			_HW_B(_HW_X0_,_hw_par x)(x,__VA_ARGS__)
#define _HW_X0_1(...)			_HW_X0_2( HW_RP __VA_ARGS__ )		// Remove parentheses
#define _HW_X0_2(...)			_HW_X0_0(__VA_ARGS__ )

#define _HW_X0_0(...)			_HW_X0_3( HW_XS(__VA_ARGS__) )		// Element 1: starter
#define _HW_X0_3(...)			_HW_X0_4( __VA_ARGS__)
#define _HW_X0_4(x,...)			_HW_B(_HW_X1_,x)(x,__VA_ARGS__)
#define _HW_X1_1(c,o,d,...)		_HW_X9(c,o,d)

#define _HW_X1_0(c,o,d,x,...)		HW_B(_HW_X2_,x)(c,o,d,x,__VA_ARGS__)	// Element 2
#define _HW_X2_1(c,o,d,...)		_HW_X9(c,o,d)
#define _HW_X2_0(c,o,d,r,...)		_HW_X2_2( HW_CODR(c,o,d,r), __VA_ARGS__ )
#define _HW_X2_2(...)			_HW_X3(__VA_ARGS__)

#define _HW_X3(c,o,d,x,...)		HW_B(_HW_X3_,x)(c,o,d,x,__VA_ARGS__)	// Element 3
#define _HW_X3_1(c,o,d,...)		_HW_X9(c,o,d)
#define _HW_X3_0(c,o,d,r,...)		_HW_X3_2( HW_CODR(c,o,d,r), __VA_ARGS__ )
#define _HW_X3_2(...)			_HW_X4(__VA_ARGS__)

#define _HW_X4(c,o,d,x,...)		HW_B(_HW_X4_,x)(c,o,d,x,__VA_ARGS__)	// Element 4
#define _HW_X4_1(c,o,d,...)		_HW_X9(c,o,d)
#define _HW_X4_0(c,o,d,r,...)		_HW_X4_2( HW_CODR(c,o,d,r), __VA_ARGS__ )
#define _HW_X4_2(...)			_HW_X5(__VA_ARGS__)

#define _HW_X5(c,o,d,x,...)		HW_B(_HW_X5_,x)(c,o,d,x,__VA_ARGS__)	// Element 5
#define _HW_X5_1(c,o,d,...)		_HW_X9(c,o,d)
#define _HW_X5_0(c,o,d,r,...)		_HW_X5_2( HW_CODR(c,o,d,r), __VA_ARGS__ )
#define _HW_X5_2(...)			_HW_X6(__VA_ARGS__)

#define _HW_X6(c,o,d,x,...)		HW_B(_HW_X6_,x)(c,o,d,x,__VA_ARGS__)	// End
#define _HW_X6_1(c,o,d,...)		_HW_X9(c,o,d)
#define _HW_X6_0(c,o,d,x,...)		,o,HW_EM(too many elements in path starting from x) [_HW_X6_0]

#define _HW_X9(c,o,d)			_HW_B(_HW_X9_,_hw_par d)(c,o,d)
#define _HW_X9_1(c,o,d)			_HW_X9_0(c,o,HW_RP d)
#define _HW_X9_0(...)			__VA_ARGS__


/*  Expand an object path, remove void arguments from definition.
 *    This is used for example to get the "putchar" function name of a LCD:
 *      HW(LCD,putchar)
 */
#define HW(...)				_HW_1( HW_X(__VA_ARGS__) )
#define _HW_1(...)			_HW_2(__VA_ARGS__)
#define _HW_2(c,o,...)			_HW_B(_HW_2,o)(c,o,__VA_ARGS__)
#define _HW_20(...)			__VA_ARGS__
#define _HW_21(c,o,...)			c


/*  Return the mask register of an _irq.
 *  Can not use HW_CODR since it's blued.
 */
#define hw__irq_mask			, _hw_irqm
#define _hw_irqm(oo,v,o,m,f)		_hw_irqm1(o,hw_##o,hw_##o##_##m)
#define _hw_irqm1(...)			_hw_irqm2(__VA_ARGS__)
#define _hw_irqm2(o,c,a,rc,...)		HW_OXR(rc,,__VA_ARGS__,c,o,a)

#define hw__irq_flag			, _hw_irqf
#define _hw_irqf(oo,v,o,m,f)		_hw_irqf1(o,hw_##o,hw_##o##_##f)
#define _hw_irqf1(...)			_hw_irqf2(__VA_ARGS__)
#define _hw_irqf2(o,c,a,rc,...)		HW_OXR(rc,,__VA_ARGS__,c,o,a)

#define hw__irq_			, _hw_irq_
#define _hw_irq_(oo,r,v,o,m,f)		_hw_irq1(o,r,hw_##o##_irq_##r)
#define _hw_irq1(...)			_hw_irq2(__VA_ARGS__)
#define _hw_irq2(o,r,...)		HW_BW(_hw_irq2_,_irq,__VA_ARGS__)(o,r,__VA_ARGS__)
#define _hw_irq2_0(o,r,...)		,(o,irq,r),HW_EM_O((o,irq,r))
#define _hw_irq2_1(o,r,ic,iv,...)	ic,(o,irq,r),(iv,__VA_ARGS__)
