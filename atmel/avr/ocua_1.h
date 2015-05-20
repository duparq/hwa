
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	Atmel AVR 8-bit timer-counter compare unit version 'a'
 *
 *	Used in: ATtinyX4 OC0A	hw_counter0_compare0
 *		 	  OC0B	hw_counter0_compare1
 */


/**
 * @page atmelavr_ocua Class _ocua: counter/timer compare unit with waveform generator
 *
 * A class `_ocua` object is a counter/timer compare unit with waveform
 * generator.
 *
 */
#define _hw_class__ocua


/**
 * @page atmelavr_ocua
 * @section atmelavr_ocua_macros Instructions that do not produce code
 * @subsection atmelavr_ocua_sup Name of the related counter
 *
 * The `hw_sup(...)` instruction retrieves the name of the counter of the compare unit:
 *
 * @code
 * #if hw_id( hw_sup(hw_counter0_compare0) ) != hw_id( hw_counter0 )
 * #  error Houston, we have a problem
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_sup__ocua			, _hw_sup_ocua
#define _hw_sup_ocua(p,i,cn,ch,ion,_)		cn


/**
 * @page atmelavr_ocua
 *
 * @subsection atmelavr_ocua_io Name of the related i/o pin
 *
 * @code
 * #if hw_id( hw_io(hw_counter0_compare0) != hw_id(hw_pin_mosi)
 * #  error Pin OC0A is in conflict with pin MOSI
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_io__ocua			, _hw_io_ocu
#define _hw_io_ocu(p,i,cn,ch,ion,...)		HW_TX(hw_##ion, __VA_ARGS__)


/*  Compare units are defined in their related counter.
 *  Nothing to be declared here.
 */
