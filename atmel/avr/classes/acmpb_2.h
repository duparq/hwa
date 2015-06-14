
/*
 * This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

HW_INLINE void _hwa_begin_p__acmpb ( hwa_acmpb_t *p, intptr_t a )
{
  _hwa_begin_reg_p( p, a, _acmpb, csr  );
  _hwa_begin_reg_p( p, a, _acmpb, did  );
}

HW_INLINE void _hwa_init_p__acmpb ( hwa_acmpb_t *p )
{
  _hwa_set__r8(  &p->csr,  0x00 );
  _hwa_set__r8(  &p->did,  0x00 );
}

HW_INLINE void _hwa_commit_p__acmpb ( hwa_t *hwa, hwa_acmpb_t *p )
{
  _hwa_commit_reg_p( p, _acmpb, csr );
  _hwa_commit_reg_p( p, _acmpb, did );
}

#define _hw_is_edge_edge			, 1
#define _hw_acmpb_edge_falling			, 2	/* ACIS */
#define _hw_acmpb_edge_rising			, 3
#define _hw_acmpb_edge_both			, 0

#define _hw_is_positive_input_positive_input	, 1
#define _hw_is_bandgap_bandgap			, 1
#define _hw_is_hw_admux0_hw_admux0		, 1

/**
 * @page atmelavr_acmpb
 * @section atmelavr_acmpb_config Configuring the analog comparator
 *
 * Note: when the analog comparator shares the analog multiplexer output with
 * the ADC, the ADC must be turned off for the analog comparator to be able to
 * use the analog multiplexer output.
 *
 * @code
 * hwa_config( ACMP,
 * 
 *            [edge,             falling
 *                             | rising
 *                             | both,]
 *
 *            [positive_input,   hw_pin_ain0
 *                             | bandgap,]
 *
 *            [negative_input,   hw_pin_ain1
 *                             | hw_admux0]
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__acmpb		, _hwa_cfacmpb

#define _hwa_cfacmpb(o,i,a,...)						\
  do {									\
    HW_G2(_hwa_cfacmpb_kedge, HW_IS(edge,__VA_ARGS__))(o,__VA_ARGS__);	\
  } while(0)

#define _hwa_cfacmpb_kedge_1(o,k,...)					\
  HW_G2(_hwa_cfacmpb_vedge, HW_IS(,_hw_acmpb_edge_##__VA_ARGS__))(o,__VA_ARGS__)

#define _hwa_cfacmpb_vedge_0(o,...)					\
  HW_ERR("`edge` can be `falling`, `rising`, or `both`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfacmpb_vedge_1(o,v,...)			\
  _hwa_write_reg(o,acis, HW_A1(_hw_acmpb_edge_##v));	\
  _hwa_cfacmpb_kedge_0(o,__VA_ARGS__)

#define _hwa_cfacmpb_kedge_0(o,...)					\
  HW_G2(_hwa_cfacmpb_kposin, HW_IS(positive_input,__VA_ARGS__))(o,__VA_ARGS__)

#define _hwa_cfacmpb_kposin_1(o,k,...)					\
  HW_G2(_hwa_cfacmpb_kbandgap, HW_IS(bandgap,__VA_ARGS__))(o,__VA_ARGS__)

#define _hwa_cfacmpb_kbandgap_0(o,v,...)				\
  if ( hw_id(v) != hw_id(hw_pin_ain0) )					\
    HWA_ERR("`positive_input` can be `hw_pin_ain0` (or synonym), "	\
	    "or `bandgap` but not `" #v "`.");				\
  _hwa_write_reg(o,acbg,0);						\
  _hwa_cfacmpb_kposin_0(o,__VA_ARGS__)

#define _hwa_cfacmpb_kbandgap_1(o,v,...)		\
  _hwa_write_reg(o,acbg,1);				\
  _hwa_cfacmpb_kposin_0(o,__VA_ARGS__)

#define _hwa_cfacmpb_kposin_0(o,...)					\
  HW_G2(_hwa_cfacmpb_knegin, HW_IS(negative_input,__VA_ARGS__))(o,__VA_ARGS__)

#define _hwa_cfacmpb_knegin_1(o,k,...)					\
  HW_G2(_hwa_cfacmpb_kadmux, HW_IS(hw_admux0,__VA_ARGS__))(o,__VA_ARGS__)

#define _hwa_cfacmpb_kadmux_0(o,v,...)					\
  if ( hw_id(v) != hw_id(hw_pin_ain1) )					\
    HWA_ERR("`negative_input` can be `hw_pin_ain1` (or synonym), "	\
	    "or `hw_admux0` but not `" #v "`.");			\
  _hwa_write_reg(o,acme,0);						\
  HW_TX(,__VA_ARGS__)

#define _hwa_cfacmpb_kadmux_1(o,v,...)					\
  _hwa_write_reg(o,acme,1);						\
  _hwa_write_reg(o,aden,0);						\
  HW_TX(,__VA_ARGS__)


/**
 * @page atmelavr_acmpb
 * @section atmelavr_acmpb_pm Power management
 * @code
 * hw_turn( ACMP, on | off );
 * @endcode
 */
#define _hw_mthd_hw_turn__acmpb			, _hw_turnacmpb

#define _hw_turnacmpb(o,i,a,...)		\
  HW_G2(_hw_turnacmpb_vstate,HW_IS(,__hw_state_##__VA_ARGS__))

#define _hw_turnacmpb_vstate_1(o,i,a,v,...)	\
  HW_TX( _hw_write_reg(o,acd,(HW_A1(__hw_state_##v)==0)), __VA_ARGS__ )

#define _hw_turnacmpb_vstate_0(o,i,a,v,...)	\
  HW_ERR("object `" #o "` of class `_acmpb` can be turned `on` or `off`, but not `" #v "`.")


/**
 * @page atmelavr_acmpb
 * <br>
 */
