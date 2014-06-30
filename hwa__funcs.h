
/* This file is ca+rt of the HWA project.
 * Copyright (c) Christophe Duca+rquet <duca+rq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

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


/** \brief	Run-time error
 *
 * \ingroup macro
 * \hideinitializer
 */
#define HWA_ERR(msg)			_HWA_ERR_2(msg, __COUNTER__)
#define _HWA_ERR_2(...)		_HWA_ERR_3(__VA_ARGS__)
#define _HWA_ERR_3(msg, num)						\
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


/*	Generic instruction 'hwa_config': configure one controller
 */
#define hwa_config(...)		HW_G2(_hwa_config_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hwa_config_xctr_0(...)	HW_ERR("first argument is not a controller.")
#define _hwa_config_xctr_1(ctr,cc,...)	\
  HW_G2(_hwa_config_xfn, HW_IS(,hwa_config_##cc##_isfn))(cc,__VA_ARGS__)
#define _hwa_config_xfn_1(cc,...)	hwa_config_##cc(__VA_ARGS__)
#define _hwa_config_xfn_0(cc,cn,ca,...)					\
  HW_ERR("controller `hw_" #cn "` of class `" #cc "` has no method `hwa_config()`.")



/*	Generic instruction 'hw_read'
 */
#define hw_read(...)		HW_G2(_hw_read_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hw_read_xctr_0(...)	HW_ERR("first argument is not a controller.")
#define _hw_read_xctr_1(ctr,cc,...)	\
  HW_G2(_hw_read_xfn, HW_IS(,hw_read_##cc##_isfn))(cc,__VA_ARGS__)
#define _hw_read_xfn_1(cc,...)	hw_read_##cc(__VA_ARGS__)
#define _hw_read_xfn_0(cc,cn,ca,...)					\
  HW_G2(_hw_read_xmem, HW_IS(mem,hw_##cc##_##__VA_ARGS__))(cc,cn,ca,__VA_ARGS__)
#define _hw_read_xmem_0(cc,cn,ca,...)					\
  HW_ERR("controller `hw_" #cn "` of class `" #cc "` has no method `hw_read` and no register `" HW_QUOTE(HW_A0(__VA_ARGS__)) "`.")
#define _hw_read_xmem_1(...)	_hw_read_xmem_2(HW_XMEM(__VA_ARGS__,))
#define _hw_read_xmem_2(...)	_hw_read_xmem_3(__VA_ARGS__)
#define _hw_read_xmem_3(x,...)	_hw_read_mem_##x(__VA_ARGS__)
#define _hw_read_mem_0	HW_ERR
#define _hw_read_mem_1(cn,ca,rn,rw,ra,rrv,rwm,rbn,rbp,v,_)	\
  _hw_read_r##rw(ca+ra,rbn,rbp)
#define _hw_read_mem_2(cn,ca,						\
			r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,		\
			r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,v,_)	\
  ((_hw_read_r##rw1(ca+ra1,rbn1,rbp1)&((1<<rbn1)-1)<<vbp1) |	\
   (_hw_read_r##rw2(ca+ar2,rbn2,rbp2)&((1<<rbn2)-1)<<vbp2))


/*	Generic instruction 'hw_write'
 */
#define hw_write(...)		HW_G2(_hw_write_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hw_write_xctr_0(...)	HW_ERR("first argument is not a controller.")
#define _hw_write_xctr_1(ctr,cc,...)	\
  HW_G2(_hw_write_xfn, HW_IS(,hw_write_##cc##_isfn))(cc,__VA_ARGS__)
#define _hw_write_xfn_1(cc,...)	hw_write_##cc(__VA_ARGS__)
#define _hw_write_xfn_0(cc,cn,ca,...)					\
  HW_G2(_hw_write_xmem, HW_IS(mem,hw_##cc##_##__VA_ARGS__))(cc,cn,ca,__VA_ARGS__)
#define _hw_write_xmem_0(cc,cn,ca,...)					\
  HW_ERR("controller `hw_" #cn "` of class `" #cc "` has no method `hw_write` and no register `" HW_QUOTE(HW_A0(__VA_ARGS__)) "`.")
#define _hw_write_xmem_1(...)	_hw_write_xmem_2(HW_XMEM(__VA_ARGS__,))
#define _hw_write_xmem_2(...)	_hw_write_xmem_3(__VA_ARGS__)
#define _hw_write_xmem_3(x,...)	_hw_write_mem_##x(__VA_ARGS__)
#define _hw_write_mem_0	HW_ERR
#define _hw_write_mem_1(cn,ca,rn,rw,ra,rrv,rwm,rbn,rbp,v,_)	\
  _hw_write_r##rw(ca+ra,rwm,rbn,rbp,v)
#define _hw_write_mem_2(cn,ca,						\
			r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,		\
			r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,v,_)	\
  do { _hw_write_r##rw1(ca+ra1,riv1,rwm1,rbn1,rbp1, (v>>vbp1)&((1<<rbn1)-1)); \
      _hw_write_r##rw2(ca+ra2,riv2,rwm2,rbn2,rbp2, (v>>vbp2)&((1<<rbn2)-1)); } while(0)


/*	Write hard registers. Internal use, no argument checking.
 */
#define _hw_write_mem(ctr,...)		_hw_write_xmem_2(HW_XMEM(__VA_ARGS__,))


/*	Generic instruction 'hwa_write'
 */
#define hwa_write(...)		HW_G2(_hwa_write_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hwa_write_xctr_0(...)	HW_ERR("first argument is not a controller.")
#define _hwa_write_xctr_1(ctr,cc,...)	\
  HW_G2(_hwa_write_xfn, HW_IS(,hwa_write_##cc##_isfn))(cc,__VA_ARGS__)
#define _hwa_write_xfn_1(cc,...)	hwa_write_##cc(__VA_ARGS__)
#define _hwa_write_xfn_0(cc,cn,ca,...)					\
  HW_G2(_hwa_write_xmem, HW_IS(mem,hw_##cc##_##__VA_ARGS__))(cc,cn,ca,__VA_ARGS__)
#define _hwa_write_xmem_0(cc,cn,ca,...)					\
  HW_ERR("controller `hw_" #cn "` of class `" #cc "` has no method `hwa_write` and no register `" HW_QUOTE(HW_A0(__VA_ARGS__)) "`.")
#define _hwa_write_xmem_1(...)	_hwa_write_xmem_2(HW_XMEM(__VA_ARGS__,))
#define _hwa_write_xmem_2(...)	_hwa_write_xmem_3(__VA_ARGS__)
#define _hwa_write_xmem_3(x,...)	_hwa_write_mem_##x(__VA_ARGS__)
#define _hwa_write_mem_0	HW_ERR
#define _hwa_write_mem_1(cn,ca,rn,rw,ra,rrv,rwm,rbn,rbp,v,_)	\
  _hwa_write_r##rw( &hwa->cn.rn, rbn, rbp, v )
#define _hwa_write_mem_2(cn,ca,						\
			r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,		\
			r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,v,_)	\
  do { _hwa_write_r##rw1(&hwa->cn.r1, rbn1, rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
      _hwa_write_r##rw2(&hwa->cn.r2, rbn2, rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0)


/*	Write hard registers. Internal use, no argument checking.
 */
#define _hwa_write_mem(ctr,...)		_hwa_write_xmem_2(HW_XMEM(__VA_ARGS__,))


/*	Write regx without arguments checking
 *	FIXME: should replace with _hw_write_xmem_1
 */
/* #define _hwa_write(...)			_hwa_write_2(__VA_ARGS__) */
/* #define _hwa_write_2(_ctr_,cc,cn,ca,x,v)	_hwa_write_3(hw_##cc##_##x,cn,v) */
/* #define _hwa_write_3(...)		_hwa_write_4(__VA_ARGS__) */
/* #define _hwa_write_4(x,...)		_hwa_write_##x(__VA_ARGS__) */

/* #define _hwa_write_reg(rn,rw,ra,rrv,rwm, cn, v)\ */
/*   _hwa_write_r##rw(&((hwa->cn).rn), rw, 0, v ) */

/* #define _hwa_write_regb(x,...)		_hwa_write_regb_##x(__VA_ARGS__) */

/* #define _hwa_write_regb_ctr(cc,cn,ca,x,...)	\ */
/*   _hwa_write_regb_ctr_2(cn, hw_##cc##_##x, __VA_ARGS__) */
/* #define _hwa_write_regb_ctr_2(...)	_hwa_write_regb_ctr_3(__VA_ARGS__) */
/* #define _hwa_write_regb_ctr_3(cn, _regb_, _reg_, rn,rw,ra,rrv,rwm, rbn,rbp, _, v) \ */
/*   _hwa_write_r##rw(&((hwa->cn).rn), rbn, rbp, v ) */

/* #define _hwa_write_regb_reg(rn,rw,ra,rrv,rwm,rbn,rbp,cn,v)	\ */
/*   _hwa_write_r##rw(&((hwa->cn).rn), rbn, rbp, v ) */



/*	Write registers in hwa_t struct. Internal use only, no argument checking!
 */
#define _hwa_write_pcr(p,cc,r,v)	_hwa_write_pcr2(HW_XMEM(cc,cn,ca,r,v,p))
#define _hwa_write_pcr2(...)		_hwa_write_pcr3(__VA_ARGS__)
#define _hwa_write_pcr3(x,...)		_hwa_write_pcr_##x(__VA_ARGS__)
#define _hwa_write_pcr_1(cn,ca,rn,rw,ra,rrv,rwm,rbn,rbp,v,p)	\
  _hwa_write_r##rw( &p->rn, rbn, rbp, v )
#define  _hwa_write_pcr_2(cn,ca,					\
			  rn1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,		\
			  rn2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,v,p)	\
  do { _hwa_write_r##rw1(&p->rn1, rbn1, rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
      _hwa_write_r##rw2(&p->rn2, rbn2, rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0)


/*	Generic instruction 'hw_toggle'
 */
#define hw_toggle(...)		HW_G2(_hw_toggle_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)
#define _hw_toggle_xctr_0(...)	HW_ERR("first argument is not a controller.")
#define _hw_toggle_xctr_1(ctr,cc,...)	\
  HW_G2(_hw_toggle_xfn, HW_IS(,hw_toggle_##cc##_isfn))(cc,__VA_ARGS__)
#define _hw_toggle_xfn_1(cc,...)	hw_toggle_##cc(__VA_ARGS__)
#define _hw_toggle_xfn_0(cc,cn,ca,...)					\
  HW_G2(_hw_toggle_xmem, HW_IS(mem,hw_##cc##_##__VA_ARGS__))(cc,cn,ca,__VA_ARGS__)
#define _hw_toggle_xmem_0(cc,cn,ca,...)					\
  HW_ERR("controller `hw_" #cn "` of class `" #cc "` has no method `hw_toggle` and no register `" HW_QUOTE(HW_A0(__VA_ARGS__)) "`.")
#define _hw_toggle_xmem_1(...)	_hw_toggle_xmem_2(HW_XMEM(__VA_ARGS__,))
#define _hw_toggle_xmem_2(...)	_hw_toggle_xmem_3(__VA_ARGS__)
#define _hw_toggle_xmem_3(x,...)	_hw_toggle_mem_##x(__VA_ARGS__)
#define _hw_toggle_mem_0	HW_ERR
#define _hw_toggle_mem_1(cn,ca,rn,rw,ra,rrv,rwm,rbn,rbp,v,_)	\
  _hw_toggle_r##rw(ca+ra,rbn,rbp)
#define _hw_toggle_mem_2(cn,ca,						\
			r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,		\
			r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,v,_)	\
  ((_hw_toggle_r##rw1(ca+ra1,rbn1,rbp1)&((1<<rbn1)-1)<<vbp1) |	\
   (_hw_toggle_r##rw2(ca+ar2,rbn2,rbp2)&((1<<rbn2)-1)<<vbp2))




/** \brief	Read from one 8-bit hardware register.
 *  \ca+ram p	address of register.
 *  \ca+ram rbn	number of consecutive bits conderned.
 *  \ca+ram rbp	position of the least significant bit conderned in the register.
 *  \return	the value of the rbn consecutive bits at position rbp in the register.
 */
HW_INLINE uint8_t _hw_read_r8 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  if ( ra == ~0 )
    HWA_ERR("invalid address");

  if ( rbp > 7 )
    HWA_ERR("bit pos > 7");

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
    HWA_ERR("invalid address");

  if ( rbp > 15 )
    HWA_ERR("bit pos > 15");

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
    HWA_ERR("invalid address");

  if ( rbp > 31 )
    HWA_ERR("bit pos > 31");

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
/*     HWA_ERR("invalid access"); */

/*   if ( rbn == 0 ) */
/*     HWA_ERR("no bit to be changed?"); */

/*   uint8_t m = (rbn > 7) ? (uint8_t)-1 : (1U<<rbn)-1 ; */

/*   if (v > m) */
/*     HWA_ERR("value too high for bits number"); */

/*   m <<= rbp ; */
/*   v <<= rbp ; */

/*   /\*	Check that we do not try to set non-writeable bits */
/*    *\/ */
/*   if ( (v & m & rwm) != (v & m) ) */
/*     HWA_ERR("bits not writeable."); */

/*   if ( (m & rwm) == rwm ) */
/*     *p = v ; */
/*   else */
/*     *p = (*p & ~m) | (v & m) ; */
/* } */

HW_INLINE void _hw_write_r8 ( intptr_t ra, uint8_t rwm,
			    uint8_t bn, uint8_t bp, uint8_t v )
{
  if ( ra == ~0 )
    HWA_ERR("invalid access");

  if ( bn == 0 )
    HWA_ERR("no bit to be changed?");

  uint8_t m = (bn > 7) ? (uint8_t)-1 : (1U<<bn)-1 ;

  if (v > m)
    HWA_ERR("value too high for bits number");

  m <<= bp ;
  v <<= bp ;

  /*	Check that we do not try to set non-writeable bits
   */
  if ( (v & m & rwm) != (v & m) )
    HWA_ERR("bits not writeable.");

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
    HWA_ERR("invalid access");

  if ( bn == 0 )
    HWA_ERR("no bit to be changed?");

  uint16_t m = (bn > 15) ? (uint16_t)-1 : (1U<<bn)-1 ;

  if (v > m)
    HWA_ERR("value too high for bits number");

  m <<= bp ;
  v <<= bp ;

  /*	Check that we do not try to set non-writeable bits
   */
  if ( (v & m & rwm) != (v & m) )
    HWA_ERR("bits not writeable.");

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
    HWA_ERR("invalid access");

  if ( rbn == 0 )
    HWA_ERR("no bit to be changed?");

  uint32_t m = (rbn > 31) ? (uint32_t)-1 : (1U<<rbn)-1 ;

  if (v > m)
    HWA_ERR("value too high for bits number");

  m <<= rbp ;
  v <<= rbp ;

  /*	Check that we do not try to set non-writeable bits
   */
  if ( (v & m & rwm) != (v & m) )
    HWA_ERR("bits not writeable.");

  if ( (m & rwm) == rwm )
    *p = v ;
  else
    *p = (*p & ~m) | (v & m) ;
}
