
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit counter
 */

/**
 * @page atmelavr_c16a
 * @section atmelavr_c16a_config Configuration
 *
 * __Note__: if the optionnal argument `overflow` is not stated, HWA will select
 * an acceptable value according to the configuration of the compare units found
 * in the HWA context. If `overflow` is stated, HWA will check the validity of
 * its value.
 *
 * @code
 * hwa_config( COUNTER_NAME,
 *
 *             //  How the counter is clocked
 *             //
 *             clock,       none                        // No clock, the counter is stopped
 *                        | prescaler_output(     0     // No clock, the counter is stopped
 *                                           |    1     // System clock
 *                                           |    8     // System clock divided by 8
 *                                           |   64     // System clock divided by 64
 *                                           |  256     // System clock divided by 256
 *                                           | 1024 )   // System clock divided by 1024
 *                        | ext_rising                  // External input, rising edge
 *                        | ext_falling,                // External input, falling edge
 *
 *             //  How does this counter count
 *             //
 *             countmode,   loop_up                     // Count up and loop
 *                        | loop_updown,                // Count up and down alternately
 *
 *             //  Class _c16a counters all count from 0
 *             //
 *           [ bottom,      0, ]
 *
 *             //  The maximum value the counter reaches (the default is `max`)
 *             //
 *           [ top,         fixed_0xFF                  // Hardware fixed value 0x00FF
 *                        | fixed_0x1FF                 // Hardware fixed value 0x01FF
 *                        | fixed_0x3FF                 // Hardware fixed value 0x03FF
 *                        | fixed_0xFFFF                // Hardware fixed value 0xFFFF
 *                        | max                         // Hardware fixed value 0xFFFF
 *                        | compare0                    // Value stored in the compare0 unit
 *                        | capture0,]                  // Value stored in the capture0 unit
 *
 *             //  When the overflow flag is set
 *             //
 *           [ overflow,    at_bottom                   // When the counter resets to bottom
 *                        | at_top                      // When the counter reaches the top value
 *                        | at_max ]                    // When the counter reaches its max value
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__c16a		, _hwa_cfc16a

/*  Mandatory argument `clock`
 *
 *    Add 2 void arguments to the end of the list so that there are always
 *    3 arguments following the last non-void argument.
 */
#define _hw_c16a_clock_none			, 0
#define _hw_c16a_clock_syshz			, 1
#define _hw_c16a_clock_prescaler_output_1	, 1	/* Useful for concat */
#define _hw_c16a_clock_prescaler_output_8	, 2
#define _hw_c16a_clock_prescaler_output_64	, 3
#define _hw_c16a_clock_prescaler_output_256	, 4
#define _hw_c16a_clock_prescaler_output_1024	, 5
#define _hw_c16a_clock_ext_rising		, 6
#define _hw_c16a_clock_ext_falling		, 7
#define _hw_c16a_clock_prescaler_output(x)	HW_G2(_hw_c16a_clock_prescaler_output,x)

#define _hwa_cfc16a(o,i,a, ...)					\
  do { HW_G2(_hwa_cfc16a_kclock,HW_IS(clock,__VA_ARGS__))(o,__VA_ARGS__,,) } while(0)

