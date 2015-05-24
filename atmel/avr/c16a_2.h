
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	Atmel AVR 16-bit timer-counter model 'a'
 *
 *	Used in:	ATtinyX4 counter1
 *			ATmegaX8 counter1 ?
 */

HW_INLINE void __hwa_begin__c16a ( hwa_c16a_t *p, intptr_t a )
{
  _hwa_begin_reg_p( p, a, _c16a, ccra     );
  _hwa_begin_reg_p( p, a, _c16a, ccrb     );
  _hwa_begin_reg_p( p, a, _c16a, ccrc     );
  _hwa_begin_reg_p( p, a, _c16a, count    );
  _hwa_begin_reg_p( p, a, _c16a, capture0 );
  _hwa_begin_reg_p( p, a, _c16a, compare0 );
  _hwa_begin_reg_p( p, a, _c16a, compare1 );
  _hwa_begin_reg_p( p, a, _c16a, imsk     );
  _hwa_begin_reg_p( p, a, _c16a, ifr      );

  p->config.clock           = 0xFF ;
  p->config.countmode       = 0xFF ;
  p->config.top             = 0xFF ;
  p->config.overflow        = 0xFF ;
  p->config.compare0.update = 0xFF ;
  p->config.compare0.output = 0xFF ;
  p->config.compare1.update = 0xFF ;
  p->config.compare1.output = 0xFF ;
  p->config.capture0.input  = 0xFF ;
  p->config.capture0.edge   = 0xFF ;
  p->config.capture0.filter = 0xFF ;
}


HW_INLINE void __hwa_init__c16a ( hwa_c16a_t *p )
{
  _hwa_set_r8(  &p->ccra,  0x00 );
  _hwa_set_r8(  &p->ccrb,  0x00 );
  _hwa_set_r8(  &p->ccrc,  0x00 );
  _hwa_set_r16( &p->count, 0x00 );
  _hwa_set_r16( &p->capture0,   0x00 );
  _hwa_set_r16( &p->compare0,  0x00 );
  _hwa_set_r16( &p->compare1,  0x00 );
  _hwa_set_r8(  &p->imsk,  0x00 );
  _hwa_set_r8(  &p->ifr,   0x00 );
}


HW_INLINE void __hwa_commit__c16a ( hwa_t *hwa, hwa_c16a_t *p )
{
  _hwa_commit_reg_p( p, _c16a, ccra  );
  _hwa_commit_reg_p( p, _c16a, ccrb  );
  _hwa_commit_reg_p( p, _c16a, ccrc  );
  _hwa_commit_reg_p( p, _c16a, count );
  _hwa_commit_reg_p( p, _c16a, capture0   );
  _hwa_commit_reg_p( p, _c16a, compare0  );
  _hwa_commit_reg_p( p, _c16a, compare1  );
  _hwa_commit_reg_p( p, _c16a, imsk  );
  _hwa_commit_reg_p( p, _c16a, ifr   );
}


/**
 * @page atmelavr_c16a
 * @section atmelavr_c16a_config Configuring the counter
 *
 * Note: if `overflow` is not stated, HWA will select an acceptable value
 * according to the configuration of the comparison units found in the HWA
 * context. If `overflow` is stated, HWA will check the validity of its value.
 *
 * @code
 * hwa_config( COUNTER,
 *
 *             //  How the counter is clocked
 *             //
 *             clock,       none                // No clock, the counter is stopped
 *                        | syshz               // CPU clock, frequency
 *                        | syshz_div_1         // CPU clock, frequency
 *                        | syshz_div_8         // CPU clock, frequency / 8
 *                        | syshz_div_64        // CPU clock, frequency / 64
 *                        | syshz_div_256       // CPU clock, frequency / 256
 *                        | syshz_div_1024      // CPU clock, frequency / 1024
 *                        | syshz_ext_rising    // External input, rising edge
 *                        | syshz_ext_falling,  // External input, falling edge
 *
 *             //  How does this counter count
 *             //
 *             countmode,   loop_up             // Count up and loop
 *                        | loop_updown,        // Count up and down alternately
 *
 *             //  Class _c16a counters count from 0
 *             //
 *            [bottom,      0, ]
 *
 *             //  The maximum value the counter reaches (the default is `max`)
 *             //
 *            [top,         fixed_0xFF          // Hardware fixed value 0x00FF
 *                        | fixed_0x1FF         // Hardware fixed value 0x01FF
 *                        | fixed_0x3FF         // Hardware fixed value 0x03FF
 *                        | fixed_0xFFFF        // Hardware fixed value 0xFFFF
 *                        | max                 // Hardware fixed value 0xFFFF
 *                        | compare0            // Value stored in the compare0 unit
 *                        | capture0,]          // Value stored in the capture0 unit
 *
 *             //  When the overflow flag is set
 *             //
 *            [overflow,    at_bottom           // When the counter resets to bottom
 *                        | at_top              // When the counter reaches the top value
 *                        | at_max ]            // When the counter reaches its max value
 *           );
 * @endcode
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

#define hw_c16a_overflow_at_bottom		, 0
#define hw_c16a_overflow_at_top			, 1
#define hw_c16a_overflow_at_max			, 2


/*	Configure counter unit
 */
