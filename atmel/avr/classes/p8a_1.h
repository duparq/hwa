
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O port
 */

/**
 * @page atmelavr_p8a Class _p8a: 8-bit I/O port
 *
 * A class `_p8a` object is an 8-bit I/O port.
 *
 * It is used in all Atmel AVR devices.
 */
#define hw_class__p8a

/*	Class registers			class, address, rwm, rfm
 */
#define hw_reg__p8a_port	_r8, 0x02, 0xFF, 0x00
#define hw_reg__p8a_ddr		_r8, 0x01, 0xFF, 0x00
#define hw_reg__p8a_pin		_r8, 0x00, 0xFF, 0x00


/*  Handle definitions such as HW_IO(port1,1,2)
 */
//#define hw_class__p8a_io

#define HW_IO__p8a			, _hw_io_p8a
#define _hw_io_p8a(o,i,a,bn,bp,...)	p8a_io(_p8a,o##_##bn##_##bp,-1,o,bn,bp)

#define _HW_X_p8a_io			, _hw_x_p8a_io
#define _hw_x_p8a_io(...)		_io1a, __VA_ARGS__

/* #define HW_NP__p8a_io			, _hw_np_p8a_io */
/* #define _hw_np_p8a_io(o,p,bn,bp,...)	bn,bp */


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t port ;
  hwa_r8_t ddr ;
} hwa_p8a_t ;

#endif
