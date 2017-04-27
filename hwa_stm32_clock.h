#ifndef HWA_STM32_CLOCK_H
#define HWA_STM32_CLOCK_H

#include "hwa_stm32_flash.h"

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

/*	Non-committable registers
 */
#define HWA_CLOCK_HWA_HSEHZ		, u32, -1,	 0, 0xFFFFFFFF
#define HWA_CLOCK_HWA_SYSHZ		, u32, -1, 8000000, 0xFFFFFFFF
#define HWA_CLOCK_HWA_AHBHZ		, u32, -1, 8000000, 0xFFFFFFFF
#define HWA_CLOCK_HWA_APB1HZ		, u32, -1, 8000000, 0xFFFFFFFF
#define HWA_CLOCK_HWA_APB2HZ		, u32, -1, 8000000, 0xFFFFFFFF

/*	Hardware registers
 */
#define HWA_CLOCK0_BASE			HWA_AHB+0x9000	/* 0x40021000 */

#define HWA_CLOCK_HWA_CR		volatile, u32, 0x00, 0x00000083, 0x010D00F9
#define HWA_CLOCK_HWA_CFGR		volatile, u32, 0x04, 0x00000000, 0x077FFFF3
#define HWA_CLOCK_HWA_CIR		volatile, u32, 0x08, 0x00000000, 0x00001F00
#define HWA_CLOCK_HWA_BDCR		volatile, u32, 0x20, 0x00000000, 0x00018305
#define HWA_CLOCK_HWA_CSR		volatile, u32, 0x24, 0x0C000000, 0xFD000001

#define HWA_CLOCK_CR_PLL_RDY		HWA_CR,   0b1,      25
#define HWA_CLOCK_CR_PLL_ON		HWA_CR,   0b1,      24
#define HWA_CLOCK_CR_HSE_BPY		HWA_CR,   0b1,      18
#define HWA_CLOCK_CR_HSE_RDY		HWA_CR,   0b1,      17
#define HWA_CLOCK_CR_HSE_ON		HWA_CR,   0b1,      16
#define HWA_CLOCK_CR_HSE_CR		HWA_CR,   0b101,    16

#define HWA_CLOCK_CFGR_PLL_MUL		HWA_CFGR, 0b1111,   18

#define HWA_CLOCK_CFGR_PLL_SRC		HWA_CFGR, 0b11,     16	/* PLLXPTRE, PLLSRC */
#define HWA_CLOCK_CFGR_PLL_SRC_HSI_DIV2	0b00			/* RESET */
#define HWA_CLOCK_CFGR_PLL_SRC_HSE	0b01
#define HWA_CLOCK_CFGR_PLL_SRC_HSE_DIV2	0b10

#define HWA_CLOCK_CFGR_PPRE2		HWA_CFGR, 0b111,    11
#define HWA_CLOCK_CFGR_PPRE1		HWA_CFGR, 0b111,    8
#define HWA_CLOCK_CFGR_PPRE_		0x0			/* RESET */
#define HWA_CLOCK_CFGR_PPRE_DIV2	0x4
#define HWA_CLOCK_CFGR_PPRE_DIV4	0x5
#define HWA_CLOCK_CFGR_PPRE_DIV8	0x6
#define HWA_CLOCK_CFGR_PPRE_DIV16	0x7

#define HWA_CLOCK_CFGR_HPRE		HWA_CFGR, 0b1111,   4
#define HWA_CLOCK_CFGR_HPRE_		0x0			/* RESET */
#define HWA_CLOCK_CFGR_HPRE_DIV2	0x8
#define HWA_CLOCK_CFGR_HPRE_DIV4	0x9
#define HWA_CLOCK_CFGR_HPRE_DIV8	0xA
#define HWA_CLOCK_CFGR_HPRE_DIV16	0xB
#define HWA_CLOCK_CFGR_HPRE_DIV64	0xC
#define HWA_CLOCK_CFGR_HPRE_DIV128	0xD
#define HWA_CLOCK_CFGR_HPRE_DIV256	0xE
#define HWA_CLOCK_CFGR_HPRE_DIV512	0xF

