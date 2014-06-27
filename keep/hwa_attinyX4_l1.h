
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	Common definitions for ATtiny{2,4,8}4 devices
 */


#define HW_DEVICE_ATTINYX4

#include "hwa_atmelavr_l1.h"
#include "hwa_attinyX4_cores_l1.h"
#include "hwa_attinyX4_ios_l1.h"
#include "hwa_attinyX4_adcs_l1.h"
#include "hwa_attinyX4_counters_l1.h"


#if !defined __ASSEMBLER__ 

#define HWA_DCL					\
  HWA_DCL_CORES					\
  HWA_DCL_IOS					\
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


/*	Interrupt vectors
 *	  Syntax: hw_isr_<i>_<ev>
 *	    i: instance
 *	    ev: event handled by the ISR
 */
#define hw_isr_int0			isr, int0, 1
#define hw_isr_pcint0			isr, pcint, 2
#define hw_isr_pcint1			isr, pcint, 2
#define hw_isr_pcint2			isr, pcint, 2
#define hw_isr_pcint3			isr, pcint, 2
#define hw_isr_pcint4			isr, pcint, 2
#define hw_isr_pcint5			isr, pcint, 2
#define hw_isr_pcint6			isr, pcint, 2
#define hw_isr_pcint7			isr, pcint, 2
#define hw_isr_pcint8			isr, pcint, 3
#define hw_isr_pcint9			isr, pcint, 3
#define hw_isr_pcint10			isr, pcint, 3
#define hw_isr_pcint11			isr, pcint, 3
#define hw_isr_watchdog_all		isr, watchdog_all, 4
#define hw_isr_counter1_capture		isr, counter1_capture, 5
#define hw_isr_counter1_match_1		isr, counter1_match_1, 6
#define hw_isr_counter1_match_a		isr, counter1_match_a, 6
#define hw_isr_counter1_match_2		isr, counter1_match_2, 7
#define hw_isr_counter1_match_b		isr, counter1_match_b, 7
#define hw_isr_counter1_overflow	isr, counter1_overflow, 8
#define hw_isr_counter0_match_1		isr, counter0_match_1, 9
#define hw_isr_counter0_match_a		isr, counter0_match_a, 9
#define hw_isr_counter0_match_2		isr, counter0_match_2, 10
#define hw_isr_counter0_match_b		isr, counter0_match_b, 10
#define hw_isr_counter0_overflow	isr, counter0_overflow, 11
#define hw_isr_acmp_all			isr, acmp_all, 12
#define hw_isr_ain1			isr, ain1, 12
#define hw_isr_adc0_all			isr, adc0_all, 13
#define hw_isr_eeprom_all		isr, eeprom_all, 14
#define hw_isr_usi_str			isr, usi_str, 15
#define hw_isr_usi_overflow		isr, usi_overflow, 16
					       
#define hw_isr_counter0_all		isr, counter0_all, all
#define hw_isr_counter1_all		isr, counter1_all, all


/* #define hw_vectors_counter0()						\ */
/*   void __vector_9 (void) __attribute__ ((alias("__vector_counter0"))) ;	\ */
/*   void __vector_10 (void) __attribute__ ((alias("__vector_counter0"))) ;	\ */
/*   void __vector_11 (void) __attribute__ ((alias("__vector_counter0"))) */

/* #define hw_vectors_counter1()						\ */
/*   void __vector_5 (void) __attribute__ ((alias("__vector_counter1"))) ;	\ */
/*   void __vector_6 (void) __attribute__ ((alias("__vector_counter1"))) ;	\ */
/*   void __vector_7 (void) __attribute__ ((alias("__vector_counter1"))) ;	\ */
/*   void __vector_8 (void) __attribute__ ((alias("__vector_counter1"))) */


#define hw_irqe_int0		hw_core0, int0
