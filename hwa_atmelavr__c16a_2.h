
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
  _hwa_begin_reg_p( p, a, _c16a, ccra  );
  _hwa_begin_reg_p( p, a, _c16a, ccrb  );
  _hwa_begin_reg_p( p, a, _c16a, ccrc  );
  _hwa_begin_reg_p( p, a, _c16a, count );
  _hwa_begin_reg_p( p, a, _c16a, icr   );
  _hwa_begin_reg_p( p, a, _c16a, ocra  );
  _hwa_begin_reg_p( p, a, _c16a, ocrb  );
  _hwa_begin_reg_p( p, a, _c16a, imsk  );
  _hwa_begin_reg_p( p, a, _c16a, ifr   );

  p->clock           = 0xFF ;
  p->countmode       = 0xFF ;
  p->top             = 0xFF ;
  p->overflow        = 0xFF ;
  p->compare0_update = 0xFF ;
  p->compare0_output = 0xFF ;
  p->compare1_update = 0xFF ;
  p->compare1_output = 0xFF ;
  p->icr_input       = 0xFF ;
  p->icr_edge        = 0xFF ;
  p->icr_filter      = 0xFF ;
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
  _hwa_commit_reg_p( p, _c16a, ccra  );
  _hwa_commit_reg_p( p, _c16a, ccrb  );
  _hwa_commit_reg_p( p, _c16a, ccrc  );
  _hwa_commit_reg_p( p, _c16a, count );
  _hwa_commit_reg_p( p, _c16a, icr   );
  _hwa_commit_reg_p( p, _c16a, ocra  );
  _hwa_commit_reg_p( p, _c16a, ocrb  );
  _hwa_commit_reg_p( p, _c16a, imsk  );
  _hwa_commit_reg_p( p, _c16a, ifr   );
}


/*	16-bit counter class '_c16a'
 */
#define hw_c16a_countmode_loop_up		, 1
#define hw_c16a_countmode_loop_updown		, 2

#define hw_c16a_top_fixed_0xFF			, 1
#define hw_c16a_top_fixed_0x1FF			, 2
#define hw_c16a_top_fixed_0x3FF			, 3
#define hw_c16a_top_fixed_0xFFFF		, 4
#define hw_c16a_top_max				, 4
#define hw_c16a_top_capture0			, 5
#define hw_c16a_top_compare0			, 6

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
#define hw_mthd_hwa_config__c16a		, _hwa_config__c16a

#define _hwa_config__c16a(c,n,i,a, ...)					\
  do { HW_G2(_hwa_config__c16a_xclock,HW_IS(clock,__VA_ARGS__))(n,__VA_ARGS__,) } while(0)

