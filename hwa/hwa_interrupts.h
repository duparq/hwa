
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
#ifndef hw__irq_mask
#define hw__irq_mask			, _hw_irqm
#define _hw_irqm(oo,v,o,m,f)		_hw_irqm1(o,hw_##o,hw_##o##_##m)
#define _hw_irqm1(...)			_hw_irqm2(__VA_ARGS__)
#define _hw_irqm2(o,c,a,rc,...)		HW_OXR(rc,,__VA_ARGS__,c,o,a)
#endif

#ifndef hw__irq_flag
#define hw__irq_flag			, _hw_irqf
#define _hw_irqf(oo,v,o,m,f)		_hw_irqf1(o,hw_##o,hw_##o##_##f)
#define _hw_irqf1(...)			_hw_irqf2(__VA_ARGS__)
#define _hw_irqf2(o,c,a,rc,...)		HW_OXR(rc,,__VA_ARGS__,c,o,a)
#endif

#define hw__irq_			, _hw_irq_
#define _hw_irq_(oo,r,v,o,m,f)		_hw_irq1(o,r,hw_##o##_irq_##r)
#define _hw_irq1(...)			_hw_irq2(__VA_ARGS__)
#define _hw_irq2(o,r,...)		HW_BW(_hw_irq2_,_irq,__VA_ARGS__)(o,r,__VA_ARGS__)
#define _hw_irq2_0(o,r,...)		,(o,irq,r),HW_EM_O((o,irq,r))
#define _hw_irq2_1(o,r,ic,iv,...)	ic,(o,irq,r),(iv,__VA_ARGS__)


/**
 * @addtogroup hwa_irq
 *
 * @act HW_ISR( IRQ [,naked] [,interruptible] ): implement an Interrupt Service
 * Routine. This can be used with assembly language.
 *
 * @arg naked (optionnal): the compiler must not generate entry/exit code.
 * @arg interruptible (optionnal): the compiler enables interrupts as soon as possible.
 *
 * @act HW_ISR( IRQ2, alias, IRQ1 ): make IRQ1 ISR handle IRQ2.
 */
/**
 * @ingroup hwa_dev
 * @hideinitializer
 *
 * Declare an ISR.
 */
/*  FIXME: this code has to be rewritten.
 *    AVR use '(object,irq)' as argument for HW_ISR().
 *    STM32 use 'object[,reason]' and looks for a _hw_isr_object[_reason] declaration (-> _HW_ISR20)
 */
#ifndef HW_ISR
#define HW_ISR(...)			_HW_ISR0(__VA_ARGS__,,,)
#define _HW_ISR0(o,...)			_HW_ISR1( HW_C3(HW_X(o)), __VA_ARGS__ )
#define _HW_ISR1(...)			_HW_ISR2(__VA_ARGS__)

#define _HW_ISR2(c,...)			HW_BW(_HW_ISR2,_irq,c)(c, __VA_ARGS__ )
//#define _HW_ISR20(x,o,...)		_HW_ISR_E(o,__VA_ARGS__)

//#define _HW_ISR21(c,o,v,p,m,f,x,...)	HW_BW(_HW_ISR5,alias,x)(v,x,__VA_ARGS__)
#define _HW_ISR21(c,o,d,...)		_HW_ISR22( HW_A0 d, __VA_ARGS__ )
#define _HW_ISR22(...)			_HW_ISR23(__VA_ARGS__)
#define _HW_ISR23(v,x,...)		HW_BW(_HW_ISR5,alias,x)(v,x,__VA_ARGS__)

#define _HW_ISR51(v,x,o,...)		_HW_ISR52(v, HW_X(o), __VA_ARGS__ )
#define _HW_ISR52(...)			_HW_ISR53(__VA_ARGS__)
#define _HW_ISR53(v,x,...)		HW_BW(_HW_ISR6,_irq,x)(v,x, __VA_ARGS__ )
#define _HW_ISR60(v,x,o,...)		_HW_ISR_E(o,__VA_ARGS__)
#define _HW_ISR61(v1,c,o,v2,p,m,f,x,...)	_HW_ISR_ALIAS(v1,v2) HW_EOL(__VA_ARGS__)

#define _HW_ISR50(v,x,...)		_HW_B(_HW_ISR7,_hw_israttr_##x)(v,x,__VA_ARGS__)
#define _HW_ISR70(v,...)		_HW_ISR9(v,) HW_EOL(__VA_ARGS__)
#define _HW_ISR71(v,x,y,...)		_HW_B(_HW_ISR8,_hw_israttr_##y)(v,x,y,__VA_ARGS__)
#define _HW_ISR80(v,x,...)		_HW_ISR9(v, HW_A1(_hw_israttr_##x)) HW_EOL(__VA_ARGS__)
#define _HW_ISR81(v,x,y,...)		_HW_ISR9(v, HW_A1(_hw_israttr_##x) HW_A1(_hw_israttr_##y)) HW_EOL(__VA_ARGS__)
#define _HW_ISR9(...)			_HW_ISR_(__VA_ARGS__)

