
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	Common definitions for ATtiny{2,4,8}4 devices
 */


#define HWA_DEVICE_ATTINYX4

/*	The include order and ids follows that of the datasheet
 */
#include "hwa_atmelavr_1.h"
#include "hwa_attinyX4_cores_1.h"		/* id: 100 */
#include "hwa_attinyX4_irqs_1.h"
#include "hwa_attinyX4_pcints_1.h"		/* id: 200 */
#include "hwa_attinyX4_ios_1.h"			/* id: 300 */
#include "hwa_attinyX4_counters_1.h"		/* id: 400 */
#include "hwa_attinyX4_pscs_1.h"		/* id: 500 */
//#include "hwa_attinyX4_usis_1.h"		/* id: 600 */
#include "hwa_attinyX4_acmps_1.h"		/* id: 700 */
#include "hwa_attinyX4_adcs_1.h"		/* id: 800 */


/** \brief	Returns the system clock frequency.
 *
 *	For Atmel ATtinyX4, the system clock frequency is determined from the
 *	fuses states in the fuse low byte (FUSE_LB must be defined at compile
 *	time).
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


#if !defined __ASSEMBLER__ 

#define HWA_DCL					\
  HWA_DCL_CORES					\
  HWA_DCL_IOS					\
  HWA_DCL_PCINTS				\
  HWA_DCL_COUNTERS				\
  HWA_DCL_ACMPS ;				\
  HWA_DCL_ADCS ;


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


#if defined HW_OEM && defined __ASSEMBLER__
/*
 *	Assembler symbols
 */
	.global __vector_0
	.global __vector_1
	.global __vector_2
	.global __vector_3
	.global __vector_4
	.global __vector_5
	.global __vector_6
	.global __vector_7
	.global __vector_8
	.global __vector_9
	.global __vector_10
	.global __vector_11
	.global __vector_12
	.global __vector_13
	.global __vector_14
	.global __vector_15
	.global __vector_16

#define SREG		0x3F
#define GIMSK		0x3B
#define   INT0		6
#define   PCIE1 	5
/* #define   RB_INT0	GIMSK, 6 */
/* #define   RB_INT1	GIMSK, 5 */
#define GIFR		0x3A
#define   INTF0		6
#define   PCIF1		5
/* #define   RB_INTF0	GIFR, 6 */
/* #define   RB_INTF1	GIFR, 5 */
#define GPIOR2		0x15
#define GPIOR1		0x14
#define GPIOR0		0x13
#define ACSR		0x08
#define	  ACI		4
#define   ACIE		3
#define EEARH		0x1F
#define EEARL		0x1E
#define EEDR		0x1D
#define EECR		0x1C
#define   EEPM1		5
#define   EEPM0		4
#define   EEMPE		2
#define   EEPE		1
#define   EERE		0
#define PCMSK1		0x20
#define   PCINT8	0
#define TIMSK1		0x0C
#define TIFR1		0x0B

#endif /* defined HW_OEM && defined __ASSEMBLER__ */
