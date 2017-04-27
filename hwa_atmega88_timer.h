#ifndef HWA_MCU_TIMER_H
#define HWA_MCU_TIMER_H

#include "hwa_timer.h"

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_timer_set_count(pname, value)	\
  HWA_HREG(pname, CNT) = value ;

#define HWA_TIMER_COUNT_MAX(pname)\
  HWA_G3(HWA, pname, COUNT_MAX)

#define HWA_TIMER2_COUNT_MAX		255

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/


/*	TCCR2A:		COM2A1 COM2A0 COM2B1 COM2B0   ----  ---- WGM21 WGM20
 *	TCCR2B:		FOC2A  FOC2B   ----   ----    WGM22 CS22 CS21  CS20
 */

#define hwa_timer_set_mode(pname, mode)					\
  do {									\
    if (&HWA_HREG(pname, CRA) == &HWA_HREG(TIMER2, CRA)) {		\
      if ( HWA_TIMER_MODE_##mode == HWA_TIMER_MODE_LOOP_UP ) /* WGM=000 */{ \
	HWA_VSET(u8, pname, CRA, 0b11, 0, 0b00);			\
	HWA_VSET(u8, pname, CRB, 0b1,  3, 0);				\
      } else {								\
	HWA_ERROR_CT(1, "This timer does not support this mode.");	\
      }									\
    } else {								\
      HWA_ERROR_CT(2, "Timer not handle yet.");				\
    }									\
  } while(0)


