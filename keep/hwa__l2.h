
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


/** \brief	Reads an 8-bits HWA register.
 */
/* HW_INLINE uint8_t hwa_peek_r8 ( hwa_r8_t *r, uint8_t rbn, uint8_t rbp ) */
/* { */
/*   return (((r->ovalue & ~r->mmask)|(r->mvalue & r->mmask)) >> rbp) & ((1U<<rbn)-1) ; */
/* } */

/** \brief	Reads a 16-bits HWA register.
 */
/* HW_INLINE uint16_t hwa_peek_r16 ( hwa_r16_t *r, uint8_t rbn, uint8_t rbp ) */
/* { */
/*   return (((r->ovalue & ~r->mmask)|(r->mvalue & r->mmask)) >> rbp) & ((1U<<rbn)-1) ; */
/* } */

/** \brief	Reads a 32-bits HWA register.
 */
/* HW_INLINE uint32_t hwa_peek_r32 ( hwa_r32_t *r, uint8_t rbn, uint8_t rbp ) */
/* { */
/*   return (((r->ovalue & ~r->mmask)|(r->mvalue & r->mmask)) >> rbp) & ((1U<<rbn)-1) ; */
/* } */


/** \brief	Writes an 8-bits HWA register
 *
 *	Write bits according to bn/bp. mmask is set even if the value is not
 *  	modified. hwa_commit() will check if the register has effectively been
 *  	modified.
 */
HW_INLINE void hwa_write_8 ( hwa_r8_t *r, uint8_t bn, uint8_t bp, uint8_t v )
{
  if (bn == 0)
    HW_RTERROR("no bit to be changed?");

  if (v > (1U<<bn)-1)
    HW_RTERROR("value too high for number of bits.");

  uint8_t sm = ((1U<<bn)-1) << bp ;	/* shifted mask  */

  //  *((volatile uint8_t*)0) = sm ;

  uint8_t sv = v << bp ;		/* shifted value */

  //  *((volatile uint8_t*)0) = sv ;

  if ((r->rwm & sm) != sm)
    HW_RTERROR("bits not writeable.");

  if ((r->mmask & sm) != 0 && (r->mvalue & sm) != sv)
    HW_RTERROR("committing is required before setting a new value.");

  r->mmask |= sm ;
  r->mvalue = (r->mvalue & ~sm) | (sm & sv) ;
}

/** \brief	Writes a 16-bits HWA register
 *
 *  \copydetails hwa_write_r8
 */
HW_INLINE void hwa_write_16 ( hwa_r16_t *r, uint8_t bn, uint8_t bp, uint16_t v )
{
  if (bn == 0)
    HW_RTERROR("no bit to be changed?");

  if (v > (1U<<bn)-1)
    HW_RTERROR("value too high for bits number.");

  uint16_t sm = ((1U<<bn)-1) << bp ;	/* shifted mask  */
  uint16_t sv = v << bp ;		/* shifted value */

  if ((r->rwm & sm) != sm)
    HW_RTERROR("bits not writeable.");

  if ((r->mmask & sm) != 0 && (r->mvalue & sm) != sv)
    HW_RTERROR("commit required before setting a new value.");

  r->mmask |= sm ;
  r->mvalue = (r->mvalue & ~sm) | (sm & sv) ;
}

/** \brief	Writes a 32-bits HWA register
 *
 *  \copydetails hwa_write_r8
 */
HW_INLINE void hwa_write_32 ( hwa_r32_t *r, uint8_t bn, uint8_t bp, uint32_t v )
{
  if (bn == 0)
    HW_RTERROR("no bit to be changed?");

  if (v > (1U<<bn)-1)
    HW_RTERROR("value too high for bits number.");

  uint32_t sm = ((1U<<bn)-1) << bp ;	/* shifted mask  */
  uint32_t sv = v << bp ;		/* shifted value */

  if ((r->rwm & sm) != sm)
    HW_RTERROR("bits not writeable.");

  if ((r->mmask & sm) != 0 && (r->mvalue & sm) != sv)
    HW_RTERROR("commit required before setting a new value.");

  r->mmask |= sm ;
  r->mvalue = (r->mvalue & ~sm) | (sm & sv) ;
}


