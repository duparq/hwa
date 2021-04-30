
/* This file is part of the HWA project.
 * Copyright (c) 2019 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Universal synchronous asynchronous receiver transmitter (USART)
 */

/**
 * @ingroup stm32_classes
 * @addtogroup stm32_sab
 *
 * @section stm32_sabif Interface
 *
 * * Configuration
 *
 * @code
 * hw|hwa( configure,	   USART,
 *
 *	 [ mode,	   uart, ]	// Default
 *	 
 *	 [ divider,	   x, ]		// Value of the clock divider
 *	 
 *	 [ clockhz,	   x,		// Source clock frequency
 *	   bps,		   y,		// Transfer rate in bits per second.
 *	  [tol,		   z,]]		// Tolerance for bps (0.01 is 1%)
 *
 *	 [ databits,	   8		// Default
 *                       | 9, ]
 *
 *	 [ parity,	   none		// Default
 *                       | even
 *                       | odd, ]
 *
 *	 [ stopbits,	   1		// Default
 *                         0.5
 *                         1.5
 *                       | 2, ]
 *
 *	 [ cts,		   on	
 *                       | off, ]	// Default
 *
 *	 [ rts,		   on	
 *                       | off, ]	// Default
 *
 *	 [ receiver,	   on	
 *                       | off, ]	// Default
 *
 *	 [ transmitter,	   on
 *                       | off ]	// Default
 *
 *	 [ run,	   	   yes
 *                       | no ] );	// Default
 * @endcode
 */
#define hw_class__sab

#define hw_configure__sab		, _hw_cfsab
#define _hw_cfsab(o,a,k,...)		HW_B(_hwa_cfsab,k)(_hw,o,k,__VA_ARGS__)

#define hwa_configure__sab		, _hwa_cfsab
#define _hwa_cfsab(o,a,k,...)		HW_B(_hwa_cfsab,k)(_hwa,o,k,__VA_ARGS__)

/*  At least one keyword
 */
#define _hwa_cfsab1(h,o,k,...)		HW_E(HW_EM_AML(([mode], [divider], [clockhz,bps,[tol]], \
							[databits], [parity], [stopbits], [cts], \
							[rts], [receiver], [transmitter])))
#define _hwa_cfsab0(h,o,k,...)		do{ HW_BW(_hwa_cfsabmd,mode,k)(h,o,k,__VA_ARGS__); }while(0)

/*	'mode'
 */
#define _hwa_cfsabmd0			_hwa_cfsabadv
#define _hwa_cfsabmd1(h,o,k,v,...)	HW_BV(_hwa_cfsabmd1,sabmd_,v,) (h,o,__VA_ARGS__)//PUSH
#define _hwa_cfsabmd10(v,...)		HW_E(HW_EM_XNIL(v,(uart))) 	HW_EAT//POP
#define _hwa_cfsabmd11(f,...)		f//POP

#define _hw_sabmd_uart			, _hwa_cfsabadv

/*	'divider'
 */
#define _hwa_cfsabadv(h,o,k,...)	HW_BW(_hwa_cfsabadv,divider,k)(h,o,k,__VA_ARGS__)
#define _hwa_cfsabadv0			_hwa_cfsaback
#define _hwa_cfsabadv1(h,o,k,v,...)	h##_write(o,brr,v); _hwa_cfsabadb(h,o,__VA_ARGS__)

/*	'clockhz'
 */
#define _hwa_cfsaback(h,o,k,...)	HW_BW(_hwa_cfsaback,clockhz,k)(h,o,k,__VA_ARGS__)
#define _hwa_cfsaback0			_hwa_cfsabadb
#define _hwa_cfsaback1(h,o,k0,v,k,...)				\
  uint32_t	clockhz	__attribute__((unused));		\
  uint32_t	bps	__attribute__((unused));		\
  float		tol	__attribute__((unused));		\
  clockhz=v; HW_BW(_hwa_cfsababr,bps,k)(h,o,k,__VA_ARGS__)

