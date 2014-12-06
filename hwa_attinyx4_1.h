
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	Common definitions for ATtiny{2,4,8}4 devices
 */


#define HW_DEVICE_ATTINYX4

/*	The include order and ids follows that of the datasheet
 */
#include "hwa_atmelavr_1.h"
#include "hwa_attinyx4_cores_1.h"		/* id: 100 */
#include "hwa_attinyx4_pcints_1.h"		/* id: 200 */
#include "hwa_attinyx4_ios_1.h"			/* id: 300 */
#include "hwa_attinyx4_counters_1.h"		/* id: 400 */
#include "hwa_attinyx4_pscs_1.h"		/* id: 500 */
#include "hwa_attinyx4_usis_1.h"		/* id: 600 */
#include "hwa_attinyx4_acmps_1.h"		/* id: 700 */
#include "hwa_attinyx4_adcs_1.h"		/* id: 800 */
#include "hwa_attinyx4_watchdogs_1.h"		/* id: 900 */
#include "hwa_attinyx4_eeproms_1.h"		/* id: 1000 */
#include "hwa_attinyx4_flashs_1.h"		/* id: 1100 */


/** \brief	Returns the system clock frequency.
 *
 *	For Atmel ATtinyX4, the system clock frequency is determined from the
 *	fuse low byte (FUSE_LB must be defined at compile time) and HW_XSOHZ if
 *	applicable.
 */
#if (FUSE_LB & 0x0F) == 2
#  define hw_syshz_base 8000000
#elif (FUSE_LB & 0x0F) == 4
#  define hw_syshz_base 128000
#else
#  define hw_syshz_base HW_XSOHZ
#endif

#if (FUSE_LB & 0x80) == 0
#  define hw_syshz	hw_syshz_base/8
#else
#  define hw_syshz	hw_syshz_base
#endif

#undef hw_syshz_base


#if !defined __ASSEMBLER__ 

#define HWA_DCL					\
  HWA_DCL_CORES ;				\
  HWA_DCL_IOS ;					\
  HWA_DCL_PCINTS ;				\
  HWA_DCL_COUNTERS ;				\
  HWA_DCL_USIS ;				\
  HWA_DCL_ACMPS ;				\
  HWA_DCL_ADCS ;				\
  HWA_DCL_WATCHDOGS ;


#define hw_sleep_until_irq()					\
  __asm__ __volatile__(						\
		       "    in    r24, 0x35"		"\n\t"	\
		       "    ori   r24, 0x20"		"\n\t"	\
		       "    out   0x35, r24"		"\n\t"	\
		       "    sleep          "		"\n\t"	\
		       "    andi  r24, 0xDF"		"\n\t"	\
		       "    out   0x35, r24"		"\n\t"	\
		       ::: "r24" )

#endif /* !defined __ASSEMBLER__ */
