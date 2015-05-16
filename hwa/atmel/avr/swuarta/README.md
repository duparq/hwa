
Class `_swuarta` implements a software UART for 1 or 2-wire communication
with automatic baudrate detection capability.

`_swuarta` can work with an 8 or 16-bit counter. It can use any pin that
provides a pin-change interrupt.

Tested on ATtinyX4 with internal oscillator (~8 MHz):
-  1200..115200 bps with 16-bit timer not prescaled
-   450.. 50000 bps with 16-bit timer 1/8 prescaled
- 38400..115200 bps with  8-bit timer not prescaled
-         10000 bps with  8-bit timer 1/8 prescaled

This file is part of the HWA project.
Copyright (c) Christophe Duparquet <duparq at free dot fr>
All rights reserved. Read LICENSE.TXT for details.



START -> capture count : CY_STSEI
MATCH -> sample : CY_RXSEI

dt0 