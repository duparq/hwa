
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
 * The NVIC is not used directly but through instructions acting on `HW_IRQ`
 * objects.
 *
 * __Actions__
 *
 * * `nvic_turn` is used to turn an IRQ on/off at the NVIC level
 * @code
 * hw | hwa ( nvic_turn, HW_IRQ(counter2),   on
 *                                         | off );
 * @endcode
 *
 * <br>
 */

#define _hw_mtd_hw_nvic_turn__irq		, _hw_nvictn
#define _hw_mtd_hwa_nvic_turn__irq		, _hwa_nvictn

#define _hw_nvictn(...)				do{ _hwx_nvictn(_hw,__VA_ARGS__,,); }while(0)
#define _hwa_nvictn(...)			do{ _hwx_nvictn(_hwa,__VA_ARGS__,,); }while(0)

#define _hwx_nvictn(h,o,v,e,f,...)		HW_Y(_hwx_nvictn_vstate,_hw_state_##__VA_ARGS__)(h,o,v,__VA_ARGS__)
#define _hwx_nvictn_vstate_0(h,o,v,x, ...)	HW_E_ST(x)
#define _hwx_nvictn_vstate_1(h,o,v,x, ...)	HW_TX(HW_G2(_hwx_nvictn_vstate1,HW_A1(_hw_state_##x))(h,o,v), __VA_ARGS__)

#define _hwx_nvictn_vstate1_1(h,o,v)		h##_nvic_enable(v)
#define _hwx_nvictn_vstate1_0(h,o,v)		h##_nvic_disable(v)

#define _hw_nvic_enable(v)			__hw_nvic_enable(v)

HW_INLINE void __hw_nvic_enable ( uint8_t v )
{
  if ( v < 32 )
    _hw_write_reg_m(nvic, iser0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hw_write_reg_m(nvic, iser1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hw_write_reg_m(nvic, iser2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(interrupt not supported);
}

#define _hwa_nvic_enable(v)			__hwa_nvic_enable(hwa,v)

HW_INLINE void __hwa_nvic_enable ( hwa_t *hwa, uint8_t v )
{
  if ( v < 32 )
    _hwa_write_reg_m(nvic, iser0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hwa_write_reg_m(nvic, iser1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hwa_write_reg_m(nvic, iser2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(interrupt not supported);
}

#define _hw_nvic_disable(v)			__hw_nvic_disable(v)

HW_INLINE void __hw_nvic_disable ( uint8_t v )
{
  if ( v < 32 )
    _hw_write_reg_m(nvic, icer0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hw_write_reg_m(nvic, icer1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hw_write_reg_m(nvic, icer2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(interrupt not supported);
}

#define _hwa_nvic_disable(v)			__hwa_nvic_disable(hwa,v)

HW_INLINE void __hwa_nvic_disable ( hwa_t *hwa, uint8_t v )
{
  if ( v < 32 )
    _hwa_write_reg_m(nvic, icer0, (1UL<<v), (1UL<<v));
  else if ( v < 64 )
    _hwa_write_reg_m(nvic, icer1, (1UL<<(v-32)), (1UL<<(v-32)));
  else if ( v < 96 )
    _hwa_write_reg_m(nvic, icer2, (1UL<<(v-64)), (1UL<<(v-64)));
  else
    HWA_E(interrupt not supported);
}



/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__nvica(o,i,a)		\
  _hwa_setup_reg( o, iser0 );			\
  _hwa_setup_reg( o, iser1 );			\
  _hwa_setup_reg( o, iser2 );			\
  _hwa_setup_reg( o, icer0 );			\
  _hwa_setup_reg( o, icer1 );			\
  _hwa_setup_reg( o, icer2 );			\

#define _hwa_init__nvica(o,i,a)			\
  _hwa_init_reg( o, iser0, 0x00000000 );	\
  _hwa_init_reg( o, iser1, 0x00000000 );	\
  _hwa_init_reg( o, iser2, 0x00000000 );	\
  _hwa_init_reg( o, icer0, 0x00000000 );	\
  _hwa_init_reg( o, icer1, 0x00000000 );	\
  _hwa_init_reg( o, icer2, 0x00000000 );	\

#define _hwa_commit__nvica(o,i,a)		\
  _hwa_commit_reg( o, iser0 );			\
  _hwa_commit_reg( o, iser1 );			\
  _hwa_commit_reg( o, iser2 );			\
  _hwa_commit_reg( o, icer0 );			\
  _hwa_commit_reg( o, icer1 );			\
  _hwa_commit_reg( o, icer2 )
