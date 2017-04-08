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

#  Load the examples-for-board function
#
. ${MFD}/examples-for-board.sh

passed=0 ; failed=0 ; skipped=0 ; FAILS=""
for BOARD in ${BOARDS} ; do
    echo -e "Checking examples for board \"${BOARD}\":"
    examples_for_board $BOARD
    for E in $EXAMPLES ; do
	echo -n "  $E: "
	cd ${MFD}/../$E
	bash ${MFD}/check.sh
	R=$?
	if [ $R -eq 0 ] ; then
	    passed=$((passed+1))
	elif [ $R -eq 4 ] ; then
	    skipped=$((skipped+1))
	elif [ $R -eq 6 ] ; then
	    skipped=$((skipped+1))
	else
	    failed=$((failed+1))
	    FAILS="$FAILS\n  $BOARD: $E"
	fi
	#echo "Result = " $R
	cd - >/dev/null
    done
done
echo -e "$passed succeeded, $failed failed, $skipped skipped."
[ -n "$FAILS" ] && echo -e "Failed:$FAILS"
