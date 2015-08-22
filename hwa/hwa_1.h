
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HWA definitions that do not produce C code
 */

/**
 * @defgroup public_obj_instructions Instructions related to one object configuration
 *
 * These instructions receive an object name as first argument and modify the
 * hardware configuration.
 */

/**
 * @defgroup public_context_instructions Instructions related to the HWA context
 */

/**
 * @defgroup public_obj_macros Instructions that provide informations about objects
 *
 * These instructions provide informations about an object without accessing the
 * hardware.
 */

/**
 * @defgroup public_reg_instructions Instructions related to registers
 *
 * These instructions receive an object name as first argument and the name of
 * one of its hardware or logical registers as a second argument.
 */

/**
 * @defgroup public_irq_instructions Instructions related to interrupts
 *
 * These instructions receive an interrupt name as first argument (that is an
 * object name that can be followed by an event name).
 */

/**
 * @defgroup public_gen_macros General purpose macros
 *
 * These instructions act on various types of arguments and do not access the
 * hardware.
 */

/**
 * @defgroup private HWA internal instructions
 *
 * These instruction are intended for internal use.
 * There is no argument checking and no error processing.
 */

/**
 * @defgroup private_classes HWA internal classes
 *
 * These classes are defined to be used internally by HWA.
 */

#include "hwa_macros.h"
#include "hwa_interrupts.h"


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
 * @ingroup public_gen_macros
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
