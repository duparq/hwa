
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq free fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/**
 * \file
 * \brief	IO functions common to all Atmel 8-bit AVR chips
 */


/*	Class & methods
 */
#define hw_class_io

#define hw_def_hw_sup_io			, _hw_sup_io
#define _hw_sup_io(c,n,i, cc,cn,ci,ca, ...)	cc,cn,ci,ca

#define hw_def_hw_bn_io					, _hw_bn_io
#define _hw_bn_io(c,n,i, cc,cn,ci,ca, bn,bp)		bn
//#define _hw_bn_io(c,n,i, cc,cn,ci,ca, bn,bp,...)	HW_TX(bn,__VA_ARGS__)

#define hw_def_hw_bp_io					, _hw_bp_io
#define _hw_bp_io(c,n,i, cc,cn,ci,ca, bn,bp)		bp

#define hw_def_hw_io_io				, _hw_io_io
#define _hw_io_io(...)				__VA_ARGS__