#define _hw_mthd_hwa_config__c16a		, _hwa_config__c16a

#define _hwa_config__c16a(p,i,a, ...)					\
  do { HW_G2(_hwa_config__c16a_xclock,HW_IS(clock,__VA_ARGS__))(p,__VA_ARGS__) } while(0)

#define _hwa_config__c16a_xclock_0(n,...)				\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_xclock_1(n,_clock_,...)			\
  HW_G2(_hwa_config__c16a_vclock,HW_IS(,hw_c16a_clock_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vclock_0(n,...)				\
  HW_ERR( "`clock` can be `none`, `syshz`, `syshz_div_8`, "		\
	  "`syshz_div_64`, `syshz_div_256`, `syshz_div_1024`, "		\
	  "`ext_falling`, `ext_rising`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_vclock_1(n,zclock,...)			\
  hwa->n.config.clock = HW_A1(hw_c16a_clock_##zclock);				\
  HW_G2(_hwa_config__c16a_xmode,HW_IS(countmode,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_xmode_0(n,...)				\
  HW_ERR("expected `countmode` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_xmode_1(n,_countmode_,...)			\
  HW_G2(_hwa_config__c16a_vmode,HW_IS(,hw_c16a_countmode_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vmode_0(n,...)				\
  HW_ERR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid mode option.")

#define _hwa_config__c16a_vmode_1(n,vmode,...)				\
  hwa->n.config.countmode = HW_A1(hw_c16a_countmode_##vmode);			\
  HW_G2(_hwa_config__c16a_xbottom,HW_IS(bottom,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_xbottom_1(n,_bottom_,...)			\
  HW_G2(_hwa_config__c16a_vbottom,HW_IS(0,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vbottom_0(n,bottom,...)	\
  HW_ERR("bottom must be `0`, not `" #bottom "`.")

#define _hwa_config__c16a_vbottom_1(n,bottom,...)	\
  _hwa_config__c16a_xbottom_0(n,__VA_ARGS__)

#define _hwa_config__c16a_xbottom_0(n,...)				\
  HW_G2(_hwa_config__c16a_xtop,HW_IS(top,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_xtop_1(n,kw,...)				\
  HW_G2(_hwa_config__c16a_vtop,HW_IS(,hw_c16a_top_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_vtop_0(n,...)					\
  HW_ERR("`top` can be `fixed_0xFF`, `fixed_0x1FF`, `fixed_0x3FF`, "	\
	 "`fixed_0xFFFF`, `max`, `capture0`, or `compare0`,"		\
	 " but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_vtop_1(n,v,...)				\
  hwa->n.config.top = HW_A1(hw_c16a_top_##v);					\
  HW_G2(_hwa_config__c16a_xoverflow,HW_IS(overflow,__VA_ARGS__))(n,__VA_ARGS__)

/* #define _hwa_config__c16a_xtop_0(n,...)				\ */
/*   HW_ERR("expected `top` instead of `" #__VA_ARGS__ "`.") */

#define _hwa_config__c16a_xtop_0(o,...)				\
  HW_G2(_hwa_config__c16a_xoverflow,HW_IS(overflow,__VA_ARGS__))(o,__VA_ARGS__)

#define _hwa_config__c16a_xoverflow_1(n,kw,...)				\
    HW_G2(_hwa_config__c16a_voverflow, HW_IS(,hw_c16a_overflow_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_config__c16a_voverflow_0(n,...)				\
  HW_ERR("optionnal parameter `overflow` must be `at_bottom`, "		\
	 "`at_top, or `at_max`, but `not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config__c16a_voverflow_1(n,v,...)				\
    HW_TX(hwa->n.config.overflow = HW_A1(hw_c16a_overflow_##v),__VA_ARGS__);

#define _hwa_config__c16a_xoverflow_0(n,...)	\
  HW_TX(,__VA_ARGS__)


/*	Solve the configuration of the counter with its compare and capture units
 */
HW_INLINE void __hwa_solve__c16a ( hwa_t *hwa __attribute__((unused)), hwa_c16a_t *p )
{
  p->solved.cs   = 0xFF ;
  p->solved.wgm  = 0xFF ;
  p->solved.coma = 0xFF ;
  p->solved.comb = 0xFF ;
  p->solved.acic = 0xFF ;
  p->solved.ices = 0xFF ;
  p->solved.icnc = 0xFF ;

  if ( p->config.clock == 0xFF )
    return ;

  /*  Clock setting
   */
  p->solved.cs = p->config.clock ;

  /*  Default config for top
   */
  if ( p->config.top == 0xFF )
    p->config.top = HW_A1(hw_c16a_top_max);

  /*  Default config for overflow
   */
  uint8_t overflow = p->config.overflow ;
  if ( overflow == 0xFF && p->config.top == HW_A1(hw_c16a_top_compare0) ) {
    if ( p->config.countmode == HW_A1(hw_c16a_countmode_loop_up) )
      overflow = HW_A1(hw_c16a_overflow_at_top);
    else /* if ( p->config.countmode == HW_A1(hw_c16a_countmode_loop_up) ) */
      overflow = HW_A1(hw_c16a_overflow_at_bottom);
  }

  /*  Compare update setting
   */
  uint8_t compare_update = 0xFF ;
  if ( p->config.compare0.update != 0xFF && p->config.compare1.update != 0xFF
       && p->config.compare0.update != p->config.compare1.update )
    HWA_ERR("optionnal parameter 'update' of class _c16a counter must be " \
	    "'immediately'.");
  compare_update = p->config.compare0.update ;

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
  if ( p->config.countmode == HW_A1(hw_c16a_countmode_loop_up)
       && p->config.top == HW_A1(hw_c16a_top_compare0)
       && overflow == HW_A1(hw_c16a_overflow_at_top) )
    wgm = 15 ;
  else    
    if ( p->config.countmode == HW_A1(hw_c16a_countmode_loop_up) ) {
      if ( p->config.top == HW_A1(hw_c16a_top_fixed_0xFFFF) )
	wgm = 0 ;
      else if (p->config.top == HW_A1(hw_c16a_top_fixed_0xFF) )
	wgm = 5 ;
      else if (p->config.top == HW_A1(hw_c16a_top_fixed_0x1FF) )
	wgm = 6 ;
      else if (p->config.top == HW_A1(hw_c16a_top_fixed_0x3FF) )
	wgm = 7 ;
      else if (p->config.top == HW_A1(hw_c16a_top_compare0) ) {
	if ( compare_update == HW_A1(hw_ocu_update_immediately)
	     || overflow == HW_A1(hw_c16a_overflow_at_top)
	     || p->config.compare1.output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     || p->config.compare1.output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match))
	  wgm = 15 ;
	else 
	  wgm = 4 ;
      }
      else /* if (p->top == HW_A1(hw_c16a_top_capture0) ) */ {
	if (compare_update == HW_A1(hw_ocu_update_at_top)
	    || overflow == HW_A1(hw_c16a_overflow_at_top)
	    || p->config.compare0.output == HW_A1(hw_ocu_output_toggle_on_match)
	    || p->config.compare0.output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	    || p->config.compare0.output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match)
	    || p->config.compare1.output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	    || p->config.compare1.output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match))
	  wgm = 14 ;
	else 
	  wgm = 12 ;
      }
    }
    else {
      if (p->config.top == HW_A1(hw_c16a_top_fixed_0xFF) )
	wgm = 1 ;
      else if (p->config.top == HW_A1(hw_c16a_top_fixed_0x1FF) )
	wgm = 2 ;
      else if (p->config.top == HW_A1(hw_c16a_top_fixed_0x3FF) )
	wgm = 3 ;
      else if (p->config.top == HW_A1(hw_c16a_top_compare0) ) {
	if (compare_update == HW_A1(hw_ocu_update_at_bottom)
	    || p->config.compare1.output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	    || p->config.compare1.output == HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down))
	  wgm = 9 ;
	else 
	  wgm = 11 ;
      }
      else /* if (p->top == HW_A1(hw_c16a_top_capture0) ) */ {
	if (compare_update == HW_A1(hw_ocu_update_at_bottom)
	    || p->config.compare0.output == HW_A1(hw_ocu_output_toggle_on_match)
	    || p->config.compare0.output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	    || p->config.compare0.output == HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down)
	    || p->config.compare1.output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	    || p->config.compare1.output == HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down))
	  wgm = 8 ;
	else 
	  wgm = 10 ;
      }
    }
      
  if (wgm != 0xFF)
    p->solved.wgm = wgm ;
  else {
    HWA_ERR("WGM value could not be solved for _c16a class counter.");
    return ;
  }

  /*	Solve the configuration of compare output A
   */
  if ( p->config.compare0.output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( p->config.compare0.output == HW_A1(hw_ocu_output_disconnected) )
      mode = 0 ;
    else if ( p->config.compare0.output == HW_A1(hw_ocu_output_toggle_on_match) )
      mode = 1 ;
    else if ( p->config.compare0.output == HW_A1(hw_ocu_output_clear_on_match)
	      || p->config.compare0.output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	      || p->config.compare0.output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    p->solved.coma = mode ;
  }

  /*  Solve the configuration of compare output B
   */
  if ( p->config.compare1.output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( p->config.compare1.output == HW_A1(hw_ocu_output_disconnected) )
      mode = 0 ;
    else if ( p->config.compare1.output == HW_A1(hw_ocu_output_toggle_on_match) )
      mode = 1 ;
    else if ( p->config.compare1.output == HW_A1(hw_ocu_output_clear_on_match)
	      || p->config.compare1.output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	      || p->config.compare1.output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    p->solved.comb = mode ;
  }

  /*	Solve the configuration of the capture input
   */
  if ( p->config.capture0.input != 0xFF ) {
    p->solved.acic = p->config.capture0.input-1 ;
    p->solved.ices = p->config.capture0.edge-1 ;
    if ( p->config.capture0.filter != 0xFF )
      p->solved.icnc = p->config.capture0.filter ;
  }


  /*	Check the validity of the configuration
   */
  if ( p->config.countmode != 0xFF || p->config.compare0.output != 0xFF || p->config.compare1.output != 0xFF ) {

    if ( p->config.countmode == 0xFF ) {
      HWA_ERR("configuration of counter is required.");
      return ;
    }

    /*	Check compare output A
     */
    if ( p->config.compare0.output != 0xFF ) {
      if ( wgm==0 || wgm==12 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_toggle_on_match) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'clear_on_match', 'set_on_match', or "
		  "'toggle_on_match'.");
      }
      else if ( wgm==5 || wgm==6 || wgm==7 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==14 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 || wgm==2 || wgm==3 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
      else if ( wgm==8 || wgm==10 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c16a counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
      //    else if ( p->top == HW_A1(hw_c16a_top_compare0)
      else if ( p->config.compare0.output ) {
	HWA_ERR("can not use of `compare_a` as both top value and output of class _c16a counter.");
      }
    }

    /*	Check compare output B
     */
    if ( p->config.compare1.output != 0xFF ) {
      if ( wgm==0 || wgm==4 || wgm==12 ) {
	if ( p->config.compare1.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_clear_on_match)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_set_on_match)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_toggle_on_match) )
	  HWA_ERR("compare output B of class _c16a counter mode must be "
		  "'disconnected', 'clear_on_match', 'set_on_match', or "
		  "'toggle_on_match'.");
      }
      else if ( wgm==5 || wgm==6 || wgm==7 || wgm==14 || wgm==15 ) {
	if ( p->config.compare1.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output B of class _c16a counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else /* if ( wgm==1 || wgm==2 || wgm==3 || wgm==8 || wgm==9 || wgm==10 || wgm==11 ) */ {
	if ( p->config.compare1.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
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
	if ( overflow != HW_A1(hw_c16a_overflow_at_max) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c16a counter must be "
		  "'at_max'.");
      }
      else if ( (wgm==5 || wgm==6 || wgm==7 || wgm==14 || wgm==15) ) {
	if ( overflow != HW_A1(hw_c16a_overflow_at_top) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c16a counter must be "
		  "'at_top'.");
      }
      else if ( overflow != HW_A1(hw_c16a_overflow_at_bottom) )
	HWA_ERR("optionnal parameter 'overflow' of class _c16a counter must be "
		"'at_bottom'.");
    }
  }
}


/**
 * @page atmelavr_c16a
 * @section atmelavr_c16a_read Getting the value of the counter
 *
 * @code
 * hw_read( COUNTER );
 * @endcode
 */
#define _hw_mthd_hw_read__c16a		, _hw_read_c16a
#define _hw_read_c16a(p,i,a,...)	HW_TX(_hw_read_reg(p,count),__VA_ARGS__)


/**
 * @page atmelavr_c16a
 * @section atmelavr_c16a_write Setting the value of the counter
 *
 * @code
 * hw/hwa_write( COUNTER, 42 );
 * @endcode
 * @code
 * hw/hwa_write_reg( COUNTER, count, 42 );
 * @endcode
 */
#define _hw_mthd_hw_write__c16a		, _hw_write_c16a
#define _hw_write_c16a(o,i,a,v,...)	HW_TX(_hw_write_reg(o,count,v),__VA_ARGS__)

#define _hw_mthd_hwa_write__c16a	, _hwa_write_c16a
#define _hwa_write_c16a(o,i,a,v)	_hwa_write_reg(o,count,v)


/**
 * @page atmelavr_c16a
 * @section atmelavr_c16a_clear Clearing the counter (setting the value to 0)
 *
 * Note: this does not reset the prescaler.
 *
 * @code
 * hw/hwa_clear( COUNTER );
 * @endcode
 * @code
 * hw/hwa_write_reg( COUNTER, count, 0 );
 * @endcode
 */
#define _hw_mthd_hw_clear__c16a		, _hw_clear_c16a
#define _hw_clear_c16a(o,i,a,...)	HW_TX(_hw_write_reg(o,count,0),__VA_ARGS__)

#define _hw_mthd_hwa_clear__c16a	, _hwa_clear_c16a
#define _hwa_clear_c16a(o,i,a)		_hwa_write_reg(o,count,0)


/**
 * @page atmelavr_c16a
 * @section atmelavr_c16a_stat Getting the status of the counter
 *
 * Available flags are:
 * * overflow
 * * compare0
 * * compare1
 * * capture0
 *
 * These flags correspond to the interrupt requests the counter can
 * trigger.
 *
 * @code
 * //  Create a structure to receive the counter status
 * //
 * hw_stat_t(COUNTER) st ;
 *
 * //  Copy the counter status to the structure
 * //
 * st = hw_stat( COUNTER );
 *
 * //  Process the overflow flag
 * //
 * if ( st.overflow ) {
 *   hw_clear_irq( COUNTER, overflow );
 *   n_overflows++ ;
 * }
 * @endcode
 *
 * @code
 * //  Process the overflow flag
 * //
 * if ( hw_stat( COUNTER ).overflow ) {
 *   hw_clear_irq( COUNTER, overflow );
 *   n_overflows++ ;
 * }
 * @endcode
 */
#define _hw_mthd_hw_stat__c16a		, _hw_stat_c16a
#define _hw_mthd_hw_stat_t__c16a	, _hw_statt_c16a

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

#define _hw_stat_c16a(p,i,a,...)	HW_TX(_hw_c16a_stat(_hw_read_reg(p, ifr)), __VA_ARGS__)

HW_INLINE _hw_c16a_stat_t _hw_c16a_stat( uint8_t byte )
{
  _hw_c16a_stat_t	st ;
  st.byte = byte ;
  return st ;
}


/**
 * @page atmelavr_c16a
 * <br>
 */
