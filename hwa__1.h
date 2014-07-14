
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA layer 1: definitions dealing with hardware registers.
 *
 *	The layer 1 (hwa_l1_*.h ) contains the definitions of
 *	"synchronous" functions accessing the real hardware registers
 *	directly. It also contains the declarations of the structures used by
 *	the second layer.
 *
 *	See hwa_exp.h or \ref notations "notations" for a description of the
 *	notations used.
 */

#include "hwa__macros.h"
#include "hwa__interrupts.h"


#if !defined __ASSEMBLER__
#  include "hwa__funcs.h"
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
  uint8_t	initstate ;	/*!< 1 if system is assumed in after-reset state	*/
  HWA_DCL			/*!< Include device-specific declarations		*/
} hwa_t ;

#endif /* !defined __ASSEMBLER__ */
