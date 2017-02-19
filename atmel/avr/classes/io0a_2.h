
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O (not connected).
 */

#define _hw_mthd_hw_configure__io0a	, _hw_io0ax
#define _hw_mthd_hw_read__io0a		, _hw_io0ax
#define _hw_mthd_hw_write__io0a		, _hw_io0ax
#define _hw_mthd_hw_toggle__io0a	, _hw_io0ax

#define _hw_io0ax( o, ... )		HW_E(pin `o` is not connected)

#define _hw_mthd_hwa_configure__io0a	, _hwa_io0ax
#define _hw_mthd_hwa_write__io0a	, _hwa_io0ax

#define _hwa_io0ax( o, ... )		HWA_ERR("`" #o "` is not connected.")

/**
 * @page atmelavr_io0a
 * <br>
 */
