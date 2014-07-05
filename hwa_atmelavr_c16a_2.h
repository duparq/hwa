
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA 16-bits version 'a' Atmel AVR timer-counters (layer 2)
 *
 *	Used in: ATtinyX4 Timer 1
 */


/*	Initialize a c16a instance
 */
#define hwa_begin_c16a(n)			\
  HWA_INIT(hw_##n, ccra);			\
  HWA_INIT(hw_##n, ccrb);			\
  HWA_INIT(hw_##n, ccrc);			\
  HWA_INIT(hw_##n, count);			\
  HWA_INIT(hw_##n, icr);			\
  HWA_INIT(hw_##n, ocra);			\
  HWA_INIT(hw_##n, ocrb);			\
  HWA_INIT(hw_##n, imsk);			\
  HWA_INIT(hw_##n, ifr);			\
  hwa->n.countmode = 0;				\
  hwa->n.top = 0;				\
  hwa->n.clock = 0;				\
  hwa->n.overflow = 0;				\
  hwa->n.update = 0;				\
  hwa->n.ocra_mode = 0;				\
  hwa->n.ocrb_mode = 0;


HW_INLINE void _hwa_reset_c16a ( hwa_c16a_t *timer )
{
  _hwa_reset_r8(  &timer->ccra );
  _hwa_reset_r8(  &timer->ccrb );
  _hwa_reset_r8(  &timer->ccrc );
  _hwa_reset_r16( &timer->count );
  _hwa_reset_r16( &timer->icr );
  _hwa_reset_r16( &timer->ocra );
  _hwa_reset_r16( &timer->ocrb );
  _hwa_reset_r8(  &timer->imsk );
  _hwa_reset_r8(  &timer->ifr );
}


/*	Configure counter unit
 */
#define hw_fn_hwa_config_c16a		, _hwa_config_c16a

#define _hwa_config_c16a(c,n,i,a, ...)					\
  do { HW_G2(hwa_config_c16a_xclock,HW_IS(clock,__VA_ARGS__))(n,__VA_ARGS__,) } while(0)

#define hwa_config_c16a_xclock_0(cn,...)				\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c16a_xclock_1(cn,_clock_,...)			\
  HW_G2(hwa_config_c16a_vclock,HW_IS(,hw_c16a_clock_##__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_vclock_0(cn,...)				\
  HW_ERR( "`clock` can be `none`, `syshz`, `syshz_div_8`, "		\
	  "`syshz_div_64`, `syshz_div_256`, `syshz_div_1024`, "		\
	  "`ext_falling`, `ext_rising`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c16a_vclock_1(cn,zclock,...)				\
  hwa->cn.clock = HW_A1(hw_c16a_clock_##zclock);			\
  HW_G2(hwa_config_c16a_xmode,HW_IS(countmode,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_xmode_0(cn,...)					\
  HW_ERR("expected `countmode` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c16a_xmode_1(cn,_countmode_,...)			\
  HW_G2(hwa_config_c16a_vmode,HW_IS(,hw_c16a_countmode_##__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_vmode_0(cn,...)					\
  HW_ERR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid mode option.")

#define hwa_config_c16a_vmode_1(cn,vmode,...)				\
  hwa->cn.countmode = HW_A1(hw_c16a_countmode_##vmode);			\
  HW_G2(hwa_config_c16a_xbottom,HW_IS(bottom,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_xbottom_1(cn,_bottom_,...)			\
  HW_G2(hwa_config_c16a_vbottom,HW_IS(0,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_vbottom_0(cn,bottom,...)	\
  HW_ERR("bottom must be `0`, not `" #bottom "`.")

#define hwa_config_c16a_vbottom_1(cn,bottom,...)	\
  hwa_config_c16a_xbottom_0(cn,__VA_ARGS__)

#define hwa_config_c16a_xbottom_0(cn,...)				\
  HW_G2(hwa_config_c16a_xtop,HW_IS(top,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_xtop_0(cn,...)				\
  HW_ERR("expected `top` instead of `" #__VA_ARGS__ "`.")

#define hwa_config_c16a_xtop_1(cn,_top_,...)				\
  HW_G2(hwa_config_c16a_vtop,HW_IS(,hw_c16a_top_##__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_vtop_0(cn,...)					\
  HW_ERR("`top` can be `fixed_0xFF`, `fixed_0x1FF`, `fixed_0x3FF`, "	\
	 "`fixed_0xFFFF`, `register_capture`, or `register_compare_a`," \
	 " but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c16a_vtop_1(cn,ztop,...)				\
    hwa->cn.top = HW_A1(hw_c16a_top_##ztop);				\
    HW_G2(hwa_config_c16a_xuc,HW_IS(update,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_xuc_1(cn,uc,...)				\
    HW_G2(hwa_config_c16a_vuc, HW_IS(,hw_counter_update_##__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_vuc_0(cn,vuc,...)				\
  HW_ERR("`update` must be `at_bottom`, `at_top, or `at_max`, but `not `" #vuc "`.")

#define hwa_config_c16a_vuc_1(cn,vuc,...)				\
  hwa->cn.update = HW_A1(hw_counter_update_##vuc);	\
  hwa_config_c16a_xuc_0(cn,__VA_ARGS__);

#define hwa_config_c16a_xuc_0(cn,...)					\
  HW_G2(hwa_config_c16a_xoverflow,HW_IS(overflow,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_xoverflow_1(cn,overflow_irq,...)	\
  HW_G2(hwa_config_c16a_voverflow,				\
	HW_IS(,hw_counter_overflow_##__VA_ARGS__))		\
  (cn,__VA_ARGS__)

#define hwa_config_c16a_voverflow_0(cn,overflow,...)			\
  HW_ERR("overflow_irq must be `at_bottom`, `at_top, or `at_max`, but `not `" #overflow "`.")

#define hwa_config_c16a_voverflow_1(cn,voverflow,...)			\
  hwa->cn.overflow = HW_A1(hw_counter_overflow_##voverflow);	\
  hwa_config_c16a_xoverflow_0(cn,__VA_ARGS__)

#define hwa_config_c16a_xoverflow_0(cn,...)			\
  HW_G2(hwa_config_c16a,HW_IS(,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_0(cn,...)				\
  HW_ERR( "too many arguments: `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c16a_1(...)


#define hw_is_overflow_overflow			, 1
#define hw_is_update_update			, 1

#define hw_counter_overflow_at_bottom		, 1
#define hw_counter_overflow_at_top		, 2
#define hw_counter_overflow_at_max		, 3

#define hw_counter_update_immediately		, 1
#define hw_counter_update_at_bottom		, 2
#define hw_counter_update_at_top		, 3


/*	Solve the configuration of the counter and its compare and capture units
 */
HW_INLINE void hwa_solve_c16a ( hwa_c16a_t *p )
{
  uint8_t wgm = 0xFF ;

  /* Mode WGM   Operation                     COUNTMODE    TOP     OCR  OVF  OCF  ICF  OCA              OCB
   *                                                               TOP
   *                                                               UPD
   *
   *   0  0000  Normal                        LOOP_UP      0xFFFF  IMM  BOT            CoM,SoM,ToM        CoM,SoM,ToM
   *   4  0100  CTC (Clear Timer on Match)    LOOP_UP      ocra    IMM  BOT  TOP                          CoM,SoM,ToM
   *  12  1100  CTC (Clear Timer on Match)    LOOP_UP      icr     IMM  BOT       TOP  CoM,SoM,ToM        CoM,SoM,ToM
   *
   *   5  0101  Fast PWM, 8-bit               LOOP_UP      0xFF    TOP  TOP            SaBCoM,CaBSoM      SaBCoM,CaBSoM
   *   6  0110  Fast PWM, 9-bit               LOOP_UP      0x1FF   TOP  TOP            SaBCoM,CaBSoM      SaBCoM,CaBSoM
   *   7  0111  Fast PWM, 10-bit              LOOP_UP      0x3FF   TOP  TOP            SaBCoM,CaBSoM      SaBCoM,CaBSoM
   *  14  1110  Fast PWM                      LOOP_UP      icr     TOP  TOP       TOP  ToM,SaBCoM,CaBSoM  SaBCoM,CaBSoM
   *  15  1111  Fast PWM                      LOOP_UP      ocra    TOP  TOP  TOP                          SaBCoM,CaBSoM
   *
   *   1  0001  PWM, Phase Correct, 8-bit     LOOP_UPDOWN  0xFF    TOP  BOT            CMUSMD,SMUCMD      CMUSMD,SMUCMD
   *   2  0010  PWM, Phase Correct, 9-bit     LOOP_UPDOWN  0x1FF   TOP  BOT            CMUSMD,SMUCMD      CMUSMD,SMUCMD
   *   3  0011  PWM, Phase Correct, 10-bit    LOOP_UPDOWN  0x3FF   TOP  BOT            CMUSMD,SMUCMD      CMUSMD,SMUCMD
   *  10  1010  PWM, Phase Correct            LOOP_UPDOWN  icr     TOP  BOT       TOP  ToM,CMUSMD,SMUCMD  CMUSMD,SMUCMD
   *  11  1011  PWM, Phase Correct            LOOP_UPDOWN  ocra    TOP  BOT  TOP                          CMUSMD,SMUCMD
   *
   *   8  1000  PWM, Phase & Freq. Correct    LOOP_UPDOWN  icr     BOT  BOT       TOP  ToM,CMUSMD,SMUCMD  CMUSMD,SMUCMD
   *   9  1001  PWM, Phase & Freq. Correct    LOOP_UPDOWN  ocra    BOT  BOT  TOP                          CMUSMD,SMUCMD
   *
   *  13  1101  *Reserved*
   */

  if ( p->clock ) {	/* if the mandatory parameter 'clock' is not 0, the
			   counter is configured */
    /*	Clock selection
     */
    _hwa_write_p(p, _hw_cbits(c16a, cs), p->clock);

    /*	Determine WGM
     */
    if ( p->countmode == HW_A1(hw_c16a_countmode_loop_up) ) {
      if (p->top == HW_A1(hw_c16a_top_fixed_0xFFFF))
	wgm = 0 ;
      else if (p->top == HW_A1(hw_c16a_top_fixed_0xFF) )
	wgm = 5 ;
      else if (p->top == HW_A1(hw_c16a_top_fixed_0x1FF) )
	wgm = 6 ;
      else if (p->top == HW_A1(hw_c16a_top_fixed_0x3FF) )
	wgm = 7 ;
      else if (p->top == HW_A1(hw_c16a_top_register_compare_a) ) {
	if (p->update == HW_A1(hw_counter_update_immediately)
	    || p->overflow == HW_A1(hw_counter_overflow_at_bottom)
	    || p->ocrb_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	    || p->ocrb_mode == HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match))
	  wgm = 15 ;
	else 
	  wgm = 4 ;
      }
      else /* if (p->top == HW_A1(hw_c16a_top_register_capture) ) */ {
	if (p->update == HW_A1(hw_counter_update_at_top)
	    || p->overflow == HW_A1(hw_counter_overflow_at_top)
	    || p->ocra_mode == HW_A1(hw_ocu_mode_toggle_on_match)
	    || p->ocra_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	    || p->ocra_mode == HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match)
	    || p->ocrb_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	    || p->ocrb_mode == HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match))
	  wgm = 14 ;
	else 
	  wgm = 12 ;
      }
    }
    else {
      if (p->top == HW_A1(hw_c16a_top_fixed_0xFF) )
	wgm = 1 ;
      else if (p->top == HW_A1(hw_c16a_top_fixed_0x1FF) )
	wgm = 2 ;
      else if (p->top == HW_A1(hw_c16a_top_fixed_0x3FF) )
	wgm = 3 ;
      else if (p->top == HW_A1(hw_c16a_top_register_compare_a) ) {
	if (p->update == HW_A1(hw_counter_update_at_bottom)
	    || p->ocrb_mode == HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	    || p->ocrb_mode == HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down))
	  wgm = 9 ;
	else 
	  wgm = 11 ;
      }
      else /* if (p->top == HW_A1(hw_c16a_top_register_capture) ) */ {
	if (p->update == HW_A1(hw_counter_update_at_bottom)
	    || p->ocra_mode == HW_A1(hw_ocu_mode_toggle_on_match)
	    || p->ocra_mode == HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	    || p->ocra_mode == HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down)
	    || p->ocrb_mode == HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	    || p->ocrb_mode == HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down))
	  wgm = 8 ;
	else 
	  wgm = 10 ;
      }
    }
      
    if (wgm != 0xFF)
      _hwa_write_p(p, _hw_cbits(c16a,wgm), wgm);
    else {
      HWA_ERR("WGM value could not be solved for c16a class counter.");
      return ;
    }
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
    _hwa_write_p(p, _hw_cbits(c16a, coma), mode );
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
    _hwa_write_p(p, _hw_cbits(c16a, comb), mode );
  }

  /*	Check the validity of the configuration
   *
   * WGM  TOP     UPD  OVF  OCA                OCB            COUNTMODE    
   *							                   
   *   0  0xFFFF  IMM  BOT  CoM,SoM,ToM        CoM,SoM,ToM    LOOP_UP      
   *   4  ocra    IMM  BOT                     CoM,SoM,ToM    LOOP_UP      
   *  12  icr     IMM  BOT  CoM,SoM,ToM        CoM,SoM,ToM    LOOP_UP      
   *							                   
   *   5  0xFF    TOP  TOP  SaBCoM,CaBSoM      SaBCoM,CaBSoM  LOOP_UP      
   *   6  0x1FF   TOP  TOP  SaBCoM,CaBSoM      SaBCoM,CaBSoM  LOOP_UP      
   *   7  0x3FF   TOP  TOP  SaBCoM,CaBSoM      SaBCoM,CaBSoM  LOOP_UP      
   *  14  icr     TOP  TOP  ToM,SaBCoM,CaBSoM  SaBCoM,CaBSoM  LOOP_UP      
   *  15  ocra    TOP  TOP                     SaBCoM,CaBSoM  LOOP_UP      
   *							                   
   *   1  0xFF    TOP  BOT  CMUSMD,SMUCMD      CMUSMD,SMUCMD  LOOP_UPDOWN  
   *   2  0x1FF   TOP  BOT  CMUSMD,SMUCMD      CMUSMD,SMUCMD  LOOP_UPDOWN  
   *   3  0x3FF   TOP  BOT  CMUSMD,SMUCMD      CMUSMD,SMUCMD  LOOP_UPDOWN  
   *  10  icr     TOP  BOT  ToM,CMUSMD,SMUCMD  CMUSMD,SMUCMD  LOOP_UPDOWN  
   *  11  ocra    TOP  BOT                     CMUSMD,SMUCMD  LOOP_UPDOWN  
   *							                   
   *   8  icr     BOT  BOT  ToM,CMUSMD,SMUCMD  CMUSMD,SMUCMD  LOOP_UPDOWN  
   *   9  ocra    BOT  BOT                     CMUSMD,SMUCMD  LOOP_UPDOWN
   */
  if ( p->clock || p->ocra_mode || p->ocrb_mode ) {

    if ( p->clock == 0 ) {
      HWA_ERR("configuration of counter is required.");
      return ;
    }

    /*	Compare output A
     */
    if ( wgm==0 || wgm==4 || wgm==12 ) {
      if ( p->ocra_mode != HW_A1(hw_ocu_mode_disconnected)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_clear_on_match)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_set_on_match)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_toggle_on_match) )
	HWA_ERR("compare output A of class c16a counter mode must be "
		"'disconnected', 'clear_on_match', 'set_on_match', or "
		"'toggle_on_match'.");
    }
    else if ( wgm==5 || wgm==6 || wgm==7 ) {
      if ( p->ocra_mode != HW_A1(hw_ocu_mode_disconnected)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match) )
	HWA_ERR("compare output A of class c16a counter mode must be "
		"'disconnected', 'set_at_bottom_clear_on_match', or "
		"'clear_at_bottom_set_on_match'.");
    }
    else if ( wgm==14 ) {
      if ( p->ocra_mode != HW_A1(hw_ocu_mode_disconnected)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_toggle_on_match)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match) )
	HWA_ERR("compare output A of class c16a counter mode must be "
		"'disconnected', 'toggle_on_match', "
		"'set_at_bottom_clear_on_match', or "
		"'clear_at_bottom_set_on_match'.");
    }
    else if ( wgm==1 || wgm==2 || wgm==3 ) {
      if ( p->ocra_mode != HW_A1(hw_ocu_mode_disconnected)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down) )
	HWA_ERR("compare output A of class c16a counter mode must be "
		"'disconnected', 'clear_on_match_up_set_on_match_down', "
		"or 'set_on_match_up_clear_on_match_down'.");
    }
    else if ( wgm==8 || wgm==10 ) {
      if ( p->ocra_mode != HW_A1(hw_ocu_mode_disconnected)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_toggle_on_match)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	   && p->ocra_mode != HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down) )
	HWA_ERR("compare output A of class c16a counter mode must be "
		"'disconnected', 'toggle_on_match', "
		"'clear_on_match_up_set_on_match_down', "
		"or 'set_on_match_up_clear_on_match_down'.");
    }
    //    else if ( p->top == HW_A1(hw_c16a_top_register_compare_a)
    else if ( p->ocra_mode ) {
      HWA_ERR("use of `compare_a` as both top value for class c16a counter "
	      "and compare output.");
    }

    /*	Compare output B
     */
    if ( wgm==0 || wgm==4 || wgm==12 ) {
      if ( p->ocrb_mode != HW_A1(hw_ocu_mode_disconnected)
	   && p->ocrb_mode != HW_A1(hw_ocu_mode_clear_on_match)
	   && p->ocrb_mode != HW_A1(hw_ocu_mode_set_on_match)
	   && p->ocrb_mode != HW_A1(hw_ocu_mode_toggle_on_match) )
	HWA_ERR("compare output B of class c16a counter mode must be "
		"'disconnected', 'clear_on_match', 'set_on_match', or "
		"'toggle_on_match'.");
    }
    else if ( wgm==5 || wgm==6 || wgm==7 || wgm==14 || wgm==15 ) {
      if ( p->ocrb_mode != HW_A1(hw_ocu_mode_disconnected)
	   && p->ocrb_mode != HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	   && p->ocrb_mode != HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match) )
	HWA_ERR("compare output B of class c16a counter mode must be "
		"'disconnected', 'set_at_bottom_clear_on_match', or "
		"'clear_at_bottom_set_on_match'.");
    }
    else /* if ( wgm==1 || wgm==2 || wgm==3 || wgm==8 || wgm==9 || wgm==10 || wgm==11 ) */ {
      if ( p->ocrb_mode != HW_A1(hw_ocu_mode_disconnected)
	   && p->ocrb_mode != HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	   && p->ocrb_mode != HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down) )
	HWA_ERR("compare output B of class c16a counter mode must be "
		"'disconnected', 'clear_on_match_up_set_on_match_down', "
		"or 'set_on_match_up_clear_on_match_down'.");
    }

    /*	Update
     */
    if ( p->update != 0 ) {
      if ( wgm==0 || wgm==4 || wgm==12 ) {
	if ( p->update != HW_A1(hw_counter_update_immediately) )
	  HWA_ERR("optionnal parameter 'update' of class c16a counter must be "\
		  "'immediately'.");
      }
      else if ( wgm==8 || wgm==9 ) {
	if ( p->update != HW_A1(hw_counter_update_at_bottom) )
	  HWA_ERR("optionnal parameter 'update' of class c16a counter must be "
		  "'at_bottom'.");
      }
      else
	if( p->update != HW_A1(hw_counter_update_at_top) )
	  HWA_ERR("optionnal parameter 'update' of class c16a counter must be "
		  "'at_top'.");
    }

    /*	Overflow
     */
    if ( p->overflow != 0 ) {
      if ( wgm==5 || wgm==6 || wgm==7 || wgm==14 || wgm==15 ) {
	if ( p->overflow != HW_A1(hw_counter_overflow_at_top) )
	  HWA_ERR("optionnal parameter 'overflow' of class c16a counter must be "
		  "'at_top'.");
      }
      else
	if ( p->overflow != HW_A1(hw_counter_overflow_at_bottom) )
	  HWA_ERR("optionnal parameter 'overflow' of class c16a counter must be "
		  "'at_bottom'.");
    }

  }
}


HW_INLINE void _hwa_commit_c16a ( hwa_t *hwa, hwa_c16a_t *timer )
{
  _hwa_commit_r8(  hwa->commit, &timer->ccra,  -1 );
  _hwa_commit_r8(  hwa->commit, &timer->ccrb,  -1 );
  _hwa_commit_r8(  hwa->commit, &timer->ccrc,  -1 );
  _hwa_commit_r16( hwa->commit, &timer->count, -1 );
  _hwa_commit_r16( hwa->commit, &timer->icr,   -1 );
  _hwa_commit_r16( hwa->commit, &timer->ocra,  -1 );
  _hwa_commit_r16( hwa->commit, &timer->ocrb,  -1 );
  _hwa_commit_r8(  hwa->commit, &timer->imsk,  -1 );
  _hwa_commit_r8(  hwa->commit, &timer->ifr,   -1 );
}
