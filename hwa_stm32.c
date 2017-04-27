
/*	This file is included by hwa.c
*/

void
ESR_RESET ( )
{
  /*	STM32 bug : when booting from RAM, SP is not loaded.
   */
  /*	When booting from SRAM, in the application initialization code, you have
   *	to relocate the vector table in SRAM using the NVIC exception table and
   *	offset register.
   */
#ifdef RUN_FROM_RAM
  if ( (((u32)isr_vector) & 0xFF000000) == 0x20000000 ) {
    __asm__ volatile("mov sp,%0" : : "r"(isr_vector[0]));
    *HWA_PTR_SCB_VTOR = (u32)isr_vector;
  }
#endif

  /*	Zero fill the bss segment.
   */
#ifdef ZERO_ALL_RAM
  for ( u32 *p = (u32*)0x02000000 ; p < (u32*)0x20050000 ; p++ )
    *p = 0 ;
#else
  for ( u32 *p = &_sbss ; p < &_ebss ; p++ )
    *p = 0 ;
#endif

#ifndef NO_DATA_INIT
  /*	Copy the data segment initializers from flash to SRAM.
   *	This is not useful if the .data section is empty but since it is
   *	impossible to know if it is empty or not at compile time (the values of
   *	_edata and _sdata will be known after linking) the compiler can not
   *	decide itself to discard this code.
   */
  for ( u32 *src = &_sidata, *dst = &_sdata ;
	dst < &_edata ;
	src++, dst++ )
    *dst = *src ;
#endif

  main();
  exit(1);
}


/*	Exceptions
 */
void WEAK ESR_NMI(void)			ESR(1)
void WEAK ESR_HARD_FAULT(void)		ESR(2)
void WEAK ESR_MEM_MANAGE(void)		ESR(3)
void WEAK ESR_BUS_FAULT(void)		ESR(4)
void WEAK ESR_USAGE_FAULT(void)		ESR(5)
void WEAK ESR_SV_CALL(void)		ESR(6)
void WEAK ESR_DEBUG_MONITOR(void)	ESR(7)
void WEAK ESR_PEND_SV(void)		ESR(8)
void WEAK ESR_SYSTICK(void)		ESR(9)


/*	Interrupts
 */
