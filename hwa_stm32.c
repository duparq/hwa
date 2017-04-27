
/*	This file is included by hwa.c
*/

void
esr_reset ( )
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
void WEAK esr_nmi(void)			ESR(1)
void WEAK esr_hard_fault(void)		ESR(2)
void WEAK esr_mem_manage(void)		ESR(3)
void WEAK esr_bus_fault(void)		ESR(4)
void WEAK esr_usage_fault(void)		ESR(5)
void WEAK esr_sv_call(void)		ESR(6)
void WEAK esr_debug_monitor(void)	ESR(7)
void WEAK esr_pend_sv(void)		ESR(8)
void WEAK esr_systick(void)		ESR(9)


/*	Interrupts
 */
void WEAK isr_wwdg(void)		ISR(0)
void WEAK isr_pvd(void)			ISR(1)
void WEAK isr_tamper(void)		ISR(2)
void WEAK isr_rtc(void)			ISR(3)
void WEAK isr_flash(void)		ISR(4)
void WEAK isr_rcc(void)			ISR(5)
void WEAK isr_exti0(void)		ISR(6)
void WEAK isr_exti1(void)		ISR(7)
void WEAK isr_exti2(void)		ISR(8)
void WEAK isr_exti3(void)		ISR(9)
void WEAK isr_exti4(void)		ISR(10)
void WEAK isr_dma1_channel1(void)	ISR(11)
void WEAK isr_dma1_channel2(void)	ISR(12)
void WEAK isr_dma1_channel3(void)	ISR(13)
void WEAK isr_dma1_channel4(void)	ISR(14)
void WEAK isr_dma1_channel5(void)	ISR(15)
void WEAK isr_dma1_channel6(void)	ISR(16)
void WEAK isr_dma1_channel7(void)	ISR(17)
void WEAK isr_adc1_2(void)		ISR(18)
void WEAK isr_usb_hp_can_tx(void)	ISR(19)
void WEAK isr_usb_lp_can_rx0(void)	ISR(20)
void WEAK isr_can_rx1(void)		ISR(21)
void WEAK isr_can_sce(void)		ISR(22)
void WEAK isr_exti9_5(void)		ISR(23)
void WEAK isr_tim1_brk(void)		ISR(24)
void WEAK isr_tim1_up(void)		ISR(25)
void WEAK isr_tim1_trg_com(void)	ISR(26)
void WEAK isr_tim1_cc(void)		ISR(27)
void WEAK isr_tim2(void)		ISR(28)
void WEAK isr_tim3(void)		ISR(29)
void WEAK isr_tim4(void)		ISR(30)
void WEAK isr_i2c1_ev(void)		ISR(31)
void WEAK isr_i2c1_er(void)		ISR(32)
void WEAK isr_i2c2_ev(void)		ISR(33)
void WEAK isr_i2c2_er(void)		ISR(34)
void WEAK isr_spi1(void)		ISR(35)
void WEAK isr_spi2(void)		ISR(36)
void WEAK isr_usart1(void)		ISR(37)
void WEAK isr_usart2(void)		ISR(38)
void WEAK isr_usart3(void)		ISR(39)
void WEAK isr_exti15_10(void)		ISR(40)
void WEAK isr_rtc_alarm(void)		ISR(41)
void WEAK isr_usb_wakeup(void)		ISR(42)
void WEAK isr_tim8_brk(void)		ISR(43)
void WEAK isr_tim8_up(void)		ISR(44)
void WEAK isr_tim8_trg_com(void)	ISR(45)
void WEAK isr_tim8_cc(void)		ISR(46)
void WEAK isr_adc3(void)		ISR(47)
void WEAK isr_fsmc(void)		ISR(48)
void WEAK isr_sdio(void)		ISR(49)
void WEAK isr_tim5(void)		ISR(50)
void WEAK isr_spi3(void)		ISR(51)
void WEAK isr_usart4(void)		ISR(52)
void WEAK isr_usart5(void)		ISR(53)
void WEAK isr_tim6(void)		ISR(54)
void WEAK isr_tim7(void)		ISR(55)
void WEAK isr_dma2_channel1(void)	ISR(56)
void WEAK isr_dma2_channel2(void)	ISR(57)
void WEAK isr_dma2_channel3(void)	ISR(58)
void WEAK isr_dma2_channel4_5(void)	ISR(59)


