
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions that produce C code specific to Atmel AVR devices
 */

#define HW_MEM_EEPROM			__attribute__((section(".eeprom")))

#define hw_asm(...)			__asm__ __volatile__(__VA_ARGS__)

#define hw_reti()			hw_asm("reti")
#define hw_sleep()			hw_asm("sleep")
#define hw_enable_interrupts()		hw_asm("sei")
#define hw_disable_interrupts()		hw_asm("cli")


/**
 * @brief Software loop of \c n system clock cycles.
 * @todo  Only works with compile time constants
 * @hideinitializer
 */
#define hw_delay_cycles(n)		__builtin_avr_delay_cycles(n)


/**
 * @brief	True if strings s0 and s1 are equal
 */
#define hw_streq(s0,s1)			(__builtin_strcmp(s0,s1)==0)


/**
 * @brief Execute a block with interrupts disabled
 * @hideinitializer
 */
#define HW_ATOMIC(...)				\
  do{						\
    uint8_t s = _hw_read_reg(hw_core0,sreg);	\
    hw_disable_interrupts();			\
    { __VA_ARGS__ }				\
    _hw_write_reg(hw_core0,sreg,s) ;		\
  }while(0)


/*
 *  FIXME: there is something strange here: why does _hw_write_r8 do almost the
 *  same things as does _hw_commit_r8? How can the fix below solve the problem
 *  from here? All that should be looked after carefully again...
 *  Simplifications in sight!
 */
/**
 * @brief  Write one hardware register.
 *
 *  Write the value into the rbn consecutive bits starting at pos rbp into
 *  the hard register at address p. Trying to write 1s into non-writeable
 *  bits triggers an error.
 *
 * @param ra	address of register.
 * @param rwm	writeable bits mask of the register.
 * @param rfm	flag bits mask of the register.
 * @param bn	number of consecutive bits conderned.
 * @param bp	position of the least significant bit conderned in the register.
 * @param v	value to write.
 */
HW_INLINE void _hw_write_r8 ( intptr_t ra, uint8_t rwm, uint8_t rfm,
			      uint8_t bn, uint8_t bp, uint8_t v )
{
#if defined HWA_CHECK_ACCESS
  if ( ra == ~0 )
    HWA_ERR("invalid access");
#endif

#if !defined HWA_NO_CHECK_USEFUL
  if ( bn == 0 )
    HWA_ERR("no bit to be changed?");
#endif

  /*	Mask of bits to modify
   */
  uint8_t wm = (1U<<bn)-1 ;

#if !defined HWA_NO_CHECK_LIMITS
  if (v > wm)
    HWA_ERR("value too high for bits number");
#endif

  wm <<= bp ;
  v <<= bp ;

  /*	Check that we do not try to set non-writeable bits
   */
  if ( (v & wm & rwm) != (v & wm) )
    HWA_ERR("bits not writeable.");

  volatile uint8_t *p = (volatile uint8_t *)ra ;

  if ( ra < 0x40 && 
       (wm==0x01 || wm==0x02 || wm==0x04 || wm==0x08 ||
	wm==0x10 || wm==0x20 || wm==0x40 || wm==0x80) ) {
    /*
     *  Just 1 bit to be written at C address < 0x40 (ASM address < 0x20): use
     *  sbi/cbi
     */
    if ( v )
      *p |= wm ; /* sbi */
    else {
      if ( wm & rfm )
	HWA_ERR("flag bit can only be cleared by writing 1 into it.");
      *p &= ~wm ; /* cbi */
    }
  }
  else {
    /*
     *	Mask of bits to be read
     *	  = bits that are writeable and not to be modified and not flags
     */
    uint8_t rm = rwm & ~wm & ~rfm ;

    if ( rm == 0 )
      /*
       *  Nothing to be read, just write the new value
       */
      *p = v ;
    else {
      /*
       *  Read-modify-write
       */
#if 0
      /*
       *  FIXME: hw_write_reg(hw_counter1, ices, 1) produces an extra
       *  'andi reg, 0x9F' though bit 5 is not writeable and should not be reset.
       */
      *p = (*p & rm) | (v & wm) ;
#else
      /*  FIX
       */
      uint8_t sm = wm & v ;     /* what has to be set     */
      uint8_t cm = wm & (~v) ;  /* what has to be cleared */
      *p = (*p & ~cm) | sm ;
#endif
    }
  }
}

/* TODO: Atmel AVR8 does not have 16 bit access instructions. Could check
 *	sbi/cbi against 2 independent bytes
 */

