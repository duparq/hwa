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
passed=0
failed=0
skipped=0
FAILS=""
for BOARD in ${BOARDS} ; do
    examples_for_board ${BOARD}
    if [ -n "${EXAMPLES}" ] ; then
	echo -e "Checking examples for board \"${BOARD}\":"
	for E in $EXAMPLES ; do
	    echo -n "  $E: "
	    cd $E
	    bash ../make/check.sh
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
	    cd - >/dev/null
	done
    fi
done
echo -e "$passed succeeded, $failed failed, $skipped skipped."
[ -n "$FAILS" ] && echo -e "Failed:$FAILS"
exit 0
