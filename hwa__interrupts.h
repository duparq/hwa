
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	Definitions related to interrupts
 */

#define hw_class_irq

/*	Definition of an interrupt
 */
#define hw_irq(...)			HW_GEN(_hw_irq, __VA_ARGS__)
#define _hw_irq(c,n,...)		_hw_irq2(n, HW_POP_##c(c,n,__VA_ARGS__,))

//#define _hw_irq(...)			HW_G2(_hw_irq9, HW_IS(irq,__VA_ARGS__))(__VA_ARGS__)
//#define _hw_irq9_0(c,n,...)		_hw_irq2(n, HW_POP_##c(c,n,__VA_ARGS__,))
//#define _hw_irq9_1(...)			__VA_ARGS__

#define _hw_irq2(...)			_hw_irq3(__VA_ARGS__)
#define _hw_irq3(n,...)						\
  HW_G2(_hw_irq,HW_IS(irq,hw_irq_##n##_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hw_irq_1(n,...)		hw_irq_##n##_##__VA_ARGS__
#define _hw_irq_0(n,...)				\
  HW_G2(_hw_irq0,HW_IS(irq,hw_irq_##n))(n,__VA_ARGS__)
#define _hw_irq0_1(n,...)		hw_irq_##n,__VA_ARGS__
#define _hw_irq0_0(n,...)		HW_ERR("neither `` or `" HW_QUOTE(__VA_ARGS__) \
					       "` is an IRQ name for hw_`" #n "`.")


/*	Definition of an irq-enable bit
 */
#define hw_irqe(...)			_hw_irqe_2(hw_irq(__VA_ARGS__))
#define _hw_irqe_2(...)			HW_G2(_hw_irqe,HW_IS(irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqe_0(...)			__VA_ARGS__
#define _hw_irqe_1(irq,v,n,ie,if,...)	HW_EOL(_hw_reg(hw_##n,ie), __VA_ARGS__,)


/*	Definition of an irq-flag bit
 */
#define hw_irqf(...)			_hw_irqf_2(hw_irq(__VA_ARGS__))
#define _hw_irqf_2(...)			HW_G2(_hw_irqf,HW_IS(irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqf_0(...)			__VA_ARGS__
#define _hw_irqf_1(irq,v,n,ie,if,...)	HW_EOL(_hw_reg(hw_##n,if), __VA_ARGS__,)


/*	Declaration of an ISR
 */
#define HW_ISR(...)			_hw_isr_2(hw_irq(__VA_ARGS__))
#define _hw_isr_2(...)			HW_G2(_hw_isr,HW_IS(irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_isr_0(...)			HW_FERR(__VA_ARGS__)
#define _hw_isr_1(irq,v,n,ie,if,...)	HW_G2(_hw_isr_a1, HW_IS(,__VA_ARGS__))(__VA_ARGS__, v)

#define _hw_isr_a1_1(_,...)		_hw_isr_(__VA_ARGS__,)
#define _hw_isr_a1_0(x,...)		HW_G2(_hw_isr_a1_0, HW_IS(,hw_israttr_##x))(x,__VA_ARGS__)
#define _hw_isr_a1_0_0(x,...)		HW_FERR(HW_ERR("`"#x"` is not a valid ISR attribute."))
#define _hw_isr_a1_0_1(x,...)		HW_G2(_hw_isr_a2,\
					      HW_IS(,__VA_ARGS__))(__VA_ARGS__, HW_A1(hw_israttr_##x))

#define _hw_isr_a2_1(_,...)		_hw_isr_(__VA_ARGS__)
#define _hw_isr_a2_0(x,...)		HW_G2(_hw_isr_a2_0, HW_IS(,hw_israttr_##x))(x,__VA_ARGS__)
#define _hw_isr_a2_0_0(x,...)		HW_FERR(HW_ERR("`"#x"` is not a valid ISR attribute."))
#define _hw_isr_a2_0_1(x,...)		HW_G2(_hw_isr_a3,\
					      HW_IS(,__VA_ARGS__))(__VA_ARGS__ HW_A1(hw_israttr_##x))

#define _hw_isr_a3_1(_,...)		_hw_isr_(__VA_ARGS__)
#define _hw_isr_a3_0(x,...)		HW_FERR(HW_ERR("garbage starting with `" #x "...`"))


#if !defined __ASSEMBLER__

/*	Turn irq on/off
 */
#define hw_def_hw_turn_irq		, _hw_turn_irq

#define _hw_turn_irq(irq, vector, n, irqe, irqf, ...)		\
  HW_G2(_hw_turn_irq_state, HW_IS(,hw_state_##__VA_ARGS__))(vector, n, irqe, __VA_ARGS__,)
#define _hw_turn_irq_state_0(vector, n, irqe, ...)		\
  HW_ERR("expected `on` or `off`, got `" HW_QUOTE(__VA_ARGS__) "` instead.")
#define _hw_turn_irq_state_1(vector, n, irqe, x, ...)		\
  _hw_write_reg( hw_##n, irqe, HW_A1(hw_state_##x) ) HW_EOP(__VA_ARGS__)


/*	Short for hw_turn( hw_irq(...), ... )
 */
#define hw_turn_irq(...)		_hw_turnirq_2(hw_irq(__VA_ARGS__))
#define _hw_turnirq_2(...)		HW_G2(_hw_turnirq,HW_IS(irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_turnirq_0(...)		__VA_ARGS__
#define _hw_turnirq_1(...)		_hw_turn_irq(__VA_ARGS__)


/*	Turn IRQ on/off
 */
#define hw_def_hwa_turn_irq		, _hwa_turn_irq_eol

/* Remove eol introduced by hw_irq() */
#define _hwa_turn_irq_eol(irq, vector, n, irqe, irqf, eol, ...)		\
  HW_G2(_hwa_turn_irq_state, HW_IS(,hw_state_##__VA_ARGS__))(vector, n, irqe, __VA_ARGS__,)

#define _hwa_turn_irq(irq, vector, n, irqe, irqf, ...)			\
  HW_G2(_hwa_turn_irq_state, HW_IS(,hw_state_##__VA_ARGS__))(vector, n, irqe, __VA_ARGS__,)
#define _hwa_turn_irq_state_0(vector, n, irqe, ...)			\
  HW_ERR("expected `on` or `off`, got `" HW_QUOTE(__VA_ARGS__) "` instead.")
#define _hwa_turn_irq_state_1(vector, n, irqe, x, ...)			\
  _hwa_write_reg( hw_##n, irqe, HW_A1(hw_state_##x) ) HW_EOP(__VA_ARGS__)

/*	Short for hwa_turn( hw_irq(...), ... )
 */
#define hwa_turn_irq(...)		_hwa_turnirq_2(hw_irq(__VA_ARGS__))
#define _hwa_turnirq_2(...)		HW_G2(_hwa_turnirq,HW_IS(irq,__VA_ARGS__))(__VA_ARGS__)
#define _hwa_turnirq_0(...)		__VA_ARGS__
#define _hwa_turnirq_1(...)		_hwa_turn_irq(__VA_ARGS__)

#endif /* !defined __ASSEMBLER__ */
