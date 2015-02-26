
/*  Atmel AVR i/o pin class _io
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq free fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*  _io8a port
 */
#define hw_class__io8a
#define _hw_pop__io8a(c,n,i,a,...)	__VA_ARGS__

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw__io8a_port			crg, 8, 0x02, 0xFF, 0x00
#define hw__io8a_ddr			crg, 8, 0x01, 0xFF, 0x00
#define hw__io8a_pin			crg, 8, 0x00, 0xFF, 0x00

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
#define hw__io6a_port			crg, 8, 0x02, 0x3F, 0x00
#define hw__io6a_ddr			crg, 8, 0x01, 0x3F, 0x00
#define hw__io6a_pin			crg, 8, 0x00, 0x3F, 0x00

#define hwa_io6a_t			hwa_io8a_t


/*  i/o pins
 */
#define hw_class__io

#define hw_def_hw_sup__io			, _hw_sup_io
#define _hw_sup_io(c,n,i, cc,cn,ci,ca, ...)	cc,cn,ci,ca

#define hw_def_hw_bn__io			, _hw_bn_io
#define _hw_bn_io(c,n,i, cc,cn,ci,ca, bn,bp)	bn
//#define _hw_bn_io(c,n,i, cc,cn,ci,ca, bn,bp,...)	HW_TX(bn,__VA_ARGS__)

#define hw_def_hw_bp__io			, _hw_bp_io
#define _hw_bp_io(c,n,i, cc,cn,ci,ca, bn,bp)	bp

#define hw_def_hw_io__io			, _hw_io_io
#define _hw_io_io(...)				__VA_ARGS__
