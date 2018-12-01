
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
 *      //  Clock source
 *      //
 *    [ clock,       apb                    // APB clock
 *                 | apb /   1              // APB clock
 *                         | 16             // APB clock divided by 16
 *                         | 256, ]         // APB clock divided by 256
 *
 *      //  Counting mode
 *      //
 *    [ direction,   stop                   // Stop
 *                 | down                   // Count down to 0 and stop
 *                 | down_loop, ]           // Count down to 0 and reload
 *
 *      //  Class _tm23a timers all count from top down to 0
 *      //
 *    [ bottom,      0, ]
 *
 *      //  The value the counter loads after 0 is reached
 *      //
 *    [ top,         VALUE, ]               // VALUE: 0 .. 0x7FFFFF
 *
 *      //  Action triggered after 0 is reached
 *      //
 *    [ action,      none
 *                 | irq
 *                 | nmi  ] );
 * @endcode
 */
#define hw_configure__tm23a	, _hw_cftm23a
#define hwa_configure__tm23a	, _hwa_cftm23a

#define _hw_cftm23a(o,i,a,k,...)					\
  do{									\
    typedef struct {							\
      uint8_t commit ;							\
      hwa_shared_t hw_shared ;						\
      hwa_tm23a_t o ;							\
    } hwa_t ;								\
    hwa_t hwa_st ; hwa_t *hwa= &hwa_st ;				\
    _hwa_setup_o( shared );						\
    _hwa_setup_o( o );							\
    HW_Y(_hwa_cftm23a_kclock_,_hw_is_clock_##k)(o,k,__VA_ARGS__,,);	\
    hwa->commit = 1; _hwa_commit_o( o ); _hwa_commit_o( shared );	\
  }while(0)

#define _hwa_cftm23a(o,i,a,k,...)	HW_Y(_hwa_cftm23a_kclock_,_hw_is_clock_##k)(o,k,__VA_ARGS__,,)


/*  Key `clock`
 */
#define _hwa_cftm23a_kclock_0(o,k,...)		HW_Y(_hwa_cftm23a_kdirection_,_hw_is_direction_##k)(o,k,__VA_ARGS__)
#define _hwa_cftm23a_kclock_1(o,k,v,...)	HW_Y(_hwa_cftm23a_vclock_,_hw_tm23a_clock_##v)(o,v,__VA_ARGS__)
#define _hwa_cftm23a_vclock_1(o,v,...)		_hwa_cftm23a_vclock_2(o,v,_hw_tm23a_clock_##v,__VA_ARGS__)
#define _hwa_cftm23a_vclock_2(...)		_hwa_cftm23a_vclock_3(__VA_ARGS__)
#define _hwa_cftm23a_vclock_3(o,v,z,x,k,...)				\
  if      (     x == 1 ) _hwa_write(o,psc,0);			\
  else if (  16*x == 1 ) _hwa_write(o,psc,1);			\
  else if ( 256*x == 1 ) _hwa_write(o,psc,2);			\
  else HWA_E_NIL(v,(apb, apb/16, apb/256));				\
  HW_Y(_hwa_cftm23a_kdirection_,_hw_is_direction_##k)(o,k,__VA_ARGS__)

#define _hwa_cftm23a_vclock_0(o,v,...)		HW_E_AVL(clock, v, apb_div(1 | 16 | 256))

#define _hw_tm23a_clock_apb		, 1

/*  Key `direction`
 */
#define _hwa_cftm23a_kdirection_1(o,k,v,...)				\
  HW_Y(_hwa_cftm23a_vdirection_,_hw_tm23a_direction_##v)(o,v,__VA_ARGS__)

#define _hwa_cftm23a_vdirection_1(o,v,k,...)			\
  _hwa_write(o,en,HW_A1(_hw_tm23a_direction_##v));		\
  _hwa_write(o,arl,HW_A2(_hw_tm23a_direction_##v));		\
  HW_Y(_hwa_cftm23a_kbottom_,_hw_is_bottom_##k)(o,k,__VA_ARGS__)

#define _hwa_cftm23a_vdirection_0(o,v,...)	HW_E_AVL(direction, v, down | down_loop | stop)

#define _hwa_cftm23a_kdirection_0(o,k,...)			\
  HW_Y(_hwa_cftm23a_kbottom_,_hw_is_bottom_##k)(o,k,__VA_ARGS__)

#define _hw_tm23a_direction_stop	, 0, 0	/* en, arl */
#define _hw_tm23a_direction_down	, 1, 0
#define _hw_tm23a_direction_down_loop	, 1, 1

/*  Key `bottom`
 */
#define _hwa_cftm23a_kbottom_1(o,k,v,...)	HW_G2(_hwa_cftm23a_vbottom,HW_IS(0,v))(o,v,__VA_ARGS__)
#define _hwa_cftm23a_vbottom_0(o,v,...)		HW_E_AVL(bottom, v, 0)
#define _hwa_cftm23a_vbottom_1(o,v,k,...)	HW_Y(_hwa_cftm23a_ktop_,_hw_is_top_##k)(o,k,__VA_ARGS__)
#define _hwa_cftm23a_kbottom_0(o,k,...)		HW_Y(_hwa_cftm23a_ktop_,_hw_is_top_##k)(o,k,__VA_ARGS__)

/*  Key `top`
 */
#define _hwa_cftm23a_ktop_1(o,k,v,kk,...)				\
  _hwa_write(o,load,(uint32_t)(v));					\
  HW_Y(_hwa_cftm23a_kaction_,_hw_is_action_##kk)(o,kk,__VA_ARGS__)

#define _hwa_cftm23a_ktop_0(o,k,...)					\
  HW_Y(_hwa_cftm23a_kaction_,_hw_is_action_##k)(o,k,__VA_ARGS__)

#if 0
/*	Optionnal parameter `irq_type`
 */
#define _hwa_cftm23a_kirqtype_1(o,k,v,...)				\
  HW_Y(_hwa_cftm23a_virqtype_,_hw_tm23a_irqtype_##v)(o,v,__VA_ARGS__)

#define _hwa_cftm23a_virqtype_1(o,v,...)			\
  _hwa_write(o,ie, HW_A1(_hw_tm23a_irqtype_##v));		\
  _hwa_write(o,irqtype,HW_A2(_hw_tm23a_irqtype_##v));	\
  HW_EOL(__VA_ARGS__)

#define _hwa_cftm23a_virqtype_0(o,v,...)	HW_E_AVL(irq_type, v, edge | level)

#define _hwa_cftm23a_kirqtype_0(o,...)		\
  HW_EOL(__VA_ARGS__)

#define _hw_tm23a_irqtype_edge		, 1, 0 /* enable, type */
#define _hw_tm23a_irqtype_level		, 1, 1
#define _hw_tm23a_irqtype_none		, 0, 0
#endif


/*  Key `action`
 */
#define _hwa_cftm23a_kaction_1(o,k,v,...)				\
  HW_Y(_hwa_cftm23a_vaction_,_hw_tm23a_action_##v)(o,v,__VA_ARGS__)

#define _hwa_cftm23a_vaction_1(o,v,...)					\
  _hwa_write(o,irqtype,0);						\
  if ( HW_A1(_hw_tm23a_action_##v) == HW_A1(_hw_tm23a_action_none ) ) {	\
    _hwa_write(o,ie,0);						\
    ets_isr_mask(1<<HW_A2(hw_irq_##o##_irq));				\
  }									\
  else {								\
    _hwa_write(o,ie,1);						\
    if ( HW_A1(_hw_tm23a_action_##v) == HW_A1(_hw_tm23a_action_irq ) )	\
      ets_isr_unmask(1<<HW_A2(hw_irq_##o##_irq));			\
    else								\
      ets_isr_mask(1<<HW_A2(hw_irq_##o##_irq));			\
  }									\
  HW_EOL(__VA_ARGS__)

#define _hwa_cftm23a_vaction_0(o,v,...)		HW_E_AVL(action, v, none | irq | nmi)

#define _hwa_cftm23a_kaction_0(o,...)		\
  HW_EOL(__VA_ARGS__)

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
#define hw_read__tm23a		, _hw_rdtm23a
#define _hw_rdtm23a(o,i,a,...)		_hw_read(o,_count) HW_EOL(__VA_ARGS__)


/**
 * @page espressif_tm23a
 *
 * The `hw_write()` instruction sets the content of the counting register:
 *
 * @code
 * hw_write( timer0, VALUE );
 * @endcode
 */
#define hw_write__tm23a	, _hw_wrtm23a
#define _hw_wrtm23a(o,i,a,v,...)	_hw_write(o,_count,v) HW_EOL(__VA_ARGS__)


/*******************************************************************************
 *									       *
 *	HWA Context							       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__tm23a(o,i,a)		\
  _hwa_setup_r( o, _load );			\
  _hwa_setup_r( o, _ctrl );			\

//  hwa->o.config.action = 0xFF

#define _hwa_init__tm23a(o,i,a)			\
    _hwa_init_r( o, _load, 0 );		\
    _hwa_init_r( o, _ctrl, 0 )

#define _hwa_commit__tm23a(o,i,a)					\
    _hwa_commit_r( o, _load );					\
    _hwa_commit_r( o, _ctrl );					\

    /* if ( hwa->o.config.action != 0xFF					\ */
    /*	 && hwa->o.config.action != HW_A1(_hw_tm23a_action_none ) ) {	\ */
    /*	 _hwa_write(o,ie,1);						\ */
    /*	 /\* _hwa_commit_r( shared, _edgeie ); *\/				\ */
    /* }									\ */
    /* if ( hwa->o.config.action == HW_A1(_hw_tm23a_action_irq) )		\ */
    /*	 ets_isr_unmask(1<<HW_A1(hw_irq_##o##_irq))			\ */


    /* if ( hwa->o.config.action == HW_A1(_hw_tm23a_action_none) ) {	\ */
    /*	 _hwa_write(o,ie,0);						\ */
    /*	 _hwa_commit_r( shared, _edgeie );				\ */
    /* }									\ */


/**
 * @page espressif_tm23a
 * <br>
 */
