
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	General purpose macro definitions usable in C or assembler source code.
 *
 *	Upper case definitions process arbitrary lists of arguments.
 *
 *	Lower case definitions deal with lists of arguments starting with a
 *	class name.
 */


/*	HWA basic classes
 */
#define hw_class_bits1
#define hw_class_bits2


/** \brief	Preprocessing error
 *
 */
#if defined __ASSEMBLER__
#  define HW_ERR(msg)		0 ; .fail "HWA: " msg
#  define HW_FERR(...)		.fail __VA_ARGS__
#else
/*
 *  avr-gcc ignores the GCC error pragma
 */
#  define HW_ERR(msg)		0 ; _Static_assert(0, "HWA: " msg)
//#  define HW_ERR(msg)		0 ; _Pragma( HW_QUOTE( GCC error HWA: msg ) )
//#  define HW_ERR(msg)		_Pragma ( HW_QUOTE( GCC error HWA: msg ) )

/*	Encapsulate the result of HW_ERR inside a fake function numberred n
 */
#define HW_FERR(...)		_HW_FERR_2(__COUNTER__, __VA_ARGS__)
#define _HW_FERR_2(...)		_HW_FERR_3(__VA_ARGS__)
#define _HW_FERR_3(n,...)	void hw_err##n { uint8_t x = __VA_ARGS__ } void hw_err##n##_

#endif


/** \brief	Element a0 of the list a0,...
 */
#define HW_A0(...)		_HW_A0_2(__VA_ARGS__,)
#define _HW_A0_2(a0,...)	a0


/** \brief	Element a1 of the list a0,a1,...
 */
#define HW_A1(...)		_HW_A1_2(__VA_ARGS__,,)
#define _HW_A1_2(a0,a1,...)	a1


/** \brief	Element a2 of the list a0,a1,a2,...
 */
#define HW_A2(...)		_HW_A2_2(__VA_ARGS__,,,)
#define _HW_A2_2(a0,a1,a2,...)	a2


/** \brief	Glue the first two arguments
 */
#define HW_G2(...)		_HW_G2_(__VA_ARGS__,,)
#define _HW_G2_(a,b,...)	a##_##b


/** \brief	Glue the first three arguments
 */
#define HW_G3(...)		_HW_G3_(__VA_ARGS__,,,)
#define _HW_G3_(a,b,c,...)	a##_##b##_##c


/*	Method (specialize instruction)
 *
 *	Check that the first argument for function f has a declared class
 *	Check that the function can be applied to that class
 *	Detect and propagate errors
 */
#define HW_MTHD(f,...)		_HW_MTHD1(f,__VA_ARGS__)
#define _HW_MTHD1(f,...)	HW_G2(_HW_MTHD1, HW_IS(,hw_class_##__VA_ARGS__))(f,__VA_ARGS__)
#define _HW_MTHD1_1(f,...)	HW_G2(_HW_MTHD2, HW_IS(,HW_G3(hw_def,f,__VA_ARGS__)))(f,__VA_ARGS__)
#define _HW_MTHD1_0(f,...)	HW_G2(_HW_MTHD1_0,HW_IS(0,__VA_ARGS__))(f,__VA_ARGS__)
#define _HW_MTHD1_0_0(f,...)	HW_ERR("`" HW_QUOTE(__VA_ARGS__) "` is not defined.")
#define _HW_MTHD1_0_1(f,...)	__VA_ARGS__
#define _HW_MTHD2_1(f,...)	HW_A1(HW_G3(hw_def,f,__VA_ARGS__))(__VA_ARGS__)
#define _HW_MTHD2_0(f,...)	HW_ERR("`"#f "` is not a method of class `" HW_QUOTE(__VA_ARGS__) "`.")


/*	Generic instruction (no specialization)
 *
 *	Check that the first argument for function f has a declared class
 *	Detect and propagate errors
 */
