
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @defgroup public HWA instructions
 * HWA instructions you use in your application.
 */

/**
 * @defgroup private HWA internal instructions
 * These instruction are intended for internal use.
 * There is not argument checking, and no error processing.
 */

/**
 * @file
 * @brief	`hwa.h` is the main include file of HWA.
 *
 * `hwa.h` is included from the application source after `HW_DEVICE` has been
 * defined with the name od the target device. `hwa.h` is responsible for
 * including all that is necessary in order to use HWA for the target device.
 *
 * HWA definitions are split in two parts:
 *
 * - The first part (files ending with `_1.h` ) contains the definitions that do
 *   not produce C code (can be used for assembler) and the definitions
 *   related to the building of the HWA context.
 *
 * - The second part (files ending with `_2.h`) contains the definitions that
 *   produce C code or make use of the HWA context.
 */

#ifndef _HWA_H_
#define _HWA_H_


#ifndef HW_DEVICE
#  error "HW_DEVICE not defined."
#endif

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


/** @brief	Run-time error.
 *
 *  Trigger an error after code generation.
 *
 * @hideinitializer
 */
#define HWA_ERR(msg)		_HWA_ERR_2(msg, __COUNTER__)
#define _HWA_ERR_2(...)		_HWA_ERR_3(__VA_ARGS__)
#define _HWA_ERR_3(msg, num)						\
  do {									\
    extern void __attribute__((error(msg))) hwa_error_##num(void); \
      hwa_error_##num();						\
  } while(0)


/** @brief	8-bit HWA context register.
 *
 *  Structure used by `hwa_` prefixed functions to handle one 8-bit hardware
 *  register.
 */
typedef struct hwa_r8_t
{
  intptr_t	a ;		/*!< Address of hardware register.		*/
  uint8_t	mmask ;		/*!< Modified bits mask.			*/
  uint8_t	mvalue ;	/*!< Modified value mask.			*/
  uint8_t	omask ;		/*!< Hardware known bits mask.			*/
  uint8_t	ovalue ;	/*!< Hardware known value mask.			*/
} hwa_r8_t ;

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


/*	Include device-specific declarations
 */
#include HW_QUOTE(../devices/HW_G2(HW_DEVICE,1).h)


#if !defined __ASSEMBLER__

/*  The HWA context.
 *
 *  This structure is instanciated by `hwa_begin()` and used by all
 *  `hwa_...(...)` functions to bufferize hardware accesses.
 *
 *  It is populated by expanding the `HWA_DCL` symbol that is defined in the
 *  target-specific files.
 */

typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/
  HWA_DCL			/*!< Include device-specific declarations		*/
} hwa_t ;

struct hwa_t ;
#  include "hwa_2.h"
#endif /* !defined __ASSEMBLER__ */

#endif /* !defined _HWA_H_ */