#define hwa_timer_set_clk(pname, clk)					\
  do {									\
    if (&HWA_HREG(pname, CRA) == &HWA_HREG(TIMER2, CRA)) {		\
      HWA_VSET(u8, TIMER2, ASSR, 0b11, 5, HWA_TIMER2_CLK_##clk);	\
    } else {								\
      HWA_ERROR_CT(2, "Timer not handle yet.");				\
    }									\
  } while(0)

inline u16 HWA_TIMER2_psc_floor(u16 psc) {		\
  if ( psc < 8 ) {					\
    return 1 ;						\
  } else if ( psc < 32 ) {				\
    return 8 ;						\
  } else if ( psc < 64 ) {				\
    return 32 ;						\
  } else if ( psc < 128 ) {				\
    return 64 ;						\
  } else if ( psc < 256 ) {				\
    return 128 ;					\
  } else if ( psc < 1024 ) {				\
    return 256 ;					\
  } else {						\
    return 1024 ;					\
  }							\
}

/* #define hwa_timer_psc_floor(pname, val)		\ */
/*   HWA_G4(HWA,pname,psc,floor)(val) */

#define hwa_timer_set_psc(pname, psc)				\
  do {								\
    if (&HWA_HREG(pname, CRA) == &HWA_HREG(TIMER2, CRA)) {	\
      if ( psc == 0 ) {						\
	HWA_VSET(u8, TIMER2, CRB, 0b111, 0, 0b000);		\
      } else if ( psc == 1 ) {					\
	HWA_VSET(u8, TIMER2, CRB, 0b111, 0, 0b001);		\
      } else if ( psc == 8 ) {					\
	HWA_VSET(u8, TIMER2, CRB, 0b111, 0, 0b010);		\
      } else if ( psc == 32 ) {					\
	HWA_VSET(u8, TIMER2, CRB, 0b111, 0, 0b011);		\
      } else if ( psc == 64 ) {					\
	HWA_VSET(u8, TIMER2, CRB, 0b111, 0, 0b100);		\
      } else if ( psc == 128 ) {				\
	HWA_VSET(u8, TIMER2, CRB, 0b111, 0, 0b101);		\
      } else if ( psc == 256 ) {				\
	HWA_VSET(u8, TIMER2, CRB, 0b111, 0, 0b110);		\
      } else if ( psc == 1024 ) {				\
	HWA_VSET(u8, TIMER2, CRB, 0b111, 0, 0b111);		\
      } else {							\
	HWA_ERROR_CT(1, "Prescaler setting not supported.");	\
      }								\
    } else {							\
      HWA_ERROR_CT(2, "Timer not handle yet.");			\
    }								\
  } while(0)

#define HWA_TIMER2_PSC_STOP		0b000
#define HWA_TIMER2_PSC_DIV1		0b001
#define HWA_TIMER2_PSC_DIV8		0b010
#define HWA_TIMER2_PSC_DIV32		0b011
#define HWA_TIMER2_PSC_DIV64		0b100
#define HWA_TIMER2_PSC_DIV128		0b101
#define HWA_TIMER2_PSC_DIV256		0b110
#define HWA_TIMER2_PSC_DIV1024		0b111


#define hwa_timer_set_clk_hz(pname, hz)					\
  do {									\
    if (&HWA_HREG(pname, CRA) == &HWA_HREG(TIMER2, CRA)) {		\
      if (HWA_VBITS(TIMER2, ASSR, vmask, 0b11, 5) != 0b11 ) {		\
	HWA_ERROR_CT(1, "Unknown timer mode.");				\
      } else {								\
	u16 psc ;							\
	if (HWA_VBITS(TIMER2, ASSR, value, 0b11, 5) == HWA_TIMER2_CLK_SYSCLK_PSC) \
	  psc = SYSCLK_HZ / hz ;					\
	else if (HWA_VBITS(TIMER2, ASSR, value, 0b11, 5) == HWA_TIMER2_CLK_TOSC_PSC) \
	  psc = TOSC_HZ / hz ;						\
	hwa_timer_set_psc(pname, psc);					\
      }									\
    } else {								\
      HWA_ERROR_CT(2, "Timer not handle yet.");				\
    }									\
  } while(0)

#define HWA_TIMER2_CLK_SYSCLK_PSC	0b00	/* default */
#define HWA_TIMER2_CLK_TOSC_PSC		0b01
#define HWA_TIMER2_CLK_EXTERN		0b11

/*	TIFR2:	---- ---- ---- ----    ---- OCF2B  OCF2A  TOV2
 *	TIMSK2:	---- ---- ---- ----    ---- OCIE2B OCIE2A TOIE2
 */
#define hwa_timer_turn_irq(pname, irq, state)			\
  do {								\
    if (&HWA_HREG(pname, CRA) == &HWA_HREG(TIMER2, CRA)) {	\
      if ( HWA_TIMER_IRQ_##irq == HWA_TIMER_IRQ_OVERFLOW ) {	\
	HWA_VSET(u8, TIMER2, IMSK, 0b1, 0, HWA_STATE_##state);	\
      } else {							\
	HWA_ERROR_CT(1, "Unknown IRQ.");			\
      }								\
    } else {							\
      HWA_ERROR_CT(2, "Timer not handle yet.");			\
    }								\
  } while(0)

#define HWA_TIMER_IRQ_OVERFLOW		1


/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

#ifndef TOSC_HZ
#  define TOSC_HZ	0
#endif

#define HWA_TIMER2_CRA		((volatile u8 *)(0xB0)) /* TCCR2A	*/
#define HWA_TIMER2_CRB		((volatile u8 *)(0xB1)) /* TCCR2B	*/
#define HWA_TIMER2_CNT		((volatile u8 *)(0xB2)) /* TCNT2	*/
#define HWA_TIMER2_OCRA		((volatile u8 *)(0xB3)) /* OCR2A	*/
#define HWA_TIMER2_OCRB		((volatile u8 *)(0xB4)) /* OCR2B	*/
#define HWA_TIMER2_ASSR		((volatile u8 *)(0xB6)) /* ASSR		*/
#define HWA_TIMER2_IMSK		((volatile u8 *)(0x70)) /* TIMSK2	*/
#define HWA_TIMER2_IFR		((volatile u8 *)(0x37)) /* TIFR2	*/


#define hwa_timer_begin(state)			\
  hwa_timer_begin_timer(TIMER2, state)

/*	Soft registers: pname, regname, type, reset value, write mask, initial state
 */
#define hwa_timer_begin_timer(pname, state)	\
  HWA_VDCL(u8, pname, CRA,  0, 0xF3, state);	\
  HWA_VDCL(u8, pname, CRB,  0, 0xC3, state);	\
  HWA_VDCL(u8, pname, ASSR, 0, 0x07, state);	\
  HWA_VDCL(u8, pname, IMSK, 0, 0x07, state)

#define hwa_timer_commit()			\
  hwa_timer_commit_timer(TIMER2)

#define hwa_timer_commit_timer(pname)		\
  HWA_COMMIT(u8, pname, CRA);			\
  HWA_COMMIT(u8, pname, CRB);			\
  HWA_COMMIT(u8, pname, ASSR);			\
  HWA_COMMIT(u8, pname, IMSK);

#endif
