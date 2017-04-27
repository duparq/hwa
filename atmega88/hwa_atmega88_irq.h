#ifndef HWA_ATMEGA88_IRQ_H
#define HWA_ATMEGA88_IRQ_H


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#ifndef EXTERN_C
#  define EXTERN_C
#endif

#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  define __INTR_ATTRS used, externally_visible
#else /* GCC < 4.1 */
#  define __INTR_ATTRS used
#endif

#define HWA_ISR_(vector, flags...)					\
  EXTERN_C void vector (void) __attribute__ ((signal,__INTR_ATTRS, flags)) ; \
  void vector (void)

#define HWA_ISR_INTERRUPTIBLE		interrupt
#define HWA_ISR_NON_INTERRUPTIBLE
#define HWA_ISR_NAKED			naked


#define HWA_ISR_HWA_EXTI0_INT0		__vector_1
#define HWA_ISR_HWA_EXTI0_INT1		__vector_2
#define HWA_ISR_HWA_PCINT0_PINCHANGE	__vector_3
#define HWA_ISR_HWA_PCINT1_PINCHANGE	__vector_4
#define HWA_ISR_HWA_PCINT2_PINCHANGE	__vector_5
#define HWA_ISR_HWA_TIMER2_PERIODIC_IRQ	__vector_7
#define HWA_ISR_HWA_TIMER2_MATCH_A	__vector_7
#define HWA_ISR_HWA_TIMER2_MATCH_LOOP	__vector_7
#define HWA_ISR_HWA_TIMER2_MATCH_B	__vector_8
#define HWA_ISR_HWA_TIMER2_OVF		__vector_9
#define HWA_ISR_HWA_TIMER2_OVERFLOW	__vector_9
#define HWA_ISR_HWA_TIMER1_CAPTURE	__vector_10
#define HWA_ISR_HWA_TIMER1_LOOP		__vector_11
#define HWA_ISR_HWA_TIMER1_MATCH_A	__vector_11
#define HWA_ISR_HWA_TIMER1_MATCH_LOOP	__vector_11
#define HWA_ISR_HWA_TIMER1_MATCH_B	__vector_12
#define HWA_ISR_HWA_TIMER1_OVERFLOW	__vector_13

#define HWA_ISR_HWA_TIMER0_MATCH_A	__vector_14
#define HWA_ISR_HWA_TIMER0_MATCH_B	__vector_15
#define HWA_ISR_HWA_TIMER0_OVERFLOW	__vector_16

#define HWA_ISR_HWA_USART0_RX		__vector_18
#define HWA_ISR_HWA_USART0_RXQNE	__vector_18
#define HWA_ISR_HWA_USART0_TXC		__vector_20
#define HWA_ISR_HWA_ADC0_COMPLETED	__vector_21


/************************************************************************
 *									*
 *			User definitions				*
 *									*
 ************************************************************************/

#define HWA_ISR(pname, event, flags...)				\
  HWA_ISR_(HWA_G3(HWA_ISR, pname, event), flags)

#endif
