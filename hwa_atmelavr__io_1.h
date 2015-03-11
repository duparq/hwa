
/*  Atmel AVR i/o pin class _io
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq free fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*  _io8a port
 */
#define hw_class__io8a
#define _hw_pop__io8a(p,i,a,...)	__VA_ARGS__

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw__io8a_port			_crg, 8, 0x02, 0xFF, 0x00
#define hw__io8a_ddr			_crg, 8, 0x01, 0xFF, 0x00
#define hw__io8a_pin			_crg, 8, 0x00, 0xFF, 0x00

#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t port ;
  hwa_r8_t ddr ;
} hwa_io8a_t ;

#endif


/*  _io6a port
 */
#define hw_class__io6a
#define _hw_pop__io6a(c,n,i,a,...)	__VA_ARGS__

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw__io6a_port			_crg, 8, 0x02, 0x3F, 0x00
#define hw__io6a_ddr			_crg, 8, 0x01, 0x3F, 0x00
#define hw__io6a_pin			_crg, 8, 0x00, 0x3F, 0x00

#define hwa_io6a_t			hwa_io8a_t


/*  i/o pins
 */
//#define hw_class__io
#define hw_class__dio

#define hw_mthd_hw_sup__dio			, _hw_sup_dio
//#define _hw_sup_io(c,n,i, cc,cn,ci,ca, ...)	cc,cn,ci,ca
#define _hw_sup_dio(n,i, cn,bn,bp,...)		HW_TX(cn, __VA_ARGS__)

#define hw_mthd_hw_bn__dio			, _hw_bn_dio
//#define _hw_bn_io(c,n,i, cc,cn,ci,ca, bn,bp)	bn
//#define _hw_bn_io(c,n,i, cc,cn,ci,ca, bn,bp,...)	HW_TX(bn,__VA_ARGS__)
#define _hw_bn_dio(c,id,cn,bn,bp)		bn

#define hw_mthd_hw_bp__dio			, _hw_bp_dio
//#define _hw_bp_io(c,n,i, cc,cn,ci,ca, bn,bp)	bp
#define _hw_bp_dio(n,i, cn,bn,bp, ...)		HW_TX(bp, __VA_ARGS__)

#define hw_mthd_hw_io__dio			, _hw_io_dio
#define _hw_io_dio(...)				__VA_ARGS__
