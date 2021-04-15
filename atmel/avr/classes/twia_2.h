
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 2-wire interface
 */

/**
 * @addtogroup atmelavr_twia
 * @section atmelavr_twia_act Actions
 *
 * hw( configure, TWI, ... ) and hwa( configure, TWI, ... ) configure the TWI:
 *
 * @code
 * hw | hwa( configure, twi0,
 *
 *	   [ bps,		   <value>, ]	//  SCL speed
 *
 *	   [ slave_address,	   <value>, ]
 *
 *	   [ general_call,	   enabled
 *				 | disabled, ]
 *
 *	   [ slave_address_mask,   <value> ] );
 * @endcode
 *
 * @note The TWI does not take control of the SCL and SDA pins until a `xfr_`
 * action is triggered. Then, it keeps control over these pins until the TWI is
 * disabled.
 */
#define hw_configure__twia		, _hw_cftwia
#define _hw_cftwia( o,a, ... )		_hw_cftwia_( _hw, o, __VA_ARGS__,, )

#define hwa_configure__twia		, _hwa_cftwia
#define _hwa_cftwia( o,a, ... )		_hw_cftwia_( _hwa, o, __VA_ARGS__,, )

/*  Optionnal argument `bps`
 *    The 'TWEN' bit that makes the TWI take control of the I/O pins
 *    is set by the 'xfr_' actions.
 */
#define _hw_cftwia_(h,o,k,...)		do { HW_BW(_hw_cftwiabps,bps,k)(h,o,k,__VA_ARGS__); }while(0)
#define _hw_cftwiabps0(h,o,k,...)	HW_BW(_hw_cftwiasa,slave_address,k)(h,o,k,__VA_ARGS__)
#define _hw_cftwiabps1(h,o,k,v,...)	HW_B(_hw_cftwiabps1,v)(h,o,v,__VA_ARGS__)
#define _hw_cftwiabps11(h,o,v,...)	HW_E(HW_EM_VAM(bps))
#define _hw_cftwiabps10(h,o,v,k,...)				\
  uint32_t hw_bps=(v), br=0, psc=0, pscreg=0 ;			\
  float brpsc = ((1.0*HW_SYSHZ / hw_bps)-16)/2 ;		\
  if ( brpsc < 256 ) {						\
    psc = 1 ;							\
    pscreg = 0 ;						\
    br = (uint32_t)(0.5 + brpsc) ;				\
    if ( brpsc < 1 && HW_SYSHZ != hw_bps*(16+2*psc*br) )	\
      HWA_E(HW_EM_XSO(v,bps)); /* value of bps unreachable */	\
  } else if ( brpsc < 4*256 ) {					\
    psc = 4 ;							\
    pscreg = 1 ;						\
    br = (uint32_t)(0.5 + brpsc/4) ;				\
  } else if ( brpsc < 16*256 ) {				\
    psc = 16 ;							\
    pscreg = 2 ;						\
    br = (uint32_t)(0.5 + brpsc/16) ;				\
  } else if ( brpsc < 64*256 ) {				\
    psc = 64 ;							\
    pscreg = 3 ;						\
    br = (uint32_t)(0.5 + brpsc/64) ;				\
  } else							\
    HWA_E(HW_EM_XSO(v,bps)); /* value of bps too low */		\
  h##_write( o, psc, pscreg );					\
  h##_write( o, br, br );					\
  HW_BW(_hw_cftwiasa,slave_address,k)(h,o,k,__VA_ARGS__)

/*	Optionnal argument `slave_address`
 */
#define _hw_cftwiasa0(h,o,k,...)	HW_BW(_hw_cftwiagc,general_call,k)(h,o,k,__VA_ARGS__)
#define _hw_cftwiasa1(h,o,k,v,...)	HW_B(_hw_cftwiasa1,v)(h,o,v,__VA_ARGS__)
#define _hw_cftwiasa11(h,o,v,...)	HW_E(HW_EM_VAM(slave_address))
#define _hw_cftwiasa10(h,o,v,k,...)				\
    uint8_t hw_sla=(v);						\
    if ( hw_sla < 0 || hw_sla > 127 )				\
      HWA_E(HW_EM_VAL(v,slave_address,(0..127)));		\
    h##_write( o, sla, hw_sla );				\
    HW_BW(_hw_cftwiagc,general_call,k)(h,o,k,__VA_ARGS__)

