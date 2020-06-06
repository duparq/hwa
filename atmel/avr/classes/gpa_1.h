
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


/*  Accept to append a number to a _gpa definition so that (portx,n) becomes a
 *  single pin at position n of portx.
 */
#define hw__gpa_			, _hw_gpa_
#define _hw_gpa_(o,n,a)			HW_YA(_hw_gpa_,_hw_isa_4bn_,n)(o,n)
#define _hw_gpa_1(o,n)			_ioa,o##_1_##n,(o,1,n)
#define _hw_gpa_0(o,n)			,(o,n),HW_EM(o has no relative n)


/*  Handle definitions such as HW_IO(port1,1,2)
 */
#define HW_IO__gpa			, _hw_io_gpa
//#define _hw_io_gpa(o,a,bn,bp,...)	_ioa,o##_##bn##_##bp,(o,bn,bp)
#define _hw_io_gpa(o,a,bn,bp,...)	HW_Y(_hw_io_gpa,__VA_ARGS__)(o,p,bn,bp,__VA_ARGS__)
#define _hw_io_gpa1(o,a,bn,bp,...)	_ioa,o##_##bn##_##bp,(o,bn,bp) HW_EOL(__VA_ARGS__)


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t port ;
  hwa_r8_t ddr ;
} hwa_gpa_t ;

#endif
