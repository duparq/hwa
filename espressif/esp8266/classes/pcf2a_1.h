
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/*	DO NOT USE!
 *
 *	This is a temporary file, for experimentation. <hwa/twimaster.h> should be used instead.
 */

#error Do not use this!

/*
 * @file
 * @brief I/O configurator
 */

/*
 * espressif_pcf2a Class _pcf2a: I/O configurator
 *
 * A class `_pcf2a` object is a I/O configurator. It configures the wake-up,
 * interrupt input, output driver, and signal source.
 *
 * It is used in:
 *  * @ref esp8266
 *
 */
#define _hw_class__pcf2a

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw__pcf2a__reg			_r32, 0x00, 0x0785, 0

/*	Class logical registers		class, reg, bn, bp
 */
#define _hw__pcf2a_wue			_cb1, _reg, 1, 10	// Wake-up enable
#define _hw__pcf2a_intt			_cb1, _reg, 3, 7	// Interrupt type
#define _hw__pcf2a_drv			_cb1, _reg, 1, 2	// Drive (push-pull / open drain)
#define _hw__pcf2a_src			_cb1, _reg, 1, 0	// Source (sigma-delta / gpio)


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t	_reg ;
} hwa_pcf2a_t ;

#endif
