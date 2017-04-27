
/*	This file is included by hwa.c
*/

#include "types.h"
#include "hwa.h"

extern unsigned long _sidata;
extern unsigned long _edata;
extern unsigned long _sdata;
extern unsigned long _ebss;
extern unsigned long _sbss;

extern void (*const isr_vector[]) (void) ;

extern void	main(void);

#define WEAK	__attribute__((weak, noreturn))

void WEAK	exit ( int status __attribute__((unused)) ) ;


#if defined HWA_ISR_FAULT_LOOP
#  define ESR(n) { isr_loop(); }
#  define ISR(n) { isr_loop(); }
#elif defined HWA_ISR_FAULT_EXIT_N
#  define ESR(n) { exit(10000 + n); }
#  define ISR(n) { exit(10000 + n); }
#else
#  define ESR(n) ;
#  define ISR(n) ;
#endif


void __attribute__((noreturn))
isr_loop ( )
{
  while(1) {}
}


void __attribute__((noreturn))
isr_exit ( )
{
  exit(10000);
}


void __attribute__((noreturn))
assert_failed ( const char *file __attribute__ ((unused)),
		u16 line __attribute__ ((unused)))
{
  exit(1);
}


void
#if !defined DEBUG
__attribute__((noreturn, weak))
#endif
exit ( int status __attribute__((unused)) )
{
  while(1) {}
}


