
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O configurator
 */

/**
 * @page espressif_pcfb Class _pcfb: I/O configurator
 *
 * A class `_pcfb` object is a I/O configurator. It configures the function,
 * direction, and pull-down of an I/O pin.
 */
#define hw_class__pcfb

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__pcfb__reg			_r32, 0x00, 0xFFFFFFFF, 0

/*	Class logical registers		class, reg, bn, bp
 */
#define hw__pcfb_fn			_cb2, _reg, 1, 6, 2, _reg, 2, 0, 0
#define hw__pcfb_spd			_cb1, _reg, 1, 5
#define hw__pcfb_pd			_cb1, _reg, 1, 3
#define hw__pcfb_pdx			_cb2, _reg, 1, 5, 1, _reg, 1, 3, 0 /* convenient */


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t	_reg ;
} hwa_pcfb_t ;

#endif