/** \brief	Writes bits in one HWA register.
 *
 * \hideinitializer
 */
/* #define hwa_write_one_p( p, r,rw,ra,rwm,rbn,rbp, v )	\ */
/*   hwa_write_r##rw( &(p)->r, rbn, rbp, v ) */


/** \brief	Writes bits spread over two HWA registers.
 *
 * \hideinitializer
 */
/* #define hwa_write_two_p( p,						\ */
/* 			 r1,rw1,ra1,rwm1,rbn1,rbp1,vbp1,		\ */
/* 			 r2,rw2,ra2,rwm2,rbn2,rbp2,vbp2, v )		\ */
/*   do {									\ */
/*     hwa_write_r##rw1(&(p)->r1, rbn1, rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \ */
/*     hwa_write_r##rw2(&(p)->r2, rbn2, rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); \ */
/*   } while(0) */


/** \brief	Initializes an 8-bits HWA register.
 *
 *  \param r		pointer on the hwa register.
 *  \param x_reset	1 if the after-reset value has to be written into the register.
 *  \param p		address of the hardware register.
 *  \param riv		after-reset value of the hardware register.
 *  \param rwm		hardware register's writeable bits mask.
 */
//HW_INLINE void hwa_init_8 ( hwa_r8_t *r, _Bool x_reset, uint8_t *p, uint8_t riv, uint8_t rwm )
HW_INLINE void hwa_init_8 ( hwa_r8_t *r, _Bool x_reset, intptr_t ra, uint8_t riv, uint8_t rwm )
{
  r->ra		= ra ;
  r->riv	= riv ;
  r->rwm	= rwm ;
  r->mmask	= 0 ;
  r->omask	= x_reset ? rwm : 0 ;
  r->ovalue	= x_reset ? riv : 0 ;
  r->mvalue	= r->ovalue ;
}

/** \brief	Initializes a 16-bits HWA register. See hwa_init_r8() for details.
 */
//HW_INLINE void hwa_init_16 ( hwa_r16_t *r, _Bool x_reset, uint16_t *p, uint16_t riv, uint16_t rwm )
HW_INLINE void hwa_init_16 ( hwa_r16_t *r, _Bool x_reset, intptr_t ra, uint16_t riv, uint16_t rwm )
{
  r->ra		= ra ;
  r->riv	= riv ;
  r->rwm	= rwm ;
  r->mmask	= 0 ;
  r->omask	= x_reset ? rwm : 0 ;
  r->ovalue	= x_reset ? riv : 0 ;
  r->mvalue	= r->ovalue ;
}

/** \brief	Initializes a 32-bits HWA register. See hwa_init_r8() for details.
 */
HW_INLINE void hwa_init_32 ( hwa_r32_t *r, _Bool x_reset, intptr_t ra, uint32_t riv, uint32_t rwm )
{
  r->ra		= ra ;
  r->riv	= riv ;
  r->rwm	= rwm ;
  r->mmask	= 0 ;
  r->omask	= x_reset ? rwm : 0 ;
  r->ovalue	= x_reset ? riv : 0 ;
  r->mvalue	= r->ovalue ;
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
HW_INLINE void hwa_commit_8 ( _Bool commit, hwa_r8_t *r, uint8_t mask )
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

#if defined HW_DEVICE_ATMELAVR
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
 *		register). See hwa_commit_r8() for details.
 */
HW_INLINE void hwa_commit_16 ( _Bool commit, hwa_r16_t *r, uint16_t mask )
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
 *		register). See hwa_commit_r8() for details.
 */
HW_INLINE void hwa_commit_32 ( _Bool commit, hwa_r32_t *r, uint32_t mask )
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
#define _HWA_INIT_2( _per_, pn,pc,pa, r )	_HWA_INIT_3( pn,pa, HW_G3(hw,pc,r) )
#define _HWA_INIT_3(...)			_HWA_INIT_4(__VA_ARGS__)
#define _HWA_INIT_4( pn,pa, _reg_, rn,rw,ra,riv,rwm ) \
  hwa_init_##rw( &hwa->pn.rn, hwa->initstate, pa+ra, riv, rwm )


