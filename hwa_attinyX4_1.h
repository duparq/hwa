
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	Common definitions for ATtiny{2,4,8}4 devices
 */


#define HW_DEVICE_ATTINYX4

#include "hwa_atmelavr_1.h"
#include "hwa_attinyX4_cores_1.h"
#include "hwa_attinyX4_ios_1.h"
#include "hwa_attinyX4_pcints_1.h"
#include "hwa_attinyX4_irqs_1.h"
#include "hwa_attinyX4_adcs_1.h"
#include "hwa_attinyX4_counters_1.h"


#if !defined __ASSEMBLER__ 

#define HWA_DCL					\
  HWA_DCL_CORES					\
  HWA_DCL_IOS					\
  HWA_DCL_PCINTS				\
  HWA_DCL_COUNTERS				\
  HWA_DCL_ADCS


#define hw_syshz	_hw_syshz()


/** \brief	Returns the system clock frequency.
 *
 *	For Atmel ATtinyX4, the system clock frequency is determined from the
 *	fuses states in the fuse low byte (FUSE_LB must be defined at compile
 *	time).
 */
HW_INLINE uint32_t _hw_syshz()
{
  uint32_t syshz = 0 ;

  if ( (FUSE_LB & 0x0F) == 2 )
    syshz = 8000000 ;
  else if ( (FUSE_LB & 0x0F) == 4 )
    syshz = 128000 ;
  else
    syshz = HW_XSOHZ ;

  if ( (FUSE_LB & 0x80) == 0 )
    syshz /= 8 ;

  return syshz ;
}
#endif /* !defined __ASSEMBLER__ */


#define hw_sleep_until_irq()					\
  __asm__ __volatile__(						\
		       "    in    r24, 0x35"		"\n\t"	\
		       "    ori   r24, 0x20"		"\n\t"	\
		       "    out   0x35, r24"		"\n\t"	\
		       "    sleep          "		"\n\t"	\
		       "    andi  r24, 0xDF"		"\n\t"	\
		       "    out   0x35, r24"		"\n\t"	\
		       ::: "r24" )


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
