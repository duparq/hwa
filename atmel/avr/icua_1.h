
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */


/**
 * @page atmelavr_icua Class _icua: counter/timer capture unit
 *
 * A class `_icua` object is a capture unit.
 *
 */
#define _hw_class__icua


/**
 * @page atmelavr_icua
 * @section atmelavr_icua_sup Name of the related counter
 *
 * The `hw_sup(...)` instruction retrieves the name of the counter related to
 * the capture unit.
 *
 * @code
 * #define CAPTURE	hw_counter0_capture0
 * #define COUNTER	hw_sup( CAPTURE ) 
 *
 * #if hw_bn(COUNTER) != 16
 * #  error Only 16-bit counter is supported!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_sup__icua			, _hw_sup_icua
#define _hw_sup_icua(p,i,cn,ch,ion,_)		cn


/**
 * @page atmelavr_icua
 * @section atmelavr_icua_io Name of the related i/o pin
 *
 * The `hw_io(...)` instruction retrieves the name of i/o pin related to the
 * capture unit.
 *
 * @code
 * #define COUNTER	hw_counter0
 * #define CAPTURE	hw_sub( COUNTER, capture0 )
 * #define INPUT	hw_io( CAPTURE )
 *
 * #if hw_id(INPUT) == hw_id(hw_pin_6)
 * #  error pin 6 is already used
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_io__icua			, _hw_ioicu
#define _hw_ioicu(p,i,cn,ch,ion,...)		HW_TX(hw_##ion, __VA_ARGS__)
