#ifndef HWA_STM32_FLASH_H
#define HWA_STM32_FLASH_H

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_FLASH0_BASE			HWA_AHB+0xA000	/* 0x40022000 */

#define HWA_FLASH_HWA_ACR			volatile, u32, 0x00, 0x00000030, 0x0000001F
#define HWA_FLASH_HWA_KEYR			volatile, u32, 0x04, 0x00000000, 0xFFFFFFFF
#define HWA_FLASH_HWA_OPTKEYR		volatile, u32, 0x08, 0x00000000, 0x00000034
#define HWA_FLASH_HWA_SR			volatile, u32, 0x0C, 0x00000080, 0x000016F7
#define HWA_FLASH_HWA_CR			volatile, u32, 0x10, 0x00000000, 0xFFFFFFFF
#define HWA_FLASH_HWA_AR			volatile, u32, 0x14, 0x00000000, 0xFFFFFFFF
#define HWA_FLASH_HWA_OBR			volatile, u32, 0x1C, 0x03FFFFFC, 0x00000000
#define HWA_FLASH_HWA_WRPR			volatile, u32, 0x20, 0xFFFFFFFF, 0x00000000

#define HWA_FLASH_ACR_PRFTBE		HWA_ACR, 0b1,   4
#define HWA_FLASH_ACR_LATENCY		HWA_ACR, 0b111, 0
#define HWA_FLASH_ACR_LATENCY_0WS	0b000			/* RESET */
#define HWA_FLASH_ACR_LATENCY_1WS	0b001
#define HWA_FLASH_ACR_LATENCY_2WS	0b010

typedef struct {
  HWA_PDCL();
  HWA_VDCL(HWA_FLASH, HWA_ACR);
} HWA_FLASH ;

#define hwa_begin_flash(reset)			\
  HWA_PINIT(HWA_FLASH, HWA_FLASH0);			\
  HWA_VINIT(HWA_FLASH, HWA_FLASH0, HWA_ACR, reset);

#define hwa_commit_flash()			\
  HWA_COMMITP(hwa_nocommit, HWA_FLASH, HWA_P(HWA_FLASH0), HWA_ACR);

#endif
