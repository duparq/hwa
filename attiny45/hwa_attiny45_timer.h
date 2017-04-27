#ifndef HWA_ATTINY45_TIMER_H
#define HWA_ATTINY45_TIMER_H


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

/*	Shared TIMER0/TIMER1 registers
 */
#define HWA_TIMER_HWA_GTCCR		volatile, u8, 0x2C, 0x00, 0x81
#define HWA_TIMER_HWA_IMSK		volatile, u8, 0x39, 0x00, 0x7E
#define HWA_TIMER_HWA_IFR		volatile, u8, 0x38, 0x00, 0x7E


/*	Convenient registers
 */
#define HWA_TIMER_HWA_MODE		, u8,  -1, HWA_TIMER_MODE_NORMAL, 0xFF
#define HWA_TIMER_HWA_CLK		, u8,  -1, HWA_TIMER_CLK_NONE, 0xFF
#define HWA_TIMER_HWA_CLKHZ		, u32, -1, 0, 0xFFFFFFFF
#define HWA_TIMER_HWA_PSC		, u16, -1, 0, 0xFFFF
#define HWA_TIMER_HWA_MAX		, u16, -1, 0, 0xFFFF
#define HWA_TIMER_HWA_HZ		, u32, -1, 0, 0xFFFFFFFF
#define HWA_TIMER_HWA_PERIOD		, u32, -1, 0, 0xFFFFFFFF

#define HWA_TIMER_MODE_NORMAL		1

#define HWA_TIMER_CLK_NONE		1
#define HWA_TIMER_CLK_SYSPSC		2
#define HWA_TIMER_CLK_TOSCPSC		3
#define HWA_TIMER_CLK_EXTERN		4


#define hwa_begin_timer(reset)			\
  hwa_timer_begin_timer0(reset)

/* hwa_timer_begin_timer1(reset)			\ */
/* hwa_timer_begin_timer2(reset) */

#define hwa_commit_timer()				\
  hwa_timer_commit_timer0(HWA_CORE0, HWA_TIMER0);

/* hwa_timer_commit_timer1(HWA_CORE0, HWA_TIMER1);	\ */
/* hwa_timer_commit_timer2(HWA_CORE0, HWA_TIMER2); */


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_timer_write_count(pname, value)	\
  HW_SETHR(pname, pname, HWA_CNT, value)

#define hw_timer_read_count(pname)		\
  HW_HR(pname, pname, HWA_CNT)

#define hw_timer_reset(pname)				\
  do {							\
    if ( HWA_G2(pname, BASE) == HWA_TIMER1_BASE ) {	\
      HW_SETHB(pname, pname, HWA_TIMER1_PSRSYNC, 1);	\
      HW_HR(pname, pname, HWA_CNT) = 0 ;		\
    }							\
    else						\
      HWA_ERROR("Not implemented.");			\
  } while(0)

#define hw_timer_set_match(pname, match, value)		\
  HW_SETHR(pname, pname, HWA_G2(pname, match), value)

#define hw_timer_turn_irq(pname, irq, state)				\
  HW_SETHB(pname, pname, HWA_G2(pname, IRQE_##irq), HWA_STATE_##state)

#define hw_timer_test_flag(pname, flag)				\
  (HW_TSTHB(pname, pname, HWA_G3(pname, FLAG, flag)) != 0)

#define hw_timer_clear_flag(pname, flag)		\
  HW_SETHB(pname, pname, HWA_G3(pname, FLAG, flag), 1)

#define hw_timer_set_prescaler(pname, psc)	\
  HWA_G2(pname, set_prescaler)(psc)

#define hw_timer_set_period(pname, period)	\
  HWA_G2(pname, set_period)(period)


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_timer_set_mode(p, mode)				\
  HWA_SETVR(HWA_TIMER, p, HWA_MODE, HWA_TIMER_MODE_##mode)

#define hwa_timer_set_prescaler(p, psc)				\
  do {								\
    HWA_SETVR(HWA_TIMER, p, HWA_CLK, HWA_TIMER_CLK_SYSPSC);	\
    HWA_SETVR(HWA_TIMER, p, HWA_PSC, psc);			\
  } while(0)

#define hwa_timer_set_clkhz(pname, hz)				\
  do {								\
    HWA_SETVR(HWA_TIMER, pname, HWA_CLK, HWA_TIMER_CLK_SYSPSC);	\
    HWA_SETVR(HWA_TIMER, pname, HWA_CLKHZ, hz);			\
  } while(0)

#define hwa_timer_set_hz(p, hz)			\
  do {						\
    HWA_SETVR(HWA_TIMER, p, HWA_HZ, hz);	\
    HWA_SETVR(HWA_TIMER, p, HWA_PERIOD, 0);	\
  } while(0)

#define hwa_timer_set_period(p, period)			\
  do {							\
    HWA_SETVR(HWA_TIMER, p, HWA_HZ, 0);			\
    HWA_SETVR(HWA_TIMER, p, HWA_PERIOD, period);	\
  } while(0)

#define hwa_timer_set_max(p, max)		\
  HWA_SETVB(HWA_TIMER, p, HWA_MAX, -1, 0, max)

#define hwa_timer_set_match(p, match, value)	\
  HWA_SETVR(p, p, HWA_G2(p, match), value)

#define hwa_timer_set_compare(p, chan, value)	\
  HWA_SETVB(p, p, HWA_OCR##chan, -1, 0, value)

#define hwa_timer_config_pin(p, pin, mode)		\
  hwa_gpio_config_pin(HWA_G3(p, PIN, pin), mode)

#define hwa_timer_drive_pin(p, chan, mode)	\
  HWA_SETVB(p, p, HWA_G4(p, DRIVE, chan, mode))

#define hwa_timer_clear_irq(p, flag)		\
  HWA_SETVB(p, p, HWA_G3(p, FLAG, flag), 1)

#define hwa_timer_turn_irq(p, irq, state)			\
  HWA_SETVB(p, p, HWA_G2(p, IRQE_##irq), HWA_STATE_##state)

#define hwa_timer_set_clk(p, clk)				\
  do {								\
    if ( p != HWA_TIMER0 )					\
      HWA_ERROR("Timer not handle yet.");			\
    HWA_SETVR(HWA_TIMER, p, HWA_CLK, HWA_TIMER_CLK_##clk);	\
  } while(0)


#include "hwa_attiny45_timer0.h"

#endif
