#ifndef HWA_STM32_PRPH_H
#define HWA_STM32_PRPH_H

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_PRPH0_BASE		HWA_AHB+0x9000					/* 0x40021000 */

#define HWA_PRPH_HWA_APB2RSTR	volatile, u32, 0x0C, 0x00000000, 0x0038FFFD	/* 0x4002100C */
#define HWA_PRPH_HWA_APB1RSTR	volatile, u32, 0x10, 0x00000000, 0x3AFEC9FF	/* 0x40021010 */
#define HWA_PRPH_HWA_AHBENR	volatile, u32, 0x14, 0x00000014, 0x00000557	/* 0x40021014 */
#define HWA_PRPH_HWA_APB2ENR	volatile, u32, 0x18, 0x00000000, 0x0038FFFD	/* 0x40021018 */
#define HWA_PRPH_HWA_APB1ENR	volatile, u32, 0x1C, 0x00000000, 0x3AFEC9FF	/* 0x4002101C */

#define HWA_PRPH_APBENR_HWA_TIMER11	HWA_APB2ENR, 0b1, 21
#define HWA_PRPH_APBENR_HWA_TIMER10	HWA_APB2ENR, 0b1, 20
#define HWA_PRPH_APBENR_HWA_TIMER9	HWA_APB2ENR, 0b1, 19
#define HWA_PRPH_APBENR_HWA_ADC3	HWA_APB2ENR, 0b1, 15
#define HWA_PRPH_APBENR_HWA_USART1	HWA_APB2ENR, 0b1, 14
#define HWA_PRPH_APBENR_HWA_TIMER8	HWA_APB2ENR, 0b1, 13
#define HWA_PRPH_APBENR_HWA_SPI1	HWA_APB2ENR, 0b1, 12
#define HWA_PRPH_APBENR_HWA_TIMER1	HWA_APB2ENR, 0b1, 11
#define HWA_PRPH_APBENR_HWA_ADC2	HWA_APB2ENR, 0b1, 10
#define HWA_PRPH_APBENR_HWA_ADC1	HWA_APB2ENR, 0b1, 9
#define HWA_PRPH_APBENR_HWA_PORTG	HWA_APB2ENR, 0b1, 8
#define HWA_PRPH_APBENR_HWA_PORTF	HWA_APB2ENR, 0b1, 7
#define HWA_PRPH_APBENR_HWA_PORTE	HWA_APB2ENR, 0b1, 6
#define HWA_PRPH_APBENR_HWA_PORTD	HWA_APB2ENR, 0b1, 5
#define HWA_PRPH_APBENR_HWA_PORTC	HWA_APB2ENR, 0b1, 4
#define HWA_PRPH_APBENR_HWA_PORTB	HWA_APB2ENR, 0b1, 3
#define HWA_PRPH_APBENR_HWA_PORTA	HWA_APB2ENR, 0b1, 2
#define HWA_PRPH_APBENR_HWA_AFIO	HWA_APB2ENR, 0b1, 0
#define HWA_PRPH_APBENR_HWA_DAC		HWA_APB1ENR, 0b1, 29
#define HWA_PRPH_APBENR_HWA_PWR		HWA_APB1ENR, 0b1, 28
#define HWA_PRPH_APBENR_HWA_BKP		HWA_APB1ENR, 0b1, 27
#define HWA_PRPH_APBENR_HWA_CAN		HWA_APB1ENR, 0b1, 25
#define HWA_PRPH_APBENR_HWA_USB		HWA_APB1ENR, 0b1, 23
#define HWA_PRPH_APBENR_HWA_I2C2	HWA_APB1ENR, 0b1, 22
#define HWA_PRPH_APBENR_HWA_I2C1	HWA_APB1ENR, 0b1, 21
#define HWA_PRPH_APBENR_HWA_UART5	HWA_APB1ENR, 0b1, 20
#define HWA_PRPH_APBENR_HWA_UART4	HWA_APB1ENR, 0b1, 19
#define HWA_PRPH_APBENR_HWA_USART3	HWA_APB1ENR, 0b1, 18
#define HWA_PRPH_APBENR_HWA_USART2	HWA_APB1ENR, 0b1, 17
#define HWA_PRPH_APBENR_HWA_SPI3	HWA_APB1ENR, 0b1, 15
#define HWA_PRPH_APBENR_HWA_SPI2	HWA_APB1ENR, 0b1, 14
#define HWA_PRPH_APBENR_HWA_WWDG	HWA_APB1ENR, 0b1, 11
#define HWA_PRPH_APBENR_HWA_TIMER14	HWA_APB1ENR, 0b1, 8
#define HWA_PRPH_APBENR_HWA_TIMER13	HWA_APB1ENR, 0b1, 7
#define HWA_PRPH_APBENR_HWA_TIMER12	HWA_APB1ENR, 0b1, 6
#define HWA_PRPH_APBENR_HWA_TIMER7	HWA_APB1ENR, 0b1, 5
#define HWA_PRPH_APBENR_HWA_TIMER6	HWA_APB1ENR, 0b1, 4
#define HWA_PRPH_APBENR_HWA_TIMER5	HWA_APB1ENR, 0b1, 3
#define HWA_PRPH_APBENR_HWA_TIMER4	HWA_APB1ENR, 0b1, 2
#define HWA_PRPH_APBENR_HWA_TIMER3	HWA_APB1ENR, 0b1, 1
#define HWA_PRPH_APBENR_HWA_TIMER2	HWA_APB1ENR, 0b1, 0


typedef struct {
  HWA_PDCL();
  HWA_VDCL(HWA_PRPH, HWA_APB2ENR);
  HWA_VDCL(HWA_PRPH, HWA_APB1ENR);
} HWA_PRPH ;


#define hwa_begin_prph(reset)			\
  HWA_PINIT(HWA_PRPH, HWA_PRPH0);			\
  HWA_VINIT(HWA_PRPH, HWA_PRPH0, HWA_APB2ENR, reset);	\
  HWA_VINIT(HWA_PRPH, HWA_PRPH0, HWA_APB1ENR, reset);


#define hwa_commit_prph()			\
  HWA_COMMITP(hwa_nocommit, HWA_PRPH, HWA_P(HWA_PRPH0), HWA_APB2ENR);	\
  HWA_COMMITP(hwa_nocommit, HWA_PRPH, HWA_P(HWA_PRPH0), HWA_APB1ENR);


/************************************************************************
 *									*
 *			Synchronous actions				*
 *									*
 ************************************************************************/


/************************************************************************
 *									*
 *			Asynchronous actions				*
 *									*
 ************************************************************************/

#define hwa_prph_turn_clk(pname, state)				\
  HWA_VSETP(HWA_PRPH, HWA_P(HWA_PRPH0), HWA_G2(HWA_PRPH_APBENR, pname), HWA_STATE_##state)

#endif
