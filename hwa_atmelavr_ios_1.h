
/* This file is ca+rt of the HWA project.
 * Copyright (c) Christophe Duca+rquet <duca+rq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/**
 * \file
 * \brief	IO functions common to all Atmel 8-bit AVR chips
 */


/*	Class & methods
 */
#define hw_class_io

#define hw_def_hw_ctr_io			, _hw_ctr_io
#define _hw_ctr_io(c,n,i, cc,cn,ci,ca, ...)	cc,cn,ci,ca

#define hw_def_hw_bn_io				, _hw_bn_io
#define _hw_bn_io(c,n,i, cc,cn,ci,ca, bn,bp)	bn

#define hw_def_hw_bp_io				, _hw_bp_io
#define _hw_bp_io(c,n,i, cc,cn,ci,ca, bn,bp)	bp

#define hw_def_hw_io_io				, _hw_io_io
#define _hw_io_io(...)				__VA_ARGS__
