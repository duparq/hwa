#!/bin/bash

#  We need to be in the examples/ directory
#
if [ ! -d make ] ; then
    echo "Not in the examples/ directory!"
    exit 1
fi

#  If no board name is given, do it for all boards
#
BOARDS=${BOARD}
[ -n "${BOARDS}" ] || BOARDS=$(cd boards ; ls *.h | sed -e 's/.h//g')

#  Load the examples-for-board function
#
. make/examples-for-board.sh

export BOARD	# used by make

for BOARD in ${BOARDS} ; do
    examples_for_board ${BOARD}
    if [ -n "${EXAMPLES}" ] ; then
	echo -e "Checking examples for board \"${BOARD}\":"
	for E in $EXAMPLES ; do
	    echo -n "  $E: "
	    cd $E
	    make --no-print-directory validate
	    cd - >/dev/null
	done
    fi
done
