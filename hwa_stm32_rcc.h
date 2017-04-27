#ifndef HWA_RCC_H
#define HWA_RCC_H


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

/* #define hw_disable_and_clear_irqs()		\ */
/*   *HWA_PTR_RCC_CIR = 0x009F0000 ; */

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_connect_pin_outclk(clk)		\
  HWA_SET(RCC_CFGR, 0b111, 24, HWA_MCO_##clk)
#define HWA_MCO_NONE				0x0 /* default */
#define HWA_MCO_SYSCLK				0x4
#define HWA_MCO_HSI				0x5
#define HWA_MCO_HSE				0x6
#define HWA_MCO_PLL_DIV2			0x7

#define hwa_connect_usbclk(clk)			\
  HWA_SET(RCC_CFGR, 0b1, 22, HWA_USBCLK_##clk)
#define HWA_USBCLK_SYSCLK_DIV1_5		0x0 /* default */
#define HWA_USBCLK_SYSCLK			0x1

/*	The PLL configuration (selection of HSI oscillator divided by 2 or HSE
 *	oscillator for PLL input clock, and multiplication factor) must be done
 *	before enabling the PLL. Once the PLL enabled, these parameters cannot
 *	be changed.
 */
#define hwa_set_pllmul(mul)						\
  do {									\
    if ( hwa_checking_policy != HWA_CHECKING_POLICY_NONE ) {		\
      if ( HWA_RCC_CR_initialised == 0 ) {				\
	if ( hwa_checking_policy != HWA_CHECKING_POLICY_RUN_TIME )	\
	  HWA_WARN_CT(1, "Can not check that the PLL is turned off.");	\
      } else if ( HWA_BITS(HWA_RCC_CR_value, 0b1, 24) == 1 )		\
	HWA_ERROR_CT(2, "PLL must be off.");				\
      if ( hwa_checking_policy == HWA_CHECKING_POLICY_RUN_TIME		\
	   && HWA_BITS(*HWA_PTR_RCC_CR, 0b1, 24) == 1)			\
	HWA_ERROR_RT(3, "PLL must be off.");				\
    }									\
    if ( HWA_PLLMUL_##mul != HWA_PLLMUL_AUTO ) {			\
      HWA_SET(RCC_CFGR, 0b1111, 18, HWA_PLLMUL_##mul);			\
    } else if (HWA_BITS(HWA_RCC_CFGR_value, 0b11, 16) == HWA_PLLSRC_HSI_DIV2) { \
      HWA_SET(RCC_CFGR, 0b1111, 18, (SYSCLK_HZ/4000000)-2) ;		\
    } else if (HWA_BITS(HWA_RCC_CFGR_value, 0b11, 16) == HWA_PLLSRC_HSE) { \
      HWA_SET(RCC_CFGR, 0b1111, 18, (SYSCLK_HZ/HSE_HZ)-2) ;		\
    } else if (HWA_BITS(HWA_RCC_CFGR_value, 0b11, 16) == HWA_PLLSRC_HSE_DIV2) { \
      HWA_SET(RCC_CFGR, 0b1111, 18, (2*SYSCLK_HZ/HSE_HZ)-2) ;		\
    }									\
  } while(0)
#define HWA_PLLMUL_2				0x0
#define HWA_PLLMUL_3				0x1
#define HWA_PLLMUL_4				0x2
#define HWA_PLLMUL_5				0x3
#define HWA_PLLMUL_6				0x4
#define HWA_PLLMUL_7				0x5
#define HWA_PLLMUL_8				0x6
#define HWA_PLLMUL_9				0x7
#define HWA_PLLMUL_10				0x8
#define HWA_PLLMUL_11				0x9
#define HWA_PLLMUL_12				0x10
#define HWA_PLLMUL_13				0x11
#define HWA_PLLMUL_14				0x12
#define HWA_PLLMUL_15				0x13
#define HWA_PLLMUL_16				0x14
#define HWA_PLLMUL_AUTO				0xff

#define hwa_connect_pll(src)			\
  HWA_SET(RCC_CFGR, 0b11, 16, HWA_PLLSRC_##src)
#define HWA_PLLSRC_HSI_DIV2			0b00 /* default */
#define HWA_PLLSRC_HSE				0b01
#define HWA_PLLSRC_HSE_DIV2			0b10

#define hwa_connect_adcclk(clk)			\
  HWA_SET(RCC_CFGR, 0b11, 14, HWA_ADCLK_##clk)
#define HWA_ADCLK_PCLK2_DIV2			0x0 /* default */
#define HWA_ADCLK_PCLK2_DIV4			0x1
#define HWA_ADCLK_PCLK2_DIV6			0x2
#define HWA_ADCLK_PCLK2_DIV8			0x3

#define hwa_connect_pclk2(clk)			\
  HWA_SET(RCC_CFGR, 0b111, 11, HWA_PCLK_##clk)
#define hwa_connect_pclk1(clk)			\
  HWA_SET(RCC_CFGR, 0b111, 8, HWA_PCLK_##clk)
#define HWA_PCLK_HCLK				0x0 /* default */
#define HWA_PCLK_HCLK_DIV2			0x4
#define HWA_PCLK_HCLK_DIV4			0x5
#define HWA_PCLK_HCLK_DIV8			0x6
#define HWA_PCLK_HCLK_DIV16			0x7

#define hwa_connect_hclk(clk)			\
  HWA_SET(RCC_CFGR, 0b1111, 4, HWA_HCLK_##clk)
#define HWA_HCLK_SYSCLK				0x0 /* default */
#define HWA_HCLK_SYSCLK_DIV2			0x8
#define HWA_HCLK_SYSCLK_DIV4			0x9
#define HWA_HCLK_SYSCLK_DIV8			0xA
#define HWA_HCLK_SYSCLK_DIV16			0xB
#define HWA_HCLK_SYSCLK_DIV64			0xC
#define HWA_HCLK_SYSCLK_DIV128			0xD
#define HWA_HCLK_SYSCLK_DIV256			0xE
#define HWA_HCLK_SYSCLK_DIV512			0xF

/*	Turn PLL on/off.
 *	Auto-commit: commit PLL config (PLLMUL & PLLSRC) before turning it on.
 */
#define hwa_turn_pll(state)						\
  do {									\
    if ( HWA_STATE_##state == HWA_STATE_ON ) {				\
      if ( HWA_BITS(HWA_RCC_CFGR_mmask, 0b111111, 16) != 0 ) {		\
	if ( hwa_commit_policy == HWA_COMMIT_POLICY_AUTO ) { 		\
	  HWA_COMMIT(RCC_CFGR);						\
	} else {							\
	  HWA_WARN_CT(1, "PLL must be configured before being turned on."); \
	}								\
      }									\
    }									\
    HWA_SET(RCC_CR, 0b1, 24, HWA_STATE_##state);			\
  } while(0)

#define hwa_wait_pll_ready()						\
  do {									\
    HWA_COMMIT_AUTO(RCC_CR, 0b1, 24);					\
    if ( hwa_checking_policy != HWA_CHECKING_POLICY_NONE ) {		\
      if ( HWA_RCC_CR_initialised == 0 ) {				\
	if ( hwa_checking_policy != HWA_CHECKING_POLICY_RUN_TIME ) {	\
	  HWA_WARN_CT(1, "Can not check that the PLL is turned on.");	\
	}								\
      } else if ( HWA_BITS(HWA_RCC_CR_ovalue, 0b1, 24) == 0 ) {		\
	HWA_ERROR_CT(2, "The PLL is turned off.");			\
      }									\
      if ( hwa_checking_policy == HWA_CHECKING_POLICY_RUN_TIME		\
	   && HWA_BITS(*HWA_PTR_RCC_CR, 0b1, 24) == 0) {		\
	HWA_ERROR_RT(3, "The PLL is turned off.");			\
      }									\
    }									\
    while (!(*HWA_PTR_RCC_CR & (1<<25))){}				\
  } while (0)

/*	Commit PLL-related registers.
 *	RCC_CFGR, 0b1111, 18	: HWA_PLLMUL
 *	RCC_CFGR, 0b11, 16	: HWA_PLLSRC
 */
#define hwa_commit_pll()			\
  do {						\
    HWA_COMMIT(RCC_CFGR);			\
    HWA_COMMIT(RCC_CR);				\
  } while(0)

#define hwa_turn_clock_security(state)		\
  HWA_SET(RCC_CR, 0b1, 19, HWA_STATE_#state)

/*	State of HSE bypass cannot be changed if HSE is running.
 */
#define hwa_turn_hse_bypass(state)				\
  do {								\
    if ( hwa_commit_policy != HWA_COMMIT_POLICY_ALWAYS )	\
      if ( HWA_BITS(RCC_CR, 0b1, 16) == 1 )			\
	HWA_WARN_();						\
    HWA_SET(RCC_CR, 0b1, 18, HWA_STATE_##state)			\
      } while(0)

#define hwa_turn_hse(state)			\
  HWA_SET(RCC_CR, 0b1, 16, HWA_STATE_##state)

#define hwa_commit_hse()			\
  HWA_COMMIT(RCC_CR)

#define hwa_wait_hse_ready()						\
  do {									\
    HWA_COMMIT_AUTO(RCC_CR, 0b1, 16);					\
    if ( hwa_checking_policy != HWA_CHECKING_POLICY_NONE ) {		\
      if ( HWA_RCC_CR_initialised == 0 ) {				\
	if ( hwa_checking_policy != HWA_CHECKING_POLICY_RUN_TIME )	\
	  HWA_WARN_CT(1, "Can not check that HSE is turned on.");	\
      } else if ( HWA_BITS(HWA_RCC_CR_ovalue, 0b1, 16) == 0 ) {		\
	HWA_ERROR_CT(2, "HSE is turned off.");				\
      }									\
      if ( hwa_checking_policy == HWA_CHECKING_POLICY_RUN_TIME		\
	   && HWA_BITS(*HWA_PTR_RCC_CR, 0b1, 16) == 0) {		\
	HWA_ERROR_RT(3, "HSE is turned off.");				\
      }									\
    }									\
    while (!(*HWA_PTR_RCC_CR & (1<<17))){}				\
  } while(0)


#define hwa_turn_hsi(state)			\
  HWA_SET(RCC_CR, 0b1, 0, HWA_STATE_##state)

#define hwa_wait_hsi_ready()				\
  do {								\
    if ( hwa_commit_policy == HWA_COMMIT_POLICY_AUTO )		\
      HWA_COMMIT(RCC_CR);					\
    if ( hwa_commit_policy != HWA_COMMIT_POLICY_ALWAYS )	\
      if ( HWA_BITS(RCC_CR, 0b1, 0) != 1 )			\
	hwa_warn();						\
    while (!(*HWA_PTR_RCC_CR & (1<<1))){}			\
  } while(0)

#define hwa_connect_sysclk(clk)			\
  HWA_SET(RCC_CFGR, 0b11, 0, HWA_SYSCLK_##clk)
#define HWA_SYSCLK_HSI				0x0 /* default */
#define HWA_SYSCLK_HSE				0x1
#define HWA_SYSCLK_PLL				0x2

/*	Turn on/off peripheral clocking.
 *	"When the peripheral clock is not active, the peripheral register values
 *	may not be readable by software and the returned value is always 0x0."
 */
#define hwa_turn_clk(pname, state)		\
  _hwa_turn_clk(pname, state)

#define hwac_turn_clk(pname, state)		\
  _hwac_turn_clk(pname, state)

/* #define hwa_commit_clk(pname)			\ */
/*   _hwa_commit_clk(pname) */

#define hwa_deinit_rcc()			\
  hwa_start_hsi() ;				\
  rcc_config_commit();				\
  hwa_connect_output_clock(NONE) ;		\
  hwa_connect_adcclk(PCLK2_DIV2);		\
  hwa_connect_pclk2(HCLK);			\
  hwa_connect_pclk1(HCLK);			\
  hwa_connect_hclk(SYSCLK);			\
  hwa_connect_sysclk(HSI);			\
  rcc_config_commit();				\
  hwa_stop_pll();				\
  hwa_stop_clock_security();			\
  hwa_stop_hse();				\
  rcc_config_commit();				\
  hwa_disable_hse_bypass();			\
  rcc_config_commit();				\
  hwa_connect_usbclk(SYSCLK_DIV1_5);		\
  hwa_set_pllmul(2);				\
  hwa_connect_pll(HSI_DIV2);			\
  rcc_config_commit();				\
  RCC_CIR_sync = 1 ;				\
  RCC_CIR_mask = 0xffffffff ;			\
  RCC_CIR_value = 0x009F0000 ;			\
  rcc_config_commit();

/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

#define HWA_PTR_RCC		HWA_PTR_AHB+0x9000 /* 0x40021000 */

#define HWA_PTR_RCC_CR		((volatile u32 *)(HWA_PTR_RCC+0x00)) /* 0x40021000 */
#define HWA_PTR_RCC_CFGR	((volatile u32 *)(HWA_PTR_RCC+0x04)) /* 0x40021004 */
#define HWA_PTR_RCC_CIR		((volatile u32 *)(HWA_PTR_RCC+0x08)) /* 0x40021008 */
#define HWA_PTR_RCC_APB2RSTR	((volatile u32 *)(HWA_PTR_RCC+0x0C)) /* 0x4002100C */
#define HWA_PTR_RCC_APB1RSTR	((volatile u32 *)(HWA_PTR_RCC+0x10)) /* 0x40021010 */
#define HWA_PTR_RCC_AHBENR	((volatile u32 *)(HWA_PTR_RCC+0x14)) /* 0x40021014 */
#define HWA_PTR_RCC_APB2ENR	((volatile u32 *)(HWA_PTR_RCC+0x18)) /* 0x40021018 */
#define HWA_PTR_RCC_APB1ENR	((volatile u32 *)(HWA_PTR_RCC+0x1C)) /* 0x4002101C */
#define HWA_PTR_RCC_BDCR	((volatile u32 *)(HWA_PTR_RCC+0x20)) /* 0x40021020 */
#define HWA_PTR_RCC_CSR		((volatile u32 *)(HWA_PTR_RCC+0x24)) /* 0x40021024 */

/*	Register declaration: name, type, address, write mask, reset value
 */
#define hwa_rcc_begin(state)						\
  HWA_DECL(RCC_CR,       u32, HWA_PTR_RCC+0x00, 0x00000083, 0x010D00F9, state) /* 0x40021000 */ \
  HWA_DECL(RCC_CFGR,     u32, HWA_PTR_RCC+0x04, 0x00000000, 0x077FFFF3, state) /* 0x40021004 */ \
  HWA_DECL(RCC_CIR,      u32, HWA_PTR_RCC+0x08, 0x00000000, 0x00001F00, state) /* 0x40021008 */ \
  HWA_DECL(RCC_APB2RSTR, u32, HWA_PTR_RCC+0x0C, 0x00000000, 0x0038FFFD, state) /* 0x4002100C */ \
  HWA_DECL(RCC_APB1RSTR, u32, HWA_PTR_RCC+0x10, 0x00000000, 0x3AFEC9FF, state) /* 0x40021010 */ \
  HWA_DECL(RCC_AHBENR,   u32, HWA_PTR_RCC+0x14, 0x00000014, 0x00000557, state) /* 0x40021014 */ \
  HWA_DECL(RCC_APB2ENR,  u32, HWA_PTR_RCC+0x18, 0x00000000, 0x0038FFFD, state) /* 0x40021018 */ \
  HWA_DECL(RCC_APB1ENR,  u32, HWA_PTR_RCC+0x1C, 0x00000000, 0x3AFEC9FF, state) /* 0x4002101C */ \
  HWA_DECL(RCC_BDCR,     u32, HWA_PTR_RCC+0x20, 0x00000000, 0x00018305, state) /* 0x40021020 */ \
  HWA_DECL(RCC_CSR,      u32, HWA_PTR_RCC+0x24, 0x0C000000, 0xFD000001, state) /* 0x40021024 */

#define hwa_rcc_commit()			\
  HWA_COMMIT(RCC_CR);				\
  HWA_COMMIT(RCC_CFGR);				\
  HWA_COMMIT(RCC_CIR);				\
  HWA_COMMIT(RCC_APB2RSTR);			\
  HWA_COMMIT(RCC_APB1RSTR);			\
  HWA_COMMIT(RCC_AHBENR);			\
  HWA_COMMIT(RCC_APB2ENR);			\
  HWA_COMMIT(RCC_APB1ENR);			\
  HWA_COMMIT(RCC_BDCR);				\
  HWA_COMMIT(RCC_CSR);

#define _hwa_turn_clk(pname, state)				\
  HWA_SET_VA(HWA_ARGS_CKEN_##pname, HWA_STATE_##state)

#define _hwac_turn_clk(pname, state)				\
  HWA_SET_VA(HWA_ARGS_CKEN_##pname, HWA_STATE_##state)		\
  HWA_COMMIT_VA(HWA_ARGS_CKEN_##pname)

/* #define _hwa_commit_clk(pname)			\ */
/*   HWA_COMMIT_VA(HWA_ARGS_CKEN_##pname) */

#define HWA_ARGS_CKEN_TIMER11			RCC_APB2ENR, 0b1, 21
#define HWA_ARGS_CKEN_TIMER10			RCC_APB2ENR, 0b1, 20
#define HWA_ARGS_CKEN_TIMER9			RCC_APB2ENR, 0b1, 19
#define HWA_ARGS_CKEN_ADC3			RCC_APB2ENR, 0b1, 15
#define HWA_ARGS_CKEN_USART1			RCC_APB2ENR, 0b1, 14
#define HWA_ARGS_CKEN_TIMER8			RCC_APB2ENR, 0b1, 13
#define HWA_ARGS_CKEN_SPI1			RCC_APB2ENR, 0b1, 12
#define HWA_ARGS_CKEN_TIMER1			RCC_APB2ENR, 0b1, 11
#define HWA_ARGS_CKEN_ADC2			RCC_APB2ENR, 0b1, 10
#define HWA_ARGS_CKEN_ADC1			RCC_APB2ENR, 0b1, 9
#define HWA_ARGS_CKEN_PORTG			RCC_APB2ENR, 0b1, 8
#define HWA_ARGS_CKEN_PORTF			RCC_APB2ENR, 0b1, 7
#define HWA_ARGS_CKEN_PORTE			RCC_APB2ENR, 0b1, 6
#define HWA_ARGS_CKEN_PORTD			RCC_APB2ENR, 0b1, 5
#define HWA_ARGS_CKEN_PORTC			RCC_APB2ENR, 0b1, 4
#define HWA_ARGS_CKEN_PORTB			RCC_APB2ENR, 0b1, 3
#define HWA_ARGS_CKEN_PORTA			RCC_APB2ENR, 0b1, 2
#define HWA_ARGS_CKEN_AFIO			RCC_APB2ENR, 0b1, 0

#define HWA_ARGS_CKEN_DAC			RCC_APB1ENR, 0b1, 29
#define HWA_ARGS_CKEN_PWR			RCC_APB1ENR, 0b1, 28
#define HWA_ARGS_CKEN_BKP			RCC_APB1ENR, 0b1, 27
#define HWA_ARGS_CKEN_CAN			RCC_APB1ENR, 0b1, 25
#define HWA_ARGS_CKEN_USB			RCC_APB1ENR, 0b1, 23
#define HWA_ARGS_CKEN_I2C2			RCC_APB1ENR, 0b1, 22
#define HWA_ARGS_CKEN_I2C1			RCC_APB1ENR, 0b1, 21
#define HWA_ARGS_CKEN_UART5			RCC_APB1ENR, 0b1, 20
#define HWA_ARGS_CKEN_UART4			RCC_APB1ENR, 0b1, 19
#define HWA_ARGS_CKEN_USART3			RCC_APB1ENR, 0b1, 18
#define HWA_ARGS_CKEN_USART2			RCC_APB1ENR, 0b1, 17
#define HWA_ARGS_CKEN_SPI3			RCC_APB1ENR, 0b1, 15
#define HWA_ARGS_CKEN_SPI2			RCC_APB1ENR, 0b1, 14
#define HWA_ARGS_CKEN_WWDG			RCC_APB1ENR, 0b1, 11
#define HWA_ARGS_CKEN_TIMER14			RCC_APB1ENR, 0b1, 8
#define HWA_ARGS_CKEN_TIMER13			RCC_APB1ENR, 0b1, 7
#define HWA_ARGS_CKEN_TIMER12			RCC_APB1ENR, 0b1, 6
#define HWA_ARGS_CKEN_TIMER7			RCC_APB1ENR, 0b1, 5
#define HWA_ARGS_CKEN_TIMER6			RCC_APB1ENR, 0b1, 4
#define HWA_ARGS_CKEN_TIMER5			RCC_APB1ENR, 0b1, 3
#define HWA_ARGS_CKEN_TIMER4			RCC_APB1ENR, 0b1, 2
#define HWA_ARGS_CKEN_TIMER3			RCC_APB1ENR, 0b1, 1
#define HWA_ARGS_CKEN_TIMER2			RCC_APB1ENR, 0b1, 0

#endif