#define _hwa_config__c16a_xclock_0(n,...)				\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_xclock_1(n,_clock_,...)			\
  HW_G2(_hwa_config__c16a_vclock,HW_IS(,hw_c16a_clock_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vclock_0(n,...)				\
  HW_ERR( "`clock` can be `none`, `syshz`, `syshz_div_8`, "		\
	  "`syshz_div_64`, `syshz_div_256`, `syshz_div_1024`, "		\
	  "`ext_falling`, `ext_rising`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_vclock_1(n,zclock,...)			\
  hwa->n.clock = HW_A1(hw_c16a_clock_##zclock);				\
  HW_G2(_hwa_config__c16a_xmode,HW_IS(countmode,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_xmode_0(n,...)				\
  HW_ERR("expected `countmode` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_xmode_1(n,_countmode_,...)			\
  HW_G2(_hwa_config__c16a_vmode,HW_IS(,hw_c16a_countmode_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vmode_0(n,...)				\
  HW_ERR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid mode option.")

#define _hwa_config__c16a_vmode_1(n,vmode,...)				\
  hwa->n.countmode = HW_A1(hw_c16a_countmode_##vmode);			\
  HW_G2(_hwa_config__c16a_xbottom,HW_IS(bottom,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_xbottom_1(n,_bottom_,...)			\
  HW_G2(_hwa_config__c16a_vbottom,HW_IS(0,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vbottom_0(n,bottom,...)	\
  HW_ERR("bottom must be `0`, not `" #bottom "`.")

#define _hwa_config__c16a_vbottom_1(n,bottom,...)	\
  _hwa_config__c16a_xbottom_0(n,__VA_ARGS__)

#define _hwa_config__c16a_xbottom_0(n,...)				\
  HW_G2(_hwa_config__c16a_xtop,HW_IS(top,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_xtop_0(n,...)				\
  HW_ERR("expected `top` instead of `" #__VA_ARGS__ "`.")

#define _hwa_config__c16a_xtop_1(n,kw,...)				\
  HW_G2(_hwa_config__c16a_vtop,HW_IS(,hw_c16a_top_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vtop_0(n,...)					\
  HW_ERR("`top` can be `fixed_0xFF`, `fixed_0x1FF`, `fixed_0x3FF`, "	\
	 "`fixed_0xFFFF`, `register_capture`, or `register_compare_a`," \
	 " but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_vtop_1(n,v,...)				\
  hwa->n.top = HW_A1(hw_c16a_top_##v);					\
  HW_G2(_hwa_config__c16a_xoverflow,HW_IS(overflow,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_xoverflow_1(n,kw,...)				\
    HW_G2(_hwa_config__c16a_voverflow, HW_IS(,hw_counter_overflow_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_voverflow_0(n,...)				\
  HW_ERR("optionnal parameter `overflow` must be `at_bottom`, "		\
	 "`at_top, or `at_max`, but `not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_voverflow_1(n,v,...)				\
    HW_TX(hwa->n.overflow = HW_A1(hw_counter_overflow_##v),__VA_ARGS__);

#define _hwa_config__c16a_xoverflow_0(n,...)	\
  HW_TX(,__VA_ARGS__)


/*	Solve the configuration of the counter with its compare and capture units
 */
HW_INLINE void __hwa_solve__c16a ( hwa_t *hwa __attribute__((unused)), hwa_c16a_t *p )
{
  if ( p->clock == 0xFF )
    return ;

  /*  Clock setting
   */
  _hwa_write_creg( p, _c16a, cs, p->clock );


  /*  Default config for overflow
   */
  uint8_t overflow = p->overflow ;
  if ( overflow == 0xFF && p->top == HW_A1(hw_c16a_top_compare0) ) {
    if ( p->countmode == HW_A1(hw_c16a_countmode_loop_up) )
      overflow = HW_A1(hw_counter_overflow_at_top);
    else /* if ( p->countmode == HW_A1(hw_c16a_countmode_loop_up) ) */
      overflow = HW_A1(hw_counter_overflow_at_bottom);
  }

  /*  Compare update setting
   */
  uint8_t compare_update = 0xFF ;
  if ( p->compare0_update != 0xFF && p->compare1_update != 0xFF
       && p->compare0_update != p->compare1_update )
    HWA_ERR("optionnal parameter 'update' of class _c16a counter must be " \
	    "'immediately'.");
  compare_update = p->compare0_update ;

  /* Mode WGM   Operation                     COUNTMODE    TOP     OCR  OVF  OCF  ICF  OCA                OCB
   *                                                               TOP
   *                                                               UPD
   *
   *   0  0000  Normal                        LOOP_UP      0xFFFF  IMM  MAX            CoM,SoM,ToM        CoM,SoM,ToM
   *   4  0100  CTC (Clear Timer on Match)    LOOP_UP      ocra    IMM  MAX  TOP                          CoM,SoM,ToM
   *  12  1100  CTC (Clear Timer on Match)    LOOP_UP      icr     IMM  MAX       TOP  CoM,SoM,ToM        CoM,SoM,ToM
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

  /*	Determine WGM
   */
  uint8_t wgm = 0xFF ;
  if ( p->countmode == HW_A1(hw_c16a_countmode_loop_up)
       && p->top == HW_A1(hw_c16a_top_compare0)
       && overflow == HW_A1(hw_counter_overflow_at_top) )
    wgm = 15 ;
  else    
    if ( p->countmode == HW_A1(hw_c16a_countmode_loop_up) ) {
      if ( p->top == HW_A1(hw_c16a_top_fixed_0xFFFF) )
	wgm = 0 ;
      else if (p->top == HW_A1(hw_c16a_top_fixed_0xFF) )
	wgm = 5 ;
      else if (p->top == HW_A1(hw_c16a_top_fixed_0x1FF) )
	wgm = 6 ;
      else if (p->top == HW_A1(hw_c16a_top_fixed_0x3FF) )
	wgm = 7 ;
      else if (p->top == HW_A1(hw_c16a_top_compare0) ) {
	if ( compare_update == HW_A1(hw_ocu_update_immediately)
	     || overflow == HW_A1(hw_counter_overflow_at_top)
	     || p->compare1_output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     || p->compare1_output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match))
	  wgm = 15 ;
	else 
	  wgm = 4 ;
      }
      else /* if (p->top == HW_A1(hw_c16a_top_capture0) ) */ {
	if (compare_update == HW_A1(hw_ocu_update_at_top)
	    || overflow == HW_A1(hw_counter_overflow_at_top)
	    || p->compare0_output == HW_A1(hw_ocu_output_toggle_on_match)
	    || p->compare0_output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	    || p->compare0_output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match)
	    || p->compare1_output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	    || p->compare1_output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match))
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
      else if (p->top == HW_A1(hw_c16a_top_compare0) ) {
	if (compare_update == HW_A1(hw_ocu_update_at_bottom)
	    || p->compare1_output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	    || p->compare1_output == HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down))
	  wgm = 9 ;
	else 
	  wgm = 11 ;
      }
      else /* if (p->top == HW_A1(hw_c16a_top_capture0) ) */ {
	if (compare_update == HW_A1(hw_ocu_update_at_bottom)
	    || p->compare0_output == HW_A1(hw_ocu_output_toggle_on_match)
	    || p->compare0_output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	    || p->compare0_output == HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down)
	    || p->compare1_output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	    || p->compare1_output == HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down))
	  wgm = 8 ;
	else 
	  wgm = 10 ;
      }
    }
      
  if (wgm != 0xFF)
    _hwa_write_creg( p, _c16a, wgm, wgm );
  else {
    HWA_ERR("WGM value could not be solved for _c16a class counter.");
    return ;
  }

  /*	Solve the configuration of compare output A
   */
  if ( p->compare0_output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( p->compare0_output == HW_A1(hw_ocu_output_disconnected) )
      mode = 0 ;
    else if ( p->compare0_output == HW_A1(hw_ocu_output_toggle_on_match) )
      mode = 1 ;
    else if ( p->compare0_output == HW_A1(hw_ocu_output_clear_on_match)
	      || p->compare0_output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	      || p->compare0_output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    _hwa_write_creg( p, _c16a, coma, mode );
  }

  /*  Solve the configuration of compare output B
   */
  if ( p->compare1_output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( p->compare1_output == HW_A1(hw_ocu_output_disconnected) )
      mode = 0 ;
    else if ( p->compare1_output == HW_A1(hw_ocu_output_toggle_on_match) )
      mode = 1 ;
    else if ( p->compare1_output == HW_A1(hw_ocu_output_clear_on_match)
	      || p->compare1_output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	      || p->compare1_output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    _hwa_write_creg( p, _c16a, comb, mode );
  }

  /*	Solve the configuration of the capture input
   */
  if ( p->icr_input != 0xFF ) {
    _hwa_write_creg( p, _c16a, acic, p->icr_input-1 );
    _hwa_write_creg( p, _c16a, ices, p->icr_edge-1 );
    _hwa_write_creg( p, _c16a, icnc, p->icr_filter );
  }


  /*	Check the validity of the configuration
   */
  if ( p->countmode != 0xFF || p->compare0_output != 0xFF || p->compare1_output != 0xFF ) {

    if ( p->countmode == 0xFF ) {
      HWA_ERR("configuration of counter is required.");
      return ;
    }

    /*	Check compare output A
     */
    if ( p->compare0_output != 0xFF ) {
      if ( wgm==0 || wgm==12 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_toggle_on_match) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'clear_on_match', 'set_on_match', or "
		  "'toggle_on_match'.");
      }
      else if ( wgm==5 || wgm==6 || wgm==7 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==14 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 || wgm==2 || wgm==3 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
      else if ( wgm==8 || wgm==10 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
      //    else if ( p->top == HW_A1(hw_c16a_top_compare0)
      else if ( p->compare0_output ) {
	HWA_ERR("can not use of `compare_a` as both top value and output of class _c16a counter.");
      }
    }

    /*	Check compare output B
     */
    if ( p->compare1_output != 0xFF ) {
      if ( wgm==0 || wgm==4 || wgm==12 ) {
	if ( p->compare1_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare1_output != HW_A1(hw_ocu_output_clear_on_match)
	     && p->compare1_output != HW_A1(hw_ocu_output_set_on_match)
	     && p->compare1_output != HW_A1(hw_ocu_output_toggle_on_match) )
	  HWA_ERR("compare output B of class _c16a counter mode must be "
		  "'disconnected', 'clear_on_match', 'set_on_match', or "
		  "'toggle_on_match'.");
      }
      else if ( wgm==5 || wgm==6 || wgm==7 || wgm==14 || wgm==15 ) {
	if ( p->compare1_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare1_output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->compare1_output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output B of class _c16a counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else /* if ( wgm==1 || wgm==2 || wgm==3 || wgm==8 || wgm==9 || wgm==10 || wgm==11 ) */ {
	if ( p->compare1_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare1_output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->compare1_output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output B of class _c16a counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
    }

    /*	Check compare update
     */
    if ( compare_update != 0xFF ) {
      if ( wgm==0 || wgm==4 || wgm==12 ) {
	if ( compare_update != HW_A1(hw_ocu_update_immediately) )
	  HWA_ERR("optionnal parameter 'update' of class _c16a counter must be "\
		  "'immediately'.");
      }
      else if ( wgm==8 || wgm==9 ) {
	if ( compare_update != HW_A1(hw_ocu_update_at_bottom) )
	  HWA_ERR("optionnal parameter 'update' of class _c16a counter must be "
		  "'at_bottom'.");
      }
      else
	if( compare_update != HW_A1(hw_ocu_update_at_top) )
	  HWA_ERR("optionnal parameter 'update' of class _c16a counter must be "
		  "'at_top'.");
    }

    /*	Overflow
     */
    if ( overflow != 0xFF ) {
      if ( (wgm==0 || wgm==4 || wgm==12) ) {
	if ( overflow != HW_A1(hw_counter_overflow_at_max) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be "
		  "'at_max'.");
      }
      else if ( (wgm==5 || wgm==6 || wgm==7 || wgm==14 || wgm==15) ) {
	if ( overflow != HW_A1(hw_counter_overflow_at_top) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be "
		  "'at_top'.");
      }
      else if ( overflow != HW_A1(hw_counter_overflow_at_bottom) )
	HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be "
		"'at_bottom'.");
    }
  }
}


/*	Read/write the 'count' register of a _c16a counter
 */
#define hw_mthd_hw_read__c16a		, _hw_read_c16a
#define _hw_read_c16a(c,n,i,a,...)	HW_TX(_hw_read_reg(c,n,i,a,count),__VA_ARGS__)

#define hw_mthd_hw_write__c16a		, _hw_write_c16a
#define _hw_write_c16a(c,n,i,a,v)	_hw_write_reg(c,n,i,a,count,v)

#define hw_mthd_hwa_write__c16a		, _hwa_write_c16a
#define _hwa_write_c16a(c,n,i,a,v)	_hwa_write_reg(c,n,i,a,count,v)

#define hw_mthd_hw_clear__c16a		, _hw_clear_c16a
#define _hw_clear_c16a(c,n,i,a,...)	HW_TX(_hw_write_reg(c,n,i,a,count,0),__VA_ARGS__)

#define hw_mthd_hwa_clear__c16a		, _hwa_clear_c16a
#define _hwa_clear_c16a(c,n,i,a)	_hwa_write_reg(c,n,i,a,count,0)


/*  Status
 *
 *	hw_stat_t(...) declares the structure that holds the status
 *	hw_stat(...) reads and returns the status
 *
 *	The only flag that is available is the irq flag.
 */
#define hw_mthd_hw_stat__c16a		, _hw_stat_c16a
#define hw_mthd_hw_stat_t__c16a		, _hw_statt_c16a

#define _hw_statt_c16a(c,n,i,a,...)	HW_TX(_hw_c16a_stat_t, __VA_ARGS__)

typedef union {
  uint8_t         byte ;
  struct {
    unsigned int  overflow : 1 ;
    unsigned int  compare0 : 1 ;
    unsigned int  compare1 : 1 ;
    unsigned int  _34      : 2 ;
    unsigned int  capture0 : 1 ;
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
