
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HSI
 */

/**
 * @page stm32_hsia Class _hsia: HSI oscillator
 *
 * `power`:
 * @code
 * hw | hwa ( power, hsi,   on
 *                        | off );
 * @endcode
 */

/* Implemented in stm32/hwa_2.h */

/**
 * @page stm32_hsia
 * <br>
 * `stat`:
 * @code
 * while ( ! hw(stat,hsi).ready ) {}	// Wait for the HSI clock to be stable.
 * @endcode
 * <br>
 */
typedef struct {
    unsigned int _0    :  1 ;
    unsigned int ready :  1 ;
    unsigned int _2_31 : 30 ;
} _hw_sthsi_t ;

#define _hw_mtd_hw_stat_t_hsi		, _hw_stthsi
#define _hw_stthsi(o,i,a,...)		 _hw_sthsi_t HW_EOL(__VA_ARGS__)

#define _hw_mtd_hw_stat_hsi		, _hw_sthsi
#define _hw_sthsi(o,i,a,g,...)		HW_Y(_hw_sthsi1,g)(g)
#define _hw_sthsi1_0(g)			HW_E_G(g)
#define _hw_sthsi1_1(g)			(*(volatile _hw_sthsi_t*)_HW_A(_HW_R(rcc,cr)))
