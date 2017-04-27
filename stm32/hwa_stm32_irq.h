#ifndef HWA_STM32_IRQ_H
#define HWA_STM32_IRQ_H

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_NVIC0_BASE		0xE000E100

#define HWA_NVIC_HWA_ISER0	volatile, u32, 0x000, 0x00000000, 0xFFFFFFFF	/* 0xE000E100 */
#define HWA_NVIC_HWA_ISER1	volatile, u32, 0x004, 0x00000000, 0xFFFFFFFF	/* 0xE000E104 */
#define HWA_NVIC_HWA_ISER2	volatile, u32, 0x008, 0x00000000, 0xFFFFFFFF	/* 0xE000E108 */
#define HWA_NVIC_HWA_ICER0	volatile, u32, 0x080, 0x00000000, 0xFFFFFFFF	/* 0xE000E180 */
#define HWA_NVIC_HWA_ICER1	volatile, u32, 0x084, 0x00000000, 0xFFFFFFFF	/* 0xE000E184 */
#define HWA_NVIC_HWA_ICER2	volatile, u32, 0x088, 0x00000000, 0xFFFFFFFF	/* 0xE000E188 */
#define HWA_NVIC_HWA_ISPR0	volatile, u32, 0x100, 0x00000000, 0xFFFFFFFF	/* 0xE000E200 */
#define HWA_NVIC_HWA_ISPR1	volatile, u32, 0x104, 0x00000000, 0xFFFFFFFF	/* 0xE000E204 */
#define HWA_NVIC_HWA_ISPR2	volatile, u32, 0x108, 0x00000000, 0xFFFFFFFF	/* 0xE000E208 */
#define HWA_NVIC_HWA_ICPR0	volatile, u32, 0x180, 0x00000000, 0xFFFFFFFF	/* 0xE000E280 */
#define HWA_NVIC_HWA_ICPR1	volatile, u32, 0x184, 0x00000000, 0xFFFFFFFF	/* 0xE000E284 */
#define HWA_NVIC_HWA_ICPR2	volatile, u32, 0x188, 0x00000000, 0xFFFFFFFF	/* 0xE000E288 */
#define HWA_NVIC_HWA_IPR0	volatile, u32, 0x300, 0x00000000, 0xFFFFFFFF	/* 0xE000E400 */
#define HWA_NVIC_HWA_IPR1	volatile, u32, 0x304, 0x00000000, 0xFFFFFFFF	/* 0xE000E404 */
#define HWA_NVIC_HWA_IPR2	volatile, u32, 0x308, 0x00000000, 0xFFFFFFFF	/* 0xE000E408 */
#define HWA_NVIC_HWA_IPR3	volatile, u32, 0x30C, 0x00000000, 0xFFFFFFFF	/* 0xE000E40C */
#define HWA_NVIC_HWA_IPR4	volatile, u32, 0x310, 0x00000000, 0xFFFFFFFF	/* 0xE000E410 */
#define HWA_NVIC_HWA_IPR5	volatile, u32, 0x314, 0x00000000, 0xFFFFFFFF	/* 0xE000E414 */
#define HWA_NVIC_HWA_IPR6	volatile, u32, 0x318, 0x00000000, 0xFFFFFFFF	/* 0xE000E418 */
#define HWA_NVIC_HWA_IPR7	volatile, u32, 0x31C, 0x00000000, 0xFFFFFFFF	/* 0xE000E41C */
#define HWA_NVIC_HWA_IPR8	volatile, u32, 0x320, 0x00000000, 0xFFFFFFFF	/* 0xE000E420 */
#define HWA_NVIC_HWA_IPR9	volatile, u32, 0x324, 0x00000000, 0xFFFFFFFF	/* 0xE000E424 */
#define HWA_NVIC_HWA_IPR10	volatile, u32, 0x328, 0x00000000, 0xFFFFFFFF	/* 0xE000E428 */
#define HWA_NVIC_HWA_IPR11	volatile, u32, 0x32C, 0x00000000, 0xFFFFFFFF	/* 0xE000E42C */
#define HWA_NVIC_HWA_IPR12	volatile, u32, 0x330, 0x00000000, 0xFFFFFFFF	/* 0xE000E430 */
#define HWA_NVIC_HWA_IPR13	volatile, u32, 0x334, 0x00000000, 0xFFFFFFFF	/* 0xE000E434 */
#define HWA_NVIC_HWA_IPR14	volatile, u32, 0x338, 0x00000000, 0xFFFFFFFF	/* 0xE000E438 */
#define HWA_NVIC_HWA_IPR15	volatile, u32, 0x33C, 0x00000000, 0xFFFFFFFF	/* 0xE000E43C */
#define HWA_NVIC_HWA_IPR16	volatile, u32, 0x340, 0x00000000, 0xFFFFFFFF	/* 0xE000E440 */

#define HWA_IRQN_HWA_EXTI0	6
#define HWA_IRQN_HWA_TIMER2	28
#define HWA_IRQN_HWA_TIMER3	29
#define HWA_IRQN_HWA_SPI1	35
#define HWA_IRQN_HWA_SPI2	36
#define HWA_IRQN_HWA_UART1	37
#define HWA_IRQN_HWA_EXTI15_10	40
#define HWA_IRQN_HWA_SPI3	51

