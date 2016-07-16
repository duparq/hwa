#!/bin/bash

#  Check that the produced machine code is the same as the one that was
#  validated for a given configuration

#  We need a board name
#
if [ -z "$BOARD" ] ; then
    BOARD=$(readlink boards/default | sed -e 's/.h//' 2>/dev/null)
    if [ -z "$BOARD" ] ; then
	echo BOARD is not defined and no default board is set
	exit 1
    fi
fi

#echo -n "$(basename $PWD): "
OUT=build/${BOARD}/out
DIABOLO=$(dirname $0)/../diabolo/software/diabolo.py


#  Build .cfg file
#
if ! make BOARD=${BOARD} ${OUT}.cfg >/dev/null 2>&1 ; then
    echo "make FAILED"
    exit 2
fi

if ! test -f ${OUT}.cfg ; then
    echo "file \"${OUT}.cfg\" does not exist"
    exit 3
fi

#  Load the configuration to get HW_DEVICE
#
. ${OUT}.cfg

#  No need to go further if there is no validation for this device
#
if ! ls .valid-*-${HW_DEVICE}-* >/dev/null 2>&1 ; then
    echo no validation file for device "'"${HW_DEVICE}"'"
    exit 4
fi

#  Compute the configuration CRC
#
CFG_CRC=$(${DIABOLO} --crc32 ${OUT}.cfg | awk '{print $1}' )
if [ "$S_CRC" = "00000000" ] ; then
    echo "CRC32 generation failed"
    exit 5
fi

#  No need to go further is this configuration has never been validated
#
if ! ls .valid-*-${HW_DEVICE}-${CFG_CRC}-* >/dev/null 2>&1 ; then

    #  Try removing '"' that where not used in previous versions and alter the
    #  CRC
    #
    sed -e 's/"//g' ${OUT}.cfg >${OUT}.cfg.s
    CFG_CRC=$(${DIABOLO} --crc32 ${OUT}.cfg.s | awk '{print $1}' )
    if [ "$S_CRC" = "00000000" ] ; then
	echo "CRC32 generation failed"
	exit 5
    fi
    if ! ls .valid-*-${HW_DEVICE}-${CFG_CRC}-* >/dev/null 2>&1 ; then
	echo no validation file for this configuration
	exit 6
    fi
fi

#  Build .bin file
#
if ! make BOARD=${BOARD} ${OUT}.bin >/dev/null 2>&1 ; then
    echo "make FAILED"
    exit 7
fi

#  Compute CRC and size
#
O_CRC=$(${DIABOLO} -q -m ${HW_DEVICE} --crc ${OUT}.bin)
O_SIZE=$(${DIABOLO} -q -m ${HW_DEVICE} --size ${OUT}.bin)

# echo "CHECK: " ${HW_DEVICE}-$CFG_CRC-$O_SIZE-$O_CRC

if ls .valid-*-${HW_DEVICE}-$CFG_CRC-$O_SIZE-$O_CRC >/dev/null 2>&1 ; then
    echo success
    exit 0
fi

#  No validation file match. GCC version?
#
CCVERSION=$(avr-gcc -dumpversion)

if ! ls .valid-${CCVERSION}-${HW_DEVICE}-${CFG_CRC}-* >/dev/null 2>&1 ; then
    echo no validation file for avr-gcc version $CCVERSION
    exit 6
fi

echo CRC mismatch $O_CRC
exit 8
