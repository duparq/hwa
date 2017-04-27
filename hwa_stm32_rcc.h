#ifndef HWA_STM32_RCC_H
#define HWA_STM32_RCC_H

/************************************************************************
 *									*
 *			Synchronous actions				*
 *									*
 ************************************************************************/

/* #define hw_disable_and_clear_irqs()		\ */
/*   *HWA_RCC_CIR = 0x009F0000 ; */

#define hw_rcc_hse_is_ready()			\
  (HWA_HBITS(RCC, HSERDY) != 0)


#define hw_rcc_pll_is_ready()			\
  (HWA_HBITS(RCC, PLLRDY) !=0 )


/************************************************************************
 *									*
 *			Asynchronous actions				*
 *									*
 ************************************************************************/

#define PLLRDY				CR, 0b1,   25
#define PLLON				CR, 0b1,   24
#define HSEBPY				CR, 0b1,   18
#define HSERDY				CR, 0b1,   17
#define HSEON				CR, 0b1,   16
#define HSE_CR				CR, 0b101, 16

#define PLLMUL				CFGR, 0b1111, 18
#define PLLXPTRE			CFGR, 0b1,    17
#define PLLSRC				CFGR, 0b1,    16
#define PPRE2				CFGR, 0b111,  11
#define PPRE1				CFGR, 0b111,  8
#define HPRE				CFGR, 0b1111, 4
#define SW				CFGR, 0b11,   0

#define PLLXSRC				CFGR, 0b11,     16
#define PLL_CFGR_MASK			CFGR, 0b111111, 16


