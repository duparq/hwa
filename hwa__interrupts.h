
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	Definitions related to interrupts
 */


/*	Definition of an interrupt
 */
#define hw_irq(...)		_hw_irq_2(__VA_ARGS__)
#define _hw_irq_2(...)		HW_G2(_hw_irq_xclass, HW_IS(,hw_class_##__VA_ARGS__))(__VA_ARGS__,,)
#define _hw_irq_xclass_0(...)	HW_G2(_hw_irq_error, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irq_error_0(x,...)	HW_ERR("`hw_" #x "` is not defined.")
#define _hw_irq_error_1(...)	__VA_ARGS__
#define _hw_irq_xclass_1(c,n,i,a,v,...)			\
  HW_G2(_hw_irq, HW_IS(irq, hw_irq_##n##_##v))(n,v, __VA_ARGS__)

#define _hw_irq_0(n,...)	HW_ERR("`" HW_QUOTE(__VA_ARGS__) \
				       "` is not a valid irq name for `hw_" #n "`.")
#define _hw_irq_1(n,v,...)	hw_irq_##n##_##v


/*	Turn irq on/off
 */
#define hw_def_hwa_turn_irq	, _hwa_turn_irq
#define _hwa_turn_irq(irq, vector, cc,cn,ci,ca, irqe, irqf, zstate)		\
  HW_G2(_hwa_turn_irq_state, HW_IS(,hw_state_##zstate))(vector, cc,cn,ci,ca, irqe, zstate)
#define _hwa_turn_irq_state_0(vector, cc,cn,ci,ca, irqe, zstate)	\
  HW_ERR("expected `on` or `off`, got `" #zstate "` instead.")
#define _hwa_turn_irq_state_1(vector, cc,cn,ci,ca, irqe, zstate)	\
  hwa_write( hw_bits(cc,cn,ci,ca, irqe), HW_A1(hw_state_##zstate) )


/*	Definition of an irq-enable bit
 */
#define hw_irqe(...)			HW_G2(_hw_irqe, HW_IS(irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqe_0(...)			HW_G2(_hw_irqe_0, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqe_0_0(...)		HW_ERR("can not process hw_irqe(" #__VA_ARGS__ ").")
#define _hw_irqe_0_1(...)		__VA_ARGS__
#define _hw_irqe_1(t,v, c,n,i,a, irqe,irqf)	_hw_bits(c,n,i,a,irqe)


/*	Definition of an irq-flag bit
 */
#define hw_irqf(...)			HW_G2(_hw_irqf, HW_IS(irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqf_0(...)			HW_G2(_hw_irqf_0, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqf_0_0(...)		HW_ERR("can not process hw_irqf(" #__VA_ARGS__ ").")
#define _hw_irqf_0_1(...)		__VA_ARGS__
#define _hw_irqf_1(t,v, c,n,i,a, irqe,irqf)	_hw_bits(c,n,i,a,irqf)


/*	Declaration of an ISR
 */
#define HW_ISR(...)			HW_G2(_hw_isr, HW_IS(irq,__VA_ARGS__))(__VA_ARGS__,)
#define _hw_isr_0(...)			HW_G2(_hw_isr_0, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_isr_0_0(...)		HW_ERR("can not process HW_ISR(" #__VA_ARGS__ ").")
#define _hw_isr_0_1(...)		__VA_ARGS__
#define _hw_isr_1(t,v, cc,cn,ci,ca, irqe,irqf, ...)	_hw_isr_2(__VA_ARGS__, v)
#define _hw_isr_2(x,...)		HW_G2(_hw_isr_a1,HW_IS(,x))(x,__VA_ARGS__)
#define _hw_isr_a1_1(_,...)		_hw_isr_(__VA_ARGS__,)
#define _hw_isr_a1_0(attr,x,...)	HW_G2(_hw_isr_a2,HW_IS(,x))(x,__VA_ARGS__,hw_israttr_##attr)
#define _hw_isr_a2_1(_,...)		_hw_isr_(__VA_ARGS__)
#define _hw_isr_a2_0(attr,x,...)	HW_G2(_hw_isr_a3,HW_IS(,x))(x,__VA_ARGS__ hw_israttr_##attr)
#define _hw_isr_a3_1(_,...)		_hw_isr_(__VA_ARGS__)
#define _hw_isr_a3_0(...)		HW_ERR( "too many arguments." )
