
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief SysTick timer
 */

#define hw_class__stka

/**
 * @addtogroup stm32_stka
 * @section stm32_stkaif Interface
 *
 * * Configuration
 *
 * @code
 * hw|hwa( configure,   systick,
 *
 *	 [ clock,	ahb		   // Clock source
 *	 	      | ahb/8 ],
 *
 *	 [ reload,	x, ]		   // Any value in 0..0xFFFFFF
 *
 *	 [ run,	        yes | no ] );
 * @endcode
 */
#define hw_configure__stka		, _hw_cfstka
#define hwa_configure__stka		, _hwa_cfstka

#define _hw_cfstka(o,a,k,...)		do{ HW_B(_hwa_cfstka,k)(_hw,o,k,__VA_ARGS__) }while(0)
#define _hwa_cfstka(o,a,k,...)		do{ HW_B(_hwa_cfstka,k)(_hwa,o,k,__VA_ARGS__) }while(0)

/*  At least one keyword
 */
#define _hwa_cfstka1(h,o,k,...)		HW_E(HW_EM_AML((clock,reload,run)))
#define _hwa_cfstka0(h,o,k,...)		HW_BW(_hwa_cfstkack,clock,k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `clock`
 */
#define _hwa_cfstkack1(h,o,k,v,...)	HW_BV(_hwa_cfstkack2,cfstkack_,v,h,o,v)(h,o,__VA_ARGS__)//PUSH
#define _hwa_cfstkack20(v,...)		HW_E(HW_EM_XNIL(v,(ahb, ahb/8)))
#define _hwa_cfstkack21(r,h,o,v)			\
  if      ( 8*r == 1 ) h##_write(o,clksource,0);	\
  else if (   r == 1 ) h##_write(o,clksource,1);	\
  else HWA_E(HW_EM_VAL(v,clock,(ahb/8, ahb)));		\
  _hwa_cfstkack0 //POP

#define _hw_cfstkack_ahb		, 1

/*  Optionnal parameter `reload`
 */
#define _hwa_cfstkack0(h,o,k,...)	HW_BW(_hwa_cfstkald,reload,k)(h,o,k,__VA_ARGS__)
#define _hwa_cfstkald1(h,o,ok,v,k,...)		\
  h##_write(o,reload,(uint32_t)(v));			\
  HW_BW(_hwa_cfstkarn,run,k)(h,o,k,__VA_ARGS__)

#define _hwa_cfstkald0(h,o,k,...)	HW_BW(_hwa_cfstkarn,run,k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `run`
 */
#define _hwa_cfstkarn0(h,o,...)		HW_EOL(__VA_ARGS__)
#define _hwa_cfstkarn1(h,o,k,v,...)	HW_BV(_hwa_cfstkarn1,state_,v,h,o)(__VA_ARGS__)//PUSH
#define _hwa_cfstkarn10(v,...)		HW_E(HW_EM_ST(v))
#define _hwa_cfstkarn11(r,n,h,o)	h##_write(o,enable,r);  HW_EOL //POP


/**
 * @addtogroup stm32_stka
 *
 * * Run control
 *
 * @code
 * hw|hwa( turn, systick, on | off );
 * @endcode
 */
#define hw_turn__stka			, _hw_tnstka
#define _hw_tnstka(o,a,...)		do{ _hwx_tnstka(_hw,o,__VA_ARGS__) }while(0)

#define hwa_turn__stka			, _hwa_tnstka
#define _hwa_tnstka(o,a,...)		do{ _hwx_tnstka(_hwa,o,__VA_ARGS__) }while(0)

#define _hwx_tnstka(h,o,v,...)		HW_BV(_hwx_tnstka_,state_,v,h,o)(__VA_ARGS__)//PUSH
#define _hwx_tnstka_0(v,...)		HW_E(HW_EM_ST(v))
#define _hwx_tnstka_1(r,n,h,o)		h##_write(o,enable,r); HW_EOL//POP


/**
 * @addtogroup stm32_stka
 *
 * * Count value
 *
 * @code
 * uint32_t v = hw( read, systick );	   // Returns the current value of the timer
 * @endcode
 */
#define hw_read__stka			, _hw_rdstka
#define _hw_rdstka(o,a,...)		_hw_read(o,current)


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__stka(o,a)			\
  _hwa_setup_r( o, ctrl );			\
  _hwa_setup_r( o, load );			\
  _hwa_setup_r( o, val	)

#define _hwa_init__stka(o,a)			\
  _hwa_init_r( o, ctrl, 0x00000000 );		\
  _hwa_init_r( o, load, 0x00000000 );		\
  _hwa_init_r( o, val,	0x00000000 )

#define _hwa_commit__stka(o,a)		\
  _hwa_commit_r( o, ctrl );			\
  _hwa_commit_r( o, load );			\
  _hwa_commit_r( o, val	 )
