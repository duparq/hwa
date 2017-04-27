#ifndef HWA_FLASH_H
#define HWA_FLASH_H

#define HWA_PTR_FLASH		HWA_PTR_AHB+0x0A000 /* 0x40022000 */

#define HWA_PTR_FLASH_ACR	((volatile u32 *)(HWA_PTR_FLASH+0x00)) /* 0x40022000 */
#define HWA_PTR_FLASH_KEYR	((volatile u32 *)(HWA_PTR_FLASH+0x04)) /* 0x40022004 */
#define HWA_PTR_FLASH_OPTKEYR	((volatile u32 *)(HWA_PTR_FLASH+0x08)) /* 0x40022008 */
#define HWA_PTR_FLASH_SR	((volatile u32 *)(HWA_PTR_FLASH+0x0C)) /* 0x4002200C */
#define HWA_PTR_FLASH_CR	((volatile u32 *)(HWA_PTR_FLASH+0x10)) /* 0x40022010 */
#define HWA_PTR_FLASH_AR	((volatile u32 *)(HWA_PTR_FLASH+0x14)) /* 0x40022014 */
#define HWA_PTR_FLASH_OBR	((volatile u32 *)(HWA_PTR_FLASH+0x1C)) /* 0x4002201C */
#define HWA_PTR_FLASH_WRPR	((volatile u32 *)(HWA_PTR_FLASH+0x20)) /* 0x40022020 */

/*	Register declaration: name, type, address, reset value, write mask
 */
#define hwa_flash_begin(state)						\
  HWA_DECL(FLASH_ACR,     u32, HWA_PTR_FLASH+0x00, 0x00000000, 0x0000001F, state) /* 0x40022000 */ \
  HWA_DECL(FLASH_KEYR,    u32, HWA_PTR_FLASH+0x04, 0x00000000, 0xFFFFFFFF, state) /* 0x40022004 */ \
  HWA_DECL(FLASH_SR,      u32, HWA_PTR_FLASH+0x0C, 0x00000000, 0x00000034, state) /* 0x4002200C */ \
  HWA_DECL(FLASH_CR,      u32, HWA_PTR_FLASH+0x10, 0x00000080, 0x000016F7, state) /* 0x40022010 */ \

#if 0
HWA_DECL(FLASH_OPTKEYR, u32, HWA_PTR_FLASH+0x08, 0x00000000, 0xFFFFFFFF, state) /* 0x40022008 */
HWA_DECL(FLASH_AR,      u32, HWA_PTR_FLASH+0x14, 0x00000000, 0xFFFFFFFF, state) /* 0x40022014 */
HWA_DECL(FLASH_OBR,     u32, HWA_PTR_FLASH+0x1C, 0x03FFFFFC, 0x00000000, state) /* 0x4002201C */
HWA_DECL(FLASH_WRPR,    u32, HWA_PTR_FLASH+0x20, 0xFFFFFFFF, 0x00000000, state) /* 0x40022020 */
#endif

#define hwa_flash_commit()			\
  HWA_COMMIT(FLASH_ACR);			\
  HWA_COMMIT(FLASH_KEYR);			\
  HWA_COMMIT(FLASH_SR);				\
  HWA_COMMIT(FLASH_CR);

#define hwa_flash_turn_prefetch_buffer(state)	\
  HWA_SET(FLASH_ACR, 0b1, 4, HWA_STATE_##state)

#define hwa_flash_set_latency(lat)			\
  if (HWA_FLASH_LAT_##lat != HWA_FLASH_LAT_AUTO) {	\
    HWA_SET(FLASH_ACR, 0b111, 0, HWA_FLASH_LAT_##lat);	\
  } else if (SYSCLK_HZ >= 48000000) {			\
    HWA_SET(FLASH_ACR, 0b111, 0, HWA_FLASH_LAT_2WS);	\
  } else if (SYSCLK_HZ >= 24000000) {			\
    HWA_SET(FLASH_ACR, 0b111, 0, HWA_FLASH_LAT_1WS);	\
  } else {						\
    HWA_SET(FLASH_ACR, 0b111, 0, HWA_FLASH_LAT_0WS);	\
  }
#define HWA_FLASH_LAT_0WS			0b000
#define HWA_FLASH_LAT_1WS			0b001
#define HWA_FLASH_LAT_2WS			0b010
#define HWA_FLASH_LAT_AUTO			0b111

#endif
