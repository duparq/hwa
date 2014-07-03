
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/** \brief	Preprocessing error
 *
 */
#if defined __ASSEMBLER__
#  define HW_ERR(msg)	.fail "HWA error: " msg
#else
#  define HW_ERR(msg)	0 ; _Static_assert(0, "HWA error:" msg)
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
#define HW_A2(...)			_HW_A2_2(__VA_ARGS__,,,)
#define _HW_A2_2(a0,a1,a2,...)		a2


/** \brief	Element a3 of the list a0,a1,a2,a3,...
 */
#define HW_A3(...)			_HW_A3_2(__VA_ARGS__,,,,)
#define _HW_A3_2(a0,a1,a2,a3,...)	a3


/** \brief	Remove first element from list
 */
/* #define HW_CDR(...)		_HW_CDR(__VA_ARGS__) */
/* #define _HW_CDR(x,...)		__VA_ARGS__ */


/** \brief	Glue first two arguments
 */
#define HW_G2(...)		_HW_G2_(__VA_ARGS__,,)
#define _HW_G2_(a,b,...)	a##_##b


/** \brief	Glue first three arguments
 */
#define HW_G3(...)		_HW_G3_(__VA_ARGS__,,,)
#define _HW_G3_(a,b,c,...)	a##_##b##_##c


/** \brief	Glue first for arguments
 */
#define HW_G4(...)		_HW_G4_(__VA_ARGS__,,,,)
#define _HW_G4_(a,b,c,d,...)	a##_##b##_##c##_##d


/*	1 if the second argument of hw_is_x_y is 1, 0 otherwise
 */
#define HW_IS(...)		_HW_IS_2(__VA_ARGS__,,)
#define _HW_IS_2(x,y,...)	HW_A1(hw_is_##x##_##y,0)

#define hw_is_0_0		, 1,	/* the comma to remove '; StaticAssert(...)' */
#define hw_is__			, 1
#define hw_is_irq_irq		, 1
#define hw_is_ok_ok		, 1


/** \brief	Quote the first element in the list
 */
#define HW_QUOTE(...)		_HW_QUOTE_2(__VA_ARGS__,)
#define _HW_QUOTE_2(x,...)	#x


/*	hw_addr(...): address of an instance (generic)
 */
