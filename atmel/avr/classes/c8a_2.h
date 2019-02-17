
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
 * @section atmelavr_c8a_cf Configure
 *
 * @note If the optionnal argument `overflow` is not stated, an acceptable value
 * will be selected according to the configuration of the compare units found in
 * the HWA context. If `overflow` is stated, the validity of its value will be
 * verified.
 *
 * @code
 * hwa( configure, counter0,
 *
 *      //  How the counter is clocked
 *      //
 *      clock,       none                        // No clock, the counter is stopped
 *                 | ioclk [/ 8|64|256|1024]     // I/O clock
 *                 | external_rising             // External input, rising edge
 *                 | external_falling,           // External input, falling edge
 *
 *      //  How does this counter count
 *      //
 *      direction,   up_loop                     // Count up and loop
 *                 | updown_loop,                // Count up and down alternately
 *
 *      //  Class _c8a counters all count from 0
 *      //
 *    [ bottom,      0, ]
 *
 *      //  The maximum value the counter reaches (the default is `max`)
 *      //
 *    [ top,         0xFF | 0x00FF | 255 | max   // Hardware fixed value 0xFF
 *                 | compare0,]                  // Value stored in the compare0 unit
 *
 *      //  When the overflow flag is set
 *      //
 *    [ overflow,    after_bottom                // When the counter counts from 0 to 1
 *                 | after_top                   // When the counter counts from top to 0
 *                 | after_max ]                 // When the counter counts from max to 0
 *    );
 * @endcode
 *
 * <br>
 * **Table of Atmel modes**
 *
 * Mode                  | `direction`   | `top`      | `overflow`     | Overflow flag | Update
 * :---------------------|:--------------|:-----------|:---------------|:--------------|:-------------	
 *  0 Normal             | `up_loop`     | `max`      | `after_max`    | max -> 0      | Immediate
 *  1 PWM, Phase correct | `updown_loop` | `max`      | `after_bottom` | 0 -> 1	       | At top
 *  2 CTC                | `up_loop`     | `compare0` | `after_max`    | max -> 0      | Immediate
 *  3 Fast PWM           | `up_loop`     | `max`      | `after_max`    | max -> 0      | At bottom
 *  5 PWM, Phase correct | `updown_loop` | `compare0` | `after_bottom` | 0 -> 1	       | At top
 *  7 Fast PWM           | `up_loop`     | `max`      | `after_top`    | top -> 0      | At bottom
 */
#define hwa_configure__c8a	, _hwa_cfc8a

/*  Mandatory argument `clock`
 *
 *    Add 2 void arguments to the end of the list so that there are always
 *    3 arguments following the last non-void argument.
 */
