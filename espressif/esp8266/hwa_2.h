
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions that produce C code specific to Atmel AVR devices
 */

/**
 * @ingroup public_ins_espressif
 * @brief Insert inline assembler code
 * @hideinitializer
 *
 * Syntax: `hw_asm("reti");  // Insert the RETI instruction`
 */
#define hw_asm(...)			__asm__ __volatile__(__VA_ARGS__)

/**
 * @ingroup public_ins_espressif
 * @brief Return from a naked interrupt service routine.
 * @hideinitializer
 */
#define hw_reti()			hw_asm("reti")

/**
 * @ingroup public_ins_espressif
 * @brief Put the core in sleep mode.
 */
#define hw_sleep_until_irq()			hw_asm("sleep")

/**
 * @ingroup public_ins_espressif
 * @brief Software loop of \c n system clock cycles.
 *
 * Only works with compile time constants.
 */
#define hw_waste_cycles(n)		__builtin_avr_delay_cycles(n)

#define _hw_enirqs(o,a,...)			hw_asm("sei") HW_EOL(__VA_ARGS__)
#define _hw_dsirqs(o,a,...)			hw_asm("cli") HW_EOL(__VA_ARGS__)

#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  define HW_ISR_ATTRIBUTES __attribute__((signal, used, externally_visible))
#else /* GCC < 4.1 */
#  define HW_ISR_ATTRIBUTES __attribute__((signal, used))
#endif

#include "../hwa/hwa_2.h"


/**
 * @brief Power a peripheral on/off.
 *
 * This is a generic method that can be implemented by all peripheral
 * classes. An object supports power management if it has a logical register
 * named `prr`.
 *
 * This definition handles both hw_power() and hwa_power().
 */
/*  Merge hw_power() and hwa_power() to _hwx_pwr(), check the validity of the
 *  given state.
 */
#define _hw_power(o,a,v,...)		HW_Y(_hwx_pwr_,_hw_state_##v)(o,_hw,v,__VA_ARGS__,)
#define _hwa_power(o,a,v,...)		HW_Y(_hwx_pwr_,_hw_state_##v)(o,_hwa,v,__VA_ARGS__,)

#define _hwx_pwr_0(o,x,v, ...)		HW_E_VL(v, o | off)

#define _hwx_pwr_1(o,x,v, ...)		\
  HW_G2(_hwx_pwr1,HW_IS(hw_error,hw_reg(o,prr)))(o,x,v) HW_EOL(__VA_ARGS__)

/*  Register prr exists, process the instruction
 */
#define _hwx_pwr1_0(o,x,v)	x##_write(o,prr,HW_A1(_hw_state_##v)==0)

/*  Register prr does not exist
 */
#define _hwx_pwr1_1(o,x,v)	HW_E(`o` does not support power management)


/**
 * @ingroup public_ins_espressif
 * @brief Execute a block with interrupts disabled
 * @hideinitializer
 */
#define HW_ATOMIC(...)				\
  do{						\
    uint8_t s = _hw_read(core0,sreg);	\
    hw( disable, interrupts );			\
    { __VA_ARGS__ }				\
    _hw_write(core0,sreg,s) ;		\
  }while(0)


/**
 * @ingroup public_ins_espressif
 * @brief EEPROM memory segment storage
 *
 * Syntax:
 * @code
 * static uint16_t HW_MEM_EEPROM numbers[16] ;	// 16 16-bit numbers in EEPROM
 * @endcode
 */
#define HW_MEM_EEPROM			__attribute__((section(".eeprom")))


/**
 * @ingroup private
 * @brief  Write one 8-bit hardware register using mask and value
 *
 * Write value `v` through `mask` bits of the hardware register at address `p`.
 * Trying to write `1`s into non-writeable bits triggers an error.
 *
 * @param ra	address of register.
 * @param rwm	writeable bits mask of the register.
 * @param rfm	flag bits mask of the register.
 * @param mask	mask of bits concerned.
 * @param value	value to write.
 */