HW_INLINE void _hw_write_r16 ( intptr_t ra, uint16_t rwm, uint16_t rfm,
			      uint8_t bn, uint8_t bp, uint16_t v )
{
#if defined HWA_CHECK_ACCESS
  if ( ra == ~0 )
    HWA_ERR("invalid access");
#endif

  if ( bn == 0 )
    HWA_ERR("no bit to be changed?");

  /*	Mask of bits to modify
   */
  uint16_t wm = (1U<<bn)-1 ;

  if (v > wm)
    HWA_ERR("value too high for bits number");

  wm <<= bp ;
  v <<= bp ;

  /*	Check that we do not try to set non-writeable bits
   */
  if ( (v & wm & rwm) != (v & wm) )
    HWA_ERR("bits not writeable.");

  volatile uint16_t *p = (volatile uint16_t *)ra ;

  if ( ra < 0x40 && 
       (wm==0x0001 || wm==0x0002 || wm==0x0004 || wm==0x0008 ||
	wm==0x0010 || wm==0x0020 || wm==0x0040 || wm==0x0080 ||
	wm==0x0100 || wm==0x0200 || wm==0x0400 || wm==0x0800 ||
	wm==0x1000 || wm==0x2000 || wm==0x4000 || wm==0x8000) ) {
    /*
     *  Just 1 bit to be written at C address < 0x40 (ASM addresses < 0x20): use
     *  sbi/cbi
     */
    if ( v )
      *p |= wm ; /* sbi */
    else {
      if ( wm & rfm )
	HWA_ERR("flag bit can only be cleared by writing 1 into it.");
      *p &= ~wm ; /* cbi */
    }
  }
  else {
    /*
     *	Mask of bits to be read
     *	  = bits that are writeable and not to be modified and not flags
     */
    uint16_t rm = rwm & ~wm & ~rfm ;

    if ( rm == 0 )
      /*
       *  Nothing to be read, just write the new value
       */
      *p = v ;
    else {
      /*
       *  Read-modify-write
       */
      *p = (*p & rm) | (v & wm) ;
    }
  }
}


/*	Commit register r of class c pointed by p
 */
#define _hwa_commit_reg_p(p,c,r)	_hwa_corp_2(_hw_creg(c,r), p)
#define _hwa_corp_2(...)		_hwa_corp_3(__VA_ARGS__)
#define _hwa_corp_3(t,...)		_hwa_corp_##t(__VA_ARGS__)

#define _hwa_corp__m1(_0,_1,r,rw,ra,rwm,rfm, bn,bp, p)	\
  _hwa_commit_r##rw(&((p)->r),rwm,rfm,hwa->commit)

#define _hwa_corp__m1x(p,_1,r,rw,ra,rwm,rfm, bn,bp, p0)	\
  _hwa_commit_r##rw(&hwa->p.r,rwm,rfm,hwa->commit)


/**  \brief Commits an HWA register
 *
 *  The code is meant to produce the best machine code among (verified on Atmel
 *  AVRs):
 *
 *  - bit-set or bit-clear:	1 instruction
 *  - load-immediate / store:	2 instructions
 *  - load / modify / store:	3 instructions or more
 */
HW_INLINE void _hwa_commit_r8 ( hwa_r8_t *r, uint8_t rwm, uint8_t rfm, _Bool commit )
{
  if ( !commit ) {
    r->ovalue = (r->ovalue & r->omask & ~r->mmask) | (r->mvalue & r->mmask) ;
    r->omask |= r->mmask ;
    r->mmask = 0 ;
    return ;
  }

  volatile uint8_t *p = (volatile uint8_t *)r->a ;

  /*  Mask of bits to be written:
   *    =     bits that are writeable (rwm)
   *      AND that has been written (mmask)
   *      AND that really need to be modified (ovalue != mvalue)
   */
  uint8_t wm = rwm & r->mmask & ((r->ovalue ^ r->mvalue) | ~r->omask);

  if ( wm ) {
    if ( (uintptr_t)p < 0x40 &&
	 (wm==0x01 || wm==0x02 || wm==0x04 || wm==0x08 ||
	  wm==0x10 || wm==0x20 || wm==0x40 || wm==0x80 ) ) {
      /*
       *  Just 1 bit to be modified at C address < 0x40 (ASM address < 0x20): use
       *  instruction CBI or SBI
       */
      if ( wm & r->mvalue )
	*p |= wm ; /* sbi */
      else
	*p &= ~wm ; /* cbi */
      r->ovalue = (r->ovalue & ~wm) | (r->mvalue & wm) ;
      r->omask |= wm ;
      r->mmask = 0 ;
      return ;
    }

    /*	Mask of bits to be read
     *	  =     bits that are not to be modified (mmask)
     *      AND not flags (rfm)
     *      AND that are not known (omask)
     *      AND that are writeable (rwm)
     */
    uint8_t rm = ~r->mmask & ~rfm & ~r->omask & rwm ;

    /*  Read only if needed
     */
    if ( rm )
      r->ovalue = *p ;

    /*  Compute new value
     */
    r->ovalue = ((r->ovalue & ~wm) | (r->mvalue & wm)) & ~rfm ;

    /*  Write new value
     */
    *p = r->ovalue | (rfm & r->mmask & r->mvalue) ;
  }

  r->omask |= r->mmask ;
  r->mmask = 0 ;
}


