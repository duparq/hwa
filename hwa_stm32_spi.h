#ifndef HWA_STM32_SPI_H
#define HWA_STM32_SPI_H

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_SPI1_BASE			HWA_APB2+0x3000 /* 0x40013000 */
#define HWA_SPI2_BASE			HWA_APB1+0x3800 /* 0x40003800 */
#define HWA_SPI3_BASE			HWA_APB1+0x3C00 /* 0x40003C00 */

#define HWA_SPI_HWA_CR1			volatile, u16, 0x00, 0x0000, 0xFFFF
#define HWA_SPI_HWA_CR2			volatile, u16, 0x04, 0x0000, 0x00E7
#define HWA_SPI_HWA_SR			volatile, u16, 0x08, 0x0002, 0x0010
#define HWA_SPI_HWA_DR			volatile, u16, 0x0C, 0x0000, 0xFFFF
#define HWA_SPI_HWA_CRCPR			, u16, 0x10                
#define HWA_SPI_HWA_RXCRC		volatile, u16, 0x14, 0x0000, 0x0000
#define HWA_SPI_HWA_TXCRC		volatile, u16, 0x18, 0x0000, 0x0000
#define HWA_SPI_HWA_I2SCFGR		volatile, u16, 0x1C, 0x0000, 0x0FBF
#define HWA_SPI_HWA_I2SPR		volatile, u16, 0x20, 0x0002, 0x03FF

/*	Non-committable registers
 */
#define HWA_SPI_HWA_BAUDRATE		, u32, -1, 0, 0xFFFFFFFF

/*	Register bits definitions
 */
#define HWA_SPI_CR1_BIDIMODE		HWA_CR1, 0b1,  15
#define HWA_SPI_CR1_BIDIOE		HWA_CR1, 0b1,  14
#define HWA_SPI_CR1_CRCEN		HWA_CR1, 0b1,  13
#define HWA_SPI_CR1_CRCNEXT		HWA_CR1, 0b1,  12
#define HWA_SPI_CR1_DFF			HWA_CR1, 0b1,  11
#define HWA_SPI_CR1_RXONLY		HWA_CR1, 0b1,  10
#define HWA_SPI_CR1_SSM			HWA_CR1, 0b1,   9
#define HWA_SPI_CR1_SSI			HWA_CR1, 0b1,   8
#define HWA_SPI_CR1_LSBFIRST		HWA_CR1, 0b1,   7
#define HWA_SPI_CR1_SPE			HWA_CR1, 0b1,   6
#define HWA_SPI_CR1_BR			HWA_CR1, 0b111, 3 
#define HWA_SPI_CR1_MSTR		HWA_CR1, 0b1,   2
#define HWA_SPI_CR1_CPOL		HWA_CR1, 0b1,   1
#define HWA_SPI_CR1_CPHA		HWA_CR1, 0b1,   0

#define HWA_SPI_SR_BSY			HWA_SR, 0b1, 7
#define HWA_SPI_SR_OVR			HWA_SR, 0b1, 6
#define HWA_SPI_SR_MODF			HWA_SR, 0b1, 5
#define HWA_SPI_SR_CRCERR		HWA_SR, 0b1, 4
#define HWA_SPI_SR_UDR			HWA_SR, 0b1, 3
#define HWA_SPI_SR_CHSIDE		HWA_SR, 0b1, 2
#define HWA_SPI_SR_TXE			HWA_SR, 0b1, 1
#define HWA_SPI_SR_RXNE			HWA_SR, 0b1, 0

/*	Pins
 */
#define HWA_SPI1_SCK			PA5
#define HWA_SPI1_MISO			PA6
#define HWA_SPI1_MOSI			PA7


typedef struct {
  HWA_PDCL();
  HWA_VDCL(HWA_SPI, HWA_CR1);
  HWA_VDCL(HWA_SPI, HWA_CR2);
  HWA_VDCL(HWA_SPI, HWA_BAUDRATE);
} HWA_SPI ;

#define hwa_begin_spi(reset)			\
  hwa_spi_begin(HWA_SPI1, reset)		\
  hwa_spi_begin(HWA_SPI2, reset)		\
  hwa_spi_begin(HWA_SPI3, reset)

#define hwa_spi_begin(pname, reset)			\
  HWA_PINIT(HWA_SPI, pname);				\
  HWA_VINIT(HWA_SPI, pname, HWA_CR1, reset);		\
  HWA_VINIT(HWA_SPI, pname, HWA_CR2, reset);		\
  HWA_VINIT(HWA_SPI, pname, HWA_BAUDRATE, 0);

#define hwa_commit_spi()						\
  _hwa_spi_commit(hwa_nocommit, HWA_P(HWA_SPI1), HWA_P(HWA_CLOCK0));	\
  _hwa_spi_commit(hwa_nocommit, HWA_P(HWA_SPI2), HWA_P(HWA_CLOCK0));	\
  _hwa_spi_commit(hwa_nocommit, HWA_P(HWA_SPI3), HWA_P(HWA_CLOCK0));