#define _hwa_cfc16a_kclock_0(o,k,...)				\
  HW_ERR("expected `clock` instead of `" #k "`.")

#define _hwa_cfc16a_kclock_1(o,k,v,...)				\
  HW_G2(_hwa_cfc16a_vclock,HW_IS(,_hw_c16a_clock_##v))(o,v,__VA_ARGS__)

#define _hwa_cfc16a_vclock_0(o,v,...)					\
  HW_ERR( "`clock` can be `none`, "				\
	  "`prescaler_output( 0 | 1 | 8 | 64 | 256 | 1024 )`, "	\
	  "`ext_falling`, `ext_rising`, but not `" #v "`.")

#define _hwa_cfc16a_vclock_1(o,v,k,...)					\
  hwa->o.config.clock = HW_A1(_hw_c16a_clock_##v);				\
  HW_G2(_hwa_cfc16a_kmode,HW_IS(countmode,k))(o,k,__VA_ARGS__)

/*  Optionnal argument `countmode`
 */
#define _hw_c16a_countmode_up_loop		, 1
#define _hw_c16a_countmode_loop_up		, 1
#define _hw_c16a_countmode_updown_loop		, 2
#define _hw_c16a_countmode_loop_updown		, 2

#define _hwa_cfc16a_kmode_0(o,k,...)					\
  HW_ERR("expected `countmode` instead of `" #k "`.")

#define _hwa_cfc16a_kmode_1(o,k,v,...)					\
  HW_G2(_hwa_cfc16a_vmode,HW_IS(,_hw_c16a_countmode_##v))(o,v,__VA_ARGS__)

#define _hwa_cfc16a_vmode_0(o,v,...)					\
  HW_ERR("`countmode` can be `up_loop`, or `updown_loop`, but not `" #v "`.")

#define _hwa_cfc16a_vmode_1(o,v,k,...)					\
  hwa->o.config.countmode = HW_A1(_hw_c16a_countmode_##v);			\
  HW_G2(_hwa_cfc16a_kbottom,HW_IS(bottom,k))(o,k,__VA_ARGS__)

/*  Optionnal argument `bottom`
 */
#define _hwa_cfc16a_kbottom_1(o,k,v,...)		\
  HW_G2(_hwa_cfc16a_vbottom,HW_IS(0,v))(o,v,__VA_ARGS__)

#define _hwa_cfc16a_vbottom_0(o,v,...)	\
  HW_ERR("bottom must be `0`, not `" #v "`.")

#define _hwa_cfc16a_vbottom_1(o,v,k,...)	\
  HW_G2(_hwa_cfc16a_ktop,HW_IS(top,k))(o,k,__VA_ARGS__)

#define _hwa_cfc16a_kbottom_0(o,k,...)				\
  HW_G2(_hwa_cfc16a_ktop,HW_IS(top,k))(o,k,__VA_ARGS__)

/*  Optionnal argument `top`
 */
#define _hw_c16a_top_fixed_0xFF			, 1
#define _hw_c16a_top_fixed_0x1FF			, 2
#define _hw_c16a_top_fixed_0x3FF			, 3
#define _hw_c16a_top_fixed_0xFFFF		, 4
#define _hw_c16a_top_max				, 4
#define _hw_c16a_top_capture0			, 5
#define _hw_c16a_top_compare0			, 6

#define _hwa_cfc16a_ktop_1(o,k,v,...)					\
  HW_G2(_hwa_cfc16a_vtop,HW_IS(,_hw_c16a_top_##v))(o,v,__VA_ARGS__)

#define _hwa_cfc16a_vtop_0(o,v,...)					\
  HW_ERR("`top` can be `fixed_0xFF`, `fixed_0x1FF`, `fixed_0x3FF`, "	\
	 "`fixed_0xFFFF`, `max`, `capture0`, or `compare0`,"		\
	 " but not `" #v "`.")

#define _hwa_cfc16a_vtop_1(o,v,k,...)					\
  hwa->o.config.top = HW_A1(_hw_c16a_top_##v);				\
  HW_G2(_hwa_cfc16a_koverflow,HW_IS(overflow,k))(o,k,__VA_ARGS__)

#define _hwa_cfc16a_ktop_0(o,k,...)					\
  HW_G2(_hwa_cfc16a_koverflow,HW_IS(overflow,k))(o,k,__VA_ARGS__)

/*  Optionnal argument `overflow`
 */
#define _hw_c16a_overflow_at_bottom			, 0
#define _hw_c16a_overflow_at_top			, 1
#define _hw_c16a_overflow_at_max			, 2

#define _hwa_cfc16a_koverflow_1(o,k,v,...)				\
  HW_G2(_hwa_cfc16a_voverflow, HW_IS(,_hw_c16a_overflow_##v))(o,v,__VA_ARGS__)

#define _hwa_cfc16a_voverflow_0(o,v,...)				\
  HW_ERR("optionnal parameter `overflow` can be `at_bottom`, "		\
	 "`at_top, or `at_max`, but `not `" #v "`.")

#define _hwa_cfc16a_voverflow_1(o,v,...)				\
  HW_TX(hwa->o.config.overflow = HW_A1(_hw_c16a_overflow_##v),__VA_ARGS__)

#define _hwa_cfc16a_koverflow_0(o,...)	\
  HW_EOL(__VA_ARGS__)


/**
 * @brief Solve and check the configuration of the counter and its compare units.
 *
 * Writing code for a HW_INLINE function is more comfortable than for a
 * function-like macro but functions can not use object names. So, this
 * function-like macro expands to the HW_INLINE function _hwa_solve_c16a() which
 * uses pointers on objects in the HWA context to compute values to be written
 * into the registers, stores them into the `solve` structure and returns an
 * error code that is processed by _hwa_solve__c16a() which knows the names of
 * the objects and then can put computed registers values into the context, even
 * in the case of external register access, and display accurate error messages.
 */
#define _hwa_solve__c16a( o,i,a )	_hwa_solve__c16a_2( o,		\
							    _hw_rel(o,compare0), \
							    _hw_rel(o,compare1), \
							    _hw_rel(o,capture0) )
#define _hwa_solve__c16a_2(...)		_hwa_solve__c16a_3(__VA_ARGS__)

#define _hwa_solve__c16a_3( o, oc0, oc1, ic0 )				\
  do {									\
    uint8_t r = _hwa_solve_c16a( &hwa->o, &hwa->oc0, &hwa->oc1, &hwa->ic0 ); \
    if ( r == 0 ) {							\
      /*								\
       *  Write solved registers					\
       */								\
      if ( hwa->o.solved.cs != 0xFF ) _hwa_write_reg( o, cs, hwa->o.solved.cs ); \
      if ( hwa->o.solved.wgm != 0xFF ) _hwa_write_reg( o, wgm, hwa->o.solved.wgm ); \
      if ( hwa->oc0.solved.com != 0xFF ) _hwa_write_reg( oc0, com, hwa->oc0.solved.com ); \
      if ( hwa->oc1.solved.com != 0xFF ) _hwa_write_reg( oc1, com, hwa->oc1.solved.com ); \
      if ( hwa->ic0.solved.acic != 0xFF ) _hwa_write_reg( ic0, acic, hwa->ic0.solved.acic ); \
      if ( hwa->ic0.solved.ices != 0xFF ) _hwa_write_reg( ic0, ices, hwa->ic0.solved.ices ); \
      if ( hwa->ic0.solved.icnc != 0xFF ) _hwa_write_reg( ic0, icnc, hwa->ic0.solved.icnc ); \
      /*								\
       *  Configure used compare outputs as i/o outputs			\
       */								\
      if ( hwa->oc0.config.output != 0xFF				\
	   && hwa->oc0.config.output != HW_A1(_hw_oc16a_output_disconnected) ) \
	hwa_config( _hw_rel(oc0,pin), direction, output );		\
      if ( hwa->oc1.config.output != 0xFF				\
	   && hwa->oc1.config.output != HW_A1(_hw_oc16a_output_disconnected) ) \
	hwa_config( _hw_rel(oc1,pin), direction, output );		\
    }									\
    else if ( r == 1 )							\
      HWA_ERR("`update` must be the same for both compare units of `" #o "`."); \
    else if ( r == 2 )							\
      HWA_ERR("WGM value could not be solved for `" #o "`.");		\
    else if ( r == 3 )							\
      HWA_ERR("configuration of `" #o "` is required.");		\
    else if ( r == 4 )							\
      HWA_ERR("`mode` of `" #oc0 "` can be "				\
	      "'disconnected', 'toggle_on_match', 'clear_on_match', or " \
	      "'set_on_match'.");					\
    else if ( r == 5 )							\
      HWA_ERR("`mode` of `" #oc0 "` can be "				\
	      "'disconnected', 'set_at_bottom_clear_on_match', or "	\
	      "'clear_at_bottom_set_on_match'.");			\
    else if ( r == 6 )							\
      HWA_ERR("`mode` of `" #oc0 "` can be "				\
	      "'disconnected', 'toggle_on_match', "			\
	      "'set_at_bottom_clear_on_match', or "			\
	      "'clear_at_bottom_set_on_match'.");			\
    else if ( r == 7 )							\
      HWA_ERR("`mode` of `" #oc0 "` can be "				\
	      "'disconnected', 'clear_on_match_up_set_on_match_down', " \
	      "or 'set_on_match_up_clear_on_match_down'.");		\
    else if ( r == 8 )							\
      HWA_ERR("`mode` of `" #oc0 "` can be "				\
	      "'disconnected', 'toggle_on_match', "			\
	      "'clear_on_match_up_set_on_match_down', "			\
	      "or 'set_on_match_up_clear_on_match_down'.");		\
    else if ( r == 9 )							\
      HWA_ERR("`mode` of `" #oc1 "` can be "				\
	      "'disconnected', 'toggle_on_match', 'clear_on_match', or " \
	      "'set_on_match'.");					\
    else if ( r == 10 )							\
      HWA_ERR("`mode` of `" #oc1 "` can be "				\
	      "'disconnected', 'set_at_bottom_clear_on_match', or "	\
	      "'clear_at_bottom_set_on_match'.");			\
    else if ( r == 11 )							\
      HWA_ERR("`mode` of `" #oc1 "` can be "				\
	      "'disconnected', 'clear_on_match_up_set_on_match_down', "	\
	      "or 'set_on_match_up_clear_on_match_down'.");		\
    else if ( r == 12 )							\
      HWA_ERR("for `" #o "`, `optionnal parameter 'update' must be 'immediately'."); \
    else if ( r == 13 )							\
      HWA_ERR("for `" #o "`, `optionnal parameter 'update' must be 'at_bottom'."); \
    else if ( r == 14 )							\
      HWA_ERR("for `" #o "`, `optionnal parameter 'update' must be 'at_top'."); \
    else if ( r == 15 )							\
      HWA_ERR("for `" #o "`, `optionnal parameter 'overflow' must be 'at_top'."); \
    else if ( r == 16 )							\
      HWA_ERR("for `" #o "`, `optionnal parameter 'overflow' must be 'at_bottom'."); \
    else if ( r == 17 )							\
      HWA_ERR("for `" #o "`, `optionnal parameter 'overflow' must be 'at_max'."); \
    else								\
      HWA_ERR("for `" #o "`, `unknown error code'.");			\
  } while(0)

/*	Solve the configuration of the counter with its compare and capture units
 */
//HW_INLINE void _hwa_solve__c16a ( hwa_t *hwa __attribute__((unused)), hwa_c16a_t *p )
HW_INLINE uint8_t _hwa_solve_c16a ( hwa_c16a_t *c, hwa_oc16a_t *oc0,
				    hwa_oc16a_t *oc1, hwa_ic16a_t *ic0 )
{
  c->solved.cs   = 0xFF ;
  c->solved.wgm  = 0xFF ;
  oc0->solved.com = 0xFF ;
  oc1->solved.com = 0xFF ;
  ic0->solved.acic = 0xFF ;
  ic0->solved.ices = 0xFF ;
  ic0->solved.icnc = 0xFF ;

  if ( c->config.clock == 0xFF )
    return 0 ;

  /*  Clock setting
   */
  c->solved.cs = c->config.clock ;

  /*  Default config for top
   */
  if ( c->config.top == 0xFF )
    c->config.top = HW_A1(_hw_c16a_top_max);

  /*  Default config for overflow
   */
  uint8_t overflow = c->config.overflow ;
  if ( overflow == 0xFF && c->config.top == HW_A1(_hw_c16a_top_compare0) ) {
    if ( c->config.countmode == HW_A1(_hw_c16a_countmode_loop_up) )
      overflow = HW_A1(_hw_c16a_overflow_at_top);
    else /* if ( c->config.countmode == HW_A1(_hw_c16a_countmode_loop_up) ) */
      overflow = HW_A1(_hw_c16a_overflow_at_bottom);
  }

  /*  Compare update setting
   */
  uint8_t compare_update = 0xFF ;
  if ( oc0->config.update != 0xFF && oc1->config.update != 0xFF
       && oc0->config.update != oc1->config.update )
    return 1 ; // HWA_ERR("optionnal parameter 'update' of class _c16a counter must be'immediately'.");
  compare_update = oc0->config.update ;

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
  if ( c->config.countmode == HW_A1(_hw_c16a_countmode_loop_up)
       && c->config.top == HW_A1(_hw_c16a_top_compare0)
       && overflow == HW_A1(_hw_c16a_overflow_at_top) )
    wgm = 15 ;
  else    
    if ( c->config.countmode == HW_A1(_hw_c16a_countmode_loop_up) ) {
      if ( c->config.top == HW_A1(_hw_c16a_top_fixed_0xFFFF) )
	wgm = 0 ;
      else if (c->config.top == HW_A1(_hw_c16a_top_fixed_0xFF) )
	wgm = 5 ;
      else if (c->config.top == HW_A1(_hw_c16a_top_fixed_0x1FF) )
	wgm = 6 ;
      else if (c->config.top == HW_A1(_hw_c16a_top_fixed_0x3FF) )
	wgm = 7 ;
      else if (c->config.top == HW_A1(_hw_c16a_top_compare0) ) {
	if ( compare_update == HW_A1(_hw_oc16a_update_immediately)
	     || overflow == HW_A1(_hw_c16a_overflow_at_top)
	     || oc1->config.output == HW_A1(_hw_oc16a_output_set_at_bottom_clear_on_match)
	     || oc1->config.output == HW_A1(_hw_oc16a_output_clear_at_bottom_set_on_match))
	  wgm = 15 ;
	else 
	  wgm = 4 ;
      }
      else /* if (c->top == HW_A1(_hw_c16a_top_capture0) ) */ {
	if (compare_update == HW_A1(_hw_oc16a_update_at_top)
	    || overflow == HW_A1(_hw_c16a_overflow_at_top)
	    || oc0->config.output == HW_A1(_hw_oc16a_output_toggle_on_match)
	    || oc0->config.output == HW_A1(_hw_oc16a_output_set_at_bottom_clear_on_match)
	    || oc0->config.output == HW_A1(_hw_oc16a_output_clear_at_bottom_set_on_match)
	    || oc1->config.output == HW_A1(_hw_oc16a_output_set_at_bottom_clear_on_match)
	    || oc1->config.output == HW_A1(_hw_oc16a_output_clear_at_bottom_set_on_match))
	  wgm = 14 ;
	else 
	  wgm = 12 ;
      }
    }
    else {
      if (c->config.top == HW_A1(_hw_c16a_top_fixed_0xFF) )
	wgm = 1 ;
      else if (c->config.top == HW_A1(_hw_c16a_top_fixed_0x1FF) )
	wgm = 2 ;
      else if (c->config.top == HW_A1(_hw_c16a_top_fixed_0x3FF) )
	wgm = 3 ;
      else if (c->config.top == HW_A1(_hw_c16a_top_compare0) ) {
	if (compare_update == HW_A1(_hw_oc16a_update_at_bottom)
	    || oc1->config.output == HW_A1(_hw_oc16a_output_clear_on_match_up_set_on_match_down)
	    || oc1->config.output == HW_A1(_hw_oc16a_output_set_on_match_up_clear_on_match_down))
	  wgm = 9 ;
	else 
	  wgm = 11 ;
      }
      else /* if (c->top == HW_A1(_hw_c16a_top_capture0) ) */ {
	if (compare_update == HW_A1(_hw_oc16a_update_at_bottom)
	    || oc0->config.output == HW_A1(_hw_oc16a_output_toggle_on_match)
	    || oc0->config.output == HW_A1(_hw_oc16a_output_clear_on_match_up_set_on_match_down)
	    || oc0->config.output == HW_A1(_hw_oc16a_output_set_on_match_up_clear_on_match_down)
	    || oc1->config.output == HW_A1(_hw_oc16a_output_clear_on_match_up_set_on_match_down)
	    || oc1->config.output == HW_A1(_hw_oc16a_output_set_on_match_up_clear_on_match_down))
	  wgm = 8 ;
	else 
	  wgm = 10 ;
      }
    }
      
  if ( wgm == 0xFF )
    return 2 ; // HWA_ERR("WGM value could not be solved for _c16a class counter.");
  c->solved.wgm = wgm ;

  /*	Solve the configuration of compare output A
   */
  if ( oc0->config.output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( oc0->config.output == HW_A1(_hw_oc16a_output_disconnected) )
      mode = 0 ;
    else if ( oc0->config.output == HW_A1(_hw_oc16a_output_toggle_on_match) )
      mode = 1 ;
    else if ( oc0->config.output == HW_A1(_hw_oc16a_output_clear_on_match)
	      || oc0->config.output == HW_A1(_hw_oc16a_output_set_at_bottom_clear_on_match)
	      || oc0->config.output == HW_A1(_hw_oc16a_output_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    oc0->solved.com = mode ;
  }

  /*  Solve the configuration of compare output B
   */
  if ( oc1->config.output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( oc1->config.output == HW_A1(_hw_oc16a_output_disconnected) )
      mode = 0 ;
    else if ( oc1->config.output == HW_A1(_hw_oc16a_output_toggle_on_match) )
      mode = 1 ;
    else if ( oc1->config.output == HW_A1(_hw_oc16a_output_clear_on_match)
	      || oc1->config.output == HW_A1(_hw_oc16a_output_set_at_bottom_clear_on_match)
	      || oc1->config.output == HW_A1(_hw_oc16a_output_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    oc1->solved.com = mode ;
  }

  /*	Solve the configuration of the capture input
   */
  if ( ic0->config.input != 0xFF ) {
    ic0->solved.acic = ic0->config.input-1 ;
    ic0->solved.ices = ic0->config.edge-1 ;
    if ( ic0->config.filter != 0xFF )
      ic0->solved.icnc = ic0->config.filter ;
  }


  /*	Check the validity of the configuration
   */
  if ( c->config.countmode != 0xFF || oc0->config.output != 0xFF || oc1->config.output != 0xFF ) {

    if ( c->config.countmode == 0xFF )
      return 3 ; // HWA_ERR("configuration of counter is required.");

    /*	Check compare output A
     */
    if ( oc0->config.output != 0xFF ) {
      if ( wgm==0 || wgm==12 ) {
	if ( oc0->config.output != HW_A1(_hw_oc16a_output_disconnected)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_clear_on_match)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_set_on_match)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_toggle_on_match) )
	  return 4 ;
	/* HWA_ERR("compare output A of class _c16a counter mode must be " */
	/* 	  "'disconnected', 'clear_on_match', 'set_on_match', or " */
	/* 	  "'toggle_on_match'."); */
      }
      else if ( wgm==5 || wgm==6 || wgm==7 ) {
	if ( oc0->config.output != HW_A1(_hw_oc16a_output_disconnected)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_set_at_bottom_clear_on_match)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_clear_at_bottom_set_on_match) )
	  return 5 ;
	  /* HWA_ERR("compare output A of class _c16a counter mode must be " */
	  /* 	  "'disconnected', 'set_at_bottom_clear_on_match', or " */
	  /* 	  "'clear_at_bottom_set_on_match'."); */
      }
      else if ( wgm==14 ) {
	if ( oc0->config.output != HW_A1(_hw_oc16a_output_disconnected)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_toggle_on_match)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_set_at_bottom_clear_on_match)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_clear_at_bottom_set_on_match) )
	  return 6 ;
	  /* HWA_ERR("compare output A of class _c16a counter mode must be " */
	  /* 	  "'disconnected', 'toggle_on_match', " */
	  /* 	  "'set_at_bottom_clear_on_match', or " */
	  /* 	  "'clear_at_bottom_set_on_match'."); */
      }
      else if ( wgm==1 || wgm==2 || wgm==3 ) {
	if ( oc0->config.output != HW_A1(_hw_oc16a_output_disconnected)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_clear_on_match_up_set_on_match_down)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_set_on_match_up_clear_on_match_down) )
	  return 7 ;
	  /* HWA_ERR("compare output A of class _c16a counter mode must be " */
	  /* 	  "'disconnected', 'clear_on_match_up_set_on_match_down', " */
	  /* 	  "or 'set_on_match_up_clear_on_match_down'."); */
      }
      else if ( wgm==8 || wgm==10 ) {
	if ( oc0->config.output != HW_A1(_hw_oc16a_output_disconnected)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_toggle_on_match)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_clear_on_match_up_set_on_match_down)
	     && oc0->config.output != HW_A1(_hw_oc16a_output_set_on_match_up_clear_on_match_down) )
	  return 8 ;
	  /* HWA_ERR("compare output A of class _c16a counter mode must be " */
	  /* 	  "'disconnected', 'toggle_on_match', " */
	  /* 	  "'clear_on_match_up_set_on_match_down', " */
	  /* 	  "or 'set_on_match_up_clear_on_match_down'."); */
      }
      //    else if ( c->top == HW_A1(_hw_c16a_top_compare0)
      else if ( oc0->config.output )
	return 9 ;
	/* HWA_ERR("can not use of `compare_a` as both top value and output of class _c16a counter."); */
    }

    /*	Check compare output B
     */
    if ( oc1->config.output != 0xFF ) {
      if ( wgm==0 || wgm==4 || wgm==12 ) {
	if ( oc1->config.output != HW_A1(_hw_oc16a_output_disconnected)
	     && oc1->config.output != HW_A1(_hw_oc16a_output_clear_on_match)
	     && oc1->config.output != HW_A1(_hw_oc16a_output_set_on_match)
	     && oc1->config.output != HW_A1(_hw_oc16a_output_toggle_on_match) )
	  return 10 ;
	  /* HWA_ERR("compare output B of class _c16a counter mode must be " */
	  /* 	  "'disconnected', 'clear_on_match', 'set_on_match', or " */
	  /* 	  "'toggle_on_match'."); */
      }
      else if ( wgm==5 || wgm==6 || wgm==7 || wgm==14 || wgm==15 ) {
	if ( oc1->config.output != HW_A1(_hw_oc16a_output_disconnected)
	     && oc1->config.output != HW_A1(_hw_oc16a_output_set_at_bottom_clear_on_match)
	     && oc1->config.output != HW_A1(_hw_oc16a_output_clear_at_bottom_set_on_match) )
	  return 11 ;
	  /* HWA_ERR("compare output B of class _c16a counter mode must be " */
	  /* 	  "'disconnected', 'set_at_bottom_clear_on_match', or " */
	  /* 	  "'clear_at_bottom_set_on_match'."); */
      }
      else /* if ( wgm==1 || wgm==2 || wgm==3 || wgm==8 || wgm==9 || wgm==10 || wgm==11 ) */ {
	if ( oc1->config.output != HW_A1(_hw_oc16a_output_disconnected)
	     && oc1->config.output != HW_A1(_hw_oc16a_output_clear_on_match_up_set_on_match_down)
	     && oc1->config.output != HW_A1(_hw_oc16a_output_set_on_match_up_clear_on_match_down) )
	  return 12 ;
	  /* HWA_ERR("compare output B of class _c16a counter mode must be " */
	  /* 	  "'disconnected', 'clear_on_match_up_set_on_match_down', " */
	  /* 	  "or 'set_on_match_up_clear_on_match_down'."); */
      }
    }

    /*	Check compare update
     */
    if ( compare_update != 0xFF ) {
      if ( wgm==0 || wgm==4 || wgm==12 ) {
	if ( compare_update != HW_A1(_hw_oc16a_update_immediately) )
	  return 13 ;
	  /* HWA_ERR("optionnal parameter 'update' of class _c16a counter must be "\ */
	  /* 	  "'immediately'."); */
      }
      else if ( wgm==8 || wgm==9 ) {
	if ( compare_update != HW_A1(_hw_oc16a_update_at_bottom) )
	  return 14 ;
	  /* HWA_ERR("optionnal parameter 'update' of class _c16a counter must be " */
	  /* 	  "'at_bottom'."); */
      }
      else
	if( compare_update != HW_A1(_hw_oc16a_update_at_top) )
	  return 15 ;
	  /* HWA_ERR("optionnal parameter 'update' of class _c16a counter must be " */
	  /* 	  "'at_top'."); */
    }

    /*	Overflow
     */
    if ( overflow != 0xFF ) {
      if ( (wgm==0 || wgm==4 || wgm==12) ) {
	if ( overflow != HW_A1(_hw_c16a_overflow_at_max) )
	  return 16 ;
	  /* HWA_ERR("optionnal parameter 'overflow' of class _c16a counter must be " */
	  /* 	  "'at_max'."); */
      }
      else if ( (wgm==5 || wgm==6 || wgm==7 || wgm==14 || wgm==15) ) {
	if ( overflow != HW_A1(_hw_c16a_overflow_at_top) )
	  return 17 ;
	  /* HWA_ERR("optionnal parameter 'overflow' of class _c16a counter must be " */
	  /* 	  "'at_top'."); */
      }
      else if ( overflow != HW_A1(_hw_c16a_overflow_at_bottom) )
	return 18 ;
	/* HWA_ERR("optionnal parameter 'overflow' of class _c16a counter must be " */
	/* 	"'at_bottom'."); */
    }
  }

  return 0 ;
}


/**
 * @page atmelavr_c16a
 * @section atmelavr_c16a_cnt Count value
 *
 * The count value is accessible for reading and writing through the following
 * instructions:
 */

/**
 * @page atmelavr_c16a
 * @code
 * hw_read( COUNTER_NAME );
 * @endcode
 */
#define _hw_mthd_hw_read__c16a		, _hw_read_c16a
#define _hw_read_c16a(o,i,a,...)	HW_TX(_hw_read_reg(o,count),__VA_ARGS__)


/**
 * @page atmelavr_c16a
 * @code
 * hw_write( COUNTER_NAME, value );
 * @endcode
 */
#define _hw_mthd_hw_write__c16a		, _hw_write_c16a
#define _hw_write_c16a(o,i,a,v,...)	HW_TX(_hw_write_reg(o,count,v),__VA_ARGS__)

/**
 * @page atmelavr_c16a
 * @code
 * hwa_write( COUNTER_NAME, value );
 * @endcode
 */
#define _hw_mthd_hwa_write__c16a	, _hwa_write_c16a
#define _hwa_write_c16a(o,i,a,v)	_hwa_write_reg(o,count,v)


#if 0
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

#define _hw_statt_c16a(o,i,a,...)	HW_TX(_hw_c16a_stat_t, __VA_ARGS__)

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

#define _hw_stat_c16a(o,i,a,...)	HW_TX(_hw_c16a_stat(_hw_read_reg(o, ifr)), __VA_ARGS__)

HW_INLINE _hw_c16a_stat_t _hw_c16a_stat( uint8_t byte )
{
  _hw_c16a_stat_t	st ;
  st.byte = byte ;
  return st ;
}
#endif


/**
 * @page atmelavr_c16a
 * @section atmelavr_c16a_st Status
 *
 * The overflow flag can be accessed through interrupt-related instructions:
 *
 * @code
 * if ( hw_stat_irqf( COUNTER_NAME ) ) {        // Read overflow IRQ flag
 *   hw_clear_irqf( COUNTER_NAME );             // Clear overflow IRQ flag
 *   hw_turn_irq( COUNTER_NAME, off );          // Disable overflow IRQs
 * }
 * @endcode
 */


/*******************************************************************************
 *                                                                             *
 *      Context management						       *
 *                                                                             *
 *******************************************************************************/

#define _hwa_setup__c16a(o,i,a)			\
  _hwa_setup_reg( o, ccra     );		\
  _hwa_setup_reg( o, ccrb     );		\
  _hwa_setup_reg( o, ccrc     );		\
  _hwa_setup_reg( o, count    );		\
  _hwa_setup_reg( o, imsk     );		\
  _hwa_setup_reg( o, ifr      );		\
  hwa->o.config.clock     = 0xFF;		\
  hwa->o.config.countmode = 0xFF;		\
  hwa->o.config.top       = 0xFF;		\
  hwa->o.config.overflow  = 0xFF
  /* hwa->o.config.compare0.update = 0xFF ;	\ */
  /* hwa->o.config.compare0.output = 0xFF ;	\ */
  /* hwa->o.config.compare1.update = 0xFF ;	\ */
  /* hwa->o.config.compare1.output = 0xFF ;	\ */

#define _hwa_init__c16a(o,i,a)					\
  _hwa_init_reg( o, ccra, 0x00 );			\
  _hwa_init_reg( o, ccrb, 0x00     );		\
  _hwa_init_reg( o, ccrc, 0x00     );		\
  _hwa_init_reg( o, count, 0x00    );		\
  _hwa_init_reg( o, imsk, 0x00     );		\
  _hwa_init_reg( o, ifr, 0x00      )

#define _hwa_commit__c16a(o,i,a)			\
  _hwa_commit_reg( o, ccra     );		\
  _hwa_commit_reg( o, ccrb     );		\
  _hwa_commit_reg( o, ccrc     );		\
  _hwa_commit_reg( o, count    );		\
  _hwa_commit_reg( o, imsk     )


/* HW_INLINE void _hwa_begin_p__c16a ( hwa_c16a_t *p, intptr_t a ) */
/* { */
/*   _hwa_setup_reg_p( p, a, _c16a, ccra     ); */
/*   _hwa_setup_reg_p( p, a, _c16a, ccrb     ); */
/*   _hwa_setup_reg_p( p, a, _c16a, ccrc     ); */
/*   _hwa_setup_reg_p( p, a, _c16a, count    ); */
/*   _hwa_setup_reg_p( p, a, _c16a, capture0 ); */
/*   _hwa_setup_reg_p( p, a, _c16a, compare0 ); */
/*   _hwa_setup_reg_p( p, a, _c16a, compare1 ); */
/*   _hwa_setup_reg_p( p, a, _c16a, imsk     ); */
/*   _hwa_setup_reg_p( p, a, _c16a, ifr      ); */

/*   p->config.clock           = 0xFF ; */
/*   p->config.countmode       = 0xFF ; */
/*   p->config.top             = 0xFF ; */
/*   p->config.overflow        = 0xFF ; */
/*   p->config.compare0.update = 0xFF ; */
/*   p->config.compare0.output = 0xFF ; */
/*   p->config.compare1.update = 0xFF ; */
/*   p->config.compare1.output = 0xFF ; */
/*   p->config.capture0.input  = 0xFF ; */
/*   p->config.capture0.edge   = 0xFF ; */
/*   p->config.capture0.filter = 0xFF ; */
/* } */


/* HW_INLINE void _hwa_init_p__c16a ( hwa_c16a_t *p ) */
/* { */
/*   _hwa_set__r8(  &p->ccra,  0x00 ); */
/*   _hwa_set__r8(  &p->ccrb,  0x00 ); */
/*   _hwa_set__r8(  &p->ccrc,  0x00 ); */
/*   _hwa_set__r16( &p->count, 0x00 ); */
/*   _hwa_set__r16( &p->capture0,   0x00 ); */
/*   _hwa_set__r16( &p->compare0,  0x00 ); */
/*   _hwa_set__r16( &p->compare1,  0x00 ); */
/*   _hwa_set__r8(  &p->imsk,  0x00 ); */
/*   _hwa_set__r8(  &p->ifr,   0x00 ); */
/* } */


/* HW_INLINE void _hwa_commit_p__c16a ( hwa_t *hwa, hwa_c16a_t *p ) */
/* { */
/*   _hwa_commit_reg_p( p, _c16a, ccra  ); */
/*   _hwa_commit_reg_p( p, _c16a, ccrb  ); */
/*   _hwa_commit_reg_p( p, _c16a, ccrc  ); */
/*   _hwa_commit_reg_p( p, _c16a, count ); */
/*   _hwa_commit_reg_p( p, _c16a, capture0   ); */
/*   _hwa_commit_reg_p( p, _c16a, compare0  ); */
/*   _hwa_commit_reg_p( p, _c16a, compare1  ); */
/*   _hwa_commit_reg_p( p, _c16a, imsk  ); */
/*   _hwa_commit_reg_p( p, _c16a, ifr   ); */
/* } */

/**
 * @page atmelavr_c16a
 * @section atmelavr_c16a_internals Internals
 *
 * Class `_c16a` objects hold the following hardware registers:
 *
 *  * `ccra`: control register a
 *  * `ccrb`: control register b
 *  * `ccrc`: control register c
 *  * `count`: count register
 *  * `ifr`: interrupt flag register
 *  * `imsk`: interrupt flag register
 *
 * that hold the following logical registers:
 *
 *  * `wgm`: counting and waveform generation mode
 *  * `cs`: clock selection
 *  * `ie`: overflow interrupt mask
 *  * `if`: overflow interrupt flag
 *
 * These registers are accessible through the @ref public_reg_instructions
 * "register access intructions".
 */


/**
 * @page atmelavr_c16a
 * <br>
 */
