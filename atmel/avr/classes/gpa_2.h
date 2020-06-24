
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O port
 */

/**
 * @addtogroup atmelavr_gpa
 * @section atmelavr_gpaact Actions
 *
 * @note These actions are not implemented yet. Configure the GPIO pins instead.
 *
 * <br><br>hw( configure, ... ) and hwa( configure, ... ): configure all the pins of the gpio port PORT.
 *
 * @code
 * hw( configure, portb, mode, output_pushpull );
 * @endcode
 *
 * @code
 * hw( configure, portb, mode, input_pullup );
 * @endcode
 */
#define hw_configure__gpa		, _hw_cfgpa
#define x_hw_cfgpa			


/**
 * @addtogroup atmelavr_gpa
 *
 * <br><br>hw( read, PORT ): gets the status of all the pins of the gpio port PORT.
 *
 * @code
 * hw( read, portb );
 * @endcode
 */


/**
 * @addtogroup atmelavr_gpa
 *
 * <br><br>hw( write, PORT, ... ) and hwa( write, PORT, ... ): configure all the pins of the gpio port PORT.
 *
 * @code
 * hw( write, portb, 0xBE );
 * @endcode
 *
 * @code
 * hwa( write, portb, 0xEF );
 * @endcode
 */
#define hw_write__gpa		, _hw_wrgpa
#define _hw_wrgpa(o,a,v,...)	_hw_wrioa(o,o,8,0,v,)

#define hwa_write__gpa		, _hwa_wrgpa
#define _hwa_wrgpa(o,a,v,...)	_hwa_wrioa(o,o,8,0,v,)


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__gpa(o,a)			\
  _hwa_setup_r( o, port );			\
  _hwa_setup_r( o, ddr	)

#define _hwa_init__gpa(o,a)			\
  _hwa_init_r( o, port, 0x00 );			\
  _hwa_init_r( o, ddr,	0x00 )

#define _hwa_commit__gpa(o,a)			\
  _hwa_commit_r( o, port );			\
  _hwa_commit_r( o, ddr	 )