#define HW_GNRC(f,...)		_HW_GNRC1(f,__VA_ARGS__)
#define _HW_GNRC1(f,...)	HW_G2(_HW_GNRC1, HW_IS(,hw_class_##__VA_ARGS__))(f,__VA_ARGS__)
#define _HW_GNRC1_1(f,...)	f(__VA_ARGS__)
#define _HW_GNRC1_0(f,...)	HW_G2(_HW_GNRC1_0,HW_IS(0,__VA_ARGS__))(f,__VA_ARGS__)
#define _HW_GNRC1_0_0(f,...)	HW_ERR("`" HW_QUOTE(__VA_ARGS__) "` is not defined.")
#define _HW_GNRC1_0_1(f,...)	__VA_ARGS__


/*	Produce result if followed by '', an error otherwise
 */
#define HW_TX(result, ...)	HW_G2(_HW_TX,HW_IS(,__VA_ARGS__))((result),__VA_ARGS__)
#define _HW_TX_0(result, ...)	HW_ERR("garbage found: `" HW_QUOTE(__VA_ARGS__) "`.")
#define _HW_TX_1(result, ...)	_HW_TX_2 result
#define _HW_TX_2(...)		__VA_ARGS__


/*	'1' if the 2nd argument of hw_is_x_y is '1', '0' if hw_is_x_y has no 2nd arg
 */
#define HW_IS(...)		_HW_IS_2(__VA_ARGS__,,)
#define _HW_IS_2(x,y,...)	HW_A1(hw_is_##x##_##y,0)
#define hw_is_0_0		, 1,	/* one more comma to remove '; StaticAssert(...)' */
#define hw_is__			, 1
#define hw_is_irq_irq		, 1


/** \brief	Quote the first element in the list
 */
#define HW_QUOTE(...)		_HW_QUOTE_2(__VA_ARGS__,)
#define _HW_QUOTE_2(x,...)	#x


/*	hw_addr(...): address of something (method)
 */
#define hw_addr(...)		HW_MTHD(hw_addr, __VA_ARGS__)

#define hw_def_hw_addr_bits1	, _hw_addr_bits1


/*	hw_ap(...): address and position of least significant bit (method)
 */
#define hw_ap(...)		HW_MTHD(hw_ap, __VA_ARGS__)

#define hw_def_hw_ap_bits1	, _hw_ap_bits1
#define _hw_ap_bits1(...)	_hw_addr_bits1(__VA_ARGS__), _hw_bp_bits1(__VA_ARGS__)


/*	hw_reg(...): memory definition of an instance's bits (generic)
 *
 *	No need to use a specialization. hw_reg() can be applied to every
 *	declared instance whatever its class.
 */
