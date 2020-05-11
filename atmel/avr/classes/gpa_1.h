
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O port
 */

/**
 * @page atmelavr_gpa Class _gpa: 8-bit I/O port
 *
 * A class `_gpa` object is an 8-bit I/O port.
 *
 * It is used in all Atmel AVR devices.
 */
#define hw_class__gpa

/*	Class registers			class, address, rwm, rfm
 */
#define hw__gpa_port			_r8, 0x02, 0xFF, 0x00
#define hw__gpa_ddr			_r8, 0x01, 0xFF, 0x00
#define hw__gpa_pin			_r8, 0x00, 0xFF, 0x00


/*  Handle definitions such as HW_IO(port1,1,2)
 */
#define HW_IO__gpa			, _hw_io_gpa
#define _hw_io_gpa(o,a,bn,bp,...)	xb(_ioa,o##_##bn##_##bp,-1,o,bn,bp)
//#define _hw_io_gpa(o,a,bn,bp,...)	_ioa,o##_##bn##_##bp,(-1,o,bn,bp)


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t port ;
  hwa_r8_t ddr ;
} hwa_gpa_t ;

#endif