/*	Optionnal argument `general_call`
 */
#define _hw_cftwiagc0			_hw_cftwiasam
#define _hw_cftwiagc1(h,o,k,v,...)	HW_BV(_hw_cftwiagc1,state_,v,h,o) (h,o,__VA_ARGS__) // PUSH
#define _hw_cftwiagc10(v,...)		HW_E(HW_EM_VOAST(v,general_call)) HW_EAT // POP
#define _hw_cftwiagc11(v,n,h,o)		h##_write( o, gce, v); _hw_cftwiasam // POP


/*	Optionnal argument `slave_address_mask`
 */
#define _hw_cftwiasam(h,o,k,...)	HW_BW(_hw_cftwiasam,slave_address_mask,k)(h,o,k,__VA_ARGS__)
#define _hw_cftwiasam0(h,o,...)		HW_EOL(__VA_ARGS__)
#define _hw_cftwiasam1(h,o,k,v,...)	HW_B(_hw_cftwia_vslam_,v)(h,o,v,__VA_ARGS__)
#define _hw_cftwiasam11(h,o,v,...)	HW_E(HW_EM_VAM(slave_address_mask))
#define _hw_cftwiasam10(h,o,v,...)			\
    uint8_t hw_sam=(v);					\
    if ( hw_sam < 0 || hw_sam > 127 )			\
      HWA_E(HW_EM_VAL(v,slave_address_mask,(0..127)));	\
    h##_write( o, slam, hw_sam ) HW_EOL(__VA_ARGS__)


/*  Submitted by gotnone via GitHub */
/**
 * @addtogroup atmelavr_twia
 * <br>
 * `turn`:
 * @code
 * hw( turn, twi0, on | off );
 * @endcode
 * @code
 * hwa( turn, twi0, on | off );
 * @endcode
 */
#define hw_turn__twia			, _hw_tntwia_
#define hwa_turn__twia			, _hwa_tntwia_

#define _hw_tntwia_(o,a, v, ...)	HW_B(_hw_tntwia__,_hw_state_##v)(_hw,o,v,__VA_ARGS__)
#define _hwa_tntwia_(o,a, v, ...)	HW_B(_hw_tntwia__,_hw_state_##v)(_hwa,o,v,__VA_ARGS__)
#define _hw_tntwia__0(h,o, v, ...)	HW_E(HW_EM_ST(v))
#define _hw_tntwia__1(h,o, v, ...)	h##_write(o, en, HW_A1(_hw_state_##v)) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_twia
 *
 * @code
 * hw( xfr_start, twi0 [,irq] );		// Transmit START condition
 * @endcode
 *
 * @code
 * hw( xfr_slaw, twi0, SLA [,irq] );		// Transmit SLA slave address + write bit
 * @endcode
 *
 * @code
 * hw( xfr_slar, twi0, SLA [,irq] );		// Transmit SLA slave address + read bit
 * @endcode
 *
 * @code
 * hw( xfr_write, twi0, DATA [,irq] );		// Transmit DATA
 * @endcode
 *
 * @code
 * hw( xfr_read, twi0, ack | nack [,irq] );	// Receive one byte, send ACK or NACK
 * @endcode
 *
 * @code
 * hw( xfr_stop, twi0 [,irq] );			// Transmit STOP condition
 * @endcode
 *
 * The optionnal `irq` parameter can be used to have the command enable the IRQ.
 *
 * These actions set the 'TWEN' bit so that the TWI takes control of the I/O pins.
 */
