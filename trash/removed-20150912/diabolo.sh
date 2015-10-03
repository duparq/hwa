#!/bin/bash

# echo $0 $*
DIABOLO=$(dirname $0)/../diabolo/host/diabolo.py

#  Run Diabolo
#  Compute --keep-txd-low from available informations

#  Load dependencies
#
. ${OUTDIR}/out.diabolo
. ${OUTDIR}/out.hwa


#  Echo $1 as $1/1000 in %.3f format
#
format.3f() {
    i=$(($1 / 1000))
    t=$(($1 - 1000*$i))
    echo $i.$t
}

#  Device clock frequency in kHz (gives times in ms)
#
DEVICE_KHZ=$(($DEVICE_SYSHZ / 1000))

#  Startup time in ms (assume maximal of 32 KCK + 64 ms)
#
SUT=$((32768 / $DEVICE_KHZ + 1 + 64))

#  Time in ms necessary to compute CRC
#
CRC=$((30 * $DEVICE_FLASH_SIZE / $DEVICE_KHZ + 1))

#  Time in seconds TXD must be maintained low to enter Diabolo
#
KEEP_TXD_LOW=$(eval format.3f $(($SUT + $CRC)))

echo ${DIABOLO} --bps=$DIABOLO_BPS --keep-txd-low $KEEP_TXD_LOW --sync $DIABOLO_SYNC $*

${DIABOLO} --bps=$DIABOLO_BPS --keep-txd-low $KEEP_TXD_LOW --sync $DIABOLO_SYNC $*
