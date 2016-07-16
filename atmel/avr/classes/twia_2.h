
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
 * @section atmelavr_twia_cf Configuration
 *
 * @note Configuring the TWI enables it and configures the SCL and SDA pins as
 * high-level outputs.
 *
 * @code
 * hw_config( TWI_NAME,
 *
 *            //  scl speed
 *            //
 *          [ sclhz,                <value>, ]
 *
 *          [ slave_address,        <value>, ]
 *
 *          [ general_call,         enabled
 *                                | disabled, ]
 *
 *          [ slave_address_mask,   <value> ]
 *
 *          );
 * @endcode
 */
#define _hw_mthd_hw_config__twia		, _hw_cftwia
#define _hw_cftwia( o,i,a, ... )		_hwx_cftwia( _hw, o, __VA_ARGS__,, )

/**
 * @page atmelavr_twia
 *
 * @code
 * hwa_config( TWI_NAME,
 *
 *             //  scl speed
 *             //
 *           [ sclhz,                <value>, ]
 *
 *           [ slave_address,        <value>, ]
 *
 *           [ general_call,         enabled
 *                                 | disabled, ]
 *
 *           [ slave_address_mask,   <value> ]
 *
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__twia		, _hwa_cftwia
#define _hwa_cftwia( o,i,a, ... )		_hwx_cftwia( _hwa, o, __VA_ARGS__,, )
\

/*	Optionnal argument `sclhz`
 */
#define _hwx_cftwia(x,o,k,...)						\
  do {									\
    /*	Configure I/Os */						\
    x##_config( hw_rel(o,pin_scl), direction, output );			\
    x##_config( hw_rel(o,pin_sda), direction, output );			\
    x##_write( hw_rel(o,pin_scl), 1 );					\
    x##_write( hw_rel(o,pin_sda), 1 );					\
    HW_G2(_hwx_cftwia_ksclhz, HW_IS(sclhz,k))(x,o,k,__VA_ARGS__);	\
  } while(0)

#define _hwx_cftwia_ksclhz_1(x,o,k,v,...)			\
  HW_G2(_hwx_cftwia_vsclhz, HW_IS(,v))(x,o,v,__VA_ARGS__)

#define _hwx_cftwia_vsclhz_1(x,o,v,...)		\
  HW_ERR("value of `sclhz` must be a number.")