void WEAK ISR_WWDG(void)		ISR(0)
void WEAK ISR_PVD(void)			ISR(1)
void WEAK ISR_TAMPER(void)		ISR(2)
void WEAK ISR_RTC(void)			ISR(3)
void WEAK ISR_FLASH(void)		ISR(4)
void WEAK ISR_RCC(void)			ISR(5)
void WEAK ISR_EXTI0(void)		ISR(6)
void WEAK ISR_EXTI1(void)		ISR(7)
void WEAK ISR_EXTI2(void)		ISR(8)
void WEAK ISR_EXTI3(void)		ISR(9)
void WEAK ISR_EXTI4(void)		ISR(10)
void WEAK ISR_DMA1_CHANNEL1(void)	ISR(11)
void WEAK ISR_DMA1_CHANNEL2(void)	ISR(12)
void WEAK ISR_DMA1_CHANNEL3(void)	ISR(13)
void WEAK ISR_DMA1_CHANNEL4(void)	ISR(14)
void WEAK ISR_DMA1_CHANNEL5(void)	ISR(15)
void WEAK ISR_DMA1_CHANNEL6(void)	ISR(16)
void WEAK ISR_DMA1_CHANNEL7(void)	ISR(17)
void WEAK ISR_ADC1_2(void)		ISR(18)
void WEAK ISR_USB_HP_CAN_TX(void)	ISR(19)
void WEAK ISR_USB_LP_CAN_RX0(void)	ISR(20)
void WEAK ISR_CAN_RX1(void)		ISR(21)
void WEAK ISR_CAN_SCE(void)		ISR(22)
void WEAK ISR_EXTI9_5(void)		ISR(23)
void WEAK ISR_TIM1_BRK(void)		ISR(24)
void WEAK ISR_TIM1_UP(void)		ISR(25)
void WEAK ISR_TIM1_TRG_COM(void)	ISR(26)
void WEAK ISR_TIM1_CC(void)		ISR(27)
void WEAK ISR_TIM2(void)		ISR(28)
void WEAK ISR_TIM3(void)		ISR(29)
void WEAK ISR_TIM4(void)		ISR(30)
void WEAK ISR_I2C1_EV(void)		ISR(31)
void WEAK ISR_I2C1_ER(void)		ISR(32)
void WEAK ISR_I2C2_EV(void)		ISR(33)
void WEAK ISR_I2C2_ER(void)		ISR(34)
void WEAK ISR_SPI1(void)		ISR(35)
void WEAK ISR_SPI2(void)		ISR(36)
void WEAK ISR_USART1(void)		ISR(37)
void WEAK ISR_USART2(void)		ISR(38)
void WEAK ISR_USART3(void)		ISR(39)
void WEAK ISR_EXTI15_10(void)		ISR(40)
void WEAK ISR_RTC_ALARM(void)		ISR(41)
void WEAK ISR_USB_WAKEUP(void)		ISR(42)
void WEAK ISR_TIM8_BRK(void)		ISR(43)
void WEAK ISR_TIM8_UP(void)		ISR(44)
void WEAK ISR_TIM8_TRG_COM(void)	ISR(45)
void WEAK ISR_TIM8_CC(void)		ISR(46)
void WEAK ISR_ADC3(void)		ISR(47)
void WEAK ISR_FSMC(void)		ISR(48)
void WEAK ISR_SDIO(void)		ISR(49)
void WEAK ISR_TIM5(void)		ISR(50)
void WEAK ISR_SPI3(void)		ISR(51)
void WEAK ISR_USART4(void)		ISR(52)
void WEAK ISR_USART5(void)		ISR(53)
void WEAK ISR_TIM6(void)		ISR(54)
void WEAK ISR_TIM7(void)		ISR(55)
void WEAK ISR_DMA2_CHANNEL1(void)	ISR(56)
void WEAK ISR_DMA2_CHANNEL2(void)	ISR(57)
void WEAK ISR_DMA2_CHANNEL3(void)	ISR(58)
void WEAK ISR_DMA2_CHANNEL4_5(void)	ISR(59)


