
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Software-emulated TWI interface (master only)
 */

#if defined HW_DEVICE_ARCH_AVR
#  include "../../atmel/avr/classes/swtwimaster.h"
#else
#  error Class _swtwimaster is supported by Atmel AVR devices only.
#endif
