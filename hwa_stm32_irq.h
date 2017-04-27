#ifndef HWA_IRQ_H
#define HWA_IRQ_H

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 ********************************************************************************/

#define hwa_turn_irq(pname, state)			\
  _hwa_turn_irq(pname, state)

#define hwa_set_irq_priority(pname, priority)	\
  _hwa_set_irq_priority(pname, priority)


/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

#define HWA_PTR_NVIC			0xE000E100

#define HWA_PTR_NVIC_ISER0		((volatile u32 *)(HWA_PTR_NVIC+0x000))
#define HWA_PTR_NVIC_ISER1		((volatile u32 *)(HWA_PTR_NVIC+0x004))
#define HWA_PTR_NVIC_ISER2		((volatile u32 *)(HWA_PTR_NVIC+0x008))
#define HWA_PTR_NVIC_ISPR0		((volatile u32 *)(HWA_PTR_NVIC+0x100))
#define HWA_PTR_NVIC_ISPR1		((volatile u32 *)(HWA_PTR_NVIC+0x104))
#define HWA_PTR_NVIC_ISPR2		((volatile u32 *)(HWA_PTR_NVIC+0x108))
#define HWA_PTR_NVIC_IPR0		((volatile u32 *)(HWA_PTR_NVIC+0x300))
#define HWA_PTR_NVIC_IPR1		((volatile u32 *)(HWA_PTR_NVIC+0x304))
#define HWA_PTR_NVIC_IPR2		((volatile u32 *)(HWA_PTR_NVIC+0x308))
#define HWA_PTR_NVIC_IPR3		((volatile u32 *)(HWA_PTR_NVIC+0x30C))
#define HWA_PTR_NVIC_IPR4		((volatile u32 *)(HWA_PTR_NVIC+0x310))
#define HWA_PTR_NVIC_IPR5		((volatile u32 *)(HWA_PTR_NVIC+0x314))
#define HWA_PTR_NVIC_IPR6		((volatile u32 *)(HWA_PTR_NVIC+0x318))
#define HWA_PTR_NVIC_IPR7		((volatile u32 *)(HWA_PTR_NVIC+0x31C))
#define HWA_PTR_NVIC_IPR8		((volatile u32 *)(HWA_PTR_NVIC+0x320))
#define HWA_PTR_NVIC_IPR9		((volatile u32 *)(HWA_PTR_NVIC+0x324))
#define HWA_PTR_NVIC_IPR10		((volatile u32 *)(HWA_PTR_NVIC+0x328))
#define HWA_PTR_NVIC_IPR11		((volatile u32 *)(HWA_PTR_NVIC+0x32C))
#define HWA_PTR_NVIC_IPR12		((volatile u32 *)(HWA_PTR_NVIC+0x330))


/*	Registers declarations: name, type, address, reset value, write mask
 */
