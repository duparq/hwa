
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief STM32F103RB
 */

#include "../hwa_1.h"

/**
 * @page stm32f103rb STM32F103RB
 *
 * @section stm32f103rb_sym Defined symbols
 *
 * HWA defines the following symbols describing the target device and its
 * hardware configuration:
 *
 * Symbol		    | Comments
 * :------------------------|:-----------
 * `HW_DEVICE_STM32F103RB`     |Void.
 * `HW_DEVICE_STM32F103xB`     |Void.
 * `HW_DEVICE_FLASH_SIZE`      |128*1024
 * `HW_DEVICE_RAM_SIZE`	       |20*1024
 * `HW_DEVICE_HSIHZ`	       |8000000
 *
 * See also:
 * * @ref stm32f103
 */
#define HW_DEVICE_STM32F103RB
/* #define HW_DEVICE_ARCH		arm */
#define HW_DEVICE_STM32F103xB
#define HW_DEVICE_FLASH_SIZE		128*1024
#define HW_DEVICE_RAM_SIZE		20*1024
#define HW_DEVICE_HSIHZ			8000000


/*******************************************************************************
 *									       *
 *	Clocks								       *
 *									       *
 *******************************************************************************/

#include "../classes/rcca_1.h"

#define _hw_def_rcc0			_rcca, 100, 0x40021000

/*	Object registers		class, address, wm, fm
 */
#define _hw_reg_rcc0_apb2enr		_r32, 0x18, 0x0038FFFD, 0


/*******************************************************************************
 *									       *
 *	Ports and pins							       *
 *									       *
 *******************************************************************************/

/**
 * @page stm32f103rb
 * @section stm32f103rb_pins Ports and pins
 *
 * HWA name	| 14pdip      | Class			  | Atmel name
 * -------------|-------------|---------------------------|-----------
 * `porta`	|	      | @ref atmelavr_p8a "_p8a"   | PORTA
 * `pin_pa0` | `pin_13` | @ref atmelavr_io1a "_io1a" | PA0
 * `pin_pa1` | `pin_12` | @ref atmelavr_io1a "_io1a" | PA1
 * `pin_pa2` | `pin_11` | @ref atmelavr_io1a "_io1a" | PA2
 * `pin_pa3` | `pin_10` | @ref atmelavr_io1a "_io1a" | PA3
 * `pin_pa4` | `pin_9`	| @ref atmelavr_io1a "_io1a" | PA4
 * `pin_pa5` | `pin_8`	| @ref atmelavr_io1a "_io1a" | PA5
 * `pin_pa6` | `pin_7`	| @ref atmelavr_io1a "_io1a" | PA6
 * `pin_pa7` | `pin_6`	| @ref atmelavr_io1a "_io1a" | PA7
 * `portb`	|	      | @ref atmelavr_p8a "_p8a"   | PORTB
 * `pin_pb0` | `pin_2`	| @ref atmelavr_io1a "_io1a" | PB0
 * `pin_pb1` | `pin_3`	| @ref atmelavr_io1a "_io1a" | PB1
 * `pin_pb2` | `pin_5`	| @ref atmelavr_io1a "_io1a" | PB2
 * `pin_pb3` | `pin_4`	| @ref atmelavr_io1a "_io1a" | PB3
 */

#include "../classes/p16a_1.h"
#include "../classes/io1a_1.h"

/*	Objects				class, id, address
 */
#define _hw_def_port0			_p16a, 100, 0x40010800
#define _hw_def_port1			_p16a, 100, 0x40010c00
#define _hw_def_port2			_p16a, 100, 0x40011000
#define _hw_def_port3			_p16a, 100, 0x40014000
#define _hw_def_port4			_p16a, 100, 0x40011800
#define _hw_def_port5			_p16a, 100, 0x40011c00
#define _hw_def_port6			_p16a, 100, 0x40012000

/*	Object registers
 */
#define _hw_reg_port0_cken		_xob1, rcc0, apb2enr, 1, 2

/*  Pins				class, id, peripheral, bn, bp
 */
#define _hw_def_pin_pa0			_io1a, 104, port0,  1,  0
#define _hw_def_pin_pa1			_io1a, 105, port0,  1,  1
#define _hw_def_pin_pa2			_io1a, 106, port0,  1,  2
#define _hw_def_pin_pa3			_io1a, 107, port0,  1,  3
#define _hw_def_pin_pa4			_io1a, 108, port0,  1,  4
#define _hw_def_pin_pa5			_io1a, 109, port0,  1,  5
#define _hw_def_pin_pa6			_io1a, 110, port0,  1,  6
#define _hw_def_pin_pa7			_io1a, 111, port0,  1,  7
#define _hw_def_pin_pa8			_io1a, 111, port0,  1,  8
#define _hw_def_pin_pa9			_io1a, 111, port0,  1,  9
#define _hw_def_pin_pa10		_io1a, 111, port0,  1, 10
#define _hw_def_pin_pa11		_io1a, 111, port0,  1, 11
#define _hw_def_pin_pa12		_io1a, 111, port0,  1, 12
#define _hw_def_pin_pa13		_io1a, 111, port0,  1, 13
#define _hw_def_pin_pa14		_io1a, 111, port0,  1, 14
#define _hw_def_pin_pa15		_io1a, 111, port0,  1, 15
#define _hw_def_porta			_io1a, 112, port0, 16,  0

#if defined HW_DEVICE_PACKAGE_LQFP64
#
#  define _hw_pin_14			, pin_pa0
#  define _hw_pin_15			, pin_pa1
#  define _hw_pin_16			, pin_pa2
#  define _hw_pin_17			, pin_pa3
#  define _hw_pin_20			, pin_pa4
#  define _hw_pin_21			, pin_pa5
#  define _hw_pin_22			, pin_pa6
#  define _hw_pin_23			, pin_pa7
#  define _hw_pin_41			, pin_pa8
#  define _hw_pin_42			, pin_pa9
#  define _hw_pin_43			, pin_pa10
#  define _hw_pin_44			, pin_pa11
#  define _hw_pin_45			, pin_pa12
#  define _hw_pin_46			, pin_pa13
#  define _hw_pin_49			, pin_pa14
#  define _hw_pin_50			, pin_pa15

#endif




#if !defined __ASSEMBLER__

/**
 * @brief The HWA context
 *
 * This structure is instanciated by hwa_begin() or hwa_begin_from_reset() and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/

  hwa_rcca_t	rcc0 ;

  hwa_p16a_t	port0 ;
  hwa_p16a_t	port1 ;
  hwa_p16a_t	port2 ;
  hwa_p16a_t	port3 ;
  hwa_p16a_t	port4 ;
  hwa_p16a_t	port5 ;
  hwa_p16a_t	port6 ;
} hwa_t ;

#include "../hwa_2.h"
#include "../classes/rcca_2.h"
#include "../classes/io1a_2.h"
#include "../classes/p16a_2.h"

HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup( rcc0 );
  _hwa_setup( port0 );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init( rcc0 );
  _hwa_init( port0 );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_commit( rcc0 );
  _hwa_commit( port0 );
}

#endif /* !defined __ASSEMBLER__ */

/**
 * @page stm32f103rb
 * <br>
 */