/*  TODO:
 *   * create a relative '(TWI,bus)' to handle TWI bus operations?
 *   * use get/put for bus transfers?
 *
 *  FIXME: could use a function 'hw_id(uint8_t v){ return v; }' to check the
 *  presence of a value so that '*ptr' would be OK?
 *    --> Could use surrounding parentheses.
 *
 *  FIXME: bus_xfer_ack / bus_xfer_nack actions?
 */
#define hw_xfr_start__twia		, _hw_twia_txstart
#define _hw_twia_txstart(o,a,k,...)	HW_BW(_hw_twiaend,irq,k)(o,ifenstart,k,__VA_ARGS__)


#define hw_xfr_stop__twia		, _hw_twia_txstop
#define _hw_twia_txstop(o,a,k,...)	HW_BW(_hw_twiaend,irq,k)(o,ifenstop,k,__VA_ARGS__)


#define hw_xfr_slaw__twia		, _hw_twia_txslaw
#define _hw_twia_txslaw(o,a,v,k,...)			\
  do{							\
    uint8_t hw_sla=(v);					\
    if ( hw_sla > 127 )					\
      HWA_E(HW_EM_VAL(v,slave address,(0..127)));	\
    _hw_write(o,dr,(hw_sla<<1)+0);			\
    HW_BW(_hw_twiaend,irq,k)(o,ifen,k,__VA_ARGS__);	\
  }while(0)


#define hw_xfr_slar__twia		, _hw_twia_txslar
#define _hw_twia_txslar(o,a,v,k,...)			\
  do{							\
    uint8_t hw_sla=(v);					\
    if ( hw_sla > 127 )					\
      HWA_E(HW_EM_VAL(v,slave address,(0..127)));	\
    _hw_write(o,dr,(hw_sla<<1)+1);			\
    HW_BW(_hw_twiaend,irq,k)(o,ifen,k,__VA_ARGS__);	\
  }while(0)

#define hw_xfr_write__twia		, _hw_twiawr
#define _hw_twiawr(o,a,v,k,...)				\
  do {							\
    _hw_write(o,dr,(v));				\
    HW_BW(_hw_twiaend,irq,k)(o,ifen,k,__VA_ARGS__);	\
  } while(0)


#define hw_xfr_read__twia		, _hw_twiard
#define _hw_twiard(o,a,k,...)		HW_BW(_hw_twiardack,ack,k)(o,k,__VA_ARGS__,,)
#define _hw_twiardack1(o,ok,k,...)	HW_BW(_hw_twiaend,irq,k)(o,ifenack,k,__VA_ARGS__)
#define _hw_twiardack0(o,k,...)		HW_BW(_hw_twiardnack,nack,k)(o,k,__VA_ARGS__)
#define _hw_twiardnack1(o,ok,k,...)	HW_BW(_hw_twiaend,irq,k)(o,ifen,k,__VA_ARGS__)
#define _hw_twiardnack0(o,k,...)	HW_E(HW_EM_XNIL(k,(ack,nack)))


#define _hw_twiaend0(o,v,...)		_hw_write(o,cr,_hw_twia_cr_##v) HW_EOL(__VA_ARGS__)
#define _hw_twiaend1(o,v,...)		_hw_write(o,cr,_hw_twia_cr_##v##ie) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_twia
 *
 * `read`:
 *
 * @code
 * uint8_t byte = hw( read, twi0 );
 * @endcode
 */
#define hw_read__twia			, _hw_rdtwia
#define _hw_rdtwia(o,a,...)		_hw_read(o,dr) HW_EOL(__VA_ARGS__)



/**
 * @addtogroup atmelavr_twia
 * <br>
 * `stat`: returns the status flags of the TWI as a byte whose value
 * can be compared to HWA predefined symbols:
 *
 * @code
 * if ( hw(stat,twi0) == HW_TWI_START ) {
 *	// Start condition has been transmitted
 * }
 * @endcode
 *
 * Predefined TWI status symbols are:
 */
#define hw_stat__twia			, _hw_stat_twia
#define _hw_stat_twia(o,a,...)		(_hw_read(o,sr)&0xF8) HW_EOL(__VA_ARGS__)


