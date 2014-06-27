
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include <inttypes.h>

/** \brief	Storage class of HWA functions.
 *
 *  HWA function-like macros MUST be injected inside their callers and not leave
 *  any trace elsewhere, i.e. they must be strictly equivalent to macros,
 *  otherwise all kinds of HWA warnings and errors will be triggered.
 *
 *  GCC does the job with the only 'inline' keyword when optimisations are on,
 *  and optimisations must be on when using HWA.
 *
 *  However, it seems that the 'static' keyword prevents the function to be
 *  inlined unless the 'always_inline' attribute is specified.
 *
 *  __attribute__((always_inline)) triggers a warning if gcc fails to inline the
 *  function.
 */
#define HW_INLINE		static inline __attribute__((always_inline))


#if defined __cplusplus
# define HW_EXTERN_C		extern "C"
#else
# define HW_EXTERN_C
#endif


/** \brief	Preprocessing error
 *
 */
#define HW_PPERROR(msg)		0 ; _Static_assert(0, "HWA error: " msg)
/* HW_INLINE int hw_foo() { return 0 ; } */
/* #define HW_PPERROR(msg)		hw_foo() ; _Static_assert(0, "HWA error: " msg) */


/** \brief	Run-time error
 *
 * \ingroup macro
 * \hideinitializer
 */
#define HW_RTERROR(msg)			_HW_RTERROR_2(msg, __COUNTER__)
#define _HW_RTERROR_2(...)		_HW_RTERROR_3(__VA_ARGS__)
#define _HW_RTERROR_3(msg, num)						\
  do {									\
    extern void __attribute__((error(msg))) hw_rterror_##num(void);	\
    hw_rterror_##num();							\
  } while(0)




/** \brief	8-bit HWA register.
 *
 *	Structure used by hwa_ prefixed functions to handle one 8-bit hardware register. 
 */
typedef struct hwa_r8_t
{
  intptr_t	ra ;		/*!< Address of hardware register.		*/
  uint8_t	riv ;		/*!< Value after system reset (initial value).	*/
  uint8_t	rwm ;		/*!< Writeable bits mask.			*/
  uint8_t	mmask ;		/*!< Modified bits mask.			*/
  uint8_t	mvalue ;	/*!< Modified value mask.			*/
  uint8_t	omask ;		/*!< Hardware known bits mask.			*/
  uint8_t	ovalue ;	/*!< Hardware known value mask.			*/
} hwa_r8_t ;

/** \brief	16-bit HWA register.
 *
 *	Structure used by hwa_ prefixed functions to handle one 16-bit hardware register. 
 */
typedef struct hwa_r16_t
{
  intptr_t	ra ;		/*!< Address of hardware register.		*/
  uint16_t	riv ;		/*!< Value after system reset (initial value).	*/
  uint16_t	rwm ;		/*!< Writeable bits mask.			*/
  uint16_t	mmask ;		/*!< Modified bits mask.			*/
  uint16_t	mvalue ;	/*!< Modified value mask.			*/
  uint16_t	omask ;		/*!< Hardware known bits mask.			*/
  uint16_t	ovalue ;	/*!< Hardware known value mask.			*/
} hwa_r16_t ;

/** \brief	32-bit HWA register.
 *
 *	Structure used by hwa_ prefixed functions to handle one 32-bit hardware register. 
 */
typedef struct hwa_r32_t
{
  intptr_t	ra ;		/*!< Address of hardware register.		*/
  uint32_t	riv ;		/*!< Value after system reset (initial value).	*/
  uint32_t	rwm ;		/*!< Writeable bits mask.			*/
  uint32_t	mmask ;		/*!< Modified bits mask.			*/
  uint32_t	mvalue ;	/*!< Modified value mask.			*/
  uint32_t	omask ;		/*!< Hardware known bits mask.			*/
  uint32_t	ovalue ;	/*!< Hardware known value mask.			*/
} hwa_r32_t ;


/** \brief	hw_read(...)
 *
 */
#define hw_config(...)		HW_APPLY(hw_config, __VA_ARGS__)


