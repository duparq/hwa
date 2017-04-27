#ifndef HWA_STM32_PWR_H
#define HWA_STM32_PWR_H

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hwac_bd_disable_wp()			\
  do {						\
    HWA_SET(PWR_CR, 0b1, 8, 1);			\
    HWA_COMMIT(PWR_CR);				\
  } while(0)

//  (*HWA_PTR_PWR_CR) |= 0x0100

/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

#define HWA_PTR_PWR		HWA_PTR_APB1+0x7000 /* 0x40007000 */
#define HWA_PTR_PWR_CR		((volatile u32 *)(HWA_PTR_PWR+0x00)) /* 0x40007000 */

#define hwa_pwr_begin(state)						\
  HWA_DECL(PWR_CR, u32, HWA_PTR_PWR+0x00, 0x00000000, 0x000001FF, state)

#define hwa_pwr_commit()			\
  HWA_COMMIT(PWR_CR)


#endif
