
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
#define HW_A2(...)		_HW_A2_2(__VA_ARGS__,,,)
#define _HW_A2_2(a0,a1,a2,...)	a2


/** \brief	Element a3 of the list a0,a1,a2,a3,...
 */
#define HW_A3(...)			_HW_A3_2(__VA_ARGS__,,,,)
#define _HW_A3_2(a0,a1,a2,a3,...)	a3


/** \brief	Remove first element from list
 */
#define HW_CDR(...)		_HW_CDR(__VA_ARGS__)
#define _HW_CDR(x,...)		__VA_ARGS__


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
#define hw_is_1_1		, 1
#define hw_is__			, 1
#define hw_is_ctr_ctr		, 1
#define hw_is_irq_irq		, 1
#define hw_is_mem_mem		, 1
#define hw_is_ocra_ocra		, 1
#define hw_is_ok_ok		, 1
#define hw_is_state_state	, 1


/** \brief	Length of list
 */
#define HW_LEN(...)		_HW_LEN_2(__VA_ARGS__,10,9,8,7,6,5,4,3,2,1)
#define _HW_LEN_2(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,x,...)	x


/** \brief	Remove first elements from list
 */
#define HW_POP_1(_1,...)			__VA_ARGS__
#define HW_POP_4(_1,_2,_3,_4,...)		__VA_ARGS__
#define HW_POP_8(_1,_2,_3,_4,_5,_6,_7,_8,...)	__VA_ARGS__



/** \brief	Quote the first element in the list
 */
#define HW_QUOTE(...)		_HW_QUOTE_2(__VA_ARGS__,)
#define _HW_QUOTE_2(x,...)	#x


/*	Generic instruction 'hw_addr': address of a controller or memory
 */
#define hw_addr(...)		HW_G2(_hw_addr_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hw_addr_xctr_1(ctr,cc,cn,ca,...)	ca
#define _hw_addr_xctr_0(...)	HW_G2(_hw_addr_xmem, HW_IS(mem,__VA_ARGS__))(__VA_ARGS__)
#define _hw_addr_xmem_0(...)	HW_ERR("hw_addr(...) only applies to one controller or memory.")
#define _hw_addr_xmem_1(mem,x,...)	_hw_addr_xmem_##x(__VA_ARGS__)
#define _hw_addr_xmem_bit(cn,rn,ra,bn,bp)	ra+HW_RA_OFFSET


/*	Generic instruction 'hw_bn': number of bits of something
 */
#define hw_bn(...)		HW_G2(_hw_bn_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hw_bn_xctr_0(...)	HW_G2(_hw_bn_xmem, HW_IS(mem,__VA_ARGS__))(__VA_ARGS__)
#define _hw_bn_xmem_0(...)	HW_ERR("first argument is not a controller.")
#define _hw_bn_xmem_1(mem,x,...)	_hw_bn_xmem_##x(__VA_ARGS__)
#define _hw_bn_xmem_bit(cn,rn,ra,bn,bp)	bn
#define _hw_bn_xctr_1(ctr,cc,...)	\
  HW_G2(_hw_bn_xfn, HW_IS(,hw_bn_##cc##_isfn))(cc,__VA_ARGS__)
#define _hw_bn_xfn_1(cc,...)	hw_bn_##cc(__VA_ARGS__)
#define _hw_bn_xfn_0(cc,cn,ca,...)					\
  HW_ERR("controller hw_`" #cn "` of class `" #cc "`has no method `hw_bn()`.")


/*	Generic instruction 'hw_bp': position of least significant bit of something
 */
#define hw_bp(...)		HW_G2(_hw_bp_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hw_bp_xctr_0(...)	HW_G2(_hw_bp_xmem, HW_IS(mem,__VA_ARGS__))(__VA_ARGS__)
#define _hw_bp_xmem_0(...)	HW_ERR(first argument is not a controller.)
#define _hw_bp_xmem_1(mem,x,...)	_hw_bp_xmem_##x(__VA_ARGS__)
#define _hw_bp_xmem_bit(cn,rn,ra,bn,bp)	bp
#define _hw_bp_xctr_1(ctr,cc,...)	\
  HW_G2(_hw_bp_xfn, HW_IS(,hw_bp_##cc##_isfn))(cc,__VA_ARGS__)
#define _hw_bp_xfn_1(cc,...)	hw_bp_##cc(__VA_ARGS__)
#define _hw_bp_xfn_0(cc,cn,ca,...)					\
  HW_ERR("controller `hw_" #cn "` of class `" #cc "` has no method `hw_bp()`.")


/** \brief	Class of an object
 */
#define hw_class(...)		HW_G2(_hw_class, HW_IS(,hw_type_##__VA_ARGS__))(__VA_ARGS__,)
#define _hw_class_0(...)	HW_ERR("type of `" #__VA_ARGS__ "` is unknown.")
#define _hw_class_1(t,c,...)	c

#define hw_type_ctr
#define hw_type_mem
#define hw_type_irq


/*	Generic instruction 'hw_ctr': definition of the controller associated to an object
 */
#define hw_ctr(...)		HW_G2(_hw_ctr_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hw_ctr_xctr_0(...)	HW_ERR("first argument is not a controller.")
#define _hw_ctr_xctr_1(ctr,cc,...)	\
  HW_G2(_hw_ctr_xfn, HW_IS(,hw_ctr_##cc##_isfn))(cc,__VA_ARGS__)
#define _hw_ctr_xfn_1(cc,...)	hw_ctr_##cc(__VA_ARGS__)
#define _hw_ctr_xfn_0(cc,cn,ca,...)					\
  HW_ERR("controller hw_`" #cn "` of class `" #cc "`has no method `hw_ctr()`.")


/*	Generic instruction 'hw_eq': equality of two objects
 */
#define hw_eq(a,b)		HW_G2(_hw_eq, HW_IS(,HW_G3(_hw_eq,hw_class(a),isfn)))(a,b)
#define _hw_eq_0(...)		0
#define _hw_eq_1(t,c,...)	_hw_eq_##c(t,c,__VA_ARGS__)


/*	Generic instruction 'hw_io': definition of the io associated to an
 *	object (or the io itself)
 */
#define hw_io(...)		HW_G2(_hw_io_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hw_io_xctr_0(...)	HW_ERR("first argument is not a controller.")
#define _hw_io_xctr_1(ctr,cc,...)	\
  HW_G2(_hw_io_xfn, HW_IS(,hw_io_##cc##_isfn))(cc,__VA_ARGS__)
#define _hw_io_xfn_1(cc,...)	hw_io_##cc(__VA_ARGS__)
#define _hw_io_xfn_0(cc,cn,ca,...)					\
  HW_ERR("controller hw_`" #cn "` of class `" #cc "`has no method `hw_io()`.")


/** \brief	Name of an object
 */
#define hw_name(...)		HW_G2(_hw_name, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__,)
#define _hw_name_0(...)		HW_ERR("first argument is not a controller.")
#define _hw_name_1(t,cc,cn,...)	cn
