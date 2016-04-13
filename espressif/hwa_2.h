
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions that produce C code specific to Atmel AVR devices
 */

#include "../hwa/hwa_2.h"

/**
 * @ingroup public_gen_instructions_atmelavr
 * @brief Insert inline assembler code
 * @hideinitializer
 *
 * Syntax: `hw_asm("reti");  // Insert the RETI instruction`
 */
#define hw_asm(...)			__asm__ __volatile__(__VA_ARGS__)

/**
 * @ingroup public_gen_instructions_atmelavr
 * @brief Return from a naked interrupt service routine.
 * @hideinitializer
 */
#define hw_reti()			HW_ERR("not implemented")

/**
 * @ingroup public_gen_instructions_atmelavr
 * @brief Put the core in sleep mode.
 */
#define hw_sleep()			HW_ERR("not implemented")

/**
 * @ingroup public_gen_instructions_atmelavr
 * @brief Allow program interruption.
 */
#define hw_enable_interrupts()		HW_ERR("not implemented")

/**
 * @ingroup public_gen_instructions_atmelavr
 * @brief Prevent program interruption.
 */
#define hw_disable_interrupts()		HW_ERR("not implemented")

/**
 * @ingroup public_gen_instructions_atmelavr
 * @brief Software loop of \c n system clock cycles.
 *
 * Only works with compile time constants.
 */
#define hw_waste_cycles(n)		HW_ERR("not implemented")


/**
 * @ingroup public_gen_instructions_atmelavr
 * @brief Execute a block with interrupts disabled
 * @hideinitializer
 */
#define HW_ATOMIC(...)			HW_ERR("not implemented")

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
HW_INLINE void _hw_write__r8_m ( intptr_t ra, uint8_t rwm, uint8_t rfm,
				 uint8_t mask, uint8_t value )
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
  //  if ( (value & mask) != value ) {
  if ( value & (~mask) ) {
    /* hw_asm("wdr"); */
    /* *(volatile uint8_t*)0 = value ; */
    /* *(volatile uint8_t*)0 = mask ; */
    /* *(volatile uint8_t*)0 = value & mask ; */
    /* hw_asm("wdr"); */
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
     *  Just 1 bit to be written at C address < 0x40 (ASM address < 0x20): use
     *  sbi/cbi
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
      uint8_t sm = mask & rwm & value ;     /* what has to be set     */
      uint8_t cm = mask & rwm & (~value) ;  /* what has to be cleared */
      *p = (*p & ~cm) | sm ;
    }
  }
}


HW_INLINE void _hw_write__r8 ( intptr_t ra, uint8_t rwm, uint8_t rfm,
			       uint8_t bn, uint8_t bp, uint8_t value )
{
  _hw_write__r8_m( ra, rwm, rfm, ((1U<<bn)-1)<<bp, value<<bp );
}


/**
 * @ingroup private
 * @brief  Write one 8-bit hardware register.
 */
/* TODO: Atmel AVR8 does not have 16 bit access instructions. Could check
 *	sbi/cbi for 2 different bytes
 */
HW_INLINE void _hw_write__r16 ( intptr_t ra, uint16_t rwm, uint16_t rfm,
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
     *  FIXME: could put a signal here to see if that code is usefull.
     */
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
HW_INLINE void _hw_write__r32_m ( intptr_t ra, uint32_t rwm, uint32_t rfm,
				  uint32_t mask, uint32_t value )
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
  //  if ( (value & mask) != value ) {
  if ( value & (~mask) ) {
    /* hw_asm("wdr"); */
    /* *(volatile uint32_t*)0 = value ; */
    /* *(volatile uint32_t*)0 = mask ; */
    /* *(volatile uint32_t*)0 = value & mask ; */
    /* hw_asm("wdr"); */
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
     *  Nothing to be read, just write the new value
     */
    *p = value ;
  else {
    /*
     *  Read-modify-write
     */
    uint32_t cm = mask & rwm ;  /* what has to be cleared */
    uint32_t sm = value ;     /* what has to be set     */
    *p = (*p & ~cm) | sm ;
  }
}


HW_INLINE void _hw_write__r32 ( intptr_t ra, uint32_t rwm, uint32_t rfm,
				uint8_t bn, uint8_t bp, uint32_t value )
{
  _hw_write__r32_m( ra, rwm, rfm, ((1ULL<<bn)-1)<<bp, value<<bp );
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
   *    =     bits that are writeable (rwm)
   *      AND that has been written (mmask)
   *      AND that really need to be modified (ovalue != mvalue)
   */
  uint32_t wm = rwm & r->mmask & ((r->ovalue ^ r->mvalue) | ~r->omask);

  if ( wm ) {
    /*	Mask of bits to be read
     *	  =     bits that are not to be modified (mmask)
     *      AND not flags (rfm)
     *      AND that are not known (omask)
     *      AND that are writeable (rwm)
     */
    uint32_t rm = ~r->mmask & ~rfm & ~r->omask & rwm ;

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

/*  Clear IRQ
 */
#define _hw_clear_irq(v,o,e,f,c, ... )	HW_TX(_hw_write_reg(o,c, 1 ), __VA_ARGS__)
#define _hwa_clear_irq(v,o,e,f,c, ... )	HW_TX(_hwa_write_reg(o,c, 1 ), __VA_ARGS__)


#define _hw_turn_irqa_1(o,e,v, ...)				\
  HW_TX(_hw_write_reg(o,e, HW_A1(_hw_state_##v)), __VA_ARGS__)

#define _hwa_turn_irqa_1(o,e,v, ...)				\
  HW_TX(_hwa_write_reg(o,e, HW_A1(_hw_state_##v)), __VA_ARGS__)

#define _hw_turn_irqb(n,v, ...)		HW_G2(_hw_turn_irqb, HW_A1(_hw_state_##v))(n)
#define _hw_turn_irqb_0(n)		ets_isr_mask(1<<n)
#define _hw_turn_irqb_1(n)		ets_isr_unmask(1<<n)

/* #define _hwa_turn_irqb(n,v, ...)	HW_G2(_hwa_turn_irqb, HW_A1(_hw_state_##v))(n) */
/* #define _hwa_turn_irqb_0(n)		ets_isr_mask(1<<n) */
/* #define _hwa_turn_irqb_1(n)		ets_isr_unmask(1<<n) */
