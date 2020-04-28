
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions that produce C code specific to STM32 devices
 * @page stm32_general STM32 general instructions
 */

/**
 * @ingroup public_ins_stm32
 * @brief Puts the core in sleep mode.
 */
#define hw_sleep_until_irq__mcu			, _hw_sleep_until_irq__mcu
#define _hw_sleep_until_irq__mcu(...)		hw_asm("wfi")

#define hw_sleep_until_event__mcu		, _hw_sleep_until_event__mcu
#define _hw_sleep_until_event__mcu(...)		hw_asm("wfe")

#define _hw_enirqs(o,a,...)			hw_asm("cpsie i") HW_EOL(__VA_ARGS__)
#define _hw_dsirqs(o,a,...)			hw_asm("cpsid i") HW_EOL(__VA_ARGS__)


/**
 * @ingroup public_ins_stm32
 * @brief Allows program interruption.
 */
#define hw_enable_fault_exceptions__mcu		, _hw_enable_fault_exceptions__mcu
#define _hw_enable_fault_exceptions__mcu(...)	hw_asm("cpsie f")


/**
 * @ingroup public_ins_stm32
 * @brief Prevents program interruption.
 */
#define hw_disable_fault_exceptions__mcu	, _hw_disable_fault_exceptions__mcu
#define _hw_disable_fault_exceptions__mcu(...)	hw_asm("cpsid f")


/**
 * @ingroup public_ins_stm32
 * @brief Software loop of \c n system clock cycles.
 */
#define hw_waste_cycles(n)			_hw_waste_cycles(n)


/*	ISR
 */
#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  define HW_ISR_ATTRIBUTES __attribute__((used, externally_visible))
#else /* GCC < 4.1 */
#  define HW_ISR_ATTRIBUTES __attribute__((used))
#endif


/*  IRQ flag is cleared writing 0 into it.
 */
#define hw_clear__irq			, _hw_clrirq
#define _hw_clrirq(o,r,v,m,f,...)	_hw_write(o,f,0)


#include "../../hwa/hwa_2.h"


HW_INLINE void _hw_waste_cycles ( volatile uint32_t n )
{
  hw_asm("	.align			\n"
	 "1:	subs	%[r], %[r], #4	\n"
	 "	bcs.n	1b		\n"
	 : [r] "+r" (n)
	 :
	 );
}


/* This is a generic method that can be implemented by all peripheral
 * classes. An object supports power management if it has a logical register
 * named `cken`.
 */
#define hw_power			, _hw_power
#define hwa_power			, _hwa_power

#define _hw_power(c,o,a,v,g,...)	HW_Y(_hwx_pwr1_,g)(_hw,o,v,g)
#define _hwa_power(c,o,a,v,g,...)	HW_Y(_hwx_pwr1_,g)(_hwa,o,v,g)
#define _hwx_pwr1_0(h,o,v,g)		HW_E_G(g)
#define _hwx_pwr1_1(h,o,v,g)		HW_Y(_hwx_pwr2_,_hw_state_##v)(h,o,v)
#define _hwx_pwr2_0(h,o,v)		HW_E_ST(v)
#define _hwx_pwr2_1(h,o,v)		HW_Y(_hwx_pwr3_,HW_G2(_hw_isa_reg, hw_##o##_##cken))(h,o,v)
#define _hwx_pwr3_0(h,o,v)		HW_E(`o` does not support power management)
#define _hwx_pwr3_1(h,o,v)		h##_write(o,cken,HW_A1(_hw_state_##v))


HW_INLINE void _hw_write_r16 ( intptr_t ra, uint16_t rwm, uint16_t rfm, uint16_t mask, uint16_t value )
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

  volatile uint16_t *p = (volatile uint16_t *)ra ;

  /*  TODO: bit set/reset
   */
  uint16_t rm = rwm & ~mask & ~rfm ;

  if ( rm == 0 )
    /*
     *  Nothing to be read, just write the new value
     */
    *p = value ;
  else {
    /*
     *  Read-modify-write
     */
    uint16_t sm = mask & rwm & value ;	/* what has to be set	  */
    uint16_t cm = mask & rwm & (~value) ;	/* what has to be cleared */
    *p = (*p & ~cm) | sm ;
  }
}


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

  /*  TODO: bit set/reset
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
    uint32_t sm = mask & rwm & value ;	/* what has to be set	  */
    uint32_t cm = mask & rwm & (~value) ;	/* what has to be cleared */
    *p = (*p & ~cm) | sm ;
  }
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
    uint16_t rm = ~r->mmask & ~rfm & ~r->omask & rwm ;

    if ( rm )
      r->ovalue = *p ;

    r->ovalue = ((r->ovalue & ~wm) | (r->mvalue & wm)) & ~rfm ;

    *p = r->ovalue | (rfm & r->mmask & r->mvalue) ;
  }

  r->omask |= r->mmask ;
  r->mmask = 0 ;
}


HW_INLINE void _hwa_commit__r32 ( hwa_r32_t *r, uint32_t rwm, uint32_t rfm, _Bool commit )
{
  if ( !commit ) {
    r->ovalue = (r->ovalue & r->omask & ~r->mmask) | (r->mvalue & r->mmask) ;
    r->omask |= r->mmask ;
    r->mmask = 0 ;
    return ;
  }

  volatile uint32_t *p = (volatile uint32_t *)r->a ;

  uint32_t wm = rwm & r->mmask & ((r->ovalue ^ r->mvalue) | ~r->omask);

  if ( wm ) {
    uint32_t rm = ~r->mmask & ~rfm & ~r->omask & rwm ;

    if ( rm )
      r->ovalue = *p ;

    r->ovalue = ((r->ovalue & ~wm) | (r->mvalue & wm)) & ~rfm ;

    *p = r->ovalue | (rfm & r->mmask & r->mvalue) ;
  }

  r->omask |= r->mmask ;
  r->mmask = 0 ;
}


HW_INLINE uint32_t _hw_read__r16 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  uint32_t m = (1UL<<rbn)-1 ;
  volatile uint16_t *p = (volatile uint16_t *)ra ;
  return ((*p)>>rbp) & m ;
}


HW_INLINE uint32_t _hw_read__r32 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  uint32_t m = (1UL<<rbn)-1 ;
  volatile uint32_t *p = (volatile uint32_t *)ra ;
  return ((*p)>>rbp) & m ;
}
