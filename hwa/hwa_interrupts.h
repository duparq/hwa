
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions for interrupts
 */

/**
 * @ingroup hwa_pub
 * @defgroup hwa_classes HWA Classes
 */

/**
 * @ingroup hwa_classes
 * @defgroup hwa_irq Class _irq: Interrupt Request
 *
 * Interrupts are HWA objects of class _irq.
 *
 * @section Interface
 */

/**
 * @ingroup hwa_dev
 * @brief Interrupt object class.
 */
#define hw_class__irq


/*  Return the mask register of an _irq.
 *  Can not use HW_CODR since it's blued.
 */
#define hw__irq_mask			, _hw_irqm
#define _hw_irqm(oo,v,o,m,f)		_hw_irqm1(o,hw_##o,hw_##o##_##m)
#define _hw_irqm1(...)			_hw_irqm2(__VA_ARGS__)
#define _hw_irqm2(o,c,a,rc,...)		HW_OXR(rc,,__VA_ARGS__,c,o,a)

#define hw__irq_flag			, _hw_irqf
#define _hw_irqf(oo,v,o,m,f)		_hw_irqf1(o,hw_##o,hw_##o##_##f)
#define _hw_irqf1(...)			_hw_irqf2(__VA_ARGS__)
#define _hw_irqf2(o,c,a,rc,...)		HW_OXR(rc,,__VA_ARGS__,c,o,a)

#define hw__irq_			, _hw_irq_
#define _hw_irq_(oo,r,v,o,m,f)		_hw_irq1(o,r,hw_##o##_irq_##r)
#define _hw_irq1(...)			_hw_irq2(__VA_ARGS__)
#define _hw_irq2(o,r,...)		HW_BW(_hw_irq2_,_irq,__VA_ARGS__)(o,r,__VA_ARGS__)
#define _hw_irq2_0(o,r,...)		,(o,irq,r),HW_EM_O((o,irq,r))
#define _hw_irq2_1(o,r,ic,iv,...)	ic,(o,irq,r),(iv,__VA_ARGS__)


/**
 * @addtogroup hwa_irq
 * @hideinitializer
 *
 * * implement an Interrupt Service Routine:
 *
 * @code
 * HW_ISR( IRQ [,naked] [,interruptible] )
 * {
 * ...
 * }
 * @endcode
 *
 * This can also be used with assembly language.
 */
#define HW_ISR(...)			_HW_ISR0(__VA_ARGS__,,,)
#define _HW_ISR0(o,...)			_HW_ISR1( HW_X(o), __VA_ARGS__ )
#define _HW_ISR1(...)			_HW_ISR2(__VA_ARGS__)
#define _HW_ISR2(x,...)			HW_BW(_HW_ISR2_,_irq,x)(x, __VA_ARGS__ )
#define _HW_ISR2_0(x,o,...)		_HW_ISR_E(o,__VA_ARGS__)
#define _HW_ISR2_1(c,o,v,p,m,f,x,...)	_HW_B(_HW_ISR3_,_hw_israttr_##x)(v,x,__VA_ARGS__)
#define _HW_ISR3_0(v,...)		_HW_ISR9(v,) HW_EOL(__VA_ARGS__)
#define _HW_ISR3_1(v,x,y,...)		_HW_B(_HW_ISR4_,_hw_israttr_##y)(v,x,y,__VA_ARGS__)
#define _HW_ISR4_0(v,x,...)		_HW_ISR9(v, HW_A1(_hw_israttr_##x)) HW_EOL(__VA_ARGS__)
#define _HW_ISR4_1(v,x,y,...)		_HW_ISR9(v, HW_A1(_hw_israttr_##x) HW_A1(_hw_israttr_##y)) HW_EOL(__VA_ARGS__)
#define _HW_ISR9(...)			_HW_ISR_(__VA_ARGS__)

#if defined __ASSEMBLER__ && !defined _HW_ISR_
#  define _HW_ISR_(vector, ...)		__vector_##vector
#  define _HW_ISR_E(o, ...)		__vector_0 HW_E(HW_EM_OT(o,irq)[_HW_ISR_E(o,__VA_ARGS__)]) 
#endif

#if !defined __ASSEMBLER__
#  define _HW_ISR_E(o, ...)	\
  void _hw_isr_error(void) __attribute__((weak)) HW_E(HW_EM_OT(o,irq)[_HW_ISR_E(o,__VA_ARGS__)])
#endif


/**
 * @addtogroup hwa_irq
 * @hideinitializer
 *
 * @par Enable an IRQ
 *
 * Syntax:
 *
 * @code
 * hw | hwa( enable, IRQ );
 * @endcode
 * 
 * Example:
 * 
 * @code
 * hw( enable, (counter2,irq) );
 * @endcode
 */
#define hw_enable__irq			, _hw_enirq
#define hwa_enable__irq			, _hwa_enirq


/**
 * @addtogroup hwa_irq
 * @hideinitializer
 *
 * @par Disable an IRQ
 *
 * Syntax:
 *
 * @code
 * hw | hwa( disable, IRQ );
 * @endcode
 * 
 * Example:
 * 
 * @code
 * hw( disable, (counter1,capture0,irq) );
 * @endcode
 */
#define hw_disable__irq			, _hw_dsirq
#define hwa_disable__irq		, _hwa_dsirq


/**
 * @addtogroup hwa_irq
 * @hideinitializer
 *
 * @par Read the IRQ flag
 *
 * Syntax:
 *
 * @code
 * hw( read, IRQ );
 * @endcode
 * 
 * Example:
 * 
 * @code
 * hw( read, (adc,irq) );
 * @endcode
 */
#define hw_read__irq			, _hw_rdirq


/**
 * @addtogroup hwa_irq
 * @hideinitializer
 *
 * @par Clear the IRQ flag
 *
 * Syntax:
 *
 * @code
 * hw | hwa( clear, IRQ );
 * @endcode
 * 
 * Example:
 * 
 * @code
 * hw( clear, (counter2,overflow,irq) );
 * @endcode
 */
#define hw_clear__irq			, _hw_clirq
#define hwa_clear__irq			, _hwa_clirq


/**
 * @addtogroup hwa_irq
 * @hideinitializer
 *
 * @par Enable interrupts
 *
 * @code
 * hw( enable, interrupts );
 * @endcode
 */
#define hw_enable_interrupts		, _hw_enirqs


/**
 * @addtogroup hwa_irq
 * @hideinitializer
 *
 * @par Disable interrupts
 *
 * @code
 * hw( disable, interrupts );
 * @endcode
 */
#define hw_disable_interrupts		, _hw_dsirqs
