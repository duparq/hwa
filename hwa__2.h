
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA layer 2: definitions that use the hwa data structure.
 *
 *	The layer 2 (files ending with _l2.h ) contains the definitions of the
 *	global HWA structure that virtualizes the real device and that is used
 *	by all the "advanced" and/or "asynchronous" functions also defined in
 *	these files.
 *
 *	See hwa___exp.h or \ref notations "notations" for a description of the
 *	notations used.
 */

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

/** \brief	Writes a 32-bits HWA register
 *
 *  \copydetails hwa_write_r8
 */
HW_INLINE void _hwa_write_r32 ( hwa_r32_t *r, uint8_t bn, uint8_t bp, uint32_t v )
{
  if (bn == 0)
    HWA_ERR("no bit to be changed?");

  if (v > (1U<<bn)-1)
    HWA_ERR("value too high for bits number.");

  uint32_t sm = ((1U<<bn)-1) << bp ;	/* shifted mask  */
  uint32_t sv = v << bp ;		/* shifted value */

  if ((r->rwm & sm) != sm)
    HWA_ERR("bits not writeable.");

  if ((r->mmask & sm) != 0 && (r->mvalue & sm) != sv)
    HWA_ERR("commit required before setting a new value.");

  r->mmask |= sm ;
  r->mvalue = (r->mvalue & ~sm) | (sm & sv) ;
}


/** \brief	Initializes an 8-bits HWA register.
 *
 *  \param r		pointer on the hwa register.
 *  \param x_reset	1 if the after-reset value has to be written into the register.
 *  \param p		address of the hardware register.
 *  \param riv		after-reset value of the hardware register.
 *  \param rwm		hardware register's writeable bits mask.
 */
HW_INLINE void _hwa_init_r8 ( hwa_r8_t *r, intptr_t ra, uint8_t riv, uint8_t rwm )
{
  r->ra		= ra ;
  r->riv	= riv ;
  r->rwm	= rwm ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}

/** \brief	Initializes a 16-bits HWA register. See _hwa_init_r8() for details.
 */
HW_INLINE void _hwa_init_r16 ( hwa_r16_t *r, intptr_t ra, uint16_t riv, uint16_t rwm )
{
  r->ra		= ra ;
  r->riv	= riv ;
  r->rwm	= rwm ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}

/** \brief	Initializes a 32-bits HWA register. See _hwa_init_r8() for details.
 */
