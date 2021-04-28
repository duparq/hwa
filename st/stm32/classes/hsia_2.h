
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HSI
 */

#define _hw_actions__hsia	, (power,stat)
#define _hwa_actions__hsia	, (power,stat)

/**
 * @addtogroup stm32_hsia
 *
 * @section stm32_hsiaif Interface
 *
 * * Power control
 *
 * @code
 * hw|hwa( power, hsi,   on
 *                     | off );
 * @endcode
 */

/* Implemented in stm32/hwa_2.h */

/**
 * @addtogroup stm32_hsia
 *
 * * Status:
 *
 * @code
 * // Wait for the HSI clock to be stable.
 * //
 * hw_stat_t(hsi) st = hw(stat,hsi) ;
 * while ( ! st.ready ) {}
 * @endcode
 */

/*  Status of the HSI
 */
typedef struct {
    unsigned int _0    :  1 ;
    unsigned int ready :  1 ;
    unsigned int _2_31 : 30 ;
} _hw_sthsi_t ;

#define hw_stat_t__hsia		, _hw_stthsi
#define _hw_stthsi(o,a,...)	 _hw_sthsi_t HW_EOL(__VA_ARGS__)

#define hw_stat__hsia		, _hw_sthsi
#define _hw_sthsi(o,a,...)	(*(volatile _hw_sthsi_t*)HW_ADDRESS((rcc,cr))) HW_EOL(__VA_ARGS__)