/** \brief	hw_read(...)
 *
 */
#define hw_read(...)		HW_APPLY(hw_read, __VA_ARGS__)
#define hw_read_reg_isfn
#define hw_read_reg1(pn,pa,r,rw,ra,riv,rwm,rbn,rbp,_end_)	\
  hw_read_##rw(pa+ra,rbn,rbp)
#define hw_read_reg2(pn,pa,\
		     r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,		\
		     r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,_end_)		\
  ((hw_read_##rw1(pa+ra1,rbn1,rbp1)&((1<<rbn1)-1)<<vbp1) |	\
   (hw_read_##rw2(pa+ar2,rbn2,rbp2)&((1<<rbn2)-1)<<vbp2))


#define hw_write(...)		HW_APPLY(hw_write, __VA_ARGS__)
#define hw_write_reg_isfn
#define hw_write_reg1(pn,pa,r,rw,ra,riv,rwm,rbn,rbp,v,_end_)	\
  hw_write_##rw(pa+ra,rwm,rbn,rbp,v)
#define hw_write_reg2(pn,pa,\
		      r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,		\
		      r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,v,_end_)	\
  do { hw_write_##rw1(pa+ra1,riv1,rwm1,rbn1,rbp1, (v>>vbp1)&((1<<rbn1)-1)); \
      hw_write_##rw2(pa+ra2,riv2,rwm2,rbn2,rbp2, (v>>vbp2)&((1<<rbn2)-1)); } while(0)

/*	_hw_write(...): for internal use, does not check arguments
 */
#define _hw_write(...)			_hw_write_2(__VA_ARGS__)
#define _hw_write_2(per,pn,pc,pa,x,v)	_hw_write_3(hw_##pc##_##x,pa,v)
#define _hw_write_3(...)		_hw_write_4(__VA_ARGS__)
#define _hw_write_4(x,...)		_hw_write_##x(__VA_ARGS__)
#define _hw_write_reg(rn,rw,ra,riv,rwm,pa,v)\
  hw_write_##rw(pa+ra,rwm,rw,0,v)


#define hw_toggle(...)		HW_APPLY(hw_toggle, __VA_ARGS__)

/*	Turn irq on/off
 */
#define hw_turn_irq(...)	HW_SPCLZ(hw_turn_irq, HW_XPIRQ(__VA_ARGS__))
#define hw_turn_irq_no		HW_PPERROR
#define hw_turn_irq_ok(pn,pc,pa,irq,state)\
  hw_write(per,pn,pc,pa, hw_##pc##_ie_##irq, state)


/** \brief	hwa_write(...)
 *
 */
#define hwa_write(...)		HW_APPLY(hwa_write, __VA_ARGS__)
#define hwa_write_reg_isfn
#define hwa_write_reg1(pn,pa,r,rw,ra,riv,rwm,rbn,rbp,v,_end_)	\
  hwa_write_##rw( &hwa->pn.r, rbn, rbp, v )
#define hwa_write_reg2(pn,pa,						\
  r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,					\
  r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,v,_end_)				\
  do { hwa_write_##rw1(&hwa->pn.r1, rbn1, rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
       hwa_write_##rw2(&hwa->pn.r2, rbn2, rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0)


/*	Write registers of hwa_t struct. Used in "solve" functions.
 */
//#define hwa_write_p(p,pc,r,v)		_hwa_write_p_2(HW_G3(hw,pc,r), v, p)
#define hwa_write_p(...)		_hwa_write_p_2(__VA_ARGS__)
#define _hwa_write_p_2(p,t,...)		_hwa_write_p_##t(__VA_ARGS__,p)

#define _hwa_write_p_regb(_reg_,rn,rw,ra,riv,rwm,rbn,rbp,v,p)		\
  hwa_write_##rw(&p->rn, rbn, rbp, v )

#define _hwa_write_p_regbb(_reg1_,rn1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,		\
  _reg2_,rn2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,v,p)			\
  do { hwa_write_##rw1(&p->rn1, rbn1, rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
       hwa_write_##rw2(&p->rn2, rbn2, rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0)


/*	Configure one controller
 *
 *		Append a void argument to help detect end of arguments or
 *		missing arguments
 */
#define hwa_config(...)		HW_APPLY(hwa_config, __VA_ARGS__,)


/*	Turn irq on/off
 */
#define hwa_turn_irq(...)	HW_SPCLZ(hwa_turn_irq, HW_XPIRQ(__VA_ARGS__))
#define hwa_turn_irq_no		HW_PPERROR
/* #define hwa_turn_irq_ok(pn,pc,pa,irq,state)\ */
/*   hwa_write_p((&hwa.pn),hw_##pc##_ie_##irq, state) */
#define hwa_turn_irq_ok(pn,pc,pa,irq,state)\
  HW_APPLY(hwa_write, per,pn,pc,pa, hw_##pc##_ie_##irq, state)


/** \brief	Read from one 8-bit hardware register.
 *  \param p	address of register.
 *  \param rbn	number of consecutive bits conderned.
 *  \param rbp	position of the least significant bit conderned in the register.
 *  \return	the value of the rbn consecutive bits at position rbp in the register.
 */
HW_INLINE uint8_t hw_read_8 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  if ( ra == ~0 )
    HW_RTERROR("invalid address");

  if ( rbp > 7 )
    HW_RTERROR("bit pos > 7");

  uint8_t m = (rbn > 7 ? (uint8_t)~0 : (1U<<rbn)-1) ;
  volatile uint8_t *p = (volatile uint8_t *)ra ;
  return ((*p)>>rbp) & m ;
}


/** \brief	Read from one 16-bit hardware register.
 *  \param p	address of register.
 *  \param rbn	number of consecutive bits conderned.
 *  \param rbp	position of the least significant bit conderned in the register.
 *  \return	the value of the rbn consecutive bits at position rbp in the register.
 */
HW_INLINE uint16_t hw_read_16 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  if ( ra == ~0 )
    HW_RTERROR("invalid address");

  if ( rbp > 15 )
    HW_RTERROR("bit pos > 15");

  uint16_t m = (rbn > 15 ? (uint16_t)~0 : (1U<<rbn)-1) ;
  volatile uint16_t *p = (volatile uint16_t *)ra ;
  return ((*p)>>rbp) & m ;
}


/** \brief	Read from one 32-bit hardware register.
 *  \param p	address of register.
 *  \param rbn	number of consecutive bits conderned.
 *  \param rbp	position of the least significant bit conderned in the register.
 *  \return	the value of the rbn consecutive bits at position rbp in the register.
 */
HW_INLINE uint32_t hw_read_32 ( uint32_t *p, uint8_t rbn, uint8_t rbp )
{
  if ( (uintptr_t)p == (uintptr_t)~0 )
    HW_RTERROR("invalid address");

  if ( rbp > 31 )
    HW_RTERROR("bit pos > 31");

  uint32_t m = (rbn > 31 ? (uint32_t)~0 : (1U<<rbn)-1) ;
  return ((*p)>>rbp) & m ;
}


/** \brief	Write to one 8-bit hardware register.
 *
 *	Write the value into the rbn consecutive bits starting at pos rbp into
 *	the hard register at address p. Trying to write 1s into non-writeable
 *	bits triggers an error.
 *
 *  \param p	address of register.
 *  \param rwm	writeable bits mask of the register.
 *  \param rbn	number of consecutive bits conderned.
 *  \param rbp	position of the least significant bit conderned in the register.
 *  \param v	value to write.
 */
/* HW_INLINE void hw_write_8 ( volatile uint8_t *p, uint8_t rwm, */
/* 			     uint8_t rbn, uint8_t rbp, uint8_t v ) */
/* { */
/*   if ( (uintptr_t)p == (uintptr_t)~0 ) */
/*     HW_RTERROR("invalid access"); */

/*   if ( rbn == 0 ) */
/*     HW_RTERROR("no bit to be changed?"); */

/*   uint8_t m = (rbn > 7) ? (uint8_t)-1 : (1U<<rbn)-1 ; */

/*   if (v > m) */
/*     HW_RTERROR("value too high for bits number"); */

/*   m <<= rbp ; */
/*   v <<= rbp ; */

/*   /\*	Check that we do not try to set non-writeable bits */
/*    *\/ */
/*   if ( (v & m & rwm) != (v & m) ) */
/*     HW_RTERROR("bits not writeable."); */

/*   if ( (m & rwm) == rwm ) */
/*     *p = v ; */
/*   else */
/*     *p = (*p & ~m) | (v & m) ; */
/* } */

HW_INLINE void hw_write_8 ( intptr_t ra, uint8_t rwm,
			    uint8_t bn, uint8_t bp, uint8_t v )
{
  if ( ra == ~0 )
    HW_RTERROR("invalid access");

  if ( bn == 0 )
    HW_RTERROR("no bit to be changed?");

  uint8_t m = (bn > 7) ? (uint8_t)-1 : (1U<<bn)-1 ;

  if (v > m)
    HW_RTERROR("value too high for bits number");

  m <<= bp ;
  v <<= bp ;

  /*	Check that we do not try to set non-writeable bits
   */
  if ( (v & m & rwm) != (v & m) )
    HW_RTERROR("bits not writeable.");

  volatile uint8_t *p = (volatile uint8_t *)ra ;

  if ( (m & rwm) == rwm )
    *p = v ;
  else
    *p = (*p & ~m) | (v & m) ;
}


/** \brief	Write to one 16-bit hardware register.
 *
 *  \copydetails hwa_write_r8
 *
 *  \param p	address of register.
 *  \param rwm	writeable bits mask of the register.
 *  \param rbn	number of consecutive bits conderned.
 *  \param rbp	position of the least significant bit conderned in the register.
 *  \param v	value to write.
 */
HW_INLINE void hw_write_16 ( intptr_t ra, uint16_t rwm,
			     uint8_t bn, uint8_t bp, uint16_t v )
{
  if ( ra == ~0 )
    HW_RTERROR("invalid access");

  if ( bn == 0 )
    HW_RTERROR("no bit to be changed?");

  uint16_t m = (bn > 15) ? (uint16_t)-1 : (1U<<bn)-1 ;

  if (v > m)
    HW_RTERROR("value too high for bits number");

  m <<= bp ;
  v <<= bp ;

  /*	Check that we do not try to set non-writeable bits
   */
  if ( (v & m & rwm) != (v & m) )
    HW_RTERROR("bits not writeable.");

  volatile uint16_t *p = (volatile uint16_t *)ra ;

  if ( (m & rwm) == rwm )
    *p = v ;
  else
    *p = (*p & ~m) | (v & m) ;
}

/** \brief	Write to one 32-bit hardware register.
 *
 *  \copydetails hwa_write_r8
 *
 *  \param p	address of register.
 *  \param rwm	writeable bits mask of the register.
 *  \param rbn	number of consecutive bits conderned.
 *  \param rbp	position of the least significant bit conderned in the register.
 *  \param v	value to write.
 */
HW_INLINE void hw_write_32 ( volatile uint32_t *p, uint32_t rwm,
			     uint8_t rbn, uint8_t rbp, uint32_t v )
{
  if ( (uintptr_t)p == (uintptr_t)~0 )
    HW_RTERROR("invalid access");

  if ( rbn == 0 )
    HW_RTERROR("no bit to be changed?");

  uint32_t m = (rbn > 31) ? (uint32_t)-1 : (1U<<rbn)-1 ;

  if (v > m)
    HW_RTERROR("value too high for bits number");

  m <<= rbp ;
  v <<= rbp ;

  /*	Check that we do not try to set non-writeable bits
   */
  if ( (v & m & rwm) != (v & m) )
    HW_RTERROR("bits not writeable.");

  if ( (m & rwm) == rwm )
    *p = v ;
  else
    *p = (*p & ~m) | (v & m) ;
}
