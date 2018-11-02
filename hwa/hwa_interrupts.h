
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


#define _hw_class__irq


/**
 * @ingroup public_ins_obj
 * @brief Returns the definition the @ref using_objects "object"'s IRQ "...".
 *
 * The first argument must be an object name and it may be followed by an
 * interrupt name.
 *
 * For example, for many counters, `HW_IRQ(counter0)` and
 * `HW_IRQ(counter0,overflow)` are equivalent.
 *
 * @code
 * hw( turn, HW_IRQ(counter0,overflow), on );	// Enables overflow IRQ for counter0
 * @endcode
 *
 * @hideinitializer
 */
/*  HW_IRQ() uses its own copy of HW_OD so that 'hwa( turn, irq(COUNTER), on );'
    does not fail as hwa() already uses HW_OD to expand the object.
 */
#define HW_IRQ(...)		_HW_IRQ1(__VA_ARGS__,,)
#define _HW_IRQ1(o,...)		_HW_IRQ2(HW_aO(o),__VA_ARGS__)
#define _HW_IRQ2(...)		_HW_IRQ3(__VA_ARGS__)
#define _HW_IRQ3(c,...)		HW_Y(_HW_IRQ3,c)(c,__VA_ARGS__)
#define _HW_IRQ3_0(c,o,i,a,x,...)	HW_G2(_HW_IRQ4,HW_IS(_irq,_hw_irq_##o##_##x))(o,x,__VA_ARGS__)
#define _HW_IRQ3_1(...)
#define _HW_IRQ4_1(o,x,...)	_hw_irq_##o##_##x
#define _HW_IRQ4_0(o,x,...)	HW_E(`o` has no IRQ named `x`.)


/*  Copy of HW_OD()
 */
#define HW_aO(object)		_HW_aO1(object)

#define _HW_aO1(...)		HW_Y(_HW_aO1,_hw_isa_leftbkt __VA_ARGS__)(__VA_ARGS__)
#define _HW_aO1_0(...)		HW_Y(_HW_aO2,_hw_class_##__VA_ARGS__)(__VA_ARGS__)
#define _HW_aO1_1(...)		_HW_aO1_2 __VA_ARGS__
#define _HW_aO1_2(...)		_HW_aO7(HW_RLX(__VA_ARGS__))

#define _HW_aO2_1(...)		__VA_ARGS__		/*  Class name found, job's done. */
#define _HW_aO2_0(o)		_HW_aO3(o,_hw_def_##o)	/*  Is o an object's name? */
#define _HW_aO3(...)		_HW_aO4(__VA_ARGS__)
#define _HW_aO4(o,...)		HW_Y(_HW_aO4,_hw_class_##__VA_ARGS__)(o,__VA_ARGS__)
#define _HW_aO4_1(o,c,...)	c,o,__VA_ARGS__
#define _HW_aO4_0(o,...)		HW_Y(_HW_aO5,o)(o)	/*  o is not an object, produce an error. */
#define _HW_aO5_1(o)		HW_E_OM()

#define _HW_aO5_0(o)		_HW_aO5_2(o,_hw_o_##o)
#define _HW_aO5_2(...)		_HW_aO5_3(__VA_ARGS__)
#define _HW_aO5_3(o,x,...)	HW_Y(_HW_aO6,x)(x,__VA_ARGS__)
#define _HW_aO6_0(o,...)		HW_E_O(o)		/* o is not recognized as an object */
#define _HW_aO6_1(x,...)		__VA_ARGS__

#define _HW_aO7(o)		_HW_aO8(o)
#define _HW_aO8(o)		HW_Y(_HW_aO8,o)(o)
#define _HW_aO8_1(o)		/* HW_RELATIVE() has emitted an error */
#define _HW_aO8_0(o)		_HW_aO8_2(o,_hw_def_##o)
#define _HW_aO8_2(...)		_HW_aO4_1(__VA_ARGS__)

#define _HW_aO11(...)		_HW_aO12(__VA_ARGS__)
#define _HW_aO12(o,r,...)	HW_Y(_HW_aO12,_hw_class_##__VA_ARGS__)(o,r,__VA_ARGS__)
#define _HW_aO12_0(o,...)	HW_E_O(o)
#define _HW_aO12_1(o,r,c,i,a)	_HW_aO13(_hw_reg_##c##_##r,o,c,a,r)
#define _HW_aO13(...)		_HW_aO14(__VA_ARGS__)
#define _HW_aO14(t,...)		HW_Y(_HW_aO14,_hw_isa_reg_##t)(t,__VA_ARGS__)
#define _HW_aO14_1(t,...)	_hw_r2m_##t(__VA_ARGS__)
#define _HW_aO14_0(t,o,c,a,r)	_HW_aO15(_hw_reg_##o##_##r,o,c,a,r)
#define _HW_aO15(...)		_HW_aO16(__VA_ARGS__)
#define _HW_aO16(t,...)		HW_Y(_HW_aO16,_hw_isa_reg_##t)(t,__VA_ARGS__)
#define _HW_aO16_1(t,...)	_hw_r2m_##t(__VA_ARGS__)
#define _HW_aO16_0(t,o,c,a,r)	HW_E(`o` has no register `r`)


