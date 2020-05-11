
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O (not connected).
 */

#define hw_configure__io0a		, _hw_io0ax
#define hw_read__io0a			, _hw_io0ax
#define hw_write__io0a			, _hw_io0ax
#define hw_toggle__io0a			, _hw_io0ax

#define _hw_io0ax( o, ... )		HW_E(pin `o` is not connected)

#define hwa_configure__io0a		, _hwa_io0ax
#define hwa_write__io0a			, _hwa_io0ax

#define _hwa_io0ax( o, ... )		HWA_ERR("`" #o "` is not connected.")
