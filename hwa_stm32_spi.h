#ifndef HWA_SPI_H
#define HWA_SPI_H

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/


/**
 * @brief  Check if SPI can transmit
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @retval bool
 */
#define hw_spi_tx_ready(pname)				\
  (HW_REGBITS(pname, SR, 0b1, 1) != 0) /* TXE */


/**
 * @brief  Check if SPI data available
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @retval bool
 */
#define hw_spi_rx_ready(pname)			\
  (HW_REGBITS(pname, SR, 0b1, 0) != 0) /* RXNE */

#define hw_spi_is_busy(pname)				\
  (HW_REGBITS(pname, SR, 0b1, 7) != 0) /* BSY */


#define hw_spi_tx(pname, byte)			\
  do {						\
    while ( !hw_spi_tx_ready(pname) ) {	}	\
    *hw_spi_data(pname) = byte ;		\
  } while(0)


#define hw_spi_rx(pname)			\
  HWA_GLUE3(hw_,pname,_rx)()


/**
 * @brief  SPI data register
 *
 * @param  pname: SPI1, SPI2, or SPI3
 */
#define hw_spi_data(pname)			\
  HWA_GLUE3(HWA_PTR_,pname,_DR)


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

/**
  * @brief  Initializes an SPI peripheral
  *
  * @param  pname: SPI1, SPI2, or SPI3
  * @param  mode: MASTER or SLAVE
  * @param  dir: 2LINES_RXTX, 2LINES_RX, 1LINE_RX, or 1LINE_TX
  * @retval None
  */
