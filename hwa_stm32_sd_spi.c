
#include "tick.h"

#if defined BOARD_MINISTM32
#  define SOCKET_WP_CONNECTED      0
#  define SPI_SD                   SPI1
#  define GPIO_CS                  GPIOB
#  define RCC_APB2Periph_GPIO_CS   RCC_APB2Periph_GPIOB
#  define GPIO_Pin_CS              GPIO_Pin_6
#  define DMA_Channel_SPI_SD_RX    DMA1_Channel2
#  define DMA_Channel_SPI_SD_TX    DMA1_Channel3
#  define DMA_FLAG_SPI_SD_TC_RX    DMA1_FLAG_TC2
#  define DMA_FLAG_SPI_SD_TC_TX    DMA1_FLAG_TC3
#  define GPIO_SPI_SD              GPIOA
#  define GPIO_Pin_SPI_SD_SCK      GPIO_Pin_5
#  define GPIO_Pin_SPI_SD_MISO     GPIO_Pin_6
#  define GPIO_Pin_SPI_SD_MOSI     GPIO_Pin_7
#  define RCC_APBPeriphClockCmd_SPI_SD  RCC_APB2PeriphClockCmd
#  define RCC_APBPeriph_SPI_SD     RCC_APB2Periph_SPI1
/* - for SPI1 and full-speed APB2: 72MHz/4 */
#  define SPI_BaudRatePrescaler_SPI_SD  SPI_BaudRatePrescaler_4


//#  define SD_PS				/* power supply switch */

#  define SD_CP				PB5	/* 0: card present, 1: socket empty */
#  define SD_CS				PB7
#  define SD_SPI			SPI1
#else
#  error "Unsupported board"
#endif


#define select()	hwac_gpio_set_pin(SD_CS, 0)
#define deselect()	hwac_gpio_set_pin(SD_CS, 1)


static void
power_on ( )
{
  hwa_begin();
  hwa_turn_clk(HW_PORTNAME(SD_CS), ON);	// Enable GPIO clock for SDCard CS
  hwa_turn_clk(SD_SPI, ON);
  hwa_commit();

#if defined SD_PS
  /* power sdcard on */
#error Not implemented
#endif

#if defined SD_CP
  hwa_turn_clk(HW_PORTNAME(SD_CP), ON);
  hwa_gpio_config_pin(SD_CP, INPUT_FLOATING);
#endif

#if defined SD_WP
  /* Config WP pin */
#error Not implemented
#endif

  tick_delay_ms(250);

  hw_gpio_set_pin(SD_CS, 1); /* Deselect */
  hwa_gpio_config_pin(SD_CS, OUTPUT_PUSHPULL_50MHZ);
  hwa_gpio_config_pin(HWA_GLUE2(SD_SPI, _SCK), ALTOUTPUT_PUSHPULL_50MHZ);
  hwa_gpio_config_pin(HWA_GLUE2(SD_SPI, _MOSI), ALTOUTPUT_PUSHPULL_50MHZ);
  hwa_gpio_config_pin(HWA_GLUE2(SD_SPI, _MISO), INPUT_PULLUP);
  hwa_commit();

  hwa_spi_set_mode(SD_SPI, MASTER, 2LINES_RXTX);
  hwa_spi_set_datasize(SD_SPI, 8BITS);
  hwa_spi_set_clk_idle_state(SD_SPI, LOW);
  hwa_spi_set_clk_phase(SD_SPI, EDGE1);
  hwa_spi_set_slave_management(SD_SPI, SOFTWARE);
  hwa_spi_set_baudrate(SD_SPI, 281250);
  hwa_spi_set_shifting(SD_SPI, MSBFIRST);
  hwa_spi_set_crc_polynomial(SD_SPI, 7);
  hwa_spi_turn_crc_calculator(SD_SPI, OFF);
  hwa_spi_turn(SD_SPI, ON);
  hwa_commit();

  while (! hw_spi_tx_ready(SD_SPI)) {}
  *hw_spi_data(SD_SPI);

#if defined SD_USE_DMA
#error Not implemented
#endif

#if 0
  /* SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; // 72000kHz/256=281kHz < 400kHz
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;

  SPI_Init(SPI_SD, &SPI_InitStructure);
  SPI_CalculateCRC(SPI_SD, DISABLE);
  SPI_Cmd(SPI_SD, ENABLE);

  /* drain SPI */
  while (SPI_I2S_GetFlagStatus(SPI_SD, SPI_I2S_FLAG_TXE) == RESET) { ; }
  dummyread = SPI_I2S_ReceiveData(SPI_SD);

#ifdef STM32_SD_USE_DMA
  /* enable DMA clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
#endif
#endif
}
