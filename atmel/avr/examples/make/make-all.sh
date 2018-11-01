#!/bin/sh

set -e

#  We need to be in the examples/ directory
#
if [ ! -d make ] ; then
    echo "Not in the examples/ directory!"
    exit 1
fi

if [ ! -f "${FAILS}" ] ; then
    echo "FAILS is not a file"
    exit 1 ;
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
fails=0
for BOARD in ${BOARDS} ; do
    examples_for_board ${BOARD}
    if [ -n "${EXAMPLES}" ] ; then
	echo Building examples for board ${BOARD}
	for i in ${EXAMPLES}
	do echo -n "  $i: "
	   cd $i
	   if make -s all >/dev/null 2>&1 ; then
	       echo success
	       passed=$((passed+1))
	   else
	       echo failed
	       echo "  $i BOARD=${BOARD}" >>${FAILS}
	       fails=$((fails+1))
	   fi
	   cd - >/dev/null
	done
    fi
done ; echo "$passed succeeded, $fails failed." ; echo
exit $fails
