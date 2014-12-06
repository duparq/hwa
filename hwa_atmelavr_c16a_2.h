
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
#define _hwa_begin_c16a(...)		_hwa_begin_c16a_2(__VA_ARGS__)
#define _hwa_begin_c16a_2(c,n,i,a)		\
  _hwa_begin_reg(c,n,i,a, ccra);		\
  _hwa_begin_reg(c,n,i,a, ccrb);		\
  _hwa_begin_reg(c,n,i,a, ccrc);		\
  _hwa_begin_reg(c,n,i,a, count);		\
  _hwa_begin_reg(c,n,i,a, icr);			\
  _hwa_begin_reg(c,n,i,a, ocra);		\
  _hwa_begin_reg(c,n,i,a, ocrb);		\
  _hwa_begin_reg(c,n,i,a, imsk);		\
  _hwa_begin_reg(c,n,i,a, ifr);			\
  hwa->n.clock = 0;				\
  hwa->n.countmode = 0;				\
  hwa->n.top = 0;				\
  hwa->n.update = 0;				\
  hwa->n.overflow = 0;				\
  hwa->n.ocra_mode = 0;				\
  hwa->n.ocrb_mode = 0;				\
  hwa->n.icr_input = 0;				\
  hwa->n.icr_edge = 0;				\
  hwa->n.icr_filter = 0;


HW_INLINE void _hwa_init_c16a ( hwa_c16a_t *timer )
{
  _hwa_set_r8(  &timer->ccra,  0x00 );
  _hwa_set_r8(  &timer->ccrb,  0x00 );
  _hwa_set_r8(  &timer->ccrc,  0x00 );
  _hwa_set_r16( &timer->count, 0x00 );
  _hwa_set_r16( &timer->icr,   0x00 );
  _hwa_set_r16( &timer->ocra,  0x00 );
  _hwa_set_r16( &timer->ocrb,  0x00 );
  _hwa_set_r8(  &timer->imsk,  0x00 );
  _hwa_set_r8(  &timer->ifr,   0x00 );
}


/*	16-bit counter class 'c16a'
 */
#define hw_c16a_countmode_loop_up		, 1
#define hw_c16a_countmode_loop_updown		, 2

#define hw_c16a_top_fixed_0xFF			, 1
#define hw_c16a_top_fixed_0x1FF			, 2
#define hw_c16a_top_fixed_0x3FF			, 3
#define hw_c16a_top_fixed_0xFFFF		, 4
#define hw_c16a_top_reg_input0			, 5
#define hw_c16a_top_reg_output0			, 6

#define hw_c16a_clock_none			, 0
#define hw_c16a_clock_syshz			, 1
#define hw_c16a_clock_syshz_div_1		, 1	/* Useful for concat */
#define hw_c16a_clock_syshz_div_8		, 2
#define hw_c16a_clock_syshz_div_64		, 3
#define hw_c16a_clock_syshz_div_256		, 4
#define hw_c16a_clock_syshz_div_1024		, 5
#define hw_c16a_clock_ext_rising		, 6
#define hw_c16a_clock_ext_falling		, 7


/*	Configure counter unit
 */
#define hw_def_hwa_config_c16a		, _hwa_config_c16a

#define _hwa_config_c16a(c,n,i,a, ...)					\
  do { HW_G2(_hwa_config_c16a_xclock,HW_IS(clock,__VA_ARGS__))(n,__VA_ARGS__,) } while(0)