__attribute__ ((section(".vectors")))
void (*const isr_vector[]) (void) = {

  /*	Exceptions
   */
  (void *)0x20005000,	/* Use 2KB stack (0x800 bytes). */
  esr_reset,		/* Use main() as reset vector for now. */

  esr_nmi,
  esr_hard_fault,
  esr_mem_manage,
  esr_bus_fault,
  esr_usage_fault,
  0, 0, 0, 0,		/* Reserved */
  esr_sv_call,
  esr_debug_monitor,
  0,			/* Reserved */
  esr_pend_sv,
  esr_systick,

  /*	Interrupts
   */
  isr_wwdg,		/* IRQ 0 */
  isr_pvd,		/* IRQ 1 */
  isr_tamper,		/* IRQ 2 */
  isr_rtc,		/* IRQ 3 */
  isr_flash,		/* IRQ 4 */
  isr_rcc,		/* IRQ 5 */
  isr_exti0,		/* IRQ 6 */
  isr_exti1,		/* IRQ 7 */
  isr_exti2,		/* IRQ 8 */
  isr_exti3,		/* IRQ 9 */
  isr_exti4,		/* IRQ 10 */
  isr_dma1_channel1,	/* IRQ 11 */
  isr_dma1_channel2,	/* IRQ 12 */
  isr_dma1_channel3,	/* IRQ 13 */
  isr_dma1_channel4,	/* IRQ 14 */
  isr_dma1_channel5,	/* IRQ 15 */
  isr_dma1_channel6,	/* IRQ 16 */
  isr_dma1_channel7,	/* IRQ 17 */
  isr_adc1_2,		/* IRQ 18 */
  isr_usb_hp_can_tx,	/* IRQ 19 */
  isr_usb_lp_can_rx0,	/* IRQ 20 */
  isr_can_rx1,		/* IRQ 21 */
  isr_can_sce,		/* IRQ 22 */
  isr_exti9_5,		/* IRQ 23 */
  isr_tim1_brk,		/* IRQ 24 */
  isr_tim1_up,		/* IRQ 25 */
  isr_tim1_trg_com,	/* IRQ 26 */
  isr_tim1_cc,		/* IRQ 27 */
  isr_tim2,		/* IRQ 28 */
  isr_tim3,		/* IRQ 29 */
  isr_tim4,		/* IRQ 30 */
  isr_i2c1_ev,		/* IRQ 31 */
  isr_i2c1_er,		/* IRQ 32 */
  isr_i2c2_ev,		/* IRQ 33 */
  isr_i2c2_er,		/* IRQ 34 */
  isr_spi1,		/* IRQ 35 */
  isr_spi2,		/* IRQ 36 */
  isr_usart1,		/* IRQ 37 */
  isr_usart2,		/* IRQ 38 */
  isr_usart3,		/* IRQ 39 */
  isr_exti15_10,	/* IRQ 40 */
  isr_rtc_alarm,	/* IRQ 41 */
  isr_usb_wakeup,	/* IRQ 42 */
  isr_tim8_brk,		/* IRQ 43 */
  isr_tim8_up,		/* IRQ 44 */
  isr_tim8_trg_com,	/* IRQ 45 */
  isr_tim8_cc,		/* IRQ 46 */
  isr_adc3,		/* IRQ 47 */
  isr_fsmc,		/* IRQ 48 */
  isr_sdio,		/* IRQ 49 */
#ifdef RUN_FROM_RAM
  (void*)0xF108F85F,	/* @0x0108: workaround for boot issue in RAM mode. */
#else
  isr_tim5,		/* IRQ 50 */
#endif
  isr_spi3,		/* IRQ 51 */
  isr_usart4,		/* IRQ 52 */
  isr_usart5,		/* IRQ 53 */
  isr_tim6,		/* IRQ 54 */
  isr_tim7,		/* IRQ 55 */
  isr_dma2_channel1,	/* IRQ 56 */
  isr_dma2_channel2,	/* IRQ 57 */
  isr_dma2_channel3,	/* IRQ 58 */
  isr_dma2_channel4_5,	/* IRQ 59 */
};