#define HWA_CLOCK_CFGR_SW		HWA_CFGR, 0b11,     0
#define HWA_CLOCK_CFGR_SW_HSI		0b00			/* RESET */
#define HWA_CLOCK_CFGR_SW_HSE		0b01
#define HWA_CLOCK_CFGR_SW_PLL		0b10

#define HWA_CLOCK_CFGR_PLL_CFGR_MASK	HWA_CFGR, 0b111111, 16


typedef struct {
  HWA_PDCL();
  HWA_VDCL(HWA_CLOCK, HWA_CR);
  HWA_VDCL(HWA_CLOCK, HWA_CFGR);

  HWA_VDCL(HWA_CLOCK, HWA_HSEHZ);
  HWA_VDCL(HWA_CLOCK, HWA_SYSHZ);
  HWA_VDCL(HWA_CLOCK, HWA_AHBHZ);
  HWA_VDCL(HWA_CLOCK, HWA_APB1HZ);
  HWA_VDCL(HWA_CLOCK, HWA_APB2HZ);
} HWA_CLOCK ;


#define hwa_begin_clock(reset)				\
  HWA_PINIT(HWA_CLOCK, HWA_CLOCK0);			\
  HWA_VINIT(HWA_CLOCK, HWA_CLOCK0, HWA_CR, reset);	\
  HWA_VINIT(HWA_CLOCK, HWA_CLOCK0, HWA_CFGR, reset);	\
							\
  HWA_VINIT(HWA_CLOCK, HWA_CLOCK0, HWA_SYSHZ, reset);	\
  HWA_VINIT(HWA_CLOCK, HWA_CLOCK0, HWA_HSEHZ, 0);	\
  HWA_VINIT(HWA_CLOCK, HWA_CLOCK0, HWA_AHBHZ, reset);	\
  HWA_VINIT(HWA_CLOCK, HWA_CLOCK0, HWA_APB1HZ, reset);	\
  HWA_VINIT(HWA_CLOCK, HWA_CLOCK0, HWA_APB2HZ, reset);

#define hwa_commit_clock()						\
  _hwa_clock_commit(hwa_nocommit, HWA_P(HWA_CLOCK0), HWA_P(HWA_FLASH0))


/*	Minimal settings: SYSHZ
 */