/**
 * @ingroup public_ins_obj
 * @brief Returns the definition of the mask bit of @ref using_objects "object"'s IRQ "...".
 * @hideinitializer
 */
#if defined DOXYGEN
#  define HW_IRQMASK(object, ...)
#else
#  define HW_IRQMASK(...)	_HW_IRQM2(HW_IRQ(__VA_ARGS__))
#endif
#define _HW_IRQM2(...)		HW_G2(_HW_IRQM,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _HW_IRQM_0(...)		__VA_ARGS__
#define _HW_IRQM_1(t,o,v,e,f)	_HW_M(o,e)


/**
 * @ingroup public_ins_obj
 * @brief Returns the definition of the flag bit of @ref using_objects "object"'s IRQ "...".
 * @hideinitializer
 *
 * @code
 * hw( read, HW_IRQFLAG(counter0,overflow) );
 * @endcode
 *
 * @code
 * hw( clear, HW_IRQFLAG(counter0) );
 * @endcode
 *
 */
#if defined DOXYGEN
#  define HW_IRQFLAG(object, ...)
#else
#  define HW_IRQFLAG(...)	_HW_IRQF2(HW_IRQ(__VA_ARGS__))
#endif
#define _HW_IRQF2(...)		HW_G2(_HW_IRQF,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _HW_IRQF_1(c,o,v,e,f)	_HW_M(o,f)
#define _HW_IRQF_0(...)		__VA_ARGS__


/**
 * @ingroup public_ins_obj
 * @brief Declares the ISR for @ref using_objects "object"'s IRQ "...".
 *
 * The `HW_ISR(...)` instruction accepts 2 optionnal arguments after the
 * designation of the IRQ:
 *
 * @li `naked`: ask the compiler to not initialize any register. You have to
 *   put the `reti` instruction yourself.
 *
 * @li `interruptible` or `non_interruptible`: ask the compiler to
 * enable/disable the interrupts as soon as possible.
 *
 * @code
 * HW_ISR( object [, reason] [, naked ] [, interruptible | non_interruptible] )
 * {
 *    ... // Service the ISR
 *
 *    [ hw_reti(); ]
 * }
 * @endcode
 *
 * @hideinitializer
 */
/*  The IRQ object/reason arguments may be followed by other arguments, so we
 *  can not use HW_IRQ().
 */
/*  Get the definition of the object
 */
#define HW_ISR(...)		_HW_ISR1(__VA_ARGS__,,,)
#define _HW_ISR1(o,...)		_HW_ISR2(HW_OD(o),__VA_ARGS__)
#define _HW_ISR2(...)		_HW_ISR3(__VA_ARGS__)

#define _HW_ISR3(c,...)		HW_Y(_HW_ISR3,c)(c,__VA_ARGS__)
#define _HW_ISR3_1(...)		void hw_isr_error_()

/*  Is _hw_irq_##o##_##x an irq?
 */
#define _HW_ISR3_0(c,o,i,a,x,...) _HW_ISR3_2(_hw_irq_##o##_##x,o,x,__VA_ARGS__)
#define _HW_ISR3_2(...)		_HW_ISR3_3(__VA_ARGS__)
#define _HW_ISR3_3(c,...)	HW_Y(_HW_ISR4,_hw_is__irq_##c)(c,__VA_ARGS__)
#define _HW_ISR4_1(c,o,v,e,f,oo,x,...) _HW_ISR9(v,__VA_ARGS__)

/*  Is _hw_irq_##o##_ an irq?
 */
#define _HW_ISR4_0(x,o,...)	_HW_ISR4_2(_hw_irq_##o##_,o,__VA_ARGS__)
#define _HW_ISR4_2(...)		_HW_ISR4_3(__VA_ARGS__)
#define _HW_ISR4_3(c,...)	HW_Y(_HW_ISR5,_hw_is__irq_##c)(c,__VA_ARGS__)
#define _HW_ISR5_1(c,o,v,e,f,oo,...) _HW_ISR9(v,__VA_ARGS__)

/*  There is an error
 */
#define _HW_ISR5_0(o,...)	HW_E(`o` has no IRQ named `` or `HW_QUOTE(__VA_ARGS__)`.) _HW_ISR_X_

/*  The definition of the IRQ is expanded, process the remaining arguments if any
 */
