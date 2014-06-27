
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Error message at compile-time
 */
#if defined __ASSEMBLER__
#  define HW_PPERROR(msg)	.fail "HWA error: " msg
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


/** \brief	Glue "hw", a1, and a3 of the liste a0,a1,a2,a3...
 *
 *	This is used for determining if a3 is the name of a register of a
 *	controller named a1.
 */
#define HW_GA1A3(...)			_HW_GA1A3_2(__VA_ARGS__,,,,)
#define _HW_GA1A3_2(a0,a1,a2,a3,...)	hw##_##a1##_##a3


/** \brief	1 if 'hw_isfn_<x>' is defined void, 0 otherwise.
 */
#define HW_ISFN(...)		_HW_ISFN_2(__VA_ARGS__,)
#define _HW_ISFN_2(x,...)	HW_IS(,x##_isfn)


/** \brief	Quote the first element in the list
 */
#define HW_QUOTE(...)		_HW_QUOTE_2(__VA_ARGS__,)
#define _HW_QUOTE_2(x,...)	#x


/** \brief	Build a function call from the list.
 */
#define HW_CALL(...)		_HW_CALL_2(__VA_ARGS__)
#define _HW_CALL_2(f,...)	f(__VA_ARGS__)


/*	Specialize a function according to the arguments
 *	The __VA_ARGS__ must be of the form: type(args...)
 */
#define HW_SPCLZ(...)		_HW_SPCLZ_2(__VA_ARGS__)
#define _HW_SPCLZ_2(f,...)	f##_##__VA_ARGS__


/** \brief	Name of an object
 */
#define hw_name(...)		HW_G2(_hw_name, HW_CT(__VA_ARGS__))(__VA_ARGS__,,)
#define _hw_name_0(x,...)	HW_PPERROR("`" #x "` is not defined.")
#define _hw_name_1(ot,on,...)	on


/** \brief	Class of an object
 */
#define hw_class(...)		HW_G2(_hw_class, HW_CT(__VA_ARGS__))(__VA_ARGS__,,,)
#define _hw_class_0(x,...)	HW_PPERROR("`" #x "` is not defined.")
#define _hw_class_1(ct,cn,cc,...)	cc


/** \brief	Address of a register or group of bits
 */
#define hw_ra(...)		HW_G2(_hw_ra, HW_CALL( HW_X2R(__VA_ARGS__) ) )
#define _hw_ra_0(x)		HW_PPERROR(x)
#define _hw_ra_reg(cn,cc,ca,rn,rw,ra,riv,rwm)		(ca+ra+HW_RA_OFFSET)
#define _hw_ra_regb(cn,cc,ca,rn,rw,ra,riv,rwm,bn,bp)	(ca+ra+HW_RA_OFFSET)



/** \brief	Pointer to a controller register
 */
#define hw_rp(...)		HW_G2(_hw_rp, HW_CALL( HW_X2R(__VA_ARGS__) ) )
#define _hw_rp_0(x)		HW_PPERROR(x)
#define _hw_rp_reg(cn,cc,ca,rn,rw,ra,riv,rwm)		(uint##rw##_t)(ca+ra+HW_RA_OFFSET)
#define _hw_rp_regb(cn,cc,ca,rn,rw,ra,riv,rwm,bn,bp)	(uint##rw##_t)(ca+ra+HW_RA_OFFSET)


/** \brief	Number of bits of an io definition
 */
/* #define hw_bn(...)		HW_G2(_hw_bn, HW_CALL( HW_X2R(__VA_ARGS__) ) ) */
/* #define _hw_bn_0(x)		HW_PPERROR(x) */
/* #define _hw_bn_reg(cn,cc,ca,rn,rw,ra,riv,rwm)		rw */
/* #define _hw_bn_regb(cn,cc,ca,rn,rw,ra,riv,rwm,bn,bp)	bn */
/* #define _hw_bn_io(_io_,ion, _ctr_,cn,cc,ca, bn, bp)	bn */

