
/* This file is part of the HWA project.
 * Copyright (c) 2012 Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/** \brief	Target device is an Atmel AVR.
 */
#define HW_DEVICE_ATMELAVR


/*	Register address offset for C/assembler
 */
#ifndef __ASSEMBLER__
#  define HW_RA_OFFSET		0
#else
#  define HW_RA_OFFSET		-0x20
#endif


/**\brief	Reset watchdog timer
 */
#define hw_reset_watchdog()		__asm__( "wdr":: )

/**\brief	Enable watchdog
 */
#define hw_enable_watchdog()		hw_write( hw_core0, wde, 1 )


/*	Enable/disable interrupts
 */
#define hw_enable_irqs()		__asm__ __volatile__ ("sei" ::)
#define hw_disable_irqs()		__asm__ __volatile__ ("cli" ::)


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
#define _hw_isr_(name, vector, ...)					\
  HW_EXTERN_C void __vector_##vector(void) HW_ISR_ATTRIBUTES __VA_ARGS__ ; \
  void __vector_##vector (void)

#define hw_israttr_interruptible	__attribute__((interrupt))
#define hw_israttr_non_interruptible
#define hw_israttr_naked		__attribute__((naked))


/*	Generic functions for counters
 */
//#define hw_typeof_counter	, ok, per
#define hw_max(...)		HW_APPLY(hw_max, __VA_ARGS__)
