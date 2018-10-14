
/**
 * @example
 *
 * @par Blink a LED using an OS timer.
 *
 * This program configures the LED pin as a digital output, then in an infinite
 * loop it toggles the LED state using an OS timer.
 *
 * Symbols:
 *
 * * `BOARD_H` is the name of the target board definition file. It can be
 *   specified at compile time via the command line. If not, the Makefile will
 *   set it to `attiny84` by default. For example, `make BOARD=nanodccduino`
 *   will lead to `BOARD_H` defined as `<boards/nanodccduino.h>`. See @ref
 *   atmelavr_boards for the list of board definition files provided.
 *
 * * `PIN_LED` is the name of the I/O pin at which a LED is connected. It
 *   is defined in the target board header file.
 *
 * @par user.c
 */

#include BOARD_H

#define IROM		__attribute__((section (".irom.text")))
#define IRAM

#if !defined PIN_LED
#  define PIN_LED	gpio2
#endif


/*  Function called every 10 ms.
 *    Toggle the LED on/off.
 */
void IROM every10ms ( )
{
  if ( hw( read, PIN_LED ) == 0 )
    hw( write, PIN_LED, 1 );
  else
    hw( write, PIN_LED, 0 );
}


void IROM user_init()
{
  /*  Configure the LED output
   */
  hw( configure, PIN_LED, mode, digital_output );

  /*  Trigger a function call every 10 ms (about)
   */
  static os_timer_t timer ;

  os_timer_disarm( &timer );
  os_timer_setfn( &timer, (os_timer_func_t *)every10ms, NULL );
  os_timer_arm( &timer, 10, 1 );
}