__attribute__ ((section(".vectors")))
void (*const isr_vector[]) (void) = {

  /*	Exceptions
   */
  (void *)0x20005000,	/* "Use 2KB stack (0x800 bytes)." */
  ESR_RESET,		/* Use main() as reset vector for now. */

  ESR_NMI,
  ESR_HARD_FAULT,
  ESR_MEM_MANAGE,
  ESR_BUS_FAULT,
  ESR_USAGE_FAULT,
  0, 0, 0, 0,		/* Reserved */
  ESR_SV_CALL,
  ESR_DEBUG_MONITOR,
  0,			/* Reserved */
  ESR_PEND_SV,
  ESR_SYSTICK,

  /*	Interrupts
   */
  ISR_WWDG,		/* IRQ 0 */
  ISR_PVD,		/* IRQ 1 */
  ISR_TAMPER,		/* IRQ 2 */
  ISR_RTC,		/* IRQ 3 */
  ISR_FLASH,		/* IRQ 4 */
  ISR_RCC,		/* IRQ 5 */
  ISR_EXTI0,		/* IRQ 6 */
  ISR_EXTI1,		/* IRQ 7 */
  ISR_EXTI2,		/* IRQ 8 */
  ISR_EXTI3,		/* IRQ 9 */
  ISR_EXTI4,		/* IRQ 10 */
  ISR_DMA1_CHANNEL1,	/* IRQ 11 */
  ISR_DMA1_CHANNEL2,	/* IRQ 12 */
  ISR_DMA1_CHANNEL3,	/* IRQ 13 */
  ISR_DMA1_CHANNEL4,	/* IRQ 14 */
  ISR_DMA1_CHANNEL5,	/* IRQ 15 */
  ISR_DMA1_CHANNEL6,	/* IRQ 16 */
  ISR_DMA1_CHANNEL7,	/* IRQ 17 */
  ISR_ADC1_2,		/* IRQ 18 */
  ISR_USB_HP_CAN_TX,	/* IRQ 19 */
  ISR_USB_LP_CAN_RX0,	/* IRQ 20 */
  ISR_CAN_RX1,		/* IRQ 21 */
  ISR_CAN_SCE,		/* IRQ 22 */
  ISR_EXTI9_5,		/* IRQ 23 */
  ISR_TIM1_BRK,		/* IRQ 24 */
  ISR_TIM1_UP,		/* IRQ 25 */
  ISR_TIM1_TRG_COM,	/* IRQ 26 */
  ISR_TIM1_CC,		/* IRQ 27 */
  ISR_TIM2,		/* IRQ 28 */
  ISR_TIM3,		/* IRQ 29 */
  ISR_TIM4,		/* IRQ 30 */
  ISR_I2C1_EV,		/* IRQ 31 */
  ISR_I2C1_ER,		/* IRQ 32 */
  ISR_I2C2_EV,		/* IRQ 33 */
  ISR_I2C2_ER,		/* IRQ 34 */
  ISR_SPI1,		/* IRQ 35 */
  ISR_SPI2,		/* IRQ 36 */
  ISR_USART1,		/* IRQ 37 */
  ISR_USART2,		/* IRQ 38 */
  ISR_USART3,		/* IRQ 39 */
  ISR_EXTI15_10,	/* IRQ 40 */
  ISR_RTC_ALARM,	/* IRQ 41 */
  ISR_USB_WAKEUP,	/* IRQ 42 */
  ISR_TIM8_BRK,		/* IRQ 43 */
  ISR_TIM8_UP,		/* IRQ 44 */
  ISR_TIM8_TRG_COM,	/* IRQ 45 */
  ISR_TIM8_CC,		/* IRQ 46 */
  ISR_ADC3,		/* IRQ 47 */
  ISR_FSMC,		/* IRQ 48 */
  ISR_SDIO,		/* IRQ 49 */
#ifdef RUN_FROM_RAM
  (void*)0xF108F85F,	/* @0x0108: workaround for boot issue in RAM mode. */
#else
  ISR_TIM5,		/* IRQ 50 */
#endif
  ISR_SPI3,		/* IRQ 51 */
  ISR_USART4,		/* IRQ 52 */
  ISR_USART5,		/* IRQ 53 */
  ISR_TIM6,		/* IRQ 54 */
  ISR_TIM7,		/* IRQ 55 */
  ISR_DMA2_CHANNEL1,	/* IRQ 56 */
  ISR_DMA2_CHANNEL2,	/* IRQ 57 */
  ISR_DMA2_CHANNEL3,	/* IRQ 58 */
  ISR_DMA2_CHANNEL4_5,	/* IRQ 59 */
};


#if ISR_DEFAULT == ISR_DEFAULT_EXIT
#pragma weak ESR_NMI			= ISR_EXIT
#pragma weak ESR_HARD_FAULT		= ISR_EXIT
#pragma weak ESR_MEM_MANAGE		= ISR_EXIT
#pragma weak ESR_BUS_FAULT		= ISR_EXIT
#pragma weak ESR_USAGE_FAULT		= ISR_EXIT
#pragma weak ESR_SV_CALL		= ISR_EXIT
#pragma weak ESR_DEBUG_MONITOR		= ISR_EXIT
#pragma weak ESR_PEND_SV		= ISR_EXIT
#pragma weak ESR_SYSTICK		= ISR_EXIT