#define hw_addr(...)		_hw_addr_2(__VA_ARGS__)
#define _hw_addr_2(...)		HW_G2(_hw_addr_xfn,			\
				      HW_IS(,hw_fn_hw_addr_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_addr_xfn_1(t,...)	HW_A1(hw_fn_hw_addr_##t)(t,__VA_ARGS__)
#define _hw_addr_xfn_0(...)	HW_G2(_hw_addr, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_addr_0(...)		HW_ERR("can not process hw_addr(" #__VA_ARGS__ ").")
#define _hw_addr_1(...)		__VA_ARGS__


/*	hw_bits(...): memory definition of an instance's bits (generic)
 */
#define hw_bits(...)		_hw_bits_2(__VA_ARGS__)
#define _hw_bits_2(...)		HW_G2(_hw_bits_xfn,			\
				      HW_IS(,hw_fn_hw_bits_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_bits_xfn_1(t,...)	HW_A1(hw_fn_hw_bits_##t)(t,__VA_ARGS__)
#define _hw_bits_xfn_0(...)	HW_G2(_hw_bits, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_bits_0(...)		HW_ERR("can not process hw_bits(" #__VA_ARGS__ ").")
#define _hw_bits_1(...)		__VA_ARGS__

#define hw_hasbits_reg
#define hw_hasbits_rb1
#define hw_hasbits_rb2
#define hw_hasbits_xreg

#define _hw_bits_cnrn(c,r)		_hw_bits_4(c,,,r,hw_##c##_##r)

#define _hw_bits(...)			_hw_bits_3(__VA_ARGS__)
#define _hw_bits_3(c,n,i,a,r)		_hw_bits_4(c,n,a,r,hw_##c##_##r)
#define _hw_bits_4(...)			_hw_bits_5(__VA_ARGS__)
#define _hw_bits_5(c,n,a,r,...)						\
  HW_G2(_hw_bits_x, HW_IS(,hw_hasbits_##__VA_ARGS__))(c,n,a,r,__VA_ARGS__)
#define _hw_bits_x_0(c,n,a,r,...)	HW_G2(_hw_bits_x_0, HW_IS(,r))(c,n,a,r)
#define _hw_bits_x_0_1(c,n,a,r)		HW_ERR("member of hw_" #c "is required.")
#define _hw_bits_x_0_0(c,n,a,r)		HW_ERR("`" #r "` is not a member of hw_" #c)
#define _hw_bits_x_1(c,n,a,r, x,...)	_hw_bits_##x(c,n,a,r,__VA_ARGS__)

#define _hw_bits_reg(c,n,a, rn,rw,ra,rrv,rwm)	\
  bits1, n,a, rn,rw,ra,rrv,rwm, rw,0

#define _hw_bits_rb1(c,n,a,xn,rn,bn,bp)	_hw_bits_rb1_2(n,a,rn,hw_##c##_##rn,bn,bp)
#define _hw_bits_rb1_2(...)		_hw_bits_rb1_3(__VA_ARGS__)
#define _hw_bits_rb1_3(n,a,rn, t, ...)		\
  bits1, n,a, rn,__VA_ARGS__

#define _hw_bits_rb2(cc,cn,ca,crn, rn1,rbn1,rbp1,vbp1, rn2,rbn2,rbp2,vbp2) \
  _hw_bits_rb2_2(cn,ca,						\
		  rn1,hw_##cc##_##rn1,rbn1,rbp1,vbp1,			\
		  rn2,hw_##cc##_##rn2,rbn2,rbp2,vbp2)
#define _hw_bits_rb2_2(...)		_hw_bits_rb2_3(__VA_ARGS__)
#define _hw_bits_rb2_3(cn,ca,						\
			rn1,reg1,rw1,ra1,rrv1,rwm1,rbn1,rbp1,vbp1,	\
			rn2,reg2,rw2,ra2,rrv2,rwm2,rbn2,rbp2,vbp2)	\
  bits2, cn,ca,								\
    rn1,rw1,ra1,rrv1,rwm1,rbn1,rbp1,vbp1,				\
    rn2,rw2,ra2,rrv2,rwm2,rbn2,rbp2,vbp2

#define _hw_bits_xreg(_c,_n,_a,_x, c,n,i,a,r)	_hw_bits_xreg_2(c,n,a,r,hw_##c##_##r)
#define _hw_bits_xreg_2(...)			_hw_bits_xreg_3(__VA_ARGS__)
#define _hw_bits_xreg_3(c,n,a,r, x,...)		_hw_bits_##x(c,n,a,r,__VA_ARGS__)


/*	hw_bn(...): number of bits of something (generic)
 */
#define hw_bn(...)		_hw_bn_2(__VA_ARGS__)
#define _hw_bn_2(...)		HW_G2(_hw_bn_xfn,			\
				      HW_IS(,hw_fn_hw_bn_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_bn_xfn_1(t,...)	HW_A1(hw_fn_hw_bn_##t)(t,__VA_ARGS__)
#define _hw_bn_xfn_0(...)	HW_G2(_hw_bn, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_bn_0(...)		HW_ERR("can not process hw_bn(" #__VA_ARGS__ ").")
#define _hw_bn_1(...)		__VA_ARGS__


/*	hw_bp(...): position of least significant bit of something (generic)
 */
#define hw_bp(...)		_hw_bp_2(__VA_ARGS__)
#define _hw_bp_2(...)		HW_G2(_hw_bp_xfn,			\
				      HW_IS(,hw_fn_hw_bp_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_bp_xfn_1(t,...)	HW_A1(hw_fn_hw_bp_##t)(t,__VA_ARGS__)
#define _hw_bp_xfn_0(...)	HW_G2(_hw_bp, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_bp_0(...)		HW_ERR("can not process hw_bp(" #__VA_ARGS__ ").")
#define _hw_bp_1(...)		__VA_ARGS__

#define hw_fn_hw_bp_bits1	, _hw_bp_bits1
#define _hw_bp_bits1(t, c,n, rn,rw,ra,rrv,rwm, bn,bp)	bp


/** \brief	Class of an instance
 */
/* #define hw_class(...)		HW_G2(_hw_class, HW_IS(,hw_type_##__VA_ARGS__))(__VA_ARGS__,) */
/* #define _hw_class_0(...)	HW_ERR("type of `" #__VA_ARGS__ "` is unknown.") */
/* #define _hw_class_1(t,c,...)	c */

/* #define hw_type_ctr */
/* #define hw_type_mem */
/* #define hw_type_irq */


/*	hw_ctr(...): definition of the controller associated to an instance (generic)
 */
#define hw_ctr(...)		_hw_ctr_2(__VA_ARGS__)
#define _hw_ctr_2(...)		HW_G2(_hw_ctr_xfn,			\
				      HW_IS(,hw_fn_hw_ctr_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_ctr_xfn_1(t,...)	HW_A1(hw_fn_hw_ctr_##t)(t,__VA_ARGS__)
#define _hw_ctr_xfn_0(...)	HW_G2(_hw_ctr, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_ctr_0(...)		HW_ERR("can not process hw_ctr(" #__VA_ARGS__ ").")
#define _hw_ctr_1(...)		__VA_ARGS__


/*	hw_id(...): id of an instance (generic)
 */
#define hw_id(...)		_hw_id_2(__VA_ARGS__)
#define _hw_id_2(...)		HW_G2(_hw_id,				\
				      HW_IS(,hw_class_##__VA_ARGS__))(__VA_ARGS__)
//#define _hw_id_0(...)		HW_ERR("can not process hw_id(" #__VA_ARGS__ ").")
#define _hw_id_0(...)		-1
#define _hw_id_1(c,n,i,a)	i


/*	hw_io(...): definition of the io associated to an instance, or the io itself (generic)
 */
#define hw_io(...)		_hw_io_2(__VA_ARGS__)
#define _hw_io_2(...)		HW_G2(_hw_io_xfn,			\
				      HW_IS(,hw_fn_hw_io_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_io_xfn_1(t,...)	HW_A1(hw_fn_hw_io_##t)(t,__VA_ARGS__)
#define _hw_io_xfn_0(...)	HW_G2(_hw_io, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_io_0(...)		HW_ERR("can not process hw_io(" #__VA_ARGS__ ").")
#define _hw_io_1(...)		__VA_ARGS__


/** \brief	Name of an object
#define hw_name(...)		HW_G2(_hw_name, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__,)
#define _hw_name_0(...)		HW_ERR("first argument is not a controller.")
#define _hw_name_1(t,cc,cn,...)	cn
 */
