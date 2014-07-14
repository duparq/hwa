
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/** \brief	Target device is an Atmel AVR.
 */
#define HWA_DEVICE_ATMELAVR


/*	Keywords
 */
#define hw_is_bottom_bottom		, 1
#define hw_is_clock_clock		, 1
#define hw_is_countmode_countmode	, 1
#define hw_is_edge_edge			, 1
#define hw_is_filter_filter		, 1
#define hw_is_input_input		, 1
#define hw_is_ocu_ocu			, 1
#define hw_is_overflow_overflow		, 1
#define hw_is_top_top			, 1
#define hw_is_update_update		, 1


/*	Register address offset for C/assembler
 */
#ifndef __ASSEMBLER__
#  define HW_RA_OFFSET		0
#else
#  define HW_RA_OFFSET		-0x20
#endif


/*	Generic functions
 */
#define _hw_addr_ctr(cc,cn,ci,ca)	ca /* FIXME: may be void */


/*	Global classes & methods
 */
#define hw_def_hw_addr_bits1		, _hw_addr_bits1

#if defined __ASSEMBLER__
#  define _hw_addr_bits1(cc,cn,ca, rn,rw,ra,...)	(ca+ra-0x20)
#else
#  define _hw_addr_bits1(cc,cn,ca, rn,rw,ra,...)	(ca+ra)
#endif



/**\brief	Reset watchdog timer
 */
#define hw_reset_watchdog()		__asm__( "wdr":: )

/**\brief	Enable watchdog
 */
#define hw_enable_watchdog()		hw_write( hw_core0, wde, 1 )


/*	Enable/disable interrupts
 */
/* #define hw_enable_irqs()		__asm__ __volatile__ ("sei" ::) */
/* #define hw_disable_irqs()		__asm__ __volatile__ ("cli" ::) */
#define hw_enable_interrupts()		__asm__ __volatile__ ("sei" ::)
#define hw_disable_interrupts()		__asm__ __volatile__ ("cli" ::)


/*	Put the MCU in sleep mode
 *
 *	  Can not optimize read/write since interrupt triggering the wake-up
 *	  could change mcucr bits.
 */
/* #define hw_sleep_until_irq()			\ */
/*   do {						\ */
/*     hw_write(hw_core0, se, 1);			\ */
/*     __asm__ __volatile__ ( "sleep" "\n\t" :: );	\ */
/*     hw_write(hw_core0, se, 0);			\ */
/*   } while (0) */

/* #define x_hw_sleep_until_irq()			\ */
/*   do {						\ */
/*     hwa_begin();				\ */
/*     hwa_write(hw_core0, se, 1);			\ */
/*     hwa_commit();				\ */
/*     __asm__ __volatile__ ( "sleep" "\n\t" :: );	\ */
/*     hwa_write(hw_core0, se, 0);			\ */
/*     hwa_commit();				\ */
/*   } while (0) */


/**\brief	Software loop of \c n system clock cycles.
 * \todo	Only works with compile time constants
 * \hideinitializer
 */
#define hw_loop(n)			__builtin_avr_delay_cycles(n)


/*	Interrupts
 */
#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  define HW_ISR_ATTRIBUTES __attribute__((signal, used, externally_visible))
#else /* GCC < 4.1 */
#  define HW_ISR_ATTRIBUTES __attribute__((signal, used))
#endif


/*  Single event ISR
 */
#if !defined __ASSEMBLER__
#  define _hw_isr_(vector, ...)					\
  HW_EXTERN_C void __vector_##vector(void) HW_ISR_ATTRIBUTES __VA_ARGS__ ; \
  void __vector_##vector (void)
#else
#  define _hw_isr_(vector, ...)		\
  __vector_##vector
#endif

#define hw_israttr_interruptible	__attribute__((interrupt))
#define hw_israttr_non_interruptible
#define hw_israttr_naked		__attribute__((naked))


/*	Generic functions for counters
 *	Replaced by hw_bn()
 */
//#define hw_max(...)		HW_APPLY(hw_max, __VA_ARGS__)
