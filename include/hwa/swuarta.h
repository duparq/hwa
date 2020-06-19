
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Software-emulated UART
 */

#if defined HW_DEVICE_ARCH_AVR
#  include "../../atmel/avr/classes/swuarta.h"
#else
#  error Class _swuarta is supported by Atmel AVR devices only.
#endif
