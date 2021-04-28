
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HSE
 */

#define _hw_actions__hsea	, (power,stat)
#define _hwa_actions__hsea	, (power,stat)

/**
 * @addtogroup stm32_hsea
 *
 * @section stm32_hseaif Interface
 *
 * * Power control
 *
 * @code
 * hw|hwa( power, hse,   on
 *		       | off );
 * @endcode
 */

/* Implemented in stm32/hwa_2.h */

/**
 * @addtogroup stm32_hsea
 *
 * * Status:
 *
 * @code
 * // Wait for the HSE clock to be stable.
 * //
 * hw_stat_t(hse) st = hw(stat,hse) ;
 * while ( ! st.ready ) {}
 * @endcode
 */

typedef struct {
    unsigned int _0_16	: 17 ;
    unsigned int ready	:  1 ;
    unsigned int _18_31 : 14 ;
} _hw_sthse_t ;

#define hw_stat_t__hsea		, _hw_stthse
#define _hw_stthse(o,a,...)	 _hw_sthse_t HW_EOL(__VA_ARGS__)

#define hw_stat__hsea		, _hw_sthse
#define _hw_sthse(o,a,...)	(*(volatile _hw_sthse_t*)HW_ADDRESS((rcc,cr))) HW_EOL(__VA_ARGS__)
