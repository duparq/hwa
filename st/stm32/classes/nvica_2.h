
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Class _nvica
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_nvica Class _nvica: Nested Vectored Interrupt Controller (NVIC)
 *
 * This class is used by:
 *
 * * @ref stm32f103 "STM32F103": `nvic`
 *
 * @section Actions
 *
 * * enable/disable IRQs at the NVIC level:
 *
 * @code
 * hw|hwa( enable, (nvic,OBJECT) );
 * @endcode
 *
 * @code
 * hw|hwa( disable, (nvic,OBJECT) );
 * @endcode
 */

#define hw_enable__nvi			, _hw_nvien
#define _hw_nvien(a,...)		_hw_nvic_enable(a)

#define hwa_enable__nvi			, _hwa_nvien
#define _hwa_nvien(a,...)		_hwa_nvic_enable(hwa,a)

#define hw_disable__nvi			, _hw_nvids
#define _hw_nvids(a,...)		_hw_nvic_enable(a)

#define hwa_disable__nvi		, _hwa_nvids
#define _hwa_nvids(a,...)		_hwa_nvic_enable(hwa,a)


HW_INLINE void _hw_nvic_enable ( uint8_t v )
{
  if ( v < 32 )
    _hw_write_m(nvic, iser0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hw_write_m(nvic, iser1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hw_write_m(nvic, iser2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(HW_EM_X([nvica2.h:_hw_nvic_enable()]interrupt not supported));
}

HW_INLINE void _hwa_nvic_enable ( hwa_t *hwa, uint8_t v )
{
  if ( v < 32 )
    _hwa_write_m(nvic, iser0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hwa_write_m(nvic, iser1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hwa_write_m(nvic, iser2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(HW_EM_X([nvica2.h:_hwa___nvic_enable()]interrupt not supported));
}

HW_INLINE void _hw_nvic_disable ( uint8_t v )
{
  if ( v < 32 )
    _hw_write_m(nvic, icer0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hw_write_m(nvic, icer1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hw_write_m(nvic, icer2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(HW_EM_X([nvica2.h:_hw_nvic_disable()]interrupt not supported));
}

HW_INLINE void _hwa_nvic_disable ( hwa_t *hwa, uint8_t v )
{
  if ( v < 32 )
    _hwa_write_m(nvic, icer0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hwa_write_m(nvic, icer1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hwa_write_m(nvic, icer2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(HW_EM_X([nvica2.h:_hwa___nvic_disable()]interrupt not supported));
}


/**
 * @addtogroup stm32_nvica
 *
 * * clear a pending interrupt:
 *
 * @code
 * hw( clear, (nvic,OBJECT) );
 * @endcode
 */
#define hw_clear__nvi			, _hw_clrnvi
#define _hw_clrnvi(a,...)		_hw_nvic_clear(a) HW_EOL(__VA_ARGS__)


HW_INLINE void _hw_nvic_clear ( uint8_t v )
{
  if ( v < 32 )
    _hw_write_m(nvic, icpr0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hw_write_m(nvic, icpr1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hw_write_m(nvic, icpr2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(HW_EM_X([nvica2.h:_hw_nvic_clear()]interrupt not supported));
}


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__nvica(o,a)			\
  _hwa_setup_r( o, iser0 );			\
  _hwa_setup_r( o, iser1 );			\
  _hwa_setup_r( o, iser2 );			\
  _hwa_setup_r( o, icer0 );			\
  _hwa_setup_r( o, icer1 );			\
  _hwa_setup_r( o, icer2 );			\

#define _hwa_init__nvica(o,a)			\
  _hwa_init_r( o, iser0, 0x00000000 );		\
  _hwa_init_r( o, iser1, 0x00000000 );		\
  _hwa_init_r( o, iser2, 0x00000000 );		\
  _hwa_init_r( o, icer0, 0x00000000 );		\
  _hwa_init_r( o, icer1, 0x00000000 );		\
  _hwa_init_r( o, icer2, 0x00000000 );		\

#define _hwa_commit__nvica(o,a)			\
  _hwa_commit_r( o, iser0 );			\
  _hwa_commit_r( o, iser1 );			\
  _hwa_commit_r( o, iser2 );			\
  _hwa_commit_r( o, icer0 );			\
  _hwa_commit_r( o, icer1 );			\
  _hwa_commit_r( o, icer2 )
