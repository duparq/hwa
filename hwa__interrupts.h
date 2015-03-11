
/*	Interrupts
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#define hw_class__irq
#define hw_is__irq__irq			, 1

#define hw_mthd_hw_turn_irq		, _hw_turn_irq
#define hw_mthd_hw_turn__irq		, _hw_turn_irq
#define hw_mthd_hwa_turn_irq		, _hwa_turn_irq
#define hw_mthd_hwa_turn__irq		, _hwa_turn_irq
#define hw_mthd_hw_clear_irq		, _hw_clear_irq
#define hw_mthd_hw_clear__irq		, _hw_clear_irq
#define hw_mthd_hwa_clear_irq		, _hwa_clear_irq
#define hw_mthd_hwa_clear__irq		, _hwa_clear_irq


/*	Definition of an interrupt, no extra parameter allowed
 */
/* #define hw_irq(...)			HW_GNRC(_hw_irq,__VA_ARGS__,) */
/* //_hw_irq(counter0,_c8a, 400, 0,compare0,) */
/* #define _hw_irq(p,c,i,a,...)		_hw_irq2(p,_hw_pop_##c(c,i,a,__VA_ARGS__)) */
/* #define _hw_irq2(...)			_hw_irq3(__VA_ARGS__) */
/* #define _hw_irq3(p,...)							\ */
/*   HW_G2(_hw_irq,HW_IS(_irq,hw_irq_##p##_##__VA_ARGS__))(p,__VA_ARGS__) */
/* #define _hw_irq_1(p,n,...)		HW_TX(hw_irq_##p##_##n, __VA_ARGS__) */
/* #define _hw_irq_0(p,...)				\ */
/*   HW_G2(_hw_irq0,HW_IS(_irq,hw_irq_##p))(p,__VA_ARGS__) */
/* #define _hw_irq0_1(p,...)		HW_TX(hw_irq_##p,__VA_ARGS__) */
/* #define _hw_irq0_0(p,...)		HW_ERR("neither `` or `" HW_QUOTE(__VA_ARGS__) \ */
/* 					       "` is an IRQ name for `" #p "`.") */

/*	Definition of an interrupt, extra arguments allowed and returned
 */