inline void
_hwa_clock_commit ( u8 dry, HWA_CLOCK *p, HWA_FLASH *flash __attribute__((unused)))
{
  u8	sw, pllsrc, mul, pllmul, ppre1, ppre2 ;
  u16	hpre ;

  if ( !p->used )
    return ;

  u32 syshz = HWA_NVALP(p, HWA_SYSHZ) ;
  u32 hsehz = HWA_NVALP(p, HWA_HSEHZ) ;
  u32 ahbhz = HWA_NVALP(p, HWA_AHBHZ) ;
  u32 apb1hz = HWA_NVALP(p, HWA_APB1HZ) ;
  u32 apb2hz = HWA_NVALP(p, HWA_APB2HZ) ;

  /*	If this module is used, SYSHZ must be specified.
   */
  if ( syshz == HWA_NONE )
    HWA_ERROR("SYSHZ must be defined.");

  /*	Select highest possible busses clocks if not given
   */
  if ( ahbhz == HWA_NONE ) {
    ahbhz = syshz ;
    HWA_VSETP(HWA_CLOCK, p, HWA_AHBHZ, -1, 0, ahbhz);
  }

  if ( apb1hz == HWA_NONE ) {
    if ( ahbhz > 36000000 )
      apb1hz = ahbhz / 2 ;
    else
      apb1hz = ahbhz ;
    HWA_VSETP(HWA_CLOCK, p, HWA_APB1HZ, -1, 0, apb1hz);
    /* HWA_WARN(""); */
  }

  if ( apb2hz == HWA_NONE ) {
    apb2hz = ahbhz ;
    HWA_VSETP(HWA_CLOCK, p, HWA_APB2HZ, -1, 0, apb2hz);
  }


  if (HWA_VBITSP(HWA_CLOCK, p, HWA_CLOCK_CFGR_SW, mvmask) == 0)
    sw = 0xFF ;
  else
    sw = HWA_VBITSP(HWA_CLOCK, p, HWA_CLOCK_CFGR_SW, mvalue) ;

  if (HWA_VBITSP(HWA_CLOCK, p, HWA_CLOCK_CFGR_PLL_SRC, mvmask) == 0)
    pllsrc = 0xFF ;
  else
    pllsrc = HWA_VBITSP(HWA_CLOCK, p, HWA_CLOCK_CFGR_PLL_SRC, mvalue) ;

  if (HWA_VBITSP(HWA_CLOCK, p, HWA_CLOCK_CFGR_PLL_MUL, mvmask) == 0)
    pllmul = 0 ;
  else
    pllmul = HWA_VBITSP(HWA_CLOCK, p, HWA_CLOCK_CFGR_PLL_MUL, mvalue) + 2;

  /*	Try SW = HSE
   */
  if ( hsehz != HWA_NONE
       && syshz == hsehz
       && (sw == 0xFF || sw == HWA_CLOCK_CFGR_SW_HSE) ) {
    sw = HWA_CLOCK_CFGR_SW_HSE ;
    goto sysclk_done ;
  }

  /*	Try SW = PLL(HSE)
   */
  if ( hsehz != HWA_NONE
       && (mul = syshz / hsehz) * hsehz == syshz
       && mul >= 2 && mul <= 16
       && (sw == 0xFF || sw == HWA_CLOCK_CFGR_SW_PLL)
       && (pllsrc == 0xFF || pllsrc == HWA_CLOCK_CFGR_PLL_SRC_HSE)
       && (pllmul == 0 || pllmul == mul) ) {
    sw = HWA_CLOCK_CFGR_SW_PLL ;
    pllsrc = HWA_CLOCK_CFGR_PLL_SRC_HSE ;
    pllmul = mul ;
    goto sysclk_done ;
  }

  /*	Try SW = PLL(HSE/2)
   */
  if ( hsehz != HWA_NONE
       && (mul = 2 * syshz / hsehz) * hsehz == 2 * syshz
       && mul >= 2 && mul <= 16
       && (sw == 0xFF || sw == HWA_CLOCK_CFGR_SW_PLL)
       && (pllsrc == 0xFF || pllsrc == HWA_CLOCK_CFGR_PLL_SRC_HSE_DIV2)
       && (pllmul == 0 || pllmul == mul) ) {
    sw = HWA_CLOCK_CFGR_SW_PLL ;
    pllsrc = HWA_CLOCK_CFGR_PLL_SRC_HSE_DIV2 ;
    pllmul = mul ;
    goto sysclk_done ;
  }

  /*	Try SW = HSI
   */
  if ( syshz == 8000000
       && (sw == 0xFF || sw == HWA_CLOCK_CFGR_SW_HSI) ) {
    sw = HWA_CLOCK_CFGR_SW_HSI ;
    goto sysclk_done ;
  }

  /*	Try SW = PLL(HSI/2)
   */
  if ( (mul = syshz / 4000000) * 4000000 == syshz
       && mul >= 2 && mul <= 16
       && (sw == 0xFF || sw == HWA_CLOCK_CFGR_SW_PLL)
       && (pllsrc == 0xFF || pllsrc == HWA_CLOCK_CFGR_PLL_SRC_HSI_DIV2)
       && (pllmul == 0 || pllmul == mul) ) {
    sw = HWA_CLOCK_CFGR_SW_PLL ;
    pllsrc = HWA_CLOCK_CFGR_PLL_SRC_HSI_DIV2 ;
    pllmul = mul ;
  }

 sysclk_done:

  /*	Check SYSCLK configuration.
   *	TODO: detail errors.
   */
  if ( sw == 0xFF
       || (sw == HWA_CLOCK_CFGR_SW_PLL
	   && (pllmul <2 || pllmul >16
	       || pllsrc == 0xFF
	       || (pllsrc == HWA_CLOCK_CFGR_PLL_SRC_HSE && syshz != mul * hsehz)
	       || (pllsrc == HWA_CLOCK_CFGR_PLL_SRC_HSE_DIV2 && syshz != mul * hsehz/2)
	       || (pllsrc == HWA_CLOCK_CFGR_PLL_SRC_HSI_DIV2 && syshz != mul * 4000000)))
       || (sw == HWA_CLOCK_CFGR_SW_HSE && syshz != hsehz)
       || (sw == HWA_CLOCK_CFGR_SW_HSI && syshz != 8000000)
       || syshz < 4000000 || syshz > 72000000 )
    HWA_ERROR("Invalid SYSCLK configuration.");

  HWA_VSETP(HWA_CLOCK, p, HWA_CLOCK_CFGR_SW, sw);
  if ( pllsrc != 0xFF )
    HWA_VSETP(HWA_CLOCK, p, HWA_CLOCK_CFGR_PLL_SRC, pllsrc);
  if ( pllmul != 0 )
    HWA_VSETP(HWA_CLOCK, p, HWA_CLOCK_CFGR_PLL_MUL, pllmul-2);

  /*	If HSE is used, HSE OSC must be started
   */
  if ( sw == HWA_CLOCK_CFGR_SW_HSE
       || (sw == HWA_CLOCK_CFGR_SW_PLL
	   && (pllsrc == HWA_CLOCK_CFGR_PLL_SRC_HSE
	       || pllsrc == HWA_CLOCK_CFGR_PLL_SRC_HSE_DIV2)))
    HWA_VSETP(HWA_CLOCK, p, HWA_CLOCK_CR_HSE_ON, 1);

  /*	AHB prescaler (HPRE)
   *	Possible values: 1, 2, 4, 8, 16, 64, 128, 256, 512
   *
   *	Reset value (1) is valid in any case.
   */
  if ( HWA_VREGP(p, HWA_AHBHZ, mvmask) != 0 )
    hpre = syshz / ahbhz ;
  else {
    if ( HWA_VBITSP(HWA_CLOCK, p, HWA_CLOCK_CFGR_HPRE, ovmask) == 0 ) {
      /* hpre = 1 ; */
      HWA_ERROR("HPRE setting is needed.");
    }
    else {
      /*
       *	Decode HPRE from hardware setting
       */
      hpre = HWA_VBITSP(HWA_CLOCK, p, HWA_CLOCK_CFGR_HPRE, ovalue) ;
      if ( (hpre & 0b1000) == 0 )
	hpre = 1 ;
      else
	hpre = 1<<( ((hpre & 0b0111)+1) + ((hpre & 0b0100) >> 2) ) ;
    }
  }

  ahbhz = syshz / hpre ;

  /*	Check and encode HPRE for hardware
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
  hpre = HWA_LOG2(hpre);
  if ( hpre < 0 || hpre > 9 || hpre == 32 )
    HWA_ERROR("HPRE invalid.");
  else {
    if 
      }
#endif
  HWA_VSETP(HWA_CLOCK, p, HWA_CLOCK_CFGR_HPRE, hpre);


  /*	APB1 prescaler (PPRE1): APB1_HZ < 36 MHz
   */
  if ( HWA_VREGP(p, HWA_APB1HZ, mvmask) )
    ppre1 = ahbhz / apb1hz ;
  else {
    if ( HWA_VBITSP(HWA_CLOCK, p, HWA_CLOCK_CFGR_PPRE1, ovmask) == 0 ) {
      /* if ( ahbhz > 36000000 ) */
      /* 	ppre1 = 2 ; */
      /* else */
      /* 	ppre1 = 1 ; */
      HWA_ERROR("PPRE1 setting is needed.");
    }
    else {
      /*
       *	Decode PPRE1 from hardware setting
       */
      ppre1 = HWA_VBITSP(HWA_CLOCK, p, HWA_CLOCK_CFGR_PPRE1, ovalue) ;
      if ( (ppre1 & 0b100) == 0 )
	ppre1 = 1 ;
      else
	ppre1 = 1<<((ppre1 & 0b011)+1) ;
      if ( ahbhz / ppre1 > 36000000 ) {
	/* HWA_WARN("PPRE1 * 2"); */
	ppre1 = ppre1 * 2 ;
      }
    }
  }

  apb1hz = ahbhz / ppre1 ;

  /*	Check and encode PPRE1 for hardware
   */
  if ( ppre1 == 1 )
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
  if ( apb1hz > 36000000 )
    HWA_ERROR("APB1 frequency > 36 MHz.");

  HWA_VSETP(HWA_CLOCK, p, HWA_CLOCK_CFGR_PPRE1, ppre1);


  /*	APB2 prescaler (PPRE2)
   */
  if ( HWA_VREGP(p, HWA_APB2HZ, mvmask) )
    ppre2 = ahbhz / apb2hz ;
  else {
    if ( HWA_VBITSP(HWA_CLOCK, p, HWA_CLOCK_CFGR_PPRE2, ovmask) == 0 ) {
      HWA_ERROR("PPRE2 setting is needed.");
      /* ppre2 = 1 ; */
    }
    else {
      /*
       *	Decode PPRE2 from hardware setting
       */
      ppre2 = HWA_VBITSP(HWA_CLOCK, p, HWA_CLOCK_CFGR_PPRE2, ovalue) ;
      if ( (ppre2 & 0b100) == 0 )
	ppre2 = 1 ;
      else
	ppre2 = 1<<((ppre2 & 0b011)+1) ;
    }
  }

  apb2hz = ahbhz / ppre2 ;

  /*	Check and encode PPRE2 for hardware
   */
  if ( ppre2 == 1 )
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

  HWA_VSETP(HWA_CLOCK, p, HWA_CLOCK_CFGR_PPRE2, ppre2);

  HWA_VSETP(HWA_CLOCK, p, HWA_SYSHZ, -1, 0, syshz);
  HWA_VSETP(HWA_CLOCK, p, HWA_AHBHZ, -1, 0, ahbhz);
  HWA_VSETP(HWA_CLOCK, p, HWA_APB1HZ, -1, 0, apb1hz);
  HWA_VSETP(HWA_CLOCK, p, HWA_APB2HZ, -1, 0, apb2hz);

  /* if ( HWA_VREGP(p, HWA_APB1HZ, mvalue) != apb1hz ) */
  /*   HWA_ERROR("HWA Error."); */

  /* if ( HWA_VREGP(p, HWA_APB1HZ, mvmask) ) { */
  /*   HWA_WARN("MVMASK."); */
  /*   if ( HWA_VREGP(p, HWA_APB1HZ, mvalue) != apb1hz ) */
  /*     HWA_WARN("MVALUE."); */
  /* } */
  /* else if ( HWA_VREGP(p, HWA_APB1HZ, ovmask) ) */
  /*   HWA_WARN("OVMASK."); */
  /* else */
  /*   HWA_WARN("NONE."); */

  /* if (HWA_NVALP(HWA_CLOCK, p, HWA_APB1HZ) != apb1hz ) */
  /*   HWA_ERROR("HWA Error."); */

  /* if (HWA_NVALP(HWA_CLOCK, p, HWA_APB1HZ) == HWA_NVALP(HWA_HCLOCK, p, HWA_AHBHZ)) */
  /*   HWA_WARN("NO CLKMUL"); */
  /* else  */
  /*   HWA_WARN("CLKMUL"); */

#if 0
  /*	Flash latency. Prefetch buffer is ON after reset.
   */
  /*	Note: The prefetch buffer must be kept on when using a prescaler different
   *	from 1 on the AHB clock. Refer to Reading the Flash memory on page 52
   *	section for more details.
   */
  if ( HWA_VBITSP(HWA_FLASH, flash, HWA_FLASH_ACR_LATENCY, mvmask) == 0 ) {
    if (syshz < 24000000)
      HWA_VSETP(HWA_FLASH, flash, HWA_FLASH_ACR_LATENCY, HWA_FLASH_ACR_LATENCY_0WS);
    else if (syshz < 48000000)
      HWA_VSETP(HWA_FLASH, flash, HWA_FLASH_ACR_LATENCY, HWA_FLASH_ACR_LATENCY_1WS);
    else
      HWA_VSETP(HWA_FLASH, flash, HWA_FLASH_ACR_LATENCY, HWA_FLASH_ACR_LATENCY_2WS);
  }

  /*	Commit flash latency before SYSCLK switch to high-speed.
   */
  HWA_COMMITP(HWA_FLASH, flash, HWA_ACR);
#endif

  /*	RM0008: The PLL configuration (selection of HSI oscillator divided by 2 or HSE
   *	oscillator for PLL input clock, and multiplication factor) must be done
   *	before enabling the PLL. Once the PLL enabled, these parameters cannot
   *	be changed.
   *	Caution: The PLL output frequency must not exceed 72 MHz.
   */
  /*	Set PLL and other device clocks configuration (PLL not enabled yet)
   */
  HWA_COMMITP(dry, HWA_CLOCK, p, HWA_CFGR);
  HWA_COMMITP(dry, HWA_CLOCK, p, HWA_CR);

  /*	Enable PLL. Sysclock will be switched automatically to PLL when PLL
   *	and its source are ready. No need to wait!
   */
  if ( sw == HWA_CLOCK_CFGR_SW_PLL ) {
    HWA_VSETP(HWA_CLOCK, p, HWA_CLOCK_CR_PLL_ON, 1);
    HWA_COMMITP(dry, HWA_CLOCK, p, HWA_CR);
  }

  ahbhz = HWA_NVALP(p, HWA_AHBHZ) ;
  if ( ahbhz == HWA_NONE )
    HWA_ERROR("");

  HWA_COMMITP(dry, HWA_CLOCK, p, HWA_SYSHZ);
  HWA_COMMITP(dry, HWA_CLOCK, p, HWA_HSEHZ);
  HWA_COMMITP(dry, HWA_CLOCK, p, HWA_AHBHZ);
  HWA_COMMITP(dry, HWA_CLOCK, p, HWA_APB1HZ);
  HWA_COMMITP(dry, HWA_CLOCK, p, HWA_APB2HZ);

  ahbhz = HWA_NVALP(p, HWA_AHBHZ) ;
  if ( ahbhz == HWA_NONE )
    HWA_ERROR("");

  p->used = 0 ;
}


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