#if defined __ASSEMBLER__ && !defined _HW_ISR_
#  define _HW_ISR_(vector, ...)		__vector_##vector
#  define _HW_ISR_E(o, ...)		__vector_0 HW_E(HW_EM_OT(o,irq)[_HW_ISR_E(o,__VA_ARGS__)]) 
#endif

#if !defined __ASSEMBLER__
#  define _HW_ISR_E(o, ...)	\
  void _hw_isr_error(void) __attribute__((weak)) HW_E(HW_EM_OT(o,irq)[_HW_ISR_E(o,__VA_ARGS__)])
#endif

/*  Handle _hw_isr_ declarations
 */
#define _HW_ISR20(c,...)	HW_B(_HW_ISRX1,c)(c,__VA_ARGS__)
#define _HW_ISRX11(z,o,e,...)	HW_E(e) void HW_G2(hw,__COUNTER__)()

/*  Reason?
 */
#define _HW_ISRX10(c,o,d,x,...)	HW_B(_HW_ISRX3,_hw_isr_##o##_##x)(o,x,__VA_ARGS__)
#define _HW_ISRX31(o,x,...)	_HW_ISRX30(o##_##x,__VA_ARGS__)

/*  Alias?
 */
#define _HW_ISRX30(o1,x,...)	HW_BW(_HW_ISRX5,alias,x)(o1,x,__VA_ARGS__)
#define _HW_ISRX51(o1,x,y,...)	_HW_ISRX52(o1,HW_C3(HW_X(y)), __VA_ARGS__ )
#define _HW_ISRX52(o1,x,...)	HW_B(_HW_ISRX52,x)(o1,x,__VA_ARGS__)
#define _HW_ISRX521(o1,z,o,e,...)	HW_E(e) void HW_G2(hw,__COUNTER__)()
#define _HW_ISRX520(o1,c,o2,d,x,...)	HW_B(_HW_ISRX53,x)(o1,o2,x,__VA_ARGS__)
#define _HW_ISRX531(o1,o2,...)	_HW_ISRX_ALIAS(HW_A1(_hw_isr_##o1),HW_A1(_hw_isr_##o2)) HW_EOL(__VA_ARGS__)

/*  	Reason?
 */
#define _HW_ISRX530(o1,o2,x,...)	HW_B(_HW_ISRX54,_hw_isr_##o2##_##x)(o1,o2,x,__VA_ARGS__)
#define _HW_ISRX541(o1,o2,x,...)	_HW_ISRX_ALIAS(HW_A1(_hw_isr_##o1),HW_A1(_hw_isr_##o2##_##x)) HW_EOL(__VA_ARGS__)
#define _HW_ISRX540(o1,o2,...)	_HW_ISRX_ALIAS(HW_A1(_hw_isr_##o1),HW_A1(_hw_isr_##o2)) HW_EOL(__VA_ARGS__)
  
#define _HW_ISRX50(o,...)	HW_B(_HW_ISRX50,_hw_isr_##o)(o,__VA_ARGS__)
#define _HW_ISRX500(o,...)	HW_E(HW_EM_OT(o,isr))
#define _HW_ISRX501(...)		_HW_ISRX9(__VA_ARGS__)

#define _HW_ISRX9(o,...)		_HW_ISRXX(HW_A1(_hw_isr_##o),__VA_ARGS__)


#define _HW_ISRXX(...)		_HW_ISRXX1(__VA_ARGS__)
#define _HW_ISRXX1(v,...)	\
  HW_EXTERN_C void __vector_##v(void) HW_ISR_ATTRIBUTES		\
    HW_B(_HW_ISRXX2,__VA_ARGS__)(__VA_ARGS__);			\
    void __vector_##v(void)
#define _HW_ISRXX20(x,...)	__attribute((x)) HW_B(_HW_ISRXX3,__VA_ARGS__)(__VA_ARGS__)
#define _HW_ISRXX30(x,...)	__attribute((x)) HW_B(_HW_ISRXX3,__VA_ARGS__)(__VA_ARGS__)
#define _HW_ISRXX21(...)
#define _HW_ISRXX31(...)
#endif // ifndef HW_ISR


/**
 * @addtogroup hwa_irq
 * @hideinitializer
 *
 * @act hw( enable, IRQ ) and hwa( enable, IRQ ): enable an IRQ
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
 * @act hw( disable, IRQ ) and hwa( disable, IRQ ): disable an IRQ
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
 * @act hw( is_enabled, IRQ ): verify if an IRQ is enabled.
 * 
 * @code
 * if ( hw( is_enabled, (counter1,capture0,irq) ) ) {
 *   // IRQ is enabled
 * }
 * @endcode
 */
#define hw_is_enabled__irq		, _hw_isenirq


/**
 * @addtogroup hwa_irq
 * @hideinitializer
 *
 * @act hw( read, IRQ ): read the IRQ flag
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
 * @act hw( clear, IRQ ) and hwa( clear, IRQ ): clear the IRQ flag
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
 * @act hw( enable, interrupts ): enable interrupts
 * 
 * Example:
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
 * @act hw( disable, interrupts ): disable interrupts
 * 
 * Example:
 *
 * @code
 * hw( disable, interrupts );
 * @endcode
 */
#define hw_disable_interrupts		, _hw_dsirqs