#define _hw_irqx(...)			HW_G2(_hw_irqx2,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqx2_1(...)		__VA_ARGS__
#define _hw_irqx2_0(p,...)						\
  HW_G2(_hw_irqx3, HW_IS(_irq,hw_irq_##p##_##__VA_ARGS__))(p,__VA_ARGS__)
#define _hw_irqx3_1(p,...)		hw_irq_##p##_##__VA_ARGS__
#define _hw_irqx3_0(p,...)					\
  HW_G2(_hw_irqx4, HW_IS(_irq,hw_irq_##p))(p,__VA_ARGS__)
#define _hw_irqx4_1(p,...)		hw_irq_##p, __VA_ARGS__
#define _hw_irqx4_0(p,...)		HW_G2(_hw_irqx5,HW_ISOBJ(p))(p,__VA_ARGS__)
#define _hw_irqx5_0(p,...)		HW_ERR("`"#p"` is not a HWA object.")
#define _hw_irqx5_1(p,...)		HW_ERR("`"#p"` has no IRQ `` or `" \
					       HW_QUOTE(__VA_ARGS__)"`.")


/*	Definition of an irq-enable bit
 */
#define hw_irqe(...)			_hw_irqe_2(hw_irq(__VA_ARGS__))
#define _hw_irqe_2(...)			HW_G2(_hw_irqe,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqe_0(...)			__VA_ARGS__
#define _hw_irqe_1(t,v,p,e,f)		_hw_xpr(p,e)
//#define _hw_irqe_1(t,v,p,e,f)		p,e


/*	Definition of an irq-flag bit
 */
#define hw_irqf(...)			_hw_irqf_2(hw_irq(__VA_ARGS__))
#define _hw_irqf_2(...)			HW_G2(_hw_irqf,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqf_0(...)			__VA_ARGS__
#define _hw_irqf_1(t,v,p,e,f)		_hw_reg(p,f)


/*	Declaration of an ISR, up to 2 attributes allowed
 */
#define HW_ISR(...)			_hw_isr_2(_hw_irqx(__VA_ARGS__,))
#define _hw_isr_2(...)			HW_G2(_hw_isr2,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_isr2_0(...)			HW_ERRFN(__VA_ARGS__)
#define _hw_isr2_1(irq,v,n,e,f,...)	HW_G2(_hw_isr_a1, HW_IS(,__VA_ARGS__))(__VA_ARGS__, v)

#define _hw_isr_a1_1(_,...)		_hw_isr_(__VA_ARGS__,)
#define _hw_isr_a1_0(x,...)		HW_G2(_hw_isr_a1_0, HW_IS(,hw_israttr_##x))(x,__VA_ARGS__)
#define _hw_isr_a1_0_0(x,...)		HW_ERRFN(HW_ERR("`"#x"` is not a valid ISR attribute."))
#define _hw_isr_a1_0_1(x,...)		\
  HW_G2(_hw_isr_a2,HW_IS(,__VA_ARGS__))(__VA_ARGS__, HW_A1(hw_israttr_##x))

#define _hw_isr_a2_1(_,...)		_hw_isr_(__VA_ARGS__)
#define _hw_isr_a2_0(x,...)		HW_G2(_hw_isr_a2_0, HW_IS(,hw_israttr_##x))(x,__VA_ARGS__)
#define _hw_isr_a2_0_0(x,...)		HW_ERRFN(HW_ERR("`"#x"` is not a valid ISR attribute."))
#define _hw_isr_a2_0_1(x,...)		\
  HW_G2(_hw_isr_a3,HW_IS(,__VA_ARGS__))(__VA_ARGS__ HW_A1(hw_israttr_##x))

#define _hw_isr_a3_1(_,...)		_hw_isr_(__VA_ARGS__)
#define _hw_isr_a3_0(x,...)		HW_ERRFN(HW_ERR("garbage starting with `" #x "...`"))


#if !defined __ASSEMBLER__

/*	Turn irq on/off
 */

#define _hw_turn_irq(v,p,e,f, ...)					\
  HW_G2(_hw_turn_irq_vstate, HW_IS(,hw_state_##__VA_ARGS__))(p,e, __VA_ARGS__,)
#define _hw_turn_irq_vstate_0(p,e, ...)					\
  HW_ERR("expected `on` or `off`, got `" HW_QUOTE(__VA_ARGS__) "` instead.")
#define _hw_turn_irq_vstate_1(p,e,v, ...)				\
    HW_TX(_hw_write_reg( p,e, HW_A1(hw_state_##v)), __VA_ARGS__)

#define _hwa_turn_irq(v,p,e,f, ...)					\
  HW_G2(_hwa_turn_irq_vstate, HW_IS(,hw_state_##__VA_ARGS__))(p,e, __VA_ARGS__,)
#define _hwa_turn_irq_vstate_0(p,e, ...)				\
  HW_ERR("expected `on` or `off`, got `" HW_QUOTE(__VA_ARGS__) "` instead.")
#define _hwa_turn_irq_vstate_1(p,e,v, ...)			\
  HW_TX(_hwa_write_reg(p,e, HW_A1(hw_state_##v)), __VA_ARGS__)

/*	Short for hw/hwa_turn( hw_irq(...), ... )
 */
#define hw_turn_irq(...)		_hw_turnirq_2(_hw_irqx(__VA_ARGS__,))
#define _hw_turnirq_2(...)		HW_G2(_hw_turnirq,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_turnirq_0(...)		__VA_ARGS__
#define _hw_turnirq_1(t,...)		_hw_turn_irq(__VA_ARGS__)

#define hwa_turn_irq(...)		_hwa_turnirq_2(_hw_irqx(__VA_ARGS__,))
#define _hwa_turnirq_2(...)		HW_G2(_hwa_turnirq,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hwa_turnirq_0(...)		__VA_ARGS__
#define _hwa_turnirq_1(t,...)		_hwa_turn_irq(__VA_ARGS__)


/*	Clear IRQ flag
 */
#define _hw_clear_irq(v,p,e,f, ... )	HW_TX(_hw_write_reg(p,f, 1 ), __VA_ARGS__)
#define _hwa_clear_irq(v,p,e,f, ... )	HW_TX(_hwa_write_reg(p,f, 1 ), __VA_ARGS__)


/*	Short for hw/hwa_clear( hw_irq(...), ... )
 */
#define hw_clear_irq(...)		_hw_clearirq_2(_hw_irqx(__VA_ARGS__,))
#define _hw_clearirq_2(...)		HW_G2(_hw_clearirq,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_clearirq_0(...)		__VA_ARGS__
#define _hw_clearirq_1(t,...)		_hw_clear_irq(__VA_ARGS__)

#define hwa_clear_irq(...)		_hwa_clearirq_2(_hw_irqx(__VA_ARGS__,))
#define _hwa_clearirq_2(...)		HW_G2(_hwa_clearirq,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hwa_clearirq_0(...)		__VA_ARGS__
#define _hwa_clearirq_1(t,...)		_hwa_clear_irq(__VA_ARGS__)


#endif /* !defined __ASSEMBLER__ */