/* #define hwa_begin_			0 */
/* #define hwa_begin_reset			1 */


/** \brief	Begin an HWA session.
 *
 *	Instanciate an hwa_t structure named 'hwa' that virtualizes the hardware
 *	and allows the use of the hwa_ functions. Nothing is done on the
 *	hardware until hwa_commit() is called.
 *
 *	Calls hwa_begin_all() that must be defined in hwa_device_l2.h.
 *
 *  \param 	begin_state can be 'reset' or left void. If 'reset' is mentionned,
 *		the virtual registers are initialized with their after-reset
 *		value.
 *
 * \hideinitializer
 */
#define _hwa_begin(begin_state)						\
  if (0) { HW_RTERROR("You may have forgotten to turn optimizations on."); } \
  uint8_t hwa_commit = 0 ; /* Will warn if hwa_commit() is not called */ \
  hwa_t hwa_st ;							\
  hwa_t *hwa = &hwa_st ;						\
  hwa->initstate = /*hwa_begin_##*/ begin_state ;			\
  hwa_begin_all(hwa)


#define hwa_begin_from_reset()			\
  _hwa_begin(1);


#define hwa_begin()				\
  _hwa_begin(0);


/** \brief	Commit configuration to hardware.
 *
 *	Solve the constraints imposed by the developper, then do the required
 *	hardware register writes.
 *
 *	Calls hwa_commit_all() that must be defined in hwa_ \e HW_DEVICE _l2.h.
 *
 * \hideinitializer
 */
#define hwa_commit()					\
  do {							\
    uint8_t foo __attribute__((unused)) = hwa_commit ;	\
    hwa->commit = 1 ;					\
    hwa_commit_all(hwa);				\
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
    hwa_commit_all(hwa);			\
  } while(0)


/*
 *	Common user functions for all HWA implementations
 *
 *	Note: HW_EXP() is used only with functions that deal with registers
 *	(read/write/toggle) or ios. It can not work with functions dealing with higher
 *	level arguments than registers, bits, or ios.
 */

/** \brief	Reads from one instance register or i/o.
 *
 *	This is a generic function-like macro expanded according to the type of
 *	its arguments.
 *
 * \hideinitializer
 */
/* #define hwa_peek(...)			HW_G28(hwa_peek, HW_EXP(__VA_ARGS__)) */
/* #define hwa_peek_fail(...)		hwa_peek_error_ ## __VA_ARGS__ */

/** \brief	Writes into one instance register or i/o.
 *
 *  This is a generic function-like macro expanded according to the type of its
 *  arguments.
 *
 * \hideinitializer
 */
/* #define hwa_write(...)			HW_G28(hwa_write, HW_EXP(__VA_ARGS__)) */
/* #define hwa_write_fail(a, s)		hwa_write_error_ ## s */


/** \brief	Toggles bits of one instance register or i/o.
 *
 *  This is a generic function-like macro expanded according to the type of its
 *  arguments.
 *
 * \hideinitializer
 */
/* #define hwa_toggle(...)			HW_G28(hwa_toggle, HW_EXP(__VA_ARGS__)) */
/* #define hwa_toggle_fail(...)		hwa_toggle_error_ ## __VA_ARGS__ */


/* \brief	Returns the current value of a register or bit-group in the HWA
 *		struct.
 *
 *	This is a generic function-like macro expanded according to the type of
 *	its arguments.
 *
 * \hideinitializer
 */
/* #define hwa_get(...)			HW_G28(hwa_peek, HW_EXP(__VA_ARGS__)) */
/* #define hwa_get_fail(...)		hwa_peek_error_ ## __VA_ARGS__ */


/*	Include device-specific declarations
 */
#ifdef DOXYGEN
#  include "hwa_device_l2.h"
#else
#  include HW_QUOTE(HW_G3(hwa, HW_DEVICE, l2).h)
#endif