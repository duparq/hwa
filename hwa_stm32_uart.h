#ifndef HWA_UART_H
#define HWA_UART_H

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_uart_rx_ready(pname)			\
  _hw_uart_rx_ready(pname)

#define _hw_uart_rx_ready(pname)		\
  (HWA_BITS(*HWA_##pname##_SR, 0b1, 5) != 0)

#define hw_uart_data(pname)			\
  _hw_uart_data(pname)

#define hw_uart_txreg(pname)			\
  _hw_uart_data(pname)

#define hw_uart_rxreg(pname)			\
  _hw_uart_data(pname)

#define hw_uart_tx_ready(pname)			\
  _hw_uart_tx_ready(pname)

#define hw_uart_getchar(pname)			\
  hw_##pname##_getchar()

#define hw_uart_putchar(pname, byte)		\
  do {						\
    while ( !hw_uart_tx_ready(pname) ) {}	\
    *hw_uart_txreg(pname) = byte ;		\
  } while(0)

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_uart_turn_irq(pname, irq, state)	\
  _hwa_uart_turn_irq(pname, irq, state)

#define hwa_uart_turn_rx(pname, state)		\
  _hwa_uart_turn_rx(pname, state)

#define hwa_uart_turn_tx(pname, state)		\
  _hwa_uart_turn_tx(pname, state)

#define hwa_uart_set_baudrate(pname, baudrate)	\
  _hwa_uart_set_baudrate(pname, baudrate)

#define hwa_uart_set_databits(pname, nb)		\
  _hwa_uart_set_databits(pname, nb)

#define hwa_uart_set_parity(pname, p)			\
  _hwa_uart_set_parity(pname, p)

#define hwa_uart_turn_hwctrl(pname, hwctrl)				\
  _hwa_uart_turn_hwctrl(pname, hwctrl)

/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

#define HWA_USART1				HWA_APB2+0x3800 /* 0x40013800 */
#define HWA_USART2				HWA_APB1+0x4400 /* 0x40004400 */
#define HWA_USART3				HWA_APB1+0x4800 /* 0x40004800 */
#define HWA_UART4				HWA_APB1+0x4c00 /* 0x40004c00 */
#define HWA_UART5				HWA_APB1+0x5000 /* 0x40005000 */

#define HWA_IRQN_USART1				37

#if 0
#define HW_UART_SR(pname)			(*(volatile u32 *)(HWA_##pname+0x00))
#define HW_UART_DR(pname)			(*(volatile u32 *)(HWA_##pname+0x04))
#define HW_UART_BRR(pname)			(*(volatile u32 *)(HWA_##pname+0x08))
#define HW_UART_CR1(pname)			(*(volatile u32 *)(HWA_##pname+0x0C))
#define HW_UART_CR2(pname)			(*(volatile u32 *)(HWA_##pname+0x10))
#define HW_UART_CR3(pname)			(*(volatile u32 *)(HWA_##pname+0x14))
#define HW_UART_GTPR(pname)			(*(volatile u32 *)(HWA_##pname+0x18))
#endif

#define HWA_USART1_SR			((volatile u32 *)(HWA_USART1+0x00))
#define HWA_USART1_DR			((volatile u32 *)(HWA_USART1+0x04))
#define HWA_USART1_BRR			((volatile u32 *)(HWA_USART1+0x08))
#define HWA_USART1_CR1			((volatile u32 *)(HWA_USART1+0x0C))
#define HWA_USART1_CR2			((volatile u32 *)(HWA_USART1+0x10))
#define HWA_USART1_CR3			((volatile u32 *)(HWA_USART1+0x14))
#define HWA_USART1_GTPR			((volatile u32 *)(HWA_USART1+0x18))

#define HWA_USART2_SR			((volatile u32 *)(HWA_USART2+0x00))
#define HWA_USART2_DR			((volatile u32 *)(HWA_USART2+0x04))
#define HWA_USART2_BRR			((volatile u32 *)(HWA_USART2+0x08))
#define HWA_USART2_CR1			((volatile u32 *)(HWA_USART2+0x0C))
#define HWA_USART2_CR2			((volatile u32 *)(HWA_USART2+0x10))
#define HWA_USART2_CR3			((volatile u32 *)(HWA_USART2+0x14))
#define HWA_USART2_GTPR			((volatile u32 *)(HWA_USART2+0x18))

#define HWA_USART3_SR			((volatile u32 *)(HWA_USART3+0x00))
#define HWA_USART3_DR			((volatile u32 *)(HWA_USART3+0x04))
#define HWA_USART3_BRR			((volatile u32 *)(HWA_USART3+0x08))
#define HWA_USART3_CR1			((volatile u32 *)(HWA_USART3+0x0C))
#define HWA_USART3_CR2			((volatile u32 *)(HWA_USART3+0x10))
#define HWA_USART3_CR3			((volatile u32 *)(HWA_USART3+0x14))
#define HWA_USART3_GTPR			((volatile u32 *)(HWA_USART3+0x18))

#define HWA_UART4_SR			((volatile u32 *)(HWA_UART4+0x00))
#define HWA_UART4_DR			((volatile u32 *)(HWA_UART4+0x04))
#define HWA_UART4_BRR			((volatile u32 *)(HWA_UART4+0x08))
#define HWA_UART4_CR1			((volatile u32 *)(HWA_UART4+0x0C))
#define HWA_UART4_CR2			((volatile u32 *)(HWA_UART4+0x10))
#define HWA_UART4_CR3			((volatile u32 *)(HWA_UART4+0x14))
#define HWA_UART4_GTPR			((volatile u32 *)(HWA_UART4+0x18))

#define HWA_UART5_SR			((volatile u32 *)(HWA_UART5+0x00))
#define HWA_UART5_DR			((volatile u32 *)(HWA_UART5+0x04))
#define HWA_UART5_BRR			((volatile u32 *)(HWA_UART5+0x08))
#define HWA_UART5_CR1			((volatile u32 *)(HWA_UART5+0x0C))
#define HWA_UART5_CR2			((volatile u32 *)(HWA_UART5+0x10))
#define HWA_UART5_CR3			((volatile u32 *)(HWA_UART5+0x14))
#define HWA_UART5_GTPR			((volatile u32 *)(HWA_UART5+0x18))

/*	Registers declarations: pname, type, address, reset value, write mask
 */
#define hwa_uart_begin_uart(pname, state)				\
  HWA_DECL(pname##_SR,   u32, HWA_##pname+0x00, 0x00000000, 0x00000360, state) \
  HWA_DECL(pname##_DR,   u32, HWA_##pname+0x04, 0x00000000, 0x00000100, state) \
  HWA_DECL(pname##_BRR,  u32, HWA_##pname+0x08, 0x00000000, 0x0000FFFF, state) \
  HWA_DECL(pname##_CR1,  u32, HWA_##pname+0x0C, 0x00000000, 0x000003FF, state) \
  HWA_DECL(pname##_CR2,  u32, HWA_##pname+0x10, 0x00000000, 0x00007F7F, state) \
  HWA_DECL(pname##_CR3,  u32, HWA_##pname+0x14, 0x00000000, 0x000007FF, state) \
  HWA_DECL(pname##_GTPR, u32, HWA_##pname+0x18, 0x00000000, 0x0000FFFF, state)

  /* _HWA_UART_DEF_GETCHAR(pname) */

/* _HWA_UART_DEF_GETCHAR(USART1) */
/* _HWA_UART_DEF_GETCHAR(USART2) */
/* _HWA_UART_DEF_GETCHAR(USART3) */
/* _HWA_UART_DEF_GETCHAR(UART4) */
/* _HWA_UART_DEF_GETCHAR(UART5) */

#define hwa_uart_begin(state)			\
  hwa_uart_begin_uart(USART1, state)		\
  hwa_uart_begin_uart(USART2, state)		\
  hwa_uart_begin_uart(USART3, state)		\
  hwa_uart_begin_uart(UART4, state)		\
  hwa_uart_begin_uart(UART5, state)

#define hwa_uart_commit_uart(dry, pname)		\
  HWA_COMMIT(dry, pname##_SR)				\
  HWA_COMMIT(dry, pname##_DR)				\
  HWA_COMMIT(dry, pname##_BRR)			\
  HWA_COMMIT(dry, pname##_CR1)			\
  HWA_COMMIT(dry, pname##_CR2)			\
  HWA_COMMIT(dry, pname##_CR3)			\
  HWA_COMMIT(dry, pname##_GTPR)

#define hwa_uart_commit(dry, )			\
  hwa_uart_commit_uart(dry, USART1)		\
  hwa_uart_commit_uart(dry, USART2)		\
  hwa_uart_commit_uart(dry, USART3)		\
  hwa_uart_commit_uart(dry, UART4)		\
  hwa_uart_commit_uart(dry, UART5)


/*	RM0008 Rev11 p. 747: BAUD = PCLK / (16 * USARTDIV)
 *
 *	USARTDIV = PCLK / (16 * BAUD)
 *
 *	PCLK == PCLK2 (i.e. APB2 clock, 72 MHz max) for USART1,
 *	PCLK == PCLK1 (36 MHz max) for all other.
 *
 *	USARTDIV is coded '12.4': 12 bits mantissa, 4 bits fraction, thus the
 *	16 bit value of this DIVISOR can be computed as:
 *		DIVISOR = (16 * PCLK) / (16 * BAUD)
 *	thus:
 *		DIVISOR = PCLK / BAUD
 *
 *	To get the nearest rounded value:
 *		DIVISOR = (PCLK + (BAUD+1)/2) / BAUD
 */
#define _hwa_uart_set_baudrate(pname, baudrate)				\
  if (HWA_##pname == HWA_USART1) {					\
    HWA_SET(pname##_BRR, 0xffff, 0, (APB2_HZ + (baudrate+1)/2) / baudrate); \
  } else {								\
    HWA_SET(pname##_BRR, 0xffff, 0, (APB1_HZ + (baudrate+1)/2) / baudrate); \
  }


#define _hwa_uart_set_databits(pname, nb)		\
  HWA_SET(pname##_CR1, 0b1,  12, HWA_UARTM_##nb)

#define HWA_UARTM_8				0
#define HWA_UARTM_9				1

#define _hwa_uart_turn_irq(pname, irq, state)				\
  HWA_SET(pname##_CR1, 0b1, HWA_UART_IRQBIT_##irq, HWA_STATE_##state)

#define HWA_UART_IRQBIT_RX			5

#define _hwa_uart_turn_rx(pname, state)			\
  HWA_SET(pname##_CR1, 0b1, 2, HWA_STATE_##state)

#define _hwa_uart_turn_tx(pname, state)			\
  HWA_SET(pname##_CR1, 0b1, 3, HWA_STATE_##state)

#define hwa_uart_config_txpin(pname, mode)				\
  _hwa_gpio_config_pins(PORTA, 1<<9, HWA_UART_TXPIN_ALTOUTPUT_##mode);

#define HWA_UART_TXPIN_ALTOUTPUT_PUSHPULL_10MHZ		0b10010
#define HWA_UART_TXPIN_ALTOUTPUT_PUSHPULL_2MHZ		0b10100
#define HWA_UART_TXPIN_ALTOUTPUT_PUSHPULL_50MHZ		0b10110
#define HWA_UART_TXPIN_ALTOUTPUT_OPENDRAIN_10MHZ	0b11010
#define HWA_UART_TXPIN_ALTOUTPUT_OPENDRAIN_2MHZ		0b11100
#define HWA_UART_TXPIN_ALTOUTPUT_OPENDRAIN_50MHZ	0b11110

#define hwa_uart_config_rxpin(pname, mode)				\
  _hwa_gpio_config_pins(PORTA, 1<<10, HWA_UART_RXPIN_INPUT_##mode);
#define HWA_UART_RXPIN_INPUT_FLOATING			0b01000
#define HWA_UART_RXPIN_INPUT_PULLDOWN			0b10000
#define HWA_UART_RXPIN_INPUT_PULLUP			0b10001

#define hwa_uart_set_stopbits(pname, nb)			\
  HWA_SET(pname##_CR2, 0b11, 12, HWA_UART_SB_##nb)
#define HWA_UART_SB_0_5				0b01
#define HWA_UART_SB_1				0b00
#define HWA_UART_SB_1_5				0b11
#define HWA_UART_SB_2				0b10

#define _hwa_uart_set_parity(pname, p)			\
  HWA_SET(pname##_CR2, 0b11,  9, HWA_UART_PARITY_##p)
#define HWA_UART_PARITY_NONE			0b00
#define HWA_UART_PARITY_EVEN			0b10
#define HWA_UART_PARITY_ODD			0b11

#define _hwa_uart_turn_hwctrl(pname, hwctrl)				\
  if (HWA_UART_HWCTRL_##hwctrl == HWA_UART_HWCTRL_OFF) {		\
    HWA_SET(pname##_CR3, 0b1,   9, 0);					\
    HWA_SET(pname##_CR3, 0b1,   8, 0);					\
  } else if (HWA_UART_HWCTRL_##hwctrl == HWA_UART_HWCTRL_CTS_ON) {	\
    HWA_SET(pname##_CR3, 0b1,   9, 1);					\
  } else if (HWA_UART_HWCTRL_##hwctrl == HWA_UART_HWCTRL_CTS_OFF) {	\
    HWA_SET(pname##_CR3, 0b1,   9, 0);					\
  } else if (HWA_UART_HWCTRL_##hwctrl == HWA_UART_HWCTRL_RTS_ON) {	\
    HWA_SET(pname##_CR3, 0b1,   8, 1);					\
  } else if (HWA_UART_HWCTRL_##hwctrl == HWA_UART_HWCTRL_RTS_OFF) {	\
    HWA_SET(pname##_CR3, 0b1,   8, 0);					\
    HWA_SET(pname##_CR3, 0b1,   8, 1);					\
  } else if (HWA_UART_HWCTRL_##hwctrl == HWA_UART_HWCTRL_ON) {		\
    HWA_SET(pname##_CR3, 0b1,   9, 1);					\
    HWA_SET(pname##_CR3, 0b1,   8, 1);					\
  }

#define HWA_UART_HWCTRL_OFF		0
#define HWA_UART_HWCTRL_CTS_ON		1
#define HWA_UART_HWCTRL_CTS_OFF		2
#define HWA_UART_HWCTRL_RTS_ON		3
#define HWA_UART_HWCTRL_RTS_OFF		4
#define HWA_UART_HWCTRL_ON		5

#define _hw_uart_data(pname)			\
  HWA_##pname##_DR

#define _hw_uart_tx_ready(pname)		\
  (HWA_BITS(*HWA_##pname##_SR, 0b1, 7) != 0)

#define _HW_UART_DEF_GETCHAR(pname)		\
  inline u8					\
  hw_##pname##_getchar()			\
  {						\
    while ( !hw_uart_rx_ready(pname) ) {}	\
    return *hw_uart_rxreg(pname) ;		\
  }

_HW_UART_DEF_GETCHAR(USART1)
_HW_UART_DEF_GETCHAR(USART2)
_HW_UART_DEF_GETCHAR(USART3)
_HW_UART_DEF_GETCHAR(UART4)
_HW_UART_DEF_GETCHAR(UART5)

#endif
