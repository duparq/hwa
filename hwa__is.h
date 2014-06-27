
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	1 if the first two arguments are the same, 0 otherwise
 */
#define HW_IS(...)		_HW_IS_2(__VA_ARGS__,,)
#define _HW_IS_2(x,y,...)	HW_A1(hw_is_##x##_##y,0)

#define hw_is_0_0			, 1,	/* the comma to remove '; StaticAssert(...)' */
#define hw_is_1_1			, 1
#define hw_is__				, 1
#define hw_is_aio_aio			, 1
#define hw_is_bottom_bottom		, 1
#define hw_is_clock_clock		, 1
#define hw_is_countmode_countmode	, 1
#define hw_is_ctr_ctr			, 1
#define hw_is_io_io			, 1
#define hw_is_irq_irq			, 1
#define hw_is_ocra_ocra			, 1
#define hw_is_ocu_ocu			, 1
#define hw_is_ok_ok			, 1
//#define hw_is_reg_reg			, 1
#define hw_is_state_state		, 1
#define hw_is_top_top			, 1
//#define hw_is_type_type			, 1
