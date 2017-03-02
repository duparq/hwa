
/*  Prevent the SDK c_types.h from being loaded
 */
#define _C_TYPES_H_

#define uint64	uint64_t
#define uint32	uint32_t
#define uint16	uint16_t
#define sint16	int16_t
#define uint8	uint8_t
#define sint8	int8_t

typedef unsigned char	bool;
/* probably should not put STATUS here */
typedef enum {
    OK = 0,
    FAIL,
    PENDING,
    BUSY,
    CANCEL,
} STATUS;

#ifdef ICACHE_FLASH
#define ICACHE_FLASH_ATTR __attribute__((section(".irom0.text")))
#define ICACHE_RODATA_ATTR __attribute__((section(".irom.text")))
#else
#define ICACHE_FLASH_ATTR
#define ICACHE_RODATA_ATTR
#endif /* ICACHE_FLASH */

#define true		(1)
#define false		(0)
