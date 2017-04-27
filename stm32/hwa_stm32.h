#ifndef HWA_STM32_H
#define HWA_STM32_H

/*	HWA main header for ST STM32
 */
#define HWA_DEVICE_STM32


/*	ARM Cortex-M3 specific definitions
 */
#define HWA_PERIPH			0x40000000
#define HWA_APB1			HWA_PERIPH+0x00000000 /* 0x40000000 */
#define HWA_APB2			HWA_PERIPH+0x00010000 /* 0x40010000 */
#define HWA_AHB				HWA_PERIPH+0x00018000 /* 0x40018000 */

#define HWA_RAM_START			0x20000000
#define HWA_RAM_END			0x20005000


typedef enum {
  HWA_EXIT_ESR			= 63000,
  HWA_EXIT_ISR			= 64000,
  HWA_EXIT_MAIN			= 65000
} HwaExitValue ;

void __attribute__((noreturn))	hwa_exit ( HwaExitValue xv __attribute__((unused)) ) ;


extern void (*const isr_vector[]) (void) ;
#if !defined __unix__
extern int main ( ) __attribute__((noreturn));
#else
extern int main ( int, char** );
#endif


/*	Load from modules
 */
#include "hwa_stm32_core.h"
#include "hwa_stm32_flash.h"
#include "hwa_stm32_prph.h"
#include "hwa_stm32_gpio.h"
#include "hwa_stm32_spi.h"
#include "hwa_stm32_timer.h"
#include "hwa_stm32_irq.h"
#include "hwa_stm32_uart.h"
#include "hwa_stm32_afio.h"

//#include "hwa_stm32_delay.h"


/*	Init HWA structure
 */
#define hwa_begin_device(reset)			\
  hwa_begin_core(reset);			\
  hwa_begin_flash(reset);			\
  hwa_begin_prph(reset);			\
  hwa_begin_gpio(reset);			\
  hwa_begin_spi(reset);				\
  hwa_begin_timer(reset);			\
  hwa_begin_uart(reset);			\
  hwa_begin_irq(reset);


/*	In this order:
 *
 *	* system clocks configuration
 *	* peripheral clocks
 *	* gpio configuration
 */
#define hwa_commit_device()			\
  do {						\
    hwa_commit_core();			\
    hwa_commit_flash();			\
    hwa_commit_prph();			\
    hwa_commit_gpio();			\
    hwa_commit_spi();			\
    hwa_commit_timer();			\
    hwa_commit_uart();			\
    hwa_commit_irq();			\
  } while(0)



/*	Delays
 */
#define hw_nops(n)			_hw_nops(n/4)

inline void
_hw_nops ( u32 cycles )
{
  __asm__
    __volatile__
    (
     "		mov	r0, %[cycles]"	"\n\t"
     "1:"				"\n\t"
     "		subs	r0, #1"		"\n\t"
     "		bne.n	1b"		"\n\t"
     :
     : [cycles] "r" (cycles)
     : "r0", "cc"
     ) ;
}


#endif
