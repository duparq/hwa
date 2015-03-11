
/*	HWA definitions that produce C code
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*  	hw/hwa_config(...): configure something (method)
 */
#define hw_config(...)			HW_MTHD(hw_config, __VA_ARGS__,)
#define hwa_config(...)			HW_MTHD(hwa_config, __VA_ARGS__,)

//#define _hwa_config(...)		_HW_MTHD(_hwa_config, __VA_ARGS__,)


/*	hw_read(...): read something (method)
 */
#define hw_read(...)			HW_MTHD(hw_read, __VA_ARGS__)
#define hw_read_reg(...)		HW_MTHD(hw_read, hw_reg(__VA_ARGS__))
#define hw_atomic_read(...)		HW_MTHD(hw_atomic_read, __VA_ARGS__)

#define _hw_read_reg(p,m)		_HW_SPEC(_hw_read, _hw_reg(p,m))


/*	hw/hwa_write(...): write something (method)
 */
#define hw_write(...)			HW_MTHD(hw_write, __VA_ARGS__)
#define hwa_write(...)			HW_MTHD(hwa_write, __VA_ARGS__)

#define hw_write_reg(...)		HW_MTHD(hw_write, hw_reg(__VA_ARGS__))
#define hwa_write_reg(...)		HW_MTHD(hwa_write, hw_reg(__VA_ARGS__))

#define _hw_write_reg(p,m,v)		_HW_SPEC(_hw_write, _hw_reg(p,m),v)
#define _hwa_write_reg(p,m,v)		_HW_SPEC(_hwa_write, _hw_reg(p,m),v)

#define _hwa_write_creg(p,c,m,v)	_HW_SPEC(_hwa_writep, _hw_creg(c,m),p,v)


/*	hw_clear(...): clear something (method)
 */
#define hw_clear(...)			HW_MTHD(hw_clear, __VA_ARGS__,)
#define hwa_clear(...)			HW_MTHD(hwa_clear, __VA_ARGS__,)


/*	hw_reset(...): reset something (method)
 */
#define hw_reset(...)			HW_MTHD(hw_reset, __VA_ARGS__,)
#define hwa_reset(...)			HW_MTHD(hwa_reset, __VA_ARGS__,)


/*	hw/hwa_power(...): power something on/off (method)
 */
#define hw_power(...)			HW_MTHD(hw_power, __VA_ARGS__,)
#define hwa_power(...)			HW_MTHD(hwa_power, __VA_ARGS__,)


/*	hw_lock_to_zero(...): clear something and keep it at 0 (mehod)
 */
#define hw_lock_to_zero(...)		HW_MTHD(hw_lock_to_zero, __VA_ARGS__)
#define hwa_lock_to_zero(...)		HW_MTHD(hwa_lock_to_zero, __VA_ARGS__)


/*	hw/hwa_release(...): release something (method)
 */
#define hw_release(...)			HW_MTHD(hw_release, __VA_ARGS__)
#define hwa_release(...)		HW_MTHD(hwa_release, __VA_ARGS__)


/*	hw_stat_t(...): structure holding the status of something (method)
 *	hw_stat(...): get the status of something (method)
 */
#define hw_stat_t(...)			HW_MTHD(hw_stat_t, __VA_ARGS__,)
#define hw_stat(...)			HW_MTHD(hw_stat, __VA_ARGS__,)


/*	hw/hwa_toggle(...): toggle something, probably an io (method)
 */
#define hw_toggle(...)			HW_MTHD(hw_toggle, __VA_ARGS__,)
#define hwa_toggle(...)			HW_MTHD(hwa_toggle, __VA_ARGS__,)


/*	hw/hwa_turn(...): turn something on/off (method)
 */
#define hw_turn(...)			HW_MTHD(hw_turn, __VA_ARGS__)
#define hwa_turn(...)			HW_MTHD(hwa_turn, __VA_ARGS__)


/*	hw/hwa_trigger(...): trigger something (method)
 */
#define hw_trigger(...)			HW_MTHD(hw_trigger, __VA_ARGS__)
#define hwa_trigger(...)		HW_MTHD(hwa_trigger, __VA_ARGS__)


/*	hw_read_reg(...): short for hw_read( hw_reg(...) )
 */
