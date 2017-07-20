
/*	This file is included by hwa.c
 */

extern int main ( );

void
hw_esr_reset ( )
{
#ifdef BOOT_RAM

  /* #  define SCB_BASE		0xE000ED00 */
  /* #  define SCB_VTOR		*((volatile u32 *)(SCB_BASE + 8))	/\* 0xE000ED08 *\/ */

  extern void (*const hw_isr_vector[]) (void) ;
  /* extern u32 const hw_isr_vector[] ; */

  /*	STM32 bug : when booting from RAM, SP is not loaded.
   */

  __asm__ volatile("mov sp,%0" : : "r"(hw_isr_vector[0]));

  /* __asm__ volatile */
  /*   ( */
  /*    "mov sp,%[stack_end]"			"\t\n" */
  /*    "mov %[scb_vtor],#hw_isr_vector"		"\t\n" */
  /*    : */
  /*    :[stack_end]"r"(hw_isr_vector[0]), */
  /*     [scb_vtor]"r"(SCB_VTOR) */
  /*    ); */

  /*	When booting from SRAM, in the application initialization code, you have
   *	to relocate the vector table in SRAM using the NVIC exception table and
   *	offset register.
   */
  *HWA_PTR_SCB_VTOR = (u32)hw_isr_vector;

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
void WEAK hw_esr_nmi(void)		ESR(2);
void WEAK hw_esr_hard(void)		ESR(3);
void WEAK hw_esr_memory(void)		ESR(4);
void WEAK hw_esr_bus(void)		ESR(5);
void WEAK hw_esr_usage(void)		ESR(6);
void WEAK hw_esr_swi(void)		ESR(11);
void WEAK hw_esr_debug(void)		ESR(12);
void WEAK hw_esr_pendswi(void)		ESR(14);
void WEAK hw_esr_systick(void)		ESR(15);

/*	Interrupts
 */
void WEAK hw_isr_wwdg(void)		ISR(0);
void WEAK hw_isr_pvd(void)		ISR(1);
void WEAK hw_isr_tamper(void)		ISR(2);
void WEAK hw_isr_rtc(void)		ISR(3);
void WEAK hw_isr_flash(void)		ISR(4);
void WEAK hw_isr_rcc(void)		ISR(5);
void WEAK hw_isr_exti0(void)		ISR(6);
void WEAK hw_isr_exti1(void)		ISR(7);
void WEAK hw_isr_exti2(void)		ISR(8);
void WEAK hw_isr_exti3(void)		ISR(9);
void WEAK hw_isr_exti4(void)		ISR(10);
void WEAK hw_isr_dma1_channel1(void)	ISR(11);
void WEAK hw_isr_dma1_channel2(void)	ISR(12);
void WEAK hw_isr_dma1_channel3(void)	ISR(13);
void WEAK hw_isr_dma1_channel4(void)	ISR(14);
void WEAK hw_isr_dma1_channel5(void)	ISR(15);
void WEAK hw_isr_dma1_channel6(void)	ISR(16);
void WEAK hw_isr_dma1_channel7(void)	ISR(17);
void WEAK hw_isr_adc1_2(void)		ISR(18);
void WEAK hw_isr_usb_hp_can_tx(void)	ISR(19);
void WEAK hw_isr_usb_lp_can_rx0(void)	ISR(20);
void WEAK hw_isr_can_rx1(void)		ISR(21);
void WEAK hw_isr_can_sce(void)		ISR(22);
void WEAK hw_isr_exti9_5(void)		ISR(23);
void WEAK hw_isr_counter1_brk(void)	ISR(24);
void WEAK hw_isr_counter1_up(void)		ISR(25);
void WEAK hw_isr_counter1_trg_com(void)	ISR(26);
void WEAK hw_isr_counter1_cc(void)		ISR(27);
void WEAK hw_isr_counter2(void)	ISR(28);
void WEAK hw_isr_counter3(void)		ISR(29);
void WEAK hw_isr_counter4(void)		ISR(30);
void WEAK hw_isr_i2c1_ev(void)		ISR(31);
void WEAK hw_isr_i2c1_er(void)		ISR(32);
void WEAK hw_isr_i2c2_ev(void)		ISR(33);
void WEAK hw_isr_i2c2_er(void)		ISR(34);
void WEAK hw_isr_spi1(void)		ISR(35);
void WEAK hw_isr_spi2(void)		ISR(36);
void WEAK hw_isr_usart1(void)		ISR(37);
void WEAK hw_isr_usart2(void)		ISR(38);
void WEAK hw_isr_usart3(void)		ISR(39);
void WEAK hw_isr_exti15_10(void)	ISR(40);
void WEAK hw_isr_rtc_alarm(void)	ISR(41);
void WEAK hw_isr_usb_wakeup(void)	ISR(42);
void WEAK hw_isr_counter8_brk(void)	ISR(43);
void WEAK hw_isr_counter8_up(void)		ISR(44);
void WEAK hw_isr_counter8_trg_com(void)	ISR(45);
void WEAK hw_isr_counter8_cc(void)		ISR(46);
void WEAK hw_isr_adc3(void)		ISR(47);
void WEAK hw_isr_fsmc(void)		ISR(48);
void WEAK hw_isr_sdio(void)		ISR(49);
void WEAK hw_isr_counter5(void)		ISR(50);
void WEAK hw_isr_spi3(void)		ISR(51);
void WEAK hw_isr_usart4(void)		ISR(52);
void WEAK hw_isr_usart5(void)		ISR(53);
void WEAK hw_isr_counter6(void)		ISR(54);
void WEAK hw_isr_counter7(void)		ISR(55);
void WEAK hw_isr_dma2_channel1(void)	ISR(56);
void WEAK hw_isr_dma2_channel2(void)	ISR(57);
void WEAK hw_isr_dma2_channel3(void)	ISR(58);
void WEAK hw_isr_dma2_channel4_5(void)	ISR(59);


typedef void (*hw_vector_t)();


__attribute__ ((section(".vectors")))
hw_vector_t hw_vectors[] = {

  (hw_vector_t)0x20005000,	/* Stack pointer */

  /*	Exceptions
   */
  hw_esr_reset,
  hw_esr_nmi,
  hw_esr_hard,
  hw_esr_memory,
  hw_esr_bus,
  hw_esr_usage,
  0, 0, 0, 0,		/* Reserved */
  hw_esr_swi,
  hw_esr_debug,
  0,			/* Reserved */
  hw_esr_pendswi,
  hw_esr_systick,

  /*	Interrupts
   */
  hw_isr_wwdg,		/* IRQ 0 */
  hw_isr_pvd,		/* IRQ 1 */
  hw_isr_tamper,		/* IRQ 2 */
  hw_isr_rtc,		/* IRQ 3 */
  hw_isr_flash,		/* IRQ 4 */
  hw_isr_rcc,		/* IRQ 5 */
  hw_isr_exti0,		/* IRQ 6 */
  hw_isr_exti1,		/* IRQ 7 */
  hw_isr_exti2,		/* IRQ 8 */
  hw_isr_exti3,		/* IRQ 9 */
  hw_isr_exti4,		/* IRQ 10 */
  hw_isr_dma1_channel1,	/* IRQ 11 */
  hw_isr_dma1_channel2,	/* IRQ 12 */
  hw_isr_dma1_channel3,	/* IRQ 13 */
  hw_isr_dma1_channel4,	/* IRQ 14 */
  hw_isr_dma1_channel5,	/* IRQ 15 */
  hw_isr_dma1_channel6,	/* IRQ 16 */
  hw_isr_dma1_channel7,	/* IRQ 17 */
  hw_isr_adc1_2,		/* IRQ 18 */
  hw_isr_usb_hp_can_tx,	/* IRQ 19 */
  hw_isr_usb_lp_can_rx0,	/* IRQ 20 */
  hw_isr_can_rx1,		/* IRQ 21 */
  hw_isr_can_sce,		/* IRQ 22 */
  hw_isr_exti9_5,		/* IRQ 23 */
  hw_isr_counter1_brk,		/* IRQ 24 */
  hw_isr_counter1_up,		/* IRQ 25 */
  hw_isr_counter1_trg_com,	/* IRQ 26 */
  hw_isr_counter1_cc,		/* IRQ 27 */
  hw_isr_counter2,		/* IRQ 28 */
  hw_isr_counter3,		/* IRQ 29 */
  hw_isr_counter4,		/* IRQ 30 */
  hw_isr_i2c1_ev,		/* IRQ 31 */
  hw_isr_i2c1_er,		/* IRQ 32 */
  hw_isr_i2c2_ev,		/* IRQ 33 */
  hw_isr_i2c2_er,		/* IRQ 34 */
  hw_isr_spi1,		/* IRQ 35 */
  hw_isr_spi2,		/* IRQ 36 */
  hw_isr_usart1,		/* IRQ 37 */
  hw_isr_usart2,		/* IRQ 38 */
  hw_isr_usart3,		/* IRQ 39 */
  hw_isr_exti15_10,	/* IRQ 40 */
  hw_isr_rtc_alarm,	/* IRQ 41 */
  hw_isr_usb_wakeup,	/* IRQ 42 */
  hw_isr_counter8_brk,		/* IRQ 43 */
  hw_isr_counter8_up,		/* IRQ 44 */
  hw_isr_counter8_trg_com,	/* IRQ 45 */
  hw_isr_counter8_cc,		/* IRQ 46 */
  hw_isr_adc3,		/* IRQ 47 */
  hw_isr_fsmc,		/* IRQ 48 */
  hw_isr_sdio,		/* IRQ 49 */
#if defined BOOT_RAM
  (void*)0xF108F85F,	/* @0x0108: workaround for boot issue in RAM mode. */
#else
  hw_isr_counter5,		/* IRQ 50 */
#endif
  hw_isr_spi3,		/* IRQ 51 */
  hw_isr_usart4,		/* IRQ 52 */
  hw_isr_usart5,		/* IRQ 53 */
  hw_isr_counter6,		/* IRQ 54 */
  hw_isr_counter7,		/* IRQ 55 */
  hw_isr_dma2_channel1,	/* IRQ 56 */
  hw_isr_dma2_channel2,	/* IRQ 57 */
  hw_isr_dma2_channel3,	/* IRQ 58 */
  hw_isr_dma2_channel4_5,	/* IRQ 59 */
};
