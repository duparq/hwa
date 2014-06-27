#!/bin/bash

#  Extract test function names and build "main" with them
#
SOURCE=$1
[ -f "$SOURCE" ] || exit 1

DST=build/${SOURCE/.c/.cp.c}

make $DST
echo "int main ( ) {"
grep -Po '(?<=^void )test[0-9A-Za-z_]*' "$DST" | (while read line ; do
    echo "extern void $line();"
    echo "$line();"
    done)
echo "return 0; }"
exit 0