#define hwa_rcc_turn_hse(state)			\
  HWA_SET(RCC, HSEON, HWA_STATE_##state)

#define hwac_rcc_turn_hse(state)		\
  do {						\
    HWA_SET(RCC, HSEON, HWA_STATE_##state);	\
    HWA_COMMIT(RCC, HSEON);			\
  } while(0)

/*	!!!
 */
#define hwa_rcc_commit_hse()			\
  do {\
  if ( VBITS(RCC, PLL_CFGR_MASK, mvmask) != 0 )\
    HWA_COMMIT_
  HWA_COMMIT(RCC, HSE_CR)


/* Note: The prefetch buffer must be kept on when using a prescaler different
 *	from 1 on the AHB clock. Refer to Reading the Flash memory on page 52
 *	section for more details.  
 */
#define hwa_rcc_connect_ahb(clk)		\
  HWA_SET(RCC, HPRE, HWA_HCLK_##clk)

#define HWA_HCLK_SYSCLK			0x0 /* default */
#define HWA_HCLK_SYSCLK_DIV2		0x8
#define HWA_HCLK_SYSCLK_DIV4		0x9
#define HWA_HCLK_SYSCLK_DIV8		0xA
#define HWA_HCLK_SYSCLK_DIV16		0xB
#define HWA_HCLK_SYSCLK_DIV64		0xC
#define HWA_HCLK_SYSCLK_DIV128		0xD
#define HWA_HCLK_SYSCLK_DIV256		0xE
#define HWA_HCLK_SYSCLK_DIV512		0xF

#define hwa_rcc_connect_apb1(clk)		\
  HWA_SET(RCC, PPRE1, HWA_PCLK_##clk)

#define hwa_rcc_connect_apb2(clk)		\
  HWA_SET(RCC, PPRE2, HWA_PCLK_##clk)

#define HWA_PCLK_HCLK			0x0 /* default */
#define HWA_PCLK_HCLK_DIV2		0x4
#define HWA_PCLK_HCLK_DIV4		0x5
#define HWA_PCLK_HCLK_DIV8		0x6
#define HWA_PCLK_HCLK_DIV16		0x7

/*	The PLL configuration (selection of HSI oscillator divided by 2 or HSE
 *	oscillator for PLL input clock, and multiplication factor) must be done
 *	before enabling the PLL. Once the PLL enabled, these parameters cannot
 *	be changed.
 */
#define hwa_rcc_connect_pll(src)		\
  HWA_SET(RCC, PLLXSRC, HWA_PLLXSRC_##src)

#define HWA_PLLXSRC_HSI_DIV2		0b00 /* default */
#define HWA_PLLXSRC_HSE			0b01
#define HWA_PLLXSRC_HSE_DIV2		0b10

/*	The PLL configuration (selection of HSI oscillator divided by 2 or HSE
 *	oscillator for PLL input clock, and multiplication factor) must be done
 *	before enabling the PLL. Once the PLL enabled, these parameters cannot
 *	be changed.
 */
/*	PLLMUL can be written only when PLL is disabled.
 *	Caution: The PLL output frequency must not exceed 72 MHz.
 */
#define hwa_rcc_set_pllmul(mul)						\
  do {									\
    if ( hwa_checking_policy != HWA_CHECKING_POLICY_NONE ) {		\
      if ( HWA_VBITS(RCC, PLLON, ovmask) != 1 ) {			\
	if ( hwa_checking_policy == HWA_CHECKING_POLICY_COMPILE_TIME )	\
	  HWA_WARN_CT(1, "Can not check that the PLL is turned off.");	\
      } else if ( HWA_VBITS(RCC, PLLON, mvalue) == 1 )			\
	HWA_ERROR_CT(2, "PLL must be off.");				\
      if ( hwa_checking_policy == HWA_CHECKING_POLICY_RUN_TIME		\
	   && HWA_HBITS(RCC, PLLON) == 1)				\
	HWA_ERROR_RT(3, "PLL must be off.");				\
    }									\
    if ( HWA_PLLMUL_##mul != HWA_PLLMUL_AUTO ) {			\
      HWA_SET(RCC, PLLMUL, HWA_PLLMUL_##mul);				\
    } else if (HWA_VBITS(RCC, PLLXSRC, mvalue) == HWA_PLLXSRC_HSI_DIV2) { \
      HWA_SET(RCC, PLLMUL, (SYSCLK_HZ/4000000)-2) ;			\
    } else if (HWA_VBITS(RCC, PLLXSRC, mvalue) == HWA_PLLXSRC_HSE) {	\
      HWA_SET(RCC, PLLMUL, (SYSCLK_HZ/XSOHZ)-2) ;			\
    } else if (HWA_VBITS(RCC, PLLXSRC, mvalue) == HWA_PLLXSRC_HSE_DIV2) { \
      HWA_SET(RCC, PLLMUL, (2*SYSCLK_HZ/XSOHZ)-2) ;			\
    }									\
  } while(0)

#define HWA_PLLMUL_2			0x0
#define HWA_PLLMUL_3			0x1
#define HWA_PLLMUL_4			0x2
#define HWA_PLLMUL_5			0x3
#define HWA_PLLMUL_6			0x4
#define HWA_PLLMUL_7			0x5
#define HWA_PLLMUL_8			0x6
#define HWA_PLLMUL_9			0x7
#define HWA_PLLMUL_10			0x8
#define HWA_PLLMUL_11			0x9
#define HWA_PLLMUL_12			0x10
#define HWA_PLLMUL_13			0x11
#define HWA_PLLMUL_14			0x12
#define HWA_PLLMUL_15			0x13
#define HWA_PLLMUL_16			0x14
#define HWA_PLLMUL_AUTO			0xff

/*	Commit PLL-related registers.
 *	RCC_CFGR, 0b1111, 18	: HWA_PLLMUL
 *	RCC_CFGR, 0b11, 16	: HWA_PLLSRC
 *
 *	Note: PLL must be configured before beeing turned on. This is ensured
 *	by commiting CFGR first, and then CR.
 */
#define hwa_rcc_commit_pll()			\
  do {						\
    HWA_COMMIT(RCC, CFGR, -1, 0);		\
    HWA_COMMIT(RCC, CR, -1, 0);			\
  } while(0)

#define hwa_rcc_connect_sysclk(clk)		\
  HWA_SET(RCC, SW, HWA_SYSCLK_##clk)

#define HWA_SYSCLK_HSI			0x0 /* default */
#define HWA_SYSCLK_HSE			0x1
#define HWA_SYSCLK_PLL			0x2



/*	Set up internal clocks
 */
#define hwac_rcc_init()						\
  hwa_rcc_turn_hse(ON);						\
  hwa_rcc_connect_ahb(SYSCLK);					\
  hwa_rcc_connect_apb1(HCLK_DIV2);				\
  hwa_rcc_connect_apb2(HCLK);					\
  hwa_rcc_connect_pll(HSE);					\
  hwa_set_pllmul(AUTO);						\
  HWA_COMMIT(u32, RCC, CFGR);					\
  hwa_rcc_turn_pll(ON);						\
  hwa_flash_turn_prefetch_buffer(ON); /* ON after reset */	\
  hwa_flash_set_latency(AUTO);					\
  hwa_rcc_commit_hse();						\
  hwa_wait_hse_ready();						\
  hwa_rcc_commit_pll();						\
  hwa_wait_pll_ready();						\
  hwa_rcc_connect_sysclk(PLL);					\
  hwa_commit();

#define hwa_rcc_turn_pll(state)						\
  HWA_SET(RCC, PLLON, HWA_STATE_##state);


#define hwa_rcc_turn_clk(pname, state)					\
  HWA_VSET_VA(u32, HWA_G2(HWA_RCC_TURN_CLK_VA, pname), HWA_STATE_##state)

#define HWA_RCC_TURN_CLK_VA_TIMER11			RCC, APB2ENR, 0b1, 21
#define HWA_RCC_TURN_CLK_VA_TIMER10			RCC, APB2ENR, 0b1, 20
#define HWA_RCC_TURN_CLK_VA_TIMER9			RCC, APB2ENR, 0b1, 19
#define HWA_RCC_TURN_CLK_VA_ADC3			RCC, APB2ENR, 0b1, 15
#define HWA_RCC_TURN_CLK_VA_USART1			RCC, APB2ENR, 0b1, 14
#define HWA_RCC_TURN_CLK_VA_TIMER8			RCC, APB2ENR, 0b1, 13
#define HWA_RCC_TURN_CLK_VA_SPI1			RCC, APB2ENR, 0b1, 12
#define HWA_RCC_TURN_CLK_VA_TIMER1			RCC, APB2ENR, 0b1, 11
#define HWA_RCC_TURN_CLK_VA_ADC2			RCC, APB2ENR, 0b1, 10
#define HWA_RCC_TURN_CLK_VA_ADC1			RCC, APB2ENR, 0b1, 9
#define HWA_RCC_TURN_CLK_VA_PORTG			RCC, APB2ENR, 0b1, 8
#define HWA_RCC_TURN_CLK_VA_PORTF			RCC, APB2ENR, 0b1, 7
#define HWA_RCC_TURN_CLK_VA_PORTE			RCC, APB2ENR, 0b1, 6
#define HWA_RCC_TURN_CLK_VA_PORTD			RCC, APB2ENR, 0b1, 5
#define HWA_RCC_TURN_CLK_VA_PORTC			RCC, APB2ENR, 0b1, 4
#define HWA_RCC_TURN_CLK_VA_PORTB			RCC, APB2ENR, 0b1, 3
#define HWA_RCC_TURN_CLK_VA_PORTA			RCC, APB2ENR, 0b1, 2
#define HWA_RCC_TURN_CLK_VA_AFIO			RCC, APB2ENR, 0b1, 0

#define HWA_RCC_TURN_CLK_VA_DAC			RCC, APB1ENR, 0b1, 29
#define HWA_RCC_TURN_CLK_VA_PWR			RCC, APB1ENR, 0b1, 28
#define HWA_RCC_TURN_CLK_VA_BKP			RCC, APB1ENR, 0b1, 27
#define HWA_RCC_TURN_CLK_VA_CAN			RCC, APB1ENR, 0b1, 25
#define HWA_RCC_TURN_CLK_VA_USB			RCC, APB1ENR, 0b1, 23
#define HWA_RCC_TURN_CLK_VA_I2C2			RCC, APB1ENR, 0b1, 22
#define HWA_RCC_TURN_CLK_VA_I2C1			RCC, APB1ENR, 0b1, 21
#define HWA_RCC_TURN_CLK_VA_UART5			RCC, APB1ENR, 0b1, 20
#define HWA_RCC_TURN_CLK_VA_UART4			RCC, APB1ENR, 0b1, 19
#define HWA_RCC_TURN_CLK_VA_USART3			RCC, APB1ENR, 0b1, 18
#define HWA_RCC_TURN_CLK_VA_USART2			RCC, APB1ENR, 0b1, 17
#define HWA_RCC_TURN_CLK_VA_SPI3			RCC, APB1ENR, 0b1, 15
#define HWA_RCC_TURN_CLK_VA_SPI2			RCC, APB1ENR, 0b1, 14
#define HWA_RCC_TURN_CLK_VA_WWDG			RCC, APB1ENR, 0b1, 11
#define HWA_RCC_TURN_CLK_VA_TIMER14			RCC, APB1ENR, 0b1, 8
#define HWA_RCC_TURN_CLK_VA_TIMER13			RCC, APB1ENR, 0b1, 7
#define HWA_RCC_TURN_CLK_VA_TIMER12			RCC, APB1ENR, 0b1, 6
#define HWA_RCC_TURN_CLK_VA_TIMER7			RCC, APB1ENR, 0b1, 5
#define HWA_RCC_TURN_CLK_VA_TIMER6			RCC, APB1ENR, 0b1, 4
#define HWA_RCC_TURN_CLK_VA_TIMER5			RCC, APB1ENR, 0b1, 3
#define HWA_RCC_TURN_CLK_VA_TIMER4			RCC, APB1ENR, 0b1, 2
#define HWA_RCC_TURN_CLK_VA_TIMER3			RCC, APB1ENR, 0b1, 1
#define HWA_RCC_TURN_CLK_VA_TIMER2			RCC, APB1ENR, 0b1, 0
#endif


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_RCC			HWA_AHB+0x9000		/* 0x40021000 */

#define HWA_RCC_CR			volatile, u32, HWA_RCC+0x00	/* 0x40021000 */
#define HWA_RCC_CFGR		volatile, u32, HWA_RCC+0x04 /* 0x40021004 */
#define HWA_RCC_CIR			volatile, u32, HWA_RCC+0x08 /* 0x40021008 */
#define HWA_RCC_APB2RSTR		volatile, u32, HWA_RCC+0x0C /* 0x4002100C */
#define HWA_RCC_APB1RSTR		volatile, u32, HWA_RCC+0x10 /* 0x40021010 */
#define HWA_RCC_AHBENR		volatile, u32, HWA_RCC+0x14 /* 0x40021014 */
#define HWA_RCC_APB2ENR		volatile, u32, HWA_RCC+0x18 /* 0x40021018 */
#define HWA_RCC_APB1ENR		volatile, u32, HWA_RCC+0x1C /* 0x4002101C */
#define HWA_RCC_BDCR		volatile, u32, HWA_RCC+0x20 /* 0x40021020 */
#define HWA_RCC_CSR			volatile, u32, HWA_RCC+0x24 /* 0x40021024 */

#define hwa_rcc_begin(state)					\
  HWA_VDCL(RCC, CR,       0x00000083, 0x010D00F9, state)	\
  HWA_VDCL(RCC, CFGR,     0x00000000, 0x077FFFF3, state)	\

/* HWA_VDCL(RCC, CIR,      0x00000000, 0x00001F00, state)	\ */
/* HWA_VDCL(RCC, APB2RSTR, 0x00000000, 0x0038FFFD, state)	\ */
/* HWA_VDCL(RCC, APB1RSTR, 0x00000000, 0x3AFEC9FF, state)	\ */
/* HWA_VDCL(RCC, AHBENR,   0x00000014, 0x00000557, state)	\ */
/* HWA_VDCL(RCC, APB2ENR,  0x00000000, 0x0038FFFD, state)	\ */
/* HWA_VDCL(RCC, APB1ENR,  0x00000000, 0x3AFEC9FF, state)	\ */
/* HWA_VDCL(RCC, BDCR,     0x00000000, 0x00018305, state)	\ */
/* HWA_VDCL(RCC, CSR,      0x0C000000, 0xFD000001, state) */

#define hwa_rcc_commit()			\
  do {						\
    HWA_COMMIT(RCC, CR, -1, 0);			\
    HWA_COMMIT(RCC, CFGR);			\
  } while(0)

/* HWA_RCC_COMMIT(RCC, CIR);			\ */
/* HWA_RCC_COMMIT(RCC, APB2RSTR);		\ */
/* HWA_RCC_COMMIT(RCC, APB1RSTR);		\ */
/* HWA_RCC_COMMIT(RCC, AHBENR);		\ */
/* HWA_RCC_COMMIT(RCC, APB2ENR);		\ */
/* HWA_RCC_COMMIT(RCC, APB1ENR);		\ */
/* HWA_RCC_COMMIT(RCC, BDCR);			\ */
/* HWA_RCC_COMMIT(RCC, CSR);			\ */



#if 0
#define hwa_rcc_connect_pin_outclk(clk)		\
  HWA_SET(RCC_CFGR, 0b111, 24, HWA_MCO_##clk)
#define HWA_MCO_NONE				0x0 /* default */
#define HWA_MCO_SYSCLK				0x4
#define HWA_MCO_HSI				0x5
#define HWA_MCO_HSE				0x6
#define HWA_MCO_PLL_DIV2			0x7

#define hwa_rcc_connect_usbclk(clk)		\
  HWA_SET(RCC_CFGR, 0b1, 22, HWA_USBCLK_##clk)
#define HWA_USBCLK_SYSCLK_DIV1_5		0x0 /* default */
#define HWA_USBCLK_SYSCLK			0x1

#define hwa_rcc_connect_pll(src)		\
  HWA_SET(RCC_CFGR, 0b11, 16, HWA_PLLSRC_##src)
#define HWA_PLLSRC_HSI_DIV2			0b00 /* default */
#define HWA_PLLSRC_HSE				0b01
#define HWA_PLLSRC_HSE_DIV2			0b10

#define hwa_rcc_connect_adcclk(clk)		\
  HWA_SET(RCC_CFGR, 0b11, 14, HWA_ADCLK_##clk)
#define HWA_ADCLK_PCLK2_DIV2			0x0 /* default */
#define HWA_ADCLK_PCLK2_DIV4			0x1
#define HWA_ADCLK_PCLK2_DIV6			0x2
#define HWA_ADCLK_PCLK2_DIV8			0x3

#define hwa_rcc_connect_apb2(clk)		\
  HWA_SET(RCC_CFGR, 0b111, 11, HWA_PCLK_##clk)
#define hwa_rcc_connect_apb1(clk)		\
  HWA_SET(RCC_CFGR, 0b111, 8, HWA_PCLK_##clk)
#define HWA_PCLK_HCLK				0x0 /* default */
#define HWA_PCLK_HCLK_DIV2			0x4
#define HWA_PCLK_HCLK_DIV4			0x5
#define HWA_PCLK_HCLK_DIV8			0x6
#define HWA_PCLK_HCLK_DIV16			0x7

#define hwa_rcc_connect_ahb(clk)		\
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
#define hwa_rcc_turn_pll(state)						\
  do {									\
    if ( HWA_STATE_##state == HWA_STATE_ON ) {				\
      if ( HWA_BITS(HWA_RCC_CFGR_mvmask, 0b111111, 16) != 0 ) {		\
	if ( hwa_rcc_commit_policy == HWA_RCC_COMMIT_POLICY_AUTO ) {	\
	  HWA_RCC_COMMIT(RCC_CFGR);					\
	} else {							\
	  HWA_WARN_CT(1, "PLL must be configured before being turned on."); \
	}								\
      }									\
    }									\
    HWA_SET(RCC_CR, 0b1, 24, HWA_STATE_##state);			\
  } while(0)

#define hwa_rcc_turn_clock_security(state)	\
  HWA_SET(RCC_CR, 0b1, 19, HWA_STATE_#state)

/*	State of HSE bypass cannot be changed if HSE is running.
 */
#define hwa_rcc_turn_hse_bypass(state)					\
  do {									\
    if ( hwa_rcc_commit_policy != HWA_RCC_COMMIT_POLICY_ALWAYS )	\
      if ( HWA_BITS(RCC_CR, 0b1, 16) == 1 )				\
	HWA_WARN_();							\
    HWA_SET(RCC_CR, 0b1, 18, HWA_STATE_##state)				\
      } while(0)


#define hwa_rcc_turn_hsi(state)			\
  HWA_SET(RCC_CR, 0b1, 0, HWA_STATE_##state)

#define hwa_wait_hsi_ready()						\
  do {									\
    if ( hwa_rcc_commit_policy == HWA_RCC_COMMIT_POLICY_AUTO )		\
      HWA_RCC_COMMIT(RCC_CR);						\
    if ( hwa_rcc_commit_policy != HWA_RCC_COMMIT_POLICY_ALWAYS )	\
      if ( HWA_BITS(RCC_CR, 0b1, 0) != 1 )				\
	hwa_warn();							\
    while (!(*HWA_RCC_CR & (1<<1))){}					\
  } while(0)

/*	Turn on/off peripheral clocking.
 *	"When the peripheral clock is not active, the peripheral register values
 *	may not be readable by software and the returned value is always 0x0."
 */
#define hwa_rcc_turn_clk(pname, state)		\
  _hwa_rcc_turn_clk(pname, state)

#define hwac_turn_clk(pname, state)		\
  _hwac_turn_clk(pname, state)

/* #define hwa_rcc_commit_clk(pname)			\ */
/*   _hwa_rcc_commit_clk(pname) */

#define hwa_deinit_rcc()			\
  hwa_start_hsi() ;				\
  rcc_config_commit();				\
  hwa_rcc_connect_output_clock(NONE) ;		\
  hwa_rcc_connect_adcclk(PCLK2_DIV2);		\
  hwa_rcc_connect_apb2(HCLK);			\
  hwa_rcc_connect_apb1(HCLK);			\
  hwa_rcc_connect_ahb(SYSCLK);			\
  hwa_rcc_connect_sysclk(HSI);			\
  rcc_config_commit();				\
  hwa_stop_pll();				\
  hwa_stop_clock_security();			\
  hwa_stop_hse();				\
  rcc_config_commit();				\
  hwa_disable_hse_bypass();			\
  rcc_config_commit();				\
  hwa_rcc_connect_usbclk(SYSCLK_DIV1_5);	\
  hwa_set_pllmul(2);				\
  hwa_rcc_connect_pll(HSI_DIV2);		\
  rcc_config_commit();				\
  RCC_CIR_sync = 1 ;				\
  RCC_CIR_mask = 0xffffffff ;			\
  RCC_CIR_value = 0x009F0000 ;			\
  rcc_config_commit();

#endif
