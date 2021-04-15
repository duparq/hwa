
#include "../hwa_1.h"
#include "../hwa_2.h"

/* #define hw_class__reset */
/* #define hw_reset		_reset */

/* #define hwa_begin__reset	, _hwa_begin_reset */

/* HW_XP(reset); */

/* HW_X(reset); */

/* hwa( begin ); */
/* hwa( begin, reset ); */
/* hwa( begin, all ); */
/* hwa( begin, reset, all ); */

#define hw_wait_irq		, _hw_wait_irq

HW_XP( irq );

HW_X( irq );

hw( wait, irq );

HW_X(counter0,irq);
HW_X(counter0,irq,overflow);
HW_X(counter0,irq,compare0);
HW_X(counter0,irq,mask);
HW_X(counter0,irq,compare0,mask);
HW_X(counter0);
HW_X(counter0,compare0);
HW_X(counter0,irq,compare0,mask);
HW_X(counter0,irq,compare0,flag);
HW_X(counter0,prescaler0);
HW_X(counter0,compare0,pin);
HW_X(counter0,compare0,pin,port,toto);

HW_X((counter0,compare0,pin));
HW_X((counter0,compare0),pin,port);
HW_X((counter0,compare0),pin,port);
HW_X(((counter0,compare0),pin,port));
HW_X((((counter0,compare0),pin),port));

HW_X(shared);
HW_X(shared, gimsk);

//_hwa_setup_r( shared, gimsk );

HW_X(watchdog0,irq);

/* hw(read,(watchdog,irq)); */

/* hwa( begin ); */
/* hwa( begin, reset ); */

//HW_ISR( watchdog0 );
/* HW_ISR( (watchdog0,irq) ); */
/* HW_ISR( (watchdog0,irq), naked ); */

/* hw( clear, (counter0,compare0,irq) ); */

/* HW_X((counter0,compare0,irq)); */

HW_ISR(counter0);