/*	'bps'
 */
#define _hwa_cfsababr0(h,o,k,...)	HW_E(HW_EM_XWW(k,clockhz,bps))
#define _hwa_cfsababr1(h,o,k0,v,k,...)	bps=v; HW_BW(_hwa_cfsabatl,tol,k)(h,o,k,__VA_ARGS__)

/*	'tol'
 */
#define _hwa_cfsabatl0			tol=0; _hwa_cfsabatl2
#define _hwa_cfsabatl1(h,o,k0,v,k,...)	tol=v; _hwa_cfsabatl2(h,o,k,__VA_ARGS__)
#define _hwa_cfsabatl2					\
  uint32_t brr = int(clockhz*1.0/bps * 16.0 + 0.5);	\
  tol=tol;						\
  _hwa_cfsabadb

/*	'databits'
 */
#define _hwa_cfsabadb(h,o,k,...)	HW_BW(_hwa_cfsabadb,databits,k)(h,o,k,__VA_ARGS__)
#define _hwa_cfsabadb0			_hwa_cfsabapy
#define _hwa_cfsabadb1(h,o,k,v,...)		\
  if      ( v==8 ) h##_write(o,m,0);		\
  else if ( v==9 ) h##_write(o,m,1);		\
  else HWA_E(HW_EM_VAL(v,databits,(8,9)));	\
  _hwa_cfsabapy(h,o,__VA_ARGS__)

/*	'parity'
 */
#define _hwa_cfsabapy(h,o,k,...)	HW_BW(_hwa_cfsabapy,parity,k)(h,o,k,__VA_ARGS__)
#define _hwa_cfsabapy0			_hwa_cfsabasb
#define _hwa_cfsabapy1(h,o,k,v,...)	HW_BV(_hwa_cfsabapy1,sabapy_,v,h,o)(h,o,__VA_ARGS__)//PUSH
#define _hwa_cfsabapy10(v,h,o)		HW_E(HW_EM_XNIL(v,(none, even, odd)))	HW_EAT//POP
#define _hwa_cfsabapy11(r,h,o)		h##_write(o,pceps,r);			_hwa_cfsabasb//POP

//					  PCE PS
#define _hw_sabapy_none			, 0
#define _hw_sabapy_even			, 1
#define _hw_sabapy_odd			, 3

/*	'stopbits'
 */
#define _hwa_cfsabasb(h,o,k,...)	HW_BW(_hwa_cfsabasb,stopbits,k)(h,o,k,__VA_ARGS__)
#define _hwa_cfsabasb0			_hwa_cfsabarx
#define _hwa_cfsabasb1(h,o,k,v,...)			\
  if      ( v==1.0 ) h##_write(o,stop,0);		\
  else if ( v==0.5 ) h##_write(o,stop,1);		\
  else if ( v==2.0 ) h##_write(o,stop,2);		\
  else if ( v==1.5 ) h##_write(o,stop,3);		\
  else HWA_E(HW_EM_VAL(v,stopbits,(0.5, 1, 1.5, 2)));	\
  _hwa_cfsabarx(h,o,__VA_ARGS__)

/*	'cts'
 */
#define _hwa_cfsabacs(h,o,k,...)	HW_BW(_hwa_cfsabacs,cts,k)(h,o,k,__VA_ARGS__)
#define _hwa_cfsabacs0			_hwa_cfsabarx
#define _hwa_cfsabacs1(h,o,k,v,...)	HW_BV(_hwa_cfsabacs1,state_,v,h,o)(h,o,__VA_ARGS__)
#define _hwa_cfsabacs10(v,h,o)		HW_E(HW_EM_ST(v))	HW_EAT
#define _hwa_cfsabacs11(r,n,h,o)	h##_write(o,ctse,r);	_hwa_cfsabars

/*	'rts'
 */
