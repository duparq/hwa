
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit counter
 */

/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_config Configuration
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
 *                        | syshz_ext_rising            // External input, rising edge
 *                        | syshz_ext_falling,          // External input, falling edge
 *
 *             //  How does this counter count
 *             //
 *             countmode,   loop_up                     // Count up and loop
 *                        | loop_updown,                // Count up and down alternately
 *
 *             //  Class _c8a counters all count from 0
 *             //
 *           [ bottom,      0, ]
 *
 *             //  The maximum value the counter reaches (the default is `max`)
 *             //
 *           [ top,         0xFF                        // Hardware fixed value 0xFF
 *                        | max                         // Hardware fixed value 0xFF
 *                        | compare0,]                  // Value stored in the compare0 unit
 *
 *             //  When the overflow flag is set
 *             //
 *           [ overflow,    at_bottom                   // When the counter resets to bottom
 *                        | at_top                      // When the counter reaches the top value
 *                        | at_max ]                    // When the counter reaches its max value
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__c8a		, _hwa_config_c8a

/*  Mandatory argument `clock`
 *
 *    Add 2 void arguments to the end of the list so that there are always
 *    3 arguments following the last non-void argument.
 */
#define _hw_c8a_clock_none			, 0
#define _hw_c8a_clock_prescaler_output_0	, 0
#define _hw_c8a_clock_prescaler_output_1	, 1	/* Useful for concat */
#define _hw_c8a_clock_prescaler_output_8	, 2
#define _hw_c8a_clock_prescaler_output_64	, 3
#define _hw_c8a_clock_prescaler_output_256	, 4
#define _hw_c8a_clock_prescaler_output_1024	, 5
#define _hw_c8a_clock_ext_rising		, 6
#define _hw_c8a_clock_ext_falling		, 7
#define _hw_c8a_clock_prescaler_output(x)	HW_G2(_hw_c8a_clock_prescaler_output,x)

#define _hwa_config_c8a(o,i,a, ...)						\
  do { HW_G2(_hwa_cfc8a_kclock,HW_IS(clock,__VA_ARGS__))(o,__VA_ARGS__,,) } while(0)

