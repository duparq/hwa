
#include <hwa/modules/esp-wroom-02.h>

#define LED		hw_pin_gpio5


/*  Function called every 250 ms
 *   * toggle the LED on/off every 200 ms
 */
void ICACHE_FLASH_ATTR every10ms ( )
{
  if ( hw_read( LED ) == 0 )
    hw_write( LED, 1 );
  else
    hw_write( LED, 0 );
}


void ICACHE_FLASH_ATTR user_init()
{
  /*  Configure the LED output
   */
  hw_config( LED,
  	     function,  gpio,			// Optionnal
  	     direction, output_when_awake
  	     );

  /*  Trigger a function call every 10 ms (about)
   */
  static os_timer_t timer ;

  os_timer_disarm( &timer );
  os_timer_setfn( &timer, (os_timer_func_t *)every10ms, NULL );
  os_timer_arm( &timer, 10, 1 );
}
