
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Interrupts
 *
 * This file contains all that is relative to interrupts.
 */

/**
 * @ingroup public_irq_instructions
 * @brief Definition of an IRQ.
 *
 * `HW_IRQ( object [, irq_name] )`
 *
 * @hideinitializer
 */
#define _hw_class__irq
#define _hw_is__irq__irq	, 1

#define HW_IRQ(...)		_HW_IRQ2(__VA_ARGS__,,)
#define _HW_IRQ2(o,x,...)	HW_G2(_HW_IRQ3,HW_IS(_irq,_hw_irq_##o##_##x))(o,x,__VA_ARGS__)
#define _HW_IRQ3_1(o,x,...)	_hw_irq_##o##_##x
#define _HW_IRQ3_0(o,...)	HW_G2(_HW_IRQ5,HW_ISON(o))(o,__VA_ARGS__)
#define _HW_IRQ5_0(o,...)	HW_E_O(o)
#define _HW_IRQ5_1(o,x,...)	HW_E(`o` has no IRQ named `x`.)


/**
 * @brief Definition of the enable bit of an IRQ
 *
 * Syntax 1: `hw_irqe( object [, irq_name] )`
 *
 * Syntax 2: `hw_irqe( irq(object [, irq_name]) )`
 * @hideinitializer
 */
#define HW_IRQMASK(...)		_HW_IRQM2(HW_IRQ(__VA_ARGS__))
#define _HW_IRQM2(...)		HW_G2(_HW_IRQM,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _HW_IRQM_0(...)		__VA_ARGS__
#define _HW_IRQM_1(t,o,v,e,f)	_HW_REG(o,e)


/**
 * @brief Definition of the flag bit of an IRQ
 *
 * Syntax 1: `hw_irqf( object [, irq_name] )`
 *
 * Syntax 2: `hw_irqf( irq(object [, irq_name]) )`
 * @hideinitializer
 */
#define HW_IRQFLAG(...)		_HW_IRQF2(HW_IRQ(__VA_ARGS__))
#define _HW_IRQF2(...)		HW_G2(_HW_IRQF,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _HW_IRQF_1(c,o,v,e,f)	_HW_REG(o,f)
#define _HW_IRQF_0(...)		__VA_ARGS__


/**
 * @ingroup public_irq_instructions
 * @brief Declaration of an ISR
 *
 * The `HW_ISR(...)` instruction accepts 2 optionnal arguments after the
 * designation of the IRQ:
 *
 * @li `isr_naked`: ask the compiler to not initialize any register. You have to
 *   put the `reti` instruction yourself.
 * @li `isr_interruptible`: ask the compiler to enable the interrupts as soon as
 *   possible.
 * @li `isr_non_interruptible`: can be use to assert that the interrupts are not
 *   enabled.
 *
 * @code
 * HW_ISR( object [, reason] [, isr_naked ] [, isr_interruptible | isr_non_interruptible] )
 * {
 *    ... // Service the ISR
 *
 *    [ hw_reti(); ]
 * }
 * @endcode
 * @hideinitializer
 */

/*  The IRQ object/reason arguments may be followed by other arguments. So, we
 *  do not use HW_IRQ().
 */
/*  Is x '_irq' ?
 */
#define HW_ISR(...)		HW_G2(_HW_ISR1,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__,,)
#define _HW_ISR1_1(...)		_HW_ISR2(__VA_ARGS__)

/*  Is _hw_irq_##o##_##x an irq?
 */
#define _HW_ISR1_0(o,x,...)	HW_G2(_HW_ISR1_3,HW_IS(_irq,_hw_irq_##o##_##x))(o,x,__VA_ARGS__)
#define _HW_ISR1_3_1(o,x,...)	_HW_ISR2(_hw_irq_##o##_##x,__VA_ARGS__)

/*  Is _hw_irq_##o##_ an irq?
 */
#define _HW_ISR1_3_0(o,...)	HW_G2(_HW_ISR1_4,HW_IS(_irq,_hw_irq_##o##_))(o,__VA_ARGS__)
#define _HW_ISR1_4_1(o,...)	_HW_ISR2(_hw_irq_##o##_, __VA_ARGS__)

/*  There is an error
 */
#define _HW_ISR1_4_0(o,...)	HW_G2(_HW_ISR1_5,HW_ISON(o))(o,__VA_ARGS__)
#define _HW_ISR1_5_1(o,...)	HW_E(`o` has no IRQ named `` or `HW_QUOTE(__VA_ARGS__)`.) _HW_ISR_X_
#define _HW_ISR1_5_0(o,...)	HW_PE(o,HW_E_O(o)) void hw_isr_error_##o()