#define _hwa_cfsabars(h,o,k,...)	HW_BW(_hwa_cfsabars,rts,k)(h,o,k,__VA_ARGS__)
#define _hwa_cfsabars0			_hwa_cfsabarx
#define _hwa_cfsabars1(h,o,k,v,...)	HW_BV(_hwa_cfsabars1,state_,v,h,o)(h,o,__VA_ARGS__)
#define _hwa_cfsabars10(v,h,o)		HW_E(HW_EM_ST(v))	HW_EAT
#define _hwa_cfsabars11(r,n,h,o)	h##_write(o,rtse,r);	_hwa_cfsabarx

/*	'receiver'
 */
#define _hwa_cfsabarx(h,o,k,...)	HW_BW(_hwa_cfsabarx,receiver,k)(h,o,k,__VA_ARGS__)
#define _hwa_cfsabarx0			_hwa_cfsabatx
#define _hwa_cfsabarx1(h,o,k,v,...)	HW_BV(_hwa_cfsabarx1,state_,v,h,o)(h,o,__VA_ARGS__)
#define _hwa_cfsabarx10(v,h,o)		HW_E(HW_EM_ST(v))	HW_EAT
#define _hwa_cfsabarx11(r,n,h,o)	h##_write(o,re,r);	_hwa_cfsabatx

/*	'transmitter'
 */
#define _hwa_cfsabatx(h,o,k,...)	HW_BW(_hwa_cfsabatx,transmitter,k)(h,o,k,__VA_ARGS__)
#define _hwa_cfsabatx0			_hwa_cfsabarn
#define _hwa_cfsabatx1(h,o,k,v,...)	HW_BV(_hwa_cfsabatx1,state_,v,h,o)(h,o,__VA_ARGS__)
#define _hwa_cfsabatx10(v,h,o)		HW_E(HW_EM_ST(v))	HW_EAT
#define _hwa_cfsabatx11(r,n,h,o)	h##_write(o,te,r);	_hwa_cfsabarn

/*	'run'
 */
#define _hwa_cfsabarn(h,o,k,...)	HW_BW(_hwa_cfsabarn,run,k)(h,o,k,__VA_ARGS__)
#define _hwa_cfsabarn0(h,o,...)		HW_EOL(__VA_ARGS__)
#define _hwa_cfsabarn1(h,o,k,v,...)	HW_BV(_hwa_cfsabarn1,state_,v,h,o)(__VA_ARGS__)
#define _hwa_cfsabarn10(v,h,o)		HW_E(HW_EM_ST(v))	HW_EAT
#define _hwa_cfsabarn11(r,n,h,o)	h##_write(o,ue,r);	HW_EOL

  
/* #define _hw_is_bps_bps			, 1 */
#define _hw_is_tol_tol			, 1
#define _hw_is_clockhz_clockhz		, 1
#define _hw_is_divider_divider		, 1


/*******************************************************************************
 *									       *
 *	HWA context							       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__sab(o,a)			\
  _hwa_setup_r( o, brr );			\
  _hwa_setup_r( o, cr1 );			\
  _hwa_setup_r( o, cr2 );			\
  _hwa_setup_r( o, cr3 );			\
  _hwa_setup_r( o, gtpr )

#define _hwa_init__sab(o,a)			\
  _hwa_init_r( o, brr,	0x00000000 );		\
  _hwa_init_r( o, cr1,	0x00000000 );		\
  _hwa_init_r( o, cr2,	0x00000000 );		\
  _hwa_init_r( o, cr3,	0x00000000 );		\
  _hwa_init_r( o, gtpr, 0x00000000 )

#define _hwa_commit__sab(o,a)			\
  _hwa_commit_r( o, brr );			\
  _hwa_commit_r( o, cr1 );			\
  _hwa_commit_r( o, cr2 );			\
  _hwa_commit_r( o, cr3 );			\
  _hwa_commit_r( o, gtpr )