/** @addtogroup atmelavr_twia
 *
 *  * Transmitter:
 *    * `HW_TWI_START`: start condition transmitted
 */
#define HW_TWI_START			0x08

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_REP_START`: repeated start condition transmitted
 */
#define HW_TWI_REP_START		0x10

/** @addtogroup atmelavr_twia
 *  * Master Transmitter:
 *    * `HW_TWI_MT_SLA_ACK`: SLA+W transmitted, ACK received
 */
#define HW_TWI_MT_SLA_ACK		0x18

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_MT_SLA_NACK`: SLA+W transmitted, NACK received
 */
#define HW_TWI_MT_SLA_NACK		0x20

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_MT_DATA_ACK`: data transmitted, ACK received
 */
#define HW_TWI_MT_DATA_ACK		0x28

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_MT_DATA_NACK`: data transmitted, NACK received
 */
#define HW_TWI_MT_DATA_NACK		0x30

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_MT_ARB_LOST`: arbitration lost in SLA+W or data
 */
#define HW_TWI_MT_ARB_LOST		0x38

/** @addtogroup atmelavr_twia
 *  * Master Receiver:
 *    * `HW_TWI_MR_ARB_LOST`: arbitration lost in SLA+R or NACK
 */
#define HW_TWI_MR_ARB_LOST		0x38

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_MR_SLA_ACK`: SLA+R transmitted, ACK received
 */
#define HW_TWI_MR_SLA_ACK		0x40

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_MR_SLA_NACK`: SLA+R transmitted, NACK received
 */
#define HW_TWI_MR_SLA_NACK		0x48

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_MR_DATA_ACK`: data received, ACK returned
 */
#define HW_TWI_MR_DATA_ACK		0x50

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_MR_DATA_NACK`: data received, NACK returned
 */
#define HW_TWI_MR_DATA_NACK		0x58

/** @addtogroup atmelavr_twia
 *  * Slave Receiver:
 *    * `HW_TWI_SR_SLA_ACK`: SLA+W received, ACK returned
 */
#define HW_TWI_SR_SLA_ACK		0x60

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_SR_ARB_LOST_SLA_ACK`: arbitration lost in SLA+RW, SLA+W received, ACK returned
 */
#define HW_TWI_SR_ARB_LOST_SLA_ACK	0x68

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_SR_GCALL_ACK`: general call received, ACK returned
 */
#define HW_TWI_SR_GCALL_ACK		0x70

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_SR_ARB_LOST_GCALL_ACK`: arbitration lost in SLA+RW, general call
 *	received, ACK returned
 */
#define HW_TWI_SR_ARB_LOST_GCALL_ACK	0x78

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_SR_DATA_ACK`: data received, ACK returned
 */
#define HW_TWI_SR_DATA_ACK		0x80

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_SR_DATA_NACK`: data received, NACK returned
 */
#define HW_TWI_SR_DATA_NACK		0x88

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_SR_GCALL_DATA_ACK`: general call data received, ACK returned
 */
#define HW_TWI_SR_GCALL_DATA_ACK	0x90

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_SR_GCALL_DATA_NACK`: general call data received, NACK returned
 */
#define HW_TWI_SR_GCALL_DATA_NACK	0x98

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_SR_STOP`: stop or repeated start condition received while selected
 */
#define HW_TWI_SR_STOP			0xA0

/** @addtogroup atmelavr_twia
 *  * Slave Transmitter:
 *    * `HW_TWI_ST_SLA_ACK`: SLA+R received, ACK returned
 */
#define HW_TWI_ST_SLA_ACK		0xA8

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_ST_ARB_LOST_SLA_ACK`: arbitration lost in SLA+RW, SLA+R received, ACK returned
 */
#define HW_TWI_ST_ARB_LOST_SLA_ACK	0xB0

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_ST_DATA_ACK`: data transmitted, ACK received
 */
#define HW_TWI_ST_DATA_ACK		0xB8

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_ST_DATA_NACK`: data transmitted, NACK received
 */
