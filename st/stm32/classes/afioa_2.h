
/* This file is part of the HWA project.
 * Copyright (c) 2019 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief AFIO
 */

/**
 * @ingroup stm32_classes
 * @addtogroup stm32_afioa
 */
#define hw_class__afioa


/*******************************************************************************
 *									       *
 *	Context								       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__afioa(o,a)			\
  _hwa_setup_map( hwa );			\
  _hwa_setup_r( o, mapr )

#define _hwa_init__afioa(o,a)			\
  _hwa_init_r( o, mapr,	 0x00000000 )

#define _hwa_commit__afioa(o,a)			\
  _hwa_commit_map( hwa );			\
  _hwa_commit_r( o, mapr )



HW_INLINE void _hwa_setup_map( hwa_t *hwa )
{
  hwa->map.error = 0 ;
  hwa->map.counter2_remap    = -1 ;
  hwa->map.counter2_etr      = 0 ;
  hwa->map.counter2_channel1 = 0 ;
  hwa->map.counter2_channel2 = 0 ;
  hwa->map.counter2_channel3 = 0 ;
  hwa->map.counter2_channel4 = 0 ;
}


HW_INLINE void _hwa_commit_map( hwa_t *hwa )
{
  if ( hwa->map.error )
    return ;

  /*  Counter 2
   */
  int8_t remap0 = -1 ;
  int8_t remap1 = -1 ;

  if ( hwa->map.counter2_etr != 0 ) {
    if ( hwa->map.counter2_etr == HW_ADDRESS((porta,0)) )
      remap0 = 0 ;
    else if ( hwa->map.counter2_etr == HW_ADDRESS((porta,15)) )
      remap0 = 1 ;
    else {
      hwa->map.error = 1 ;
      HWA_E(HW_EM_OMAP((counter2,etr))) ;
    }
  }

  if ( hwa->map.counter2_channel1 != 0 ) {
    if ( hwa->map.counter2_channel1 == HW_ADDRESS((porta,0)) )
      remap0 = 0 ;
    else if ( hwa->map.counter2_channel1 == HW_ADDRESS((porta,15)) )
      remap0 = 1 ;
    else {
      hwa->map.error = 1 ;
      HWA_E(HW_EM_OMAP((counter2,channel1)));
    }
  }

  if ( hwa->map.counter2_channel2 != 0 ) {
    if ( hwa->map.counter2_channel2 == HW_ADDRESS((porta,1)) && remap0 == -1 )
      remap0 = 0 ;
    else if ( hwa->map.counter2_channel2 == HW_ADDRESS((portb,3)) && remap0 == -1 )
      remap0 = 1 ;
    else {
      hwa->map.error = 1 ;
      HWA_E(HW_EM_OMAP((counter2,channel2)));
    }
  }

  if ( hwa->map.counter2_channel3 != 0 ) {
    if ( hwa->map.counter2_channel3 == HW_ADDRESS((porta,2)) )
      remap1 = 0 ;
    else if ( hwa->map.counter2_channel3 == HW_ADDRESS((portb,10)) )
      remap1 = 1 ;
    else {
      hwa->map.error = 1 ;
      HWA_E(HW_EM_OMAP((counter2,channel3)));
    }
  }

  if ( hwa->map.counter2_channel4 != 0 ) {
    if ( hwa->map.counter2_channel4 == HW_ADDRESS((porta,3)) && remap1 == -1 )
      remap1 = 0 ;
    else if ( hwa->map.counter2_channel4 == HW_ADDRESS((portb,11)) && remap1 == -1 )
      remap1 = 1 ;
    else {
      hwa->map.error = 1 ;
      HWA_E(HW_EM_OMAP((counter2,channel4)));
    }
  }

  if ( hwa->map.error )
    return ;

  if ( remap0 != -1 || remap1 != -1 ) {
    if ( remap0 == -1 ) remap0 = 0 ;
    if ( remap1 == -1 ) remap1 = 0 ;
    uint8_t remap = (remap1*2 + remap0) & 3 ;

    if ( hwa->map.counter2_remap != -1 && hwa->map.counter2_remap != remap )
      HWA_E(HW_EM_OMAP(counter2));

    hwa->map.counter2_remap = remap ;
    _hwa_write( afio, counter2_remap, remap );
  }
}
