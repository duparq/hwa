
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA 16-bits version 'a' Atmel AVR timer-counters (layer 2)
 *
 *	Used in: ATtinyX4 Timer 1
 */


/*	Initialize a c8a instance
 */
#define hwa_begin_c8a(n)			\
  HWA_INIT(hw_##n, ccra);			\
  HWA_INIT(hw_##n, ccrb);			\
  HWA_INIT(hw_##n, count);			\
  HWA_INIT(hw_##n, ocra);			\
  HWA_INIT(hw_##n, ocrb);			\
  HWA_INIT(hw_##n, imsk);			\
  HWA_INIT(hw_##n, ifr);			\
  hwa->n.clock = 0;				\
  hwa->n.countmode = 0;				\
  hwa->n.top = 0;				\
  hwa->n.update = 0;				\
  hwa->n.overflow = 0;				\
  hwa->n.ocra_mode = 0;				\
  hwa->n.ocrb_mode = 0;


HW_INLINE void _hwa_reset_c8a ( hwa_c8a_t *timer )
{
  _hwa_reset_r8( &timer->ccra );
  _hwa_reset_r8( &timer->ccrb );
  _hwa_reset_r8( &timer->count );
  _hwa_reset_r8( &timer->ocra );
  _hwa_reset_r8( &timer->ocrb );
  _hwa_reset_r8( &timer->imsk );
  _hwa_reset_r8( &timer->ifr );
}


/*	8-bit counter class 'c8a'
 */
#define hw_c8a_countmode_loop_up		, 1
#define hw_c8a_countmode_loop_updown		, 2

#define hw_c8a_top_fixed_0xFF			, 1
#define hw_c8a_top_register_compare_a		, 2

#define hw_c8a_clock_none			, 0
#define hw_c8a_clock_syshz			, 1
#define hw_c8a_clock_syshz_div_8		, 2
#define hw_c8a_clock_syshz_div_64		, 3
#define hw_c8a_clock_syshz_div_256		, 4
#define hw_c8a_clock_syshz_div_1024		, 5
#define hw_c8a_clock_ext_rising			, 6
#define hw_c8a_clock_ext_falling		, 7


/*	Configure counter
 */
#define hw_def_hwa_config_c8a		, _hwa_config_c8a

#define _hwa_config_c8a(c,n,i,a, ...)					\
  do { HW_G2(_hwa_config_c8a_xclock,HW_IS(clock,__VA_ARGS__))(n,__VA_ARGS__,) } while(0)

#define _hwa_config_c8a_xclock_0(n,...)					\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_c8a_xclock_1(n,_clock_,...)				\
  HW_G2(_hwa_config_c8a_vclock,HW_IS(,hw_c8a_clock_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c8a_vclock_0(n,...)					\
  HW_ERR( "`clock` can be `none`, `syshz`, `syshz_div_8`, "		\
	  "`syshz_div_64`, `syshz_div_256`, `syshz_div_1024`, "		\
	  "`ext_falling`, `ext_rising`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_c8a_vclock_1(n,zclock,...)				\
  hwa->n.clock = HW_A1(hw_c8a_clock_##zclock);				\
  HW_G2(_hwa_config_c8a_xmode,HW_IS(countmode,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c8a_xmode_0(n,...)					\
  HW_ERR("expected `countmode` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_c8a_xmode_1(n,_countmode_,...)			\
  HW_G2(_hwa_config_c8a_vmode,HW_IS(,hw_c8a_countmode_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c8a_vmode_0(n,...)					\
  HW_ERR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid mode option.")

#define _hwa_config_c8a_vmode_1(n,vmode,...)				\
  hwa->n.countmode = HW_A1(hw_c8a_countmode_##vmode);			\
  HW_G2(_hwa_config_c8a_xbottom,HW_IS(bottom,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c8a_xbottom_1(n,_bottom_,...)			\
  HW_G2(_hwa_config_c8a_vbottom,HW_IS(0,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c8a_vbottom_0(n,bottom,...)		\
  HW_ERR("bottom must be `0`, not `" #bottom "`.")

#define _hwa_config_c8a_vbottom_1(n,bottom,...)	\
  _hwa_config_c8a_xbottom_0(n,__VA_ARGS__)

#define _hwa_config_c8a_xbottom_0(n,...)				\
  HW_G2(_hwa_config_c8a_xtop,HW_IS(top,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c8a_xtop_0(n,...)				\
  HW_ERR("expected `top` instead of `" #__VA_ARGS__ "`.")

#define _hwa_config_c8a_xtop_1(n,_top_,...)				\
  HW_G2(_hwa_config_c8a_vtop,HW_IS(,hw_c8a_top_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c8a_vtop_0(n,...)					\
  HW_ERR("`top` can be `fixed_0xFF` or `register_compare_a`,"		\
	 " but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_c8a_vtop_1(n,ztop,...)				\
  hwa->n.top = HW_A1(hw_c8a_top_##ztop);				\
  HW_G2(_hwa_config_c8a_xuc,HW_IS(update,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c8a_xuc_1(n,uc,...)					\
  HW_G2(_hwa_config_c8a_vuc, HW_IS(,hw_counter_update_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c8a_vuc_0(n,vuc,...)				\
    HW_ERR("`update` must be `at_bottom`, `at_top, or `at_max`, but `not `" #vuc "`.")

#define _hwa_config_c8a_vuc_1(n,vuc,...)		\
  hwa->n.update = HW_A1(hw_counter_update_##vuc);	\
  _hwa_config_c8a_xuc_0(n,__VA_ARGS__);

#define _hwa_config_c8a_xuc_0(n,...)					\
  HW_G2(_hwa_config_c8a_xoverflow,HW_IS(overflow,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c8a_xoverflow_1(n,overflow,...)			\
  HW_G2(_hwa_config_c8a_voverflow, HW_IS(,hw_counter_overflow_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c8a_voverflow_0(n,overflow,...)		\
  HW_ERR("optionnal parameter `overflow` must be `at_bottom`, "	\
	 "`at_top, or `at_max`, but `not `" #overflow "`.")

#define _hwa_config_c8a_voverflow_1(n,voverflow,...)		\
  hwa->n.overflow = HW_A1(hw_counter_overflow_##voverflow);	\
  HW_EOP(__VA_ARGS__)
//  _hwa_config_c8a_xoverflow_0(n,__VA_ARGS__)

#define _hwa_config_c8a_xoverflow_0(n,...)			\
  HW_EOP(__VA_ARGS__)

/* #define _hwa_config_c8a_xoverflow_0(n,...)			\ */
/*   HW_G2(_hwa_config_c8a,HW_IS(,__VA_ARGS__))(n,__VA_ARGS__) */

/* #define _hwa_config_c8a_0(n,...)				\ */
/*   HW_ERR( "too many arguments: `" HW_QUOTE(__VA_ARGS__) "`.") */

/* #define _hwa_config_c8a_1(...) */


/*	Solve the configuration of the counter and its compare and capture units
 */
HW_INLINE void hwa_solve_c8a ( hwa_c8a_t *p )
{
  uint8_t wgm = 0xFF ;

  /* Mode WGM  Operation  COUNTMODE    TOP   UPD  OVF  OCA                    OCB
   *                                            
   *  0   000  Normal     LOOP_UP      0xFF  IMM  MAX  DIS,ToM,CoM,SoM        DIS,ToM,CoM,SoM
   *  2   010  CTC        LOOP_UP      OCRA  IMM  MAX  DIS,ToM,CoM,SoM        DIS,ToM,CoM,SoM
   *
   *  3   011  Fast PWM   LOOP_UP      0xFF  BOT  MAX  DIS,SaBCoM,CaBSoM      DIS,SaBCoM,CaBSoM
   *  7   111  Fast PWM   LOOP_UP      OCRA  BOT  TOP  DIS,ToM,CoMSaB,SoMCaB  DIS,SaBCoM,CaBSoM
   *
   *  1   001  PWM, PhC   LOOP_UPDOWN  0xFF  TOP  BOT  DIS,CmuSmd,SmuCmd      DIS,CmuSmd,SmuCmd   
   *  5   101  PWM, PhC   LOOP_UPDOWN  OCRA  TOP  BOT  DIS,ToM,CmuSmd,SmuCmd  DIS,CmuSmd,SmuCmd
   *
   *  4   100  *Reserved*
   *  6   110  *Reserved*
   */

  if ( p->clock ) {	/* if the mandatory parameter 'clock' is not 0, the
			   counter is configured */
    /*	Clock selection
     */
    _hwa_write_p(p, _hw_cbits(c8a, cs), p->clock);

    /*	Determine WGM
     */
    if ( p->countmode == HW_A1(hw_c8a_countmode_loop_up) ) {
      if (p->top == HW_A1(hw_c8a_top_fixed_0xFF)) {
	if (p->update == HW_A1(hw_counter_update_immediately)
	    || p->overflow == HW_A1(hw_counter_overflow_at_bottom)
	    || p->ocra_mode == HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match)
	    || p->ocra_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	    || p->ocrb_mode == HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match)
	    || p->ocrb_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match))
	  wgm = 3 ;
	else 
	  wgm = 0 ;
      }
      else /* p->top == HW_A1(hw_c8a_top_register_capture) */ {
	if (p->update == HW_A1(hw_counter_update_at_top)
	    || p->overflow == HW_A1(hw_counter_overflow_at_top)
	    || p->ocra_mode == HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match)
	    || p->ocra_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	    || p->ocrb_mode == HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match)
	    || p->ocrb_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match))
	  wgm = 7 ;
	else 
	  wgm = 2 ;
      }
    }
    else /* p->countmode == HW_A1(hw_c8a_countmode_loop_updown) */ {
      if (p->top == HW_A1(hw_c8a_top_register_compare_a) )
	wgm = 5 ;
      else 
	wgm = 1 ;
    }
      
    if (wgm == 0xFF) {
      HWA_ERR("WGM value could not be solved for c8a class counter.");
      return ;
    }

    _hwa_write_p(p, _hw_cbits(c8a,wgm), wgm);
  }

  /*	Solve the configuration of compare output A
   */
  if ( p->ocra_mode ) {

    uint8_t	mode = 0xFF ;

    if ( p->ocra_mode == HW_A1(hw_ocu_mode_disconnected) )
      mode = 0 ;
    else if ( p->ocra_mode == HW_A1(hw_ocu_mode_toggle_on_match) )
      mode = 1 ;
    else if ( p->ocra_mode == HW_A1(hw_ocu_mode_clear_on_match)
	      || p->ocra_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	      || p->ocra_mode == HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    /*  Write the hardware configuration bits
     */
    _hwa_write_p(p, _hw_cbits(c8a, coma), mode );
  }

  /*	Solve the configuration of compare output B
   */
  if ( p->ocrb_mode ) {

    uint8_t	mode = 0xFF ;

    if ( p->ocrb_mode == HW_A1(hw_ocu_mode_disconnected) )
      mode = 0 ;
    else if ( p->ocrb_mode == HW_A1(hw_ocu_mode_toggle_on_match) )
      mode = 1 ;
    else if ( p->ocrb_mode == HW_A1(hw_ocu_mode_clear_on_match)
	      || p->ocrb_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	      || p->ocrb_mode == HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    /*  Write the hardware configuration bits
     */
    _hwa_write_p(p, _hw_cbits(c8a, comb), mode );
  }


  /*	Check the validity of the configuration
   */
  if ( p->clock || p->ocra_mode || p->ocrb_mode ) {

    if ( p->clock == 0 ) {
      HWA_ERR("configuration of counter is required.");
      return ;
    }

    /*	Compare output A
     */
    if ( p->ocra_mode != 0 ) {
      if ( wgm==0 || wgm==2 ) {
	if ( p->ocra_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_toggle_on_match)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_clear_on_match)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_set_on_match))
	  HWA_ERR("compare output A of class c8a counter mode must be "
		  "'disconnected', 'toggle_on_match', 'clear_on_match', or "
		  "'set_on_match'.");
      }
      else if ( wgm==3 ) {
	if ( p->ocra_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class c8a counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==7 ) {
	if ( p->ocra_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_toggle_on_match)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class c8a counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 ) {
	if ( p->ocra_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class c8a counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
      else if ( wgm==5 ) {
	if ( p->ocra_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_toggle_on_match)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	     && p->ocra_mode != HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class c8a counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
    }

    /*	Compare output B
     */
    if ( p->ocrb_mode != 0 ) {
      if ( wgm==0 || wgm==2 ) {
	if ( p->ocrb_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->ocrb_mode != HW_A1(hw_ocu_mode_toggle_on_match)
	     && p->ocrb_mode != HW_A1(hw_ocu_mode_clear_on_match)
	     && p->ocrb_mode != HW_A1(hw_ocu_mode_set_on_match))
	  HWA_ERR("compare output B of class c8a counter mode must be "
		  "'disconnected', 'toggle_on_match', 'clear_on_match', or "
		  "'set_on_match'.");
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( p->ocrb_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->ocrb_mode != HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	     && p->ocrb_mode != HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output B of class c8a counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 || wgm==5 ) {
	if ( p->ocrb_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->ocrb_mode != HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	     && p->ocrb_mode != HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output B of class c8a counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
    }

    /*	Update
     */
    if ( p->update != 0 ) {
      if ( wgm==0 || wgm==2 ) {
	if ( p->update != HW_A1(hw_counter_update_immediately) )
	  HWA_ERR("optionnal parameter 'update' of class c8a counter must be "\
		  "'immediately'.");
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( p->update != HW_A1(hw_counter_update_at_bottom) )
	  HWA_ERR("optionnal parameter 'update' of class c8a counter must be "
		  "'at_bottom'.");
      }
      else
	if( p->update != HW_A1(hw_counter_update_at_top) )
	  HWA_ERR("optionnal parameter 'update' of class c8a counter must be "
		  "'at_top'.");
    }

    /*	Overflow
     */
    if ( p->overflow != 0 ) {
      if ( wgm==3 || wgm==7 ) {
	if ( p->overflow != HW_A1(hw_counter_overflow_at_top) )
	  HWA_ERR("optionnal parameter 'overflow' of class c8a counter must be "
		  "'at_top'.");
      }
      else
	if ( p->overflow != HW_A1(hw_counter_overflow_at_bottom) )
	  HWA_ERR("optionnal parameter 'overflow' of class c8a counter must be "
		  "'at_bottom'.");
    }

  }
}


HW_INLINE void _hwa_commit_c8a ( hwa_t *hwa, hwa_c8a_t *timer )
{
  _hwa_commit_r8( hwa->commit, &timer->ccra,  -1 );
  _hwa_commit_r8( hwa->commit, &timer->ccrb,  -1 );
  _hwa_commit_r8( hwa->commit, &timer->count, -1 );
  _hwa_commit_r8( hwa->commit, &timer->ocra,  -1 );
  _hwa_commit_r8( hwa->commit, &timer->ocrb,  -1 );
  _hwa_commit_r8( hwa->commit, &timer->imsk,  -1 );
  _hwa_commit_r8( hwa->commit, &timer->ifr,   -1 );
}
