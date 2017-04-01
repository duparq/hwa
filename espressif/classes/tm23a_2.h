
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief _tm23a
 */

/**
 * @page espressif_tm23a
 * @section espressif_tm23a_config Configuration
 *
 * @code
 * hwa( configure, timer0,
 *
 *	       //  Clock source
 *	       //
 *	     [ clock,	    apb			   // APB clock
 *			  | apb_div(  1		   // APB clock
 *				    | 2		   // APB clock divided by 2
 *				    | 4		   // APB clock divided by 4
 *				    | ...
 *				    | 256 ), ]	   // APB clock divided by 256
 *
 *	       //  Counting mode
 *	       //
 *	     [ countmode,   stop		   // Stop
 *			  | down		   // Count down to 0 and stop
 *			  | loop_down, ]	   // Count down to 0 and reload
 *
 *	       //  Class _tm23a timers all count from top down to 0
 *	       //
 *	     [ bottom,	    0, ]
 *
 *	       //  The value the counter loads after 0 is reached
 *	       //
 *	     [ top,	    VALUE, ]		   // VALUE: 0 .. 0x7FFFFF
 *
 *	       //  Action triggered after 0 is reached
 *	       //
 *	     [ action,	    none
 *			  | irq
 *			  | nmi	 ]
 *	     );
 * @endcode
 */
#define _hw_mthd_hw_config__tm23a	, _hw_cftm23a
#define _hw_mthd_hwa_config__tm23a	, _hwa_cftm23a