#define hwa_clock_set_xso_hz(hz)\
  HWA_VSETP(HWA_CLOCK, HWA_P(HWA_CLOCK0), HWA_HSEHZ, -1, 0, hz)

#define hwa_clock_set_sys_hz(hz)\
  HWA_VSETP(HWA_CLOCK, HWA_P(HWA_CLOCK0), HWA_SYSHZ, -1, 0, hz)

#define hwa_clock_set_ahb_hz(hz)	HWA_VSETP(HWA_CLOCK, HWA_P(HWA_CLOCK0), AHBHZ, -1, 0, hz)
#define hwa_clock_set_apb1_hz(hz)	HWA_VSETP(HWA_CLOCK, HWA_P(HWA_CLOCK0), APB1HZ, -1, 0, hz)
#define hwa_clock_set_apb2_hz(hz)	HWA_VSETP(HWA_CLOCK, HWA_P(HWA_CLOCK0), APB2HZ, -1, 0, hz)

/* #define hwa_clock_set_ahb_hz(hz)	HWA_XSETP(HWA_P(CLOCK0), ahb_hz, hz) */
/* #define hwa_clock_set_apb1_hz(hz)	HWA_XSETP(HWA_P(CLOCK0), apb1_hz, hz) */
/* #define hwa_clock_set_apb2_hz(hz)	HWA_XSETP(HWA_P(CLOCK0), apb2_hz, hz) */

#endif
