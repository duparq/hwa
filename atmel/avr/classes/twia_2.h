
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 2-wire interface
 */

/**
 * @page atmelavr_twia
 * @section atmelavr_twia_act Actions
 *
 * `configure`:
 *
 * __Note__ The `configure` action does not make the TWI take control of the SCL
 * and SDA pins until a `bus_` action is triggered. Then, it keeps control over
 * these pins until the TWI is turned off.
 *
 * @code
 * hw | hwa( configure, twi0,
 *
 *	   [ bps,		   <value>, ]	//  SCL speed
 *
 *	   [ slave_address,	   <value>, ]
 *
 *	   [ general_call,	   enabled
 *	   			 | disabled, ]
 *
 *	   [ slave_address_mask,   <value> ] );
 * @endcode
 */
#define hw_configure__twia		, _hw_cftwia
#define _hw_cftwia( o,a, ... )	_hwx_cftwia( _hw, o, __VA_ARGS__,, )

#define hwa_configure__twia		, _hwa_cftwia
#define _hwa_cftwia( o,a, ... )	_hwx_cftwia( _hwa, o, __VA_ARGS__,, )

/*	Optionnal argument `bps`
 */
#define _hwx_cftwia(x,o,k,...)						\
  do {									\
    /*	The 'TWEN' bit that makes the TWI take control of the */	\
    /*	I/O pins is set by the 'bus_' actions */			\
    HW_Y(_hwx_cftwia_kbps_,_hw_is_bps_##k)(x,o,k,__VA_ARGS__);		\
  } while(0)

#define _hwx_cftwia_kbps_1(x,o,k,v,...)		\
  HW_Y(_hwx_cftwia_vbps_,v)(x,o,v,__VA_ARGS__)

#define _hwx_cftwia_vbps_1(x,o,v,...)		HW_E_VM(bps)

#define _hwx_cftwia_vbps_0(x,o,v,k,...)					\
  uint32_t br=0, psc=0, pscreg=0 ;					\
  float brpsc = ((1.0*HW_SYSHZ / v)-16)/2 ;				\
  if ( brpsc < 256 ) {							\
    psc = 1 ;								\
    pscreg = 0 ;							\
    br = (uint32_t)(0.5 + brpsc) ;					\
    if ( brpsc < 1 && HW_SYSHZ != v*(16+2*psc*br) )			\
      HWA_ERR("can not find a configuration for `bps = " #v "`.");	\
  } else if ( brpsc < 4*256 ) {						\
    psc = 4 ;								\
    pscreg = 1 ;							\
    br = (uint32_t)(0.5 + brpsc/4) ;					\
  } else if ( brpsc < 16*256 ) {					\
    psc = 16 ;								\
    pscreg = 2 ;							\
    br = (uint32_t)(0.5 + brpsc/16) ;					\
  } else if ( brpsc < 64*256 ) {					\
    psc = 64 ;								\
    pscreg = 3 ;							\
    br = (uint32_t)(0.5 + brpsc/64) ;					\
  } else								\
    HWA_ERR("value of `bps` is too low.");				\
  x##_write( o, psc, pscreg );						\
  x##_write( o, br, br );						\
  HW_G2(_hwx_cftwia_ksladdr,HW_IS(slave_address,k))(x,o,k,__VA_ARGS__)

#define _hwx_cftwia_kbps_0(x,o,k,...)					\
  HW_G2(_hwx_cftwia_ksladdr,HW_IS(slave_address,k))(x,o,k,__VA_ARGS__)

/*	Optionnal argument `slave_address`
 */
#define _hwx_cftwia_ksladdr_1(x,o,k,v,...)		\
  HW_Y(_hwx_cftwia_vsladdr_,v)(x,o,v,__VA_ARGS__)

#define _hwx_cftwia_vsladdr_1(x,o,v,...)	HW_E_VM(slave_address)

#define _hwx_cftwia_vsladdr_0(x,o,v,k,...)				\
  if ( v < 0 || v > 127 )						\
    HWA_ERR("value of `slave_address` must be in the range 0..127.");	\
  x##_write( o, sla, v );						\
  HW_G2(_hwx_cftwia_kgcall,HW_IS(general_call,k))(x,o,k,__VA_ARGS__)

#define _hwx_cftwia_ksladdr_0(x,o,k,...)				\
  HW_G2(_hwx_cftwia_kgcall,HW_IS(general_call,k))(x,o,k,__VA_ARGS__)

/*	Optionnal argument `general_call`
 */
#define _hwx_cftwia_kgcall_1(x,o,k,v,...)			\
  HW_Y(_hwx_cftwia_vgcall_,_hw_state_##v)(x,o,v,__VA_ARGS__)

#define _hwx_cftwia_vgcall_0(x,o,v,...)		\
  HW_E_AVL(general_call, v, enabled | disabled)

#define _hwx_cftwia_vgcall_1(x,o,v,k,...)				\
  x##_write( o, gce, HW_A1(_hw_state_##v );				\
  HW_G2(_hwx_cftwia_kslam,HW_IS(slave_address_mask,k))(x,o,k,__VA_ARGS__)

#define _hwx_cftwia_kgcall_0(x,o,k,...)					\
  HW_G2(_hwx_cftwia_kslam,HW_IS(slave_address_mask,k))(x,o,k,__VA_ARGS__)

/*	Optionnal argument `slave_address_mask`
 */
#define _hwx_cftwia_kslam_1(x,o,k,v,...)	\
  HW_Y(_hwx_cftwia_vslam_,v)(x,o,v,__VA_ARGS__)

#define _hwx_cftwia_vslam_1(x,o,v,...)		HW_E_VM(slave_address_mask)

#define _hwx_cftwia_vslam_0(x,o,v,...)					\
  if ( v < 0 || v > 127 )						\
    HWA_ERR("value of `slave_address_mask` must be in the range 0..127."); \
  x##_write( o, slam, v ) HW_EOL(__VA_ARGS__)

#define _hwx_cftwia_kslam_0(x,o,...)		\
  HW_EOL(__VA_ARGS__)


/*  Submitted by gotnone via GitHub */
/**
 * @page atmelavr_twia
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

#define _hw_tntwia_(o,a, v, ...)	HW_Y(_hwx_tntwia__,_hw_state_##v)(_hw,o,v,__VA_ARGS__)
#define _hwa_tntwia_(o,a, v, ...)	HW_Y(_hwx_tntwia__,_hw_state_##v)(_hwa,o,v,__VA_ARGS__)
#define _hwx_tntwia__0(x,o, v, ...)	HW_E_ST(v)
#define _hwx_tntwia__1(x,o, v, ...)	x##_write(o, en, HW_A1(_hw_state_##v)) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_twia
 *
 * `bus_...`:
 *
 * @code
 * hw( bus_start, twi0 [,irq] );	      // Transmit START condition
 * @endcode
 * @code
 * hw( bus_slaw,  twi0, SLA [,irq] );	      // Transmit SLA slave address + write bit
 * @endcode
 * @code
 * hw( bus_slar,  twi0, SLA [,irq] );	      // Transmit SLA slave address + read bit
 * @endcode
 * @code
 * hw( bus_write,  twi0, DATA [,irq] );	      // Transmit DATA
 * @endcode
 * @code
 * hw( bus_read,  twi0, ack | nack [,irq] );  // Receive one byte, send ACK or NACK
 * @endcode
 * @code
 * hw( bus_stop,  twi0 [,irq] );	      // Transmit STOP condition
 * @endcode
 *
 * The optionnal `irq` parameter can be used to have the command enable the IRQ.
 *
 * These actions set the 'TWEN' bit so that the TWI takes control of the I/O pins.
 *
 * __Note__ HWA verifies to some extent the nature of the given parameters. As
 * all this is implemented using macro definitions, some care must be taken
 * regarding how the parameters are written in order to avoid a strange behavior
 * of the compiler. For example, if the DATA parameter is `*ptr`, you must
 * rewrite it as `(*ptr)` or use a temporary, as the preprocessor can not
 * process the `*` character. (FIXME: could use a function 'hw_id(uint8_t v){
 * return v; }' to check the presence of a value so that '*ptr' would be OK?)
 */
/*  TODO:
 *   * create a relative '(TWI,bus)' to handle TWI bus operations?
 *   * use get/put for bus transfers?
 */
#define hw_bus_start__twia		, _hw_twia_txstart
#define _hw_twia_txstart(o,a,k,...)	HW_Y(_hw_twia_txend_,_hw_is_irq_##k)(o,ifenstart,k,__VA_ARGS__)


#define hw_bus_stop__twia		, _hw_twia_txstop
#define _hw_twia_txstop(o,a,k,...)	HW_Y(_hw_twia_txend_,_hw_is_irq_##k)(o,ifenstop,k,__VA_ARGS__)


#define hw_bus_slaw__twia		, _hw_twia_txslaw
#define _hw_twia_txslaw(o,a,...)	HW_Y(_hw_twia_txslawv_,__VA_ARGS__)(o,__VA_ARGS__)
#define _hw_twia_txslawv_1(...)		HW_E(missing slave address)
#define _hw_twia_txslawv_0(o,v,k,...)				\
  do {								\
    if ( ((uint8_t)(v)) > 127 )					\
      HWA_ERR("slave address must be in the range 0..127.");	\
    _hw_write(o,dr,((v)<<1)+0);					\
    HW_Y(_hw_twia_txend_,_hw_is_irq_##k)(o,ifen,k,__VA_ARGS__);	\
  } while(0)


#define hw_bus_slar__twia		, _hw_twia_txslar
#define _hw_twia_txslar(o,a,...)	HW_Y(_hw_twia_vtxslar_,__VA_ARGS__)(o,__VA_ARGS__)
#define _hw_twia_vtxslar_1(...)		HW_E(missing slave address)
#define _hw_twia_vtxslar_0(o,v,k,...)				\
  do {								\
    if ( ((uint8_t)(v)) > 127 )					\
      HWA_ERR("slave address must be in the range 0..127.");	\
    _hw_write(o,dr,((v)<<1)+1);					\
    HW_Y(_hw_twia_txend_,_hw_is_irq_##k)(o,ifen,k,__VA_ARGS__);	\
  } while(0)

/*  FIXME: could use a function 'hw_id(uint8_t v){ return v; }' to check the
 *  presence of a value so that '*ptr' would be OK?
 */
#define hw_bus_write__twia		, _hw_twiawr
#define _hw_twiawr(o,a,...)		HW_Y(_hw_twiawrv_,__VA_ARGS__)(o,__VA_ARGS__)
#define _hw_twiawrv_1(...)		HW_E(missing value)
#define _hw_twiawrv_0(o,v,k,...)					\
  do {									\
    _hw_write(o,dr,v);							\
    HW_Y(_hw_twia_txend_,_hw_is_irq_##k,)(o,ifen,k,__VA_ARGS__);	\
  } while(0)


#define hw_bus_read__twia		, _hw_twiard
#define _hw_twiard(o,a,k,...)		HW_Y0(_hw_twiard_ack,_hw_is_ack_##k)(o,k,__VA_ARGS__,,)
#define _hw_twiard_ack1(o,ok,k,...)	HW_Y0(_hw_twia_txend_,_hw_is_irq_##k)(o,ifenack,k,__VA_ARGS__)
#define _hw_twiard_ack0(o,k,...)	HW_Y0(_hw_twiard_nack,_hw_is_nack_##k)(o,k,__VA_ARGS__)
#define _hw_twiard_nack1(o,ok,k,...)	HW_Y0(_hw_twia_txend_,_hw_is_irq_##k)(o,ifen,k,__VA_ARGS__)
#define _hw_twiard_nack0(o,k,...)	HW_E_VL(k, ack | nack)


#define _hw_twia_txend_0(o,v,...)	_hw_write(o,cr,_hw_twia_cr_##v) HW_EOL(__VA_ARGS__)
#define _hw_twia_txend_1(o,v,...)	_hw_write(o,cr,_hw_twia_cr_##v##ie) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_twia
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
 * @page atmelavr_twia
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
#define _hw_stat_twia(o,a,...)	(_hw_read(o,sr)&0xF8) HW_EOL(__VA_ARGS__)


/** @page atmelavr_twia
 *
 *  * Transmitter:
 *    * `HW_TWI_START`: start condition transmitted
 */
#define HW_TWI_START			0x08

/** @page atmelavr_twia
 *    * `HW_TWI_REP_START`: repeated start condition transmitted
 */
#define HW_TWI_REP_START		0x10

/** @page atmelavr_twia
 *  * Master Transmitter:
 *    * `HW_TWI_MT_SLA_ACK`: SLA+W transmitted, ACK received
 */
#define HW_TWI_MT_SLA_ACK		0x18

/** @page atmelavr_twia
 *    * `HW_TWI_MT_SLA_NACK`: SLA+W transmitted, NACK received
 */
#define HW_TWI_MT_SLA_NACK		0x20

/** @page atmelavr_twia
 *    * `HW_TWI_MT_DATA_ACK`: data transmitted, ACK received
 */
#define HW_TWI_MT_DATA_ACK		0x28

/** @page atmelavr_twia
 *    * `HW_TWI_MT_DATA_NACK`: data transmitted, NACK received
 */
#define HW_TWI_MT_DATA_NACK		0x30

/** @page atmelavr_twia
 *    * `HW_TWI_MT_ARB_LOST`: arbitration lost in SLA+W or data
 */
#define HW_TWI_MT_ARB_LOST		0x38

/** @page atmelavr_twia
 *  * Master Receiver:
 *    * `HW_TWI_MR_ARB_LOST`: arbitration lost in SLA+R or NACK
 */
#define HW_TWI_MR_ARB_LOST		0x38

/** @page atmelavr_twia
 *    * `HW_TWI_MR_SLA_ACK`: SLA+R transmitted, ACK received
 */
#define HW_TWI_MR_SLA_ACK		0x40

/** @page atmelavr_twia
 *    * `HW_TWI_MR_SLA_NACK`: SLA+R transmitted, NACK received
 */
#define HW_TWI_MR_SLA_NACK		0x48

/** @page atmelavr_twia
 *    * `HW_TWI_MR_DATA_ACK`: data received, ACK returned
 */
#define HW_TWI_MR_DATA_ACK		0x50

/** @page atmelavr_twia
 *    * `HW_TWI_MR_DATA_NACK`: data received, NACK returned
 */
#define HW_TWI_MR_DATA_NACK		0x58

/** @page atmelavr_twia
 *  * Slave Receiver:
 *    * `HW_TWI_SR_SLA_ACK`: SLA+W received, ACK returned
 */
#define HW_TWI_SR_SLA_ACK		0x60

/** @page atmelavr_twia
 *    * `HW_TWI_SR_ARB_LOST_SLA_ACK`: arbitration lost in SLA+RW, SLA+W received, ACK returned
 */
#define HW_TWI_SR_ARB_LOST_SLA_ACK	0x68

/** @page atmelavr_twia
 *    * `HW_TWI_SR_GCALL_ACK`: general call received, ACK returned
 */
#define HW_TWI_SR_GCALL_ACK		0x70

/** @page atmelavr_twia
 *    * `HW_TWI_SR_ARB_LOST_GCALL_ACK`: arbitration lost in SLA+RW, general call
 *	received, ACK returned
 */
#define HW_TWI_SR_ARB_LOST_GCALL_ACK	0x78

/** @page atmelavr_twia
 *    * `HW_TWI_SR_DATA_ACK`: data received, ACK returned
 */
#define HW_TWI_SR_DATA_ACK		0x80

/** @page atmelavr_twia
 *    * `HW_TWI_SR_DATA_NACK`: data received, NACK returned
 */
#define HW_TWI_SR_DATA_NACK		0x88

/** @page atmelavr_twia
 *    * `HW_TWI_SR_GCALL_DATA_ACK`: general call data received, ACK returned
 */
#define HW_TWI_SR_GCALL_DATA_ACK	0x90

/** @page atmelavr_twia
 *    * `HW_TWI_SR_GCALL_DATA_NACK`: general call data received, NACK returned
 */
#define HW_TWI_SR_GCALL_DATA_NACK	0x98

/** @page atmelavr_twia
 *    * `HW_TWI_SR_STOP`: stop or repeated start condition received while selected
 */
#define HW_TWI_SR_STOP			0xA0

/** @page atmelavr_twia
 *  * Slave Transmitter:
 *    * `HW_TWI_ST_SLA_ACK`: SLA+R received, ACK returned
 */
#define HW_TWI_ST_SLA_ACK		0xA8

/** @page atmelavr_twia
 *    * `HW_TWI_ST_ARB_LOST_SLA_ACK`: arbitration lost in SLA+RW, SLA+R received, ACK returned
 */
#define HW_TWI_ST_ARB_LOST_SLA_ACK	0xB0

/** @page atmelavr_twia
 *    * `HW_TWI_ST_DATA_ACK`: data transmitted, ACK received
 */
#define HW_TWI_ST_DATA_ACK		0xB8

/** @page atmelavr_twia
 *    * `HW_TWI_ST_DATA_NACK`: data transmitted, NACK received
 */
#define HW_TWI_ST_DATA_NACK		0xC0

/** @page atmelavr_twia
 *    * `HW_TWI_ST_LAST_DATA`: last data byte transmitted, ACK received
 */
#define HW_TWI_ST_LAST_DATA		0xC8

/** @page atmelavr_twia
 *  * Misc:
 *    * `HW_TWI_NO_INFO`: no state information available
 */
#define HW_TWI_NO_INFO			0xF8

/** @page atmelavr_twia
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


#define _hwa_commit__twia(o,a)		\
  _hwa_commit_r( o, br	);			\
  _hwa_commit_r( o, cr	);			\
  _hwa_commit_r( o, sr	);			\
  _hwa_commit_r( o, ar	);			\
  _hwa_commit_r( o, amr )
  

/**
 * @page atmelavr_twia
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

#define _hw_declare_twia(o,a,...)				\
								\
  HW_EOL(__VA_ARGS__)						\
								\
  void _hw_##o##_start_write_stop ( uint8_t sla, uint8_t v );	\
  uint8_t _hw_##o##_start_read_stop ( uint8_t sla )


#define HW_IMPLEMENT__twia		, _hw_define_twia

#define _hw_define_twia(o,a,...)				\
								\
  HW_EOL(__VA_ARGS__)						\
								\
  void _hw_##o##_start_write_stop ( uint8_t sla, uint8_t v )	\
  {								\
    hw( bus_start, o );						\
    while( !hw( read, (o,irq) ) ) {}				\
    hw( bus_slaw, o, sla & 0x7F );				\
    while( !hw( read, (o,irq) ) ) {}				\
    hw( bus_write, o, v );					\
    while( !hw( read, (o,irq) ) ) {}				\
    hw( bus_stop, o );						\
  }								\
								\
  uint8_t _hw_##o##_start_read_stop ( uint8_t sla )		\
  {								\
    hw( bus_start, o );						\
    while( !hw( read, (o,irq) ) ) {}				\
    hw( bus_slaw, o, sla & 0x7F );				\
    while( !hw( read, (o,irq) ) ) {}				\
    hw( bus_read, o, nack );					\
    while( !hw( read, (o,irq) ) ) {}				\
    hw( bus_stop, o );						\
								\
    return hw( read, o );					\
  }								\
								\
  HW_FOO() /* for semicolon */
