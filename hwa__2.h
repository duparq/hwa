
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/** \file
 *  \brief	Definitions producing C code.
 */

#define hw_state_on			, 1
#define hw_state_off			, 0


/*	hw/hwa_config(...): configure something (method)
 */
#define hw_config(...)			HW_MTHD(hw_config, __VA_ARGS__)
#define hwa_config(...)			HW_MTHD(hwa_config, __VA_ARGS__)


/*	hw_clear(...): clear something (method)
 */
#define hw_clear(...)			HW_MTHD(hw_clear, __VA_ARGS__)
#define hwa_clear(...)			HW_MTHD(hwa_clear, __VA_ARGS__)


/*	hw_lock_to_zero(...): clear something and keep it at 0 (mehod)
 */
#define hw_lock_to_zero(...)		HW_MTHD(hw_lock_to_zero, __VA_ARGS__)
#define hwa_lock_to_zero(...)		HW_MTHD(hwa_lock_to_zero, __VA_ARGS__)


/*	hw_read(...): read something (method)
 */
#define hw_read(...)			HW_MTHD(hw_read, __VA_ARGS__)

#define hw_def_hw_read_bits1		, _hw_read_bits1
#define hw_def_hw_read_bits2		, _hw_read_bits2

#define _hw_read_bits1(bits1, n,a, rn,rw,ra,rwm,rfm, rbn,rbp)	\
  _hw_read_r##rw(a+ra,rbn,rbp)
