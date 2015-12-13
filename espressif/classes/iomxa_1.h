
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O multiplexer _iomxa
 */

/**
 * @page espressif_iomxa Class _iomxa: 16-bit I/O multiplexer
 *
 * A class `_iomxa` object is a 16-bit I/O multiplexer.
 *
 * It is used in:
 *  * @ref esp8266
 *
 * The connection of an I/O pin and a signal is done through the
 * hw_config() instruction applied to the pin.
 */
#define _hw_class__iomxa


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t	_conf ;
  hwa_r32_t	hw_pin_gpio0 ;
  hwa_r32_t	hw_pin_gpio1 ;
  hwa_r32_t	hw_pin_gpio2 ;
  hwa_r32_t	hw_pin_gpio3 ;
  hwa_r32_t	hw_pin_gpio4 ;
  hwa_r32_t	hw_pin_gpio5 ;
  hwa_r32_t	hw_pin_gpio6 ;
  hwa_r32_t	hw_pin_gpio7 ;
  hwa_r32_t	hw_pin_gpio8 ;
  hwa_r32_t	hw_pin_gpio9 ;
  hwa_r32_t	hw_pin_gpio10 ;
  hwa_r32_t	hw_pin_gpio11 ;
  hwa_r32_t	hw_pin_gpio12 ;
  hwa_r32_t	hw_pin_gpio13 ;
  hwa_r32_t	hw_pin_gpio14 ;
  hwa_r32_t	hw_pin_gpio15 ;
} hwa_iomxa_t ;

#endif