#define _hw_cftm23a(o,i,a,...)						\
  do{									\
    typedef struct {							\
      uint8_t commit ;							\
      hwa_shared_t hw_shared ;						\
      hwa_tm23a_t o ;							\
    } hwa_t ;								\
    hwa_t hwa_st ; hwa_t *hwa= &hwa_st ;				\
    _hwa_setup( shared );						\
    _hwa_setup( o );							\
    HW_X(_hwa_cftm23a_kclock,_hw_is_clock_##__VA_ARGS__)(o,__VA_ARGS__,,); \
    hwa->commit = 1; _hwa_commit( o ); _hwa_commit( shared );	\
  }while(0)

#define _hwa_cftm23a(o,i,a,...)						\
  HW_X(_hwa_cftm23a_kclock,_hw_is_clock_##__VA_ARGS__)(o,__VA_ARGS__,,) \


/*	Optionnal parameter `clock`
 */
#define _hwa_cftm23a_kclock_1(o,k,v,...)				\
  HW_X(_hwa_cftm23a_vclock,_hw_tm23a_clock_##v)(o,v,__VA_ARGS__)

#define _hwa_cftm23a_vclock_1(o,v,...)					\
  _hwa_write_reg(o,psc,HW_A1(_hw_tm23a_clock_##v));			\
  HW_X(_hwa_cftm23a_kcountmode,_hw_is_countmode_##__VA_ARGS__)(o,__VA_ARGS__)

#define _hwa_cftm23a_vclock_0(o,v,...)		HW_E_AVL(clock, v, apb_div(1 | 16 | 256))

#define _hwa_cftm23a_kclock_0(o,k,...)					\
  HW_X(_hwa_cftm23a_kcountmode,_hw_is_countmode_##k)(o,k,__VA_ARGS__)

#define _hw_is_clock_clock		, 1
#define _hw_tm23a_clock_apb		, 0
#define _hw_tm23a_clock_apb_div_1	, 0
#define _hw_tm23a_clock_apb_div_16	, 1
#define _hw_tm23a_clock_apb_div_256	, 2
#define _hw_tm23a_clock_apb_div(x)		HW_G2(_hw_tm23a_clock_apb_div,x)

/*	Optionnal parameter `countmode`
 */
#define _hwa_cftm23a_kcountmode_1(o,k,v,...)				\
  HW_X(_hwa_cftm23a_vcountmode,_hw_tm23a_countmode_##v)(o,v,__VA_ARGS__)

#define _hwa_cftm23a_vcountmode_1(o,v,k,...)			\
  _hwa_write_reg(o,en,HW_A1(_hw_tm23a_countmode_##v));		\
  _hwa_write_reg(o,arl,HW_A2(_hw_tm23a_countmode_##v));		\
  HW_X(_hwa_cftm23a_kbottom,_hw_is_bottom_##k)(o,k,__VA_ARGS__)

#define _hwa_cftm23a_vcountmode_0(o,v,...)	HW_E_AVL(countmode, v, down | loop_down | stop)

#define _hwa_cftm23a_kcountmode_0(o,k,...)			\
  HW_X(_hwa_cftm23a_kbottom,_hw_is_bottom_##k)(o,k,__VA_ARGS__)

#define _hw_is_countmode_countmode	, 1
#define _hw_tm23a_countmode_stop	, 0, 0	/* en, arl */
#define _hw_tm23a_countmode_down	, 1, 0
#define _hw_tm23a_countmode_loop_down	, 1, 1

/*	Optionnal parameter `bottom`
 */
#define _hwa_cftm23a_kbottom_1(o,k,v,...)			\
  HW_G2(_hwa_cftm23a_vbottom,HW_IS(0,v))(o,v,__VA_ARGS__)

#define _hwa_cftm23a_vbottom_0(o,v,...)		HW_E_AVL(bottom, v, 0)

#define _hwa_cftm23a_vbottom_1(o,v,k,...)			\
    HW_X(_hwa_cftm23a_ktop,_hw_is_top_##k)(o,k,__VA_ARGS__)

#define _hwa_cftm23a_kbottom_0(o,k,...)				\
    HW_X(_hwa_cftm23a_ktop,_hw_is_top_##k)(o,k,__VA_ARGS__)

#define _hw_is_bottom_bottom		, 1

/*	Optionnal parameter `top`
 */
#define _hwa_cftm23a_ktop_1(o,k,v,...)					\
    _hwa_write_reg(o,load,v);						\
    HW_X(_hwa_cftm23a_kaction,_hw_is_action_##__VA_ARGS__)(o,__VA_ARGS__)

#define _hwa_cftm23a_ktop_0(o,...)					\
  HW_X(_hwa_cftm23a_kaction,_hw_is_action_##__VA_ARGS__)(o,__VA_ARGS__)

#define _hw_is_top_top			, 1

#if 0
/*	Optionnal parameter `irq_type`
 */
#define _hwa_cftm23a_kirqtype_1(o,k,v,...)				\
  HW_X(_hwa_cftm23a_virqtype,_hw_tm23a_irqtype_##v)(o,v,__VA_ARGS__)

#define _hwa_cftm23a_virqtype_1(o,v,...)			\
  _hwa_write_reg(o,ie, HW_A1(_hw_tm23a_irqtype_##v));		\
  _hwa_write_reg(o,irqtype,HW_A2(_hw_tm23a_irqtype_##v));	\
  HW_EOL(__VA_ARGS__)

#define _hwa_cftm23a_virqtype_0(o,v,...)	HW_E_AVL(irq_type, v, edge | level)

#define _hwa_cftm23a_kirqtype_0(o,...)		\
  HW_EOL(__VA_ARGS__)

#define _hw_is_irq_type_irq_type	, 1
#define _hw_tm23a_irqtype_edge		, 1, 0 /* enable, type */
#define _hw_tm23a_irqtype_level		, 1, 1
#define _hw_tm23a_irqtype_none		, 0, 0
#endif


/*	Optionnal parameter `action`
 */
#define _hwa_cftm23a_kaction_1(o,k,v,...)				\
  HW_X(_hwa_cftm23a_vaction,_hw_tm23a_action_##v)(o,v,__VA_ARGS__)

#define _hwa_cftm23a_vaction_1(o,v,...)					\
  _hwa_write_reg(o,irqtype,0);						\
  if ( HW_A1(_hw_tm23a_action_##v) == HW_A1(_hw_tm23a_action_none ) ) {	\
    _hwa_write_reg(o,ie,0);						\
    ets_isr_mask(1<<HW_A1(_hw_irq_##o##_irq));				\
  }									\
  else {								\
    _hwa_write_reg(o,ie,1);						\
    if ( HW_A1(_hw_tm23a_action_##v) == HW_A1(_hw_tm23a_action_irq ) )	\
      ets_isr_unmask(1<<HW_A1(_hw_irq_##o##_irq));			\
    else								\
      ets_isr_mask(1<<HW_A1(_hw_irq_##o##_irq));			\
  }									\
  HW_EOL(__VA_ARGS__)

#define _hwa_cftm23a_vaction_0(o,v,...)		HW_E_AVL(action, v, none | irq | nmi)

#define _hwa_cftm23a_kaction_0(o,...)		\
  HW_EOL(__VA_ARGS__)

#define _hw_is_action_action		, 1
#define _hw_tm23a_action_none		, 0
#define _hw_tm23a_action_irq		, 1
#define _hw_tm23a_action_nmi		, 2

/**
 * @page espressif_tm23a
 * @section espressif_tm23a_data Count
 *
 * The `read` instruction returns the content of the counting register:
 *
 * @code
 * uint32_t count = hw( read, timer0 );
 * @endcode
 */
#define _hw_mthd_hw_read__tm23a		, _hw_rdtm23a
#define _hw_rdtm23a(o,i,a,...)		HW_TX(_hw_read_reg(o,_count),__VA_ARGS__)


/**
 * @page espressif_tm23a
 *
 * The `hw_write()` instruction sets the content of the counting register:
 *
 * @code
 * hw_write( timer0, VALUE );
 * @endcode
 */
#define _hw_mthd_hw_write__tm23a	, _hw_wrtm23a
#define _hw_wrtm23a(o,i,a,v,...)	HW_TX(_hw_write_reg(o,_count,v),__VA_ARGS__)


/*******************************************************************************
 *									       *
 *	HWA Context							       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__tm23a(o,i,a)		\
  _hwa_setup_reg( o, _load );			\
  _hwa_setup_reg( o, _ctrl );			\

//  hwa->o.config.action = 0xFF

#define _hwa_init__tm23a(o,i,a)			\
    _hwa_init_reg( o, _load, 0 );		\
    _hwa_init_reg( o, _ctrl, 0 )

#define _hwa_commit__tm23a(o,i,a)					\
    _hwa_commit_reg( o, _load );					\
    _hwa_commit_reg( o, _ctrl );					\

    /* if ( hwa->o.config.action != 0xFF					\ */
    /*	 && hwa->o.config.action != HW_A1(_hw_tm23a_action_none ) ) {	\ */
    /*	 _hwa_write_reg(o,ie,1);						\ */
    /*	 /\* _hwa_commit_reg( shared, _edgeie ); *\/				\ */
    /* }									\ */
    /* if ( hwa->o.config.action == HW_A1(_hw_tm23a_action_irq) )		\ */
    /*	 ets_isr_unmask(1<<HW_A1(_hw_irq_##o##_irq))			\ */


    /* if ( hwa->o.config.action == HW_A1(_hw_tm23a_action_none) ) {	\ */
    /*	 _hwa_write_reg(o,ie,0);						\ */
    /*	 _hwa_commit_reg( shared, _edgeie );				\ */
    /* }									\ */


/**
 * @page espressif_tm23a
 * <br>
 */
