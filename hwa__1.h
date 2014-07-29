
/* This file is ca+rt of the HWA project.
 * Copyright (c) Christophe Duca+rquet <duca+rq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include <stdint.h>

/** \brief	Storage class of HWA functions.
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
 *  __attribute__((always_inline)) triggers a warning if gcc fails to inline the
 *  function.
 */
#define HW_INLINE		static inline __attribute__((always_inline))


#if defined __cplusplus
# define HW_EXTERN_C		extern "C"
#else
# define HW_EXTERN_C
#endif


/*	HWA_ERR(msg): run-time error
 */
/** \brief	Run-time error
 *
 * \ingroup macro
 * \hideinitializer
 */
#define HWA_ERR(msg)		_HWA_ERR_2(msg, __COUNTER__)
#define _HWA_ERR_2(...)		_HWA_ERR_3(__VA_ARGS__)
#define _HWA_ERR_3(msg, num)						\
  do {									\
    extern void __attribute__((error(msg))) hwa_error_##num(void); \
      hwa_error_##num();						\
  } while(0)


/** \brief	8-bit HWA register.
 *
 *	Structure used by hwa_ prefixed functions to handle one 8-bit hardware register.
 */
typedef struct hwa_r8_t
{
  intptr_t	ra ;		/*!< Address of hardware register.		*/
  uint8_t	riv ;		/*!< Value after system reset (initial value).	*/
  uint8_t	rwm ;		/*!< Writeable bits mask.			*/
  uint8_t	mmask ;		/*!< Modified bits mask.			*/
  uint8_t	mvalue ;	/*!< Modified value mask.			*/
  uint8_t	omask ;		/*!< Hardware known bits mask.			*/
  uint8_t	ovalue ;	/*!< Hardware known value mask.			*/
} hwa_r8_t ;

/** \brief	16-bit HWA register.
 *
 *	Structure used by hwa_ prefixed functions to handle one 16-bit hardware register.
 */
typedef struct hwa_r16_t
{
  intptr_t	ra ;		/*!< Address of hardware register.		*/
  uint16_t	riv ;		/*!< Value after system reset (initial value).	*/
  uint16_t	rwm ;		/*!< Writeable bits mask.			*/
  uint16_t	mmask ;		/*!< Modified bits mask.			*/
  uint16_t	mvalue ;	/*!< Modified value mask.			*/
  uint16_t	omask ;		/*!< Hardware known bits mask.			*/
  uint16_t	ovalue ;	/*!< Hardware known value mask.			*/
} hwa_r16_t ;

/** \brief	32-bit HWA register.
 *
 *	Structure used by hwa_ prefixed functions to handle one 32-bit hardware register.
 */
typedef struct hwa_r32_t
{
  intptr_t	ra ;		/*!< Address of hardware register.		*/
  uint32_t	riv ;		/*!< Value after system reset (initial value).	*/
  uint32_t	rwm ;		/*!< Writeable bits mask.			*/
  uint32_t	mmask ;		/*!< Modified bits mask.			*/
  uint32_t	mvalue ;	/*!< Modified value mask.			*/
  uint32_t	omask ;		/*!< Hardware known bits mask.			*/
  uint32_t	ovalue ;	/*!< Hardware known value mask.			*/
} hwa_r32_t ;
