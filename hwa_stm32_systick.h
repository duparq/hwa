#ifndef HWA_SYSTICK_H
#define HWA_SYSTICK_H

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_systick_connect_clk(clksrc)				\
  HWA_SET(SYSTICK_CTRL, 0b1, 2, HWA_SYSTICK_CLKSRC_##clksrc);

#define HWA_SYSTICK_CLKSRC_CORE			1
#define HWA_SYSTICK_CLKSRC_AHB_DIV8		0
  
#define hwa_systick_turn_irq(state)			\
  HWA_SET(SYSTICK_CTRL, 0b1, 1, HWA_STATE_##state);

#define hwa_systick_turn(state)				\
  HWA_SET(SYSTICK_CTRL, 0b1, 0, HWA_STATE_##state);
 
#define hwa_systick_set_reload_value(value)	\
  *HWA_PTR_SYSTICK_LOAD=value

#define hwa_systick_get_value()			\
  (*HWA_PTR_SYSTICK_VALUE)

#define hwa_systick_flag_is_set()			\
  (HWA_BITS(*HWA_PTR_SYSTICK_CTRL, 0b1, 16) != 0)

/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

#define HWA_PTR_SYSTICK			0xE000E010

#define HWA_PTR_SYSTICK_CTRL		((volatile u32 *)(HWA_PTR_SYSTICK+0x0)) /* 0xE000E010 */
#define HWA_PTR_SYSTICK_LOAD		((volatile u32 *)(HWA_PTR_SYSTICK+0x4)) /* 0xE000E014 */
#define HWA_PTR_SYSTICK_VALUE		((volatile u32 *)(HWA_PTR_SYSTICK+0x8)) /* 0xE000E018 */

/*	Registers declarations: name, type, address, reset value, write mask
 */
#define hwa_systick_begin(state)					\
  HWA_DECL(SYSTICK_CTRL,  u32, HWA_PTR_SYSTICK+0x0, 0x00000000, 0x00000007, state) /* 0xE000E010 */

#if 0
HWA_PDCL(SYSTICK_LOAD,  u32, HWA_PTR_SYSTICK+0x4) /* 0xE000E014 */
HWA_PDCL(SYSTICK_VALUE, u32, HWA_PTR_SYSTICK+0x8) /* 0xE000E018 */
HWA_DECL(SYSTICK_CALIB, u32, HWA_PTR_SYSTICK+0xC, 0x00000000, 0x00000000, state) /* 0xE000E01C */
#endif


#define hwa_systick_commit()			\
  HWA_COMMIT(SYSTICK_CTRL)
#if 0
HWA_COMMIT(SYSTICK_LOAD)			
HWA_COMMIT(SYSTICK_VALUE)
HWA_COMMIT(SYSTICK_CALIB)
#endif

#endif
