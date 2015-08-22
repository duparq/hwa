
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O port
 */


/*******************************************************************************
 *                                                                             *
 *      Context management						       *
 *                                                                             *
 *******************************************************************************/

#if 0
HW_INLINE void _hwa_begin_p__p8a ( hwa_p8a_t *p, intptr_t a )
{
  _hwa_create_reg_p( p, a, _p8a, port );
  _hwa_create_reg_p( p, a, _p8a, ddr  );
}


HW_INLINE void _hwa_init_p__p8a ( hwa_p8a_t *p )
{
  _hwa_set__r8( &p->port, 0x00 );
  _hwa_set__r8( &p->ddr,  0x00 );
}


HW_INLINE void _hwa_commit_p__p8a ( hwa_t *hwa, hwa_p8a_t *p )
{
  _hwa_commit_reg_p( p, _p8a, port );
  _hwa_commit_reg_p( p, _p8a, ddr  );
}
#endif


#define _hwa_create__p8a(o,i,a)			\
  _hwa_create_reg( o, port );			\
  _hwa_create_reg( o, ddr  )

#define _hwa_init__p8a(o,i,a)			\
  _hwa_init_reg( o, port, 0x00 );		\
  _hwa_init_reg( o, ddr,  0x00 )

#define _hwa_commit__p8a(o,i,a)		\
  _hwa_commit_reg( o, port );			\
  _hwa_commit_reg( o, ddr  )


/**
 * @page atmelavr_p8a Class _p8a: 8-bit I/O port
 * <br>
 */
