
/*  This file is part of the HWA project.
 *  Copyright (c) 2018 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/*  Include the target board (and device) definitions
 */
#include BOARD_H

#include <hwa/ext/swtwimaster.h>
#include <hwa/ext/pcf8574.h>
#include <hwa/ext/hd44780.h>

#if HW_ADDRESS(twi0) != -1
#  define TWI		twi0
#else
#  define TWI		HW_SWTWIMASTER( scl, (portc,5),	\
					sda, (portc,4),	\
					bps, TWI_BPS )
#endif

#define TWI_BPS		100000

#define LCD		HW_HD44780( lines, 2,			\
				    cols,  16,			\
				    e,     (PCF, 1, 2),		\
				    rs,    (PCF, 1, 0),		\
				    rw,    (PCF, 1, 1),		\
				    data,  (PCF, 4, 4) )

/* #define LCD		HW_HD44780( lines, 2,			\ */
/* 				    cols,  16,			\ */
/* 				    e,     (portb,2),			\ */
/* 				    rs,    (portb,0),			\ */
/* 				    rw,    (portb,1),			\ */
/* 				    data,  (port1,4,4) ) */

#define PCF		HW_PCF8574( interface, TWI, address, 0x27 )

#define LCD_LED		(PCF, 1, 3)

HW_DECLARE( TWI );
HW_DECLARE( PCF );
HW_DECLARE( LCD );
