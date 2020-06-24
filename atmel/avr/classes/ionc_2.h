
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O (not connected).
 */

#define hw_configure__ionc		, _hw_ioncx
#define hwa_configure__ionc		, _hw_ioncx
#define hw_read__ionc			, _hw_ioncx
#define hw_write__ionc			, _hw_ioncx
#define hwa_write__ionc			, _hw_ioncx
#define hw_toggle__ionc			, _hw_ioncx
#define hwa_toggle__ionc			, _hw_ioncx

#define _hw_ioncx( o, ... )		HW_ERR(HW_EM_ONC(o))
