
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr__acmpa_1.h"

/*
 *	Analog comparator
 */

/*	Instance			class, name, id, address
 */				        
#define hw_acmp0			_acmpa, acmp0, 700, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */				        
#define _hw__acmpa_csr			crg, 8, 0x28, 0xDF, 0x10
