
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Class _nvica
 */

/**
 * @page stm32_nvica
 *
 * __Actions__
 *
 * `enable`: enable an IRQ at the NVIC level
 *
 * @code
 * hw( enable, nvic, irq(counter2) );
 * @endcode
 *
 * @code
 * hwa( enable, nvic, irq(counter2) );
 * @endcode
 */
#define hw_enable__nvica		, _hw_nvicaen
#define hwa_enable__nvica		, _hwa_nvicaen

#define _hw_nvicaen(o,a,x,...)		_hwx_nvicaed01(_hw_nvic_en,HW_X(x))
#define _hwa_nvicaen(o,a,x,...)		_hwx_nvicaed01(_hwa_nvic_en,HW_X(x))

#define _hwx_nvicaed01(...)		_hwx_nvicaed02(__VA_ARGS__)
#define _hwx_nvicaed02(h,c,...)		HW_KW(_hwx_nvicaed02,_irq,c)(h,c,__VA_ARGS__)
#define _hwx_nvicaed021(h,c,x,p,n,...)	h##able(n)
#define _hwx_nvicaen020(h,f,c,...)	HW_Y0(_hwx_nvicerr,c)(c,__VA_ARGS__)
#define _hwx_nvicerr1(z,x,e,...)	HW_E(e) hw_donothing()
#define _hwx_nvicerr00(c,o,...)		HW_E(argument of type _irq required)


/**
 * @page stm32_nvica
 *
 * __Actions__
 *
 * `disable`: enable an IRQ at the NVIC level
 *
 * @code
 * hw( disable, nvic, irq(counter2) );
 * @endcode
 *
 * @code
 * hwa( disable, nvic, irq(counter2) );
 * @endcode
 */
#define hw_disable__nvica		, _hw_nvicads
#define hwa_disable__nvica		, _hwa_nvicads

#define _hw_nvicads(o,a,x,...)		_hwx_nvicaed01(_hw_nvic_dis,HW_X(x))
#define _hwa_nvicads(o,a,x,...)		_hwx_nvicaed01(_hwa_nvic_dis,HW_X(x))


/**
 * @page stm32_nvica
 *
 * __Actions__
 *
 * `turn`: turn an IRQ on/off at the NVIC level
 * @code
 * hw | hwa ( turn, nvic, irq(counter2),   on
 *					 | off );
 * @endcode
 *
 * <br>
 */

#define hw_turn__nvica			, _hw_nvictn
#define _hw_nvictn(...)			do{ _hwx_nvictn(_hw,__VA_ARGS__,,); }while(0)

#define hwa_turn__nvica			, _hwa_nvictn
#define _hwa_nvictn(...)		do{ _hwx_nvictn(_hwa,__VA_ARGS__,,); }while(0)

#define _hwx_nvictn(h,o,a,x,...)	_hwx_nvictn01(h,HW_X(x),__VA_ARGS__)
#define _hwx_nvictn01(...)		_hwx_nvictn02(__VA_ARGS__)
#define _hwx_nvictn02(h,c,...)		HW_Y0(_hwx_nvictn02_,c)(h,c,__VA_ARGS__)
#define _hwx_nvictn02_0(h,c,n,o,v,m,f,s,...)	HW_Y0(_hwx_nvictn03_,_hw_state_##s)(h,o,v,s,__VA_ARGS__)
#define _hwx_nvictn03_0(h,o,v,s, ...)	HW_E_ST(s)
#define _hwx_nvictn03_1(h,o,v,s, ...)	HW_G2(_hwx_nvictn,HW_A1(_hw_state_##s))(h,o,v) HW_EOL(__VA_ARGS__)

#define _hwx_nvictn_1(h,o,v)		h##_nvic_enable(v)
#define _hwx_nvictn_0(h,o,v)		h##_nvic_disable(v)


/**
 * @page stm32_nvica
 * `turn`: enables/disables interrupts.
 *
 * @code
 * hw | hwa ( turn, (counter2,nvic), on | off );
 * @endcode
 */
#define hw_class__nvirq

#define hw_turn__nvirq			, _hw_tnnvirq
#define _hw_tnnvirq(...)		do{ _hwx_tnnvirq(_hw,__VA_ARGS__); }while(0)

#define hwa_turn__nvirq			, _hwa_tnnvirq
#define _hwa_tnnvirq(...)		do{ _hwx_tnnvirq(_hwa,__VA_ARGS__); }while(0)

#define _hwx_tnnvirq(h,o,v,s,...)	HW_Y0(_hwx_nvictn03_,_hw_state_##s)(h,o,v,s,__VA_ARGS__)


HW_INLINE void _hw_nvic_enable ( uint8_t v )
{
  if ( v < 32 )
    _hw_write_m(nvic, iser0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hw_write_m(nvic, iser1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hw_write_m(nvic, iser2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(interrupt not supported);
}

#define _hwa_nvic_enable(v)		__hwa_nvic_enable(hwa,v)

HW_INLINE void __hwa_nvic_enable ( hwa_t *hwa, uint8_t v )
{
  if ( v < 32 )
    _hwa_write_m(nvic, iser0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hwa_write_m(nvic, iser1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hwa_write_m(nvic, iser2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(interrupt not supported);
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
    HWA_E(interrupt not supported);
}

#define _hwa_nvic_disable(v)		__hwa_nvic_disable(hwa,v)

HW_INLINE void __hwa_nvic_disable ( hwa_t *hwa, uint8_t v )
{
  if ( v < 32 )
    _hwa_write_m(nvic, icer0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hwa_write_m(nvic, icer1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hwa_write_m(nvic, icer2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(interrupt not supported);
}


/**
 * @page stm32_nvica
 * `clear`: clears pending interrupts.
 *
 * @code
 * hw( clear, (nvic,counter2) );
 * @endcode
 */
#define hw_clear__nvirq			, _hw_clrnvirq
#define _hw_clrnvirq(o,v,...)		_hw_nvic_clear(v) HW_EOL(__VA_ARGS__)


HW_INLINE void _hw_nvic_clear ( uint8_t v )
{
  if ( v < 32 )
    _hw_write_m(nvic, icpr0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hw_write_m(nvic, icpr1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hw_write_m(nvic, icpr2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(interrupt not supported);
}



/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__nvica(o,a)		\
  _hwa_setup_r( o, iser0 );			\
  _hwa_setup_r( o, iser1 );			\
  _hwa_setup_r( o, iser2 );			\
  _hwa_setup_r( o, icer0 );			\
  _hwa_setup_r( o, icer1 );			\
  _hwa_setup_r( o, icer2 );			\

#define _hwa_init__nvica(o,a)			\
  _hwa_init_r( o, iser0, 0x00000000 );	\
  _hwa_init_r( o, iser1, 0x00000000 );	\
  _hwa_init_r( o, iser2, 0x00000000 );	\
  _hwa_init_r( o, icer0, 0x00000000 );	\
  _hwa_init_r( o, icer1, 0x00000000 );	\
  _hwa_init_r( o, icer2, 0x00000000 );	\

#define _hwa_commit__nvica(o,a)		\
  _hwa_commit_r( o, iser0 );			\
  _hwa_commit_r( o, iser1 );			\
  _hwa_commit_r( o, iser2 );			\
  _hwa_commit_r( o, icer0 );			\
  _hwa_commit_r( o, icer1 );			\
  _hwa_commit_r( o, icer2 )
