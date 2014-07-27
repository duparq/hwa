
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA global include file
 *
 * HWA definitions are spread over two layers:
 *
 * - The first layer (hwa_l1_*.h ) contains the definitions of
 * "synchronous" functions accessing the real hardware registers directly. It
 * also contains the declarations of the structures used by the second layer.
 *
 * - The second layer (hwa_l2_*.h ) contains the definitions of the
 * global HWA structure that virtualizes the hardware and that is used by all
 * the "advanced" or "asynchronous" functions also declared in these files.
 *
 * \req HWA_DEVICE must be defined.
 *
 * \defgroup exp 	Macros that expand arguments for other macros.
 * \defgroup global	Global HWA definitions
 * \defgroup macro	General-purpose macro definitions
 */

#ifndef _HWA_H_
#define _HWA_H_

#ifndef HWA_DEVICE
#  error "HWA_DEVICE not defined."
#endif


/**
 * \brief	Set external system clock speed to 0 if none specified.
 * \ingroup	global
 */
#ifndef HW_XSOHZ
#  define HW_XSOHZ	0
#endif

#include "hwa__macros.h"
#include "hwa__interrupts.h"

#if !defined __ASSEMBLER__
#  include "hwa__1.h"
#endif

#define hw_state_on		, 1
#define hw_state_off		, 0


/*	Include device-specific declarations
 */
#ifdef DOXYGEN
#  include "hwa_device_1.h"
#else
#  include HW_QUOTE(HW_G3(hwa, HWA_DEVICE, 1).h)
#endif


#if !defined __ASSEMBLER__

/** \brief	The hwa struct.
 *
 * This structure is instanciated by hwa_begin() and used by all hwa_...(...)
 * functions to bufferize hardware accesses.
 */

typedef struct {
  uint8_t	commit ;	/*!< 1 if commit do write hard registers		*/
  //  uint8_t	initstate ;	/*!< 1 if system is assumed in after-reset state	*/
  HWA_DCL			/*!< Include device-specific declarations		*/
} hwa_t ;

struct hwa_t ;
#  include "hwa__2.h"
#endif

#endif /* !defined _HWA_H_ */
