
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HWA definitions that produce C code
 */


/*
 * @ingroup public_ins
 * @brief Trigger an error after code generation.
 * @hideinitializer
 */
#define HWA_ERR(...)		_HWA_ERR_2(__COUNTER__,__VA_ARGS__)
#define _HWA_ERR_2(...)		_HWA_ERR_3(__VA_ARGS__)
#define _HWA_ERR_3(num,...)						\
  do {									\
    extern void __attribute__((error(#__VA_ARGS__))) hwa_error_##num(void); \
      hwa_error_##num();						\
  } while(0)


#define HWA_E(s)		_HWA_ERR_2(__COUNTER__,HW_Q(HWA: s.))
#define HWA_E_INTERNAL()	HWA_E(internal error)
#define HWA_E_VL(v,l)		HWA_E(`v` is not `l`)
#define HWA_E_NIL(v,l)		HWA_E(`v` is not in `l`)


/*
 * @ingroup public_ins
 * @brief Insert inline assembler code
 * @hideinitializer
 *
 * @code
 * hw_asm("reti");  // Insert the RETI instruction
 * @endcode
 */
#define hw_asm(...)			__asm__ __volatile__(__VA_ARGS__)


/*  Catch a trailing semicolon 
 */
extern void hw_foo();
#define HW_FOO()			extern void hw_foo()


#define hwa_begin_			, _hwa_begin_
#define hwa_begin_reset			, _hwa_begin_reset


/*
 * @ingroup public_ins
 * @brief Create a context to memorize what the `hwa(...)` instructions do.
 * @hideinitializer
 *
 * Nothing is written into the hardware until `hwa(commit)` is called.
 */
#define _hwa_begin_(g,...)		HW_B(_hwa_begin_,g)(g,__VA_ARGS__)
#define _hwa_begin_0(g,...)		HW_E(HW_EM_IA(g))
#define _hwa_begin_1(...)						\
  _hwa_check_optimizations(0);						\
  hwa_t hwa_st ; hwa_t *hwa = &hwa_st ;					\
  _hwa_setup_context(hwa) ;						\
  uint8_t hwa_xcommit = 0 /* Will warn if hwa(commit) is not called */


/*
 * @ingroup public_ins
 * @brief Create a context to memorize what the `hwa(...)` instructions do.
 * @hideinitializer
 *
 * The context is initialized with the values the registers have after a
 * system reset.
 *
 * Nothing is written into the hardware until `hwa(commit)` is called.
 */
#define _hwa_begin_reset(r,g,...)	HW_B(_hwa_begin_reset_,g)(g,__VA_ARGS__)
#define _hwa_begin_reset_0(r,g,...)	HW_E(HW_EM_IA(g))
#define _hwa_begin_reset_1(...)			\
  _hwa_check_optimizations(0);			\
  hwa_t hwa_st ; hwa_t *hwa = &hwa_st ;		\
  _hwa_setup_context(hwa) ;			\
  _hwa_init_context(hwa) ;			\
  _hwa_nocommit_() ;				\
  uint8_t hwa_xcommit = 0


/*
 * @ingroup public_ins
 * @brief Generate machine code for the configuration stored in the context.
 *
 * Solve the configuration stored into the HWA context, then do the required
 * hardware register writes.
 *
 * @hideinitializer
 */
/* _hwa_commit_context() must be defined somewhere in the device-specific files.
 */
#define _hwa_commit_(...)				\
  do {							\
    uint8_t foo __attribute__((unused)) = hwa_xcommit ;	\
    hwa->commit = 1 ;					\
    _hwa_commit_context(hwa);				\
  } while(0)

#define hwa_commit_				, _hwa_commit_


/*
 * @ingroup public_ins
 * @brief  Same as `hwa(commit)` but do not write into hardware.
 *
 * This is used to put the HWA context in a known state before modifying it.
 *
 * @hideinitializer
 */
#define _hwa_nocommit_(...)			\
  do {						\
    hwa->commit = 0 ;				\
    _hwa_commit_context(hwa);			\
  } while(0)

#define hwa_nocommit_			, _hwa_nocommit_


/*
 * @ingroup private_mac
 * @brief Specialize instruction `f` for class `c`: HW_FC(f,c,...) -> fc(...)
 * @hideinitializer
 *
 *  Arguments must start with a class name that is to be appended to the
 *  function name.
 */
#define HW_FC(...)		_HW_FC(__VA_ARGS__)
#define _HW_FC(f,c,...)		f##c(__VA_ARGS__,,)


/*
 * @ingroup private_ins
 * @brief Read one register of an object
 * @hideinitializer
 *
 * _hw_read( object, register );
 *
 */
#define _hw_read(o,r)		HW_FC(_hw_read_,HW_X((o,r)),)

#define _hw_read_(o,...)	HW_E(HW_A0(__VA_ARGS__))	// Error message

/*
 * @ingroup private_ins
 * @brief Read one register of an object with interrupts disabled
 * @hideinitializer
 *
 * `_hw_atomic_read( object, register );`
 */
#define _hw_atomic_read(o,r)	HW_FC(_hw_atomic_read_,HW_X((o,r)),)


#define hw_uint_t__r8		uint8_t
#define hw_uint_t__r16		uint16_t
#define hw_uint_t__r32		uint32_t


/*
 * @ingroup private_ins
 * @brief Write one register of an object
 * @hideinitializer
 *
 * `_hw_write( object, register, value );`
 */
#define _hw_write(o,r,v)	HW_FC(_hw_write_,HW_X((o,r)),v,)

#define _hw_write_(o,...)	HW_E(HW_A0(__VA_ARGS__))	// Error message

/*
 * @ingroup private_ins
 * @brief Write one register of an object
 * @hideinitializer
 *
 * `_hwa_write( object, register, value );`
 */
#define _hwa_write(o,r,v)	HW_FC(_hwa_write_,HW_X((o,r)),v,)

#define _hwa_write_(o,...)	HW_E(HW_A0(__VA_ARGS__))	// Error message


/*  Read/write _mem8/_mem16 (memory positions)
 *    Used by _swuart to access dt0/dtn registers.
 */
#define hw_read__mem8			, _hw_read_mem8
#define _hw_read_mem8(o,a,...)		*a

#define hw_read__mem16			, _hw_read_mem16
#define _hw_read_mem16(o,a,...)		*a

#define hw_write__mem8			, _hw_write_mem8
#define _hw_write_mem8(o,a,v,...)	*a = (v)

#define hw_write__mem16			, _hw_write_mem16
#define _hw_write_mem16(o,a,v,...)	*a = (v)


/*  Read/write memory of registers
 */
#define hw_read__m111		, _hw_read__m111

#define _hw_read__m111(n,o,r,c,a,wm,fm,bn,bp,...)	\
  _hw_read_##c(a,bn,bp)

#define hwa_write__m111		, _hwa_write__m111

#define _hwa_write__m111(n,o,r,c,a,wm,fm,bn,bp,v,...)	\
  _hwa_write##c(&hwa->o.r,wm,fm,((1ULL<<bn)-1)<<bp,((unsigned long long)(v))<<bp)

#define hw_write__m111		, _hw_write__m111

#define _hw_write__m111(n,o,r,c,a,wm,fm,bn,bp,v,...)	\
  _hw_write_##c(a,wm,fm,bn,bp,v)

#define _hw_write__m112(n,o,r,c,a,wm,fm,bn1,bp1,vp1,bn2,bp2,vp2,v,...)	\
  do{									\
    hw_uint_t_##c val = v ;						\
    _hw_write##c( a, wm, fm,						\
		  (((1ULL<<bn1)-1)<<bp1) | (((1ULL<<bn2)-1)<<bp2),	\
		  (((val>>vp1)&((1<<bn1)-1))<<bp1) | (((val>>bp2)&((1<<bn2)-1))<<bp2));	\
  }while(0)

#define hwa_write__m122		, _hwa_write__m122

#define _hwa_write__m122( n, o,						\
			  r1,c1,a1,wm1,fm1,bn1,bp1,vp1,			\
			  r2,c2,a2,wm2,fm2,bn2,bp2,vp2, v, ... )	\
  do {									\
    hw_uint_t_##c1 val = (v);						\
    _hwa_write_##c1(&hwa->o.r1, wm1,fm1, bn1,bp1, (val>>(vp1))&((1ULL<<bn1)-1)); \
    _hwa_write_##c2(&hwa->o.r2, wm2,fm2, bn2,bp2, (val>>(vp2))&((1ULL<<bn2)-1)); \
  } while(0)


/*
 * @brief  Write the register of an object
 */
#define _hwa_write_o(c,o,r,v,...)	_hwa_write(o,r,v) HW_EOL(__VA_ARGS__)


#define hwa_write__xob1		, _hwa__write__xob1

#define _hwa_write__xob1(o,r,bn,bp,v)	_hwa_write__xob1_2(hw_##o##_##r,o,r,bn,bp,v)
#define _hwa_write__xob1_2(...)		_hwa_write__xob1_3(__VA_ARGS__)
#define _hwa_write__xob1_3(rc,ra,rwm,rfm,o,r,bn,bp,v)	\
  _hwa_write_##rc( &hwa->o.r, rwm,rfm, bn,bp, v )

/*  Added for atmel/avr/classes/io1a_2.h:
 *    _hwa(write,_##o##_##did, 1);
 *    _hwa_write(_##o##_##did, 1);
 *	-> _hwa__write__xob1(hw_shared, did, 1, 0, 1,);
 *  FIXME: keep?
 */
#define _hwa__write__xob1(o,r,bn,bp,v,...)	_hwa_write__xob1(o,r,bn,bp,v)


/*
 * @ingroup private_ins
 * @brief Write some bits of a hardware register
 * @hideinitializer
 *
 * _hw_write_m( o, r, m, v );
 */
#define _hw_write_m(o,r,...)			HW_FC(_hw_wrorm,HW_X((o,r)),__VA_ARGS__,)

#define _hw_wrorm_m111(n,o,r,c,a,wm,fm,bn,bp,m,v,...)	_hw_write##c(a,wm,fm,m,v)

/*
 * @ingroup private_ins
 * @brief Write some bits of a hardware register
 * @hideinitializer
 *
 *	_hwa_write_m( o, r, m, v );
 */

#define _hwa_write_m(o,r,...)			HW_FC(_hwa_wrorm,HW_X((o,r)),__VA_ARGS__,)

#define _hwa_wrorm_m111(n,o,r,c,a,wm,fm,bn,bp,m,v,...)	_hwa_write##c(&hwa->o.r,wm,fm,m,v)


/*
 * @brief Initialize the HWA context registers addresses of an object
 */
#define _hwa_setup_o(o)			_hwa_setup00( o, hw_##o )
#define _hwa_setup00(...)		_hwa_setup01(__VA_ARGS__)
#define _hwa_setup01(o,c,a)		_hwa_setup_##c(o,a)


/*
 * @brief Initialize the HWA context registers of an object with their reset value
 */
#define _hwa_init_o(o)			_hwa_init00( o, hw_##o )
#define _hwa_init00(...)		_hwa_init01(__VA_ARGS__)
#define _hwa_init01(o,c,a)		_hwa_init_##c(o,a)


/*
 * @brief Solve the configuration of an object
 */
#define _hwa_solve_o(o)			_hwa_solve00( o, hw_##o )
#define _hwa_solve00(...)		_hwa_solve01(__VA_ARGS__)
#define _hwa_solve01(o,c,...)		_hwa_solve_##c(o,__VA_ARGS__)


/*
 * @brief Commit the registers of an object
 */
#define _hwa_commit_o(o)		_hwa_commit00( o, hw_##o )
#define _hwa_commit00(...)		_hwa_commit01(__VA_ARGS__)
#define _hwa_commit01(o,c,a)		_hwa_commit_##c(o,a)


/*
 * @ingroup private_ins
 * @brief Create a HWA register
 * @hideinitializer
 */
#define _hwa_setup_r(o,r)			_hwa_setup_or02(HW_X((o,r)))
#define _hwa_setup_or02(...)			_hwa_setup_or03(__VA_ARGS__)
#define _hwa_setup_or03(m,n,o,r,c,a,...)	_hwa_setup_##c(&hwa->o.r, a)


/*
 * @ingroup private_ins
 * @brief Initialize an HWA register of an object with its reset value
 * @hideinitializer
 */
#define _hwa_init_r(o,r,v)			_hwa_init_reg_2(v,HW_X((o,r)))
#define _hwa_init_reg_2(...)			_hwa_init_reg_3(__VA_ARGS__)
#define _hwa_init_reg_3(v,m,n,o,r,c,a,...)	_hwa_set_##c(&hwa->o.r, v)


/*
 * @ingroup private_ins
 * @brief Commit one object hardware register
 * @hideinitializer
 */
#define _hwa_commit_r(o,r)			HW_FC(_hwa_commit,HW_X((o,r)))

#define _hwa_commit_m111(n,o,r,c,a,wm,fm,bn,bp,...)	_hwa_commit_##c(&hwa->o.r,wm,fm,hwa->commit)

#define _hwa_nocommit_r(o,r)			HW_FC(_hwa_nocommit,HW_X((o,r)))

#define _hwa_nocommit_m111(n,o,r,c,a,wm,fm,bn,bp,...)	_hwa_commit_##c(&hwa->o.r,wm,fm,0)


/*
 * @ingroup private_ins
 * @brief Get the mmask of the logical register `r` of object `o`.
 *
 * The mmask is set each time a `write` is performed. It is reset after the
 * value has been committed.
 *
 * @hideinitializer
 */
#define _hwa_mmask(o,r)				HW_FC(_hwa_mmask_,HW_X(o,r))

#define _hwa_mmask__m111(n,o,r,c,a,wm,fm,bn,bp,...)	(((hwa->o.r.mmask)>>bp)&((1ULL<<bn)-1))


/*
 * @ingroup private_ins
 * @brief Get the value to be committed for the logical register `r` of object `o`.
 * @hideinitializer
 */
#define _hwa_mvalue(o,r)				HW_FC(_hwa_mvalue_,HW_X(o,r))

#define _hwa_mvalue__m111(n,o,r,c,a,wm,fm,bn,bp,...)	(((hwa->o.r.mvalue)>>bp)&((1ULL<<bn)-1))


/*
 * @ingroup private_ins
 * @brief Get the last committed value for the logical register `r` of object `o`.
 * @hideinitializer
 */
#define _hwa_ovalue(o,r)				HW_FC(_hwa_ovalue_,HW_X(o,r))

#define _hwa_ovalue__m111(n,o,r,c,a,wm,fm,bn,bp,...)	(((hwa->o.r.ovalue)>>bp)&((1ULL<<bn)-1))



HW_INLINE void _hwa_setup__r8 ( hwa_r8_t *r, intptr_t a )
{
  r->a		= a ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}

HW_INLINE void _hwa_setup__r16 ( hwa_r16_t *r, intptr_t a )
{
  r->a		= a ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}

HW_INLINE void _hwa_setup__r32 ( hwa_r32_t *r, intptr_t a )
{
  r->a		= a ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}


/*
 * @ingroup private_ins
 * @brief  Initialize a HWA register to a specific value (usually the reset value).
 * @hideinitializer
 */
HW_INLINE void _hwa_set__r8 ( hwa_r8_t *r, uint8_t v )
{
  if ( r->mmask )
    HWA_ERR("commit required before resetting.");

  r->mmask = 0xFF ;
  r->mvalue = v ;
}

HW_INLINE void _hwa_set__r16 ( hwa_r16_t *r, uint16_t v )
{
  if ( r->mmask )
    HWA_ERR("commit required before resetting.");

  r->mmask = 0xFFFF ;
  r->mvalue = v ;
}

HW_INLINE void _hwa_set__r32 ( hwa_r32_t *r, uint32_t v )
{
  if ( r->mmask )
    HWA_ERR("commit required before resetting.");

  r->mmask = 0xFFFFFFFF ;
  r->mvalue = v ;
}


/*
 * @ingroup private_ins
 * @brief  Write into one 8-bit context register.
 *
 * Write value `v` into `msk` bits of the context register pointed by
 * `r`. Trying to write `1`s into non-writeable bits triggers an error.
 *
 * The mask of modified values `mmask` is set according to `msk` even if
 * the value is not modified. `_hwa_commit__r8()` will check if the register has
 * effectively been modified.
 *
 * @param r	register pointer.
 * @param rwm	writeable bits mask of the register.
 * @param rfm	flag bits mask of the register.
 * @param msk	mask of bits concerned.
 * @param v	value to write.
 */
HW_INLINE void _hwa_write_r8 ( hwa_r8_t *r, uint8_t rwm, uint8_t rfm, uint8_t msk, uint8_t v )
{
  if (v & ~msk)
    HWA_ERR("value overflows the mask.");

  if ((rwm & msk) != msk)
    HWA_ERR("trying to modify bits that are not writeable.");

  if ((r->mmask & msk) != 0 && (r->mvalue & msk) != v)
    HWA_ERR("committing is required before setting a new value.");

  if ( msk & rfm )
    if ( v == 0 )
      HWA_ERR("flag bit can only be cleared by writing 1 into it.");

  r->mmask |= msk ;
  r->mvalue = (r->mvalue & ~msk) | (msk & v) ;
}

HW_INLINE void _hwa_write_r16 ( hwa_r16_t *r, uint16_t rwm, uint16_t rfm, uint16_t msk, uint16_t v )
{
  if (v & ~msk)
    HWA_ERR("value overflows the mask.");

  if ((rwm & msk) != msk)
    HWA_ERR("trying to modify bits that are not writeable.");

  if ((r->mmask & msk) != 0 && (r->mvalue & msk) != v)
    HWA_ERR("committing is required before setting a new value.");

  if ( msk & rfm )
    if ( v == 0 )
      HWA_ERR("flag bit can only be cleared by writing 1 into it.");

  r->mmask |= msk ;
  r->mvalue = (r->mvalue & ~msk) | (msk & v) ;
}

HW_INLINE void _hwa_write_r32 ( hwa_r32_t *r, uint32_t rwm, uint32_t rfm, uint32_t msk, uint32_t v )
{
  if ( (v & msk & rwm) != v )
    HWA_ERR("value overflow.");

  if ((rwm & msk) != msk && msk != 0xFFFFFFFF )
    HWA_ERR("trying to modify bits that are not writeable.");

  if ((r->mmask & msk) != 0 && (r->mvalue & msk) != v)
    HWA_ERR("committing is required before setting a new value.");

  if ( msk & rfm )
    if ( v == 0 )
      HWA_ERR("flag bit can only be cleared by writing 1 into it.");

  r->mmask |= msk ;
  r->mvalue = (r->mvalue & ~msk) | (msk & v) ;
}


/*
 * @ingroup private_ins
 * @brief Trigger an error if optimizers failed to remove this code
 * @hideinitializer
 */
HW_INLINE void _hwa_check_optimizations ( uint8_t x )
{
  if (x) { HWA_ERR("you may have forgotten to turn optimizations on."); }
}


#define _hw_write__r8(ra,rwm,rfm,bn,bp,v)	_hw_write_r8(ra,rwm,rfm,((1UL<<bn)-1)<<bp,((uint8_t)(v))<<bp)
#define _hw_write__r16(ra,rwm,rfm,bn,bp,v)	_hw_write_r16(ra,rwm,rfm,((1UL<<bn)-1)<<bp,(v)<<bp)
#define _hw_write__r32(ra,rwm,rfm,bn,bp,v)	_hw_write_r32(ra,rwm,rfm,((1ULL<<bn)-1)<<bp,(v)<<bp)

#define _hwa_write__r8(ra,rwm,rfm,bn,bp,v)	_hwa_write_r8(ra,rwm,rfm,((1UL<<bn)-1)<<bp,((uint8_t)(v))<<bp)
#define _hwa_write__r16(ra,rwm,rfm,bn,bp,v)	_hwa_write_r16(ra,rwm,rfm,((1UL<<bn)-1)<<bp,(v)<<bp)
#define _hwa_write__r32(ra,rwm,rfm,bn,bp,v)	_hwa_write_r32(ra,rwm,rfm,((1ULL<<bn)-1)<<bp,(v)<<bp)


