
/*  Atmel AVR i/o pin class _io
 *
 * This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @page atmelavr_io8a Class _io8a: i/o port
 * A class `_io8a` object is an i/o port.
 */
#define _hw_class__io8a

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define _hw__io8a_port			_r8, 0x02, 0xFF, 0x00
#define _hw__io8a_ddr			_r8, 0x01, 0xFF, 0x00
#define _hw__io8a_pin			_r8, 0x00, 0xFF, 0x00

#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t port ;
  hwa_r8_t ddr ;
} hwa_io8a_t ;

#endif


/*  _io6a port
 */
#define _hw_class__io6a
#define _hw_pop__io6a(c,n,i,a,...)	__VA_ARGS__

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define _hw__io6a_port			_r8, 0x02, 0x3F, 0x00
#define _hw__io6a_ddr			_r8, 0x01, 0x3F, 0x00
#define _hw__io6a_pin			_r8, 0x00, 0x3F, 0x00

#define hwa_io6a_t			hwa_io8a_t


/**
 * @page atmelavr_pin1 Class _pin1: i/o pin definition
 *
 * A class `_pin1` object is an i/o definition. This can be a single pin or a
 * group of consecutive pins inside the same port.
 */
#define _hw_class__pin1


/**
 * @page atmelavr_pin1
 * @section atmelavr_pin1_def Creating a pin definition (for developers)
 *
 * A `_pin1` class pin definition named `mypin` is created with:
 *
 *     #define _hw_pin_mypin	      	 _pin1, id, port, bn, bp
 *
 * where:
 *
 * * `id` is a unique number identifying the object
 *
 * * `port` is the name of the port object holding the pin, e.g.: hw_porta
 *
 * * `bn` is the number of consecutive bits the pin definition contains
 *
 * * `bp` is the position of the least significant bit of the pin definition in the port
 *
 */


/**
 * @page atmelavr_pin1
 * @section atmelavr_pin1_sup Getting the name of the port owning the pin
 *
 * Note: this triggers an error if the pin definition is spread accross
 * different ports.
 *
 * @code
 * #define PA0		hw_pin_pa0
 * #define PORTA	hw_port_a
 * #if hw_id(hw_sup(PA0)) != hw_id(PORTA)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_sup__pin1			, _hw_sup_pin1
#define _hw_sup_pin1(n,i, cn,bn,bp,...)		cn


/**
 * @page atmelavr_pin1
 * @section atmelavr_pin1_bn Getting the number of bits of a pin definition
 *
 * This is 1 for single pins, but can be greater for groups of consecutive pins.
 *
 * Note: this triggers an error if the pin definition contains more than one
 * group.
 *
 * @code
 * #if hw_id(hw_pin_pa3) && (hw_bn(hw_pin_pa3) != 1)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__pin1			, _hw_bn_pin1
#define _hw_bn_pin1(c,id,cn,bn,bp,...)		bn


/**
 * @page atmelavr_pin1
 * @section atmelavr_pin1_bp Getting the position of the pin in the port
 *
 * For a group of consecutive pins, this gives the position of the least
 * significant bit.
 *
 * Note: this triggers an error if the pin definition contains more than one
 * group.
 *
 * @code
 * #if hw_id(hw_pin_pa3) && (hw_bp(hw_pin_pa3) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bp__pin1			, _hw_bp_pin1
#define _hw_bp_pin1(p,i, cn,bn,bp,...)		bp


/**
 * @page atmelavr_pin1
 * @section atmelavr_pin1_io Getting the name of the i/o pin
 *
 * This is useful for example to check whether two pin names are in fact the same
 * pin, or to get the i/o pin associated to an object (compare output of a
 * counter...).
 *
 * @code
 * #if hw_id(hw_io(hw_pin_mosi)) != hw_id(hw_pin_pa6)
 * #  error MOSI and PA6 are not the same pin
 * #endif
 * @endcode
 *
 * @code
 * #if hw_id(hw_io(hw_sub(hw_counter0,compare0))) != hw_id(hw_pin_6)
 * #  error OC0A is not on pin 6
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_io__pin1			, _hw_io_pin1
#define _hw_io_pin1(p,i,cn,bn,bp,...)		p