#if ISR_DEFAULT == ISR_DEFAULT_EXIT
#pragma weak esr_nmi			= isr_exit
#pragma weak esr_hard_fault		= isr_exit
#pragma weak esr_mem_manage		= isr_exit
#pragma weak esr_bus_fault		= isr_exit
#pragma weak esr_usage_fault		= isr_exit
#pragma weak esr_sv_call		= isr_exit
#pragma weak esr_debug_monitor		= isr_exit
#pragma weak esr_pend_sv		= isr_exit
#pragma weak esr_systick		= isr_exit

#pragma weak isr_wwdg			= isr_exit
#pragma weak isr_pvd			= isr_exit
#pragma weak isr_tamper			= isr_exit
#pragma weak isr_rtc			= isr_exit
#pragma weak isr_flash			= isr_exit
#pragma weak isr_rcc			= isr_exit
#pragma weak isr_exti0			= isr_exit
#pragma weak isr_exti1			= isr_exit
#pragma weak isr_exti2			= isr_exit
#pragma weak isr_exti3			= isr_exit
#pragma weak isr_exti4			= isr_exit
#pragma weak isr_dma1_channel1		= isr_exit
#pragma weak isr_dma1_channel2		= isr_exit
#pragma weak isr_dma1_channel3		= isr_exit
#pragma weak isr_dma1_channel4		= isr_exit
#pragma weak isr_dma1_channel5		= isr_exit
#pragma weak isr_dma1_channel6		= isr_exit
#pragma weak isr_dma1_channel7		= isr_exit
#pragma weak isr_adc1_2			= isr_exit
#pragma weak isr_usb_hp_can_tx		= isr_exit
#pragma weak isr_usb_lp_can_rx0		= isr_exit
#pragma weak isr_can_rx1		= isr_exit
#pragma weak isr_can_sce		= isr_exit
#pragma weak isr_exti9_5		= isr_exit
#pragma weak isr_tim1_brk		= isr_exit
#pragma weak isr_tim1_up		= isr_exit
#pragma weak isr_tim1_trg_com		= isr_exit
#pragma weak isr_tim1_cc		= isr_exit
#pragma weak isr_tim2			= isr_exit
#pragma weak isr_tim3			= isr_exit
#pragma weak isr_tim4			= isr_exit
#pragma weak isr_i2c1_ev		= isr_exit
#pragma weak isr_i2c1_er		= isr_exit
#pragma weak isr_i2c2_ev		= isr_exit
#pragma weak isr_i2c2_er		= isr_exit
#pragma weak isr_spi1			= isr_exit
#pragma weak isr_spi2			= isr_exit
#pragma weak isr_usart1			= isr_exit
#pragma weak isr_usart2			= isr_exit
#pragma weak isr_usart3			= isr_exit
#pragma weak isr_exti15_10		= isr_exit
#pragma weak isr_rtc_alarm		= isr_exit
#pragma weak isr_usb_wakeup		= isr_exit
#pragma weak isr_tim8_brk		= isr_exit
#pragma weak isr_tim8_up		= isr_exit
#pragma weak isr_tim8_trg_com		= isr_exit
#pragma weak isr_tim8_cc		= isr_exit
#pragma weak isr_adc3			= isr_exit
#pragma weak isr_fsmc			= isr_exit
#pragma weak isr_sdio			= isr_exit
#pragma weak isr_tim5			= isr_exit
#pragma weak isr_spi3			= isr_exit
#pragma weak isr_usart4			= isr_exit
#pragma weak isr_usart5			= isr_exit
#pragma weak isr_tim6			= isr_exit
#pragma weak isr_tim7			= isr_exit
#pragma weak isr_dma2_channel1		= isr_exit
#pragma weak isr_dma2_channel2		= isr_exit
#pragma weak isr_dma2_channel3		= isr_exit
#pragma weak isr_dma2_channel4_5	= isr_exit
#endif
