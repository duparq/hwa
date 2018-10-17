
/**
 * @example
 *
 * @par Toggle the function of GPIO1 between gpio and (uart0,txd).
 *
 * While booting, the ESP8266 sends messages on uart0 configured at 74880 bps.
 * Toggling DTR (miniterm.py: Ctrl+T,Ctrl+D) allows resetting the device and see these messages.
 *
 * On the Wemos board, the LED is connected to GPIO2 and is active low (and shared with UART1_TXD):
 *   * the LED is turned off and GPIO1 (TXD) is set low for 100 ms
 *   * the LED is turned on for 400 ms and the uart0 sends the uptime on TXD
 *
 * @par user.c
 */

/*    make install
 *    python miniterm.py /dev/ttyUSB0 74880
 */

#include BOARD_H

#define IROM		__attribute__((section (".irom.text")))
#define IRAM

#if !defined PIN_LED
#  define PIN_LED	gpio5
#endif


/*  Function called every 10 ms
 */
void IROM every10ms ( )
{
  static uint8_t	calls ;

  calls++ ;

  if ( calls == 10 ) {
    /*
     *	Configure GPIO1 as U0TXD to send a message
     */
    hw( write, PIN_LED, 1 );
    hw( configure, gpio1, function, (uart0,txd) );
    os_printf("%d\n", hw_uptime_us());
  }
  else if ( calls >= 50 ) {
    /*
     *	Configure GPIO1 as gpio1 to turn TXD low for 100 ms
     */
    calls = 0 ;
    hw( write, PIN_LED, 0 );
    hw( configure, gpio1, function, gpio, mode, digital_output );
    os_printf("FAIL!\n"); /* That will not be transmitted */
  }
}


void IROM user_init()
{
  os_printf("Hello World!\n");

  hw( configure, PIN_LED, mode, digital_output );

  /*  After RESET, GPIO1 is connected to (uart0,txd) so that we can send messages
   *  with os_printf().
   *
   *  Ensure that GPIO1 will be set low when configured as a GPIO.
   */
  hw( write, gpio1, 0 );
  hw( configure, PIN_LED, mode, digital_output );

  /*  Trigger a function call every 10 ms (about)
   */
  static os_timer_t timer ;

  os_timer_disarm( &timer );
  os_timer_setfn( &timer, (os_timer_func_t *)every10ms, NULL );
  os_timer_arm( &timer, 10, 1 );
}
