
/*
 *    https://github.com/pfalcon/esp-open-sdk/issues/279
 *
 *    cd esp-open-sdk/sdk
 *    ../xtensa-lx106-elf/bin/esptool.py -p /dev/ttyUSB0 write_flash -ff 40m -fm dout -fs 32m 0x3e000 bin/blank.bin 0x3fc000 bin/esp_init_data_default.bin 0x3fe000 bin/blank.bin
 *    cd esp-open-sdk/examples/blinky
 *    ../../xtensa-lx106-elf/bin/esptool.py -p /dev/ttyUSB0 write_flash -ff 40m -fm dout -fs 32m 0 blinky-0x00000.bin 0x10000 blinky-0x10000.bin
 *    python miniterm.py /dev/ttyUSB0 74880
 */

#include BOARD_H

#define IROM		__attribute__((section (".irom.text")))
#define IRAM

#if !defined LED
#  define LED		gpio5
#endif


/*  Function called every 10 ms
 *   * toggle the LED on/off every 200 ms
 *   * when the LED is turned on, turn TXD low for 100 ms
 *   * when the LED if turned off, send "ON\n" on TXD
 */
void IROM every10ms ( )
{
  static uint8_t	count ;
  static uint8_t	txdlow ;

  if ( txdlow ) {
    txdlow-- ;
    if ( txdlow == 0 )
      /*
       *  TXD has been set low for 100 ms. Release it now: connect pin GPIO1 to
       *  the TXD signal
       */
      hw( configure, gpio1, function, uart0_txd );
  }

  count++ ;
  if ( count < 20 )
    return ;

  /*  The following is done once every 200 ms
   */
  count = 0 ;

  hw( toggle, LED );
  
  if ( hw( read, LED ) == 1 ) {
    /*
     *	Turn TXD low for 100 ms: connect pin GPIO1 to the GPIO1 signal
     */
    txdlow = 10 ;
    hw( configure, gpio1, function, gpio );
  }
  else {
    /*
     *	Send message
     */
    os_printf("ON\n");
  }
}


void IROM user_init()
{
  hw( configure, LED,
      function,	 gpio,
      direction, output );

  /*  Pin GPIO1 is used alternatively as a GPIO and as pin TXD of hw_uart0.
   *
   *  After RESET, it is connected to uart0_txd so that we can send messages
   *  with os_printf().
   *
   *  We want a low level on that pin when used as a GPIO.
   */
  hw( write, gpio1, 0 );

  /*  Configure the UART
   *	Note: the OS has already configured the RXD and TXD pins
   */
  /* hw( configure, uart0, */
  /*     baudrate,	 9600, */
  /*     databits,	 8, */
  /*     parity,	 none, */
  /*     stopbits,	 1, */
  /*     /\* pin_txd,     hw_gpio1, *\/ */
  /*     /\* pin_rxd,     hw_gpio3, *\/ */
  /*     ); */

  os_printf("Hello World!\n");

  /*  Trigger a function call every 10 ms (about)
   */
  static os_timer_t timer ;

  os_timer_disarm( &timer );
  os_timer_setfn( &timer, (os_timer_func_t *)every10ms, NULL );
  os_timer_arm( &timer, 10, 1 );
}