#define _hw_read_bits2(bits2, n,a,				\
		       r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,	\
		       r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2)	\
  ((_hw_read_r##rw1(a+ra1,rbn1,rbp1)<<vbp1) |			\
   (_hw_read_r##rw2(a+ra2,rbn2,rbp2)<<vbp2))


/*	hw_read_reg(...): short for hw_read( hw_reg(...) )
 */
#define hw_read_reg(i,r)		_hw_readreg_2(hw_reg(i,r))
#define _hw_readreg_2(...)		_hw_readreg_3(__VA_ARGS__)
#define _hw_readreg_3(t,...)		_hw_read_##t(t,__VA_ARGS__)
/*
 *	Internal use, no argument checking.
 */
#define _hw_read_reg(...)		_hw_read_reg_2(__VA_ARGS__)
#define _hw_read_reg_2(c,n,i,a, r)	_hw_readreg_2(_hw_reg(c,n,i,a,r))


/*	hw/hwa_release(...): release something (method)
 */
#define hw_release(...)			HW_MTHD(hw_release, __VA_ARGS__)
#define hwa_release(...)		HW_MTHD(hwa_release, __VA_ARGS__)


/*	hw_status(...): status of something (method)
 */
#define hw_status(...)			HW_MTHD(hw_status, __VA_ARGS__)


/*	hw/hwa_toggle(...): toggle something, probably an io (method)
 */
#define hw_toggle(...)			HW_MTHD(hw_toggle, __VA_ARGS__)
#define hwa_toggle(...)			HW_MTHD(hwa_toggle, __VA_ARGS__)


/*	hw/hwa_turn(...): turn something on/off (method)
 */
#define hw_turn(...)			HW_MTHD(hw_turn, __VA_ARGS__)
#define hwa_turn(...)			HW_MTHD(hwa_turn, __VA_ARGS__)


/*	hw/hwa_trigger(...): trigger something (method)
 */
#define hw_trigger(...)			HW_MTHD(hw_trigger, __VA_ARGS__)
#define hwa_trigger(...)		HW_MTHD(hwa_trigger, __VA_ARGS__)


/*	hw/hwa_write(...): write something (method)
 */
#define hw_write(...)			HW_MTHD(hw_write, __VA_ARGS__)
#define hwa_write(...)			HW_MTHD(hwa_write, __VA_ARGS__)

#define hw_def_hw_write_bits1		, _hw_write_bits1
#define hw_def_hw_write_bits2		, _hw_write_bits2

#define _hw_write_bits1(bits1, cn,ca, rn,rw,ra,rwm,rfm, rbn,rbp, v)	\
  _hw_write_r##rw(ca+ra,rwm,rfm,rbn,rbp,v)
#define _hw_write_bits2(bits2, cn,ca,					\
			rn1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
			rn2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2, v)	\
  do { _hw_write_r##rw1(ca+ra1,rwm1,rfm1,rbn1,rbp1, (v>>vbp1)&((1<<rbn1)-1)); \
      _hw_write_r##rw2(ca+ra2,rwm2,rfm2,rbn2,rbp2, (v>>vbp2)&((1<<rbn2)-1)); } while(0)

#define hw_def_hwa_write_bits1		, _hwa_write_bits1
#define hw_def_hwa_write_bits2		, _hwa_write_bits2

#define _hwa_write(...)			_hwa_write_2(__VA_ARGS__) /* Internal use */
#define _hwa_write_2(x,...)		_hwa_write_##x(x,__VA_ARGS__)

#define _hwa_write_bits1(bits1, cn,ca, rn,rw,ra,rwm,rfm, bn,bp, v)	\
  _hwa_write_r##rw( &hwa->cn.rn, bn,bp, v )

#define _hwa_write_bits2(bits2,cn,ca,					\
			 r1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
			 r2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2, v)	\
  do { _hwa_write_r##rw1(&hwa->cn.r1, rbn1, rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
      _hwa_write_r##rw2(&hwa->cn.r2, rbn2, rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0)


/*	hw/hwa_write_reg(...): write register.
 */
#define hw_write_reg(n,r,v)		_hw_wrtreg_2(hw_reg(n,r),v)
#define _hw_wrtreg_2(...)		_hw_wrtreg_3(__VA_ARGS__)
#define _hw_wrtreg_3(t,...)		_hw_write_##t(t,__VA_ARGS__)

#define hwa_write_reg(n,r,v)		_hwa_wrtreg_2(hw_reg(n,r),v)
#define _hwa_wrtreg_2(...)		_hwa_wrtreg_3(__VA_ARGS__)
#define _hwa_wrtreg_3(t,...)		_hwa_write_##t(t,__VA_ARGS__)

/*	Internal use, no argument checking.
 */
#define _hw_write_reg(...)		_hw_write_reg_2(__VA_ARGS__)
#define _hw_write_reg_2(c,n,i,a, r, v)	_hw_write_reg_3(_hw_reg(c,n,i,a,r),v)
#define _hw_write_reg_3(...)		_hw_write_reg_4(__VA_ARGS__)
#define _hw_write_reg_4(x,...)		_hw_write_##x(x,__VA_ARGS__)

#define _hwa_write_reg(...)		_hwa_write_reg_2(__VA_ARGS__)
#define _hwa_write_reg_2(c,n,i,a, r, v)	_hwa_write_reg_3(_hw_reg(c,n,i,a,r),v)
#define _hwa_write_reg_3(...)		_hwa_write_reg_4(__VA_ARGS__)
#define _hwa_write_reg_4(x,...)		_hwa_write_##x(x,__VA_ARGS__)

/*	Write register in hwa_t struct. Internal use only, no argument checking!
 */
#define _hwa_write_p(...)		_hwa_write_p_2(__VA_ARGS__)
#define _hwa_write_p_2(p, ...)						\
  HW_G2(_hwa_write_p_xfn, HW_IS(,hw_def_hwa_write_p_##__VA_ARGS__))(p, __VA_ARGS__)
#define _hwa_write_p_xfn_1(p, t,...)	HW_A1(hw_def_hwa_write_p_##t)(p,t,__VA_ARGS__)
#define _hwa_write_p_xfn_0(p, ...)	HW_G2(_hwa_write_p, HW_IS(0,__VA_ARGS__))(p,__VA_ARGS__)
#define _hwa_write_p_0(...)						\
    HW_ERR("can not process hwa_write_p(" HW_QUOTE(__VA_ARGS__) ",...).")
#define _hwa_write_p_1(...)		__VA_ARGS__

#define hw_def_hwa_write_p_bits1	, _hwa_write_p_bits1
#define hw_def_hwa_write_p_bits2	, _hwa_write_p_bits2

#define _hwa_write_p_bits1(p, bits1, cn,ca,			\
			   rn1,rw1,ra1,rwm1,rfm1,rbn1,rbp1, v)	\
  _hwa_write_r##rw1( &p->rn1, rbn1, rbp1, v )

#define _hwa_write_p_bits2(p, bits2, cn,ca,				\
			   rn1,rw1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,	\
			   rn2,rw2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2, v)	\
  do { _hwa_write_r##rw1(&p->rn1, rbn1, rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
      _hwa_write_r##rw2(&p->rn2, rbn2, rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0)


/** \brief	Initializes an 8-bits HWA register.
 *
 *  \param r		pointer on the hwa register.
 *  \param x_reset	1 if the after-reset value has to be written into the register.
 *  \param p		address of the hardware register.
 *  \param rwm		hardware register's writeable bits mask.
 */
HW_INLINE void _hwa_begin_r8 ( hwa_r8_t *r, intptr_t ra, uint8_t rwm, uint8_t rfm )
{
  r->ra		= ra ;
  r->rwm	= rwm ;
  r->rfm	= rfm ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}

/** \brief	Initializes a 16-bits HWA register. See _hwa_begin_r8() for details.
 */
HW_INLINE void _hwa_begin_r16 ( hwa_r16_t *r, intptr_t ra, uint16_t rwm, uint16_t rfm )
{
  r->ra		= ra ;
  r->rwm	= rwm ;
  r->rfm	= rfm ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}


/** \brief	Resets an 8-bits HWA register.
 */
HW_INLINE void _hwa_reset_r8 ( hwa_r8_t *r, uint8_t v )
{
  /* FIXME: should check that there's nothing to commit first */
  r->mmask = r->rwm ;
  r->mvalue = v ;
}

HW_INLINE void _hwa_reset_r16 ( hwa_r16_t *r, uint16_t v )
{
  r->mmask = r->rwm ;
  r->mvalue = v ;
}


/** \brief	Writes an 8-bits HWA register
 *
 *	Write bits according to bn/bp. mmask is set even if the value is not
 *  	modified. hwa_commit() will check if the register has effectively been
 *  	modified.
 */
HW_INLINE void _hwa_write_r8 ( hwa_r8_t *r, uint8_t bn, uint8_t bp, uint8_t v )
{
  if (bn == 0)
    HWA_ERR("no bit to be changed?");

  if (v > (1U<<bn)-1)
    HWA_ERR("value too high for number of bits.");

  uint8_t sm = ((1U<<bn)-1) << bp ;	/* shifted mask  */

  //  *((volatile uint8_t*)0) = sm ;

  uint8_t sv = v << bp ;		/* shifted value */

  //  *((volatile uint8_t*)0) = sv ;

  if ((r->rwm & sm) != sm)
    HWA_ERR("bits not writeable.");

  if ((r->mmask & sm) != 0 && (r->mvalue & sm) != sv)
    HWA_ERR("committing is required before setting a new value.");

  if ( sm & r->rfm )
    if ( v == 0 )
      HWA_ERR("flag bit can only be cleared by writing 1 into it.");

  r->mmask |= sm ;
  r->mvalue = (r->mvalue & ~sm) | (sm & sv) ;
}

/** \brief	Writes a 16-bits HWA register
 *
 *  \copydetails hwa_write_r8
 */
HW_INLINE void _hwa_write_r16 ( hwa_r16_t *r, uint8_t bn, uint8_t bp, uint16_t v )
{
  if (bn == 0)
    HWA_ERR("no bit to be changed?");

  if (v > (1U<<bn)-1)
    HWA_ERR("value too high for bits number.");

  uint16_t sm = ((1U<<bn)-1) << bp ;	/* shifted mask  */
  uint16_t sv = v << bp ;		/* shifted value */

  if ((r->rwm & sm) != sm)
    HWA_ERR("bits not writeable.");

  if ((r->mmask & sm) != 0 && (r->mvalue & sm) != sv)
    HWA_ERR("commit required before setting a new value.");

  r->mmask |= sm ;
  r->mvalue = (r->mvalue & ~sm) | (sm & sv) ;
}


/** \brief	Initialize an HWA register
 *
 *  \param c	class of the register.
 *  \param i	instance of the register.
 *  \param r	name of the register.
 *
 * \hideinitializer
 */
#define _hwa_begin_reg(...)			_hwa_begin_reg_2(__VA_ARGS__)
#define _hwa_begin_reg_2(c,n,i,a, r)		_hwa_begin_reg_3(n,a,r, hw_##c##_##r)
#define _hwa_begin_reg_3(...)			_hwa_begin_reg_4(__VA_ARGS__)
#define _hwa_begin_reg_4(n,a,r, rt,rw,ra,rwm,rfm )	\
  _hwa_begin_r##rw( &hwa->n.r, a+ra, rwm, rfm )


/** \brief	Begin an HWA session. Allows the use of the hwa_...(...) functions.
 *
 *	Instanciate an hwa_t structure named 'hwa' that virtualizes the
 *	hardware. Nothing is done on the hardware until hwa_commit() is called.
 *
 *	Calls hwa_begin_all() that must be defined in hwa_<device>_2.h.
 *
 * \hideinitializer
 */

HW_INLINE void _hwa_begin_all(hwa_t*) ;		/* defined in device-specific files */
HW_INLINE void _hwa_reset_all(hwa_t*) ;		/* defined in device-specific files */

HW_INLINE void __hwa_begin( hwa_t *hwa )
{
  if (0) { HWA_ERR("you may have forgotten to turn optimizations on."); }
  _hwa_begin_all(hwa) ;
}


#define hwa_begin()							\
  hwa_t hwa_st ; hwa_t *hwa = &hwa_st ; __hwa_begin(hwa) ;		\
  uint8_t hwa_commit = 0 /* Will warn if hwa_commit() is not called */


#define hwa_begin_from_reset()						\
  hwa_t hwa_st ; hwa_t *hwa = &hwa_st ; __hwa_begin(hwa) ;		\
  uint8_t hwa_commit = 0 ; /* Will warn if hwa_commit() is not called */ \
  _hwa_reset_all(hwa) ; hwa_nocommit()


#define hwa_reset_all()		_hwa_reset_all(hwa)


/** \brief	Commit configuration to hardware.
 *
 *	Solve the constraints imposed by the developer, then do the required
 *	hardware register writes.
 *
 *	Calls _hwa_commit_all() that must be defined in hwa_ \e HW_DEVICE _l2.h.
 *
 * \hideinitializer
 */
#define hwa_commit()					\
  do {							\
    uint8_t foo __attribute__((unused)) = hwa_commit ;	\
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


/*	Include device-specific declarations
 */
#ifdef DOXYGEN
#  include "hwa_device_2.h"
#else
#  include HW_QUOTE(HW_G2(hwa,HW_DEVICE)_2.h)
#endif
