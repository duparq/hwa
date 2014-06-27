
/* This file is ca+rt of the HWA project.
 * Copyright (c) Christophe Duca+rquet <duca+rq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

//#include <inttypes.h>
#include <stdint.h>

/** \brief	Storage class of HWA functions.
 *
 *  HWA function-like macros MUST be injected inside their callers and not leave
 *  any trace elsewhere, i.e. they must be strictly equivalent to macros,
 *  otherwise all kinds of HWA warnings and errors will be triggered.
 *
 *  GCC does the job with only the 'inline' keyword when optimisations are on,
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
//#define HW_PPERROR(msg)		0, _Static_assert(0, "HWA error: " msg)
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
#define hw_read_reg1(cn,ca,r,rw,ra,riv,rwm,rbn,rbp,_end_)	\
  _hw_read_r##rw(ca+ra,rbn,rbp)
#define hw_read_reg2(cn,ca,\
		     r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,		\
		     r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,_end_)		\
  ((_hw_read_r##rw1(ca+ra1,rbn1,rbp1)&((1<<rbn1)-1)<<vbp1) |	\
   (_hw_read_r##rw2(ca+ar2,rbn2,rbp2)&((1<<rbn2)-1)<<vbp2))


#define hw_write(...)		HW_APPLY(hw_write, __VA_ARGS__)
#define hw_write_reg_isfn
#define hw_write_reg1(cn,ca,r,rw,ra,riv,rwm,rbn,rbp,v,_end_)	\
  _hw_write_r##rw(ca+ra,rwm,rbn,rbp,v)
#define hw_write_reg2(cn,ca,\
		      r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,		\
		      r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,v,_end_)	\
  do { _hw_write_r##rw1(ca+ra1,riv1,rwm1,rbn1,rbp1, (v>>vbp1)&((1<<rbn1)-1)); \
      _hw_write_r##rw2(ca+ra2,riv2,rwm2,rbn2,rbp2, (v>>vbp2)&((1<<rbn2)-1)); } while(0)


/*	Write hard registers. Internal use, no argument checking.
 */
#define _hw_write(...)			_hw_write_2(__VA_ARGS__)
#define _hw_write_2(_ctr_,cn,cc,ca,x,v)	_hw_write_3(hw_##cc##_##x,ca,v)
#define _hw_write_3(...)		_hw_write_4(__VA_ARGS__)
#define _hw_write_4(x,...)		_hw_write_##x(__VA_ARGS__)
#define _hw_write_reg(rn,rw,ra,riv,rwm,ca,v)\
  _hw_write_r##rw(ca+ra,rwm,rw,0,v)
#define _hw_write_regb(_reg_,rn,rw,ra,riv,rwm,bn,bp,ca,v)\
  _hw_write_r##rw(ca+ra,rwm,bn,bp,v)


#define hw_toggle(...)		HW_APPLY(hw_toggle, __VA_ARGS__)


/** \brief	hwa_write(...)
 *
 */
#define hwa_write(...)		HW_APPLY(hwa_write, __VA_ARGS__)
#define hwa_write_reg_isfn
#define hwa_write_reg1(cn,ca,rn,rw,ra,riv,rwm,rbn,rbp,v,_end_)	\
  _hwa_write_r##rw( &hwa->cn.rn, rbn, rbp, v )
