
/*	Device-specific hardware acess definitions.
 */


/**\brief	Software loop of \c n system clock cycles.
 * \todo	Only works with compile time constants
 * \hideinitializer
 */
#define hw_delay_cycles(n)		__builtin_avr_delay_cycles(n)


/*	Enable/disable interrupts
 */
#define hw_enable_interrupts()		__asm__ __volatile__ ("sei" ::)
#define hw_disable_interrupts()		__asm__ __volatile__ ("cli" ::)


#define HW_ATOMIC(...)				\
  do{						\
    uint8_t s = hw_read_reg(hw_core0,sreg);	\
    hw_disable_interrupts();			\
    __VA_ARGS__ ;				\
    hw_write_reg(hw_core0,sreg,s) ;		\
  }while(0)


/** \brief	Write one hardware register.
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

HW_INLINE void _hw_write_r8 ( intptr_t ra, uint8_t rwm, uint8_t rfm,
			      uint8_t bn, uint8_t bp, uint8_t v )
{
#if !defined HWA_NO_CHECK_ACCESS
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
      *p = (*p & rm) | (v & wm) ;
    }
  }
}

/* TODO: Atmel AVR8 does not have 16 bit access instructions. Could check
 *	sbi/cbi against 2 independent bytes
 */

HW_INLINE void _hw_write_r16 ( intptr_t ra, uint16_t rwm, uint16_t rfm,
			      uint8_t bn, uint8_t bp, uint16_t v )
{
  if ( ra == ~0 )
    HWA_ERR("invalid access");

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


/**  \brief Commits an HWA register
 *
 *  The code is meant to produce the best machine code among (verified on Atmel
 *  AVRs):
 *
 *  - bit-set or bit-clear:	1 instruction
 *  - load-immediate / store:	2 instructions
 *  - load / modify / store:	3 instructions
 */
HW_INLINE void _hwa_commit_r8 ( hwa_r8_t *r,
				intptr_t ra, uint8_t rwm, uint8_t rfm, _Bool commit )
{
  volatile uint8_t *p = (volatile uint8_t *)ra ;

  /*  Compute the mask of bits to be committed (do not commit bits untouched
   *  since last commit).
   *
   *  hwa_write does not permit r->mmask to extand beyond rwm but _hwa_set does.
   */
  /*  Mask of bits to be written (toggled or unknown bits)
   */
  uint8_t wm = rwm & r->mmask & ((r->ovalue ^ r->mvalue) | ~r->omask);

  if ( wm ) {

    if ( commit && (uintptr_t)p < 0x40 &&
	 (wm==0x01 || wm==0x02 || wm==0x04 || wm==0x08 ||
	  wm==0x10 || wm==0x20 || wm==0x40 || wm==0x80 ) ) {
    /*
     *  Just 1 bit to be written at C address < 0x40 (ASM address < 0x20): use
     *  sbi/cbi
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

    /*	Mask of bits to be read
     *	  = bits that are writeable and not to be modified and not flags
     */
    uint8_t rm = rwm & ~r->mmask & ~r->omask & ~rfm ;

    /*  Read only if needed: something to read, commit required
     */
    if ( rm && commit ) {
      r->ovalue = *p ;
      r->omask = rwm & ~rfm ;
    }

    /*  Compute value
     */
    r->ovalue = (r->ovalue & ~wm) | (r->mvalue & wm) ;

    /*  Write value if needed: something to write, commit required
     */
    if ( wm && commit )
      *p = r->ovalue ;
    r->ovalue &= ~rfm ;
  }

  r->omask |= r->mmask ;
  r->omask &= ~rfm ;
  r->mmask = 0 ;
}

HW_INLINE void _hwa_commit_r16 ( hwa_r16_t *r,
				 intptr_t ra, uint16_t rwm, uint16_t rfm, _Bool commit )
{
  volatile uint16_t *p = (volatile uint16_t *)ra ;
  uint16_t wm = r->mmask & ((r->ovalue ^ r->mvalue) | ~r->omask);
  if ( wm ) {
    /* Do not check for sbi/cbi for 16-bit access as 8-bit AVRs do not have
       16-bit configuration registers */
    uint16_t rm = rwm & ~r->mmask & ~r->omask & ~rfm ;
    if ( rm && commit ) {
      r->ovalue = *p ;
      r->omask = rwm & ~rfm ;
    }
    r->ovalue = (r->ovalue & ~wm) | (r->mvalue & wm) ;
    if ( wm && commit )
      *p = r->ovalue ;
    r->ovalue &= ~rfm ;
  }
  r->omask |= r->mmask ;
  r->omask &= ~rfm ;
  r->mmask = 0 ;
}


/** \brief	Read from one hardware register.
 *
 *  \param p	address of register.
 *  \param rbn	number of consecutive bits conderned.
 *  \param rbp	position of the least significant bit conderned in the register.
 *  \return	the value of the rbn consecutive bits at position rbp in the register.
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


#define hw_asm(...)	__asm__ __volatile__(__VA_ARGS__)
//#define hw_reti()	__asm__ __volatile__("reti\n":::)
#define hw_reti()	hw_asm("reti\n")
#define hw_sleep()	hw_asm("sleep\n")
