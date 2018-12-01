#!/bin/sh

set -e

#  We need to be in the examples/ directory
#
if [ ! -d make ] ; then
    echo "Not in the examples/ directory!"
    exit 1
fi

if [ ! -f "${FAILS}" ] ; then
    LOCAL=true
    FAILS=$(mktemp); export FAILS ;
else
    LOCAL=""
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
total=0
for BOARD in ${BOARDS} ; do
    examples_for_board ${BOARD}
    if [ -n "${EXAMPLES}" ] ; then
	echo Building examples for board ${BOARD}
	for i in ${EXAMPLES}
	do echo -n "  $i: "
	   total=$(($total + 1))
	   cd $i
	   if make -s all >/dev/null 2>&1 ; then
	       echo success
	       passed=$((passed+1))
	   else
	       echo failed
	       echo "  $i BOARD=${BOARD}" >>${FAILS}
	   fi
	   cd - >/dev/null
	done
    fi
done

fails=$(cat ${FAILS} | wc -l)
echo "$passed/$total succeeded." ; echo

if [ -n "$LOCAL" ] ; then
    if [ $passed -lt $total ] ; then
	echo "Fails:"
	cat ${FAILS}
	echo
    fi
    rm ${FAILS}
fi

exit $fails