#define _hwa_cfc8a(o,i,a,k,...)						\
  do { HW_Y(_hwa_cfc8a_kclock_,_hw_is_clock_##k)(o,k,__VA_ARGS__,,) } while(0)

#define _hwa_cfc8a_kclock_0(o,k,...)		\
  HW_E_VL(k,clock)

#define _hwa_cfc8a_kclock_1(o,k,v,...)				\
  HW_Y(_hwa_cfc8a_vclock_,_hw_c1clk_##v)(o,v,__VA_ARGS__)

#define _hwa_cfc8a_vclock_0(o,v,...)					\
  HW_E_AVL(clock, v, none | ioclk [/ 8|64|256|1024] | external_falling | external_rising)

#define _hwa_cfc8a_vclock_1(o,v,k,...)				\
  hwa->o.config.clock = HW_VF(_hw_c1clk_##v);			\
  HW_Y(_hwa_cfc8a_kmode_,_hw_is_direction_##k)(o,k,__VA_ARGS__)

/*  Mandatory argument `direction`
 */
#define _hw_c8a_direction_up_loop	, 1
#define _hw_c8a_direction_updown_loop	, 2

#define _hwa_cfc8a_kmode_0(o,k,...)		\
  HW_E_VL(k,direction)

#define _hwa_cfc8a_kmode_1(o,k,v,...)					\
  HW_Y(_hwa_cfc8a_vmode_,_hw_c8a_direction_##v)(o,v,__VA_ARGS__)

#define _hwa_cfc8a_vmode_0(o,v,...)		\
  HW_E_AVL(direction, v, up_loop | updown_loop)

#define _hwa_cfc8a_vmode_1(o,v,k,...)				\
  hwa->o.config.direction = HW_A1(_hw_c8a_direction_##v);	\
  HW_Y(_hwa_cfc8a_kbottom_,_hw_is_bottom_##k)(o,k,__VA_ARGS__)

/*  Optionnal argument `bottom`
 */
#define _hwa_cfc8a_kbottom_1(o,k,v,...)			\
  HW_G2(_hwa_cfc8a_vbottom,HW_IS(0,v))(o,v,__VA_ARGS__)

#define _hwa_cfc8a_vbottom_0(o,v,...)		\
  HW_E_AVL(bottom, v, `0`)

#define _hwa_cfc8a_vbottom_1(o,v,k,...)				\
  HW_Y(_hwa_cfc8a_ktop_,_hw_is_top_##k)(o,k,__VA_ARGS__)

#define _hwa_cfc8a_kbottom_0(o,k,...)				\
  HW_Y(_hwa_cfc8a_ktop_,_hw_is_top_##k)(o,k,__VA_ARGS__)

/*  Optionnal argument `top`
 */
#define _hw_c8a_top_0xFF		, 1
#define _hw_c8a_top_0x00FF		, 1
#define _hw_c8a_top_255			, 1
#define _hw_c8a_top_max			, 1
#define _hw_c8a_top_compare0		, 2

#define _hwa_cfc8a_ktop_1(o,k,v,...)				\
  HW_Y(_hwa_cfc8a_vtop_,_hw_c8a_top_##v)(o,v,__VA_ARGS__)

#define _hwa_cfc8a_vtop_0(o,v,...)		\
  HW_E_AVL(top, v, 0xFF | max | compare0)

#define _hwa_cfc8a_vtop_1(o,v,k,...)					\
  hwa->o.config.top = HW_A1(_hw_c8a_top_##v);				\
  HW_Y(_hwa_cfc8a_koverflow_,_hw_is_overflow_##k)(o,k,__VA_ARGS__)

#define _hwa_cfc8a_ktop_0(o,k,...)					\
  HW_Y(_hwa_cfc8a_koverflow_,_hw_is_overflow_##k)(o,k,__VA_ARGS__)

/*  Optionnal argument `overflow`
 */
#define _hw_c8a_overflow_after_bottom	, 0
#define _hw_c8a_overflow_after_top		, 1
#define _hw_c8a_overflow_after_max		, 2

#define _hwa_cfc8a_koverflow_1(o,k,v,...)				\
  HW_Y(_hwa_cfc8a_voverflow_,_hw_c8a_overflow_##v)(o,v,__VA_ARGS__)

#define _hwa_cfc8a_voverflow_0(o,v,...)			\
  HW_E_OAVL(overflow, v, after_bottom | after_top | after_max)

#define _hwa_cfc8a_voverflow_1(o,v,...)					\
  if ( hwa->o.config.direction == HW_A1(_hw_c8a_direction_up_loop)	\
       && HW_A1(_hw_c8a_overflow_##v) == HW_A1(_hw_c8a_overflow_after_bottom) ) \
    HWA_ERR("optionnal parameter `overflow` can not be `after_bottom` "	\
	    "when direction is `up_loop`.");				\
  hwa->o.config.overflow = HW_A1(_hw_c8a_overflow_##v);  HW_EOL(__VA_ARGS__)

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
#define _hwa_solve__c8a( o,i,a )				\
  _hwa_solve__c8a_2( o, hw_##o##_compare0, hw_##o##_compare1 )

#define _hwa_solve__c8a_2(...)		_hwa_solve__c8a_3(__VA_ARGS__)

#define _hwa_solve__c8a_3( o, compare0, compare1 )			\
  do {									\
    uint8_t r = _hwa_solve_c8a( &hwa->o, &hwa->compare0, &hwa->compare1 ); \
    if ( r == 1 )							\
      HWA_ERR("`update` must be the same for both compare units of `" #o "`."); \
    else if ( r == 2 )							\
      HWA_ERR("WGM value could not be solved for `" #o "`.");		\
    else if ( r == 3 )							\
      HWA_ERR("configuration of `" #o "` is required.");		\
    else if ( r == 4 )							\
      HWA_ERR("`mode` of `" #compare0 "` can be "			\
	      "'disconnected', 'toggle_after_match', 'clear_after_match', or " \
	      "'set_after_match'.");					\
    else if ( r == 5 )							\
      HWA_ERR("`mode` of `" #compare0 "` can be "			\
	      "'disconnected', 'set_at_bottom_clear_after_match', or "	\
	      "'clear_at_bottom_set_after_match'.");			\
    else if ( r == 6 )							\
      HWA_ERR("`mode` of `" #compare0 "` can be "			\
	      "'disconnected', 'toggle_after_match', "			\
	      "'set_at_bottom_clear_after_match', or "			\
	      "'clear_at_bottom_set_after_match'.");			\
    else if ( r == 7 )							\
      HWA_ERR("`mode` of `" #compare0 "` can be "			\
	      "'disconnected', 'clear_after_match_up_set_after_match_down', "	\
	      "or 'set_after_match_up_clear_after_match_down'.");		\
    else if ( r == 8 )							\
      HWA_ERR("`mode` of `" #compare0 "` can be "			\
	      "'disconnected', 'toggle_after_match', "			\
	      "'clear_after_match_up_set_after_match_down', "			\
	      "or 'set_after_match_up_clear_after_match_down'.");		\
    else if ( r == 9 )							\
      HWA_ERR("`mode` of `" #compare1 "` can be "			\
	      "'disconnected', 'toggle_after_match', 'clear_after_match', or " \
	      "'set_after_match'.");					\
    else if ( r == 10 )							\
      HWA_ERR("`mode` of `" #compare1 "` can be "			\
	      "'disconnected', 'set_at_bottom_clear_after_match', or "	\
	      "'clear_at_bottom_set_after_match'.");			\
    else if ( r == 11 )							\
      HWA_ERR("`mode` of `" #compare1 "` can be "			\
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
	_hwa( configure, (compare0,pin), mode, digital_output );	\
      if ( hwa->compare1.config.output != 0xFF				\
	   && hwa->compare1.config.output != HW_A1(_hw_cmp8a_output_disconnected) ) \
	_hwa( configure, (compare1,pin), mode, digital_output );	\
    }									\
  } while(0)


HW_INLINE uint8_t _hwa_solve_c8a ( hwa_c8a_t *p, hwa_cmp8a_t *compare0, hwa_cmp8a_t *compare1  )
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
    p->config.top = HW_A1(_hw_c8a_top_max);

  /*  Default config for overflow
   */
  uint8_t overflow = p->config.overflow ;
  if ( overflow == 0xFF && p->config.top == HW_A1(_hw_c8a_top_compare0) ) {
    if ( p->config.direction == HW_A1(_hw_c8a_direction_up_loop) )
      overflow = HW_A1(_hw_c8a_overflow_after_top);
    else /* if ( p->config.direction == HW_A1(_hw_c8a_direction_up_loop) ) */
      overflow = HW_A1(_hw_c8a_overflow_after_bottom);
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
   *  0	  000  Normal	  LOOP_UP      0xFF  IMM  MAX+1  DIS,ToM,CoM,SoM	      DIS,ToM,CoM,SoM
   *  2	  010  CTC	  LOOP_UP      OCRA  IMM  MAX+1  DIS,ToM,CoM,SoM	      DIS,ToM,CoM,SoM
   *
   *  3	  011  Fast PWM	  LOOP_UP      0xFF  BOT  MAX  DIS,SaBCoM,CaBSoM      DIS,SaBCoM,CaBSoM
   *  7	  111  Fast PWM	  LOOP_UP      OCRA  BOT  TOP  DIS,ToM,CoMSaB,SoMCaB  DIS,SaBCoM,CaBSoM
   *
   *  1	  001  PWM, PhC	  LOOP_UPDOWN  0xFF  TOP  BOT+1  DIS,CmuSmd,SmuCmd      DIS,CmuSmd,SmuCmd	  
   *  5	  101  PWM, PhC	  LOOP_UPDOWN  OCRA  TOP  BOT+1  DIS,ToM,CmuSmd,SmuCmd  DIS,CmuSmd,SmuCmd
   *
   *  4	  100  *Reserved*
   *  6	  110  *Reserved*
   */

  /*	Determine WGM
   */
  uint8_t wgm = 0xFF ;
  if ( p->config.direction == HW_A1(_hw_c8a_direction_up_loop) ) {
    if ( p->config.top == HW_A1(_hw_c8a_top_0xFF) ) {
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
       *  FIXME: a change of pin from one of the 4 modes below to
       *  'disconnected' causes a useless modification of wgm from 7 to 2. As
       *  WGM2 is not in the same register as WGM1:0, this generates useless
       *  code.
       */
      if ( compare_update == HW_A1(_hw_cmp8a_update_after_bottom )
	   || overflow == HW_A1(_hw_c8a_overflow_after_top)
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

  /*  Check the validity of the configuration of compare output A
   */
  if ( compare0->config.output != 0xFF ) {
    if ( wgm==0 || wgm==2 ) {
      if ( compare0->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_toggle_after_match)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_clear_after_match)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_set_after_match))
	return 4 ;
      /* HWA_ERR("compare output A of class _c8a counter mode must be " */
      /*	"'disconnected', 'toggle_after_match', 'clear_after_match', or " */
      /*	"'set_after_match'."); */

    }
    else if ( wgm==3 ) {
      if ( compare0->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_set_at_bottom_clear_after_match)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_clear_at_bottom_set_after_match) )
	return 5 ;
      /* HWA_ERR("compare output A of class _c8a counter mode must be " */
      /*	"'disconnected', 'set_at_bottom_clear_after_match', or " */
      /*	"'clear_at_bottom_set_after_match'."); */
    }
    else if ( wgm==7 ) {
      if ( compare0->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_toggle_after_match)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_set_at_bottom_clear_after_match)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_clear_at_bottom_set_after_match) )
	return 6 ;
      /* HWA_ERR("compare output A of class _c8a counter mode must be " */
      /*	"'disconnected', 'toggle_after_match', " */
      /*	"'set_at_bottom_clear_after_match', or " */
      /*	"'clear_at_bottom_set_after_match'."); */
    }
    else if ( wgm==1 ) {
      if ( compare0->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_clear_after_match_up_set_after_match_down)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_set_after_match_up_clear_after_match_down) )
	/* HWA_ERR("compare output A of class _c8a counter mode must be " */
	/*	  "'disconnected', 'clear_after_match_up_set_after_match_down', " */
	/*	  "or 'set_after_match_up_clear_after_match_down'."); */
	return 7 ;
    }
    else if ( wgm==5 ) {
      if ( compare0->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_toggle_after_match)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_clear_after_match_up_set_after_match_down)
	   && compare0->config.output != HW_A1(_hw_cmp8a_output_set_after_match_up_clear_after_match_down) )
	/* HWA_ERR("compare output A of class _c8a counter mode must be " */
	/*	  "'disconnected', 'toggle_after_match', " */
	/*	  "'clear_after_match_up_set_after_match_down', " */
	/*	  "or 'set_after_match_up_clear_after_match_down'."); */
	return 8 ;
    }
  }

  /*  Check the validity of the configuration of compare output B
   */
  if ( compare1->config.output != 0xFF ) {
    if ( wgm==0 || wgm==2 ) {
      if ( compare1->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	   && compare1->config.output != HW_A1(_hw_cmp8a_output_toggle_after_match)
	   && compare1->config.output != HW_A1(_hw_cmp8a_output_clear_after_match)
	   && compare1->config.output != HW_A1(_hw_cmp8a_output_set_after_match))
	/* HWA_ERR("compare output B of class _c8a counter mode must be " */
	/*	  "'disconnected', 'toggle_after_match', 'clear_after_match', or " */
	/*	  "'set_after_match'."); */
	return 9 ;
    }
    else if ( wgm==3 || wgm==7 ) {
      if ( compare1->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	   && compare1->config.output != HW_A1(_hw_cmp8a_output_set_at_bottom_clear_after_match)
	   && compare1->config.output != HW_A1(_hw_cmp8a_output_clear_at_bottom_set_after_match) )
	/* HWA_ERR("compare output B of class _c8a counter mode must be " */
	/*	  "'disconnected', 'set_at_bottom_clear_after_match', or " */
	/*	  "'clear_at_bottom_set_after_match'."); */
	return 10 ;
    }
    else if ( wgm==1 || wgm==5 ) {
      if ( compare1->config.output != HW_A1(_hw_cmp8a_output_disconnected)
	   && compare1->config.output != HW_A1(_hw_cmp8a_output_clear_after_match_up_set_after_match_down)
	   && compare1->config.output != HW_A1(_hw_cmp8a_output_set_after_match_up_clear_after_match_down) )
	/* HWA_ERR("compare output B of class _c8a counter mode must be " */
	/*	  "'disconnected', 'clear_after_match_up_set_after_match_down', " */
	/*	  "or 'set_after_match_up_clear_after_match_down'."); */
	return 11 ;
    }
  }

  /*  Check the validity of the configuration of update
   */
  if ( compare_update != 0xFF ) {
    if ( wgm==0 || wgm==2 ) {
      if ( compare_update != HW_A1(_hw_cmp8a_update_immediately) )
	/* HWA_ERR("optionnal parameter 'update' of class _c8a counter must be "\ */
	/*	  "'immediately'."); */
	return 12 ;
    }
    else if ( wgm==3 || wgm==7 ) {
      if ( compare_update != HW_A1(_hw_cmp8a_update_after_bottom) )
	/* HWA_ERR("optionnal parameter 'update' of class _c8a counter must be " */
	/*	  "'after_bottom'."); */
	return 13 ;
    }
    else
      if( compare_update != HW_A1(_hw_cmp8a_update_after_top) )
	/* HWA_ERR("optionnal parameter 'update' of class _c8a counter must be " */
	/*	  "'after_top'."); */
	return 14 ;
  }

  /*  Check the validity of the configuration of overflow
   */
  if ( overflow != 0xFF ) {
    if ( wgm==7 ) {
      if ( overflow != HW_A1(_hw_c8a_overflow_after_top) )
	/* HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be " */
	/*	  "'after_top'."); */
	return 15 ;
    }
    else if ( (wgm==1 || wgm==5) ) {
      if ( overflow != HW_A1(_hw_c8a_overflow_after_bottom) )
	/* HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be " */
	/*	  "'after_bottom'."); */
	return 16 ;
    }
    else if ( overflow != HW_A1(_hw_c8a_overflow_after_max) )
      /* HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be " */
      /*	"'after_max'."); */
      return 17 ;
  }

  return 0 ;
}


/**
 * @page atmelavr_c8a
 * @section atmelavr_rdc8a Read
 *
 * @code
 * uint8_t n = hw( read, counter0 );      // Get the count
 * @endcode
 */
#define hw_read__c8a		, _hw_read_c8a
#define _hw_read_c8a(o,i,a,...)		_hw_read(o,count) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_c8a
 * @section atmelavr_wrc8a Write
 * @code
 * hw( write, counter0, value );
 * @endcode
 */
#define hw_write__c8a		, _hw_write_c8a
#define _hw_write_c8a(o,i,a,v,...)	_hw_write(o,count,v) HW_EOL(__VA_ARGS__)

/**
 * @page atmelavr_c8a
 * <br>
 * @code
 * hwa( write, counter0, value );
 * @endcode
 */
#define hwa_write__c8a		, _hwa_write_c8a
#define _hwa_write_c8a(o,i,a,v,...)	_hwa_write(o,count,v) HW_EOL(__VA_ARGS__)



/**
 * @page atmelavr_c8a
 * @section atmelavr_stc8a Status
 *
 * The overflow flag can be accessed through interrupt-related instructions:
 *
 * @code
 * if ( hw( read, irqflag(counter0) ) ) {	// Read overflow IRQ flag
 *   hw( clear, irqflag(counter0) );		// Clear overflow IRQ flag
 *   hw( turn, irq(counter0), off );		// Disable overflow IRQs
 * }
 * @endcode
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__c8a(o,i,a)			\
  /* _hwa_setup_r( o, gtccr); */		\
  _hwa_setup_r( o, ccra);			\
  _hwa_setup_r( o, ccrb);			\
  _hwa_setup_r( o, count);			\
  _hwa_setup_r( o, imsk);			\
  _hwa_setup_r( o, ifr);			\
  hwa->o.config.clock	  = 0xFF;		\
  hwa->o.config.direction = 0xFF;		\
  hwa->o.config.top	  = 0xFF;		\
  hwa->o.config.overflow  = 0xFF


#define _hwa_init__c8a(o,i,a)			\
  /* _hwa_init_r( o, gtccr, 0x00 ); */		\
  _hwa_init_r( o, ccra,  0x00 );		\
  _hwa_init_r( o, ccrb,  0x00 );		\
  _hwa_init_r( o, count, 0x00 );		\
  _hwa_init_r( o, imsk,  0x00 );		\
  _hwa_init_r( o, ifr,   0x00 )


/* hwa->o.config.clock	   = HW_A1(_hw_c8a_clock_none);		\ */
/* hwa->o.config.direction = HW_A1(_hw_c8a_direction_up_loop);	\ */
/* hwa->o.config.top	   = HW_A1(_hw_c8a_top_max);		\ */
/* hwa->o.config.overflow  = HW_A1(_hw_c8a_overflow_after_max) */


#define _hwa_commit__c8a(o,i,a)			\
  /* _hwa_commit_r( o, gtccr); */		\
  _hwa_commit_r( o, ccra);			\
  _hwa_commit_r( o, ccrb);			\
  _hwa_commit_r( o, count);			\
  _hwa_commit_r( o, imsk);			\
  _hwa_commit_r( o, ifr)

/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_examples Examples
 *
 * The following code triggers a compare IRQ every 32 ioclk cycles:
 * @code
 * //  An IRQ is triggered when the count register is reset to 0
 * hwa( configure, counter0,
 *      clock,     ioclk/8,
 *      direction, up_loop,
 *      top,       max,
 *      overflow,  after_max );
 * @endcode
 */
  
/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_internals Internals
 *
 * Class `_c8a` objects hold the following hardware registers:
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
 *
 * These registers are accessible through the @ref public_ins
 * "register access intructions".
 */