/* #define hw_read_reg(i,r)		_hw_readreg_2(hw_xpr(i,r)) */
/* #define _hw_readreg_2(...)		_hw_readreg_3(__VA_ARGS__) */
/* #define _hw_readreg_3(t,...)		_hw_read_##t(__VA_ARGS__) */
//#define _hw_rdreg(p,r)			hw_read(hw_xpr(p,r))
//#define _hw_rdreg(p,r)			HW_MTHD(hw_read, hw_xpr(p,r))
/*
 *	Internal use, no argument checking.
 */
//#define _hw_read_reg(i,r)		_hw_readreg_2(_hw_xpr(i,r))
//#define _hw_readreg_2(...)		_hw_readreg_3(__VA_ARGS__)
//#define _hw_readreg_3(t,...)		_hw_read_##t(__VA_ARGS__)

//#define _hw_read_reg(p,m)		_HW_MTHD(_hw_read, _hw_reg(p,m))
//#define _hw_read_reg(p,m)		HW_MTHD(_hw_read,hw_reg(p,m))

//#define _hw_atomic_read_reg(...)		_hw_atomic_read_reg_2(__VA_ARGS__)
//#define _hw_atomic_read_reg_2(n,c,i,a, r)	_hw_atomic_readreg_2(_hw_reg(n,c,i,a,r))

//#define hw_atomic_read_reg(i,r)		_hw_atomic_readreg_2(hw_reg(i,r))
//#define _hw_atomic_readreg_2(...)	_hw_atomic_readreg_3(__VA_ARGS__)
//#define _hw_atomic_readreg_3(t,...)	_hw_atomic_read_##t(t,__VA_ARGS__)


//#define hw_mthd_hw_atomic_read__m1	, _hw_atomic_read__m1
//#define _hw_atomic_read__m1(_m1, n,a, rn,rw,ra,rwm,rfm, rbn,rbp)	
//  _hw_atomic_read_r##rw(a+ra,rbn,rbp)


#define hw_mthd_hw_read__m1		, _hw_read__m1
#define hw_mthd_hw_read__m2		, _hw_read__m2
#define hw_mthd_hw_write__m1		, _hw_write__m1
#define hw_mthd_hw_write__m2		, _hw_write__m2
//#define hw_mthd_hwa_write__m1		, _hwa_write__m1
//#define hw_mthd_hwa_write__m2		, _hwa_write__m2

//#define hw_read__m1			_hw_read__m1

#define _hw_read__m1(p,a, r,rw,ra,rwm,rfm, rbn,rbp)	\
  _hw_read_r##rw(a+ra,rbn,rbp)