#define hwa_spi_set_mode(pname, mode, dir)	\
  _hwa_spi_set_mode(pname, HWA_SPI_MODE_##mode, HWA_SPI_DIR_##dir)

#define HWA_SPI_MODE_MASTER		0
#define HWA_SPI_MODE_SLAVE		1
#define HWA_SPI_DIR_2LINES_RXTX		0
#define HWA_SPI_DIR_2LINES_RX		1
#define HWA_SPI_DIR_1LINE_RX		2
#define HWA_SPI_DIR_1LINE_TX		3

#define _hwa_spi_set_mode(pname, mode, dir)				\
  do {									\
    HWA_SET(pname##_CR1, (u32)0xFFFF, 0, 0);/* Reset value */		\
    if (mode == HWA_SPI_MODE_MASTER) {					\
      HWA_SET(pname##_CR1, 0b1, 8, 1); /* SSI */			\
      HWA_SET(pname##_CR1, 0b1, 2, 1); /* MSTR */			\
    }									\
    if (dir == HWA_SPI_DIR_2LINES_RX) {					\
      HWA_SET(pname##_CR1, 0b1, 10, 1); /* RXONLY */			\
    } else if (dir == HWA_SPI_DIR_1LINE_RX) {				\
      HWA_SET(pname##_CR1, 0b1, 15, 1); /* BIDIMODE */			\
    } else if (dir == HWA_SPI_DIR_1LINE_TX) {				\
      HWA_SET(pname##_CR1, 0b11, 14, 0x3); /* BIDIMODE BIDIOE */	\
    }									\
  } while(0)


/**
 * @brief  Set SPI data size
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  size: 8BITS or 16BITS
 * @retval None
 */
#define hwa_spi_set_datasize(pname, size)	\
  _hwa_spi_set_datasize(pname, HWA_SPI_##size)

#define HWA_SPI_8BITS			0
#define HWA_SPI_16BITS			1

#define _hwa_spi_set_datasize(pname, size)	\
  HWA_SET(pname##_CR1, 0b1, 11, size) /* DFF */

/**
 * @brief  Set SPI clock idle state
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  state: LOW or HIGH
 * @retval None
 */
#define hwa_spi_set_clk_idle_state(pname, state)		\
  _hwa_spi_set_clk_idle_state(pname, HWA_SPI_CLK_IDLE_##state)

#define HWA_SPI_CLK_IDLE_LOW		0
#define HWA_SPI_CLK_IDLE_HIGH		1

#define _hwa_spi_set_clk_idle_state(pname, state)	\
  HWA_SET(pname##_CR1, 0b1, 1, state) /* CPOL */

/**
 * @brief  Set SPI clock phase
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  phase: EDGE1 or EDGE2
 * @retval None
 */
#define hwa_spi_set_clk_phase(pname, phase)		\
  _hwa_spi_set_clk_phase(pname, HWA_SPI_CLK_PHASE_##phase)

#define HWA_SPI_CLK_PHASE_EDGE1		0
#define HWA_SPI_CLK_PHASE_EDGE2		1

#define _hwa_spi_set_clk_phase(pname, phase)	\
  HWA_SET(pname##_CR1, 0b1, 0, phase) /* CPHA */

/**
 * @brief  Set SPI slave management
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  mode: HARDWARE or SOFTWARE
 * @retval None
 */
#define hwa_spi_set_slave_management(pname, mode)		\
  _hwa_spi_set_slave_management(pname, HWA_SPI_NSS_##mode)

#define HWA_SPI_NSS_HARDWARE		0
#define HWA_SPI_NSS_SOFTWARE		1

#define _hwa_spi_set_slave_management(pname, mode)	\
  HWA_SET(pname##_CR1, 0b1, 9, mode) /* SSM */

/**
 * @brief  Set SPI baudrate
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  rate: PCLK divided by 2, 4, 8, 16, 32, 64, 128, 256
 * @note   SPI1 is clocked by PCLK2, SPI2 and SPI3 are clocked by PCLK1
 * @retval None
 */
#define hwa_spi_set_baudrate(pname, rate)		\
  _hwa_spi_set_baudrate(pname, rate)

#define HWA_SPI_NSS_HARDWARE		0
#define HWA_SPI_NSS_SOFTWARE		1

#define _hwa_spi_set_baudrate(pname, rate)		\
  do {							\
    u32 clk ;						\
    if (HWA_PTR_##pname##_CR1 == HWA_PTR_SPI1_CR1)	\
      clk = PCLK2_HZ ;					\
    else						\
      clk = PCLK1_HZ ;					\
    if (clk / rate == 2) {				\
      HWA_SET(pname##_CR1, 0b111, 3, 0x0);		\
    } else if (clk / rate == 4) {			\
      HWA_SET(pname##_CR1, 0b111, 3, 0x1);		\
    } else if (clk / rate == 8) {			\
      HWA_SET(pname##_CR1, 0b111, 3, 0x2);		\
    } else if (clk / rate == 16) {			\
      HWA_SET(pname##_CR1, 0b111, 3, 0x3);		\
    } else if (clk / rate == 32) {			\
      HWA_SET(pname##_CR1, 0b111, 3, 0x4);		\
    } else if (clk / rate == 64) {			\
      HWA_SET(pname##_CR1, 0b111, 3, 0x5);		\
    } else if (clk / rate == 128) {			\
      HWA_SET(pname##_CR1, 0b111, 3, 0x6);		\
    } else if (clk / rate == 256) {			\
      HWA_SET(pname##_CR1, 0b111, 3, 0x7);		\
    } else {						\
      HWA_ERROR_CT(1, "Invalid baudrate");		\
    }							\
  } while(0)


/**
 * @brief  Set SPI shifting direction
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  dir: MSBFIRST or LSBFIRST
 * @retval None
 */
#define hwa_spi_set_shifting(pname, dir)		\
  _hwa_spi_set_shifting(pname, HWA_SPI_SHIFT_##dir)

#define HWA_SPI_SHIFT_MSBFIRST		0
#define HWA_SPI_SHIFT_LSBFIRST		1

#define _hwa_spi_set_shifting(pname, dir)	\
  HWA_SET(pname##_CR1, 0b1, 7, dir) /* LSBFIRST */


/**
 * @brief  Set SPI CRC polynomial
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  poly: 16 bits value of CRC polynomial
 * @retval None
 */
#define hwa_spi_set_crc_polynomial(pname, poly)		\
  hw_spi_set_crc_polynomial(pname, poly)

#define hw_spi_set_crc_polynomial(pname, poly)	\
  *HWA_PTR_##pname##_CRCPR = poly


/**
 * @brief  Turn SPI hardware CRC calculator ON/OFF
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  state: ON or OFF
 * @retval None
 */
#define hwa_spi_turn_crc_calculator(pname, state)		\
  _hwa_spi_turn_crc_calculator(pname, HWA_STATE_##state)

#define _hwa_spi_turn_crc_calculator(pname, state)	\
  HWA_SET(pname##_CR1, 0b1, 13, state) /* CRCEN */


/**
 * @brief  Turn SPI ON/OFF
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  state: ON or OFF
 * @retval None
 */
#define hwa_spi_turn(pname, state)		\
  _hwa_spi_turn(pname, HWA_STATE_##state)

#define _hwa_spi_turn(pname, state)	\
  HWA_SET(pname##_CR1, 0b1, 6, state) /* SPE */


/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

#define HWA_PTR_SPI1			HWA_PTR_APB2+0x3000 /* 0x40013000 */
#define HWA_PTR_SPI2			HWA_PTR_APB1+0x3800 /* 0x40003800 */
#define HWA_PTR_SPI3			HWA_PTR_APB1+0x3C00 /* 0x40003C00 */

#define HWA_PTR_SPI1_CR1		((volatile u16 *)(HWA_PTR_SPI1+0x00))
#define HWA_PTR_SPI1_CR2		((volatile u16 *)(HWA_PTR_SPI1+0x04))
#define HWA_PTR_SPI1_SR			((volatile u16 *)(HWA_PTR_SPI1+0x08)) /* 0x40013008 */
#define HWA_PTR_SPI1_DR			((volatile u16 *)(HWA_PTR_SPI1+0x0C))
#define HWA_PTR_SPI1_CRCPR		((         u16 *)(HWA_PTR_SPI1+0x10))
#define HWA_PTR_SPI1_RXCRC		((volatile u16 *)(HWA_PTR_SPI1+0x14))
#define HWA_PTR_SPI1_TXCRC		((volatile u16 *)(HWA_PTR_SPI1+0x18))
#define HWA_PTR_SPI1_I2SCFGR		((volatile u16 *)(HWA_PTR_SPI1+0x1C))
#define HWA_PTR_SPI1_I2SPR		((volatile u16 *)(HWA_PTR_SPI1+0x20))

#define HWA_PTR_SPI2_CR1		((volatile u16 *)(HWA_PTR_SPI2+0x00))
#define HWA_PTR_SPI2_CR2		((volatile u16 *)(HWA_PTR_SPI2+0x04))
#define HWA_PTR_SPI2_SR			((volatile u16 *)(HWA_PTR_SPI2+0x08))
#define HWA_PTR_SPI2_DR			((volatile u16 *)(HWA_PTR_SPI2+0x0C))
#define HWA_PTR_SPI2_CRCPR		((         u16 *)(HWA_PTR_SPI2+0x10))
#define HWA_PTR_SPI2_RXCRC		((volatile u16 *)(HWA_PTR_SPI2+0x14))
#define HWA_PTR_SPI2_TXCRC		((volatile u16 *)(HWA_PTR_SPI2+0x18))
#define HWA_PTR_SPI2_I2SCFGR		((volatile u16 *)(HWA_PTR_SPI2+0x1C))
#define HWA_PTR_SPI2_I2SPR		((volatile u16 *)(HWA_PTR_SPI2+0x20))

#define HWA_PTR_SPI3_CR1		((volatile u16 *)(HWA_PTR_SPI3+0x00))
#define HWA_PTR_SPI3_CR2		((volatile u16 *)(HWA_PTR_SPI3+0x04))
#define HWA_PTR_SPI3_SR			((volatile u16 *)(HWA_PTR_SPI3+0x08))
#define HWA_PTR_SPI3_DR			((volatile u16 *)(HWA_PTR_SPI3+0x0C))
#define HWA_PTR_SPI3_CRCPR		((         u16 *)(HWA_PTR_SPI3+0x10))
#define HWA_PTR_SPI3_RXCRC		((volatile u16 *)(HWA_PTR_SPI3+0x14))
#define HWA_PTR_SPI3_TXCRC		((volatile u16 *)(HWA_PTR_SPI3+0x18))
#define HWA_PTR_SPI3_I2SCFGR		((volatile u16 *)(HWA_PTR_SPI3+0x1C))
#define HWA_PTR_SPI3_I2SPR		((volatile u16 *)(HWA_PTR_SPI3+0x20))

#define HWA_IRQN_SPI1			?
#define HWA_IRQN_SPI2			?
#define HWA_IRQN_SPI3			?


#define hwa_spi_begin(state)			\
  hwa_spi_begin_(SPI1, state)			\
  hwa_spi_begin_(SPI2, state)			\
  hwa_spi_begin_(SPI3, state)

/*	Registers declarations: name, type, address, reset value, write mask
 */
#define hwa_spi_begin_(pname, state)					\
  HWA_DECL(pname##_CR1,     u16, HWA_PTR_##pname+0x00, 0x0000, 0xFFFF, state) \
  HWA_DECL(pname##_CR2,     u16, HWA_PTR_##pname+0x04, 0x0000, 0x00E7, state) \
  HWA_DECL(pname##_DR,      u16, HWA_PTR_##pname+0x0C, 0x0000, 0xFFFF, state) \
  HWA_DECL(pname##_RXCRC,   u16, HWA_PTR_##pname+0x14, 0x0000, 0x0000, state) \
  HWA_DECL(pname##_TXCRC,   u16, HWA_PTR_##pname+0x18, 0x0000, 0x0000, state) \
  HWA_DECL(pname##_I2SCFGR, u16, HWA_PTR_##pname+0x1C, 0x0000, 0x0FBF, state) \
  HWA_DECL(pname##_I2SPR,   u16, HWA_PTR_##pname+0x20, 0x0002, 0x03FF, state)

#define hwa_spi_commit()			\
  hwa_spi_commit_(SPI1)				\
  hwa_spi_commit_(SPI2)				\
  hwa_spi_commit_(SPI3)

#define hwa_spi_commit_(pname)			\
  HWA_COMMIT(pname##_CR1);			\
  HWA_COMMIT(pname##_CR2);			\
  HWA_COMMIT(pname##_DR);			\
  HWA_COMMIT(pname##_RXCRC);			\
  HWA_COMMIT(pname##_TXCRC);			\
  HWA_COMMIT(pname##_I2SCFGR);			\
  HWA_COMMIT(pname##_I2SPR);

#define _HW_SPI_DEF_RX(pname)			\
  inline u8					\
  hw_##pname##_rx()				\
  {						\
    while ( !hw_spi_rx_ready(pname) ) {}	\
    return *hw_spi_data(pname) ;		\
  }

_HW_SPI_DEF_RX(SPI1)
_HW_SPI_DEF_RX(SPI2)
_HW_SPI_DEF_RX(SPI3)

#endif
