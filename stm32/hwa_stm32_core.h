#ifndef HWA_STM32_CORE_H
#define HWA_STM32_CORE_H

#include "hwa_stm32_flash.h"

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

/* #undef HWA_ERROR */
/* #define HWA_ERROR(...) do {} while(0) */


/*	Convenient abstraction registers
 */
#define HWA_CORE_HWA_HSEHZ		, u32, -1,	 0, 0xFFFFFFFF
#define HWA_CORE_HWA_SYSHZ		, u32, -1, 8000000, 0xFFFFFFFF
#define HWA_CORE_HWA_AHBHZ		, u32, -1,       0, 0xFFFFFFFF
#define HWA_CORE_HWA_APB1HZ		, u32, -1,       0, 0xFFFFFFFF
#define HWA_CORE_HWA_APB2HZ		, u32, -1,       0, 0xFFFFFFFF

/*	Hardware registers
 */
#define HWA_CORE0_BASE			HWA_AHB+0x9000	/* 0x40021000 */

#define HWA_CORE_HWA_CR			volatile, u32, 0x00, 0x00000083, 0x010D00F9
#define HWA_CORE_HWA_CFGR		volatile, u32, 0x04, 0x00000000, 0x077FFFF3
#define HWA_CORE_HWA_CIR		volatile, u32, 0x08, 0x00000000, 0x00001F00
#define HWA_CORE_HWA_BDCR		volatile, u32, 0x20, 0x00000000, 0x00018305
#define HWA_CORE_HWA_CSR		volatile, u32, 0x24, 0x0C000000, 0xFD000001

#define HWA_CORE_PLL_RDY		HWA_CR,   0b1,      25
#define HWA_CORE_PLLON			HWA_CR,   0b1,      24
#define HWA_CORE_HSE_BPY		HWA_CR,   0b1,      18
#define HWA_CORE_HSE_RDY		HWA_CR,   0b1,      17
#define HWA_CORE_HSE_ON			HWA_CR,   0b1,      16
#define HWA_CORE_HSE_CR			HWA_CR,   0b101,    16
#define HWA_CORE_HSIRDY			HWA_CR,   0b1,      1
#define HWA_CORE_HSION			HWA_CR,   0b1,      0

#define HWA_CORE_PLLMUL			HWA_CFGR, 0b1111,   18

#define HWA_CORE_PLL_SRC		HWA_CFGR, 0b11,     16	/* PLLXPTRE, PLLSRC */
#define HWA_CORE_PLL_SRC_HSI_DIV2	0b00			/* RESET */
#define HWA_CORE_PLL_SRC_HSE		0b01
#define HWA_CORE_PLL_SRC_HSE_DIV2	0b10

#define HWA_CORE_PPRE2			HWA_CFGR, 0b111,    11
#define HWA_CORE_PPRE1			HWA_CFGR, 0b111,    8
#define HWA_CORE_PPRE_			0x0			/* RESET */
#define HWA_CORE_PPRE_DIV2		0x4
#define HWA_CORE_PPRE_DIV4		0x5
#define HWA_CORE_PPRE_DIV8		0x6
#define HWA_CORE_PPRE_DIV16		0x7

#define HWA_CORE_HPRE			HWA_CFGR, 0b1111,   4
#define HWA_CORE_HPRE_			0x0			/* RESET */
#define HWA_CORE_HPRE_DIV2		0x8
#define HWA_CORE_HPRE_DIV4		0x9
#define HWA_CORE_HPRE_DIV8		0xA
#define HWA_CORE_HPRE_DIV16		0xB
#define HWA_CORE_HPRE_DIV64		0xC
#define HWA_CORE_HPRE_DIV128		0xD
#define HWA_CORE_HPRE_DIV256		0xE
#define HWA_CORE_HPRE_DIV512		0xF

#define HWA_CORE_SW			HWA_CFGR, 0b11,     0
#define HWA_CORE_SW_HSI			0b00			/* RESET */
#define HWA_CORE_SW_HSE			0b01
#define HWA_CORE_SW_PLL			0b10

#define HWA_CORE_PLL_CFGR_MASK		HWA_CFGR, 0b111111, 16