void
HWA_ESR_RESET ( )
{
  /*	STM32 bug : when booting from RAM, SP is not loaded.
   */
  /*	When booting from SRAM, in the application initialization code, you have
   *	to relocate the vector table in SRAM using the NVIC exception table and
   *	offset register.
   */
#ifdef RUN_FROM_RAM
  if ( (((u32)isr_vector) & 0xFF000000) == 0x20000000 ) {
    __asm__ volatile("mov sp,%[sp]" : : [sp] "r" (isr_vector[0]) );

    /* #define HWA_SCB	0xE000ED00 */
    /* #define HWA_SCB_VTOR	((volatile u32 *)(HWA_SCB+8)) /\* 0xE000ED08 *\/ */
    /* *HWA_SCB_VTOR = (u32)isr_vector; */

    *(u32 *)0xE000ED08 = (u32)isr_vector ;
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
void WEAK HWA_ESR_NMI(void)			ESR(1)
void WEAK HWA_ESR_HARD_FAULT(void)		ESR(2)
void WEAK HWA_ESR_MEM_MANAGE(void)		ESR(3)
void WEAK HWA_ESR_BUS_FAULT(void)		ESR(4)
void WEAK HWA_ESR_USAGE_FAULT(void)		ESR(5)
void WEAK HWA_ESR_SV_CALL(void)			ESR(6)
void WEAK HWA_ESR_DEBUG_MONITOR(void)		ESR(7)
void WEAK HWA_ESR_PEND_SV(void)			ESR(8)
void WEAK HWA_ESR_SYSTICK(void)			ESR(9)


/*	Interrupts
 */
void WEAK HWA_ISR_HWA_WWDG(void)		ISR(0)
void WEAK HWA_ISR_HWA_PVD(void)			ISR(1)
void WEAK HWA_ISR_HWA_TAMPER(void)		ISR(2)
void WEAK HWA_ISR_HWA_RTC(void)			ISR(3)
void WEAK HWA_ISR_HWA_FLASH(void)		ISR(4)
void WEAK HWA_ISR_HWA_RCC(void)			ISR(5)
void WEAK HWA_ISR_HWA_EXTI0(void)		ISR(6)
void WEAK HWA_ISR_HWA_EXTI1(void)		ISR(7)
void WEAK HWA_ISR_HWA_EXTI2(void)		ISR(8)
void WEAK HWA_ISR_HWA_EXTI3(void)		ISR(9)
void WEAK HWA_ISR_HWA_EXTI4(void)		ISR(10)
void WEAK HWA_ISR_HWA_DMA1_CHANNEL1(void)	ISR(11)
void WEAK HWA_ISR_HWA_DMA1_CHANNEL2(void)	ISR(12)
void WEAK HWA_ISR_HWA_DMA1_CHANNEL3(void)	ISR(13)
void WEAK HWA_ISR_HWA_DMA1_CHANNEL4(void)	ISR(14)
void WEAK HWA_ISR_HWA_DMA1_CHANNEL5(void)	ISR(15)
void WEAK HWA_ISR_HWA_DMA1_CHANNEL6(void)	ISR(16)
void WEAK HWA_ISR_HWA_DMA1_CHANNEL7(void)	ISR(17)
void WEAK HWA_ISR_HWA_ADC1_2(void)		ISR(18)
void WEAK HWA_ISR_HWA_USB_HP_CAN_TX(void)	ISR(19)
void WEAK HWA_ISR_HWA_USB_LP_CAN_RX0(void)	ISR(20)
void WEAK HWA_ISR_HWA_CAN_RX1(void)		ISR(21)
void WEAK HWA_ISR_HWA_CAN_SCE(void)		ISR(22)
void WEAK HWA_ISR_HWA_EXTI9_5(void)		ISR(23)
void WEAK HWA_ISR_HWA_TIMER1_BRK(void)		ISR(24)
void WEAK HWA_ISR_HWA_TIMER1_UP(void)		ISR(25)
void WEAK HWA_ISR_HWA_TIMER1_TRG_COM(void)	ISR(26)
void WEAK HWA_ISR_HWA_TIMER1_CC(void)		ISR(27)
void WEAK HWA_ISR_HWA_TIMER2(void)		ISR(28)
void WEAK HWA_ISR_HWA_TIMER3(void)		ISR(29)
void WEAK HWA_ISR_HWA_TIMER4(void)		ISR(30)
void WEAK HWA_ISR_HWA_I2C1_EV(void)		ISR(31)
void WEAK HWA_ISR_HWA_I2C1_ER(void)		ISR(32)
void WEAK HWA_ISR_HWA_I2C2_EV(void)		ISR(33)
void WEAK HWA_ISR_HWA_I2C2_ER(void)		ISR(34)
void WEAK HWA_ISR_HWA_SPI1(void)		ISR(35)
void WEAK HWA_ISR_HWA_SPI2(void)		ISR(36)
void WEAK HWA_ISR_HWA_USART1(void)		ISR(37)
void WEAK HWA_ISR_HWA_USART2(void)		ISR(38)
void WEAK HWA_ISR_HWA_USART3(void)		ISR(39)
void WEAK HWA_ISR_HWA_EXTI15_10(void)		ISR(40)
void WEAK HWA_ISR_HWA_RTC_ALARM(void)		ISR(41)
void WEAK HWA_ISR_HWA_USB_WAKEUP(void)		ISR(42)
void WEAK HWA_ISR_HWA_TIMER8_BRK(void)		ISR(43)
void WEAK HWA_ISR_HWA_TIMER8_UP(void)		ISR(44)
void WEAK HWA_ISR_HWA_TIMER8_TRG_COM(void)	ISR(45)
void WEAK HWA_ISR_HWA_TIMER8_CC(void)		ISR(46)
void WEAK HWA_ISR_HWA_ADC3(void)		ISR(47)
void WEAK HWA_ISR_HWA_FSMC(void)		ISR(48)
void WEAK HWA_ISR_HWA_SDIO(void)		ISR(49)
void WEAK HWA_ISR_HWA_TIMER5(void)		ISR(50)
void WEAK HWA_ISR_HWA_SPI3(void)		ISR(51)
void WEAK HWA_ISR_HWA_USART4(void)		ISR(52)
void WEAK HWA_ISR_HWA_USART5(void)		ISR(53)
void WEAK HWA_ISR_HWA_TIMER6(void)		ISR(54)
void WEAK HWA_ISR_HWA_TIMER7(void)		ISR(55)
void WEAK HWA_ISR_HWA_DMA2_CHANNEL1(void)	ISR(56)
void WEAK HWA_ISR_HWA_DMA2_CHANNEL2(void)	ISR(57)
void WEAK HWA_ISR_HWA_DMA2_CHANNEL3(void)	ISR(58)
void WEAK HWA_ISR_HWA_DMA2_CHANNEL4_5(void)	ISR(59)


__attribute__ ((section(".vectors")))
void (*const isr_vector[]) (void) = {

  /*	Exceptions
   */
  (void *)0x20005000,		/* Stack pointer	*/
  HWA_ESR_RESET,		/* Reset vector		*/

  HWA_ESR_NMI,
  HWA_ESR_HARD_FAULT,
  HWA_ESR_MEM_MANAGE,
  HWA_ESR_BUS_FAULT,
  HWA_ESR_USAGE_FAULT,
  0, 0, 0, 0,			/* Reserved */
  HWA_ESR_SV_CALL,
  HWA_ESR_DEBUG_MONITOR,
  0,				/* Reserved */
  HWA_ESR_PEND_SV,
  HWA_ESR_SYSTICK,

  /*	Interrupts
   */
  HWA_ISR_HWA_WWDG,		/* IRQ 0 */
  HWA_ISR_HWA_PVD,		/* IRQ 1 */
  HWA_ISR_HWA_TAMPER,		/* IRQ 2 */
  HWA_ISR_HWA_RTC,		/* IRQ 3 */
  HWA_ISR_HWA_FLASH,		/* IRQ 4 */
  HWA_ISR_HWA_RCC,		/* IRQ 5 */
  HWA_ISR_HWA_EXTI0,		/* IRQ 6 */
  HWA_ISR_HWA_EXTI1,		/* IRQ 7 */
  HWA_ISR_HWA_EXTI2,		/* IRQ 8 */
  HWA_ISR_HWA_EXTI3,		/* IRQ 9 */
  HWA_ISR_HWA_EXTI4,		/* IRQ 10 */
  HWA_ISR_HWA_DMA1_CHANNEL1,	/* IRQ 11 */
  HWA_ISR_HWA_DMA1_CHANNEL2,	/* IRQ 12 */
  HWA_ISR_HWA_DMA1_CHANNEL3,	/* IRQ 13 */
  HWA_ISR_HWA_DMA1_CHANNEL4,	/* IRQ 14 */
  HWA_ISR_HWA_DMA1_CHANNEL5,	/* IRQ 15 */
  HWA_ISR_HWA_DMA1_CHANNEL6,	/* IRQ 16 */
  HWA_ISR_HWA_DMA1_CHANNEL7,	/* IRQ 17 */
  HWA_ISR_HWA_ADC1_2,		/* IRQ 18 */
  HWA_ISR_HWA_USB_HP_CAN_TX,	/* IRQ 19 */
  HWA_ISR_HWA_USB_LP_CAN_RX0,	/* IRQ 20 */
  HWA_ISR_HWA_CAN_RX1,		/* IRQ 21 */
  HWA_ISR_HWA_CAN_SCE,		/* IRQ 22 */
  HWA_ISR_HWA_EXTI9_5,		/* IRQ 23 */
  HWA_ISR_HWA_TIMER1_BRK,	/* IRQ 24 */
  HWA_ISR_HWA_TIMER1_UP,	/* IRQ 25 */
  HWA_ISR_HWA_TIMER1_TRG_COM,	/* IRQ 26 */
  HWA_ISR_HWA_TIMER1_CC,	/* IRQ 27 */
  HWA_ISR_HWA_TIMER2,		/* IRQ 28 */
  HWA_ISR_HWA_TIMER3,		/* IRQ 29 */
  HWA_ISR_HWA_TIMER4,		/* IRQ 30 */
  HWA_ISR_HWA_I2C1_EV,		/* IRQ 31 */
  HWA_ISR_HWA_I2C1_ER,		/* IRQ 32 */
  HWA_ISR_HWA_I2C2_EV,		/* IRQ 33 */
  HWA_ISR_HWA_I2C2_ER,		/* IRQ 34 */
  HWA_ISR_HWA_SPI1,		/* IRQ 35 */
  HWA_ISR_HWA_SPI2,		/* IRQ 36 */
  HWA_ISR_HWA_USART1,		/* IRQ 37 */
  HWA_ISR_HWA_USART2,		/* IRQ 38 */
  HWA_ISR_HWA_USART3,		/* IRQ 39 */
  HWA_ISR_HWA_EXTI15_10,	/* IRQ 40 */
  HWA_ISR_HWA_RTC_ALARM,	/* IRQ 41 */
  HWA_ISR_HWA_USB_WAKEUP,	/* IRQ 42 */
  HWA_ISR_HWA_TIMER8_BRK,	/* IRQ 43 */
  HWA_ISR_HWA_TIMER8_UP,	/* IRQ 44 */
  HWA_ISR_HWA_TIMER8_TRG_COM,	/* IRQ 45 */
  HWA_ISR_HWA_TIMER8_CC,	/* IRQ 46 */
  HWA_ISR_HWA_ADC3,		/* IRQ 47 */
  HWA_ISR_HWA_FSMC,		/* IRQ 48 */
  HWA_ISR_HWA_SDIO,		/* IRQ 49 */
#ifdef RUN_FROM_RAM
  (void*)0xF108F85F,		/* @0x0108: workaround for boot issue in RAM mode. */
#else
  HWA_ISR_HWA_TIMER5,		/* IRQ 50 */
#endif
  HWA_ISR_HWA_SPI3,		/* IRQ 51 */
  HWA_ISR_HWA_USART4,		/* IRQ 52 */
  HWA_ISR_HWA_USART5,		/* IRQ 53 */
  HWA_ISR_HWA_TIMER6,		/* IRQ 54 */
  HWA_ISR_HWA_TIMER7,		/* IRQ 55 */
  HWA_ISR_HWA_DMA2_CHANNEL1,	/* IRQ 56 */
  HWA_ISR_HWA_DMA2_CHANNEL2,	/* IRQ 57 */
  HWA_ISR_HWA_DMA2_CHANNEL3,	/* IRQ 58 */
  HWA_ISR_HWA_DMA2_CHANNEL4_5,	/* IRQ 59 */
};


#if defined HWA_ISR_FAULT_EXIT
#pragma weak HWA_ESR_NMI		= HWA_ISR_EXIT
#pragma weak HWA_ESR_HARD_FAULT		= HWA_ISR_EXIT
#pragma weak HWA_ESR_MEM_MANAGE		= HWA_ISR_EXIT
#pragma weak HWA_ESR_BUS_FAULT		= HWA_ISR_EXIT
#pragma weak HWA_ESR_USAGE_FAULT	= HWA_ISR_EXIT
#pragma weak HWA_ESR_SV_CALL		= HWA_ISR_EXIT
#pragma weak HWA_ESR_DEBUG_MONITOR	= HWA_ISR_EXIT
#pragma weak HWA_ESR_PEND_SV		= HWA_ISR_EXIT
#pragma weak HWA_ESR_SYSTICK		= HWA_ISR_EXIT

#pragma weak HWA_ISR_HWA_WWDG		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_PVD		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TAMPER		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_RTC		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_FLASH		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_RCC		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_EXTI0		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_EXTI1		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_EXTI2		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_EXTI3		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_EXTI4		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_DMA1_CHANNEL1	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_DMA1_CHANNEL2	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_DMA1_CHANNEL3	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_DMA1_CHANNEL4	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_DMA1_CHANNEL5	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_DMA1_CHANNEL6	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_DMA1_CHANNEL7	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_ADC1_2		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_USB_HP_CAN_TX	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_USB_LP_CAN_RX0	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_CAN_RX1	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_CAN_SCE	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_EXTI9_5	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER1_BRK	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER1_UP	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER1_TRG_COM	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER1_CC	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER2		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER3		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER4		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_I2C1_EV	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_I2C1_ER	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_I2C2_EV	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_I2C2_ER	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_SPI1		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_SPI2		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_USART1		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_USART2		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_USART3		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_EXTI15_10	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_RTC_ALARM	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_USB_WAKEUP	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER8_BRK	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER8_UP	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER8_TRG_COM	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER8_CC	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_ADC3		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_FSMC		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_SDIO		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER5		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_SPI3		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_USART4		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_USART5		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER6		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_TIMER7		= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_DMA2_CHANNEL1	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_DMA2_CHANNEL2	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_DMA2_CHANNEL3	= HWA_ISR_EXIT
#pragma weak HWA_ISR_HWA_DMA2_CHANNEL4_5= HWA_ISR_EXIT
#endif
