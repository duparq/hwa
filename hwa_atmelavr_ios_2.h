
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


#define hw_def_hwa_config_io		, hwa_config_io
#define hwa_config_io(t,ion,ioid, cc,cn,cid,ca, bn, bp, mode)	\
  _hwa_config_io(&hwa->cn, bn, bp, hw_iomode_##mode)


/** \brief Configures one or more consecutive i/o pins
 *  \param p	pointer to i/o port instance in hwa struct
 *  \param bn	number of consecutive bits to configure
 *  \param bp   position of least significant bit to configure
 *  \param mode	pin(s) mode
 */
HW_INLINE void _hwa_config_io( hwa_io_t *p, uint8_t bn, uint8_t bp, uint8_t mode )
{
  /* if ( mode & 0x20 ) {	/\* didr *\/ */
  /*   if ( (uintptr_t)p->didr.ra == (uintptr_t)-1 ) */
  /*     HWA_ERR("no digital input filter for this io port"); */
  /*   else */
  /*     _hwa_write_r8( &p->didr, bn, bp, ((mode & 0x10)!=0)*((1U<<bn)-1) ); */
  /* } */

  if ( mode & 0x08 )	/* pull-up */
    _hwa_write_r8( &p->port, bn, bp, ((mode & 0x04)!=0)*((1U<<bn)-1) );

  if ( mode & 0x02 )	/* ddr */
    _hwa_write_r8( &p->ddr, bn, bp, ((mode & 0x01)!=0)*((1U<<bn)-1) );
}


#define hw_def_hwa_write_io	, _hwa_write_io

#define _hwa_write_io(t, ion,ioid, cc,cn,ci,ca, bn,bp, v)	\
  _hwa_write_r8(&hwa->cn.port, bn, bp, v)
