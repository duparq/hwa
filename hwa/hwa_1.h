
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HWA definitions that do not produce C code
 */

#include "hwa_macros.h"
#include "hwa_interrupts.h"


#if DOXYGEN

/**
 * @ingroup public_def
 * @brief The name of the device as used by the compiler.
 * @hideinitializer
 */
#  define HW_DEVICE

/**
 * @ingroup public_def
 * @brief Defined if the packaging of the device is device_package. See the @ref support "device-specific documentation" for details.
 * @hideinitializer
 */
#  define HW_DEVICE_PACKAGE_device_package

/**
 * @ingroup public_def
 * @brief The device vendor. See the @ref support "device-specific documentation" for details.
 * @hideinitializer
 */
#  define HW_DEVICE_VENDOR

/**
 * @ingroup public_def
 * @brief The device architecture. See the @ref support "device-specific documentation" for details.
 * @hideinitializer
 */
#  define HW_DEVICE_ARCH

/**
 * @ingroup public_def
 * @brief The CPU clock frequency (cpu cycles per second).
 */
#  define hw_syshz

#endif /* defined DOXYGEN */


/*	State definitions		, positive, negative
 */
#define _hw_state_on			, 1, 0
#define _hw_state_off			, 0, 1
#define _hw_state_yes			, 1, 0
#define _hw_state_no			, 0, 1
#define _hw_state_enabled		, 1, 0
#define _hw_state_disabled		, 0, 1

/**
 * @ingroup private_def
 * @brief 8-bit hardware register class.
 */
#define _hw_class__r8


/**
 * @ingroup private_def
 * @brief 16-bit hardware register class.
 */
#define _hw_class__r16


/**
 * @ingroup private_def
 * @brief 32-bit hardware register class.
 */
#define _hw_class__r32


/**
 * @ingroup private_def
 * @brief Class logical register made of one group of consecutive bits.
 */
#define _hw_class__cb1


/**
 * @ingroup private_def
 * @brief Class logical register made of two groups of consecutive bits.
 */
#define _hw_class__cb2


/**
 * @ingroup private_def
 * @brief Object logical register made of one group of consecutive bits.
 */
#define _hw_class__ob1


/**
 * @ingroup private_def
 * @brief Object logical register made of two groups of consecutive bits.
 */
#define _hw_class__ob2


/**
 * @ingroup private_def
 * @brief Interrupt object class.
 */
#define _hw_class__irq


/**
 * @ingroup private_def
 * @brief Memory definition of one group of consecutive bits.
 */
#define _hw_class__m1


/**
 * @ingroup private_def
 * @brief Memory definition of two groups of consecutive bits.
 */
#define _hw_class__m2


/**
 * @ingroup private_def
 * @brief Object logical register made of one group of consecutive bits.
 */
#define _hw_class__xob1


/**
 * @ingroup private_def
 * @brief Object register class.
 *
 *  An `_oreg` class object is a register of an object that can be accessed with
 *  the generic instructions designed for objects.
 */
#define _hw_class__oreg


#if !defined __ASSEMBLER__

#include <stdint.h>


/*  Storage class of HWA functions.
 *
 *  HWA function-like macros MUST be injected inside their callers and not leave
 *  any trace elsewhere, i.e. they must be strictly equivalent to macros,
 *  otherwise all kinds of HWA warnings and errors will be triggered.
 *
 *  GCC does the job with only the 'inline' keyword when optimisations are on,
 *  and optimisations must be on when using HWA.
 *
 *  However, it seems that the 'static' keyword prevents the function to be
 *  inlined unless the 'always_inline' attribute is specified.
 *
 *  `__attribute__((always_inline))` triggers a warning if gcc fails to inline the
 *  function.
 */
#define HW_INLINE		static inline __attribute__((always_inline))


#if defined __cplusplus
# define HW_EXTERN_C		extern "C"
#else
# define HW_EXTERN_C
#endif


/**
 * @ingroup public_ins
 * @brief Trigger an error after code generation.
 * @hideinitializer
 */
#define HWA_ERR(msg)		_HWA_ERR_2(msg, __COUNTER__)
#define _HWA_ERR_2(...)		_HWA_ERR_3(__VA_ARGS__)
#define _HWA_ERR_3(msg, num)						\
  do {									\
    extern void __attribute__((error(msg))) hwa_error_##num(void); \
      hwa_error_##num();						\
  } while(0)


/**
 * @brief 8-bit HWA context register.
 *
 * This structure is used in the HWA context to store one 8-bit hardware
 * register.
 */
typedef struct hwa_r8_t
{
  intptr_t	a ;		/*!< Address of hardware register.		*/
  uint8_t	mmask ;		/*!< Modified bits mask.			*/
  uint8_t	mvalue ;	/*!< Modified value mask.			*/
  uint8_t	omask ;		/*!< Hardware known bits mask.			*/
  uint8_t	ovalue ;	/*!< Hardware known value mask.			*/
} hwa_r8_t ;


/**
 * @brief 16-bit HWA context register.
 *
 * This structure is used in the HWA context to store one 16-bit hardware
 * register.
 */
typedef struct hwa_r16_t
{
  intptr_t	a ;		/*!< Address of hardware register.		*/
  uint16_t	mmask ;		/*!< Modified bits mask.			*/
  uint16_t	mvalue ;	/*!< Modified value mask.			*/
  uint16_t	omask ;		/*!< Hardware known bits mask.			*/
  uint16_t	ovalue ;	/*!< Hardware known value mask.			*/
} hwa_r16_t ;

typedef struct rem_hwa_r32_t
{
  intptr_t	a ;		/*!< Address of hardware register.		*/
  uint32_t	mmask ;		/*!< Modified bits mask.			*/
  uint32_t	mvalue ;	/*!< Modified value mask.			*/
  uint32_t	omask ;		/*!< Hardware known bits mask.			*/
  uint32_t	ovalue ;	/*!< Hardware known value mask.			*/
} hwa_r32_t ;


#endif /* !defined __ASSEMBLER__ */