#define _HW_ISR9(v,x,...)	HW_Y(_HW_ISR9,x)(v,x,__VA_ARGS__)
#define _HW_ISR9_1(v,...)	_HW_ISR_(v,)
#define _HW_ISR9_0(v,x,...)	HW_Y(_HW_ISR10,_hw_israttr_##x)(v,x,__VA_ARGS__)
#define _HW_ISR10_0(v,x,...)	HW_E(object has no IRQ named `x`) void hw_isr_error_##x()
#define _HW_ISR10_1(v,a1,...)	HW_Y(_HW_ISR11,__VA_ARGS__)(v,a1,__VA_ARGS__)
#define _HW_ISR11_1(v,a1,...)	_HW_ISR_(v,HW_A1(_hw_israttr_##a1))
#define _HW_ISR11_0(v,a1,x,...)	HW_Y(_HW_ISR12,_hw_israttr_##x)(v,a1,x,__VA_ARGS__)
#define _HW_ISR12_0(v,a1,x,...)	HW_E_T(x) void hw_isr_error_##x()
#define _HW_ISR12_1(v,a1,a2,...)	HW_Y(_HW_ISR13,__VA_ARGS__)(v,a1,a2,__VA_ARGS__,)
#define _HW_ISR13_1(v,a1,a2,...)	_HW_ISR_(v, HW_A1(_hw_israttr_##a1) HW_A1(_hw_israttr_##a2))
#define _HW_ISR13_0(v,a1,a2,x,...)	HW_E_T(x) void hw_isr_error_##x()


#if !defined __ASSEMBLER__


/**
 * @ingroup public_ins_obj
 * @brief Declares the ISR for @ref using_objects "object"'s IRQ "...".
 * @hideinitializer
 *
 * The `HW_VOID_ISR(...)` declares an ISR that doen nothing. This is useful for
 * example when the interrupt is used to wake the core up.
 *
 * @code
 * HW_VOID_ISR( object [, reason] )
 * @endcode
 */
//#define HW_VOID_ISR(...)		HW_ISR(__VA_ARGS__,naked,){ hw_asm("reti");}

#if defined DOXYGEN
#  define HW_VOID_ISR(object, ...)
#else
#  define HW_VOID_ISR(...)		_HW_VISR1(__VA_ARGS__,,,)
#endif

#define _HW_VISR1(x,...)	HW_G2(_HW_VISR2,HW_IS(_irq,x))(x,__VA_ARGS__)
#define _HW_VISR2_1(...)	_HW_VISR11(__VA_ARGS__)
#define _HW_VISR2_0(o,x,...)	HW_G2(_HW_VISR3,HW_IS(_irq,_hw_irq_##o##_##x))(o,x,__VA_ARGS__)
#define _HW_VISR3_1(o,x,...)	_HW_VISR11(_hw_irq_##o##_##x,__VA_ARGS__)
#define _HW_VISR3_0(o,...)	HW_G2(_HW_VISR4,HW_ISON(o))(o,__VA_ARGS__)
#define _HW_VISR4_0(o,...)	HW_PE(o,HW_E_O(o)) void hw_isr_error_##o()
#define _HW_VISR4_1(o,...)	HW_E(`o` has no IRQ named `` or `HW_QUOTE(__VA_ARGS__)`.) _HW_VISR_X_

#define _HW_VISR11(...)			_HW_VISR12(__VA_ARGS__)
#define _HW_VISR12(i,o,v,e,f,g,...)	HW_Y(_HW_VISR13,g)(v,g,__VA_ARGS__)
#define _HW_VISR13_0(v,g,...)		HW_E_G(g)
#define _HW_VISR13_1(v,...)		_HW_VISR_(v) (void)0 //extern int hw_foo


/**
 * @ingroup private_ins
 * @brief  Turns an IRQ on/off.
 * @hideinitializer
 */
#define _hw_mtd_hw_turn__irq		, _hw_tnirq

#define _hw_tnirq(o,v,e,f,vv,...)	HW_Y(_hw_tnirq,_hw_state_##vv)(o,e,vv,__VA_ARGS__)
#define _hw_tnirq_0(o,e,x, ...)		HW_E_ST(x)
#define _hw_tnirq_1(o,e,v, ...)		_hw_write_reg(o,e, HW_A1(_hw_state_##v)) HW_EOL(__VA_ARGS__)


#define _hw_mtd_hwa_turn__irq		, _hwa_tnirq

/**
 * @ingroup private_ins
 * @brief  Turns an IRQ on/off.
 * @hideinitializer
 */
#define _hwa_tnirq(o,v,e,f,vv,...)	HW_Y(_hwa_tnirq,_hw_state_##vv)(o,e,vv,__VA_ARGS__)
#define _hwa_tnirq_0(o,e,x, ...)	HW_E_ST(x)
#define _hwa_tnirq_1(o,e,v, ...)	_hwa_write_reg(o,e, HW_A1(_hw_state_##v)) HW_EOL(__VA_ARGS__)


/**
 * @ingroup private_ins
 * @brief  Clears an IRQ flag.
 * @hideinitializer
 */
#define _hw_mtd_hw_clear__irq		, _hw_clear_irq

#define _hw_clear_irq(v,p,e,f,...)	_hw_write_reg(p,f,1) HW_EOL(__VA_ARGS__)


/**
 * @ingroup private_ins
 * @brief  Clears an irq flag.
 * @hideinitializer
 */
#define _hw_mtd_hwa_clear__irq		, _hwa_clear_irq

#define _hwa_clear_irq(v,p,e,f,...)	_hwa_write_reg(p,f,1) HW_EOL(__VA_ARGS__)


#endif /* !defined __ASSEMBLER__ */
