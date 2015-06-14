
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @defgroup public_obj_instructions Instructions related to one object configuration
 *
 * These instructions receive an object as first argument and lead to
 * a modification of the hardware configuration.
 */

/**
 * @defgroup public_gen_instructions Instructions related to general hardware configuration
 *
 * These instructions lead to a modification of the hardware configuration that
 * is not related to a specific object.
 */

/**
 * @defgroup public_obj_macros Instructions providing informations about objects
 *
 * These instructions provide informations about an object without accessing the
 * hardware.
 */

/**
 * @defgroup public_gen_macros General purpose macros
 *
 * These instructions act on various types of arguments and do not access the
 * hardware.
 */

/**
 * @defgroup private HWA internal instructions
 * These instruction are intended for internal use.
 * There is not argument checking, and no error processing.
 */

/**
 * @file
 * @brief  This is the main include file of HWA.
 *
 * This file is included from the application source after `HW_DEVICE` has been
 * defined with the name od the target device. It includes all that is necessary
 * to use HWA with the target device.
 *
 * HWA definitions are split in two parts:
 *
 * * The first part (files ending with `_1.h` ) contains the definitions that do
 *   not produce C code (can be used for assembler) and the definitions
 *   related to the building of the HWA context.
 *
 * * The second part (files ending with `_2.h`) contains the definitions that
 *   produce C code or make use of the HWA context.
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
