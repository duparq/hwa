
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	Interrupts
 */
#if 0
// STM32F103 to update
#define _hw_enirq(o,v,n,m,f,...)	_hw_write(n,m,1)  HW_EOL(__VA_ARGS__)
#define _hwa_enirq(o,v,n,m,f,...)	_hwa_write(n,m,1)  HW_EOL(__VA_ARGS__)

#define _hw_dsirq(o,v,n,m,f,...)	_hw_write(n,m,0)  HW_EOL(__VA_ARGS__)
#define _hwa_dsirq(o,v,n,m,f,...)	_hwa_write(n,m,0)  HW_EOL(__VA_ARGS__)

#define _hw_isenirq(o,v,n,m,f,...)	_hw_read(n,m)  HW_EOL(__VA_ARGS__)

#define _hw_rdirq(o,v,n,m,f,...)	_hw_read(n,f)  HW_EOL(__VA_ARGS__)

#define _hw_clirq(o,v,n,m,f,...)	_hw_write(n,f,0)  HW_EOL(__VA_ARGS__)	/* Write 0 to clear */
#define _hwa_clirq(o,v,n,m,f,...)	_hwa_write(n,f,0)  HW_EOL(__VA_ARGS__)	/* Write 0 to clear */
#endif

// Update for STM32F4
//   o is "(object,irq)"
//
#define _hw_enirq(o,mask,flag,clr,...)	_hw_write( HW_A0 o, mask, 1 )  HW_EOL(__VA_ARGS__)
#define _hwa_enirq(o,mask,flag,clr,...)	_hwa_write( HW_A0 o, mask, 1 )  HW_EOL(__VA_ARGS__)

#define _hw_dsirq(o,mask,flag,clr,...)	_hw_write( HW_A0 o, mask, 0 )  HW_EOL(__VA_ARGS__)
#define _hwa_dsirq(o,mask,flag,clr,...)	_hwa_write( HW_A0 o, mask, 0 )  HW_EOL(__VA_ARGS__)

#define _hw_clirq(o,mask,flag,clr,...)	_hw_write( HW_A0 o, flag, clr )  HW_EOL(__VA_ARGS__)
#define _hwa_clirq(o,mask,flag,clr,...)	_hwa_write( HW_A0 o, flag, clr )  HW_EOL(__VA_ARGS__)

/* FIXME: should use (oject,irq,flag) and (oject,irq,mask) */
#define _hw_rdirq(o,mask,flag,clr,...)		_hw_read( HW_A0 o, flag )  HW_EOL(__VA_ARGS__)
#define _hw_isenirq(o,mask,flag,clr,...)	_hw_read( HW_A0 o, mask )  HW_EOL(__VA_ARGS__)


#define _hw_enirqs(o,a,...)		hw_asm("cpsie i") HW_EOL(__VA_ARGS__)
#define _hw_dsirqs(o,a,...)		hw_asm("cpsid i") HW_EOL(__VA_ARGS__)


/**
 * @ingroup stm32
 * @defgroup stm32_evt Faults and events
 *
 * <br><br>hw( enable, faults ) and hw( disable, faults ):
 *
 * @code
 * hw( enable, faults );
 * @endcode
 *
 * @code
 * hw( disable, faults );
 * @endcode
 */
#define hw_enable_			, _hw_enable
#define _hw_enable(...)			HW_E(HW_EM_SL(( hw(enable,faults), hw(enable,interrupts) )))

#define hw_disable_			, _hw_disable
#define _hw_disable(...)		HW_E(HW_EM_SL(( hw(disable,faults), hw(disable,interrupts) )))

#define hw_enable_faults		, _hw_enable_faults
#define _hw_enable_faults(r,...)	, hw_asm("cpsie f") HW_EOL(__VA_ARGS__)

#define hw_disable_faults		, _hw_disable_faults
#define _hw_disable_faults(r,...)	, hw_asm("cpsid f") HW_EOL(__VA_ARGS__)


/**
 * @addtogroup stm32_evt
 * 
 * <br><br>hw( wait, event ):
 *
 * @code
 * hw( wait, event );
 * @endcode
 */
#define hw_wait_event			, _hw_wait_event
#define _hw_wait_event(r,...)		hw_asm("wfe") HW_EOL(__VA_ARGS__)

#define hw_wait_			, _hw_wait
#define _hw_wait(...)			HW_E(HW_EM_SL(( hw(wait,irq), hw(wait,event) )))