#define HWA_IRQN_ALL		0xFFFF


typedef struct {
  HWA_PDCL()
  HWA_VDCL(HWA_NVIC, HWA_ISER0);
  HWA_VDCL(HWA_NVIC, HWA_ISER1);
  HWA_VDCL(HWA_NVIC, HWA_ISER2);
  HWA_VDCL(HWA_NVIC, HWA_ICER0);
  HWA_VDCL(HWA_NVIC, HWA_ICER1);
  HWA_VDCL(HWA_NVIC, HWA_ICER2);
  HWA_VDCL(HWA_NVIC, HWA_ISPR0);
  HWA_VDCL(HWA_NVIC, HWA_ISPR1);
  HWA_VDCL(HWA_NVIC, HWA_ISPR2);
  HWA_VDCL(HWA_NVIC, HWA_ICPR0);
  HWA_VDCL(HWA_NVIC, HWA_ICPR1);
  HWA_VDCL(HWA_NVIC, HWA_ICPR2);
  HWA_VDCL(HWA_NVIC, HWA_IPR0 );
  HWA_VDCL(HWA_NVIC, HWA_IPR1 );
  HWA_VDCL(HWA_NVIC, HWA_IPR2 );
  HWA_VDCL(HWA_NVIC, HWA_IPR3 );
  HWA_VDCL(HWA_NVIC, HWA_IPR4 );
  HWA_VDCL(HWA_NVIC, HWA_IPR5 );
  HWA_VDCL(HWA_NVIC, HWA_IPR6 );
  HWA_VDCL(HWA_NVIC, HWA_IPR7 );
  HWA_VDCL(HWA_NVIC, HWA_IPR8 );
  HWA_VDCL(HWA_NVIC, HWA_IPR9 );
  HWA_VDCL(HWA_NVIC, HWA_IPR10);
  HWA_VDCL(HWA_NVIC, HWA_IPR11);
  HWA_VDCL(HWA_NVIC, HWA_IPR12);
  HWA_VDCL(HWA_NVIC, HWA_IPR13);
  HWA_VDCL(HWA_NVIC, HWA_IPR14);
  HWA_VDCL(HWA_NVIC, HWA_IPR15);
  HWA_VDCL(HWA_NVIC, HWA_IPR16);
} HWA_NVIC ;

#define hwa_begin_irq(reset)					\
  HWA_PINIT(HWA_NVIC, HWA_NVIC0);				\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_ISER0, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_ISER1, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_ISER2, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_ICER0, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_ICER1, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_ICER2, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_ISPR0, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_ISPR1, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_ISPR2, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_ICPR0, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_ICPR1, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_ICPR2, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR0 , reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR1 , reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR2 , reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR3 , reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR4 , reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR5 , reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR6 , reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR7 , reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR8 , reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR9 , reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR10, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR11, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR12, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR13, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR14, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR15, reset);		\
  HWA_VINIT(HWA_NVIC, HWA_NVIC0, HWA_IPR16, reset);

#define hwa_commit_irq()					\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_ISER0);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_ISER1);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_ISER2);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_ICER0);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_ICER1);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_ICER2);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_ISPR0);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_ISPR1);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_ISPR2);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_ICPR0);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_ICPR1);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_ICPR2);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR0 );		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR1 );		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR2 );		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR3 );		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR4 );		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR5 );		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR6 );		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR7 );		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR8 );		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR9 );		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR10);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR11);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR12);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR13);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR14);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR15);		\
  HWA_COMMIT(HWA_CORE0, HWA_NVIC, HWA_NVIC0, HWA_IPR16);


/************************************************************************
 *									*
 *			User definitions				*
 *									*
 ************************************************************************/

#define HWA_ISR(mname, pname, flags)					\
  static void HWA_G2(ISR, pname)(u16 flags);				\
  void HWA_G2(HWA_ISR, pname)() {					\
    u16 sr = HW_HR(mname, pname, HWA_SR) ;				\
    HW_HR(mname, pname, HWA_SR) = 0 ;					\
    HWA_G2(ISR, pname)(sr) ;						\
  }									\
  static void HWA_G2(ISR, pname)(u16 flags __attribute__((unused)))


/************************************************************************
 *									*
 *			Synchronous actions				*
 *									*
 ************************************************************************/

