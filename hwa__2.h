
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/** \file
 *  \brief	Necessary definitions for C code production.
 */

#define hw_state_on		, 1
#define hw_state_off		, 0


/*	hw/hwa_config(...): configure something (generic)
 */
#define hw_config(...)		_hw_config_2(__VA_ARGS__)
#define _hw_config_2(...)	HW_G2(_hw_config_xfn,			\
				      HW_IS(,hw_def_hw_config_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_config_xfn_1(c,...)	HW_A1(hw_def_hw_config_##c)(c,__VA_ARGS__)
#define _hw_config_xfn_0(...)	HW_G2(_hw_config, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_config_0(...)	HW_ERR("can not process hw_config(" HW_QUOTE(__VA_ARGS__) ",...).")
#define _hw_config_1(...)	__VA_ARGS__

#define hwa_config(...)		_hwa_config_2(__VA_ARGS__)
#define _hwa_config_2(...)	HW_G2(_hwa_config_xfn,			\
				      HW_IS(,hw_def_hwa_config_##__VA_ARGS__))(__VA_ARGS__)
#define _hwa_config_xfn_1(t,...)	HW_A1(hw_def_hwa_config_##t)(t,__VA_ARGS__)
#define _hwa_config_xfn_0(...)	HW_G2(_hwa_config, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hwa_config_0(...)	HW_ERR("can not process hwa_config(" HW_QUOTE(__VA_ARGS__) ",...).")
#define _hwa_config_1(...)	__VA_ARGS__


/*	hw_clear(...): clear something (generic)
 */
#define hw_clear(...)		_hw_clear_2(__VA_ARGS__)
#define _hw_clear_2(...)	HW_G2(_hw_clear_xfn,			\
				      HW_IS(,hw_def_hw_clear_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_clear_xfn_1(c,...)	HW_A1(hw_def_hw_clear_##c)(c,__VA_ARGS__)
#define _hw_clear_xfn_0(...)	HW_G2(_hw_clear, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_clear_0(...)	HW_ERR("hw_clear(" HW_QUOTE(__VA_ARGS__) ",...) is not defined.")
#define _hw_clear_1(...)	__VA_ARGS__


/*	hw_lock_to_zero(...): clear something and keep it at 0 (generic)
 */
#define hw_lock_to_zero(...)		_hw_lock0_2(__VA_ARGS__)
#define _hw_lock0_2(...)	HW_G2(_hw_lock0_xfn,			\
				      HW_IS(,hw_def_hw_lock_to_zero_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_lock0_xfn_1(c,...)	HW_A1(hw_def_hw_lock_to_zero_##c)(c,__VA_ARGS__)
#define _hw_lock0_xfn_0(...)	HW_G2(_hw_lock0, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_lock0_0(...)	HW_ERR("hw_lock0(" HW_QUOTE(__VA_ARGS__) ",...) is not defined.")
#define _hw_lock0_1(...)	__VA_ARGS__


/*	hw_read(...): read something (generic)
 */
#define hw_read(...)		_hw_read_2(__VA_ARGS__)
#define _hw_read_2(...)		HW_G2(_hw_read_xfn, \
				      HW_IS(,hw_def_hw_read_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_read_xfn_1(t,...)	HW_A1(hw_def_hw_read_##t)(t,__VA_ARGS__)
#define _hw_read_xfn_0(...)	HW_G2(_hw_read, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_read_0(...)		HW_ERR("can not process hw_read(" HW_QUOTE(__VA_ARGS__) ",...).")
#define _hw_read_1(...)		__VA_ARGS__

#define hw_def_hw_read_bits1	, _hw_read_bits1
#define hw_def_hw_read_bits2	, _hw_read_bits2

#define _hw_read_bits1(bits1, n,a, rn,rw,ra,riv,rwm,rfm, rbn,rbp)	\
  _hw_read_r##rw(a+ra,rbn,rbp)
#define _hw_read_bits2(bits2, n,a,				\
		       r1,rw1,ra1,riv1,rwm1,rfm1,rbn1,rbp1,vbp1,	\
		       r2,rw2,ra2,riv2,rwm2,rfm2,rbn2,rbp2,vbp2)	\
  ((_hw_read_r##rw1(a+ra1,rbn1,rbp1)<<vbp1) |			\
   (_hw_read_r##rw2(a+ra2,rbn2,rbp2)<<vbp2))


/*	hw_read_reg(...): short for hw_read( hw_reg(...) )
 */
#define hw_read_reg(n,r)	_hw_rdbts_2(hw_reg(n,r))
#define _hw_rdbts_2(...)	_hw_rdbts_3(__VA_ARGS__)
#define _hw_rdbts_3(t,...)	_hw_read_##t(t,__VA_ARGS__)
/*
 *	Internal use, no argument checking.
 */
#define _hw_read_reg(...)		_hw_read_reg_2(__VA_ARGS__)
#define _hw_read_reg_2(c,n,i,a, r)	_hw_rdbts_2(_hw_reg(c,n,i,a,r))


/*	hw_release(...): release something (generic)
 */
#define hw_release(...)		_hw_release_2(__VA_ARGS__)
#define _hw_release_2(...)	HW_G2(_hw_release_xfn,			\
				      HW_IS(,hw_def_hw_release_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_release_xfn_1(c,...)	HW_A1(hw_def_hw_release_##c)(c,__VA_ARGS__)
#define _hw_release_xfn_0(...)	HW_G2(_hw_release, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_release_0(...)	HW_ERR("hw_release(" HW_QUOTE(__VA_ARGS__) ",...) is not defined.")
#define _hw_release_1(...)	__VA_ARGS__


/*	hw_toggle(...): toggle something, (generic but probably an io)
 */
#define hw_toggle(...)		_hw_toggle_2(__VA_ARGS__)
#define _hw_toggle_2(...)	HW_G2(_hw_toggle_xfn, HW_IS(,hw_def_hw_toggle_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_toggle_xfn_1(t,...)	HW_A1(hw_def_hw_toggle_##t)(t,__VA_ARGS__)
#define _hw_toggle_xfn_0(...)	HW_G2(_hw_toggle, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_toggle_0(...)	HW_ERR("can not process hw_toggle(" HW_QUOTE(__VA_ARGS__) ",...).")
#define _hw_toggle_1(...)	__VA_ARGS__


/*	hw_turn(...): turn something on/off (generic)
 */
#define hw_turn(...)		_hw_turn_2(__VA_ARGS__)
#define _hw_turn_2(...)		HW_G2(_hw_turn_xfn, \
				      HW_IS(,hw_def_hw_turn_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_turn_xfn_1(t,...)	HW_A1(hw_def_hw_turn_##t)(t,__VA_ARGS__)
#define _hw_turn_xfn_0(...)	HW_G2(_hw_turn, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_turn_0(...)		HW_ERR("can not process hw_turn(" HW_QUOTE(__VA_ARGS__) ",...).")
#define _hw_turn_1(...)		__VA_ARGS__


/*	hwa_turn(...): turn something on/off (generic)
 */
#define hwa_turn(...)		_hwa_turn_2(__VA_ARGS__)
#define _hwa_turn_2(...)	HW_G2(_hwa_turn_xfn, \
				      HW_IS(,hw_def_hwa_turn_##__VA_ARGS__))(__VA_ARGS__)
#define _hwa_turn_xfn_1(t,...)	HW_A1(hw_def_hwa_turn_##t)(t,__VA_ARGS__)
#define _hwa_turn_xfn_0(...)	HW_G2(_hwa_turn, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hwa_turn_0(...)	HW_ERR("can not process hwa_turn(" HW_QUOTE(__VA_ARGS__) ",...).")
#define _hwa_turn_1(...)	__VA_ARGS__


/*	hw_trigger(...): trigger something on/off (generic)
 */
#define hw_trigger(...)		_hw_trigger_2(__VA_ARGS__)
#define _hw_trigger_2(...)	HW_G2(_hw_trigger_xfn, \
				      HW_IS(,hw_def_hw_trigger_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_trigger_xfn_1(t,...)	HW_A1(hw_def_hw_trigger_##t)(t,__VA_ARGS__)
#define _hw_trigger_xfn_0(...)	HW_G2(_hw_trigger, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_trigger_0(...)	HW_ERR("can not process hw_trigger("HW_QUOTE(__VA_ARGS__)".")
#define _hw_trigger_1(...)	__VA_ARGS__

/*	hwa_trigger(...): trigger something on/off (generic)
 */
#define hwa_trigger(...)	_hwa_trigger_2(__VA_ARGS__)
#define _hwa_trigger_2(...)	HW_G2(_hwa_trigger_xfn, \
				      HW_IS(,hw_def_hwa_trigger_##__VA_ARGS__))(__VA_ARGS__)
#define _hwa_trigger_xfn_1(t,...)	HW_A1(hw_def_hwa_trigger_##t)(t,__VA_ARGS__)
#define _hwa_trigger_xfn_0(...)	HW_G2(_hwa_trigger, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hwa_trigger_0(...)	HW_ERR("can not process hwa_trigger("HW_QUOTE(__VA_ARGS__)".")
#define _hwa_trigger_1(...)	__VA_ARGS__


/*	hw_write(...): write something (generic)
 */
#define hw_write(...)		_hw_write_2(__VA_ARGS__)
#define _hw_write_2(...)	HW_G2(_hw_write_xfn, \
				      HW_IS(,hw_def_hw_write_##__VA_ARGS__))(__VA_ARGS__)
#define _hw_write_xfn_1(t,...)	HW_A1(hw_def_hw_write_##t)(t,__VA_ARGS__)
#define _hw_write_xfn_0(...)	HW_G2(_hw_write, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_write_0(...)	HW_ERR("can not process hw_write(" HW_QUOTE(__VA_ARGS__) ",...).")
#define _hw_write_1(...)	__VA_ARGS__

#define hw_def_hw_write_bits1		, _hw_write_bits1
#define hw_def_hw_write_bits2		, _hw_write_bits2

#define _hw_write_bits1(bits1, cn,ca, rn,rw,ra,riv,rwm,rfm, rbn,rbp, v)	\
  _hw_write_r##rw(ca+ra,rwm,rfm,rbn,rbp,v)
#define _hw_write_bits2(bits2, cn,ca,					\
		       rn1,rw1,ra1,riv1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
		       rn2,rw2,ra2,riv2,rwm2,rfm2,rbn2,rbp2,vbp2, v)		\
  do { _hw_write_r##rw1(ca+ra1,rwm1,rfm1,rbn1,rbp1, (v>>vbp1)&((1<<rbn1)-1)); \
      _hw_write_r##rw2(ca+ra2,rwm2,rfm2,rbn2,rbp2, (v>>vbp2)&((1<<rbn2)-1)); } while(0)


/*	hwa_write(...): write something (generic)
 */
#define hwa_write(...)		_hwa_write_2(__VA_ARGS__)
#define _hwa_write_2(...)	HW_G2(_hwa_write_xfn, HW_IS(,hw_def_hwa_write_##__VA_ARGS__))(__VA_ARGS__)
#define _hwa_write_xfn_1(t,...)	HW_A1(hw_def_hwa_write_##t)(t,__VA_ARGS__)
#define _hwa_write_xfn_0(...)	HW_G2(_hwa_write, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hwa_write_0(...)	HW_ERR("can not process hwa_write(" HW_QUOTE(__VA_ARGS__) ",...).")
#define _hwa_write_1(...)	__VA_ARGS__

#define hw_def_hwa_write_bits1		, _hwa_write_bits1
#define hw_def_hwa_write_bits2		, _hwa_write_bits2

#define _hwa_write_bits1(bits1, cn,ca, rn,rw,ra,riv,rwm,rfm, bn,bp, v)	\
  _hwa_write_r##rw( &hwa->cn.rn, bn,bp, v )

#define _hwa_write_bits2(bits2,cn,ca,					\
			r1,rw1,ra1,riv1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
			r2,rw2,ra2,riv2,rwm2,rfm2,rbn2,rbp2,vbp2, v)		\
  do { _hwa_write_r##rw1(&hwa->cn.r1, rbn1, rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
      _hwa_write_r##rw2(&hwa->cn.r2, rbn2, rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0)


/*	hw/hwa_write_reg(...)
 */
#define hw_write_reg(n,r,v)	_hw_wrbts_2(hw_reg(n,r),v)
#define _hw_wrbts_2(...)	_hw_wrbts_3(__VA_ARGS__)
#define _hw_wrbts_3(t,...)	_hw_write_##t(t,__VA_ARGS__)

#define hwa_write_reg(n,r,v)	_hwa_wrbts_2(hw_reg(n,r),v)
#define _hwa_wrbts_2(...)	_hwa_wrbts_3(__VA_ARGS__)
#define _hwa_wrbts_3(t,...)	_hwa_write_##t(t,__VA_ARGS__)


/*	Write hard registers. Internal use, no argument checking.
 */
#define _hw_write_reg(...)			_hw_write_reg_2(__VA_ARGS__)
#define _hw_write_reg_2(c,n,i,a, r, v)		_hw_write_reg_3(_hw_reg(c,n,i,a,r),v)
#define _hw_write_reg_3(...)			_hw_write_reg_4(__VA_ARGS__)
#define _hw_write_reg_4(x,...)			_hw_write_##x(x,__VA_ARGS__)

#define _hwa_write_reg(...)			_hwa_write_reg_2(__VA_ARGS__)
#define _hwa_write_reg_2(c,n,i,a, r, v)	_hwa_write_reg_3(_hw_reg(c,n,i,a,r),v)
#define _hwa_write_reg_3(...)			_hwa_write_reg_4(__VA_ARGS__)
#define _hwa_write_reg_4(x,...)		_hwa_write_##x(x,__VA_ARGS__)


/*	Write registers in hwa_t struct. Internal use only, no argument checking!
 */
#define _hwa_write_p(...)	_hwa_write_p_2(__VA_ARGS__)
#define _hwa_write_p_2(p, ...)	HW_G2(_hwa_write_p_xfn, HW_IS(,hw_def_hwa_write_p_##__VA_ARGS__))(p, __VA_ARGS__)
#define _hwa_write_p_xfn_1(p, t,...)	HW_A1(hw_def_hwa_write_p_##t)(p,t,__VA_ARGS__)
#define _hwa_write_p_xfn_0(p, ...)	HW_G2(_hwa_write_p, HW_IS(0,__VA_ARGS__))(p,__VA_ARGS__)
#define _hwa_write_p_0(...)	HW_ERR("can not process hwa_write_p(" HW_QUOTE(__VA_ARGS__) ",...).")
#define _hwa_write_p_1(...)	__VA_ARGS__

#define hw_def_hwa_write_p_bits1		, _hwa_write_p_bits1
#define hw_def_hwa_write_p_bits2		, _hwa_write_p_bits2

#define _hwa_write_p_bits1(p, bits1, cn,ca,			\
			  rn1,rw1,ra1,riv1,rwm1,rfm1,rbn1,rbp1, v)	\
  _hwa_write_r##rw1( &p->rn1, rbn1, rbp1, v )

#define _hwa_write_p_bits2(p, bits2, cn,ca,				\
			  rn1,rw1,ra1,riv1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
			  rn2,rw2,ra2,riv2,rwm2,rfm2,rbn2,rbp2,vbp2, v)	\
  do { _hwa_write_r##rw1(&p->rn1, rbn1, rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
      _hwa_write_r##rw2(&p->rn2, rbn2, rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0)


/** \brief	Initializes an 8-bits HWA register.
 *
 *  \param r		pointer on the hwa register.
 *  \param x_reset	1 if the after-reset value has to be written into the register.
 *  \param p		address of the hardware register.
 *  \param riv		after-reset value of the hardware register.
 *  \param rwm		hardware register's writeable bits mask.
 */
HW_INLINE void _hwa_begin_r8 ( hwa_r8_t *r, intptr_t ra, uint8_t riv, uint8_t rwm, uint8_t rfm )
{
  r->ra		= ra ;
  r->riv	= riv ;
  r->rwm	= rwm ;
  r->rfm	= rfm ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}

/** \brief	Initializes a 16-bits HWA register. See _hwa_begin_r8() for details.
 */
HW_INLINE void _hwa_begin_r16 ( hwa_r16_t *r, intptr_t ra, uint16_t riv, uint16_t rwm, uint16_t rfm )
{
  r->ra		= ra ;
  r->riv	= riv ;
  r->rwm	= rwm ;
  r->rfm	= rfm ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}

/** \brief	Initializes a 32-bits HWA register. See _hwa_begin_r8() for details.
 */
HW_INLINE void _hwa_begin_r32 ( hwa_r32_t *r, intptr_t ra, uint32_t riv, uint32_t rwm, uint32_t rfm )
{
  r->ra		= ra ;
  r->riv	= riv ;
  r->rwm	= rwm ;
  r->rfm	= rfm ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}


/** \brief	Resets an 8-bits HWA register.
 */
HW_INLINE void _hwa_reset_r8 ( hwa_r8_t *r )
{
  /* FIXME: should check that there's nothing to commit first */
  r->mmask = r->rwm ;
  r->mvalue = r->riv ;
}

HW_INLINE void _hwa_reset_r16 ( hwa_r16_t *r )
{
  r->mmask = r->rwm ;
  r->mvalue = r->riv ;
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
#define _hwa_begin_reg_4(n,a,r, rt,rw,ra,riv,rwm,rfm )	\
  _hwa_begin_r##rw( &hwa->n.r, a+ra, riv, rwm, rfm )


/** \brief	Begin an HWA session. Allows the use of the hwa_...(...) functions.
 *
 *	Instanciate an hwa_t structure named 'hwa' that virtualizes the
 *	hardware. Nothing is done on the hardware until hwa_commit() is called.
 *
 *	Calls hwa_begin_all() that must be defined in hwa_device_l2.h.
 *
 * \hideinitializer
 */

HW_INLINE void _hwa_begin_all(hwa_t*) ;		/* defined in device-specific code */
HW_INLINE void _hwa_reset_all(hwa_t*) ;		/* defined in device-specific code */

HW_INLINE void __hwa_begin( hwa_t *hwa )
{
  if (0) { HWA_ERR("You may have forgotten to turn optimizations on."); }
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
 *	Calls _hwa_commit_all() that must be defined in hwa_ \e HWA_DEVICE _l2.h.
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
#  include "hwa_device_l2.h"
#else
#  include HW_QUOTE(HW_G3(hwa, HWA_DEVICE, 2).h)
#endif
