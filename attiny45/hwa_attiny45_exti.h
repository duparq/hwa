#ifndef HWA_ATTINY45_EXTI_H
#define HWA_ATTINY45_EXTI_H


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

/*	INT0 - INT1
 */
/* #define HWA_EXTI0_BASE			0x20 */

/* #define HWA_EXTI_HWA_MCUCR		volatile, u8, 0x35, 0x00, 0x03 */
/* #define HWA_EXTI_HWA_GIMSK		volatile, u8, 0x3B, 0x00, 0x60 */
/* #define HWA_EXTI_HWA_GIFR		volatile, u8, 0x3A, 0x00, 0x60 */

/*	Register bits definitions
 */
/* #define HWA_EXTI_ISC0			HWA_MCUCR, 0b11, 0 */

/* #define HWA_EXTI_SENSE_INT0_LOW		HWA_MCUCR, 0b11, 0, 0b00 */
/* #define HWA_EXTI_SENSE_INT0_CHANGE	HWA_MCUCR, 0b11, 0, 0b01 */
/* #define HWA_EXTI_SENSE_INT0_FALL	HWA_MCUCR, 0b11, 0, 0b10 */
/* #define HWA_EXTI_SENSE_INT0_RISE	HWA_MCUCR, 0b11, 0, 0b11 */

/* #define HWA_EXTI_SENSE_PB2_LOW		HWA_MCUCR, 0b11, 0, 0b00 */
/* #define HWA_EXTI_SENSE_PB2_CHANGE	HWA_MCUCR, 0b11, 0, 0b01 */
/* #define HWA_EXTI_SENSE_PB2_FALL		HWA_MCUCR, 0b11, 0, 0b10 */
/* #define HWA_EXTI_SENSE_PB2_RISE		HWA_MCUCR, 0b11, 0, 0b11 */

/* #define HWA_EXTI_IRQF_PB2		HWA_CORE_INTF0 */
/* #define HWA_EXTI_IRQF_INT0		HWA_CORE_INTF0 */

/* #define HWA_EXTI_IRQE_PB2		HWA_CORE_INT0 */
/* #define HWA_EXTI_IRQE_INT0		HWA_CORE_INT0 */
/* #define HWA_CORE_INT0			HWA_GIMSK, 0b1, 6 */
/* #define HWA_CORE_PCIE			HWA_GIMSK, 0b1, 5 */


/* typedef struct { */
/*   HWA_PDCL(); */
/*   HWA_VDCL(HWA_EXTI, HWA_MCUCR); */
/*   /\* HWA_VDCL(HWA_EXTI, HWA_GIFR); *\/ */
/*   /\* HWA_VDCL(HWA_EXTI, HWA_GIMSK); *\/ */
/* } HWA_EXTI ; */


/* #define hwa_begin_exti(reset)				\ */
/*   HWA_PINIT(HWA_EXTI, HWA_EXTI0);			\ */
/*   HWA_VINIT(HWA_EXTI, HWA_EXTI0, HWA_MCUCR, reset);	\ */
/*   /\* HWA_VINIT(HWA_EXTI, HWA_EXTI0, HWA_GIFR,  reset);	\ *\/ */
/*   /\* HWA_VINIT(HWA_EXTI, HWA_EXTI0, HWA_GIMSK, reset); *\/ */


/* #define hwa_commit_exti()			\ */
/*   hwa_exti_commit(HWA_CORE0, HWA_EXTI0); */


/* inline void */
/* hwa_exti_commit ( HWA_CORE *core, HWA_EXTI *p ) */
/* { */
/*   if ( !p->used ) */
/*     return ; */

/*   HWA_COMMIT(core, HWA_EXTI, p, HWA_MCUCR); */
/*   /\* HWA_COMMIT(core, HWA_EXTI, p, HWA_GIFR); *\/ */
/*   /\* HWA_COMMIT(core, HWA_EXTI, p, HWA_GIMSK); *\/ */

/*   p->used = 0 ; */
/* } */


#define HWA_EXTI_INT0_LOW	HWA_CORE_ISC0_LOW
#define HWA_EXTI_INT0_CHANGE	HWA_CORE_ISC0_CHANGE
#define HWA_EXTI_INT0_FALL	HWA_CORE_ISC0_FALL
#define HWA_EXTI_INT0_RISE	HWA_CORE_ISC0_RISE

#define HWA_EXTI_IRQF_INT0	HWA_CORE_INTF0
#define HWA_EXTI_IRQE_INT0	HWA_CORE_INT0


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_exti_clear_irq(pin)					\
  HW_SETHB(HWA_CORE, HWA_CORE0, HWA_G2(HWA_EXTI_IRQF, pin), 1)

#define hw_exti_turn_irq(pin, state)					\
  HW_SETHB(HWA_CORE, HWA_CORE0, HWA_G2(HWA_EXTI_IRQE, pin), HWA_STATE_##state)

#define hw_exti_is_enabled(pin)					\
  (HW_TSTHB(HWA_CORE, HWA_CORE0, HWA_G2(HWA_EXTI_IRQE, pin)) != 0)


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

/* #define HWA_EXTI_INT0_LOW	HWA_MCUCR, 0b11, 0, 0b00 */
/* #define HWA_EXTI_INT0_CHANGE	HWA_MCUCR, 0b11, 0, 0b01 */
/* #define HWA_EXTI_INT0_FALL	HWA_MCUCR, 0b11, 0, 0b10 */
/* #define HWA_EXTI_INT0_RISE	HWA_MCUCR, 0b11, 0, 0b11 */

#define hwa_exti_config_pin(pin, event)					\
  HWA_SETVB(HWA_CORE, HWA_CORE0, HWA_G3(HWA_EXTI, pin, event))

#define hwa_exti_clear_irq(pin)					\
  HWA_SETVB(HWA_CORE, HWA_CORE0, HWA_G2(HWA_EXTI_IRQF, pin), 1)

#define hwa_exti_turn_irq(pin, state)					\
  HWA_SETVB(HWA_CORE, HWA_CORE0, HWA_G2(HWA_EXTI_IRQE, pin), HWA_STATE_##state)

#endif
