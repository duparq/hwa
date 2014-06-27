
/*	Expands arguments for irqs
 */
#define HW_XIRQ(...)		HW_G2(_hw_xirq_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__,)
#define _hw_xirq_xctr_0(...)	HW_G2(_hw_xirq_xaio, HW_IS(aio,__VA_ARGS__))(__VA_ARGS__)
//#define _hw_xirq_xaio_0(x,...)	0, "`" #x "`: is not a controller nor an aio."

#define _hw_xirq_xaio_0(...)	HW_G2(_hw_xirq_error, HW_IS(0,__VA_ARGS__))(__VA_ARGS__)
#define _hw_xirq_error_0(x,...)	0, "`" #x "`: is not a controller nor an aio."
#define _hw_xirq_error_1(...)	__VA_ARGS__

#define _hw_xirq_xctr_1(_ctr_,cn,cc,ca, ...)	\
  HW_G2(_hw_xirq_ctr, HW_IS(irq, hw_irq_##cn##_##__VA_ARGS__))(cn,cc,ca, __VA_ARGS__)

#define _hw_xirq_ctr_0(cn,cc,ca,...) \
  0, "`" HW_QUOTE(__VA_ARGS__) "` is not a valid irq name."

#define _hw_xirq_ctr_1(cn,cc,ca, irq, ...)				\
  hw_irq##_##cn##_##irq, __VA_ARGS__

#define _hw_xirq_irq(cn,cc,ca, irq, ...)				\
  hw_irq##_##cn##_##irq, __VA_ARGS__

#define _hw_xirq_xaio_1(_aio_,aion,ion, _ctr_,cn,cc,ca,...)\
  hw_irq_##aion, __VA_ARGS__


/*	Definition of the irq-enable bit associated to an aio or a controller
 */
#define hw_irqe(...)			_hw_irqe_2( HW_XIRQ(__VA_ARGS__) )
#define _hw_irqe_2(...)			_hw_irqe_3(__VA_ARGS__)
#define _hw_irqe_3(x,...)		_hw_irqe_##x(__VA_ARGS__)
#define _hw_irqe_irq(v,_ctr_,cn,cc,ca, irqe,irqf,...)	_HW_X2R_ctr(_ctr_,cn,cc,ca, irqe)


/*	Definition of the irq-flag bit associated to an aio or a controller
 */
#define hw_irqf(...)			_hw_irqf_2( HW_XIRQ(__VA_ARGS__) )
#define _hw_irqf_2(...)			_hw_irqf_3(__VA_ARGS__)
#define _hw_irqf_3(x,...)		_hw_irqf_##x(__VA_ARGS__)
#define _hw_irqf_irq(v,_ctr_,cn,cc,ca, irqe,irqf,...)	_HW_X2R_ctr(_ctr_,cn,cc,ca, irqf)


/*	Declaration of an ISR
 */
#define HW_ISR(...)			_hw_isr_2( HW_XIRQ(__VA_ARGS__) )
#define _hw_isr_2(...)			_hw_isr_3(__VA_ARGS__)
#define _hw_isr_3(x,...)		_hw_isr_##x(__VA_ARGS__)
#define _hw_isr_irq(v,_ctr_,cn,cc,ca, irqe,irqf,...)	_hw_isr_4(__VA_ARGS__, v)
#define _hw_isr_4(x,...)		HW_G2(_hw_isr_a1,HW_IS(,x))(x,__VA_ARGS__)
#define _hw_isr_a1_1(_,...)		_hw_isr_(__VA_ARGS__,)
#define _hw_isr_a1_0(attr,x,...)	HW_G2(_hw_isr_a2,HW_IS(,x))(x,__VA_ARGS__,hw_israttr_##attr)
#define _hw_isr_a2_1(_,...)		_hw_isr_(__VA_ARGS__)
#define _hw_isr_a2_0(attr,x,...)	HW_G2(_hw_isr_a3,HW_IS(,x))(x,__VA_ARGS__ hw_israttr_##attr)
#define _hw_isr_a3_1(_,...)		_hw_isr_(__VA_ARGS__)
#define _hw_isr_a3_0(...)		HW_PPERROR( "too many arguments." )