HW_INLINE void _hw_write_r8 ( intptr_t ra, uint8_t rwm, uint8_t rfm, uint8_t mask, uint8_t value )
{
#if defined HWA_CHECK_ACCESS
  if ( ra == ~0 )
    HWA_ERR("invalid access");
#endif

#if !defined HWA_NO_CHECK_USEFUL
  if ( mask == 0 )
    HWA_ERR("no bit to be changed?");
#endif

#if !defined HWA_NO_CHECK_LIMITS
  if ( value & (~mask) ) {
    HWA_ERR("value overflows mask");
  }
#endif

  /*  Verify that we do not try to set non-writeable bits
   */
  if ( (value & mask & rwm) != (value & mask) )
    HWA_ERR("bits not writeable.");

  volatile uint8_t *p = (volatile uint8_t *)ra ;

  if ( ra < 0x40 && 
       (mask==0x01 || mask==0x02 || mask==0x04 || mask==0x08 ||
	mask==0x10 || mask==0x20 || mask==0x40 || mask==0x80) ) {
    /*
     *	Just 1 bit to be written at C address < 0x40 (ASM address < 0x20): use
     *	sbi/cbi
     */
    if ( value )
      *p |= mask ; /* sbi */
    else
      *p &= ~mask ; /* cbi */
  }
  else {
    /*
     *	Mask of bits to be read
     *	  = bits that are writeable and not to be modified and not flags
     */
    uint8_t rm = rwm & ~mask & ~rfm ;

    if ( rm == 0 )
      /*
       *  Nothing to be read, just write the new value
       */
      *p = value ;
    else {
      /*
       *  Read-modify-write
       */
      uint8_t sm = mask & rwm & value ;	    /* what has to be set     */
      uint8_t cm = mask & rwm & (~value) ;  /* what has to be cleared */
      *p = (*p & ~cm) | sm ;
    }
  }
}


/**
 * @ingroup private
 * @brief  Write one 8-bit hardware register.
 */
/* TODO: Atmel AVR8 does not have 16 bit access instructions. Could check
 *	sbi/cbi for 2 different bytes
 */
HW_INLINE void _hw_write_r16 ( intptr_t ra, uint16_t rwm, uint16_t rfm, uint8_t bn, uint8_t bp, uint16_t v )
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
    HWA_ERR("value too high for number of bits");

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
     *	FIXME: could put a signal here to see if that code is usefull.
     */
    /*
     *	Just 1 bit to be written at C address < 0x40 (ASM addresses < 0x20): use
     *	sbi/cbi
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


/**
 * @ingroup private
 * @brief  Write one 32-bit hardware register using mask and value
 *
 * Write value `v` through `mask` bits of the hardware register at address `p`.
 * Trying to write `1`s into non-writeable bits triggers an error.
 *
 * @param ra	address of register.
 * @param rwm	writeable bits mask of the register.
 * @param rfm	flag bits mask of the register.
 * @param mask	mask of bits concerned.
 * @param value	value to write.
 */
HW_INLINE void _hw_write_r32 ( intptr_t ra, uint32_t rwm, uint32_t rfm, uint32_t mask, uint32_t value )
{
#if defined HWA_CHECK_ACCESS
  if ( ra == ~0 )
    HWA_ERR("invalid access");
#endif

#if !defined HWA_NO_CHECK_USEFUL
  if ( mask == 0 )
    HWA_ERR("no bit to be changed?");
#endif

#if !defined HWA_NO_CHECK_LIMITS
  if ( value & (~mask) ) {
    HWA_ERR("value overflows mask");
  }
#endif

  /*  Verify that we do not try to set non-writeable bits
   */
  if ( (value & mask & rwm) != (value & mask) )
    HWA_ERR("bits not writeable.");

  volatile uint32_t *p = (volatile uint32_t *)ra ;

  /*
   *	Mask of bits to be read
   *	  = bits that are writeable and not to be modified and not flags
   */
  uint32_t rm = rwm & ~mask & ~rfm ;

  if ( rm == 0 )
    /*
     *	Nothing to be read, just write the new value
     */
    *p = value ;
  else {
    /*
     *	Read-modify-write
     */
    uint32_t cm = mask & rwm ;	/* what has to be cleared */
    uint32_t sm = value ;     /* what has to be set	*/
    *p = (*p & ~cm) | sm ;
  }
}