#define HW_TWI_ST_DATA_NACK		0xC0

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_ST_LAST_DATA`: last data byte transmitted, ACK received
 */
#define HW_TWI_ST_LAST_DATA		0xC8

/** @addtogroup atmelavr_twia
 *  * Misc:
 *    * `HW_TWI_NO_INFO`: no state information available
 */
#define HW_TWI_NO_INFO			0xF8

/** @addtogroup atmelavr_twia
 *    * `HW_TWI_BUS_ERROR`: illegal start or stop condition
 */
#define HW_TWI_BUS_ERROR		0x00
 


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__twia(o,a)			\
  _hwa_setup_r( o, br	 );			\
  _hwa_setup_r( o, cr	 );			\
  _hwa_setup_r( o, sr	 );			\
  _hwa_setup_r( o, ar	 );			\
  _hwa_setup_r( o, amr )


#define _hwa_init__twia(o,a)			\
  _hwa_init_r( o, br,	 0x00 );		\
  _hwa_init_r( o, cr,	 0x00 );		\
  _hwa_init_r( o, sr,	 0xF8 );		\
  _hwa_init_r( o, ar,	 0xFE );		\
  _hwa_init_r( o, amr, 0x00 )


#define _hwa_commit__twia(o,a)			\
  _hwa_commit_r( o, br	);			\
  _hwa_commit_r( o, cr	);			\
  _hwa_commit_r( o, sr	);			\
  _hwa_commit_r( o, ar	);			\
  _hwa_commit_r( o, amr )
  

/**
 * @addtogroup atmelavr_twia
 * @section atmelavr_twia_regs Registers
 *
 * Class `_twia` objects hold the following hardware registers:
 *
 *  * `br`: bit rate register
 *  * `cr`: control register
 *  * `sr`: status + prescaler register
 *  * `ar`: slave address + general call register
 *  * `amr`: slave address mask register
 *
 * that hold the following logical registers:
 *
 *  * `start`: transmit start condition
 *  * `stop`: transmit stop condition
 *  * `ack`: enable ack
 *  * `collision`: collision detected
 *  * `en`: enable SCL/SDA I/O control
 *  * `if`: IRQ flag
 *  * `ie`: enable IRQ
 *  * `status`: status code
 *  * `psc`: prescaler setting
 *  * `sla`: slave address
 *  * `slam`: enable ack mask
 *  * `gce`: general call enable
 */


/*******************************************************************************
 *									       *
 *	Implementation							       *
 *									       *
 *******************************************************************************/

#define HW_DECLARE__twia		, _hw_declare_twia

#define _hw_declare_twia(o,a,...)					\
    void _hw_##o##_start_write_stop ( uint8_t sla, uint8_t v );		\
    uint8_t _hw_##o##_start_read_stop ( uint8_t sla ) HW_EOL(__VA_ARGS__)


#define HW_IMPLEMENT__twia		, _hw_define_twia

#define _hw_define_twia(o,a,...)				\
    void _hw_##o##_start_write_stop ( uint8_t sla, uint8_t v )	\
    {								\
      hw( xfr_start, o );					\
      while( !hw( read, (o,irq) ) ) {}				\
      hw( xfr_slaw, o, sla & 0x7F );				\
      while( !hw( read, (o,irq) ) ) {}				\
      hw( xfr_write, o, v );					\
      while( !hw( read, (o,irq) ) ) {}				\
      hw( xfr_stop, o );					\
    }								\
								\
    uint8_t _hw_##o##_start_read_stop ( uint8_t sla )		\
    {								\
      hw( xfr_start, o );					\
      while( !hw( read, (o,irq) ) ) {}				\
      hw( xfr_slaw, o, sla & 0x7F );				\
      while( !hw( read, (o,irq) ) ) {}				\
      hw( xfr_read, o, nack );					\
      while( !hw( read, (o,irq) ) ) {}				\
      hw( xfr_stop, o );					\
    								\
      return hw( read, o );					\
    }								\
								\
    extern uint8_t hw_foo()					\
    								\
      HW_EOL(__VA_ARGS__)