#define _hw_read__m2(p,a,					\
		     r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,	\
		     r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2)	\
  ((_hw_read_r##rw1(a+ra1,rbn1,rbp1)<<vbp1) |			\
   (_hw_read_r##rw2(a+ra2,rbn2,rbp2)<<vbp2))


/*	_hw/_hwa_write( _m*, v );
 */
#define _hw_write(...)			_hw_write_2(__VA_ARGS__) /* Internal use */
#define _hw_write_2(x,...)		_hw_write_##x(__VA_ARGS__)
//#define _hw_write(...)	_HW_SPEC_2(hw_write, __VA_ARGS__) /* Does not work */

#define _hw_write__m1(cn,ca, rn,rw,ra,rwm,rfm, rbn,rbp, v)	\
  _hw_write_r##rw(ca+ra,rwm,rfm,rbn,rbp,v)
#define _hw_write__m2(cn,ca,					\
		       rn1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
		       rn2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2, v)		\
  do { _hw_write_r##rw1(ca+ra1,rwm1,rfm1,rbn1,rbp1, (v>>vbp1)&((1<<rbn1)-1)); \
      _hw_write_r##rw2(ca+ra2,rwm2,rfm2,rbn2,rbp2, (v>>vbp2)&((1<<rbn2)-1)); } while(0)

#define _hwa_write(...)			_hwa_write_2(__VA_ARGS__) /* Internal use */
#define _hwa_write_2(x,...)		_hwa_write_##x(x,__VA_ARGS__)

#define _hwa_write__m1(p,a, r,rw,ra,rwm,rfm, bn,bp, v)	\
  _hwa_write_r##rw( &hwa->p.r, rwm,rfm, bn,bp, v )

#define _hwa_write__m2(_m2,cn,ca,					\
			 r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
			 r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2, v)	\
  do {									\
    _hwa_write_r##rw1(&hwa->cn.r1, rwm1,rfm1, rbn1,rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
      _hwa_write_r##rw2(&hwa->cn.r2, rwm2,rfm2, rbn2,rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); \
  } while(0)


/*  Functions used to write into the HWA context using a pointer instead of a
 *  name (creg)
 */
#define _hwa_writep__m1(_0,_1,rn,rw,ra,rwm,rfm, bn,bp, p,v)	\
  _hwa_write_r##rw( &p->rn, rwm,rfm, bn,bp,v)

#define _hwa_writep__m1x(p,a,r,rw,ra,rwm,rfm, bn,bp, p0,v)	/* result of an _irg */	\
  _hwa_write_r##rw( &hwa->p.r, rwm,rfm, bn,bp,v)

#define _hwa_writep__m2(_0,_1,						\
		       r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
		       r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2, p,v )	\
  do { _hwa_write_r##rw1(&p->r1, rwm1,rfm1, rbn1,rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
      _hwa_write_r##rw2(&p->r2, rwm2,rfm2, rbn2,rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0)



/*	hw/hwa_write_reg(...): write register.
 */
//#define hw_write_reg(p,b,v)		_hw_write(_hw_xpr(p,b),v)
//#define hwa_write_reg(p,b,v)		_hwa_write(_hw_xpr(p,b),v)
//#define _hw_write_reg(p,b,v)		_hw_write(_hw_xpr(p,b),v)


/*  Write some bits of a memory definition
 *
 *	_hw_write_bits( mdef, bn, bp, v );
 */
#define _hw_write_bits(...)		_hw_wrb(__VA_ARGS__)
#define _hw_wrb(t,...)			_hw_wrb_##t(__VA_ARGS__)
#define _hw_wrb__m1(p,a,r,rw,ra,rwm,rfm,rbn,rbp, bn,bp, v)\
  _hw_write_r##rw(a+ra,rwm,rfm,bn,bp,v)

/* #define _hwa_write_reg(...)		_hwa_write_reg_2(__VA_ARGS__) */
/* #define _hwa_write_reg_2(n,c,i,a, r, v)	_hwa_write_reg_3(_hw_reg(n,c,i,a,r),v) */
/* #define _hwa_write_reg_3(...)		_hwa_write_reg_4(__VA_ARGS__) */
/* #define _hwa_write_reg_4(x,...)		_hwa_write_##x(x,__VA_ARGS__) */

/* #define _hwa_write_reg(p,m,v)		_hwa_write_reg_2(_hw_xpr(p,m),v) */
/* #define _hwa_write_reg_2(...)		_hwa_write_reg_4(__VA_ARGS__) */
/* //_hwa_write_reg_4(_m1, core0,0, mcucr,8,0x55,0xFF,0x00, 1,5,sleep); */
/* #define _hwa_write_reg_4(x,...)		_hwa_write_##x(__VA_ARGS__) */

/*	Write register in hwa_t struct. Internal use only, no argument checking
 */
/* #define _hwa_write_creg(p,c,m,v)		_hwa_wrpcr_2(_hw_creg(c,m), p,v) */
/* #define _hwa_wrpcr_2(...)		_hwa_wrpcr_3(__VA_ARGS__) */
/* #define _hwa_wrpcr_3(t,...)		_hwa_wrpcr_##t(__VA_ARGS__) */

/* #define _hwa_wrpcr__m1(_0,_1,rn,rw,ra,rwm,rfm, bn,bp, p,v)	\ */
/*   _hwa_write_r##rw( &p->rn, rwm,rfm, bn,bp,v) */

/* #define _hwa_wrpcr__m1x(p,a,r,rw,ra,rwm,rfm, bn,bp, p0,v)	\ */
/*   _hwa_write_r##rw( &hwa->p.r, rwm,rfm, bn,bp,v) */

/* #define _hwa_wrpcr__m2(_0,_1,						\ */
/* 		       r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\ */
/* 		       r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2, p,v )	\ */
/*   do { _hwa_write_r##rw1(&p->r1, rwm1,rfm1, rbn1,rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \ */
/*       _hwa_write_r##rw2(&p->r2, rwm2,rfm2, rbn2,rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0) */

#define _hwa_begin(n)			_hwa_begin_2(n, hw_##n)
#define _hwa_begin_2(...)		_hwa_begin_3(__VA_ARGS__)
#define _hwa_begin_3(n,c,i,a)		__hwa_begin_##c(&hwa->n,a)


#define _hwa_init(n)			_hwa_init_2(n, hw_##n)
#define _hwa_init_2(...)		_hwa_init_3(__VA_ARGS__)
#define _hwa_init_3(n,c,i,a)		__hwa_init_##c(&hwa->n)


#define _hwa_solve(n)			_hwa_solve_2(n, hw_##n)
#define _hwa_solve_2(...)		_hwa_solve_3(__VA_ARGS__)
#define _hwa_solve_3(n,c,i,a)		__hwa_solve_##c(hwa, &hwa->n)


#define _hwa_commit(n)			_hwa_commit_2(n, hw_##n)
#define _hwa_commit_2(...)		_hwa_commit_3(__VA_ARGS__)
#define _hwa_commit_3(n,c,i,a)		__hwa_commit_##c(hwa,&hwa->n)


#define _hwa_begin_reg_p(p,a,c,r)		_hwa_berp_2(p,a,c,r,hw_##c##_##r)
#define _hwa_berp_2(...)			_hwa_berp_3(__VA_ARGS__)
#define _hwa_berp_3(p,a,c,r, rt,rw,ra,rwm,rfm)	_hwa_begin_r##rw(&p->r,a+ra)


HW_INLINE void _hwa_begin_r8 ( hwa_r8_t *r, intptr_t a )
{
  r->a		= a ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}

HW_INLINE void _hwa_begin_r16 ( hwa_r16_t *r, intptr_t a )
{
  r->a		= a ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}


/** \brief	Inits an HWA register to a specific value (usually the reset value).
 */
HW_INLINE void _hwa_set_r8 ( hwa_r8_t *r, uint8_t v )
{
  if ( r->mmask )
    HWA_ERR("commit required before resetting.");

  r->mmask = 0xFF ;
  r->mvalue = v ;
}

HW_INLINE void _hwa_set_r16 ( hwa_r16_t *r, uint16_t v )
{
  if ( r->mmask )
    HWA_ERR("commit required before resetting.");

  r->mmask = 0xFFFF ;
  r->mvalue = v ;
}


/** \brief	Writes an HWA register
 *
 *	Write bits according to bn/bp. mmask is set even if the value is not
 *  	modified. hwa_commit() will check if the register has effectively been
 *  	modified.
 */
HW_INLINE void _hwa_write_r8 ( hwa_r8_t *r, 
			       uint8_t rwm, uint8_t rfm,
			       uint8_t bn, uint8_t bp, uint8_t v )
{
  if (bn == 0)
    HWA_ERR("no bit to be changed?");

  if (v > (1U<<bn)-1)
    HWA_ERR("value too high for number of bits.");

  uint8_t sm = ((1U<<bn)-1) << bp ;	/* shifted mask  */

  //  *((volatile uint8_t*)0) = sm ;

  uint8_t sv = v << bp ;		/* shifted value */

  //  *((volatile uint8_t*)0) = sv ;

  if ((rwm & sm) != sm)
    HWA_ERR("bits not writeable.");

  if ((r->mmask & sm) != 0 && (r->mvalue & sm) != sv)
    HWA_ERR("committing is required before setting a new value.");

  if ( sm & rfm )
    if ( v == 0 )
      HWA_ERR("flag bit can only be cleared by writing 1 into it.");

  r->mmask |= sm ;
  r->mvalue = (r->mvalue & ~sm) | (sm & sv) ;
}

HW_INLINE void _hwa_write_r16 ( hwa_r16_t *r,
				uint16_t rwm, uint16_t rfm,
				uint8_t bn, uint8_t bp, uint16_t v )
{
  if (bn == 0)
    HWA_ERR("no bit to be changed?");

  if (v > (1U<<bn)-1)
    HWA_ERR("value too high for bits number.");

  uint16_t sm = ((1U<<bn)-1) << bp ;	/* shifted mask  */
  uint16_t sv = v << bp ;		/* shifted value */

  if ((rwm & sm) != sm)
    HWA_ERR("bits not writeable.");

  if ((r->mmask & sm) != 0 && (r->mvalue & sm) != sv)
    HWA_ERR("commit required before setting a new value.");

  if ( sm & rfm )
    if ( v == 0 )
      HWA_ERR("flag bit can only be cleared by writing 1 into it.");

  r->mmask |= sm ;
  r->mvalue = (r->mvalue & ~sm) | (sm & sv) ;
}


/** 
 * @addtogroup dev
 * \brief	Initialize an HWA register
 *
 *  \param c	class of the register.
 *  \param i	instance of the register.
 *  \param r	name of the register.
 *
 * \hideinitializer
 */
#define _hwa_begin_reg(...)			_hwa_begin_reg_2(__VA_ARGS__)
#define _hwa_begin_reg_2(n,c,i,a, r)		_hwa_begin_reg_3(n,a,r, hw_##c##_##r)
#define _hwa_begin_reg_3(...)			_hwa_begin_reg_4(__VA_ARGS__)
#define _hwa_begin_reg_4(n,a,r, rt,rw,ra, ... )	_hwa_begin_r##rw( &hwa->n.r, a+ra )


HW_INLINE void hwa_check_optimizations ( uint8_t x )
{
  if (x) { HWA_ERR("you may have forgotten to turn optimizations on."); }
}


/** \brief	Begin an HWA session. Allows the use of the hwa_...(...) functions.
 *
 *	Instanciate an hwa_t structure named 'hwa' that virtualizes the
 *	hardware. Nothing is done on the hardware until hwa_commit() is called.
 *
 *	Calls hwa_begin_all() that must be defined in hwa_<device>_2.h.
 *
 * \hideinitializer
 */
#define hwa_begin()							\
  hwa_check_optimizations(0);						\
  hwa_t hwa_st ; hwa_t *hwa = &hwa_st ;					\
  _hwa_begin_all(hwa) ;							\
  uint8_t hwa_xcommit = 0 /* Will warn if hwa_commit() is not called */


#define hwa_begin_from_reset()						\
  hwa_check_optimizations(0);						\
  hwa_t hwa_st ; hwa_t *hwa = &hwa_st ;					\
  _hwa_begin_all(hwa) ;							\
  _hwa_init_all(hwa) ;							\
  hwa_nocommit() ;							\
  uint8_t hwa_xcommit = 0


/** \brief	Commit configuration to hardware.
 *
 *	Solve the constraints imposed by the developer, then do the required
 *	hardware register writes.
 *
 *	Calls _hwa_commit() that must be defined in hwa_ \e HW_DEVICE _l2.h.
 *
 * \hideinitializer
 */
#define hwa_commit()					\
  do {							\
    uint8_t foo __attribute__((unused)) = hwa_xcommit ;	\
    hwa->commit = 1 ;					\
    _hwa_commit_all(hwa);				\
  } while(0)


/** \brief	Same as hwa_commit() but do not write to hardware.
 *
 *	This is used to modify a configuration that's already been
 *	committed.
 *
 * \hideinitializer
 */
#define hwa_nocommit()				\
  do {						\
    hwa->commit = 0 ;				\
    _hwa_commit_all(hwa);			\
  } while(0)


#define _hwa_commit_reg(...)			_hwa_commit_reg_2(__VA_ARGS__)
#define _hwa_commit_reg_2(n,c,i,a, r, co)	_hwa_commit_reg_3(n,a,r, hw_##c##_##r, co)
#define _hwa_commit_reg_3(...)			_hwa_commit_reg_4(__VA_ARGS__)
#define _hwa_commit_reg_4(n,a,r, rt,rw,ra,rwm,rfm, co )	\
  _hwa_commit_r##rw( &hwa->n.r,rwm,rfm, co )


/*	Include device-specific declarations
 */
#ifdef DOXYGEN
#  include "hwa_device_2.h"
#else
#  include HW_QUOTE(HW_G2(hwa,HW_DEVICE)_2.h)
#endif
