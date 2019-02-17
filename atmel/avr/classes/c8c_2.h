
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit counter
 */

HW_INLINE uint8_t _hw_c8cck_none( float v )
{
  if ( v != 0 )
    HWA_E_NIL(value of `clock`, (`none`, `ioclk [/ 8|32|64|128|256|512|1024]`, `external_osc`));

  return 0 ;
}

HW_INLINE uint8_t _hw_c8cck_ioclk( float v )
{
  if ( v == 1.0 )
    return 1 ;
  if ( v == 1.0/8 )
    return 2 ;
  if ( v == 1.0/32 )
    return 3 ;
  if ( v == 1.0/64 )
    return 4 ;
  if ( v == 1.0/128 )
    return 5 ;
  if ( v == 1.0/256 )
    return 6 ;
  if ( v == 1.0/1024 )
    return 7 ;

  HWA_E_NIL(value of `clock`, (`none`, `ioclk [/ 8|32|64|128|256|512|1024]`, `external_osc`));
  return 0 ;
}

HW_INLINE uint8_t _hw_c8cck_xosc( float v )
{
  if ( v != 0 )
    HWA_E_NIL(value of `clock`, (`none`, `ioclk [/ 8|32|64|128|256|512|1024]`, `external_osc`));

  return 8 ;
}

/**
 * @page atmelavr_c8c
 * @section atmelavr_c8c_config Configuration
 *
 * __Note__ If the optionnal argument `overflow` is not stated, HWA will select
 * an acceptable value according to the configuration of the compare units found
 * in the HWA context. If `overflow` is stated, HWA will check the validity of
 * its value.
 *
 * @code
 * hwa( configure, counter0,
 * 
 *      //  How the counter is clocked
 *      //
 *      clock,       none                       // No clock, the counter is stopped
 *                 | ioclk [/ 8|32|64|128       // I/O clock [divided]
 *                             |256|512|1024]   //
 *                 | external_xosc,                  // Crystal between pins TOSC1-TOSC2
 *
 *      //  How does this counter count
 *      //
 *      direction,   up_loop                    // Count up and loop
 *                 | updown_loop,               // Count up and down alternately
 *
 *      //  Class _c8c counters all count from 0
 *      //
 *    [ bottom,     0, ]
 *
 *      //  The maximum value the counter reaches (the default is `max`)
 *      //
 *    [ top,        fixed_0xFF                  // Hardware fixed value 0xFF
 *                | max                         // Hardware fixed value 0xFF
 *                | compare0, ]                 // Value stored in the compare0 unit
 *
 *      //  When the overflow flag is set
 *      //
 *    [ overflow,    after_bottom                  // When the counter resets to bottom
 *                | after_top                      // When the counter reaches the top value
 *                | after_max ]                    // When the counter reaches its max value
 *      );
 * @endcode
 */
#define hwa_configure__c8c	, _hwa_config_c8c

/*  Mandatory argument `clock`
 *
 *    Add 2 void arguments to the end of the list so that there are always
 *    3 arguments following the last non-void argument.
 */
