
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#ifndef _HW_ATMELAVR_COUNTERS_H_
#define _HW_ATMELAVR_COUNTERS_H_

/*
 *	HWA common declarations to all Atmel AVR counter-timers
 */

/* #include "hwa_atmelavr__ocua_2.h" */
/* #include "hwa_atmelavr__icua_2.h" */


/*	Parameters for counter units
 */
#define hw_counter_overflow_at_bottom		, 0
#define hw_counter_overflow_at_top		, 1
#define hw_counter_overflow_at_max		, 2

#define hw_counter_update_immediately		, 0
#define hw_counter_update_at_bottom		, 1
#define hw_counter_update_at_top		, 2

#endif
