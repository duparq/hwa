
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#define hwa_config_io_isfn
#define hwa_config_io(io, _per_,pn,pc,pa, bn, bp, mode, _)	\
  _hwa_config_io( &hwa->pn, bn, bp, HW_G2(hw_iomode,mode) )

/** \brief Configures one or more consecutive i/o pins
 *  \param p	pointer to i/o port instance in hwa struct
 *  \param bn	number of consecutive bits to configure
 *  \param bp   position of least significant bit to configure
 *  \param mode	pin(s) mode
 */
HW_INLINE void _hwa_config_io( hwa_io_t *p, uint8_t bn, uint8_t bp, uint8_t mode )
{
  if ( mode & 0x20 ) {	/* didr */
    if ( (uintptr_t)p->didr.ra == (uintptr_t)-1 )
      HW_RTERROR("no digital input filter for this io port");
    else
      hwa_write_8( &p->didr, bn, bp, ((mode & 0x10)!=0)*((1U<<bn)-1) );
  }

  if ( mode & 0x08 )	/* pull-up */
    hwa_write_8( &p->port, bn, bp, ((mode & 0x04)!=0)*((1U<<bn)-1) );

  if ( mode & 0x02 )	/* ddr */
    hwa_write_8( &p->ddr, bn, bp, ((mode & 0x01)!=0)*((1U<<bn)-1) );
}


#define hwa_write_io_isfn
#define hwa_write_io(io, _per_,pn,pc,pa, bn, bp, value)	\
  _hwa_write_io( &hwa->pn, bn, bp, value )

HW_INLINE void _hwa_write_io( hwa_io_t *p, uint8_t bn, uint8_t bp, uint8_t v )
{
  /*  Set BR bits to 1 and BS bits to 0
   *    BS bits have priority
   */
  hwa_write_8( &p->port, bn, bp, v );
}