inline s8
hwa_log2 ( u16 n )
{
  s8 l2 = 0 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  if ( (1<<l2) == n ) return l2 ; if ( ++l2 > 15 ) return -1 ;
  return -1 ;
}


inline void
_hwa_spi_commit ( u8 dry, HWA_SPI *p, HWA_CLOCK *c )
{
  if ( !p->used )
    return ;

  u32 baudrate = HWA_NVALP(p, HWA_BAUDRATE) ;
  if ( baudrate != HWA_NONE ) {
    u32 clkhz ;
    if ( p->hwaddr == HWA_SPI1_BASE )
      clkhz = HWA_NVALP(c, HWA_APB2HZ) ;
    else
      clkhz = HWA_NVALP(c, HWA_APB1HZ) ;

    if ( clkhz == HWA_NONE )
      HWA_ERROR("Bus clock speed not set.");

    s8 psc = hwa_log2( clkhz / baudrate ) ;
    if ( psc < 1 || psc > 8 )
      HWA_ERROR("Can not find prescaler value for baudrate.");
    HWA_VSETP(HWA_SPI, p, HWA_SPI_CR1_BR, psc-1);
  }

  HWA_COMMITP(dry, HWA_SPI, p, HWA_CR1, -1, 0);
  HWA_COMMITP(dry, HWA_SPI, p, HWA_CR2, -1, 0);
  HWA_COMMITP(dry, HWA_SPI, p, HWA_BAUDRATE, -1, 0);

  p->used = 0 ;
}



/************************************************************************
 *									*
 *			Synchronous actions				*
 *									*
 ************************************************************************/

/**
 * @brief  SPI data register
 *
 * @param  pname: SPI1, SPI2, or SPI3
 */
#define hw_spi_data(pname)		HWA_HREG(HWA_SPI, pname, HWA_DR)
#define hw_spi_set_data(pname, value)	HWA_HREG(HWA_SPI, pname, HWA_DR) = value

/**
 * @brief  Check if SPI can transmit
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @retval bool
 */
#define hw_spi_tx_ready(pname)				\
  (HWA_HGET(HWA_SPI, pname, HWA_SPI_SR_TXE) != 0)


/**
 * @brief  Check if SPI data available
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @retval bool
 */
#define hw_spi_rx_ready(pname)				\
  (HWA_HGET(HWA_SPI, pname, HWA_SPI_SR_RXNE) != 0)


/**
 */
#define hw_spi_is_busy(pname)				\
  (HWA_HGET(HWA_SPI, pname, HWA_SPI_SR_BSY) != 0)


#define hw_spi_tx(pname, byte)			\
  do {						\
    while ( !hw_spi_tx_ready(pname) ) {	}	\
    hw_spi_data(pname) = byte ;			\
  } while(0)


/* #define hw_spi_rx(pname)			\ */
/*   HWA_GLUE3(hw_,pname,_rx)() */


/************************************************************************
 *									*
 *			Asynchronous actions				*
 *									*
 ************************************************************************/


/**
 * @brief  Initializes an SPI peripheral
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  mode: MASTER or SLAVE
 * @param  dir: 2LINES_RXTX, 2LINES_RX, 1LINE_RX, or 1LINE_TX
 * @shiht  shift: 
 * @retval None
 */
#define hwa_spi_set_mode(pname, mode, dir, size, shift, clkidle, clkedge) \
  do {									\
    hwa_prph_turn_clk(pname, ON);					\
    /*									\
     *	Start configuration from RESET defaults				\
     */									\
    HWA_VINIT(HWA_SPI, pname, HWA_CR1, 1);				\
    HWA_VINIT(HWA_SPI, pname, HWA_CR2, 1);				\
									\
    hwa_gpio_config_pin(HWA_G2(pname, SCK), ALTOUTPUT);			\
  									\
    if (HWA_SPI_MODE_##mode == HWA_SPI_MODE_MASTER) {			\
      HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_SSI, 1);		\
      HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_MSTR, 1);		\
    } else								\
      HWA_ERROR("SPI Mode not supported yet.");				\
    									\
    if (HWA_SPI_DIR_##dir == HWA_SPI_DIR_2LINES_RXTX) {			\
      hwa_gpio_config_pin(HWA_G2(pname, MOSI), ALTOUTPUT);		\
      hwa_gpio_config_pin(HWA_G2(pname, MISO), INPUT_PULLUP);		\
      HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_SPE, 1);		\
    } else {								\
      HWA_WARN("SPI DIR not tested yet.");				\
      if (HWA_SPI_DIR_##dir == HWA_SPI_DIR_2LINES_RX) {			\
	hwa_gpio_config_pin(HWA_G2(pname, MOSI), ALTOUTPUT);		\
	hwa_gpio_config_pin(HWA_G2(pname, MISO), INPUT_PULLUP);		\
	HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_RXONLY, 1);	\
      } else if (HWA_SPI_DIR_##dir == HWA_SPI_DIR_1LINE_RX) {		\
	HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_BIDIMODE, 1);	\
      } else if (HWA_SPI_DIR_##dir == HWA_SPI_DIR_1LINE_TX) {		\
	HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_BIDIMODE, 1);	\
	HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_BIDIOE, 1);	\
      }									\
    }									\
    									\
    HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_DFF, HWA_SPI_DATASIZE_##size); \
    HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_LSBFIRST, HWA_SPI_SHIFT_##shift); \
    HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_CPOL, HWA_SPI_CLKIDLE_##clkidle); \
    HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_CPHA, HWA_SPI_CLKSAMPLE_##clkedge); \
  } while(0)