#define hw_reg(...)		HW_GNRC(_hw_reg_3, __VA_ARGS__)
#define _hw_reg_3(c,n,i,a,r)	_hw_reg_4(c,n,a,r,hw_##c##_##r)
#define _hw_reg_4(...)		_hw_reg_5(__VA_ARGS__)
#define _hw_reg_5(c,n,a,r,...)						\
  HW_G2(_hw_reg_x, HW_IS(,hw_hasbits_##__VA_ARGS__))(c,n,a,r,__VA_ARGS__)

#define hw_hasbits_crg
#define hw_hasbits_cb1
#define hw_hasbits_cb2
#define hw_hasbits_irg

#define _hw_reg_x_0(c,n,a,r,...)	HW_G2(_hw_reg_x_0, HW_IS(,r))(c,n,a,r)
#define _hw_reg_x_0_1(c,n,a,r)		HW_ERR("member of hw_" #c "is required.")
#define _hw_reg_x_0_0(c,n,a,r)		HW_ERR("`"#r"` is not a memory definition of `hw_"#c"`.")
#define _hw_reg_x_1(c,n,a,r, x,...)	_hw_reg_##x(c,n,a,r,__VA_ARGS__)

#define _hw_reg_crg(c,n,a,r,rw,ra,rwm,rfm)	\
  bits1, n,a, r,rw,ra,rwm,rfm, rw,0

#define _hw_reg_cb1(c,n,a,xn,rn,bn,bp)	_hw_reg_cb1_2(n,a,rn,hw_##c##_##rn,bn,bp)
#define _hw_reg_cb1_2(...)		_hw_reg_cb1_3(__VA_ARGS__)
#define _hw_reg_cb1_3(n,a,rn, t, ...)		\
  bits1, n,a, rn,__VA_ARGS__

#define _hw_reg_cb2(c,n,a,r, r1,rbn1,rbp1,vbp1, r2,rbn2,rbp2,vbp2)	\
  _hw_reg_cb2_2(n,a,							\
		 r1,hw_##c##_##r1,rbn1,rbp1,vbp1,			\
		 r2,hw_##c##_##r2,rbn2,rbp2,vbp2)
#define _hw_reg_cb2_2(...)		_hw_reg_cb2_3(__VA_ARGS__)
#define _hw_reg_cb2_3(n,a,						\
		       r1,crg1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,	\
		       r2,crg2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2)	\
  bits2, n,a,								\
    r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,				\
    r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2

#define _hw_reg_irg(_c,_n,_a,_x, c,n,i,a,r)	_hw_reg_irg_2(c,n,a,r,hw_##c##_##r)
#define _hw_reg_irg_2(...)			_hw_reg_irg_3(__VA_ARGS__)
#define _hw_reg_irg_3(c,n,a,r, x,...)		_hw_reg_##x(c,n,a,r,__VA_ARGS__)


/*	_hw_reg(...): memory definition of an instance's bits (generic)
 *
 *		Internal use only, no argument checking
 */
#define _hw_reg(...)		_hw_reg_3(__VA_ARGS__)


/*	_hw_creg(...): memory definition of a class' bits (generic)
 *
 *		Internal use only, no argument checking
 */
#define _hw_creg(c,r)		_hw_reg_4(c,,,r,hw_##c##_##r)


/*	hw_bn(...): number of bits of something (method)
 */
#define hw_bn(...)		HW_MTHD(hw_bn, __VA_ARGS__)

#define hw_def_hw_bn_bits1	, _hw_bn_bits1

#define _hw_bn_bits1(t, c,n, rn,rw,ra,rwm,rfm, bn,bp)	bn


/*	hw_bp(...): position of least significant bit of something (method)
 */
#define hw_bp(...)		HW_MTHD(hw_bp, __VA_ARGS__)

#define hw_def_hw_bp_bits1	, _hw_bp_bits1

#define _hw_bp_bits1(t, c,n, rn,rw,ra,rwm,rfm, bn,bp)	bp


/*	hw_id(...): id of an instance (generic)
 *
 *	Do not use HW_GNRC(): return 0 if instance does not exist
 */
#define hw_id(...)		_hw_id_2(__VA_ARGS__)
#define _hw_id_2(...)		HW_G2(_hw_id, HW_IS(,hw_class_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_id_0(...)		0	/* instance does not exist */
#define _hw_id_1(c,n,i,...)	i


/*	hw_io(...): definition of the io associated to an instance, or the io itself (method)
 */
#define hw_io(...)		HW_MTHD(hw_io, __VA_ARGS__)


/*	hw_name(...): name of an instance (generic)
 *
 *		No specialization: can be applied to
 *		every declared instance whatever its class.
 */
#define hw_name(...)		HW_GNRC(_hw_name, __VA_ARGS__)
#define _hw_name(c,n,...)	n


/*	hw_sub(...): sub module of a controller
 */
#define hw_sub(x,y)		HW_GNRC(_hw_sub,x,y)
#define _hw_sub(c,n,i,a, x)	hw_##n##_##x


/*	hw_sup(...): definition of the controller associated to an instance (method)
 */
#define hw_sup(...)		HW_MTHD(hw_sup, __VA_ARGS__)
