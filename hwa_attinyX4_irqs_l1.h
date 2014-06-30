
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	Interrupt vectors, masks, flags
 */


/* #define hw_vectors_counter0()						\ */
/*   void __vector_9 (void) __attribute__ ((alias("__vector_counter0"))) ;	\ */
/*   void __vector_10 (void) __attribute__ ((alias("__vector_counter0"))) ;	\ */
/*   void __vector_11 (void) __attribute__ ((alias("__vector_counter0"))) */

/* #define hw_vectors_counter1()						\ */
/*   void __vector_5 (void) __attribute__ ((alias("__vector_counter1"))) ;	\ */
/*   void __vector_6 (void) __attribute__ ((alias("__vector_counter1"))) ;	\ */
/*   void __vector_7 (void) __attribute__ ((alias("__vector_counter1"))) ;	\ */
/*   void __vector_8 (void) __attribute__ ((alias("__vector_counter1"))) */


/*	Interrupt vectors, enable & flag bits
 *
 *	Syntax:		'irq', vector, controller, enable bit, flag bit
 */
#define hw_irq_pin_int0			irq, 1, hw_core0, int0, intf0

#define hw_irq_pcic0_all		irq, 2, hw_pcic0, irqe, irqf

#define hw_irq_pin_pcint7		irq, 2, hw_pcic0, pcint7, irqf
#define hw_irq_pin_pcint6		irq, 2, hw_pcic0, pcint6, irqf
#define hw_irq_pin_pcint5		irq, 2, hw_pcic0, pcint5, irqf
#define hw_irq_pin_pcint4		irq, 2, hw_pcic0, pcint4, irqf
#define hw_irq_pin_pcint3		irq, 2, hw_pcic0, pcint3, irqf
#define hw_irq_pin_pcint2		irq, 2, hw_pcic0, pcint2, irqf
#define hw_irq_pin_pcint1		irq, 2, hw_pcic0, pcint1, irqf
#define hw_irq_pin_pcint0		irq, 2, hw_pcic0, pcint0, irqf

#define hw_irq_pcic1_all		irq, 3, hw_pcic1, irqe, irqf

#define hw_irq_pin_pcint11		irq, 3, hw_pcic1, pcint11, irqf
#define hw_irq_pin_pcint10		irq, 3, hw_pcic1, pcint10, irqf
#define hw_irq_pin_pcint9		irq, 3, hw_pcic1, pcint9, irqf

#define hw_irq_pin_pcint8_		irq, 3, hw_pcic1, pcint8, irqf
#define hw_irq_pin_pcint8_all		irq, 3, hw_pcic1, pcint8, irqf

#define hw_irq_watchdog_all		irq, 4, hw_watchdog, ie, if
#define hw_irq_counter1_capture		irq, 5, hw_counter1, icie, icf
#define hw_irq_counter1_match_a		irq, 6, hw_counter1, ociea, ocfa
#define hw_irq_counter1_compare_a	irq, 6, hw_counter1, ociea, ocfa
#define hw_irq_counter1_match_b		irq, 7, hw_counter1, ocieb, ocfb
#define hw_irq_counter1_compare_b	irq, 7, hw_counter1, ocieb, ocfb
#define hw_irq_counter1_overflow	irq, 8, hw_counter1, oie, ov
					       
/* #define hw_irq_counter0_all		irq, counter0_all, all */
/* #define hw_irq_counter1_all		irq, counter1_all, all */

#define hw_irq_counter0_match_a		irq, 9, hw_counter0, ociea, ocfa
#define hw_irq_counter0_compare_a	irq, 9, hw_counter0, ociea, ocfa
#define hw_irq_counter0_match_b		irq, 10, hw_counter0, ocieb, ocfb
#define hw_irq_counter0_compare_b	irq, 10, hw_counter0, ocieb, ocfb
#define hw_irq_counter0_overflow	irq, 11, hw_counter0, oie, ov

#define hw_irq_acmp_all			irq, 12, acmp_all, 12
#define hw_irq_pin_ain1			irq, 12, ain1, 12
#define hw_irq_adc0_all			irq, 13, adc0_all, 13
#define hw_irq_eeprom_all		irq, 14, eeprom_all, 14
#define hw_irq_usi_str			irq, 15, usi_str, 15
#define hw_irq_usi_overflow		irq, 16, usi_overflow, 16