HW_INLINE void _hwa_init_r32 ( hwa_r32_t *r, intptr_t ra, uint32_t riv, uint32_t rwm )
{
  r->ra		= ra ;
  r->riv	= riv ;
  r->rwm	= rwm ;
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


/**  \brief Commits an 8-bits HWA register (update the hardware register if
 *  needed).
 *
 *  The code is meant to produce the best machine code among (verified on Atmel
 *  AVRs):
 *
 *  - bit-set or bit-clear:	1 instruction
 *  - load-immediate / store:	2 instructions
 *  - load / modify / store:	3 instructions
 */
HW_INLINE void _hwa_commit_r8 ( _Bool commit, hwa_r8_t *r, uint8_t mask )
{
  /*  Compute the mask of bits to be committed (do not commit bits untouched
   *  since last commit).
   *
   *  hwa_write does not permit r->mmask to extend beyond r->rwm
   */
  mask &= r->mmask ;

  /*  FIXME:
   *
   *    * with p not declared 'volatile', gcc discards all the hardware
   *      read-write instructions of hwa_sleep_until_interrupt() after
   *      hwa_begin(RESET)
   *
   *	* with p declared 'volatile', gcc produces not optimised code for the
   *      hardware read-write instructions of hwa_sleep_until_interrupt() after
   *      hwa_begin()
   */
  volatile uint8_t *p = (volatile uint8_t *)r->ra ;

  /*  Mask of bits to be written (toggled or unknown bits)
   */
  uint8_t wm = mask & ((r->ovalue ^ r->mvalue) | ~r->omask);

  if ( wm ) {

#if defined HWA_DEVICE_ATMELAVR
    _Bool x_onebit = ( wm==0x01 || wm==0x02 || wm==0x04 || wm==0x08 ||
		       wm==0x10 || wm==0x20 || wm==0x40 || wm==0x80 ) ;

    if ( x_onebit && commit && (uintptr_t)p < 0x40 ) {
      /*
       *  Use bit-set/bit-clear if possible
       *
       *	AVR: only possible for ASM addresses < 0x20, i.e. C addresses <
       *	0x40
       */
      if ( wm & r->mvalue )
	*p |= wm ;
      else
	*p &= ~wm ;
      r->ovalue = (r->ovalue & ~wm) | (r->mvalue & wm) ;
      r->mmask &= ~wm ;
      r->omask |= wm ;
      return ;
    }
#endif

    /*  Mask of bits to be read (unknown bits that are writeable and must not be
     *  modified)
     */
    uint8_t rm = r->rwm & ~mask & ~r->omask ;

    rm = rm & ~r->omask ;

    /*  Read only if needed:
     *    something to read, commit required, real register
     */
    if ( rm && commit && (uintptr_t)p != (uintptr_t)~0) {
      //      r->ovalue = *p & rm ;
      r->ovalue = *p ;
      r->omask = r->rwm ;
    }

    /*  Compute value
     */
    r->ovalue = (r->ovalue & ~wm) | (r->mvalue & wm) ;

    /*  Write value
     *    something to write, commit required, real register
     */
    if ( wm && commit && (uintptr_t)p != (uintptr_t)~0)
      *p = r->ovalue ;
  }

  r->mmask &= ~mask ;
  r->omask |= mask ;
}

/** \brief	Commit a 16-bits HWA register (update the hardware
 *		register). See _hwa_commit_r8() for details.
 */
HW_INLINE void _hwa_commit_r16 ( _Bool commit, hwa_r16_t *r, uint16_t mask )
{
  mask &= r->mmask ;
  volatile uint16_t *p = (volatile uint16_t *)r->ra ;
  uint16_t wm = mask & ((r->mmask & (r->ovalue ^ r->mvalue)) | ~r->omask);
  if ( wm ) {
    uint16_t rm = ~r->omask & r->rwm & ~mask ;
    if ( rm && commit && (uintptr_t)p != (uintptr_t)~0) {
      r->ovalue = *p & rm ;
      r->omask = r->rwm ;
    }
    r->ovalue = (r->ovalue & ~wm) | (r->mvalue & wm) ;
    if ( wm && commit && (uintptr_t)p != (uintptr_t)~0)
      *p = r->ovalue ;
  }
  r->mmask &= ~mask ;
  r->omask |= mask ;
}

/** \brief	Commit a 32-bits HWA register (update the hardware
 *		register). See _hwa_commit_r8() for details.
 */
HW_INLINE void _hwa_commit_r32 ( _Bool commit, hwa_r32_t *r, uint32_t mask )
{
  mask &= r->mmask ;

  volatile uint32_t *p = (volatile uint32_t *)r->ra ;

  uint32_t wm = mask & ((r->ovalue ^ r->mvalue) | ~r->omask);

  if ( wm ) {

    uint32_t rm = r->rwm & ~mask & ~r->omask ;

    rm = rm & ~r->omask ;

    if ( rm && commit && (uintptr_t)p != (uintptr_t)~0) {
      //      r->ovalue = *p & rm ;
      r->ovalue = *p ;
      r->omask = r->rwm ;
    }

    r->ovalue = (r->ovalue & ~wm) | (r->mvalue & wm) ;

    if ( wm && commit && (uintptr_t)p != (uintptr_t)~0)
      *p = r->ovalue ;
  }

  r->mmask &= ~mask ;
  r->omask |= mask ;
}


/** \brief	Initialize an HWA register
 *
 *  \param c	class of the register.
 *  \param i	instance of the register.
 *  \param r	name of the register.
 *
 * \hideinitializer
 */
#define HWA_INIT(...)				_HWA_INIT_2(__VA_ARGS__)
#define _HWA_INIT_2(cc,cn,ci,ca, rn )		_HWA_INIT_3(cn,ca,rn, hw_##cc##_##rn)
#define _HWA_INIT_3(...)			_HWA_INIT_4(__VA_ARGS__)
#define _HWA_INIT_4(cn,ca,rn, reg,rw,ra,rrv,rwm )	\
  _hwa_init_r##rw( &hwa->cn.rn, ca+ra, rrv, rwm )


/** \brief	Begin an HWA session. Allows the use of the hwa_...(...) functions.
 *
 *	Instanciate an hwa_t structure named 'hwa' that virtualizes the
 *	hardware. Nothing is done on the hardware until hwa_commit() is called.
 *
 *	Calls hwa_begin_all() that must be defined in hwa_device_l2.h.
 *
 * \hideinitializer
 */

HW_INLINE void _hwa_begin_all(hwa_t*) ;
HW_INLINE void _hwa_reset_all(hwa_t*) ;

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
