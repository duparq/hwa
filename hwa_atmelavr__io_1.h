
/*  Atmel AVR i/o pin class _io
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq free fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @page atmelavr_io8a _io8a
 * A class `_io8a` object is an i/o port.
 */
#define _hw_class__io8a

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define _hw__io8a_port			_crg, 8, 0x02, 0xFF, 0x00
#define _hw__io8a_ddr			_crg, 8, 0x01, 0xFF, 0x00
#define _hw__io8a_pin			_crg, 8, 0x00, 0xFF, 0x00

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
#define _hw__io6a_port			_crg, 8, 0x02, 0x3F, 0x00
#define _hw__io6a_ddr			_crg, 8, 0x01, 0x3F, 0x00
#define _hw__io6a_pin			_crg, 8, 0x00, 0x3F, 0x00

#define hwa_io6a_t			hwa_io8a_t


/**
 * @page atmelavr_dio _dio
 * A class `_dio` object is an i/o pin.
 */
#define _hw_class__dio


/**
 * @page atmelavr_dio
 * @par Get the name of the port owning the pin
 * @code
 * #define PA0		hw_pin_pa0
 * #define PORTA	hw_porta
 * #if hw_id(hw_sup(PA0)) != hw_id(PORTA)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_sup__dio			, _hw_sup_dio
#define _hw_sup_dio(n,i, cn,bn,bp,...)		cn


/**
 * @page atmelavr_dio
 * @par Get the number of bits of the pin
 * Of course, this should be 1.
 * @code
 * #if hw_id(hw_pin_pa3) && (hw_bn(hw_pin_pa3) != 1)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__dio			, _hw_bn_dio
#define _hw_bn_dio(c,id,cn,bn,bp,...)		bn


/**
 * @page atmelavr_dio
 * @par Get the position of the pin in the port
 * @code
 * #if hw_id(hw_pin_pa3) && (hw_bp(hw_pin_pa3) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bp__dio			, _hw_bp_dio
#define _hw_bp_dio(p,i, cn,bn,bp,...)		bp


/**
 * @page atmelavr_dio
 * @par Get the name of the i/o pin
 * @code
 * #if hw_id(hw_io(hw_pin_mosi)) != hw_id(hw_pin_pa6)
 * #  error MOSI and PA6 are not the same pin
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_io__dio			, _hw_io_dio
#define _hw_io_dio(p,i,cn,bn,bp,...)		p