typedef struct {
  u8	commit ;
  HWA_PDCL()
  HWA_VDCL(HWA_CORE, HWA_CR);
  HWA_VDCL(HWA_CORE, HWA_CFGR);

  HWA_VDCL(HWA_CORE, HWA_HSEHZ);
  HWA_VDCL(HWA_CORE, HWA_SYSHZ);
  HWA_VDCL(HWA_CORE, HWA_AHBHZ);
  HWA_VDCL(HWA_CORE, HWA_APB1HZ);
  HWA_VDCL(HWA_CORE, HWA_APB2HZ);
} HWA_CORE ;


#define hwa_begin_core(reset)				\
  HWA_PINIT(HWA_CORE, HWA_CORE0)			\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_CR, reset);	\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_CFGR, reset);	\
  							\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_SYSHZ, reset);	\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_HSEHZ, 0);		\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_AHBHZ, reset);	\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_APB1HZ, reset);	\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_APB2HZ, reset);

#define hwa_commit_core()			\
  hwa_core_commit(HWA_CORE0, HWA_FLASH0)


#define hwa_core_reset()			\
  HWA_RESET(HWA_CORE, HWA_CORE0, HWA_CR);	\
  HWA_RESET(HWA_CORE, HWA_CORE0, HWA_CFGR);	\
						\
  HWA_RESET(HWA_CORE, HWA_CORE0, HWA_SYSHZ);	\
  HWA_RESET(HWA_CORE, HWA_CORE0, HWA_HSEHZ);	\
  HWA_RESET(HWA_CORE, HWA_CORE0, HWA_AHBHZ);	\
  HWA_RESET(HWA_CORE, HWA_CORE0, HWA_APB1HZ);	\
  HWA_RESET(HWA_CORE, HWA_CORE0, HWA_APB2HZ);


/*	Minimal settings: SYSHZ
 */