#pragma weak ISR_WWDG			= ISR_EXIT
#pragma weak ISR_PVD			= ISR_EXIT
#pragma weak ISR_TAMPER			= ISR_EXIT
#pragma weak ISR_RTC			= ISR_EXIT
#pragma weak ISR_FLASH			= ISR_EXIT
#pragma weak ISR_RCC			= ISR_EXIT
#pragma weak ISR_EXTI0			= ISR_EXIT
#pragma weak ISR_EXTI1			= ISR_EXIT
#pragma weak ISR_EXTI2			= ISR_EXIT
#pragma weak ISR_EXTI3			= ISR_EXIT
#pragma weak ISR_EXTI4			= ISR_EXIT
#pragma weak ISR_DMA1_CHANNEL1		= ISR_EXIT
#pragma weak ISR_DMA1_CHANNEL2		= ISR_EXIT
#pragma weak ISR_DMA1_CHANNEL3		= ISR_EXIT
#pragma weak ISR_DMA1_CHANNEL4		= ISR_EXIT
#pragma weak ISR_DMA1_CHANNEL5		= ISR_EXIT
#pragma weak ISR_DMA1_CHANNEL6		= ISR_EXIT
#pragma weak ISR_DMA1_CHANNEL7		= ISR_EXIT
#pragma weak ISR_ADC1_2			= ISR_EXIT
#pragma weak ISR_USB_HP_CAN_TX		= ISR_EXIT
#pragma weak ISR_USB_LP_CAN_RX0		= ISR_EXIT
#pragma weak ISR_CAN_RX1		= ISR_EXIT
#pragma weak ISR_CAN_SCE		= ISR_EXIT
#pragma weak ISR_EXTI9_5		= ISR_EXIT
#pragma weak ISR_TIM1_BRK		= ISR_EXIT
#pragma weak ISR_TIM1_UP		= ISR_EXIT
#pragma weak ISR_TIM1_TRG_COM		= ISR_EXIT
#pragma weak ISR_TIM1_CC		= ISR_EXIT
#pragma weak ISR_TIM2			= ISR_EXIT
#pragma weak ISR_TIM3			= ISR_EXIT
#pragma weak ISR_TIM4			= ISR_EXIT
#pragma weak ISR_I2C1_EV		= ISR_EXIT
#pragma weak ISR_I2C1_ER		= ISR_EXIT
#pragma weak ISR_I2C2_EV		= ISR_EXIT
#pragma weak ISR_I2C2_ER		= ISR_EXIT
#pragma weak ISR_SPI1			= ISR_EXIT
#pragma weak ISR_SPI2			= ISR_EXIT
#pragma weak ISR_USART1			= ISR_EXIT
#pragma weak ISR_USART2			= ISR_EXIT
#pragma weak ISR_USART3			= ISR_EXIT
#pragma weak ISR_EXTI15_10		= ISR_EXIT
#pragma weak ISR_RTC_ALARM		= ISR_EXIT
#pragma weak ISR_USB_WAKEUP		= ISR_EXIT
#pragma weak ISR_TIM8_BRK		= ISR_EXIT
#pragma weak ISR_TIM8_UP		= ISR_EXIT
#pragma weak ISR_TIM8_TRG_COM		= ISR_EXIT
#pragma weak ISR_TIM8_CC		= ISR_EXIT
#pragma weak ISR_ADC3			= ISR_EXIT
#pragma weak ISR_FSMC			= ISR_EXIT
#pragma weak ISR_SDIO			= ISR_EXIT
#pragma weak ISR_TIM5			= ISR_EXIT
#pragma weak ISR_SPI3			= ISR_EXIT
#pragma weak ISR_USART4			= ISR_EXIT
#pragma weak ISR_USART5			= ISR_EXIT
#pragma weak ISR_TIM6			= ISR_EXIT
#pragma weak ISR_TIM7			= ISR_EXIT
#pragma weak ISR_DMA2_CHANNEL1		= ISR_EXIT
#pragma weak ISR_DMA2_CHANNEL2		= ISR_EXIT
#pragma weak ISR_DMA2_CHANNEL3		= ISR_EXIT
#pragma weak ISR_DMA2_CHANNEL4_5	= ISR_EXIT
#endif
