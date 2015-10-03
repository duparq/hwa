#!/bin/bash

#  We need to be in the examples/ directory
#
if [ $(basename "$PWD") != "examples" ] ; then
    echo "Not in the examples/ directory!"
    exit 1
fi

#  If no board name is given, do it for all boards
#
BOARDS=${BOARD}
if [ -z "$BOARDS" ] ; then
    BOARDS="attiny84 attiny85 nanodccduino pro-micro"
fi

#  Directory of this file
#
MFD=$(cd $(dirname $0) ; pwd)

compiled=0 ; passed=0 ; failed=0 ; skipped=0
for BOARD in ${BOARDS} ; do

    echo -e "\nChecking all examples in \"${PWD}\" for board \"${BOARD}\":"

    for i in $(find */ -name "main.c" | sort) ; do
	echo -n "$(dirname $i): "
	cd $(dirname $i)
	bash ${MFD}/check.sh
	R=$?
	if [ $R -eq 0 ] ; then
	    compiled=$((compiled+1))
	    passed=$((passed+1))
	elif [ $R -eq 4 ] ; then
	    skipped=$((skipped+1))
	elif [ $R -eq 6 ] ; then
	    skipped=$((skipped+1))
	else
	    compiled=$((compiled+1))
	    failed=$((failed+1))
	fi
	#echo "Result = " $R
	cd - >/dev/null
    done
done
echo -e "\n$compiled compiled, $passed successed, $failed failed, $skipped skipped."