#define _hwa_cfc8a_kclock_0(o,k,...)					\
  HW_ERR("expected `clock` instead of `" #k "`.")

#define _hwa_cfc8a_kclock_1(o,k,v,...)					\
  HW_G2(_hwa_cfc8a_vclock,HW_IS(,_hw_c8a_clock_##v))(o,v,__VA_ARGS__)

#define _hwa_cfc8a_vclock_0(o,v,...)				\
  HW_ERR( "`clock` can be `none`, "				\
	  "`prescaler_output( 0 | 1 | 8 | 64 | 256 | 1024 )`, "	\
	  "`ext_falling`, `ext_rising`, but not `" #v "`.")

#define _hwa_cfc8a_vclock_1(o,v,k,...)				\
  hwa->o.config.clock = HW_A1(_hw_c8a_clock_##v);		\
  HW_G2(_hwa_cfc8a_kmode,HW_IS(countmode,k))(o,k,__VA_ARGS__)

/*  Optionnal argument `countmode`
 */
#define _hw_c8a_countmode_loop_up		, 1
#define _hw_c8a_countmode_loop_updown		, 2

#define _hwa_cfc8a_kmode_0(o,k,...)					\
  HW_ERR("expected `countmode` instead of `" #k "`.")

#define _hwa_cfc8a_kmode_1(o,k,v,...)					\
  HW_G2(_hwa_cfc8a_vmode,HW_IS(,_hw_c8a_countmode_##v))(o,v,__VA_ARGS__)

#define _hwa_cfc8a_vmode_0(o,v,...)					\
  HW_ERR("`countmode` can be `loop_up`, or `loo_updown`, but not `" #v "`.")

#define _hwa_cfc8a_vmode_1(o,v,k,...)					\
  hwa->o.config.countmode = HW_A1(_hw_c8a_countmode_##v);			\
  HW_G2(_hwa_cfc8a_kbottom,HW_IS(bottom,k))(o,k,__VA_ARGS__)

/*  Optionnal argument `bottom`
 */
#define _hwa_cfc8a_kbottom_1(o,k,v,...)			\
  HW_G2(_hwa_cfc8a_vbottom,HW_IS(0,v))(o,v,__VA_ARGS__)

#define _hwa_cfc8a_vbottom_0(o,v,...)			\
  HW_ERR("bottom must be `0`, not `" #v "`.")

#define _hwa_cfc8a_vbottom_1(o,v,k,...)			\
  HW_G2(_hwa_cfc8a_ktop,HW_IS(top,k))(o,k,__VA_ARGS__)

#define _hwa_cfc8a_kbottom_0(o,k,...)			\
  HW_G2(_hwa_cfc8a_ktop,HW_IS(top,k))(o,k,__VA_ARGS__)

/*  Optionnal argument `top`
 */
#define _hw_c8a_top_0xFF			, 1
#define _hw_c8a_top_0x00FF			, 1
#define _hw_c8a_top_255				, 1
#define _hw_c8a_top_max				, 1
#define _hw_c8a_top_compare0			, 2

#define _hwa_cfc8a_ktop_1(o,k,v,...)					\
  HW_G2(_hwa_cfc8a_vtop,HW_IS(,_hw_c8a_top_##v))(o,v,__VA_ARGS__)

#define _hwa_cfc8a_vtop_0(o,v,...)				\
  HW_ERR("`top` can be `0xFF`, `max`, or `compare0`,"		\
	 " but not `" #v "`.")

#define _hwa_cfc8a_vtop_1(o,v,k,...)					\
  hwa->o.config.top = HW_A1(_hw_c8a_top_##v);				\
  HW_G2(_hwa_cfc8a_koverflow,HW_IS(overflow,k))(o,k,__VA_ARGS__)

#define _hwa_cfc8a_ktop_0(o,k,...)					\
  HW_G2(_hwa_cfc8a_koverflow,HW_IS(overflow,k))(o,k,__VA_ARGS__)

/*  Optionnal argument `overflow`
 */
#define _hw_c8a_overflow_at_bottom		, 0
#define _hw_c8a_overflow_at_top			, 1
#define _hw_c8a_overflow_at_max			, 2

#define _hwa_cfc8a_koverflow_1(o,k,v,...)				\
  HW_G2(_hwa_cfc8a_voverflow, HW_IS(,_hw_c8a_overflow_##v))(o,v,__VA_ARGS__)

#define _hwa_cfc8a_voverflow_0(o,v,...)				\
  HW_ERR("optionnal parameter `overflow` can be `at_bottom`, "	\
	 "`at_top, or `at_max`, but `not `" #v "`.")

#define _hwa_cfc8a_voverflow_1(o,v,...)				\
  if ( hwa->o.config.countmode == HW_A1(_hw_c8a_countmode_loop_up)		\
       && HW_A1(_hw_c8a_overflow_##v) == HW_A1(_hw_c8a_overflow_at_bottom) ) \
    HWA_ERR("optionnal parameter `overflow` can not be `at_bottom` "	\
	    "when countmode is `loop_up`.");				\
  HW_TX(hwa->o.config.overflow = HW_A1(_hw_c8a_overflow_##v); ,__VA_ARGS__)

#define _hwa_cfc8a_koverflow_0(o,...)		\
  HW_EOL(__VA_ARGS__)


/**
 * @brief Solve and check the configuration of the counter and its compare units.
 *
 * Writing code for a HW_INLINE function is more comfortable than for a
 * function-like macro but functions can not use object names. So, this
 * function-like macro expands to the HW_INLINE function _hwa_solve_c8a() which
 * uses pointers on objects in the HWA context to compute values to be written
 * into the registers, stores them into the `solve` structure and returns an
 * error code that is processed by _hwa_solve__c8a() which knows the names of
 * the objects and then can put computed registers values into the context, even
 * in the case of external register access, and display accurate error messages.
 */
#define _hwa_solve__c8a( o,i,a )	_hwa_solve__c8a_2( o,		\
							   _hw_rel(o,compare0),	\
							   _hw_rel(o,compare1) )
#define _hwa_solve__c8a_2(...)		_hwa_solve__c8a_3(__VA_ARGS__)

#define _hwa_solve__c8a_3( o, oc0, oc1 )				\
  do {									\
    uint8_t r = _hwa_solve_c8a( &hwa->o, &hwa->oc0, &hwa->oc1 );	\
    if ( r == 1 )							\
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
	      "'disconnected', 'clear_on_match_up_set_on_match_down', "	\
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
    else {								\
      /*								\
       *  Write solved registers					\
       */								\
      if ( hwa->o.solved.cs != 0xFF ) _hwa_write_reg( o, cs, hwa->o.solved.cs ); \
      if ( hwa->o.solved.wgm != 0xFF ) _hwa_write_reg( o, wgm, hwa->o.solved.wgm ); \
      if ( hwa->oc0.solved.com != 0xFF ) _hwa_write_reg( oc0, com, hwa->oc0.solved.com ); \
      if ( hwa->oc1.solved.com != 0xFF ) _hwa_write_reg( oc1, com, hwa->oc1.solved.com ); \
      /*								\
       *  Configure used compare outputs as i/o outputs			\
       */								\
      if ( hwa->oc0.config.output != 0xFF				\
	   && hwa->oc0.config.output != HW_A1(_hw_oc8a_output_disconnected) ) \
	hwa_config( _hw_rel(oc0,pin), direction, output );		\
      if ( hwa->oc1.config.output != 0xFF				\
	   && hwa->oc1.config.output != HW_A1(_hw_oc8a_output_disconnected) ) \
	hwa_config( _hw_rel(oc1,pin), direction, output );		\
    }									\
  } while(0)


HW_INLINE uint8_t _hwa_solve_c8a ( hwa_c8a_t *p, hwa_oc8a_t *oc0, hwa_oc8a_t *oc1  )
{
  /*	0xFF == unchanged
   */
  p->solved.cs    = 0xFF ;
  p->solved.wgm   = 0xFF ;
  oc0->solved.com = 0xFF ;
  oc1->solved.com = 0xFF ;

  if ( p->config.clock == 0xFF )
    return 0 ;

  /*	Clock selection
   */
  p->solved.cs = p->config.clock ;

  /*  Default config for top
   */
  if ( p->config.top == 0xFF )
    p->config.top = HW_A1(_hw_c8a_top_max);

  /*  Default config for overflow
   */
  uint8_t overflow = p->config.overflow ;
  if ( overflow == 0xFF && p->config.top == HW_A1(_hw_c8a_top_compare0) ) {
    if ( p->config.countmode == HW_A1(_hw_c8a_countmode_loop_up) )
      overflow = HW_A1(_hw_c8a_overflow_at_top);
    else /* if ( p->config.countmode == HW_A1(_hw_c8a_countmode_loop_up) ) */
      overflow = HW_A1(_hw_c8a_overflow_at_bottom);
  }

  /*  Compare update setting
   */
  uint8_t compare_update = 0xFF ;
  if ( oc0->config.update != 0xFF && oc1->config.update != 0xFF
       && oc0->config.update != oc1->config.update )
    return 1 ; //HWA_ERR("`update` must be the same for both compare units.");

  compare_update = oc0->config.update ;


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

  /*	Determine WGM
   */
  uint8_t wgm = 0xFF ;
  if ( p->config.countmode == HW_A1(_hw_c8a_countmode_loop_up) ) {
    if ( p->config.top == HW_A1(_hw_c8a_top_0xFF) ) {
      if ( compare_update == HW_A1(_hw_oc8a_update_at_bottom)
	   || oc0->config.output == HW_A1(_hw_oc8a_output_clear_at_bottom_set_on_match)
	   || oc0->config.output == HW_A1(_hw_oc8a_output_set_at_bottom_clear_on_match)
	   || oc1->config.output == HW_A1(_hw_oc8a_output_clear_at_bottom_set_on_match)
	   || oc1->config.output == HW_A1(_hw_oc8a_output_set_at_bottom_clear_on_match))
	wgm = 3 ;
      else 
	wgm = 0 ;
    }
    else /* top == ocra */ {
      /*
       *  FIXME: a change of pin from one of the 4 modes below to
       *  'disconnected' causes a useless modification of wgm from 7 to 2. As
       *  WGM2 is not in the same register as WGM1:0, this generates useless
       *  code.
       */
      if ( compare_update == HW_A1(_hw_oc8a_update_at_bottom )
	   || overflow == HW_A1(_hw_c8a_overflow_at_top)
	   || oc0->config.output == HW_A1(_hw_oc8a_output_clear_at_bottom_set_on_match)
	   || oc0->config.output == HW_A1(_hw_oc8a_output_set_at_bottom_clear_on_match)
	   || oc1->config.output == HW_A1(_hw_oc8a_output_clear_at_bottom_set_on_match)
	   || oc1->config.output == HW_A1(_hw_oc8a_output_set_at_bottom_clear_on_match))
	wgm = 7 ;
      else
	wgm = 2 ;
    }
  }
  else /* countmode == loop_updown */ {
    if ( p->config.top == HW_A1(_hw_c8a_top_0xFF) )
      wgm = 1 ;
    else /* top == ocra */
      wgm = 5 ;
  }

  if (wgm == 0xFF) {
    // HWA_ERR("WGM value could not be solved for _c8a class counter.");
    return 2 ;
  }

  p->solved.wgm = wgm ;


  /*	Solve the configuration of compare output A
   */
  if ( oc0->config.output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( oc0->config.output == HW_A1(_hw_oc8a_output_disconnected) )
      mode = 0 ;
    else if ( oc0->config.output == HW_A1(_hw_oc8a_output_toggle_on_match) )
      mode = 1 ;
    else if ( oc0->config.output == HW_A1(_hw_oc8a_output_clear_on_match)
	      || oc0->config.output == HW_A1(_hw_oc8a_output_set_at_bottom_clear_on_match)
	      || oc0->config.output == HW_A1(_hw_oc8a_output_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    oc0->solved.com = mode ;
  }


  /*	Solve the configuration of compare output B
   */
  if ( oc1->config.output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( oc1->config.output == HW_A1(_hw_oc8a_output_disconnected) )
      mode = 0 ;
    else if ( oc1->config.output == HW_A1(_hw_oc8a_output_toggle_on_match) )
      mode = 1 ;
    else if ( oc1->config.output == HW_A1(_hw_oc8a_output_clear_on_match)
	      || oc1->config.output == HW_A1(_hw_oc8a_output_set_at_bottom_clear_on_match)
	      || oc1->config.output == HW_A1(_hw_oc8a_output_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    oc1->solved.com = mode ;
  }


  /*	Check the validity of the configuration
   */
  if ( p->config.clock != 0xFF || oc0->config.output != 0xFF \
       || oc1->config.output != 0xFF ) {

    if ( p->config.clock == 0xFF ) {
      // HWA_ERR("configuration of counter is required.");
      return 3 ;
    }

    /*	Compare output A
     */
    if ( oc0->config.output != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( oc0->config.output != HW_A1(_hw_oc8a_output_disconnected)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_toggle_on_match)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_clear_on_match)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_set_on_match))
	  return 4 ;
	/* HWA_ERR("compare output A of class _c8a counter mode must be " */
	/* 	"'disconnected', 'toggle_on_match', 'clear_on_match', or " */
	/* 	"'set_on_match'."); */

      }
      else if ( wgm==3 ) {
	if ( oc0->config.output != HW_A1(_hw_oc8a_output_disconnected)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_set_at_bottom_clear_on_match)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_clear_at_bottom_set_on_match) )
	  return 5 ;
	/* HWA_ERR("compare output A of class _c8a counter mode must be " */
	/* 	"'disconnected', 'set_at_bottom_clear_on_match', or " */
	/* 	"'clear_at_bottom_set_on_match'."); */
      }
      else if ( wgm==7 ) {
	if ( oc0->config.output != HW_A1(_hw_oc8a_output_disconnected)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_toggle_on_match)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_set_at_bottom_clear_on_match)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_clear_at_bottom_set_on_match) )
	  return 6 ;
	/* HWA_ERR("compare output A of class _c8a counter mode must be " */
	/* 	"'disconnected', 'toggle_on_match', " */
	/* 	"'set_at_bottom_clear_on_match', or " */
	/* 	"'clear_at_bottom_set_on_match'."); */
      }
      else if ( wgm==1 ) {
	if ( oc0->config.output != HW_A1(_hw_oc8a_output_disconnected)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_clear_on_match_up_set_on_match_down)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_set_on_match_up_clear_on_match_down) )
	  /* HWA_ERR("compare output A of class _c8a counter mode must be " */
	  /* 	  "'disconnected', 'clear_on_match_up_set_on_match_down', " */
	  /* 	  "or 'set_on_match_up_clear_on_match_down'."); */
	  return 7 ;
      }
      else if ( wgm==5 ) {
	if ( oc0->config.output != HW_A1(_hw_oc8a_output_disconnected)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_toggle_on_match)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_clear_on_match_up_set_on_match_down)
	     && oc0->config.output != HW_A1(_hw_oc8a_output_set_on_match_up_clear_on_match_down) )
	  /* HWA_ERR("compare output A of class _c8a counter mode must be " */
	  /* 	  "'disconnected', 'toggle_on_match', " */
	  /* 	  "'clear_on_match_up_set_on_match_down', " */
	  /* 	  "or 'set_on_match_up_clear_on_match_down'."); */
	  return 8 ;
      }
    }

    /*	Compare output B
     */
    if ( oc1->config.output != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( oc1->config.output != HW_A1(_hw_oc8a_output_disconnected)
	     && oc1->config.output != HW_A1(_hw_oc8a_output_toggle_on_match)
	     && oc1->config.output != HW_A1(_hw_oc8a_output_clear_on_match)
	     && oc1->config.output != HW_A1(_hw_oc8a_output_set_on_match))
	  /* HWA_ERR("compare output B of class _c8a counter mode must be " */
	  /* 	  "'disconnected', 'toggle_on_match', 'clear_on_match', or " */
	  /* 	  "'set_on_match'."); */
	  return 9 ;
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( oc1->config.output != HW_A1(_hw_oc8a_output_disconnected)
	     && oc1->config.output != HW_A1(_hw_oc8a_output_set_at_bottom_clear_on_match)
	     && oc1->config.output != HW_A1(_hw_oc8a_output_clear_at_bottom_set_on_match) )
	  /* HWA_ERR("compare output B of class _c8a counter mode must be " */
	  /* 	  "'disconnected', 'set_at_bottom_clear_on_match', or " */
	  /* 	  "'clear_at_bottom_set_on_match'."); */
	  return 10 ;
      }
      else if ( wgm==1 || wgm==5 ) {
	if ( oc1->config.output != HW_A1(_hw_oc8a_output_disconnected)
	     && oc1->config.output != HW_A1(_hw_oc8a_output_clear_on_match_up_set_on_match_down)
	     && oc1->config.output != HW_A1(_hw_oc8a_output_set_on_match_up_clear_on_match_down) )
	  /* HWA_ERR("compare output B of class _c8a counter mode must be " */
	  /* 	  "'disconnected', 'clear_on_match_up_set_on_match_down', " */
	  /* 	  "or 'set_on_match_up_clear_on_match_down'."); */
	  return 11 ;
      }
    }

    /*	Update
     */
    if ( compare_update != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( compare_update != HW_A1(_hw_oc8a_update_immediately) )
	  /* HWA_ERR("optionnal parameter 'update' of class _c8a counter must be "\ */
	  /* 	  "'immediately'."); */
	  return 12 ;
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( compare_update != HW_A1(_hw_oc8a_update_at_bottom) )
	  /* HWA_ERR("optionnal parameter 'update' of class _c8a counter must be " */
	  /* 	  "'at_bottom'."); */
	  return 13 ;
      }
      else
	if( compare_update != HW_A1(_hw_oc8a_update_at_top) )
	  /* HWA_ERR("optionnal parameter 'update' of class _c8a counter must be " */
	  /* 	  "'at_top'."); */
	  return 14 ;
    }

    /*	Overflow
     */
    if ( overflow != 0xFF ) {
      if ( wgm==7 ) {
	if ( overflow != HW_A1(_hw_c8a_overflow_at_top) )
	  /* HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be " */
	  /* 	  "'at_top'."); */
	  return 15 ;
      }
      else if ( (wgm==1 || wgm==5) ) {
	if ( overflow != HW_A1(_hw_c8a_overflow_at_bottom) )
	  /* HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be " */
	  /* 	  "'at_bottom'."); */
	  return 16 ;
      }
      else if ( overflow != HW_A1(_hw_c8a_overflow_at_max) )
	/* HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be " */
	/* 	"'at_max'."); */
	return 17 ;
    }
  }

  return 0 ;
}

/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_cnt Count value
 *
 * The count value is accessible for reading and writing through the following
 * instructions:
 */

/**
 * @page atmelavr_c8a
 * @code
 * hw_read( COUNTER_NAME );
 * @endcode
 */
#define _hw_mthd_hw_read__c8a		, _hw_read_c8a
#define _hw_read_c8a(o,i,a,...)		HW_TX(_hw_read_reg(o,count),__VA_ARGS__)


/**
 * @page atmelavr_c8a
 * @code
 * hw_write( COUNTER_NAME, value );
 * @endcode
 */
#define _hw_mthd_hw_write__c8a		, _hw_write_c8a
#define _hw_write_c8a(o,i,a,v,...)	HW_TX(_hw_write_reg(o,count,v),__VA_ARGS__)

/**
 * @page atmelavr_c8a
 * @code
 * hwa_write( COUNTER_NAME, value );
 * @endcode
 */
#define _hw_mthd_hwa_write__c8a		, _hwa_write_c8a
#define _hwa_write_c8a(o,i,a,v,...)	HW_TX(_hwa_write_reg(o,count,v),__VA_ARGS__)

#if 0
/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_clear Clearing the counter (setting the value to 0)
 *
 * __Note__: this does not reset the prescaler.
 *
 * @code
 * hw/hwa_clear( COUNTER_NAME );
 * @endcode
 * @code
 * hw/hwa_write_reg( COUNTER_NAME, count, 0 );
 * @endcode
 */
#define _hw_mthd_hw_clear__c8a		, _hw_clear_c8a
#define _hw_clear_c8a(p,i,a,...)	HW_TX(_hw_write_reg(p,count,0),__VA_ARGS__)

#define _hw_mthd_hwa_clear__c8a		, _hwa_clear_c8a
#define _hwa_clear_c8a(p,i,a,...)	HW_TX(_hwa_write_reg(p,count,0),__VA_ARGS__)

/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_stat Status of the counter
 *
 * Available flags are:
 * * overflow
 * * compare0
 * * compare1
 *
 * These flags correspond to the interrupt requests the counter can
 * trigger.
 *
 * @code
 * //  Create a structure to receive the counter status
 * //
 * hw_stat_t(COUNTER_NAME) st ;
 *
 * //  Copy the counter status to the structure
 * //
 * st = hw_stat( COUNTER_NAME );
 *
 * //  Process the overflow flag
 * //
 * if ( st.overflow ) {
 *   hw_clear_irq( COUNTER_NAME, overflow );
 *   n_overflows++ ;
 * }
 * @endcode
 *
 * @code
 * //  Process the overflow flag
 * //
 * if ( hw_stat( COUNTER_NAME ).overflow ) {
 *   hw_clear_irq( COUNTER_NAME, overflow );
 *   n_overflows++ ;
 * }
 * @endcode
 */

#define _hw_mthd_hw_stat_t__c8a		, _hw_statt_c8a
#define _hw_statt_c8a(o,i,a,...)	HW_TX(_##o##_stat_t, __VA_ARGS__)

typedef union {
  uint8_t         byte ;
  struct {
    unsigned int  __0      : 1 ;
    unsigned int  overflow : 1 ;
    unsigned int  __2      : 1 ;
    unsigned int  compare1 : 1 ;
    unsigned int  compare0 : 1 ;
    unsigned int  __5to7   : 3 ;
  };
} _hw_c8a_stat_t ;

#define _hw_mthd_hw_stat__c8a		, _hw_stat_c8a
#define _hw_stat_c8a(o,i,a,...)		HW_TX(_hw_c8a_stat(_hw_read_reg(o, ifr)),__VA_ARGS__)

HW_INLINE _hw_c8a_stat_t _hw_c8a_stat( uint8_t byte )
{
  _hw_c8a_stat_t	st ;
  st.byte = byte ;
  return st ;
}
#endif


/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_st Status
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

#define _hwa_setup__c8a(o,i,a)			\
  /* _hwa_setup_reg( o, gtccr); */			\
  _hwa_setup_reg( o, ccra);			\
  _hwa_setup_reg( o, ccrb);			\
  _hwa_setup_reg( o, count);			\
  _hwa_setup_reg( o, imsk);			\
  _hwa_setup_reg( o, ifr);			\
  hwa->o.config.clock     = 0xFF;		\
  hwa->o.config.countmode = 0xFF;		\
  hwa->o.config.top       = 0xFF;		\
  hwa->o.config.overflow  = 0xFF


#define _hwa_init__c8a(o,i,a)					\
  /* _hwa_init_reg( o, gtccr, 0x00 ); */				\
  _hwa_init_reg( o, ccra,  0x00 );				\
  _hwa_init_reg( o, ccrb,  0x00 );				\
  _hwa_init_reg( o, count, 0x00 );				\
  _hwa_init_reg( o, imsk,  0x00 );				\
  _hwa_init_reg( o, ifr,   0x00 )


  /* hwa->o.config.clock     = HW_A1(_hw_c8a_clock_none);		\ */
  /* hwa->o.config.countmode = HW_A1(_hw_c8a_countmode_loop_up);	\ */
  /* hwa->o.config.top       = HW_A1(_hw_c8a_top_max);		\ */
  /* hwa->o.config.overflow  = HW_A1(_hw_c8a_overflow_at_max) */


#define _hwa_commit__c8a(o,i,a)			\
  /* _hwa_commit_reg( o, gtccr); */			\
  _hwa_commit_reg( o, ccra);			\
  _hwa_commit_reg( o, ccrb);			\
  _hwa_commit_reg( o, count);			\
  _hwa_commit_reg( o, imsk);			\
  _hwa_commit_reg( o, ifr)
  
/**
 * @page atmelavr_c8a
 * @section Internals
 *
 * Though it should not be necessary, internal registers are accessible through
 * the @ref public_reg_instructions "register access intructions".
 *
 * Class `_c8a` counters have the following hardware registers:
 *
 *  * `ccra`: control register a
 *  * `ccrb`: control register b
 *  * `count`: count register
 *  * `imsk`: interrupt mask register
 *  * `ifr`: interrupt flag register
 *
 * that hold the following logical registers:
 *
 *  * `wgm`: counting and waveform generation mode
 *  * `cs`: clock selection
 *  * `ie`: overflow interrupt mask
 *  * `if`: overflow interrupt flag
 */

/**
 * @page atmelavr_c8a
 * <br>
 */