inline void
hwa_core_commit ( HWA_CORE *core, HWA_FLASH *flash )
{
  u32	syshz, hsehz, ahbhz, apb1hz, apb2hz ;
  u8	sw, pllsrc, mul, pllmul, ppre1, ppre2 ;
  u16	hpre ;

  if ( !core->used )
    return ;


  /*  SYSHZ change while using PLL
   *    -- switch to HSE
   *    -- stop PLL
   *	PLL will be reconfigured afterwards
   */
  if ( core->commit &&
       HWA_SR(core, HWA_SYSHZ, mmask) &&
       ((HWA_SMSK(HWA_CORE, core, omask, HWA_CORE_SW) &&
  	 HWA_GETSB(HWA_CORE, core, ovalue, HWA_CORE_SW) == HWA_CORE_SW_PLL) ||
  	(HWA_SMSK(HWA_CORE, core, omask, HWA_CORE_SW) == 0))
       ) {
    HWA_SETVB(HWA_CORE, core, HWA_CORE_SW, HWA_CORE_SW_HSE);
    HWA_COMMIT(core, HWA_CORE, core, HWA_BREG(HWA_CORE_SW));
    HWA_SETVB(HWA_CORE, core, HWA_CORE_PLLON, 0);
    HWA_COMMIT(core, HWA_CORE, core, HWA_BREG(HWA_CORE_PLLON));
  }

  syshz  = HWA_GETVR(core, HWA_SYSHZ,  0);
  hsehz  = HWA_GETVR(core, HWA_HSEHZ,  0);
  ahbhz  = HWA_GETVR(core, HWA_AHBHZ,  0);
  apb1hz = HWA_GETVR(core, HWA_APB1HZ, 0);
  apb2hz = HWA_GETVR(core, HWA_APB2HZ, 0);

  /* hpre   = HWA_GETVB(core, HWA_CORE_HPRE,  0xFF); */
  /* if ( hpre != 0xFF ) */
  /*   if ( (hpre & 0b1000) == 0 ) */
  /*     hpre = 1 ; */
  /*   else */
  /*     hpre = 1<<( ((hpre & 0b0111)+1) + ((hpre & 0b0100) >> 2) ) ; */
  /* else */
  /*   hpre = 0 ; */

  /* ppre1  = HWA_GETVB(core, HWA_CORE_PPRE1, 0xFF); */
  /* if ( ppre1 != 0xFF ) */
  /*   if ( (ppre1 & 0b100) == 0 ) */
  /*     ppre1 = 1 ; */
  /*   else */
  /*     ppre1 = 1<<((ppre1 & 0b011)+1) ; */
  /* else */
  /*   ppre1 = 0 ; */

  /* ppre2  = HWA_GETVB(core, HWA_CORE_PPRE2, 0xFF); */
  /* if ( ppre2 != 0xFF ) */
  /*   if ( (ppre2 & 0b100) == 0 ) */
  /*     ppre2 = 1 ; */
  /*   else */
  /*     ppre2 = 1<<((ppre2 & 0b011)+1) ; */
  /* else */
  /*   ppre2 = 0 ; */
      

  if ( syshz == 0 ) HWA_ERROR("SYSHZ must be defined.");

  /*  If not constrained, set ahbhz, apb1hz and abp2hz to maximum
   */

  if ( ahbhz == 0 ) {
    ahbhz = syshz ;
    HWA_SETVR(HWA_CORE, core, HWA_AHBHZ, ahbhz);
  }

  if ( apb1hz == 0 ) {
    if ( ahbhz > 36000000 )
      apb1hz = ahbhz / 2 ;
    else
      apb1hz = ahbhz ;
    HWA_SETVR(HWA_CORE, core, HWA_APB1HZ, apb1hz);
  }

  if ( apb2hz == 0 ) {
    apb2hz = ahbhz ;
    HWA_SETVR(HWA_CORE, core, HWA_APB2HZ, apb2hz);
  }

  hpre  = syshz / ahbhz ;
  ppre1 = ahbhz / apb1hz ;
  ppre2 = ahbhz / apb2hz ;

  if ( ahbhz * hpre != syshz )   HWA_ERROR("");
  if ( apb1hz * ppre1 != ahbhz ) HWA_ERROR("");
  if ( apb1hz > 36000000 )	 HWA_ERROR("APB1 frequency > 36 MHz.");
  if ( apb2hz * ppre2 != ahbhz ) HWA_ERROR("");


  if (HWA_GETSB(HWA_CORE, core, mmask, HWA_CORE_SW) == 0)
    sw = 0xFF ; /* 0xFF == NOT SET */
  else
    sw = HWA_GETSB(HWA_CORE, core, mvalue, HWA_CORE_SW) ;

  if (HWA_GETSB(HWA_CORE, core, mmask, HWA_CORE_PLL_SRC) == 0)
    pllsrc = 0xFF ; /* 0xFF == NOT SET */
  else
    pllsrc = HWA_GETSB(HWA_CORE, core, mvalue, HWA_CORE_PLL_SRC) ;

  if (HWA_GETSB(HWA_CORE, core, mmask, HWA_CORE_PLLMUL) == 0)
    pllmul = 0 ;
  else
    pllmul = HWA_GETSB(HWA_CORE, core, mvalue, HWA_CORE_PLLMUL) + 2;

  /*	Try SW = HSE
   */
  if ( hsehz != 0
       && syshz == hsehz
       && (sw == 0xFF || sw == HWA_CORE_SW_HSE) ) {
    sw = HWA_CORE_SW_HSE ;
    goto sysclk_done ;
  }

  /*	Try SW = PLL(HSE)
   */
  if ( hsehz != 0
       && (mul = syshz / hsehz) * hsehz == syshz
       && mul >= 2 && mul <= 16
       && (sw == 0xFF || sw == HWA_CORE_SW_PLL)
       && (pllsrc == 0xFF || pllsrc == HWA_CORE_PLL_SRC_HSE)
       && (pllmul == 0 || pllmul == mul) ) {
    sw = HWA_CORE_SW_PLL ;
    pllsrc = HWA_CORE_PLL_SRC_HSE ;
    pllmul = mul ;
    goto sysclk_done ;
  }

  /*	Try SW = PLL(HSE/2)
   */
  if ( hsehz != 0
       && (mul = 2 * syshz / hsehz) * hsehz == 2 * syshz
       && mul >= 2 && mul <= 16
       && (sw == 0xFF || sw == HWA_CORE_SW_PLL)
       && (pllsrc == 0xFF || pllsrc == HWA_CORE_PLL_SRC_HSE_DIV2)
       && (pllmul == 0 || pllmul == mul) ) {
    sw = HWA_CORE_SW_PLL ;
    pllsrc = HWA_CORE_PLL_SRC_HSE_DIV2 ;
    pllmul = mul ;
    goto sysclk_done ;
  }

  /*	Try SW = HSI
   */
  if ( syshz == 8000000
       && (sw == 0xFF || sw == HWA_CORE_SW_HSI) ) {
    sw = HWA_CORE_SW_HSI ;
    goto sysclk_done ;
  }

  /*	Try SW = PLL(HSI/2)
   */
  if ( (mul = syshz / 4000000) * 4000000 == syshz
       && mul >= 2 && mul <= 16
       && (sw == 0xFF || sw == HWA_CORE_SW_PLL)
       && (pllsrc == 0xFF || pllsrc == HWA_CORE_PLL_SRC_HSI_DIV2)
       && (pllmul == 0 || pllmul == mul) ) {
    sw = HWA_CORE_SW_PLL ;
    pllsrc = HWA_CORE_PLL_SRC_HSI_DIV2 ;
    pllmul = mul ;
  }
 sysclk_done:


  /*	Check SYSCLK configuration.
   *	TODO: detail errors.
   */
  if ( sw == 0xFF
       || (sw == HWA_CORE_SW_PLL
	   && (pllmul <2 || pllmul >16
	       || pllsrc == 0xFF
	       || (pllsrc == HWA_CORE_PLL_SRC_HSE && syshz != mul * hsehz)
	       || (pllsrc == HWA_CORE_PLL_SRC_HSE_DIV2 && syshz != mul * hsehz/2)
	       || (pllsrc == HWA_CORE_PLL_SRC_HSI_DIV2 && syshz != mul * 4000000)))
       || (sw == HWA_CORE_SW_HSE && syshz != hsehz)
       || (sw == HWA_CORE_SW_HSI && syshz != 8000000)
       || syshz < 4000000 || syshz > 72000000 )
    HWA_ERROR("Invalid SYSCLK configuration.");

  HWA_SETVB(HWA_CORE, core, HWA_CORE_SW, sw);
  if ( pllsrc != 0xFF )
    HWA_SETVB(HWA_CORE, core, HWA_CORE_PLL_SRC, pllsrc);
  if ( pllmul != 0 )
    HWA_SETVB(HWA_CORE, core, HWA_CORE_PLLMUL, pllmul-2);


  /*	If HSE is used, HSE OSC must be started
   */
  if ( sw == HWA_CORE_SW_HSE
       || (sw == HWA_CORE_SW_PLL
	   && (pllsrc == HWA_CORE_PLL_SRC_HSE
	       || pllsrc == HWA_CORE_PLL_SRC_HSE_DIV2)))
    HWA_SETVB(HWA_CORE, core, HWA_CORE_HSE_ON, 1);


  /*	Check and encode HPRE
   */
#if 1
    if ( hpre == 1 )
      hpre = 0b0000 ;
    else if ( hpre == 2 )
      hpre = 0b1000 ;
    else if ( hpre == 4 )
      hpre = 0b1001 ;
    else if ( hpre == 8 )
      hpre = 0b1010 ;
    else if ( hpre == 16 )
      hpre = 0b1011 ;
    else if ( hpre == 64 )
      hpre = 0b1100 ;
    else if ( hpre == 128 )
      hpre = 0b1101 ;
    else if ( hpre == 256 )
      hpre = 0b1110 ;
    else if ( hpre == 512 )
      hpre = 0b1111 ;
    else
      HWA_ERROR("HPRE invalid.");
#else
  hpre = /* HWA_LOG2 */ hwa_log2_ceil(hpre);
  if ( hpre < 0 || hpre > 9 )
    HWA_ERROR("HPRE invalid.");
  else {
  }
#endif
  HWA_SETVB(HWA_CORE, core, HWA_CORE_HPRE, hpre);


  /*	Check and encode PPRE1
   */
  if ( ppre1 == 0xFF )
    HWA_ERROR("");
  else if ( ppre1 == 1 )
    ppre1 = 0b000 ;
  else if ( ppre1 == 2 )
    ppre1 = 0b100 ;
  else if ( ppre1 == 4 )
    ppre1 = 0b101 ;
  else if ( ppre1 == 8 )
    ppre1 = 0b110 ;
  else if ( ppre1 == 16 )
    ppre1 = 0b111 ;
  else
    HWA_ERROR("PPRE1 invalid.");

  HWA_SETVB(HWA_CORE, core, HWA_CORE_PPRE1, ppre1);


  /*	Check and encode PPRE2
   */
  if ( ppre2 == 0xFF )
    HWA_ERROR("");
  else if ( ppre2 == 1 )
    ppre2 = 0b000 ;
  else if ( ppre2 == 2 )
    ppre2 = 0b100 ;
  else if ( ppre2 == 4 )
    ppre2 = 0b101 ;
  else if ( ppre2 == 8 )
    ppre2 = 0b110 ;
  else if ( ppre2 == 16 )
    ppre2 = 0b111 ;
  else
    HWA_ERROR("PPRE2 invalid.");

  HWA_SETVB(HWA_CORE, core, HWA_CORE_PPRE2, ppre2);

  /*	Flash latency. Prefetch buffer is ON after reset.
   *	Commit flash latency before SYSCLK switch to high-speed.
   */
  /*	Note: The prefetch buffer must be kept on when using a prescaler different
   *	from 1 on the AHB clock. Refer to Reading the Flash memory on page 52
   *	section for more details.
   */
  if ( HWA_GETSB(HWA_FLASH, flash, mmask, HWA_FLASH_LATENCY) == 0 ) {
    if (syshz < 24000000)
      HWA_SETVB(HWA_FLASH, flash, HWA_FLASH_LATENCY, HWA_FLASH_LATENCY_0WS);
    else if (syshz < 48000000)
      HWA_SETVB(HWA_FLASH, flash, HWA_FLASH_LATENCY, HWA_FLASH_LATENCY_1WS);
    else
      HWA_SETVB(HWA_FLASH, flash, HWA_FLASH_LATENCY, HWA_FLASH_LATENCY_2WS);
  }
  HWA_COMMIT(core, HWA_FLASH, flash, HWA_ACR);

  /*	RM0008: The PLL configuration (selection of HSI oscillator divided by 2 or HSE
   *	oscillator for PLL input clock, and multiplication factor) must be done
   *	before enabling the PLL. Once the PLL enabled, these parameters cannot
   *	be changed.
   *	Caution: The PLL output frequency must not exceed 72 MHz.
   */
  /*	Set PLL and other device clocks configuration (PLL not enabled yet)
   */
  HWA_COMMIT(core, HWA_CORE, core, HWA_CFGR);
  HWA_COMMIT(core, HWA_CORE, core, HWA_CR);

  /*	Enable PLL. Sysclock will be switched automatically to PLL when PLL
   *	and its source are ready. No need to wait!
   */
  if ( sw == HWA_CORE_SW_PLL ) {
    HWA_SETVB(HWA_CORE, core, HWA_CORE_PLLON, 1);
    HWA_COMMIT(core, HWA_CORE, core, HWA_CR);
  }

  /*  Always commit convenient registers
   */
  HWA_COMMIT(core, HWA_CORE, core, HWA_SYSHZ);
  HWA_COMMIT(core, HWA_CORE, core, HWA_HSEHZ);
  HWA_COMMIT(core, HWA_CORE, core, HWA_AHBHZ);
  HWA_COMMIT(core, HWA_CORE, core, HWA_APB1HZ);
  HWA_COMMIT(core, HWA_CORE, core, HWA_APB2HZ);

  core->used = 0 ;
}


/************************************************************************
 *									*
 *			Synchronous actions				*
 *									*
 ************************************************************************/

#define hw_core_wait_pll_ready()				\
  while ( ! HW_TSTHB(HWA_CORE, HWA_CORE0, HWA_CORE_PLL_RDY) )

#define hw_core_sleep_until_interrupt()	__asm__ volatile("wfi.w")

/************************************************************************
 *									*
 *			Asynchronous actions				*
 *									*
 ************************************************************************/

#define hwa_core_set_xso_hz(hz)			\
  HWA_SETVR(HWA_CORE, HWA_CORE0, HWA_HSEHZ, hz)

#define hwa_core_set_sys_hz(hz)			\
  HWA_SETVR(HWA_CORE, HWA_CORE0, HWA_SYSHZ, hz)

#define hwa_core_set_ahb_hz(hz)  HWA_SETVR(HWA_CORE, HWA_CORE0, HWA_AHBHZ,  hz)
#define hwa_core_set_apb1_hz(hz) HWA_SETVR(HWA_CORE, HWA_CORE0, HWA_APB1HZ, hz)
#define hwa_core_set_apb2_hz(hz) HWA_SETVR(HWA_CORE, HWA_CORE0, HWA_APB2HZ, hz)

#endif
