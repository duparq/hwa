
#include BOARD_H

HW_REGISTER(counter0,count)

HW_REGISTER(_counter0,count)

HW_REGISTER(counter0,_count)

HW_ADDRESS(HW_REGISTER(counter0,count))

HW_ADDRESS(HW_REGISTER(_counter0,count))

HW_ADDRESS(HW_REGISTER(counter0,_count))

#if HW_ADDRESS(HW_REGISTER(counter0,count)) < 0xFFFF
ADDRESS REGISTER counter0,count < 0xFFFF
#else
ADDRESS REGISTER counter0,count >= 0xFFFF
#endif

#if HW_ADDRESS(HW_REGISTER(_counter0,count)) < 0xFFFF
ADDRESS REGISTER counter0,count < 0xFFFF
#else
ADDRESS REGISTER counter0,count >= 0xFFFF
#endif