/**
 * @ingroup private
 * @brief Commit an 8-bit HWA register to hardware
 * @hideinitializer
 *
 * The code is meant to produce the best machine code among (verified on Atmel
 * AVRs):
 *
 * - bit-set or bit-clear:	1 instruction
 * - load-immediate / store:	2 instructions
 * - load / modify / store:	3 instructions or more
 */
HW_INLINE void _hwa_commit__r8 ( hwa_r8_t *r, uint8_t rwm, uint8_t rfm, _Bool commit )
{
  if ( !commit ) {
    r->ovalue = (r->ovalue & r->omask & ~r->mmask) | (r->mvalue & r->mmask) ;
    r->omask |= r->mmask ;
    r->mmask = 0 ;
    return ;
  }

  volatile uint8_t *p = (volatile uint8_t *)r->a ;

  /*  Mask of bits to be written:
   *	=     bits that are writeable (rwm)
   *	  AND that has been written (mmask)
   *	  AND that really need to be modified (ovalue != mvalue)
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
     *	  =	bits that are not to be modified (mmask)
     *	    AND not flags (rfm)
     *	    AND that are not known (omask)
     *	    AND that are writeable (rwm)
     */
    uint8_t rm = ~r->mmask & ~rfm & ~r->omask & rwm ;

    /*	Read only if needed
     */
    if ( rm )
      r->ovalue = *p ;

    /*	Compute new value
     */
    r->ovalue = ((r->ovalue & ~wm) | (r->mvalue & wm)) & ~rfm ;

    /*	Write new value
     */
    *p = r->ovalue | (rfm & r->mmask & r->mvalue) ;
  }

  r->omask |= r->mmask ;
  r->mmask = 0 ;
}


HW_INLINE void _hwa_commit__r16 ( hwa_r16_t *r, uint16_t rwm, uint16_t rfm, _Bool commit )
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
     * Do not try sbi/cbi for 16-bit access as since 8-bit AVRs do not have
     * 16-bit configuration registers, it is unlikely that it would be useful.
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
 * @ingroup private
 * @brief Commit an 32-bit HWA register to hardware
 * @hideinitializer
 */
HW_INLINE void _hwa_commit__r32 ( hwa_r32_t *r, uint32_t rwm, uint32_t rfm, _Bool commit )
{
  if ( !commit ) {
    r->ovalue = (r->ovalue & r->omask & ~r->mmask) | (r->mvalue & r->mmask) ;
    r->omask |= r->mmask ;
    r->mmask = 0 ;
    return ;
  }

  volatile uint32_t *p = (volatile uint32_t *)r->a ;

  /*  Mask of bits to be written:
   *	=     bits that are writeable (rwm)
   *	  AND that has been written (mmask)
   *	  AND that really need to be modified (ovalue != mvalue)
   */
  uint32_t wm = rwm & r->mmask & ((r->ovalue ^ r->mvalue) | ~r->omask);

  if ( wm ) {
    /*	Mask of bits to be read
     *	  =	bits that are not to be modified (mmask)
     *	    AND not flags (rfm)
     *	    AND that are not known (omask)
     *	    AND that are writeable (rwm)
     */
    uint32_t rm = ~r->mmask & ~rfm & ~r->omask & rwm ;

    /*	Read only if needed
     */
    if ( rm )
      r->ovalue = *p ;

    /*	Compute new value
     */
    r->ovalue = ((r->ovalue & ~wm) | (r->mvalue & wm)) & ~rfm ;

    /*	Write new value
     */
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
HW_INLINE uint8_t _hw_read__r8 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  uint8_t m = (1U<<rbn)-1 ;
  volatile uint8_t *p = (volatile uint8_t *)ra ;
  return ((*p)>>rbp) & m ;
}

HW_INLINE uint16_t _hw_read__r16 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  uint16_t m = (1UL<<rbn)-1 ;
  volatile uint16_t *p = (volatile uint16_t *)ra ;
  return ((*p)>>rbp) & m ;
}