#if 0
#endif

#define HWA_SPI_MODE_MASTER		0
#define HWA_SPI_MODE_SLAVE		1
#define HWA_SPI_DIR_2LINES_RXTX		0
#define HWA_SPI_DIR_2LINES_RX		1
#define HWA_SPI_DIR_1LINE_RX		2
#define HWA_SPI_DIR_1LINE_TX		3
#define HWA_SPI_DATASIZE_8BITS		0
#define HWA_SPI_DATASIZE_16BITS		1
#define HWA_SPI_SHIFT_MSBFIRST		0
#define HWA_SPI_SHIFT_LSBFIRST		1
#define HWA_SPI_CLKIDLE_CLK_IDLE_LOW	0
#define HWA_SPI_CLKIDLE_CLK_IDLE_HIGH	1
#define HWA_SPI_CLKSAMPLE_SAMPLE_EDGE1	0
#define HWA_SPI_CLKSAMPLE_SAMPLE_EDGE2	1


/**
 * @brief  Set SPI baudrate
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  rate: PCLK divided by 2, 4, 8, 16, 32, 64, 128, 256
 * @note   SPI1 is clocked by PCLK2, SPI2 and SPI3 are clocked by PCLK1
 * @retval None
 */

#define hwa_spi_set_baudrate(pname, baudrate)				\
  hwa_prph_turn_clk(pname, ON);						\
  HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_BAUDRATE, -1, 0, baudrate);


/**
 * @brief  Set SPI data size
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  size: 8BITS or 16BITS
 * @retval None
 */
#define hwa_spi_set_datasize(pname, size)		\
  do {							\
    if ( size == 8 )					\
      HWA_VSETP(HWA_SPI, pname, HWA_SPI_CR1_DFF, 0);	\
    else if ( size == 16 )				\
      HWA_VSETP(HWA_SPI, pname, HWA_SPI_CR1_DFF, 1);	\
    else						\
      HWA_ERROR("Format not supported.");		\
  }


/**
 * @brief  Set SPI clock idle state
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  state: LOW or HIGH
 * @retval None
 */
#define hwa_spi_set_clk_idle_state(pname, state)			\
  HWA_VSETP(HWA_SPI, pname, HWA_SPI_CR1_CPOL, HWA_SPI_CLK_IDLE_##state)

#define HWA_SPI_CLK_IDLE_LOW		0
#define HWA_SPI_CLK_IDLE_HIGH		1


/**
 * @brief  Set SPI clock phase
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  phase: EDGE1 or EDGE2
 * @retval None
 */
#define hwa_spi_set_clk_phase(pname, phase)				\
  HWA_VSETP(HWA_SPI, pname, HWA_SPI_CR1_CPHA, HWA_SPI_CLK_PHASE_##phase)

#define HWA_SPI_CLK_PHASE_EDGE1		0
#define HWA_SPI_CLK_PHASE_EDGE2		1


/**
 * @brief  Set SPI slave management
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  mode: HARDWARE or SOFTWARE
 * @retval None
 */
#define hwa_spi_set_slave_management(pname, mode)		\
  HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_SSM, HWA_SPI_NSS_##mode)

#define HWA_SPI_NSS_HARDWARE		0
#define HWA_SPI_NSS_SOFTWARE		1


/**
 * @brief  Turn SPI IRQ ON/OFF
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  irq: TX, RX, ERR
 * @param  state: ON or OFF
 * @retval None
 */
#define hwa_spi_turn_irq(pname, irq, state)		\
  HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_CR2, 0b1, HWA_SPI_IRQ_##irq, HWA_STATE_##state)

#define HWA_SPI_IRQ_TX			7
#define HWA_SPI_IRQ_RX			6
#define HWA_SPI_IRQ_ERR			5


/**
 * @brief  Turn SPI ON/OFF
 *
 * @param  pname: SPI1, SPI2, or SPI3
 * @param  state: ON or OFF
 * @retval None
 */
#define hwa_spi_turn(pname, state)		\
  HWA_VSETP(HWA_SPI, HWA_P(pname), HWA_SPI_CR1_SPE, HWA_STATE_##state)



/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

/* #define _HW_SPI_DEF_RX(pname)			\ */
/*   inline u8					\ */
/*   hw_##pname##_rx()				\ */
/*   {						\ */
/*     while ( !hw_spi_rx_ready(pname) ) {}	\ */
/*     return *hw_spi_data(pname) ;		\ */
/*   } */

/* _HW_SPI_DEF_RX(SPI1) */
/* _HW_SPI_DEF_RX(SPI2) */
/* _HW_SPI_DEF_RX(SPI3) */

#endif