/*  The definition of the IRQ is expanded, process the remaining arguments if any
 */
#define _HW_ISR2(...)		_HW_ISR3(__VA_ARGS__)
#define _HW_ISR3(i,o,v,e,f,...)	HW_G2(_HW_ISR4,HW_IS(,__VA_ARGS__))(v,__VA_ARGS__)
#define _HW_ISR4_1(v,...)	HW_TX(_HW_ISR_(v,),__VA_ARGS__)
#define _HW_ISR4_0(v,x,...)	HW_G2(_HW_ISR5, HW_IS(,_hw_israttr_##x))(v,x,__VA_ARGS__)
#define _HW_ISR5_0(v,x,...)	HW_E(object has no IRQ named `x`) void hw_isr_error_##x()
#define _HW_ISR5_1(v,a1,...)	HW_G2(_HW_ISR6,HW_IS(,__VA_ARGS__))(v,a1,__VA_ARGS__)
#define _HW_ISR6_1(v,a1,...)	_HW_ISR_(v,HW_A1(_hw_israttr_##a1))
#define _HW_ISR6_0(v,a1,x,...)	HW_G2(_HW_ISR7, HW_IS(,_hw_israttr_##x))(v,a1,x,__VA_ARGS__)
#define _HW_ISR7_0(v,a1,x,...)	HW_E_T(x) void hw_isr_error_##x()
#define _HW_ISR7_1(v,a1,a2,...)	HW_G2(_HW_ISR8,HW_IS(,__VA_ARGS__))(v,a1,a2,__VA_ARGS__,)
#define _HW_ISR8_1(v,a1,a2,...)	_HW_ISR_(v, HW_A1(_hw_israttr_##a1) HW_A1(_hw_israttr_##a2))
#define _HW_ISR8_0(v,a1,a2,x,...)	HW_E_T(x) void hw_isr_error_##x()


/*  Definition of an interrupt. Extra arguments are allowed and returned unchanged.
 *  Only used by HW_ISR().
 *
 *    HW_IRQX(counter0)
 *    HW_IRQX(hw_counter0,compare)
 *    HW_IRQX(hw_counter0,compare,isr_naked,...)
 */
//#define HW_ISR1_(...)		_HW_ISR1_1(__VA_ARGS__,,)


#if !defined __ASSEMBLER__

#define _hw_mthd_hw_turn__irq		, _hw_turn_irq

/**
 * @ingroup private
 * @brief  Turn an IRQ on/off
 * @hideinitializer
 */
#define _hw_turn_irq(o,v,e,f, ...)					\
  HW_G2(_hw_turn_irq_vstate, HW_IS(,_hw_state_##__VA_ARGS__))(o,e, __VA_ARGS__,)
#define _hw_turn_irq_vstate_0(o,e,x, ...)	HW_E_ST(x)
#define _hw_turn_irq_vstate_1(o,e,v, ...)			\
  HW_TX(_hw_write_reg(o,e, HW_A1(_hw_state_##v)), __VA_ARGS__)


#define _hw_mthd_hwa_turn__irq		, _hwa_turn_irq

/**
 * @ingroup private
 * @brief  Turn an IRQ on/off
 * @hideinitializer
 */
#define _hwa_turn_irq(o,v,e,f, ...)					\
  HW_G2(_hwa_turn_irq_vstate, HW_IS(,_hw_state_##__VA_ARGS__))(o,e, __VA_ARGS__,)
#define _hwa_turn_irq_vstate_0(o,e,x, ...)	HW_E_ST(x)
#define _hwa_turn_irq_vstate_1(o,e,v, ...)			\
  HW_TX(_hwa_write_reg(o,e, HW_A1(_hw_state_##v)), __VA_ARGS__)


/**
 * @ingroup private
 * @brief  Clear an IRQ flag
 * @hideinitializer
 */
#define _hw_clear_irq(v,p,e,f, ... )	HW_TX(_hw_write_reg(p,f, 1 ), __VA_ARGS__)
#define _hw_mthd_hw_clear__irq		, _hw_clear_irq


/**
 * @ingroup private
 * @brief  Clear irq flag
 * @hideinitializer
 */
#define _hwa_clear_irq(v,p,e,f, ... )	HW_TX(_hwa_write_reg(p,f, 1 ), __VA_ARGS__)
#define _hw_mthd_hwa_clear__irq		, _hwa_clear_irq


#endif /* !defined __ASSEMBLER__ */
