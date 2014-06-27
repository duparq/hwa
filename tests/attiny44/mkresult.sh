#!/bin/bash

SOURCE=$1
ELF=$2
BIN=$3
#F2=/tmp/hwa-$$-results


if [ -z "$SOURCE" ] ; then
    echo "No source." >&2
    exit 1
fi
if [ -z "$ELF" ] ; then
    echo "No elf." >&2
    exit 1
fi
if [ -z "$BIN" ] ; then
    echo "No bin." >&2
    exit 1
fi


#  Get test functions names from .elf, sort by addresses (hoping this will give
#  the same order as in the source file), and get their assembly code from .bin
#
avr-nm -S $ELF | grep "T test" | sort | (while read line ; do
    start=$(echo $line | cut -d' ' -f1)
    size=$(echo $line | cut -d' ' -f2)
    name=$(echo $line | cut -d' ' -f4)

    start=$(printf "%d" 0x$start)
    size=$(printf "%d" 0x$size)
    size=$(($size - 2))	# remove 'ret' code

    #echo "avr-objdump --start-address $start --stop-address $stop" >&2
    echo "$name: "
    if [ $size -gt 0 ] ; then
    	# hexdump -e'/1 "%02X"' -s $start -n $size $BIN ; echo
        stop=$(($start + $size))
	avr-objdump \
	    --start-address $start \
	    --stop-address $stop \
	    -b binary -D -m avr5 \
    	    $BIN | tail -n +8 | cut -b 16- | cut -d';' -f1
    fi
    echo
    done)

exit 0