HW_INLINE void _hwa_commit_r16 ( hwa_r16_t *r, uint16_t rwm, uint16_t rfm, _Bool commit )
{
  if ( !commit ) {
    r->ovalue = (r->ovalue & r->omask & ~r->mmask) | (r->mvalue & r->mmask) ;
    r->omask |= r->mmask ;
    r->mmask = 0 ;
    return ;
  }

  volatile uint16_t *p = (volatile uint16_t *)r->a ;

  uint16_t wm = rwm & r->mmask & ((r->ovalue ^ r->mvalue) | ~r->omask);

  if ( wm ) {
    /*
     * Do not check for sbi/cbi for 16-bit access as since 8-bit AVRs do not
     * have 16-bit configuration registers, it is unlikely that it would be
     * useful.
     */
    uint16_t rm = ~r->mmask & ~rfm & ~r->omask & rwm ;

    if ( rm )
      r->ovalue = *p ;

    r->ovalue = ((r->ovalue & ~wm) | (r->mvalue & wm)) & ~rfm ;

    *p = r->ovalue | (rfm & r->mmask & r->mvalue) ;
  }

  r->omask |= r->mmask ;
  r->mmask = 0 ;
}



/**
 * @brief Read from one hardware register.
 *
 * @param ra	address of register.
 * @param rbn	number of consecutive bits conderned.
 * @param rbp	position of the least significant bit conderned in the register.
 * @return	the value of the rbn consecutive bits at position rbp in the register.
 */
HW_INLINE uint8_t _hw_read_r8 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  uint8_t m = (1U<<rbn)-1 ;
  volatile uint8_t *p = (volatile uint8_t *)ra ;
  return ((*p)>>rbp) & m ;
}

HW_INLINE uint16_t _hw_read_r16 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  uint16_t m = (1UL<<rbn)-1 ;
  volatile uint16_t *p = (volatile uint16_t *)ra ;
  return ((*p)>>rbp) & m ;
}


/*	Atomic read
 *
 *	FIXME: if the I bit is set after writing SREG with its prior value, is
 *	the execution of the next opcode guaranteed as if the SEI instruction
 *	was used?
 */
#define _hw_atomic_read_r8		_hw_read_r8

HW_INLINE uint16_t _hw_atomic_read_r16 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  volatile uint8_t *pl = (volatile uint8_t *)ra+0 ;
  volatile uint8_t *ph = (volatile uint8_t *)ra+1 ;
  uint16_t v ;
  uint16_t m = (1UL<<rbn)-1 ;

  if ( (m & 0xFF) && (m >> 8) ) {
    uint8_t s = _hw_read_reg(hw_core0,sreg);
    hw_disable_interrupts();
    uint8_t lb = *pl ;
    _hw_write_reg(hw_core0,sreg,s);
    uint8_t hb = *ph ;
    v = (hb << 8) | lb ;
  }
  else if ( m & 0xFF )
    v = *pl ;
  else
    v = (*ph)<<8 ;
  return (v>>rbp) & m ;
}


/*	ISR
 */
#define hw_israttr_isr_interruptible		, __attribute__((interrupt))
#define hw_israttr_isr_non_interruptible	, 
#define hw_israttr_isr_naked			, __attribute__((naked))

#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  define HW_ISR_ATTRIBUTES __attribute__((signal, used, externally_visible))
#else /* GCC < 4.1 */
#  define HW_ISR_ATTRIBUTES __attribute__((signal, used))
#endif

/*  Single event ISR
 */
#define _hw_isr_(vector, ...)						\
  HW_EXTERN_C void __vector_##vector(void) HW_ISR_ATTRIBUTES __VA_ARGS__ ; \
  void __vector_##vector (void)
