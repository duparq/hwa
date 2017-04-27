#ifndef HWA_STM32_AFIO_H
#define HWA_STM32_AFIO_H

#include "hwa_gpio.h"

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_AFIO_BASE		HWA_APB2+0x0000 /* 0x40010000 */

#define HWA_AFIO_HWA_EVCR	volatile, u32, 0x00, 0x00000000, 0x000000FF
#define HWA_AFIO_HWA_MAPR	volatile, u32, 0x04, 0x00000000, 0x071FFFFF
#define HWA_AFIO_HWA_EXTICR1	volatile, u32, 0x08, 0x00000000, 0x0000FFFF
#define HWA_AFIO_HWA_EXTICR2	volatile, u32, 0x0C, 0x00000000, 0x0000FFFF
#define HWA_AFIO_HWA_EXTICR3	volatile, u32, 0x10, 0x00000000, 0x0000FFFF
#define HWA_AFIO_HWA_EXTICR4	volatile, u32, 0x14, 0x00000000, 0x0000FFFF
#define HWA_AFIO_HWA_MAPR2	volatile, u32, 0x1C, 0x00000000, 0x000007E0

#define HWA_PORTCODE_HWA_PORTA	0b0000
#define HWA_PORTCODE_HWA_PORTB	0b0001
#define HWA_PORTCODE_HWA_PORTC	0b0010
#define HWA_PORTCODE_HWA_PORTD	0b0011
#define HWA_PORTCODE_HWA_PORTE	0b0100
#define HWA_PORTCODE_HWA_PORTF	0b0101
#define HWA_PORTCODE_HWA_PORTG	0b0110

#define HWA_EXTI_BASE		HWA_APB2+0x0400 /* 0x40010400 */

#define HWA_EXTI_HWA_IMR	volatile, u32, 0x00, 0x00000000, 0x000FFFFF
#define HWA_EXTI_HWA_EMR	volatile, u32, 0x04, 0x00000000, 0x000FFFFF
#define HWA_EXTI_HWA_RTSR	volatile, u32, 0x08, 0x00000000, 0x000FFFFF
#define HWA_EXTI_HWA_FTSR	volatile, u32, 0x0C, 0x00000000, 0x000FFFFF
#define HWA_EXTI_HWA_SWIER	volatile, u32, 0x10, 0x00000000, 0x000FFFFF
#define HWA_EXTI_HWA_PR		volatile, u32, 0x14, 0x00000000, 0x000FFFFF

#define HWA_AFIO_EVENT_RISE	1
#define HWA_AFIO_EVENT_FALL	2


typedef struct {
  HWA_PDCL()
  HWA_VDCL(HWA_AFIO, HWA_EVCR);
  HWA_VDCL(HWA_AFIO, HWA_MAPR);
  HWA_VDCL(HWA_AFIO, HWA_EXTICR1);
  HWA_VDCL(HWA_AFIO, HWA_EXTICR2);
  HWA_VDCL(HWA_AFIO, HWA_EXTICR3);
  HWA_VDCL(HWA_AFIO, HWA_EXTICR4);
  HWA_VDCL(HWA_AFIO, HWA_MAPR2);
} HWA_AFIO ;


#define hwa_begin_gpio(reset)			\
  hwa_begin_gpio_port(HWA_PORTA, reset)		\
  hwa_begin_gpio_port(HWA_PORTB, reset)		\
  hwa_begin_gpio_port(HWA_PORTC, reset)		\
  hwa_begin_gpio_port(HWA_PORTD, reset)		\
  hwa_begin_gpio_port(HWA_PORTE, reset)		\
  hwa_begin_gpio_port(HWA_PORTF, reset)		\
  hwa_begin_gpio_port(HWA_PORTG, reset)

#define hwa_begin_gpio_port(pname, reset)				\
  HWA_PINIT(HWA_GPIO, pname);						\
  HWA_VINIT(HWA_GPIO, pname, HWA_CRL, reset);				\
  HWA_VINIT(HWA_GPIO, pname, HWA_CRH, reset);				\
  HWA_VINIT(HWA_GPIO, pname, HWA_ODR, reset);				\
  HWA_VINIT(HWA_GPIO, pname, HWA_BSRR, 1);	/* Never need to read BSRR */

/************************************************************************
 *									*
 *			Asynchronous actions				*
 *									*
 ************************************************************************/

#define hwa_gpio_turn_irq(pin, event, state)				\
  do {									\
  hwa_prph_turn_clk(HWA_AFIO, ON);					\
  u8 pn = HWA_PINNUM(pin);						\
  u8 afioshift = (pn % 4) * 4 ;						\
  if ( pn < 4 ) {							\
    HWA_SETVB(HWA_AFIO, HWA_PORTNAME(pin), HWA_EXTICR1,			\
	      0b1111, afioshift, HWA_G2(HWA_PORTCODE, HWA_PORTNAME(pin))); \
    if ( HWA_AFIO_EVENT_##event == HWA_AFIO_EVENT_RISE ) {		\
    }									\
  } while(0)

#endif
