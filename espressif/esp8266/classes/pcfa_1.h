
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O configurator
 */

/**
 * @page espressif_pcfa Class _pcfa: I/O configurator
 *
 * A class `_pcfa` object is a I/O configurator. It configures the function,
 * direction, and pull-up of an I/O pin.
 *
 * It is used in:
 *  * @ref esp8266
 *
 */
#define hw_class__pcfa

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw_reg__pcfa__reg		_r32, 0x00, 0x1BB, 0

/*	Class logical registers		class, reg, bn, bp
 */
#define hw_reg__pcfa_fn			_cb2, _reg, 1, 8, 2, _reg, 2, 4, 0
#define hw_reg__pcfa_pu			_cb1, _reg, 1, 7
#define hw_reg__pcfa_spu		_cb1, _reg, 1, 3
#define hw_reg__pcfa_pux		_cb2, _reg, 1, 7, 1, _reg, 1, 3, 0 /* convenient */
#define hw_reg__pcfa_soe		_cb1, _reg, 1, 1
#define hw_reg__pcfa_oe			_cb1, _reg, 1, 0
#define hw_reg__pcfa_oex		_cb1, _reg, 2, 0 /* convenient */


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t	_reg ;
} hwa_pcfa_t ;

#endif
