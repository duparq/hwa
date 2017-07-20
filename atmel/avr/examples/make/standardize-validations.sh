#!/bin/bash


strip() {
    # Remove all text between build and .text:
    sed -i '/build/,/.text:/d' $1
    # Replace multiple blank lines with single
    sed -i '/^$/N;/^\n$/D' $1
}

reconf() {
    # Extract CRC32 of the original configuration from the file name
    OLD=$(echo $i | egrep -o '[a-f0-9]{8}')
    # Compute CRC32 for new configuration
    egrep -h -o '^[_a-zA-Z0-9]+=".+"$' $i >/tmp/conf
    NEW=$(diabolo --crc32 /tmp/conf)
    # Rename file
    NAME=$(echo $i | sed -e "s/$OLD/$NEW/")
    if [ "$i" != "$NAME" ] ; then
	echo Rewrite configuration:
	echo "  $i"
	echo "  $NAME"
        mv $i $NAME
    fi
}

for i in $* ; do
    #echo "  $i: "
    strip $i
    RECONF=""
    if egrep -q '[_a-zA-Z0-9]+=[^"]' $i ; then
	# Quote configuration values
	perl -i -pe 's/([_a-zA-Z0-9]+)=([\._a-zA-Z0-9]+)/\1="\2"/g' $i
	RECONF=1
    fi
    if grep -q 'hw_pin_' $i ; then
	# Rename pins
	perl -i -pe 's/hw_pin_/pin_/g' $i
	RECONF=1
    fi
    if grep -q '="pin_' $i ; then
	# Rename pins
	perl -i -pe 's/="pin_/="/g' $i
	RECONF=1
    fi
    if grep -q '="hw_' $i ; then
	# Remove hw_ prefix from object names
	perl -i -pe 's/="hw_([a-z0-9]+)"/="\1"/g' $i
	RECONF=1
    fi
    if egrep -q '(="loop_up"|="loop_updown")' $i ; then
	# Rename counting mode
	perl -i -pe 's/="loop_up"/="up_loop"/g;' \
	     -pe 's/="loop_updown"/="updown_loop"/g;' $i
	RECONF=1
    fi
    if egrep -q '(="oc[0-9][0-9]")' $i ; then
	# Rename compare outputs
	perl -i -pe 's/="oc([0-9])([0-9])"/="counter\1compare\2"/g;' $i
	RECONF=1
    fi
    if [ -n "$RECONF" ] ; then
	reconf $i
    else
	echo "$i: nothing to do."
    fi
done