#define hw_bn(...)	HW_G2(_hw_bn_xtype, HW_IS(0,hw_loosetype(__VA_ARGS__)))(__VA_ARGS__,,)
#define _hw_bn_xtype_1(x,...)	HW_PPERROR("`" #x "` is not declared.")
#define _hw_bn_xtype_0(...)	HW_G2(_hw_bn_xio, HW_IS(io,__VA_ARGS__))(__VA_ARGS__)
#define _hw_bn_xio_1(_io_,ion, _ctr_,cn,cc,ca, bn, bp, _1, _2)	bn
#define _hw_bn_xio_0(...)	HW_G2(_hw_bn_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hw_bn_xctr_0(x,n,...)	HW_PPERROR("can not apply hw_io(...) to " #x " `hw_" #n "`.")
#define _hw_bn_xctr_1(ctr,cn,cc,ca,x,...)		\
  _hw_bn_ctr(ctr,cn,cc,ca,hw_##cc##_##x,__VA_ARGS__)
#define _hw_bn_ctr(...)	_hw_bn_ctr_2(__VA_ARGS__)
#define _hw_bn_ctr_2(ctr,cn,cc,ca,x,...)				\
  HW_G2(_hw_bn_ctr, hw_loosetype(x))(ctr,cn,cc,ca,x,__VA_ARGS__)
#define _hw_bn_ctr_reg(ctr,cn,cc,ca, reg,rn,rw,...)				rw
#define _hw_bn_ctr_regb(ctr,cn,cc,ca, regb,reg,rn,rw,ra,rrv,rwm,bn,...)	bn
#define _hw_bn_ctr_regbb(...)	HW_PPERROR("hw_bn(...) is not implemented for regbb.")
#define _hw_bn_ctr_0(ctr,cn,cc,...)					\
  HW_G2(_hw_bn_xfn, HW_IS(,hw_bn_##cc##_isfn))(ctr,cn,cc,__VA_ARGS__)
#define _hw_bn_xfn_0(ctr,cn,cc,...)					\
  HW_PPERROR("can not apply hw_bn(...) to " #cc " `hw_" #cn "`.")
#define _hw_bn_xfn_1(ctr,cn,cc,...)		\
  hw_bn_##cc(ctr,cn,cc,__VA_ARGS__)


/** \brief	Position of least significant bit of an io or bit definition
 */
#define hw_bp(...)		HW_G2(_hw_bp, HW_CALL( HW_X2R(__VA_ARGS__) ) )
#define _hw_bp_0(x)		HW_PPERROR(x)
#define _hw_bp_reg(cn,cc,ca,rn,rw,ra,riv,rwm)		0
#define _hw_bp_regb(cn,cc,ca,rn,rw,ra,riv,rwm,bn,bp)	bp
#define _hw_bp_io(_io_,ion, _ctr_,cn,cc,ca, bn, bp)	bp


/** \brief	Definition of the controller associated to an object
 */
/* #define hw_ctr(...)		HW_G2(_hw_ctr, hw_type(__VA_ARGS__))(__VA_ARGS__,) */
/* #define _hw_ctr_0(...)		HW_PPERROR("`" HW_QUOTE(__VA_ARGS__) "` is unknown.") */
/* #define _hw_ctr_1(...)		HW_PPERROR("`" HW_QUOTE(__VA_ARGS__) "` is a fake.") */

#define hw_ctr(...)		HW_G2(_hw_ctr, hw_loosetype(__VA_ARGS__))(__VA_ARGS__,)
#define _hw_ctr_0(...)		HW_PPERROR("`" HW_QUOTE(__VA_ARGS__) "` is not declared.")
#define _hw_ctr_io(io,ion,_ctr_,cn,cc,ca,...)		ctr,cn,cc,ca
#define _hw_ctr_aio(_aio_,aion,ion,_ctr_,cn,cc,ca,...)	ctr,cn,cc,ca
#define _hw_ctr_ctr(_ctr_,cn,cc,...)	HW_G2(_hw_ctr_xctr, HW_IS(ctr,__VA_ARGS__))(cn,__VA_ARGS__)
#define _hw_ctr_xctr_0(cn,...)	HW_PPERROR("`hw_" #cn "` has no associated controller.")
#define _hw_ctr_xctr_1(x,_ctr_,cn,cc,ca,...)	ctr,cn,cc,ca


/*	Definition of the io associated to an object (or the io itself)
 */
#define hw_io(...)							\
  HW_G2(_hw_io_xtype, HW_IS(0,hw_loosetype(__VA_ARGS__)))(__VA_ARGS__,)
#define _hw_io_xtype_1(x,...)	HW_PPERROR("`" #x "` is not declared.")
#define _hw_io_xtype_0(...)	HW_G2(_hw_io_xio, HW_IS(io,__VA_ARGS__))(__VA_ARGS__)
#define _hw_io_xio_1(io,ion, ctr,cn,cc,ca, bn,bp, _)	io,ion, ctr,cn,cc,ca, bn,bp
#define _hw_io_xio_0(...)	HW_G2(_hw_io_xaio, HW_IS(aio,__VA_ARGS__))(__VA_ARGS__)
#define _hw_io_xaio_1(_aio_,aion,ion, ...)	hw_##ion
#define _hw_io_xaio_0(...)	HW_G2(_hw_io_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hw_io_xctr_0(x,n,...)	HW_PPERROR("can not apply hw_io(...) to " #x " `hw_" #n "`.")
#define _hw_io_xctr_1(ctr,cn,cc,...)					\
  HW_G2(_hw_io_xfn, HW_IS(,hw_io_##cc##_isfn))(ctr,cn,cc,__VA_ARGS__)
#define _hw_io_xfn_0(ctr,cn,cc,...)					\
  HW_PPERROR("can not apply hw_io(...) to " #cc " `hw_" #cn "`.")
#define _hw_io_xfn_1(ctr,cn,cc,...)		\
  hw_io_##cc(ctr,cn,cc,__VA_ARGS__)


/** \brief	Equality of two objects
 */
/*  The definitions of aios are inconsistent. We must extract the names to later
 *  get the ios and controllers and then compare them.
 *  The arguments are swaped so that their types can be checked more easily.
 */
#define hw_eq(a,b)		HW_G2(_hw_eq, hw_type(a))(hw_name(a),hw_name(b),b,a)
#define _hw_eq_0(...)		0

#define _hw_eq_io(na,nb,...)	HW_G2(_hw_eq_io, HW_IS(io,__VA_ARGS__))(__VA_ARGS__)
#define _hw_eq_io_0(...)	0
#define _hw_eq_io_1(...)	_hw_eq_io_1_2(__VA_ARGS__) /* expand for hw_eq_aio_aio */
#define _hw_eq_io_1_2(_io0_,ion0,_ctr0_,cn0,cc0,ca0,bn0,bp0,	\
			  _io1_,ion1,_ctr1_,cn1,cc1,ca1,bn1,bp1)	\
  (ca0==ca1 && bp0==bp1 && bn0==bn1)

#define _hw_eq_aio(na,nb,...)		HW_G2(_hw_eq_aio, HW_IS(aio,__VA_ARGS__))(na,nb)
#define _hw_eq_aio_0(...)	0
#define _hw_eq_aio_1(na,nb)	\
  _hw_eq_io_1(hw_io(hw_##na), hw_io(hw_##nb)) &&	\
  _hw_eq_ctr_1(hw_ctr(hw_##na), hw_ctr(hw_##nb))

#define _hw_eq_ctr(na,nb,...)		HW_G2(_hw_eq_ctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hw_eq_ctr_0(...)	0
#define _hw_eq_ctr_1(...)	_hw_eq_ctr_1_2(__VA_ARGS__) /* expand for hw_eq_aio_aio */
#define _hw_eq_ctr_1_2(_ctr0_,cn0,cc0,ca0, _ctr1_,cn1,cc1,ca1)  (ca0 == ca1)
