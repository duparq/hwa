
/*	This file is included by hwa.c
*/

extern int main ( );

void
esr_reset ( )
{
#ifdef BOOT_RAM

/* #  define SCB_BASE		0xE000ED00 */
/* #  define SCB_VTOR		*((volatile u32 *)(SCB_BASE + 8))	/\* 0xE000ED08 *\/ */

  extern void (*const isr_vector[]) (void) ;
  /* extern u32 const isr_vector[] ; */

  /*	STM32 bug : when booting from RAM, SP is not loaded.
   */

  __asm__ volatile("mov sp,%0" : : "r"(isr_vector[0]));

  /* __asm__ volatile */
  /*   ( */
  /*    "mov sp,%[stack_end]"			"\t\n" */
  /*    "mov %[scb_vtor],#isr_vector"		"\t\n" */
  /*    : */
  /*    :[stack_end]"r"(isr_vector[0]), */
  /*     [scb_vtor]"r"(SCB_VTOR) */
  /*    ); */

  /*	When booting from SRAM, in the application initialization code, you have
   *	to relocate the vector table in SRAM using the NVIC exception table and
   *	offset register.
   */
  *HWA_PTR_SCB_VTOR = (u32)isr_vector;

#endif

#if 0
  unsigned long *pulSrc, *pulDest;

  /* Copy the data segment initializers from flash to SRAM.
   */
  pulSrc = &_sidata;
  for(pulDest = &_sdata; pulDest < &_edata; )
    {
      *(pulDest++) = *(pulSrc++);
    }

  // Zero fill the bss segment.
  //
  for(pulDest = &_sbss; pulDest < &_ebss; )
    {
      *(pulDest++) = 0;
    }
#endif

  main();
  for(;;){}
  /* exit(1); */
}


#define WEAK		__attribute__((weak))

#define ESR(n)
#define ISR(n)


/*	Exceptions
 */
void WEAK esr_nmi(void)			ESR(1);
void WEAK esr_hard_fault(void)		ESR(2);
void WEAK esr_mem_manage(void)		ESR(3);
void WEAK esr_bus_fault(void)		ESR(4);
void WEAK esr_usage_fault(void)		ESR(5);
void WEAK esr_sv_call(void)		ESR(6);
void WEAK esr_debug_monitor(void)	ESR(7);
void WEAK esr_pend_sv(void)		ESR(8);
void WEAK esr_systick(void)		ESR(9);


/*	Interrupts
 */
void WEAK isr_wwdg(void)		ISR(0);
void WEAK isr_pvd(void)			ISR(1);
void WEAK isr_tamper(void)		ISR(2);
void WEAK isr_rtc(void)			ISR(3);
void WEAK isr_flash(void)		ISR(4);
void WEAK isr_rcc(void)			ISR(5);
void WEAK isr_exti0(void)		ISR(6);
void WEAK isr_exti1(void)		ISR(7);
void WEAK isr_exti2(void)		ISR(8);
void WEAK isr_exti3(void)		ISR(9);
void WEAK isr_exti4(void)		ISR(10);
void WEAK isr_dma1_channel1(void)	ISR(11);
void WEAK isr_dma1_channel2(void)	ISR(12);
void WEAK isr_dma1_channel3(void)	ISR(13);
void WEAK isr_dma1_channel4(void)	ISR(14);
void WEAK isr_dma1_channel5(void)	ISR(15);
void WEAK isr_dma1_channel6(void)	ISR(16);
void WEAK isr_dma1_channel7(void)	ISR(17);
void WEAK isr_adc1_2(void)		ISR(18);
void WEAK isr_usb_hp_can_tx(void)	ISR(19);
void WEAK isr_usb_lp_can_rx0(void)	ISR(20);
void WEAK isr_can_rx1(void)		ISR(21);
void WEAK isr_can_sce(void)		ISR(22);
void WEAK isr_exti9_5(void)		ISR(23);
void WEAK isr_tim1_brk(void)		ISR(24);
void WEAK isr_tim1_up(void)		ISR(25);
void WEAK isr_tim1_trg_com(void)	ISR(26);
void WEAK isr_tim1_cc(void)		ISR(27);
void WEAK isr_tim2(void)		ISR(28);
void WEAK isr_tim3(void)		ISR(29);
void WEAK isr_tim4(void)		ISR(30);
void WEAK isr_i2c1_ev(void)		ISR(31);
void WEAK isr_i2c1_er(void)		ISR(32);
void WEAK isr_i2c2_ev(void)		ISR(33);
void WEAK isr_i2c2_er(void)		ISR(34);
void WEAK isr_spi1(void)		ISR(35);
void WEAK isr_spi2(void)		ISR(36);
void WEAK isr_usart1(void)		ISR(37);
void WEAK isr_usart2(void)		ISR(38);
void WEAK isr_usart3(void)		ISR(39);
void WEAK isr_exti15_10(void)		ISR(40);
void WEAK isr_rtc_alarm(void)		ISR(41);
void WEAK isr_usb_wakeup(void)		ISR(42);
void WEAK isr_tim8_brk(void)		ISR(43);
void WEAK isr_tim8_up(void)		ISR(44);
void WEAK isr_tim8_trg_com(void)	ISR(45);
void WEAK isr_tim8_cc(void)		ISR(46);
void WEAK isr_adc3(void)		ISR(47);
void WEAK isr_fsmc(void)		ISR(48);
void WEAK isr_sdio(void)		ISR(49);
void WEAK isr_tim5(void)		ISR(50);
void WEAK isr_spi3(void)		ISR(51);
void WEAK isr_usart4(void)		ISR(52);
void WEAK isr_usart5(void)		ISR(53);
void WEAK isr_tim6(void)		ISR(54);
void WEAK isr_tim7(void)		ISR(55);
void WEAK isr_dma2_channel1(void)	ISR(56);
void WEAK isr_dma2_channel2(void)	ISR(57);
void WEAK isr_dma2_channel3(void)	ISR(58);
void WEAK isr_dma2_channel4_5(void)	ISR(59);


typedef void (*vector_t)();


__attribute__ ((section(".vectors")))
vector_t isr_vector[] = {

  (vector_t)0x20005000,	/* Stack pointer */

  /*	Exceptions
   */
  esr_reset,
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
#if defined BOOT_RAM
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
