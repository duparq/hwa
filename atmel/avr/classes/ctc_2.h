
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit counter
 */

HW_INLINE uint8_t _hw_ctcck_none( float v )
{
  if ( v != 0 )
    HWA_E_NIL(value of `clock`, (`none`, `ioclk [/ 8|32|64|128|256|512|1024]`, `external_osc`));

  return 0 ;
}

HW_INLINE uint8_t _hw_ctcck_ioclk( float v )
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

HW_INLINE uint8_t _hw_ctcck_xosc( float v )
{
  if ( v != 0 )
    HWA_E_NIL(value of `clock`, (`none`, `ioclk [/ 8|32|64|128|256|512|1024]`, `external_osc`));

  return 8 ;
}

/**
 * @page atmelavr_ctc
 * @section atmelavr_ctc_act Actions
 *
 * <br>
 * `configure`:
 *
 * __Note__ If the optionnal argument `overflow` is not stated, HWA will select
 * an acceptable value according to the configuration of the compare units found
 * in the HWA context. If `overflow` is stated, HWA will check the validity of
 * its value.
 *
 * @code
 * hwa( configure, counter0,
 * 
 *	//  How the counter is clocked
 *	//
 *	clock,	     none			// No clock, the counter is stopped
 *		   | ioclk [/ 8|32|64|128	// I/O clock [divided]
 *			       |256|512|1024]	//
 *		   | external_xosc,		     // Crystal between pins TOSC1-TOSC2
 *
 *	//  How does this counter count
 *	//
 *	direction,   up_loop			// Count up and loop
 *		   | updown_loop,		// Count up and down alternately
 *
 *	//  Class _ctc counters all count from 0
 *	//
 *    [ bottom,	    0, ]
 *
 *	//  The maximum value the counter reaches (the default is `max`)
 *	//
 *    [ top,	    fixed_0xFF			// Hardware fixed value 0xFF
 *		  | max				// Hardware fixed value 0xFF
 *		  | compare0, ]			// Value stored in the compare0 unit
 *
 *	//  When the overflow flag is set
 *	//
 *    [ overflow,   after_bottom		// When the counter resets to bottom
 *		  | after_top			// When the counter reaches the top value
 *		  | after_max ]			// When the counter reaches its max value
 *	);
 * @endcode
 */
#define hwa_configure__ctc		, _hwa_config_ctc

/*  Mandatory argument `clock`
 *
 *    Add 2 void arguments to the end of the list so that there are always
 *    3 arguments following the last non-void argument.
 */
