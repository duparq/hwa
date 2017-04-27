#ifndef HWA_TIMER_H
#define HWA_TIMER_H

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_timer_clr_irq(name, irq)		\
  _hw_timer_clr_irq(name, irq)

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_timer_set_count(name, n)		\
  _hwa_timer_set_count(name, n)

#define hwa_timer_set_div(name, n)		\
  _hwa_timer_set_div(name, n)

#define hwa_timer_set_top(name, n)		\
  _hwa_timer_set_top(name, n)

#define hwa_timer_turn_irq(name, irq, state)			\
  _hwa_timer_turn_irq(name, HWA_TIMER_IRQBIT_##irq, HWA_STATE_##state)

#define hwa_timer_turn(name, state)		\
  _hwa_timer_turn(name, HWA_STATE_##state)


/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

#define HWA_PTR_TIMER2				HWA_PTR_APB1+0x0000 /* 0x40000000 */
#define HWA_PTR_TIMER3				HWA_PTR_APB1+0x0400 /* 0x40000400 */
#define HWA_PTR_TIMER4				HWA_PTR_APB1+0x0800 /* 0x40000800 */
#define HWA_PTR_TIMER5				HWA_PTR_APB1+0x0C00 /* 0x40000C00 */

#define HWA_IRQN_TIMER2				28

#if 0
#define HW_TIMER_CR1(pname)			(*(volatile u32 *)(HWA_PTR_##pname+0x00))
#define HW_TIMER_CR2(pname)			(*(volatile u32 *)(HWA_PTR_##pname+0x04))
#define HW_TIMER_DIER(pname)			(*(volatile u32 *)(HWA_PTR_##pname+0x0C))
#define HW_TIMER_SR(pname)			(*(volatile u32 *)(HWA_PTR_##pname+0x10))
#define HW_TIMER_CNT(pname)			(*(volatile u32 *)(HWA_PTR_##pname+0x24))
#define HW_TIMER_PSC(pname)			(*(volatile u32 *)(HWA_PTR_##pname+0x28))
#define HW_TIMER_ARR(pname)			(*(volatile u32 *)(HWA_PTR_##pname+0x2C))
#endif

#define HWA_PTR_TIMER2_CR1			((volatile u32 *)(HWA_PTR_TIMER2+0x00))
#define HWA_PTR_TIMER2_CR2			((volatile u32 *)(HWA_PTR_TIMER2+0x04))
#define HWA_PTR_TIMER2_DIER			((volatile u32 *)(HWA_PTR_TIMER2+0x0C))
#define HWA_PTR_TIMER2_SR			((volatile u32 *)(HWA_PTR_TIMER2+0x10))
#define HWA_PTR_TIMER2_CNT			((volatile u32 *)(HWA_PTR_TIMER2+0x24))
#define HWA_PTR_TIMER2_PSC			((volatile u32 *)(HWA_PTR_TIMER2+0x28))
#define HWA_PTR_TIMER2_ARR			((volatile u32 *)(HWA_PTR_TIMER2+0x2C))

#define HWA_PTR_TIMER3_CR1			((volatile u32 *)(HWA_PTR_TIMER3+0x00))
#define HWA_PTR_TIMER3_CR2			((volatile u32 *)(HWA_PTR_TIMER3+0x04))
#define HWA_PTR_TIMER3_DIER			((volatile u32 *)(HWA_PTR_TIMER3+0x0C))
#define HWA_PTR_TIMER3_SR			((volatile u32 *)(HWA_PTR_TIMER3+0x10))
#define HWA_PTR_TIMER3_CNT			((volatile u32 *)(HWA_PTR_TIMER3+0x24))
#define HWA_PTR_TIMER3_PSC			((volatile u32 *)(HWA_PTR_TIMER3+0x28))
#define HWA_PTR_TIMER3_ARR			((volatile u32 *)(HWA_PTR_TIMER3+0x2C))

#define HWA_PTR_TIMER4_CR1			((volatile u32 *)(HWA_PTR_TIMER4+0x00))
#define HWA_PTR_TIMER4_CR2			((volatile u32 *)(HWA_PTR_TIMER4+0x04))
#define HWA_PTR_TIMER4_DIER			((volatile u32 *)(HWA_PTR_TIMER4+0x0C))
#define HWA_PTR_TIMER4_SR			((volatile u32 *)(HWA_PTR_TIMER4+0x10))
#define HWA_PTR_TIMER4_CNT			((volatile u32 *)(HWA_PTR_TIMER4+0x24))
#define HWA_PTR_TIMER4_PSC			((volatile u32 *)(HWA_PTR_TIMER4+0x28))
#define HWA_PTR_TIMER4_ARR			((volatile u32 *)(HWA_PTR_TIMER4+0x2C))

#define HWA_PTR_TIMER5_CR1			((volatile u32 *)(HWA_PTR_TIMER5+0x00))
#define HWA_PTR_TIMER5_CR2			((volatile u32 *)(HWA_PTR_TIMER5+0x04))
#define HWA_PTR_TIMER5_DIER			((volatile u32 *)(HWA_PTR_TIMER5+0x0C))
#define HWA_PTR_TIMER5_SR			((volatile u32 *)(HWA_PTR_TIMER5+0x10))
#define HWA_PTR_TIMER5_CNT			((volatile u32 *)(HWA_PTR_TIMER5+0x24))
#define HWA_PTR_TIMER5_PSC			((volatile u32 *)(HWA_PTR_TIMER5+0x28))
#define HWA_PTR_TIMER5_ARR			((volatile u32 *)(HWA_PTR_TIMER5+0x2C))

#define hwa_timer_begin(state)			\
  hwa_timer_begin_(TIMER2, state)		\
  hwa_timer_begin_(TIMER3, state)		\
  hwa_timer_begin_(TIMER4, state)		\
  hwa_timer_begin_(TIMER5, state)

/*	Registers declarations: name, type, address, reset value, write mask
 */
#define hwa_timer_begin_(pname, state)					\
  HWA_DECL(pname##_CR1,  u32, HWA_PTR_##pname+0x00, 0x00000000, 0x000003FF, state) \
  HWA_DECL(pname##_CR2,  u32, HWA_PTR_##pname+0x04, 0x00000000, 0x000000F8, state) \
  HWA_DECL(pname##_DIER, u32, HWA_PTR_##pname+0x0C, 0x00000000, 0x00005F5F, state) \
  HWA_DECL(pname##_SR,   u32, HWA_PTR_##pname+0x10, 0x00000000, 0x00001E5F, state) \
  HWA_DECL(pname##_CNT,  u32, HWA_PTR_##pname+0x24, 0x00000000, 0x0000FFFF, state) \
  HWA_DECL(pname##_PSC,  u32, HWA_PTR_##pname+0x28, 0x00000000, 0x0000FFFF, state) \
  HWA_DECL(pname##_ARR,  u32, HWA_PTR_##pname+0x2C, 0x00000000, 0x0000FFFF, state)

#define hwa_timer_commit()			\
  hwa_timer_commit_(TIMER2)			\
  hwa_timer_commit_(TIMER3)			\
  hwa_timer_commit_(TIMER4)			\
  hwa_timer_commit_(TIMER5)

#define hwa_timer_commit_(pname)			\
  HWA_COMMIT(pname##_CR1);			\
  HWA_COMMIT(pname##_CR2);			\
  HWA_COMMIT(pname##_SR);			\
  HWA_COMMIT(pname##_DIER);			\
  HWA_COMMIT(pname##_CNT);			\
  HWA_COMMIT(pname##_PSC);			\
  HWA_COMMIT(pname##_ARR);

#define _hwa_timer_set_count(name, count)	\
  HWA_SET(name##_CNT, 0xffff, 0, count)

#define _hwa_timer_set_div(name, div)		\
  HWA_SET(name##_PSC, 0xffff, 0, div)

#define _hwa_timer_set_top(name, top)		\
  HWA_SET(name##_ARR, 0xffff, 0, top)

#define _hwa_timer_turn_irq(name, irq, state)	\
  HWA_SET(name##_DIER, 0b1, irq, state)

#define _hwa_timer_turn(name, state)		\
  HWA_SET(name##_CR1, 0b1, 0, state)

#define _hw_timer_clr_irq(pname, pirq)			\
  *HWA_PTR_##pname##_SR &= ~(1<<HWA_TIMER_IRQBIT_##pirq)

#define HWA_TIMER_IRQBIT_UPDATE			0

#endif
