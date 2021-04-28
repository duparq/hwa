
/*  When booting from RAM, SP is not loaded.
 *  When booting from SRAM, in the application initialization code, you have
 *  to relocate the vector table in SRAM using the NVIC exception table and
 *  offset register.
 */


extern int main ( ) __attribute__((noreturn));
extern unsigned long _sidata ;
extern unsigned long _edata ;
extern unsigned long _sdata ;
extern unsigned long _ebss ;
extern unsigned long _sbss ;


void
hw_esr_reset ( )
{
  /*  Copy the data segment initializers
   */
#if 1
  unsigned long *src = &_sidata;
  for( unsigned long *dst = &_sdata ; dst < &_edata; ) {
    *(dst++) = *(src++);
  }
#endif

  /*  Zero fill the bss segment. 
   */  
#if 1
  for( unsigned long *dst = &_sbss ; dst < &_ebss; ) {
    *(dst++) = 0;
  }
#endif

  main();
  /* for(;;){} */
  /* exit(1); */
}


#define WEAK		__attribute__((weak))


/*	Exceptions
 */
void WEAK hw_esr_nmi()			;
void WEAK hw_esr_hardfault()		;
void WEAK hw_esr_memmanage()		;
void WEAK hw_esr_busfault()		;
void WEAK hw_esr_usagefault()		;
void WEAK hw_esr_svcall()		;
void WEAK hw_esr_debugmonitor()		;
void WEAK hw_esr_pendsv()		;
void WEAK hw_esr_systick()		;

/*	Interrupts
 */
void WEAK hw_isr_wwdg()			;
void WEAK hw_isr_pvd()			;
void WEAK hw_isr_tamper()		;
void WEAK hw_isr_rtc()			;
void WEAK hw_isr_flash()		;
void WEAK hw_isr_rcc()			;
void WEAK hw_isr_exti0()		;
void WEAK hw_isr_exti1()		;
void WEAK hw_isr_exti2()		;
void WEAK hw_isr_exti3()		;
void WEAK hw_isr_exti4()		;
void WEAK hw_isr_dma1_stream0()		;
void WEAK hw_isr_dma1_stream1()		;
void WEAK hw_isr_dma1_stream2()		;
void WEAK hw_isr_dma1_stream3()		;
void WEAK hw_isr_dma1_stream4()		;
void WEAK hw_isr_dma1_stream5()		;
void WEAK hw_isr_dma1_stream6()		;
void WEAK hw_isr_adc1_2()		;
void WEAK hw_isr_can1_tx()		;
void WEAK hw_isr_can1_rx0()		;
void WEAK hw_isr_can1_rx1()		;
void WEAK hw_isr_can1_sce()		;
void WEAK hw_isr_exti9_5()		;
void WEAK hw_isr_counter1_brk()		;
void WEAK hw_isr_counter1_up()		;
void WEAK hw_isr_counter1_trg_com()	;
void WEAK hw_isr_counter1_cc()		;
void WEAK hw_isr_counter2()		;
void WEAK hw_isr_counter3()		;
void WEAK hw_isr_counter4()		;
void WEAK hw_isr_i2c1_ev()		;
void WEAK hw_isr_i2c1_er()		;
void WEAK hw_isr_i2c2_ev()		;
void WEAK hw_isr_i2c2_er()		;
void WEAK hw_isr_spi1()			;
void WEAK hw_isr_spi2()			;
void WEAK hw_isr_usart1()		;
void WEAK hw_isr_usart2()		;
void WEAK hw_isr_usart3()		;
void WEAK hw_isr_exti15_10()		;
void WEAK hw_isr_rtc_alarm()		;
void WEAK hw_isr_exti18_otgfswkup()	;
void WEAK hw_isr_counter8_brk_counter12()	;
void WEAK hw_isr_counter8_up_counter13()	;
void WEAK hw_isr_counter8_trg_com_counter14()	;
void WEAK hw_isr_counter8_cc()		;
void WEAK hw_isr_dma1_stream7()		;
void WEAK hw_isr_fsmc()			;
void WEAK hw_isr_sdio()			;
void WEAK hw_isr_counter5()		;
void WEAK hw_isr_spi3()			;
void WEAK hw_isr_usart4()		;
void WEAK hw_isr_usart5()		;
void WEAK hw_isr_counter6_dac1_dac2()	;
void WEAK hw_isr_counter7()		;

