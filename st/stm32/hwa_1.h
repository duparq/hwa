
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions common to all STM32 devices that do not produce C code
 */

/**
 * @addtogroup stm32
 * @{
 *
 * @name Device description
 *
 * These definitions are computed by HWA from the target device name and the
 * definitions provided by the user.
 *
 * @{
 */

/**
 *  Device family
 */
#define HW_DEVICE_FAMILY		stm32

/**
 *  Device family
 */
#define HW_DEVICE_FAMILY_STM32

/**
 *  Device vendor
 */
#define HW_DEVICE_VENDOR_ST

/**
 *  Device vendor
 */
#define HW_DEVICE_VENDOR		st

/**
 *  Device architecture
 */
#define HW_DEVICE_ARCH_STM32

/**
 *  Device architecture
 */
#define HW_DEVICE_ARCH			stm32

/** @} */
/** @} */


#include "hwa_errors.h"		/* Family specific error messages */


/*  Keywords for stm32
 */
#define _hw_is_48MHzdiv_48MHzdiv		, 1
#define _hw_is_compare_flag_compare_flag	, 1
#define _hw_is_sysclkdiv_sysclkdiv		, 1
#define _hw_is__isr__isr			, 1


#define hw__irq_flag			, _hw_irqf
#define _hw_irqf(o,m,f,x)		HW_CODG(HW_COD(HW_A0 o),f)

#define hw__irq_mask			, _hw_irqm
#define _hw_irqm(o,m,f,x)		HW_CODG(HW_COD(HW_A0 o),m)


#define HW_ISR(...)			_HW_ISR01(__VA_ARGS__,,,,)
#define _HW_ISR01(o,r,...)		_HW_ISR02(_hw_isr_##o##_##r,o,r,__VA_ARGS__)
#define _HW_ISR02(x,...)		HW_BW(_HW_ISR1,_isr,x)(x,__VA_ARGS__)
#define _HW_ISR10(x,o,r,...)		HW_E(HW_EM_ISR(o r)) void HW_G2(hw,__COUNTER__)()
#define _HW_ISR11(c,n,esr,o,x,...)	void esr() HW_ISR_ATTRIBUTES; HW_EOL(__VA_ARGS__) void esr()


#if !defined __ASSEMBLER__
typedef signed int		int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int		uint8_t __attribute__((__mode__(__QI__)));
typedef signed int		int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int		uint16_t __attribute__ ((__mode__ (__HI__)));
typedef signed int		int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int		uint32_t __attribute__ ((__mode__ (__SI__)));
typedef int32_t			intptr_t;
typedef uint32_t		uintptr_t;
#endif

#include "../../hwa/hwa_1.h"