#define hw_irq_turn(pname, state)					\
  do {									\
    u16 irqn = HWA_G2(HWA_IRQN, pname) ;				\
    if ( HWA_STATE_##state == HWA_STATE_ON ) {				\
      if (irqn < 32)							\
	HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ISER0) = 0b1<<(irqn % 32);	\
      else if (irqn < 64)						\
	HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ISER1) = 0b1<<(irqn % 32);	\
      else if (irqn < 68)						\
	HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ISER2) = 0b1<<(irqn % 32);	\
      else if (irqn == 0xFFFF) {					\
	HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ISER0) = 0xFFFFFFFF ;		\
	HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ISER1) = 0xFFFFFFFF ;		\
	HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ISER2) = 0xFFFFFFFF ;		\
      }									\
      else								\
	HWA_ERROR("Bad irq number.");					\
    }									\
    else {								\
      if (irqn < 32)							\
	HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ICER0) = 0b1<<(irqn % 32);	\
      else if (irqn < 64)						\
	HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ICER1) = 0b1<<(irqn % 32);	\
      else if (irqn < 68)						\
	HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ICER2) = 0b1<<(irqn % 32);	\
      else if (irqn == 0xFFFF) {					\
	HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ICER0) = 0xFFFFFFFF ;		\
	HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ICER1) = 0xFFFFFFFF ;		\
	HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ICER2) = 0xFFFFFFFF ;		\
      }									\
      else								\
	HWA_ERROR("Bad irq number.");					\
    }									\
  } while(0)


#define hw_irq_clear(pname)						\
  do {									\
    u16 irqn = HWA_G2(HWA_IRQN, pname) ;				\
    if (irqn < 32)							\
      HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ICPR0) = 0b1<<(irqn % 32);	\
    else if (irqn < 64)							\
      HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ICPR1) = 0b1<<(irqn % 32);	\
    else if (irqn < 68)							\
      HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ICPR2) = 0b1<<(irqn % 32);	\
    else if (irqn == 0xFFFF) {						\
      HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ICPR0) = 0xFFFFFFFF ;		\
      HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ICPR1) = 0xFFFFFFFF ;		\
      HW_HR(HWA_NVIC, HWA_NVIC0, HWA_ICPR2) = 0xFFFFFFFF ;		\
    }									\
    else								\
      HWA_ERROR("Bad irq number.");					\
  } while(0)


#define hw_irq_set_priority(pname, priority)				\
  do {									\
    if ( priority < 0 || priority > 15)					\
      HWA_ERROR("priority out of range 0..15");				\
    u8 *r = (u8*)HW_HA(HWA_NVIC, HWA_NVIC0, HWA_IPR0) + HWA_G2(HWA_IRQN, pname); \
    *r = priority ;							\
  } while (0)



/************************************************************************
 *									*
 *			Asynchronous actions				*
 *									*
 ************************************************************************/

#define hwa_irq_turn(pname, state)					\
  do {									\
    u16 irqn = HWA_G2(HWA_IRQN, pname) ;				\
    if ( HWA_STATE_##state == HWA_STATE_ON ) {				\
      if (irqn < 32)							\
	HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ISER0, 0b1, ((irqn)   &0x1f), 1); \
      else if (irqn < 64)						\
	HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ISER1, 0b1, (irqn-32)&0x1f, 1); \
      else if (irqn < 68)						\
	HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ISER2, 0b1, (irqn-64)&0x1f, 1); \
      else if (irqn == 0xFFFF) {					\
	HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ISER0, 0xFFFFFFFF, 0, 0xFFFFFFFF); \
	HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ISER1, 0xFFFFFFFF, 0, 0xFFFFFFFF); \
	HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ISER2, 0xFFFFFFFF, 0, 0xFFFFFFFF); \
      }									\
      else								\
	HWA_ERROR("Bad irq number.");					\
    }									\
    else {								\
      if (irqn < 32)							\
	HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ICER0, 0b1, ((irqn)   &0x1f), 1); \
      else if (irqn < 64)						\
	HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ICER1, 0b1, (irqn-32)&0x1f, 1); \
      else if (irqn < 68)						\
	HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ICER2, 0b1, (irqn-64)&0x1f, 1); \
      else if (irqn == 0xFFFF) {					\
	HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ICER0, 0xFFFFFFFF, 0, 0xFFFFFFFF); \
	HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ICER1, 0xFFFFFFFF, 0, 0xFFFFFFFF); \
	HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ICER2, 0xFFFFFFFF, 0, 0xFFFFFFFF); \
      }									\
      else								\
	HWA_ERROR("Bad irq number.");					\
    }									\
  } while(0)


#define hwa_irq_clear(pname)						\
  do {									\
    u16 irqn = HWA_G2(HWA_IRQN, pname) ;				\
    if (irqn < 32)							\
      HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ICPR0, 0b1, ((irqn)   &0x1f), 1); \
    else if (irqn < 64)							\
      HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ICPR1, 0b1, (irqn-32)&0x1f, 1); \
    else if (irqn < 68)							\
      HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ICPR2, 0b1, (irqn-64)&0x1f, 1); \
    else if (irqn == 0xFFFF) {						\
      HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ICPR0, 0xFFFFFFFF, 0, 0xFFFFFFFF); \
      HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ICPR1, 0xFFFFFFFF, 0, 0xFFFFFFFF); \
      HWA_SETVB(HWA_NVIC, HWA_NVIC0, HWA_ICPR2, 0xFFFFFFFF, 0, 0xFFFFFFFF); \
    }									\
    else								\
      HWA_ERROR("Bad irq number.");					\
  } while(0)


#endif