#define _hwx_cftwia_vsclhz_0(x,o,v,k,...)				\
  uint32_t br=0, psc=0, pscreg=0 ;					\
  float brpsc = ((1.0*hw_syshz / v)-16)/2 ;				\
  if ( brpsc < 256 ) {							\
    psc = 1 ;								\
    pscreg = 0 ;							\
    br = (uint32_t)(0.5 + brpsc) ;					\
    if ( brpsc < 1 && hw_syshz != v*(16+2*psc*br) )			\
      HWA_ERR("can not find a configuration for `sclhz = " #v "`.");	\
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
    HWA_ERR("value of `sclhz` is too low.");				\
  x##_write_reg( o, psc, pscreg );					\
  x##_write_reg( o, br, br );						\
  HW_G2(_hwx_cftwia_ksladdr, HW_IS(slave_address,k))(x,o,k,__VA_ARGS__)

#define _hwx_cftwia_ksclhz_0(x,o,k,...)					\
  HW_G2(_hwx_cftwia_ksladdr, HW_IS(slave_address,k))(x,o,k,__VA_ARGS__)

#define _hw_is_sclhz_sclhz		, 1

/*	Optionnal argument `slave_address`
 */
#define _hwx_cftwia_ksladdr_1(x,o,k,v,...)			\
  HW_G2(_hwx_cftwia_vsladdr, HW_IS(,v))(x,o,v,__VA_ARGS__)

#define _hwx_cftwia_vsladdr_1(x,o,v,...)		\
  HW_ERR("value of `slave_address` must be a number.")

#define _hwx_cftwia_vsladdr_0(x,o,v,k,...)				\
  if ( v < 0 || v > 127 )						\
    HWA_ERR("value of `slave_address` must be in the range 0..127.");	\
  x##_write_reg( o, sla, v );						\
  HW_G2(_hwx_cftwia_kgcall, HW_IS(general_call,k))(x,o,k,__VA_ARGS__)

#define _hwx_cftwia_ksladdr_0(x,o,k,...)				\
  HW_G2(_hwx_cftwia_kgcall, HW_IS(general_call,k))(x,o,k,__VA_ARGS__)

#define _hw_is_slave_address_slave_address		, 1

/*	Optionnal argument `general_call`
 */
#define _hwx_cftwia_kgcall_1(x,o,k,v,...)				\
  HW_G2(_hwx_cftwia_vgcall, HW_IS(,_hw_state_##v))(x,o,v,__VA_ARGS__)

#define _hwx_cftwia_vgcall_0(x,o,v,...)					\
  HW_ERR("`general_call` can be `enabled` or `disabled`, but not `" #v "`.")

#define _hwx_cftwia_vgcall_1(x,o,v,k,...)				\
  x##_write_reg( o, gce, HW_A1(_hw_state_##v );				\
		 HW_G2(_hwx_cftwia_kslam, HW_IS(slave_address_mask,k))(x,o,k,__VA_ARGS__)

#define _hwx_cftwia_kgcall_0(x,o,k,...)					\
  HW_G2(_hwx_cftwia_kslam, HW_IS(slave_address_mask,k))(x,o,k,__VA_ARGS__)

#define _hw_is_general_call_general_call		, 1

/*	Optionnal argument `slave_address_mask`
 */
#define _hwx_cftwia_kslam_1(x,o,k,v,...)			\
  HW_G2(_hwx_cftwia_vslam, HW_IS(,v))(x,o,v,__VA_ARGS__)

#define _hwx_cftwia_vslam_1(x,o,v,...)				\
  HW_ERR("value of `slave_address_mask` must be a number.")

#define _hwx_cftwia_vslam_0(x,o,v,...)					\
  if ( v < 0 || v > 127 )						\
    HWA_ERR("value of `slave_address_mask` must be in the range 0..127."); \
  HW_TX( x##_write_reg( o, slam, v ), __VA_ARGS__)

#define _hwx_cftwia_kslam_0(x,o,...)		\
  HW_EOL(__VA_ARGS__)

#define _hw_is_slave_address_mask_slave_address_mask	, 1


/**
 * @page atmelavr_twia
 * @section Commands
 *
 * Class `_twia` peripherals are driven using the `hw_cmd()` instruction.
 * An optionnal `irq` parameter can be used to have the command enable the IRQ.
 *
 * @note HWA verifies to some extent the nature of the given parameters. As all
 * this is implemented using macro definitions, some care must be taken
 * regarding how the parameters are written in order to avoid strange
 * behavior. For example, if the DATA parameter is `*ptr`, you must rewrite it
 * as `(*ptr)` or use a temporary, as the preprocessor can not process the `*`
 * character.
 *
 * @code
 * hw_cmd( TWI_NAME, start [,irq] );                // Transmit START condition
 * hw_cmd( TWI_NAME, slaw, SLA [,irq] );            // Transmit SLA slave address + write bit
 * hw_cmd( TWI_NAME, slar, SLA [,irq] );            // Transmit SLA slave address + read bit
 * hw_cmd( TWI_NAME, write, DATA [,irq] );          // Transmit DATA
 * hw_cmd( TWI_NAME, read, ack | nack [,irq] );     // Receive one byte, send ACK or NACK
 * hw_cmd( TWI_NAME, stop [,irq] );                 // Transmit STOP condition
 * @endcode
 */

#define _hw_cmd__twia_start		, _hw_cmd_twia_start
#define _hw_cmd_twia_start(o,...)					\
  HW_G2(_hw_cmd_twia_end,HW_IS(irq,__VA_ARGS__))(o,ifenstart,__VA_ARGS__)


#define _hw_cmd__twia_stop		, _hw_cmd_twia_stop
#define _hw_cmd_twia_stop(o,...)					\
  HW_G2(_hw_cmd_twia_end,HW_IS(irq,__VA_ARGS__))(o,ifenstop,__VA_ARGS__)


#define _hw_cmd__twia_slaw		, _hw_cmd_twia_slaw
#define _hw_cmd_twia_slaw(o,...)				\
  HW_G2(_hw_cmd_twia_vslaw,HW_IS(,__VA_ARGS__))(o,__VA_ARGS__)
#define _hw_cmd_twia_vslaw_1(...)		\
  HW_ERR("slave address missing.")
#define _hw_cmd_twia_vslaw_0(o,v,...)					\
  if ( ((uint8_t)(v)) > 127 )						\
    HWA_ERR("slave address must be in the range 0..127.");		\
  _hw_write_reg(o,dr,((v)<<1)+0);					\
  HW_G2(_hw_cmd_twia_end,HW_IS(irq,__VA_ARGS__))(o,ifen,__VA_ARGS__)


#define _hw_cmd__twia_slar		, _hw_cmd_twia_slar
#define _hw_cmd_twia_slar(o,...)					\
  HW_G2(_hw_cmd_twia_vslar,HW_IS_VOID(__VA_ARGS__))(o,__VA_ARGS__)
#define _hw_cmd_twia_vslar_1(...)		\
  HW_ERR("slave address missing.")
#define _hw_cmd_twia_vslar_0(o,v,...)					\
  if ( ((uint8_t)(v)) > 127 )						\
    HWA_ERR("slave address must be in the range 0..127.");		\
  _hw_write_reg(o,dr,((v)<<1)+1);					\
  HW_G2(_hw_cmd_twia_end,HW_IS(irq,__VA_ARGS__))(o,ifen,__VA_ARGS__)


#define _hw_cmd__twia_write		, _hw_cmd_twia_write
#define _hw_cmd_twia_write(o,...)					\
  HW_G2(_hw_cmd_twia_vwrite,HW_IS_VOID(__VA_ARGS__))(o,__VA_ARGS__)
#define _hw_cmd_twia_vwrite_1(...)		\
  HW_ERR("value missing.")
#define _hw_cmd_twia_vwrite_0(o,v,...)					\
  _hw_write_reg(o,dr,v);						\
  HW_G2(_hw_cmd_twia_end,HW_IS(irq,__VA_ARGS__))(o,ifen,__VA_ARGS__)


#define _hw_cmd__twia_read		, _hw_cmd_twia_read
#define _hw_cmd_twia_read(o,...)					\
  HW_G2(_hw_cmd_twia_read_ack,HW_IS(ack,__VA_ARGS__))(o,__VA_ARGS__)
#define _hw_cmd_twia_read_ack_1(o,k,...)				\
  HW_G2(_hw_cmd_twia_end,HW_IS(irq,__VA_ARGS__))(o,ifenack,__VA_ARGS__)
#define _hw_cmd_twia_read_ack_0(o,...)					\
  HW_G2(_hw_cmd_twia_read_nack,HW_IS(nack,__VA_ARGS__))(o,__VA_ARGS__)
#define _hw_cmd_twia_read_nack_1(o,k,...)				\
  HW_G2(_hw_cmd_twia_end,HW_IS(irq,__VA_ARGS__))(o,ifen,__VA_ARGS__)
#define _hw_cmd_twia_read_nack_0(o,...)					\
  HW_ERR("expected `ack` or `nack` instead of `" #__VA_ARGS__ "`.");

#define _hw_is_ack_ack			, 1
#define _hw_is_nack_nack		, 1


#define _hw_cmd_twia_end_0(o,v,...)				\
  HW_TX( _hw_write_reg(o,cr,_hw_twia_cr_##v), __VA_ARGS__ )

#define _hw_cmd_twia_end_1(o,v,k,...)				\
  HW_TX( _hw_write_reg(o,cr,_hw_twia_cr_##v##ie), __VA_ARGS__ )

#define _hw_is_irq_irq			, 1


/**
 * @page atmelavr_twia
 * @section atmelavr_twia_data Data
 *
 * The `hw_read()` returns the content of the data register.
 *
 * @code
 * uint8_t byte = hw_read( TWI_NAME );
 * @endcode
 */
#define _hw_mthd_hw_read__twia		, _hw_rdtwia
#define _hw_rdtwia(o,i,a,...)		HW_TX(_hw_read_reg(o,dr),__VA_ARGS__)



/**
 * @page atmelavr_twia
 * @section atmelavr_twia_stat Status
 *
 * The `hw_stat()` instruction returns the status flags of the TWI as a byte
 * whose value can be compared to HWA predefined symbols:
 *
 * @code
 * if ( hw_stat(TWI_NAME) == HW_TWI_START ) {
 *      // Start condition has been transmitted
 * }
 * @endcode
 *
 * Predefined TWI status symbols are:
 */
#define _hw_mthd_hw_stat__twia		, _hw_stat_twia
#define _hw_stat_twia(o,i,a,...)	HW_TX((_hw_read_reg(o,sr)&0xF8), __VA_ARGS__)


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

#define _hwa_setup__twia(o,i,a)			\
  _hwa_setup_reg( o, br	 );			\
  _hwa_setup_reg( o, cr	 );			\
  _hwa_setup_reg( o, sr	 );			\
  _hwa_setup_reg( o, ar	 );			\
  _hwa_setup_reg( o, amr )


#define _hwa_init__twia(o,i,a)			\
  _hwa_init_reg( o, br,	 0x00 );		\
  _hwa_init_reg( o, cr,	 0x00 );		\
  _hwa_init_reg( o, sr,	 0xF8 );		\
  _hwa_init_reg( o, ar,	 0xFE );		\
  _hwa_init_reg( o, amr, 0x00 )


#define _hwa_commit__twia(o,i,a)		\
  _hwa_commit_reg( o, br  );			\
  _hwa_commit_reg( o, cr  );			\
  _hwa_commit_reg( o, sr  );			\
  _hwa_commit_reg( o, ar  );			\
  _hwa_commit_reg( o, amr )
  

/**
 * @page atmelavr_twia
 * @section atmelavr_twia_internals Internals
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
 *
 * These registers are accessible through the @ref public_reg_instructions
 * "register access intructions".
 */


/**
 * @page atmelavr_twia
 * <br>
 */