#define hwa_irq_begin(state)						\
  HWA_DECL(NVIC_ISER0, u32, HWA_PTR_NVIC+0x000, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E100 */ \
  HWA_DECL(NVIC_ISER1, u32, HWA_PTR_NVIC+0x004, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E104 */ \
  HWA_DECL(NVIC_ISER2, u32, HWA_PTR_NVIC+0x008, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E108 */ \
  HWA_DECL(NVIC_ISPR0, u32, HWA_PTR_NVIC+0x100, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E200 */ \
  HWA_DECL(NVIC_ISPR1, u32, HWA_PTR_NVIC+0x104, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E204 */ \
  HWA_DECL(NVIC_ISPR2, u32, HWA_PTR_NVIC+0x108, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E208 */ \
  HWA_DECL(NVIC_IPR0,  u32, HWA_PTR_NVIC+0x300, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E400 */ \
  HWA_DECL(NVIC_IPR1,  u32, HWA_PTR_NVIC+0x304, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E404 */ \
  HWA_DECL(NVIC_IPR2,  u32, HWA_PTR_NVIC+0x308, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E408 */ \
  HWA_DECL(NVIC_IPR3,  u32, HWA_PTR_NVIC+0x30C, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E40C */ \
  HWA_DECL(NVIC_IPR4,  u32, HWA_PTR_NVIC+0x310, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E410 */ \
  HWA_DECL(NVIC_IPR5,  u32, HWA_PTR_NVIC+0x314, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E414 */ \
  HWA_DECL(NVIC_IPR6,  u32, HWA_PTR_NVIC+0x318, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E418 */ \
  HWA_DECL(NVIC_IPR7,  u32, HWA_PTR_NVIC+0x31C, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E41C */ \
  HWA_DECL(NVIC_IPR8,  u32, HWA_PTR_NVIC+0x320, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E420 */ \
  HWA_DECL(NVIC_IPR9,  u32, HWA_PTR_NVIC+0x324, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E424 */ \
  HWA_DECL(NVIC_IPR10, u32, HWA_PTR_NVIC+0x328, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E428 */ \
  HWA_DECL(NVIC_IPR11, u32, HWA_PTR_NVIC+0x32C, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E42C */ \
  HWA_DECL(NVIC_IPR12, u32, HWA_PTR_NVIC+0x330, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E430 */

#if 0
HWA_DECL(NVIC_ICER_0, u32, HWA_PTR_NVIC+0x080, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E180 */
HWA_DECL(NVIC_ICER_1, u32, HWA_PTR_NVIC+0x084, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E184 */
HWA_DECL(NVIC_ICER_2, u32, HWA_PTR_NVIC+0x088, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E188 */
HWA_DECL(NVIC_ICPR_0, u32, HWA_PTR_NVIC+0x180, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E280 */
HWA_DECL(NVIC_ICPR_1, u32, HWA_PTR_NVIC+0x184, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E284 */
HWA_DECL(NVIC_ICPR_2, u32, HWA_PTR_NVIC+0x188, 0x00000000, 0xFFFFFFFF, state) /* 0xE000E288 */
#endif

#define hwa_irq_commit()			\
  HWA_COMMIT(NVIC_ISER0)			\
  HWA_COMMIT(NVIC_ISER1)			\
  HWA_COMMIT(NVIC_ISER2)			\
  HWA_COMMIT(NVIC_ISPR0)			\
  HWA_COMMIT(NVIC_ISPR1)			\
  HWA_COMMIT(NVIC_ISPR2)			\
  HWA_COMMIT(NVIC_IPR0)			\
  HWA_COMMIT(NVIC_IPR1)			\
  HWA_COMMIT(NVIC_IPR2)			\
  HWA_COMMIT(NVIC_IPR3)			\
  HWA_COMMIT(NVIC_IPR4)			\
  HWA_COMMIT(NVIC_IPR5)			\
  HWA_COMMIT(NVIC_IPR6)			\
  HWA_COMMIT(NVIC_IPR7)			\
  HWA_COMMIT(NVIC_IPR8)			\
  HWA_COMMIT(NVIC_IPR9)			\
  HWA_COMMIT(NVIC_IPR10)			\
  HWA_COMMIT(NVIC_IPR11)			\
  HWA_COMMIT(NVIC_IPR12)


#define _hwa_turn_irq(pname, state)			\
  _hwa_turn_irqn(HWA_IRQN_##pname, HWA_STATE_##state)

#define _hwa_turn_irqn(irqn, state)					\
  if (irqn < 32)      { HWA_SET(NVIC_ISER0, 0b1, ((irqn)   &0x1f), state); } \
  else if (irqn < 64) { HWA_SET(NVIC_ISER1, 0b1, ((irqn-32)&0x1f), state); } \
  else if (irqn < 68) { HWA_SET(NVIC_ISER2, 0b1, ((irqn-64)&0x1f), state); } \
  else { HWA_ERROR_CT(1, "Bad irq number."); }


#define _hwa_irq_fire_irqn(irqn)					\
  if (irqn < 32)      { HWA_SET(NVIC_ISPR0, 0b1, irqn     &0x1f, state; } \
  else if (irqn < 64) { HWA_SET(NVIC_ISPR1, 0b1, (irqn-32)&0x1f, state; } \
  else if (irqn < 68) { HWA_SET(NVIC_ISPR2, 0b1, (irqn-64)&0x1f, state; } \
  else { HWA_ERROR_CT(1, "Bad irq number."); }


#define _hwa_irq_clr_irqn(irqn)						\
  if (irqn < 32)      { HWA_SET(NVIC_ICPR0, 0b1, irqn     &0x1f, state; } \
  else if (irqn < 64) { HWA_SET(NVIC_ICPR1, 0b1, (irqn-32)&0x1f, state; } \
  else if (irqn < 68) { HWA_SET(NVIC_ICPR2, 0b1, (irqn-64)&0x1f, state; } \
  else { HWA_ERROR_CT(1, "Bad irq number."); }


/* The STM32 only implements 16 levels of priority so only four bits of this
 * field are active. However it is important to note that the priority is set by
 * the four most significant bits.
 */
#define _hwa_set_irq_priority(pname, priority)				\
  _hwa_set_ipr_n(HWA_IRQN_##pname / 4, 8*(HWA_IRQN_##pname % 4), priority << 4)

#define _hwa_set_ipr_n(regn, shift, priority)				\
  if ( regn == 0 )       { HWA_SET(NVIC_IPR0,  0xff, shift, priority); } \
  else if ( regn == 1 )  { HWA_SET(NVIC_IPR1,  0xff, shift, priority); } \
  else if ( regn == 2 )  { HWA_SET(NVIC_IPR2,  0xff, shift, priority); } \
  else if ( regn == 3 )  { HWA_SET(NVIC_IPR3,  0xff, shift, priority); } \
  else if ( regn == 4 )  { HWA_SET(NVIC_IPR4,  0xff, shift, priority); } \
  else if ( regn == 5 )  { HWA_SET(NVIC_IPR5,  0xff, shift, priority); } \
  else if ( regn == 6 )  { HWA_SET(NVIC_IPR6,  0xff, shift, priority); } \
  else if ( regn == 7 )  { HWA_SET(NVIC_IPR7,  0xff, shift, priority); } \
  else if ( regn == 8 )  { HWA_SET(NVIC_IPR8,  0xff, shift, priority); } \
  else if ( regn == 9 )  { HWA_SET(NVIC_IPR9,  0xff, shift, priority); } \
  else if ( regn == 10 ) { HWA_SET(NVIC_IPR10, 0xff, shift, priority); } \
  else if ( regn == 11 ) { HWA_SET(NVIC_IPR11, 0xff, shift, priority); } \
  else if ( regn == 12 ) { HWA_SET(NVIC_IPR12, 0xff, shift, priority); } \
  else { HWA_ERROR_CT(1, "Bad register number."); }

#endif