#define _hwa_config_c16a_xclock_0(n,...)					\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_c16a_xclock_1(n,_clock_,...)				\
  HW_G2(_hwa_config_c16a_vclock,HW_IS(,hw_c16a_clock_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c16a_vclock_0(n,...)					\
  HW_ERR( "`clock` can be `none`, `syshz`, `syshz_div_8`, "		\
	  "`syshz_div_64`, `syshz_div_256`, `syshz_div_1024`, "		\
	  "`ext_falling`, `ext_rising`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_c16a_vclock_1(n,zclock,...)				\
  hwa->n.clock = HW_A1(hw_c16a_clock_##zclock);				\
  HW_G2(_hwa_config_c16a_xmode,HW_IS(countmode,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c16a_xmode_0(n,...)					\
  HW_ERR("expected `countmode` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_c16a_xmode_1(n,_countmode_,...)			\
  HW_G2(_hwa_config_c16a_vmode,HW_IS(,hw_c16a_countmode_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c16a_vmode_0(n,...)					\
  HW_ERR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid mode option.")

#define _hwa_config_c16a_vmode_1(n,vmode,...)				\
  hwa->n.countmode = HW_A1(hw_c16a_countmode_##vmode);			\
  HW_G2(_hwa_config_c16a_xbottom,HW_IS(bottom,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c16a_xbottom_1(n,_bottom_,...)			\
  HW_G2(_hwa_config_c16a_vbottom,HW_IS(0,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c16a_vbottom_0(n,bottom,...)		\
  HW_ERR("bottom must be `0`, not `" #bottom "`.")

#define _hwa_config_c16a_vbottom_1(n,bottom,...)	\
  _hwa_config_c16a_xbottom_0(n,__VA_ARGS__)

#define _hwa_config_c16a_xbottom_0(n,...)				\
  HW_G2(_hwa_config_c16a_xtop,HW_IS(top,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c16a_xtop_0(n,...)				\
  HW_ERR("expected `top` instead of `" #__VA_ARGS__ "`.")

#define _hwa_config_c16a_xtop_1(n,_top_,...)				\
  HW_G2(_hwa_config_c16a_vtop,HW_IS(,hw_c16a_top_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c16a_vtop_0(n,...)					\
  HW_ERR("`top` can be `fixed_0xFF`, `fixed_0x1FF`, `fixed_0x3FF`, "	\
	 "`fixed_0xFFFF`, `register_capture`, or `register_compare_a`," \
	 " but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_c16a_vtop_1(n,ztop,...)				\
  hwa->n.top = HW_A1(hw_c16a_top_##ztop);				\
  HW_G2(_hwa_config_c16a_xuc,HW_IS(update,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c16a_xuc_1(n,uc,...)					\
  HW_G2(_hwa_config_c16a_vuc, HW_IS(,hw_counter_update_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c16a_vuc_0(n,vuc,...)				\
    HW_ERR("`update` must be `at_bottom`, `at_top, or `at_max`, but `not `" #vuc "`.")

#define _hwa_config_c16a_vuc_1(n,vuc,...)		\
  hwa->n.update = HW_A1(hw_counter_update_##vuc);	\
  _hwa_config_c16a_xuc_0(n,__VA_ARGS__);

#define _hwa_config_c16a_xuc_0(n,...)					\
  HW_G2(_hwa_config_c16a_xoverflow,HW_IS(overflow,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c16a_xoverflow_1(n,overflow,...)	\
  HW_G2(_hwa_config_c16a_voverflow, HW_IS(,hw_counter_overflow_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config_c16a_voverflow_0(n,overflow,...)			\
  HW_ERR("optionnal parameter `overflow` must be `at_bottom`, "		\
	 "`at_top, or `at_max`, but `not `" #overflow "`.")

#define _hwa_config_c16a_voverflow_1(n,voverflow,...)		\
  HW_TX(hwa->n.overflow = HW_A1(hw_counter_overflow_##voverflow),__VA_ARGS__);

#define _hwa_config_c16a_xoverflow_0(n,...)			\
  HW_TX(,__VA_ARGS__)


/*	Solve the configuration of the counter with its compare and capture units
 */
HW_INLINE void hwa_solve_c16a ( hwa_t *hwa, hwa_c16a_t *p )
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

  if ( p->countmode ) {	/* if the mandatory parameter 'countmode' is not 0, the
			   counter is configured */
    /*	Clock selection
     */
    _hwa_write_p(p, _hw_creg(c16a, cs), p->clock);

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
      _hwa_write_p(p, _hw_creg(c16a,wgm), wgm);
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
    _hwa_write_p(p, _hw_creg(c16a, coma), mode );
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
    _hwa_write_p(p, _hw_creg(c16a, comb), mode );
  }

  /*	Solve the configuration of the capture input
   */
  if ( p->icr_input ) {
#if !defined HW_DEVICE_ATTINYX4
#  warn "TODO: check the validity of this"
#endif
    _hwa_write_reg( hw_acmp0, acic, p->icr_input-1 );
    _hwa_write_p(p, _hw_creg(c16a, ices), p->icr_edge-1 );
    _hwa_write_p(p, _hw_creg(c16a, icnc), p->icr_filter );
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
  if ( p->countmode || p->ocra_mode || p->ocrb_mode ) {

    if ( p->countmode == 0 ) {
      HWA_ERR("configuration of counter is required.");
      return ;
    }

    /*	Compare output A
     */
    if ( p->ocra_mode != 0 ) {
      if ( wgm==0 || wgm==12 ) {
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
	HWA_ERR("use of `compare_a` as both top value and compare output of class c16a counter.");
      }
    }

    /*	Compare output B
     */
    if ( p->ocrb_mode != 0 ) {
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


#define _hwa_commit_c16a(...)		_hwa_commit_c16a_2(__VA_ARGS__)
#define _hwa_commit_c16a_2(c,n,i,a, co)		\
  _hwa_commit_reg(c,n,i,a, ccra,  co );		\
  _hwa_commit_reg(c,n,i,a, ccrb,  co );		\
  _hwa_commit_reg(c,n,i,a, ccrc,  co );		\
  _hwa_commit_reg(c,n,i,a, count, co );		\
  _hwa_commit_reg(c,n,i,a, icr,   co );		\
  _hwa_commit_reg(c,n,i,a, ocra,  co );		\
  _hwa_commit_reg(c,n,i,a, ocrb,  co );		\
  _hwa_commit_reg(c,n,i,a, imsk,  co );		\
  _hwa_commit_reg(c,n,i,a, ifr,   co );