#define _hwa_config_ctc(o,a,k,...)					\
  do { HW_B(_hwa_cfctc_kclock_,_hw_is_clock_##k)(o,k,__VA_ARGS__,,) } while(0)

#define _hwa_cfctc_kclock_0(o,k,...)					\
  HW_E_VL(k,clock)

#define _hwa_cfctc_kclock_1(o,k,v,...)					\
  HW_B(_hwa_cfctc_vclock_,_hw_ctc_clock_##v)(o,v,__VA_ARGS__)

#define _hwa_cfctc_vclock_0(o,v,...)					\
  HW_E_AVL(clock, v, none | ioclk [/ 8|32|64|128|256|512|1024] | external_xosc)

#define _hwa_cfctc_vclock_1(o,v,k,...)					\
  hwa->o.config.clock = HW_VF(_hw_ctc_clock_##v);			\
  HW_B(_hwa_cfctc_kmode_,_hw_is_direction_##k)(o,k,__VA_ARGS__)

#define _hw_ctc_clock_none		, _hw_ctcck_none, 0
#define _hw_ctc_clock_ioclk		, _hw_ctcck_ioclk, 1.0
#define _hw_ctc_clock_external_xosc	, _hw_ctcck_xosc, 0

/*  Optionnal argument `direction`
 */
#define _hw_ctc_direction_up_loop	, 1
#define _hw_ctc_direction_updown_loop	, 2

#define _hwa_cfctc_kmode_0(o,k,...)					\
  HW_E_VL(k,direction)

#define _hwa_cfctc_kmode_1(o,k,v,...)					\
  HW_B(_hwa_cfctc_vmode_,_hw_ctc_direction_##v)(o,v,__VA_ARGS__)

#define _hwa_cfctc_vmode_0(o,v,...)					\
  HW_E_AVL(mode, v, up_loop | updown_loop)

#define _hwa_cfctc_vmode_1(o,v,k,...)					\
  hwa->o.config.direction = HW_A1(_hw_ctc_direction_##v);			\
  HW_B(_hwa_cfctc_kbottom_,_hw_is_bottom_##k)(o,k,__VA_ARGS__)

/*  Optionnal argument `bottom`
 */
#define _hwa_cfctc_kbottom_1(o,k,v,...)			\
  HW_G2(_hwa_cfctc_vbottom,HW_IS(0,v))(o,v,__VA_ARGS__)

#define _hwa_cfctc_vbottom_0(o,v,...)			\
  HW_E_AVL(bottom, v, `0`)

#define _hwa_cfctc_vbottom_1(o,v,k,...)			\
  HW_B(_hwa_cfctc_ktop_,_hw_is_top_##k)(o,k,__VA_ARGS__)

#define _hwa_cfctc_kbottom_0(o,k,...)			\
  HW_B(_hwa_cfctc_ktop_,_hw_is_top_##k)(o,k,__VA_ARGS__)

/*  Optionnal argument `top`
 */
#define _hw_ctc_top_fixed_0xFF			, 1
#define _hw_ctc_top_max			, 1
#define _hw_ctc_top_compare0		, 2

#define _hwa_cfctc_ktop_1(o,k,v,...)					\
  HW_B(_hwa_cfctc_vtop_,_hw_ctc_top_##v)(o,v,__VA_ARGS__)

#define _hwa_cfctc_vtop_0(o,v,...)				\
  HW_E_AVL(top, v, fixed_0xFF | max | compare0)

#define _hwa_cfctc_vtop_1(o,v,k,...)					\
  hwa->o.config.top = HW_A1(_hw_ctc_top_##v);				\
  HW_B(_hwa_cfctc_koverflow_,_hw_is_overflow_##k)(o,k,__VA_ARGS__)

#define _hwa_cfctc_ktop_0(o,k,...)					\
  HW_B(_hwa_cfctc_koverflow_,_hw_is_overflow_##k)(o,k,__VA_ARGS__)

/*  Optionnal argument `overflow`
 */
#define _hw_ctc_overflow_after_bottom	, 0
#define _hw_ctc_overflow_after_top	, 1
#define _hw_ctc_overflow_after_max	, 2

#define _hwa_cfctc_koverflow_1(o,k,v,...)				\
  HW_B(_hwa_cfctc_voverflow_,_hw_ctc_overflow_##v)(o,v,__VA_ARGS__)

#define _hwa_cfctc_voverflow_0(o,v,...)				\
  HW_E_OAVL(overflow, v, after_bottom | after_top | after_max)

#define _hwa_cfctc_voverflow_1(o,v,...)				\
  if ( hwa->o.config.direction == HW_A1(_hw_ctc_direction_up_loop)		\
       && HW_A1(_hw_ctc_overflow_##v) == HW_A1(_hw_ctc_overflow_after_bottom) ) \
    HWA_ERR("optionnal parameter `overflow` can not be `after_bottom` "	\
	    "when direction is `up_loop`.");				\
  hwa->o.config.overflow = HW_A1(_hw_ctc_overflow_##v);	 HW_EOL(__VA_ARGS__)

#define _hwa_cfctc_koverflow_0(o,...)		\
  HW_EOL(__VA_ARGS__)


/**
 * @brief Solve and check the configuration of the counter and its compare units.
 *
 * Writing code for a HW_INLINE function is more comfortable than for a
 * function-like macro but functions can not use object names. So, this
 * function-like macro expands to the HW_INLINE function _hwa_solve_ctc() which
 * uses pointers on objects in the HWA context to compute values to be written
 * into the registers, stores them into the `solve` structure and returns an
 * error code that is processed by _hwa_solve__ctc() which knows the names of
 * the objects and then can put computed registers values into the context, even
 * in the case of external register access, and display accurate error messages.
 */
#define _hwa_solve__ctc( o, a )						\
  do {									\
    uint8_t r = _hwa_solve_ctc( &hwa->o, &hwa->o.compare0, &hwa->o.compare1 );	\
    if ( r == 1 )							\
      HWA_ERR("`update` must be the same for both compare units of `" #o "`."); \
    else if ( r == 2 )							\
      HWA_ERR("WGM value could not be solved for `" #o "`.");		\
    else if ( r == 3 )							\
      HWA_ERR("configuration of `" #o "` is required.");		\
    else if ( r == 4 )							\
      HWA_ERR("`mode` of compare0 can be "				\
	      "'disconnected', 'toggle_after_match', 'clear_after_match', or " \
	      "'set_after_match'.");					\
    else if ( r == 5 )							\
      HWA_ERR("`mode` of compare0 can be "				\
	      "'disconnected', 'set_at_bottom_clear_after_match', or "	\
	      "'clear_at_bottom_set_after_match'.");			\
    else if ( r == 6 )							\
      HWA_ERR("`mode` of compare0 can be "				\
	      "'disconnected', 'toggle_after_match', "			\
	      "'set_at_bottom_clear_after_match', or "			\
	      "'clear_at_bottom_set_after_match'.");			\
    else if ( r == 7 )							\
      HWA_ERR("`mode` of compare0 can be "				\
	      "'disconnected', 'clear_after_match_up_set_after_match_down', "	\
	      "or 'set_after_match_up_clear_after_match_down'.");		\
    else if ( r == 8 )							\
      HWA_ERR("`mode` of compare0 can be "				\
	      "'disconnected', 'toggle_after_match', "			\
	      "'clear_after_match_up_set_after_match_down', "			\
	      "or 'set_after_match_up_clear_after_match_down'.");		\
    else if ( r == 9 )							\
      HWA_ERR("`mode` of compare1 can be "				\
	      "'disconnected', 'toggle_after_match', 'clear_after_match', or " \
	      "'set_after_match'.");					\
    else if ( r == 10 )							\
      HWA_ERR("`mode` of compare1 can be "				\
	      "'disconnected', 'set_at_bottom_clear_after_match', or "	\
	      "'clear_at_bottom_set_after_match'.");			\
    else if ( r == 11 )							\
      HWA_ERR("`mode` of compare1 can be "				\
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
      if ( hwa->o.compare0.solved.com != 0xFF ) _hwa_write( o, com0, hwa->o.compare0.solved.com ); \
      if ( hwa->o.compare1.solved.com != 0xFF ) _hwa_write( o, com1, hwa->o.compare1.solved.com ); \
      /*								\
       *  Configure used compare outputs as i/o outputs			\
       */								\
      if ( hwa->o.compare0.config.output != 0xFF				\
	   && hwa->o.compare0.config.output != HW_A1(_hw_oca_output_disconnected) ) \
	_hwa( configure, (o,compare0,pin), mode, digital_output );	\
      if ( hwa->o.compare1.config.output != 0xFF				\
	   && hwa->o.compare1.config.output != HW_A1(_hw_oca_output_disconnected) ) \
	_hwa( configure, (o,compare1,pin), mode, digital_output );	\
    }									\
  } while(0)


HW_INLINE uint8_t _hwa_solve_ctc ( hwa_ctc_t *p, hwa_oca_t *compare0, hwa_oca_t *compare1	 )
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
    p->config.top = HW_A1(_hw_ctc_top_max);

  /*  Default config for overflow
   */
  uint8_t overflow = p->config.overflow ;
  if ( overflow == 0xFF && p->config.top == HW_A1(_hw_ctc_top_compare0) ) {
    if ( p->config.direction == HW_A1(_hw_ctc_direction_up_loop) )
      overflow = HW_A1(_hw_ctc_overflow_after_top);
    else /* if ( p->config.direction == HW_A1(_hw_ctc_direction_up_loop) ) */
      overflow = HW_A1(_hw_ctc_overflow_after_bottom);
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
  if ( p->config.direction == HW_A1(_hw_ctc_direction_up_loop) ) {
    if ( p->config.top == HW_A1(_hw_ctc_top_fixed_0xFF) ) {
      if ( compare_update == HW_A1(_hw_oca_update_after_bottom)
	   || compare0->config.output == HW_A1(_hw_oca_output_clear_at_bottom_set_after_match)
	   || compare0->config.output == HW_A1(_hw_oca_output_set_at_bottom_clear_after_match)
	   || compare1->config.output == HW_A1(_hw_oca_output_clear_at_bottom_set_after_match)
	   || compare1->config.output == HW_A1(_hw_oca_output_set_at_bottom_clear_after_match))
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
      if ( compare_update == HW_A1(_hw_oca_update_after_bottom )
	   || overflow == HW_A1(_hw_ctc_overflow_after_top)
	   || compare0->config.output == HW_A1(_hw_oca_output_clear_at_bottom_set_after_match)
	   || compare0->config.output == HW_A1(_hw_oca_output_set_at_bottom_clear_after_match)
	   || compare1->config.output == HW_A1(_hw_oca_output_clear_at_bottom_set_after_match)
	   || compare1->config.output == HW_A1(_hw_oca_output_set_at_bottom_clear_after_match))
	wgm = 7 ;
      else
	wgm = 2 ;
    }
  }
  else /* direction == updown_loop */ {
    if ( p->config.top == HW_A1(_hw_ctc_top_fixed_0xFF) )
      wgm = 1 ;
    else /* top == ocra */
      wgm = 5 ;
  }

  if (wgm == 0xFF) {
    // HWA_ERR("WGM value could not be solved for _ctc class counter.");
    return 2 ;
  }

  p->solved.wgm = wgm ;


  /*	Solve the configuration of compare output A
   */
  if ( compare0->config.output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( compare0->config.output == HW_A1(_hw_oca_output_disconnected) )
      mode = 0 ;
    else if ( compare0->config.output == HW_A1(_hw_oca_output_toggle_after_match) )
      mode = 1 ;
    else if ( compare0->config.output == HW_A1(_hw_oca_output_clear_after_match)
	      || compare0->config.output == HW_A1(_hw_oca_output_set_at_bottom_clear_after_match)
	      || compare0->config.output == HW_A1(_hw_oca_output_clear_after_match_up_set_after_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    compare0->solved.com = mode ;
  }


  /*	Solve the configuration of compare output B
   */
  if ( compare1->config.output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( compare1->config.output == HW_A1(_hw_oca_output_disconnected) )
      mode = 0 ;
    else if ( compare1->config.output == HW_A1(_hw_oca_output_toggle_after_match) )
      mode = 1 ;
    else if ( compare1->config.output == HW_A1(_hw_oca_output_clear_after_match)
	      || compare1->config.output == HW_A1(_hw_oca_output_set_at_bottom_clear_after_match)
	      || compare1->config.output == HW_A1(_hw_oca_output_clear_after_match_up_set_after_match_down) )
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
	if ( compare0->config.output != HW_A1(_hw_oca_output_disconnected)
	     && compare0->config.output != HW_A1(_hw_oca_output_toggle_after_match)
	     && compare0->config.output != HW_A1(_hw_oca_output_clear_after_match)
	     && compare0->config.output != HW_A1(_hw_oca_output_set_after_match))
	  return 4 ;
	/* HWA_ERR("compare output A of class _ctc counter mode must be " */
	/*	"'disconnected', 'toggle_after_match', 'clear_after_match', or " */
	/*	"'set_after_match'."); */

      }
      else if ( wgm==3 ) {
	if ( compare0->config.output != HW_A1(_hw_oca_output_disconnected)
	     && compare0->config.output != HW_A1(_hw_oca_output_set_at_bottom_clear_after_match)
	     && compare0->config.output != HW_A1(_hw_oca_output_clear_at_bottom_set_after_match) )
	  return 5 ;
	/* HWA_ERR("compare output A of class _ctc counter mode must be " */
	/*	"'disconnected', 'set_at_bottom_clear_after_match', or " */
	/*	"'clear_at_bottom_set_after_match'."); */
      }
      else if ( wgm==7 ) {
	if ( compare0->config.output != HW_A1(_hw_oca_output_disconnected)
	     && compare0->config.output != HW_A1(_hw_oca_output_toggle_after_match)
	     && compare0->config.output != HW_A1(_hw_oca_output_set_at_bottom_clear_after_match)
	     && compare0->config.output != HW_A1(_hw_oca_output_clear_at_bottom_set_after_match) )
	  return 6 ;
	/* HWA_ERR("compare output A of class _ctc counter mode must be " */
	/*	"'disconnected', 'toggle_after_match', " */
	/*	"'set_at_bottom_clear_after_match', or " */
	/*	"'clear_at_bottom_set_after_match'."); */
      }
      else if ( wgm==1 ) {
	if ( compare0->config.output != HW_A1(_hw_oca_output_disconnected)
	     && compare0->config.output != HW_A1(_hw_oca_output_clear_after_match_up_set_after_match_down)
	     && compare0->config.output != HW_A1(_hw_oca_output_set_after_match_up_clear_after_match_down) )
	  /* HWA_ERR("compare output A of class _ctc counter mode must be " */
	  /*	  "'disconnected', 'clear_after_match_up_set_after_match_down', " */
	  /*	  "or 'set_after_match_up_clear_after_match_down'."); */
	  return 7 ;
      }
      else if ( wgm==5 ) {
	if ( compare0->config.output != HW_A1(_hw_oca_output_disconnected)
	     && compare0->config.output != HW_A1(_hw_oca_output_toggle_after_match)
	     && compare0->config.output != HW_A1(_hw_oca_output_clear_after_match_up_set_after_match_down)
	     && compare0->config.output != HW_A1(_hw_oca_output_set_after_match_up_clear_after_match_down) )
	  /* HWA_ERR("compare output A of class _ctc counter mode must be " */
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
	if ( compare1->config.output != HW_A1(_hw_oca_output_disconnected)
	     && compare1->config.output != HW_A1(_hw_oca_output_toggle_after_match)
	     && compare1->config.output != HW_A1(_hw_oca_output_clear_after_match)
	     && compare1->config.output != HW_A1(_hw_oca_output_set_after_match))
	  /* HWA_ERR("compare output B of class _ctc counter mode must be " */
	  /*	  "'disconnected', 'toggle_after_match', 'clear_after_match', or " */
	  /*	  "'set_after_match'."); */
	  return 9 ;
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( compare1->config.output != HW_A1(_hw_oca_output_disconnected)
	     && compare1->config.output != HW_A1(_hw_oca_output_set_at_bottom_clear_after_match)
	     && compare1->config.output != HW_A1(_hw_oca_output_clear_at_bottom_set_after_match) )
	  /* HWA_ERR("compare output B of class _ctc counter mode must be " */
	  /*	  "'disconnected', 'set_at_bottom_clear_after_match', or " */
	  /*	  "'clear_at_bottom_set_after_match'."); */
	  return 10 ;
      }
      else if ( wgm==1 || wgm==5 ) {
	if ( compare1->config.output != HW_A1(_hw_oca_output_disconnected)
	     && compare1->config.output != HW_A1(_hw_oca_output_clear_after_match_up_set_after_match_down)
	     && compare1->config.output != HW_A1(_hw_oca_output_set_after_match_up_clear_after_match_down) )
	  /* HWA_ERR("compare output B of class _ctc counter mode must be " */
	  /*	  "'disconnected', 'clear_after_match_up_set_after_match_down', " */
	  /*	  "or 'set_after_match_up_clear_after_match_down'."); */
	  return 11 ;
      }
    }

    /*	Update
     */
    if ( compare_update != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( compare_update != HW_A1(_hw_oca_update_immediately) )
	  /* HWA_ERR("optionnal parameter 'update' of class _ctc counter must be "\ */
	  /*	  "'immediately'."); */
	  return 12 ;
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( compare_update != HW_A1(_hw_oca_update_after_bottom) )
	  /* HWA_ERR("optionnal parameter 'update' of class _ctc counter must be " */
	  /*	  "'after_bottom'."); */
	  return 13 ;
      }
      else
	if( compare_update != HW_A1(_hw_oca_update_after_top) )
	  /* HWA_ERR("optionnal parameter 'update' of class _ctc counter must be " */
	  /*	  "'after_top'."); */
	  return 14 ;
    }

    /*	Overflow
     */
    if ( overflow != 0xFF ) {
      if ( wgm==7 ) {
	if ( overflow != HW_A1(_hw_ctc_overflow_after_top) )
	  /* HWA_ERR("optionnal parameter 'overflow' of class _ctc counter must be " */
	  /*	  "'after_top'."); */
	  return 15 ;
      }
      else if ( (wgm==1 || wgm==5) ) {
	if ( overflow != HW_A1(_hw_ctc_overflow_after_bottom) )
	  /* HWA_ERR("optionnal parameter 'overflow' of class _ctc counter must be " */
	  /*	  "'after_bottom'."); */
	  return 16 ;
      }
      else if ( overflow != HW_A1(_hw_ctc_overflow_after_max) )
	/* HWA_ERR("optionnal parameter 'overflow' of class _ctc counter must be " */
	/*	"'after_max'."); */
	return 17 ;
    }
  }

  return 0 ;
}


/**
 * @page atmelavr_ctc
 *
 * <br>
 * `read`:
 *
 * __Note__ See [that
 * thread](http://www.avrfreaks.net/comment/141688#comment-141688) on [AVR
 * Freaks](http://www.avrfreaks.net) for count register write issues.
 *
 * The count value is accessible for reading and writing through the following
 * instructions:
 */
/**
 * @page atmelavr_ctc
 * @code
 * hw( read, counter0 );
 * @endcode
 */
#define hw_read__ctc			, _hw_read_ctc
#define _hw_read_ctc(o,a,...)		_hw_read(o,count) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_ctc
 *
 * <br>
 * `write`:
 *
 * @code
 * hw( write, counter0, value );
 * @endcode
 */
#define hw_write__ctc			, _hw_write_ctc
#define _hw_write_ctc(o,a,v,...)	_hw_write(o,count,v) HW_EOL(__VA_ARGS__)

/**
 * @page atmelavr_ctc
 * @code
 * hwa( write, counter0, value );
 * @endcode
 */
#define hwa_write__ctc			, _hwa_write_ctc
#define _hwa_write_ctc(o,a,v)		_hwa_write(o,count,v)

#if 0
/**
 * @page atmelavr_ctc
 *
 *  * setting the count value to 0 (this does not reset the prescaler):
 *
 * @code
 *`hw( clear, counter0 )`;
 * @endcode
 */
#define hw_clear__ctc			, _hw_clear_ctc
#define _hw_clear_ctc(o,a,...)	_hw_write(o,count,0) HW_EOL(__VA_ARGS__)

/**
 * @page atmelavr_ctc
 *
 * @code
 * hwa( clear, counter0 );
 * @endcode
 */
#define hwa_clear__ctc			, _hwa_clear_ctc
#define _hwa_clear_ctc(o,a,...)	_hwa_write(o,count,0) HW_EOL(__VA_ARGS__)
#endif


/**
 * @page atmelavr_ctc
 * @section atmelavr_ctc_st Status
 *
 * The overflow flag can be accessed through interrupt-related instructions:
 *
 * @code
 * if ( hw( read, (counter0,irq) ) ) {	// Read overflow IRQ flag
 *   hw( clear, (counter0,irq) );		// Clear overflow IRQ flag
 *   hw( disable, (counter0,irq) );		// Disable overflow IRQs
 * }
 * @endcode
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__ctc(o,a)			\
  _hwa_setup_r( o, ccra);			\
  _hwa_setup_r( o, ccrb);			\
  _hwa_setup_r( o, count);			\
  _hwa_setup_r( o, imsk);			\
  _hwa_setup_r( o, ifr);			\
  hwa->o.config.clock	  = 0xFF;		\
  hwa->o.config.direction = 0xFF;		\
  hwa->o.config.top	  = 0xFF;		\
  hwa->o.config.overflow  = 0xFF;		\
  hwa->o.compare0.config.update	= 0xFF ;	\
  hwa->o.compare0.config.output	= 0xFF ;	\
  hwa->o.compare1.config.update	= 0xFF ;	\
  hwa->o.compare1.config.output	= 0xFF


#define _hwa_init__ctc(o,a)					\
  _hwa_init_r( o, ccra,	 0x00 );				\
  _hwa_init_r( o, ccrb,	 0x00 );				\
  _hwa_init_r( o, count, 0x00 );				\
  _hwa_init_r( o, imsk,	 0x00 );				\
  _hwa_init_r( o, ifr,	 0x00 )


#define _hwa_commit__ctc(o,a)			\
  _hwa_commit_r( o, ccra);			\
  _hwa_commit_r( o, ccrb);			\
  _hwa_commit_r( o, count);			\
  _hwa_commit_r( o, imsk);			\
  _hwa_commit_r( o, ifr)
  

/**
 * @page atmelavr_ctc
 * @section atmelavr_ctc_internals Internals
 *
 * Class `_ctc` objects hold the following hardware registers:
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
 */