void WEAK hw_isr_dma2_stream0()		;
void WEAK hw_isr_dma2_stream1()		;
void WEAK hw_isr_dma2_stream2()		;
void WEAK hw_isr_dma2_stream3()		;
void WEAK hw_isr_dma2_stream4()		;
void WEAK hw_isr_dfsdm1_flto()		;
void WEAK hw_isr_dfsdm1_flt1_exti19()	;
void WEAK hw_isr_can2tx()		;
void WEAK hw_isr_can2rx0()		;
void WEAK hw_isr_can2rx1()		;
void WEAK hw_isr_can2sce()		;
void WEAK hw_isr_otgfs()		;
void WEAK hw_isr_dma2_stream5()		;
void WEAK hw_isr_dma2_stream6()		;
void WEAK hw_isr_dma2_stream7()		;
void WEAK hw_isr_usart6()		;
void WEAK hw_isr_i2c3_ev()		;
void WEAK hw_isr_i2c3_er()		;
void WEAK hw_isr_can3tx()		;
void WEAK hw_isr_can3rx0()		;
void WEAK hw_isr_can3rx1()		;
void WEAK hw_isr_can3sce()		;
void WEAK hw_isr_crypto()		;
void WEAK hw_isr_rng()			;
void WEAK hw_isr_fpu()			;
void WEAK hw_isr_uart7()		;
void WEAK hw_isr_uart8()		;
void WEAK hw_isr_spi4()			;
void WEAK hw_isr_spi5()			;
void WEAK hw_isr_sai1()			;
void WEAK hw_isr_uart9()		;
void WEAK hw_isr_uart10()		;
void WEAK hw_isr_quad_spi()		;
void WEAK hw_isr_i2cfmp1ev_i2c4ev()	;
void WEAK hw_isr_i2cfmp1er_i2c4er()	;
void WEAK hw_isr_lptim1_exti23()	;
void WEAK hw_isr_dfsdm2_flto0()		;
void WEAK hw_isr_dfsdm2_flto1()		;
void WEAK hw_isr_dfsdm2_flto2()		;
void WEAK hw_isr_dfsdm2_flto3()		;


typedef void (*hw_vector_t)();