#define hw_wait_irq			, _hw_wait_irq
#define _hw_wait_irq(r,...)		hw_asm("wfi") HW_EOL(__VA_ARGS__)


#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  define HW_ISR_ATTRIBUTES __attribute__((used, externally_visible))
#else /* GCC < 4.1 */
#  define HW_ISR_ATTRIBUTES __attribute__((used))
#endif

#define _hw_israttr_naked		, __attribute__((naked))


/*  Single event ISR
 */
#define _HW_ISR_(...)		_HW_ISR__(__VA_ARGS__)
#define _HW_ISR__(v,...)							\
  HW_EXTERN_C void __vector_##v(void) HW_ISR_ATTRIBUTES __VA_ARGS__ ;	\
  void __vector_##v(void)


/*  Void ISR
 */
#define _HW_VISR_(v)							\
  HW_EXTERN_C void __vector_##v(void) __attribute__((naked)) ;		\
  void __vector_##v(void) { hw_asm("reti"); }



#include "../../hwa/hwa_2.h"



#define hw_waste_cycles(n)		_hw_waste_cycles(n)

HW_INLINE void _hw_waste_cycles ( volatile uint32_t n )
{
  hw_asm("	.align			\n"
	 "1:	subs	%[r], %[r], #4	\n"
	 "	bcs.n	1b		\n"
	 : [r] "+r" (n)
	 :
	 );
}


/* This is a generic method, it handles any object.
 * An object supports power management if it has a logical register
 * named `cken`.
 */
#define hw_power			, _hw_power
#define hwa_power			, _hwa_power

#define _hw_power(c,o,...)		HW_B(_hwpwr,HW_G2(_hw_isa_reg, hw_##o##_##cken))(hw,c,o,__VA_ARGS__)
#define _hwa_power(c,o,...)		HW_B(_hwpwr,HW_G2(_hw_isa_reg, hw_##o##_##cken))(hwa,c,o,__VA_ARGS__)

#define _hwpwr0(h,c,o,...)		HW_B(_hwpwr0,h##_actions_##c)(h,c,o)
#define _hwpwr00(h,c,o)			HW_E(HW_EM_OCM(o,c,power)) hw_foo()
#define _hwpwr01(h,c,o)			HW_E(HW_EM_AOCL(power,o,c,HW_A1(h##_actions_##c))) hw_foo()

#define _hwpwr1(h,c,o,a,v,...)		HW_B(_hwpwr1,_hw_state_##v)(h,c,o,v,__VA_ARGS__)
#define _hwpwr1_			_hwpwr10
#define _hwpwr10(h,c,o,v,...)		HW_E(HW_EM_ST(v)) hw_foo()
#define _hwpwr11(h,c,o,v,...)		_##h##_write(o,cken,HW_A1(_hw_state_##v)) HW_EOL(__VA_ARGS__)




HW_INLINE void _hw_write_r16 ( intptr_t ra, uint16_t rwm, uint16_t rfm, uint16_t mask, uint16_t value )
{
#if defined HWA_CHECK_ACCESS
  if ( ra == ~0 )
    HWA_E(HW_EM_X("_hw_write_r16: invalid access"));
#endif

#if !defined HWA_NO_CHECK_USEFUL
  if ( mask == 0 )
    HWA_E(HW_EM_X("_hw_write_r16: no bit to be changed?"));
#endif

#if !defined HWA_NO_CHECK_LIMITS
  if ( value & (~mask) ) {
    HWA_E(HW_EM_X("_hw_write_r16: value overflows mask"));
  }
#endif

  /*  Verify that we do not try to set non-writeable bits
   */
  if ( (value & mask & rwm) != (value & mask) )
    HWA_E(HW_EM_X("_hw_write_r16: bits not writeable."));

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
    HWA_E(HW_EM_X("_hw_write_r32: invalid access"));
#endif

#if !defined HWA_NO_CHECK_USEFUL
  if ( mask == 0 )
    HWA_E(HW_EM_X("_hw_write_r32: no bit to be changed?"));
#endif

#if !defined HWA_NO_CHECK_LIMITS
  if ( value & (~mask) ) {
    HWA_E(HW_EM_X("_hw_write_r32: value overflows mask"));
  }
#endif

  /*  Verify that we do not try to set non-writeable bits
   */
  if ( (value & mask & rwm) != (value & mask) )
    HWA_E(HW_EM_X("_hw_write_r32: bits not writeable."));

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