#define _hwa_config_c8c(o,i,a,k,...)					\
  do { HW_Y(_hwa_cfc8c_kclock_,_hw_is_clock_##k)(o,k,__VA_ARGS__,,) } while(0)

#define _hwa_cfc8c_kclock_0(o,k,...)					\
  HW_E_VL(k,clock)

#define _hwa_cfc8c_kclock_1(o,k,v,...)					\
  HW_Y(_hwa_cfc8c_vclock_,_hw_c8c_clock_##v)(o,v,__VA_ARGS__)

#define _hwa_cfc8c_vclock_0(o,v,...)					\
  HW_E_AVL(clock, v, none | ioclk [/ 8|32|64|128|256|512|1024] | external_xosc)

#define _hwa_cfc8c_vclock_1(o,v,k,...)					\
  hwa->o.config.clock = HW_VF(_hw_c8c_clock_##v);			\
  HW_Y(_hwa_cfc8c_kmode_,_hw_is_direction_##k)(o,k,__VA_ARGS__)

#define _hw_c8c_clock_none		, _hw_c8cck_none, 0
#define _hw_c8c_clock_ioclk		, _hw_c8cck_ioclk, 1.0
#define _hw_c8c_clock_external_xosc		, _hw_c8cck_xosc, 0

/*  Optionnal argument `direction`
 */
#define _hw_c8c_direction_up_loop	, 1
#define _hw_c8c_direction_updown_loop	, 2

#define _hwa_cfc8c_kmode_0(o,k,...)					\
  HW_E_VL(k,direction)

#define _hwa_cfc8c_kmode_1(o,k,v,...)					\
  HW_Y(_hwa_cfc8c_vmode_,_hw_c8c_direction_##v)(o,v,__VA_ARGS__)

#define _hwa_cfc8c_vmode_0(o,v,...)					\
  HW_E_AVL(mode, v, up_loop | updown_loop)

#define _hwa_cfc8c_vmode_1(o,v,k,...)					\
  hwa->o.config.direction = HW_A1(_hw_c8c_direction_##v);			\
  HW_Y(_hwa_cfc8c_kbottom_,_hw_is_bottom_##k)(o,k,__VA_ARGS__)

/*  Optionnal argument `bottom`
 */
#define _hwa_cfc8c_kbottom_1(o,k,v,...)			\
  HW_G2(_hwa_cfc8c_vbottom,HW_IS(0,v))(o,v,__VA_ARGS__)

#define _hwa_cfc8c_vbottom_0(o,v,...)			\
  HW_E_AVL(bottom, v, `0`)

#define _hwa_cfc8c_vbottom_1(o,v,k,...)			\
  HW_Y(_hwa_cfc8c_ktop_,_hw_is_top_##k)(o,k,__VA_ARGS__)

#define _hwa_cfc8c_kbottom_0(o,k,...)			\
  HW_Y(_hwa_cfc8c_ktop_,_hw_is_top_##k)(o,k,__VA_ARGS__)

/*  Optionnal argument `top`
 */
#define _hw_c8c_top_fixed_0xFF			, 1
#define _hw_c8c_top_max			, 1
#define _hw_c8c_top_compare0		, 2

#define _hwa_cfc8c_ktop_1(o,k,v,...)					\
  HW_Y(_hwa_cfc8c_vtop_,_hw_c8c_top_##v)(o,v,__VA_ARGS__)

#define _hwa_cfc8c_vtop_0(o,v,...)				\
  HW_E_AVL(top, v, fixed_0xFF | max | compare0)

#define _hwa_cfc8c_vtop_1(o,v,k,...)					\
  hwa->o.config.top = HW_A1(_hw_c8c_top_##v);				\
  HW_Y(_hwa_cfc8c_koverflow_,_hw_is_overflow_##k)(o,k,__VA_ARGS__)

#define _hwa_cfc8c_ktop_0(o,k,...)					\
  HW_Y(_hwa_cfc8c_koverflow_,_hw_is_overflow_##k)(o,k,__VA_ARGS__)

/*  Optionnal argument `overflow`
 */
#define _hw_c8c_overflow_after_bottom	, 0
#define _hw_c8c_overflow_after_top		, 1
#define _hw_c8c_overflow_after_max		, 2

#define _hwa_cfc8c_koverflow_1(o,k,v,...)				\
  HW_Y(_hwa_cfc8c_voverflow_,_hw_c8c_overflow_##v)(o,v,__VA_ARGS__)

#define _hwa_cfc8c_voverflow_0(o,v,...)				\
  HW_E_OAVL(overflow, v, after_bottom | after_top | after_max)

#define _hwa_cfc8c_voverflow_1(o,v,...)				\
  if ( hwa->o.config.direction == HW_A1(_hw_c8c_direction_up_loop)		\
       && HW_A1(_hw_c8c_overflow_##v) == HW_A1(_hw_c8c_overflow_after_bottom) ) \
    HWA_ERR("optionnal parameter `overflow` can not be `after_bottom` "	\
	    "when direction is `up_loop`.");				\
  hwa->o.config.overflow = HW_A1(_hw_c8c_overflow_##v);  HW_EOL(__VA_ARGS__)

#define _hwa_cfc8c_koverflow_0(o,...)		\
  HW_EOL(__VA_ARGS__)


/**
 * @brief Solve and check the configuration of the counter and its compare units.
 *
 * Writing code for a HW_INLINE function is more comfortable than for a
 * function-like macro but functions can not use object names. So, this
 * function-like macro expands to the HW_INLINE function _hwa_solve_c8c() which
 * uses pointers on objects in the HWA context to compute values to be written
 * into the registers, stores them into the `solve` structure and returns an
 * error code that is processed by _hwa_solve__c8c() which knows the names of
 * the objects and then can put computed registers values into the context, even
 * in the case of external register access, and display accurate error messages.
 */
#define _hwa_solve__c8c( o,i,a )	_hwa_solve__c8c_2( o,		\
							   hw_##o##_compare0,	\
							   hw_##o##_compare1 )
#define _hwa_solve__c8c_2(...)		_hwa_solve__c8c_3(__VA_ARGS__)

#define _hwa_solve__c8c_3( o, compare0, compare1 )				\
  do {									\
    uint8_t r = _hwa_solve_c8c( &hwa->o, &hwa->compare0, &hwa->compare1 );	\
    if ( r == 1 )							\
      HWA_ERR("`update` must be the same for both compare units of `" #o "`."); \
    else if ( r == 2 )							\
      HWA_ERR("WGM value could not be solved for `" #o "`.");		\
    else if ( r == 3 )							\
      HWA_ERR("configuration of `" #o "` is required.");		\
    else if ( r == 4 )							\
      HWA_ERR("`mode` of `" #compare0 "` can be "				\
	      "'disconnected', 'toggle_after_match', 'clear_after_match', or " \
	      "'set_after_match'.");					\
    else if ( r == 5 )							\
      HWA_ERR("`mode` of `" #compare0 "` can be "				\
	      "'disconnected', 'set_at_bottom_clear_after_match', or "	\
	      "'clear_at_bottom_set_after_match'.");			\
    else if ( r == 6 )							\
      HWA_ERR("`mode` of `" #compare0 "` can be "				\
	      "'disconnected', 'toggle_after_match', "			\
	      "'set_at_bottom_clear_after_match', or "			\
	      "'clear_at_bottom_set_after_match'.");			\
    else if ( r == 7 )							\
      HWA_ERR("`mode` of `" #compare0 "` can be "				\
	      "'disconnected', 'clear_after_match_up_set_after_match_down', "	\
	      "or 'set_after_match_up_clear_after_match_down'.");		\
    else if ( r == 8 )							\
      HWA_ERR("`mode` of `" #compare0 "` can be "				\
	      "'disconnected', 'toggle_after_match', "			\
	      "'clear_after_match_up_set_after_match_down', "			\
	      "or 'set_after_match_up_clear_after_match_down'.");		\
    else if ( r == 9 )							\
      HWA_ERR("`mode` of `" #compare1 "` can be "				\
	      "'disconnected', 'toggle_after_match', 'clear_after_match', or " \
	      "'set_after_match'.");					\
    else if ( r == 10 )							\
      HWA_ERR("`mode` of `" #compare1 "` can be "				\
	      "'disconnected', 'set_at_bottom_clear_after_match', or "	\
	      "'clear_at_bottom_set_after_match'.");			\
    else if ( r == 11 )							\
      HWA_ERR("`mode` of `" #compare1 "` can be "				\
	      "'disconnected', 'clear_after_match_up_set_after_match_down', "	\
	      "or 'set_after_match_up_clear_after_match_down'.");		\
    else if ( r == 12 )							\
      HWA_ERR("for `" #o "`, `optionnal parameter 'update' must be 'immediately'."); \
    else if ( r == 13 )							\
      HWA_ERR("for `" #o "`, `optionnal parameter 'update' must be 'after_bottom'."); \
    else if ( r == 14 )							\
      HWA_ERR("for `" #o "`, `optionnal parameter 'update' must be 'after_top'."); \
    else if ( r == 15 )							\
      HWA_ERR("for `" #o "`, `optionnal parameter 'overflow' must be 'after_top'."); \
    else if ( r == 16 )							\
      HWA_ERR("for `" #o "`, `optionnal parameter 'overflow' must be 'after_bottom'."); \
    else if ( r == 17 )							\
      HWA_ERR("for `" #o "`, `optionnal parameter 'overflow' must be 'after_max'."); \
    else {								\
      /*								\
       *  Write solved registers					\
       */								\
      if ( hwa->o.solved.cs != 0xFF ) _hwa_write( o, cs, hwa->o.solved.cs ); \
      if ( hwa->o.solved.wgm != 0xFF ) _hwa_write( o, wgm, hwa->o.solved.wgm ); \
      if ( hwa->compare0.solved.com != 0xFF ) _hwa_write( compare0, com, hwa->compare0.solved.com ); \
      if ( hwa->compare1.solved.com != 0xFF ) _hwa_write( compare1, com, hwa->compare1.solved.com ); \
      /*								\
       *  Configure used compare outputs as i/o outputs			\
       */								\
      if ( hwa->compare0.config.output != 0xFF				\
	   && hwa->compare0.config.output != HW_A1(_hw_cmp8a_output_disconnected) ) \
	_hwa( configure, (compare0,pin), mode, digital_output );		\
      if ( hwa->compare1.config.output != 0xFF				\
	   && hwa->compare1.config.output != HW_A1(_hw_cmp8a_output_disconnected) ) \
	_hwa( configure, (compare1,pin), mode, digital_output );		\
    }									\
  } while(0)


HW_INLINE uint8_t _hwa_solve_c8c ( hwa_c8c_t *p, hwa_cmp8a_t *compare0, hwa_cmp8a_t *compare1	 )
{
  /*	0xFF == unchanged
   */
  p->solved.cs	  = 0xFF ;
  p->solved.wgm	  = 0xFF ;
  compare0->solved.com = 0xFF ;
  compare1->solved.com = 0xFF ;

  if ( p->config.clock == 0xFF )
    return 0 ;

  /*	Clock selection
   */
  p->solved.cs = p->config.clock ;

  /*  Default config for top
   */
  if ( p->config.top == 0xFF )
    p->config.top = HW_A1(_hw_c8c_top_max);

  /*  Default config for overflow
   */
  uint8_t overflow = p->config.overflow ;
  if ( overflow == 0xFF && p->config.top == HW_A1(_hw_c8c_top_compare0) ) {
    if ( p->config.direction == HW_A1(_hw_c8c_direction_up_loop) )
      overflow = HW_A1(_hw_c8c_overflow_after_top);
    else /* if ( p->config.direction == HW_A1(_hw_c8c_direction_up_loop) ) */
      overflow = HW_A1(_hw_c8c_overflow_after_bottom);
  }

  /*  Compare update setting
   */
  uint8_t compare_update = 0xFF ;
  if ( compare0->config.update != 0xFF && compare1->config.update != 0xFF
       && compare0->config.update != compare1->config.update )
    return 1 ; //HWA_ERR("`update` must be the same for both compare units.");

  compare_update = compare0->config.update ;


  /* Mode WGM  Operation  COUNTMODE    TOP   UPD  OVF  OCA		      OCB
   *						
   *  0	  000  Normal	  LOOP_UP      0xFF  IMM  MAX  DIS,ToM,CoM,SoM	      DIS,ToM,CoM,SoM
   *  2	  010  CTC	  LOOP_UP      OCRA  IMM  MAX  DIS,ToM,CoM,SoM	      DIS,ToM,CoM,SoM
   *
   *  3	  011  Fast PWM	  LOOP_UP      0xFF  BOT  MAX  DIS,SaBCoM,CaBSoM      DIS,SaBCoM,CaBSoM
   *  7	  111  Fast PWM	  LOOP_UP      OCRA  BOT  TOP  DIS,ToM,CoMSaB,SoMCaB  DIS,SaBCoM,CaBSoM
   *
   *  1	  001  PWM, PhC	  LOOP_UPDOWN  0xFF  TOP  BOT  DIS,CmuSmd,SmuCmd      DIS,CmuSmd,SmuCmd	  
   *  5	  101  PWM, PhC	  LOOP_UPDOWN  OCRA  TOP  BOT  DIS,ToM,CmuSmd,SmuCmd  DIS,CmuSmd,SmuCmd
   *
   *  4	  100  *Reserved*
   *  6	  110  *Reserved*
   */

  /*	Determine WGM
   */
  uint8_t wgm = 0xFF ;
  if ( p->config.direction == HW_A1(_hw_c8c_direction_up_loop) ) {
    if ( p->config.top == HW_A1(_hw_c8c_top_fixed_0xFF) ) {
      if ( compare_update == HW_A1(_hw_cmp8a_update_after_bottom)
	   || compare0->config.output == HW_A1(_hw_cmp8a_output_clear_at_bottom_set_after_match)
	   || compare0->config.output == HW_A1(_hw_cmp8a_output_set_at_bottom_clear_after_match)
	   || compare1->config.output == HW_A1(_hw_cmp8a_output_clear_at_bottom_set_after_match)
	   || compare1->config.output == HW_A1(_hw_cmp8a_output_set_at_bottom_clear_after_match))
	wgm = 3 ;
      else 
	wgm = 0 ;
    }
    else /* top == ocra */ {
      /*
       *  FIXME: a change of output_mode from one of the 4 modes below to
       *  'disconnected' causes a useless modification of wgm from 7 to 2. As
       *  wgm2 is not in the same register as wgm1:0, this generates useless
       *  code.
       */
      if ( compare_update == HW_A1(_hw_cmp8a_update_after_bottom )
	   || overflow == HW_A1(_hw_c8c_overflow_after_top)
	   || compare0->config.output == HW_A1(_hw_cmp8a_output_clear_at_bottom_set_after_match)
	   || compare0->config.output == HW_A1(_hw_cmp8a_output_set_at_bottom_clear_after_match)
	   || compare1->config.output == HW_A1(_hw_cmp8a_output_clear_at_bottom_set_after_match)
	   || compare1->config.output == HW_A1(_hw_cmp8a_output_set_at_bottom_clear_after_match))
	wgm = 7 ;
      else
	wgm = 2 ;
    }
  }
  else /* direction == updown_loop */ {
    if ( p->config.top == HW_A1(_hw_c8c_top_fixed_0xFF) )
      wgm = 1 ;
    else /* top == ocra */
      wgm = 5 ;
  }

  if (wgm == 0xFF) {
    // HWA_ERR("WGM value could not be solved for _c8c class counter.");
    return 2 ;
  }

  p->solved.wgm = wgm ;


  /*	Solve the configuration of compare output A
   */
  if ( compare0->config.output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( compare0->config.output == HW_A1(_hw_cmp8a_output_disconnected) )
      mode = 0 ;
    else if ( compare0->config.output == HW_A1(_hw_cmp8a_output_toggle_after_match) )
      mode = 1 ;
    else if ( compare0->config.output == HW_A1(_hw_cmp8a_output_clear_after_match)
	      || compare0->config.output == HW_A1(_hw_cmp8a_output_set_at_bottom_clear_after_match)
	      || compare0->config.output == HW_A1(_hw_cmp8a_output_clear_after_match_up_set_after_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    compare0->solved.com = mode ;
  }


  /*	Solve the configuration of compare output B
   */
  if ( compare1->config.output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( compare1->config.output == HW_A1(_hw_cmp8a_output_disconnected) )
      mode = 0 ;
    else if ( compare1->config.output == HW_A1(_hw_cmp8a_output_toggle_after_match) )
      mode = 1 ;
    else if ( compare1->config.output == HW_A1(_hw_cmp8a_output_clear_after_match)
	      || compare1->config.output == HW_A1(_hw_cmp8a_output_set_at_bottom_clear_after_match)
	      || compare1->config.output == HW_A1(_hw_cmp8a_output_clear_after_match_up_set_after_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    compare1->solved.com = mode ;
  }


  /*	Check the validity of the configuration
   */
  if ( p->config.clock != 0xFF || compare0->config.output != 0xFF \
       || compare1->config.output != 0xFF ) {

    if ( p->config.clock == 0xFF ) {
      // HWA_ERR("configuration of counter is required.");
      return 3 ;
    }

    /*	Compare output A
     */
    if ( compare0->config.output != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( compare0->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_toggle_after_match)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_clear_after_match)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_set_after_match))
	  return 4 ;
	/* HWA_ERR("compare output A of class _c8c counter mode must be " */
	/*	"'disconnected', 'toggle_after_match', 'clear_after_match', or " */
	/*	"'set_after_match'."); */

      }
      else if ( wgm==3 ) {
	if ( compare0->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_set_at_bottom_clear_after_match)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_clear_at_bottom_set_after_match) )
	  return 5 ;
	/* HWA_ERR("compare output A of class _c8c counter mode must be " */
	/*	"'disconnected', 'set_at_bottom_clear_after_match', or " */
	/*	"'clear_at_bottom_set_after_match'."); */
      }
      else if ( wgm==7 ) {
	if ( compare0->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_toggle_after_match)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_set_at_bottom_clear_after_match)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_clear_at_bottom_set_after_match) )
	  return 6 ;
	/* HWA_ERR("compare output A of class _c8c counter mode must be " */
	/*	"'disconnected', 'toggle_after_match', " */
	/*	"'set_at_bottom_clear_after_match', or " */
	/*	"'clear_at_bottom_set_after_match'."); */
      }
      else if ( wgm==1 ) {
	if ( compare0->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_clear_after_match_up_set_after_match_down)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_set_after_match_up_clear_after_match_down) )
	  /* HWA_ERR("compare output A of class _c8c counter mode must be " */
	  /*	  "'disconnected', 'clear_after_match_up_set_after_match_down', " */
	  /*	  "or 'set_after_match_up_clear_after_match_down'."); */
	  return 7 ;
      }
      else if ( wgm==5 ) {
	if ( compare0->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_toggle_after_match)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_clear_after_match_up_set_after_match_down)
	     && compare0->config.output != HW_A1(_hw_cmp8a_output_set_after_match_up_clear_after_match_down) )
	  /* HWA_ERR("compare output A of class _c8c counter mode must be " */
	  /*	  "'disconnected', 'toggle_after_match', " */
	  /*	  "'clear_after_match_up_set_after_match_down', " */
	  /*	  "or 'set_after_match_up_clear_after_match_down'."); */
	  return 8 ;
      }
    }

    /*	Compare output B
     */
    if ( compare1->config.output != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( compare1->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	     && compare1->config.output != HW_A1(_hw_cmp8a_output_toggle_after_match)
	     && compare1->config.output != HW_A1(_hw_cmp8a_output_clear_after_match)
	     && compare1->config.output != HW_A1(_hw_cmp8a_output_set_after_match))
	  /* HWA_ERR("compare output B of class _c8c counter mode must be " */
	  /*	  "'disconnected', 'toggle_after_match', 'clear_after_match', or " */
	  /*	  "'set_after_match'."); */
	  return 9 ;
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( compare1->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	     && compare1->config.output != HW_A1(_hw_cmp8a_output_set_at_bottom_clear_after_match)
	     && compare1->config.output != HW_A1(_hw_cmp8a_output_clear_at_bottom_set_after_match) )
	  /* HWA_ERR("compare output B of class _c8c counter mode must be " */
	  /*	  "'disconnected', 'set_at_bottom_clear_after_match', or " */
	  /*	  "'clear_at_bottom_set_after_match'."); */
	  return 10 ;
      }
      else if ( wgm==1 || wgm==5 ) {
	if ( compare1->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	     && compare1->config.output != HW_A1(_hw_cmp8a_output_clear_after_match_up_set_after_match_down)
	     && compare1->config.output != HW_A1(_hw_cmp8a_output_set_after_match_up_clear_after_match_down) )
	  /* HWA_ERR("compare output B of class _c8c counter mode must be " */
	  /*	  "'disconnected', 'clear_after_match_up_set_after_match_down', " */
	  /*	  "or 'set_after_match_up_clear_after_match_down'."); */
	  return 11 ;
      }
    }

    /*	Update
     */
    if ( compare_update != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( compare_update != HW_A1(_hw_cmp8a_update_immediately) )
	  /* HWA_ERR("optionnal parameter 'update' of class _c8c counter must be "\ */
	  /*	  "'immediately'."); */
	  return 12 ;
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( compare_update != HW_A1(_hw_cmp8a_update_after_bottom) )
	  /* HWA_ERR("optionnal parameter 'update' of class _c8c counter must be " */
	  /*	  "'after_bottom'."); */
	  return 13 ;
      }
      else
	if( compare_update != HW_A1(_hw_cmp8a_update_after_top) )
	  /* HWA_ERR("optionnal parameter 'update' of class _c8c counter must be " */
	  /*	  "'after_top'."); */
	  return 14 ;
    }

    /*	Overflow
     */
    if ( overflow != 0xFF ) {
      if ( wgm==7 ) {
	if ( overflow != HW_A1(_hw_c8c_overflow_after_top) )
	  /* HWA_ERR("optionnal parameter 'overflow' of class _c8c counter must be " */
	  /*	  "'after_top'."); */
	  return 15 ;
      }
      else if ( (wgm==1 || wgm==5) ) {
	if ( overflow != HW_A1(_hw_c8c_overflow_after_bottom) )
	  /* HWA_ERR("optionnal parameter 'overflow' of class _c8c counter must be " */
	  /*	  "'after_bottom'."); */
	  return 16 ;
      }
      else if ( overflow != HW_A1(_hw_c8c_overflow_after_max) )
	/* HWA_ERR("optionnal parameter 'overflow' of class _c8c counter must be " */
	/*	"'after_max'."); */
	return 17 ;
    }
  }

  return 0 ;
}


/**
 * @page atmelavr_c8c
 * @section atmelavr_c8c_cnt Count value
 *
 * __Note__ See [that
 * thread](http://www.avrfreaks.net/comment/141688#comment-141688) on [AVR
 * Freaks](http://www.avrfreaks.net) for count register write issues.
 *
 * The count value is accessible for reading and writing through the following
 * instructions:
 */
/**
 * @page atmelavr_c8c
 * @code
 * hw( read, counter0 );
 * @endcode
 */
#define hw_read__c8c		, _hw_read_c8c
#define _hw_read_c8c(o,i,a,...)		_hw_read(o,count) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_c8c
 * @code
 * hw( write, counter0, value );
 * @endcode
 */
#define hw_write__c8c		, _hw_write_c8c
#define _hw_write_c8c(o,i,a,v,...)	_hw_write(o,count,v) HW_EOL(__VA_ARGS__)

/**
 * @page atmelavr_c8c
 * @code
 * hwa( write, counter0, value );
 * @endcode
 */
#define hwa_write__c8c		, _hwa_write_c8c
#define _hwa_write_c8c(o,i,a,v)		_hwa_write(o,count,v)

#if 0
/**
 * @page atmelavr_c8c
 *
 *  * setting the count value to 0 (this does not reset the prescaler):
 *
 * @code
 *`hw( clear, counter0 )`;
 * @endcode
 */
#define hw_clear__c8c		, _hw_clear_c8c
#define _hw_clear_c8c(o,i,a,...)	_hw_write(o,count,0) HW_EOL(__VA_ARGS__)

/**
 * @page atmelavr_c8c
 *
 * @code
 * hwa( clear, counter0 );
 * @endcode
 */
#define hwa_clear__c8c		, _hwa_clear_c8c
#define _hwa_clear_c8c(o,i,a,...)	_hwa_write(o,count,0) HW_EOL(__VA_ARGS__)
#endif


/**
 * @page atmelavr_c8c
 * @section atmelavr_c8c_st Status
 *
 * The overflow flag can be accessed through interrupt-related instructions:
 *
 * @code
 * if ( hw( read, irqflag( counter0 ) ) ) {	// Read overflow IRQ flag
 *   hw( clear, irqflag( counter0 ) );		// Clear overflow IRQ flag
 *   hw( turn, irq(counter0), off );		// Disable overflow IRQs
 * }
 * @endcode
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__c8c(o,i,a)			\
  _hwa_setup_r( o, ccra);			\
  _hwa_setup_r( o, ccrb);			\
  _hwa_setup_r( o, count);			\
  _hwa_setup_r( o, imsk);			\
  _hwa_setup_r( o, ifr);			\
  hwa->o.config.clock	  = 0xFF;		\
  hwa->o.config.direction = 0xFF;		\
  hwa->o.config.top	  = 0xFF;		\
  hwa->o.config.overflow  = 0xFF


#define _hwa_init__c8c(o,i,a)					\
  _hwa_init_r( o, ccra,  0x00 );				\
  _hwa_init_r( o, ccrb,  0x00 );				\
  _hwa_init_r( o, count, 0x00 );				\
  _hwa_init_r( o, imsk,  0x00 );				\
  _hwa_init_r( o, ifr,   0x00 )


  /* hwa->o.config.clock     = HW_A1(_hw_c8c_clock_none);		\ */
  /* hwa->o.config.direction = HW_A1(_hw_c8c_direction_up_loop);	\ */
  /* hwa->o.config.top	     = HW_A1(_hw_c8c_top_max);		\ */
  /* hwa->o.config.overflow  = HW_A1(_hw_c8c_overflow_after_max) */


#define _hwa_commit__c8c(o,i,a)			\
  /* _hwa_commit_r( o, gtccr); */			\
  _hwa_commit_r( o, ccra);			\
  _hwa_commit_r( o, ccrb);			\
  _hwa_commit_r( o, count);			\
  _hwa_commit_r( o, imsk);			\
  _hwa_commit_r( o, ifr)
  

/**
 * @page atmelavr_c8c
 * @section atmelavr_c8c_internals Internals
 *
 * Class `_c8c` objects hold the following hardware registers:
 *
 *  * `ccra`: control register a
 *  * `ccrb`: control register b
 *  * `count`: count register
 *  * `imsk`: interrupt mask register
 *  * `ifr`: interrupt flag register
 *  * `assr`: asynchronous status register
 *
 * that hold the following logical registers:
 *
 *  * `wgm`: counting and waveform generation mode
 *  * `cs`: clock selection
 *  * `ie`: overflow interrupt mask
 *  * `if`: overflow interrupt flag
 *
 * These registers are accessible through the @ref public_ins
 * "register access intructions".
 */


/**
 * @page atmelavr_c8c
 * <br>
 */