__attribute__ ((section(".vectors")))
hw_vector_t hw_vectors[] =
 {
  /* Stack pointer */
  (hw_vector_t)(0x20000000+RAMSIZE),

  /*	Exceptions
   */
  hw_esr_reset,
  hw_esr_nmi,
  hw_esr_hardfault,
  hw_esr_memmanage,
  hw_esr_busfault,
  hw_esr_usagefault,
  0, 0, 0, 0,			/* Reserved */
  hw_esr_svcall,
  hw_esr_debugmonitor,
  0,				/* Reserved */
  hw_esr_pendsv,
  hw_esr_systick,

  /*	Interrupts
   */
  hw_isr_wwdg,			/* IRQ 0 */
  hw_isr_pvd,			/* IRQ 1 */
  hw_isr_tamper,		/* IRQ 2 */
  hw_isr_rtc,			/* IRQ 3 */
  hw_isr_flash,			/* IRQ 4 */
  hw_isr_rcc,			/* IRQ 5 */
  hw_isr_exti0,			/* IRQ 6 */
  hw_isr_exti1,			/* IRQ 7 */
  hw_isr_exti2,			/* IRQ 8 */
  hw_isr_exti3,			/* IRQ 9 */
  hw_isr_exti4,			/* IRQ 10 */
  hw_isr_dma1_stream0,		/* IRQ 11 */
  hw_isr_dma1_stream1,		/* IRQ 12 */
  hw_isr_dma1_stream2,		/* IRQ 13 */
  hw_isr_dma1_stream3,		/* IRQ 14 */
  hw_isr_dma1_stream4,		/* IRQ 15 */
  hw_isr_dma1_stream5,		/* IRQ 16 */
  hw_isr_dma1_stream6,		/* IRQ 17 */
  hw_isr_adc1_2,		/* IRQ 18 */
  hw_isr_can1_tx,		/* IRQ 19 */
  hw_isr_can1_rx0,		/* IRQ 20 */
  hw_isr_can1_rx1,		/* IRQ 21 */
  hw_isr_can1_sce,		/* IRQ 22 */
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
  hw_isr_spi1,			/* IRQ 35 */
  hw_isr_spi2,			/* IRQ 36 */
  hw_isr_usart1,		/* IRQ 37 */
  hw_isr_usart2,		/* IRQ 38 */
  hw_isr_usart3,		/* IRQ 39 */
  hw_isr_exti15_10,		/* IRQ 40 */
  hw_isr_rtc_alarm,		/* IRQ 41 */
  hw_isr_exti18_otgfswkup,	/* IRQ 42 */
  hw_isr_counter8_brk_counter12,/* IRQ 43 */
  hw_isr_counter8_up_counter13,	/* IRQ 44 */
  hw_isr_counter8_trg_com_counter14,	/* IRQ 45 */
  hw_isr_counter8_cc,		/* IRQ 46 */
  hw_isr_dma1_stream7,		/* IRQ 47 */
  hw_isr_fsmc,			/* IRQ 48 */
  hw_isr_sdio,			/* IRQ 49 */
/* #if defined BOOT_RAM */
/*   (hw_vector_t)0xF108F85F,	/\* @0x0108: workaround for boot issue in RAM mode. *\/ */
/* #else */
  hw_isr_counter5,		/* IRQ 50 */
/* #endif */
  hw_isr_spi3,			/* IRQ 51 */
  hw_isr_usart4,		/* IRQ 52 */
  hw_isr_usart5,		/* IRQ 53 */
  hw_isr_counter6_dac1_dac2,	/* IRQ 54 */
  hw_isr_counter7,		/* IRQ 55 */
  hw_isr_dma2_stream0,		/* IRQ 56 */
  hw_isr_dma2_stream1,		/* IRQ 57 */
  hw_isr_dma2_stream2,		/* IRQ 58 */
  hw_isr_dma2_stream3,		/* IRQ 59 */
  hw_isr_dma2_stream4,		/* IRQ 60 */
  hw_isr_dfsdm1_flto,		/* IRQ 61 */
  hw_isr_dfsdm1_flt1_exti19,	/* IRQ 62 */
  hw_isr_can2tx,		/* IRQ 63 */
  hw_isr_can2rx0,		/* IRQ 64 */
  hw_isr_can2rx1,		/* IRQ 65 */
  hw_isr_can2sce,		/* IRQ 66 */
  hw_isr_otgfs,			/* IRQ 67 */
  hw_isr_dma2_stream5,		/* IRQ 68 */
  hw_isr_dma2_stream6,		/* IRQ 69 */
  hw_isr_dma2_stream7,		/* IRQ 70 */
  hw_isr_usart6,		/* IRQ 71 */
  hw_isr_i2c3_ev,		/* IRQ 72 */
  hw_isr_i2c3_er,		/* IRQ 73 */
  hw_isr_can3tx,		/* IRQ 74 */
  hw_isr_can3rx0,		/* IRQ 75 */
  hw_isr_can3rx1,		/* IRQ 76 */
  hw_isr_can3sce,		/* IRQ 77 */
  0,				/* Reserved */
  hw_isr_crypto,		/* IRQ 79 */
  hw_isr_rng,			/* IRQ 80 */
  hw_isr_fpu,			/* IRQ 81 */
  hw_isr_uart7,			/* IRQ 82 */
  hw_isr_uart8,			/* IRQ 83 */
  hw_isr_spi4,			/* IRQ 84 */
  hw_isr_spi5,			/* IRQ 85 */
  0,				/* Reserved */
  hw_isr_sai1,			/* IRQ 87 */
  hw_isr_uart9,			/* IRQ 88 */
  hw_isr_uart10,		/* IRQ 89 */
  0,				/* Reserved */
  0,				/* Reserved */
  hw_isr_quad_spi,		/* IRQ 92 */
  0,				/* Reserved */
  0,				/* Reserved */
  hw_isr_i2cfmp1ev_i2c4ev,	/* IRQ 95 */
  hw_isr_i2cfmp1er_i2c4er,	/* IRQ 96 */
  hw_isr_lptim1_exti23,		/* IRQ 97 */
  hw_isr_dfsdm2_flto0,		/* IRQ 98 */
  hw_isr_dfsdm2_flto1,		/* IRQ 99 */
  hw_isr_dfsdm2_flto2,		/* IRQ 100 */
  hw_isr_dfsdm2_flto3,		/* IRQ 101 */
};
