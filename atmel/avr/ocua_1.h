
/*	Atmel AVR 8-bit timer-counter compare unit version 'a'
 *
 *	Used in: ATtinyX4 OC0A	hw_counter0_compare0
 *		 	  OC0B	hw_counter0_compare1
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/**
 * @page atmelavr_ocua Class _ocua: counter/timer compare unit with waveform
 * generator
 *
 * A class `_ocua` object is a counter/timer compare unit with waveform
 * generator.
 *
 */
#define _hw_class__ocua


/**
 * @page atmelavr_ocua
 *
 * @par Name of the related counter
 *
 * @code
 * #define COMPARE	hw_counter0_compare0
 * #define COUNTER	hw_sup( COMPARE ) 
 *
 * #if hw_bn(COUNTER) != 16
 * #  error Only 16-bit counter is supported!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_sup__ocua			, _hw_sup_ocua
#define _hw_sup_ocua(p,i,cn,ch,ion,_)		cn


/**
 * @page atmelavr_ocua
 *
 * @par Name of the related i/o pin
 *
 * @code
 * #define COUNTER	hw_counter0
 * #define COMPARE	hw_sub( COUNTER, compare0 )
 * #define OUTPUT	hw_io( COMPARE )
 *
 * #if hw_id(OUTPUT) == hw_id(hw_pin_mosi)
 * #  error OUTPUT pin is in conflict with pin MOSI
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_io__ocua			, _hw_io_ocu
#define _hw_io_ocu(p,i,cn,ch,ion,...)		HW_TX(hw_##ion, __VA_ARGS__)


/*  Compare units are defined in their related counter.
 *  Nothing to be declared here.
 */
