
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	Definitions related to interrupts
 */


/*	Definition of an interrupt
 */
#define hw_irq(...)		HW_G2(_hw_xirq_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__,)
#define _hw_xirq_xctr_0(...)	HW_G2(_hw_xirq_error, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_xirq_error_0(x,...)	0, "hw_`" #x "`: is not a controller."
#define _hw_xirq_error_1(...)	__VA_ARGS__

#define _hw_xirq_xctr_1(ctr,cc,cn, ...)				\
  _hw_xirq_xctr_2(HW_LEN(hw_##cn),cn,ctr,cc,cn,__VA_ARGS__)
#define _hw_xirq_xctr_2(...)		_hw_xirq_xctr_3(__VA_ARGS__)
#define _hw_xirq_xctr_3(n,cn,...)	_hw_xirq_xctr_4(cn,HW_POP_##n(__VA_ARGS__))
#define _hw_xirq_xctr_4(...)		_hw_xirq_xctr_5(__VA_ARGS__)
#define _hw_xirq_xctr_5(cn,...)	\
  HW_G2(_hw_xirq, HW_IS(irq, hw_irq_##cn##_##__VA_ARGS__))(cn, __VA_ARGS__)

#define _hw_xirq_0(cn,...)		\
  0, "`" HW_QUOTE(HW_A0(__VA_ARGS__)) "` is not a valid irq name for controller `hw_" #cn "`."

#define _hw_xirq_1(cn,in,...)			\
  hw_irq_##cn##_##in


/*	Turn irq on/off
 */
#define hwa_turn_irq_isfn
#define hwa_turn_irq(v, ctr,cc,cn,ca, irqe, irqf, zstate)\
  HW_G2(_hwa_turn_irq_state, HW_IS(,hw_state_##zstate))(vector,_ctr_,cc,cn,ca, irqe, irqf, zstate)
#define _hwa_turn_irq_state_0(vector, _ctr_,cc,cn,ca, irqe, irqf, zstate) \
  HW_ERR("expected `on` or `off`, got `" #zstate "` instead.")
#define _hwa_turn_irq_state_1(vector, ctr,cc,cn,ca, irqe, irqf, zstate)	\
  _hwa_write_mem(ctr,cc,cn,ca, irqe, HW_A1(hw_state_##zstate))


/*	Definition of an irq-enable bit
 */
#define hw_irqe(...)			_hw_irqe_2( hw_irq(__VA_ARGS__) )
#define _hw_irqe_2(...)			_hw_irqe_3(__VA_ARGS__)
#define _hw_irqe_3(x,...)		_hw_irqe_##x(__VA_ARGS__)
#define _hw_irqe_irq(v, ctr,cc,cn,ca, irqe,irqf, ...)	_hw_irqe_irq_2( HW_XMEM(cc,cn,ca,irqe ) )
#define _hw_irqe_irq_2(...)		_hw_irqe_irq_3(__VA_ARGS__)
#define _hw_irqe_irq_3(_1,cn,ca,rn,rw,ra,rrv,rwm,rbn,rbp,_)	mem,bit,cn,rn,ca+ra,rbn,rbp


/*	Definition of an irq-flag bit
 */
#define hw_irqf(...)			_hw_irqf_2( hw_irq(__VA_ARGS__) )
#define _hw_irqf_2(...)			_hw_irqf_3(__VA_ARGS__)
#define _hw_irqf_3(x,...)		_hw_irqf_##x(__VA_ARGS__)
#define _hw_irqf_irq(v, ctr,cc,cn,ca, irqe,irqf, ...)	_hw_irqf_irq_2( HW_XMEM(cc,cn,ca,irqf ) )
#define _hw_irqf_irq_2(...)		_hw_irqf_irq_3(__VA_ARGS__)
#define _hw_irqf_irq_3(_1,cn,ca,rn,rw,ra,rrv,rwm,rbn,rbp,_)	mem,bit,cn,rn,ca+ra,rbn,rbp


/*	Declaration of an ISR
 */
#define HW_ISR(...)			_hw_isr_2( hw_irq(__VA_ARGS__), )
#define _hw_isr_2(...)			_hw_isr_3(__VA_ARGS__)
#define _hw_isr_3(x,...)		_hw_isr_##x(__VA_ARGS__)
#define _hw_isr_irq(v,_ctr_,cc,cn,ca, irqe,irqf,...)	_hw_isr_4(__VA_ARGS__, v)
#define _hw_isr_4(x,...)		HW_G2(_hw_isr_a1,HW_IS(,x))(x,__VA_ARGS__)
#define _hw_isr_a1_1(_,...)		_hw_isr_(__VA_ARGS__,)
#define _hw_isr_a1_0(attr,x,...)	HW_G2(_hw_isr_a2,HW_IS(,x))(x,__VA_ARGS__,hw_israttr_##attr)
#define _hw_isr_a2_1(_,...)		_hw_isr_(__VA_ARGS__)
#define _hw_isr_a2_0(attr,x,...)	HW_G2(_hw_isr_a3,HW_IS(,x))(x,__VA_ARGS__ hw_israttr_##attr)
#define _hw_isr_a3_1(_,...)		_hw_isr_(__VA_ARGS__)
#define _hw_isr_a3_0(...)		HW_ERR( "too many arguments." )
