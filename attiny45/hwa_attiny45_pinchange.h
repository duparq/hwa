#ifndef HWA_ATMEGA88_PINCHANGE_H
#define HWA_ATMEGA88_PINCHANGE_H


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_PINCHANGE0_BASE		0x00

#define HWA_PINCHANGE_HWA_CR		volatile, u8, 0x68, 0x00, 0x07
#define HWA_PINCHANGE_HWA_FR		volatile, u8, 0x3B, 0x00, 0x07
#define HWA_PINCHANGE_HWA_MSK2		volatile, u8, 0x6D, 0x00, 0xFF
#define HWA_PINCHANGE_HWA_MSK1		volatile, u8, 0x6C, 0x00, 0x7F
#define HWA_PINCHANGE_HWA_MSK0		volatile, u8, 0x6B, 0x00, 0xFF

/*	Register bits definitions
 */
#define HWA_PINCHANGE_PCINT23		HWA_MSK2, 0b1, 7
#define HWA_PINCHANGE_PCINT18		HWA_MSK2, 0b1, 2


typedef struct {
  HWA_PDCL();
  HWA_VDCL(HWA_PINCHANGE, HWA_CR);
  HWA_VDCL(HWA_PINCHANGE, HWA_FR);
  HWA_VDCL(HWA_PINCHANGE, HWA_MSK2);
  HWA_VDCL(HWA_PINCHANGE, HWA_MSK1);
  HWA_VDCL(HWA_PINCHANGE, HWA_MSK0);
} HWA_PINCHANGE ;


#define hwa_begin_pinchange(reset)				\
  HWA_PINIT(HWA_PINCHANGE, HWA_PINCHANGE0);			\
  HWA_VINIT(HWA_PINCHANGE, HWA_PINCHANGE0, HWA_CR, reset);	\
  HWA_VINIT(HWA_PINCHANGE, HWA_PINCHANGE0, HWA_FR,  reset);	\
  HWA_VINIT(HWA_PINCHANGE, HWA_PINCHANGE0, HWA_MSK2, reset);	\
  HWA_VINIT(HWA_PINCHANGE, HWA_PINCHANGE0, HWA_MSK1, reset);	\
  HWA_VINIT(HWA_PINCHANGE, HWA_PINCHANGE0, HWA_MSK0, reset);


#define hwa_commit_pinchange()			\
  hwa_pinchange_commit(HWA_CORE0, HWA_PINCHANGE0);


inline void
hwa_pinchange_commit ( HWA_CORE *core, HWA_PINCHANGE *p )
{
  if ( !p->used )
    return ;

  HWA_COMMIT(core, HWA_PINCHANGE, p, HWA_CR);
  HWA_COMMIT(core, HWA_PINCHANGE, p, HWA_MSK2);
  HWA_COMMIT(core, HWA_PINCHANGE, p, HWA_MSK1);
  HWA_COMMIT(core, HWA_PINCHANGE, p, HWA_MSK0);

  p->used = 0 ;
}


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_pinchange_turn(pin, state)	\
  HW_SETHB(HWA_PINCHANGE, HWA_PINCHANGE0, HWA_G2(HWA_PINCHANGE, pin), HWA_STATE_##state)

#define hw_pinchange_clear_irq(pin)					\
  HW_SETHB(HWA_PINCHANGE, HWA_PINCHANGE0, HWA_G2(HWA_PINCHANGE_IRQF, pin), 1)

#define hw_pinchange_turn_irq(pin, state)					\
  HW_SETHB(HWA_PINCHANGE, HWA_PINCHANGE0, HWA_G2(HWA_PINCHANGE_IRQE, pin), HWA_STATE_##state)


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_pinchange_turn(pin, state)	\
  HWA_SETVB(HWA_PINCHANGE, HWA_PINCHANGE0, HWA_G2(HWA_PINCHANGE, pin), HWA_STATE_##state)

#define hwa_pinchange_clear_irq(pin)					\
  HWA_SETVB(HWA_PINCHANGE, HWA_PINCHANGE0, HWA_G2(HWA_PINCHANGE_IRQF, pin), 1)

#define hwa_pinchange_turn_irq(pin, state)					\
  HWA_SETVB(HWA_PINCHANGE, HWA_PINCHANGE0, HWA_G2(HWA_PINCHANGE_IRQE, pin), HWA_STATE_##state)

#endif