#define hwa_write_reg2(cn,ca,						\
		       r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,		\
		       r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,v,_end_)	\
  do { _hwa_write_r##rw1(&hwa->cn.r1, rbn1, rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
      _hwa_write_r##rw2(&hwa->cn.r2, rbn2, rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0)


/*	Write regx without arguments checking
 */
#define _hwa_write(...)			_hwa_write_2(__VA_ARGS__)
#define _hwa_write_2(_ctr_,cn,cc,ca,x,v)	_hwa_write_3(hw_##cc##_##x,cn,v)
#define _hwa_write_3(...)		_hwa_write_4(__VA_ARGS__)
#define _hwa_write_4(x,...)		_hwa_write_##x(__VA_ARGS__)

#define _hwa_write_reg(rn,rw,ra,rrv,rwm, cn, v)\
  _hwa_write_r##rw(&((hwa->cn).rn), rw, 0, v )

#define _hwa_write_regb(x,...)		_hwa_write_regb_##x(__VA_ARGS__)

#define _hwa_write_regb_ctr(cn,cc,ca,x,...)	\
  _hwa_write_regb_ctr_2(cn, hw_##cc##_##x, __VA_ARGS__)
#define _hwa_write_regb_ctr_2(...)	_hwa_write_regb_ctr_3(__VA_ARGS__)
#define _hwa_write_regb_ctr_3(cn, _regb_, _reg_, rn,rw,ra,rrv,rwm, rbn,rbp, _, v) \
  _hwa_write_r##rw(&((hwa->cn).rn), rbn, rbp, v )

#define _hwa_write_regb_reg(rn,rw,ra,rrv,rwm,rbn,rbp,cn,v)	\
  _hwa_write_r##rw(&((hwa->cn).rn), rbn, rbp, v )



/*	Write registers in hwa_t struct. Internal use, no argument checking.
 */
#define _hwa_write_cp(...)			_hwa_write_cp_2(__VA_ARGS__)
#define _hwa_write_cp_2(p,t,...)		_hwa_write_cp_##t(__VA_ARGS__,p)
#define _hwa_write_cp_regb(_reg_,rn,rw,ra,riv,rwm,rbn,rbp,v,p)		\
  _hwa_write_r##rw(&p->rn, rbn, rbp, v )
#define _hwa_write_cp_regbb(_reg1_,rn1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,		\
  _reg2_,rn2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,v,p)			\
  do { _hwa_write_r##rw1(&p->rn1, rbn1, rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
       _hwa_write_r##rw2(&p->rn2, rbn2, rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0)


/*	Configure one controller
 *
 *		Append a void argument to help detect end of arguments or
 *		missing arguments
 */
#define hwa_config(...)		HW_APPLY(hwa_config, __VA_ARGS__,)


/*	Turn irq on/off
 */
#define hw_turn_irq(...)	HW_SPCLZ(hw_turn_irq, HW_XPIRQ(__VA_ARGS__))
#define hw_turn_irq_0		HW_PPERROR
#define hw_turn_irq_1(cn,cc,ca,irq,state)		\
  _hw_write(ctr,cn,cc,ca, hw_##cc##_ie_##irq, state)

#define hwa_turn_irq(...)	_hwa_turn_irq_2( HW_CALL( HW_XIRQ(__VA_ARGS__)))
#define _hwa_turn_irq_2(...)	_hwa_turn_irq_3( __VA_ARGS__ )
//#define _hwa_turn_irq_3(...)	_hwa_turn_irq_ ## __VA_ARGS__
//#define _hwa_turn_irq_0(error)	HW_PPERROR(error)

#define _hwa_turn_irq_3(...)	HW_G2(_hwa_turn_irq_error, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hwa_turn_irq_error_1(...) __VA_ARGS__
#define _hwa_turn_irq_error_0(...) _hwa_turn_irq_ ## __VA_ARGS__

  //#define _hwa_turn_irq_0(error)	0, error
#define _hwa_turn_irq_irq(vector,_ctr_,cn,cc,ca, irqe, irqf, zstate, _)	\
  HW_G2(_hwa_turn_irq_state, HW_IS(state, hw_##zstate))(vector,_ctr_,cn,cc,ca, irqe, irqf, zstate)

#define _hwa_turn_irq_state_0(vector, _ctr_,cn,cc,ca, irqe, irqf, zstate)	\
    HW_PPERROR("`" #zstate "` is not a valid irq state.")
#define _hwa_turn_irq_state_1(vector, _ctr_,cn,cc,ca, irqe, irqf, zstate)	\
    _hwa_write_2(_ctr_,cn,cc,ca, irqe, HW_A1(hw_##zstate))


/** \brief	Read from one 8-bit hardware register.
 *  \ca+ram p	address of register.
 *  \ca+ram rbn	number of consecutive bits conderned.
 *  \ca+ram rbp	position of the least significant bit conderned in the register.
 *  \return	the value of the rbn consecutive bits at position rbp in the register.
 */
HW_INLINE uint8_t _hw_read_r8 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
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
 *  \ca+ram p	address of register.
 *  \ca+ram rbn	number of consecutive bits conderned.
 *  \ca+ram rbp	position of the least significant bit conderned in the register.
 *  \return	the value of the rbn consecutive bits at position rbp in the register.
 */
HW_INLINE uint16_t _hw_read_r16 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
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
 *  \ca+ram p	address of register.
 *  \ca+ram rbn	number of consecutive bits conderned.
 *  \ca+ram rbp	position of the least significant bit conderned in the register.
 *  \return	the value of the rbn consecutive bits at position rbp in the register.
 */
HW_INLINE uint32_t _hw_read_r32 ( uint32_t *p, uint8_t rbn, uint8_t rbp )
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
 *  \ca+ram p	address of register.
 *  \ca+ram rwm	writeable bits mask of the register.
 *  \ca+ram rbn	number of consecutive bits conderned.
 *  \ca+ram rbp	position of the least significant bit conderned in the register.
 *  \ca+ram v	value to write.
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

HW_INLINE void _hw_write_r8 ( intptr_t ra, uint8_t rwm,
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
 *  \ca+ram p	address of register.
 *  \ca+ram rwm	writeable bits mask of the register.
 *  \ca+ram rbn	number of consecutive bits conderned.
 *  \ca+ram rbp	position of the least significant bit conderned in the register.
 *  \ca+ram v	value to write.
 */
HW_INLINE void _hw_write_r16 ( intptr_t ra, uint16_t rwm,
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
 *  \ca+ram p	address of register.
 *  \ca+ram rwm	writeable bits mask of the register.
 *  \ca+ram rbn	number of consecutive bits conderned.
 *  \ca+ram rbp	position of the least significant bit conderned in the register.
 *  \ca+ram v	value to write.
 */
HW_INLINE void _hw_write_r32 ( volatile uint32_t *p, uint32_t rwm,
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
