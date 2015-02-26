
/*	Atmel AVR 16-bit timer-counter model 'a'
 *
 *	Used in:	ATtinyX4 counter1
 *			ATmegaX8 counter1 ?
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


HW_INLINE void __hwa_begin__c16a ( hwa_c16a_t *p, intptr_t a )
{
  _hwa_begin_pacr( p, a, _c16a, ccra  );
  _hwa_begin_pacr( p, a, _c16a, ccrb  );
  _hwa_begin_pacr( p, a, _c16a, ccrc  );
  _hwa_begin_pacr( p, a, _c16a, count );
  _hwa_begin_pacr( p, a, _c16a, icr   );
  _hwa_begin_pacr( p, a, _c16a, ocra  );
  _hwa_begin_pacr( p, a, _c16a, ocrb  );
  _hwa_begin_pacr( p, a, _c16a, imsk  );
  _hwa_begin_pacr( p, a, _c16a, ifr   );

  p->clock        = 0xFF ;
  p->countmode    = 0xFF ;
  p->top          = 0xFF ;
  p->update       = 0xFF ;
  p->overflow     = 0xFF ;
  p->output0_mode = 0xFF ;
  p->output1_mode = 0xFF ;
  p->icr_input    = 0xFF ;
  p->icr_edge     = 0xFF ;
  p->icr_filter   = 0xFF ;
}


HW_INLINE void __hwa_init__c16a ( hwa_c16a_t *p )
{
  _hwa_set_r8(  &p->ccra,  0x00 );
  _hwa_set_r8(  &p->ccrb,  0x00 );
  _hwa_set_r8(  &p->ccrc,  0x00 );
  _hwa_set_r16( &p->count, 0x00 );
  _hwa_set_r16( &p->icr,   0x00 );
  _hwa_set_r16( &p->ocra,  0x00 );
  _hwa_set_r16( &p->ocrb,  0x00 );
  _hwa_set_r8(  &p->imsk,  0x00 );
  _hwa_set_r8(  &p->ifr,   0x00 );
}


HW_INLINE void __hwa_commit__c16a ( hwa_t *hwa, hwa_c16a_t *p )
{
  _hwa_commit_pcr( p, _c16a, ccra  );
  _hwa_commit_pcr( p, _c16a, ccrb  );
  _hwa_commit_pcr( p, _c16a, ccrc  );
  _hwa_commit_pcr( p, _c16a, count );
  _hwa_commit_pcr( p, _c16a, icr   );
  _hwa_commit_pcr( p, _c16a, ocra  );
  _hwa_commit_pcr( p, _c16a, ocrb  );
  _hwa_commit_pcr( p, _c16a, imsk  );
  _hwa_commit_pcr( p, _c16a, ifr   );
}


/*	16-bit counter class '_c16a'
 */
#define hw__c16a_countmode_loop_up		, 1
#define hw__c16a_countmode_loop_updown		, 2

#define hw__c16a_top_fixed_0xFF			, 1
#define hw__c16a_top_fixed_0x1FF		, 2
#define hw__c16a_top_fixed_0x3FF		, 3
#define hw__c16a_top_fixed_0xFFFF		, 4
#define hw__c16a_top_max			, 4
#define hw__c16a_top_input0			, 5
#define hw__c16a_top_output0			, 6

#define hw__c16a_clock_none			, 0
#define hw__c16a_clock_syshz			, 1
#define hw__c16a_clock_syshz_div_1		, 1	/* Useful for concat */
#define hw__c16a_clock_syshz_div_8		, 2
#define hw__c16a_clock_syshz_div_64		, 3
#define hw__c16a_clock_syshz_div_256		, 4
#define hw__c16a_clock_syshz_div_1024		, 5
#define hw__c16a_clock_ext_rising		, 6
#define hw__c16a_clock_ext_falling		, 7


/*	Configure counter unit
 */
#define hw_def_hwa_config__c16a		, _hwa_config__c16a

