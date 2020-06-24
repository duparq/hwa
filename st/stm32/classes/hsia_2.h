
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HSI
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_hsia Class _hsia: HSI oscillator
 *
 * @section stm32_hsia_act Actions
 *
 * * Power the HSI on/off:
 *
 * @code
 * hw|hwa( power, hsi,   on
 *                     | off
 * );
 * @endcode
 */

/* Implemented in stm32/hwa_2.h */

/**
 * @addtogroup stm32_hsia
 *
 * * Get the status of the HSI (the only flag it
 * contains is `ready`):
 *
 * @code
 * hw_stat_t(hsi) st = hw(stat,hsi) ;
 * @endcode
 *
 * @code
 * while ( ! hw(stat,hsi).ready ) {}	// Wait for the HSI clock to be stable.
 * @endcode
 * <br>
 *
 * @section stm32_hsia_reg Registers
 *
 * Logical registers:
 *
 */

/*  Status of the HSI
 */
typedef struct {
    unsigned int _0    :  1 ;
    unsigned int ready :  1 ;
    unsigned int _2_31 : 30 ;
} _hw_sthsi_t ;

#define hw_stat_t__hsia			, _hw_stthsi
#define _hw_stthsi(o,a,...)		 _hw_sthsi_t HW_EOL(__VA_ARGS__)

#define hw_stat__hsia			, _hw_sthsi
#define _hw_sthsi(o,a,...)		(*(volatile _hw_sthsi_t*)HW_ADDRESS((rcc,cr))) HW_EOL(__VA_ARGS__)
