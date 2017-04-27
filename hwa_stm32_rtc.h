#ifndef HWA_STM32_RTC_H
#define HWA_STM32_RTC_H

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_rtc_get_seconds()				\
  ((*HWA_PTR_RTC_CNTH)<<16 | (*HWA_PTR_RTC_CNTL))

#define hw_rtc_is_enabled()\
  (((*HWA_PTR_RCC_BDCR) & 0x00008000) != 0)

#define hw_rtc_sync_regs()						\
  do {									\
    (*HWA_PTR_RTC_CRL) &= ~0x0008 ;			/* Clear RSF */ \
    while ( ((*HWA_PTR_RTC_CRL) & 0x0008) == 0 ) {}	/* then wait it is set */ \
  } while(0)

#define hw_rtc_wait_rtoff()				\
  do {							\
    while ( ((*HWA_PTR_RTC_CRL)&0x0020) == 0 ) {}	\
  } while(0)

#define hw_rtc_enter_config()						\
  do {									\
    hw_rtc_wait_rtoff();		/* Poll RTOFF until it is set */ \
    (*HWA_PTR_RTC_CRL) |= 0x0010 ;	/* Set CNF to enter config mode */ \
  } while(0)

#define hw_rtc_exit_config()						\
  (*HWA_PTR_RTC_CRL) &= ~0x0010 ;	/* Clear CNF to exit config mode */

#define hw_rtc_set_prediv(prediv)		\
  do {						\
    *HWA_PTR_RTC_PRLH = prediv >> 16 ;		\
    *HWA_PTR_RTC_PRLL = prediv & 0xFFFF ;	\
  } while(0)

#define hw_rtc_autoconf()			\
  hw_rtc_enter_config();			\
  hw_rtc_set_div();

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_rtc_connect_clk(clksrc)\
  HWA_SET(RCC_BDCR, 0b11, 8, HWA_RTC_CLKSRC_##clksrc);

#define HWA_RTC_CLKSRC_NONE		0b00
#define HWA_RTC_CLKSRC_LSE		0b01
#define HWA_RTC_CLKSRC_LSI		0b10
#define HWA_RTC_CLKSRC_HSE_DIV128	0b11

/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

#define HWA_PTR_RTC		HWA_PTR_APB1+0x2800 /* 0x40002800 */

#define HWA_PTR_RTC_CRH		((volatile u32 *)(HWA_PTR_RTC+0x00)) /* 0x40002800 */
#define HWA_PTR_RTC_CRL		((volatile u32 *)(HWA_PTR_RTC+0x04)) /* 0x40002804 */
#define HWA_PTR_RTC_PRLH	((volatile u32 *)(HWA_PTR_RTC+0x08)) /* 0x40002808 */
#define HWA_PTR_RTC_PRLL	((volatile u32 *)(HWA_PTR_RTC+0x0C)) /* 0x4000280C */
#define HWA_PTR_RTC_DIVH	((volatile u32 *)(HWA_PTR_RTC+0x10)) /* 0x40002810 */
#define HWA_PTR_RTC_DIVL	((volatile u32 *)(HWA_PTR_RTC+0x14)) /* 0x40002814 */
#define HWA_PTR_RTC_CNTH	((volatile u32 *)(HWA_PTR_RTC+0x18)) /* 0x40002818 */
#define HWA_PTR_RTC_CNTL	((volatile u32 *)(HWA_PTR_RTC+0x1C)) /* 0x4000281C */
#define HWA_PTR_RTC_ALRH	((volatile u32 *)(HWA_PTR_RTC+0x20)) /* 0x40002820 */
#define HWA_PTR_RTC_ALRL	((volatile u32 *)(HWA_PTR_RTC+0x24)) /* 0x40002824 */

/*	Register declaration: name, type, address, write mask, reset value
 */
#define hwa_rtc_begin(state)						\
  HWA_DECL(RTC_CRH,  u32, HWA_PTR_RTC+0x00, 0x0000, 0x0007, state)	\
  HWA_DECL(RTC_CRL,  u32, HWA_PTR_RTC+0x04, 0x001F, 0x0020, state)	\
  HWA_DECL(RTC_PRLH, u32, HWA_PTR_RTC+0x08, 0x000F, 0x0000, state)	\
  HWA_DECL(RTC_PRLL, u32, HWA_PTR_RTC+0x0C, 0x8000, 0xFFFF, state)	\
  HWA_DECL(RTC_CNTH, u32, HWA_PTR_RTC+0x18, 0x0000, 0xFFFF, state)	\
  HWA_DECL(RTC_CNTL, u32, HWA_PTR_RTC+0x1C, 0x0000, 0xFFFF, state)	\
  HWA_DECL(RTC_ALRH, u32, HWA_PTR_RTC+0x20, 0xFFFF, 0xFFFF, state)	\
  HWA_DECL(RTC_ALRL, u32, HWA_PTR_RTC+0x24, 0xFFFF, 0xFFFF, state)

#define hwa_rtc_commit()			\
  HWA_COMMIT(RTC_CRH)				\
  HWA_COMMIT(RTC_CRL)				\
  HWA_COMMIT(RTC_PRLH)				\
  HWA_COMMIT(RTC_PRLL)				\
  HWA_COMMIT(RTC_CNTH)				\
  HWA_COMMIT(RTC_CNTL)				\
  HWA_COMMIT(RTC_ALRH)				\
  HWA_COMMIT(RTC_ALRL)

#endif