#define _hwa_config__c16a(c,n,i,a, ...)					\
  do { HW_G2(_hwa_config__c16a_xclock,HW_IS(clock,__VA_ARGS__))(n,__VA_ARGS__,) } while(0)

#define _hwa_config__c16a_xclock_0(n,...)					\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_xclock_1(n,_clock_,...)				\
  HW_G2(_hwa_config__c16a_vclock,HW_IS(,hw__c16a_clock_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vclock_0(n,...)					\
  HW_ERR( "`clock` can be `none`, `syshz`, `syshz_div_8`, "		\
	  "`syshz_div_64`, `syshz_div_256`, `syshz_div_1024`, "		\
	  "`ext_falling`, `ext_rising`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_vclock_1(n,zclock,...)				\
  hwa->n.clock = HW_A1(hw__c16a_clock_##zclock);				\
  HW_G2(_hwa_config__c16a_xmode,HW_IS(countmode,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_xmode_0(n,...)					\
  HW_ERR("expected `countmode` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_xmode_1(n,_countmode_,...)			\
  HW_G2(_hwa_config__c16a_vmode,HW_IS(,hw__c16a_countmode_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vmode_0(n,...)					\
  HW_ERR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid mode option.")

#define _hwa_config__c16a_vmode_1(n,vmode,...)				\
  hwa->n.countmode = HW_A1(hw__c16a_countmode_##vmode);			\
  HW_G2(_hwa_config__c16a_xbottom,HW_IS(bottom,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_xbottom_1(n,_bottom_,...)			\
  HW_G2(_hwa_config__c16a_vbottom,HW_IS(0,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vbottom_0(n,bottom,...)		\
  HW_ERR("bottom must be `0`, not `" #bottom "`.")

#define _hwa_config__c16a_vbottom_1(n,bottom,...)	\
  _hwa_config__c16a_xbottom_0(n,__VA_ARGS__)

#define _hwa_config__c16a_xbottom_0(n,...)				\
  HW_G2(_hwa_config__c16a_xtop,HW_IS(top,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_xtop_0(n,...)				\
  HW_ERR("expected `top` instead of `" #__VA_ARGS__ "`.")

#define _hwa_config__c16a_xtop_1(n,_top_,...)				\
  HW_G2(_hwa_config__c16a_vtop,HW_IS(,hw__c16a_top_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vtop_0(n,...)					\
  HW_ERR("`top` can be `fixed_0xFF`, `fixed_0x1FF`, `fixed_0x3FF`, "	\
	 "`fixed_0xFFFF`, `register_capture`, or `register_compare_a`," \
	 " but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_vtop_1(n,ztop,...)				\
  hwa->n.top = HW_A1(hw__c16a_top_##ztop);				\
  HW_G2(_hwa_config__c16a_xuc,HW_IS(update,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_xuc_1(n,uc,...)					\
  HW_G2(_hwa_config__c16a_vuc, HW_IS(,hw_counter_update_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vuc_0(n,vuc,...)				\
    HW_ERR("`update` must be `at_bottom`, `at_top, or `at_max`, but `not `" #vuc "`.")

#define _hwa_config__c16a_vuc_1(n,vuc,...)		\
  hwa->n.update = HW_A1(hw_counter_update_##vuc);	\
  _hwa_config__c16a_xuc_0(n,__VA_ARGS__);

#define _hwa_config__c16a_xuc_0(n,...)					\
  HW_G2(_hwa_config__c16a_xoverflow,HW_IS(overflow,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_xoverflow_1(n,overflow,...)	\
  HW_G2(_hwa_config__c16a_voverflow, HW_IS(,hw_counter_overflow_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_voverflow_0(n,overflow,...)			\
  HW_ERR("optionnal parameter `overflow` must be `at_bottom`, "		\
	 "`at_top, or `at_max`, but `not `" #overflow "`.")

#define _hwa_config__c16a_voverflow_1(n,voverflow,...)		\
  HW_TX(hwa->n.overflow = HW_A1(hw_counter_overflow_##voverflow),__VA_ARGS__);

#define _hwa_config__c16a_xoverflow_0(n,...)			\
  HW_TX(,__VA_ARGS__)


/*	Solve the configuration of the counter with its compare and capture units
 */
HW_INLINE void __hwa_solve__c16a ( hwa_t *hwa __attribute__((unused)), hwa_c16a_t *p )
{
  uint8_t wgm = 0xFF ;

  /* Mode WGM   Operation                     COUNTMODE    TOP     OCR  OVF  OCF  ICF  OCA                OCB
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

  if ( p->clock != 0xFF ) {

    /*	Clock selection
     */
    _hwa_write_pcr( p, _c16a, cs, p->clock );

    /*	Determine WGM
     */
    if ( p->countmode == HW_A1(hw__c16a_countmode_loop_up) ) {
      if (p->top == HW_A1(hw__c16a_top_fixed_0xFFFF))
	wgm = 0 ;
      else if (p->top == HW_A1(hw__c16a_top_fixed_0xFF) )
	wgm = 5 ;
      else if (p->top == HW_A1(hw__c16a_top_fixed_0x1FF) )
	wgm = 6 ;
      else if (p->top == HW_A1(hw__c16a_top_fixed_0x3FF) )
	wgm = 7 ;
      else if (p->top == HW_A1(hw__c16a_top_output0) ) {
	if (p->update == HW_A1(hw_counter_update_immediately)
	    || p->overflow == HW_A1(hw_counter_overflow_at_bottom)
	    || p->output1_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	    || p->output1_mode == HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match))
	  wgm = 15 ;
	else 
	  wgm = 4 ;
      }
      else /* if (p->top == HW_A1(hw__c16a_top_input0) ) */ {
	if (p->update == HW_A1(hw_counter_update_at_top)
	    || p->overflow == HW_A1(hw_counter_overflow_at_top)
	    || p->output0_mode == HW_A1(hw_ocu_mode_toggle_on_match)
	    || p->output0_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	    || p->output0_mode == HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match)
	    || p->output1_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	    || p->output1_mode == HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match))
	  wgm = 14 ;
	else 
	  wgm = 12 ;
      }
    }
    else {
      if (p->top == HW_A1(hw__c16a_top_fixed_0xFF) )
	wgm = 1 ;
      else if (p->top == HW_A1(hw__c16a_top_fixed_0x1FF) )
	wgm = 2 ;
      else if (p->top == HW_A1(hw__c16a_top_fixed_0x3FF) )
	wgm = 3 ;
      else if (p->top == HW_A1(hw__c16a_top_output0) ) {
	if (p->update == HW_A1(hw_counter_update_at_bottom)
	    || p->output1_mode == HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	    || p->output1_mode == HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down))
	  wgm = 9 ;
	else 
	  wgm = 11 ;
      }
      else /* if (p->top == HW_A1(hw__c16a_top_input0) ) */ {
	if (p->update == HW_A1(hw_counter_update_at_bottom)
	    || p->output0_mode == HW_A1(hw_ocu_mode_toggle_on_match)
	    || p->output0_mode == HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	    || p->output0_mode == HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down)
	    || p->output1_mode == HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	    || p->output1_mode == HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down))
	  wgm = 8 ;
	else 
	  wgm = 10 ;
      }
    }
      
    if (wgm != 0xFF)
      _hwa_write_pcr( p, _c16a, wgm, wgm );
    else {
      HWA_ERR("WGM value could not be solved for _c16a class counter.");
      return ;
    }
  }

#if 1
  /*	Solve the configuration of compare output A
   */
  if ( p->output0_mode != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( p->output0_mode == HW_A1(hw_ocu_mode_disconnected) )
      mode = 0 ;
    else if ( p->output0_mode == HW_A1(hw_ocu_mode_toggle_on_match) )
      mode = 1 ;
    else if ( p->output0_mode == HW_A1(hw_ocu_mode_clear_on_match)
	      || p->output0_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	      || p->output0_mode == HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    /*  Write the hardware configuration bits
     */
    _hwa_write_pcr( p, _c16a, coma, mode );
  }

  /*  Solve the configuration of compare output B
   */
  if ( p->output1_mode != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( p->output1_mode == HW_A1(hw_ocu_mode_disconnected) )
      mode = 0 ;
    else if ( p->output1_mode == HW_A1(hw_ocu_mode_toggle_on_match) )
      mode = 1 ;
    else if ( p->output1_mode == HW_A1(hw_ocu_mode_clear_on_match)
	      || p->output1_mode == HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	      || p->output1_mode == HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    /*  Write the hardware configuration bits
     */
    _hwa_write_pcr( p, _c16a, comb, mode );
  }

  /*	Solve the configuration of the capture input
   */
  if ( p->icr_input != 0xFF ) {
    _hwa_write_pcr( p, _c16a, acic, p->icr_input-1 );
    _hwa_write_pcr( p, _c16a, ices, p->icr_edge-1 );
    _hwa_write_pcr( p, _c16a, icnc, p->icr_filter );
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
  if ( p->countmode != 0xFF || p->output0_mode != 0xFF || p->output1_mode != 0xFF ) {

    if ( p->countmode == 0xFF ) {
      HWA_ERR("configuration of counter is required.");
      return ;
    }

    /*	Compare output A
     */
    if ( p->output0_mode != 0xFF ) {
      if ( wgm==0 || wgm==12 ) {
	if ( p->output0_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->output0_mode != HW_A1(hw_ocu_mode_clear_on_match)
	     && p->output0_mode != HW_A1(hw_ocu_mode_set_on_match)
	     && p->output0_mode != HW_A1(hw_ocu_mode_toggle_on_match) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'clear_on_match', 'set_on_match', or "
		  "'toggle_on_match'.");
      }
      else if ( wgm==5 || wgm==6 || wgm==7 ) {
	if ( p->output0_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->output0_mode != HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	     && p->output0_mode != HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==14 ) {
	if ( p->output0_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->output0_mode != HW_A1(hw_ocu_mode_toggle_on_match)
	     && p->output0_mode != HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	     && p->output0_mode != HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 || wgm==2 || wgm==3 ) {
	if ( p->output0_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->output0_mode != HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	     && p->output0_mode != HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
      else if ( wgm==8 || wgm==10 ) {
	if ( p->output0_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->output0_mode != HW_A1(hw_ocu_mode_toggle_on_match)
	     && p->output0_mode != HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	     && p->output0_mode != HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
      //    else if ( p->top == HW_A1(hw__c16a_top_output0)
      else if ( p->output0_mode ) {
	HWA_ERR("use of `compare_a` as both top value and compare output of class _c16a counter.");
      }
    }

    /*	Compare output B
     */
    if ( p->output1_mode != 0xFF ) {
      if ( wgm==0 || wgm==4 || wgm==12 ) {
	if ( p->output1_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->output1_mode != HW_A1(hw_ocu_mode_clear_on_match)
	     && p->output1_mode != HW_A1(hw_ocu_mode_set_on_match)
	     && p->output1_mode != HW_A1(hw_ocu_mode_toggle_on_match) )
	  HWA_ERR("compare output B of class _c16a counter mode must be "
		  "'disconnected', 'clear_on_match', 'set_on_match', or "
		  "'toggle_on_match'.");
      }
      else if ( wgm==5 || wgm==6 || wgm==7 || wgm==14 || wgm==15 ) {
	if ( p->output1_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->output1_mode != HW_A1(hw_ocu_mode_set_at_bottom_clear_on_match)
	     && p->output1_mode != HW_A1(hw_ocu_mode_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output B of class _c16a counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else /* if ( wgm==1 || wgm==2 || wgm==3 || wgm==8 || wgm==9 || wgm==10 || wgm==11 ) */ {
	if ( p->output1_mode != HW_A1(hw_ocu_mode_disconnected)
	     && p->output1_mode != HW_A1(hw_ocu_mode_clear_on_match_up_set_on_match_down)
	     && p->output1_mode != HW_A1(hw_ocu_mode_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output B of class _c16a counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
    }

    /*	Update
     */
    if ( p->update != 0xFF ) {
      if ( wgm==0 || wgm==4 || wgm==12 ) {
	if ( p->update != HW_A1(hw_counter_update_immediately) )
	  HWA_ERR("optionnal parameter 'update' of class _c16a counter must be "\
		  "'immediately'.");
      }
      else if ( wgm==8 || wgm==9 ) {
	if ( p->update != HW_A1(hw_counter_update_at_bottom) )
	  HWA_ERR("optionnal parameter 'update' of class _c16a counter must be "
		  "'at_bottom'.");
      }
      else
	if( p->update != HW_A1(hw_counter_update_at_top) )
	  HWA_ERR("optionnal parameter 'update' of class _c16a counter must be "
		  "'at_top'.");
    }

    /*	Overflow
     */
    if ( p->overflow != 0xFF ) {
      if ( wgm==5 || wgm==6 || wgm==7 || wgm==14 || wgm==15 ) {
	if ( p->overflow != HW_A1(hw_counter_overflow_at_top) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c16a counter must be "
		  "'at_top'.");
      }
      else
	if ( p->overflow != HW_A1(hw_counter_overflow_at_bottom) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c16a counter must be "
		  "'at_bottom'.");
    }

  }
#endif
}


/*	Read/write the 'count' register of a _c16a counter
 */
#define hw_def_hw_read__c16a		, _hw_read_c16a
#define _hw_read_c16a(c,n,i,a,...)	HW_TX(_hw_read_reg(c,n,i,a,count),__VA_ARGS__)

#define hw_def_hw_write__c16a		, _hw_write_c16a
#define _hw_write_c16a(c,n,i,a,v)	_hw_write_reg(c,n,i,a,count,v)

#define hw_def_hwa_write__c16a		, _hwa_write_c16a
#define _hwa_write_c16a(c,n,i,a,v)	_hwa_write_reg(c,n,i,a,count,v)

#define hw_def_hw_clear__c16a		, _hw_clear_c16a
#define _hw_clear_c16a(c,n,i,a,...)	HW_TX(_hw_write_reg(c,n,i,a,count,0),__VA_ARGS__)

#define hw_def_hwa_clear__c16a		, _hwa_clear_c16a
#define _hwa_clear_c16a(c,n,i,a)	_hwa_write_reg(c,n,i,a,count,0)


/*  Status
 *
 *	hw_stat_t(...) declares the structure that holds the status
 *	hw_stat(...) reads and returns the status
 *
 *	The only flag that is available is the irq flag.
 */
#define hw_def_hw_stat__c16a		, _hw_stat_c16a
#define hw_def_hw_stat_t__c16a		, _hw_statt_c16a

#define _hw_statt_c16a(c,n,i,a,...)	HW_TX(_hw_c16a_stat_t, __VA_ARGS__)

typedef union {
  uint8_t         byte ;
  struct {
    unsigned int  overflow : 1 ;
    unsigned int  output0  : 1 ;
    unsigned int  output1  : 1 ;
    unsigned int  _34      : 2 ;
    unsigned int  input0   : 1 ;
    unsigned int  _76      : 2 ;
  };
} _hw_c16a_stat_t ;

#define _hw_stat_c16a(c,n,i,a)		_hw_c16a_stat( _hw_read_reg(c,n,i,a, ifr) )

HW_INLINE _hw_c16a_stat_t _hw_c16a_stat( uint8_t byte )
{
  _hw_c16a_stat_t	st ;
  st.byte = byte ;
  return st ;
}