HW_INLINE uint32_t _hw_read__r32 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  uint32_t m = (1ULL<<rbn)-1 ;
  volatile uint32_t *p = (volatile uint32_t *)ra ;
  return ((*p)>>rbp) & m ;
}


/*	Atomic read
 *
 *	FIXME: if the I bit is set after writing SREG with its prior value, is
 *	the execution of the next opcode guaranteed as if the SEI instruction
 *	was used?
 */
#define _hw_atomic_read__r8		_hw_read__r8


HW_INLINE uint16_t __hw_atomic_read__r16 ( intptr_t ra )
{
  uint16_t r;

  hw_asm("cli"			"\n\t"
	 "lds %A[r], %[a]"	"\n\t"
	 "sei"			"\n\t"
	 "lds %B[r], %[a]+1"	"\n\t"
	 : [r] "=&r" (r)
	 : [a] "p"   (ra)
	 : "memory"
	 );
  return r;
}


HW_INLINE uint16_t _hw_atomic_read__r16 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  uint16_t v ;
  uint16_t m = ((1UL<<rbn)-1)<<rbp ;

#if 0
  volatile uint8_t *pl = (volatile uint8_t *)ra+0 ;
  volatile uint8_t *ph = (volatile uint8_t *)ra+1 ;

  if ( (m & 0xFF) && (m >> 8) ) {
    uint8_t s = _hw_read(core0,sreg);
    hw( disable, interrupts );
    uint8_t lb = *pl ;
    _hw_write(core0,sreg,s);
    uint8_t hb = *ph ;
    v = (hb << 8) | lb ;
  }
  else if ( m & 0xFF )
    v = *pl ;
  else
    v = (*ph)<<8 ;
#else
  if ( (m&0xFF) == 0 )
    v = (*(volatile uint8_t *)ra+1)<<8 ;
  else if ( (m>>8) == 0 )
    v = *(volatile uint8_t *)ra;
  else
    v = __hw_atomic_read__r16( ra );
#endif

  return (v>>rbp) & m ;
}


#if 0
/*
 *	From http://www.avrfreaks.net/forum/atomic-readwrite-uint16t-variable?skey=atomic%20write
 */
#define atomic_read_word(__addr)		      \
(__extension__({				      \
  uint16_t __result;				      \
  __asm__ __volatile__ (			      \
    "cli		      \n\t"		      \
    "lds %A[res], %[addr]     \n\t"		      \
    "sei		      \n\t"		      \
    "lds %B[res], %[addr] + 1 \n\t"		      \
    : [res]  "=&r" (__result)			      \
    : [addr] "p"   (&(__addr))			      \
    : "memory"					      \
  );						      \
  __result;					      \
}))

#define atomic_write_word_restore(__addr, __data)     \
(__extension__({				      \
  uint8_t  __tmp;				      \
  __asm__ __volatile__ (			      \
    "in	 %[tmp], __SREG__      \n\t"		      \
    "cli		       \n\t"		      \
    "sts %[addr], %A[data]     \n\t"		      \
    "out __SREG__, %[tmp]      \n\t"		      \
    "sts %[addr] + 1, %B[data] \n\t"		      \
    : [tmp]  "=&r" (__tmp)			      \
    : [data] "r"   (__data)			      \
    , [addr] "p"   (&(__addr))			      \
    : "memory"					      \
  );						      \
}))
#endif
