#ifndef HWA_ATMEGA88_EXTI_H
#define HWA_ATMEGA88_EXTI_H


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

/*	INT0 - INT1
 */
#define HWA_EXTI0_BASE			0x00

#define HWA_EXTI_HWA_CRA		volatile, u8, 0x69, 0x00, 0x0F
#define HWA_EXTI_HWA_FR			volatile, u8, 0x3C, 0x00, 0x03
#define HWA_EXTI_HWA_MSK		volatile, u8, 0x3D, 0x00, 0x03

/*	Register bits definitions
 */
#define HWA_EXTI_ISC1			HWA_CRA, 0b11, 2
#define HWA_EXTI_ISC0			HWA_CRA, 0b11, 0

#define HWA_EXTI_SENSE_INT0_LOW		HWA_CRA, 0b11, 0, 0b00
#define HWA_EXTI_SENSE_INT0_CHANGE	HWA_CRA, 0b11, 0, 0b01
#define HWA_EXTI_SENSE_INT0_FALL	HWA_CRA, 0b11, 0, 0b10
#define HWA_EXTI_SENSE_INT0_RISE	HWA_CRA, 0b11, 0, 0b11

#define HWA_EXTI_SENSE_PD2_LOW		HWA_CRA, 0b11, 0, 0b00
#define HWA_EXTI_SENSE_PD2_CHANGE	HWA_CRA, 0b11, 0, 0b01
#define HWA_EXTI_SENSE_PD2_FALL		HWA_CRA, 0b11, 0, 0b10
#define HWA_EXTI_SENSE_PD2_RISE		HWA_CRA, 0b11, 0, 0b11

#define HWA_EXTI_SENSE_INT1_LOW		HWA_CRA, 0b11, 2, 0b00
#define HWA_EXTI_SENSE_INT1_CHANGE	HWA_CRA, 0b11, 2, 0b01
#define HWA_EXTI_SENSE_INT1_FALL	HWA_CRA, 0b11, 2, 0b10
#define HWA_EXTI_SENSE_INT1_RISE	HWA_CRA, 0b11, 2, 0b11

#define HWA_EXTI_IRQF_PD2		HWA_FR,  0b1, 0
#define HWA_EXTI_IRQF_INT0		HWA_FR,  0b1, 0
#define HWA_EXTI_IRQF_INT1		HWA_FR,  0b1, 1

#define HWA_EXTI_IRQE_PD2		HWA_MSK, 0b1, 0
#define HWA_EXTI_IRQE_INT0		HWA_MSK, 0b1, 0
#define HWA_EXTI_IRQE_INT1		HWA_MSK, 0b1, 1


typedef struct {
  HWA_PDCL();
  HWA_VDCL(HWA_EXTI, HWA_CRA);
  HWA_VDCL(HWA_EXTI, HWA_FR);
  HWA_VDCL(HWA_EXTI, HWA_MSK);
} HWA_EXTI ;


#define hwa_begin_exti(reset)				\
  HWA_PINIT(HWA_EXTI, HWA_EXTI0);			\
  HWA_VINIT(HWA_EXTI, HWA_EXTI0, HWA_CRA, reset);	\
  HWA_VINIT(HWA_EXTI, HWA_EXTI0, HWA_FR,  reset);	\
  HWA_VINIT(HWA_EXTI, HWA_EXTI0, HWA_MSK, reset);


#define hwa_commit_exti()			\
  hwa_exti_commit(HWA_CORE0, HWA_EXTI0);


inline void
hwa_exti_commit ( HWA_CORE *core, HWA_EXTI *p )
{
  if ( !p->used )
    return ;

  HWA_COMMIT(core, HWA_EXTI, p, HWA_CRA);
  HWA_COMMIT(core, HWA_EXTI, p, HWA_FR);
  HWA_COMMIT(core, HWA_EXTI, p, HWA_MSK);

  p->used = 0 ;
}


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_exti_clear_irq(pin)					\
  HW_SETHB(HWA_EXTI, HWA_EXTI0, HWA_G2(HWA_EXTI_IRQF, pin), 1)

#define hw_exti_turn_irq(pin, state)					\
  HW_SETHB(HWA_EXTI, HWA_EXTI0, HWA_G2(HWA_EXTI_IRQE, pin), HWA_STATE_##state)

#define hw_exti_is_enabled(pin)					\
  (HW_TSTHB(HWA_EXTI, HWA_EXTI0, HWA_G2(HWA_EXTI_IRQE, pin)) != 0)


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_exti_config_pin(pin, event)					\
  HWA_SETVB(HWA_EXTI, HWA_EXTI0, HWA_G3(HWA_EXTI_SENSE, pin, event))

#define hwa_exti_clear_irq(pin)					\
  HWA_SETVB(HWA_EXTI, HWA_EXTI0, HWA_G2(HWA_EXTI_IRQF, pin), 1)

#define hwa_exti_turn_irq(pin, state)					\
  HWA_SETVB(HWA_EXTI, HWA_EXTI0, HWA_G2(HWA_EXTI_IRQE, pin), HWA_STATE_##state)

#endif
